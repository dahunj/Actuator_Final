// Dispatcher.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "Dispatcher.h"

#include "LogFile.h"
#include "Common.h"
#include "SequenceMain.h"

#define UDP_DISPATCHER_LPORT	8020
#define UDP_DISPATCHER_HPORT	8020

IMPLEMENT_DYNAMIC(CDispatcher, CWnd)

CDispatcher g_objDispatcher;

CCriticalSection g_csDispatcher;	// Send_Command 문제 해결하기 위함

// CDispatcher

CDispatcher::CDispatcher()
{
	m_strRecvCmd = "";
	m_bConnected = FALSE;
	m_nMdjIndex = 0;
	m_nPortNo = 0;
	Reset(0);
}

CDispatcher::~CDispatcher()
{
}

BEGIN_MESSAGE_MAP(CDispatcher, CWnd)
	ON_MESSAGE(UM_UDP_CLIENT_RECEIVE, OnUdpClientReceive)
END_MESSAGE_MAP()

// CDispatcherer 메시지 처리기입니다.

BOOL CDispatcher::Initialize()
{
	BOOL bOpenRecv = m_UdpRecv.Open_Socket(UDP_DISPATCHER_LPORT, this);
	BOOL bOpenSend = m_UdpSend.Open_Socket(this);
	if (!bOpenRecv || !bOpenSend) return FALSE;

	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	CString strLog;
	strLog.Format("Initialize : Handler IP(%s), TimeOver(%d msec)", pRosData->sHandlerIp, pRosData->nJudgeTimeOver);
	g_objLogFile.Save_DispatcherLog(strLog);

	Set_ConnectRequest();

	return TRUE;
}

void CDispatcher::Terminate()
{

	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		CString strIp = pRosData->lstMdjIp.GetNext(pos);
		Set_ConnectEnd(strIp);
	}

	m_UdpRecv.Close_Socket();
	m_UdpSend.Close_Socket();

	g_objDataManager.Save_RosData();

	g_objLogFile.Save_DispatcherLog("Terminate");
}

void CDispatcher::Reset(int nPortNo)
{
	if (nPortNo == 0) {
		memset(m_bJudgeReq, 0x00, sizeof(BOOL) * 6 * 20 * 40);
		memset(m_dwReqStart, 0x00, sizeof(DWORD) * 6 * 20 * 40);
		memset(m_bJudgeDone, 0x00, sizeof(BOOL) * 6 * 20 * 40);
		memset(m_dwTimeStart, 0x00, sizeof(DWORD) * 6 * 20 * 40);
	} else {
		memset(m_bJudgeReq[nPortNo-1], 0x00, sizeof(BOOL) * 20 * 40);
		memset(m_dwReqStart[nPortNo-1], 0x00, sizeof(DWORD) * 20 * 40);
		memset(m_bJudgeDone[nPortNo-1], 0x00, sizeof(BOOL) * 20 * 40);
		memset(m_dwTimeStart[nPortNo-1], 0x00, sizeof(DWORD) * 20 * 40);
	}
}

///////////////////////////////////////////////////////////////////////////////
// UDP Socket Message

LRESULT CDispatcher::OnUdpClientReceive(WPARAM wLocalPort, LPARAM lParam)
{
	UINT nPort = (UINT)wLocalPort;
	BYTE byRecv[1025] = { 0 };
	CString strLog;

	int nLen = m_UdpRecv.Read_Socket(byRecv);

	if (nLen < 1) {
		strLog.Format("[H<-J] : Local Port (%d) Mismatch or Receive Data Zero (%d)", nPort, nLen);
		g_objLogFile.Save_DispatcherLog(strLog);
		return 0;
	}

	CString strRecvSocket;
	strRecvSocket.Format("%s", byRecv);
	m_strRecvCmd += strRecvSocket;

	while (!m_strRecvCmd.IsEmpty()) {
		int nStart = m_strRecvCmd.Find("@");
		int nEnd = m_strRecvCmd.Find("\n");

		if (nEnd < 0) break;	// 버퍼에 들어오는 중...

		if (nStart < 0 || nStart > nEnd) {
			strLog.Format("[H<-J] : <<Error>> %s : Start(%d), End(%d)", m_strRecvCmd, nStart, nEnd);
			g_objLogFile.Save_DispatcherLog(strLog);
			m_strRecvCmd.Delete(0, nEnd + 1);	// 쓰레기값이 채워져 있어서...
			continue;
		}

		CString strRecv = m_strRecvCmd.Mid(nStart + 1, nEnd - nStart - 1);
		m_strRecvCmd.Delete(0, nEnd + 1);

		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		if (!pEquipData->bUseROS) return 0;

		char chSep = ',';
		CString strCmd, strOp, strIp;

		AfxExtractSubString(strCmd, strRecv, 0, chSep);
		AfxExtractSubString(strOp, strRecv, 1, chSep);
		AfxExtractSubString(strIp, strRecv, 2, chSep);	// Recieve MDJ IP

		// Dispatcher Log /////////////////////////////////////////////////////
		strLog.Format("[H<-J] : %s", strRecv);
		g_objLogFile.Save_DispatcherLog(strLog);
		///////////////////////////////////////////////////////////////////////

		CString strArg[8];
		for (int i = 0; i < 8; i++) AfxExtractSubString(strArg[i], strRecv, i + 3, chSep);

		if (strCmd == "CONNECT") {
			if (strOp == "REQUEST")	Get_ConnectRequest(strIp);
			else if (strOp == "REPLY") Get_ConnectReply(strIp);
			else if (strOp == "END") Get_ConnectEnd(strIp);

		} else if (strCmd == "STATUS") {
			if (strOp == "REQUEST")	Get_StatusRequest(strIp);
			else if (strOp == "REPLY") Get_StatusReply(strArg[0]);
			else if (strOp == "UPDATE") Get_StatusUpdate(strArg[0]);

		} else if (strCmd == "JUDGE") {
			if (strOp == "REPLY") Get_JudgeReply(strArg[0], strArg[1], strArg[2], strArg[3], strArg[4], strArg[5], strArg[6], strArg[7]);

		} else if (strCmd == "INFO") {
			if (strOp == "REQUEST")	Get_InfoRequest(strIp);
		}
	}

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CDispatcher::Get_ConnectRequest(CString sIp)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	POSITION pos = pRosData->lstMdjIp.Find(sIp);
	if (!pos) pRosData->lstMdjIp.AddTail(sIp);

	Set_ConnectReply(sIp);
}

void CDispatcher::Get_ConnectReply(CString sIp)
{
	m_bConnected = TRUE;
}

void CDispatcher::Get_ConnectEnd(CString sIp)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	POSITION pos = pRosData->lstMdjIp.Find(sIp);
	if (pos) pRosData->lstMdjIp.RemoveAt(pos);
	Set_ConnectEnd(sIp);

	if (pRosData->lstMdjIp.GetCount() < 1) m_bConnected = FALSE;
}

void CDispatcher::Get_StatusRequest(CString sIp)
{
	int nEqStatus = (int)g_objSequenceMain.Is_MainThreadRun();
	Set_StatusReply(sIp, nEqStatus);
}

void CDispatcher::Get_StatusReply(CString sStatus)
{
	int nRosStatus = atoi(sStatus);
}

void CDispatcher::Get_StatusUpdate(CString sStatus)
{
	int nRosStatus = atoi(sStatus);
}

void CDispatcher::Get_InfoRequest(CString sIp)
{
	Set_InfoReply(sIp);
}

void CDispatcher::Get_JudgeReply(CString sModel, CString sLotId, CString sPortNo, CString sTrayNo, CString sCmNo, CString sBarcode, CString sCode, CString sJudge)
{
	CString strLog;
	int	nPx = atoi(sPortNo) - 1;	// Port Number Index (1 ~ 6)
	int	nTx = atoi(sTrayNo) - 1;	// Tray Number Index (1 ~ 20)
	int	nCx = atoi(sCmNo) - 1;		// Module Number Index (1 ~ 40)

	gData.nROSReqCount--; if (gData.nROSReqCount < 0) gData.nROSReqCount = 0;
	if (nPx < 0 || nPx > 5 || nTx < 0 || nTx > 19 || nCx < 0 || nCx > 39) {
		strLog.Format("[Get_JudgeReply] Receive Data Error1 ==> LotId(%s),JudgeReq(%d),TrayNo(%d),CmNo(%d),Judge(%s)", sLotId, (int)m_bJudgeReq, nTx+1, nCx+1, sJudge);
		g_objLogFile.Save_DispatcherLog(strLog);
		return;
	}

//	if (sJudge != "G" && sJudge != "N" && sJudge != "R" && sJudge != "1" && sJudge != "2" && sJudge != "3") {
	if (sJudge != "G" && sJudge != "N" && sJudge != "R") {
		strLog.Format("[Get_JudgeReply] Receive Data Error2 ==> LotId(%s),JudgeReq(%d),TrayNo(%d),CmNo(%d),Judge(%s)", sLotId, (int)m_bJudgeReq, nTx+1, nCx+1, sJudge);
		g_objLogFile.Save_DispatcherLog(strLog);
		return;
	}

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!m_bJudgeReq[nPx][nTx][nCx]) {
		strLog.Format("[Get_JudgeReply] Receive Data Error3 ==> LotId(%s),JudgeReq(%d),TrayNo(%d),CmNo(%d),Judge(%s)", sLotId, (int)m_bJudgeReq, nTx+1, nCx+1, sJudge);
		g_objLogFile.Save_DispatcherLog(strLog);
		return;
	}

	if (m_bJudgeDone[nPx][nTx][nCx] || gLot.nJudge_R[nPx][nTx][nCx] > 0) {
		strLog.Format("[Get_JudgeReply] Already been judged,LotId(%s),TrayNo(%d),CmNo(%d),Judge(%s),PreJudge(%d)", sLotId, nTx+1, nCx+1, sJudge, gLot.nJudge_R[nPx][nTx][nCx]);
		g_objLogFile.Save_DispatcherLog(strLog);
		return;
	}

	if (sJudge == "G") { gLot.nJudge_R[nPx][nTx][nCx] = 2; gLot.nRosJugCount[nPx][1]++;}	// Good
	if (sJudge == "N") { gLot.nJudge_R[nPx][nTx][nCx] = 3; gLot.nRosJugCount[nPx][3]++;}	// ROS NG
	if (sJudge == "R") { gLot.nJudge_R[nPx][nTx][nCx] = 4; gLot.nRosJugCount[nPx][4]++;}	// ROS Repair
	if (sCode.GetLength() > 0) {
		if (sJudge == "N") sCode.Replace("-", "_");
		gLot.sNGCode_I[nPx][nTx][nCx][0] = gLot.sNGCode_I[nPx][nTx][nCx][1] = sCode;
	}

	m_bJudgeDone[nPx][nTx][nCx] = TRUE;

	DWORD dwTerm = GetTickCount() - m_dwReqStart[nPx][nTx][nCx];
	strLog.Format("[Get_JudgeReply] Judge Result Bar(%s) PortNo(%s) TrayNo(%s) CmNo(%s) Judge(%s-%s) Time,%d", sBarcode, sPortNo, sTrayNo, sCmNo, sJudge, sCode, dwTerm);
	g_objLogFile.Save_DispatcherLog(strLog);
}

/////////////////////////////////////////////////////////////////////////////
// Set Command

void CDispatcher::Set_ConnectRequest()
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	CString	strSendCmd, strIp;
	strSendCmd.Format("CONNECT,REQUEST,%s", pRosData->sHandlerIp);

	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_ConnectReply(CString sIp)
{
	m_bConnected = TRUE;

	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,REPLY,%s", pRosData->sHandlerIp);
	Send_Command(sIp, strSendCmd);
}

void CDispatcher::Set_ConnectEnd(CString sIp)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,END,%s", pRosData->sHandlerIp);
	Send_Command(sIp, strSendCmd);
}

void CDispatcher::Set_StatusRequest()
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	CString	strSendCmd, strIp;
	strSendCmd.Format("STATUS,REQUEST,%s", pRosData->sHandlerIp);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_StatusReply(CString sIp, int nStatus)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REPLY,%s,%d", pRosData->sHandlerIp, nStatus);
	Send_Command(sIp, strSendCmd);
}

void CDispatcher::Set_StatusUpdate(int nStatus)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	CString	strSendCmd, strIp;
	strSendCmd.Format("STATUS,UPDATE,%s,%d", pRosData->sHandlerIp, nStatus);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_LotStart(int nPortNo)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	CString strLotId = gLot.sLotID[nPortNo-1];
	int nTrayUseCnt  = gLot.nTrayCount[nPortNo-1] - 1;
	int nCmUseCnt    = gLot.nCmCount[nPortNo-1];
	m_nPortNo = nPortNo;

	CString	strSendCmd, strIp;
	strSendCmd.Format("LOT,START,%s,%s,%s,%d,%d,%d", pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nPortNo, nTrayUseCnt, nCmUseCnt);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_LotEnd(int nPortNo)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	CString strLotId = gLot.sLotID[nPortNo-1];

	CString	strSendCmd, strIp;
	strSendCmd.Format("LOT,END,%s,%s,%s,%d", pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nPortNo);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

void CDispatcher::Set_InfoReply(CString sIp)
{
	if (m_nPortNo < 1) return;

	CString strLotId = gLot.sLotID[m_nPortNo-1];
	int nTrayUseCnt  = gLot.nTrayCount[m_nPortNo-1] - 1;
	int nCmUseCnt    = gLot.nCmCount[m_nPortNo-1];

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();

	CString	strSendCmd;
	strSendCmd.Format("INFO,REPLY,%s,%s,%s,%d,%d,%d", pRosData->sHandlerIp, pEquipData->sModelName, strLotId, m_nPortNo, nTrayUseCnt, nCmUseCnt);
	Send_Command(sIp, strSendCmd);
}

void CDispatcher::Set_JudgeRequest(int nPortNo, int nTrayNo, int nCmNo)
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) {
		m_bJudgeDone[nPortNo-1][nTrayNo-1][nCmNo-1] = TRUE;
		if (gLot.nJudge_I[nPortNo-1][nTrayNo-1][nCmNo-1][0] == 7 || gLot.nJudge_I[nPortNo-1][nTrayNo-1][nCmNo-1][0] == 8 || gLot.nJudge_I[nPortNo-1][nTrayNo-1][nCmNo-1][0] == 9) {
			gLot.nJudge_R[nPortNo-1][nTrayNo-1][nCmNo-1] = gLot.nJudge_I[nPortNo-1][nTrayNo-1][nCmNo-1][0];
			gLot.nRosJugCount[nPortNo-1][6]++;
		} else {
			gLot.nRosJugCount[nPortNo-1][0]++;
			gLot.nJudge_R[nPortNo-1][nTrayNo-1][nCmNo-1] = gLot.nJudge_I[nPortNo-1][nTrayNo-1][nCmNo-1][0] = 4;
			gLot.nRosJugCount[nPortNo-1][2]++;	//ROS미연결-> ROS-Repair
		}
		CString strLog;
		strLog.Format("ROS 미연결 ==> LotID(%s) Bar(%s) PortNo(%d) TrayNo(%d) CmNo(%d) SNo(%d)", gLot.sLotID[nPortNo-1], gLot.sBarCode[nPortNo-1][nTrayNo-1][nCmNo-1], nPortNo, nTrayNo, nCmNo, gLot.nJudge_R[nPortNo-1][nTrayNo-1][nCmNo-1]);
		g_objLogFile.Save_DispatcherLog(strLog);

		g_objCommon.Show_Error(9310);
		return;
	}

	//1번 기준 우상 -> 우하로 Convert (MES 전송시)
	//1번 기준 우하 -> 우상로 Convert (MES 수신시)
	int nPocket[40] = {37, 38, 39, 40, 33, 34, 35, 36, 29, 30,
					   31, 32, 25, 26, 27, 28, 21, 22, 23, 24,
					   17, 18, 19, 20, 13, 14, 15, 16,  9, 10,
					   11, 12,  5,  6,  7,  8,  1,  2,  3,  4 };

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	CString strLotId   = gLot.sLotID[nPortNo-1];
	CString strBarcode = gLot.sBarCode[nPortNo-1][nTrayNo-1][nCmNo-1];
	CString strNgCode  = gLot.sNGCode_I[nPortNo-1][nTrayNo-1][nCmNo-1][0];

	m_bJudgeReq[nPortNo-1][nTrayNo-1][nCmNo-1] = TRUE;
	m_bJudgeDone[nPortNo-1][nTrayNo-1][nCmNo-1] = FALSE;
	m_dwReqStart[nPortNo-1][nTrayNo-1][nCmNo-1] = GetTickCount();
	gLot.nJudge_I[nPortNo-1][nTrayNo-1][nCmNo-1][0] = 4;
	gData.nROSReqCount++; gLot.nRosJugCount[nPortNo-1][0]++;

	int nPocketNo = 0, nFind = 0;
	if (pEquipData->bUseMES && strBarcode.GetLength() > 10) {
		for (int i = 1; i < 640; i++) {
			if (strBarcode == gNG->sModuleID[nPortNo-1][i][0]) {
				int nINo = atoi(gNG->sModuleID[nPortNo-1][i][9]);
				if (nINo > 0 && nINo < 41) nPocketNo = nPocket[nINo-1];
				nFind = i+1; break;
			}
		}
	}

	CString	strSendCmd, strIp;
	if (gData.bJahwa) {
		strSendCmd.Format("JUDGE,REQUEST,%s,%s,%s,%d,%d,%d,%s,%s,%d",
			pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nPortNo, nTrayNo, nCmNo, strBarcode, strNgCode, gLot.nImageCnt[nPortNo-1][nTrayNo-1][nCmNo-1]);
	} else {
		if (nFind == 0) {
			strSendCmd.Format("JUDGE,REQUEST,%s,%s,%s,%d,%d,%d,%s,%s,0,%d,,,,,",
				pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nPortNo, nTrayNo, nCmNo, strBarcode, strNgCode, gLot.nImageCnt[nPortNo-1][nTrayNo-1][nCmNo-1]);
		} else {
			strSendCmd.Format("JUDGE,REQUEST,%s,%s,%s,%d,%d,%d,%s,%s,0,%d,%s,%s,%s,1,%d,%s",
				pRosData->sHandlerIp, pEquipData->sModelName, strLotId, nPortNo, nTrayNo, nCmNo, strBarcode, strNgCode, gLot.nImageCnt[nPortNo-1][nTrayNo-1][nCmNo-1],
				gNG->sModuleID[nPortNo-1][nFind-1][2], gNG->sModuleID[nPortNo-1][nFind-1][6], gNG->sModuleID[nPortNo-1][nFind-1][8], nPocketNo, gNG->sModuleID[nPortNo-1][nFind-1][7]);
			   //0:MODULEID,1:SITE,2:EQPID,3:EQPNAME,4:TOOL_CAVITY,5:PARA,6:DATE,7:ROS_JUDGE,8:DFA_LOTID,9:POCKETNO
		}
	}

	if (m_nMdjIndex >= pRosData->lstMdjIp.GetCount()) m_nMdjIndex = 0;	// 다시 첫번째 부터...

	POSITION pos = pRosData->lstMdjIp.FindIndex(m_nMdjIndex++);
	strIp = pRosData->lstMdjIp.GetAt(pos); 
	Send_Command(strIp, strSendCmd);
}

void CDispatcher::Set_TimeUpdate()
{
	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	if (pRosData->lstMdjIp.GetCount() < 1) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strTime;
	strTime.Format("%04d,%02d,%02d,%02d,%02d,%02d,%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	CString	strSendCmd, strIp;
	strSendCmd.Format("TIME,UPDATE,%s,%s", pRosData->sHandlerIp, strTime);
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		strIp = pRosData->lstMdjIp.GetNext(pos);
		Send_Command(strIp, strSendCmd);
	}
}

/////////////////////////////////////////////////////////////////////////////
// UDP Socket Send Message

void CDispatcher::Send_Command(CString sIp, CString sSend)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseROS) return;

	CString strLog;
	strLog.Format("[H->J] : %s", sSend);
	g_objLogFile.Save_DispatcherLog(strLog);

	CString strSendSocket;
	strSendSocket.Format("@%s\n", sSend);

	char chSend[1025] = { 0 };
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	g_csDispatcher.Lock();		// Critical Section
	m_UdpSend.Write_Socket(sIp, UDP_DISPATCHER_HPORT, (BYTE*)chSend, nLength);
	g_csDispatcher.Unlock();	// Critical Section
}

///////////////////////////////////////////////////////////////////////////////

BOOL CDispatcher::Is_JudgeDone(int nPortNo, int nTrayNo, int nCmNo)
{
	if (nPortNo == 0 || nTrayNo == 0 || nCmNo == 0 || gData.bCycleStop) return TRUE;

	if (!m_bJudgeReq[nPortNo-1][nTrayNo-1][nCmNo-1]) return TRUE;
	if (m_bJudgeDone[nPortNo-1][nTrayNo-1][nCmNo-1]) return TRUE;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	int nTerm = (int)(GetTickCount() - m_dwTimeStart[nPortNo-1][nTrayNo-1][nCmNo-1]);

	if (nTerm > pEquipData->nTimeOver[1]) {		// Time Over
		CString strLog;
		strLog.Format("Judge Time Over (%d msec),Bar(%s),PortNo(%d),TrayNo(%d),CmNo(%d), NG(%s)", pEquipData->nTimeOver[1], gLot.sBarCode[nPortNo-1][nTrayNo-1][nCmNo-1], nPortNo, nTrayNo, nCmNo, gLot.sNGCode_I[nPortNo-1][nTrayNo-1][nCmNo-1][0]);
		g_objLogFile.Save_DispatcherLog(strLog);
		m_bJudgeDone[nPortNo-1][nTrayNo-1][nCmNo-1] = TRUE;
		gLot.nJudge_R[nPortNo-1][nTrayNo-1][nCmNo-1] = gLot.nJudge_I[nPortNo-1][nTrayNo-1][nCmNo-1][0] = 4;
		gLot.nRosJugCount[nPortNo-1][2]++;	//ROS Timeout -> ROS-Repair
		gLot.sNGCode_I[nPortNo-1][nTrayNo-1][nCmNo-1][0] = "ROS Timeout";
		return TRUE;
	}
	return FALSE;
}

void CDispatcher::Set_TimeOver(int nPortNo, int nTrayNo, int nCmNo)
{
	m_dwTimeStart[nPortNo-1][nTrayNo-1][nCmNo-1] = GetTickCount();
}

/////////////////////////////////////////////////////////////////////////////

void CDispatcher::Test_Command(int nNo)
{
}
