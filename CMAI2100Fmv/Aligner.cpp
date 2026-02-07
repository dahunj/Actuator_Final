// Align.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "Aligner.h"

#include "LogFile.h"
#include "Common.h"

#include "WorkDlg.h"
#include "ManualDlg.h"
#include "SequenceMain.h"

#define UDP_PC4_HOST_IP		"192.168.0.31"
#define UDP_MAIN_LPORT		8010
#define UDP_MAIN_HPORT		8010
#define UDP_LD1_LPORT		8011
#define UDP_LD1_HPORT		8011
#define UDP_LD2_LPORT		8012
#define UDP_LD2_HPORT		8012
#define UDP_MD1_LPORT		8013
#define UDP_MD1_HPORT		8013
#define UDP_MD2_LPORT		8014
#define UDP_MD2_HPORT		8014
#define UDP_CP1_LPORT		8015
#define UDP_CP1_HPORT		8015
#define UDP_CP2_LPORT		8016
#define UDP_CP2_HPORT		8016

IMPLEMENT_DYNAMIC(CAligner, CWnd)

CAligner g_objAligner;

CCriticalSection g_csAligner;	// Send_Command 문제 해결하기 위함

// CAligner

CAligner::CAligner()
{
	m_strRecvCmd = "";

	m_bConnectAlignerLd1 = m_bConnectAlignerLd2 = FALSE;
	m_bConnectAlignerMd1 = m_bConnectAlignerMd2 = FALSE;
	m_bConnectAlignerCp1 = m_bConnectAlignerCp2 = FALSE;

	// Vision PC1 상태 (0:Not Ready, 1:Ready)
	m_nStatusAlignerLd1 = m_nStatusAlignerLd2 = 0;
	m_nStatusAlignerMd1 = m_nStatusAlignerMd2 = 0;
	m_nStatusAlignerCp1 = m_nStatusAlignerCp2 = 0;
}

CAligner::~CAligner()
{
}

BEGIN_MESSAGE_MAP(CAligner, CWnd)
	ON_WM_TIMER()
	ON_MESSAGE(UM_UDP_RECEIVE, OnUdpReceive)
END_MESSAGE_MAP()

// CAligner 메시지 처리기입니다.

void CAligner::Initialize()
{
	m_UdpAlignerMain.Open_Socket(UDP_MAIN_LPORT, UDP_MAIN_HPORT, UDP_PC4_HOST_IP, this);

	BOOL bAlignerLd1Opened = m_UdpAlignerLd1.Open_Socket(UDP_LD1_LPORT, UDP_LD1_HPORT, UDP_PC4_HOST_IP, this);
	BOOL bAlignerLd2Opened = m_UdpAlignerLd2.Open_Socket(UDP_LD2_LPORT, UDP_LD2_HPORT, UDP_PC4_HOST_IP, this);
	BOOL bAlignerMd1Opened = m_UdpAlignerMd1.Open_Socket(UDP_MD1_LPORT, UDP_MD1_HPORT, UDP_PC4_HOST_IP, this);
	BOOL bAlignerMd2Opened = m_UdpAlignerMd2.Open_Socket(UDP_MD2_LPORT, UDP_MD2_HPORT, UDP_PC4_HOST_IP, this);
	BOOL bAlignerCp1Opened = m_UdpAlignerCp1.Open_Socket(UDP_CP1_LPORT, UDP_CP1_HPORT, UDP_PC4_HOST_IP, this);
	BOOL bAlignerCp2Opened = m_UdpAlignerCp2.Open_Socket(UDP_CP2_LPORT, UDP_CP2_HPORT, UDP_PC4_HOST_IP, this);

	if (bAlignerLd1Opened) Set_ConnectRequest(ALIGNER_LD1);
	if (bAlignerLd2Opened) Set_ConnectRequest(ALIGNER_LD2);
	if (bAlignerMd1Opened) Set_ConnectRequest(ALIGNER_MD1);
	if (bAlignerMd2Opened) Set_ConnectRequest(ALIGNER_MD2);
	if (bAlignerCp1Opened) Set_ConnectRequest(ALIGNER_CP1);
	if (bAlignerCp2Opened) Set_ConnectRequest(ALIGNER_CP2);
}

void CAligner::Terminate()
{
	m_UdpAlignerMain.Close_Socket();

	Set_ConnectEnd(ALIGNER_LD1);
	Set_ConnectEnd(ALIGNER_LD2);
	Set_ConnectEnd(ALIGNER_MD1);
	Set_ConnectEnd(ALIGNER_MD2);
	Set_ConnectEnd(ALIGNER_CP1);
	Set_ConnectEnd(ALIGNER_CP2);

	m_UdpAlignerLd1.Close_Socket();
	m_UdpAlignerLd2.Close_Socket();
	m_UdpAlignerMd1.Close_Socket();
	m_UdpAlignerMd2.Close_Socket();
	m_UdpAlignerCp1.Close_Socket();
	m_UdpAlignerCp2.Close_Socket();
}

///////////////////////////////////////////////////////////////////////////////
// UDP Socket Message

void CAligner::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);
	switch (nIDEvent) {
	case ALIGNER_LD1: m_nStatusAlignerLd1 = 0; break;
	case ALIGNER_LD2: m_nStatusAlignerLd2 = 0; break;
	case ALIGNER_MD1: m_nStatusAlignerMd1 = 0; break;
	case ALIGNER_MD2: m_nStatusAlignerMd2 = 0; break;
	case ALIGNER_CP1: m_nStatusAlignerCp1 = 0; break;
	case ALIGNER_CP2: m_nStatusAlignerCp2 = 0; break;
	}
	CWnd::OnTimer(nIDEvent);
}

LRESULT CAligner::OnUdpReceive(WPARAM wLocalPort, LPARAM lParam)
{
	UINT nPort = (UINT)wLocalPort;
	int nAligner = 0, nLen = 0;
	BYTE byRecv[1024] = { 0 };
	CString strLog;

	if (nPort == UDP_MAIN_HPORT) { nAligner = ALIGNER_MAIN;	nLen = m_UdpAlignerMain.Read_Socket(byRecv); }
	if (nPort == UDP_LD1_HPORT)  { nAligner = ALIGNER_LD1;	nLen = m_UdpAlignerLd1.Read_Socket(byRecv); }
	if (nPort == UDP_LD2_HPORT)  { nAligner = ALIGNER_LD2;	nLen = m_UdpAlignerLd2.Read_Socket(byRecv); }
	if (nPort == UDP_MD1_HPORT)  { nAligner = ALIGNER_MD1;	nLen = m_UdpAlignerMd1.Read_Socket(byRecv); }
	if (nPort == UDP_MD2_HPORT)  { nAligner = ALIGNER_MD2;	nLen = m_UdpAlignerMd2.Read_Socket(byRecv); }
	if (nPort == UDP_CP1_HPORT)  { nAligner = ALIGNER_CP1;	nLen = m_UdpAlignerCp1.Read_Socket(byRecv); }
	if (nPort == UDP_CP2_HPORT)  { nAligner = ALIGNER_CP2;	nLen = m_UdpAlignerCp2.Read_Socket(byRecv); }

	if (nAligner == 0 || nLen < 1) {
		strLog.Format("[H<-V%d] : Local Port (%d) Mismatch or Receive Data Zero (%d)", nAligner, nPort, nLen);
		g_objLogFile.Save_AlignLog(strLog);
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
			strLog.Format("[H<-V%d] : <<Error>> %s : Start(%d), End(%d)", nAligner, m_strRecvCmd, nStart, nEnd);
			g_objLogFile.Save_AlignLog(strLog);
			m_strRecvCmd.Delete(0, nEnd + 1);	// 쓰레기값이 채워져 있어서...
			continue;
		}

		CString strRecv = m_strRecvCmd.Mid(nStart + 1, nEnd - nStart - 1);
		m_strRecvCmd.Delete(0, nEnd + 1);

		char chSep = ',';
		CString strCmd, strOp;

		AfxExtractSubString(strCmd, strRecv, 0, chSep);
		AfxExtractSubString(strOp, strRecv, 1, chSep);

		// Align Log ////////////////////////////////////////////
		if (strCmd != "STATUS" && strOp != "UPDATE") {
			strLog.Format("[H<-V%d] : %s", nAligner, strRecv);
			g_objLogFile.Save_AlignLog(strLog);
		}
		/////////////////////////////////////////////////////////

		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		if (nAligner == ALIGNER_LD1 && !pEquipData->bUseAlignLoad) return 0;
		if (nAligner == ALIGNER_LD2 && !pEquipData->bUseAlignLoad) return 0;
		if (nAligner == ALIGNER_MD1 && !pEquipData->bUseAlignModule) return 0;
		if (nAligner == ALIGNER_MD2 && !pEquipData->bUseAlignModule) return 0;
		if (nAligner == ALIGNER_CP1 && !pEquipData->bUseAlignCap) return 0;
		if (nAligner == ALIGNER_CP2 && !pEquipData->bUseAlignCap) return 0;

		CString strArg[8];
		for (int i = 0; i < 8; i++) AfxExtractSubString(strArg[i], strRecv, i + 2, chSep);

		if (strCmd == "CONNECT") {
			if (strOp == "REQUEST")	Get_ConnectRequest(nAligner);
			else if (strOp == "REPLY") Get_ConnectReply(nAligner);
			else if (strOp == "END") Get_ConnectEnd(nAligner);

		} else if (strCmd == "STATUS") {
			if (strOp == "REQUEST")	Get_StatusRequest(nAligner);
			else if (strOp == "REPLY") Get_StatusReply(nAligner, strArg[0]);
			else if (strOp == "UPDATE") Get_StatusUpdate(nAligner, strArg[0]);

		} else if (strCmd == "SCAN") {
			if (strOp == "COMPLETE") Get_ScanComplete(nAligner, strArg[0], strArg[1], strArg[2], strArg[3]);

		} else if (strCmd == "ALIGN") {
			if (strOp == "COMPLETE") Get_AlignComplete(nAligner, strArg[0], strArg[1], strArg[2], strArg[3], strArg[4], strArg[5], strArg[6], strArg[7]);

		} else if (strCmd == "TMOVE") {
			if (strOp == "REQUEST") Get_TMoveRequest(nAligner, strArg[0], strArg[1]);

		} else if (strCmd == "TIME") {
			if (strOp == "UPDATE") Get_TimeUpdate(nAligner, strArg[0]);
		}
	}

	return 1;
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CAligner::Get_ConnectRequest(int nAligner)
{
	if (nAligner == ALIGNER_LD1) m_bConnectAlignerLd1 = TRUE;
	if (nAligner == ALIGNER_LD2) m_bConnectAlignerLd2 = TRUE;
	if (nAligner == ALIGNER_MD1) m_bConnectAlignerMd1 = TRUE;
	if (nAligner == ALIGNER_MD2) m_bConnectAlignerMd2 = TRUE;
	if (nAligner == ALIGNER_CP1) m_bConnectAlignerCp1 = TRUE;
	if (nAligner == ALIGNER_CP2) m_bConnectAlignerCp2 = TRUE;

	Set_ConnectReply(nAligner);
}

void CAligner::Get_ConnectReply(int nAligner)
{
	if (nAligner == ALIGNER_LD1) m_bConnectAlignerLd1 = TRUE;
	if (nAligner == ALIGNER_LD2) m_bConnectAlignerLd2 = TRUE;
	if (nAligner == ALIGNER_MD1) m_bConnectAlignerMd1 = TRUE;
	if (nAligner == ALIGNER_MD2) m_bConnectAlignerMd2 = TRUE;
	if (nAligner == ALIGNER_CP1) m_bConnectAlignerCp1 = TRUE;
	if (nAligner == ALIGNER_CP2) m_bConnectAlignerCp2 = TRUE;
}

void CAligner::Get_ConnectEnd(int nAligner)
{
	if (nAligner == ALIGNER_LD1) m_bConnectAlignerLd1 = FALSE;
	if (nAligner == ALIGNER_LD2) m_bConnectAlignerLd2 = FALSE;
	if (nAligner == ALIGNER_MD1) m_bConnectAlignerMd1 = FALSE;
	if (nAligner == ALIGNER_MD2) m_bConnectAlignerMd2 = FALSE;
	if (nAligner == ALIGNER_CP1) m_bConnectAlignerCp1 = FALSE;
	if (nAligner == ALIGNER_CP2) m_bConnectAlignerCp2 = FALSE;
}

void CAligner::Get_StatusRequest(int nAligner)
{
	BOOL bStatus = g_objSequenceMain.Is_MainThreadRun();
	if (bStatus) Set_StatusReply(nAligner, 1);
	else Set_StatusReply(nAligner, 0);
}

void CAligner::Get_StatusReply(int nAligner, CString sStatus)
{
	if (nAligner == ALIGNER_LD1) m_nStatusAlignerLd1 = atoi(sStatus);
	if (nAligner == ALIGNER_LD2) m_nStatusAlignerLd2 = atoi(sStatus);
	if (nAligner == ALIGNER_MD1) m_nStatusAlignerMd1 = atoi(sStatus);
	if (nAligner == ALIGNER_MD2) m_nStatusAlignerMd2 = atoi(sStatus);
	if (nAligner == ALIGNER_CP1) m_nStatusAlignerCp1 = atoi(sStatus);
	if (nAligner == ALIGNER_CP2) m_nStatusAlignerCp2 = atoi(sStatus);
}

void CAligner::Get_StatusUpdate(int nAligner, CString sStatus)
{
	if (nAligner == ALIGNER_MAIN) return;
	if (nAligner != ALIGNER_LD1 && nAligner != ALIGNER_LD2 &&
		nAligner != ALIGNER_MD1 && nAligner != ALIGNER_MD2 &&
		nAligner != ALIGNER_CP1 && nAligner != ALIGNER_CP2) return;

	KillTimer(nAligner);
	if (nAligner == ALIGNER_LD1) m_nStatusAlignerLd1 = atoi(sStatus);
	if (nAligner == ALIGNER_LD2) m_nStatusAlignerLd2 = atoi(sStatus);
	if (nAligner == ALIGNER_MD1) m_nStatusAlignerMd1 = atoi(sStatus);
	if (nAligner == ALIGNER_MD2) m_nStatusAlignerMd2 = atoi(sStatus);
	if (nAligner == ALIGNER_CP1) m_nStatusAlignerCp1 = atoi(sStatus);
	if (nAligner == ALIGNER_CP2) m_nStatusAlignerCp2 = atoi(sStatus);
	SetTimer(nAligner, 15000, NULL);
}

void CAligner::Get_ScanComplete(int nAligner, CString sLotId, CString sMainNo, CString sSubNo, CString sGbn)
{
	int nErrType = 0;
	int	nMainNo = atoi(sMainNo);
	int	nSubNo  = atoi(sSubNo);

	if (nMainNo < 1 || nMainNo > 4 || nSubNo < 1 || nSubNo > 3) nErrType = 1;
	if (sGbn != "AL1" && sGbn != "AL2" && sGbn != "AM1" && sGbn != "AM2" && sGbn != "AC1" && sGbn != "AC2") nErrType = 2;

	if (nErrType == 0) return;

	if (g_dlgWork.IsWindowVisible()) {
		g_objCommon.Show_Error(6100 + nErrType);
// 		g_objSequenceMain.End_MainRunThread();
	}
}

void CAligner::Get_AlignComplete(int nAligner, CString sLotId, CString sMainNo, CString sSubNo, CString sGbn, CString sJurge, CString sX, CString sY, CString sA)
{
	int nErrType = 0;
	int nMainNo = atoi(sMainNo);
	int nSubNo  = atoi(sSubNo);
	double dX = atof(sX);
	double dY = atof(sY);
	double dA = atof(sA);
	
	if (nMainNo < 1 || nMainNo > 4 || nSubNo < 1 || nSubNo > 3) nErrType = 1;
	if (sJurge != "G" && sJurge != "N" && sJurge != "D" && sJurge != "E") nErrType = 2;
	int nIndex = 9;
	if		(sGbn == "AL1") nIndex = 0;
	else if (sGbn == "AL2") nIndex = 1;
	else if (sGbn == "AM1") nIndex = 2;
	else if (sGbn == "AM2") nIndex = 3;
	else if (sGbn == "AC1") nIndex = 4;
	else if (sGbn == "AC2") nIndex = 5;
	else nErrType = 3;

	if (nErrType != 0) return;

	if (sJurge == "G") {
		gData.dAlignX[nIndex] = dX;
		gData.dAlignY[nIndex] = dY;
		gData.dAlignR[nIndex] = dA;
		gData.bAlignDone[nIndex] = TRUE;
	} else {
		gData.dAlignX[nIndex] = 0.0;
		gData.dAlignY[nIndex] = 0.0;
		gData.dAlignR[nIndex] = 0.0;
		gData.bAlignDone[nIndex] = FALSE;

		if (g_dlgWork.IsWindowVisible()) {
			g_objCommon.Show_Error(6200 + nIndex);
		}
	}
}

void CAligner::Get_TMoveRequest(int nAligner, CString strGbn, CString strA)
{
	double dA = atof(strA);
	double dR = dA;
/*
	if		  (strGbn == "AL1") {
		if (g_dlgManual.IsWindowVisible()) {
			if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER1_R)) return;

			g_objAJinAXL.Move_Relative(AX_LOAD_PICKER1_R, dR);
			while (!g_objAJinAXL.Is_Done(AX_LOAD_PICKER1_R)) { DoEvents(); }

			Set_MoveComplete(nAligner, strGbn);
		}

	} else if (strGbn == "AL2") {
		if (g_dlgManual.IsWindowVisible()) {
			if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER2_R)) return;

			g_objAJinAXL.Move_Relative(AX_LOAD_PICKER2_R, dR);
			while (!g_objAJinAXL.Is_Done(AX_LOAD_PICKER2_R)) { DoEvents(); }

			Set_MoveComplete(nAligner, strGbn);
		}

	} else if (strGbn == "AM1") {
	} else if (strGbn == "AM2") {
	} else if (strGbn == "AC1") {
		if (g_dlgManual.IsWindowVisible()) {
			if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_R)) return;

			g_objAJinAXL.Move_Relative(AX_CAP_PICKER1_R, dR);
			while (!g_objAJinAXL.Is_Done(AX_CAP_PICKER1_R)) { DoEvents(); }

			Set_MoveComplete(nAligner, strGbn);
		}

	} else if (strGbn == "AC2") {
		if (g_dlgManual.IsWindowVisible()) {
			if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_R)) return;

			g_objAJinAXL.Move_Relative(AX_CAP_PICKER2_R, dR);
			while (!g_objAJinAXL.Is_Done(AX_CAP_PICKER2_R)) { DoEvents(); }

			Set_MoveComplete(nAligner, strGbn);
		}
	}
*/
}

void CAligner::Get_TimeUpdate(int nInspector, CString sTime)
{
	// sTime Format : "2000-01-01 12:30:30 000"
	CString strTemp;
	SYSTEMTIME time;

	strTemp = sTime.Mid(0, 4);  time.wYear = atoi(strTemp);			// Year
	strTemp = sTime.Mid(5, 2);  time.wMonth = atoi(strTemp);		// Month
	strTemp = sTime.Mid(8, 2);  time.wDay = atoi(strTemp);			// Day
	strTemp = sTime.Mid(11, 2); time.wHour = atoi(strTemp);			// Hour
	strTemp = sTime.Mid(14, 2); time.wMinute = atoi(strTemp);		// Minite
	strTemp = sTime.Mid(17, 2); time.wSecond = atoi(strTemp);		// Second
	strTemp = sTime.Mid(20, 3); time.wMilliseconds = atoi(strTemp);	// MilliSecond

	SetLocalTime(&time);
}

/////////////////////////////////////////////////////////////////////////////
// Set Command

void CAligner::Set_ConnectRequest(int nAligner)
{
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,REQUEST");
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_ConnectReply(int nAligner)
{
	CString	strSendCmd;
	strSendCmd.Format("CONNECT,REPLY");
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_ConnectEnd(int nAligner)
{
	CString	strSendCmd;
	strSendCmd = "CONNECT,END";
	Send_Command(nAligner, strSendCmd);

	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_LD1) m_bConnectAlignerLd1 = FALSE;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_LD2) m_bConnectAlignerLd2 = FALSE;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_MD1) m_bConnectAlignerMd1 = FALSE;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_MD2) m_bConnectAlignerMd2 = FALSE;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_CP1) m_bConnectAlignerCp1 = FALSE;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_CP2) m_bConnectAlignerCp2 = FALSE;
}

void CAligner::Set_StatusRequest(int nAligner)
{
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_LD1) m_nStatusAlignerLd1 = 0;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_LD2) m_nStatusAlignerLd2 = 0;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_MD1) m_nStatusAlignerMd1 = 0;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_MD2) m_nStatusAlignerMd2 = 0;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_CP1) m_nStatusAlignerCp1 = 0;
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_CP2) m_nStatusAlignerCp2 = 0;

	CString	strSendCmd;
	strSendCmd.Format("STATUS,REQUEST");
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_StatusReply(int nAligner, int nStatus)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,REPLY,%d", nStatus);
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_StatusUpdate(int nAligner, int nStatus)
{
	CString	strSendCmd;
	strSendCmd.Format("STATUS,UPDATE,%d", nStatus);
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_LotStart(int nAligner)
{
	CString	strSendCmd;
	strSendCmd.Format("LOT,START,%s,%d,%d", gData.sLotID, gData.nTrayUseCount, gData.nCmUseCount);
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_LotEnd(int nAligner)
{
	CString	strSendCmd;
	strSendCmd.Format("LOT,END,%s", gData.sLotID);
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_LoadComplete(int nAligner, int nMainNo, int nSubNo, CString sGbn)
{
	int nAno = 0;
	if		(sGbn == "AL1") nAno = 0;
	else if (sGbn == "AL2") nAno = 1;
	else if (sGbn == "AM1") nAno = 2;
	else if (sGbn == "AM2") nAno = 3;
	else if (sGbn == "AC1") nAno = 4;
	else if (sGbn == "AC2") nAno = 5;
	else if (sGbn == "AS1") nAno = 6;
	else if (sGbn == "AS2") nAno = 7;
	else return;

	gData.bAlignDone[nAno] = FALSE;
	gData.dAlignX[nAno] = gData.dAlignY[nAno] = gData.dAlignR[nAno] = 0.0;

	CString	strSendCmd;
	strSendCmd.Format("LOAD,COMPLETE,%s,%d,%d,%s", gData.sLotID, nMainNo, nSubNo, sGbn);
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_MoveComplete(int nAligner, CString sGbn)
{
	CString	strSendCmd;
	strSendCmd.Format("MOVE,COMPLETE,%s", sGbn);
	Send_Command(nAligner, strSendCmd);
}

void CAligner::Set_TimeUpdate(int nAligner)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strTime;
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d %03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	CString	strSendCmd;
	strSendCmd.Format("TIME,UPDATE,%s", strTime);
	Send_Command(nAligner, strSendCmd);
}

///////////////////////////////////////////////////////////////////////////////

int CAligner::Get_VisionStatus(int nAligner)
{
	switch (nAligner) {
	case ALIGNER_LD1:	return m_nStatusAlignerLd1;
	case ALIGNER_LD2:	return m_nStatusAlignerLd2;
	case ALIGNER_MD1:	return m_nStatusAlignerMd1;
	case ALIGNER_MD2:	return m_nStatusAlignerMd2;
	case ALIGNER_CP1:	return m_nStatusAlignerCp1;
	case ALIGNER_CP2:	return m_nStatusAlignerCp2;
	default:			return 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// UDP Socket Send Message

void CAligner::Send_Command(int nAligner, CString strSend)
{
	// Align Log //////////////////////////////////////
	CString strLog;
	strLog.Format("[H->V%d] : %s", nAligner, strSend);
	g_objLogFile.Save_AlignLog(strLog);
	///////////////////////////////////////////////////////

	g_csAligner.Lock();	// Critical Section

	CString strSendSocket;
	strSendSocket.Format("@%s\n", strSend);

	char chSend[1024] = { 0 };
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_LD1) m_UdpAlignerLd1.Write_Socket((BYTE*)chSend, nLength);
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_LD2) m_UdpAlignerLd2.Write_Socket((BYTE*)chSend, nLength);
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_MD1) m_UdpAlignerMd1.Write_Socket((BYTE*)chSend, nLength);
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_MD2) m_UdpAlignerMd2.Write_Socket((BYTE*)chSend, nLength);
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_CP1) m_UdpAlignerCp1.Write_Socket((BYTE*)chSend, nLength);
	if (nAligner == ALIGNER_ALL || nAligner == ALIGNER_CP2) m_UdpAlignerCp2.Write_Socket((BYTE*)chSend, nLength);
	if (nAligner == ALIGNER_MAIN) m_UdpAlignerMain.Write_Socket((BYTE*)chSend, nLength);

	g_csAligner.Unlock();	// Critical Section
}
/////////////////////////////////////////////////////////////////////////////

void CAligner::DoEvents(int nSleep)
{
	MSG msg;
	if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (nSleep > 0) Sleep(nSleep);
}

/////////////////////////////////////////////////////////////////////////////

void CAligner::Test_Command(int nNo)
{
}
