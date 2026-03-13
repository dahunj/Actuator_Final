// MesAgent.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "Inspector.h"
#include "LogFile.h"
#include "Common.h"
#include "SequenceMain.h"
//#include "OperatorDlg.h"
#include "MesAgent.h"

#define	MES_AGENT_IP	"127.0.0.1"
#define MES_AGENT_PORT	10000		// MesAgent Handler Port

IMPLEMENT_DYNAMIC(CMesAgent, CWnd)

CMesAgent g_objMesAgent;

// CMesAgent

CMesAgent::CMesAgent()
{
	m_bConnected = FALSE;
	m_bHostOnline = FALSE;
	m_strRecvCmd = "";
	for(int i=0; i<100; i++) m_sSizeNG[i] = "";
}

CMesAgent::~CMesAgent()
{
}

BEGIN_MESSAGE_MAP(CMesAgent, CWnd)
	ON_WM_TIMER()
	ON_MESSAGE(UM_CLIENT_CONNECT, OnClientConnect)
	ON_MESSAGE(UM_CLIENT_RECEIVE, OnClientReceive)
	ON_MESSAGE(UM_CLIENT_CLOSE, OnClientClose)
END_MESSAGE_MAP()

// CMesAgent 메시지 처리기입니다.

void CMesAgent::Initialize()
{
	if (m_bConnected) return;

	m_Client.Open_Socket(MES_AGENT_IP, MES_AGENT_PORT, this);	Sleep(3000);

	CString sLog, sKey;
	CIniFileCS INI(gsCurrentDir + "\\System\\SizeNGOrder.ini");
	if (!INI.Check_File()) {
		sLog.Format("MesAgent-Initialize => SizeNGOrder.ini File Not Found!!!!");
		g_objLogFile.Save_MesAgentLog(sLog);
		AfxMessageBox(sLog);
		return;
	}

	m_nSizeCount = INI.Get_Integer("SIZENG", "COUNT", 0);
	if (m_nSizeCount > 100) m_nSizeCount = 100;
	for(int i=0; i<m_nSizeCount; i++) {
		sKey.Format("%02d", i+1);
		m_sSizeNG[i] = INI.Get_String("SIZENG", sKey, "");
	}		

	sLog.Format("MesAgent Initialize. SizeNG Count=%d", m_nSizeCount);
	g_objLogFile.Save_MesAgentLog(sLog);
}

void CMesAgent::Terminate()
{
	m_bConnected = FALSE;
	m_bHostOnline = FALSE;
	m_Client.Close_Socket();

	g_objLogFile.Save_MesAgentLog("MesAgent Terminate.");	Sleep(500);
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CMesAgent::OnClientConnect(WPARAM wConnect, LPARAM lParam)
{
	m_bConnected = (BOOL)wConnect;
	if (!m_bConnected) return 0;

	Set_OperUpdate(gData.sOperID);
	Set_EquipState(4);	//Ready
	g_objLogFile.Save_MesAgentLog("MesAgent Connected");
	return 0;
}

LRESULT CMesAgent::OnClientClose(WPARAM wParam, LPARAM lParam)
{
	m_bConnected = FALSE;
	m_bHostOnline = FALSE;
	m_Client.Close_Socket();
	g_objLogFile.Save_MesAgentLog("MesAgent Disconnected");
	return 0;
}

LRESULT CMesAgent::OnClientReceive(WPARAM wParam, LPARAM lParam)
{
	BYTE byRecv[1025] = { 0 };	// Buffer 1024, Last 0x00
	int nLen = m_Client.Read_Socket(byRecv);

	CString strRecvSocket, strLog;
	strRecvSocket.Format("%s", byRecv);
	m_strRecvCmd += strRecvSocket;

	while (!m_strRecvCmd.IsEmpty()) {
		int nStart = m_strRecvCmd.Find("@");
		int nEnd = m_strRecvCmd.Find("\n");

		if (nEnd < 0) break;	// 버퍼에 들어오는 중...

		if (nStart < 0 || nStart > nEnd) {
			strLog.Format("[<-] : <<Error>> %s : Start(%d), End(%d)", m_strRecvCmd, nStart, nEnd);
			g_objLogFile.Save_MesAgentLog(strLog);
			m_strRecvCmd.Delete(0, nEnd + 1);	// 쓰레기값이 채워져 있어서...
			continue;
		}

		CString strRecv = m_strRecvCmd.Mid(nStart + 1, nEnd - nStart - 1);
		m_strRecvCmd.Delete(0, nEnd + 1);

		// Inspector Log ////////////////////////////////////////////////////////////
		strLog.Format("[<-] : %s", strRecv);
		g_objLogFile.Save_MesAgentLog(strLog);
		/////////////////////////////////////////////////////////////////////////////

		char chSep = ',';
		CString strCmd, strOp;

		AfxExtractSubString(strCmd, strRecv, 0, chSep);
		AfxExtractSubString(strOp, strRecv, 1, chSep);

		CString strArg[10];
		for (int i = 0; i < 7; i++) AfxExtractSubString(strArg[i], strRecv, i + 2, chSep);

		if (strCmd == "CONTROL") {
			if (strOp == "STATE") Get_ControlState(strArg[0]);

		} else if (strCmd == "LOT") {
			if (strOp == "START")  Get_LotStart(strArg[0], strArg[1], strArg[2], strArg[3], strArg[4]);
			if (strOp == "CANCEL") Get_LotCancel(strArg[0], strArg[1],  strArg[2]);

		} else if (strCmd == "TIME") {
			if (strOp == "UPDATE") Get_TimeSync();

		} else if (strCmd == "RECIPE") {
			if (strOp == "REQUEST") Get_RecipeList(strArg[0]);
			if (strOp == "SELECT") Get_PPSelect(strArg[0], strArg[1]);
			if (strOp == "COMPLETE") Get_PPSelectCompletedReport(strArg[0], strArg[1]);
			if (strOp == "FAIL")	Get_PPSelectFail(strArg[0], strArg[1], strArg[2], strArg[3]);

		} else if (strCmd == "CM") {
			if (strOp == "RESULT") Get_CmResult(strArg[0], strArg[1],  strArg[2], strArg[3], strArg[4], strArg[5]);
			if (strOp == "FAIL")   Get_CmFail(strArg[0], strArg[1], strArg[2], strArg[3]);

		} else if (strCmd == "HOST") {
			if (strOp == "MESSAGE") Get_HostMessage(strArg[0]);

		} else if (strCmd == "MODULE") 
		{
			if (strOp == "DATA1") Get_ModuleData1(strRecv);
			if (strOp == "DATA2") Get_ModuleData2(strRecv);
		} 
		else if (strCmd == "NGLOT")
		{
			if (strOp == "START")  Get_NGLotStart(strArg[0], strArg[1], strArg[2]);
//			if (strOp == "CANCEL") Get_LotCancel(strArg[0], strArg[1],  strArg[2]);

		}
		else if (strCmd == "RMS")
		{
			if (strOp == "ALREADYDONE") Get_RMSAlreadyDone();
			if (strOp == "LOADDONE") Get_RMSAlreadyDone();
		}
	}

	return 0;
}

void CMesAgent::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);
/*
	if (gMes.nMarStatus == 3) {
		if (GetTickCount() - m_dwStart > 5000) {
			Set_NGLotEnd(m_sNGLotID, m_nNGCount);
			KillTimer(0);
			return;
		}
	}
	SetTimer(0, 100, NULL);
	CWnd::OnTimer(nIDEvent);
*/
}

///////////////////////////////////////////////////////////////////////////////
// Get Command

void CMesAgent::Get_ControlState(CString sFlag)
{
	int nOnline = atoi(sFlag);	// 1:Online, 2:Offline
// 	if (m_bHostOnline && nOnline == 2) g_objCommon.Show_Error(9006);	// Agent 에서 Offline 변경
	if (nOnline == 1 && m_bHostOnline == FALSE) Set_OperUpdate(gData.sOperID);
	m_bHostOnline = (nOnline == 1 ? TRUE : FALSE);
}

void CMesAgent::Get_LotStart(CString sLotId, CString sRecipe, CString sCmCount, CString sVendor, CString sConfig)
{
	int nPortNo = 99;
	int nCmCount = atoi(sCmCount);

	if (gMes.sHostNGConfig.GetLength() > 1 && sConfig.GetLength() > 1 && gMes.sHostNGConfig != sConfig) {
		gMes.sMESConfig = sConfig;
		g_objCommon.Show_Error(9117); return;
	}

//#ifndef AJIN_BOARD_USE
//	nCmCount = 640;
//	sLotId = "TEST1234";
//	sRecipe = "A53B_DPAMS_REV0";
//	sCmCount = "320";
//	sVendor = "DPAMS";
//	sConfig = "";
//
//#endif
	gMes.nHostRcvCmCount = nCmCount;
	gMes.sHostCancelLotId = sLotId;
	gMes.sHostCancelCode = sRecipe;
	gMes.sHostCancelText = sCmCount;
	gMes.sHostVendor = sVendor;
	gMes.sHostConfig = sConfig;
	m_sStartLot = sLotId;

	for(int i=0; i<6; i++) {
		if (gLot.sLotID[i] == sLotId) { nPortNo = i; break; }
	}
	if (nPortNo > 90 || sLotId.GetLength() < 2) { g_objCommon.Show_Error(9009); return; }

	gMes.sHostRecipe[nPortNo]  = sRecipe;
	gMes.nHostCmCount[nPortNo] = nCmCount;

	if (sRecipe.GetLength() < 1) { g_objCommon.Show_Error(9001); return; }
//	if (gLot.nCmCount[nPortNo] != nCmCount) { g_objCommon.Show_Error(9010); return; }

	if (Exist_Recipe(sRecipe) == FALSE) 
	{
		g_objCommon.Show_Error(9007);	return;
	}
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (sRecipe != pEquipData->sModelName) 
	{
		if (pEquipData->bUseMESRcpCheck)
		{
			g_objCommon.Show_Error(9008);	return;
		}
		g_objCommon.Display_MESRecipe(sRecipe);
	}
		
	gMes.nLotStatus[nPortNo]++;	//Lot수신1
	g_objCommon.Set_LotCount(nPortNo+1, sLotId, nCmCount);
}

void CMesAgent::Get_LotCancel(CString sLotId, CString sCode, CString sText)
{
	gMes.sHostCancelLotId = sLotId;
	gMes.sHostCancelCode = sCode;
	gMes.sHostCancelText = sText;

	int nPortNo = 99;
	for(int i=0; i<6; i++) {
		if (gLot.sLotID[i] == sLotId) { nPortNo = i; break; }
	}
	if (nPortNo > 10 || sLotId.GetLength() < 2) {
		g_objCommon.Show_Error(9002);
		return;
	}

	gMes.nLotStatus[nPortNo] = 9;	//Lot취소
	g_objCommon.Show_Error(9002);
}

void CMesAgent::Get_TimeSync()
{
	g_objInspector.Set_TimeUpdate(INSPECTOR_ALL);
}

void CMesAgent::Get_RecipeList(CString sFlag)		// 0:All, 1:Current Recipe
{
	int nType = atoi(sFlag);
	Set_RecipeList(nType);
}

void CMesAgent::Get_CmResult(CString sLotId, CString sCmId, CString sJudge, CString sNgCode, CString sNgText, CString sMarginal)
{
	CString	strLog;

	int nPortNo = 99;
	for(int i=0; i<6; i++) {
		if (gLot.sLotID[i] == sLotId) { nPortNo = i; break; }
	}
	if (nPortNo > 10 || sLotId.GetLength() < 2) {
		strLog.Format("MESAgent ReciveData LotID error => (%s) (%s) (%s) (%s) (%s) (%s)", sLotId, sCmId, sJudge, sNgCode, sNgText, sMarginal);
		g_objLogFile.Save_MesAgentLog(strLog);
		return;
	}
	if (sCmId.GetLength() < 10) {
		strLog.Format("MESAgent ReciveData ModuleID error => (%s) (%s) (%s) (%s) (%s) (%s)", sLotId, sCmId, sJudge, sNgCode, sNgText, sMarginal);
		g_objLogFile.Save_MesAgentLog(strLog);
		return;
	}
	
	int nTray = -1, nCmNo = -1;
	for(int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			if (gLot.sBarCode[nPortNo][i][j] == sCmId) {
				nTray = i, nCmNo = j;	break;
			}
		}
		if (nTray > -1) break;
	}
	if (nTray == -1 || nCmNo == -1) {
		strLog.Format("MESAgent ReciveData ModuleID Not Found => (%s) (%s) (%s) (%s) (%s) (%s)", sLotId, sCmId, sJudge, sNgCode, sNgText, sMarginal);
		g_objLogFile.Save_MesAgentLog(strLog);
		return;
	}

//	gMes.sCmCode[nPortNo][nTray][nCmNo] = sNgCode;
//	gMes.sCmText[nPortNo][nTray][nCmNo] = sNgText;	// Result Done
	if (sJudge == "NG") {
		gMes.nCmResult[nPortNo][nTray][nCmNo] = 2;
	} else {
		if (gMes.nCmResult[nPortNo][nTray][nCmNo] != 2) gMes.nCmResult[nPortNo][nTray][nCmNo] = 1;
	}
	if (sLotId.Left(3) == SKIP_LOT) gMes.nCmResult[nPortNo][nTray][nCmNo] = 1;
	if (sMarginal == "OK") gLot.nMarginal[nPortNo][nTray][nCmNo] = 9;

	DWORD dwTerm = GetTickCount() - m_dwReqStart[nPortNo][nTray][nCmNo];
	strLog.Format("[Get_CmResult] MES CM Result(%s) Lot(%s) Judge(%s) Code(%s) Text(%s) PortNo(%d) TrayNo(%d) CmNo(%d) Marginal(%s) Time,%d", sCmId, sLotId, sJudge, sNgCode, sNgText, nPortNo+1, nTray+1, nCmNo+1, sMarginal, dwTerm);
	g_objLogFile.Save_MesAgentLog(strLog);
}

void CMesAgent::Get_CmFail(CString sLotId, CString sCmId, CString sCode, CString sText)
{
	CString	strLog;
	gMes.sHostCancelLotId = sLotId;
	gMes.sHostCancelModule = sCmId;
	gMes.sHostCancelCode = sCode;
	gMes.sHostCancelText = sText;

	if (sCmId.GetLength() < 2) {
		strLog.Format("MESAgent CmFail ReciveData ModuleID error => (%s) (%s) (%s) (%s)", sLotId, sCmId, sCode, sText);
		g_objLogFile.Save_MesAgentLog(strLog);
		g_objCommon.Show_Error(9005);
		return;
	}

	int nPort = -1, nTray = -1, nCmNo = -1;
	for(int i=0; i<6; i++) {
		for(int j=0; j<20; j++) {
			for(int k=0; k<40; k++) {
				if (gLot.sBarCode[i][j][k] == sCmId) {
					nPort = i; nTray = j, nCmNo = k; break;
				}
			}
			if (nTray > -1) break;
		}
		if (nTray > -1) break;
	}
	if (nTray == -1 || nCmNo == -1) {
		strLog.Format("MESAgent CmFail ReciveData ModuleID Not Found => (%s) (%s) (%s) (%s)", sLotId, sCmId, sCode, sText);
		g_objLogFile.Save_MesAgentLog(strLog);
		g_objCommon.Show_Error(9005);
		return;
	}

	gMes.sHostCancelLotId = gLot.sLotID[nPort];
	gMes.nCmResult[nPort][nTray][nCmNo] = 2;
//	gMes.sCmCode[nPort][nTray][nCmNo] = gMes.sHostCancelCode;
//	gMes.sCmText[nPort][nTray][nCmNo] = gMes.sHostCancelText;

	g_objCommon.Show_Error(9005);

	strLog.Format("[Get_CmFail] MES CM Fail(%s) LotID(%s) Code(%s) Text(%s) PortNo(%d) TrayNo(%d) CmNo(%d)", sCmId, sLotId, sCode, sText, nPort+1, nTray+1, nCmNo+1);
	g_objLogFile.Save_MesAgentLog(strLog);
}

void CMesAgent::Get_HostMessage(CString sMsg)
{
	g_objCommon.Show_Alarm(sMsg, 1);
}

void CMesAgent::Get_ModuleData1(CString sData)
{
	CString strLog, sTemp, sCnt, sRcvData[320][11];
	gMes.nLotConfirm[LOAD_STAGE] = 4;
#ifndef AJIN_BOARD_USE
	gMes.nLotConfirm[LOAD_STAGE] = 4;
	gMes.nLotStatus[0]++;
	return;
#endif
	AfxExtractSubString(sCnt, sData, 2, ',');
	int nLen = sData.GetLength();
	int nCnt = atoi(sCnt);
	if (nCnt < 1 || nCnt > 640) {
		if (m_sStartLot.Left(3) == SKIP_LOT) {
			for(int i=0; i<6; i++) {
				if (gLot.sLotID[i] == m_sStartLot) {
					gMes.nLotStatus[i]++;	//Lot수신2

					strLog.Format("MESAgent Module Data1 LotID Skip => LotID(%s) Port(%d)", m_sStartLot, i+1);
					g_objLogFile.Save_MesAgentLog(strLog);
					return;
				}
			}

			gMes.sHostCancelLotId = m_sStartLot;
			strLog.Format("MESAgent Module LotID Error1 => (%s)", m_sStartLot);
			g_objLogFile.Save_MesAgentLog(strLog);
			g_objCommon.Show_Error(9022);
			return;
		}

		strLog.Format("MESAgent Module Data1 Error => Count(%d) Length(%d)", nCnt, nLen);
		g_objLogFile.Save_MesAgentLog(strLog);
		g_objCommon.Show_Error(9021);
		return;
	}

	int k=3, nRcvCnt;
	if (nCnt > 320) nRcvCnt = 320;
	else			nRcvCnt = nCnt;
	for(int i=0; i<nRcvCnt; i++) {
		for(int j=0; j<11; j++) {
			AfxExtractSubString(sRcvData[i][j], sData, k++, ',');
		}
	}
	gMes.sHostCancelLotId = sRcvData[0][0];
	if (sRcvData[0][0].GetLength() < 5) {
		strLog.Format("MESAgent Module LotID Error => (%s)", sRcvData[0][0]);
		g_objLogFile.Save_MesAgentLog(strLog);
		g_objCommon.Show_Error(9022);
		return;
	}

	//0:LOTID,1:MODULEID,2:SITE,3:EQPID,4:EQPNAME,5:TOOL_CAVITY,6:PARA,7:DATE,8:ROS_JUDGE,9:DFA_LOTID,10:POCKETNO =>
	//0:MODULEID,1:SITE,2:EQPID,3:EQPNAME,4:TOOL_CAVITY,5:PARA,6:DATE,7:ROS_JUDGE,8:DFA_LOTID,9:POCKETNO
//	gLot.sLotID[2] = sRcvData[0][0];	//gjc_test
	for(int i=0; i<6; i++) {
		if (gLot.sLotID[i] == sRcvData[0][0]) {
			for(int j=0; j<nRcvCnt; j++) {
				for(int k=1; k<11; k++) {
					gNG->sModuleID[i][j][k-1] = sRcvData[j][k];
				}
			}
			gMes.nLotStatus[i]++;	//Lot수신2

			strLog.Format("Module Port(%d) Data1: Count(%d) LotID(%s) Module(%s)", i, nCnt, sRcvData[0][0], gNG->sModuleID[i][0][0]);
			g_objLogFile.Save_MesAgentLog(strLog);

			for(int j=0; j<nRcvCnt; j++) {
				sTemp = "";
				for(int k=0; k<10; k++) {
					sTemp += "," + gNG->sModuleID[i][j][k];
				}
				strLog.Format("Module Data1: %s", sTemp);
				g_objLogFile.Save_MesAgentLog(strLog);
			}
			return;
		}
	}
	strLog.Format("MESAgent Module Data1 LotID Not Found Error => LotID(%s)", sRcvData[0][0]);
	g_objLogFile.Save_MesAgentLog(strLog);
	g_objCommon.Show_Error(9023);
}

void CMesAgent::Get_ModuleData2(CString sData)
{
	CString strLog, sTemp, sCnt, sRcvData[320][11];


	gMes.nLotConfirm[LOAD_STAGE] = 4;
	AfxExtractSubString(sCnt, sData, 2, ',');
	int nLen = sData.GetLength();
	int nCnt = atoi(sCnt);
	if (nCnt < 320 || nCnt > 640) {
		strLog.Format("MESAgent Module Data2 Error => Count(%d) Length(%d)", nCnt, nLen);
		g_objLogFile.Save_MesAgentLog(strLog);
		g_objCommon.Show_Error(9021);
		return;
	}

	int k=3, nRcvCnt, jx;
	nRcvCnt = nCnt - 320;
	for(int i=0; i<nRcvCnt; i++) 
	{
		for(int j=0; j<11; j++) 
		{
			AfxExtractSubString(sRcvData[i][j], sData, k++, ',');
		}
	}

	//0:LOTID,1:MODULEID,2:SITE,3:EQPID,4:EQPNAME,5:TOOL_CAVITY,6:PARA,7:DATE,8:ROS_JUDGE,9:DFA_LOTID,10:POCKETNO =>
	//0:MODULEID,1:SITE,2:EQPID,3:EQPNAME,4:TOOL_CAVITY,5:PARA,6:DATE,7:ROS_JUDGE,8:DFA_LOTID,9:POCKETNO
//	gLot.sLotID[2] = sRcvData[0][0];	//gjc_test
	for(int i=0; i<6; i++) 
	{

		if (gLot.sLotID[i] == sRcvData[0][0]) 
		{
			for(int j=320; j<nCnt; j++) 
			{
				for(int k=1; k<11; k++) 
				{
					jx = j - 320;
					gNG->sModuleID[i][j][k-1] = sRcvData[jx][k];
				}
			}
			gMes.nLotStatus[i]++;


			strLog.Format("Module Port(%d) Data2: Count(%d) LotID(%s) Module(%s)", i, nCnt, sRcvData[0][0], gNG->sModuleID[i][0][0]);
			g_objLogFile.Save_MesAgentLog(strLog);

			for(int j=320; j<nCnt; j++) 
			{
				sTemp = "";
				for(int k=0; k<10; k++) 
				{
					sTemp += "," + gNG->sModuleID[i][j][k];
				}
				strLog.Format("Module Data2: %s", sTemp);
				g_objLogFile.Save_MesAgentLog(strLog);
			}
			
			return;
		}
	}
	strLog.Format("MESAgent Module Data2 LotID Not Found Error => LotID(%s)", sRcvData[0][0]);
	g_objLogFile.Save_MesAgentLog(strLog);
	g_objCommon.Show_Error(9023);
}

void CMesAgent::Get_PPSelect(CString sLotId, CString sRecipe)
{
	gMes.sHostLotIDTemp = sLotId;
	gMes.sHostRecipeTemp = sRecipe;
	if (gMes.sHostLotIDTemp.GetLength() < 5 || gMes.sHostRecipeTemp.GetLength() < 2) 
	{
		g_objCommon.Show_Error(9004); return;
	}
	gMes.nLotConfirm[LOAD_STAGE] = 2;
}

void CMesAgent::Get_PPSelectCompletedReport(CString sLotId, CString sRecipe)
{
	gMes.sHostLotIDTemp = sLotId;
	gMes.sHostRecipeTemp = sRecipe;

	gMes.nLotConfirm[LOAD_STAGE] = 3;
}

void CMesAgent::Get_PPSelectFail(CString sLotId, CString sRecipe, CString sCode, CString sText)
{
	gMes.sHostLotIDTemp = sLotId;
	gMes.sHostRecipeTemp = sRecipe;
	gMes.sHostCancelCode = sCode;
	gMes.sHostCancelText = sText;
	g_objCommon.Show_Error(9030);
}




void CMesAgent::Get_NGLotStart(CString sNGLotId, CString sNGVendor, CString sNGConfig)
{
	gMes.nMarCount = gMes.nMarTrayCount = gMes.nNoReadCount = 0;
	gMes.sHostNGLotID = sNGLotId;
	gMes.sHostNGVendor = sNGVendor;
	if (sNGConfig.GetLength() > 5) gMes.sHostNGConfig = sNGConfig;
	else						   gMes.sHostNGConfig = gMes.sHostConfig;

	if (gMes.sHostNGLotID.GetLength() < 5) {
		g_objCommon.Show_Error(9024);	return;
	}

	gMes.nMarStatus = 2;
	Set_NGLotStart(gMes.sHostNGLotID);
}


void CMesAgent::Get_RMSAlreadyDone()
{
	gData.bRMSDone = TRUE;
}

void CMesAgent::Get_RMSDone()
{
	gData.bRMSDone = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Set Command

void CMesAgent::Set_EquipState(int nFlag)
{
	// MES : Init, idle, Setup, Ready, Executing(=Run), Paused(=Down)
	CString strSend;
	strSend.Format("EQUIP,STATE,%d", nFlag);	// 1:Init, 2:Idle, 3:Setup, 4:Ready, 5:Run(=Executing), 6;Pause(=Down)
	Send_Command(strSend);
}

void CMesAgent::Set_ErrorUpdate(int nFlag, CString sErrNo)
{
	CString strSend;
	strSend.Format("ERROR,UPDATE,%d,%s", nFlag, sErrNo);
	Send_Command(strSend);
}

void CMesAgent::Set_ControlState(int nFlag, CString sOperId)
{
	CString strSend;
	strSend.Format("CONTROL,STATE,%d,%s", nFlag, sOperId);
	Send_Command(strSend);
	if (nFlag == 2) m_bHostOnline = FALSE;	// 사용자 Offline
}

void CMesAgent::Set_LotStart(int nType, int nPortNo, CString sLotId, CString sRecipe, int nCount)	//0:Request, 1:Started
{
	gMes.nLotStatus[nPortNo] = 4;	//Lot시작

	CString strSend;
	strSend.Format("LOT,START,%d,%s,%s,%d", nType, sLotId, sRecipe, nCount);
	Send_Command(strSend);
	m_sStartLot = sLotId;
}

void CMesAgent::Set_LotIDReport(int nType, int nPortNo, CString sLotId, CString sRecipe, int nCount)	//0:Request, 1:Started
{
	gMes.nLotStatus[nPortNo] = 1;	//Lot ID report = Lot 송신
	
	CString strSend;
	strSend.Format("LOT,START,%d,%s,%s,%d", nType, sLotId, sRecipe, nCount);
	Send_Command(strSend);
	m_sStartLot = sLotId;
}

void CMesAgent::Set_LotEnd(int nPortNo, CString sLotId, CString sRecipe, int nHCount, int nOk, int nNg)
{
	gMes.nLotStatus[nPortNo] = 0;
	CString strSend;
	strSend.Format("LOT,END,%s,%s,%d,%d,%d", sLotId, sRecipe, nHCount, nOk, nNg);
	Send_Command(strSend);
}

void CMesAgent::Set_LotEnd(int nPortNo, CString sLotId, CString sDeepData1, CString sDeepData2, CString sDeepData3, CString sDeepData4, CString sDeepData5)
{
	gMes.nLotStatus[nPortNo] = 0;
	if (nPortNo < 1 || nPortNo > 6) return;
	int nNo = nPortNo - 1;

	CString strSend;
	strSend.Format("LOT,END,%s,%s,%d,%d,%d,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d",
				sLotId, gMes.sHostRecipe[nNo], gMes.nHostCmCount[nNo], gLot.nGoodCount[nNo], gLot.nNgCount[nNo]+gLot.nSkipCount[nNo],
				sDeepData1, sDeepData2, sDeepData3, sDeepData4, sDeepData5,
				gLot.nRosJugCount[nNo][0], gLot.nRosJugCount[nNo][1], gLot.nRosJugCount[nNo][3], gLot.nRosJugCount[nNo][2]+gLot.nRosJugCount[nNo][4], gLot.nRosJugCount[nNo][10],
				                                                      gLot.nRosJugCount[nNo][3] +gLot.nRosJugCount[nNo][2]+gLot.nRosJugCount[nNo][4] +gLot.nRosJugCount[nNo][10]);
				//Deep Learning투입수, Deep Learning양품수, Deep Learning NG수, Deep Learning TimeOut수, Deep Learning투입 Image수
				//ROS투입수,                ROS양품수,                 ROS NG수,                  ROS Repair수,                                        ROS Skip수,   MVI수(ROS NG+ROS Repair+ROS Skip)
	Send_Command(strSend);
}

void CMesAgent::Set_LotAbort(CString sLotId)
{
	CString strSend;
	strSend.Format("LOT,ABORT,%s", sLotId);
	Send_Command(strSend);
}

void CMesAgent::Set_OperUpdate(CString sOperId)
{
	if (sOperId.GetLength() < 4) return;
	CString strSend;
	strSend.Format("OPER,UPDATE,%s", sOperId);
	Send_Command(strSend);
}

void CMesAgent::Set_IdleReport(CString sOperId, CString sSTime, CString sETime, CString sCode, CString sType)
{
	CString strSend;
	strSend.Format("IDLE,REPORT,%s,%s,%s,%s,%s", sOperId, sSTime, sETime, sCode, sType);
	Send_Command(strSend);
}


void CMesAgent::Set_LotReport(CString sLotID)
{
	CString strSend;
	//strSend.Format("LOT,REPORT,%s,%s,%s,%s,%s", sOperId, sSTime, sETime, sCode, sType);
	//Send_Command(strSend);
}

void CMesAgent::Set_RecipeList(int nFlag)						// 0:All, 1:Current Recipe
{
	CString strSend;

	if (nFlag == 1) {	// 1:Current Recipe
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		strSend.Format("RECIPE,REQUEST,1,1,%s", pEquipData->sModelName);
		Send_Command(strSend);
	}
	if (nFlag == 0) {	// 0:All Recipe
		int		nCount = 0;
		CString sPathSource, sRcipeData = "";

		sPathSource = gsCurrentDir + "\\System\\Model";

		if (GetFileAttributes(sPathSource) == -1) {	// 디렉토리 없음
			strSend.Format("RECIPE,REQUEST,0,%d,%s", nCount, sRcipeData);
			Send_Command(strSend);
			return;
		}

		CFileFind ff;
		BOOL bFile = ff.FindFile(sPathSource + _T("\\*.*"));

		while(bFile)
		{
			bFile = ff.FindNextFile();

			CString str;	// = ff.GetFileName();
			if(ff.IsDots()) continue;

			if(ff.IsDirectory()){
				str = ff.GetFileName();	nCount++;
				if (nCount == 1) sRcipeData = str;
				else			 sRcipeData = sRcipeData + "," + str;
			}
		}
		ff.Close();

		strSend.Format("RECIPE,REQUEST,0,%d,%s", nCount, sRcipeData);
		Send_Command(strSend);
	}
}

void CMesAgent::Set_CmRequest(CString sLotId, CString sCmId, int nPortNo, int nTrayNo, int nCmNo)
{
	CString strSend;
	strSend.Format("CM,REQUEST,%s,%s", sLotId, sCmId);
	Send_Command(strSend);

	m_dwReqStart[nPortNo-1][nTrayNo-1][nCmNo-1] = GetTickCount();
}

void CMesAgent::Set_CmEnd(int nType, int nPortNo, int nTrayNo, int nCmNo, int nOut)
{
	if (nPortNo < 1 || nPortNo > 6 || nCmNo < 1 || nCmNo > 40) return;

	CString	sLotID  = gLot.sLotID[nPortNo-1];
	CString	strCmId = gLot.sBarCode[nPortNo-1][nTrayNo-1][nCmNo-1];
	CString	strNGCd = gLot.sNGCode_I[nPortNo-1][nTrayNo-1][nCmNo-1][0];
	CString	sMarginal = "";

	CString strResult, strNgCode;
	if (nType == 1) {
		strResult = "NG";
		if	(strNGCd == "BARCODE_NOREAD" || strCmId.GetLength() < 15) 
		{
			strCmId = "NOREAD"; strNgCode = "BARCODE_NOREAD";
		} 		
		else 
		{
			strNgCode == "MARGINAL_OK"; sMarginal = "OK"; gMes.nMarCount++;
		}
	} else {
		strResult = "OK";
		strNgCode = "00";
	}

	

	CString strSend;
	strSend.Format("CM,END,%s,%s,%s,%s,%d,%s", sLotID, strCmId, strResult, strNgCode, nOut, sMarginal);
	g_objLogFile.Save_TestLog(strSend);
	Send_Command(strSend);	
}

CString CMesAgent::Set_NGSort(int nPno, int nTNo, int CNo)
{
	CString sNGCode;

	sNGCode = gLot.sNGCode_I[nPno-1][nTNo-1][CNo-1][0];
	if (sNGCode == "BARCODE_NOREAD" || sNGCode == "MES_NG" || sNGCode == "ROI_FAIL" || sNGCode == "GRAB_FAIL") return sNGCode;
	if (sNGCode == "Vision Result Timeout" || sNGCode == "ROS Timeout" || sNGCode == "MCBTM" || sNGCode == "FAI_RECOFAIL_SP") return sNGCode;
	if (sNGCode == "Skip_ROS_N" || sNGCode == "Skip_ROS_R" || sNGCode == "MARGINAL_OK") return sNGCode;

	int nSeq[10] = { 999, 999, 999, 999, 999, 999, 999, 999, 999, 999 };
	for (int i=1; i<6; i++) {
		for (int j=0; j<m_nSizeCount; j++) {
			if (m_sSizeNG[j].GetLength() > 0 && gLot.sNGCode_I[nPno-1][nTNo-1][CNo-1][i] == m_sSizeNG[j]) {
				nSeq[i-1] = j; break;
			}
		}
	}

	int nNo = 999, nI;
	for (int i=0; i<5; i++) {
		if (nNo > nSeq[i]) { nNo = nSeq[i]; nI = i; }
	}
	if (nNo < 100) { gLot.sNGCode_I[nPno-1][nTNo-1][CNo-1][0] = sNGCode = m_sSizeNG[nNo]; }
	if (sNGCode.GetLength() < 1) sNGCode = "NG";
	return sNGCode;
}

void CMesAgent::Set_TerminalOK()
{
	CString strSend;
	strSend.Format("TERMINAL,MSG");
	Send_Command(strSend);
}

void CMesAgent::Set_NGLotRequest()
{
	gMes.nMarStatus = 1;
	CString strSend;
	strSend.Format("NGLOT,REQUEST");
	Send_Command(strSend);
}

void CMesAgent::Set_NGLotStart(CString sNGLotId)
{
	gMes.sGUItNGLotID = sNGLotId;
	gMes.nGUICount[0] = gMes.nNGLotCount;
	gMes.nGUICount[1] = gMes.nMarCount;
	gMes.nGUICount[2] = gMes.nMarTrayCount;
	gMes.nGUICount[3] = gMes.nNoReadCount;

	CString strSend;
	strSend.Format("NGLOT,START,%s,0", sNGLotId);
	Send_Command(strSend);

//	m_dwStart = GetTickCount();
//	SetTimer(0, 100, NULL);	//NGLot완공송신
}

void CMesAgent::Set_NGLotEnd(CString sNGLotId, int nMarCount)
{
	CString strSend;
	strSend.Format("NGLOT,END,%s,%d", sNGLotId, nMarCount);
	Send_Command(strSend);

	gMes.nMarStatus = 0;
	gMes.sHostNGConfig = "";
}

void CMesAgent::Set_RMSCheck()
{
	CString strSend;

	gData.bRMSDone = FALSE;

	strSend.Format("RMS,CHECK");
	Send_Command(strSend);

}


void CMesAgent::Set_PPSelectReport(CString sLotId, CString sVersion)
{
	CString strSend; 
	strSend.Format("RECIPE,REPORT,%s", sVersion);
	Send_Command(strSend);	
}


///////////////////////////////////////////////////////////////////////////////

void CMesAgent::Send_Command(CString sSend)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) return;

	CString strSendSocket, strLog;

	if (!m_bConnected) return;
	if (sSend.Left(7) != "CONTROL" && sSend.Left(9) != "LOT,ABORT") {
		if (!m_bHostOnline) return;
	}

	strSendSocket.Format("@%s\n", sSend);

	char chSend[1001] = { 0 };	// Buffer 1000, Last 0x00
	int nLength = strSendSocket.GetLength();
	memcpy(chSend, (LPSTR)(LPCSTR)strSendSocket, nLength);

	if (!m_Client.Write_Socket((BYTE*)chSend, nLength)) return;

	// Host Log ////////////////////////////////////////////
	strLog.Format("[->] : %s", sSend);
	g_objLogFile.Save_MesAgentLog(strLog);
	///////////////////////////////////////////////////////
}

///////////////////////////////////////////////////////////////////////////////
BOOL CMesAgent::Exist_Recipe(CString sRecipe)
{
	CString sPathSource;

	sPathSource = gsCurrentDir + "\\System\\Model";
	if (GetFileAttributes(sPathSource) == -1) return FALSE;

	CFileFind ff;
	BOOL bFile = ff.FindFile(sPathSource + _T("\\*.*"));

	while(bFile)
	{
		bFile = ff.FindNextFile();
		if(ff.IsDots()) continue;

		if(ff.IsDirectory()) {
			if (sRecipe == ff.GetFileName()) { ff.Close(); return TRUE; }
		}
	}
	ff.Close();

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/*/
#pragma region No Use Methods
// 안 쓰는 메서드

void CMesAgent::Set_LotReady(CString sLotId, int nPortIdx)
{
	CString strSend;
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	strSend.Format("LOT,READY,%s,%d", sLotId, nPortIdx);
	Send_Command(strSend);
}

void CMesAgent::Set_LotIdReport(CString sLotId, int nPortNo, CString sRecipeId)
{
	CString strSend;
	strSend.Format("LOT,REPORT,%s,%d,%s", sLotId, nPortNo, sRecipeId);
	Send_Command(strSend);
}

void CMesAgent::Set_IdleRequest()
{
	CString strSend;
	strSend.Format("IDLE,REQUEST");
	Send_Command(strSend);
}

void CMesAgent::Cancel_Data()
{
	g_objDataManager.Read_EquipData();
	g_objDataManager.Read_MoveData();
}
#pragma endregion Not_Use_Method
/*/