// SequenceMain.cpp : 구현 파일
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SequenceMain.h"
#include "LogFile.h"
#include "Common.h"
#include "Inspector.h"
#include "Dispatcher.h"
#include "CMAI2100Dlg.h"
#include "WorkDlg.h"
#include "MesAgent.h"
#include <math.h>

CSequenceMain g_objSequenceMain;

///////////////////////////////////////////////////////////////////////////////

CSequenceMain::CSequenceMain()
{
	for (int i = 0; i < AXIS_COUNT; i++) {
		m_pStatus[i] = g_objAJinAXL.Get_pStatus(i);
		m_pParam[i] = g_objAJinAXL.Get_pParam(i);
	}

	m_pDX00 = g_objAJinAXL.Get_pDX00();
	m_pDX01 = g_objAJinAXL.Get_pDX01();
	m_pDX02 = g_objAJinAXL.Get_pDX02();
	m_pDX03 = g_objAJinAXL.Get_pDX03();
	m_pDX04 = g_objAJinAXL.Get_pDX04();
	m_pDX05 = g_objAJinAXL.Get_pDX05();
	m_pDX06 = g_objAJinAXL.Get_pDX06();
	m_pDX07 = g_objAJinAXL.Get_pDX07();
	m_pDX08 = g_objAJinAXL.Get_pDX08();
	m_pDX09 = g_objAJinAXL.Get_pDX09();
	m_pDX10 = g_objAJinAXL.Get_pDX10();
	m_pDX11 = g_objAJinAXL.Get_pDX11();
	m_pDX12 = g_objAJinAXL.Get_pDX12();
	m_pDX13 = g_objAJinAXL.Get_pDX13();
	m_pDX14 = g_objAJinAXL.Get_pDX14();

	m_pDY00 = g_objAJinAXL.Get_pDY00();
	m_pDY01 = g_objAJinAXL.Get_pDY01();
	m_pDY02 = g_objAJinAXL.Get_pDY02();
	m_pDY03 = g_objAJinAXL.Get_pDY03();
	m_pDY04 = g_objAJinAXL.Get_pDY04();
	m_pDY05 = g_objAJinAXL.Get_pDY05();
	m_pDY06 = g_objAJinAXL.Get_pDY06();
	m_pDY07 = g_objAJinAXL.Get_pDY07();
	m_pDY08 = g_objAJinAXL.Get_pDY08();
	m_pDY09 = g_objAJinAXL.Get_pDY09();
	m_pDY10 = g_objAJinAXL.Get_pDY10();
	m_pDY11 = g_objAJinAXL.Get_pDY11();
	m_pDY12 = g_objAJinAXL.Get_pDY12();
	m_pDY13 = g_objAJinAXL.Get_pDY13();
	m_pDY14 = g_objAJinAXL.Get_pDY14();

	m_pEquipData = g_objDataManager.Get_pEquipData();
	m_pMoveData = g_objDataManager.Get_pMoveData();
	m_pRosData = g_objDataManager.Get_pRosData();

	m_bThreadMainRun = FALSE;
	m_pThreadMainRun = NULL;

	

	Reset_MainRunCase();
}

CSequenceMain::~CSequenceMain()
{
	if (m_pThreadMainRun) {
		m_bThreadMainRun = FALSE;
		WaitForSingleObject(m_pThreadMainRun->m_hThread, INFINITE);
	}
}

void CSequenceMain::Reset_MainRunCase()
{
	m_nElevator1Case	= 0;
	m_nElevator2Case	= 0;
	m_nElevator3Case	= 0;
	m_nElevator4Case	= 0;
	m_nElevator5Case	= 0;
	m_nElevator6Case	= 0;
	m_nElevator7Case	= 0;
	m_nTransfer1Case	= 0;
	m_nTransfer2Case	= 0;
	m_nLoadStage1Case	= 0;
	m_nLoadStage2Case	= 50;
	m_nLoadPicker1Case	= 0;
	m_nLoadPicker2Case	= 70;
	m_nVisionStage1Case = 50;
	m_nVisionStage2Case = 00;
	m_nVisionStage3Case = 60;
	m_nVisionStage4Case = 70;
	m_nUnloadPicker1Case= 0;
	m_nUnloadPicker2Case= 50;
	m_nNGStage1Case		= 0;
	m_nNGStage2Case		= 50;
	m_nGoodStage1Case	= 0;
	m_nGoodStage2Case	= 50;
	m_nShipAlignCase	= 0;
}

int *CSequenceMain::Get_pMainRunCase()
{
	static int nCase[24] = { 0 };

	nCase[0]  = m_nElevator1Case;	
	nCase[1]  = m_nElevator2Case;	
	nCase[2]  = m_nElevator3Case;	
	nCase[3]  = m_nElevator4Case;	
	nCase[4]  = m_nElevator5Case;	
	nCase[5]  = m_nElevator6Case;	
	nCase[6]  = m_nElevator7Case;	
	nCase[7]  = m_nTransfer1Case;	
	nCase[8]  = m_nTransfer2Case;	
	nCase[9]  = m_nLoadStage1Case;	
	nCase[10] = m_nLoadStage2Case;	
	nCase[11] = m_nLoadPicker1Case;	
	nCase[12] = m_nLoadPicker2Case;	
	nCase[13] = m_nVisionStage1Case;
	nCase[14] = m_nVisionStage2Case;
	nCase[15] = m_nVisionStage3Case;
	nCase[16] = m_nVisionStage4Case;
	nCase[17] = m_nUnloadPicker1Case;
	nCase[18] = m_nUnloadPicker2Case;
	nCase[19] = m_nNGStage1Case;	
	nCase[20] = m_nNGStage2Case;	
	nCase[21] = m_nGoodStage1Case;	
	nCase[22] = m_nGoodStage2Case;	
	nCase[23] = m_nShipAlignCase;	

	return nCase;
}

int CSequenceMain::Get_MainRunCase(int nRun)
{
	if (nRun == AUTO_ELEVATOR_1)		return m_nElevator1Case;	
	if (nRun == AUTO_ELEVATOR_2)		return m_nElevator2Case;	
	if (nRun == AUTO_ELEVATOR_3)		return m_nElevator3Case;	
	if (nRun == AUTO_ELEVATOR_4)		return m_nElevator4Case;	
	if (nRun == AUTO_ELEVATOR_5)		return m_nElevator5Case;	
	if (nRun == AUTO_ELEVATOR_6)		return m_nElevator6Case;	
	if (nRun == AUTO_ELEVATOR_7)		return m_nElevator7Case;	
	if (nRun == AUTO_TRANSFER_1)		return m_nTransfer1Case;	
	if (nRun == AUTO_TRANSFER_2)		return m_nTransfer2Case;	
	if (nRun == AUTO_LOAD_STAGE_1)		return m_nLoadStage1Case;	
	if (nRun == AUTO_LOAD_STAGE_2)		return m_nLoadStage2Case;	
	if (nRun == AUTO_LOAD_PICKER_1)		return m_nLoadPicker1Case;	
	if (nRun == AUTO_LOAD_PICKER_2)		return m_nLoadPicker2Case;	
	if (nRun == AUTO_VISION_STAGE_1)	return m_nVisionStage1Case;
	if (nRun == AUTO_VISION_STAGE_2)	return m_nVisionStage2Case;
	if (nRun == AUTO_VISION_STAGE_3)	return m_nVisionStage3Case;
	if (nRun == AUTO_VISION_STAGE_4)	return m_nVisionStage4Case;
	if (nRun == AUTO_UNLOAD_PICKER_1)	return m_nUnloadPicker1Case;
	if (nRun == AUTO_UNLOAD_PICKER_2)	return m_nUnloadPicker2Case;
	if (nRun == AUTO_NG_STAGE_1)		return m_nNGStage1Case;	
	if (nRun == AUTO_NG_STAGE_2)		return m_nNGStage2Case;	
	if (nRun == AUTO_GOOD_STAGE_1)		return m_nGoodStage1Case;	
	if (nRun == AUTO_GOOD_STAGE_2)		return m_nGoodStage2Case;	
	if (nRun == AUTO_SHIP_ALIGN)		return m_nShipAlignCase;	

	return 0;
}

void CSequenceMain::Set_MainRunCase(int nRun, int nCase)
{
	if (nRun == AUTO_ELEVATOR_1)		m_nElevator1Case		= nCase;
	if (nRun == AUTO_ELEVATOR_2)		m_nElevator2Case		= nCase;
	if (nRun == AUTO_ELEVATOR_3)		m_nElevator3Case		= nCase;
	if (nRun == AUTO_ELEVATOR_4)		m_nElevator4Case		= nCase;
	if (nRun == AUTO_ELEVATOR_5)		m_nElevator5Case		= nCase;
	if (nRun == AUTO_ELEVATOR_6)		m_nElevator6Case		= nCase;
	if (nRun == AUTO_ELEVATOR_7)		m_nElevator7Case		= nCase;
	if (nRun == AUTO_TRANSFER_1)		m_nTransfer1Case		= nCase;
	if (nRun == AUTO_TRANSFER_2)		m_nTransfer2Case		= nCase;
	if (nRun == AUTO_LOAD_STAGE_1)		m_nLoadStage1Case		= nCase;
	if (nRun == AUTO_LOAD_STAGE_2)		m_nLoadStage2Case		= nCase;
	if (nRun == AUTO_LOAD_PICKER_1)		m_nLoadPicker1Case		= nCase;
	if (nRun == AUTO_LOAD_PICKER_2)		m_nLoadPicker2Case		= nCase;
	if (nRun == AUTO_VISION_STAGE_1)	m_nVisionStage1Case		= nCase;
	if (nRun == AUTO_VISION_STAGE_2)	m_nVisionStage2Case		= nCase;
	if (nRun == AUTO_VISION_STAGE_3)	m_nVisionStage3Case		= nCase;
	if (nRun == AUTO_VISION_STAGE_4)	m_nVisionStage4Case		= nCase;
	if (nRun == AUTO_UNLOAD_PICKER_1)	m_nUnloadPicker1Case	= nCase;
	if (nRun == AUTO_UNLOAD_PICKER_2)	m_nUnloadPicker2Case	= nCase;
	if (nRun == AUTO_NG_STAGE_1)		m_nNGStage1Case			= nCase;
	if (nRun == AUTO_NG_STAGE_2)		m_nNGStage2Case			= nCase;
	if (nRun == AUTO_GOOD_STAGE_1)		m_nGoodStage1Case		= nCase;
	if (nRun == AUTO_GOOD_STAGE_2)		m_nGoodStage2Case		= nCase;
	if (nRun == AUTO_SHIP_ALIGN)		m_nShipAlignCase		= nCase;
}

void CSequenceMain::Set_MainRunLoop(int nRun, int nLoop)
{
	if (nRun == AUTO_ELEVATOR_1)		m_tElevator1Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_ELEVATOR_2)		m_tElevator2Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_ELEVATOR_3)		m_tElevator3Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_ELEVATOR_4)		m_tElevator4Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_ELEVATOR_5)		m_tElevator5Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_ELEVATOR_6)		m_tElevator6Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_ELEVATOR_7)		m_tElevator7Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_TRANSFER_1)		m_tTransfer1Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_TRANSFER_2)		m_tTransfer2Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_LOAD_STAGE_1)		m_tLoadStage1Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_LOAD_STAGE_2)		m_tLoadStage2Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_LOAD_PICKER_1)		m_tLoadPicker1Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_LOAD_PICKER_2)		m_tLoadPicker2Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_VISION_STAGE_1)	m_tVisionStage1Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_VISION_STAGE_2)	m_tVisionStage2Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_VISION_STAGE_3)	m_tVisionStage3Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_VISION_STAGE_4)	m_tVisionStage4Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_UNLOAD_PICKER_1)	m_tUnloadPicker1Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_UNLOAD_PICKER_2)	m_tUnloadPicker2Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_NG_STAGE_1)		m_tNGStage1Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_NG_STAGE_2)		m_tNGStage2Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_GOOD_STAGE_1)		m_tGoodStage1Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_GOOD_STAGE_2)		m_tGoodStage2Loop.Set_LoopTime(nLoop);
	if (nRun == AUTO_SHIP_ALIGN)		m_tShipAlignLoop.Set_LoopTime(nLoop);
}

BOOL CSequenceMain::Get_IsAutoRun()
{
	int *pCase = Get_pMainRunCase();
	for (int i = 0; i < 24; i++) 
	{
		if (i <= AUTO_ELEVATOR_7      && *(pCase + i) == 20) continue;
		if (i <= AUTO_ELEVATOR_7      && *(pCase + i) == 51) continue;

		if (i == AUTO_LOAD_STAGE_1    && m_nLoadStage1Case == 50) continue;
		if (i == AUTO_LOAD_STAGE_2    && m_nLoadStage2Case == 50) continue;
		if (i == AUTO_LOAD_PICKER_1   && m_nLoadPicker1Case == 70) continue;
		if (i == AUTO_LOAD_PICKER_2   && m_nLoadPicker2Case == 70) continue;
		if (i == AUTO_UNLOAD_PICKER_1 && m_nUnloadPicker1Case == 50) continue;
		if (i == AUTO_UNLOAD_PICKER_2 && m_nUnloadPicker2Case == 50) continue;

		if (i == AUTO_NG_STAGE_1      && m_nNGStage1Case == 50) continue;
		if (i == AUTO_NG_STAGE_2      && m_nNGStage2Case == 50) continue;
		if (i == AUTO_GOOD_STAGE_1    && m_nGoodStage1Case == 50) continue;
		if (i == AUTO_GOOD_STAGE_2    && m_nGoodStage2Case == 50) continue;

		if (i == AUTO_VISION_STAGE_1  && (m_nVisionStage1Case == 50 || m_nVisionStage1Case == 60 || m_nVisionStage1Case == 70)) continue;
		if (i == AUTO_VISION_STAGE_2  && (m_nVisionStage2Case == 50 || m_nVisionStage2Case == 60 || m_nVisionStage2Case == 70)) continue;
		if (i == AUTO_VISION_STAGE_3  && (m_nVisionStage3Case == 50 || m_nVisionStage3Case == 60 || m_nVisionStage3Case == 70)) continue;
		if (i == AUTO_VISION_STAGE_4  && (m_nVisionStage4Case == 50 || m_nVisionStage4Case == 60 || m_nVisionStage4Case == 70)) continue;

		if (*(pCase + i) > 0) return TRUE;
	}
//	if (!Check_TrayEmpty()) return TRUE;
	if (!Check_ModuleEmpty()) return TRUE;
	
	return FALSE;
}

void CSequenceMain::Begin_MainRunThread()
{
	Run_Replay();

	if (m_pThreadMainRun) End_MainRunThread();
	m_bThreadMainRun = TRUE;
	m_pThreadMainRun = AfxBeginThread(Thread_MainRun, NULL);
}

void CSequenceMain::End_MainRunThread()
{
	if (m_pThreadMainRun) {
		m_bThreadMainRun = FALSE;
		WaitForSingleObject(m_pThreadMainRun->m_hThread, INFINITE);
	}
}

void CSequenceMain::Run_Replay()
{
	int nLoop = 30000;	//30초
	if (m_nUnloadPicker1Case == 13 || m_nUnloadPicker2Case == 13) nLoop = 300000;	//5분

	m_tElevator1Loop.Set_LoopTime(nLoop);
	m_tElevator2Loop.Set_LoopTime(nLoop);
	m_tElevator3Loop.Set_LoopTime(nLoop);
	m_tElevator4Loop.Set_LoopTime(nLoop);
	m_tElevator5Loop.Set_LoopTime(nLoop);
	m_tElevator6Loop.Set_LoopTime(nLoop);
	m_tElevator7Loop.Set_LoopTime(nLoop);
	m_tTransfer1Loop.Set_LoopTime(nLoop);
	m_tTransfer2Loop.Set_LoopTime(nLoop);
	m_tLoadStage1Loop.Set_LoopTime(nLoop);
	m_tLoadStage2Loop.Set_LoopTime(nLoop);
	m_tLoadPicker1Loop.Set_LoopTime(nLoop);
	m_tLoadPicker2Loop.Set_LoopTime(nLoop);
	m_tVisionStage1Loop.Set_LoopTime(nLoop);
	m_tVisionStage2Loop.Set_LoopTime(nLoop);
	m_tVisionStage3Loop.Set_LoopTime(nLoop);
	m_tVisionStage4Loop.Set_LoopTime(nLoop);
	m_tUnloadPicker1Loop.Set_LoopTime(nLoop);
	m_tUnloadPicker2Loop.Set_LoopTime(nLoop);
	m_tNGStage1Loop.Set_LoopTime(nLoop);
	m_tNGStage2Loop.Set_LoopTime(nLoop);
	m_tGoodStage1Loop.Set_LoopTime(nLoop);
	m_tGoodStage2Loop.Set_LoopTime(nLoop);
//	m_tShipAlignLoop.Set_LoopTime(nLoop);
	m_tShipAlignLoop.Set_LoopTime(5000);

	if (!m_pEquipData->bUseMES) {
		if (m_nLoadStage1Case == 5 || m_nLoadStage2Case == 5) gLot.sRecipeName[m_nRcpPortNo] = gData.sRecipeName;
	}
}

/////////////////////////////////////////////////////////////////////////////
// Main Thread Function 
UINT CSequenceMain::Thread_MainRun(LPVOID lpVoid)
{
	while (g_objSequenceMain.m_bThreadMainRun) {
		if (!g_objCommon.Check_MainEmgAir()) break;
		if (!g_objCommon.Check_MainDoor(TRUE)) break;
//		if (!g_objCommon.Check_TraySlide()) break;
		if (!g_objCommon.Check_ServoOn()) break;
		if (!g_objCommon.Check_DirveAlarm()) break;
		if (!g_objCommon.Check_EndLimit()) break;
		if (!g_objCommon.Check_EmptyTray()) break;
		if (!g_objCommon.Check_Elevator()) break;

		if (!g_objSequenceMain.Run_Elevator1()) break;		//  1. (Error : 2100)
		if (!g_objSequenceMain.Run_Elevator2()) break;		//  2. (Error : 2200)
		if (!g_objSequenceMain.Run_Elevator3()) break;		//  3. (Error : 2300)
		if (!g_objSequenceMain.Run_Elevator4()) break;		//  4. (Error : 2400)
		if (!g_objSequenceMain.Run_Elevator5()) break;		//  5. (Error : 2500)
		if (!g_objSequenceMain.Run_Elevator6()) break;		//  6. (Error : 2600)
		if (!g_objSequenceMain.Run_Elevator7()) break;		//  7. (Error : 2700)
		if (!g_objSequenceMain.Run_Transfer1()) break;		//  8. (Error : 3000)
		if (!g_objSequenceMain.Run_Transfer2()) break;		//  9. (Error : 3500)
		if (!g_objSequenceMain.Run_LoadStage1()) break;		// 10. (Error : 4000)
		if (!g_objSequenceMain.Run_LoadStage2()) break;		// 11. (Error : 4500)
		if (!g_objSequenceMain.Run_LoadPicker1()) break;	// 12. (Error : 5000)
		if (!g_objSequenceMain.Run_LoadPicker2()) break;	// 13. (Error : 5500)
		if (!g_objSequenceMain.Run_VisionStage1()) break;	// 14. (Error : 6000)
		if (!g_objSequenceMain.Run_VisionStage2()) break;	// 15. (Error : 6200)
		if (!g_objSequenceMain.Run_VisionStage3()) break;	// 16. (Error : 6400)
		if (!g_objSequenceMain.Run_VisionStage4()) break;	// 17. (Error : 6600)
		if (!g_objSequenceMain.Run_UnloadPicker1()) break;	// 18. (Error : 7000)
		if (!g_objSequenceMain.Run_UnloadPicker2()) break;	// 19. (Error : 7500)
		if (!g_objSequenceMain.Run_NGStage1()) break;		// 20. (Error : 8000)
		if (!g_objSequenceMain.Run_NGStage2()) break;		// 21. (Error : 8200)
		if (!g_objSequenceMain.Run_GoodStage1()) break;		// 22. (Error : 8400)
		if (!g_objSequenceMain.Run_GoodStage2()) break;		// 23. (Error : 8600)
		if (!g_objSequenceMain.Run_ShipAlign()) break;		// 24. (Error : 8800)

		if (!g_objSequenceMain.Run_Simulation()) break;		//  99.
		if (gLot.nJobStatus == 1 && g_objSequenceMain.Get_IsAutoRun()==FALSE) {
			gLot.nJobStatus = 2;
		}
		if (gLot.nJobStatus == 2 && g_objSequenceMain.LotEnd_Run()) break;

		Sleep(10);
	}

	g_objSequenceMain.m_bThreadMainRun = FALSE;
	g_objSequenceMain.m_pThreadMainRun = NULL;

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BOOL CSequenceMain::LotEnd_Run()
{
	if (Get_IsAutoRun()) return FALSE;
	int nA, nB, nC;
	if (Check_Transfer2(nA, nB, nC)) return FALSE;

	gLot.nJobStatus = 0;
	g_objSequenceMain.Set_ClearRunData(1);
	if (!m_pEquipData->bUseMES) { gMes.nMarCount = gMes.nMarTrayCount = gMes.nNoReadCount = 0; }

// 	Beep_Post(1000);
	g_dlgWork.PostMessage(UM_JOB_COMPELTE, NULL, NULL);
	if (gData.bCycleStop) g_dlgWork.PostMessage(UM_RESET_CYCLE_STOP, 1, NULL);

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Set_MainState(STATE_LOTEND);
//	g_objMES.Set_Status(3);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

void CSequenceMain::Set_ClearRunData(int nType)
{
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			gData.InfoAlignTray[i][j] = gData.InfoLoadTray[i][j] = gData.InfoNgTray[i][j] = gData.InfoGoodTray[i][j] = 0;
		}
	}
	for(int i=0; i<2; i++) {
		for(int j=0; j<10; j++) {
			gData.InfoLoadPick[i][j] = gData.InfoUnloadPick[i][j] = 0;
		}
	}
	for(int i=0; i<4; i++) {
		for(int j=0; j<10; j++) {
			gData.InfoVision[i][j]  = 0;
		}
	}

	gData.sLotID_Start = gData.sLotID_NGBuffer = ""; gData.nTrayNo_NGBuffer = 0; gData.nPortNo_NGBuffer = 0; gData.nROSReqCount = 0;
	for(int i=0; i<2; i++) {
		gData.sLotID_Tansfer[i] = gData.sLotID_LoadStage[i] = gData.sLotID_LoadPicker[i] = gData.sLotID_UnloadPicker[i] = gData.sLotID_NGTray[i] = gData.sLotID_GoodTray[i] = "";
		gData.nTrayNo_Tansfer[i] = gData.nTrayNo_LoadStage[i] = gData.nTrayNo_LoadPicker[i] = gData.nTrayNo_UnloadPicker[i] = gData.nTrayNo_NGTray[i] = gData.nTrayNo_GoodTray[i] = 0;
		gData.nPortNo_Tansfer[i] = gData.nPortNo_LoadStage[i] = gData.nPortNo_LoadPicker[i] = gData.nPortNo_UnloadPicker[i] = gData.nPortNo_NGTray[i] = gData.nPortNo_GoodTray[i] = 0;
		gData.nElevatGDTray[i] = 0;
	}
	for(int i=0; i<4; i++) {
		gData.sLotID_VisionStage[i] = "";	gData.nTrayNo_VisionStage[i] = 0; gData.nPortNo_VisionStage[i] = 0;
	}
	gData.sLotID_Tansfer[2] = gData.sLotID_LoadStage[2] = gData.sLotID_LoadPicker[2] = gData.sLotID_UnloadPicker[2] = gData.sLotID_NGTray[2] = gData.sLotID_GoodTray[2] = gData.sLotID_VisionStage[4] = ""; 

	gLot.nJobCycle = gLot.nJobStatus = gLot.nUnLastPortID = 0;
	for(int i=0; i<6; i++) {
		gLot.nCmCount[i] = gLot.nTrayCount[i] = gLot.nLastCount[i] = gLot.nLotStatus[i] = gLot.nTrayOutCnt[i] = gLot.nGoodCount[i] = gLot.nNgCount[i] = 0;
		gLot.nUnlGdTrayCount[i] = gLot.nUnlNGTrayCount[i] = gLot.nOutTrayCnt[i][0] = gLot.nOutTrayCnt[i][1] = gLot.nSkipCount[i] = gLot.nAlignCount[i] = 0;
		gLot.nErrorCount[i] = gLot.dwErrorTime[i] = gLot.dwStopTime[i] = gMes.nLotStatus[i] = 0;
		gLot.sLotID[i] = gLot.sLLStartTime[i] = gLot.sLLEndTime[i] = "";
		gLot.bEmptyTray[i] = gLot.bEmptyNGTray[i] = FALSE;
		for (int j = 0; j < 3; j++) gLot.nTrayPutCnt[i][j] = 0;
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 20; j++) {
			for (int k = 0; k < 40; k++) {
				gMes.nCmResult[i][j][k] = gLot.nJudge_R[i][j][k] = gLot.nImageCnt[i][j][k] = gLot.nMarginal[i][j][k] = 0; gLot.sBarCode[i][j][k] = "";
				for (int l = 0; l < 6; l++) { gLot.nJudge_I[i][j][k][l] = 0; gLot.sNGCode_I[i][j][k][l] = ""; }
				for (int l = 0; l <10; l++)	  gLot.nHistory[i][j][k][l] = 0;
			}
		}
	}
	for (int i = 0; i < 6; i++) for (int j = 0; j <13; j++) gLot.nRosJugCount[i][j] = 0;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 7; j++) gData.dElevatorZPos[i][j] = 0.0;
	g_objDispatcher.Reset(0);

	for (int i = 0; i < 6; i++) for (int j = 0; j < 16; j++) for (int k = 0; k < 40; k++) for (int m = 0; m < 5; m++) for (int n = 0; n < 10; n++) gNG->sNGCode[i][j][k][m][n] = "";
	for (int i = 0; i < 6; i++) for (int j = 0; j <640; j++) for (int k = 0; k < 10; k++) gNG->sModuleID[i][j][k] = "";
	for(int i=0; i< 5; i++) gData.nNG_MC[i][1] = 0;

//	CString strLog;
//	strLog.Format("[SequenceMain] Scan Wait(%0.4lf) Count(%d) Inspection Wait(%0.4lf) Count(%d)", gData.dScanTime, gData.nScanTimeOverCnt, gData.dInspTime, gData.nInspectionOverCnt);
//	g_objLogFile.Save_HandlerLog(strLog);
	g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 0, NULL);
}

///////////////////////////////////////////////////////////////////////////////

int CSequenceMain::Get_NGCmCount(int nStageNo)
{
	int nCount = 0;
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoNgTray[i][j] > 0) nCount++;
		}
	}
	return nCount;
}

BOOL CSequenceMain::Search_Module(CString sLotID, CString sModuleID)
{
	if (gData.bJahwa) return TRUE;
	if (!m_pEquipData->bUseMES) return TRUE;
	if (sModuleID.GetLength() < 20) return TRUE;

	for(int i=0; i<6; i++) {
		if (gLot.sLotID[i] == sLotID) {
			for(int j=0; j<640; j++) {
				if (gNG->sModuleID[i][j][0] == sModuleID) return TRUE;
			}
			return FALSE;	//NG처리,허수배출
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_Transfer1(int &nFmTarget, int &nToTarget, int &nPortNo)
{
	//gData.nElevatorOpen[10] //0:Stop,1:Open,2:Opened //1(L1),2(L2),3(EN),4(EG),5(NB),6(U1),7(U2)
	//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)
	//1순위 Stage  -> Empty-Good
	//2순위 Load12 -> Empty-NG
	//3순위 Load12 -> Stage

	//1순위 Stage  -> Empty-Good
	nFmTarget = nToTarget = nPortNo = 0;
	if (m_nLoadStage1Case == 60 && m_pDX04->iLoadStage1TrayExist) { nFmTarget = 1; nToTarget = 6; nPortNo = gData.nPortNo_LoadStage[0]; }
	if (m_nLoadStage2Case == 60 && m_pDX04->iLoadStage2TrayExist) { nFmTarget = 2; nToTarget = 6; nPortNo = gData.nPortNo_LoadStage[1]; }
	if (nFmTarget > 0 && nToTarget > 0) return TRUE;

	if (gData.bCycleStop) return FALSE;
	//2순위 Load12 -> Empty-NG
	
	int nJobNo = 0;
	int nSNo = gLot.nJobCycle;
	for(int i=nSNo; i<6; i++) {
		if (gLot.nCmCount[i] > 0 && gLot.nTrayCount[i] > 1) {
			nJobNo = i;
			if (gLot.bEmptyTray[i] == FALSE) { nPortNo = i+11; break; }
			if (gLot.nTrayCount[i]-1 > gLot.nTrayOutCnt[i]) { nPortNo = i+1; break; }
		}
		if (nPortNo > 0) break;
	}
	if (nPortNo == 0) {
		for(int i=0; i<nSNo; i++) {
			if (gLot.nCmCount[i] > 0 && gLot.nTrayCount[i] > 1) {
				nJobNo = i;
				if (gLot.bEmptyTray[i] == FALSE) { nPortNo = i+11; break; }
				if (gLot.nTrayCount[i]-1 > gLot.nTrayOutCnt[i]) { nPortNo = i+1; break; }
			}
			if (nPortNo > 0) break;
		}
	}
	if (nPortNo == 0) return FALSE;

	if ((nPortNo >= 1 && nPortNo <= 3) || (nPortNo >= 11 && nPortNo <= 13)) nFmTarget = 3;
	else																	nFmTarget = 4;
	if (nPortNo > 10) {
		gLot.nJobCycle = nJobNo;
		if (nPortNo == 12) {	//착공순서문제 보완
			if (gLot.nCmCount[0] > 0 && gLot.bEmptyTray[0] == FALSE) { gLot.nJobCycle = 0; return FALSE; }
		}
		if (nPortNo == 13) {
			if (gLot.nCmCount[0] > 0 && gLot.bEmptyTray[0] == FALSE) { gLot.nJobCycle = 0; return FALSE; }
			if (gLot.nCmCount[1] > 0 && gLot.bEmptyTray[1] == FALSE) { gLot.nJobCycle = 1; return FALSE; }
		}
		if (nPortNo == 15) {
			if (gLot.nCmCount[3] > 0 && gLot.bEmptyTray[3] == FALSE) { gLot.nJobCycle = 3; return FALSE; }
		}
		if (nPortNo == 16) {
			if (gLot.nCmCount[3] > 0 && gLot.bEmptyTray[3] == FALSE) { gLot.nJobCycle = 3; return FALSE; }
			if (gLot.nCmCount[4] > 0 && gLot.bEmptyTray[4] == FALSE) { gLot.nJobCycle = 4; return FALSE; }
		}

		nPortNo = nPortNo - 10; nToTarget = 5;	return TRUE;
	}

	//3순위 Load12 -> Stage12
//	if (gData.nPortNo_LoadStage[0] > 0 && gData.nPortNo_LoadStage[1] > 0) return FALSE;
	if (m_pDX04->iLoadStage1TrayExist && m_pDX04->iLoadStage2TrayExist) return FALSE;
	if (m_nLoadStage1Case > 0 && m_nLoadStage2Case > 0) return FALSE;
	nToTarget = 1;

	if (nFmTarget > 0 && nToTarget > 0) { gLot.nJobCycle = nJobNo; return TRUE; }
	else								return FALSE;
}

BOOL CSequenceMain::Check_Transfer2(int &nFmTarget, int &nToTarget, int &nPortNo)
{
	int		nSNo;
	CString sLogID;
	//gData.nElevatorOpen[10] //0:Stop,1:Open,2:Opened //1(L1),2(L2),3(EN),4(EG),5(NB),6(U1),7(U2)
	//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)

	//1순위 Empty-NG(E3)  -> Unload Lot 12(E67)
	//2순위 Good-Stage 12 -> Unload Lot 12(E67)
	//3순위 Empty-Good(E4)-> Buffer NG(E5)
	//4순위 NG-Stage 12   -> Buffer NG(E5)
	//5순위 Empty-Good(E4)-> Good-Stage 12
	//6순위 Empty-NG(E3)  -> NG-Stage 12

	//1순위 Empty-NG(E3) -> Unload Lot 12(E67)
	nFmTarget = nToTarget = nPortNo = 0;
	if (gData.nElevatGDTray[0] == 2) { nFmTarget = 5; nToTarget = 8; return TRUE; }
	if (gData.nElevatGDTray[1] == 2) { nFmTarget = 5; nToTarget = 9; return TRUE; }

	//2순위 Good-Stage 12-> Unload Lot 12
	nFmTarget = nToTarget = nPortNo = 0;
	if ((m_nGoodStage1Case == 60 && m_pDX12->iGoodStage1TrayExist) ||
		(m_nGoodStage2Case == 60 && m_pDX12->iGoodStage2TrayExist)) {
		if (m_nGoodStage1Case == 60) { nFmTarget = 12; nPortNo = gData.nPortNo_GoodTray[0]; }
		if (m_nGoodStage2Case == 60) { nFmTarget = 13; nPortNo = gData.nPortNo_GoodTray[1]; }

		if (nPortNo >= 1 && nPortNo <= 3 && gData.nElevatGDTray[0] != 2) nToTarget = 8;
		if (nPortNo >= 4 && nPortNo <= 6 && gData.nElevatGDTray[1] != 2) nToTarget = 9;
	}
	if (nFmTarget > 0 && nToTarget > 0) return TRUE;

	//3순위 Empty-Good(E4)-> Buffer NG(E5)
	nFmTarget = nToTarget = nPortNo = 0;
	if (gData.nNGLot_NGBuffer == 1) { nFmTarget = 6; nToTarget = 7; return TRUE; }

	//4순위 NG-Stage 12  -> Buffer NG(E5)
	nFmTarget = nToTarget = nPortNo = 0;
	if ((m_nNGStage1Case == 60 && m_pDX11->iNGStage1TrayExist) ||
		(m_nNGStage2Case == 60 && m_pDX11->iNGStage2TrayExist)) {
		if (m_nNGStage1Case == 60) { nFmTarget = 10; nPortNo = gData.nPortNo_NGTray[0]; sLogID = gData.sLotID_NGTray[0]; nSNo = 1; }
		if (m_nNGStage2Case == 60) { nFmTarget = 11; nPortNo = gData.nPortNo_NGTray[1]; sLogID = gData.sLotID_NGTray[1]; nSNo = 2; }

		if (gData.nNGLot_NGBuffer != 1) { nToTarget = 7; return TRUE; }
	}

	if (Check_ModuleEmpty())  return FALSE;

	//5순위 Empty-Good   -> Good-Stage 12
	nFmTarget = nToTarget = nPortNo = 0;
	if (m_nGoodStage1Case == 0 && !m_pDX12->iGoodStage1TrayExist) { nFmTarget = 6; nToTarget = 12; nPortNo = gData.nPortNo_GoodTray[0]; }
	if (m_nGoodStage2Case == 0 && !m_pDX12->iGoodStage2TrayExist) { nFmTarget = 6; nToTarget = 13; nPortNo = gData.nPortNo_GoodTray[1]; }
	if (nFmTarget > 0 && nToTarget > 0) return TRUE;

	//6순위 Empty-NG     -> NG-Stage 12
	nFmTarget = nToTarget = nPortNo = 0;
	if (m_nNGStage1Case == 0 && !m_pDX11->iNGStage1TrayExist) {	nFmTarget = 5;	nToTarget = 10; nPortNo = gData.nPortNo_NGTray[0]; }
	if (m_nNGStage2Case == 0 && !m_pDX11->iNGStage2TrayExist) {	nFmTarget = 5;	nToTarget = 11; nPortNo = gData.nPortNo_NGTray[1]; }
	if (nFmTarget > 0 && nToTarget > 0) return TRUE;

	return FALSE;
}

BOOL CSequenceMain::Check_TrayEmpty()
{
	if (m_pDX03->iTransferLTrayExist) return FALSE;
	if (m_pDX03->iTransferRTrayExist) return FALSE;
	if (m_pDX04->iLoadStage1TrayExist) return FALSE;
	if (m_pDX04->iLoadStage2TrayExist) return FALSE;
	if (m_pDX11->iNGStage1TrayExist) return FALSE;
	if (m_pDX11->iNGStage2TrayExist) return FALSE;
	if (m_pDX12->iGoodStage1TrayExist) return FALSE;
	if (m_pDX12->iGoodStage2TrayExist) return FALSE;

	return TRUE;
}

BOOL CSequenceMain::Check_ModuleEmpty()
{
	for (int i=0; i<2; i++) {
		if (gData.sLotID_Tansfer[i].GetLength()>0) return FALSE;
		if (gData.sLotID_LoadStage[i].GetLength()>0) return FALSE;
		if (gData.sLotID_LoadPicker[i].GetLength()>0) return FALSE;
		if (gData.sLotID_UnloadPicker[i].GetLength()>0) return FALSE;
		if (gData.sLotID_NGTray[i].GetLength()>0) return FALSE;
		if (gData.sLotID_GoodTray[i].GetLength()>0) return FALSE;
	}
	for (int i=0; i<4; i++) {
		if (gData.sLotID_VisionStage[i].GetLength()>0) return FALSE;
	}	
	return TRUE;
}

BOOL CSequenceMain::Check_EmptyUnloadPicker()
{
	if (gData.sLotID_Tansfer[0].GetLength()>0) return FALSE;
	for (int i=0; i<2; i++) {
		if (gData.sLotID_LoadStage[i].GetLength()>0) return FALSE;
		if (gData.sLotID_LoadPicker[i].GetLength()>0) return FALSE;
		if (gData.sLotID_UnloadPicker[i].GetLength()>0) return FALSE;
	}
	for (int i=0; i<4; i++) {
		if (gData.sLotID_VisionStage[i].GetLength()>0) return FALSE;
	}	
	return TRUE;
}

BOOL CSequenceMain::Check_LotEndTray(CString sLotID, int nPortNo)
{
	if (sLotID == "" || nPortNo < 1) return FALSE;

	if (sLotID == gData.sLotID_Tansfer[0]) return FALSE;
	for (int i=0; i<2; i++) {
		if (sLotID == gData.sLotID_LoadStage[i]) return FALSE;
		if (sLotID == gData.sLotID_LoadPicker[i]) return FALSE;
		if (sLotID == gData.sLotID_UnloadPicker[i]) return FALSE;
		if (sLotID == gData.sLotID_GoodTray[i]) return FALSE;
//		if (sLotID == gData.sLotID_NGTray[i]) return FALSE;
	}
	for (int i=0; i<4; i++) {
		if (sLotID == gData.sLotID_VisionStage[i]) return FALSE;
	}
//	if (sLotID == gData.sLotID_NGBuffer) return FALSE;

	return TRUE;
}

BOOL CSequenceMain::Check_LotEndNG()
{
	if (gData.sLotID_Tansfer[0].GetLength()>0) return FALSE;
	for (int i=0; i<2; i++) {
		if (gData.sLotID_LoadStage[i].GetLength()>0) return FALSE;
		if (gData.sLotID_LoadPicker[i].GetLength()>0) return FALSE;
		if (gData.sLotID_UnloadPicker[i].GetLength()>0) return FALSE;
		if (gData.sLotID_NGTray[i].GetLength()>0) return FALSE;
	}
	for (int i=0; i<4; i++) {
		if (gData.sLotID_VisionStage[i].GetLength()>0) return FALSE;
	}	
	return TRUE;
}

BOOL CSequenceMain::Check_LotEndNGTray(CString sLotID, int nPortNo, int nNo)
{
	if (sLotID == "" || nPortNo < 1) return FALSE;
	if (gLot.nTrayCount[nPortNo-1]-1 != gLot.nTrayOutCnt[nPortNo-1]) return FALSE;

	if (sLotID == gData.sLotID_Tansfer[0]) return FALSE;
	for (int i=0; i<2; i++) {
		if (sLotID == gData.sLotID_LoadStage[i]) return FALSE;
		if (sLotID == gData.sLotID_LoadPicker[i]) return FALSE;
		if (sLotID == gData.sLotID_UnloadPicker[i]) return FALSE;
		if (sLotID == gData.sLotID_GoodTray[i]) return FALSE;
	}
	for (int i=0; i<4; i++) {
		if (sLotID == gData.sLotID_VisionStage[i]) return FALSE;
	}
	if (m_pEquipData->bUseCMCheck && sLotID == gData.sLotID_NGBuffer) return FALSE;
	if (m_pEquipData->bUseCMCheck == FALSE) {
		if (nNo == 1 && sLotID == gData.sLotID_NGTray[1]) return FALSE;
		if (nNo == 2 && sLotID == gData.sLotID_NGTray[0]) return FALSE;
	}

	return TRUE;
}

BOOL CSequenceMain::Check_LotEndENGTray(CString sLotID, int nPortNo)
{
	if (sLotID == "" || nPortNo < 1) return FALSE;
	if (gLot.nTrayCount[nPortNo-1]-1 != gLot.nTrayOutCnt[nPortNo-1]) return FALSE;

	for (int i=0; i<2; i++) {
		if (sLotID == gData.sLotID_Tansfer[i]) return FALSE;
		if (sLotID == gData.sLotID_LoadStage[i]) return FALSE;
		if (sLotID == gData.sLotID_LoadPicker[i]) return FALSE;
		if (sLotID == gData.sLotID_UnloadPicker[i]) return FALSE;
		if (sLotID == gData.sLotID_GoodTray[i]) return FALSE;
		if (m_pEquipData->bUseCMCheck == FALSE && sLotID == gData.sLotID_NGTray[i]) return FALSE;
	}
	for (int i=0; i<4; i++) {
		if (sLotID == gData.sLotID_VisionStage[i]) return FALSE;
	}

	return TRUE;
}

BOOL CSequenceMain::Check_LotEndUnloadPicker(CString sLotID, int nPortNo)
{
	if (sLotID == "" || nPortNo < 1) return FALSE;
	if (gLot.nTrayCount[nPortNo-1]-1 != gLot.nTrayOutCnt[nPortNo-1]) return FALSE;

	if (sLotID == gData.sLotID_Tansfer[0]) return FALSE;
	for (int i=0; i<2; i++) {
		if (sLotID == gData.sLotID_LoadStage[i]) return FALSE;
		if (sLotID == gData.sLotID_LoadPicker[i]) return FALSE;
		if (sLotID == gData.sLotID_UnloadPicker[i]) return FALSE;
	}
	for (int i=0; i<4; i++) {
		if (sLotID == gData.sLotID_VisionStage[i]) return FALSE;
	}
//	if (m_pEquipData->bUseCMCheck == FALSE && sLotID == gData.sLotID_NGBuffer) return FALSE;
	return TRUE;
}

BOOL CSequenceMain::Check_LotEndUnloadNG(CString sLotID, int nPortNo, int nPickNo)
{
	if (sLotID == "" || nPortNo < 1) return FALSE;
	if (gLot.nTrayCount[nPortNo-1]-1 != gLot.nTrayOutCnt[nPortNo-1]) return FALSE;

	if (sLotID == gData.sLotID_Tansfer[0]) return FALSE;
	for (int i=0; i<2; i++) {
		if (sLotID == gData.sLotID_LoadStage[i]) return FALSE;
		if (sLotID == gData.sLotID_LoadPicker[i]) return FALSE;
	}
	if (nPickNo == 1) { if (sLotID == gData.sLotID_UnloadPicker[1]) return FALSE; }
	else			  { if (sLotID == gData.sLotID_UnloadPicker[0]) return FALSE; }
	for (int i=0; i<4; i++) {
		if (sLotID == gData.sLotID_VisionStage[i]) return FALSE;
	}
	return TRUE;
}

void CSequenceMain::Set_NextLot(CString sLotID, DWORD dwTime)
{
	int nNextPortLot = 0;
	for (int i=0; i<2; i++) {
		if (gData.sLotID_GoodTray[i].GetLength() > 1 && gData.nPortNo_GoodTray[i] > 0 && sLotID != gData.sLotID_GoodTray[i]) {
			nNextPortLot = gData.nPortNo_GoodTray[i]; gLot.dwLLLotStart[nNextPortLot-1] = dwTime;
		}
	}
	for (int i=0; i<2; i++) {
		if (gData.sLotID_NGTray[i].GetLength() > 1 && gData.nPortNo_NGTray[i] > 0 && sLotID != gData.sLotID_NGTray[i]) {
			nNextPortLot = gData.nPortNo_NGTray[i]; gLot.dwLLLotStart[nNextPortLot-1] = dwTime;
		}
	}
	for (int i=0; i<2; i++) {
		if (gData.sLotID_UnloadPicker[i].GetLength() > 1 && gData.nPortNo_UnloadPicker[i] > 0 && sLotID != gData.sLotID_UnloadPicker[i]) {
			nNextPortLot = gData.nPortNo_UnloadPicker[i]; gLot.dwLLLotStart[nNextPortLot-1] = dwTime;
		}
	}
	for (int i=0; i<4; i++) {
		if (gData.sLotID_VisionStage[i].GetLength() > 1 && gData.nPortNo_VisionStage[i] > 0 && sLotID != gData.sLotID_VisionStage[i]) {
			nNextPortLot = gData.nPortNo_VisionStage[i]; gLot.dwLLLotStart[nNextPortLot-1] = dwTime;
		}
	}
	for (int i=0; i<2; i++) {
		if (gData.sLotID_LoadPicker[i].GetLength() > 1 && gData.nPortNo_LoadPicker[i] > 0 && sLotID != gData.sLotID_LoadPicker[i]) {
			nNextPortLot = gData.nPortNo_LoadPicker[i]; gLot.dwLLLotStart[nNextPortLot-1] = dwTime;
		}
	}
	for (int i=0; i<2; i++) {
		if (gData.sLotID_LoadStage[i].GetLength() > 1 && gData.nPortNo_LoadStage[i] > 0 && sLotID != gData.sLotID_LoadStage[i]) {
			nNextPortLot = gData.nPortNo_LoadStage[i]; gLot.dwLLLotStart[nNextPortLot-1] = dwTime;
		}
	}
	if (gData.sLotID_Tansfer[0].GetLength() > 1 && gData.nPortNo_Tansfer[0] > 0 && sLotID != gData.sLotID_Tansfer[0]) {
		nNextPortLot = gData.nPortNo_Tansfer[0]; gLot.dwLLLotStart[nNextPortLot-1] = dwTime;
	}
}

BOOL CSequenceMain::Check_EmptyNGTray()
{
	for(int i=0; i<TRAY_CM_Y; i++) {
		for(int j=0; j<TRAY_CM_X; j++) {
			if (gData.InfoNgTray[i][j] > 0) return FALSE;
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_EmptyGoodTray()
{
	for(int i=0; i<TRAY_CM_Y; i++) {
		for(int j=0; j<TRAY_CM_X; j++) {
			if (gData.InfoGoodTray[i][j] > 0) return FALSE;
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_Load12Empy()
{
	for(int i=0; i<6; i++) {
		if (gLot.nCmCount[i] > 0) {
			if (gLot.nTrayCount[i]-1 > gLot.nTrayOutCnt[i]) return FALSE;
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_LotRun(int nSNo, int nPortNo)
{
	int nPno;
	if (nSNo == 0 && gData.sLotID_LoadStage[1].GetLength() > 1 && gData.nPortNo_LoadStage[1] > 0) {
		nPno = gData.nPortNo_LoadStage[1];
		if (nPno > 0 && gLot.sRecipeName[nPno-1] == gLot.sRecipeName[nPortNo-1]) return TRUE;
		else																	 return FALSE;
	}
	if (nSNo == 1 && gData.sLotID_LoadStage[0].GetLength() > 1 && gData.nPortNo_LoadStage[0] > 0) {
		nPno = gData.nPortNo_LoadStage[0];
		if (nPno > 0 && gLot.sRecipeName[nPno-1] == gLot.sRecipeName[nPortNo-1]) return TRUE;
		else																	 return FALSE;
	}
	for (int i=0; i<2; i++) {
		if (gData.sLotID_LoadPicker[i].GetLength() > 1 && gData.nPortNo_LoadPicker[i] > 0) {
			nPno = gData.nPortNo_LoadPicker[1];
			if (nPno > 0 && gLot.sRecipeName[nPno-1] == gLot.sRecipeName[nPortNo-1]) return TRUE;
			else																	 return FALSE;
		}
	}
	for (int i=0; i<4; i++) {
		if (gData.sLotID_VisionStage[i].GetLength() > 1 && gData.nPortNo_VisionStage[i] > 0) {
			nPno = gData.nPortNo_VisionStage[1];
			if (nPno > 0 && gLot.sRecipeName[nPno-1] == gLot.sRecipeName[nPortNo-1]) return TRUE;
			else																	 return FALSE;
		}
	}
	for (int i=0; i<2; i++) {
		if (gData.sLotID_UnloadPicker[i].GetLength() > 1 && gData.nPortNo_UnloadPicker[i] > 0) {
			nPno = gData.nPortNo_UnloadPicker[1];
			if (nPno > 0 && gLot.sRecipeName[nPno-1] == gLot.sRecipeName[nPortNo-1]) return TRUE;
			else																	 return FALSE;
		}
	}
	return TRUE;
}

void CSequenceMain::Set_AlignData(int nPortNo)
{
	int nCount = 0;
#ifdef AJIN_BOARD_USE
	if (gLot.nTrayCount[nPortNo-1]-1 == gLot.nTrayOutCnt[nPortNo-1]) {
		for(int i=0; i<10; i++) {
			for(int j=0; j<4; j++) {
				nCount++;
				if (nCount <= gLot.nLastCount[nPortNo-1]) gData.InfoAlignTray[i][j] = 2;
			}
		}
	} else {
		for(int i=0; i<10; i++) for(int j=0; j<4; j++) gData.InfoAlignTray[i][j] = 2;	//Good
	}
#else
	if (gLot.nCmCount[nPortNo-1] > 20 || !m_pEquipData->bUseGoodSort) {
		if (gLot.nTrayCount[nPortNo-1]-1 == gLot.nTrayOutCnt[nPortNo-1]) {
			for(int i=0; i<10; i++) {
				for(int j=0; j<4; j++) {
					nCount++;
					if (nCount <= gLot.nLastCount[nPortNo-1]) gData.InfoAlignTray[i][j] = 2;
				}
			}
		} else {
			for(int i=0; i<10; i++) for(int j=0; j<4; j++) gData.InfoAlignTray[i][j] = 2;	//Good
		}
	} else {
		if (gLot.nCmCount[nPortNo-1] == 10) {
			gData.InfoAlignTray[0][1] = 2; gData.InfoAlignTray[0][3] = 2;
			gData.InfoAlignTray[1][1] = 2; gData.InfoAlignTray[1][3] = 2;
			gData.InfoAlignTray[2][1] = 2; gData.InfoAlignTray[2][3] = 2;
			gData.InfoAlignTray[5][1] = 2; gData.InfoAlignTray[5][3] = 2;
			gData.InfoAlignTray[8][1] = 2; gData.InfoAlignTray[8][3] = 2;
		} else {
			for(int i=0; i<10; i++) {
				for(int j=0; j<2; j++) {
					nCount++;
					if (nCount <= gLot.nCmCount[nPortNo-1]) gData.InfoAlignTray[i][j] = 2;
				}
			}
		}
	}
#endif
	g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 1, NULL);
}

BOOL CSequenceMain::Check_AlignData(int nPortNo)
{
	int nCMCount = 0;
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoAlignTray[i][j] > 0) nCMCount++;
		}
	}
	if (nCMCount < 1) return FALSE;

	if (gLot.nTrayCount[nPortNo-1]-1 == 1) {
		if (gLot.nCmCount[nPortNo-1] != nCMCount) {
			gAlm.nPortNo = nPortNo;
			gLot.nAlignCount[nPortNo-1] = nCMCount;
			return FALSE;
		}
	}

	if (m_pEquipData->bUseAlign1) {
		if (gLot.nTrayCount[nPortNo-1]-1 == gLot.nTrayOutCnt[nPortNo-1]) {
			if (gLot.nCmCount[nPortNo-1] != gLot.nAlignCount[nPortNo-1]) {
				gAlm.nPortNo = nPortNo;
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CSequenceMain::Check_AlignDataAdd(int nPortNo)
{
	int nCMCount = 0;
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoAlignTray[i][j] > 0) nCMCount++;
		}
	}
	gLot.nAlignCount[nPortNo-1] = gLot.nAlignCount[nPortNo-1] + nCMCount;
	gAlm.nAlignCount = nCMCount;

	return TRUE;
}

void CSequenceMain::Set_AlignToStage(int nPortNo)
{
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoAlignTray[i][j] > 0) gData.InfoLoadTray[i][j] = 1;
			else							   gData.InfoLoadTray[i][j] = 0;
		}
	}
	g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 2, NULL);
	Init_AlignTray();
}

BOOL CSequenceMain::Check_LoadModule(int &nYNo)
{
	if (nYNo > 0) {
		if (nYNo > 9) return FALSE;
		for(int j=0; j<4; j++) {
			if (gData.InfoLoadTray[nYNo][j] > 0) { nYNo++; return TRUE; }
		}
	} else {
		for(int i=0; i<10; i++) {
			for(int j=0; j<4; j++) {
				if (gData.InfoLoadTray[i][j] > 0) { nYNo = i+1; return TRUE; } 
			}
		}
	}
	return FALSE;
}

BOOL CSequenceMain::Check_EmptyLoadTray()
{
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoLoadTray[i][j] > 0) return FALSE; 
		}
	}
	return TRUE;
}

void CSequenceMain::Init_AlignTray()
{
	for(int i=0; i<10; i++) for(int j=0; j<4; j++) gData.InfoAlignTray[i][j] = 0;
	g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 1, NULL);
}

void CSequenceMain::Init_LoadTray()
{
	for(int i=0; i<10; i++) for(int j=0; j<4; j++) gData.InfoLoadTray[i][j] = 0;
	g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 2, NULL);
}

void CSequenceMain::Init_NgTray(int nStageNo)
{
	gData.sLotID_NGTray[nStageNo]  = "";
	gData.nTrayNo_NGTray[nStageNo] = gData.nPortNo_NGTray[nStageNo] = 0;

	for(int i=0; i<10; i++) for(int j=0; j<4; j++) gData.InfoNgTray[i][j] = 0;
	g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 3, NULL);
}

void CSequenceMain::Init_GoodTray(int nStageNo)
{
	gData.sLotID_GoodTray[nStageNo]  = "";
	gData.nTrayNo_GoodTray[nStageNo] = gData.nPortNo_GoodTray[nStageNo] = 0;

	for(int i=0; i<10; i++) for(int j=0; j<4; j++) gData.InfoGoodTray[i][j] = 0;
	g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 4, NULL);
}

void CSequenceMain::Init_ShiipAlignData(int nJobNo)
{
	if (nJobNo == 0) {
		for(int i=0; i<4; i++) {
			for(int j=0; j<3; j++) {
				gData.dAlignVisionX[i][j] = gData.dAlignVisionY[i][j] = 0.0;
			}
		}
	} else {
		for(int j=0; j<3; j++) {
			gData.dAlignVisionX[nJobNo-1][j] = gData.dAlignVisionY[nJobNo-1][j] = 0.0;
		}
	}
}

BOOL CSequenceMain::Check_InspectDone(int nPNo, int nPortNo, int nTrayNo)
{
	BOOL bUseVision = TRUE;
	if (nPNo < 1 || nPNo > 2 || nPortNo < 1 || nPortNo > 6 || nTrayNo < 1 || nTrayNo > 16) return FALSE;

	if (!m_pEquipData->bUseBottom && !m_pEquipData->bUseTop1 && !m_pEquipData->bUseTop2 && !m_pEquipData->bUseBotAng && !m_pEquipData->bUseTopAng) bUseVision = FALSE;
	if (!gData.bUseDryRun && bUseVision) {
		Set_InspectDone(nPNo, nPortNo, nTrayNo);
		for (int i = 0; i < 8; i++) {
			if (gData.InfoUnloadPick[nPNo-1][i] == 1) return FALSE;
		}
	}

	int nNGType[8] = { 3, 4, 5, 11, 12, 15, 15, 15 };
	if (gData.bUseDryRun ||  gData.bCycleStop || gData.bResultTest || bUseVision == FALSE) {
		int nCno = gData.InfoUnloadPick[nPNo-1][9] - 1;
		for(int i=0; i<8; i++) {
			if (gData.InfoUnloadPick[nPNo-1][i] > 0) {
				int nRand = g_objCommon.Get_Random(0, 99); gData.InfoUnloadPick[nPNo-1][i] = (nRand < m_pEquipData->nDryRunNg ? 3 : 2);
				if (!bUseVision && !gData.bResultTest) {
					if (m_pEquipData->bUseGoodSort) { if (gData.InfoUnloadPick[nPNo-1][i] == 3) gData.InfoUnloadPick[nPNo-1][i] = 7; }
					if (gData.InfoUnloadPick[nPNo-1][i] != 2) {
						gLot.sNGCode_I[nPortNo-1][nTrayNo-1][i+nCno][0] = "NG-Code";
						for(int j=0; j<10; j++) {
							gNG->sNGCode[nPortNo-1][nTrayNo-1][i+nCno][2][j] = "NG-Code"; 
						}
						if (nNGType[i] == 15) {
							gLot.nJudge_I[nPortNo-1][nTrayNo-1][i+nCno][0] = 15;	//Marginal_OK
							gLot.nMarginal[nPortNo-1][nTrayNo-1][i+nCno] = i+1;
							gLot.sNGCode_I[nPortNo-1][nTrayNo-1][i+nCno][0] = "MARGINAL_OK";
						}
						gData.InfoUnloadPick[nPNo-1][i] = nNGType[i];
					}
				}
			}
		}
	} else {
		for(int i=0; i<8; i++) {
			if (gData.InfoUnloadPick[nPNo-1][i] == 1) return FALSE;
		}
	}
	return TRUE;
}

void CSequenceMain::Set_InspectDone(int nPNo, int nPortNo, int nTrayNo)
{
	if (nPNo < 1 || nPNo > 2 || nPortNo < 1 || nPortNo > 6 || nTrayNo < 1 || nTrayNo > 20 ) return;

	int nCno = gData.InfoUnloadPick[nPNo-1][9] - 1;
	for(int i=0; i<8; i++) {
		if ((i+nCno) >= 40) break;

		if (gData.InfoUnloadPick[nPNo-1][i] > 0) {
			if (gData.bUseBarSort) {
				if (gLot.sBarCode[nPortNo-1][nTrayNo-1][i+nCno].GetLength() > 0) {
					if (g_objCommon.BarcodeFind(gLot.sBarCode[nPortNo-1][nTrayNo-1][i+nCno]) > 0) {
						if (gData.nBarSortTray == 1) gData.InfoUnloadPick[nPNo-1][i] = 3;	//NG
						else						 gData.InfoUnloadPick[nPNo-1][i] = 2;	//Good
					} else {
						if (gData.nBarSortTray == 1) gData.InfoUnloadPick[nPNo-1][i] = 2;	//Good
						else						 gData.InfoUnloadPick[nPNo-1][i] = 3;	//NG
					}
				}
			} else {
				if (gLot.nJudge_I[nPortNo-1][nTrayNo-1][i+nCno][0] > 0) {
					gData.InfoUnloadPick[nPNo-1][i] = gLot.nJudge_I[nPortNo-1][nTrayNo-1][i+nCno][0];
				}
			}
		}
	}
}

void CSequenceMain::Set_ReInspectDone(int nPNo, int nPortNo, int nTrayNo)
{
	if (nPNo < 1 || nPNo > 2 || nPortNo < 1 || nPortNo > 6 || nTrayNo < 1 || nTrayNo > 20 ) return;

	int nCno = gData.InfoUnloadPick[nPNo-1][9] - 1;
	for(int i=0; i<8; i++) {
		if ((i+nCno) >= 40) break;

		if (gData.InfoUnloadPick[nPNo-1][i] == 1) {
			if (gData.bUseBarSort) {
				if (gLot.sBarCode[nPortNo-1][nTrayNo-1][i+nCno].GetLength() > 0) {
					if (g_objCommon.BarcodeFind(gLot.sBarCode[nPortNo-1][nTrayNo-1][i+nCno]) > 0) {
						if (gData.nBarSortTray == 1) gData.InfoUnloadPick[nPNo-1][i] = 3;	//NG
						else						 gData.InfoUnloadPick[nPNo-1][i] = 2;	//Good
					} else {
						if (gData.nBarSortTray == 1) gData.InfoUnloadPick[nPNo-1][i] = 2;	//Good
						else						 gData.InfoUnloadPick[nPNo-1][i] = 3;	//NG
					}
				} else {
						if (gData.nBarSortTray == 1) gData.InfoUnloadPick[nPNo-1][i] = 2;	//Good
						else						 gData.InfoUnloadPick[nPNo-1][i] = 3;	//NG
				}
			} else {
				if (gLot.sBarCode[nPortNo-1][nTrayNo-1][i+nCno].GetLength() < 15) {
					gLot.nJudge_I[nPortNo-1][nTrayNo-1][i+nCno][0]  = 12;	//BARCODE_NOREAD
					gLot.sNGCode_I[nPortNo-1][nTrayNo-1][i+nCno][0] = "BARCODE_NOREAD";
					gLot.nRosJugCount[nPortNo-1][5]++; gLot.nRosJugCount[nPortNo-1][7]++;
					gData.InfoUnloadPick[nPNo-1][i] = 12;
				} else {
					gLot.nJudge_I[nPortNo-1][nTrayNo-1][i+nCno][0]  = 5;	//Vision Result Timeout
					gLot.sNGCode_I[nPortNo-1][nTrayNo-1][i+nCno][0] = "Vision Result Timeout";
					gLot.nRosJugCount[nPortNo-1][5]++; gLot.nRosJugCount[nPortNo-1][9]++;
					gData.InfoUnloadPick[nPNo-1][i] = 5; 
				}
				gData.nNG_MC[3][1]++;
			}
			m_sLog.Format("Set_ReInspectDone MC[Unload Picker:%d LotID[%s] PortNo:%d TrayNo:%d CmNo:%d Bar:%s] NG_Count(%d) NG_Code(%d) BarSort(%d-%d)",
				nPNo, gData.sLotID_UnloadPicker[nPNo-1], nPortNo, nTrayNo, (i+nCno+1), gLot.sBarCode[nPortNo-1][nTrayNo-1][i+nCno], gData.nNG_MC[3][1], gData.InfoUnloadPick[nPNo-1][i], gData.bUseBarSort, gData.nBarSortTray);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
	}
		
	if (gData.nNG_MC[3][0] > 0 && gData.nNG_MC[3][0] <= gData.nNG_MC[3][1]) {
		gAlm.sAlmLotID[0] = gData.sLotID_UnloadPicker[nPNo-1]; gAlm.sAlmLotID[1] = "Inspect"; 
		g_objCommon.Show_Error(9204);
	}
}

void CSequenceMain::Set_ROSTime(int nPNo, int nPortNo, int nTrayNo)
{
	if (nPNo < 1 || nPNo > 2 || nPortNo < 1 || nPortNo > 6 || nTrayNo < 1 || nTrayNo > 20) return;
	if (gData.bUseDryRun || gData.bCycleStop || !m_pEquipData->bUseROS) return;

	int nCNo = gData.InfoUnloadPick[nPNo-1][9];
	for(int i = 0; i < 8; i++) {
		if (gData.InfoUnloadPick[nPNo-1][i] > 0) {
			g_objDispatcher.Set_TimeOver(nPortNo, nTrayNo, i + nCNo);
		}
	}
}

BOOL CSequenceMain::Check_ROSDone(int nPNo, int nPortNo, int nTrayNo)
{
	if (gData.bUseBarSort) return TRUE;	//Barcode Sort사용
	if (nPNo < 1 || nPNo > 2 || nPortNo < 1 || nPortNo > 6 || nTrayNo < 1 || nTrayNo > 20) return FALSE;

	if (!m_pEquipData->bUseROS && m_pEquipData->bUsePassGood) {
		for(int i=0; i<8; i++) {
			if (gData.InfoUnloadPick[nPNo-1][i] > 0) gData.InfoUnloadPick[nPNo-1][i] = 2;
		}
		return TRUE;
	}
	if (gData.bUseDryRun || gData.bCycleStop || !m_pEquipData->bUseROS) return TRUE;

	int nCNo = gData.InfoUnloadPick[nPNo-1][9];
	for(int i = 0; i < 8; i++) {
		if (gData.InfoUnloadPick[nPNo-1][i] > 0) {
			if (!g_objDispatcher.Is_JudgeDone(nPortNo, nTrayNo, i + nCNo)) return FALSE;
		}
	}
	Set_ROSDone(nPNo, nPortNo, nTrayNo);

	return TRUE;
}

void CSequenceMain::Set_ROSDone(int nPNo, int nPortNo, int nTrayNo)
{
	if (nPNo < 1 || nPNo > 2 || nPortNo < 1 || nPortNo > 6 || nTrayNo < 1 || nTrayNo > 20 ) return;

	int nCno = gData.InfoUnloadPick[nPNo-1][9] - 1;
	for(int i=0; i<8; i++) {
		if ((i+nCno) >= 40) break;

		if (gData.InfoUnloadPick[nPNo-1][i] > 0) {
			if (gLot.nJudge_R[nPortNo-1][nTrayNo-1][i+nCno] > 0) {
				gData.InfoUnloadPick[nPNo-1][i] = gLot.nJudge_R[nPortNo-1][nTrayNo-1][i+nCno];
			}
			if (m_pEquipData->bUsePassGood) gData.InfoUnloadPick[nPNo-1][i] = 2;
		}
	}
}

BOOL CSequenceMain::Check_JudgeDone(int nPNo, int nPortNo, int nTrayNo)
{
	if (nPNo < 1 || nPNo > 4 || nPortNo < 1 || nPortNo > 6 || nTrayNo < 1 || nTrayNo > 20) return FALSE;

	if (gData.bUseDryRun || gData.bCycleStop) return TRUE;
	if (!m_pEquipData->bUseBottom && !m_pEquipData->bUseTop1 && !m_pEquipData->bUseTop2 && !m_pEquipData->bUseBotAng && !m_pEquipData->bUseTopAng) return TRUE;

	int nCMno = gData.InfoVision[nPNo-1][9] - 1;
	for (int i = 0; i < 8; i++) {
		if (gData.InfoVision[nPNo-1][i] > 0) {
			if (gLot.nJudge_I[nPortNo-1][nTrayNo-1][nCMno+i][0] == 0) return FALSE;
		}
	}

	if (!m_pEquipData->bUseROS) return TRUE;

	int nCNo = gData.InfoVision[nPNo-1][9];
	for(int i = 0; i < 8; i++) {
		if (gData.InfoVision[nPNo-1][i] > 0) {
			if (!g_objDispatcher.Is_JudgeDone(nPortNo, nTrayNo, nCNo+i)) return FALSE;
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_ShipAlign(int &nJobNo)
{
	//1순위 Good Stage
	//2순위 NG Stage
	nJobNo = 0;
	if (m_nNGStage1Case   == 20) nJobNo = 1;
	if (m_nNGStage2Case   == 20) nJobNo = 2;
	if (m_nGoodStage1Case == 20) nJobNo = 3;
	if (m_nGoodStage2Case == 20) nJobNo = 4;

	if (nJobNo > 0) return TRUE;
	else			return FALSE;
}

BOOL CSequenceMain::Get_TrayPosition(int nPNo, int nJobNo, int nPosX, int nPosY, double &dToPosX, double &dToPosY)
{
	double dX[3], dY[3];
	if (nPNo < 1 || nPNo > 2 || nJobNo < 1 || nJobNo > 4) return FALSE;

	m_pEquipData = g_objDataManager.Get_pEquipData();
	m_pMoveData  = g_objDataManager.Get_pMoveData();

	//(0,0) (3,0) (3,9) 점 좌표계산 (30,28)
	if (nJobNo == 1) //NG1
	{	
		dX[0] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[5] : m_pMoveData->dUnloadPickerX2[5]);
		dY[0] = m_pMoveData->dNGStageY1[3];			//(0,0)
		dX[1] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[9] : m_pMoveData->dUnloadPickerX2[9]);
		dY[1] = m_pMoveData->dNGStageY1[4];			//(3,0)
		dX[2] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[10] : m_pMoveData->dUnloadPickerX2[10]);
		dY[2] = m_pMoveData->dNGStageY1[5];			//(3,9)
	}
	if (nJobNo == 2) //NG2 
	{	
		dX[0] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[6] : m_pMoveData->dUnloadPickerX2[6]);
		dY[0] = m_pMoveData->dNGStageY2[3];			//(0,0)
		dX[1] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[11] : m_pMoveData->dUnloadPickerX2[11]);
		dY[1] = m_pMoveData->dNGStageY2[4];			//(3,0)
		dX[2] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[12] : m_pMoveData->dUnloadPickerX2[12]);
		dY[2] = m_pMoveData->dNGStageY2[5];			//(3,9)
	}
	if (nJobNo == 3) //Good1
	{	
		dX[0] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[7] : m_pMoveData->dUnloadPickerX2[7]);
		dY[0] = m_pMoveData->dGoodStageY1[3];		//(0,0)
		dX[1] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[13] : m_pMoveData->dUnloadPickerX2[13]);
		dY[1] = m_pMoveData->dGoodStageY1[4];		//(3,0)
		dX[2] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[14] : m_pMoveData->dUnloadPickerX2[14]);
		dY[2] = m_pMoveData->dGoodStageY1[5];		//(3,9)
	}
	if (nJobNo == 4) //Good2 
	{	
		dX[0] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[8] : m_pMoveData->dUnloadPickerX2[8]);
		dY[0] = m_pMoveData->dGoodStageY2[3];		//(0,0)
		dX[1] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[15] : m_pMoveData->dUnloadPickerX2[15]);
		dY[1] = m_pMoveData->dGoodStageY2[4];		//(3,0)
		dX[2] = (nPNo == 1 ? m_pMoveData->dUnloadPickerX1[16] : m_pMoveData->dUnloadPickerX2[16]);
		dY[2] = m_pMoveData->dGoodStageY2[5]	;	//(3,9)
	}

	//(0,0) (3,0) (3,9) 위치에 Vision Align 편차 계산
	if (m_pEquipData->bUseAlign2)
	{
		dX[0] = dX[0] + gData.dAlignVisionX[nJobNo-1][0];
		dY[0] = dY[0] + gData.dAlignVisionY[nJobNo-1][0];
		dX[1] = dX[1] + gData.dAlignVisionX[nJobNo-1][1];
		dY[1] = dY[1] + gData.dAlignVisionY[nJobNo-1][1];
		dX[2] = dX[2] + gData.dAlignVisionX[nJobNo-1][2];
		dY[2] = dY[2] + gData.dAlignVisionY[nJobNo-1][2];
	}

	//Pitch, Offset 계산
	double dPitchX  = (dX[1] - dX[0]) / 3.0;
	double dPitchY  = (dY[2] - dY[1]) / 9.0;
	double dOffSetX = (dX[2] - dX[1]) / 9.0;
	double dOffSetY = (dY[1] - dY[0]) / 3.0;

	//X = X0 + PiatchX * PosX(0~3) + OffsetX * PosY;
	//Y = Y0 + PiatchY * PosY(0~9) + OffsetY * PosX;
	dToPosX = dX[0] + dPitchX * (double)(nPosX-1) + dOffSetX * (double)(nPosY-1);
	dToPosY = dY[0] + dPitchY * (double)(nPosY-1) + dOffSetY * (double)(nPosX-1);

	m_sLog.Format("A2 Data [Picker:%d Job:%d Option:%d] PosXY(%d,%d) => (%0.3lf,%0.3lf) (%0.3lf,%0.3lf,%0.3lf,%0.3lf,%0.3lf,%0.3lf)", nPNo, nJobNo, m_pEquipData->bUseAlign2, nPosX, nPosY, dToPosX, dToPosY,
													dX[0], dX[1], dX[2], dY[0], dY[1], dY[2]);
	g_objLogFile.Save_HandlerLog(m_sLog);

	return TRUE;
}

/*
BOOL CSequenceMain::Get_TrayPosition(int nPNo, int nJobNo, int nPosX, int nPosY, double &dToPosX, double &dToPosY)
{
	int	   nI = nJobNo - 1;
	double dX[3], dY[3];
	if (nPNo < 1 || nPNo > 2 || nJobNo < 1 || nJobNo > 4) return FALSE;

	m_pEquipData = g_objDataManager.Get_pEquipData();
	m_pMoveData  = g_objDataManager.Get_pMoveData();

	//(0,0) (3,0) (3,9) 점 좌표계산
	if (nPNo == 1) {		//Unload Picker1
		if (nJobNo == 1) {	//NG1
			dX[0] = m_pMoveData->dUnloadPickerX1[5];									//(0,0)
			dY[0] = m_pMoveData->dNGStageY1[3];											//(0,0)
			dX[1] = m_pMoveData->dUnloadPickerX1[5] - (m_pEquipData->dTrayPitchX * 3);	//(3,0)
			dY[1] = m_pMoveData->dNGStageY1[3];											//(3,0)
			dX[2] = m_pMoveData->dUnloadPickerX1[5] - (m_pEquipData->dTrayPitchX * 3);	//(3,9)
			dY[2] = m_pMoveData->dNGStageY1[3]      + (m_pEquipData->dTrayPitchY * 9);	//(3,9)
		}
		if (nJobNo == 2) {	//NG2
			dX[0] = m_pMoveData->dUnloadPickerX1[6];									//(0,0)
			dY[0] = m_pMoveData->dNGStageY2[3];											//(0,0)
			dX[1] = m_pMoveData->dUnloadPickerX1[6] - (m_pEquipData->dTrayPitchX * 3);	//(3,0)
			dY[1] = m_pMoveData->dNGStageY2[3];											//(3,0)
			dX[2] = m_pMoveData->dUnloadPickerX1[6] - (m_pEquipData->dTrayPitchX * 3);	//(3,9)
			dY[2] = m_pMoveData->dNGStageY2[3]      + (m_pEquipData->dTrayPitchY * 9);	//(3,9)
		}
		if (nJobNo == 3) {	//Good1
			dX[0] = m_pMoveData->dUnloadPickerX1[7];									//(0,0)
			dY[0] = m_pMoveData->dGoodStageY1[3];										//(0,0)
			dX[1] = m_pMoveData->dUnloadPickerX1[7] - (m_pEquipData->dTrayPitchX * 3);	//(3,0)
			dY[1] = m_pMoveData->dGoodStageY1[3];										//(3,0)
			dX[2] = m_pMoveData->dUnloadPickerX1[7] - (m_pEquipData->dTrayPitchX * 3);	//(3,9)
			dY[2] = m_pMoveData->dGoodStageY1[3]    + (m_pEquipData->dTrayPitchY * 9);	//(3,9)
		}
		if (nJobNo == 4) {	//Good2
			dX[0] = m_pMoveData->dUnloadPickerX1[8];									//(0,0)
			dY[0] = m_pMoveData->dGoodStageY2[3];										//(0,0)
			dX[1] = m_pMoveData->dUnloadPickerX1[8] - (m_pEquipData->dTrayPitchX * 3);	//(3,0)
			dY[1] = m_pMoveData->dGoodStageY2[3];										//(3,0)
			dX[2] = m_pMoveData->dUnloadPickerX1[8] - (m_pEquipData->dTrayPitchX * 3);	//(3,9)
			dY[2] = m_pMoveData->dGoodStageY2[3]    + (m_pEquipData->dTrayPitchY * 9);	//(3,9)
		}
	}
	if (nPNo == 2) {		//Unload Picker2
		if (nJobNo == 1) {	//NG1
			dX[0] = m_pMoveData->dUnloadPickerX2[5];									//(0,0)
			dY[0] = m_pMoveData->dNGStageY1[3];											//(0,0)
			dX[1] = m_pMoveData->dUnloadPickerX2[5] - (m_pEquipData->dTrayPitchX * 3);	//(3,0)
			dY[1] = m_pMoveData->dNGStageY1[3];											//(3,0)
			dX[2] = m_pMoveData->dUnloadPickerX2[5] - (m_pEquipData->dTrayPitchX * 3);	//(3,9)
			dY[2] = m_pMoveData->dNGStageY1[3]      + (m_pEquipData->dTrayPitchY * 9);	//(3,9)
		}
		if (nJobNo == 2) {	//NG2
			dX[0] = m_pMoveData->dUnloadPickerX2[6];									//(0,0)
			dY[0] = m_pMoveData->dNGStageY2[3];											//(0,0)
			dX[1] = m_pMoveData->dUnloadPickerX2[6] - (m_pEquipData->dTrayPitchX * 3);	//(3,0)
			dY[1] = m_pMoveData->dNGStageY2[3];											//(3,0)
			dX[2] = m_pMoveData->dUnloadPickerX2[6] - (m_pEquipData->dTrayPitchX * 3);	//(3,9)
			dY[2] = m_pMoveData->dNGStageY2[3]      + (m_pEquipData->dTrayPitchY * 9);	//(3,9)
		}
		if (nJobNo == 3) {	//Good1
			dX[0] = m_pMoveData->dUnloadPickerX2[7];									//(0,0)
			dY[0] = m_pMoveData->dGoodStageY1[3];										//(0,0)
			dX[1] = m_pMoveData->dUnloadPickerX2[7] - (m_pEquipData->dTrayPitchX * 3);	//(3,0)
			dY[1] = m_pMoveData->dGoodStageY1[3];										//(3,0)
			dX[2] = m_pMoveData->dUnloadPickerX2[7] - (m_pEquipData->dTrayPitchX * 3);	//(3,9)
			dY[2] = m_pMoveData->dGoodStageY1[3]    + (m_pEquipData->dTrayPitchY * 9);	//(3,9)
		}
		if (nJobNo == 4) {	//Good2
			dX[0] = m_pMoveData->dUnloadPickerX2[8];									//(0,0)
			dY[0] = m_pMoveData->dGoodStageY2[3];										//(0,0)
			dX[1] = m_pMoveData->dUnloadPickerX2[8] - (m_pEquipData->dTrayPitchX * 3);	//(3,0)
			dY[1] = m_pMoveData->dGoodStageY2[3];										//(3,0)
			dX[2] = m_pMoveData->dUnloadPickerX2[8] - (m_pEquipData->dTrayPitchX * 3);	//(3,9)
			dY[2] = m_pMoveData->dGoodStageY2[3]    + (m_pEquipData->dTrayPitchY * 9);	//(3,9)
		}
	}

	//(0,0) (3,0) (3,9) 위치에 Vision Align 편차 계산
	if (m_pEquipData->bUseAlign2) {
		dX[0] = dX[0] + gData.dAlignVisionX[nI][0];
		dY[0] = dY[0] + gData.dAlignVisionY[nI][0];
		dX[1] = dX[1] + gData.dAlignVisionX[nI][1];
		dY[1] = dY[1] + gData.dAlignVisionY[nI][1];
		dX[2] = dX[2] + gData.dAlignVisionX[nI][2];
		dY[2] = dY[2] + gData.dAlignVisionY[nI][2];
	}

	//Pitch, Offset 계산
	double dPitchX  = (dX[1] - dX[0]) / 3.0;
	double dPitchY  = (dY[2] - dY[1]) / 9.0;
	double dOffSetX = (dX[2] - dX[1]) / 9.0;
	double dOffSetY = (dY[1] - dY[0]) / 3.0;

	//X = X0 + PiatchX * PosX(0~4) + OffsetX * PosY;
	//Y = Y0 + PiatchY * PosY(0~9) + OffsetY * PosX;
	dToPosX = dX[0] + dPitchX * (double)nPosX + dOffSetX * (double)nPosY;
	dToPosY = dY[0] + dPitchY * (double)nPosY + dOffSetY * (double)nPosX;

	m_sLog.Format("A2 Data [Picker:%d Job:%d Option:%d] PosXY(%d,%d) => (%0.3lf,%0.3lf)", nPNo, nJobNo, m_pEquipData->bUseAlign2, nPosX, nPosY, dToPosX, dToPosY);
	g_objLogFile.Save_HandlerLog(m_sLog);
	return TRUE;
}
*/
int CSequenceMain::Check_NGExist(int nPNo, int &nJNo)
{
	nJNo = 0;
	for(int i=0; i<8; i++) {
		if (gData.InfoUnloadPick[nPNo-1][i] > 2) {
			nJNo = gData.InfoUnloadPick[nPNo-1][i];
			return (i+1);
		}
	}
	return 0;
}

BOOL CSequenceMain::Select_NGTrayPoketNo(int nType, int &nPosX, int &nPosY)
{
/*
	nPosX = nPosY = 0;
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoNgTray[i][j] == 0) {
				nPosY = i + 1;	//10
				nPosX = j + 1;	//4
				return TRUE;
			}
		}
	}
*/
	//Type => 3:NG, 4:ROS재검, 5:Barcode,MES, 6:치수불량123, 7:치수불량1, 8:치수불량2, 9:치수불량3
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoNgTray[i][j] == 0) {
				if (m_pEquipData->bUseCosmeticNG || !m_pEquipData->bUseNGSort || gData.bUseBarSort ||
					m_pEquipData->nTrayBase[i][j] == nType) {
					nPosY = i + 1;	//10
					nPosX = j + 1;	//4
					return TRUE;
				}
				if (!m_pEquipData->bUseCosmeticNG && m_pEquipData->bUseNGSort && m_pEquipData->nTrayBase[i][j] == 6) {
					if (nType == 7 || nType == 8 || nType == 9) {
						nPosY = i + 1;	//10
						nPosX = j + 1;	//4
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

int CSequenceMain::Check_GoodExist(int nPNo, int &nPosX, int &nPosY)
{
	for(int i=0; i<8; i++) {
		if (gData.InfoUnloadPick[nPNo-1][i] >= 2) {
			int nNo = gData.InfoUnloadPick[nPNo-1][9] + i;
			nPosX = nNo % TRAY_CM_X;	if (nPosX==0) nPosX = 4;
			nPosY = nNo / TRAY_CM_X;	if (nPosX!=4) nPosY++;
			return (i+1);
		}
	}
	return 0;
}

BOOL CSequenceMain::Select_GoodTrayPoketNo(int nPNo, int nTNo, int &nPosX, int &nPosY)
{
	if (m_pEquipData->bUseGoodSort && !gData.bUseBarSort) {
		if (Check_EmptyGoodTray() || nTNo+1 == gLot.nOutTrayCnt[nPNo][0]) {
			if (gData.InfoGoodTray[nPosY-1][nPosX-1] == 0) return TRUE;
		}
	} else {
		nPosX = nPosY = 0;
		for(int i=0; i<10; i++) {
			for(int j=0; j<4; j++) {
				if (gData.InfoGoodTray[i][j] == 0) {
					nPosY = i + 1;	//10
					nPosX = j + 1;	//4
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CSequenceMain::Check_NGTrayFull()
{
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoNgTray[i][j] == 0) return FALSE; 
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_GooodTrayFull()
{
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (gData.InfoGoodTray[i][j] == 0) return FALSE; 
		}
	}
	return TRUE;
}

BOOL CSequenceMain::Check_EemptyLoadPicker(int nPNo)
{
	if (nPNo < 1 || nPNo > 2) return FALSE;
	for(int i=0; i<8; i++) {
		if (gData.InfoLoadPick[nPNo-1][i] > 0) return FALSE;
	}
	return TRUE;
}

BOOL CSequenceMain::Check_EemptyVisionStage(int nVNo)
{
	if (nVNo < 1 || nVNo > 4) return FALSE;
	for(int i=0; i<8; i++) {
		if (gData.InfoVision[nVNo-1][i] > 0) return FALSE;
	}
	return TRUE;
}

BOOL CSequenceMain::Check_ElevatorSearch(int nENo)
{
	if (gData.dElevatorZPos[0][nENo-1] <= 1.0) return TRUE;
	if (nENo == 1 && !m_pDX00->iElevator1TrayExist) return TRUE;
	if (nENo == 2 && !m_pDX00->iElevator2TrayExist) return TRUE;
	if (nENo == 3 && !m_pDX01->iElevator3TrayExist) return TRUE;
	if (nENo == 4 && !m_pDX01->iElevator4TrayExist) return TRUE;
	if (nENo == 5 && !m_pDX02->iElevator5TrayExist) return TRUE;
	if (nENo == 6 && !m_pDX02->iElevator6TrayExist) return TRUE;
	if (nENo == 7 && !m_pDX02->iElevator7TrayExist) return TRUE;

	if (fabs(gData.dElevatorZPos[1][nENo-1] - gData.dElevatorZPos[0][nENo-1]) > (TRAY_PITCH*2.0)) return TRUE;
//	if (fabs(gData.dElevatorZPos[1][nENo-1] - gData.dElevatorZPos[0][nENo-1]) > (TRAY_PITCH+2.0)) return FALSE;
	if (fabs(gData.dElevatorZPos[1][nENo-1] - gData.dElevatorZPos[0][nENo-1]) > (TRAY_PITCH+3.0)) return FALSE;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BOOL CSequenceMain::Set_LotStart(CString sLotID, int nPortNo)
{
	if (nPortNo < 1 || nPortNo > 6) return TRUE;
	for(int i=1; i<=7; i++) {
		if (!g_objCommon.Check_SlideLock(i)) {
			g_objCommon.Show_Error(2081+(100*i));
			return FALSE;
		}
	}

	int nNo = nPortNo - 1;
	SYSTEMTIME time;
	GetLocalTime(&time);

	gLot.sLLStartTime[nNo].Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	gLot.sMESStartTime[nNo].Format("%04d/%02d/%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	gLot.sLLSHHMMSS[nNo].Format("%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
	gLot.dwLLLotStart[nNo] = GetTickCount();

	gLot.sLLEndTime[nNo] = gLot.sMESEndTime[nNo] = "";
	gLot.nErrorCount[nNo] = gLot.dwErrorTime[nNo] = gLot.dwStopTime[nNo] = gLot.dwLLLotEnd[nNo] = 0;
	gLot.dLLTackTime[nNo] = 0.0;
	gLot.nRunPortNo = nPortNo;

	g_objDispatcher.Set_LotStart(nPortNo);
	gData.sLotID_Start = gLot.sLotID[nNo];
	g_objMesAgent.Set_LotStart(1, nNo, gLot.sLotID[nNo], gLot.sRecipeName[nNo], gLot.nCmCount[nNo]);

	// Log 표준화
	gData.nStdLotNo++;
	gData.nTotLotNo[nNo] = gData.nStdLotNo;
	CIniFileCS INI_EQP(gsCurrentDir + "\\System\\EquipData.ini");
	INI_EQP.Set_Integer("STD_LOG", "STD_LOT_NO", gData.nStdLotNo);

	g_objLogFile.Save_EfficiencyLog(gLot.sLotID[nNo], "Start", "Elevator", 903, "Lot Start");
	return TRUE;
}

//nGTray 1:GoodTray1, 2:GoodTray2
void CSequenceMain::Set_LotEnd(CString sLotID, int nPortNo)
{
	if (nPortNo < 1 || nPortNo > 6) return;

	int nNo = nPortNo - 1;
	gLot.sRstLotID[nNo]     = gLot.sLotID[nNo];
	gLot.nRstCmCount[nNo]   = gLot.nCmCount[nNo];
	gLot.nRstGoodCount[nNo] = gLot.nGoodCount[nNo];
	gLot.nRstNgCount[nNo]   = gLot.nNgCount[nNo] + gLot.nSkipCount[nNo];
	gLot.nLotStatus[nNo] = 3;
	gData.nRejectLotCount   = gLot.nNgCount[nNo] + gLot.nSkipCount[nNo];

	SYSTEMTIME time;
	GetLocalTime(&time);

	gLot.dwLLLotEnd[nNo] = GetTickCount();
	gLot.sLLEndTime[nNo].Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	gLot.sMESEndTime[nNo].Format("%04d/%02d/%02d %02d:%02d:%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	gLot.sLLEHHMMSS[nNo].Format("%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);

	DWORD dwTime = gLot.dwLLLotEnd[nNo] - gLot.dwLLLotStart[nNo];
	gLot.dLLTackTime[nNo] = dwTime / 1000.0 / gLot.nRstCmCount[nNo];
	Set_NextLot(gLot.sLotID[nNo], gLot.dwLLLotEnd[nNo]);

	CString sLog;
	double dRate = (gLot.nCmCount[nNo] == 0 ? 0.0 : (gLot.nGoodCount[nNo] * 100.0) / gLot.nCmCount[nNo]);

	//"Time,PortNo,LotID,Count,NG_Count,Good_Count,Rate,Skip_Count,Bar_NoRead,RosJudge,RosGood,RosNG,RosRepair,RosTimeOver,Start_Time,End_Time,Tack\r\n");
	sLog.Format("%d,%s,%d,%d,%d,%0.1lf,%d,%d,%d,%d,%d,%d,%d,%s,%s,%0.5lf,%d",
				nPortNo, gLot.sLotID[nNo], gLot.nCmCount[nNo], gLot.nNgCount[nNo], gLot.nGoodCount[nNo], dRate, gLot.nRosJugCount[nNo][10], //gLot.nSkipCount[nNo],
				gLot.nRosJugCount[nNo][5], gLot.nRosJugCount[nNo][0], gLot.nRosJugCount[nNo][1], gLot.nRosJugCount[nNo][3], gLot.nRosJugCount[nNo][4], gLot.nRosJugCount[nNo][2],
				gLot.sLLStartTime[nNo], gLot.sLLEndTime[nNo], gLot.dLLTackTime[nNo], gLot.nRosJugCount[nNo][6]);
	g_objLogFile.Save_JobListLog(sLog);

	sLog.Format("%d,%s,%d,%d,%d,%0.1lf,%d,%d,%d,%d,%d,%d,%d,%s,%s,%0.5lf,%d,%d,%d",
				nPortNo, gLot.sLotID[nNo], gLot.nCmCount[nNo], gLot.nNgCount[nNo], gLot.nGoodCount[nNo], dRate, gLot.nRosJugCount[nNo][10], //gLot.nSkipCount[nNo],
				gLot.nRosJugCount[nNo][5], gLot.nRosJugCount[nNo][0], gLot.nRosJugCount[nNo][1], gLot.nRosJugCount[nNo][3], gLot.nRosJugCount[nNo][4], gLot.nRosJugCount[nNo][2],
				gLot.sLLStartTime[nNo], gLot.sLLEndTime[nNo], gLot.dLLTackTime[nNo], gLot.nRosJugCount[nNo][6], gLot.nRosJugCount[nNo][11], gLot.nRosJugCount[nNo][12]);
	g_objLogFile.Save_HandlerLog(sLog);

	gLot.sELotID = gLot.sLotID[nNo];
	sLog.Format("%d,%d,%d,%d,%0.1lf,%d,%d,%d,%d,%d,%d,%d,%s,%s,%0.5lf,%d",
				nPortNo, gLot.nCmCount[nNo], gLot.nNgCount[nNo], gLot.nGoodCount[nNo], dRate, gLot.nRosJugCount[nNo][10], //gLot.nSkipCount[nNo],
				gLot.nRosJugCount[nNo][5], gLot.nRosJugCount[nNo][0], gLot.nRosJugCount[nNo][1], gLot.nRosJugCount[nNo][3], gLot.nRosJugCount[nNo][4], gLot.nRosJugCount[nNo][2],
				gLot.sLLStartTime[nNo], gLot.sLLEndTime[nNo], gLot.dLLTackTime[nNo], gLot.nRosJugCount[nNo][6]);
	g_objLogFile.Save_ECMLog(0, sLog);

	//Time \tLot_ID \tTotal \tGood \tNG \tRate \tSkip \tBar_NoRead \tRosRequest \tRosGood \tRosNg \tRosRepair \tRosTimeOut \tFiltering1 \tFiltering2 \tRateAvi \tRunTime \tTack\r\n");
	double dFiltering1 = (gLot.nRosJugCount[nNo][0] == 0 ? 0.0 : (gLot.nRosJugCount[nNo][1] * 100.0) / gLot.nRosJugCount[nNo][0]);
	double dFiltering2 = (gLot.nCmCount[nNo] == 0 ? 0.0 : (gLot.nRosJugCount[nNo][1] * 100.0) / gLot.nCmCount[nNo]);
	double dRateAvi = (gLot.nCmCount[nNo] == 0 ? 0.0 : ((gLot.nGoodCount[nNo] - gLot.nRosJugCount[nNo][1]) * 100.0) / gLot.nCmCount[nNo]);
	double dRunTime = dwTime / 1000.0;

	sLog.Format("\t%s \t%d \t%d \t%d \t%0.3lf \t%d \t%d \t%d \t%d \t%d \t%d \t%d \t%0.2lf \t%0.2lf \t%0.3lf \t%0.3lf \t%0.3lf",
		gLot.sLotID[nNo], gLot.nCmCount[nNo], gLot.nGoodCount[nNo], gLot.nNgCount[nNo], dRate,  gLot.nRosJugCount[nNo][10], gLot.nRosJugCount[nNo][5],
		gLot.nRosJugCount[nNo][0], gLot.nRosJugCount[nNo][1], gLot.nRosJugCount[nNo][3], gLot.nRosJugCount[nNo][4], gLot.nRosJugCount[nNo][2],
		dFiltering1, dFiltering2, dRateAvi, dRunTime, gLot.dLLTackTime[nNo]);
	g_objLogFile.Save_DailyLot(sLog);
	g_objLogFile.Save_LotLog(nNo+1);

	sLog.Format("%s,%d,%d,%d,%0.3lf,%d,%d,%d,%d,%d,%d,%d,%0.2lf,%0.2lf,%0.3lf,%0.3lf,%0.3lf",
		gLot.sLotID[nNo], gLot.nCmCount[nNo], gLot.nGoodCount[nNo], gLot.nNgCount[nNo], dRate,  gLot.nRosJugCount[nNo][10], gLot.nRosJugCount[nNo][5],
		gLot.nRosJugCount[nNo][0], gLot.nRosJugCount[nNo][1], gLot.nRosJugCount[nNo][3], gLot.nRosJugCount[nNo][4], gLot.nRosJugCount[nNo][2],
		dFiltering1, dFiltering2, dRateAvi, dRunTime, gLot.dLLTackTime[nNo]);
	g_objLogFile.Save_ECMDailyLot(sLog);

	//Time,호기,Lot ID,Lot Start,Lot End,Cycle Time,LM(EA),Run Time,Stop Time,Error Time,Error Count,수율,UPH,MTB\r\n");
	sLog.Format(",%s,%s,%s,%s,%0.3lf,%d,%0.3lf,%0.3lf,%0.3lf,%d,%0.2lf,%0.3lf,%0.3lf",
		m_pEquipData->sEquipName, gLot.sLotID[nNo], gLot.sLLSHHMMSS[nNo], gLot.sLLEHHMMSS[nNo], gLot.dLLTackTime[nNo], gLot.nCmCount[nNo], dRunTime,
		(double)(gLot.dwStopTime[nNo]) / 1000, (double)(gLot.dwErrorTime[nNo]) / 1000, gLot.nErrorCount[nNo], dRate, 3600 / gLot.dLLTackTime[nNo],
		(double)(dRunTime / 1000 / (gLot.nErrorCount[nNo] + 1)));
	g_objLogFile.Save_OperatingRatio(sLog);

//	g_objMesAgent.Set_LotEnd(nNo, gLot.sLotID[nNo], gMes.sHostRecipe[nNo], gMes.nHostCmCount[nNo], gLot.nGoodCount[nNo], gLot.nNgCount[nNo]+gLot.nSkipCount[nNo]);
//	g_objInspector.Set_LotEnd(INSPECTOR_ALL, gLot.sLotID[nNo], nPortNo);
	g_objDispatcher.Set_LotEnd(nPortNo);

	gData.nDay_TotalCnt += gLot.nCmCount[nNo];
	gData.nDay_NGCnt += gLot.nNgCount[nNo];
	gData.nDay_GoodCnt += gLot.nGoodCount[nNo];

	CIniFileCS INI_EQP(gsCurrentDir + "\\System\\EquipData.ini");
	if (INI_EQP.Check_File()) {
		INI_EQP.Set_Integer("DAY_TOTAL", "COUNT", gData.nDay_TotalCnt);
		INI_EQP.Set_Integer("DAY_TOTAL", "NG_COUNT", gData.nDay_NGCnt);
		INI_EQP.Set_Integer("DAY_TOTAL", "GOOD_COUNT", gData.nDay_GoodCnt);
	}
	g_objLogFile.Save_EfficiencyLog(gLot.sLotID[nNo], "Stop", "Elevator", 903, "Lot End");

	gLot.nJobPortNo[gLot.nJobNo]	= nPortNo;
	gLot.sJobLotID[gLot.nJobNo]		= gLot.sLotID[nNo];
	gLot.nJobCmCount[gLot.nJobNo]	= gLot.nCmCount[nNo];
	gLot.nJobGoodCount[gLot.nJobNo]	= gLot.nGoodCount[nNo];
	gLot.nJobNgCount[gLot.nJobNo]	= gLot.nNgCount[nNo] + gLot.nSkipCount[nNo];
	gLot.dJobRate[gLot.nJobNo]		= dRate;
	gLot.sJobStartTime[gLot.nJobNo] = gLot.sLLStartTime[nNo];
	gLot.sJobEndTime[gLot.nJobNo]	= gLot.sLLEndTime[nNo];
	gLot.dJobTack[gLot.nJobNo]		= gLot.dLLTackTime[nNo];
	gLot.nJobNo++; if (gLot.nJobNo >= 10) gLot.nJobNo = 0;

	if (gData.nRejectMaxCount > 0 && gData.nRejectLotCount >= gData.nRejectMaxCount)
			g_dlgWork.PostMessage(UM_LOT_END_MSG, nPortNo, 9);
//	else if (gLot.nCmCount[nNo] != gLot.nRstNgCount[nNo] + gLot.nRstGoodCount[nNo])
//			g_dlgWork.PostMessage(UM_LOT_END_MSG, nPortNo, 2);	//입력수량과 검사수량이 안맞았을때 알람메세지 보여준다.
	else	g_dlgWork.PostMessage(UM_LOT_END_MSG, nPortNo, 0);

	g_dlgWork.PostMessage(UM_UPDATE_UPH, NULL, NULL);
}

void CSequenceMain::Beep_Post(int nTime)
{
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oBuzzerBit0 = m_pEquipData->bBuzzer[1][0];
	pDY13->oBuzzerBit1 = m_pEquipData->bBuzzer[1][1];
	pDY13->oBuzzerBit2 = m_pEquipData->bBuzzer[1][2];
	pDY13->oBuzzerBit3 = m_pEquipData->bBuzzer[1][3];
	pDY13->oBuzzerBit4 = m_pEquipData->bBuzzer[1][4];
	g_objAJinAXL.Write_Output(13);

 	Sleep(nTime);

	pDY13->oBuzzerBit0 = FALSE;
	pDY13->oBuzzerBit1 = FALSE;
	pDY13->oBuzzerBit2 = FALSE;
	pDY13->oBuzzerBit3 = FALSE;
	pDY13->oBuzzerBit4 = FALSE;
 	g_objAJinAXL.Write_Output(13);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  1. (Error : 2100)
BOOL CSequenceMain::Run_Elevator1()
{
	static int	  nElevZAxisNo = AX_ELEVATOR_Z1;
	static double dElev1PrePos, dElev1PostPos, dElelavtorZ1, dElev1Positi;

	dElev1PrePos  = m_pMoveData->dElevatorZ1[1];
	dElev1PostPos = m_pMoveData->dElevatorZ1[2];
	if (gData.nElevatorOpen[1] > 0) return TRUE;
	if (m_nElevator1Case < 50 && !m_pDX00->iElevator1SlideClose) return TRUE;

	switch (m_nElevator1Case) {
	case 0:	// Wait
		m_tElevator1Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (!m_pDX00->iElevator1TrayExist) {
			m_nElevator1Case = 30; m_tElevator1Loop.Set_LoopTime(5000);
		} else {
			m_tElevator1Loop.Takt_Start(1, 1, TRUE);
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator1Case = 8; m_tElevator1Loop.Set_LoopTime(5000);
			} else {
				m_nElevator1Case = 10; m_tElevator1Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 8:
			m_pDY00->oElevator1Clamp1On = FALSE; m_pDY00->oElevator1Clamp1Off = TRUE;
			m_pDY00->oElevator1Clamp2On = FALSE; m_pDY00->oElevator1Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(0);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(5000);
		break;
	case 9:
		if (!m_pDX00->iElevator1Clamp1On && m_pDX00->iElevator1Clamp1Off && !m_pDX00->iElevator1Clamp2On && m_pDX00->iElevator1Clamp2Off) {
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(5000);
		}
		break;
	case 10:
		if (m_pDX00->iElevator1Height1 || m_pDX00->iElevator1Height2) {
			m_tElevator1Loop.Takt_Save(1, 1); m_tElevator1Loop.Takt_Start(1, 2);
			m_nElevator1Case = 12; m_tElevator1Loop.Set_LoopTime(5000);
		} else {
			dElev1Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_UD;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_UD);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev1Positi);
			m_nElevator1Case = 10; m_tElevator1Loop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if (m_pDX00->iElevator1Height1 || m_pDX00->iElevator1Height2) {
			dElev1Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_DN*-1.0;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_DN*-1.0);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(30000);
		} else {
			m_tElevator1Loop.Takt_Save(1, 2); m_tElevator1Loop.Takt_Start(1, 3);
			m_nElevator1Case = 14; m_tElevator1Loop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev1Positi);
			m_nElevator1Case = 12; m_tElevator1Loop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if (m_pDX00->iElevator1Height1 && m_pDX00->iElevator1Height2) {
			m_tElevator1Loop.Takt_Save(1, 3); m_tElevator1Loop.Takt_Start(1, 4);
			m_nElevator1Case = 16; m_tElevator1Loop.Set_LoopTime(30000);
		} else {
			dElev1Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_SL;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_SL);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev1Positi);
			m_nElevator1Case = 14; m_tElevator1Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			dElev1Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + dElev1PostPos;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, dElev1PostPos);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev1Positi);
			m_tElevator1Loop.Takt_Save(1, 4, TRUE);
			gData.dElevatorZPos[1][0] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(3000);
		}
		break;
	case 18:
		if (Check_ElevatorSearch(1)) {
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator1Case = 40; m_tElevator1Loop.Set_LoopTime(30000);
			} else {
				m_nElevator1Case = 20; m_tElevator1Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 20:	// Picker Wait
		m_tElevator1Loop.Set_LoopTime(30000);
		return TRUE;

	case 21:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][0] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			if (!m_pDX00->iElevator1TrayExist) gData.dElevatorZPos[0][0] = 0.0;
			m_nElevator1Case = 1; m_tElevator1Loop.Set_LoopTime(30000);
		}
		break;

	case 30:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Move_Position(nElevZAxisNo, 0);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(30000);
		}
		break;
	case 31:
		if (g_objCommon.Check_Position(nElevZAxisNo, 0)) {
			g_objCommon.Save_Motion(nElevZAxisNo, 0);
			m_nElevator1Case = 20; m_tElevator1Loop.Set_LoopTime(5000);
		}
		break;

	case 40:
			m_pDY00->oElevator1Clamp1On = TRUE; m_pDY00->oElevator1Clamp1Off = FALSE;
			m_pDY00->oElevator1Clamp2On = TRUE; m_pDY00->oElevator1Clamp2Off = FALSE;
			g_objAJinAXL.Write_Output(0);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(5000);
		break;
	case 41:
		if (m_pDX00->iElevator1Clamp1On && !m_pDX00->iElevator1Clamp1Off && m_pDX00->iElevator1Clamp2On && !m_pDX00->iElevator1Clamp2Off) {
			if (!m_tElevator1Loop.Waiting_Time(500)) break;
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(5000);
		}
		break;
	case 42:
			m_pDY00->oElevator1Clamp1On = FALSE; m_pDY00->oElevator1Clamp1Off = TRUE;
			m_pDY00->oElevator1Clamp2On = FALSE; m_pDY00->oElevator1Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(0);
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(5000);
		break;
	case 43:
		if (!m_pDX00->iElevator1Clamp1On && m_pDX00->iElevator1Clamp1Off && !m_pDX00->iElevator1Clamp2On && m_pDX00->iElevator1Clamp2Off) {
			m_nElevator1Case = 20; m_tElevator1Loop.Set_LoopTime(5000);
		}
		break;

	case 51:
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(5000);
		break;
	case 52:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][0] = 0.0;
			m_nElevator1Case++; m_tElevator1Loop.Set_LoopTime(3000);
		}
		break;
	case 53:
		if (m_pDX00->iElevator1SlideClose) {
			m_nElevator1Case = 1; m_tElevator1Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 1. (Error : 2100)
	if (m_tElevator1Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(2100 + m_nElevator1Case);
		return FALSE;
	}
	return TRUE;
}

//  2. (Error : 2200)
BOOL CSequenceMain::Run_Elevator2()
{
	static int	  nElevZAxisNo = AX_ELEVATOR_Z2;
	static double dElev2PrePos, dElev2PostPos, dElelavtorZ2, dElev2Positi;

	dElev2PrePos  = m_pMoveData->dElevatorZ2[1];
	dElev2PostPos = m_pMoveData->dElevatorZ2[2];
	if (gData.nElevatorOpen[2] > 0) return TRUE;
	if (m_nElevator2Case < 50 && !m_pDX00->iElevator2SlideClose) return TRUE;

	switch (m_nElevator2Case) {
	case 0:	// Wait
		m_tElevator2Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (!m_pDX00->iElevator2TrayExist) {
			m_nElevator2Case = 30; m_tElevator2Loop.Set_LoopTime(5000);
		} else {
			m_tElevator2Loop.Takt_Start(2, 1, TRUE);
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator2Case = 8; m_tElevator2Loop.Set_LoopTime(5000);
			} else {
				m_nElevator2Case = 10; m_tElevator2Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 8:
			m_pDY00->oElevator2Clamp1On = FALSE; m_pDY00->oElevator2Clamp1Off = TRUE;
			m_pDY00->oElevator2Clamp2On = FALSE; m_pDY00->oElevator2Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(0);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(5000);
		break;
	case 9:
		if (!m_pDX00->iElevator2Clamp1On && m_pDX00->iElevator2Clamp1Off && !m_pDX00->iElevator2Clamp2On && m_pDX00->iElevator2Clamp2Off) {
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(5000);
		}
		break;
	case 10:
		if (m_pDX00->iElevator2Height1 || m_pDX00->iElevator2Height2) {
			m_tElevator2Loop.Takt_Save(2, 1); m_tElevator2Loop.Takt_Start(2, 2);
			m_nElevator2Case = 12; m_tElevator2Loop.Set_LoopTime(5000);
		} else {
			dElev2Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_UD;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_UD);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev2Positi);
			m_nElevator2Case = 10; m_tElevator2Loop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if (m_pDX00->iElevator2Height1 || m_pDX00->iElevator2Height2) {
			dElev2Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_DN*-1.0;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_DN*-1.0);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(30000);
		} else {
			m_tElevator2Loop.Takt_Save(2, 2); m_tElevator2Loop.Takt_Start(2, 3);
			m_nElevator2Case = 14; m_tElevator2Loop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev2Positi);
			m_nElevator2Case = 12; m_tElevator2Loop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if (m_pDX00->iElevator2Height1 && m_pDX00->iElevator2Height2) {
			m_tElevator2Loop.Takt_Save(2, 3); m_tElevator2Loop.Takt_Start(2, 4);
			m_nElevator2Case = 16; m_tElevator2Loop.Set_LoopTime(30000);
		} else {
			dElev2Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_SL;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_SL);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev2Positi);
			m_nElevator2Case = 14; m_tElevator2Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			dElev2Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + dElev2PostPos;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, dElev2PostPos);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev2Positi);
			m_tElevator2Loop.Takt_Save(2, 4, TRUE);
			gData.dElevatorZPos[1][1] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(3000);
		}
		break;
	case 18:
		if (Check_ElevatorSearch(2)) {
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator2Case = 40; m_tElevator2Loop.Set_LoopTime(30000);
			} else {
				m_nElevator2Case = 20; m_tElevator2Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 20:	// Picker Wait
		m_tElevator2Loop.Set_LoopTime(30000);
		return TRUE;

	case 21:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][1] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			if (!m_pDX00->iElevator2TrayExist) gData.dElevatorZPos[0][1] = 0.0;
			m_nElevator2Case = 1; m_tElevator2Loop.Set_LoopTime(30000);
		}
		break;

	case 30:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Move_Position(nElevZAxisNo, 0);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(30000);
		}
		break;
	case 31:
		if (g_objCommon.Check_Position(nElevZAxisNo, 0)) {
			g_objCommon.Save_Motion(nElevZAxisNo, 0);
			m_nElevator2Case = 20; m_tElevator2Loop.Set_LoopTime(5000);
		}
		break;

	case 40:
			m_pDY00->oElevator2Clamp1On = TRUE; m_pDY00->oElevator2Clamp1Off = FALSE;
			m_pDY00->oElevator2Clamp2On = TRUE; m_pDY00->oElevator2Clamp2Off = FALSE;
			g_objAJinAXL.Write_Output(0);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(5000);
		break;
	case 41:
		if (m_pDX00->iElevator2Clamp1On && !m_pDX00->iElevator2Clamp1Off && m_pDX00->iElevator2Clamp2On && !m_pDX00->iElevator2Clamp2Off) {
			if (!m_tElevator2Loop.Waiting_Time(500)) break;
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(5000);
		}
		break;
	case 42:
			m_pDY00->oElevator2Clamp1On = FALSE; m_pDY00->oElevator2Clamp1Off = TRUE;
			m_pDY00->oElevator2Clamp2On = FALSE; m_pDY00->oElevator2Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(0);
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(5000);
		break;
	case 43:
		if (!m_pDX00->iElevator2Clamp1On && m_pDX00->iElevator2Clamp1Off && !m_pDX00->iElevator2Clamp2On && m_pDX00->iElevator2Clamp2Off) {
			m_nElevator2Case = 20; m_tElevator2Loop.Set_LoopTime(5000);
		}
		break;

	case 51:
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(5000);
		break;
	case 52:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][1] = 0.0;
			m_nElevator2Case++; m_tElevator2Loop.Set_LoopTime(3000);
		}
		break;
	case 53:
		if (m_pDX00->iElevator2SlideClose) {
			m_nElevator2Case = 1; m_tElevator2Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 2. (Error : 2200)
	if (m_tElevator2Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(2200 + m_nElevator2Case);
		return FALSE;
	}
	return TRUE;
}

//  3. (Error : 2300)
BOOL CSequenceMain::Run_Elevator3()
{
	static int	  nElevZAxisNo = AX_ELEVATOR_Z3;
	static double dElev3PrePos, dElev3PostPos, dElelavtorZ3, dElev3Positi;

	dElev3PrePos  = m_pMoveData->dElevatorZ3[1];
	dElev3PostPos = m_pMoveData->dElevatorZ3[2];
	if (gData.nElevatorOpen[3] > 0) return TRUE;
	if (m_nElevator3Case < 50 && !m_pDX01->iElevator3SlideClose) return TRUE;

	switch (m_nElevator3Case) {
	case 0:	// Wait
		m_tElevator3Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (!m_pDX01->iElevator3TrayExist) {
			m_nElevator3Case = 30; m_tElevator3Loop.Set_LoopTime(5000);
		} else {
			m_tElevator3Loop.Takt_Start(3, 1, TRUE);
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator3Case = 8; m_tElevator3Loop.Set_LoopTime(5000);
			} else {
				m_nElevator3Case = 10; m_tElevator3Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 8:
			m_pDY01->oElevator3Clamp1On = FALSE; m_pDY01->oElevator3Clamp1Off = TRUE;
			m_pDY01->oElevator3Clamp2On = FALSE; m_pDY01->oElevator3Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(5000);
		break;
	case 9:
		if (!m_pDX01->iElevator3Clamp1On && m_pDX01->iElevator3Clamp1Off && !m_pDX01->iElevator3Clamp2On && m_pDX01->iElevator3Clamp2Off) {
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(5000);
		}
		break;
	case 10:
		if (m_pDX01->iElevator3Height1 || m_pDX01->iElevator3Height2) {
			m_tElevator3Loop.Takt_Save(3, 1); m_tElevator3Loop.Takt_Start(3, 2);
			m_nElevator3Case = 12; m_tElevator3Loop.Set_LoopTime(5000);
		} else {
			dElev3Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_UD;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_UD);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev3Positi);
			m_nElevator3Case = 10; m_tElevator3Loop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if (m_pDX01->iElevator3Height1 || m_pDX01->iElevator3Height2) {
			dElev3Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_DN*-1.0;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_DN*-1.0);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(30000);
		} else {
			m_tElevator3Loop.Takt_Save(3, 2); m_tElevator3Loop.Takt_Start(3, 3);
			m_nElevator3Case = 14; m_tElevator3Loop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev3Positi);
			m_nElevator3Case = 12; m_tElevator3Loop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if (m_pDX01->iElevator3Height1 && m_pDX01->iElevator3Height2) {
			m_tElevator3Loop.Takt_Save(3, 3); m_tElevator3Loop.Takt_Start(3, 4);
			m_nElevator3Case = 16; m_tElevator3Loop.Set_LoopTime(30000);
		} else {
			dElev3Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_SL;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_SL);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev3Positi);
			m_nElevator3Case = 14; m_tElevator3Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			dElev3Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + dElev3PostPos;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, dElev3PostPos);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev3Positi);
			m_tElevator3Loop.Takt_Save(3, 4, TRUE);
			gData.dElevatorZPos[1][2] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(3000);
		}
		break;
	case 18:
		if (Check_ElevatorSearch(3)) {
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator3Case = 40; m_tElevator3Loop.Set_LoopTime(30000);
			} else {
				m_nElevator3Case = 20; m_tElevator3Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 20:	// Picker Wait
		m_tElevator3Loop.Set_LoopTime(30000);
		return TRUE;

	case 21:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][2] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			if (!m_pDX01->iElevator3TrayExist) gData.dElevatorZPos[0][2] = 0.0;
			m_nElevator3Case = 1; m_tElevator3Loop.Set_LoopTime(30000);
		}
		break;

	case 30:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Move_Position(nElevZAxisNo, 0);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(30000);
		}
		break;
	case 31:
		if (g_objCommon.Check_Position(nElevZAxisNo, 0)) {
			g_objCommon.Save_Motion(nElevZAxisNo, 0);
			m_nElevator3Case = 20; m_tElevator3Loop.Set_LoopTime(5000);
		}
		break;

	case 40:
			m_pDY01->oElevator3Clamp1On = TRUE; m_pDY01->oElevator3Clamp1Off = FALSE;
			m_pDY01->oElevator3Clamp2On = TRUE; m_pDY01->oElevator3Clamp2Off = FALSE;
			g_objAJinAXL.Write_Output(1);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(5000);
		break;
	case 41:
		if (m_pDX01->iElevator3Clamp1On && !m_pDX01->iElevator3Clamp1Off && m_pDX01->iElevator3Clamp2On && !m_pDX01->iElevator3Clamp2Off) {
			if (!m_tElevator3Loop.Waiting_Time(500)) break;
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(5000);
		}
		break;
	case 42:
			m_pDY01->oElevator3Clamp1On = FALSE; m_pDY01->oElevator3Clamp1Off = TRUE;
			m_pDY01->oElevator3Clamp2On = FALSE; m_pDY01->oElevator3Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(5000);
		break;
	case 43:
		if (!m_pDX01->iElevator3Clamp1On && m_pDX01->iElevator3Clamp1Off && !m_pDX01->iElevator3Clamp2On && m_pDX01->iElevator3Clamp2Off) {
			m_nElevator3Case = 20; m_tElevator3Loop.Set_LoopTime(5000);
		}
		break;

	case 51:
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(5000);
		break;
	case 52:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][2] = 0.0;
			m_nElevator3Case++; m_tElevator3Loop.Set_LoopTime(3000);
		}
		break;
	case 53:
		if (m_pDX01->iElevator3SlideClose) {
			m_nElevator3Case = 1; m_tElevator3Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 3. (Error : 2300)
	if (m_tElevator3Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(2300 + m_nElevator3Case);
		return FALSE;
	}
	return TRUE;
}

//  4. (Error : 2400)
BOOL CSequenceMain::Run_Elevator4()
{
	static int	  nElevZAxisNo = AX_ELEVATOR_Z4;
	static double dElev4PrePos, dElev4PostPos, dElelavtorZ4, dElev4Positi;

	dElev4PrePos  = m_pMoveData->dElevatorZ4[1];
	dElev4PostPos = m_pMoveData->dElevatorZ4[2];
	if (gData.nElevatorOpen[4] > 0) return TRUE;
	if (m_nElevator4Case < 50 && !m_pDX01->iElevator4SlideClose) return TRUE;

	switch (m_nElevator4Case) {
	case 0:	// Wait
		m_tElevator4Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (!m_pDX01->iElevator4TrayExist) {
			m_nElevator4Case = 30; m_tElevator4Loop.Set_LoopTime(5000);
		} else {
			m_tElevator4Loop.Takt_Start(4, 1, TRUE);
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator4Case = 8; m_tElevator4Loop.Set_LoopTime(5000);
			} else {
				m_nElevator4Case = 10; m_tElevator4Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 8:
			m_pDY01->oElevator4Clamp1On = FALSE; m_pDY01->oElevator4Clamp1Off = TRUE;
			m_pDY01->oElevator4Clamp2On = FALSE; m_pDY01->oElevator4Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(5000);
		break;
	case 9:
		if (!m_pDX01->iElevator4Clamp1On && m_pDX01->iElevator4Clamp1Off && !m_pDX01->iElevator4Clamp2On && m_pDX01->iElevator4Clamp2Off) {
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(5000);
		}
		break;
	case 10:
		if (m_pDX01->iElevator4Height1 || m_pDX01->iElevator4Height2) {
			m_tElevator4Loop.Takt_Save(4, 1); m_tElevator4Loop.Takt_Start(4, 2);
			m_nElevator4Case = 12; m_tElevator4Loop.Set_LoopTime(5000);
		} else {
			dElev4Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_UD;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_UD);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev4Positi);
			m_nElevator4Case = 10; m_tElevator4Loop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if (m_pDX01->iElevator4Height1 || m_pDX01->iElevator4Height2) {
			dElev4Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_DN*-1.0;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_DN*-1.0);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(30000);
		} else {
			m_tElevator4Loop.Takt_Save(4, 2); m_tElevator4Loop.Takt_Start(4, 3);
			m_nElevator4Case = 14; m_tElevator4Loop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev4Positi);
			m_nElevator4Case = 12; m_tElevator4Loop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if (m_pDX01->iElevator4Height1 && m_pDX01->iElevator4Height2) {
			m_tElevator4Loop.Takt_Save(4, 3); m_tElevator4Loop.Takt_Start(4, 4);
			m_nElevator4Case = 16; m_tElevator4Loop.Set_LoopTime(30000);
		} else {
			dElev4Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_SL;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_SL);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev4Positi);
			m_nElevator4Case = 14; m_tElevator4Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			dElev4Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + dElev4PostPos;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, dElev4PostPos);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev4Positi);
			m_tElevator4Loop.Takt_Save(4, 4, TRUE);
			gData.dElevatorZPos[1][3] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(3000);
		}
		break;
	case 18:
		if (Check_ElevatorSearch(4)) {
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator4Case = 40; m_tElevator4Loop.Set_LoopTime(30000);
			} else {
				m_nElevator4Case = 20; m_tElevator4Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 20:	// Picker Wait
		m_tElevator4Loop.Set_LoopTime(30000);
		return TRUE;

	case 21:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][3] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			if (!m_pDX01->iElevator4TrayExist) gData.dElevatorZPos[0][3] = 0.0;
			m_nElevator4Case = 1; m_tElevator4Loop.Set_LoopTime(30000);
		}
		break;

	case 30:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Move_Position(nElevZAxisNo, 0);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(30000);
		}
		break;
	case 31:
		if (g_objCommon.Check_Position(nElevZAxisNo, 0)) {
			g_objCommon.Save_Motion(nElevZAxisNo, 0);
			m_nElevator4Case = 20; m_tElevator4Loop.Set_LoopTime(5000);
		}
		break;

	case 40:
			m_pDY01->oElevator4Clamp1On = TRUE; m_pDY01->oElevator4Clamp1Off = FALSE;
			m_pDY01->oElevator4Clamp2On = TRUE; m_pDY01->oElevator4Clamp2Off = FALSE;
			g_objAJinAXL.Write_Output(1);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(5000);
		break;
	case 41:
		if (m_pDX01->iElevator4Clamp1On && !m_pDX01->iElevator4Clamp1Off && m_pDX01->iElevator4Clamp2On && !m_pDX01->iElevator4Clamp2Off) {
			if (!m_tElevator4Loop.Waiting_Time(500)) break;
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(5000);
		}
		break;
	case 42:
			m_pDY01->oElevator4Clamp1On = FALSE; m_pDY01->oElevator4Clamp1Off = TRUE;
			m_pDY01->oElevator4Clamp2On = FALSE; m_pDY01->oElevator4Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(1);
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(5000);
		break;
	case 43:
		if (!m_pDX01->iElevator4Clamp1On && m_pDX01->iElevator4Clamp1Off && !m_pDX01->iElevator4Clamp2On && m_pDX01->iElevator4Clamp2Off) {
			m_nElevator4Case = 20; m_tElevator4Loop.Set_LoopTime(5000);
		}
		break;

	case 51:
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(5000);
		break;
	case 52:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][3] = 0.0;
			m_nElevator4Case++; m_tElevator4Loop.Set_LoopTime(3000);
		}
		break;
	case 53:
		if (m_pDX01->iElevator4SlideClose) {
			m_nElevator4Case = 1; m_tElevator4Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 4. (Error : 2400)
	if (m_tElevator4Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(2400 + m_nElevator4Case);
		return FALSE;
	}
	return TRUE;
}

//  5. (Error : 2500)
BOOL CSequenceMain::Run_Elevator5()
{
	static int	  nElevZAxisNo = AX_ELEVATOR_Z5;
	static double dElev5PrePos, dElev5PostPos, dElelavtorZ5, dElev5Positi;

	dElev5PrePos  = m_pMoveData->dElevatorZ5[1];
	dElev5PostPos = m_pMoveData->dElevatorZ5[2];
	if (gData.nElevatorOpen[5] > 0) return TRUE;
	if (m_nElevator5Case < 50 && !m_pDX02->iElevator5SlideClose) return TRUE;

	switch (m_nElevator5Case) {
	case 0:	// Wait
		m_tElevator5Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (!m_pDX02->iElevator5TrayExist) {
			m_nElevator5Case = 30; m_tElevator5Loop.Set_LoopTime(5000);
		} else {
			m_tElevator5Loop.Takt_Start(5, 1, TRUE);
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator5Case = 8; m_tElevator5Loop.Set_LoopTime(5000);
			} else {
				m_nElevator5Case = 10; m_tElevator5Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 8:
			m_pDY02->oElevator5Clamp1On = FALSE; m_pDY02->oElevator5Clamp1Off = TRUE;
			m_pDY02->oElevator5Clamp2On = FALSE; m_pDY02->oElevator5Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(2);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(5000);
		break;
	case 9:
		if (!m_pDX02->iElevator5Clamp1On && m_pDX02->iElevator5Clamp1Off && !m_pDX02->iElevator5Clamp2On && m_pDX02->iElevator5Clamp2Off) {
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(5000);
		}
		break;
	case 10:
		if (m_pDX02->iElevator5Height1 || m_pDX02->iElevator5Height2) {
			m_tElevator5Loop.Takt_Save(5, 1); m_tElevator5Loop.Takt_Start(5, 2);
			m_nElevator5Case = 12; m_tElevator5Loop.Set_LoopTime(5000);
		} else {
			dElev5Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_UD;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_UD);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev5Positi);
			m_nElevator5Case = 10; m_tElevator5Loop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if (m_pDX02->iElevator5Height1 || m_pDX02->iElevator5Height2) {
			dElev5Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_DN*-1.0;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_DN*-1.0);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(30000);
		} else {
			m_tElevator5Loop.Takt_Save(5, 2); m_tElevator5Loop.Takt_Start(5, 3);
			m_nElevator5Case = 14; m_tElevator5Loop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev5Positi);
			m_nElevator5Case = 12; m_tElevator5Loop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if (m_pDX02->iElevator5Height1 && m_pDX02->iElevator5Height2) {
			m_tElevator5Loop.Takt_Save(5, 3); m_tElevator5Loop.Takt_Start(5, 4);
			m_nElevator5Case = 16; m_tElevator5Loop.Set_LoopTime(30000);
		} else {
			dElev5Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_SL;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_SL);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev5Positi);
			m_nElevator5Case = 14; m_tElevator5Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			dElev5Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + dElev5PostPos;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, dElev5PostPos);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev5Positi);
			m_tElevator5Loop.Takt_Save(5, 4, TRUE);
			gData.dElevatorZPos[1][4] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(3000);
		}
		break;
	case 18:
		if (Check_ElevatorSearch(5)) {
			if (m_pEquipData->bElevatorAlign) {
				m_nElevator5Case = 40; m_tElevator5Loop.Set_LoopTime(30000);
			} else {
				m_nElevator5Case = 20; m_tElevator5Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 20:	// Picker Wait
		m_tElevator5Loop.Set_LoopTime(30000);
		return TRUE;

	case 21:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][4] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			if (!m_pDX02->iElevator5TrayExist) gData.dElevatorZPos[0][4] = 0.0;
			m_nElevator5Case = 1; m_tElevator5Loop.Set_LoopTime(30000);
		}
		break;

	case 30:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Move_Position(nElevZAxisNo, 0);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(30000);
		}
		break;
	case 31:
		if (g_objCommon.Check_Position(nElevZAxisNo, 0)) {
			g_objCommon.Save_Motion(nElevZAxisNo, 0);
			m_nElevator5Case = 20; m_tElevator5Loop.Set_LoopTime(5000);
		}
		break;

	case 40:
			m_pDY02->oElevator5Clamp1On = TRUE; m_pDY02->oElevator5Clamp1Off = FALSE;
			m_pDY02->oElevator5Clamp2On = TRUE; m_pDY02->oElevator5Clamp2Off = FALSE;
			g_objAJinAXL.Write_Output(2);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(5000);
		break;
	case 41:
		if (m_pDX02->iElevator5Clamp1On && !m_pDX02->iElevator5Clamp1Off && m_pDX02->iElevator5Clamp2On && !m_pDX02->iElevator5Clamp2Off) {
			if (!m_tElevator5Loop.Waiting_Time(500)) break;
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(5000);
		}
		break;
	case 42:
			m_pDY02->oElevator5Clamp1On = FALSE; m_pDY02->oElevator5Clamp1Off = TRUE;
			m_pDY02->oElevator5Clamp2On = FALSE; m_pDY02->oElevator5Clamp2Off = TRUE;
			g_objAJinAXL.Write_Output(2);
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(5000);
		break;
	case 43:
		if (!m_pDX02->iElevator5Clamp1On && m_pDX02->iElevator5Clamp1Off && !m_pDX02->iElevator5Clamp2On && m_pDX02->iElevator5Clamp2Off) {
			m_nElevator5Case = 20; m_tElevator5Loop.Set_LoopTime(5000);
		}
		break;

	case 51:
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(5000);
		break;
	case 52:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][4] = 0.0;
			m_nElevator5Case++; m_tElevator5Loop.Set_LoopTime(3000);
		}
		break;
	case 53:
		if (m_pDX02->iElevator5SlideClose) {
			m_nElevator5Case = 1; m_tElevator5Loop.Set_LoopTime(30000);
		}
		break;

	}

	//  5. (Error : 2500)
	if (m_tElevator5Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(2500 + m_nElevator5Case);
		return FALSE;
	}
	return TRUE;
}

//  6. (Error : 2600)
BOOL CSequenceMain::Run_Elevator6()
{
	static int	  nElevZAxisNo = AX_ELEVATOR_Z6;
	static double dElev6PrePos, dElev6PostPos, dElelavtorZ6, dElev6Positi;

	dElev6PrePos  = m_pMoveData->dElevatorZ6[1];
	dElev6PostPos = m_pMoveData->dElevatorZ6[2];
	if (gData.nElevatorOpen[6] > 0) return TRUE;
	if (m_nElevator6Case < 50 && !m_pDX02->iElevator6SlideClose) return TRUE;

	switch (m_nElevator6Case) {
	case 0:	// Wait
		m_tElevator6Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (!m_pDX02->iElevator6TrayExist) {
			m_nElevator6Case = 30; m_tElevator6Loop.Set_LoopTime(5000);
		} else {
			m_tElevator6Loop.Takt_Start(6, 1, TRUE);
			m_nElevator6Case = 10; m_tElevator6Loop.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (m_pDX02->iElevator6Height1) {
			m_tElevator6Loop.Takt_Save(6, 1); m_tElevator6Loop.Takt_Start(5, 2);
			m_nElevator6Case = 12; m_tElevator6Loop.Set_LoopTime(5000);
		} else {
			dElev6Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_UD;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_UD);
			m_nElevator6Case++; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev6Positi);
			m_nElevator6Case = 10; m_tElevator6Loop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if (m_pDX02->iElevator6Height1) {
			dElev6Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_DN*-1.0;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_DN*-1.0);
			m_nElevator6Case++; m_tElevator6Loop.Set_LoopTime(30000);
		} else {
			m_tElevator6Loop.Takt_Save(6, 2); m_tElevator6Loop.Takt_Start(5, 3);
			m_nElevator6Case = 14; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev6Positi);
			m_nElevator6Case = 12; m_tElevator6Loop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if (m_pDX02->iElevator6Height1) {
			m_tElevator6Loop.Takt_Save(6, 3); m_tElevator6Loop.Takt_Start(5, 4);
			m_nElevator6Case = 16; m_tElevator6Loop.Set_LoopTime(30000);
		} else {
			dElev6Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_SL;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_SL);
			m_nElevator6Case++; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev6Positi);
			m_nElevator6Case = 14; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			dElev6Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + dElev6PostPos;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, dElev6PostPos);
			m_nElevator6Case++; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev6Positi);
			m_tElevator6Loop.Takt_Save(6, 4, TRUE);
			gData.dElevatorZPos[1][5] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			m_nElevator6Case++; m_tElevator6Loop.Set_LoopTime(3000);
		}
		break;
	case 18:
		if (Check_ElevatorSearch(6)) {
			m_nElevator6Case = 20; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;

	case 20:	// Picker Wait
		m_tElevator6Loop.Set_LoopTime(30000);
		return TRUE;

	case 21:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][5] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			if (!m_pDX02->iElevator6TrayExist) gData.dElevatorZPos[0][5] = 0.0;
			m_nElevator6Case = 1; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;

	case 30:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Move_Position(nElevZAxisNo, 0);
			m_nElevator6Case++; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;
	case 31:
		if (g_objCommon.Check_Position(nElevZAxisNo, 0)) {
			g_objCommon.Save_Motion(nElevZAxisNo, 0);
			m_nElevator6Case = 20; m_tElevator6Loop.Set_LoopTime(5000);
		}
		break;

	case 51:
			m_nElevator6Case++; m_tElevator6Loop.Set_LoopTime(5000);
		break;
	case 52:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][5] = 0.0;
			m_nElevator6Case++; m_tElevator6Loop.Set_LoopTime(3000);
		}
		break;
	case 53:
		if (m_pDX02->iElevator6SlideClose) {
			m_nElevator6Case = 1; m_tElevator6Loop.Set_LoopTime(30000);
		}
		break;

	}

	//  6. (Error : 2600)
	if (m_tElevator6Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(2600 + m_nElevator6Case);
		return FALSE;
	}
	return TRUE;
}

//  7. (Error : 2700)
BOOL CSequenceMain::Run_Elevator7()
{
	static int	  nElevZAxisNo = AX_ELEVATOR_Z7;
	static double dElev7PrePos, dElev7PostPos, dElelavtorZ7, dElev7Positi;

	dElev7PrePos  = m_pMoveData->dElevatorZ7[1];
	dElev7PostPos = m_pMoveData->dElevatorZ7[2];
	if (gData.nElevatorOpen[7] > 0) return TRUE;
	if (m_nElevator7Case < 50 && !m_pDX02->iElevator7SlideClose) return TRUE;

	switch (m_nElevator7Case) {
	case 0:	// Wait
		m_tElevator7Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (!m_pDX02->iElevator7TrayExist) {
			m_nElevator7Case = 30; m_tElevator7Loop.Set_LoopTime(5000);
		} else {
			m_tElevator7Loop.Takt_Start(7, 1, TRUE);
			m_nElevator7Case = 10; m_tElevator7Loop.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (m_pDX02->iElevator7Height1) {
			m_tElevator7Loop.Takt_Save(7, 1); m_tElevator7Loop.Takt_Start(7, 2);
			m_nElevator7Case = 12; m_tElevator7Loop.Set_LoopTime(5000);
		} else {
			dElev7Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_UD;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_UD);
			m_nElevator7Case++; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev7Positi);
			m_nElevator7Case = 10; m_tElevator7Loop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if (m_pDX02->iElevator7Height1) {
			dElev7Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_DN*-1.0;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_DN*-1.0);
			m_nElevator7Case++; m_tElevator7Loop.Set_LoopTime(30000);
		} else {
			m_tElevator7Loop.Takt_Save(7, 2); m_tElevator7Loop.Takt_Start(7, 3);
			m_nElevator7Case = 14; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev7Positi);
			m_nElevator7Case = 12; m_tElevator7Loop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if (m_pDX02->iElevator7Height1) {
			m_tElevator7Loop.Takt_Save(7, 3); m_tElevator7Loop.Takt_Start(7, 4);
			m_nElevator7Case = 16; m_tElevator7Loop.Set_LoopTime(30000);
		} else {
			dElev7Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + ELEVATOR_SL;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, ELEVATOR_SL);
			m_nElevator7Case++; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev7Positi);
			m_nElevator7Case = 14; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			dElev7Positi = g_objAJinAXL.Get_Position(nElevZAxisNo) + dElev7PostPos;
			g_objAJinAXL.Move_Relative(nElevZAxisNo, dElev7PostPos);
			m_nElevator7Case++; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Save_Motion(nElevZAxisNo, -1, dElev7Positi);
			m_tElevator7Loop.Takt_Save(7, 4, TRUE);
			gData.dElevatorZPos[1][6] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			m_nElevator7Case++; m_tElevator7Loop.Set_LoopTime(3000);
		}
		break;
	case 18:
		if (Check_ElevatorSearch(7)) {
			m_nElevator7Case = 20; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;

	case 20:	// Picker Wait
		m_tElevator7Loop.Set_LoopTime(30000);
		return TRUE;

	case 21:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][6] = g_objAJinAXL.Get_Position(nElevZAxisNo);
			if (!m_pDX02->iElevator7TrayExist) gData.dElevatorZPos[0][6] = 0.0;
			m_nElevator7Case = 1; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;

	case 30:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			g_objCommon.Move_Position(nElevZAxisNo, 0);
			m_nElevator7Case++; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;
	case 31:
		if (g_objCommon.Check_Position(nElevZAxisNo, 0)) {
			g_objCommon.Save_Motion(nElevZAxisNo, 0);
			m_nElevator7Case = 20; m_tElevator7Loop.Set_LoopTime(5000);
		}
		break;

	case 51:
			m_nElevator7Case++; m_tElevator7Loop.Set_LoopTime(5000);
		break;
	case 52:
		if (g_objAJinAXL.Is_Done(nElevZAxisNo)) {
			gData.dElevatorZPos[0][6] = 0.0;
			m_nElevator7Case++; m_tElevator7Loop.Set_LoopTime(3000);
		}
		break;
	case 53:
		if (m_pDX02->iElevator7SlideClose) {
			m_nElevator7Case = 1; m_tElevator7Loop.Set_LoopTime(30000);
		}
		break;

	}

	//  7. (Error : 2700)
	if (m_tElevator7Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(2700 + m_nElevator7Case);
		return FALSE;
	}
	return TRUE;
}

//  8. (Error : 3000)
BOOL CSequenceMain::Run_Transfer1()
{
//	gData.nTransferX1Pos;	//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)
//	gData.nElevatorOpen[10];//0:Stop,1:Open,2:Opened //1(L1),2(L2),3(EN),4(EG),5(NB),6(U1),7(U2)
	static int nFmTran1Pos = 0;
	static int nToTran1Pos = 0;
	static int nPort1No = 0;

	switch (m_nTransfer1Case)
	{
	case 0:	//작업판단
		if (Check_Transfer1(nFmTran1Pos, nToTran1Pos, nPort1No))
		{
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(60000);
		} 
		else
		{
			if (Check_Load12Empy()) 
			{
				if (m_nLoadStage1Case == 0 && m_nLoadStage2Case == 50 && m_pDX04->iLoadStage2TrayExist) {
					m_nLoadStage1Case = 10; gNG->nTrayOX[0][0] = 0;
				}
				if (m_nLoadStage2Case == 0 && m_nLoadStage1Case == 50 && m_pDX04->iLoadStage1TrayExist) {
					m_nLoadStage2Case = 10; gNG->nTrayOX[0][1] = 0;
				}
			}
		}
		return TRUE;

	case 1:
		if ((nFmTran1Pos == 1) ||	//LS1
			(nFmTran1Pos == 2) ||	//LS2
			(nFmTran1Pos == 3) ||	//L1
			(nFmTran1Pos == 4) )    //L2
		{	
			
			
			m_tTransfer1Loop.Takt_Start(8, 1, TRUE);
			g_objCommon.Move_Position(AX_TRANSFER_Z1, 0);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(10000);
		}
		break;
	case 2:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) {
			gData.nTransferX1Pos = nFmTran1Pos;
			g_objCommon.Move_Position(AX_TRANSFER_X1, gData.nTransferX1Pos);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
		}
		break;
	case 3:
		if (g_objCommon.Check_Position(AX_TRANSFER_X1, gData.nTransferX1Pos)) 
		{
			g_objCommon.Save_Motion(AX_TRANSFER_X1, gData.nTransferX1Pos);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if (!m_pDX03->iTransferLTrayExist) 
		{
			m_pDY03->oTransferLGrabOpen = TRUE; m_pDY03->oTransferLGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (m_pDX03->iTransferLGrab1Open && !m_pDX03->iTransferLGrab1Close) 
		{
			if (m_pDX03->iTransferLGrab2Open && !m_pDX03->iTransferLGrab2Close) 
			{
				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
				m_tTransfer1Loop.Takt_Save(8, 1); m_tTransfer1Loop.Takt_Start(8, 2);
			}
		}
		break;

	case 6:	//MES Start
		if (m_pEquipData->bUseMES && (nFmTran1Pos == 3 || nFmTran1Pos == 4) && nToTran1Pos == 5) 
		{
			gAlm.sAlmLotID[1].Format("%d", nPort1No);
			//gMes.nLotPortNo = nPort1No;
			//Type 0 Lot Start : Lot ID Report 
			//g_objMesAgent.Set_LotIDReport(0, nPort1No-1, gLot.sLotID[nPort1No-1], gData.sRecipeName, gLot.nCmCount[nPort1No-1]);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		else
		{
			if (!m_pEquipData->bUseMES && nPort1No > 0) gLot.sRecipeName[nPort1No-1] = gData.sRecipeName;
			
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 8; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 7:
		m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);		
		break;
	
	case 8:	// Tray Up
		if (nFmTran1Pos == 1 || nFmTran1Pos == 2) m_nTransfer1Case = 10;	//Up Stage 12(1,2)
		if (nFmTran1Pos == 3)					  m_nTransfer1Case = 20;	//Up Lot1   (3)
		if (nFmTran1Pos == 4)					  m_nTransfer1Case = 30;	//Up Lot2   (4)
		m_tTransfer1Loop.Set_LoopTime(60000);
		break;

	case 10:	//Up Stage 12(1,2)
		if ((nFmTran1Pos == 1 && m_nLoadStage1Case == 60) ||
			(nFmTran1Pos == 2 && m_nLoadStage2Case == 60) )
		{
			m_tTransfer1Loop.Takt_Save(8, 2); m_tTransfer1Loop.Takt_Start(8, 3);
			if (nFmTran1Pos == 1) g_objCommon.Move_Position(AX_TRANSFER_Z1, 9);
			if (nFmTran1Pos == 2) g_objCommon.Move_Position(AX_TRANSFER_Z1, 10);
			
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++;	m_tTransfer1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 11:
		if ((nFmTran1Pos == 1 && g_objCommon.Check_Position(AX_TRANSFER_Z1, 9)) ||
			(nFmTran1Pos == 2 && g_objCommon.Check_Position(AX_TRANSFER_Z1, 10)) ) {
			if (nFmTran1Pos == 1) g_objCommon.Save_Motion(AX_TRANSFER_Z1, 9);
			if (nFmTran1Pos == 2) g_objCommon.Save_Motion(AX_TRANSFER_Z1, 10);
			m_tTransfer1Loop.Takt_Save(8, 3); m_tTransfer1Loop.Takt_Start(8, 4);
			m_pDY03->oTransferLGrabOpen = FALSE; m_pDY03->oTransferLGrabClose = TRUE;
			g_objAJinAXL.Write_Output(3);
			
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 12:
		if (!m_pDX03->iTransferLGrab1Open && m_pDX03->iTransferLGrab1Close) {
			if (!m_pDX03->iTransferLGrab2Open && m_pDX03->iTransferLGrab2Close) {
				if (!m_tTransfer1Loop.Waiting_Time(300)) break;
				m_tTransfer1Loop.Takt_Save(8, 4); m_tTransfer1Loop.Takt_Start(8, 5);
				g_objCommon.Move_Position(AX_TRANSFER_Z1, 0);
				
				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++;	m_tTransfer1Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 13:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, 0);
			
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 14:
		if (m_pDX03->iTransferLTrayExist) {
			gData.sLotID_Tansfer[0]  = gData.sLotID_LoadStage[nFmTran1Pos-1]; 
			gData.nTrayNo_Tansfer[0] = gData.nTrayNo_LoadStage[nFmTran1Pos-1];
			gData.nPortNo_Tansfer[0] = gData.nPortNo_LoadStage[nFmTran1Pos-1];
			gData.sLotID_Tansfer[2]  = gData.sLotID_Tansfer[0];

			gData.sLotID_LoadStage[nFmTran1Pos-1]  = "";
			gData.nTrayNo_LoadStage[nFmTran1Pos-1] = gData.nPortNo_LoadStage[nFmTran1Pos-1] = 0;

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);

			m_sLog.Format("[Transfer1: Up Load-Stage%d] Lot(%s) TNo(%d) PNo(%d)", (nFmTran1Pos), gData.sLotID_Tansfer[0], gData.nTrayNo_Tansfer[0], gData.nPortNo_Tansfer[0]);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		break;
	case 15:
		if (m_pDX03->iTransferLTrayExist) 
		{
			m_tTransfer1Loop.Takt_Save(8, 5); m_tTransfer1Loop.Takt_Start(8, 6);
			if (nFmTran1Pos == 1 && m_nLoadStage1Case == 60) m_nLoadStage1Case = 61;
			if (nFmTran1Pos == 2 && m_nLoadStage2Case == 60) m_nLoadStage2Case = 61;

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 40; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;

	case 20:	//Up Lot1   (3)
		if (m_pDX03->iTransferLGrab1Open && !m_pDX03->iTransferLGrab1Close) 
		{
			if (m_pDX03->iTransferLGrab2Open && !m_pDX03->iTransferLGrab2Close) 
			{
				m_tTransfer1Loop.Takt_Save(8, 6); m_tTransfer1Loop.Takt_Start(8, 7);
				m_pDY00->oElevator1Clamp1On = FALSE; m_pDY00->oElevator1Clamp1Off = TRUE;
				m_pDY00->oElevator1Clamp2On = FALSE; m_pDY00->oElevator1Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(0);
				
				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 21:
		if (!m_pDX00->iElevator1Clamp1On && m_pDX00->iElevator1Clamp1Off && !m_pDX00->iElevator1Clamp2On && m_pDX00->iElevator1Clamp2Off) {
			m_tTransfer1Loop.Takt_Save(8, 7); m_tTransfer1Loop.Takt_Start(8, 8);
			
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(60000);
		}
		break;
	case 22:
		if (m_nElevator1Case == 20 && gData.nElevatorOpen[1] == 0) {
			m_tTransfer1Loop.Takt_Save(8, 8); m_tTransfer1Loop.Takt_Start(8, 9);
			g_objCommon.Move_Position(AX_TRANSFER_Z1, 3);
			
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(60000);
		}
		return TRUE;
	case 23:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 3)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, 3);
			m_tTransfer1Loop.Takt_Save(8, 9); m_tTransfer1Loop.Takt_Start(8, 10);
			m_pDY03->oTransferLGrabOpen = FALSE; m_pDY03->oTransferLGrabClose = TRUE;
			g_objAJinAXL.Write_Output(3);
			
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 24:
		if (!m_pDX03->iTransferLGrab1Open && m_pDX03->iTransferLGrab1Close) {
			if (!m_pDX03->iTransferLGrab2Open && m_pDX03->iTransferLGrab2Close) {
//				m_pDY00->oElevator1Clamp1On = TRUE; m_pDY00->oElevator1Clamp1Off = FALSE;
//				m_pDY00->oElevator1Clamp2On = TRUE; m_pDY00->oElevator1Clamp2Off = FALSE;
//				g_objAJinAXL.Write_Output(0);
				m_tTransfer1Loop.Takt_Save(8, 10); m_tTransfer1Loop.Takt_Start(8, 11);
				
				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 25:
//		if (m_pDX00->iElevator1Clamp1On && !m_pDX00->iElevator1Clamp1Off && m_pDX00->iElevator1Clamp2On && !m_pDX00->iElevator1Clamp2Off) {
			g_objCommon.Move_Position(AX_TRANSFER_Z1, 0);
			
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
//		}
		break;
	case 26:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) 
		{
			if (m_pDX03->iTransferLTrayExist) 
			{
				g_objCommon.Save_Motion(AX_TRANSFER_Z1, 0);
				m_pDY00->oElevator1Clamp1On = FALSE; m_pDY00->oElevator1Clamp1Off = TRUE;
				m_pDY00->oElevator1Clamp2On = FALSE; m_pDY00->oElevator1Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(0);
				
				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 27:
		if (!m_pDX00->iElevator1Clamp1On && m_pDX00->iElevator1Clamp1Off && !m_pDX00->iElevator1Clamp2On && m_pDX00->iElevator1Clamp2Off) 
		{
			if (nToTran1Pos == 5) 
			{				
				if (!Set_LotStart(gLot.sLotID[nPort1No-1], nPort1No)) return FALSE;
				gLot.bEmptyTray[nPort1No-1] = TRUE;
			}
			else
			{
				gLot.nTrayOutCnt[nPort1No-1]++;
			}

			gData.sLotID_Tansfer[0]  = gLot.sLotID[nPort1No-1];
			gData.nTrayNo_Tansfer[0] = gLot.nTrayOutCnt[nPort1No-1];
			gData.nPortNo_Tansfer[0] = nPort1No;
			gData.sLotID_Tansfer[2]  = gData.sLotID_Tansfer[0];

			if (m_nElevator1Case == 20) m_nElevator1Case = 21;

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 40; m_tTransfer1Loop.Set_LoopTime(5000);
			m_tTransfer1Loop.Takt_Save(8, 11); m_tTransfer1Loop.Takt_Start(8, 12);

			m_sLog.Format("[Transfer1: Up Load-Lot1] Lot(%s) TNo(%d) PNo(%d)", gData.sLotID_Tansfer[0], gData.nTrayNo_Tansfer[0], gData.nPortNo_Tansfer[0]);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		break;

	case 30:	//Up Lot2   (4)
		if (m_pDX03->iTransferLGrab1Open && !m_pDX03->iTransferLGrab1Close) 
		{
			if (m_pDX03->iTransferLGrab2Open && !m_pDX03->iTransferLGrab2Close) 
			{
				m_tTransfer1Loop.Takt_Save(8, 12); m_tTransfer1Loop.Takt_Start(8, 13);
				m_pDY00->oElevator2Clamp1On = FALSE; m_pDY00->oElevator2Clamp1Off = TRUE;
				m_pDY00->oElevator2Clamp2On = FALSE; m_pDY00->oElevator2Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(0);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 31:
		if (!m_pDX00->iElevator2Clamp1On && m_pDX00->iElevator2Clamp1Off && !m_pDX00->iElevator2Clamp2On && m_pDX00->iElevator2Clamp2Off) 
		{
			m_tTransfer1Loop.Takt_Save(8, 13); m_tTransfer1Loop.Takt_Start(8, 14);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(60000);
		}
		break;
	case 32:
		if (m_nElevator2Case == 20 && gData.nElevatorOpen[2] == 0) 
		{
			m_tTransfer1Loop.Takt_Save(8, 14); m_tTransfer1Loop.Takt_Start(8, 15);
			g_objCommon.Move_Position(AX_TRANSFER_Z1, 4);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(60000);
		}
		return TRUE;
	case 33:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 4)) 
		{
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, 4);
			m_tTransfer1Loop.Takt_Save(8, 15); m_tTransfer1Loop.Takt_Start(8, 16);
			m_pDY03->oTransferLGrabOpen = FALSE; m_pDY03->oTransferLGrabClose = TRUE;
			g_objAJinAXL.Write_Output(3);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 34:
		if (!m_pDX03->iTransferLGrab1Open && m_pDX03->iTransferLGrab1Close) 
		{
			if (!m_pDX03->iTransferLGrab2Open && m_pDX03->iTransferLGrab2Close) 
			{
//				m_pDY00->oElevator2Clamp1On = TRUE; m_pDY00->oElevator2Clamp1Off = FALSE;
//				m_pDY00->oElevator2Clamp2On = TRUE; m_pDY00->oElevator2Clamp2Off = FALSE;
//				g_objAJinAXL.Write_Output(0);
				m_tTransfer1Loop.Takt_Save(8, 16); m_tTransfer1Loop.Takt_Start(8, 17);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 35:
//		if (m_pDX00->iElevator2Clamp1On && !m_pDX00->iElevator2Clamp1Off && m_pDX00->iElevator2Clamp2On && !m_pDX00->iElevator2Clamp2Off) {
			g_objCommon.Move_Position(AX_TRANSFER_Z1, 0);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
//		}
		break;
	case 36:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) 
		{
			if (m_pDX03->iTransferLTrayExist) 
			{
				g_objCommon.Save_Motion(AX_TRANSFER_Z1, 0);
				m_pDY00->oElevator2Clamp1On = FALSE; m_pDY00->oElevator2Clamp1Off = TRUE;
				m_pDY00->oElevator2Clamp2On = FALSE; m_pDY00->oElevator2Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(0);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 37:
		if (!m_pDX00->iElevator2Clamp1On && m_pDX00->iElevator2Clamp1Off && !m_pDX00->iElevator2Clamp2On && m_pDX00->iElevator2Clamp2Off) {
			if (nToTran1Pos == 5) {
				if (!Set_LotStart(gLot.sLotID[nPort1No-1], nPort1No)) return FALSE;
				gLot.bEmptyTray[nPort1No-1] = TRUE;
			} else {
				gLot.nTrayOutCnt[nPort1No-1]++;
			}

			gData.sLotID_Tansfer[0]  = gLot.sLotID[nPort1No-1];
			gData.nTrayNo_Tansfer[0] = gLot.nTrayOutCnt[nPort1No-1];
			gData.nPortNo_Tansfer[0] = nPort1No;
			gData.sLotID_Tansfer[2]  = gData.sLotID_Tansfer[0];

			if (m_nElevator2Case == 20) m_nElevator2Case = 21;

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 40; m_tTransfer1Loop.Set_LoopTime(5000);
			m_tTransfer1Loop.Takt_Save(8, 17); m_tTransfer1Loop.Takt_Start(8, 18);

			m_sLog.Format("[Transfer1: Up Load-Lot2] Lot(%s) TNo(%d) PNo(%d)", gData.sLotID_Tansfer[0], gData.nTrayNo_Tansfer[0], gData.nPortNo_Tansfer[0]);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		break;

//	gData.nTransferX1Pos;	//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)
	case 40:	//Tray Down
		if (nToTran1Pos == 1 || nToTran1Pos == 2) m_nTransfer1Case = 41;	//Down Stage 12 (1,2)
		if (nToTran1Pos == 5)					  m_nTransfer1Case = 51;	//Down Empty-NG (5)
		if (nToTran1Pos == 6)					  m_nTransfer1Case = 61;	//Down Empty-Good (6)
		m_tTransfer1Loop.Set_LoopTime(5000);
		break;

	case 41:	//Down Stage 12 (1,2)
		nToTran1Pos = 0;
		if (m_nLoadStage1Case == 0) nToTran1Pos = 1;
		if (m_nLoadStage2Case == 0) nToTran1Pos = 2;
		if (nToTran1Pos > 0) 
		{
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++;	m_tTransfer1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 42:	
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) {
			m_tTransfer1Loop.Takt_Save(8, 18); m_tTransfer1Loop.Takt_Start(8, 19);
			gData.nTransferX1Pos = nToTran1Pos;
//			g_objCommon.Move_Position(AX_TRANSFER_X1, nToTran1Pos, 0.7);
			g_objCommon.Move_Position(AX_TRANSFER_X1, nToTran1Pos);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(10000);
		}
		break;
	case 43:
		if (g_objCommon.Check_Position(AX_TRANSFER_X1, nToTran1Pos)) {
			if ((nToTran1Pos == 1 && !m_pDX04->iLoadStage1TrayExist) ||
				(nToTran1Pos == 2 && !m_pDX04->iLoadStage2TrayExist)) {
				g_objCommon.Save_Motion(AX_TRANSFER_X1, nToTran1Pos);
				m_tTransfer1Loop.Takt_Save(8, 19); m_tTransfer1Loop.Takt_Start(8, 20);
				g_objCommon.Move_Position(AX_TRANSFER_Z1, nToTran1Pos);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 44:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, nToTran1Pos)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, nToTran1Pos);
			m_tTransfer1Loop.Takt_Save(8, 20); m_tTransfer1Loop.Takt_Start(8, 21);
			m_pDY03->oTransferLGrabOpen = TRUE; m_pDY03->oTransferLGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 45:
		if (m_pDX03->iTransferLGrab1Open && !m_pDX03->iTransferLGrab1Close) {
			if (m_pDX03->iTransferLGrab2Open && !m_pDX03->iTransferLGrab2Close) {
				if (!m_tTransfer1Loop.Waiting_Time(300)) break;
				m_tTransfer1Loop.Takt_Save(8, 21); m_tTransfer1Loop.Takt_Start(8, 22);
				g_objCommon.Move_Position(AX_TRANSFER_Z1, 0);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 46:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) 
		{
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, 0);
			m_sLog.Format("[Transfer1: Down Load-Stage%d] Lot(%s) TNo(%d) PNo(%d)", nToTran1Pos, gData.sLotID_Tansfer[0], gData.nTrayNo_Tansfer[0], gData.nPortNo_Tansfer[0]);
			g_objLogFile.Save_HandlerLog(m_sLog);

			gData.sLotID_LoadStage[nToTran1Pos-1]  = gData.sLotID_Tansfer[0];
			gData.nTrayNo_LoadStage[nToTran1Pos-1] = gData.nTrayNo_Tansfer[0];
			gData.nPortNo_LoadStage[nToTran1Pos-1] = gData.nPortNo_Tansfer[0];
			gData.sLotID_LoadStage[2]  = gData.sLotID_LoadStage[nToTran1Pos-1];

			gData.sLotID_Tansfer[0]  = "";
			gData.nTrayNo_Tansfer[0] = gData.nPortNo_Tansfer[0] = 0;
			m_tTransfer1Loop.Takt_Save(8, 22); m_tTransfer1Loop.Takt_Start(8, 23);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 47:
		if (!m_pDX03->iTransferLTrayExist) 
		{
			if ((nToTran1Pos == 1 && m_pDX04->iLoadStage1TrayExist) ||
				(nToTran1Pos == 2 && m_pDX04->iLoadStage2TrayExist) ) 
			{
				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 48:
			if (m_nLoadStage1Case == 0) m_nLoadStage1Case = 1;
			if (m_nLoadStage2Case == 0) m_nLoadStage2Case = 1;
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 70; m_tTransfer1Loop.Set_LoopTime(5000);
		break;

	case 51:	//Down Empty-NG (5)
		if (gData.nTransferX2Pos > 5) 
		{
			m_tTransfer1Loop.Takt_Save(8, 23); m_tTransfer1Loop.Takt_Start(8, 24);
			gData.nTransferX1Pos = nToTran1Pos;
			g_objCommon.Move_Position(AX_TRANSFER_X1, gData.nTransferX1Pos);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 53; m_tTransfer1Loop.Set_LoopTime(30000);
		} 
		else
		{
			m_tTransfer1Loop.Takt_Save(8, 24); m_tTransfer1Loop.Takt_Start(8, 25);
			gData.nTransferX1Pos = 4;	//L2
			g_objCommon.Move_Position(AX_TRANSFER_X1, 4);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
		}
		break;
	case 52:
		if (g_objCommon.Check_Position(AX_TRANSFER_X1, 4)) 
		{
			if (gData.nTransferX2Pos > 5) 
			{
				g_objCommon.Save_Motion(AX_TRANSFER_X1, 4);
				m_tTransfer1Loop.Takt_Save(8, 25); m_tTransfer1Loop.Takt_Start(8, 26);
				gData.nTransferX1Pos = nToTran1Pos;
				g_objCommon.Move_Position(AX_TRANSFER_X1, gData.nTransferX1Pos);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
			}
		}
		return TRUE;
	case 53:
		if (g_objCommon.Check_Position(AX_TRANSFER_X1, gData.nTransferX1Pos)) 
		{
			g_objCommon.Save_Motion(AX_TRANSFER_X1, gData.nTransferX1Pos);
			m_tTransfer1Loop.Takt_Save(8, 26); m_tTransfer1Loop.Takt_Start(8, 27);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
		}
		break;
	case 54:
		if (m_nElevator3Case == 20 && gData.nElevatorOpen[3] == 0) 
		{
			m_tTransfer1Loop.Takt_Save(8, 27); m_tTransfer1Loop.Takt_Start(8, 28);
			g_objCommon.Move_Position(AX_TRANSFER_Z1, nToTran1Pos);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++;	m_tTransfer1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 55:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, nToTran1Pos)) 
		{
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, nToTran1Pos);
			m_tTransfer1Loop.Takt_Save(8, 28); m_tTransfer1Loop.Takt_Start(8, 29);
			m_pDY03->oTransferLGrabOpen = TRUE; m_pDY03->oTransferLGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 56:
		if (m_pDX03->iTransferLGrab1Open && !m_pDX03->iTransferLGrab1Close) 
		{
			if (m_pDX03->iTransferLGrab2Open && !m_pDX03->iTransferLGrab2Close)
			{
				if (!m_tTransfer1Loop.Waiting_Time(300)) break;
				m_tTransfer1Loop.Takt_Save(8, 29); m_tTransfer1Loop.Takt_Start(8, 30);
				g_objCommon.Move_Position(AX_TRANSFER_Z1, 0);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 57:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) 
		{
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, 0);
			m_sLog.Format("[Transfer1: Down Empty-NG] Lot(%s) TNo(%d) PNo(%d)", gData.sLotID_Tansfer[0], gData.nTrayNo_Tansfer[0], gData.nPortNo_Tansfer[0]);
			g_objLogFile.Save_HandlerLog(m_sLog);

			gData.sLotID_Tansfer[0]  = "";
			gData.nTrayNo_Tansfer[0] = gData.nPortNo_Tansfer[0] = 0;

			m_tTransfer1Loop.Takt_Save(8, 30); m_tTransfer1Loop.Takt_Start(8, 31);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 58:
		if (!m_pDX03->iTransferLTrayExist) 
		{
			if (m_nElevator3Case == 20) m_nElevator3Case = 21;
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 70; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;

	case 61:	//Down Empty-Good (6)
		if (gData.nTransferX2Pos > 6) 
		{
			m_tTransfer1Loop.Takt_Save(8, 31); m_tTransfer1Loop.Takt_Start(8, 32);
			gData.nTransferX1Pos = nToTran1Pos;
			g_objCommon.Move_Position(AX_TRANSFER_X1, gData.nTransferX1Pos);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 63; m_tTransfer1Loop.Set_LoopTime(30000);
		} 
		else
		{
			m_tTransfer1Loop.Takt_Save(8, 32); m_tTransfer1Loop.Takt_Start(8, 33);
			g_objCommon.Move_Position(AX_TRANSFER_X1, 4);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
		}
		break;
	case 62:
		if (g_objCommon.Check_Position(AX_TRANSFER_X1, 4)) 
		{
			double dT2Pos = g_objAJinAXL.Get_Position(AX_TRANSFER_X2);
			if (gData.nTransferX2Pos > 6 && dT2Pos < (m_pMoveData->dTransferX2[2]-10)) 
			{
				g_objCommon.Save_Motion(AX_TRANSFER_X1, 4);
				m_tTransfer1Loop.Takt_Save(8, 33); m_tTransfer1Loop.Takt_Start(8, 34);
				gData.nTransferX1Pos = nToTran1Pos;
				g_objCommon.Move_Position(AX_TRANSFER_X1, gData.nTransferX1Pos);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
			}
		}
		return TRUE;
	case 63:
		if (g_objCommon.Check_Position(AX_TRANSFER_X1, gData.nTransferX1Pos))
		{
			g_objCommon.Save_Motion(AX_TRANSFER_X1, gData.nTransferX1Pos);
			m_tTransfer1Loop.Takt_Save(8, 34); m_tTransfer1Loop.Takt_Start(8, 35);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
		}
		break;
	case 64:
		if (m_nElevator4Case == 20 && gData.nElevatorOpen[4] == 0) 
		{
			m_tTransfer1Loop.Takt_Save(8, 35); m_tTransfer1Loop.Takt_Start(8, 36);
			g_objCommon.Move_Position(AX_TRANSFER_Z1, nToTran1Pos);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++;	m_tTransfer1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 65:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, nToTran1Pos)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, nToTran1Pos);
			m_tTransfer1Loop.Takt_Save(8, 36); m_tTransfer1Loop.Takt_Start(8, 37);
			m_pDY03->oTransferLGrabOpen = TRUE; m_pDY03->oTransferLGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 66:
		if (m_pDX03->iTransferLGrab1Open && !m_pDX03->iTransferLGrab1Close) 
		{
			if (m_pDX03->iTransferLGrab2Open && !m_pDX03->iTransferLGrab2Close) 
			{
				if (!m_tTransfer1Loop.Waiting_Time(300)) break;
				m_tTransfer1Loop.Takt_Save(8, 37); m_tTransfer1Loop.Takt_Start(8, 38);
				g_objCommon.Move_Position(AX_TRANSFER_Z1, 0);

				m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
				m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 67:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) 
		{
			g_objCommon.Save_Motion(AX_TRANSFER_Z1, 0);
			m_sLog.Format("[Transfer1: Down Empty-Good] Lot(%s) TNo(%d) PNo(%d)", gData.sLotID_Tansfer[0], gData.nTrayNo_Tansfer[0], gData.nPortNo_Tansfer[0]);
			g_objLogFile.Save_HandlerLog(m_sLog);

			gData.sLotID_Tansfer[0]  = "";
			gData.nTrayNo_Tansfer[0] = gData.nPortNo_Tansfer[0] = 0;

			m_tTransfer1Loop.Takt_Save(8, 38); m_tTransfer1Loop.Takt_Start(8, 39);

			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;
	case 68:
		if (!m_pDX03->iTransferLTrayExist) 
		{
			if (m_nElevator4Case == 20) m_nElevator4Case = 21;
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 70; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;

	case 70:	//대기위치로
			if (m_pDX04->iLoadStage1TrayExist && m_pDX04->iLoadStage2TrayExist) gData.nTransferX1Pos = 1;
			else																gData.nTransferX1Pos = 3;
			g_objCommon.Move_Position(AX_TRANSFER_X1, gData.nTransferX1Pos);
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case++; m_tTransfer1Loop.Set_LoopTime(30000);
		break;
	case 71:
		if (g_objCommon.Check_Position(AX_TRANSFER_X1, gData.nTransferX1Pos)) 
		{
			g_objCommon.Save_Motion(AX_TRANSFER_X1, gData.nTransferX1Pos);
			m_tTransfer1Loop.Takt_Save(8, 39, TRUE);
			m_sLog.Format("MCC,8,Transfer1,%d", m_nTransfer1Case); g_objLogFile.Save_SeqLog(m_sLog);
			m_nTransfer1Case = 0; m_tTransfer1Loop.Set_LoopTime(5000);
		}
		break;

	}

	//  8. (Error : 3000)
	if (m_tTransfer1Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(3000 + m_nTransfer1Case);
		return FALSE;
	}
	return TRUE;
}

//  9. (Error : 3500)
BOOL CSequenceMain::Run_Transfer2()
{
//	gData.nTransferX2Pos;	//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)
//	gData.nElevatorOpen[10];//0:Stop,1:Open,2:Opened //1(L1),2(L2),3(EN),4(EG),5(NB),6(U1),7(U2)
	static int nFmTran2Pos = 0;
	static int nToTran2Pos = 0;
	static int nPort2No = 0, nPosX = 0, nPosZ = 0;

	switch (m_nTransfer2Case) {
	case 0:	//작업판단
		if (Check_EmptyUnloadPicker()==FALSE) {
			if (m_nNGStage1Case == 0 && m_pDX11->iNGStage1TrayExist) m_nNGStage1Case = 1;
			if (m_nNGStage2Case == 0 && m_pDX11->iNGStage2TrayExist) m_nNGStage2Case = 1;
			if (m_nGoodStage1Case == 0 && m_pDX12->iGoodStage1TrayExist) m_nGoodStage1Case = 1;
			if (m_nGoodStage2Case == 0 && m_pDX12->iGoodStage2TrayExist) m_nGoodStage2Case = 1;
		}
		if (Check_Transfer2(nFmTran2Pos, nToTran2Pos, nPort2No)) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(60000);
		}
		return TRUE;

	case 1:
			g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		break;
	case 2:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			m_pDY03->oTransferRGrabOpen = TRUE; m_pDY03->oTransferRGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 3:
		if (m_pDX03->iTransferRGrab1Open && !m_pDX03->iTransferRGrab1Close) {
			if (m_pDX03->iTransferRGrab2Open && !m_pDX03->iTransferRGrab2Close) {
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 4:
		if (nFmTran2Pos == 5 || nFmTran2Pos == 6) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		} else {
			gData.nTransferX2Pos = nFmTran2Pos;
			m_nTransfer2Case = 6; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 5:
		if ((nFmTran2Pos == 5 && gData.nTransferX1Pos < 5) ||
			(nFmTran2Pos == 6 && gData.nTransferX1Pos < 6) ) {
			gData.nTransferX2Pos = nFmTran2Pos;
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		return TRUE;

	case 6:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			m_tTransfer2Loop.Takt_Start(9, 1, TRUE);
			nPosX = gData.nTransferX2Pos - 4;
			if (gData.nTransferX2Pos ==  5) nPosZ =  1;	//Up Empty-NG (5)
			if (gData.nTransferX2Pos ==  6) nPosZ =  2;	//Up Empty-Good (6)
			if (gData.nTransferX2Pos ==  7) nPosZ = 10;	//Up Buffer NG (7)
			if (gData.nTransferX2Pos == 10) nPosZ = 11;	//Up NG-Stage 1 (10)
			if (gData.nTransferX2Pos == 11) nPosZ = 12;	//Up NG-Stage 2 (11)
			if (gData.nTransferX2Pos == 12) nPosZ = 13;	//Up Good-Stage 1 (12)
			if (gData.nTransferX2Pos == 13) nPosZ = 14;	//Up Good-Stage 2 (13)

			g_objCommon.Move_Position(AX_TRANSFER_X2, nPosX);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
	case 7:
		if (g_objCommon.Check_Position(AX_TRANSFER_X2, nPosX)) {
			g_objCommon.Save_Motion(AX_TRANSFER_X2, nPosX);
			m_tTransfer2Loop.Takt_Save(9, 1); m_tTransfer2Loop.Takt_Start(9, 2);
			m_nTransfer2Case = 9; m_tTransfer2Loop.Set_LoopTime(5000);
		}
		break;
	
	case 9:
		if (gData.nTransferX2Pos ==  5) m_nTransfer2Case = 10;	//Up Empty-NG (5)
		if (gData.nTransferX2Pos ==  6) m_nTransfer2Case = 20;	//Up Empty-Good (6)
		if (gData.nTransferX2Pos ==  7) m_nTransfer2Case = 30;	//Up Buffer NG (7)
		if (gData.nTransferX2Pos == 10) m_nTransfer2Case = 40;	//Up NG-Stage 1 (10)
		if (gData.nTransferX2Pos == 11) m_nTransfer2Case = 40;	//Up NG-Stage 2 (11)
		if (gData.nTransferX2Pos == 12) m_nTransfer2Case = 50;	//Up Good-Stage 1 (12)
		if (gData.nTransferX2Pos == 13) m_nTransfer2Case = 50;	//Up Good-Stage 2 (13)
		m_tTransfer2Loop.Set_LoopTime(5000);
		break;

	// gData.nElevatorOpen[10];//0:Stop,1:Open,2:Opened //1(L1),2(L2),3(EN),4(EG),5(NB),6(U1),7(U2)
	case 10:	//Up Empty-NG (5)
		if (m_nElevator3Case == 20 && gData.nElevatorOpen[3] == 0) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 11:
		if (m_nElevator3Case == 20 && gData.nElevatorOpen[3] == 0) {
			if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
				m_tTransfer2Loop.Takt_Save(9, 2); m_tTransfer2Loop.Takt_Start(9, 3);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 12:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 3); m_tTransfer2Loop.Takt_Start(9, 4);
			m_pDY03->oTransferRGrabOpen = FALSE; m_pDY03->oTransferRGrabClose = TRUE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 13:
		if (!m_pDX03->iTransferRGrab1Open && m_pDX03->iTransferRGrab1Close) {
			if (!m_pDX03->iTransferRGrab2Open && m_pDX03->iTransferRGrab2Close) {
				m_tTransfer2Loop.Takt_Save(9, 4); m_tTransfer2Loop.Takt_Start(9, 5);
//				m_pDY01->oElevator3Clamp1On = TRUE; m_pDY01->oElevator3Clamp1Off = FALSE;
//				m_pDY01->oElevator3Clamp2On = TRUE; m_pDY01->oElevator3Clamp2Off = FALSE;
//				g_objAJinAXL.Write_Output(1);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 14:
//		if (m_pDX01->iElevator3Clamp1On && !m_pDX01->iElevator3Clamp1Off && m_pDX01->iElevator3Clamp2On && !m_pDX01->iElevator3Clamp2Off) {
			g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
//		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			if (m_pDX03->iTransferRTrayExist) {
				g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
				m_tTransfer2Loop.Takt_Save(9, 5); m_tTransfer2Loop.Takt_Start(9, 6);
				m_pDY01->oElevator3Clamp1On = FALSE; m_pDY01->oElevator3Clamp1Off = TRUE;
				m_pDY01->oElevator3Clamp2On = FALSE; m_pDY01->oElevator3Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(1);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 16:
		if (!m_pDX01->iElevator3Clamp1On && m_pDX01->iElevator3Clamp1Off && !m_pDX01->iElevator3Clamp2On && m_pDX01->iElevator3Clamp2Off) {
			m_sLog.Format("[Transfer2: Up Empty-NG] Lot(%s) TNo(%d) PNo(%d)", gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1]);
			g_objLogFile.Save_HandlerLog(m_sLog);

			gData.sLotID_Tansfer[1] = "";
			gData.nTrayNo_Tansfer[1] = gData.nPortNo_Tansfer[1] = 0;

			if (m_nElevator3Case == 20) m_nElevator3Case = 21;
			m_nTransfer2Case = 60; m_tTransfer2Loop.Set_LoopTime(5000);
			m_tTransfer2Loop.Takt_Save(9, 6); m_tTransfer2Loop.Takt_Start(9, 7);
		}
		break;

	case 20:	//Up Empty-Good (6)
		if (m_nElevator4Case == 20 && gData.nElevatorOpen[4] == 0) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 21:
		if (m_nElevator4Case == 20 && gData.nElevatorOpen[4] == 0) {
			if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
				m_tTransfer2Loop.Takt_Save(9, 7); m_tTransfer2Loop.Takt_Start(9, 8);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 22:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 8); m_tTransfer2Loop.Takt_Start(9, 9);
			m_pDY03->oTransferRGrabOpen = FALSE; m_pDY03->oTransferRGrabClose = TRUE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 23:
		if (!m_pDX03->iTransferRGrab1Open && m_pDX03->iTransferRGrab1Close) {
			if (!m_pDX03->iTransferRGrab2Open && m_pDX03->iTransferRGrab2Close) {
				m_tTransfer2Loop.Takt_Save(9, 9); m_tTransfer2Loop.Takt_Start(9, 10);
//				m_pDY01->oElevator4Clamp1On = TRUE; m_pDY01->oElevator4Clamp1Off = FALSE;
//				m_pDY01->oElevator4Clamp2On = TRUE; m_pDY01->oElevator4Clamp2Off = FALSE;
//				g_objAJinAXL.Write_Output(1);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 24:
//		if (m_pDX01->iElevator4Clamp1On && !m_pDX01->iElevator4Clamp1Off && m_pDX01->iElevator4Clamp2On && !m_pDX01->iElevator4Clamp2Off) {
			g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
//		}
		break;
	case 25:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			if (m_pDX03->iTransferRTrayExist) {
				g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
				m_tTransfer2Loop.Takt_Save(9, 10); m_tTransfer2Loop.Takt_Start(9, 11);
				m_pDY01->oElevator4Clamp1On = FALSE; m_pDY01->oElevator4Clamp1Off = TRUE;
				m_pDY01->oElevator4Clamp2On = FALSE; m_pDY01->oElevator4Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(1);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 26:
		if (!m_pDX01->iElevator4Clamp1On && m_pDX01->iElevator4Clamp1Off && !m_pDX01->iElevator4Clamp2On && m_pDX01->iElevator4Clamp2Off) {
			m_sLog.Format("[Transfer2: Up Empty-Good] Lot(%s) TNo(%d) PNo(%d)", gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1]);
			g_objLogFile.Save_HandlerLog(m_sLog);

			gData.sLotID_Tansfer[1] = "";
			gData.nTrayNo_Tansfer[1] = gData.nPortNo_Tansfer[1] = 0;

			if (m_nElevator4Case == 20) m_nElevator4Case = 21;
			m_nTransfer2Case = 60; m_tTransfer2Loop.Set_LoopTime(5000);
			m_tTransfer2Loop.Takt_Save(9, 11); m_tTransfer2Loop.Takt_Start(9, 12);
		}
		break;

	case 30:	//Up Buffer NG (7)
		if (m_nElevator5Case == 20 && gData.nElevatorOpen[5] == 0) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 31:
		if (m_nElevator5Case == 20 && gData.nElevatorOpen[5] == 0) {
			if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
				m_tTransfer2Loop.Takt_Save(9, 12); m_tTransfer2Loop.Takt_Start(9, 13);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 32:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 13); m_tTransfer2Loop.Takt_Start(9, 14);
			m_pDY03->oTransferRGrabOpen = FALSE; m_pDY03->oTransferRGrabClose = TRUE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 33:
		if (!m_pDX03->iTransferRGrab1Open && m_pDX03->iTransferRGrab1Close) {
			if (!m_pDX03->iTransferRGrab2Open && m_pDX03->iTransferRGrab2Close) {
				m_tTransfer2Loop.Takt_Save(9, 14); m_tTransfer2Loop.Takt_Start(9, 15);
//				m_pDY02->oElevator5Clamp1On = TRUE; m_pDY02->oElevator5Clamp1Off = FALSE;
//				m_pDY02->oElevator5Clamp2On = TRUE; m_pDY02->oElevator5Clamp2Off = FALSE;
				g_objAJinAXL.Write_Output(2);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 34:
//		if (m_pDX02->iElevator5Clamp1On && !m_pDX02->iElevator5Clamp1Off && m_pDX02->iElevator5Clamp2On && !m_pDX02->iElevator5Clamp2Off) {
			g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
//		}
		break;
	case 35:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			if (m_pDX03->iTransferRTrayExist) {
				g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
				m_tTransfer2Loop.Takt_Save(9, 15); m_tTransfer2Loop.Takt_Start(9, 16);
				m_pDY02->oElevator5Clamp1On = FALSE; m_pDY02->oElevator5Clamp1Off = TRUE;
				m_pDY02->oElevator5Clamp2On = FALSE; m_pDY02->oElevator5Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(2);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 36:
		if (!m_pDX02->iElevator5Clamp1On && m_pDX02->iElevator5Clamp1Off && !m_pDX02->iElevator5Clamp2On && m_pDX02->iElevator5Clamp2Off) {
			gData.sLotID_Tansfer[1] = gData.sLotID_NGBuffer;
			gData.nTrayNo_Tansfer[1] = gData.nTrayNo_NGBuffer;
			gData.nPortNo_Tansfer[1] = gData.nPortNo_NGBuffer;
			gData.sLotID_Tansfer[2]  = gData.sLotID_Tansfer[1];

//			if (!m_pDX02->iElevator5TrayExist) {
			gData.nTrayNo_NGBuffer--;
			if (gData.nTrayNo_NGBuffer < 1) {
				gData.sLotID_NGBuffer = "";
				gData.nTrayNo_NGBuffer = gData.nPortNo_NGBuffer = 0;
			}
			if (m_nElevator5Case == 20) m_nElevator5Case = 21;
			m_nTransfer2Case = 60; m_tTransfer2Loop.Set_LoopTime(5000);

			m_sLog.Format("[Transfer2: Up Buffer-NG] Lot(%s) TNo(%d) PNo(%d)", gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1]);
			g_objLogFile.Save_HandlerLog(m_sLog);
			m_tTransfer2Loop.Takt_Save(9, 16); m_tTransfer2Loop.Takt_Start(9, 17);
		}
		break;

	case 40:	//Up NG-Stage 12 (10,11)
		if ((gData.nTransferX2Pos == 10 && m_nNGStage1Case == 60) ||
			(gData.nTransferX2Pos == 11 && m_nNGStage2Case == 60) ) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 41:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			m_tTransfer2Loop.Takt_Save(9, 17); m_tTransfer2Loop.Takt_Start(9, 18);
			g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 18); m_tTransfer2Loop.Takt_Start(9, 19);
			m_pDY03->oTransferRGrabOpen = FALSE; m_pDY03->oTransferRGrabClose = TRUE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 43:
		if (!m_pDX03->iTransferRGrab1Open && m_pDX03->iTransferRGrab1Close) {
			if (!m_pDX03->iTransferRGrab2Open && m_pDX03->iTransferRGrab2Close) {
				if (!m_tTransfer2Loop.Waiting_Time(300)) break;
				m_tTransfer2Loop.Takt_Save(9, 19); m_tTransfer2Loop.Takt_Start(9, 20);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 44:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 45:
		if (m_pDX03->iTransferRTrayExist) {
			gData.sLotID_Tansfer[1] = gData.sLotID_NGTray[gData.nTransferX2Pos-10];
			gData.nTrayNo_Tansfer[1] = gData.nTrayNo_NGTray[gData.nTransferX2Pos-10];
			gData.nPortNo_Tansfer[1] = gData.nPortNo_NGTray[gData.nTransferX2Pos-10];
			gData.sLotID_Tansfer[2]  = gData.sLotID_Tansfer[1];
			gData.nNGLot_Transfer = gData.nNGLot_NGTray[gData.nTransferX2Pos-10];

			gData.sLotID_NGTray[gData.nTransferX2Pos-10] = "";
			gData.nTrayNo_NGTray[gData.nTransferX2Pos-10] = gData.nPortNo_NGTray[gData.nTransferX2Pos-10] = gData.nNGLot_NGTray[gData.nTransferX2Pos-10] = 0;

			if (m_nNGStage1Case == 60) m_nNGStage1Case = 61;
			if (m_nNGStage2Case == 60) m_nNGStage2Case = 61;
			m_nTransfer2Case = 60; m_tTransfer2Loop.Set_LoopTime(5000);

			m_sLog.Format("[Transfer2: Up NG-Stage%d] Lot(%s) TNo(%d) PNo(%d)", (gData.nTransferX2Pos-9), gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1]);
			g_objLogFile.Save_HandlerLog(m_sLog);
			m_tTransfer2Loop.Takt_Save(9, 20); m_tTransfer2Loop.Takt_Start(9, 21);
		}
		break;

	case 50:	//Up Good-Stage 12 (12,13)
		if ((gData.nTransferX2Pos == 12 && m_nGoodStage1Case == 60) ||
			(gData.nTransferX2Pos == 13 && m_nGoodStage2Case == 60) ) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		return TRUE;
	case 51:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			m_tTransfer2Loop.Takt_Save(9, 21); m_tTransfer2Loop.Takt_Start(9, 22);
			g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 52:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 22); m_tTransfer2Loop.Takt_Start(9, 23);
			m_pDY03->oTransferRGrabOpen = FALSE; m_pDY03->oTransferRGrabClose = TRUE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 53:
		if (!m_pDX03->iTransferRGrab1Open && m_pDX03->iTransferRGrab1Close) {
			if (!m_pDX03->iTransferRGrab2Open && m_pDX03->iTransferRGrab2Close) {
				if (!m_tTransfer2Loop.Waiting_Time(300)) break;
				m_tTransfer2Loop.Takt_Save(9, 23); m_tTransfer2Loop.Takt_Start(9, 24);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 54:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 55:
		if (m_pDX03->iTransferRTrayExist) {
			gData.sLotID_Tansfer[1] = gData.sLotID_GoodTray[gData.nTransferX2Pos-12];
			gData.nTrayNo_Tansfer[1] = gData.nTrayNo_GoodTray[gData.nTransferX2Pos-12];
			gData.nPortNo_Tansfer[1] = gData.nPortNo_GoodTray[gData.nTransferX2Pos-12];
			gData.sLotID_Tansfer[2]  = gData.sLotID_Tansfer[1];

			gData.sLotID_GoodTray[gData.nTransferX2Pos-12] = "";
			gData.nTrayNo_GoodTray[gData.nTransferX2Pos-12] = gData.nPortNo_GoodTray[gData.nTransferX2Pos-12] = 0;

			if (m_nGoodStage1Case == 60) m_nGoodStage1Case = 61;
			if (m_nGoodStage2Case == 60) m_nGoodStage2Case = 61;
			m_nTransfer2Case = 60; m_tTransfer2Loop.Set_LoopTime(5000);

			m_sLog.Format("[Transfer2: Up Good-Stage%d] Lot(%s) TNo(%d) PNo(%d)", (gData.nTransferX2Pos-11), gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1]);
			g_objLogFile.Save_HandlerLog(m_sLog);
			m_tTransfer2Loop.Takt_Save(9, 24); m_tTransfer2Loop.Takt_Start(9, 25);
		}
		break;

	case 60:	//Tray Down
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			gData.nTransferX2Pos = nToTran2Pos;
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 61:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			m_tTransfer2Loop.Takt_Save(9, 25); m_tTransfer2Loop.Takt_Start(9, 26);
			nPosX = nPosZ = gData.nTransferX2Pos - 4;
			double dSpeed = 1.0;
//			if (nPosX == 3 || nPosX == 4 || nPosX == 5) dSpeed = 0.7;
			if (nFmTran2Pos == 5 && nToTran2Pos == 8) nPosX = 10;	//E3->E6
			if (nFmTran2Pos == 7 && nToTran2Pos == 8) nPosX = 11;	//E5->E6
			if (nFmTran2Pos == 5 && nToTran2Pos == 9) nPosX = 12;	//E3->E7
			if (nFmTran2Pos == 7 && nToTran2Pos == 9) nPosX = 13;	//E5->E7
			g_objCommon.Move_Position(AX_TRANSFER_X2, nPosX, dSpeed);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
	case 62:
		if (g_objCommon.Check_Position(AX_TRANSFER_X2, nPosX)) {
			g_objCommon.Save_Motion(AX_TRANSFER_X2, nPosX);
			m_tTransfer2Loop.Takt_Save(9, 26); m_tTransfer2Loop.Takt_Start(9, 27);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		break;
	case 63:
		if (gData.nTransferX2Pos ==  7) m_nTransfer2Case = 70;	//Down Buffer NG (7)
		if (gData.nTransferX2Pos ==  8) m_nTransfer2Case = 75;	//Down Unload Lot 1 (8)
		if (gData.nTransferX2Pos ==  9) m_nTransfer2Case = 75;	//Down Unload Lot 2 (9)
		if (gData.nTransferX2Pos == 10) m_nTransfer2Case = 80;	//Down NG-Stage 1 (10)
		if (gData.nTransferX2Pos == 11) m_nTransfer2Case = 80;	//Down NG-Stage 2 (11)
		if (gData.nTransferX2Pos == 12) m_nTransfer2Case = 85;	//Down Good-Stage 1 (12)
		if (gData.nTransferX2Pos == 13) m_nTransfer2Case = 85;	//Down Good-Stage 2 (13)
		m_tTransfer2Loop.Set_LoopTime(30000);
		break;

	case 70:	//Down Buffer NG (7)
		if (m_nElevator5Case == 20 && gData.nElevatorOpen[5] == 0) {
			if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
				m_tTransfer2Loop.Takt_Save(9, 27); m_tTransfer2Loop.Takt_Start(9, 28);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		return TRUE;
	case 71:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 28); m_tTransfer2Loop.Takt_Start(9, 29);
			m_pDY03->oTransferRGrabOpen = TRUE; m_pDY03->oTransferRGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 72:
		if (m_pDX03->iTransferRGrab1Open && !m_pDX03->iTransferRGrab1Close) {
			if (m_pDX03->iTransferRGrab2Open && !m_pDX03->iTransferRGrab2Close) {
				if (!m_tTransfer2Loop.Waiting_Time(300)) break;
				m_tTransfer2Loop.Takt_Save(9, 29); m_tTransfer2Loop.Takt_Start(9, 30);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 73:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			if (!m_pDX03->iTransferRTrayExist) {
				g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
				m_sLog.Format("[Transfer2: Down Buffer-NG] FNo(%d) Lot(%s) TNo(%d) PNo(%d) NGLot(%d) NGBuf(%d-%d-%d)", nFmTran2Pos, gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1], gData.nNGLot_Transfer, gData.nTrayNo_NGBuffer, gMes.nMarTrayCount, gData.nMgnTrayCount);
				g_objLogFile.Save_HandlerLog(m_sLog);

				gData.sLotID_NGBuffer = gData.sLotID_Tansfer[1];
				gData.nPortNo_NGBuffer = gData.nPortNo_Tansfer[1];
				gData.nTrayNo_NGBuffer++;
				gData.nNGLot_NGBuffer = gData.nNGLot_Transfer;

				gData.sLotID_Tansfer[1] = "";
				gData.nTrayNo_Tansfer[1] = gData.nPortNo_Tansfer[1] = gData.nNGLot_Transfer = 0;

				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(5000);
				m_tTransfer2Loop.Takt_Save(9, 30); m_tTransfer2Loop.Takt_Start(9, 31);

				if (nFmTran2Pos == 6) {
					gData.nNGLot_NGBuffer = 0;

					m_sLog.Format("NG-Lot 완공 되었습니다..\nNG-Lot(%s)\nNG수량(%d) Marginal수량(%d)\n바코드 NoRead 수량(%d)", gMes.sGUItNGLotID, gMes.nGUICount[0]-gMes.nGUICount[1], gMes.nGUICount[1], gMes.nGUICount[3]);
					if (m_pEquipData->bUseMES) g_objCommon.Show_Alarm(m_sLog);
				} else {
					if (Check_LotEndNG()) {
						if (gData.nNGLot_NGBuffer == 0 && gMes.nMarTrayCount >= gData.nMgnTrayCount) {
							gData.nNGLot_NGBuffer = 1;
							g_objMesAgent.Set_NGLotEnd(gMes.sHostNGLotID, gMes.nMarCount);

							m_sLog.Format("[Transfer2_NGLot-End] NGLot(%s) NGLot(%d-%d-%d-%d) S1(%d-%d) S2(%d-%d)",
									gMes.sHostNGLotID, gMes.nMarCount, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case, gData.nNGLot_NGTray[0] , gData.nNGLot_NGTray[1]);
							g_objLogFile.Save_HandlerLog(m_sLog);
						}
					}
				}
			}
		}
		break;
	case 74:
		if (m_pDX02->iElevator5TrayExist) {
			if (m_nElevator5Case == 20) m_nElevator5Case = 21;
			m_nTransfer2Case = 95; m_tTransfer2Loop.Set_LoopTime(5000);
		}
		break;


	case 75:	//Down Unload Lot 12 (8,9)
		if ((gData.nTransferX2Pos == 8 && m_nElevator6Case == 20 && gData.nElevatorOpen[6] == 0) ||
			(gData.nTransferX2Pos == 9 && m_nElevator7Case == 20 && gData.nElevatorOpen[7] == 0) ) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 76:	//Down Unload Lot 12 (8,9)
		if ((gData.nTransferX2Pos == 8 && m_nElevator6Case == 20 && gData.nElevatorOpen[6] == 0) ||
			(gData.nTransferX2Pos == 9 && m_nElevator7Case == 20 && gData.nElevatorOpen[7] == 0) ) {
			if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
				m_tTransfer2Loop.Takt_Save(9, 31); m_tTransfer2Loop.Takt_Start(9, 32);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 77:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 32); m_tTransfer2Loop.Takt_Start(9, 33);
			m_pDY03->oTransferRGrabOpen = TRUE; m_pDY03->oTransferRGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 78:
		if (m_pDX03->iTransferRGrab1Open && !m_pDX03->iTransferRGrab1Close) {
			if (m_pDX03->iTransferRGrab2Open && !m_pDX03->iTransferRGrab2Close) {
				if (!m_tTransfer2Loop.Waiting_Time(300)) break;
				m_tTransfer2Loop.Takt_Save(9, 33); m_tTransfer2Loop.Takt_Start(9, 34);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 79:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			if (!m_pDX03->iTransferRTrayExist) {
				g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
				if (nFmTran2Pos == 12 || nFmTran2Pos == 13) {
					if (gData.nTransferX2Pos == 8) gData.nElevatGDTray[0] = 1;
					if (gData.nTransferX2Pos == 9) gData.nElevatGDTray[1] = 1;
					m_sLog.Format("[Transfer2: Down Unload-Fm%d-Lot%d-G] Lot(%s) TNo(%d) PNo(%d-%d)", nFmTran2Pos, (gData.nTransferX2Pos-7), gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1], nPort2No);
				} else {
					if (gData.nTransferX2Pos == 8) gData.nElevatGDTray[0] = 0;
					if (gData.nTransferX2Pos == 9) gData.nElevatGDTray[1] = 0;
					m_sLog.Format("[Transfer2: Down Unload-Fm%d-Lot%d-E] Lot(%s) TNo(%d) PNo(%d-%d)", nFmTran2Pos, (gData.nTransferX2Pos-7), gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1], nPort2No);
				}
				g_objLogFile.Save_HandlerLog(m_sLog);

				if (nPort2No == 0) nPort2No = gLot.nUnLastPortID;
				if (nFmTran2Pos == 12 || nFmTran2Pos == 13) gLot.nUnlGdTrayCount[nPort2No-1]++;
				else										gLot.nUnlNGTrayCount[nPort2No-1]++;
				if (nFmTran2Pos == 5)						gLot.bEmptyNGTray[nPort2No-1] = TRUE;
				else {
					if (gData.sLotID_Tansfer[1].GetLength() > 0) gLot.sUnLastLotID = gData.sLotID_Tansfer[1];
					if (gData.nPortNo_Tansfer[1] > 0)			 gLot.nUnLastPortID = gData.nPortNo_Tansfer[1];
				}

				gData.sLotID_Tansfer[1] = "";
				gData.nTrayNo_Tansfer[1] = gData.nPortNo_Tansfer[1] = 0;

				if (gData.nTransferX2Pos == 8 && m_nElevator6Case == 20) m_nElevator6Case = 21;
				if (gData.nTransferX2Pos == 9 && m_nElevator7Case == 20) m_nElevator7Case = 21;
				m_nTransfer2Case = 95; m_tTransfer2Loop.Set_LoopTime(5000);
				m_tTransfer2Loop.Takt_Save(9, 34); m_tTransfer2Loop.Takt_Start(9, 35);

				if (Check_LotEndTray(gLot.sUnLastLotID, nPort2No)) {
					if (nFmTran2Pos == 12 || nFmTran2Pos == 13) {
						if (gData.nTransferX2Pos == 8) gData.nElevatGDTray[0] = 2;
						if (gData.nTransferX2Pos == 9) gData.nElevatGDTray[1] = 2;
					}

					if (gLot.bEmptyNGTray[nPort2No-1]) {
						gLot.nUnLastPortID = nPort2No;
						gLot.sUnLastLotID = gLot.sLotID[nPort2No-1];
						gData.bInpectLotEnd = FALSE;
						g_objInspector.Set_LotEnd(INSPECTOR_ALL, gLot.sLotID[nPort2No-1], nPort2No);

						if (!m_pEquipData->bUseBottom && !m_pEquipData->bUseBotAng && !m_pEquipData->bUseTop1 && !m_pEquipData->bUseTopAng && !m_pEquipData->bUseTop2) {
							gData.bInpectLotEnd = TRUE;
						}
						if (!m_pEquipData->bUseMES) gData.bInpectLotEnd = TRUE;

						m_nTransfer2Case = 94; m_tTransfer2Loop.Set_LoopTime(60000);
					}
				}
			}
		}
		break;

	case 80:	//Down NG-Stage 12 (10,11)
		if ((gData.nTransferX2Pos == 10 && m_nNGStage1Case == 0) ||
			(gData.nTransferX2Pos == 11 && m_nNGStage2Case == 0) ) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 81:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			m_tTransfer2Loop.Takt_Save(9, 35); m_tTransfer2Loop.Takt_Start(9, 36);
			g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 82:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 36); m_tTransfer2Loop.Takt_Start(9, 37);
			m_pDY03->oTransferRGrabOpen = TRUE; m_pDY03->oTransferRGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 83:
		if (m_pDX03->iTransferRGrab1Open && !m_pDX03->iTransferRGrab1Close) {
			if (m_pDX03->iTransferRGrab2Open && !m_pDX03->iTransferRGrab2Close) {
				if (!m_tTransfer2Loop.Waiting_Time(300)) break;
				m_tTransfer2Loop.Takt_Save(9, 37); m_tTransfer2Loop.Takt_Start(9, 38);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 84:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			if (!m_pDX03->iTransferRTrayExist) {
				g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
				m_sLog.Format("[Transfer2: Down NG-Stage%d] Lot(%s) TNo(%d) PNo(%d)", (gData.nTransferX2Pos-9), gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1]);
				g_objLogFile.Save_HandlerLog(m_sLog);
				
				gData.sLotID_NGTray[gData.nTransferX2Pos-10] = gData.sLotID_Tansfer[1];
				gData.nTrayNo_NGTray[gData.nTransferX2Pos-10] = gData.nTrayNo_Tansfer[1];
				gData.nPortNo_NGTray[gData.nTransferX2Pos-10] = gData.nPortNo_Tansfer[1];
				gData.sLotID_NGTray[2] = gData.sLotID_NGTray[gData.nTransferX2Pos-10];

				gData.sLotID_Tansfer[1] = "";
				gData.nTrayNo_Tansfer[1] = gData.nPortNo_Tansfer[1] = 0;

				if (!Check_ModuleEmpty()) {
					if (m_nNGStage1Case == 0) m_nNGStage1Case = 1;
					if (m_nNGStage2Case == 0) m_nNGStage2Case = 1;
				}
				m_nTransfer2Case = 95; m_tTransfer2Loop.Set_LoopTime(5000);
				m_tTransfer2Loop.Takt_Save(9, 38); m_tTransfer2Loop.Takt_Start(9, 39);
			}
		}
		break;

	case 85:	//Down Good-Stage 12 (12,13)
		if ((gData.nTransferX2Pos == 12 && m_nGoodStage1Case == 0) ||
			(gData.nTransferX2Pos == 13 && m_nGoodStage2Case == 0) ) {
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 86:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			m_tTransfer2Loop.Takt_Save(9, 39); m_tTransfer2Loop.Takt_Start(9, 40);
			g_objCommon.Move_Position(AX_TRANSFER_Z2, nPosZ);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 87:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, nPosZ)) {
			g_objCommon.Save_Motion(AX_TRANSFER_Z2, nPosZ);
			m_tTransfer2Loop.Takt_Save(9, 40); m_tTransfer2Loop.Takt_Start(9, 41);
			m_pDY03->oTransferRGrabOpen = TRUE; m_pDY03->oTransferRGrabClose = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
		}
		break;
	case 88:
		if (m_pDX03->iTransferRGrab1Open && !m_pDX03->iTransferRGrab1Close) {
			if (m_pDX03->iTransferRGrab2Open && !m_pDX03->iTransferRGrab2Close) {
				if (!m_tTransfer2Loop.Waiting_Time(300)) break;
				m_tTransfer2Loop.Takt_Save(9, 41); m_tTransfer2Loop.Takt_Start(9, 42);
				g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
				m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 89:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
			if (!m_pDX03->iTransferRTrayExist) {
				g_objCommon.Save_Motion(AX_TRANSFER_Z2, 0);
				m_sLog.Format("[Transfer2: Down Good-Stage%d] Lot(%s) TNo(%d) PNo(%d)", (gData.nTransferX2Pos-11), gData.sLotID_Tansfer[1], gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1]);
				g_objLogFile.Save_HandlerLog(m_sLog);
	
				gData.sLotID_GoodTray[gData.nTransferX2Pos-12] = gData.sLotID_Tansfer[1];
				gData.nTrayNo_GoodTray[gData.nTransferX2Pos-12] = gData.nTrayNo_Tansfer[1];
				gData.nPortNo_GoodTray[gData.nTransferX2Pos-12] = gData.nPortNo_Tansfer[1];
				gData.sLotID_GoodTray[2] = gData.sLotID_GoodTray[gData.nTransferX2Pos-12];

				gData.sLotID_Tansfer[1] = "";
				gData.nTrayNo_Tansfer[1] = gData.nPortNo_Tansfer[1] = 0;

				if (!Check_ModuleEmpty()) {
					if (m_nGoodStage1Case == 0) m_nGoodStage1Case = 1;
					if (m_nGoodStage2Case == 0) m_nGoodStage2Case = 1;
				}
				m_nTransfer2Case = 95; m_tTransfer2Loop.Set_LoopTime(5000);
				m_tTransfer2Loop.Takt_Save(9, 42); m_tTransfer2Loop.Takt_Start(9, 43);
			}
		}
		break;

	case 94:	//LotEnd
		if (gData.bInpectLotEnd || gData.bUseDryRun || gData.bCycleStop) {
			Set_LotEnd(gLot.sUnLastLotID, gLot.nUnLastPortID);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(5000);
		}
		break;

//	gData.nTransferX2Pos;	//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)
	case 95:	//대기위치로
		if (Check_Transfer2(nFmTran2Pos, nToTran2Pos, nPort2No)) {
			m_tTransfer2Loop.Takt_Save(9, 43, TRUE);
			m_nTransfer2Case = 0; m_tTransfer2Loop.Set_LoopTime(5000);
		} else {
			if		(m_pDX12->iGoodStage1TrayExist && m_pDX12->iGoodStage2TrayExist) { nPosX = 8; gData.nTransferX2Pos = 12; }
			else if (m_pDX11->iNGStage1TrayExist   && m_pDX11->iNGStage2TrayExist)	 { nPosX = 6; gData.nTransferX2Pos = 10; }
			else																	 { nPosX = 3; gData.nTransferX2Pos =  7; }
			g_objCommon.Move_Position(AX_TRANSFER_X2, nPosX);
			m_nTransfer2Case++; m_tTransfer2Loop.Set_LoopTime(30000);
		}
		break;
	case 96:
		if (g_objCommon.Check_Position(AX_TRANSFER_X2, nPosX)) {
			g_objCommon.Save_Motion(AX_TRANSFER_X2, nPosX);
			m_tTransfer2Loop.Takt_Save(9, 43, TRUE);
			m_nTransfer2Case = 0; m_tTransfer2Loop.Set_LoopTime(5000);
		}
		break;

	}

	//  9. (Error : 3500)
	if (m_tTransfer2Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(3500 + m_nTransfer2Case);
		return FALSE;
	}
	return TRUE;
}

// 10. (Error : 4000)
BOOL CSequenceMain::Run_LoadStage1()
{
	static int nStageNo1 = 0, nPortNo1;	//0고정

	switch (m_nLoadStage1Case) {
	case 0:	// Wait
		m_tLoadStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (m_pDX04->iLoadStage1TrayExist) {
			gNG->nTrayOX[0][0] = 1;
			m_tLoadStage1Loop.Takt_Start(10, 1, TRUE);
			m_pDY04->oLoadStage1MasterIn = TRUE; m_pDY04->oLoadStage1MasterOut = FALSE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 2:
		if (m_pDX04->iLoadStage1MasterIn && !m_pDX04->iLoadStage1MasterOut) {
			m_tLoadStage1Loop.Takt_Save(10, 1); m_tLoadStage1Loop.Takt_Start(10, 2);
			m_pDY04->oLoadStage1SlaveIn = TRUE; m_pDY04->oLoadStage1SlaveOut = FALSE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if (m_pDX04->iLoadStage1SlaveIn && !m_pDX04->iLoadStage1SlaveOut) {
			m_tLoadStage1Loop.Takt_Save(10, 2); m_tLoadStage1Loop.Takt_Start(10, 3);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if (m_pDX04->iLoadStage1Up && !m_pDX04->iLoadStage1Down) {
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 5:	//Inspection Start
		if (m_pDX04->iLoadStage1TrayExist) 
		{
			nPortNo1 = m_nRcpPortNo = gData.nPortNo_LoadStage[nStageNo1] - 1;
			if (gLot.nLotStatus[nPortNo1] == 0)
			{
				gLot.nLotStatus[nPortNo1] = 1;
				gData.sReadyRecipe = gLot.sRecipeName[nPortNo1];
				g_objInspector.Set_LotReadyFalse();
				g_objInspector.Set_LotStart(INSPECTOR_ALL, gLot.sLotID[nPortNo1], nPortNo1+1, gLot.nTrayCount[nPortNo1]-1, gLot.nCmCount[nPortNo1], gLot.sRecipeName[nPortNo1], m_pEquipData->sPROG_VER, m_pEquipData->sPARA_VER, m_pEquipData->bUseCosmeticNG);
				m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(180000);
			}
			else
			{
				m_nLoadStage1Case = 10; m_tLoadStage1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 6:
		if (g_objInspector.Check_LotReady())
		{
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 7:	//Align Wait
		if (Check_LotRun(nStageNo1, nPortNo1+1)) m_nLoadStage1Case = 10;
		gData.nLoadAlignRetry = 0; m_tLoadStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 10:	//Align Wait
		if (m_nLoadStage2Case >= 30)
		{
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 11:
		if (m_pDX04->iLoadStage1Up && !m_pDX04->iLoadStage1Down) 
		{
			m_tLoadStage1Loop.Takt_Save(10, 3); m_tLoadStage1Loop.Takt_Start(10, 4);
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 3);	//Aling1
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 3)) 
		{
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, 3);
			m_tLoadStage1Loop.Takt_Save(10, 4); m_tLoadStage1Loop.Takt_Start(10, 5);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		break;

	case 13:
		if (gNG->nTrayOX[0][0] == 0 || (gNG->nTrayOX[0][0] == 1 && m_pDX04->iLoadStage1TrayExist)) {
			if (!m_pEquipData->bUseAlign1 || gNG->nTrayOX[0][0] == 0) {
				if (gNG->nTrayOX[0][0] == 1) Set_AlignData(gData.nPortNo_LoadStage[nStageNo1]);
				g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 5);	//Aling3
				m_nLoadStage1Case = 19; m_tLoadStage1Loop.Set_LoopTime(30000);
			} else {
				Init_AlignTray();
				gData.bAlignScanDone = FALSE;
				g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A1", gData.sLotID_LoadStage[nStageNo1], gData.nPortNo_LoadStage[nStageNo1], gData.nTrayNo_LoadStage[nStageNo1], 1);
				m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 14:
		if (gData.bAlignScanDone) {
			if (!m_tLoadStage1Loop.Waiting_Time(m_pEquipData->nDelayTime[5])) break;
			m_tLoadStage1Loop.Takt_Save(10, 5); m_tLoadStage1Loop.Takt_Start(10, 6);
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 4);	//Aling2
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(10000);
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 4)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, 4);
			m_tLoadStage1Loop.Takt_Save(10, 6); m_tLoadStage1Loop.Takt_Start(10, 7);
			gData.bAlignScanDone = FALSE;
			g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A1", gData.sLotID_LoadStage[nStageNo1], gData.nPortNo_LoadStage[nStageNo1], gData.nTrayNo_LoadStage[nStageNo1], 2);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(10000);
		}
		break;
	case 16:
		if (gData.bAlignScanDone) {
			if (!m_tLoadStage1Loop.Waiting_Time(m_pEquipData->nDelayTime[5])) break;
			m_tLoadStage1Loop.Takt_Save(10, 7); m_tLoadStage1Loop.Takt_Start(10, 8);
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 5);	//Aling3
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(10000);
		}
		break;
	case 17:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 5)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, 5);
			m_tLoadStage1Loop.Takt_Save(10, 8); m_tLoadStage1Loop.Takt_Start(10, 9);
			gData.bAlignScanDone = gData.bAlignA1Done = FALSE;
			g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A1", gData.sLotID_LoadStage[nStageNo1], gData.nPortNo_LoadStage[nStageNo1], gData.nTrayNo_LoadStage[nStageNo1], 3);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(10000);
		}
		break;
	case 18:
		if (gData.bAlignA1Done) {
			if (!m_tLoadStage1Loop.Waiting_Time(m_pEquipData->nDelayTime[5])) break;
			Check_AlignDataAdd(gData.nPortNo_LoadStage[nStageNo1]);

			m_tLoadStage1Loop.Takt_Save(10, 9); m_tLoadStage1Loop.Takt_Start(10, 10);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 19:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 5)) {
			if (gNG->nTrayOX[0][0] == 1) {
				if (Check_AlignData(gData.nPortNo_LoadStage[nStageNo1])) {
					g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, 5);
					m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
				}
			} else {
				g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, 5);
				m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 20:	//Align Wait
		if (m_nLoadStage2Case > 20 && m_nLoadStage2Case < 40) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 1);	//Wait
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		} else if (m_nLoadStage2Case < 20 || m_nLoadStage2Case >= 40) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 2);	//Unload
			m_nLoadStage1Case = 23; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 21:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 1)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, 1);
			m_tLoadStage1Loop.Takt_Save(10, 10); m_tLoadStage1Loop.Takt_Start(10, 11);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 22:	//Align Wait
		if (m_nLoadStage2Case < 20 || m_nLoadStage2Case >= 40) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 2);	//Unload
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 23:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 2)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, 2);
			m_tLoadStage1Loop.Takt_Save(10, 11); m_tLoadStage1Loop.Takt_Start(10, 12);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 24:
		if (gNG->nTrayOX[0][0] == 0 || (gNG->nTrayOX[0][0] == 1 && m_pDX04->iLoadStage1TrayExist)) {
			Set_AlignToStage(gData.nPortNo_LoadStage[nStageNo1]);
			m_nLoadStage1Case = 30; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	// Load Picker Wait
		m_tLoadStage1Loop.Set_LoopTime(5000);
		return TRUE;
	case 31:
		if (m_nLoadStage2Case < 30 || m_nLoadStage2Case >= 50) {
			m_tLoadStage1Loop.Takt_Save(10, 12); m_tLoadStage1Loop.Takt_Start(10, 13);
			m_pDY04->oLoadStage1Up = FALSE; m_pDY04->oLoadStage1Down = TRUE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(10000);
		}
		return TRUE;
	case 32:
		if (!m_pDX04->iLoadStage1Up && m_pDX04->iLoadStage1Down) {
			m_tLoadStage1Loop.Takt_Save(10, 13); m_tLoadStage1Loop.Takt_Start(10, 14);
			m_nLoadStage1Case = 40; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		break;

	case 40:	//Up Wait
		if (m_nLoadStage2Case < 40 || m_nLoadStage2Case >= 60) {
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 41:
		if (!m_pDX04->iLoadStage1Up && m_pDX04->iLoadStage1Down) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 0);	//load
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 0)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, 0);
			m_tLoadStage1Loop.Takt_Save(10, 14); m_tLoadStage1Loop.Takt_Start(10, 15);
			m_nLoadStage1Case = 50; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 50:	//Align후
		if (m_nLoadStage2Case >= 30 && m_nLoadStage2Case < 50) {
			m_tLoadStage1Loop.Takt_Save(10, 15); m_tLoadStage1Loop.Takt_Start(10, 16);
			m_pDY04->oLoadStage1Up = TRUE; m_pDY04->oLoadStage1Down = FALSE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 51:
		if (m_pDX04->iLoadStage1Up && !m_pDX04->iLoadStage1Down) {
			m_tLoadStage1Loop.Takt_Save(10, 16); m_tLoadStage1Loop.Takt_Start(10, 17);
			m_pDY04->oLoadStage1SlaveIn = FALSE; m_pDY04->oLoadStage1SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 52:
		if (!m_pDX04->iLoadStage1SlaveIn && m_pDX04->iLoadStage1SlaveOut) {
			m_tLoadStage1Loop.Takt_Save(10, 17); m_tLoadStage1Loop.Takt_Start(10, 18);
			m_pDY04->oLoadStage1MasterIn = FALSE; m_pDY04->oLoadStage1MasterOut = TRUE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 53:
		if (!m_pDX04->iLoadStage1MasterIn && m_pDX04->iLoadStage1MasterOut) {
			m_tLoadStage1Loop.Takt_Save(10, 18); m_tLoadStage1Loop.Takt_Start(10, 19);
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 54:
		if (gNG->nTrayOX[0][0] == 1) {
			m_nLoadStage1Case++; m_tLoadStage1Loop.Set_LoopTime(30000);
		} else {
			m_tLoadStage1Loop.Takt_Save(10, 19, TRUE);
			m_nLoadStage1Case = 0; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 55:
		if (m_pDX04->iLoadStage1TrayExist) {
			m_nLoadStage1Case = 60; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		break;

	case 60:	// Transfer Picker Wait
		m_tLoadStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 61:
		if (!m_pDX04->iLoadStage1TrayExist) {
			gNG->nTrayOX[0][0] = 0;
			m_tLoadStage1Loop.Takt_Save(10, 19, TRUE);
			m_nLoadStage1Case = 0; m_tLoadStage1Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 10. (Error : 4000)
	if (m_tLoadStage1Loop.Over_LoopTime()) {
		if (m_nLoadStage1Case == 6) gLot.nLotStatus[nPortNo1] = 0;
		g_objCommon.Show_Error(4000 + m_nLoadStage1Case);
		return FALSE;
	}
	return TRUE;
}

// 11. (Error : 4500)
BOOL CSequenceMain::Run_LoadStage2()
{
	static int nStageNo2 = 1, nPortNo2;	//1고정

	switch (m_nLoadStage2Case) {
	case 0:	// Wait
		m_tLoadStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (m_pDX04->iLoadStage2TrayExist) {
			gNG->nTrayOX[0][1] = 1;
			m_tLoadStage2Loop.Takt_Start(11, 1, TRUE);
			m_pDY04->oLoadStage2MasterIn = TRUE; m_pDY04->oLoadStage2MasterOut = FALSE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 2:
		if (m_pDX04->iLoadStage2MasterIn && !m_pDX04->iLoadStage2MasterOut) {
			m_tLoadStage2Loop.Takt_Save(11, 1); m_tLoadStage2Loop.Takt_Start(11, 2);
			m_pDY04->oLoadStage2SlaveIn = TRUE; m_pDY04->oLoadStage2SlaveOut = FALSE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if (m_pDX04->iLoadStage2SlaveIn && !m_pDX04->iLoadStage2SlaveOut) {
			m_tLoadStage2Loop.Takt_Save(11, 2); m_tLoadStage2Loop.Takt_Start(11, 3);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if (m_pDX04->iLoadStage2Up && !m_pDX04->iLoadStage2Down) {
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 5:	//Inspection Start
		if (m_pDX04->iLoadStage2TrayExist) {
			nPortNo2 = m_nRcpPortNo = gData.nPortNo_LoadStage[nStageNo2] - 1;
			if (gLot.nLotStatus[nPortNo2] == 0) {
				gLot.nLotStatus[nPortNo2] = 1;
				gData.sReadyRecipe = gLot.sRecipeName[nStageNo2];
				g_objInspector.Set_LotReadyFalse();
				g_objInspector.Set_LotStart(INSPECTOR_ALL, gLot.sLotID[nPortNo2], nPortNo2+1, gLot.nTrayCount[nPortNo2]-1, gLot.nCmCount[nPortNo2], gLot.sRecipeName[nPortNo2], m_pEquipData->sPROG_VER, m_pEquipData->sPARA_VER, m_pEquipData->bUseCosmeticNG);
				m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(180000);
			} else {
				m_nLoadStage2Case = 10; m_tLoadStage2Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 6:
		if (g_objInspector.Check_LotReady()) {
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 7:	//Align Wait
		if (Check_LotRun(nStageNo2, nPortNo2+1)) m_nLoadStage2Case = 10;
		gData.nLoadAlignRetry = 0; m_tLoadStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 10:	//Align Wait
		if (m_nLoadStage1Case >= 30) {
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 11:
		if (m_pDX04->iLoadStage2Up && !m_pDX04->iLoadStage2Down) {
			m_tLoadStage2Loop.Takt_Save(11, 3); m_tLoadStage2Loop.Takt_Start(11, 4);
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 3);	//Aling1
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 3)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, 3);
			m_tLoadStage2Loop.Takt_Save(11, 4); m_tLoadStage2Loop.Takt_Start(11, 5);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		break;

	case 13:
		if (gNG->nTrayOX[0][1] == 0 || (gNG->nTrayOX[0][1] == 1 && m_pDX04->iLoadStage2TrayExist)) {
			if (!m_pEquipData->bUseAlign1 || gNG->nTrayOX[0][1] == 0) {
				if (gNG->nTrayOX[0][1] == 1) Set_AlignData(gData.nPortNo_LoadStage[nStageNo2]);
				g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 5);	//Aling3
				m_nLoadStage2Case = 19; m_tLoadStage2Loop.Set_LoopTime(30000);
			} else {
				Init_AlignTray();
				gData.bAlignScanDone = FALSE;
				g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A1", gData.sLotID_LoadStage[nStageNo2], gData.nPortNo_LoadStage[nStageNo2], gData.nTrayNo_LoadStage[nStageNo2], 1);
				m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 14:
		if (gData.bAlignScanDone) {
			if (!m_tLoadStage2Loop.Waiting_Time(m_pEquipData->nDelayTime[5])) break;
			m_tLoadStage2Loop.Takt_Save(11, 5); m_tLoadStage2Loop.Takt_Start(11, 6);
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 4);	//Aling2
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 4)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, 4);
			m_tLoadStage2Loop.Takt_Save(11, 6); m_tLoadStage2Loop.Takt_Start(11, 7);
			gData.bAlignScanDone = FALSE;
			g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A1", gData.sLotID_LoadStage[nStageNo2], gData.nPortNo_LoadStage[nStageNo2], gData.nTrayNo_LoadStage[nStageNo2], 2);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 16:
		if (gData.bAlignScanDone) {
			if (!m_tLoadStage2Loop.Waiting_Time(m_pEquipData->nDelayTime[5])) break;
			m_tLoadStage2Loop.Takt_Save(11, 7); m_tLoadStage2Loop.Takt_Start(11, 8);
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 5);	//Aling3
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 17:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 5)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, 5);
			m_tLoadStage2Loop.Takt_Save(11, 8); m_tLoadStage2Loop.Takt_Start(11, 9);
			gData.bAlignScanDone = gData.bAlignA1Done = FALSE;
			g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A1", gData.sLotID_LoadStage[nStageNo2], gData.nPortNo_LoadStage[nStageNo2], gData.nTrayNo_LoadStage[nStageNo2], 3);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 18:
		if (gData.bAlignA1Done) {
			if (!m_tLoadStage2Loop.Waiting_Time(m_pEquipData->nDelayTime[5])) break;
			Check_AlignDataAdd(gData.nPortNo_LoadStage[nStageNo2]);

			m_tLoadStage2Loop.Takt_Save(11, 9); m_tLoadStage2Loop.Takt_Start(11, 10);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 19:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 5)) {
			if (gNG->nTrayOX[0][1] == 1) {
				if (Check_AlignData(gData.nPortNo_LoadStage[nStageNo2])) {
					g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, 5);
					m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
				}
			} else {
				g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, 5);
				m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 20:	//Align Wait
		if (m_nLoadStage1Case > 20 && m_nLoadStage1Case < 40) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 1);	//Wait
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		} else if (m_nLoadStage1Case < 20 || m_nLoadStage1Case >= 40) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 2);	//Unload
			m_nLoadStage2Case = 23; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 21:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 1)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, 1);
			m_tLoadStage2Loop.Takt_Save(11, 10); m_tLoadStage2Loop.Takt_Start(11, 11);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 22:	//Align Wait
		if (m_nLoadStage1Case < 20 || m_nLoadStage1Case >= 40) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 2);	//Unload
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 23:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 2)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, 2);
			m_tLoadStage2Loop.Takt_Save(11, 11); m_tLoadStage2Loop.Takt_Start(11, 12);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 24:
		if (gNG->nTrayOX[0][1] == 0 || (gNG->nTrayOX[0][1] == 1 && m_pDX04->iLoadStage2TrayExist)) {
			Set_AlignToStage(gData.nPortNo_LoadStage[nStageNo2]);
			m_nLoadStage2Case = 30; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	// Load Picker Wait
		m_tLoadStage2Loop.Set_LoopTime(5000);
		return TRUE;
	case 31:
		if (m_nLoadStage1Case < 30 || m_nLoadStage1Case >= 50) {
			m_tLoadStage2Loop.Takt_Save(11, 12); m_tLoadStage2Loop.Takt_Start(11, 13);
			m_pDY04->oLoadStage2Up = FALSE; m_pDY04->oLoadStage2Down = TRUE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(10000);
		}
		return TRUE;
	case 32:
		if (!m_pDX04->iLoadStage2Up && m_pDX04->iLoadStage2Down) {
			m_tLoadStage2Loop.Takt_Save(11, 13); m_tLoadStage2Loop.Takt_Start(11, 14);
			m_nLoadStage2Case = 40; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		break;

	case 40:	//Up Wait
		if (m_nLoadStage1Case < 40 || m_nLoadStage1Case >= 60) {
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 41:
		if (!m_pDX04->iLoadStage2Up && m_pDX04->iLoadStage2Down) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 0);	//load
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 0)) {
			g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, 0);
			m_tLoadStage2Loop.Takt_Save(11, 14); m_tLoadStage2Loop.Takt_Start(11, 15);
			m_nLoadStage2Case = 50; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 50:	//Align후
		if (m_nLoadStage1Case >= 30 && m_nLoadStage1Case < 50) {
			m_tLoadStage2Loop.Takt_Save(11, 15); m_tLoadStage2Loop.Takt_Start(11, 16);
			m_pDY04->oLoadStage2Up = TRUE; m_pDY04->oLoadStage2Down = FALSE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 51:
		if (m_pDX04->iLoadStage2Up && !m_pDX04->iLoadStage2Down) {
			m_tLoadStage2Loop.Takt_Save(11, 16); m_tLoadStage2Loop.Takt_Start(11, 17);
			m_pDY04->oLoadStage2SlaveIn = FALSE; m_pDY04->oLoadStage2SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 52:
		if (!m_pDX04->iLoadStage2SlaveIn && m_pDX04->iLoadStage2SlaveOut) {
			m_tLoadStage2Loop.Takt_Save(11, 17); m_tLoadStage2Loop.Takt_Start(11, 18);
			m_pDY04->oLoadStage2MasterIn = FALSE; m_pDY04->oLoadStage2MasterOut = TRUE;
			g_objAJinAXL.Write_Output(4);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 53:
		if (!m_pDX04->iLoadStage2MasterIn && m_pDX04->iLoadStage2MasterOut) {
			m_tLoadStage2Loop.Takt_Save(11, 18); m_tLoadStage2Loop.Takt_Start(11, 19);
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 54:
		if (gNG->nTrayOX[0][1] == 1) {
			m_nLoadStage2Case++; m_tLoadStage2Loop.Set_LoopTime(30000);
		} else {
			m_tLoadStage2Loop.Takt_Save(11, 19, TRUE);
			m_nLoadStage2Case = 0; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 55:
		if (m_pDX04->iLoadStage2TrayExist) {
			m_nLoadStage2Case = 60; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		break;

	case 60:	// Transfer Picker Wait
		m_tLoadStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 61:
		if (!m_pDX04->iLoadStage2TrayExist) {
			gNG->nTrayOX[0][1] = 0;
			m_tLoadStage2Loop.Takt_Save(11, 19, TRUE);
			m_nLoadStage2Case = 0; m_tLoadStage2Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 11. (Error : 4500)
	if (m_tLoadStage2Loop.Over_LoopTime()) {
		if (m_nLoadStage2Case == 6) gLot.nLotStatus[nPortNo2] = 0;
		g_objCommon.Show_Error(4500 + m_nLoadStage2Case);
		return FALSE;
	}
	return TRUE;
}

// 12. (Error : 5000)
BOOL CSequenceMain::Run_LoadPicker1()
{
	static int n1No = 1;			//1(고정)
	static int nLPStage1No = 0;	//1,2
	static int nLoad1PosY = 0;	//1~10
	static int n1BTMNo, n1CMno1, n1CMno5, n1LPVisionNo, n1LP, n1LT, n1LM, nL1Retry;
	static double dLPStage1PosY = 0, dLPStage1PosX = 0;

	switch (m_nLoadPicker1Case) {
	case 0:	// Wait
		if (m_nLoadStage1Case == 30 && !m_pDX04->iLoadStage1TrayExist && Check_EmptyLoadTray()) m_nLoadStage1Case = 31;
		if (m_nLoadStage2Case == 30 && !m_pDX04->iLoadStage2TrayExist && Check_EmptyLoadTray()) m_nLoadStage2Case = 31;
		if (m_nLoadStage1Case == 31 || m_nLoadStage2Case == 31) {
			m_sLog.Format("[LoadPicker1: Start] Empty - Seq(%d-%d)", m_nLoadStage1Case, m_nLoadStage2Case);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		if (m_nLoadStage1Case == 30 || m_nLoadStage2Case == 30) {
			if (m_nLoadStage1Case == 30) nLPStage1No = 1;
			if (m_nLoadStage2Case == 30) nLPStage1No = 2;
			g_objCommon.Set_LoadPickerUp(n1No);	gData.nLPCount1 = 0;
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 0);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(5000);

			m_sLog.Format("[LoadPicker1: Start] StageNo(%d)", nLPStage1No);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		return TRUE;

	case 1:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) 
		{
			if (g_objCommon.Get_LoadPickerUp(n1No)) 
			{
				g_objCommon.Move_Position(AX_LOAD_PICKER_X1, nLPStage1No);
				g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, nLPStage1No);
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 2:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X1, nLPStage1No) && g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, nLPStage1No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_X1, nLPStage1No);	g_objCommon.Save_Motion(AX_LOAD_PICKER_Y1, nLPStage1No);
			g_objCommon.Set_LoadPickerOpen(n1No);	nLoad1PosY = 0;
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(10000);
		}
		break;
	case 3:
		if (Check_LoadModule(nLoad1PosY)) 
		{
			m_tLoadPicker1Loop.Takt_Start(12, 1, TRUE);
			if (nLPStage1No == 1) {
				dLPStage1PosY = m_pMoveData->dLoadStageY1[2] + (m_pEquipData->dTrayPitchY * (nLoad1PosY - 1));
				g_objAJinAXL.Move_Absolute(AX_LOAD_STAGE_Y1, dLPStage1PosY);
			}
			if (nLPStage1No == 2) {
				dLPStage1PosY = m_pMoveData->dLoadStageY2[2] + (m_pEquipData->dTrayPitchY * (nLoad1PosY - 1));
				g_objAJinAXL.Move_Absolute(AX_LOAD_STAGE_Y2, dLPStage1PosY);
			}
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		} 
		else 
		{
			gData.sLotID_LoadStage[nLPStage1No-1]  = "";
			gData.nTrayNo_LoadStage[nLPStage1No-1] = gData.nPortNo_LoadStage[nLPStage1No-1] = 0;

			if (m_nLoadStage1Case == 30) m_nLoadStage1Case = 31;
			if (m_nLoadStage2Case == 30) m_nLoadStage2Case = 31;
			m_nLoadPicker1Case = 0; m_tLoadPicker1Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if ((nLPStage1No == 1 && g_objAJinAXL.Is_MoveDone(AX_LOAD_STAGE_Y1, dLPStage1PosY)) ||
			(nLPStage1No == 2 && g_objAJinAXL.Is_MoveDone(AX_LOAD_STAGE_Y2, dLPStage1PosY)) ) {
			if (nLPStage1No == 1) g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, -1, dLPStage1PosY);
			if (nLPStage1No == 2) g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, -1, dLPStage1PosY);
			m_tLoadPicker1Loop.Takt_Save(12, 1); m_tLoadPicker1Loop.Takt_Start(12, 2);
			g_objCommon.Set_LoadPickerDown(n1No, 1);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objCommon.Get_LoadPickerDown(n1No, 1)) {
			m_tLoadPicker1Loop.Takt_Save(12, 2); m_tLoadPicker1Loop.Takt_Start(12, 3);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, nLPStage1No);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 6:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, nLPStage1No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, nLPStage1No);
			m_tLoadPicker1Loop.Takt_Save(12, 3); m_tLoadPicker1Loop.Takt_Start(12, 4);
			gData.sLotID_LoadPicker[n1No-1]  = gData.sLotID_LoadStage[nLPStage1No-1];
			gData.nTrayNo_LoadPicker[n1No-1] = gData.nTrayNo_LoadStage[nLPStage1No-1];
			gData.nPortNo_LoadPicker[n1No-1] = gData.nPortNo_LoadStage[nLPStage1No-1];
			gData.sLotID_LoadPicker[2]		 = gData.sLotID_LoadPicker[n1No-1];

			for(int i=0; i<4; i++) {
				gData.InfoLoadPick[n1No-1][i] = gData.InfoLoadTray[nLoad1PosY-1][i];	gData.InfoLoadTray[nLoad1PosY-1][i] = 0;
			}
			gData.InfoLoadPick[n1No-1][9] = ((nLoad1PosY-1) * 4) + 1;

			n1LP = gData.nPortNo_LoadPicker[n1No-1] - 1;
			n1LT = gData.nTrayNo_LoadPicker[n1No-1] - 1;
			n1LM = gData.InfoLoadPick[n1No-1][9] - 1;
			for(int i=0; i<4; i++) {
				if (gData.InfoLoadPick[n1No-1][i] > 0) gLot.nTrayPutCnt[n1LP][2]++;
				gLot.nHistory[n1LP][n1LT][n1LM+i][0] = nLPStage1No;
				gLot.nHistory[n1LP][n1LT][n1LM+i][1] = 1;
				gLot.nHistory[n1LP][n1LT][n1LM+i][2] = i + 1;
			}

			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 7:
		if (g_objCommon.Get_LoadPickerDown(n1No, 1)) {
			g_objCommon.Set_LoadPickerClose(n1No, 1);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 8:
		if (g_objCommon.Get_LoadPickerClose(n1No, 1)) {
			if (!m_tLoadPicker1Loop.Waiting_Time(m_pEquipData->nDelayTime[1])) break;
			m_tLoadPicker1Loop.Takt_Save(12, 4); m_tLoadPicker1Loop.Takt_Start(12, 5);
			g_objCommon.Set_LoadPickerUp(n1No);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 0);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 9:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) {
			if (g_objCommon.Get_LoadPickerUp(n1No)) {
				g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, 0);
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(m_pEquipData->nDelayTime[10]);
			}
		}
		break;
	case 10:
		if (g_objCommon.Get_LoadPickerCheck(n1No, 9, 0, gData.InfoLoadPick[n1No-1])) {
			if (Check_LoadModule(nLoad1PosY)) {
				m_tLoadPicker1Loop.Takt_Save(12, 5); m_tLoadPicker1Loop.Takt_Start(12, 6);
				if (nLPStage1No == 1) {
					dLPStage1PosY = m_pMoveData->dLoadStageY1[2] + (m_pEquipData->dTrayPitchY * (nLoad1PosY - 1));
					g_objAJinAXL.Move_Absolute(AX_LOAD_STAGE_Y1, dLPStage1PosY);
				}
				if (nLPStage1No == 2) {
					dLPStage1PosY = m_pMoveData->dLoadStageY2[2] + (m_pEquipData->dTrayPitchY * (nLoad1PosY - 1));
					g_objAJinAXL.Move_Absolute(AX_LOAD_STAGE_Y2, dLPStage1PosY);
				}
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
			} else {
				m_nLoadPicker1Case = 18; m_tLoadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 11:
		if ((m_nLoadPicker2Case > 41 && m_nLoadPicker2Case < 80) ||
			(m_nLoadPicker2Case > 33 && m_nLoadPicker2Case < 80 && gData.nLPCount2 >= 4) ) {
			m_tLoadPicker1Loop.Takt_Save(12, 6); m_tLoadPicker1Loop.Takt_Start(12, 7);
			dLPStage1PosX = m_pMoveData->dLoadPickerX1[nLPStage1No] + (m_pEquipData->dTrayPitchX * 4);
			g_objAJinAXL.Move_Absolute(AX_LOAD_PICKER_X1, dLPStage1PosX);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;

	case 12:
		if ((nLPStage1No == 1 && g_objAJinAXL.Is_MoveDone(AX_LOAD_STAGE_Y1, dLPStage1PosY)) ||
			(nLPStage1No == 2 && g_objAJinAXL.Is_MoveDone(AX_LOAD_STAGE_Y2, dLPStage1PosY)) ) {
			if (g_objAJinAXL.Is_MoveDone(AX_LOAD_PICKER_X1, dLPStage1PosX)) {
				if (nLPStage1No == 1) g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, -1, dLPStage1PosY);
				if (nLPStage1No == 2) g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, -1, dLPStage1PosY);
				g_objCommon.Save_Motion(AX_LOAD_PICKER_X1, -1, dLPStage1PosX);
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 13:
		if (g_objCommon.Get_LoadPickerOpen(n1No, 2)) {
			g_objCommon.Set_LoadPickerDown(n1No, 2);
			m_tLoadPicker1Loop.Takt_Save(12, 7); m_tLoadPicker1Loop.Takt_Start(12, 8);
			for(int i=0; i<4; i++) {
				gData.InfoLoadPick[n1No-1][i+4] = gData.InfoLoadTray[nLoad1PosY-1][i]; gData.InfoLoadTray[nLoad1PosY-1][i] = 0;
			}

			for(int i=0; i<4; i++) {
				if (gData.InfoLoadPick[n1No-1][i+4] > 0) gLot.nTrayPutCnt[n1LP][2]++;
				gLot.nHistory[n1LP][n1LT][n1LM+i+4][0] = nLPStage1No;
				gLot.nHistory[n1LP][n1LT][n1LM+i+4][1] = 1;
				gLot.nHistory[n1LP][n1LT][n1LM+i+4][2] = i + 1 + 4;
			}

			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objCommon.Get_LoadPickerDown(n1No, 2)) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, nLPStage1No);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, nLPStage1No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, nLPStage1No);
			m_tLoadPicker1Loop.Takt_Save(12, 8); m_tLoadPicker1Loop.Takt_Start(12, 9);
			g_objCommon.Set_LoadPickerClose(n1No, 2);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objCommon.Get_LoadPickerClose(n1No, 2)) {
			if (!m_tLoadPicker1Loop.Waiting_Time(m_pEquipData->nDelayTime[1])) break;
			m_tLoadPicker1Loop.Takt_Save(12, 9); m_tLoadPicker1Loop.Takt_Start(12, 10);
			g_objCommon.Set_LoadPickerUp(n1No);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 0);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(m_pEquipData->nDelayTime[10]);
		}
		break;
	case 17:
//		if (g_objCommon.Get_LoadPickerUp(n1No)) {
			if (g_objCommon.Get_LoadPickerCheck(n1No, 9, 0, gData.InfoLoadPick[n1No-1])) {
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
			}
//		}
		break;
	case 18:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, 0);
			m_tLoadPicker1Loop.Takt_Save(12, 10); m_tLoadPicker1Loop.Takt_Start(12, 11);
			if (Check_EmptyLoadTray()) {
				gData.sLotID_LoadStage[nLPStage1No-1]  = "";
				gData.nTrayNo_LoadStage[nLPStage1No-1] = gData.nPortNo_LoadStage[nLPStage1No-1] = 0;

				if (m_nLoadStage1Case == 30) m_nLoadStage1Case = 31;
				if (m_nLoadStage2Case == 30) m_nLoadStage2Case = 31;
			}
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 19:
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		break;

	case 20:
		if (m_nLoadPicker2Case < 20 || (m_nLoadPicker2Case >= 41 && m_nLoadPicker2Case < 80)) 
		{
			m_tLoadPicker1Loop.Takt_Save(12, 11); m_tLoadPicker1Loop.Takt_Start(12, 12);
			g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 1);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 1);
			g_objCommon.Move_Position(AX_BTM_LIGHT_Z, 1);

			g_objCommon.Move_Position(AX_LOAD_PICKER_X1, 3);	//BTM
			g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, 3);
			g_objCommon.Move_Position(AX_LOAD_PICKER_P1, 1);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;

	case 21:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X1, 3) && g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 3) && g_objCommon.Check_Position(AX_LOAD_PICKER_P1, 1)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_X1, 3);	g_objCommon.Save_Motion(AX_LOAD_PICKER_Y1, 3);	g_objCommon.Save_Motion(AX_LOAD_PICKER_P1, 1);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(m_pEquipData->nDelayTime[10]);
		}
		break;
	case 22:
		if (g_objCommon.Get_LoadPickerCheck(n1No, 9, 0, gData.InfoLoadPick[n1No-1])) {
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(5000);
		}
		break;
	case 23:
		if (m_pEquipData->bUseBottom) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 3);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		} else {
			m_nLoadPicker1Case = 29; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 24:
		if (g_objCommon.Check_Position(AX_BTM_ANGLE_Y, 1) ) {
			g_objCommon.Save_Motion(AX_BTM_ANGLE_Y, 1);
			m_tLoadPicker1Loop.Takt_Save(12, 12); m_tLoadPicker1Loop.Takt_Start(12, 13);
//			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 1);
//			g_objCommon.Move_Position(AX_BTM_LIGHT_Z, 1);
			g_objCommon.Set_LoadPickerDown(n1No);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 25:
		if (g_objCommon.Get_LoadPickerDown(n1No)) {
			n1BTMNo = gData.nLPCount1 = gData.nScanRetry[0] = 0;
			n1CMno1 = gData.InfoLoadPick[n1No-1][9];
			n1CMno5 = gData.InfoLoadPick[n1No-1][9] + 4;
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 26:
		if (g_objCommon.Get_LoadPickerDown(n1No)) {
			m_tLoadPicker1Loop.Takt_Save(12, 13); m_tLoadPicker1Loop.Takt_Start(12, 14);
			dLPStage1PosX = m_pMoveData->dLoadPickerX1[3] + (m_pEquipData->dPitchBtm * n1BTMNo);
			g_objAJinAXL.Move_Absolute(AX_LOAD_PICKER_X1, dLPStage1PosX);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 1);	nL1Retry = 0;
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(60000);
		}
		break;
	case 27:
		if (g_objAJinAXL.Is_MoveDone(AX_LOAD_PICKER_X1, dLPStage1PosX)) {
			if (g_objCommon.Check_Position(AX_BTM_LIGHT_Z, 1) && g_objAJinAXL.Is_Done(AX_BTM_FOCUS_Z)) {
				if (!m_tLoadPicker1Loop.Waiting_Time(m_pEquipData->nDelayTime[2])) break;
				g_objCommon.Save_Motion(AX_LOAD_PICKER_X1, -1, dLPStage1PosX);	g_objCommon.Save_Motion(AX_BTM_LIGHT_Z, 1);
				m_tLoadPicker1Loop.Takt_Save(12, 14); m_tLoadPicker1Loop.Takt_Start(12, 15);
				gData.bBTMScanDone = FALSE;
				int nModule1 = n1CMno1; if (gData.InfoLoadPick[n1No-1][n1BTMNo] < 1)   nModule1 = -1;
				int nModule5 = n1CMno5; if (gData.InfoLoadPick[n1No-1][n1BTMNo+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC1, "B1", gData.sLotID_LoadPicker[n1No-1], gData.nPortNo_LoadPicker[n1No-1], gData.nTrayNo_LoadPicker[n1No-1], nModule1, gData.nTrayNo_LoadPicker[n1No-1], nModule5);
				gAlm.sAlmLID[1] = gData.sLotID_LoadPicker[n1No-1]; gAlm.nAlmTNo[1] = gData.nTrayNo_LoadPicker[n1No-1]; gAlm.nAlmPNo[1] = nModule1;
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 28:
		if (gData.bBTMScanDone || !m_pEquipData->bUseBottom) {
			m_tLoadPicker1Loop.Takt_Save(12, 15); m_tLoadPicker1Loop.Takt_Start(12, 16);
			n1BTMNo++; n1CMno1++; n1CMno5++;
			if (n1BTMNo >= 4) {
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
			} else {
				m_nLoadPicker1Case = 26; m_tLoadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 29:
		if (m_pEquipData->bUseBotAng) {
			g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 2);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 2);
			g_objCommon.Move_Position(AX_BTM_LIGHT_Z, 2);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 3);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		} else {
			m_nLoadPicker1Case = 40; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 30:
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		break;
	case 31:
		if (g_objCommon.Check_Position(AX_BTM_FOCUS_Z, 2) && g_objCommon.Check_Position(AX_BTM_LIGHT_Z, 2) ) {
			g_objCommon.Save_Motion(AX_BTM_FOCUS_Z, 2);	g_objCommon.Save_Motion(AX_BTM_LIGHT_Z, 2);
			m_tLoadPicker1Loop.Takt_Save(12, 16); m_tLoadPicker1Loop.Takt_Start(12, 17);
//			g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 2);
			n1BTMNo = gData.nLPCount1 = gData.nScanRetry[0] = 0;
			n1CMno1 = gData.InfoLoadPick[n1No-1][9];
			n1CMno5 = gData.InfoLoadPick[n1No-1][9] + 4;
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 32:
		if (g_objCommon.Get_LoadPickerDown(n1No)) {
			m_tLoadPicker1Loop.Takt_Save(12, 17); m_tLoadPicker1Loop.Takt_Start(12, 18);
			dLPStage1PosX = m_pMoveData->dLoadPickerX1[3] + (m_pEquipData->dPitchBtm * n1BTMNo);
			g_objAJinAXL.Move_Absolute(AX_LOAD_PICKER_X1, dLPStage1PosX);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 2);	nL1Retry = 0;
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(60000);
		}
		break;
	case 33:
		if (g_objAJinAXL.Is_MoveDone(AX_LOAD_PICKER_X1, dLPStage1PosX)) {
			if (g_objCommon.Check_Position(AX_BTM_ANGLE_Y, 2) && g_objAJinAXL.Is_Done(AX_BTM_FOCUS_Z)) {
				if (!m_tLoadPicker1Loop.Waiting_Time(m_pEquipData->nDelayTime[2])) break;
				g_objCommon.Save_Motion(AX_LOAD_PICKER_X1, -1, dLPStage1PosX);	g_objCommon.Save_Motion(AX_BTM_ANGLE_Y, 2);
				m_tLoadPicker1Loop.Takt_Save(12, 18); m_tLoadPicker1Loop.Takt_Start(12, 19);
				gData.bBTMScanDone = FALSE;
				int nModule1 = n1CMno1; if (gData.InfoLoadPick[n1No-1][n1BTMNo] < 1)   nModule1 = -1;
				int nModule5 = n1CMno5; if (gData.InfoLoadPick[n1No-1][n1BTMNo+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC1, "AG", gData.sLotID_LoadPicker[n1No-1], gData.nPortNo_LoadPicker[n1No-1], gData.nTrayNo_LoadPicker[n1No-1], nModule1, gData.nTrayNo_LoadPicker[n1No-1], nModule5);
				gAlm.sAlmLID[1] = gData.sLotID_LoadPicker[n1No-1]; gAlm.nAlmTNo[1] = gData.nTrayNo_LoadPicker[n1No-1]; gAlm.nAlmPNo[1] = nModule1;
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 34:
		if (gData.bBTMScanDone || !m_pEquipData->bUseBotAng) {
			m_tLoadPicker1Loop.Takt_Save(12, 19); m_tLoadPicker1Loop.Takt_Start(12, 20);
			n1BTMNo++; n1CMno1++; n1CMno5++;
			gData.nLPCount1 = n1BTMNo;
			if (n1BTMNo >= 4) {
//				g_objCommon.Set_LoadPickerUp(n1No);
				g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 1);
				g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 0);
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
			} else {
				m_nLoadPicker1Case = 32; m_tLoadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 35:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0) ) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, 0);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 36:
		if (Check_EemptyLoadPicker(n1No)) {
			g_objCommon.Set_LoadPickerUp(n1No);
			g_objCommon.Move_Position(AX_LOAD_PICKER_X1, 4);

			gData.sLotID_LoadPicker[n1No-1]  = "";
			gData.nTrayNo_LoadPicker[n1No-1] = gData.nPortNo_LoadPicker[n1No-1] = 0;
			for(int i=0; i<10; i++) gData.InfoLoadPick[n1No-1][i] = 0;
			
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		} else {
			m_nLoadPicker1Case = 40; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 37:
		if (g_objCommon.Get_LoadPickerUp(n1No)) {
			if (g_objCommon.Check_Position(AX_LOAD_PICKER_X1, 4) ) {
				g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, 0);
				g_objCommon.Move_Position(AX_LOAD_PICKER_P1, 0);
				m_nLoadPicker1Case = 60; m_tLoadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 40:
		if (m_nLoadPicker2Case < 40 || (m_nLoadPicker2Case > 61 && m_nLoadPicker2Case < 80)) {
//			if (g_objCommon.Get_LoadPickerUp(n1No)) {
				m_tLoadPicker1Loop.Takt_Save(12, 20); m_tLoadPicker1Loop.Takt_Start(12, 21);
				g_objCommon.Move_Position(AX_LOAD_PICKER_X1, 4);
				g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, 4);
				g_objCommon.Move_Position(AX_LOAD_PICKER_P1, 2);
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
//			}
		}
		return TRUE;

	case 41:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X1, 4) && g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 4) && g_objCommon.Check_Position(AX_LOAD_PICKER_P1, 2) ) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_X1, 4);	g_objCommon.Save_Motion(AX_LOAD_PICKER_Y1, 4);	g_objCommon.Save_Motion(AX_LOAD_PICKER_P1, 2);
			m_tLoadPicker1Loop.Takt_Save(12, 21); m_tLoadPicker1Loop.Takt_Start(12, 22);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 42:
		n1LPVisionNo = 0;
		if (m_nVisionStage1Case == 0) n1LPVisionNo = 1;
		if (m_nVisionStage2Case == 0) n1LPVisionNo = 2;
		if (m_nVisionStage3Case == 0) n1LPVisionNo = 3;
		if (m_nVisionStage4Case == 0) n1LPVisionNo = 4;

		if (n1LPVisionNo > 0) {
			m_tLoadPicker1Loop.Takt_Save(12, 22); m_tLoadPicker1Loop.Takt_Start(12, 23);
			g_objCommon.Set_VisionVacuumOn(n1LPVisionNo);
			g_objCommon.Set_LoadPickerDown(n1No);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 43:
		if (g_objCommon.Get_LoadPickerDown(n1No)) {
			m_tLoadPicker1Loop.Takt_Save(12, 23); m_tLoadPicker1Loop.Takt_Start(12, 24);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 4);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 44:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 4) ) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, 4);
			m_tLoadPicker1Loop.Takt_Save(12, 24); m_tLoadPicker1Loop.Takt_Start(12, 25);
			g_objCommon.Set_LoadPickerOpen(n1No);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 45:
		if (g_objCommon.Get_LoadPickerOpen(n1No)) {
			if (!m_tLoadPicker1Loop.Waiting_Time(m_pEquipData->nDelayTime[0])) break;
			m_tLoadPicker1Loop.Takt_Save(12, 25); m_tLoadPicker1Loop.Takt_Start(12, 26);
			g_objCommon.Set_LoadPickerUp(n1No);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 46:
		if (g_objCommon.Get_LoadPickerUp(n1No)) {
			m_tLoadPicker1Loop.Takt_Save(12, 26); m_tLoadPicker1Loop.Takt_Start(12, 27);

			gData.sLotID_VisionStage[n1LPVisionNo-1]  = gData.sLotID_LoadPicker[n1No-1];
			gData.nTrayNo_VisionStage[n1LPVisionNo-1] = gData.nTrayNo_LoadPicker[n1No-1];
			gData.nPortNo_VisionStage[n1LPVisionNo-1] = gData.nPortNo_LoadPicker[n1No-1];
			gData.sLotID_VisionStage[4]  = gData.sLotID_VisionStage[n1LPVisionNo-1];

			gData.sLotID_LoadPicker[n1No-1]  = "";
			gData.nTrayNo_LoadPicker[n1No-1] = gData.nPortNo_LoadPicker[n1No-1] = 0;

			for(int i=0; i<10; i++) {
				 gData.InfoVision[n1LPVisionNo-1][i] = gData.InfoLoadPick[n1No-1][i]; gData.InfoLoadPick[n1No-1][i] = 0;
			}
			for(int i=0; i<8; i++) { gLot.nHistory[n1LP][n1LT][n1LM+i][3] = gData.nVisionNo = n1LPVisionNo; }
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(3000);
		}
		break;
	case 47:
//		if (g_objCommon.Get_VisionVacuumOn(n1LPVisionNo, 9, gData.InfoVision[n1LPVisionNo-1])) {
			g_objCommon.Set_VisionVacuumOff(n1LPVisionNo);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 0);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
//		}
		break;
	case 48:
		if (g_objCommon.Get_LoadPickerUp(n1No)) {
			m_pDY03->oAlignMasterIn = TRUE; m_pDY03->oAlignMasterOut = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 49:
		if (m_pDX03->iAlignMasterIn && !m_pDX03->iAlignMasterOut) {
			m_tLoadPicker1Loop.Takt_Save(12, 27); m_tLoadPicker1Loop.Takt_Start(12, 28);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, 0);
			g_objCommon.Move_Position(AX_LOAD_PICKER_P1, 0);
			m_pDY03->oAlignSlave1In = TRUE; m_pDY03->oAlignSlave1Out = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 50:
		if (m_pDX03->iAlignSlave1In && !m_pDX03->iAlignSlave1Out) {
			m_pDY03->oAlignSlave2In = TRUE; m_pDY03->oAlignSlave2Out = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 51:
		if (m_pDX03->iAlignSlave2In && !m_pDX03->iAlignSlave2Out) {
			m_tLoadPicker1Loop.Takt_Save(12, 28); m_tLoadPicker1Loop.Takt_Start(12, 29);
			g_objCommon.Set_VisionVacuumOn(n1LPVisionNo);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 52:
		if (m_pDX03->iAlignSlave1In && !m_pDX03->iAlignSlave1Out && m_pDX03->iAlignSlave2In && !m_pDX03->iAlignSlave2Out) {
			if (!m_tLoadPicker1Loop.Waiting_Time(300)) break;
			m_pDY03->oAlignSlave2In = FALSE; m_pDY03->oAlignSlave2Out = TRUE;
			g_objAJinAXL.Write_Output(3);
			if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0)) {
				g_objCommon.Move_Position(AX_LOAD_PICKER_X1, 1);
			}
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 53:
		if (!m_pDX03->iAlignSlave2In && m_pDX03->iAlignSlave2Out) {
			m_pDY03->oAlignSlave1In = FALSE; m_pDY03->oAlignSlave1Out = TRUE;
			g_objAJinAXL.Write_Output(3);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 54:
		if (!m_pDX03->iAlignSlave1In && m_pDX03->iAlignSlave1Out) {
			m_tLoadPicker1Loop.Takt_Save(12, 29); m_tLoadPicker1Loop.Takt_Start(12, 30);
			m_pDY03->oAlignMasterIn = FALSE; m_pDY03->oAlignMasterOut = TRUE;
			g_objAJinAXL.Write_Output(3);
			if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0)) {
				g_objCommon.Move_Position(AX_LOAD_PICKER_X1, 1);
			}
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 55:
		if (!m_pDX03->iAlignMasterIn && m_pDX03->iAlignMasterOut) {
			m_tLoadPicker1Loop.Takt_Save(12, 30); m_tLoadPicker1Loop.Takt_Start(12, 31);
			if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0)) {
				g_objCommon.Move_Position(AX_LOAD_PICKER_X1, 1);
			}
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(3000+m_pEquipData->nDelayTime[4]);
		}
		break;
	case 56:
		if (g_objCommon.Get_VisionVacuumOn(n1LPVisionNo, 9, gData.InfoVision[n1LPVisionNo-1])) {
			if (Check_EemptyVisionStage(n1LPVisionNo)) {
				gData.sLotID_VisionStage[n1LPVisionNo-1] = "";
				gData.nTrayNo_VisionStage[n1LPVisionNo-1] = gData.nPortNo_VisionStage[n1LPVisionNo-1] = 0;

				for(int i=0; i<10; i++) gData.InfoVision[n1LPVisionNo-1][i] = 0;

			} else {
				if (n1LPVisionNo == 1) m_nVisionStage1Case = 1;
				if (n1LPVisionNo == 2) m_nVisionStage2Case = 1;
				if (n1LPVisionNo == 3) m_nVisionStage3Case = 1;
				if (n1LPVisionNo == 4) m_nVisionStage4Case = 1;
			}
			m_nLoadPicker1Case = 70; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 70:
		if (m_nLoadPicker2Case > 21 && m_nLoadPicker2Case < 70) 
		{			
			m_nLoadPicker1Case = 0; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;

		/*case 60:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0) ) {
		g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, 0);
		m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
		case 61:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0) ) {
		g_objCommon.Save_Motion(AX_LOAD_PICKER_Y1, 0);
		m_tLoadPicker1Loop.Takt_Save(12, 31); m_tLoadPicker1Loop.Takt_Start(12, 32);
		g_objCommon.Move_Position(AX_LOAD_PICKER_X1, nLOADPICKER1_X_Stage1);
		m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
		case 62:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X1, nLOADPICKER1_X_Stage1) && g_objCommon.Check_Position(AX_LOAD_PICKER_P1, 0) ) {
		g_objCommon.Save_Motion(AX_LOAD_PICKER_X1, nLOADPICKER1_X_Stage1);
		m_tLoadPicker1Loop.Takt_Save(12, 32, TRUE);
		m_nLoadPicker1Case = 70; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;

		case 70:
		if (m_nLoadPicker2Case > 21 && m_nLoadPicker2Case < 70) {
		g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, 1);
		m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;
		case 71:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 1) ) {
		g_objCommon.Save_Motion(AX_LOAD_PICKER_Y1, 1);
		m_nLoadPicker1Case = 0; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;*/

	case 81:
		if (g_objCommon.Get_LoadPickerUp(n1No)) {
			if (g_objCommon.Get_LoadPickerCheck(n1No, 9, 0, gData.InfoLoadPick[n1No-1])) {
				m_nLoadPicker1Case = 10; m_tLoadPicker1Loop.Set_LoopTime(30000);
			} else {
				for(int i=0; i<4; i++) {
					if (gData.nLoadPicker1ErrNo[i] == 1) {
						g_objCommon.Set_LoadPickerOpen(n1No, 9, i+1);
					}
				}
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 82:
		if (g_objCommon.Get_LoadPickerUp(n1No)) {
			if (!m_tLoadPicker1Loop.Waiting_Time(500)) break;
			g_objCommon.Set_LoadPickerDown(n1No, 1);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 83:
		if (g_objCommon.Get_LoadPickerDown(n1No, 1)) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, nLPStage1No);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 84:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, nLPStage1No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, nLPStage1No);
			m_nLoadPicker1Case = 7; m_tLoadPicker1Loop.Set_LoopTime(5000);
		}
		break;

	case 85:
		if (g_objCommon.Get_LoadPickerUp(n1No)) {
			if (g_objCommon.Get_LoadPickerCheck(n1No, 9, 0, gData.InfoLoadPick[n1No-1])) {
				m_nLoadPicker1Case = 17; m_tLoadPicker1Loop.Set_LoopTime(30000);
			} else {
				for(int i=4; i<8; i++) {
					if (gData.nLoadPicker1ErrNo[i] == 1) {
						g_objCommon.Set_LoadPickerOpen(n1No, 9, i+1);
					}
				}
				m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 86:
		if (g_objCommon.Get_LoadPickerUp(n1No)) {
			if (!m_tLoadPicker1Loop.Waiting_Time(500)) break;
			g_objCommon.Set_LoadPickerDown(n1No, 2);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 87:
		if (g_objCommon.Get_LoadPickerDown(n1No, 2)) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, nLPStage1No);
			m_nLoadPicker1Case++; m_tLoadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 88:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, nLPStage1No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z1, nLPStage1No);
			m_nLoadPicker1Case = 14; m_tLoadPicker1Loop.Set_LoopTime(5000);
		}
		break;

	}

	// 12. (Error : 5000)
	if (m_tLoadPicker1Loop.Over_LoopTime()) {
//		if (m_nLoadPicker1Case == 28 || m_nLoadPicker1Case == 34) {
//			nL1Retry++;
//			if (nL1Retry == 1) { m_nLoadPicker1Case--; return TRUE; }
//		}
//		if (m_nLoadPicker1Case == 27 || m_nLoadPicker1Case == 33) m_nLoadPicker1Case++;
		g_objCommon.Show_Error(5000 + m_nLoadPicker1Case);
		return FALSE;
	}
	return TRUE;
}

// 13. (Error : 5500)
BOOL CSequenceMain::Run_LoadPicker2()
{
	static int n2No = 2;			//2(고정)
	static int nLPStage2No = 0;	//1,2
	static int nLoad2PosY = 0;	//1~10
	static int n2BTMNo, n2CMno1, n2CMno5, n2LPVisionNo, n2LP, n2LT, n2LM, nL2Retry;
	static double dLPStage2PosY = 0, dLPStage2PosX = 0;

	switch (m_nLoadPicker2Case) {
	case 0:	// Wait
		if (m_nLoadStage1Case == 30 && !m_pDX04->iLoadStage1TrayExist && Check_EmptyLoadTray()) m_nLoadStage1Case = 31;
		if (m_nLoadStage2Case == 30 && !m_pDX04->iLoadStage2TrayExist && Check_EmptyLoadTray()) m_nLoadStage2Case = 31;
		if (m_nLoadStage1Case == 31 || m_nLoadStage2Case == 31) {
			m_sLog.Format("[LoadPicker2: Start] Empty - Seq(%d-%d)", m_nLoadStage1Case, m_nLoadStage2Case);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		if (m_nLoadStage1Case == 30 || m_nLoadStage2Case == 30) {
			if (m_nLoadStage1Case == 30) nLPStage2No = 1;
			if (m_nLoadStage2Case == 30) nLPStage2No = 2;
			g_objCommon.Set_LoadPickerUp(n2No);	gData.nLPCount2 = 0;
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 0);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(5000);

			m_sLog.Format("[LoadPicker2: Start] StageNo(%d)", nLPStage2No);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		return TRUE;

	case 1:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) 
		{
			if (g_objCommon.Get_LoadPickerUp(n2No)) 
			{
				if (m_nLoadPicker1Case <= 21 || m_nLoadPicker1Case >= 70) return TRUE;

				g_objCommon.Move_Position(AX_LOAD_PICKER_X2, nLPStage2No);
				g_objCommon.Move_Position(AX_LOAD_PICKER_Y2, nLPStage2No);
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 2:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X2, nLPStage2No) && g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, nLPStage2No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_X2, nLPStage2No);	g_objCommon.Save_Motion(AX_LOAD_PICKER_Y2, nLPStage2No);
			g_objCommon.Set_LoadPickerOpen(n2No);	nLoad2PosY = 0;
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(10000);
		}
		break;
	case 3:
		if (Check_LoadModule(nLoad2PosY)) {
			m_tLoadPicker2Loop.Takt_Start(13, 1, TRUE);
			if (nLPStage2No == 1) {
				dLPStage2PosY = m_pMoveData->dLoadStageY1[2] + (m_pEquipData->dTrayPitchY * (nLoad2PosY - 1));
				g_objAJinAXL.Move_Absolute(AX_LOAD_STAGE_Y1, dLPStage2PosY);
			}
			if (nLPStage2No == 2) {
				dLPStage2PosY = m_pMoveData->dLoadStageY2[2] + (m_pEquipData->dTrayPitchY * (nLoad2PosY - 1));
				g_objAJinAXL.Move_Absolute(AX_LOAD_STAGE_Y2, dLPStage2PosY);
			}
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		} else {
			gData.sLotID_LoadStage[nLPStage2No-1]  = "";
			gData.nTrayNo_LoadStage[nLPStage2No-1] = gData.nPortNo_LoadStage[nLPStage2No-1] = 0;

			if (m_nLoadStage1Case == 30) m_nLoadStage1Case = 31;
			if (m_nLoadStage2Case == 30) m_nLoadStage2Case = 31;
			m_nLoadPicker2Case = 0; m_tLoadPicker2Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if ((nLPStage2No == 1 && g_objAJinAXL.Is_MoveDone(AX_LOAD_STAGE_Y1, dLPStage2PosY)) ||
			(nLPStage2No == 2 && g_objAJinAXL.Is_MoveDone(AX_LOAD_STAGE_Y2, dLPStage2PosY)) ) {
			if (nLPStage2No == 1) g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, -1, dLPStage2PosY);
			if (nLPStage2No == 2) g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, -1, dLPStage2PosY);
			m_tLoadPicker2Loop.Takt_Save(13, 1); m_tLoadPicker2Loop.Takt_Start(13, 2);
			g_objCommon.Set_LoadPickerDown(n2No, 1);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objCommon.Get_LoadPickerDown(n2No, 1)) {
			m_tLoadPicker2Loop.Takt_Save(13, 2); m_tLoadPicker2Loop.Takt_Start(13, 3);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, nLPStage2No);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 6:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, nLPStage2No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, nLPStage2No);
			m_tLoadPicker2Loop.Takt_Save(13, 3); m_tLoadPicker2Loop.Takt_Start(13, 4);
			gData.sLotID_LoadPicker[n2No-1]  = gData.sLotID_LoadStage[nLPStage2No-1];
			gData.nTrayNo_LoadPicker[n2No-1] = gData.nTrayNo_LoadStage[nLPStage2No-1];
			gData.nPortNo_LoadPicker[n2No-1] = gData.nPortNo_LoadStage[nLPStage2No-1];
			gData.sLotID_LoadPicker[2]		 = gData.sLotID_LoadPicker[n2No-1];

			for(int i=0; i<4; i++) {
				gData.InfoLoadPick[n2No-1][i] = gData.InfoLoadTray[nLoad2PosY-1][i];	gData.InfoLoadTray[nLoad2PosY-1][i] = 0;
			}
			gData.InfoLoadPick[n2No-1][9] = ((nLoad2PosY-1) * 4) + 1;
			
			n2LP = gData.nPortNo_LoadPicker[n2No-1] - 1;
			n2LT = gData.nTrayNo_LoadPicker[n2No-1] - 1;
			n2LM = gData.InfoLoadPick[n2No-1][9] - 1;
			for(int i=0; i<4; i++) {
				if (gData.InfoLoadPick[n2No-1][i] > 0) gLot.nTrayPutCnt[n2LP][2]++;
				gLot.nHistory[n2LP][n2LT][n2LM+i][0] = nLPStage2No;
				gLot.nHistory[n2LP][n2LT][n2LM+i][1] = 2;
				gLot.nHistory[n2LP][n2LT][n2LM+i][2] = i + 1;
			}

			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 7:
		if (g_objCommon.Get_LoadPickerDown(n2No, 1)) {
			g_objCommon.Set_LoadPickerClose(n2No, 1);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 8:
		if (g_objCommon.Get_LoadPickerClose(n2No, 1)) {
			if (!m_tLoadPicker2Loop.Waiting_Time(m_pEquipData->nDelayTime[1])) break;
			m_tLoadPicker2Loop.Takt_Save(13, 4); m_tLoadPicker2Loop.Takt_Start(13, 5);
			g_objCommon.Set_LoadPickerUp(n2No);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 0);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 9:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) {
			if (g_objCommon.Get_LoadPickerUp(n2No)) {
				g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, 0);
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(m_pEquipData->nDelayTime[10]);
			}
		}
		break;
	case 10:
		if (g_objCommon.Get_LoadPickerCheck(n2No, 9, 0, gData.InfoLoadPick[n2No-1])) {
			if (Check_LoadModule(nLoad2PosY)) {
				m_tLoadPicker2Loop.Takt_Save(13, 5); m_tLoadPicker2Loop.Takt_Start(13, 6);
				if (nLPStage2No == 1) {
					dLPStage2PosY = m_pMoveData->dLoadStageY1[2] + (m_pEquipData->dTrayPitchY * (nLoad2PosY - 1));
					g_objAJinAXL.Move_Absolute(AX_LOAD_STAGE_Y1, dLPStage2PosY);
				}
				if (nLPStage2No == 2) {
					dLPStage2PosY = m_pMoveData->dLoadStageY2[2] + (m_pEquipData->dTrayPitchY * (nLoad2PosY - 1));
					g_objAJinAXL.Move_Absolute(AX_LOAD_STAGE_Y2, dLPStage2PosY);
				}
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
			} else {
				m_nLoadPicker2Case = 18; m_tLoadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 11:
		if ((m_nLoadPicker1Case > 41 && m_nLoadPicker1Case < 80) ||
			(m_nLoadPicker1Case > 33 && m_nLoadPicker1Case < 80 && gData.nLPCount1 >= 4) ) {
			m_tLoadPicker2Loop.Takt_Save(13, 6); m_tLoadPicker2Loop.Takt_Start(13, 7);
			dLPStage2PosX = m_pMoveData->dLoadPickerX2[nLPStage2No] + (m_pEquipData->dTrayPitchX * 4);
			g_objAJinAXL.Move_Absolute(AX_LOAD_PICKER_X2, dLPStage2PosX);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;

	case 12:
		if ((nLPStage2No == 1 && g_objAJinAXL.Is_MoveDone(AX_LOAD_STAGE_Y1, dLPStage2PosY)) ||
			(nLPStage2No == 2 && g_objAJinAXL.Is_MoveDone(AX_LOAD_STAGE_Y2, dLPStage2PosY)) ) {
			if (g_objAJinAXL.Is_MoveDone(AX_LOAD_PICKER_X2, dLPStage2PosX)) {
				if (nLPStage2No == 1) g_objCommon.Save_Motion(AX_LOAD_STAGE_Y1, -1, dLPStage2PosY);
				if (nLPStage2No == 2) g_objCommon.Save_Motion(AX_LOAD_STAGE_Y2, -1, dLPStage2PosY);
				g_objCommon.Save_Motion(AX_LOAD_PICKER_X2, -1, dLPStage2PosX);
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 13:
		if (g_objCommon.Get_LoadPickerOpen(n2No, 2)) {
			g_objCommon.Set_LoadPickerDown(n2No, 2);
			m_tLoadPicker2Loop.Takt_Save(13, 7); m_tLoadPicker2Loop.Takt_Start(13, 8);
			for(int i=0; i<4; i++) {
				gData.InfoLoadPick[n2No-1][i+4] = gData.InfoLoadTray[nLoad2PosY-1][i]; gData.InfoLoadTray[nLoad2PosY-1][i] = 0;
			}

			for(int i=0; i<4; i++) {
				if (gData.InfoLoadPick[n2No-1][i+4] > 0) gLot.nTrayPutCnt[n2LP][2]++;
				gLot.nHistory[n2LP][n2LT][n2LM+i+4][0] = nLPStage2No;
				gLot.nHistory[n2LP][n2LT][n2LM+i+4][1] = 2;
				gLot.nHistory[n2LP][n2LT][n2LM+i+4][2] = i + 1 + 4;
			}

			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objCommon.Get_LoadPickerDown(n2No, 2)) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, nLPStage2No);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, nLPStage2No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, nLPStage2No);
			m_tLoadPicker2Loop.Takt_Save(13, 8); m_tLoadPicker2Loop.Takt_Start(13, 9);
			g_objCommon.Set_LoadPickerClose(n2No, 2);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objCommon.Get_LoadPickerClose(n2No, 2)) {
			if (!m_tLoadPicker2Loop.Waiting_Time(m_pEquipData->nDelayTime[1])) break;
			m_tLoadPicker2Loop.Takt_Save(13, 9); m_tLoadPicker2Loop.Takt_Start(13, 10);
			g_objCommon.Set_LoadPickerUp(n2No);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 0);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(m_pEquipData->nDelayTime[10]);
		}
		break;
	case 17:
//		if (g_objCommon.Get_LoadPickerUp(n2No)) {
			if (g_objCommon.Get_LoadPickerCheck(n2No, 9, 0, gData.InfoLoadPick[n2No-1])) {
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
			}
//		}
		break;
	case 18:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, 0);
			m_tLoadPicker2Loop.Takt_Save(13, 10); m_tLoadPicker2Loop.Takt_Start(13, 11);
			if (Check_EmptyLoadTray()) {
				gData.sLotID_LoadStage[nLPStage2No-1]  = "";
				gData.nTrayNo_LoadStage[nLPStage2No-1] = gData.nPortNo_LoadStage[nLPStage2No-1] = 0;

				if (m_nLoadStage1Case == 30) m_nLoadStage1Case = 31;
				if (m_nLoadStage2Case == 30) m_nLoadStage2Case = 31;
			}
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 19:
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		break;

	case 20:
		if (m_nLoadPicker1Case < 20 || (m_nLoadPicker1Case >= 41 && m_nLoadPicker1Case < 80)) {
			m_tLoadPicker2Loop.Takt_Save(13, 11); m_tLoadPicker2Loop.Takt_Start(13, 12);
			g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 1);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 1);
			g_objCommon.Move_Position(AX_BTM_LIGHT_Z, 1);

			g_objCommon.Move_Position(AX_LOAD_PICKER_X2, 3);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Y2, 3);
			g_objCommon.Move_Position(AX_LOAD_PICKER_P2, 1);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;

	case 21:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X2, 3) && g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 3) && g_objCommon.Check_Position(AX_LOAD_PICKER_P2, 1)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_X2, 3);	g_objCommon.Save_Motion(AX_LOAD_PICKER_Y2, 3);	g_objCommon.Save_Motion(AX_LOAD_PICKER_P2, 1);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(m_pEquipData->nDelayTime[10]);
		}
		break;
	case 22:
		if (g_objCommon.Get_LoadPickerCheck(n2No, 9, 0, gData.InfoLoadPick[n2No-1])) {
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(5000);
		}
		break;
	case 23:
		if (m_pEquipData->bUseBottom) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 3);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		} else {
			m_nLoadPicker2Case = 29; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 24:
		if (g_objCommon.Check_Position(AX_BTM_ANGLE_Y, 1) ) {
			g_objCommon.Save_Motion(AX_BTM_ANGLE_Y, 1);
			m_tLoadPicker2Loop.Takt_Save(13, 12); m_tLoadPicker2Loop.Takt_Start(13, 13);
//			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 1);
//			g_objCommon.Move_Position(AX_BTM_LIGHT_Z, 1);
			g_objCommon.Set_LoadPickerDown(n2No);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 25:
		if (g_objCommon.Get_LoadPickerDown(n2No)) {
			n2BTMNo = gData.nLPCount2 = gData.nScanRetry[0] = 0;
			n2CMno1 = gData.InfoLoadPick[n2No-1][9];
			n2CMno5 = gData.InfoLoadPick[n2No-1][9] + 4;
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 26:
		if (g_objCommon.Get_LoadPickerDown(n2No)) {
			m_tLoadPicker2Loop.Takt_Save(13, 13); m_tLoadPicker2Loop.Takt_Start(13, 14);
			dLPStage2PosX = m_pMoveData->dLoadPickerX2[3] + (m_pEquipData->dPitchBtm * n2BTMNo);
			g_objAJinAXL.Move_Absolute(AX_LOAD_PICKER_X2, dLPStage2PosX);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 1);	nL2Retry = 0;
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(60000);
		}
		break;
	case 27:
		if (g_objAJinAXL.Is_MoveDone(AX_LOAD_PICKER_X2, dLPStage2PosX)) {
			if (g_objCommon.Check_Position(AX_BTM_LIGHT_Z, 1) && g_objAJinAXL.Is_Done(AX_BTM_FOCUS_Z)) {
				if (!m_tLoadPicker2Loop.Waiting_Time(m_pEquipData->nDelayTime[2])) break;
				g_objCommon.Save_Motion(AX_LOAD_PICKER_X2, -1, dLPStage2PosX);	g_objCommon.Save_Motion(AX_BTM_LIGHT_Z, 1);
				m_tLoadPicker2Loop.Takt_Save(13, 14); m_tLoadPicker2Loop.Takt_Start(13, 15);
				gData.bBTMScanDone = FALSE;
				int nModule1 = n2CMno1; if (gData.InfoLoadPick[n2No-1][n2BTMNo] < 1)   nModule1 = -1;
				int nModule5 = n2CMno5; if (gData.InfoLoadPick[n2No-1][n2BTMNo+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC1, "B1", gData.sLotID_LoadPicker[n2No-1], gData.nPortNo_LoadPicker[n2No-1], gData.nTrayNo_LoadPicker[n2No-1], nModule1, gData.nTrayNo_LoadPicker[n2No-1], nModule5);
				gAlm.sAlmLID[1] = gData.sLotID_LoadPicker[n2No-1]; gAlm.nAlmTNo[1] = gData.nTrayNo_LoadPicker[n2No-1]; gAlm.nAlmPNo[1] = nModule1;
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 28:
		if (gData.bBTMScanDone || !m_pEquipData->bUseBottom) {
			m_tLoadPicker2Loop.Takt_Save(13, 15); m_tLoadPicker2Loop.Takt_Start(13, 16);
			n2BTMNo++; n2CMno1++; n2CMno5++;
			if (n2BTMNo >= 4) {
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
			} else {
				m_nLoadPicker2Case = 26; m_tLoadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 29:
		if (m_pEquipData->bUseBotAng) {
			g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 2);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 2);
			g_objCommon.Move_Position(AX_BTM_LIGHT_Z, 2);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 3);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		} else {
			m_nLoadPicker2Case = 40; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 30:
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		break;
	case 31:
		if (g_objCommon.Check_Position(AX_BTM_FOCUS_Z, 2) && g_objCommon.Check_Position(AX_BTM_LIGHT_Z, 2) ) {
			g_objCommon.Save_Motion(AX_BTM_FOCUS_Z, 2);	g_objCommon.Save_Motion(AX_BTM_LIGHT_Z, 2);
			m_tLoadPicker2Loop.Takt_Save(13, 16); m_tLoadPicker2Loop.Takt_Start(13, 17);
			n2BTMNo = gData.nLPCount2 = gData.nScanRetry[0] = 0;
			n2CMno1 = gData.InfoLoadPick[n2No-1][9];
			n2CMno5 = gData.InfoLoadPick[n2No-1][9] + 4;
//			g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 2);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 32:
		if (g_objCommon.Get_LoadPickerDown(n2No)) {
			m_tLoadPicker2Loop.Takt_Save(13, 17); m_tLoadPicker2Loop.Takt_Start(13, 18);
			dLPStage2PosX = m_pMoveData->dLoadPickerX2[3] + (m_pEquipData->dPitchBtm * n2BTMNo);
			g_objAJinAXL.Move_Absolute(AX_LOAD_PICKER_X2, dLPStage2PosX);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 2);	nL2Retry = 0;
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(60000);
		}
		break;
	case 33:
		if (g_objAJinAXL.Is_MoveDone(AX_LOAD_PICKER_X2, dLPStage2PosX)) {
			if (g_objCommon.Check_Position(AX_BTM_ANGLE_Y, 2) && g_objAJinAXL.Is_Done(AX_BTM_FOCUS_Z)) {
				if (!m_tLoadPicker2Loop.Waiting_Time(m_pEquipData->nDelayTime[2])) break;
				g_objCommon.Save_Motion(AX_LOAD_PICKER_X2, -1, dLPStage2PosX);	g_objCommon.Save_Motion(AX_BTM_ANGLE_Y, 2);
				m_tLoadPicker2Loop.Takt_Save(13, 18); m_tLoadPicker2Loop.Takt_Start(13, 19);
				gData.bBTMScanDone = FALSE;
				int nModule1 = n2CMno1; if (gData.InfoLoadPick[n2No-1][n2BTMNo] < 1)   nModule1 = -1;
				int nModule5 = n2CMno5; if (gData.InfoLoadPick[n2No-1][n2BTMNo+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC1, "AG", gData.sLotID_LoadPicker[n2No-1], gData.nPortNo_LoadPicker[n2No-1], gData.nTrayNo_LoadPicker[n2No-1], nModule1, gData.nTrayNo_LoadPicker[n2No-1], nModule5);
				gAlm.sAlmLID[1] = gData.sLotID_LoadPicker[n2No-1]; gAlm.nAlmTNo[1] = gData.nTrayNo_LoadPicker[n2No-1]; gAlm.nAlmPNo[1] = nModule1;
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 34:
		if (gData.bBTMScanDone || !m_pEquipData->bUseBotAng) {
			m_tLoadPicker2Loop.Takt_Save(13, 19); m_tLoadPicker2Loop.Takt_Start(13, 20);
			n2BTMNo++; n2CMno1++; n2CMno5++;
			gData.nLPCount2 = n2BTMNo;
			if (n2BTMNo >= 4) {
//				g_objCommon.Set_LoadPickerUp(n2No);
				g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 1);
				g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 0);
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
			} else {
				m_nLoadPicker2Case = 32; m_tLoadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 35:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0) ) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, 0);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 36:
		if (Check_EemptyLoadPicker(n2No)) {
			g_objCommon.Set_LoadPickerUp(n2No);
			g_objCommon.Move_Position(AX_LOAD_PICKER_X2, 4);

			gData.sLotID_LoadPicker[n2No-1]  = "";
			gData.nTrayNo_LoadPicker[n2No-1] = gData.nPortNo_LoadPicker[n2No-1] = 0;
			for(int i=0; i<10; i++) gData.InfoLoadPick[n2No-1][i] = 0;
			
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		} else {
			m_nLoadPicker2Case = 40; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 37:
		if (g_objCommon.Get_LoadPickerUp(n2No)) {
			if (g_objCommon.Check_Position(AX_LOAD_PICKER_X2, 4) ) {
				g_objCommon.Move_Position(AX_LOAD_PICKER_Y2, 0);
				g_objCommon.Move_Position(AX_LOAD_PICKER_P2, 0);
				m_nLoadPicker2Case = 60; m_tLoadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 40:
		if (m_nLoadPicker1Case < 40 || (m_nLoadPicker1Case > 61 && m_nLoadPicker1Case < 80)) {
//			if (g_objCommon.Get_LoadPickerUp(n2No)) {
				m_tLoadPicker2Loop.Takt_Save(13, 20); m_tLoadPicker2Loop.Takt_Start(13, 21); 
				g_objCommon.Move_Position(AX_LOAD_PICKER_X2, 4);	//Align
				g_objCommon.Move_Position(AX_LOAD_PICKER_Y2, 4);
				g_objCommon.Move_Position(AX_LOAD_PICKER_P2, 2);
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
//			}
		}
		return TRUE;

	case 41:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X2, 4) && g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 4) && g_objCommon.Check_Position(AX_LOAD_PICKER_P2, 2) ) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_X2, 4);	g_objCommon.Save_Motion(AX_LOAD_PICKER_Y2, 4);	g_objCommon.Save_Motion(AX_LOAD_PICKER_P2, 2);
			m_tLoadPicker2Loop.Takt_Save(13, 21); m_tLoadPicker2Loop.Takt_Start(13, 22); 
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 42:
		n2LPVisionNo = 0;
		if (m_nVisionStage1Case == 0) n2LPVisionNo = 1;
		if (m_nVisionStage2Case == 0) n2LPVisionNo = 2;
		if (m_nVisionStage3Case == 0) n2LPVisionNo = 3;
		if (m_nVisionStage4Case == 0) n2LPVisionNo = 4;

		if (n2LPVisionNo > 0) {
			m_tLoadPicker2Loop.Takt_Save(13, 22); m_tLoadPicker2Loop.Takt_Start(13, 23); 
			g_objCommon.Set_VisionVacuumOn(n2LPVisionNo);
			g_objCommon.Set_LoadPickerDown(n2No);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 43:
		if (g_objCommon.Get_LoadPickerDown(n2No)) {
			m_tLoadPicker2Loop.Takt_Save(13, 23); m_tLoadPicker2Loop.Takt_Start(13, 24); 
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 4);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 44:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 4) ) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, 4);
			m_tLoadPicker2Loop.Takt_Save(13, 24); m_tLoadPicker2Loop.Takt_Start(13, 25); 
			g_objCommon.Set_LoadPickerOpen(n2No);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 45:
		if (g_objCommon.Get_LoadPickerOpen(n2No)) {
			if (!m_tLoadPicker2Loop.Waiting_Time(m_pEquipData->nDelayTime[0])) break;
			m_tLoadPicker2Loop.Takt_Save(13, 25); m_tLoadPicker2Loop.Takt_Start(13, 26); 
			g_objCommon.Set_LoadPickerUp(n2No);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 46:
		if (g_objCommon.Get_LoadPickerUp(n2No)) {
			m_tLoadPicker2Loop.Takt_Save(13, 26); m_tLoadPicker2Loop.Takt_Start(13, 27); 

			gData.sLotID_VisionStage[n2LPVisionNo-1]  = gData.sLotID_LoadPicker[n2No-1];
			gData.nTrayNo_VisionStage[n2LPVisionNo-1] = gData.nTrayNo_LoadPicker[n2No-1];
			gData.nPortNo_VisionStage[n2LPVisionNo-1] = gData.nPortNo_LoadPicker[n2No-1];
			gData.sLotID_VisionStage[4]  = gData.sLotID_VisionStage[n2LPVisionNo-1];

			gData.sLotID_LoadPicker[n2No-1]  = "";
			gData.nTrayNo_LoadPicker[n2No-1] = gData.nPortNo_LoadPicker[n2No-1] = 0;

			for(int i=0; i<10; i++) {
				 gData.InfoVision[n2LPVisionNo-1][i] = gData.InfoLoadPick[n2No-1][i]; gData.InfoLoadPick[n2No-1][i] = 0;
			}
			for(int i=0; i<8; i++) { gLot.nHistory[n2LP][n2LT][n2LM+i][3] = gData.nVisionNo = n2LPVisionNo; }
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(3000);
		}
		break;
	case 47:
//		if (g_objCommon.Get_VisionVacuumOn(n2LPVisionNo, 9, gData.InfoVision[n2LPVisionNo-1])) {
			g_objCommon.Set_VisionVacuumOff(n2LPVisionNo);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 0);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
//		}
		break;
	case 48:
		if (g_objCommon.Get_LoadPickerUp(n2No)) {
			m_pDY03->oAlignMasterIn = TRUE; m_pDY03->oAlignMasterOut = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 49:
		if (m_pDX03->iAlignMasterIn && !m_pDX03->iAlignMasterOut) {
			m_tLoadPicker2Loop.Takt_Save(13, 27); m_tLoadPicker2Loop.Takt_Start(13, 28); 
			g_objCommon.Move_Position(AX_LOAD_PICKER_Y2, 0);
			g_objCommon.Move_Position(AX_LOAD_PICKER_P2, 0);
			m_pDY03->oAlignSlave1In = TRUE; m_pDY03->oAlignSlave1Out = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 50:
		if (m_pDX03->iAlignSlave1In && !m_pDX03->iAlignSlave1Out) {
			m_pDY03->oAlignSlave2In = TRUE; m_pDY03->oAlignSlave2Out = FALSE;
			g_objAJinAXL.Write_Output(3);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 51:
		if (m_pDX03->iAlignSlave2In && !m_pDX03->iAlignSlave2Out) {
			m_tLoadPicker2Loop.Takt_Save(13, 28); m_tLoadPicker2Loop.Takt_Start(13, 29); 
			g_objCommon.Set_VisionVacuumOn(n2LPVisionNo);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 52:
		if (m_pDX03->iAlignSlave1In && !m_pDX03->iAlignSlave1Out && m_pDX03->iAlignSlave2In && !m_pDX03->iAlignSlave2Out) {
			if (!m_tLoadPicker2Loop.Waiting_Time(300)) break;
			m_pDY03->oAlignSlave2In = FALSE; m_pDY03->oAlignSlave2Out = TRUE;
			g_objAJinAXL.Write_Output(3);
			if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0)) {
				g_objCommon.Move_Position(AX_LOAD_PICKER_X2, 1);
			}
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 53:
		if (!m_pDX03->iAlignSlave2In && m_pDX03->iAlignSlave2Out) {
			m_pDY03->oAlignSlave1In = FALSE; m_pDY03->oAlignSlave1Out = TRUE;
			g_objAJinAXL.Write_Output(3);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 54:
		if (!m_pDX03->iAlignSlave1In && m_pDX03->iAlignSlave1Out) {
			m_tLoadPicker2Loop.Takt_Save(13, 29); m_tLoadPicker2Loop.Takt_Start(13, 30); 
			m_pDY03->oAlignMasterIn = FALSE; m_pDY03->oAlignMasterOut = TRUE;
			g_objAJinAXL.Write_Output(3);
			if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0)) {
				g_objCommon.Move_Position(AX_LOAD_PICKER_X2, 1);
			}
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 55:
		if (!m_pDX03->iAlignMasterIn && m_pDX03->iAlignMasterOut) {
			m_tLoadPicker2Loop.Takt_Save(13, 30); m_tLoadPicker2Loop.Takt_Start(13, 31); 
			if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0)) {
				g_objCommon.Move_Position(AX_LOAD_PICKER_X2, 1);
			}
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(3000+m_pEquipData->nDelayTime[4]);
		}
		break;
	case 56:
		if (g_objCommon.Get_VisionVacuumOn(n2LPVisionNo, 9, gData.InfoVision[n2LPVisionNo-1])) {
			if (Check_EemptyVisionStage(n2LPVisionNo)) {
				gData.sLotID_VisionStage[n2LPVisionNo-1] = "";
				gData.nTrayNo_VisionStage[n2LPVisionNo-1] = gData.nPortNo_VisionStage[n2LPVisionNo-1] = 0;

				for(int i=0; i<10; i++) gData.InfoVision[n2LPVisionNo-1][i] = 0;
			} else {
				if (n2LPVisionNo == 1) m_nVisionStage1Case = 1;
				if (n2LPVisionNo == 2) m_nVisionStage2Case = 1;
				if (n2LPVisionNo == 3) m_nVisionStage3Case = 1;
				if (n2LPVisionNo == 4) m_nVisionStage4Case = 1;
			}
			m_nLoadPicker2Case = 70; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 70:
		if (m_nLoadPicker1Case > 21 && m_nLoadPicker1Case < 70) {
			
			m_nLoadPicker2Case = 0; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;
		/*case 60:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0) ) {
		g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, 0);
		m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
		case 61:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0) ) {
		g_objCommon.Save_Motion(AX_LOAD_PICKER_Y2, 0);
		m_tLoadPicker2Loop.Takt_Save(13, 31); m_tLoadPicker2Loop.Takt_Start(13, 32); 
		g_objCommon.Move_Position(AX_LOAD_PICKER_X2, 1);
		m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
		case 62:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X2, 1) && g_objCommon.Check_Position(AX_LOAD_PICKER_P2, 0) ) {
		g_objCommon.Save_Motion(AX_LOAD_PICKER_X2, 1);
		m_tLoadPicker2Loop.Takt_Save(13, 32, TRUE);
		m_nLoadPicker2Case = 70; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;

		case 70:
		if (m_nLoadPicker1Case > 21 && m_nLoadPicker1Case < 70) {
		g_objCommon.Move_Position(AX_LOAD_PICKER_Y2, 1);
		m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;
		case 71:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 1) ) {
		g_objCommon.Save_Motion(AX_LOAD_PICKER_Y2, 1);
		m_nLoadPicker2Case = 0; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;*/

	case 81:
		if (g_objCommon.Get_LoadPickerUp(n2No)) {
			if (g_objCommon.Get_LoadPickerCheck(n2No, 9, 0, gData.InfoLoadPick[n2No-1])) {
				m_nLoadPicker2Case = 10; m_tLoadPicker2Loop.Set_LoopTime(30000);
			} else {
				for(int i=0; i<4; i++) {
					if (gData.nLoadPicker2ErrNo[i] == 1) {
						g_objCommon.Set_LoadPickerOpen(n2No, 9, i+1);
					}
				}
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 82:
		if (g_objCommon.Get_LoadPickerUp(n2No)) {
			if (!m_tLoadPicker2Loop.Waiting_Time(500)) break;
			g_objCommon.Set_LoadPickerDown(n2No, 1);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 83:
		if (g_objCommon.Get_LoadPickerDown(n2No, 1)) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, nLPStage2No);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 84:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, nLPStage2No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, nLPStage2No);
			m_nLoadPicker2Case = 7; m_tLoadPicker2Loop.Set_LoopTime(5000);
		}
		break;

	case 85:
		if (g_objCommon.Get_LoadPickerUp(n2No)) {
			if (g_objCommon.Get_LoadPickerCheck(n2No, 9, 0, gData.InfoLoadPick[n2No-1])) {
				m_nLoadPicker2Case = 17; m_tLoadPicker2Loop.Set_LoopTime(30000);
			} else {
				for(int i=4; i<8; i++) {
					if (gData.nLoadPicker2ErrNo[i] == 1) {
						g_objCommon.Set_LoadPickerOpen(n2No, 9, i+1);
					}
				}
				m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 86:
		if (g_objCommon.Get_LoadPickerUp(n2No)) {
			if (!m_tLoadPicker2Loop.Waiting_Time(500)) break;
			g_objCommon.Set_LoadPickerDown(n2No, 2);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 87:
		if (g_objCommon.Get_LoadPickerDown(n2No, 2)) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, nLPStage2No);
			m_nLoadPicker2Case++; m_tLoadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 88:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, nLPStage2No)) {
			g_objCommon.Save_Motion(AX_LOAD_PICKER_Z2, nLPStage2No);
			m_nLoadPicker2Case = 14; m_tLoadPicker2Loop.Set_LoopTime(5000);
		}
		break;

	}

	// 13. (Error : 5500)
	if (m_tLoadPicker2Loop.Over_LoopTime()) {
//		if (m_nLoadPicker2Case == 28 || m_nLoadPicker2Case == 34) {
//			nL2Retry++;
//			if (nL2Retry == 1) { m_nLoadPicker2Case--; return TRUE; }
//		}
//		if (m_nLoadPicker2Case == 27 || m_nLoadPicker2Case == 33) m_nLoadPicker2Case++;
		g_objCommon.Show_Error(5500 + m_nLoadPicker2Case);
		return FALSE;
	}
	return TRUE;
}

// 14. (Error : 6000)
BOOL CSequenceMain::Run_VisionStage1()
{
	static int nS1No = 1;		//1,2,3,4(고정)
	static int n1Tno1, n1Tno5, n1FrontVisionCase, nV1Retry;
	static double dStage1PosX = 0, dVision1PosZ = 0;
	static DWORD dwV1RosTime[3];	//Top2,Buffer,Unload

	n1FrontVisionCase = m_nVisionStage3Case;
	switch (m_nVisionStage1Case) {
	case 0:	// Wait
		m_tVisionStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (( m_pEquipData->bUseTopAng && n1FrontVisionCase > 14) ||
			(!m_pEquipData->bUseTopAng && n1FrontVisionCase > 4)) {
			m_sLog.Format("[Inspection Stage1: Start] Inspection Stage3 Case(%d)", n1FrontVisionCase);
			g_objLogFile.Save_HandlerLog(m_sLog);

			m_tVisionStage1Loop.Takt_Start(14, 1, TRUE); 
			m_pDY07->oInspectStage1Deg0 = TRUE; m_pDY07->oInspectStage1Deg90 = FALSE;
			g_objAJinAXL.Write_Output(7);

			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 2:
		if (!m_pDX03->iAlignSlave1In && m_pDX03->iAlignSlave1Out && !m_pDX03->iAlignSlave2In && m_pDX03->iAlignSlave2Out && !m_pDX03->iAlignMasterIn && m_pDX03->iAlignMasterOut) {
			if (m_pDX07->iInspectStage1Up && !m_pDX07->iInspectStage1Down) {
				if (m_pDX07->iInspectStage1Yin && !m_pDX07->iInspectStage1YOut) {
					if (n1FrontVisionCase > 14) {
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 1);	//Top1
					} else {
						dStage1PosX = m_pMoveData->dVisionStageX1[0] + ALIGN_TOP1_POS;
						g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X1, dStage1PosX);
					}
					m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
				}
			}
		}
		break;
	case 3:	//Align->Top1 Scan 대기
		if (n1FrontVisionCase > 14) {
#ifdef NEW_FINAL
				if (m_pEquipData->bUseTopAng) {
					//dVision1PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS1No-1][0];
					dVision1PosZ = m_pMoveData->dTOPVisionZ1[1];
					g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision1PosZ);
					m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
				} else {
					if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X1)) {
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 1);	//Top1
						//dVision1PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS1No-1][0];
						dVision1PosZ = m_pMoveData->dTOPVisionZ1[1];
						g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision1PosZ);
						m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
					}
				}
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 1)) {
				if (m_pEquipData->bUseTopAng) {
					g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
					//dVision1PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS1No-1][0];
					dVision1PosZ = m_pMoveData->dTOPVisionZ1[1];
					g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision1PosZ);
					m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
				} else {
					if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X1)) {
						g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 1);	//Top1
						//dVision1PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS1No-1][0];
						dVision1PosZ = m_pMoveData->dTOPVisionZ1[1];
						g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision1PosZ);
						m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
					}
				}
			}
#endif
		} else {
			if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X1)) {
				if (n1FrontVisionCase > 6 && gData.nTop1Cnt > 0) {
					if (gData.nTop1Cnt > 3) gData.nTop1Cnt = 3;
					dStage1PosX = m_pMoveData->dVisionStageX1[0] + ALIGN_TOP1_POS + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
					double dStagePos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X1);
					if (dStagePos != dStage1PosX) g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X1, dStage1PosX);
				}
			}
			m_tVisionStage1Loop.Set_LoopTime(10000);
		}
		return TRUE;

	case 4:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 1)) {
			if (m_pDX07->iInspectStage1Deg0) {
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, 1);
				m_tVisionStage1Loop.Takt_Save(14, 1); m_tVisionStage1Loop.Takt_Start(14, 2); 
				gData.nVisionPos[1][0] = 0; gData.nVisionPos[1][1] = nS1No;
				gData.nTop1Cnt = gData.nScanRetry[1] = 0;
				n1Tno1 = gData.InfoVision[nS1No-1][9];
				n1Tno5 = gData.InfoVision[nS1No-1][9] + 4;
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 5:	//Top2 Scan 대기
		if (n1FrontVisionCase >= 22 || (n1FrontVisionCase >= 17 && gData.nTop1Cnt <= 1) || (n1FrontVisionCase >= 17 && gData.nTop2Cnt >= gData.nTop1Cnt)) {
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(20000);
		}
		return TRUE;

	case 6:
		if (m_pDX07->iInspectStage1Up && !m_pDX07->iInspectStage1Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
				m_tVisionStage1Loop.Takt_Save(14, 2); m_tVisionStage1Loop.Takt_Start(14, 3); 
				dStage1PosX = m_pMoveData->dVisionStageX1[1] + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X1, dStage1PosX);
//				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);	nV1Retry = 0;
				//dVision1PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS1No-1][gData.nTop1Cnt];
				dVision1PosZ = m_pMoveData->dTOPVisionZ1[1];
				g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision1PosZ);	nV1Retry = 0;
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 7:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X1, dStage1PosX)) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#else
			if (g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 1) && g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#endif
				if (!m_tVisionStage1Loop.Waiting_Time(m_pEquipData->nDelayTime[3])) break;
#ifdef NEW_FINAL
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, -1, dStage1PosX);
#else
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, -1, dStage1PosX);	g_objCommon.Save_Motion(AX_TOP1_LIGHT_Z, 1);
#endif
				m_tVisionStage1Loop.Takt_Save(14, 3); m_tVisionStage1Loop.Takt_Start(14, 4); 
				gData.bTop1ScanDone = FALSE;	gData.nVsNo[0] = nS1No; gData.nVsIx[0] = gData.nTop1Cnt+1;
				int nModule1 = n1Tno1; if (gData.InfoVision[nS1No-1][gData.nTop1Cnt] < 1)   nModule1 = -1;
				int nModule5 = n1Tno5; if (gData.InfoVision[nS1No-1][gData.nTop1Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC2, "T1", gData.sLotID_VisionStage[nS1No-1], gData.nPortNo_VisionStage[nS1No-1], gData.nTrayNo_VisionStage[nS1No-1], nModule1, gData.nTrayNo_VisionStage[nS1No-1], nModule5);
				gAlm.sAlmLID[2] = gData.sLotID_VisionStage[nS1No-1]; gAlm.nAlmTNo[2] = gData.nTrayNo_VisionStage[nS1No-1]; gAlm.nAlmPNo[2] = nModule1;
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 8:
		if (gData.bTop1ScanDone || !m_pEquipData->bUseTop1) {
			m_tVisionStage1Loop.Takt_Save(14, 4); m_tVisionStage1Loop.Takt_Start(14, 5); 
			gData.nTop1Cnt++; n1Tno1++; n1Tno5++;
			if (gData.nTop1Cnt >= 4) {
				if (m_pEquipData->bUseTopAng) {
					gData.nTop1Cnt = 0;
					n1Tno1 = gData.InfoVision[nS1No-1][9];
					n1Tno5 = gData.InfoVision[nS1No-1][9] + 4;

					g_objCommon.Move_Position(AX_TOP1_VISION_Z, 2);
					g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 1);
#ifdef NEW_FINAL
#else
					g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 2);
#endif
					m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
				} else {
					m_nVisionStage1Case = 12; m_tVisionStage1Loop.Set_LoopTime(5000);
				}
			} else {
				m_nVisionStage1Case = 5; m_tVisionStage1Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 9:	//Top1-Angle
#ifdef NEW_FINAL
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2)) {
			g_objCommon.Save_Motion(AX_TOP1_VISION_Z, 2); gData.nScanRetry[1] = 0;
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(30000);
		}
#else
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2) && g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 2) ) {
			g_objCommon.Save_Motion(AX_TOP1_VISION_Z, 2);	g_objCommon.Save_Motion(AX_TOP1_LIGHT_Z, 2);
			g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 2); gData.nScanRetry[1] = 0;
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(30000);
		}
#endif
		break;
	case 10:	//Top1-Angle
		if (m_pDX07->iInspectStage1Up && !m_pDX07->iInspectStage1Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
				m_tVisionStage1Loop.Takt_Save(14, 5); m_tVisionStage1Loop.Takt_Start(14, 6); 
				dStage1PosX = m_pMoveData->dVisionStageX1[1] + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X1, dStage1PosX);
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 2);	nV1Retry = 0;
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X1, dStage1PosX)) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 2) && g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#endif
				if (!m_tVisionStage1Loop.Waiting_Time(m_pEquipData->nDelayTime[9])) break;
#ifdef NEW_FINAL
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, -1, dStage1PosX);
#else
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, -1, dStage1PosX);	g_objCommon.Save_Motion(AX_TOP1_ANGLE_Y, 2);
#endif
				m_tVisionStage1Loop.Takt_Save(14, 6); m_tVisionStage1Loop.Takt_Start(14, 7); 
				gData.bTop1ScanDone = FALSE;	gData.nVsNo[0] = nS1No; gData.nVsIx[0] = gData.nTop1Cnt+1;
				int nModule1 = n1Tno1; if (gData.InfoVision[nS1No-1][gData.nTop1Cnt] < 1)   nModule1 = -1;
				int nModule5 = n1Tno5; if (gData.InfoVision[nS1No-1][gData.nTop1Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC2, "TG", gData.sLotID_VisionStage[nS1No-1], gData.nPortNo_VisionStage[nS1No-1], gData.nTrayNo_VisionStage[nS1No-1], nModule1, gData.nTrayNo_VisionStage[nS1No-1], nModule5);
				gAlm.sAlmLID[2] = gData.sLotID_VisionStage[nS1No-1]; gAlm.nAlmTNo[2] = gData.nTrayNo_VisionStage[nS1No-1]; gAlm.nAlmPNo[2] = nModule1;
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 12:
		if (gData.bTop1ScanDone || !m_pEquipData->bUseTopAng) {
			m_tVisionStage1Loop.Takt_Save(14, 7); m_tVisionStage1Loop.Takt_Start(14, 8); 
			gData.nTop1Cnt++; n1Tno1++; n1Tno5++;
			if (gData.nTop1Cnt >= 4) {
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
#ifdef NEW_FINAL
#else
				g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 1);
#endif
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
			} else {
				m_nVisionStage1Case = 10; m_tVisionStage1Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 13:
		if (n1FrontVisionCase > 22) {
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 14:
		if (m_pDX07->iInspectStage1Up && !m_pDX07->iInspectStage1Down) {
			if (m_pDX07->iInspectStage1Yin && !m_pDX07->iInspectStage1YOut) {
				m_tVisionStage1Loop.Takt_Save(14, 8); m_tVisionStage1Loop.Takt_Start(14, 9); 
				m_pDY07->oInspectStage1Deg0 = FALSE; m_pDY07->oInspectStage1Deg90 = TRUE;
				g_objAJinAXL.Write_Output(7);
//				g_objCommon.Move_Position(AX_TOP2_VISION_Z, 1);
				g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 2);		//Top2
				//dVision1PosZ = m_pMoveData->dTOPVisionZ2[1] + gData.dFocusOffset[nS1No-1][4];
				dVision1PosZ = m_pMoveData->dTOPVisionZ2[1];
				g_objAJinAXL.Move_Absolute(AX_TOP2_VISION_Z, dVision1PosZ);
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 2)) {
//			if (g_objCommon.Check_Position(AX_TOP2_VISION_Z, 1)) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				if (m_pDX07->iInspectStage1Deg90) {
					g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, 2);	g_objCommon.Save_Motion(AX_TOP2_VISION_Z, 1);
					m_tVisionStage1Loop.Takt_Save(14, 9); m_tVisionStage1Loop.Takt_Start(14, 10); 
					gData.nVisionPos[1][1] = 0; gData.nVisionPos[1][2] = nS1No;
					gData.nTop2Cnt = gData.nScanRetry[2] = 0;
					n1Tno1 = gData.InfoVision[nS1No-1][9];
					n1Tno5 = gData.InfoVision[nS1No-1][9] + 4;
					m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(20000);
				}
			}
		}
		break;
	case 16:
		if (m_pDX07->iInspectStage1Up && !m_pDX07->iInspectStage1Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				m_tVisionStage1Loop.Takt_Save(14, 10); m_tVisionStage1Loop.Takt_Start(14, 11); 
				dStage1PosX = m_pMoveData->dVisionStageX1[2] + (m_pEquipData->dPitchTop * gData.nTop2Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X1, dStage1PosX);
//				g_objCommon.Move_Position(AX_TOP2_VISION_Z, 1);
				//dVision1PosZ = m_pMoveData->dTOPVisionZ2[1] + gData.dFocusOffset[nS1No-1][4+gData.nTop2Cnt];
				dVision1PosZ = m_pMoveData->dTOPVisionZ2[1];
				g_objAJinAXL.Move_Absolute(AX_TOP2_VISION_Z, dVision1PosZ);	nV1Retry = 0;
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X1, dStage1PosX)) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				if (!m_tVisionStage1Loop.Waiting_Time(m_pEquipData->nDelayTime[9])) break;
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, -1, dStage1PosX);
				m_tVisionStage1Loop.Takt_Save(14, 11); m_tVisionStage1Loop.Takt_Start(14, 12); 
				gData.bTop2ScanDone = FALSE;	gData.nVsNo[1] = nS1No; gData.nVsIx[1] = gData.nTop2Cnt+1;
				int nModule1 = n1Tno1; if (gData.InfoVision[nS1No-1][gData.nTop2Cnt] < 1)   nModule1 = -1;
				int nModule5 = n1Tno5; if (gData.InfoVision[nS1No-1][gData.nTop2Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC3, "T2", gData.sLotID_VisionStage[nS1No-1], gData.nPortNo_VisionStage[nS1No-1], gData.nTrayNo_VisionStage[nS1No-1], nModule1, gData.nTrayNo_VisionStage[nS1No-1], nModule5);
				gAlm.sAlmLID[3] = gData.sLotID_VisionStage[nS1No-1]; gAlm.nAlmTNo[3] = gData.nTrayNo_VisionStage[nS1No-1]; gAlm.nAlmPNo[3] = nModule1;
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 18:
		if (gData.bTop2ScanDone || !m_pEquipData->bUseTop2) {
			m_tVisionStage1Loop.Takt_Save(14, 12); m_tVisionStage1Loop.Takt_Start(14, 13); 
			gData.nTop2Cnt++; n1Tno1++; n1Tno5++;
			if (gData.nTop2Cnt >= 4) {
				dwV1RosTime[0] = GetTickCount();
				m_nVisionStage1Case = 20; m_tVisionStage1Loop.Set_LoopTime(5000);
			} 
			else 
			{
				m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 19:	//Buffer에 있으면 Scan 1번하고 대기
		if (n1FrontVisionCase < 19 || (n1FrontVisionCase >= 23 && gData.nTop2Cnt <= 1) || n1FrontVisionCase >= 25) {
			m_nVisionStage1Case = 16; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 20:
		if (n1FrontVisionCase < 20 || n1FrontVisionCase >= 25) {
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 21:
		if (m_pDX07->iInspectStage1Up && !m_pDX07->iInspectStage1Down) {
			if (m_pDX07->iInspectStage1Yin && !m_pDX07->iInspectStage1YOut) {
				if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X1, dStage1PosX)) {
					m_tVisionStage1Loop.Takt_Save(14, 13); m_tVisionStage1Loop.Takt_Start(14, 14); 
					g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 4);
					m_pDY07->oInspectStage1Deg0 = TRUE; m_pDY07->oInspectStage1Deg90 = FALSE;
					g_objAJinAXL.Write_Output(7);
					m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
				}
			}
		}
		break;
	case 22:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 4)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, 4);
			m_tVisionStage1Loop.Takt_Save(14, 14); m_tVisionStage1Loop.Takt_Start(14, 15); 
			dwV1RosTime[1] = dwV1RosTime[0];
			gData.nVisionPos[1][2] = 0; gData.nVisionPos[1][4] = nS1No;
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
		}
		break;
	case 23:
		if (n1FrontVisionCase < 22 || n1FrontVisionCase > 34) {
			m_tVisionStage1Loop.Takt_Save(14, 15); m_tVisionStage1Loop.Takt_Start(14, 16); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 3);
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 24:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, 3);
			m_tVisionStage1Loop.Takt_Save(14, 16); m_tVisionStage1Loop.Takt_Start(14, 17); 
			dwV1RosTime[2] = dwV1RosTime[1];
			gData.nVisionPos[1][4] = 0; gData.nVisionPos[1][3] = nS1No;
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 25:
			m_nVisionStage1Case = 30; m_tVisionStage1Loop.Set_LoopTime(30000);
		break;
	case 26:	//RosTime 6초대기
		if (GetTickCount() - dwV1RosTime[2] >= 6000) 
		{
			m_nVisionStage1Case = 30; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	//Unload Picker wait
		m_tVisionStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 31:
		if (m_pDX07->iInspectStage1Up && !m_pDX07->iInspectStage1Down) 
		{
			if (m_pDX07->iInspectStage1Yin && !m_pDX07->iInspectStage1YOut) 
			{			
				if (n1FrontVisionCase < 30 || n1FrontVisionCase > 52)
				{
					/*double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage3Case);
					double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX3[INSPECT_STAGE3_X_Top2Pos];
					if(dTarget < dCurrent) return TRUE;*/
					
					m_pDY07->oInspectStage1Up = FALSE; m_pDY07->oInspectStage1Down = TRUE;
					g_objAJinAXL.Write_Output(7);
					m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
				}				
			}
		}
		return TRUE;	
	case 32:
		if (!m_pDX07->iInspectStage1Up && m_pDX07->iInspectStage1Down)
		{
			m_tVisionStage1Loop.Takt_Save(14, 18); m_tVisionStage1Loop.Takt_Start(14, 19); 
			gData.nVisionPos[1][3] = 0; gData.nVisionPos[0][3] = nS1No;
			if (nS1No == 1) 
			{
				m_pDY07->oInspectStage1Yin = FALSE; m_pDY07->oInspectStage1YOut = TRUE;
				g_objAJinAXL.Write_Output(7);
			}
			if (nS1No == 4) 
			{
				m_pDY08->oInspectStage4Yin = FALSE; m_pDY08->oInspectStage4YOut = TRUE;
				g_objAJinAXL.Write_Output(8);
			}
			m_nVisionStage1Case = 34; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 34:
		if ((nS1No == 1 && !m_pDX07->iInspectStage1Yin && m_pDX07->iInspectStage1YOut) ||
			(nS1No == 2) || (nS1No == 3) ||
			(nS1No == 4 && !m_pDX08->iInspectStage4Yin && m_pDX08->iInspectStage4YOut) ) 
		{
			m_tVisionStage1Loop.Takt_Save(14, 19); m_tVisionStage1Loop.Takt_Start(14, 20); 
			m_nVisionStage1Case = 35; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 35:
		if (n1FrontVisionCase >= 0 && n1FrontVisionCase < 31) 
		{
			m_nVisionStage1Case = 61; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		else if (n1FrontVisionCase < 50 || n1FrontVisionCase >= 70) 
		{
			double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage3Case);
			double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX3[INSPECT_STAGE3_X_AlignPos];
			if(dTarget < dCurrent) return TRUE;

			m_nVisionStage1Case = 51; m_tVisionStage1Loop.Set_LoopTime(5000);
		}	
		else if (n1FrontVisionCase < 40 || n1FrontVisionCase >= 60) 
		{
			double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage3Case);
			double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX3[INSPECT_STAGE3_X_Top2Pos];
			if(dTarget < dCurrent && !Check_ModuleEmpty() ) return TRUE;

			m_nVisionStage1Case = 41; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 40:
		if (n1FrontVisionCase < 40 || n1FrontVisionCase >= 60) 
		{
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 41:
		if (!m_pDX07->iInspectStage1Up && m_pDX07->iInspectStage1Down) 
		{
			m_tVisionStage1Loop.Takt_Save(14, 20); m_tVisionStage1Loop.Takt_Start(14, 21); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_Top2Pos);
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
		}
		break;

	case 42:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_Top2Pos)) 
{
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_Top2Pos);
			m_tVisionStage1Loop.Takt_Save(14, 21); m_tVisionStage1Loop.Takt_Start(14, 22); 
			gData.nVisionPos[0][3] = 0; gData.nVisionPos[0][2] = nS1No;
			m_nVisionStage1Case = 50; m_tVisionStage1Loop.Set_LoopTime(60000);
		}
		break;
	case 50:
		if (n1FrontVisionCase < 50 || n1FrontVisionCase >= 70)
		{
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 51:
		if (!m_pDX07->iInspectStage1Up && m_pDX07->iInspectStage1Down)
		{
			m_tVisionStage1Loop.Takt_Save(14, 22); m_tVisionStage1Loop.Takt_Start(14, 23); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_Top1Pos);
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
		}
		break;
	case 52:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_Top1Pos))
		{
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_Top1Pos);
			m_tVisionStage1Loop.Takt_Save(14, 23); m_tVisionStage1Loop.Takt_Start(14, 24); 
			gData.nVisionPos[0][2] = 0; gData.nVisionPos[0][1] = nS1No;
			m_nVisionStage1Case = 60; m_tVisionStage1Loop.Set_LoopTime(60000);
		}
		break;
	case 60:
		if (n1FrontVisionCase >= 0 && n1FrontVisionCase < 50) {
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 61:
		if (!m_pDX07->iInspectStage1Up && m_pDX07->iInspectStage1Down) {
			m_tVisionStage1Loop.Takt_Save(14, 24); m_tVisionStage1Loop.Takt_Start(14, 25); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_AlignPos);
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
		}
		break;
	case 62:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_AlignPos)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X1, INSPECT_STAGE1_X_AlignPos);
			m_tVisionStage1Loop.Takt_Save(14, 25); m_tVisionStage1Loop.Takt_Start(14, 26); 
			gData.nVisionPos[0][1] = 0; gData.nVisionPos[0][0] = nS1No;
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(10000);
		}
		break;
	case 63:
		if (!m_pDX07->iInspectStage1Up && m_pDX07->iInspectStage1Down) {
/*			if (nS1No == 1) {
				m_pDY07->oInspectStage1Yin = TRUE; m_pDY07->oInspectStage1YOut = FALSE;
				g_objAJinAXL.Write_Output(7);
			}
			if (nS1No == 4) {
				m_pDY08->oInspectStage4Yin = TRUE; m_pDY08->oInspectStage4YOut = FALSE;
				g_objAJinAXL.Write_Output(8);
			}*/
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 64:
//		if ((nS1No == 1 && m_pDX07->iInspectStage1Yin && !m_pDX07->iInspectStage1YOut) ||
//			(nS1No == 2) || (nS1No == 3) ||
//			(nS1No == 4 && m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) ) {
			m_nVisionStage1Case = 70; m_tVisionStage1Loop.Set_LoopTime(5000);
//		}
		break;

	case 70:
		if (n1FrontVisionCase > 4 && n1FrontVisionCase < 60) {
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 71:
		if (!m_pDX07->iInspectStage1Up && m_pDX07->iInspectStage1Down) {
			m_tVisionStage1Loop.Takt_Save(14, 26); m_tVisionStage1Loop.Takt_Start(14, 27); 
			if (nS1No == 1) {
				m_pDY07->oInspectStage1Yin = TRUE; m_pDY07->oInspectStage1YOut = FALSE;
				g_objAJinAXL.Write_Output(7);
			}
			if (nS1No == 4) {
				m_pDY08->oInspectStage4Yin = TRUE; m_pDY08->oInspectStage4YOut = FALSE;
				g_objAJinAXL.Write_Output(8);
			}
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 72:
		if (m_pDX07->iInspectStage1Yin && !m_pDX07->iInspectStage1YOut) {
			m_tVisionStage1Loop.Takt_Save(14, 27); m_tVisionStage1Loop.Takt_Start(14, 28); 
			m_pDY07->oInspectStage1Up = TRUE; m_pDY07->oInspectStage1Down = FALSE;
			g_objAJinAXL.Write_Output(7);
			m_nVisionStage1Case++; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 73:
		if (m_pDX07->iInspectStage1Up && !m_pDX07->iInspectStage1Down) {
			m_tVisionStage1Loop.Takt_Save(14, 28, TRUE);
			gData.nVisionPos[0][0] = 0; gData.nVisionPos[1][0] = nS1No;
			m_nVisionStage1Case = 0; m_tVisionStage1Loop.Set_LoopTime(5000);
		}
		break;

	}

	// 14. (Error : 6000)
	if (m_tVisionStage1Loop.Over_LoopTime()) {
//		if (m_nVisionStage1Case == 8 || m_nVisionStage1Case == 12 || m_nVisionStage1Case == 18) {
//			nV1Retry++;
//			if (nV1Retry == 1) { m_nVisionStage1Case--; return TRUE; }
//		}
//		if (m_nVisionStage1Case == 7 || m_nVisionStage1Case == 11 || m_nVisionStage1Case == 17) m_nVisionStage1Case++;
		if (m_nVisionStage1Case == 26) { m_nVisionStage1Case = 30; return TRUE; }
		g_objCommon.Show_Error(6000 + m_nVisionStage1Case);
		return FALSE;
	}
	return TRUE;
}

// 15. (Error : 6200)
BOOL CSequenceMain::Run_VisionStage2()
{
	static int nS2No = 2;		//1,2,3,4(고정)
	static int n2Tno1, n2Tno5, n2FrontVisionCase, nV2Retry;
	static double dStage2PosX = 0, dVision2PosZ = 0;
	static DWORD dwV2RosTime[3];	//Top2,Buffer,Unload

	n2FrontVisionCase = m_nVisionStage1Case;
	switch (m_nVisionStage2Case) {
	case 0:	// Wait
		m_tVisionStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (( m_pEquipData->bUseTopAng && n2FrontVisionCase > 14) ||
			(!m_pEquipData->bUseTopAng && n2FrontVisionCase > 4)) {
			m_sLog.Format("[Inspection Stage2: Start] Inspection Stage1 Case(%d)", n2FrontVisionCase);
			g_objLogFile.Save_HandlerLog(m_sLog);

			m_tVisionStage2Loop.Takt_Start(15, 1, TRUE); 
			m_pDY07->oInspectStage2Deg0 = TRUE; m_pDY07->oInspectStage2Deg90 = FALSE;
			g_objAJinAXL.Write_Output(7);

			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 2:
		if (!m_pDX03->iAlignSlave1In && m_pDX03->iAlignSlave1Out && !m_pDX03->iAlignSlave2In && m_pDX03->iAlignSlave2Out && !m_pDX03->iAlignMasterIn && m_pDX03->iAlignMasterOut) {
			if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) {
				if (n2FrontVisionCase > 14) {
					g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 1);
				} else {
					dStage2PosX = m_pMoveData->dVisionStageX2[0] + ALIGN_TOP1_POS;
					g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X2, dStage2PosX);
				}
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 3:
		if (n2FrontVisionCase > 14) {
#ifdef NEW_FINAL
				if (m_pEquipData->bUseTopAng) {
					//dVision2PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS2No-1][0];
					dVision2PosZ = m_pMoveData->dTOPVisionZ1[1];
					g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision2PosZ);
					m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
				} else {
					if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X2)) {
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 1);
						//dVision2PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS2No-1][0];
						dVision2PosZ = m_pMoveData->dTOPVisionZ1[1];
						g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision2PosZ);
						m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
					}
				}
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 1)) {
				if (m_pEquipData->bUseTopAng) {
					g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
					//dVision2PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS2No-1][0];
					dVision2PosZ = m_pMoveData->dTOPVisionZ1[1];
					g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision2PosZ);
					m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
				} else {
					if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X2)) {
						g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 1);
						//dVision2PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS2No-1][0];
						dVision2PosZ = m_pMoveData->dTOPVisionZ1[1];
						g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision2PosZ);
						m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
					}
				}
			}
#endif
		} else {
			if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X2)) {
				if (n2FrontVisionCase > 6 && gData.nTop1Cnt > 0) {
					if (gData.nTop1Cnt > 3) gData.nTop1Cnt = 3;
					dStage2PosX = m_pMoveData->dVisionStageX2[0] + ALIGN_TOP1_POS + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
					double dStagePos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X2);
					if (dStagePos != dStage2PosX) g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X2, dStage2PosX);
				}
			}
			m_tVisionStage2Loop.Set_LoopTime(10000);
		}
		return TRUE;

	case 4:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 1)) {
			if (m_pDX07->iInspectStage2Deg0) {
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, 1);
				m_tVisionStage2Loop.Takt_Save(15, 1); m_tVisionStage2Loop.Takt_Start(15, 2); 
				gData.nVisionPos[1][0] = 0; gData.nVisionPos[1][1] = nS2No;
				gData.nTop1Cnt = gData.nScanRetry[1] = 0;
				n2Tno1 = gData.InfoVision[nS2No-1][9];
				n2Tno5 = gData.InfoVision[nS2No-1][9] + 4;
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 5:
		if (n2FrontVisionCase >= 22 || (n2FrontVisionCase >= 17 && gData.nTop1Cnt <= 1) || (n2FrontVisionCase >= 17 && gData.nTop2Cnt >= gData.nTop1Cnt)) {
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(20000);
		}
		return TRUE;
	case 6:
		if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
				m_tVisionStage2Loop.Takt_Save(15, 2); m_tVisionStage2Loop.Takt_Start(15, 3); 
				dStage2PosX = m_pMoveData->dVisionStageX2[1] + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X2, dStage2PosX);
//				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
				//dVision2PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS2No-1][gData.nTop1Cnt];
				dVision2PosZ = m_pMoveData->dTOPVisionZ1[1];
				g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision2PosZ);	nV2Retry = 0;
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 7:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X2, dStage2PosX)) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#else
			if (g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 1) && g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#endif
				if (!m_tVisionStage2Loop.Waiting_Time(m_pEquipData->nDelayTime[3])) break;
#ifdef NEW_FINAL
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, -1, dStage2PosX);
#else
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, -1, dStage2PosX);	g_objCommon.Save_Motion(AX_TOP1_LIGHT_Z, 1);
#endif
				m_tVisionStage2Loop.Takt_Save(15, 3); m_tVisionStage2Loop.Takt_Start(15, 4); 
				gData.bTop1ScanDone = FALSE;	gData.nVsNo[0] = nS2No; gData.nVsIx[0] = gData.nTop1Cnt+1;
				int nModule1 = n2Tno1; if (gData.InfoVision[nS2No-1][gData.nTop1Cnt] < 1)   nModule1 = -1;
				int nModule5 = n2Tno5; if (gData.InfoVision[nS2No-1][gData.nTop1Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC2, "T1", gData.sLotID_VisionStage[nS2No-1], gData.nPortNo_VisionStage[nS2No-1], gData.nTrayNo_VisionStage[nS2No-1], nModule1, gData.nTrayNo_VisionStage[nS2No-1], nModule5);
				gAlm.sAlmLID[2] = gData.sLotID_VisionStage[nS2No-1]; gAlm.nAlmTNo[2] = gData.nTrayNo_VisionStage[nS2No-1]; gAlm.nAlmPNo[2] = nModule1;
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 8:
		if (gData.bTop1ScanDone || !m_pEquipData->bUseTop1) {
			m_tVisionStage2Loop.Takt_Save(15, 4); m_tVisionStage2Loop.Takt_Start(15, 5); 
			gData.nTop1Cnt++; n2Tno1++; n2Tno5++;
			if (gData.nTop1Cnt >= 4) {
				if (m_pEquipData->bUseTopAng) {
					gData.nTop1Cnt = 0;
					n2Tno1 = gData.InfoVision[nS2No-1][9];
					n2Tno5 = gData.InfoVision[nS2No-1][9] + 4;

					g_objCommon.Move_Position(AX_TOP1_VISION_Z, 2);
					g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 1);
#ifdef NEW_FINAL
#else
					g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 2);
#endif
					m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(30000);
				} else {
					m_nVisionStage2Case = 12; m_tVisionStage2Loop.Set_LoopTime(5000);
				}
			} else {
				m_nVisionStage2Case = 5; m_tVisionStage2Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 9:	//Top1-Angle
#ifdef NEW_FINAL
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2)) {
			g_objCommon.Save_Motion(AX_TOP1_VISION_Z, 2); gData.nScanRetry[1] = 0;
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(30000);
		}
#else
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2) && g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 2) ) {
			g_objCommon.Save_Motion(AX_TOP1_VISION_Z, 2);	g_objCommon.Save_Motion(AX_TOP1_LIGHT_Z, 2);
			g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 2); gData.nScanRetry[1] = 0;
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(30000);
		}
#endif
		break;
	case 10:
		if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
				m_tVisionStage2Loop.Takt_Save(15, 5); m_tVisionStage2Loop.Takt_Start(15, 6); 
				dStage2PosX = m_pMoveData->dVisionStageX2[1] + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X2, dStage2PosX);
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 2);	nV2Retry = 0;
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X2, dStage2PosX)) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 2) && g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#endif
				if (!m_tVisionStage2Loop.Waiting_Time(m_pEquipData->nDelayTime[9])) break;
#ifdef NEW_FINAL
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, -1, dStage2PosX);
#else
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, -1, dStage2PosX);	g_objCommon.Save_Motion(AX_TOP1_ANGLE_Y, 2);
#endif
				m_tVisionStage2Loop.Takt_Save(15, 6); m_tVisionStage2Loop.Takt_Start(15, 7); 
				gData.bTop1ScanDone = FALSE;	gData.nVsNo[0] = nS2No; gData.nVsIx[0] = gData.nTop1Cnt+1;
				int nModule1 = n2Tno1; if (gData.InfoVision[nS2No-1][gData.nTop1Cnt] < 1)   nModule1 = -1;
				int nModule5 = n2Tno5; if (gData.InfoVision[nS2No-1][gData.nTop1Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC2, "TG", gData.sLotID_VisionStage[nS2No-1], gData.nPortNo_VisionStage[nS2No-1], gData.nTrayNo_VisionStage[nS2No-1], nModule1, gData.nTrayNo_VisionStage[nS2No-1], nModule5);
				gAlm.sAlmLID[2] = gData.sLotID_VisionStage[nS2No-1]; gAlm.nAlmTNo[2] = gData.nTrayNo_VisionStage[nS2No-1]; gAlm.nAlmPNo[2] = nModule1;
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 12:
		if (gData.bTop1ScanDone || !m_pEquipData->bUseTopAng) {
			m_tVisionStage2Loop.Takt_Save(15, 7); m_tVisionStage2Loop.Takt_Start(15, 8); 
			gData.nTop1Cnt++; n2Tno1++; n2Tno5++;
			if (gData.nTop1Cnt >= 4) {
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
#ifdef NEW_FINAL
#else
				g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 1);
#endif
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(30000);
			} else {
				m_nVisionStage2Case = 10; m_tVisionStage2Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 13:
		if (n2FrontVisionCase > 22) {
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 14:
		if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) {
			m_tVisionStage2Loop.Takt_Save(15, 8); m_tVisionStage2Loop.Takt_Start(15, 9); 
			m_pDY07->oInspectStage2Deg0 = FALSE; m_pDY07->oInspectStage2Deg90 = TRUE;
			g_objAJinAXL.Write_Output(7);
//			g_objCommon.Move_Position(AX_TOP2_VISION_Z, 1);
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 2);
			//dVision2PosZ = m_pMoveData->dTOPVisionZ2[1] + gData.dFocusOffset[nS2No-1][4];
			dVision2PosZ = m_pMoveData->dTOPVisionZ2[1];
			g_objAJinAXL.Move_Absolute(AX_TOP2_VISION_Z, dVision2PosZ);
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 2)) {
//			if (g_objCommon.Check_Position(AX_TOP2_VISION_Z, 1)) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				if (m_pDX07->iInspectStage2Deg90) {
					g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, 2);	g_objCommon.Save_Motion(AX_TOP2_VISION_Z, 1);
					m_tVisionStage2Loop.Takt_Save(15, 9); m_tVisionStage2Loop.Takt_Start(15, 10); 
					gData.nVisionPos[1][1] = 0; gData.nVisionPos[1][2] = nS2No;
					gData.nTop2Cnt = gData.nScanRetry[2] = 0;
					n2Tno1 = gData.InfoVision[nS2No-1][9];
					n2Tno5 = gData.InfoVision[nS2No-1][9] + 4;
					m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(20000);
				}
			}
		}
		break;
	case 16:
		if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				m_tVisionStage2Loop.Takt_Save(15, 10); m_tVisionStage2Loop.Takt_Start(15, 11); 
				dStage2PosX = m_pMoveData->dVisionStageX2[2] + (m_pEquipData->dPitchTop * gData.nTop2Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X2, dStage2PosX);
//				g_objCommon.Move_Position(AX_TOP2_VISION_Z, 1);
				//dVision2PosZ = m_pMoveData->dTOPVisionZ2[1] + gData.dFocusOffset[nS2No-1][4+gData.nTop2Cnt];
				dVision2PosZ = m_pMoveData->dTOPVisionZ2[1];
				g_objAJinAXL.Move_Absolute(AX_TOP2_VISION_Z, dVision2PosZ);	nV2Retry = 0;
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X2, dStage2PosX)) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				if (!m_tVisionStage2Loop.Waiting_Time(m_pEquipData->nDelayTime[9])) break;
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, -1, dStage2PosX);
				m_tVisionStage2Loop.Takt_Save(15, 11); m_tVisionStage2Loop.Takt_Start(15, 12); 
				gData.bTop2ScanDone = FALSE;	gData.nVsNo[1] = nS2No; gData.nVsIx[1] = gData.nTop2Cnt+1;
				int nModule1 = n2Tno1; if (gData.InfoVision[nS2No-1][gData.nTop2Cnt] < 1)   nModule1 = -1;
				int nModule5 = n2Tno5; if (gData.InfoVision[nS2No-1][gData.nTop2Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC3, "T2", gData.sLotID_VisionStage[nS2No-1], gData.nPortNo_VisionStage[nS2No-1], gData.nTrayNo_VisionStage[nS2No-1], nModule1, gData.nTrayNo_VisionStage[nS2No-1], nModule5);
				gAlm.sAlmLID[3] = gData.sLotID_VisionStage[nS2No-1]; gAlm.nAlmTNo[3] = gData.nTrayNo_VisionStage[nS2No-1]; gAlm.nAlmPNo[3] = nModule1;
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 18:
		if (gData.bTop2ScanDone || !m_pEquipData->bUseTop2) {
			m_tVisionStage2Loop.Takt_Save(15, 12); m_tVisionStage2Loop.Takt_Start(15, 13); 
			gData.nTop2Cnt++; n2Tno1++; n2Tno5++;
			if (gData.nTop2Cnt >= 4) {
				dwV2RosTime[0] = GetTickCount();
				m_nVisionStage2Case = 20; m_tVisionStage2Loop.Set_LoopTime(5000);
			} else {
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 19:
		if (n2FrontVisionCase < 19 || (n2FrontVisionCase >= 23 && gData.nTop2Cnt <= 1) || n2FrontVisionCase >= 25) {
			m_nVisionStage2Case = 16; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 20:
		if (n2FrontVisionCase < 20 || n2FrontVisionCase >= 25) {
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 21:
		if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) {
			if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X2, dStage2PosX)) {
				m_tVisionStage2Loop.Takt_Save(15, 13); m_tVisionStage2Loop.Takt_Start(15, 14); 
				g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 4);
				m_pDY07->oInspectStage2Deg0 = TRUE; m_pDY07->oInspectStage2Deg90 = FALSE;
				g_objAJinAXL.Write_Output(7);
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 22:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 4)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, 4);
			m_tVisionStage2Loop.Takt_Save(15, 14); m_tVisionStage2Loop.Takt_Start(15, 15); 
			dwV2RosTime[1] = dwV2RosTime[0];
			gData.nVisionPos[1][2] = 0; gData.nVisionPos[1][4] = nS2No;
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 23:
		if (n2FrontVisionCase < 22 || n2FrontVisionCase > 34) {
			m_tVisionStage2Loop.Takt_Save(15, 15); m_tVisionStage2Loop.Takt_Start(15, 16); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 3);
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
		}
		return TRUE;
	case 24:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, 3);
			m_tVisionStage2Loop.Takt_Save(15, 16); m_tVisionStage2Loop.Takt_Start(15, 17); 
			dwV2RosTime[2] = dwV2RosTime[1];
			gData.nVisionPos[1][4] = 0; gData.nVisionPos[1][3] = nS2No;
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 25:
			m_nVisionStage2Case = 30; m_tVisionStage2Loop.Set_LoopTime(30000);
		break;
	case 26:	//RosTime 6초대기
		if (GetTickCount() - dwV2RosTime[2] >= 6000) {
			m_nVisionStage2Case = 30; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	//Unload Picker wait
		m_tVisionStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 31:
		if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) 
		{
			if (n2FrontVisionCase < 30 || n2FrontVisionCase > 52) 
			{
				/*double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage1Case);
				double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX1[INSPECT_STAGE1_X_Top2Pos];
				if (dTarget < dCurrent) return TRUE;*/

				m_pDY07->oInspectStage2Up = FALSE; m_pDY07->oInspectStage2Down = TRUE;
				g_objAJinAXL.Write_Output(7);
				m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
			}
		}
		return TRUE;		
	case 32:
		if (!m_pDX07->iInspectStage2Up && m_pDX07->iInspectStage2Down) 
		{
			m_tVisionStage2Loop.Takt_Save(15, 18); m_tVisionStage2Loop.Takt_Start(15, 19); 
			gData.nVisionPos[1][3] = 0; gData.nVisionPos[0][3] = nS2No;
//			if (nS2No == 1) {
//				m_pDY07->oInspectStage2Yin = FALSE; m_pDY07->oInspectStage2YOut = TRUE;
//				g_objAJinAXL.Write_Output(7);
//			}
//			if (nS2No == 4) {
//				m_pDY08->oInspectStage4Yin = FALSE; m_pDY08->oInspectStage4YOut = TRUE;
//				g_objAJinAXL.Write_Output(8);
//			}
			m_nVisionStage2Case = 34; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 34:
		if (
			(nS2No == 2) || (nS2No == 3) ||
			(nS2No == 4 && !m_pDX08->iInspectStage4Yin && m_pDX08->iInspectStage4YOut) ) {
			m_tVisionStage2Loop.Takt_Save(15, 19); m_tVisionStage2Loop.Takt_Start(15, 20); 
			m_nVisionStage2Case = 35; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 35:
		if (n2FrontVisionCase >= 0 && n2FrontVisionCase < 31) 
		{
			m_nVisionStage2Case = 61; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		else if (n2FrontVisionCase < 50 || n2FrontVisionCase >= 70) 
		{
			double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage1Case);
			double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX1[INSPECT_STAGE1_X_AlignPos];
			if(dTarget < dCurrent && !Check_ModuleEmpty() ) return TRUE;
			m_nVisionStage2Case = 51; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		else if (n2FrontVisionCase < 40 || n2FrontVisionCase >= 60)
		{
			double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage1Case);
			double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX1[INSPECT_STAGE1_X_Top1Pos];
			if(dTarget < dCurrent) return TRUE;
			m_nVisionStage2Case = 41; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 40:
		if (n2FrontVisionCase < 40 || n2FrontVisionCase >= 60)
		{
			

			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 41:
		if (!m_pDX07->iInspectStage2Up && m_pDX07->iInspectStage2Down) 
		{
			m_tVisionStage2Loop.Takt_Save(15, 20); m_tVisionStage2Loop.Takt_Start(15, 21); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 2);
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 2)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, 2);
			m_tVisionStage2Loop.Takt_Save(15, 21); m_tVisionStage2Loop.Takt_Start(15, 22); 
			gData.nVisionPos[0][3] = 0; gData.nVisionPos[0][2] = nS2No;
			m_nVisionStage2Case = 50; m_tVisionStage2Loop.Set_LoopTime(60000);
			m_nVisionStage2Case = 35; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		break;


	case 50:
		if (n2FrontVisionCase < 50 || n2FrontVisionCase >= 70) 
		{			
			

			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 51:
		if (!m_pDX07->iInspectStage2Up && m_pDX07->iInspectStage2Down) 
		{
			m_tVisionStage2Loop.Takt_Save(15, 22); m_tVisionStage2Loop.Takt_Start(15, 23); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, INSPECT_STAGE2_X_Top1Pos);
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 52:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, INSPECT_STAGE2_X_Top1Pos)) 
		{
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, INSPECT_STAGE2_X_Top1Pos);
			m_tVisionStage2Loop.Takt_Save(15, 23); m_tVisionStage2Loop.Takt_Start(15, 24); 
			gData.nVisionPos[0][2] = 0; gData.nVisionPos[0][1] = nS2No;
			m_nVisionStage2Case = 60; m_tVisionStage2Loop.Set_LoopTime(60000);
		}
		break;
	case 60:
		if (n2FrontVisionCase >= 0 && n2FrontVisionCase < 50)
		{
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 61:
		if (!m_pDX07->iInspectStage2Up && m_pDX07->iInspectStage2Down) 
		{
			m_tVisionStage2Loop.Takt_Save(15, 24); m_tVisionStage2Loop.Takt_Start(15, 25); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 0);
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 62:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X2, 0);
			m_tVisionStage2Loop.Takt_Save(15, 25); m_tVisionStage2Loop.Takt_Start(15, 26); 
			gData.nVisionPos[0][1] = 0; gData.nVisionPos[0][0] = nS2No;
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(10000);
		}
		break;
	case 63:
		if (!m_pDX07->iInspectStage2Up && m_pDX07->iInspectStage2Down) {
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 64:
//		if (
//			(nS2No == 2) || (nS2No == 3) ||
//			(nS2No == 4 && m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) ) {
			m_nVisionStage2Case = 70; m_tVisionStage2Loop.Set_LoopTime(5000);
//		}
		break;

	case 70:
		if (n2FrontVisionCase > 4 && n2FrontVisionCase < 60) {
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 71:
		if (!m_pDX07->iInspectStage2Up && m_pDX07->iInspectStage2Down) {
			m_tVisionStage2Loop.Takt_Save(15, 26); m_tVisionStage2Loop.Takt_Start(15, 27); 
			m_pDY07->oInspectStage2Up = TRUE; m_pDY07->oInspectStage2Down = FALSE;
			g_objAJinAXL.Write_Output(7);
			m_nVisionStage2Case++; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 72:
		if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) {
			m_tVisionStage2Loop.Takt_Save(15, 27, TRUE);
			gData.nVisionPos[0][0] = 0; gData.nVisionPos[1][0] = nS2No;
			m_nVisionStage2Case = 0; m_tVisionStage2Loop.Set_LoopTime(5000);
		}
		break;

	}

	// 15. (Error : 6200)
	if (m_tVisionStage2Loop.Over_LoopTime()) {
//		if (m_nVisionStage2Case == 8 || m_nVisionStage2Case == 12 || m_nVisionStage2Case == 18) {
//			nV2Retry++;
//			if (nV2Retry == 1) { m_nVisionStage2Case--; return TRUE; }
//		}
//		if (m_nVisionStage2Case == 7 || m_nVisionStage2Case == 11 || m_nVisionStage2Case == 17) m_nVisionStage2Case++;
		if (m_nVisionStage2Case == 26) { m_nVisionStage2Case = 30; return TRUE; }
		g_objCommon.Show_Error(6200 + m_nVisionStage2Case);
		return FALSE;
	}
	return TRUE;
}

// 16. (Error : 6400)
BOOL CSequenceMain::Run_VisionStage3()
{
	static int nS3No = 3;		//1,2,3,4(고정)
	static int n3Tno1, n3Tno5, n3FrontVisionCase, nV3Retry;
	static double dStage3PosX = 0, dVision3PosZ = 0;
	static DWORD dwV3RosTime[3];	//Top2,Buffer,Unload

	n3FrontVisionCase = m_nVisionStage4Case;
	switch (m_nVisionStage3Case) {
	case 0:	// Wait
		m_tVisionStage3Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (( m_pEquipData->bUseTopAng && n3FrontVisionCase > 14) ||
			(!m_pEquipData->bUseTopAng && n3FrontVisionCase > 4)) {
			m_sLog.Format("[Inspection Stage3: Start] Inspection Stage4 Case(%d)", n3FrontVisionCase);
			g_objLogFile.Save_HandlerLog(m_sLog);

			m_tVisionStage3Loop.Takt_Start(16, 1, TRUE); 
			m_pDY08->oInspectStage3Deg0 = TRUE; m_pDY08->oInspectStage3Deg90 = FALSE;
			g_objAJinAXL.Write_Output(8);

			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 2:
		if (!m_pDX03->iAlignSlave1In && m_pDX03->iAlignSlave1Out && !m_pDX03->iAlignSlave2In && m_pDX03->iAlignSlave2Out && !m_pDX03->iAlignMasterIn && m_pDX03->iAlignMasterOut) {
			if (m_pDX08->iInspectStage3Up && !m_pDX08->iInspectStage3Down) {
				if (n3FrontVisionCase > 14) {
					g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 1);
				} else {
					dStage3PosX = m_pMoveData->dVisionStageX3[0] + ALIGN_TOP1_POS;
					g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X3, dStage3PosX);
				}
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 3:
		if (n3FrontVisionCase > 14) {
#ifdef NEW_FINAL
				if (m_pEquipData->bUseTopAng) {
					//dVision3PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS3No-1][0];
					dVision3PosZ = m_pMoveData->dTOPVisionZ1[1];
					g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision3PosZ);
					m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
				} else {
					if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X3)) {
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 1);	//Top1
						//dVision3PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS3No-1][0];
						dVision3PosZ = m_pMoveData->dTOPVisionZ1[1];
						g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision3PosZ);
						m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
					}
				}
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 1)) {
				if (m_pEquipData->bUseTopAng) {
					g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
					//dVision3PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS3No-1][0];
					dVision3PosZ = m_pMoveData->dTOPVisionZ1[1];
					g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision3PosZ);
					m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
				} else {
					if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X3)) {
						g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 1);	//Top1
						//dVision3PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS3No-1][0];
						dVision3PosZ = m_pMoveData->dTOPVisionZ1[1];
						g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision3PosZ);
						m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
					}
				}
			}
#endif
		} else {
			if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X3)) {
				if (n3FrontVisionCase > 6 && gData.nTop1Cnt > 0) {
					if (gData.nTop1Cnt > 3) gData.nTop1Cnt = 3;
					dStage3PosX = m_pMoveData->dVisionStageX3[0] + ALIGN_TOP1_POS + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
					double dStagePos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X3);
					if (dStagePos != dStage3PosX) g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X3, dStage3PosX);
				}
			}
			m_tVisionStage3Loop.Set_LoopTime(10000);
		}
		return TRUE;

	case 4:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 1)) {
			if (m_pDX08->iInspectStage3Deg0) {
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, 1);
				m_tVisionStage3Loop.Takt_Save(16, 1); m_tVisionStage3Loop.Takt_Start(16, 2); 
				gData.nVisionPos[1][0] = 0; gData.nVisionPos[1][1] = nS3No;
				gData.nTop1Cnt = gData.nScanRetry[1] = 0;
				n3Tno1 = gData.InfoVision[nS3No-1][9];
				n3Tno5 = gData.InfoVision[nS3No-1][9] + 4;
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 5:
		if (n3FrontVisionCase >= 22 || (n3FrontVisionCase >= 17 && gData.nTop1Cnt <= 1) || (n3FrontVisionCase >= 17 && gData.nTop2Cnt >= gData.nTop1Cnt)) {
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(20000);
		}
		return TRUE;
	case 6:
		if (m_pDX08->iInspectStage3Up && !m_pDX08->iInspectStage3Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
				m_tVisionStage3Loop.Takt_Save(16, 2); m_tVisionStage3Loop.Takt_Start(16, 3); 
				dStage3PosX = m_pMoveData->dVisionStageX3[1] + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X3, dStage3PosX);
//				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
				//dVision3PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS3No-1][gData.nTop1Cnt];
				dVision3PosZ = m_pMoveData->dTOPVisionZ1[1];
				g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision3PosZ);	nV3Retry = 0;
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 7:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X3, dStage3PosX)) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#else
			if (g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 1) && g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#endif
				if (!m_tVisionStage3Loop.Waiting_Time(m_pEquipData->nDelayTime[3])) break;
#ifdef NEW_FINAL
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, -1, dStage3PosX);
#else
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, -1, dStage3PosX);	g_objCommon.Save_Motion(AX_TOP1_LIGHT_Z, 1);
#endif
				m_tVisionStage3Loop.Takt_Save(16, 3); m_tVisionStage3Loop.Takt_Start(16, 4); 
				gData.bTop1ScanDone = FALSE;	gData.nVsNo[0] = nS3No; gData.nVsIx[0] = gData.nTop1Cnt+1;
				int nModule1 = n3Tno1; if (gData.InfoVision[nS3No-1][gData.nTop1Cnt] < 1)   nModule1 = -1;
				int nModule5 = n3Tno5; if (gData.InfoVision[nS3No-1][gData.nTop1Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC2, "T1", gData.sLotID_VisionStage[nS3No-1], gData.nPortNo_VisionStage[nS3No-1], gData.nTrayNo_VisionStage[nS3No-1], nModule1, gData.nTrayNo_VisionStage[nS3No-1], nModule5);
				gAlm.sAlmLID[2] = gData.sLotID_VisionStage[nS3No-1]; gAlm.nAlmTNo[2] = gData.nTrayNo_VisionStage[nS3No-1]; gAlm.nAlmPNo[2] = nModule1;
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 8:
		if (gData.bTop1ScanDone || !m_pEquipData->bUseTop1) {
			m_tVisionStage3Loop.Takt_Save(16, 4); m_tVisionStage3Loop.Takt_Start(16, 5); 
			gData.nTop1Cnt++; n3Tno1++; n3Tno5++;
			if (gData.nTop1Cnt >= 4) {
				if (m_pEquipData->bUseTopAng) {
					gData.nTop1Cnt = 0;
					n3Tno1 = gData.InfoVision[nS3No-1][9];
					n3Tno5 = gData.InfoVision[nS3No-1][9] + 4;

					g_objCommon.Move_Position(AX_TOP1_VISION_Z, 2);
					g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 1);
#ifdef NEW_FINAL
#else
					g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 2);
#endif
					m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(30000);
				} else {
					m_nVisionStage3Case = 12; m_tVisionStage3Loop.Set_LoopTime(5000);
				}
			} else {
				m_nVisionStage3Case = 5; m_tVisionStage3Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 9:	//Top1-Angle
#ifdef NEW_FINAL
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2)) {
			g_objCommon.Save_Motion(AX_TOP1_VISION_Z, 2); gData.nScanRetry[1] = 0;
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(30000);
		}
#else
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2) && g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 2) ) {
			g_objCommon.Save_Motion(AX_TOP1_VISION_Z, 2);	g_objCommon.Save_Motion(AX_TOP1_LIGHT_Z, 2);
			g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 2); gData.nScanRetry[1] = 0;
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(30000);
		}
#endif
		break;
	case 10:
		if (m_pDX08->iInspectStage3Up && !m_pDX08->iInspectStage3Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
				m_tVisionStage3Loop.Takt_Save(16, 5); m_tVisionStage3Loop.Takt_Start(16, 6); 
				dStage3PosX = m_pMoveData->dVisionStageX3[1] + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X3, dStage3PosX);
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 2);	nV3Retry = 0;
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X3, dStage3PosX)) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 2) && g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#endif
				if (!m_tVisionStage3Loop.Waiting_Time(m_pEquipData->nDelayTime[9])) break;
#ifdef NEW_FINAL
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, -1, dStage3PosX);
#else
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, -1, dStage3PosX);	g_objCommon.Save_Motion(AX_TOP1_ANGLE_Y, 2);
#endif
				m_tVisionStage3Loop.Takt_Save(16, 6); m_tVisionStage3Loop.Takt_Start(16, 7); 
				gData.bTop1ScanDone = FALSE;	gData.nVsNo[0] = nS3No; gData.nVsIx[0] = gData.nTop1Cnt+1;
				int nModule1 = n3Tno1; if (gData.InfoVision[nS3No-1][gData.nTop1Cnt] < 1)   nModule1 = -1;
				int nModule5 = n3Tno5; if (gData.InfoVision[nS3No-1][gData.nTop1Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC2, "TG", gData.sLotID_VisionStage[nS3No-1], gData.nPortNo_VisionStage[nS3No-1], gData.nTrayNo_VisionStage[nS3No-1], nModule1, gData.nTrayNo_VisionStage[nS3No-1], nModule5);
				gAlm.sAlmLID[2] = gData.sLotID_VisionStage[nS3No-1]; gAlm.nAlmTNo[2] = gData.nTrayNo_VisionStage[nS3No-1]; gAlm.nAlmPNo[2] = nModule1;
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 12:
		if (gData.bTop1ScanDone || !m_pEquipData->bUseTopAng) {
			m_tVisionStage3Loop.Takt_Save(16, 7); m_tVisionStage3Loop.Takt_Start(16, 8); 
			gData.nTop1Cnt++; n3Tno1++; n3Tno5++;
			if (gData.nTop1Cnt >= 4) {
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
#ifdef NEW_FINAL
#else
				g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 1);
#endif
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(30000);
			} else {
				m_nVisionStage3Case = 10; m_tVisionStage3Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 13:
		if (n3FrontVisionCase > 22) {
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 14:
		if (m_pDX08->iInspectStage3Up && !m_pDX08->iInspectStage3Down) {
			m_tVisionStage3Loop.Takt_Save(16, 8); m_tVisionStage3Loop.Takt_Start(16, 9); 
			m_pDY08->oInspectStage3Deg0 = FALSE; m_pDY08->oInspectStage3Deg90 = TRUE;
			g_objAJinAXL.Write_Output(8);
//			g_objCommon.Move_Position(AX_TOP2_VISION_Z, 1);
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 2);
			//dVision3PosZ = m_pMoveData->dTOPVisionZ2[1] + gData.dFocusOffset[nS3No-1][4];
			dVision3PosZ = m_pMoveData->dTOPVisionZ2[1];
			g_objAJinAXL.Move_Absolute(AX_TOP2_VISION_Z, dVision3PosZ);
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 2)) {
//			if (g_objCommon.Check_Position(AX_TOP2_VISION_Z, 1)) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				if (m_pDX08->iInspectStage3Deg90) {
					g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, 2);	g_objCommon.Save_Motion(AX_TOP2_VISION_Z, 1);
					m_tVisionStage3Loop.Takt_Save(16, 9); m_tVisionStage3Loop.Takt_Start(16, 10); 
					gData.nVisionPos[1][1] = 0; gData.nVisionPos[1][2] = nS3No;
					gData.nTop2Cnt = gData.nScanRetry[2] = 0;
					n3Tno1 = gData.InfoVision[nS3No-1][9];
					n3Tno5 = gData.InfoVision[nS3No-1][9] + 4;
					m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(20000);
				}
			}
		}
		break;
	case 16:
		if (m_pDX08->iInspectStage3Up && !m_pDX08->iInspectStage3Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				m_tVisionStage3Loop.Takt_Save(16, 10); m_tVisionStage3Loop.Takt_Start(16, 11); 
				dStage3PosX = m_pMoveData->dVisionStageX3[2] + (m_pEquipData->dPitchTop * gData.nTop2Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X3, dStage3PosX);
//				g_objCommon.Move_Position(AX_TOP2_VISION_Z, 1);
				//dVision3PosZ = m_pMoveData->dTOPVisionZ2[1] + gData.dFocusOffset[nS3No-1][4+gData.nTop2Cnt];
				dVision3PosZ = m_pMoveData->dTOPVisionZ2[1];
				g_objAJinAXL.Move_Absolute(AX_TOP2_VISION_Z, dVision3PosZ);	nV3Retry = 0;
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X3, dStage3PosX)) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				if (!m_tVisionStage3Loop.Waiting_Time(m_pEquipData->nDelayTime[9])) break;
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, -1, dStage3PosX);
				m_tVisionStage3Loop.Takt_Save(16, 11); m_tVisionStage3Loop.Takt_Start(16, 12); 
				gData.bTop2ScanDone = FALSE;	gData.nVsNo[1] = nS3No; gData.nVsIx[1] = gData.nTop2Cnt+1;
				int nModule1 = n3Tno1; if (gData.InfoVision[nS3No-1][gData.nTop2Cnt] < 1)   nModule1 = -1;
				int nModule5 = n3Tno5; if (gData.InfoVision[nS3No-1][gData.nTop2Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC3, "T2", gData.sLotID_VisionStage[nS3No-1], gData.nPortNo_VisionStage[nS3No-1], gData.nTrayNo_VisionStage[nS3No-1], nModule1, gData.nTrayNo_VisionStage[nS3No-1], nModule5);
				gAlm.sAlmLID[3] = gData.sLotID_VisionStage[nS3No-1]; gAlm.nAlmTNo[3] = gData.nTrayNo_VisionStage[nS3No-1]; gAlm.nAlmPNo[3] = nModule1;
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 18:
		if (gData.bTop2ScanDone || !m_pEquipData->bUseTop2) {
			m_tVisionStage3Loop.Takt_Save(16, 12); m_tVisionStage3Loop.Takt_Start(16, 13); 
			gData.nTop2Cnt++; n3Tno1++; n3Tno5++;
			if (gData.nTop2Cnt >= 4) {
				dwV3RosTime[0] = GetTickCount();
				m_nVisionStage3Case = 20; m_tVisionStage3Loop.Set_LoopTime(5000);
			} else {
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 19:
		if (n3FrontVisionCase < 19 || (n3FrontVisionCase >= 23 && gData.nTop2Cnt <= 1) || n3FrontVisionCase >= 25) {
			m_nVisionStage3Case = 16; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 20:
		if (n3FrontVisionCase < 20 || n3FrontVisionCase >= 25) {
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 21:
		if (m_pDX08->iInspectStage3Up && !m_pDX08->iInspectStage3Down) {
			if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X3, dStage3PosX)) {
				m_tVisionStage3Loop.Takt_Save(16, 13); m_tVisionStage3Loop.Takt_Start(16, 14); 
				g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 4);
				m_pDY08->oInspectStage3Deg0 = TRUE; m_pDY08->oInspectStage3Deg90 = FALSE;
				g_objAJinAXL.Write_Output(8);
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 22:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 4)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, 4);
			m_tVisionStage3Loop.Takt_Save(16, 14); m_tVisionStage3Loop.Takt_Start(16, 15); 
			dwV3RosTime[1] = dwV3RosTime[0];
			gData.nVisionPos[1][2] = 0; gData.nVisionPos[1][4] = nS3No;
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
		}
		break;
	case 23:
		if (n3FrontVisionCase < 22 || n3FrontVisionCase > 34) {
			m_tVisionStage3Loop.Takt_Save(16, 15); m_tVisionStage3Loop.Takt_Start(16, 16); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 3);
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
		}
		return TRUE;
	case 24:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, 3);
			m_tVisionStage3Loop.Takt_Save(16, 16); m_tVisionStage3Loop.Takt_Start(16, 17); 
			dwV3RosTime[2] = dwV3RosTime[1];
			gData.nVisionPos[1][4] = 0; gData.nVisionPos[1][3] = nS3No;
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(30000);
		}
		break;
	case 25:
			m_nVisionStage3Case = 30; m_tVisionStage3Loop.Set_LoopTime(30000);
		break;
	case 26:	//RosTime 6초대기
		if (GetTickCount() - dwV3RosTime[2] >= 6000) {
			m_nVisionStage3Case = 30; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	//Unload Picker wait
		m_tVisionStage3Loop.Set_LoopTime(5000);
		return TRUE;

	case 31:
		if (m_pDX08->iInspectStage3Up && !m_pDX08->iInspectStage3Down) 
		{
			if (n3FrontVisionCase < 30 || n3FrontVisionCase > 52)
			{				
				/*double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage4Case);
				double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX4[INSPECT_STAGE4_X_Top2Pos];
				if(dTarget < dCurrent) return TRUE;*/

				m_pDY08->oInspectStage3Up = FALSE; m_pDY08->oInspectStage3Down = TRUE;
				g_objAJinAXL.Write_Output(8);
				m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
			}
		}
		return TRUE;
	
	case 32:
		if (!m_pDX08->iInspectStage3Up && m_pDX08->iInspectStage3Down) 
		{
			m_tVisionStage3Loop.Takt_Save(16, 18); m_tVisionStage3Loop.Takt_Start(16, 19); 
			gData.nVisionPos[1][3] = 0; gData.nVisionPos[0][3] = nS3No;
			m_nVisionStage3Case = 34; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		break;
	case 34:
		if ((nS3No == 2) || (nS3No == 3) ||
			(nS3No == 4 && !m_pDX08->iInspectStage4Yin && m_pDX08->iInspectStage4YOut) ) 
		{
			m_tVisionStage3Loop.Takt_Save(16, 19); m_tVisionStage3Loop.Takt_Start(16, 20); 
			m_nVisionStage3Case = 35; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		break;

	case 35:
		if (n3FrontVisionCase >= 0 && n3FrontVisionCase < 31) 
		{
			m_nVisionStage3Case = 61; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		else if ( n3FrontVisionCase < 50 || n3FrontVisionCase >= 70) 
		{
			double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage4Case);
			double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX4[INSPECT_STAGE4_X_AlignPos];
			if(dTarget < dCurrent && !Check_ModuleEmpty()) return TRUE;
			m_nVisionStage3Case = 51; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		else if (n3FrontVisionCase < 40 || n3FrontVisionCase >= 60) 
		{
			double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage4Case);
			double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX4[INSPECT_STAGE4_X_Top1Pos];
			if(dTarget < dCurrent || !Check_ModuleEmpty() ) return TRUE;
			m_nVisionStage3Case = 41; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 40:
		if (n3FrontVisionCase < 40 || n3FrontVisionCase >= 60) 
		{
			
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 41:
		if (!m_pDX08->iInspectStage3Up && m_pDX08->iInspectStage3Down) 
		{
			m_tVisionStage3Loop.Takt_Save(16, 20); m_tVisionStage3Loop.Takt_Start(16, 21); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 2);
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 2)) 
		{
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, 2);
			m_tVisionStage3Loop.Takt_Save(16, 21); m_tVisionStage3Loop.Takt_Start(16, 22); 
			gData.nVisionPos[0][3] = 0; gData.nVisionPos[0][2] = nS3No;
			m_nVisionStage3Case = 50; m_tVisionStage3Loop.Set_LoopTime(60000);
		}
		break;
	case 50:
		if (n3FrontVisionCase < 50 || n3FrontVisionCase >= 70) 
		{
			
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 51:
		if (!m_pDX08->iInspectStage3Up && m_pDX08->iInspectStage3Down) {
			m_tVisionStage3Loop.Takt_Save(16, 22); m_tVisionStage3Loop.Takt_Start(16, 23); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 1);
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
		}
		break;
	case 52:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 1)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, 1);
			m_tVisionStage3Loop.Takt_Save(16, 23); m_tVisionStage3Loop.Takt_Start(16, 24); 
			gData.nVisionPos[0][2] = 0; gData.nVisionPos[0][1] = nS3No;
			m_nVisionStage3Case = 60; m_tVisionStage3Loop.Set_LoopTime(60000);
		}
		break;
	case 60:
		if (n3FrontVisionCase >= 0 && n3FrontVisionCase < 50) 
		{
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 61:
		if (!m_pDX08->iInspectStage3Up && m_pDX08->iInspectStage3Down) {
			m_tVisionStage3Loop.Takt_Save(16, 24); m_tVisionStage3Loop.Takt_Start(16, 25); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 0);
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
		}
		break;
	case 62:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X3, 0);
			m_tVisionStage3Loop.Takt_Save(16, 25); m_tVisionStage3Loop.Takt_Start(16, 26); 
			gData.nVisionPos[0][1] = 0; gData.nVisionPos[0][0] = nS3No;
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(10000);
		}
		break;
	case 63:
		if (!m_pDX08->iInspectStage3Up && m_pDX08->iInspectStage3Down) {
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		break;
	case 64:
///		if (
//			(nS3No == 2) || (nS3No == 3) ||
//			(nS3No == 4 && m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) ) {
			m_nVisionStage3Case = 70; m_tVisionStage3Loop.Set_LoopTime(5000);
//		}
		break;

	case 70:
		if (n3FrontVisionCase > 4 && n3FrontVisionCase < 60) {
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 71:
		if (!m_pDX08->iInspectStage3Up && m_pDX08->iInspectStage3Down) {
			m_tVisionStage3Loop.Takt_Save(16, 26); m_tVisionStage3Loop.Takt_Start(16, 27); 
			m_pDY08->oInspectStage3Up = TRUE; m_pDY08->oInspectStage3Down = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_nVisionStage3Case++; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		break;
	case 72:
		if (m_pDX08->iInspectStage3Up && !m_pDX08->iInspectStage3Down) {
			m_tVisionStage3Loop.Takt_Save(16, 27, TRUE);
			gData.nVisionPos[0][0] = 0; gData.nVisionPos[1][0] = nS3No;
			m_nVisionStage3Case = 0; m_tVisionStage3Loop.Set_LoopTime(5000);
		}
		break;

	}

	// 16. (Error : 6400)
	if (m_tVisionStage3Loop.Over_LoopTime()) {
//		if (m_nVisionStage3Case == 8 || m_nVisionStage3Case == 12 || m_nVisionStage3Case == 18) {
//			nV3Retry++;
//			if (nV3Retry == 1) { m_nVisionStage3Case--; return TRUE; }
//		}
//		if (m_nVisionStage3Case == 7 || m_nVisionStage3Case == 11 || m_nVisionStage3Case == 17) m_nVisionStage3Case++;
		if (m_nVisionStage3Case == 26) { m_nVisionStage3Case = 30; return TRUE; }
		g_objCommon.Show_Error(6400 + m_nVisionStage3Case);
		return FALSE;
	}
	return TRUE;
}

// 17. (Error : 6600)
BOOL CSequenceMain::Run_VisionStage4()
{
	static int nS4No = 4;		//1,2,3,4(고정)
	static int n4Tno1, n4Tno5, n4FrontVisionCase, nV4Retry;
	static double dStage4PosX = 0, dVision4PosZ = 0;
	static DWORD dwV4RosTime[3];	//Top2,Buffer,Unload

	n4FrontVisionCase = m_nVisionStage2Case;
	switch (m_nVisionStage4Case) {
	case 0:	// Wait
		m_tVisionStage4Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (( m_pEquipData->bUseTopAng && n4FrontVisionCase > 14) ||
			(!m_pEquipData->bUseTopAng && n4FrontVisionCase > 4)) {
			m_sLog.Format("[Inspection Stage4: Start] Inspection Stage2 Case(%d)", n4FrontVisionCase);
			g_objLogFile.Save_HandlerLog(m_sLog);

			m_tVisionStage4Loop.Takt_Start(17, 1, TRUE); 
			m_pDY08->oInspectStage4Deg0 = TRUE; m_pDY08->oInspectStage4Deg90 = FALSE;
			g_objAJinAXL.Write_Output(8);

			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 2:
		if (!m_pDX03->iAlignSlave1In && m_pDX03->iAlignSlave1Out && !m_pDX03->iAlignSlave2In && m_pDX03->iAlignSlave2Out && !m_pDX03->iAlignMasterIn && m_pDX03->iAlignMasterOut) {
			if (m_pDX08->iInspectStage4Up && !m_pDX08->iInspectStage4Down) {
				if (m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) {
					if (n4FrontVisionCase > 14) {
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 1);
					} else {
						dStage4PosX = m_pMoveData->dVisionStageX4[0] + ALIGN_TOP1_POS;
						g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X4, dStage4PosX);
					}
					m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
				}
			}
		}
		break;
	case 3:
		if (n4FrontVisionCase > 14) {
#ifdef NEW_FINAL
				if (m_pEquipData->bUseTopAng) {
					//dVision4PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS4No-1][0];
					dVision4PosZ = m_pMoveData->dTOPVisionZ1[1];
					g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision4PosZ);
					m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
				} else {
					if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X4)) {
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 1);	//Top1
						//dVision4PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS4No-1][0];
						dVision4PosZ = m_pMoveData->dTOPVisionZ1[1];
						g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision4PosZ);
						m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
					}
				}
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 1)) 
			{
				if (m_pEquipData->bUseTopAng) 
				{
					g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
					//dVision4PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS4No-1][0];
					dVision4PosZ = m_pMoveData->dTOPVisionZ1[1];
					g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision4PosZ);
					m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
				} else {
					if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X4)) {
						g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
						g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 1);	//Top1
						//dVision4PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS4No-1][0];
						dVision4PosZ = m_pMoveData->dTOPVisionZ1[1];
						g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision4PosZ);
						m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
					}
				}
			}
#endif
		} 
		else
		{
			if (g_objAJinAXL.Is_Done(AX_INSPECT_STAGE_X4))
			{
				if (n4FrontVisionCase > 6 && gData.nTop1Cnt > 0)
				{
					if (gData.nTop1Cnt > 3) gData.nTop1Cnt = 3;
					dStage4PosX = m_pMoveData->dVisionStageX4[0] + ALIGN_TOP1_POS + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
					double dStagePos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X4);
					if (dStagePos != dStage4PosX) g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X4, dStage4PosX);
				}
			}
			m_tVisionStage4Loop.Set_LoopTime(10000);
		}
		return TRUE;

	case 4:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 1)) {
			if (m_pDX08->iInspectStage4Deg0) {
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, 1);
				m_tVisionStage4Loop.Takt_Save(17, 1); m_tVisionStage4Loop.Takt_Start(17, 2); 
				gData.nVisionPos[1][0] = 0; gData.nVisionPos[1][1] = nS4No;
				gData.nTop1Cnt = gData.nScanRetry[1] = 0;
				n4Tno1 = gData.InfoVision[nS4No-1][9];
				n4Tno5 = gData.InfoVision[nS4No-1][9] + 4;
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 5:
		if (n4FrontVisionCase >= 22 || (n4FrontVisionCase >= 17 && gData.nTop1Cnt <= 1) || (n4FrontVisionCase >= 17 && gData.nTop2Cnt >= gData.nTop1Cnt)) {
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(20000);
		}
		return TRUE;
	case 6:
		if (m_pDX08->iInspectStage4Up && !m_pDX08->iInspectStage4Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
				m_tVisionStage4Loop.Takt_Save(17, 2); m_tVisionStage4Loop.Takt_Start(17, 3); 
				dStage4PosX = m_pMoveData->dVisionStageX4[1] + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X4, dStage4PosX);
//				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
				//dVision4PosZ = m_pMoveData->dTOPVisionZ1[1] + gData.dFocusOffset[nS4No-1][gData.nTop1Cnt];
				dVision4PosZ = m_pMoveData->dTOPVisionZ1[1];
				g_objAJinAXL.Move_Absolute(AX_TOP1_VISION_Z, dVision4PosZ);	nV4Retry = 0;
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 7:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X4, dStage4PosX)) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#else
			if (g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 1) && g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#endif
				if (!m_tVisionStage4Loop.Waiting_Time(m_pEquipData->nDelayTime[3])) break;
#ifdef NEW_FINAL
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, -1, dStage4PosX);
#else
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, -1, dStage4PosX);	g_objCommon.Save_Motion(AX_TOP1_LIGHT_Z, 1);
#endif
				m_tVisionStage4Loop.Takt_Save(17, 3); m_tVisionStage4Loop.Takt_Start(17, 4); 
				gData.bTop1ScanDone = FALSE;	gData.nVsNo[0] = nS4No; gData.nVsIx[0] = gData.nTop1Cnt+1;
				int nModule1 = n4Tno1; if (gData.InfoVision[nS4No-1][gData.nTop1Cnt] < 1)   nModule1 = -1;
				int nModule5 = n4Tno5; if (gData.InfoVision[nS4No-1][gData.nTop1Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC2, "T1", gData.sLotID_VisionStage[nS4No-1], gData.nPortNo_VisionStage[nS4No-1], gData.nTrayNo_VisionStage[nS4No-1], nModule1, gData.nTrayNo_VisionStage[nS4No-1], nModule5);
				gAlm.sAlmLID[2] = gData.sLotID_VisionStage[nS4No-1]; gAlm.nAlmTNo[2] = gData.nTrayNo_VisionStage[nS4No-1]; gAlm.nAlmPNo[2] = nModule1;
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 8:
		if (gData.bTop1ScanDone || !m_pEquipData->bUseTop1) {
			m_tVisionStage4Loop.Takt_Save(17, 4); m_tVisionStage4Loop.Takt_Start(17, 5); 
			gData.nTop1Cnt++; n4Tno1++; n4Tno5++;
			if (gData.nTop1Cnt >= 4) {
				if (m_pEquipData->bUseTopAng) {
					gData.nTop1Cnt = 0;
					n4Tno1 = gData.InfoVision[nS4No-1][9];
					n4Tno5 = gData.InfoVision[nS4No-1][9] + 4;

					g_objCommon.Move_Position(AX_TOP1_VISION_Z, 2);
					g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 1);
#ifdef NEW_FINAL
#else
					g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 2);
#endif
					m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(30000);
				} else {
					m_nVisionStage4Case = 12; m_tVisionStage4Loop.Set_LoopTime(5000);
				}
			} else {
				m_nVisionStage4Case = 5; m_tVisionStage4Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 9:	//Top1-Angle
#ifdef NEW_FINAL
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2)) {
			g_objCommon.Save_Motion(AX_TOP1_VISION_Z, 2); gData.nScanRetry[1] = 0;
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(30000);
		}
#else
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2) && g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 2) ) {
			g_objCommon.Save_Motion(AX_TOP1_VISION_Z, 2);	g_objCommon.Save_Motion(AX_TOP1_LIGHT_Z, 2);
			g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 2); gData.nScanRetry[1] = 0;
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(30000);
		}
#endif
		break;
	case 10:
		if (m_pDX08->iInspectStage4Up && !m_pDX08->iInspectStage4Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
				m_tVisionStage4Loop.Takt_Save(17, 5); m_tVisionStage4Loop.Takt_Start(17, 6); 
				dStage4PosX = m_pMoveData->dVisionStageX4[1] + (m_pEquipData->dPitchTop * gData.nTop1Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X4, dStage4PosX);
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 2);	nV4Retry = 0;
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X4, dStage4PosX)) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 2) && g_objAJinAXL.Is_Done(AX_TOP1_VISION_Z)) {
#endif
				if (!m_tVisionStage4Loop.Waiting_Time(m_pEquipData->nDelayTime[9])) break;
#ifdef NEW_FINAL
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, -1, dStage4PosX);
#else
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, -1, dStage4PosX);	g_objCommon.Save_Motion(AX_TOP1_ANGLE_Y, 2);
#endif
				m_tVisionStage4Loop.Takt_Save(17, 6); m_tVisionStage4Loop.Takt_Start(17, 7); 
				gData.bTop1ScanDone = FALSE;	gData.nVsNo[0] = nS4No; gData.nVsIx[0] = gData.nTop1Cnt+1;
				int nModule1 = n4Tno1; if (gData.InfoVision[nS4No-1][gData.nTop1Cnt] < 1)   nModule1 = -1;
				int nModule5 = n4Tno5; if (gData.InfoVision[nS4No-1][gData.nTop1Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC2, "TG", gData.sLotID_VisionStage[nS4No-1], gData.nPortNo_VisionStage[nS4No-1], gData.nTrayNo_VisionStage[nS4No-1], nModule1, gData.nTrayNo_VisionStage[nS4No-1], nModule5);
				gAlm.sAlmLID[2] = gData.sLotID_VisionStage[nS4No-1]; gAlm.nAlmTNo[2] = gData.nTrayNo_VisionStage[nS4No-1]; gAlm.nAlmPNo[2] = nModule1;
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 12:
		if (gData.bTop1ScanDone || !m_pEquipData->bUseTopAng) {
			m_tVisionStage4Loop.Takt_Save(17, 7); m_tVisionStage4Loop.Takt_Start(17, 8); 
			gData.nTop1Cnt++; n4Tno1++; n4Tno5++;
			if (gData.nTop1Cnt >= 4) {
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
#ifdef NEW_FINAL
#else
				g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 1);
#endif
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(30000);
			} else {
				m_nVisionStage4Case = 10; m_tVisionStage4Loop.Set_LoopTime(5000);
			}
		}
		break;

	case 13:
		if (n4FrontVisionCase > 22) {
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 14:
		if (m_pDX08->iInspectStage4Up && !m_pDX08->iInspectStage4Down) {
			if (m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) {
				m_tVisionStage4Loop.Takt_Save(17, 8); m_tVisionStage4Loop.Takt_Start(17, 9); 
				m_pDY08->oInspectStage4Deg0 = FALSE; m_pDY08->oInspectStage4Deg90 = TRUE;
				g_objAJinAXL.Write_Output(8);
//				g_objCommon.Move_Position(AX_TOP2_VISION_Z, 1);
				g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 2);
				//dVision4PosZ = m_pMoveData->dTOPVisionZ2[1] + gData.dFocusOffset[nS4No-1][4];
				dVision4PosZ = m_pMoveData->dTOPVisionZ2[1];
				g_objAJinAXL.Move_Absolute(AX_TOP2_VISION_Z, dVision4PosZ);
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 2)) {
//			if (g_objCommon.Check_Position(AX_TOP2_VISION_Z, 1)) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				if (m_pDX08->iInspectStage4Deg90) {
					g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, 2);	g_objCommon.Save_Motion(AX_TOP2_VISION_Z, 1);
					m_tVisionStage4Loop.Takt_Save(17, 9); m_tVisionStage4Loop.Takt_Start(17, 10); 
					gData.nVisionPos[1][1] = 0; gData.nVisionPos[1][2] = nS4No;
					gData.nTop2Cnt = gData.nScanRetry[2] = 0;
					n4Tno1 = gData.InfoVision[nS4No-1][9];
					n4Tno5 = gData.InfoVision[nS4No-1][9] + 4;
					m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(20000);
				}
			}
		}
		break;
	case 16:
		if (m_pDX08->iInspectStage4Up && !m_pDX08->iInspectStage4Down) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				m_tVisionStage4Loop.Takt_Save(17, 10); m_tVisionStage4Loop.Takt_Start(17, 11); 
				dStage4PosX = m_pMoveData->dVisionStageX4[2] + (m_pEquipData->dPitchTop * gData.nTop2Cnt);
				g_objAJinAXL.Move_Absolute(AX_INSPECT_STAGE_X4, dStage4PosX);
//				g_objCommon.Move_Position(AX_TOP2_VISION_Z, 1);
				//dVision4PosZ = m_pMoveData->dTOPVisionZ2[1] + gData.dFocusOffset[nS4No-1][4+gData.nTop2Cnt];
				dVision4PosZ = m_pMoveData->dTOPVisionZ2[1];
				g_objAJinAXL.Move_Absolute(AX_TOP2_VISION_Z, dVision4PosZ);	nV4Retry = 0;
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(60000);
			}
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X4, dStage4PosX)) {
			if (g_objAJinAXL.Is_Done(AX_TOP2_VISION_Z)) {
				if (!m_tVisionStage4Loop.Waiting_Time(m_pEquipData->nDelayTime[9])) break;
				g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, -1, dStage4PosX);
				m_tVisionStage4Loop.Takt_Save(17, 11); m_tVisionStage4Loop.Takt_Start(17, 12); 
				gData.bTop2ScanDone = FALSE;	gData.nVsNo[1] = nS4No; gData.nVsIx[1] = gData.nTop2Cnt+1;
				int nModule1 = n4Tno1; if (gData.InfoVision[nS4No-1][gData.nTop2Cnt] < 1)   nModule1 = -1;
				int nModule5 = n4Tno5; if (gData.InfoVision[nS4No-1][gData.nTop2Cnt+4] < 1) nModule5 = -1;
				g_objInspector.Set_LoadComplete(INSPECTOR_PC3, "T2", gData.sLotID_VisionStage[nS4No-1], gData.nPortNo_VisionStage[nS4No-1], gData.nTrayNo_VisionStage[nS4No-1], nModule1, gData.nTrayNo_VisionStage[nS4No-1], nModule5);
				gAlm.sAlmLID[3] = gData.sLotID_VisionStage[nS4No-1]; gAlm.nAlmTNo[3] = gData.nTrayNo_VisionStage[nS4No-1]; gAlm.nAlmPNo[3] = nModule1;
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
			}
		}
		break;
	case 18:
		if (gData.bTop2ScanDone || !m_pEquipData->bUseTop2) {
			m_tVisionStage4Loop.Takt_Save(17, 12); m_tVisionStage4Loop.Takt_Start(17, 13); 
			gData.nTop2Cnt++; n4Tno1++; n4Tno5++;
			if (gData.nTop2Cnt >= 4) {
				dwV4RosTime[0] = GetTickCount();
				m_nVisionStage4Case = 20; m_tVisionStage4Loop.Set_LoopTime(5000);
			} else {
				m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
			}
		}
		break;
	case 19:
		if (n4FrontVisionCase < 19 || (n4FrontVisionCase >= 23 && gData.nTop2Cnt <= 1) || n4FrontVisionCase >= 25) {
			m_nVisionStage4Case = 16; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 20:
		if (n4FrontVisionCase < 20 || n4FrontVisionCase >= 25) {
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 21:
		if (m_pDX08->iInspectStage4Up && !m_pDX08->iInspectStage4Down) {
			if (m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) {
				if (g_objAJinAXL.Is_MoveDone(AX_INSPECT_STAGE_X4, dStage4PosX)) {
					m_tVisionStage4Loop.Takt_Save(17, 13); m_tVisionStage4Loop.Takt_Start(17, 14); 
					g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 4);
					m_pDY08->oInspectStage4Deg0 = TRUE; m_pDY08->oInspectStage4Deg90 = FALSE;
					g_objAJinAXL.Write_Output(8);
					m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
				}
			}
		}
		break;
	case 22:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 4)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, 4);
			m_tVisionStage4Loop.Takt_Save(17, 14); m_tVisionStage4Loop.Takt_Start(17, 15); 
			dwV4RosTime[1] = dwV4RosTime[0];
			gData.nVisionPos[1][2] = 0; gData.nVisionPos[1][4] = nS4No;
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
		}
		break;
	case 23:
		if (n4FrontVisionCase < 22 || n4FrontVisionCase > 34) {
			m_tVisionStage4Loop.Takt_Save(17, 15); m_tVisionStage4Loop.Takt_Start(17, 16); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 3);
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
		}
		return TRUE;
	case 24:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, 3);
			m_tVisionStage4Loop.Takt_Save(17, 16); m_tVisionStage4Loop.Takt_Start(17, 17); 
			dwV4RosTime[2] = dwV4RosTime[1];
			gData.nVisionPos[1][4] = 0; gData.nVisionPos[1][3] = nS4No;
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(30000);
		}
		break;
	case 25:
			m_nVisionStage4Case = 30; m_tVisionStage4Loop.Set_LoopTime(30000);
		break;
	case 26:	//RosTime 6초대기
		if (GetTickCount() - dwV4RosTime[2] >= 6000) {
			m_nVisionStage4Case = 30; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	//Unload Picker wait
		m_tVisionStage4Loop.Set_LoopTime(5000);
		return TRUE;

	case 31:
		if (m_pDX08->iInspectStage4Up && !m_pDX08->iInspectStage4Down)
		{
			if (m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut)
			{
				if (n4FrontVisionCase < 30 || n4FrontVisionCase > 52)
				{
					/*double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage2Case);
					double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX2[INSPECT_STAGE2_X_Top2Pos];
					if(dTarget < dCurrent) return TRUE;*/
										
					m_pDY08->oInspectStage4Up = FALSE; m_pDY08->oInspectStage4Down = TRUE;
					g_objAJinAXL.Write_Output(8);
					m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
				}
						
			}
		}
		return TRUE;		
	case 32:
		if (!m_pDX08->iInspectStage4Up && m_pDX08->iInspectStage4Down) 
		{
			m_tVisionStage4Loop.Takt_Save(17, 18); m_tVisionStage4Loop.Takt_Start(17, 19); 
			gData.nVisionPos[1][3] = 0; gData.nVisionPos[0][3] = nS4No;
			if (nS4No == 1)
			{
				m_pDY08->oInspectStage4Yin = FALSE; m_pDY08->oInspectStage4YOut = TRUE;
				g_objAJinAXL.Write_Output(8);
			}
			if (nS4No == 4)
			{
				m_pDY08->oInspectStage4Yin = FALSE; m_pDY08->oInspectStage4YOut = TRUE;
				g_objAJinAXL.Write_Output(8);
			}
			m_nVisionStage4Case = 34; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		break;
	case 34:
		if ((nS4No == 1 && !m_pDX08->iInspectStage4Yin && m_pDX08->iInspectStage4YOut) ||
			(nS4No == 2) || (nS4No == 3) ||
			(nS4No == 4 && !m_pDX08->iInspectStage4Yin && m_pDX08->iInspectStage4YOut) ) 
		{
			m_tVisionStage4Loop.Takt_Save(17, 19); m_tVisionStage4Loop.Takt_Start(17, 20); 
			m_nVisionStage4Case = 35; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		break;

	case 35:
		if (n4FrontVisionCase >= 0 && n4FrontVisionCase < 31) 
		{
			m_nVisionStage4Case = 61; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		else if (n4FrontVisionCase < 50 || n4FrontVisionCase >= 70) 
		{
			double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage2Case);
			double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX2[INSPECT_STAGE2_X_AlignPos];
			if(dTarget < dCurrent) return TRUE;

			m_nVisionStage4Case = 51; m_tVisionStage4Loop.Set_LoopTime(5000);
		} 
		else if (n4FrontVisionCase < 40 || n4FrontVisionCase >= 60) 
		{
			double dCurrent = g_objAJinAXL.Get_Position(m_nVisionStage2Case);
			double dTarget = g_objDataManager.Get_pMoveData()->dVisionStageX2[INSPECT_STAGE2_X_Top1Pos];
			if(dTarget < dCurrent && !Check_ModuleEmpty() ) return TRUE;

			m_nVisionStage4Case = 41; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 40:
		if (n4FrontVisionCase < 40 || n4FrontVisionCase >= 60) 
		{
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 41:
		if (!m_pDX08->iInspectStage4Up && m_pDX08->iInspectStage4Down) {
			m_tVisionStage4Loop.Takt_Save(17, 20); m_tVisionStage4Loop.Takt_Start(17, 21); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 2);
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 2)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, 2);
			m_tVisionStage4Loop.Takt_Save(17, 21); m_tVisionStage4Loop.Takt_Start(17, 22); 
			gData.nVisionPos[0][3] = 0; gData.nVisionPos[0][2] = nS4No;
			m_nVisionStage4Case = 50; m_tVisionStage4Loop.Set_LoopTime(60000);
		}
		break;
	case 50:
		if (n4FrontVisionCase < 50 || n4FrontVisionCase >= 70) 
		{			
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 51:
		if (!m_pDX08->iInspectStage4Up && m_pDX08->iInspectStage4Down) 
		{
			m_tVisionStage4Loop.Takt_Save(17, 22); m_tVisionStage4Loop.Takt_Start(17, 23); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, INSPECT_STAGE4_X_Top1Pos);
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
		}
		break;
	case 52:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, INSPECT_STAGE4_X_Top1Pos)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, INSPECT_STAGE4_X_Top1Pos);
			m_tVisionStage4Loop.Takt_Save(17, 23); m_tVisionStage4Loop.Takt_Start(17, 24); 
			gData.nVisionPos[0][2] = 0; gData.nVisionPos[0][1] = nS4No;
			m_nVisionStage4Case = 61; m_tVisionStage4Loop.Set_LoopTime(60000);
		}
		break;
	case 60:
		if (n4FrontVisionCase >= 0 && n4FrontVisionCase < 50) 
		{
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 61:
		if (!m_pDX08->iInspectStage4Up && m_pDX08->iInspectStage4Down) {
			m_tVisionStage4Loop.Takt_Save(17, 24); m_tVisionStage4Loop.Takt_Start(17, 25); 
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, INSPECT_STAGE4_X_AlignPos);
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
		}
		break;
	case 62:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, INSPECT_STAGE4_X_AlignPos)) {
			g_objCommon.Save_Motion(AX_INSPECT_STAGE_X4, INSPECT_STAGE4_X_AlignPos);
			m_tVisionStage4Loop.Takt_Save(17, 25); m_tVisionStage4Loop.Takt_Start(17, 26); 
			gData.nVisionPos[0][1] = 0; gData.nVisionPos[0][0] = nS4No;
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(10000);
		}
		break;
	case 63:
		if (!m_pDX08->iInspectStage4Up && m_pDX08->iInspectStage4Down) {
/*			if (nS4No == 1) {
				m_pDY08->oInspectStage4Yin = TRUE; m_pDY08->oInspectStage4YOut = FALSE;
				g_objAJinAXL.Write_Output(8);
			}
			if (nS4No == 4) {
				m_pDY08->oInspectStage4Yin = TRUE; m_pDY08->oInspectStage4YOut = FALSE;
				g_objAJinAXL.Write_Output(8);
			}*/
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		break;
	case 64:
//		if ((nS4No == 1 && m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) ||
//			(nS4No == 2) || (nS4No == 3) ||
//			(nS4No == 4 && m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) ) {
			m_nVisionStage4Case = 70; m_tVisionStage4Loop.Set_LoopTime(5000);
//		}
		break;

	case 70:
		if (n4FrontVisionCase > 4 && n4FrontVisionCase < 60) {
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		return TRUE;
	case 71:
		if (!m_pDX08->iInspectStage4Up && m_pDX08->iInspectStage4Down) {
			m_tVisionStage4Loop.Takt_Save(17, 26); m_tVisionStage4Loop.Takt_Start(17, 27); 
			m_pDY08->oInspectStage4Yin = TRUE; m_pDY08->oInspectStage4YOut = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		break;	
	case 72:
		if (m_pDX08->iInspectStage4Yin && !m_pDX08->iInspectStage4YOut) {
			m_tVisionStage4Loop.Takt_Save(17, 27); m_tVisionStage4Loop.Takt_Start(17, 28); 
			m_pDY08->oInspectStage4Up = TRUE; m_pDY08->oInspectStage4Down = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_nVisionStage4Case++; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		break;
	case 73:
		if (m_pDX08->iInspectStage4Up && !m_pDX08->iInspectStage4Down) {
			m_tVisionStage4Loop.Takt_Save(17, 28, TRUE);
			gData.nVisionPos[0][0] = 0; gData.nVisionPos[1][0] = nS4No;
			m_nVisionStage4Case = 0; m_tVisionStage4Loop.Set_LoopTime(5000);
		}
		break;

	}

	// 17. (Error : 6600)
	if (m_tVisionStage4Loop.Over_LoopTime()) {
//		if (m_nVisionStage4Case == 8 || m_nVisionStage4Case == 12 || m_nVisionStage4Case == 18) {
//			nV4Retry++;
//			if (nV4Retry == 1) { m_nVisionStage4Case--; return TRUE; }
//		}
//		if (m_nVisionStage4Case == 7 || m_nVisionStage4Case == 11 || m_nVisionStage4Case == 17) m_nVisionStage4Case++;
		if (m_nVisionStage4Case == 26) { m_nVisionStage4Case = 30; return TRUE; }
		g_objCommon.Show_Error(6600 + m_nVisionStage4Case);
		return FALSE;
	}
	return TRUE;
}

// 18. (Error : 7000)
BOOL CSequenceMain::Run_UnloadPicker1()
{
	static int n1No = 1;	//1고정
	static int n1VNo, n1NSNo, n1ModuleNo, n1PosX, n1PosY, n1UP, n1UT, n1UM, nJudgeNo1;
	static double d1PosX, d1PosY;

	switch (m_nUnloadPicker1Case) 
	{
	case 0:	// Wait
		n1VNo = 0;
		if (m_nVisionStage1Case == 30) n1VNo = 1;
		if (m_nVisionStage2Case == 30) n1VNo = 2;
		if (m_nVisionStage3Case == 30) n1VNo = 3;
		if (m_nVisionStage4Case == 30) n1VNo = 4;
		if (n1VNo > 0) 
		{
			if (gData.nTrayNo_VisionStage[n1VNo-1] > 0) 
			{
				m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(5000);

				m_sLog.Format("[UnloadPicker1: Start] Inspection StageNo(%d)", n1VNo);
				g_objLogFile.Save_HandlerLog(m_sLog);
			}
			else
			{
				if (m_nVisionStage1Case == 30) m_nVisionStage1Case = 31;
				if (m_nVisionStage2Case == 30) m_nVisionStage2Case = 31;
				if (m_nVisionStage3Case == 30) m_nVisionStage3Case = 31;
				if (m_nVisionStage4Case == 30) m_nVisionStage4Case = 31;
			}
		}
		if (Check_EmptyUnloadPicker()) 
		{
			if (m_nNGStage1Case == 30) m_nNGStage1Case = 31;
			if (m_nNGStage2Case == 30) m_nNGStage2Case = 31;
			if (m_nGoodStage1Case == 30) m_nGoodStage1Case = 31;
			if (m_nGoodStage2Case == 30) m_nGoodStage2Case = 31;
		}
		return TRUE;

	case 1:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0)) 
		{
			if (g_objCommon.Get_UnloadPickerUp(n1No))
			{
				g_objCommon.Move_Position(AX_UNLOAD_PICKER_X1, n1VNo);
				g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y1, n1VNo);
				g_objCommon.Move_Position(AX_UNLOAD_PICKER_P1, 0);
				m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 2:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_X1, n1VNo) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, n1VNo) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_P1, 0)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X1, n1VNo);	g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y1, n1VNo);	g_objCommon.Save_Motion(AX_UNLOAD_PICKER_P1, 0);
			m_tUnloadPicker1Loop.Takt_Start(18, 1, TRUE); 
			g_objCommon.Set_UnloadPickerOpen(n1No);
			g_objCommon.Set_UnloadPickerDown(n1No);

			gData.sLotID_UnloadPicker[n1No-1]  = gData.sLotID_VisionStage[n1VNo-1];
			gData.nTrayNo_UnloadPicker[n1No-1] = gData.nTrayNo_VisionStage[n1VNo-1];
			gData.nPortNo_UnloadPicker[n1No-1] = gData.nPortNo_VisionStage[n1VNo-1];
			gData.sLotID_UnloadPicker[2]	   = gData.sLotID_UnloadPicker[n1No-1];

			for(int i=0; i<10; i++) {
				gData.InfoUnloadPick[n1No-1][i] = gData.InfoVision[n1VNo-1][i];	gData.InfoVision[n1VNo-1][i] = 0;
			}
			gData.sLotID_VisionStage[n1VNo-1] = "";
			gData.nTrayNo_VisionStage[n1VNo-1] = gData.nPortNo_VisionStage[n1VNo-1] = 0;

			n1UP = gData.nPortNo_UnloadPicker[n1No-1] - 1;
			n1UT = gData.nTrayNo_UnloadPicker[n1No-1] - 1;
			n1UM = gData.InfoUnloadPick[n1No-1][9] - 1;
			for(int i=n1UM; (i<40 || i<n1UM+8); i++) gLot.nHistory[n1UP][n1UT][i][4] = 1;

			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 3:
		if (g_objCommon.Get_UnloadPickerDown(n1No)) {
			m_tUnloadPicker1Loop.Takt_Save(18, 1); m_tUnloadPicker1Loop.Takt_Start(18, 2); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z1, n1VNo);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, n1VNo))
		{
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z1, n1VNo);
			m_tUnloadPicker1Loop.Takt_Save(18, 2); m_tUnloadPicker1Loop.Takt_Start(18, 3); 
			g_objCommon.Set_VisionVacuumOff(n1VNo);
			g_objCommon.Set_UnloadPickerClose(n1No);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objCommon.Get_UnloadPickerClose(n1No)) 
		{
			if (!m_tUnloadPicker1Loop.Waiting_Time(m_pEquipData->nDelayTime[8])) break;
			m_tUnloadPicker1Loop.Takt_Save(18, 3); m_tUnloadPicker1Loop.Takt_Start(18, 4); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z1, 0);
			g_objCommon.Set_UnloadPickerUp(n1No);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 6:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0))
		{
			if (g_objCommon.Get_UnloadPickerUp(n1No)) 
			{
				g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z1, 0);
				m_tUnloadPicker1Loop.Takt_Save(18, 4); m_tUnloadPicker1Loop.Takt_Start(18, 5); 
				m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 7:
		if (g_objCommon.Get_UnloadPickerCheck(n1No, 9, gData.InfoUnloadPick[n1No-1])) 
		{
			if (g_objCommon.Get_UnloadPickerUp(n1No))
			{
				m_tUnloadPicker1Loop.Takt_Save(18, 5); m_tUnloadPicker1Loop.Takt_Start(18, 6); 
				if (m_nVisionStage1Case == 30) m_nVisionStage1Case = 31;
				if (m_nVisionStage2Case == 30) m_nVisionStage2Case = 31;
				if (m_nVisionStage3Case == 30) m_nVisionStage3Case = 31;
				if (m_nVisionStage4Case == 30) m_nVisionStage4Case = 31;

				m_nUnloadPicker1Case = 10; m_tUnloadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 10:
		if (m_nUnloadPicker2Case > 33 && m_nUnloadPicker2Case < 70)
		{
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_X1, UNLOAD_PICKER1_X_NG_STAGE1_11);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_P1, 1);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 11:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_X1, UNLOAD_PICKER1_X_NG_STAGE1_11) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_P1, 1)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X1, UNLOAD_PICKER1_X_NG_STAGE1_11);	g_objCommon.Save_Motion(AX_UNLOAD_PICKER_P1, 1);
			gAlm.sAlmLID[0] = gData.sLotID_UnloadPicker[n1No-1]; gAlm.nAlmTNo[0] = gData.nTrayNo_UnloadPicker[n1No-1]; gAlm.nAlmPNo[0] = gData.InfoUnloadPick[n1No-1][9];
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
		}
		break;
	case 12:
		if (Check_InspectDone(n1No, gData.nPortNo_UnloadPicker[n1No-1], gData.nTrayNo_UnloadPicker[n1No-1])) {
			if (!m_tUnloadPicker1Loop.Waiting_Time(500)) break;
			m_tUnloadPicker1Loop.Takt_Save(18, 6); m_tUnloadPicker1Loop.Takt_Start(18, 7); 
			Set_ROSTime(n1No, gData.nPortNo_UnloadPicker[n1No-1], gData.nTrayNo_UnloadPicker[n1No-1]);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(300000);	//5분
		}
		break;
	case 13:
		if (Check_ROSDone(n1No, gData.nPortNo_UnloadPicker[n1No-1], gData.nTrayNo_UnloadPicker[n1No-1])) {
			m_tUnloadPicker1Loop.Takt_Save(18, 7); m_tUnloadPicker1Loop.Takt_Start(18, 8); 
			m_nUnloadPicker1Case = 18; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;

	case 14:
		// 0:None, 1:요청, 2:Start수신 Run, 3:End송신
		if (!m_pEquipData->bUseMES || gMes.nMarStatus == 2) 
		{	
			m_nUnloadPicker1Case = 17; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		else
		{
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (gMes.nMarStatus == 3) 
		{
			m_nUnloadPicker1Case = 14; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		else
		{
			gMes.nMarStatus = gMes.nMarCount = gMes.nMarTrayCount = gMes.nNGLotCount = gMes.nManualEnd = 0;
			gMes.sHostNGLotID = gMes.sHostNGVendor = gMes.sStartTime = gMes.sEndTime = "";

			if (m_pEquipData->bUseMES) g_objMesAgent.Set_NGLotRequest();
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (!m_pEquipData->bUseMES || gMes.nMarStatus == 2) {
			m_sLog.Format("[UnloadPicer1_NGLot-Start] NGLot(%s) NGLot(%d-%d-%d-%d) S1(%d-%d)",
					gMes.sHostNGLotID, gMes.nMarCount, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case);
			g_objLogFile.Save_HandlerLog(m_sLog);

			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (m_nUnloadPicker2Case < 20 || (m_nUnloadPicker2Case > 42 && m_nUnloadPicker2Case < 70)) {
			m_nUnloadPicker1Case = 19; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;

	case 18:
		if (m_nUnloadPicker2Case < 14 || (m_nUnloadPicker2Case > 29 && m_nUnloadPicker2Case < 70)) {
			if (m_nNGStage1Case == 30 || m_nNGStage2Case == 30) {
				m_nUnloadPicker1Case = 14; m_tUnloadPicker1Loop.Set_LoopTime(30000);
			}
		}
		return TRUE;

	case 19:
		int nType;
		n1ModuleNo = Check_NGExist(n1No, nType);
		nJudgeNo1 = nType;
		if (n1ModuleNo > 0) 
		{
			m_nUnloadPicker1Case = 21; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		} 
		else
		{
			//NGLot수동완공
			if (gMes.nManualEnd == 1) 
			{	
				g_objMesAgent.Set_NGLotEnd(gMes.sHostNGLotID, gMes.nMarCount);
				m_nUnloadPicker1Case = 18; m_tUnloadPicker1Loop.Set_LoopTime(60000);
				gMes.nManualEnd = 0;

				if (m_nNGStage1Case == 30) { m_nNGStage1Case = 31; gData.nNGLot_NGTray[0] = 1; }
				if (m_nNGStage2Case == 30) { m_nNGStage2Case = 31; gData.nNGLot_NGTray[1] = 1; }

				m_sLog.Format("[UnloadPicker_NGLot-End:11] NGLot(%s) NGLot(%d-%d-%d-%d) S1(%d-%d) S2(%d-%d)",
							gMes.sHostNGLotID, gMes.nMarCount, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case, gData.nNGLot_NGTray[0] , gData.nNGLot_NGTray[1]);
				g_objLogFile.Save_HandlerLog(m_sLog);

				if (!m_pEquipData->bUseMES) 
				{
					gMes.nMarStatus = gMes.nMarCount = gMes.nMarTrayCount = gMes.nNGLotCount = gMes.nManualEnd = 0;
				}
			}

			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 20:
		if (m_nUnloadPicker2Case < 20 || (m_nUnloadPicker2Case > 42 && m_nUnloadPicker2Case < 70)) 
		{
			m_nUnloadPicker1Case = 30; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 21:
		if (m_nUnloadPicker2Case < 20 || (m_nUnloadPicker2Case > 42 && m_nUnloadPicker2Case < 70)) 
		{
			n1NSNo = 0;
//			if (m_nNGStage1Case == 30 && !m_pDX11->iNGStage1TrayExist && gData.nPortNo_NGTray[0] < 1) m_nNGStage1Case = 31;
//			if (m_nNGStage2Case == 30 && !m_pDX11->iNGStage2TrayExist && gData.nPortNo_NGTray[1] < 1) m_nNGStage2Case = 31;
			if (m_nNGStage1Case == 30 && gNG->nTrayOX[1][0] == 0) m_nNGStage1Case = 31;
			if (m_nNGStage2Case == 30 && gNG->nTrayOX[1][1] == 0) m_nNGStage2Case = 31;

			if (m_nNGStage1Case == 30) n1NSNo = 5;
			if (m_nNGStage2Case == 30) n1NSNo = 6;
			if (n1NSNo > 0) 
			{
				if (Select_NGTrayPoketNo(nJudgeNo1, n1PosX, n1PosY)) 
				{
					g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y1, n1NSNo);
					m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
				}
				else
				{
					if (gMes.nMarTrayCount >= gData.nMgnTrayCount) 
					{	//NGLot자동완공
						g_objMesAgent.Set_NGLotEnd(gMes.sHostNGLotID, gMes.nMarCount);
						m_nUnloadPicker1Case = 18; m_tUnloadPicker1Loop.Set_LoopTime(60000);

						if (m_nNGStage1Case == 30) { m_nNGStage1Case = 31; gData.nNGLot_NGTray[0] = 1; }
						if (m_nNGStage2Case == 30) { m_nNGStage2Case = 31; gData.nNGLot_NGTray[1] = 1; }

						m_sLog.Format("[UnloadPicker_NGLot-End:12] NGLot(%s) NGLot(%d-%d-%d-%d) S1(%d-%d) S2(%d-%d)",
										gMes.sHostNGLotID, gMes.nMarCount, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case, gData.nNGLot_NGTray[0] , gData.nNGLot_NGTray[1]);
						g_objLogFile.Save_HandlerLog(m_sLog);

						if (!m_pEquipData->bUseMES) 
						{
							gMes.nMarStatus = gMes.nMarCount = gMes.nMarTrayCount = gMes.nNGLotCount = gMes.nManualEnd = 0;
						}
					} 
					else
					{
						if (m_nNGStage1Case == 30) { m_nNGStage1Case = 31; gData.nNGLot_NGTray[0] = 0; }
						if (m_nNGStage2Case == 30) { m_nNGStage2Case = 31; gData.nNGLot_NGTray[1] = 0; }
					}
				}
			}
		}
		return TRUE;
	case 22:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, n1NSNo)) 
		{
			if (Get_TrayPosition(n1No, (n1NSNo-4), n1PosX, n1PosY, d1PosX, d1PosY)) 
			{
				g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y1, n1NSNo);
				m_tUnloadPicker1Loop.Takt_Save(18, 8); m_tUnloadPicker1Loop.Takt_Start(18, 9); 
//				d1PosX = d1PosX + (m_pEquipData->dTrayPitchX * (n1ModuleNo - n1PosX));
				d1PosX = d1PosX + (m_pEquipData->dTrayPitchX * (n1ModuleNo - 1));
				g_objAJinAXL.Move_Absolute(AX_UNLOAD_PICKER_X1, d1PosX);
				if (n1NSNo==5) g_objAJinAXL.Move_Absolute(AX_NG_STAGE_Y1, d1PosY);
				if (n1NSNo==6) g_objAJinAXL.Move_Absolute(AX_NG_STAGE_Y2, d1PosY);
				m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);

//				m_sLog.Format("A2 Data [Picker:%d Job:%d Opt:%d] Type(%d) MNo(%d) XY(%d-%d) PosXY(%0.3lf-%0.3lf)", n1No, (n1NSNo-4), m_pEquipData->bUseNGSort, nJudgeNo1, n1ModuleNo, n1PosX, n1PosY, d1PosX, d1PosY);
//				g_objLogFile.Save_HandlerLog(m_sLog);
			}
		}
		break;
	case 23:
		if (g_objAJinAXL.Is_MoveDone(AX_UNLOAD_PICKER_X1, d1PosX))
		{
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X1, -1, d1PosX);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 24:
		if ((n1NSNo==5 && g_objAJinAXL.Is_MoveDone(AX_NG_STAGE_Y1, d1PosY)) ||
			(n1NSNo==6 && g_objAJinAXL.Is_MoveDone(AX_NG_STAGE_Y2, d1PosY)) ) 
		{
			if (n1NSNo==5) g_objCommon.Save_Motion(AX_NG_STAGE_Y1, -1, d1PosY);
			if (n1NSNo==6) g_objCommon.Save_Motion(AX_NG_STAGE_Y2, -1, d1PosY);
			m_tUnloadPicker1Loop.Takt_Save(18, 9); m_tUnloadPicker1Loop.Takt_Start(18, 10); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z1, n1NSNo);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 25:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, n1NSNo)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z1, n1NSNo);
			m_tUnloadPicker1Loop.Takt_Save(18, 10); m_tUnloadPicker1Loop.Takt_Start(18, 11); 
			g_objCommon.Set_UnloadPickerDown(n1No, n1ModuleNo);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 26:
		if (g_objCommon.Get_UnloadPickerDown(n1No, n1ModuleNo)) {
			m_tUnloadPicker1Loop.Takt_Save(18, 11); m_tUnloadPicker1Loop.Takt_Start(18, 12); 
			g_objCommon.Set_UnloadPickerOpen(n1No, n1ModuleNo);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 27:
		if (g_objCommon.Get_UnloadPickerOpen(n1No, n1ModuleNo)) {
			if (!m_tUnloadPicker1Loop.Waiting_Time(m_pEquipData->nDelayTime[7])) break;
			m_tUnloadPicker1Loop.Takt_Save(18, 12); m_tUnloadPicker1Loop.Takt_Start(18, 13); 
			g_objCommon.Set_UnloadPickerUp(n1No);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 28:
		if (g_objCommon.Get_UnloadPickerUp(n1No)) {
			m_tUnloadPicker1Loop.Takt_Save(18, 13); m_tUnloadPicker1Loop.Takt_Start(18, 14); 
			gLot.nNgCount[n1UP]++;	gLot.nTrayPutCnt[n1UP][1]++;
			if (Check_EmptyNGTray()) gMes.nMarTrayCount++;
			gLot.nOutTrayCnt[n1UP][1] = gMes.nMarTrayCount; if (gLot.nOutTrayCnt[n1UP][1] == 0) gLot.nOutTrayCnt[n1UP][1] = 1;

			gData.sLotID_NGTray[n1NSNo-5]  = gData.sLotID_UnloadPicker[n1No-1];
			gData.nTrayNo_NGTray[n1NSNo-5] = gData.nTrayNo_UnloadPicker[n1No-1];
			gData.nPortNo_NGTray[n1NSNo-5] = gData.nPortNo_UnloadPicker[n1No-1];
			gData.sLotID_NGTray[2]  = gData.sLotID_NGTray[n1NSNo-5];

			gData.InfoNgTray[n1PosY-1][n1PosX-1] = gData.InfoUnloadPick[n1No-1][n1ModuleNo-1];
			gData.InfoUnloadPick[n1No-1][n1ModuleNo-1] = 0;

			gMes.nNGLotCount++;
			gLot.nHistory[n1UP][n1UT][n1UM+n1ModuleNo-1][6] = gLot.nOutTrayCnt[n1UP][1];
			gLot.nHistory[n1UP][n1UT][n1UM+n1ModuleNo-1][7] = (n1PosY-1) * 4 + n1PosX;
			gLot.nHistory[n1UP][n1UT][n1UM+n1ModuleNo-1][8] = n1NSNo-4;
			g_objLogFile.Save_OutTrayNLog(n1UP+1, n1UT+1, n1UM+n1ModuleNo); 
			g_objMesAgent.Set_CmEnd(1, n1UP+1, n1UT+1, n1UM+n1ModuleNo, (n1PosY-1) * 4 + n1PosX);

			m_nUnloadPicker1Case = 19; m_tUnloadPicker1Loop.Set_LoopTime(30000);

			m_sLog.Format("[UnloadPicker_NGLot-NGDown:%d Job:%d Option:%d] P(%d-1) Type(%d) => (%d,%d-%0.3lf,%0.3lf) NGLot(%d-%d-%d-%d) S1(%d-%d) S2(%d-%d)",
				n1No, (n1NSNo-4), m_pEquipData->bUseAlign2, n1ModuleNo, gData.InfoNgTray[n1PosY-1][n1PosX-1], n1PosX, n1PosY, d1PosX, d1PosY, m_nUnloadPicker1Case, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case, gData.nNGLot_NGTray[0], gData.nNGLot_NGTray[1]);
			g_objLogFile.Save_HandlerLog(m_sLog);

			if (gData.InfoNgTray[n1PosY-1][n1PosX-1] == 12) {
				gData.nNoReadNo = (n1PosY-1)*4 + n1PosX;
				gMes.nNoReadCount++;

				m_sLog.Format("[NG-Tray Barcode No Read => TrayNo:%d Position:%d Total-Count:%d", gMes.nMarTrayCount, gData.nNoReadNo, gMes.nNoReadCount);
				g_objLogFile.Save_HandlerLog(m_sLog);
				g_objCommon.Show_Error(7099);
				return FALSE;
			} 
		}
		break;

	/*case 29:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, 0)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y1, 0);
			m_nUnloadPicker1Case = 40; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;*/
	case 30:
		n1ModuleNo = Check_GoodExist(n1No, n1PosX, n1PosY);
		if (n1ModuleNo > 0) 
		{
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		} 
		else 
		{
//			if (Check_LotEndUnloadNG(gData.sLotID_UnloadPicker[n1No-1], gData.nPortNo_UnloadPicker[n1No-1], n1No)) {
//				if (m_nNGStage1Case == 30)   m_nNGStage1Case = 31;
//				if (m_nNGStage2Case == 30)   m_nNGStage2Case = 31;
//			}
			if (Check_GooodTrayFull()) {
				if (m_nGoodStage1Case == 30) m_nGoodStage1Case = 31;
				if (m_nGoodStage2Case == 30) m_nGoodStage2Case = 31;
			}
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y1, 0);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z1, 0);
			

			CString sLotID  = gData.sLotID_UnloadPicker[n1No-1];
			int		nPortNo = gData.nPortNo_UnloadPicker[n1No-1];
			gData.sLotID_UnloadPicker[n1No-1] = "";
			gData.nTrayNo_UnloadPicker[n1No-1] = gData.nPortNo_UnloadPicker[n1No-1] = 0;
			for(int i=0; i<10; i++) gData.InfoUnloadPick[n1No-1][i] = 0;

			if (Check_LotEndUnloadPicker(sLotID, nPortNo)) {
				if (m_nGoodStage1Case == 30) m_nGoodStage1Case = 31;
				if (m_nGoodStage2Case == 30) m_nGoodStage2Case = 31;
			}	
			
			m_nUnloadPicker1Case = 41; m_tUnloadPicker1Loop.Set_LoopTime(15000);
		}
		break;
	case 31:
		if (m_nUnloadPicker2Case < 30 ||  (m_nUnloadPicker2Case > 42 && m_nUnloadPicker2Case < 70)) {
			if (g_objAJinAXL.Is_Done(AX_UNLOAD_PICKER_X1)) {
				n1NSNo = 0;
//				if (m_nGoodStage1Case == 30 && !m_pDX12->iGoodStage1TrayExist && gData.nTrayNo_GoodTray[0] < 1) m_nGoodStage1Case = 31;
//				if (m_nGoodStage2Case == 30 && !m_pDX12->iGoodStage2TrayExist && gData.nTrayNo_GoodTray[1] < 1) m_nGoodStage2Case = 31;
				if (m_nGoodStage1Case == 30 && gNG->nTrayOX[2][0] == 0) m_nGoodStage1Case = 31;
				if (m_nGoodStage2Case == 30 && gNG->nTrayOX[2][1] == 0) m_nGoodStage2Case = 31;
				if (m_nGoodStage1Case == 30) n1NSNo = 7;
				if (m_nGoodStage2Case == 30) n1NSNo = 8;
				if (n1NSNo > 0) {
					if (Select_GoodTrayPoketNo(n1UP, n1UT, n1PosX, n1PosY)) {
						g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y1, n1NSNo);
						g_objCommon.Move_Position(AX_UNLOAD_PICKER_P1, 2);
						m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
					} else {
						if (m_nGoodStage1Case == 30) m_nGoodStage1Case = 31;
						if (m_nGoodStage2Case == 30) m_nGoodStage2Case = 31;
					}
				} else {
					if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_X1, 7)) g_objCommon.Move_Position(AX_UNLOAD_PICKER_X1, 7);
				}
			}
		}
		return TRUE;
	case 32:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, n1NSNo) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_P1, 2)) {
			if (Get_TrayPosition(n1No, (n1NSNo-4), n1PosX, n1PosY, d1PosX, d1PosY)) {
				g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y1, n1NSNo);	g_objCommon.Save_Motion(AX_UNLOAD_PICKER_P1, 2);
				m_tUnloadPicker1Loop.Takt_Save(18, 14); m_tUnloadPicker1Loop.Takt_Start(18, 15); 
//				d1PosX = d1PosX + (m_pEquipData->dTrayPitchX * (n1ModuleNo - n1PosX));
				d1PosX = d1PosX + (m_pEquipData->dTrayPitchX * (n1ModuleNo - 1));
				g_objAJinAXL.Move_Absolute(AX_UNLOAD_PICKER_X1, d1PosX);
				if (n1NSNo==7) g_objAJinAXL.Move_Absolute(AX_GOOD_STAGE_Y1, d1PosY);
				if (n1NSNo==8) g_objAJinAXL.Move_Absolute(AX_GOOD_STAGE_Y2, d1PosY);
				m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);

				m_sLog.Format("A2 Data [Picker:%d Job:%d] PosX(%0.3lf) (%d,%d)", n1No, (n1NSNo-4), d1PosX, n1ModuleNo, n1PosX);
				g_objLogFile.Save_HandlerLog(m_sLog);
			}
		}
		break;
	case 33:
		if (g_objAJinAXL.Is_MoveDone(AX_UNLOAD_PICKER_X1, d1PosX)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X1, -1, d1PosX);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 34:
		if ((n1NSNo==7 && g_objAJinAXL.Is_MoveDone(AX_GOOD_STAGE_Y1, d1PosY)) ||
			(n1NSNo==8 && g_objAJinAXL.Is_MoveDone(AX_GOOD_STAGE_Y2, d1PosY)) ) {
			if (n1NSNo==7) g_objCommon.Save_Motion(AX_GOOD_STAGE_Y1, -1, d1PosY);
			if (n1NSNo==8) g_objCommon.Save_Motion(AX_GOOD_STAGE_Y2, -1, d1PosY);
			m_tUnloadPicker1Loop.Takt_Save(18, 15); m_tUnloadPicker1Loop.Takt_Start(18, 16); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z1, n1NSNo);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 35:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, n1NSNo)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z1, n1NSNo);
			m_tUnloadPicker1Loop.Takt_Save(18, 16); m_tUnloadPicker1Loop.Takt_Start(18, 17); 
			g_objCommon.Set_UnloadPickerDown(n1No, 9, n1ModuleNo, n1PosX, gData.InfoUnloadPick[n1No-1]);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 36:
		if (g_objCommon.Get_UnloadPickerDown(n1No, 9, n1ModuleNo, n1PosX, gData.InfoUnloadPick[n1No-1])) {
			m_tUnloadPicker1Loop.Takt_Save(18, 17); m_tUnloadPicker1Loop.Takt_Start(18, 18); 
			g_objCommon.Set_UnloadPickerOpen(n1No, 9, n1ModuleNo, n1PosX, gData.InfoUnloadPick[n1No-1]);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 37:
		if (g_objCommon.Get_UnloadPickerOpen(n1No, 9, n1ModuleNo, n1PosX, gData.InfoUnloadPick[n1No-1])) {
			if (!m_tUnloadPicker1Loop.Waiting_Time(m_pEquipData->nDelayTime[7])) break;
			m_tUnloadPicker1Loop.Takt_Save(18, 18); m_tUnloadPicker1Loop.Takt_Start(18, 19); 
			g_objCommon.Set_UnloadPickerUp(n1No);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 38:
		if (g_objCommon.Get_UnloadPickerUp(n1No)) {
			m_tUnloadPicker1Loop.Takt_Save(18, 19); m_tUnloadPicker1Loop.Takt_Start(18, 20); 
			if (Check_EmptyGoodTray()) {
				if (m_pEquipData->bUseGoodSort) gLot.nOutTrayCnt[n1UP][0] = n1UT+1;
				else							gLot.nOutTrayCnt[n1UP][0]++;
			}

			gData.sLotID_GoodTray[n1NSNo-7]  = gData.sLotID_UnloadPicker[n1No-1];
			gData.nTrayNo_GoodTray[n1NSNo-7] = gData.nTrayNo_UnloadPicker[n1No-1];
			gData.nPortNo_GoodTray[n1NSNo-7] = gData.nPortNo_UnloadPicker[n1No-1];
			gData.sLotID_GoodTray[2]  = gData.sLotID_GoodTray[n1NSNo-7];

			for(int i=0; i<gData.nUnloadPick1DownCnt; i++) {
				gLot.nGoodCount[n1UP]++;	gLot.nTrayPutCnt[n1UP][0]++;
				gData.InfoGoodTray[n1PosY-1][n1PosX-1+i] = gData.InfoUnloadPick[n1No-1][n1ModuleNo-1+i];
				gData.InfoUnloadPick[n1No-1][n1ModuleNo-1+i] = 0;

				gLot.nHistory[n1UP][n1UT][n1UM+n1ModuleNo-1+i][5] = gLot.nOutTrayCnt[n1UP][0];
				gLot.nHistory[n1UP][n1UT][n1UM+n1ModuleNo-1+i][7] = (n1PosY-1) * 4 + n1PosX + i;
				gLot.nHistory[n1UP][n1UT][n1UM+n1ModuleNo-1+i][8] = n1NSNo-6;
				g_objLogFile.Save_OutTrayGLog(n1UP+1, n1UT+1, n1UM+n1ModuleNo+i);
				g_objMesAgent.Set_CmEnd(0, n1UP+1, n1UT+1, n1UM+n1ModuleNo+i, (n1PosY-1) * 4 + n1PosX + i);
			}

			m_sLog.Format("[UnloadPicker:%d Job:%d Option:%d] P(%d-%d) => (%d,%d-%0.3lf,%0.3lf)", n1No, (n1NSNo-4), m_pEquipData->bUseAlign2, n1ModuleNo, gData.nUnloadPick1DownCnt, n1PosX, n1PosY, d1PosX, d1PosY);
			g_objLogFile.Save_HandlerLog(m_sLog);

			m_nUnloadPicker1Case = 30; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;

	case 40:
		if (g_objCommon.Get_UnloadPickerUp(n1No)) {
			
		}
		break;
	case 41:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, UNLOADPICKER1_Z_Ready) 
			&& g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, UNLOADPICKER1_Y_Ready)) 
		{
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z1, UNLOADPICKER1_Z_Ready);		
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y1, UNLOADPICKER1_Y_Ready);
			m_tUnloadPicker1Loop.Takt_Save(18, 20); 
			
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_X1, UNLOADPICKER1_X_InspectionStage1);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_P1, UNLOADPICKER1_P_InspectionStage);
			m_tUnloadPicker1Loop.Takt_Start(18, 22); 

			m_nUnloadPicker1Case = 43; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 43:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_X1, UNLOADPICKER1_X_InspectionStage1) 
			&& g_objCommon.Check_Position(AX_UNLOAD_PICKER_P1, UNLOADPICKER1_P_InspectionStage) ) 
		{
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X1, UNLOADPICKER1_X_InspectionStage1);
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_P1, UNLOADPICKER1_P_InspectionStage); 
			m_tUnloadPicker1Loop.Takt_Save(18, 22); m_tUnloadPicker1Loop.Takt_Start(18, 23); 
			m_nUnloadPicker1Case = 50; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;

	case 50:
		if (m_nUnloadPicker2Case > 11 && m_nUnloadPicker2Case < 50) 
		{
			m_tUnloadPicker1Loop.Takt_Save(18, 23); m_tUnloadPicker1Loop.Takt_Start(18, 24); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y1, 1);
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 51:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, 1)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y1, 1);
			m_tUnloadPicker1Loop.Takt_Save(18, 24, TRUE);
			m_nUnloadPicker1Case = 0; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;

	case 81:
		if (g_objCommon.Get_UnloadPickerUp(n1No)) 
		{
			if (g_objCommon.Get_UnloadPickerCheck(n1No, 9, gData.InfoUnloadPick[n1No-1])) 
			{
				m_nUnloadPicker1Case = 7; m_tUnloadPicker1Loop.Set_LoopTime(30000);
			}
			else
			{
				for(int i=0; i<8; i++) 
				{
					if (gData.nUnloadPicker1ErrNo[i] == 1) 
					{
						g_objCommon.Set_UnloadPickerOpen(n1No, i+1);
					}
				}
				m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 82:
		if (g_objCommon.Get_UnloadPickerUp(n1No))
		{
			if (!m_tUnloadPicker1Loop.Waiting_Time(500)) break;
			for(int i=0; i<8; i++) 
			{
				if (gData.nUnloadPicker1ErrNo[i] == 1) 
				{
					g_objCommon.Set_UnloadPickerDown(n1No, i+1);
				}
			}
			m_nUnloadPicker1Case++; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;
	case 83:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0))
		{
			if (!m_tUnloadPicker1Loop.Waiting_Time(500)) break;
			m_tUnloadPicker1Loop.Takt_Save(18, 1); m_tUnloadPicker1Loop.Takt_Start(18, 2); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z1, n1VNo);
			m_nUnloadPicker1Case = 4; m_tUnloadPicker1Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 18. (Error : 7000)
	if (m_tUnloadPicker1Loop.Over_LoopTime()) 
	{
		if (m_nUnloadPicker1Case == 12 && m_pEquipData->bUseAutoSkip) 
		{
			Set_ReInspectDone(1, gData.nPortNo_UnloadPicker[0], gData.nTrayNo_UnloadPicker[0]);
			m_tUnloadPicker1Loop.Set_LoopTime(30000);
			return TRUE;
		}
		g_objCommon.Show_Error(7000 + m_nUnloadPicker1Case);
		return FALSE;
	}
	return TRUE;
}

// 19. (Error : 7500)
BOOL CSequenceMain::Run_UnloadPicker2()
{
	static int n2No = 2;	//2고정
	static int n2VNo, n2NSNo, n2ModuleNo, n2PosX, n2PosY, n2UP, n2UT, n2UM, nJudgeNo2;
	static double d2PosX, d2PosY;

	switch (m_nUnloadPicker2Case) {
	case 0:	// Wait
		n2VNo = 0;
		if (m_nVisionStage1Case == 30) n2VNo = 1;
		if (m_nVisionStage2Case == 30) n2VNo = 2;
		if (m_nVisionStage3Case == 30) n2VNo = 3;
		if (m_nVisionStage4Case == 30) n2VNo = 4;
		if (n2VNo > 0) {
			if (gData.nTrayNo_VisionStage[n2VNo-1] > 0) {
				m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(5000);

				m_sLog.Format("[UnloadPicker2: Start] Inspection StageNo(%d)", n2VNo);
				g_objLogFile.Save_HandlerLog(m_sLog);
			} else {
				if (m_nVisionStage1Case == 30) m_nVisionStage1Case = 31;
				if (m_nVisionStage2Case == 30) m_nVisionStage2Case = 31;
				if (m_nVisionStage3Case == 30) m_nVisionStage3Case = 31;
				if (m_nVisionStage4Case == 30) m_nVisionStage4Case = 31;
			}
		}
		if (Check_EmptyUnloadPicker()) {
			if (m_nNGStage1Case == 30) m_nNGStage1Case = 31;
			if (m_nNGStage2Case == 30) m_nNGStage2Case = 31;
			if (m_nGoodStage1Case == 30) m_nGoodStage1Case = 31;
			if (m_nGoodStage2Case == 30) m_nGoodStage2Case = 31;
		}
		return TRUE;

	case 1:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0)) {
			if (g_objCommon.Get_UnloadPickerUp(n2No)) {
				g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z2, 0);
				g_objCommon.Move_Position(AX_UNLOAD_PICKER_X2, n2VNo);
				g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y2, n2VNo);
				g_objCommon.Move_Position(AX_UNLOAD_PICKER_P2, 0);
				m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(10000);
			}
		}
		break;
	case 2:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_X2, n2VNo) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, n2VNo) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_P2, 0)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X2, n2VNo);	g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y2, n2VNo);	g_objCommon.Save_Motion(AX_UNLOAD_PICKER_P2, 0);
			m_tUnloadPicker2Loop.Takt_Start(19, 1, TRUE); 
			g_objCommon.Set_UnloadPickerOpen(n2No);
			g_objCommon.Set_UnloadPickerDown(n2No);

			gData.sLotID_UnloadPicker[n2No-1]  = gData.sLotID_VisionStage[n2VNo-1];
			gData.nTrayNo_UnloadPicker[n2No-1] = gData.nTrayNo_VisionStage[n2VNo-1];
			gData.nPortNo_UnloadPicker[n2No-1] = gData.nPortNo_VisionStage[n2VNo-1];
			gData.sLotID_UnloadPicker[2]	   = gData.sLotID_UnloadPicker[n2No-1];

			for(int i=0; i<10; i++) {
				gData.InfoUnloadPick[n2No-1][i] = gData.InfoVision[n2VNo-1][i];	gData.InfoVision[n2VNo-1][i] = 0;
			}
			gData.sLotID_VisionStage[n2VNo-1] = "";
			gData.nTrayNo_VisionStage[n2VNo-1] = gData.nPortNo_VisionStage[n2VNo-1] = 0;

			n2UP = gData.nPortNo_UnloadPicker[n2No-1] - 1;
			n2UT = gData.nTrayNo_UnloadPicker[n2No-1] - 1;
			n2UM = gData.InfoUnloadPick[n2No-1][9] - 1;
			for(int i=n2UM; (i<40 || i<n2UM+8); i++) gLot.nHistory[n2UP][n2UT][i][4] = 2;

			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 3:
		if (g_objCommon.Get_UnloadPickerDown(n2No)) {
			m_tUnloadPicker2Loop.Takt_Save(19, 1); m_tUnloadPicker2Loop.Takt_Start(19, 2); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z2, n2VNo);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, n2VNo)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z2, n2VNo);
			m_tUnloadPicker2Loop.Takt_Save(19, 2); m_tUnloadPicker2Loop.Takt_Start(19, 3); 
			g_objCommon.Set_VisionVacuumOff(n2VNo);
			g_objCommon.Set_UnloadPickerClose(n2No);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objCommon.Get_UnloadPickerClose(n2No)) {
			if (!m_tUnloadPicker2Loop.Waiting_Time(m_pEquipData->nDelayTime[8])) break;
			m_tUnloadPicker2Loop.Takt_Save(19, 3); m_tUnloadPicker2Loop.Takt_Start(19, 4); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z2, 0);
			g_objCommon.Set_UnloadPickerUp(n2No);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 6:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0)) {
			if (g_objCommon.Get_UnloadPickerUp(n2No)) {
				g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z2, 0);
				m_tUnloadPicker2Loop.Takt_Save(19, 4); m_tUnloadPicker2Loop.Takt_Start(19, 5); 
				m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 7:
		if (g_objCommon.Get_UnloadPickerCheck(n2No, 9, gData.InfoUnloadPick[n2No-1])) {
			if (g_objCommon.Get_UnloadPickerUp(n2No)) {
				m_tUnloadPicker2Loop.Takt_Save(19, 5); m_tUnloadPicker2Loop.Takt_Start(19, 6); 
				if (m_nVisionStage1Case == 30) m_nVisionStage1Case = 31;
				if (m_nVisionStage2Case == 30) m_nVisionStage2Case = 31;
				if (m_nVisionStage3Case == 30) m_nVisionStage3Case = 31;
				if (m_nVisionStage4Case == 30) m_nVisionStage4Case = 31;

				m_nUnloadPicker2Case = 10; m_tUnloadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;

	case 10:
		if (m_nUnloadPicker1Case > 33 && m_nUnloadPicker1Case < 70) {
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_X2, 5);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_P2, 1);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 11:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_X2, 5) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_P2, 1)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X2, 5);
			gAlm.sAlmLID[0] = gData.sLotID_UnloadPicker[n2No-1]; gAlm.nAlmTNo[0] = gData.nTrayNo_UnloadPicker[n2No-1]; gAlm.nAlmPNo[0] = gData.InfoUnloadPick[n2No-1][9];
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(m_pEquipData->nTimeOver[0]);
		}
		break;
	case 12:
		if (Check_InspectDone(n2No, gData.nPortNo_UnloadPicker[n2No-1], gData.nTrayNo_UnloadPicker[n2No-1])) {
			if (!m_tUnloadPicker2Loop.Waiting_Time(500)) break;
			m_tUnloadPicker2Loop.Takt_Save(19, 6); m_tUnloadPicker2Loop.Takt_Start(19, 7); 
			Set_ROSTime(n2No, gData.nPortNo_UnloadPicker[n2No-1], gData.nTrayNo_UnloadPicker[n2No-1]);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(300000);	//5분
		}
		break;
	case 13:
		if (Check_ROSDone(n2No, gData.nPortNo_UnloadPicker[n2No-1], gData.nTrayNo_UnloadPicker[n2No-1])) {
			m_tUnloadPicker2Loop.Takt_Save(19, 7); m_tUnloadPicker2Loop.Takt_Start(19, 8); 
			m_nUnloadPicker2Case = 18; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;

	case 14:
		if (!m_pEquipData->bUseMES || gMes.nMarStatus == 2) {	// 0:None, 1:요청, 2:Start수신 Run, 3:End송신
			m_nUnloadPicker2Case = 17; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		} else {
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (gMes.nMarStatus == 3) {
			m_nUnloadPicker2Case = 14; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		} else {
			gMes.nMarStatus = gMes.nMarCount = gMes.nMarTrayCount = gMes.nNGLotCount = gMes.nManualEnd = 0;
			gMes.sHostNGLotID = gMes.sHostNGVendor = gMes.sStartTime = gMes.sEndTime = "";
			
			if (m_pEquipData->bUseMES) g_objMesAgent.Set_NGLotRequest();
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (!m_pEquipData->bUseMES || gMes.nMarStatus == 2) {
			m_sLog.Format("[UnloadPicer2_NGLot-Start] NGLot(%s) NGLot(%d-%d-%d-%d) S1(%d-%d)",
					gMes.sHostNGLotID, gMes.nMarCount, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case);
			g_objLogFile.Save_HandlerLog(m_sLog);

			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (m_nUnloadPicker1Case < 20 || (m_nUnloadPicker1Case > 42 && m_nUnloadPicker1Case < 70)) {
			m_nUnloadPicker2Case = 19; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;

	case 18:
		if (m_nUnloadPicker1Case < 14 || (m_nUnloadPicker1Case > 29 && m_nUnloadPicker1Case < 70)) {
			if (m_nNGStage1Case == 30 || m_nNGStage2Case == 30) {
				m_nUnloadPicker2Case = 14; m_tUnloadPicker2Loop.Set_LoopTime(30000);
			}
		}
		return TRUE;

	case 19:
		int nType;
		n2ModuleNo = Check_NGExist(n2No, nType);
		nJudgeNo2 = nType;
		if (n2ModuleNo > 0) {
			m_nUnloadPicker2Case = 21; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		} else {
			if (gMes.nManualEnd == 1) {	//NGLot수동완공
				g_objMesAgent.Set_NGLotEnd(gMes.sHostNGLotID, gMes.nMarCount);
				m_nUnloadPicker2Case = 18; m_tUnloadPicker2Loop.Set_LoopTime(60000);
				gMes.nManualEnd = 0;

				if (m_nNGStage1Case == 30) { m_nNGStage1Case = 31; gData.nNGLot_NGTray[0] = 1; }
				if (m_nNGStage2Case == 30) { m_nNGStage2Case = 31; gData.nNGLot_NGTray[1] = 1; }

				m_sLog.Format("[UnloadPicker_NGLot-End:21] NGLot(%s) NGLot(%d-%d-%d-%d) S1(%d-%d) S2(%d-%d)",
								gMes.sHostNGLotID, gMes.nMarCount, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case, gData.nNGLot_NGTray[0] , gData.nNGLot_NGTray[1]);
				g_objLogFile.Save_HandlerLog(m_sLog);

				if (!m_pEquipData->bUseMES) {
					gMes.nMarStatus = gMes.nMarCount = gMes.nMarTrayCount = gMes.nNGLotCount = gMes.nManualEnd = 0;
				}
			}
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 20:
		if (m_nUnloadPicker1Case < 20 || (m_nUnloadPicker1Case > 42 && m_nUnloadPicker1Case < 70)) {
			m_nUnloadPicker2Case = 30; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 21:
		if (m_nUnloadPicker1Case < 20 || (m_nUnloadPicker1Case > 42 && m_nUnloadPicker1Case < 70)) {
			n2NSNo = 0;
//			if (m_nNGStage1Case == 30 && !m_pDX11->iNGStage1TrayExist && gData.nPortNo_NGTray[0] < 1) m_nNGStage1Case = 31;
//			if (m_nNGStage2Case == 30 && !m_pDX11->iNGStage2TrayExist && gData.nPortNo_NGTray[1] < 1) m_nNGStage2Case = 31;
			if (m_nNGStage1Case == 30 && gNG->nTrayOX[1][0] == 0) m_nNGStage1Case = 31;
			if (m_nNGStage2Case == 30 && gNG->nTrayOX[1][1] == 0) m_nNGStage2Case = 31;

			if (m_nNGStage1Case == 30) n2NSNo = 5;
			if (m_nNGStage2Case == 30) n2NSNo = 6;
			if (n2NSNo > 0) {
				if (Select_NGTrayPoketNo(nJudgeNo2, n2PosX, n2PosY)) {
					g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y2, n2NSNo);
					m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
				} else {
					if (gMes.nMarTrayCount >= gData.nMgnTrayCount) {
						g_objMesAgent.Set_NGLotEnd(gMes.sHostNGLotID, gMes.nMarCount);
						m_nUnloadPicker2Case = 18; m_tUnloadPicker2Loop.Set_LoopTime(60000);

						if (m_nNGStage1Case == 30) { m_nNGStage1Case = 31; gData.nNGLot_NGTray[0] = 1; }
						if (m_nNGStage2Case == 30) { m_nNGStage2Case = 31; gData.nNGLot_NGTray[1] = 1; }

						m_sLog.Format("[UnloadPicker_NGLot-End:22] NGLot(%s) NGLot(%d-%d-%d-%d) S1(%d-%d) S2(%d-%d)",
										gMes.sHostNGLotID, gMes.nMarCount, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case, gData.nNGLot_NGTray[0] , gData.nNGLot_NGTray[1]);
						g_objLogFile.Save_HandlerLog(m_sLog);

						if (!m_pEquipData->bUseMES) {
							gMes.nMarStatus = gMes.nMarCount = gMes.nMarTrayCount = gMes.nNGLotCount = gMes.nManualEnd = 0;
						}
					} else {
						if (m_nNGStage1Case == 30) { m_nNGStage1Case = 31; gData.nNGLot_NGTray[0] = 0; }
						if (m_nNGStage2Case == 30) { m_nNGStage2Case = 31; gData.nNGLot_NGTray[1] = 0; }
					}
				}
			}
		}
		return TRUE;
	case 22:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, n2NSNo)) {
			if (Get_TrayPosition(n2No, (n2NSNo-4), n2PosX, n2PosY, d2PosX, d2PosY)) {
				g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y2, n2NSNo);
				m_tUnloadPicker2Loop.Takt_Save(19, 8); m_tUnloadPicker2Loop.Takt_Start(19, 9); 
//				d2PosX = d2PosX + (m_pEquipData->dTrayPitchX * (n2ModuleNo - n2PosX));
				d2PosX = d2PosX + (m_pEquipData->dTrayPitchX * (n2ModuleNo - 1));
				g_objAJinAXL.Move_Absolute(AX_UNLOAD_PICKER_X2, d2PosX);
				if (n2NSNo==5) g_objAJinAXL.Move_Absolute(AX_NG_STAGE_Y1, d2PosY);
				if (n2NSNo==6) g_objAJinAXL.Move_Absolute(AX_NG_STAGE_Y2, d2PosY);
				m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);

//				m_sLog.Format("A2 Data [Picker:%d Job:%d Opt:%d] Type(%d) MNo(%d) XY(%d-%d) PosXY(%0.3lf-%0.3lf)", n2No, (n2NSNo-4), m_pEquipData->bUseNGSort, nJudgeNo2, n2ModuleNo, n2PosX, n2PosY, d2PosX, d2PosY);
//				g_objLogFile.Save_HandlerLog(m_sLog);

			}
		}
		break;
	case 23:
		if (g_objAJinAXL.Is_MoveDone(AX_UNLOAD_PICKER_X2, d2PosX)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X2, -1, d2PosX);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 24:
		if ((n2NSNo==5 && g_objAJinAXL.Is_MoveDone(AX_NG_STAGE_Y1, d2PosY)) ||
			(n2NSNo==6 && g_objAJinAXL.Is_MoveDone(AX_NG_STAGE_Y2, d2PosY)) ) {
			if (n2NSNo==5) g_objCommon.Save_Motion(AX_NG_STAGE_Y1, -1, d2PosY);
			if (n2NSNo==6) g_objCommon.Save_Motion(AX_NG_STAGE_Y2, -1, d2PosY);
			m_tUnloadPicker2Loop.Takt_Save(19, 9); m_tUnloadPicker2Loop.Takt_Start(19, 10); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z2, n2NSNo);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 25:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, n2NSNo)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z2, n2NSNo);
			m_tUnloadPicker2Loop.Takt_Save(19, 10); m_tUnloadPicker2Loop.Takt_Start(19, 11); 
			g_objCommon.Set_UnloadPickerDown(n2No, n2ModuleNo);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 26:
		if (g_objCommon.Get_UnloadPickerDown(n2No, n2ModuleNo)) {
			m_tUnloadPicker2Loop.Takt_Save(19, 11); m_tUnloadPicker2Loop.Takt_Start(19, 12); 
			g_objCommon.Set_UnloadPickerOpen(n2No, n2ModuleNo);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 27:
		if (g_objCommon.Get_UnloadPickerOpen(n2No, n2ModuleNo)) {
			if (!m_tUnloadPicker2Loop.Waiting_Time(m_pEquipData->nDelayTime[7])) break;
			m_tUnloadPicker2Loop.Takt_Save(19, 12); m_tUnloadPicker2Loop.Takt_Start(19, 13); 
			g_objCommon.Set_UnloadPickerUp(n2No);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 28:
		if (g_objCommon.Get_UnloadPickerUp(n2No)) {
			m_tUnloadPicker2Loop.Takt_Save(19, 13); m_tUnloadPicker2Loop.Takt_Start(19, 14); 
			gLot.nNgCount[n2UP]++;	gLot.nTrayPutCnt[n2UP][1]++;
			if (Check_EmptyNGTray()) gMes.nMarTrayCount++;
			gLot.nOutTrayCnt[n2UP][1] = gMes.nMarTrayCount; if (gLot.nOutTrayCnt[n2UP][1] == 0) gLot.nOutTrayCnt[n2UP][1] = 1;

			gData.sLotID_NGTray[n2NSNo-5]  = gData.sLotID_UnloadPicker[n2No-1];
			gData.nTrayNo_NGTray[n2NSNo-5] = gData.nTrayNo_UnloadPicker[n2No-1];
			gData.nPortNo_NGTray[n2NSNo-5] = gData.nPortNo_UnloadPicker[n2No-1];
			gData.sLotID_NGTray[2]  = gData.sLotID_NGTray[n2NSNo-5];

			gData.InfoNgTray[n2PosY-1][n2PosX-1] = gData.InfoUnloadPick[n2No-1][n2ModuleNo-1];
			gData.InfoUnloadPick[n2No-1][n2ModuleNo-1] = 0;

			gMes.nNGLotCount++;
			gLot.nHistory[n2UP][n2UT][n2UM+n2ModuleNo-1][6] = gLot.nOutTrayCnt[n2UP][1];
			gLot.nHistory[n2UP][n2UT][n2UM+n2ModuleNo-1][7] = (n2PosY-1) * 4 + n2PosX;
			gLot.nHistory[n2UP][n2UT][n2UM+n2ModuleNo-1][8] = n2NSNo-4;
			g_objLogFile.Save_OutTrayNLog(n2UP+1, n2UT+1, n2UM+n2ModuleNo); 
			g_objMesAgent.Set_CmEnd(1, n2UP+1, n2UT+1, n2UM+n2ModuleNo, (n2PosY-1) * 4 + n2PosX);
			
			m_nUnloadPicker2Case = 19; m_tUnloadPicker2Loop.Set_LoopTime(30000);

			m_sLog.Format("[UnloadPicker_NGLot-NGDown:%d Job:%d Option:%d] P(%d-1) Type(%d) => (%d,%d-%0.3lf,%0.3lf) NGLot(%d-%d-%d-%d) S1(%d-%d) S2(%d-%d)",
				n2No, (n2NSNo-4), m_pEquipData->bUseAlign2, n2ModuleNo, gData.InfoNgTray[n2PosY-1][n2PosX-1], n2PosX, n2PosY, d2PosX, d2PosY, m_nUnloadPicker2Case, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus, m_nNGStage1Case, m_nNGStage2Case, gData.nNGLot_NGTray[0] , gData.nNGLot_NGTray[1]);
			g_objLogFile.Save_HandlerLog(m_sLog);

			if (gData.InfoNgTray[n2PosY-1][n2PosX-1] == 12) {
				gData.nNoReadNo = (n2PosY-1)*4 + n2PosX;
				gMes.nNoReadCount++;

				m_sLog.Format("[NG-Tray Barcode No Read => TrayNo:%d Position:%d Total-Count:%d", gMes.nMarTrayCount, gData.nNoReadNo, gMes.nNoReadCount);
				g_objLogFile.Save_HandlerLog(m_sLog);
				g_objCommon.Show_Error(7599);
			return FALSE;
			}
		}
		break;

	/*case 29:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, 0)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y2, 0);
			m_nUnloadPicker2Case = 40; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;*/
	case 30:
		n2ModuleNo = Check_GoodExist(n2No, n2PosX, n2PosY);
		if (n2ModuleNo > 0) {
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		else
		{
//			if (Check_LotEndUnloadNG(gData.sLotID_UnloadPicker[n2No-1], gData.nPortNo_UnloadPicker[n2No-1], n2No)) {
//				if (m_nNGStage1Case == 30)   m_nNGStage1Case = 31;
//				if (m_nNGStage2Case == 30)   m_nNGStage2Case = 31;
//			}

			if (Check_GooodTrayFull()) {
				if (m_nGoodStage1Case == 30) m_nGoodStage1Case = 31;
				if (m_nGoodStage2Case == 30) m_nGoodStage2Case = 31;
			}
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y2, 0);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z2, 0);
			

			CString sLotID  = gData.sLotID_UnloadPicker[n2No-1];
			int		nPortNo = gData.nPortNo_UnloadPicker[n2No-1];
			gData.sLotID_UnloadPicker[n2No-1] = "";
			gData.nTrayNo_UnloadPicker[n2No-1] = gData.nPortNo_UnloadPicker[n2No-1] = 0;
			for(int i=0; i<10; i++) gData.InfoUnloadPick[n2No-1][i] = 0;

			if (Check_LotEndUnloadPicker(sLotID, nPortNo)) {
				if (m_nGoodStage1Case == 30) m_nGoodStage1Case = 31;
				if (m_nGoodStage2Case == 30) m_nGoodStage2Case = 31;
			}
			m_nUnloadPicker2Case = 41; m_tUnloadPicker2Loop.Set_LoopTime(15000);

		}
		break;
	case 31:
		if (m_nUnloadPicker1Case < 30 || (m_nUnloadPicker1Case > 42 && m_nUnloadPicker1Case < 70)) {
			if (g_objAJinAXL.Is_Done(AX_UNLOAD_PICKER_X2)) {
				n2NSNo = 0;
//				if (m_nGoodStage1Case == 30 && !m_pDX12->iGoodStage1TrayExist && gData.nTrayNo_GoodTray[0] < 1) m_nGoodStage1Case = 31;
//				if (m_nGoodStage2Case == 30 && !m_pDX12->iGoodStage2TrayExist && gData.nTrayNo_GoodTray[1] < 1) m_nGoodStage2Case = 31;
				if (m_nGoodStage1Case == 30 && gNG->nTrayOX[2][0] == 0) m_nGoodStage1Case = 31;
				if (m_nGoodStage2Case == 30 && gNG->nTrayOX[2][1] == 0) m_nGoodStage2Case = 31;
				if (m_nGoodStage1Case == 30) n2NSNo = 7;
				if (m_nGoodStage2Case == 30) n2NSNo = 8;
				if (n2NSNo > 0) {
					if (Select_GoodTrayPoketNo(n2UP, n2UT, n2PosX, n2PosY)) {
						g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y2, n2NSNo);
						g_objCommon.Move_Position(AX_UNLOAD_PICKER_P2, 2);
						m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
					} else {
						if (m_nGoodStage1Case == 30) m_nGoodStage1Case = 31;
						if (m_nGoodStage2Case == 30) m_nGoodStage2Case = 31;
					}
				} else {
					if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_X2, 7)) g_objCommon.Move_Position(AX_UNLOAD_PICKER_X2, 7);
				}
			}
		}
		return TRUE;
	case 32:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, n2NSNo) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_P2, 2)) {
			if (Get_TrayPosition(n2No, (n2NSNo-4), n2PosX, n2PosY, d2PosX, d2PosY)) {
				g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y2, n2NSNo);
				m_tUnloadPicker2Loop.Takt_Save(19, 14); m_tUnloadPicker2Loop.Takt_Start(19, 15); 
//				d2PosX = d2PosX + (m_pEquipData->dTrayPitchX * (n2ModuleNo - n2PosX));
				d2PosX = d2PosX + (m_pEquipData->dTrayPitchX * (n2ModuleNo - 1));
				g_objAJinAXL.Move_Absolute(AX_UNLOAD_PICKER_X2, d2PosX);
				if (n2NSNo==7) g_objAJinAXL.Move_Absolute(AX_GOOD_STAGE_Y1, d2PosY);
				if (n2NSNo==8) g_objAJinAXL.Move_Absolute(AX_GOOD_STAGE_Y2, d2PosY);
				m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);

				m_sLog.Format("A2 Data [Picker:%d Job:%d] PosX(%0.3lf) (%d,%d)", n2No, (n2NSNo-4), d2PosX, n2ModuleNo, n2PosX);
				g_objLogFile.Save_HandlerLog(m_sLog);
			}
		}
		break;
	case 33:
		if (g_objAJinAXL.Is_MoveDone(AX_UNLOAD_PICKER_X2, d2PosX)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X2, -1, d2PosX);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 34:
		if ((n2NSNo==7 && g_objAJinAXL.Is_MoveDone(AX_GOOD_STAGE_Y1, d2PosY)) ||
			(n2NSNo==8 && g_objAJinAXL.Is_MoveDone(AX_GOOD_STAGE_Y2, d2PosY)) ) {
			if (n2NSNo==7) g_objCommon.Save_Motion(AX_GOOD_STAGE_Y1, -1, d2PosY);
			if (n2NSNo==8) g_objCommon.Save_Motion(AX_GOOD_STAGE_Y2, -1, d2PosY);
			m_tUnloadPicker2Loop.Takt_Save(19, 15); m_tUnloadPicker2Loop.Takt_Start(19, 16); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z2, n2NSNo);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 35:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, n2NSNo)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z2, n2NSNo);
			m_tUnloadPicker2Loop.Takt_Save(19, 16); m_tUnloadPicker2Loop.Takt_Start(19, 17); 
			g_objCommon.Set_UnloadPickerDown(n2No, 9, n2ModuleNo, n2PosX, gData.InfoUnloadPick[n2No-1]);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 36:
		if (g_objCommon.Get_UnloadPickerDown(n2No, 9, n2ModuleNo, n2PosX, gData.InfoUnloadPick[n2No-1])) {
			m_tUnloadPicker2Loop.Takt_Save(19, 17); m_tUnloadPicker2Loop.Takt_Start(19, 18); 
			g_objCommon.Set_UnloadPickerOpen(n2No, 9, n2ModuleNo, n2PosX, gData.InfoUnloadPick[n2No-1]);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 37:
		if (g_objCommon.Get_UnloadPickerOpen(n2No, 9, n2ModuleNo, n2PosX, gData.InfoUnloadPick[n2No-1])) {
			if (!m_tUnloadPicker2Loop.Waiting_Time(m_pEquipData->nDelayTime[7])) break;
			m_tUnloadPicker2Loop.Takt_Save(19, 18); m_tUnloadPicker2Loop.Takt_Start(19, 19); 
			g_objCommon.Set_UnloadPickerUp(n2No);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 38:
		if (g_objCommon.Get_UnloadPickerUp(n2No)) {
			m_tUnloadPicker2Loop.Takt_Save(19, 19); m_tUnloadPicker2Loop.Takt_Start(19, 20); 
			if (Check_EmptyGoodTray()) {
				if (m_pEquipData->bUseGoodSort) gLot.nOutTrayCnt[n2UP][0] = n2UT+1;
				else							gLot.nOutTrayCnt[n2UP][0]++;
			}

			gData.sLotID_GoodTray[n2NSNo-7]  = gData.sLotID_UnloadPicker[n2No-1];
			gData.nTrayNo_GoodTray[n2NSNo-7] = gData.nTrayNo_UnloadPicker[n2No-1];
			gData.nPortNo_GoodTray[n2NSNo-7] = gData.nPortNo_UnloadPicker[n2No-1];
			gData.sLotID_GoodTray[2]  = gData.sLotID_GoodTray[n2NSNo-7];

			for(int i=0; i<gData.nUnloadPick2DownCnt; i++) {
				gLot.nGoodCount[n2UP]++;	gLot.nTrayPutCnt[n2UP][0]++;
				gData.InfoGoodTray[n2PosY-1][n2PosX-1+i] = gData.InfoUnloadPick[n2No-1][n2ModuleNo-1+i];
				gData.InfoUnloadPick[n2No-1][n2ModuleNo-1+i] = 0;

				gLot.nHistory[n2UP][n2UT][n2UM+n2ModuleNo-1+i][5] = gLot.nOutTrayCnt[n2UP][0];
				gLot.nHistory[n2UP][n2UT][n2UM+n2ModuleNo-1+i][7] = (n2PosY-1) * 4 + n2PosX + i;
				gLot.nHistory[n2UP][n2UT][n2UM+n2ModuleNo-1+i][8] = n2NSNo-6;
				g_objLogFile.Save_OutTrayGLog(n2UP+1, n2UT+1, n2UM+n2ModuleNo+i);
				g_objMesAgent.Set_CmEnd(0, n2UP+1, n2UT+1, n2UM+n2ModuleNo+i, (n2PosY-1) * 4 + n2PosX + i);
			}

			m_sLog.Format("[UnloadPicker:%d Job:%d Option:%d] P(%d-%d) => (%d,%d-%0.3lf,%0.3lf)", n2No, (n2NSNo-4), m_pEquipData->bUseAlign2, n2ModuleNo, gData.nUnloadPick2DownCnt, n2PosX, n2PosY, d2PosX, d2PosY);
			g_objLogFile.Save_HandlerLog(m_sLog);

			m_nUnloadPicker2Case = 30; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;

	case 40:
		if (g_objCommon.Get_UnloadPickerUp(n2No)) {
			
		}
		break;
	case 41:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, 0) ) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Z2, 0);
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y2, 0);
			m_tUnloadPicker2Loop.Takt_Save(19, 20); m_tUnloadPicker2Loop.Takt_Start(19, 21); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_X2, 1);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_P2, 0);
			m_nUnloadPicker2Case = 43; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;

	case 43:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_X2, 1) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_P2, 0)) 
		{
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_X2, 1);
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_P2, 0);
			m_tUnloadPicker2Loop.Takt_Save(19, 22); m_tUnloadPicker2Loop.Takt_Start(19, 23); 
			m_nUnloadPicker2Case = 50; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;

	case 50:
		if (m_nUnloadPicker1Case > 11 && m_nUnloadPicker1Case < 50) {
			m_tUnloadPicker2Loop.Takt_Save(19, 23); m_tUnloadPicker2Loop.Takt_Start(19, 24); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y2, 1);
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 51:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, 1)) {
			g_objCommon.Save_Motion(AX_UNLOAD_PICKER_Y2, 1);
			m_tUnloadPicker2Loop.Takt_Save(19, 24, TRUE);
			m_nUnloadPicker2Case = 0; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;

	case 81:
		if (g_objCommon.Get_UnloadPickerUp(n2No)) {
			if (g_objCommon.Get_UnloadPickerCheck(n2No, 9, gData.InfoUnloadPick[n2No-1])) {
				m_nUnloadPicker2Case = 7; m_tUnloadPicker2Loop.Set_LoopTime(30000);
			} else {
				for(int i=0; i<8; i++) {
					if (gData.nUnloadPicker2ErrNo[i] == 1) {
						g_objCommon.Set_UnloadPickerOpen(n2No, i+1);
					}
				}
				m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
			}
		}
		break;
	case 82:
		if (g_objCommon.Get_UnloadPickerUp(n2No)) {
			if (!m_tUnloadPicker2Loop.Waiting_Time(500)) break;
			for(int i=0; i<8; i++) {
				if (gData.nUnloadPicker2ErrNo[i] == 1) {
					g_objCommon.Set_UnloadPickerDown(n2No, i+1);
				}
			}
			m_nUnloadPicker2Case++; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;
	case 83:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0)) {
			if (!m_tUnloadPicker2Loop.Waiting_Time(500)) break;
			m_tUnloadPicker2Loop.Takt_Save(19, 1); m_tUnloadPicker2Loop.Takt_Start(19, 2); 
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z2, n2VNo);
			m_nUnloadPicker2Case = 4; m_tUnloadPicker2Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 19. (Error : 7500)
	if (m_tUnloadPicker2Loop.Over_LoopTime()) {
		if (m_nUnloadPicker2Case == 12 && m_pEquipData->bUseAutoSkip) {
			Set_ReInspectDone(2, gData.nPortNo_UnloadPicker[1], gData.nTrayNo_UnloadPicker[1]);
			m_tUnloadPicker2Loop.Set_LoopTime(30000);
			return TRUE;
		}
		g_objCommon.Show_Error(7500 + m_nUnloadPicker2Case);
		return FALSE;
	}
	return TRUE;
}

// 20. (Error : 8000)
BOOL CSequenceMain::Run_NGStage1()
{
	static int	  nNStage1No      = 0;	//0고정
	static int	  nNStage1YAxisNo = AX_NG_STAGE_Y1;

	switch (m_nNGStage1Case) {
	case 0:	// Wait
		m_tNGStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (m_pDX11->iNGStage1TrayExist) {
			gNG->nTrayOX[1][0] = 1;
			m_tNGStage1Loop.Takt_Start(20, 1, TRUE); 
			m_pDY11->oNGStage1MasterIn = TRUE; m_pDY11->oNGStage1MasterOut = FALSE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 2:
		if (m_pDX11->iNGStage1MasterIn && !m_pDX11->iNGStage1MasterOut) {
			m_tNGStage1Loop.Takt_Save(20, 1); m_tNGStage1Loop.Takt_Start(20, 2); 
			m_pDY11->oNGStage1SlaveIn = TRUE; m_pDY11->oNGStage1SlaveOut = FALSE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if (m_pDX11->iNGStage1SlaveIn && !m_pDX11->iNGStage1SlaveOut) {
			m_tNGStage1Loop.Takt_Save(20, 2); m_tNGStage1Loop.Takt_Start(20, 3); 
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if (m_pDX11->iNGStage1Up && !m_pDX11->iNGStage1Down) {
			m_nNGStage1Case = 10; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 10:	//Align Wait
		if (m_nNGStage2Case > 22) {
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 11:
		if (m_pDX11->iNGStage1Up && !m_pDX11->iNGStage1Down) {
			m_tNGStage1Loop.Takt_Save(20, 3); m_tNGStage1Loop.Takt_Start(20, 4); 
			g_objCommon.Move_Position(nNStage1YAxisNo, 1);	//Aling1
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (g_objCommon.Check_Position(nNStage1YAxisNo, 1)) {
			g_objCommon.Save_Motion(nNStage1YAxisNo, 1);
			m_tNGStage1Loop.Takt_Save(20, 4); m_tNGStage1Loop.Takt_Start(20, 5); 
			m_nNGStage1Case = 20; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 20:	//Align Wait
		return TRUE;
	case 21:
		if (m_nNGStage2Case > 20 && m_nNGStage2Case < 40) {
			m_tNGStage1Loop.Takt_Save(20, 5); m_tNGStage1Loop.Takt_Start(20, 6); 
			g_objCommon.Move_Position(nNStage1YAxisNo, 2);	//Wait
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		} else if (m_nNGStage2Case <= 20 || m_nNGStage2Case >= 40) {
			m_tNGStage1Loop.Takt_Save(20, 5); m_tNGStage1Loop.Takt_Start(20, 6); 
			g_objCommon.Move_Position(nNStage1YAxisNo, 3);	//Work
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 22:
		if (g_objCommon.Check_Position(nNStage1YAxisNo, 2) || g_objCommon.Check_Position(nNStage1YAxisNo, 3)) {
			if (g_objCommon.Check_Position(nNStage1YAxisNo, 2)) g_objCommon.Save_Motion(nNStage1YAxisNo, 2);
			m_tNGStage1Loop.Takt_Save(20, 6); m_tNGStage1Loop.Takt_Start(20, 7); 
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 23:
		if (m_nNGStage2Case <= 20 || m_nNGStage2Case >= 40) {
			g_objCommon.Move_Position(nNStage1YAxisNo, 3);	//Work
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 24:
		if (g_objCommon.Check_Position(nNStage1YAxisNo, 3)) {
			g_objCommon.Save_Motion(nNStage1YAxisNo, 3);
			m_tNGStage1Loop.Takt_Save(20, 7); m_tNGStage1Loop.Takt_Start(20, 8); 
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 25:
		if (gNG->nTrayOX[1][0] == 0 || (gNG->nTrayOX[1][0] == 1 && m_pDX11->iNGStage1TrayExist)) {
			Init_NgTray(nNStage1No);
			gData.nNGLot_NGTray[0] = 0;
			m_nNGStage1Case = 30; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	// Unload Picker Wait
		m_tNGStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 31:
		if (m_nNGStage2Case < 30 || m_nNGStage2Case >= 50) {
			m_tNGStage1Loop.Takt_Save(20, 8); m_tNGStage1Loop.Takt_Start(20, 9); 
			m_pDY11->oNGStage1Up = FALSE; m_pDY11->oNGStage1Down = TRUE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(10000);

			int nNGCount = Get_NGCmCount(1);
			m_sLog.Format("[NGStage_Change:1 NGLot(%s) TrayCout(%d) CmCount(%d/%d)", gMes.sHostNGLotID, gMes.nMarTrayCount, nNGCount, gMes.nNGLotCount);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		return TRUE;
	case 32:
		if (!m_pDX11->iNGStage1Up && m_pDX11->iNGStage1Down) {
			m_tNGStage1Loop.Takt_Save(20, 9); m_tNGStage1Loop.Takt_Start(20, 10); 
			m_nNGStage1Case = 40; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		break;

	case 40:	//Up Wait
		if (m_nNGStage2Case < 40 || m_nNGStage2Case >= 60) {
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 41:
		if (!m_pDX11->iNGStage1Up && m_pDX11->iNGStage1Down) {
			m_tNGStage1Loop.Takt_Save(20, 10); m_tNGStage1Loop.Takt_Start(20, 11); 
			g_objCommon.Move_Position(nNStage1YAxisNo, 0);	//load
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(nNStage1YAxisNo, 0)) {
			g_objCommon.Save_Motion(nNStage1YAxisNo, 0);
			m_tNGStage1Loop.Takt_Save(20, 11); m_tNGStage1Loop.Takt_Start(20, 12); 
			m_nNGStage1Case = 50; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 50:
		if (m_nNGStage2Case > 22 && m_nNGStage2Case < 50) {
			m_tNGStage1Loop.Takt_Save(20, 12); m_tNGStage1Loop.Takt_Start(20, 13); 
			m_pDY11->oNGStage1Up = TRUE; m_pDY11->oNGStage1Down = FALSE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 51:
		if (m_pDX11->iNGStage1Up && !m_pDX11->iNGStage1Down) {
			m_tNGStage1Loop.Takt_Save(20, 13); m_tNGStage1Loop.Takt_Start(20, 14); 
			m_pDY11->oNGStage1SlaveIn = FALSE; m_pDY11->oNGStage1SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 52:
		if (!m_pDX11->iNGStage1SlaveIn && m_pDX11->iNGStage1SlaveOut) {
			m_tNGStage1Loop.Takt_Save(20, 14); m_tNGStage1Loop.Takt_Start(20, 15); 
			m_pDY11->oNGStage1MasterIn = FALSE; m_pDY11->oNGStage1MasterOut = TRUE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 53:
		if (!m_pDX11->iNGStage1MasterIn && m_pDX11->iNGStage1MasterOut) {
			m_tNGStage1Loop.Takt_Save(20, 15); m_tNGStage1Loop.Takt_Start(20, 16); 
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 54:
		if (gNG->nTrayOX[1][0] == 1) {
			m_nNGStage1Case++; m_tNGStage1Loop.Set_LoopTime(30000);
		} else {
			m_tNGStage1Loop.Takt_Save(20, 16, TRUE);
			m_nNGStage1Case = 0; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 55:
		if (m_pDX11->iNGStage1TrayExist) {
			if (gData.nPortNo_NGTray[0] > 0) m_nNGStage1Case = 60;
			else							 m_nNGStage1Case = 0;
			m_tNGStage1Loop.Set_LoopTime(30000);
		}
		break;

	case 60:	// Transfer Picker Wait
		m_tNGStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 61:
		if (!m_pDX11->iNGStage1TrayExist) {
			gNG->nTrayOX[1][0] = 0;
			m_tNGStage1Loop.Takt_Save(20, 16, TRUE);
			m_nNGStage1Case = 0; m_tNGStage1Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 20. (Error : 8000)
	if (m_tNGStage1Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(8000 + m_nNGStage1Case);
		return FALSE;
	}
	return TRUE;
}

// 21. (Error : 8200)
BOOL CSequenceMain::Run_NGStage2()
{
	static int	  nNStage2No	  = 1;	//1고정
	static int	  nNStage2YAxisNo = AX_NG_STAGE_Y2;

	switch (m_nNGStage2Case) {
	case 0:	// Wait
		m_tNGStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (m_pDX11->iNGStage2TrayExist) {
			gNG->nTrayOX[1][1] = 1;
			m_tNGStage2Loop.Takt_Start(21, 1, TRUE); 
			m_pDY11->oNGStage2MasterIn = TRUE; m_pDY11->oNGStage2MasterOut = FALSE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 2:
		if (m_pDX11->iNGStage2MasterIn && !m_pDX11->iNGStage2MasterOut) {
			m_tNGStage2Loop.Takt_Save(21, 1); m_tNGStage2Loop.Takt_Start(21, 2); 
			m_pDY11->oNGStage2SlaveIn = TRUE; m_pDY11->oNGStage2SlaveOut = FALSE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if (m_pDX11->iNGStage2SlaveIn && !m_pDX11->iNGStage2SlaveOut) {
			m_tNGStage2Loop.Takt_Save(21, 2); m_tNGStage2Loop.Takt_Start(21, 3); 
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if (m_pDX11->iNGStage2Up && !m_pDX11->iNGStage2Down) {
			m_nNGStage2Case = 10; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 10:	//Align Wait
		if (m_nNGStage1Case > 22) {
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 11:
		if (m_pDX11->iNGStage2Up && !m_pDX11->iNGStage2Down) {
			m_tNGStage2Loop.Takt_Save(21, 3); m_tNGStage2Loop.Takt_Start(21, 4); 
			g_objCommon.Move_Position(nNStage2YAxisNo, 1);	//Aling1
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (g_objCommon.Check_Position(nNStage2YAxisNo, 1)) {
			g_objCommon.Save_Motion(nNStage2YAxisNo, 1);
			m_tNGStage2Loop.Takt_Save(21, 4); m_tNGStage2Loop.Takt_Start(21, 5); 
			m_nNGStage2Case = 20; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 20:	//Align Wait
		return TRUE;
	case 21:
		if (m_nNGStage1Case > 20 && m_nNGStage1Case < 40) {
			m_tNGStage2Loop.Takt_Save(21, 5); m_tNGStage2Loop.Takt_Start(21, 6); 
			g_objCommon.Move_Position(nNStage2YAxisNo, 2);	//Wait
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		} else if (m_nNGStage1Case <= 20 || m_nNGStage1Case >= 40) {
			m_tNGStage2Loop.Takt_Save(21, 5); m_tNGStage2Loop.Takt_Start(21, 6); 
			g_objCommon.Move_Position(nNStage2YAxisNo, 3);	//Work
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 22:
		if (g_objCommon.Check_Position(nNStage2YAxisNo, 2) || g_objCommon.Check_Position(nNStage2YAxisNo, 3)) {
			if (g_objCommon.Check_Position(nNStage2YAxisNo, 2)) g_objCommon.Save_Motion(nNStage2YAxisNo, 2);
			m_tNGStage2Loop.Takt_Save(21, 6); m_tNGStage2Loop.Takt_Start(21, 7); 
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 23:
		if (m_nNGStage1Case <= 20 || m_nNGStage1Case >= 40) {
			g_objCommon.Move_Position(nNStage2YAxisNo, 3);	//Work
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 24:
		if (g_objCommon.Check_Position(nNStage2YAxisNo, 3)) {
			g_objCommon.Save_Motion(nNStage2YAxisNo, 3);
			m_tNGStage2Loop.Takt_Save(21, 7); m_tNGStage2Loop.Takt_Start(21, 8); 
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 25:
		if (gNG->nTrayOX[1][1] == 0 || (gNG->nTrayOX[1][1] == 1 && m_pDX11->iNGStage2TrayExist)) {
			Init_NgTray(nNStage2No);
			gData.nNGLot_NGTray[1] = 0;
			m_nNGStage2Case = 30; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	// Unload Picker Wait
		m_tNGStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 31:
		if (m_nNGStage1Case < 30 || m_nNGStage1Case >= 50) {
			m_tNGStage2Loop.Takt_Save(21, 8); m_tNGStage2Loop.Takt_Start(21, 9); 
			m_pDY11->oNGStage2Up = FALSE; m_pDY11->oNGStage2Down = TRUE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(10000);

			int nNGCount = Get_NGCmCount(2);
			m_sLog.Format("[NGStage_Change:2 NGLot(%s) TrayCout(%d) CmCount(%d/%d)", gMes.sHostNGLotID, gMes.nMarTrayCount, nNGCount, gMes.nNGLotCount);
			g_objLogFile.Save_HandlerLog(m_sLog);
		}
		return TRUE;
	case 32:
		if (!m_pDX11->iNGStage2Up && m_pDX11->iNGStage2Down) {
			m_tNGStage2Loop.Takt_Save(21, 9); m_tNGStage2Loop.Takt_Start(21, 10); 
			m_nNGStage2Case = 40; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		break;

	case 40:	//Up Wait
		if (m_nNGStage1Case < 40 || m_nNGStage1Case >= 60) {
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 41:
		if (!m_pDX11->iNGStage2Up && m_pDX11->iNGStage2Down) {
			m_tNGStage2Loop.Takt_Save(21, 10); m_tNGStage2Loop.Takt_Start(21, 11); 
			g_objCommon.Move_Position(nNStage2YAxisNo, 0);	//load
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(nNStage2YAxisNo, 0)) {
			g_objCommon.Save_Motion(nNStage2YAxisNo, 0);
			m_tNGStage2Loop.Takt_Save(21, 11); m_tNGStage2Loop.Takt_Start(21, 12); 
			m_nNGStage2Case = 50; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 50:
		if (m_nNGStage1Case > 22 && m_nNGStage1Case < 50) {
			m_tNGStage2Loop.Takt_Save(21, 12); m_tNGStage2Loop.Takt_Start(21, 13); 
			m_pDY11->oNGStage2Up = TRUE; m_pDY11->oNGStage2Down = FALSE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 51:
		if (m_pDX11->iNGStage2Up && !m_pDX11->iNGStage2Down) {
			m_tNGStage2Loop.Takt_Save(21, 13); m_tNGStage2Loop.Takt_Start(21, 14); 
			m_pDY11->oNGStage2SlaveIn = FALSE; m_pDY11->oNGStage2SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 52:
		if (!m_pDX11->iNGStage2SlaveIn && m_pDX11->iNGStage2SlaveOut) {
			m_tNGStage2Loop.Takt_Save(21, 14); m_tNGStage2Loop.Takt_Start(21, 15); 
			m_pDY11->oNGStage2MasterIn = FALSE; m_pDY11->oNGStage2MasterOut = TRUE;
			g_objAJinAXL.Write_Output(11);
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 53:
		if (!m_pDX11->iNGStage2MasterIn && m_pDX11->iNGStage2MasterOut) {
			m_tNGStage2Loop.Takt_Save(21, 15); m_tNGStage2Loop.Takt_Start(21, 16); 
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 54:
		if (gNG->nTrayOX[1][1] == 1) {
			m_nNGStage2Case++; m_tNGStage2Loop.Set_LoopTime(30000);
		} else {
			m_tNGStage2Loop.Takt_Save(21, 16, TRUE);
			m_nNGStage2Case = 0; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 55:
		if (m_pDX11->iNGStage2TrayExist) {
			if (gData.nPortNo_NGTray[1] > 0) m_nNGStage2Case = 60;
			else							 m_nNGStage2Case = 0;
			m_tNGStage2Loop.Set_LoopTime(30000);
		}
		break;

	case 60:	// Transfer Picker Wait
		m_tNGStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 61:
		if (!m_pDX11->iNGStage2TrayExist) {
			gNG->nTrayOX[1][1] = 0;
			m_tNGStage2Loop.Takt_Save(21, 16, TRUE);
			m_nNGStage2Case = 0; m_tNGStage2Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 21. (Error : 8200)
	if (m_tNGStage2Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(8200 + m_nNGStage2Case);
		return FALSE;
	}
	return TRUE;
}

// 22. (Error : 8400)
BOOL CSequenceMain::Run_GoodStage1()
{
	static int	  nGStage1No		= 0;	//0고정
	static int	  nGStage1YAxisNo = AX_GOOD_STAGE_Y1;

	switch (m_nGoodStage1Case) {
	case 0:	// Wait
		m_tGoodStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (m_pDX12->iGoodStage1TrayExist) {
			gNG->nTrayOX[2][0] = 1;
			m_tGoodStage1Loop.Takt_Start(22, 1, TRUE);
			m_pDY12->oGoodStage1MasterIn = TRUE; m_pDY12->oGoodStage1MasterOut = FALSE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 2:
		if (m_pDX12->iGoodStage1MasterIn && !m_pDX12->iGoodStage1MasterOut) {
			m_tGoodStage1Loop.Takt_Save(22, 1); m_tGoodStage1Loop.Takt_Start(22, 2); 
			m_pDY12->oGoodStage1SlaveIn = TRUE; m_pDY12->oGoodStage1SlaveOut = FALSE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if (m_pDX12->iGoodStage1SlaveIn && !m_pDX12->iGoodStage1SlaveOut) {
			m_tGoodStage1Loop.Takt_Save(22, 2); m_tGoodStage1Loop.Takt_Start(22, 3); 
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if (m_pDX12->iGoodStage1Up && !m_pDX12->iGoodStage1Down) {
			m_nGoodStage1Case = 10; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 10:	//Align Wait
		if (m_nGoodStage2Case > 22) {
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 11:
		if (m_pDX12->iGoodStage1Up && !m_pDX12->iGoodStage1Down) {
			m_tGoodStage1Loop.Takt_Save(22, 3); m_tGoodStage1Loop.Takt_Start(22, 4); 
			g_objCommon.Move_Position(nGStage1YAxisNo, 1);	//Aling1
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (g_objCommon.Check_Position(nGStage1YAxisNo, 1)) {
			g_objCommon.Save_Motion(nGStage1YAxisNo, 1);
			m_tGoodStage1Loop.Takt_Save(22, 4); m_tGoodStage1Loop.Takt_Start(22, 5); 
			m_nGoodStage1Case = 20; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 20:	//Align Wait
		return TRUE;
	case 21:
		if (m_nGoodStage2Case > 20 && m_nGoodStage2Case < 40) {
			m_tGoodStage1Loop.Takt_Save(22, 5); m_tGoodStage1Loop.Takt_Start(22, 6); 
			g_objCommon.Move_Position(nGStage1YAxisNo, 2);	//Wait
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(30000);
		} else if (m_nGoodStage2Case <= 20 || m_nGoodStage2Case >= 40) {
			m_tGoodStage1Loop.Takt_Save(22, 5); m_tGoodStage1Loop.Takt_Start(22, 6); 
			g_objCommon.Move_Position(nGStage1YAxisNo, 3);	//Work
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 22:
		if (g_objCommon.Check_Position(nGStage1YAxisNo, 2) || g_objCommon.Check_Position(nGStage1YAxisNo, 3)) {
			if (g_objCommon.Check_Position(nGStage1YAxisNo, 2)) g_objCommon.Save_Motion(nGStage1YAxisNo, 2);
			m_tGoodStage1Loop.Takt_Save(22, 6); m_tGoodStage1Loop.Takt_Start(22, 7); 
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 23:
		if (m_nGoodStage2Case <= 20 || m_nGoodStage2Case >= 40) {
			g_objCommon.Move_Position(nGStage1YAxisNo, 3);	//Work
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 24:
		if (g_objCommon.Check_Position(nGStage1YAxisNo, 3)) {
			g_objCommon.Save_Motion(nGStage1YAxisNo, 3);
			m_tGoodStage1Loop.Takt_Save(22, 7); m_tGoodStage1Loop.Takt_Start(22, 8); 
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 25:
		if (gNG->nTrayOX[2][0] == 0 || (gNG->nTrayOX[2][0] == 1 && m_pDX12->iGoodStage1TrayExist)) {
			Init_GoodTray(nGStage1No);
			m_nGoodStage1Case = 30; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	// Unload Picker Wait
		m_tGoodStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 31:
		if (m_nGoodStage2Case < 30 || m_nGoodStage2Case >= 50) {
			m_tGoodStage1Loop.Takt_Save(22, 8); m_tGoodStage1Loop.Takt_Start(22, 9); 
			m_pDY12->oGoodStage1Up = FALSE; m_pDY12->oGoodStage1Down = TRUE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(10000);
		}
		return TRUE;
	case 32:
		if (!m_pDX12->iGoodStage1Up && m_pDX12->iGoodStage1Down) {
			m_tGoodStage1Loop.Takt_Save(22, 9); m_tGoodStage1Loop.Takt_Start(22, 10); 
			m_nGoodStage1Case = 40; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		break;

	case 40:	//Up Wait
		if (m_nGoodStage2Case < 40 || m_nGoodStage2Case >= 60) {
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 41:
		if (!m_pDX12->iGoodStage1Up && m_pDX12->iGoodStage1Down) {
			m_tGoodStage1Loop.Takt_Save(22, 10); m_tGoodStage1Loop.Takt_Start(22, 11); 
			g_objCommon.Move_Position(nGStage1YAxisNo, 0);	//load
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(nGStage1YAxisNo, 0)) {
			g_objCommon.Save_Motion(nGStage1YAxisNo, 0);
			m_tGoodStage1Loop.Takt_Save(22, 11); m_tGoodStage1Loop.Takt_Start(22, 12); 
			m_nGoodStage1Case = 50; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;

	case 50:
		if (m_nGoodStage2Case > 22 && m_nGoodStage2Case < 50) {
			m_tGoodStage1Loop.Takt_Save(22, 12); m_tGoodStage1Loop.Takt_Start(22, 13); 
			m_pDY12->oGoodStage1Up = TRUE; m_pDY12->oGoodStage1Down = FALSE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 51:
		if (m_pDX12->iGoodStage1Up && !m_pDX12->iGoodStage1Down) {
			m_tGoodStage1Loop.Takt_Save(22, 13); m_tGoodStage1Loop.Takt_Start(22, 14); 
			m_pDY12->oGoodStage1SlaveIn = FALSE; m_pDY12->oGoodStage1SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 52:
		if (!m_pDX12->iGoodStage1SlaveIn && m_pDX12->iGoodStage1SlaveOut) {
			m_tGoodStage1Loop.Takt_Save(22, 14); m_tGoodStage1Loop.Takt_Start(22, 15); 
			m_pDY12->oGoodStage1MasterIn = FALSE; m_pDY12->oGoodStage1MasterOut = TRUE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 53:
		if (!m_pDX12->iGoodStage1MasterIn && m_pDX12->iGoodStage1MasterOut) {
			m_tGoodStage1Loop.Takt_Save(22, 15); m_tGoodStage1Loop.Takt_Start(22, 16); 
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(5000);
		}
		break;
	case 54:
		if (gNG->nTrayOX[2][0] == 1) {
			m_nGoodStage1Case++; m_tGoodStage1Loop.Set_LoopTime(30000);
		} else {
			m_tGoodStage1Loop.Takt_Save(22, 16, TRUE);
			m_nGoodStage1Case = 0; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		break;
	case 55:
		if (m_pDX12->iGoodStage1TrayExist) {
			if (gData.nPortNo_GoodTray[0] > 0) m_nGoodStage1Case = 60;
			else							   m_nGoodStage1Case = 0;
			m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		break;

	case 60:	// Transfer Picker Wait
		m_tGoodStage1Loop.Set_LoopTime(5000);
		return TRUE;

	case 61:
		if (!m_pDX12->iGoodStage1TrayExist) {
			gNG->nTrayOX[2][0] = 0;
			m_tGoodStage1Loop.Takt_Save(22, 16, TRUE);
			m_nGoodStage1Case = 0; m_tGoodStage1Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 22. (Error : 8400)
	if (m_tGoodStage1Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(8400 + m_nGoodStage1Case);
		return FALSE;
	}
	return TRUE;
}

// 23. (Error : 8600)
BOOL CSequenceMain::Run_GoodStage2()
{
	static int	  nGStage2No		= 1;	//1고정
	static int	  nGStage2YAxisNo = AX_GOOD_STAGE_Y2;

	switch (m_nGoodStage2Case) {
	case 0:	// Wait
		m_tGoodStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 1:
		if (m_pDX12->iGoodStage2TrayExist) {
			gNG->nTrayOX[2][1] = 1;
			m_tGoodStage2Loop.Takt_Start(23, 1, TRUE);
			m_pDY12->oGoodStage2MasterIn = TRUE; m_pDY12->oGoodStage2MasterOut = FALSE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 2:
		if (m_pDX12->iGoodStage2MasterIn && !m_pDX12->iGoodStage2MasterOut) {
			m_tGoodStage2Loop.Takt_Save(23, 1); m_tGoodStage2Loop.Takt_Start(23, 2); 
			m_pDY12->oGoodStage2SlaveIn = TRUE; m_pDY12->oGoodStage2SlaveOut = FALSE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if (m_pDX12->iGoodStage2SlaveIn && !m_pDX12->iGoodStage2SlaveOut) {
			m_tGoodStage2Loop.Takt_Save(23, 2); m_tGoodStage2Loop.Takt_Start(23, 3); 
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if (m_pDX12->iGoodStage2Up && !m_pDX12->iGoodStage2Down) {
			m_nGoodStage2Case = 10; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 10:	//Align Wait
		if (m_nGoodStage1Case > 22) {
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		return TRUE;

	case 11:
		if (m_pDX12->iGoodStage2Up && !m_pDX12->iGoodStage2Down) {
			m_tGoodStage2Loop.Takt_Save(23, 3); m_tGoodStage2Loop.Takt_Start(23, 4); 
			g_objCommon.Move_Position(nGStage2YAxisNo, 1);	//Aling1
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (g_objCommon.Check_Position(nGStage2YAxisNo, 1)) {
			g_objCommon.Save_Motion(nGStage2YAxisNo, 1);
			m_tGoodStage2Loop.Takt_Save(23, 4); m_tGoodStage2Loop.Takt_Start(23, 5); 
			m_nGoodStage2Case = 20; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 20:	//Align Wait
		return TRUE;
	case 21:
		if (m_nGoodStage1Case > 20 && m_nGoodStage1Case < 40) {
			m_tGoodStage2Loop.Takt_Save(23, 5); m_tGoodStage2Loop.Takt_Start(23, 6); 
			g_objCommon.Move_Position(nGStage2YAxisNo, 2);	//Wait
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(30000);
		} else if (m_nGoodStage1Case <= 20 || m_nGoodStage1Case >= 40) {
			m_tGoodStage2Loop.Takt_Save(23, 5); m_tGoodStage2Loop.Takt_Start(23, 6); 
			g_objCommon.Move_Position(nGStage2YAxisNo, 3);	//Work
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 22:
		if (g_objCommon.Check_Position(nGStage2YAxisNo, 2) || g_objCommon.Check_Position(nGStage2YAxisNo, 3)) {
			if (g_objCommon.Check_Position(nGStage2YAxisNo, 2)) g_objCommon.Save_Motion(nGStage2YAxisNo, 2);
			m_tGoodStage2Loop.Takt_Save(23, 6); m_tGoodStage2Loop.Takt_Start(23, 7); 
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 23:
		if (m_nGoodStage1Case <= 20 || m_nGoodStage1Case >= 40) {
			g_objCommon.Move_Position(nGStage2YAxisNo, 3);	//Work
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 24:
		if (g_objCommon.Check_Position(nGStage2YAxisNo, 3)) {
			g_objCommon.Save_Motion(nGStage2YAxisNo, 3);
			m_tGoodStage2Loop.Takt_Save(23, 7); m_tGoodStage2Loop.Takt_Start(23, 8); 
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 25:
		if (gNG->nTrayOX[2][1] == 0 || (gNG->nTrayOX[2][1] == 1 && m_pDX12->iGoodStage2TrayExist)) {
			Init_GoodTray(nGStage2No);
			m_nGoodStage2Case = 30; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 30:	// Unload Picker Wait
		m_tGoodStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 31:
		if (m_nGoodStage1Case < 30 || m_nGoodStage1Case >= 50) {
			m_tGoodStage2Loop.Takt_Save(23, 8); m_tGoodStage2Loop.Takt_Start(23, 9); 
			m_pDY12->oGoodStage2Up = FALSE; m_pDY12->oGoodStage2Down = TRUE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(10000);
		}
		return TRUE;
	case 32:
		if (!m_pDX12->iGoodStage2Up && m_pDX12->iGoodStage2Down) {
			m_tGoodStage2Loop.Takt_Save(23, 9); m_tGoodStage2Loop.Takt_Start(23, 10); 
			m_nGoodStage2Case = 40; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		break;

	case 40:	//Up Wait
		if (m_nGoodStage1Case < 40 || m_nGoodStage1Case >= 60) {
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 41:
		if (!m_pDX12->iGoodStage2Up && m_pDX12->iGoodStage2Down) {
			m_tGoodStage2Loop.Takt_Save(23, 10); m_tGoodStage2Loop.Takt_Start(23, 11); 
			g_objCommon.Move_Position(nGStage2YAxisNo, 0);	//load
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 42:
		if (g_objCommon.Check_Position(nGStage2YAxisNo, 0)) {
			g_objCommon.Save_Motion(nGStage2YAxisNo, 0);
			m_tGoodStage2Loop.Takt_Save(23, 11); m_tGoodStage2Loop.Takt_Start(23, 12); 
			m_nGoodStage2Case = 50; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;

	case 50:
		if (m_nGoodStage1Case > 22 && m_nGoodStage1Case < 50) {
			m_tGoodStage2Loop.Takt_Save(23, 12); m_tGoodStage2Loop.Takt_Start(23, 13); 
			m_pDY12->oGoodStage2Up = TRUE; m_pDY12->oGoodStage2Down = FALSE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		return TRUE;
	case 51:
		if (m_pDX12->iGoodStage2Up && !m_pDX12->iGoodStage2Down) {
			m_tGoodStage2Loop.Takt_Save(23, 13); m_tGoodStage2Loop.Takt_Start(23, 14); 
			m_pDY12->oGoodStage2SlaveIn = FALSE; m_pDY12->oGoodStage2SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 52:
		if (!m_pDX12->iGoodStage2SlaveIn && m_pDX12->iGoodStage2SlaveOut) {
			m_tGoodStage2Loop.Takt_Save(23, 14); m_tGoodStage2Loop.Takt_Start(23, 15); 
			m_pDY12->oGoodStage2MasterIn = FALSE; m_pDY12->oGoodStage2MasterOut = TRUE;
			g_objAJinAXL.Write_Output(12);
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 53:
		if (!m_pDX12->iGoodStage2MasterIn && m_pDX12->iGoodStage2MasterOut) {
			m_tGoodStage2Loop.Takt_Save(23, 15); m_tGoodStage2Loop.Takt_Start(23, 16); 
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(5000);
		}
		break;
	case 54:
		if (gNG->nTrayOX[2][1] == 1) {
			m_nGoodStage2Case++; m_tGoodStage2Loop.Set_LoopTime(30000);
		} else {
			m_tGoodStage2Loop.Takt_Save(23, 16, TRUE);
			m_nGoodStage2Case = 0; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		break;
	case 55:
		if (m_pDX12->iGoodStage2TrayExist) {
			if (gData.nPortNo_GoodTray[1] > 0) m_nGoodStage2Case = 60;
			else							   m_nGoodStage2Case = 0;
			m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		break;

	case 60:	// Transfer Picker Wait
		m_tGoodStage2Loop.Set_LoopTime(5000);
		return TRUE;

	case 61:
		if (!m_pDX12->iGoodStage2TrayExist) {
			gNG->nTrayOX[2][1] = 0;
			m_tGoodStage2Loop.Takt_Save(23, 16, TRUE);
			m_nGoodStage2Case = 0; m_tGoodStage2Loop.Set_LoopTime(30000);
		}
		break;

	}

	// 23. (Error : 8600)
	if (m_tGoodStage2Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(8600 + m_nGoodStage2Case);
		return FALSE;
	}
	return TRUE;
}

// 24. (Error : 8800)
BOOL CSequenceMain::Run_ShipAlign()
{
	static int nSJobNo;	//1,2,3,4
	static double dSAlignX, dSAlignY;
	if (m_nShipAlignCase > 1 && !m_pEquipData->bUseAlign2) m_nShipAlignCase = 8;

	switch (m_nShipAlignCase) {
	case 0:	// Wait
		if (Check_ShipAlign(nSJobNo)) 
		{
			m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(5000);
		}
		return TRUE;

	case 1:
		if (Check_ShipAlign(nSJobNo)) 
		{
			if (!m_tShipAlignLoop.Waiting_Time(500)) break;
			Init_ShiipAlignData(nSJobNo);

			BOOL bTrayExist = FALSE;
			if (nSJobNo == 1 && m_pDX11->iNGStage1TrayExist)   bTrayExist = TRUE;
			if (nSJobNo == 2 && m_pDX11->iNGStage2TrayExist)   bTrayExist = TRUE;
			if (nSJobNo == 3 && m_pDX12->iGoodStage1TrayExist) bTrayExist = TRUE;
			if (nSJobNo == 4 && m_pDX12->iGoodStage2TrayExist) bTrayExist = TRUE;

			if (bTrayExist == FALSE || !m_pEquipData->bUseAlign2) 
			{
				if (nSJobNo == 1) m_nNGStage1Case   = 21;
				if (nSJobNo == 2) m_nNGStage2Case   = 21;	
				if (nSJobNo == 3) m_nGoodStage1Case = 21;
				if (nSJobNo == 4) m_nGoodStage2Case = 21;
				m_nShipAlignCase = 0; m_tShipAlignLoop.Set_LoopTime(5000);
			} 
			else
			{
				m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(5000);
			}
		} 
		else
		{
			m_nShipAlignCase = 0; m_tShipAlignLoop.Set_LoopTime(5000);
		}
		break;
	case 2:
		if (nSJobNo > 0 && nSJobNo < 5) {
			m_tShipAlignLoop.Takt_Start(24, 1, TRUE);
			g_objCommon.Move_Position(AX_SHIP_ALIGN_X, (nSJobNo-1));

			if (nSJobNo == 1) g_objCommon.Move_Position(AX_NG_STAGE_Y1, 1);
			if (nSJobNo == 2) g_objCommon.Move_Position(AX_NG_STAGE_Y2, 1);
			if (nSJobNo == 3) g_objCommon.Move_Position(AX_GOOD_STAGE_Y1, 1);
			if (nSJobNo == 4) g_objCommon.Move_Position(AX_GOOD_STAGE_Y2, 1);

			m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(10000);
		}
		break;
	case 3:
		if (g_objCommon.Check_Position(AX_SHIP_ALIGN_X, (nSJobNo-1))) {
			if ((nSJobNo == 1 && g_objCommon.Check_Position(AX_NG_STAGE_Y1,   1)) ||
				(nSJobNo == 2 && g_objCommon.Check_Position(AX_NG_STAGE_Y2,   1)) ||
				(nSJobNo == 3 && g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 1)) ||
				(nSJobNo == 4 && g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 1)) ) {

				g_objCommon.Save_Motion(AX_SHIP_ALIGN_X, (nSJobNo-1));
				gData.bAlignShipDone = FALSE;
				if (nSJobNo < 3) g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A2", "NG_STAGE",   nSJobNo, nSJobNo, 1);
				else			g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A2", "GOOD_STAGE", nSJobNo, nSJobNo, 1);
				m_tShipAlignLoop.Takt_Save(24, 1); m_tShipAlignLoop.Takt_Start(24, 2);
				m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(10000);
			}
		}
		break;
	case 4:
		if (gData.bAlignShipDone) {
			if (!m_tShipAlignLoop.Waiting_Time(m_pEquipData->nDelayTime[6])) break;
			dSAlignX = m_pMoveData->dShiipAling[nSJobNo-1] - (m_pEquipData->dTrayPitchX * 3);
			g_objAJinAXL.Move_Absolute(AX_SHIP_ALIGN_X, dSAlignX);
			m_tShipAlignLoop.Takt_Save(24, 2); m_tShipAlignLoop.Takt_Start(24, 3);
			m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(10000);
		}
		break;
	case 5:
		if (g_objAJinAXL.Is_MoveDone(AX_SHIP_ALIGN_X, dSAlignX)) {
			g_objCommon.Save_Motion(AX_SHIP_ALIGN_X, -1, dSAlignX);
			gData.bAlignShipDone = FALSE;
			if (nSJobNo < 3) g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A2", "NG_STAGE",   nSJobNo, nSJobNo, 2);
			else			g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A2", "GOOD_STAGE", nSJobNo, nSJobNo, 2);
			m_tShipAlignLoop.Takt_Save(24, 3); m_tShipAlignLoop.Takt_Start(24, 4);
			m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(10000);
		}
		break;
	case 6:
		if (gData.bAlignShipDone) {
			if (!m_tShipAlignLoop.Waiting_Time(m_pEquipData->nDelayTime[6])) break;
			if (nSJobNo == 1) dSAlignY = m_pMoveData->dNGStageY1[1]   + (m_pEquipData->dTrayPitchY * 9);
			if (nSJobNo == 2) dSAlignY = m_pMoveData->dNGStageY2[1]   + (m_pEquipData->dTrayPitchY * 9);
			if (nSJobNo == 3) dSAlignY = m_pMoveData->dGoodStageY1[1] + (m_pEquipData->dTrayPitchY * 9);
			if (nSJobNo == 4) dSAlignY = m_pMoveData->dGoodStageY2[1] + (m_pEquipData->dTrayPitchY * 9);

			if (nSJobNo == 1) g_objAJinAXL.Move_Absolute(AX_NG_STAGE_Y1,   dSAlignY);
			if (nSJobNo == 2) g_objAJinAXL.Move_Absolute(AX_NG_STAGE_Y2,   dSAlignY);
			if (nSJobNo == 3) g_objAJinAXL.Move_Absolute(AX_GOOD_STAGE_Y1, dSAlignY);
			if (nSJobNo == 4) g_objAJinAXL.Move_Absolute(AX_GOOD_STAGE_Y2, dSAlignY);
			
			m_tShipAlignLoop.Takt_Save(24, 4); m_tShipAlignLoop.Takt_Start(24, 5);
			m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(10000);
		}
		break;
	case 7:
		if ((nSJobNo == 1 && g_objAJinAXL.Is_MoveDone(AX_NG_STAGE_Y1,   dSAlignY)) ||
			(nSJobNo == 2 && g_objAJinAXL.Is_MoveDone(AX_NG_STAGE_Y2,   dSAlignY)) ||
			(nSJobNo == 3 && g_objAJinAXL.Is_MoveDone(AX_GOOD_STAGE_Y1, dSAlignY)) ||
			(nSJobNo == 4 && g_objAJinAXL.Is_MoveDone(AX_GOOD_STAGE_Y2, dSAlignY)) ) {
			if (nSJobNo == 1) g_objCommon.Save_Motion(AX_NG_STAGE_Y1,   -1, dSAlignY);
			if (nSJobNo == 2) g_objCommon.Save_Motion(AX_NG_STAGE_Y2,   -1, dSAlignY);
			if (nSJobNo == 3) g_objCommon.Save_Motion(AX_GOOD_STAGE_Y1, -1, dSAlignY);
			if (nSJobNo == 4) g_objCommon.Save_Motion(AX_GOOD_STAGE_Y2, -1, dSAlignY);
			gData.bAlignShipDone = FALSE;
			if (nSJobNo < 3) g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A2", "NG_STAGE",   nSJobNo, nSJobNo, 3);
			else			g_objInspector.Set_AlignRequest(INSPECTOR_PC1, "A2", "GOOD_STAGE", nSJobNo, nSJobNo, 3);
			m_tShipAlignLoop.Takt_Save(24, 5); m_tShipAlignLoop.Takt_Start(24, 6);
			m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(10000);
		}
		break;
	case 8:
		if (gData.bAlignShipDone || !m_pEquipData->bUseAlign2) {
			if (!m_tShipAlignLoop.Waiting_Time(m_pEquipData->nDelayTime[6])) break;
			if (nSJobNo == 1) m_nNGStage1Case   = 21;
			if (nSJobNo == 2) m_nNGStage2Case   = 21;	
			if (nSJobNo == 3) m_nGoodStage1Case = 21;
			if (nSJobNo == 4) m_nGoodStage2Case = 21;

//			g_objCommon.Move_Position(AX_SHIP_ALIGN_X, 4);	//Ready
			m_tShipAlignLoop.Takt_Save(24, 6, TRUE);
			m_nShipAlignCase++; m_tShipAlignLoop.Set_LoopTime(10000);
		}
		break;
	case 9:
//		if (g_objCommon.Check_Position(AX_SHIP_ALIGN_X, 4)) {
			m_nShipAlignCase = 0; m_tShipAlignLoop.Set_LoopTime(10000);
//		}
		break;

	}

	// 24. (Error : 8800)
	if (m_tShipAlignLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(8800 + m_nShipAlignCase);
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CSequenceMain::Run_Simulation()
{
#ifdef AJIN_BOARD_USE
	return TRUE;
#endif

	if (m_nElevator3Case == 10) { Sleep(SIM_WAITTIMES); m_pDX01->iElevator3Height1 = TRUE; }
	if (m_nElevator3Case == 12) { Sleep(SIM_WAITTIMES); m_pDX01->iElevator3Height1 = FALSE; }
	if (m_nElevator3Case == 14) { Sleep(SIM_WAITTIMES); m_pDX01->iElevator3Height1 = TRUE; }

	if (m_nElevator4Case == 10) { Sleep(SIM_WAITTIMES); m_pDX01->iElevator4Height1 = TRUE; }
	if (m_nElevator4Case == 12) { Sleep(SIM_WAITTIMES); m_pDX01->iElevator4Height1 = FALSE; }
	if (m_nElevator4Case == 14) { Sleep(SIM_WAITTIMES); m_pDX01->iElevator4Height1 = TRUE; }

	if (m_nElevator5Case ==  2) { Sleep(SIM_WAITTIMES); m_pDX02->iElevator5Height1 = FALSE; m_pDX02->iElevator5Height2 = FALSE; }
	if (m_nElevator5Case == 10) { Sleep(SIM_WAITTIMES); m_pDX02->iElevator5Height1 = TRUE; }
	if (m_nElevator5Case == 12) { Sleep(SIM_WAITTIMES); m_pDX02->iElevator5Height1 = FALSE; m_pDX02->iElevator5Height2 = FALSE; }
	if (m_nElevator5Case == 14) { Sleep(SIM_WAITTIMES); m_pDX02->iElevator5Height1 = TRUE;  m_pDX02->iElevator5Height2 = TRUE; }

	if (m_nTransfer1Case == 14) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferLTrayExist = TRUE; }
	if (m_nTransfer1Case == 26) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferLTrayExist = TRUE; }
	if (m_nTransfer1Case == 36) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferLTrayExist = TRUE; }
	if (m_nTransfer1Case == 47) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferLTrayExist = FALSE; }
	if (m_nTransfer1Case == 47) { if (m_nLoadStage1Case == 0) m_pDX04->iLoadStage1TrayExist = TRUE; }
	if (m_nTransfer1Case == 47) { if (m_nLoadStage2Case == 0) m_pDX04->iLoadStage2TrayExist = TRUE; }
	if (m_nTransfer1Case == 58) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferLTrayExist = FALSE; }
	if (m_nTransfer1Case == 68) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferLTrayExist = FALSE; }
	
	if (m_nTransfer2Case == 15) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = TRUE; }
	if (m_nTransfer2Case == 25) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = TRUE; }
	if (m_nTransfer2Case == 35) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = TRUE; }
	if (m_nTransfer2Case == 36) { Sleep(SIM_WAITTIMES); m_pDX02->iElevator5TrayExist = FALSE; }
	if (m_nTransfer2Case == 45) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = TRUE; }
	if (m_nTransfer2Case == 55) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = TRUE; }
	if (m_nTransfer2Case == 73) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = FALSE; }
	if (m_nTransfer2Case == 74) { Sleep(SIM_WAITTIMES); m_pDX02->iElevator5TrayExist = TRUE; }
	if (m_nTransfer2Case == 79) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = FALSE; }
	if (m_nTransfer2Case == 84) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = FALSE; }
	if (m_nTransfer2Case == 89) { Sleep(SIM_WAITTIMES); m_pDX03->iTransferRTrayExist = FALSE;
								if ((gData.nTransferX2Pos-11)==1) m_pDX12->iGoodStage1TrayExist = TRUE;
								if ((gData.nTransferX2Pos-11)==2) m_pDX12->iGoodStage2TrayExist = TRUE; }

	if (m_nLoadStage1Case ==  1) { Sleep(SIM_WAITTIMES); m_pDX04->iLoadStage1TrayExist = TRUE; }
	if (m_nLoadStage1Case == 61) { Sleep(SIM_WAITTIMES); m_pDX04->iLoadStage1TrayExist = FALSE; }
	if (m_nLoadStage2Case ==  1) { Sleep(SIM_WAITTIMES); m_pDX04->iLoadStage2TrayExist = TRUE; }
	if (m_nLoadStage2Case == 61) { Sleep(SIM_WAITTIMES); m_pDX04->iLoadStage2TrayExist = FALSE; }

	if (m_nNGStage1Case ==  1) { Sleep(SIM_WAITTIMES); m_pDX11->iNGStage1TrayExist = TRUE; }
	if (m_nNGStage1Case == 54 && gData.nPortNo_NGTray[0] > 0) { Sleep(SIM_WAITTIMES); m_pDX11->iNGStage1TrayExist = TRUE; }
	if (m_nNGStage1Case == 61) { Sleep(SIM_WAITTIMES); m_pDX11->iNGStage1TrayExist = FALSE; }
	if (m_nNGStage2Case ==  1) { Sleep(SIM_WAITTIMES); m_pDX11->iNGStage2TrayExist = TRUE; }
	if (m_nNGStage2Case == 54 && gData.nPortNo_NGTray[1] > 0) { Sleep(SIM_WAITTIMES); m_pDX11->iNGStage2TrayExist = TRUE; }
	if (m_nNGStage2Case == 61) { Sleep(SIM_WAITTIMES); m_pDX11->iNGStage2TrayExist = FALSE; }

	if (m_nGoodStage1Case ==  1) { Sleep(SIM_WAITTIMES); m_pDX12->iGoodStage1TrayExist = TRUE; }
	if (m_nGoodStage1Case == 54 && gData.nPortNo_GoodTray[0] > 0) { Sleep(SIM_WAITTIMES); m_pDX12->iGoodStage1TrayExist = TRUE; }
	if (m_nGoodStage1Case == 61) { Sleep(SIM_WAITTIMES); m_pDX12->iGoodStage1TrayExist = FALSE; }
	if (m_nGoodStage2Case ==  1) { Sleep(SIM_WAITTIMES); m_pDX12->iGoodStage2TrayExist = TRUE; }
	if (m_nGoodStage2Case == 54 && gData.nPortNo_GoodTray[1] > 0) { Sleep(SIM_WAITTIMES); m_pDX12->iGoodStage2TrayExist = TRUE; }
	if (m_nGoodStage2Case == 61) { Sleep(SIM_WAITTIMES); m_pDX12->iGoodStage2TrayExist = FALSE; }

	if (m_nLoadPicker1Case == 19) m_nLoadPicker1Case++;
	if (m_nLoadPicker2Case == 19) m_nLoadPicker2Case++;

	if (m_nVisionStage1Case ==  8 || m_nVisionStage2Case ==  8 || m_nVisionStage3Case ==  8 || m_nVisionStage4Case ==  8) gData.bTop1ScanDone = TRUE;
	if (m_nVisionStage1Case == 12 || m_nVisionStage2Case == 12 || m_nVisionStage3Case == 12 || m_nVisionStage4Case == 12) gData.bTop1ScanDone = TRUE;
	if (m_nVisionStage1Case == 18 || m_nVisionStage2Case == 18 || m_nVisionStage3Case == 18 || m_nVisionStage4Case == 18) gData.bTop2ScanDone = TRUE;

	return TRUE;
}