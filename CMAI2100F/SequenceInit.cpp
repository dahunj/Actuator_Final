// SequenceInit.cpp : 구현 파일
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SequenceInit.h"
#include "LogFile.h"
#include "Common.h"
#include "CMAI2100Dlg.h"
#include "SequenceMain.h"
#include "WorkDlg.h"
#include "MesAgent.h"

CSequenceInit g_objSequenceInit;

CSequenceInit::CSequenceInit()
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
	
	m_bThreadInitial = FALSE;
	m_pThreadInitial = NULL;
	
	Reset_InitialCase();

	m_bInitComplete = FALSE;
}

CSequenceInit::~CSequenceInit()
{
	if (m_pThreadInitial) {
		m_bThreadInitial = FALSE;
		WaitForSingleObject(m_pThreadInitial->m_hThread, INFINITE);
	}
}

int *CSequenceInit::Get_InitialCase()
{
	static int nCase[10] = { 0 };

	nCase[0]  = m_niMainCase;			//  0. (Error : 1000)
	nCase[1]  = m_niElevatorCase;		//  1. (Error : 1100)
	nCase[2]  = m_niTransferCase;		//  2. (Error : 1200)
	nCase[3]  = m_niLoadStageCase;		//  3. (Error : 1300)
	nCase[4]  = m_niLoadPickerCase;		//  4. (Error : 1400)
	nCase[5]  = m_niVisionStageCase;	//  5. (Error : 1500)
	nCase[6]  = m_niUnloadPickerCase;	//  6. (Error : 1600)
	nCase[7]  = m_niNGStageCase;		//  7. (Error : 1700)
	nCase[8]  = m_niGoodStageCase;		//  8. (Error : 1800)

	return nCase;
}

void CSequenceInit::Begin_InitialThread()
{
	m_bInitComplete = FALSE;

	Init_Replay();

	Reset_InitialCase();	m_niMainCase = 1;
//	if (m_niMainCase == 0) m_niMainCase = 1;

	CString strMsg;
	for (int i=1; i<8; i++) {
		if (gData.nElevatorOpen[i] > 0) {
			strMsg.Format("Elevator %d Door 버턴을 눌러 주시고, Lot 시작해 주세요......", i);
			g_objCommon.Show_MsgBox(1, strMsg);
			return;
		}
	}
	if (!g_objCommon.Check_TraySlide(9)) {
		return;
	}

	g_objDataManager.Read_EquipData();
	g_objDataManager.Read_IdleData();
	g_dlgWork.Clear_MainLotID();

	if (m_pThreadInitial) End_InitialThread();
	m_bThreadInitial = TRUE;
	m_pThreadInitial = AfxBeginThread(Thread_Initial, NULL);
}

void CSequenceInit::End_InitialThread()
{
	if (m_pThreadInitial) {
		m_bThreadInitial = FALSE;
		WaitForSingleObject(m_pThreadInitial->m_hThread, INFINITE);
	}
}

void CSequenceInit::Init_Replay()
{
	m_tiMainLoop.Set_LoopTime(5000);
	m_tiElevatorLoop.Set_LoopTime(5000);
	m_tiTransferLoop.Set_LoopTime(5000);
	m_tiLoadStageLoop.Set_LoopTime(5000);
	m_tiLoadPickerLoop.Set_LoopTime(5000);
	m_tiVisionStageLoop.Set_LoopTime(5000);
	m_tiUnloadPickerLoop.Set_LoopTime(5000);
	m_tiNGStageLoop.Set_LoopTime(5000);
	m_tiGoodStageLoop.Set_LoopTime(5000);
}

void CSequenceInit::Reset_InitialCase()
{
	m_niMainCase			= 0;
	m_niElevatorCase		= 0;
	m_niTransferCase		= 0;
	m_niLoadStageCase		= 0;
	m_niLoadPickerCase		= 0;
	m_niVisionStageCase		= 0;
	m_niUnloadPickerCase	= 0;
	m_niNGStageCase			= 0;
	m_niGoodStageCase		= 0;
}

/////////////////////////////////////////////////////////////////////////////
// Initial Thread Function 

UINT CSequenceInit::Thread_Initial(LPVOID lpVoid)
{
	if (!g_objAJinAXL.Device_Check()) {
		g_objAJinAXL.Terminate();	Sleep(1000);
		if (!g_objAJinAXL.Initialize()) {
			if (gData.nLanguage == 0) AfxMessageBox("AJin SSCNET 보드 재검색에 실패하였습니다.");
			else					  AfxMessageBox("AJin SSCNET board rescan failed.");
			return 0;
		}
		Sleep(1000);
	}

	while (g_objSequenceInit.m_bThreadInitial) {
		if (!g_objCommon.Check_MainEmgAir()) break;
		if (!g_objCommon.Check_MainDoor()) break;
		if (!g_objCommon.Check_TraySlide(1)) break;
		if (!g_objCommon.Check_ServoOn()) break;
		if (!g_objCommon.Check_DirveAlarm()) break;

		if (!g_objSequenceInit.Initial_MainRun()) break;		//  0. (Error : 1000)
		if (!g_objSequenceInit.Initial_Elevator()) break;		//  1. (Error : 1100)
		if (!g_objSequenceInit.Initial_Transfer()) break;		//  2. (Error : 1200)
		if (!g_objSequenceInit.Initial_LoadStage()) break;		//  3. (Error : 1300)
		if (!g_objSequenceInit.Initial_LoadPicker()) break;		//  4. (Error : 1400)
		if (!g_objSequenceInit.Initial_VisionStage()) break;	//  5. (Error : 1500)
		if (!g_objSequenceInit.Initial_UnloadPicker()) break;	//  6. (Error : 1600)
		if (!g_objSequenceInit.Initial_NGStage()) break;		//  7. (Error : 1700)
		if (!g_objSequenceInit.Initial_GoodStage()) break;		//  8. (Error : 1800)

		if (!g_objSequenceInit.Initial_Simulation()) break;		// 99. (Simulation)

		Sleep(10);
	} 
	g_objSequenceInit.m_bThreadInitial = FALSE;
	g_objSequenceInit.m_pThreadInitial = NULL;

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// 0. Main (Error : 1000)
BOOL CSequenceInit::Initial_MainRun()
{
	switch (m_niMainCase) {
	case 0:		// Wait
		return TRUE;

	case 1:		// Initial Start
		g_objLogFile.Save_HandlerLog("[Initial Sequence - Main] start");
		g_objMesAgent.Set_EquipState(1);	//Init

		m_pDY04->oBTMIonizerOn = FALSE;    m_pDY04->oBTMIonizerBlow = FALSE;
		m_pDY04->oBTMSuctionOn = FALSE;    m_pDY04->oTOPIonizerOn = FALSE;
		m_pDY04->oTOPIonizerBlow = FALSE;  m_pDY04->oTOPSuctionOn = FALSE;
		g_objAJinAXL.Write_Output(4);

		m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		break;

	case 2:
		if (!m_pDX03->iTransferLTrayExist) {
			g_objCommon.Set_VisionVacuumOn(1);
			g_objCommon.Set_VisionVacuumOn(2);
			g_objCommon.Set_VisionVacuumOn(3);
			g_objCommon.Set_VisionVacuumOn(4);
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(5000);
		}
		break;
	case 3:
		if (!m_pDX03->iTransferRTrayExist) {
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 4:
		if (!m_pDX04->iLoadStage1TrayExist && !m_pDX04->iLoadStage2TrayExist) {
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 5:
//		if (!m_pDX11->iNGStage1TrayExist && !m_pDX11->iNGStage2TrayExist) {
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
//		}
		break;
	case 6:
//		if (!m_pDX12->iGoodStage1TrayExist && !m_pDX12->iGoodStage2TrayExist) {
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
//		}
		break;
	case 7:
		if (!m_pDX05->iLoadPicker1Exist1 &&
			!m_pDX05->iLoadPicker1Exist2 &&
			!m_pDX05->iLoadPicker1Exist3 &&
			!m_pDX05->iLoadPicker1Exist4 &&
			!m_pDX05->iLoadPicker1Exist5 &&
			!m_pDX05->iLoadPicker1Exist6 &&
			!m_pDX05->iLoadPicker1Exist7 &&
			!m_pDX05->iLoadPicker1Exist8 ) {
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 8:
		if (!m_pDX06->iLoadPicker2Exist1 &&
			!m_pDX06->iLoadPicker2Exist2 &&
			!m_pDX06->iLoadPicker2Exist3 &&
			!m_pDX06->iLoadPicker2Exist4 &&
			!m_pDX06->iLoadPicker2Exist5 &&
			!m_pDX06->iLoadPicker2Exist6 &&
			!m_pDX06->iLoadPicker2Exist7 &&
			!m_pDX06->iLoadPicker2Exist8 ) {
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 9:
		if (!m_pDX09->iUnloadPicker1Exist1 &&
			!m_pDX09->iUnloadPicker1Exist2 &&
			!m_pDX09->iUnloadPicker1Exist3 &&
			!m_pDX09->iUnloadPicker1Exist4 &&
			!m_pDX09->iUnloadPicker1Exist5 &&
			!m_pDX09->iUnloadPicker1Exist6 &&
			!m_pDX09->iUnloadPicker1Exist7 &&
			!m_pDX09->iUnloadPicker1Exist8 ) {
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 10:
		if (!m_pDX10->iUnloadPicker2Exist1 &&
			!m_pDX10->iUnloadPicker2Exist2 &&
			!m_pDX10->iUnloadPicker2Exist3 &&
			!m_pDX10->iUnloadPicker2Exist4 &&
			!m_pDX10->iUnloadPicker2Exist5 &&
			!m_pDX10->iUnloadPicker2Exist6 &&
			!m_pDX10->iUnloadPicker2Exist7 &&
			!m_pDX10->iUnloadPicker2Exist8 ) {
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 11:
		if (!m_pDX07->iInspectStage1Vac1On &&
			!m_pDX07->iInspectStage1Vac2On &&
			!m_pDX07->iInspectStage1Vac3On &&
			!m_pDX07->iInspectStage1Vac4On &&
			!m_pDX07->iInspectStage1Vac5On &&
			!m_pDX07->iInspectStage1Vac6On &&
			!m_pDX07->iInspectStage1Vac7On &&
			!m_pDX07->iInspectStage1Vac8On ) {
			g_objCommon.Set_VisionVacuumOff(1);
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 12:
		if (!m_pDX07->iInspectStage2Vac1On &&
			!m_pDX07->iInspectStage2Vac2On &&
			!m_pDX07->iInspectStage2Vac3On &&
			!m_pDX07->iInspectStage2Vac4On &&
			!m_pDX07->iInspectStage2Vac5On &&
			!m_pDX07->iInspectStage2Vac6On &&
			!m_pDX07->iInspectStage2Vac7On &&
			!m_pDX07->iInspectStage2Vac8On ) {
			g_objCommon.Set_VisionVacuumOff(2);
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 13:
		if (!m_pDX08->iInspectStage3Vac1On &&
			!m_pDX08->iInspectStage3Vac2On &&
			!m_pDX08->iInspectStage3Vac3On &&
			!m_pDX08->iInspectStage3Vac4On &&
			!m_pDX08->iInspectStage3Vac5On &&
			!m_pDX08->iInspectStage3Vac6On &&
			!m_pDX08->iInspectStage3Vac7On &&
			!m_pDX08->iInspectStage3Vac8On ) {
			g_objCommon.Set_VisionVacuumOff(3);
			m_niMainCase++; m_tiMainLoop.Set_LoopTime(3000);
		}
		break;
	case 14:
		if (!m_pDX08->iInspectStage4Vac1On &&
			!m_pDX08->iInspectStage4Vac2On &&
			!m_pDX08->iInspectStage4Vac3On &&
			!m_pDX08->iInspectStage4Vac4On &&
			!m_pDX08->iInspectStage4Vac5On &&
			!m_pDX08->iInspectStage4Vac6On &&
			!m_pDX08->iInspectStage4Vac7On &&
			!m_pDX08->iInspectStage4Vac8On ) {
			g_objCommon.Set_VisionVacuumOff(4);
			m_niMainCase = 50; m_tiMainLoop.Set_LoopTime(5000);
		}
		break;

	case 50:	// 각 파트 초기화 진행
		if (m_niElevatorCase		== 0)	m_niElevatorCase	= 1;
		if (m_niTransferCase		== 0)	m_niTransferCase	= 1;
		if (m_niLoadStageCase		== 0)	m_niLoadStageCase	= 1;
		if (m_niLoadPickerCase		== 0)	m_niLoadPickerCase	= 1;
		if (m_niVisionStageCase		== 0)	m_niVisionStageCase	= 1;
		if (m_niUnloadPickerCase	== 0)	m_niUnloadPickerCase= 1;
		if (m_niNGStageCase			== 0)	m_niNGStageCase		= 1;
		if (m_niGoodStageCase		== 0)	m_niGoodStageCase	= 1;
		m_niMainCase++;
		return TRUE;

	case 51:	// Wait 
		if (m_niElevatorCase == 90 && m_niTransferCase == 90 && m_niLoadStageCase == 90 && m_niLoadPickerCase == 90 &&
			m_niVisionStageCase == 90 && m_niUnloadPickerCase == 90 && m_niNGStageCase == 90 && m_niGoodStageCase == 90) {
			m_niMainCase = 90;
		}
		return TRUE;
		
	case 90:	// Initial Complete
		m_bInitComplete = TRUE;

		Reset_InitialCase();

		// 변수 초기화
		g_objSequenceMain.Reset_MainRunCase();
		g_objSequenceMain.Set_ClearRunData(0);
		g_objMesAgent.Set_EquipState(4);	//Ready

		for(int i=0; i<10; i++) gData.nElevatorOpen[i] = 0;

		CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
		pMainDlg->Set_MainState(STATE_INITEND);

		g_objLogFile.Save_HandlerLog("[Initial Sequence - Main] End");
		m_niMainCase = 0;
		return FALSE;	// Thread_Initial 종료
	}

	// 1. Main (Error : 1000)
	if (m_tiMainLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1000 + m_niMainCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 1. (Error : 1100)
BOOL CSequenceInit::Initial_Elevator()
{
	switch (m_niElevatorCase) {
	case 0:		// Wait
		return TRUE;

	case 1:
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_Elevator Start");
		m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
		break;

	case 2:
		m_pDY00->oElevator1Clamp1On = FALSE; m_pDY00->oElevator1Clamp1Off = TRUE;
		m_pDY00->oElevator1Clamp2On = FALSE; m_pDY00->oElevator1Clamp2Off = TRUE;
		m_pDY00->oElevator2Clamp1On = FALSE; m_pDY00->oElevator2Clamp1Off = TRUE;
		m_pDY00->oElevator2Clamp2On = FALSE; m_pDY00->oElevator2Clamp2Off = TRUE;
		g_objAJinAXL.Write_Output(0);
		m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
		break;
	case 3:
		if (!m_pDX00->iElevator1Clamp1On && m_pDX00->iElevator1Clamp1Off) {
			if (!m_pDX00->iElevator1Clamp2On && m_pDX00->iElevator1Clamp2Off) {
				m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 4:
		if (!m_pDX00->iElevator2Clamp1On && m_pDX00->iElevator2Clamp1Off) {
			if (!m_pDX00->iElevator2Clamp2On && m_pDX00->iElevator2Clamp2Off) {
				m_pDY01->oElevator3Clamp1On = FALSE; m_pDY01->oElevator3Clamp1Off = TRUE;
				m_pDY01->oElevator3Clamp2On = FALSE; m_pDY01->oElevator3Clamp2Off = TRUE;
				m_pDY01->oElevator4Clamp1On = FALSE; m_pDY01->oElevator4Clamp1Off = TRUE;
				m_pDY01->oElevator4Clamp2On = FALSE; m_pDY01->oElevator4Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(1);
				m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 5:
		if (!m_pDX01->iElevator3Clamp1On && m_pDX01->iElevator3Clamp1Off) {
			if (!m_pDX01->iElevator3Clamp2On && m_pDX01->iElevator3Clamp2Off) {
				m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 6:
		if (!m_pDX01->iElevator4Clamp1On && m_pDX01->iElevator4Clamp1Off) {
			if (!m_pDX01->iElevator4Clamp2On && m_pDX01->iElevator4Clamp2Off) {
				m_pDY02->oElevator5Clamp1On = FALSE; m_pDY02->oElevator5Clamp1Off = TRUE;
				m_pDY02->oElevator5Clamp2On = FALSE; m_pDY02->oElevator5Clamp2Off = TRUE;
				g_objAJinAXL.Write_Output(2);
				m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 7:
		if (!m_pDX02->iElevator5Clamp1On && m_pDX02->iElevator5Clamp1Off) {
			if (!m_pDX02->iElevator5Clamp2On && m_pDX02->iElevator5Clamp2Off) {
				m_niElevatorCase = 11; m_tiElevatorLoop.Set_LoopTime(30000);
			}
		}
		break;

	case 11:
			g_objAJinAXL.Home_Search(AX_ELEVATOR_Z1);
			g_objAJinAXL.Home_Search(AX_ELEVATOR_Z2);
			g_objAJinAXL.Home_Search(AX_ELEVATOR_Z3);
			g_objAJinAXL.Home_Search(AX_ELEVATOR_Z4);
			g_objAJinAXL.Home_Search(AX_ELEVATOR_Z5);
			g_objAJinAXL.Home_Search(AX_ELEVATOR_Z6);
			g_objAJinAXL.Home_Search(AX_ELEVATOR_Z7);
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		break;
	case 12:
		if (g_objAJinAXL.Is_Home(AX_ELEVATOR_Z1)) {
			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z1, gData.dElevatorDown);
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Home(AX_ELEVATOR_Z2)) {
			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z2, gData.dElevatorDown);
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objAJinAXL.Is_Home(AX_ELEVATOR_Z3)) {
			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z3, gData.dElevatorDown);
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Home(AX_ELEVATOR_Z4)) {
			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z4, gData.dElevatorDown);
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Home(AX_ELEVATOR_Z5)) {
			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z5, gData.dElevatorDown);
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Home(AX_ELEVATOR_Z6)) {
			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z6, gData.dElevatorDown);
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 18:
		if (g_objAJinAXL.Is_Home(AX_ELEVATOR_Z7)) {
			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z7, gData.dElevatorDown);
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 19:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z1)) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 20:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z2)) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 21:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z3)) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 22:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z4)) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 23:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z5)) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 24:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z6)) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(30000);
		}
		break;
	case 25:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z7)) {
			m_niElevatorCase = 31; m_tiElevatorLoop.Set_LoopTime(5000);
		}
		break;

	case 31:
		if (!m_pDX00->iElevator1Height1 && !m_pDX00->iElevator1Height2) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
		}
		break;
	case 32:
		if (!m_pDX00->iElevator2Height1 && !m_pDX00->iElevator2Height2) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
		}
		break;
	case 33:
		if (!m_pDX01->iElevator3Height1 && !m_pDX01->iElevator3Height2) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
		}
		break;
	case 34:
		if (!m_pDX01->iElevator4Height1 && !m_pDX01->iElevator4Height2) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
		}
		break;
	case 35:
		if (!m_pDX02->iElevator5Height1 && !m_pDX02->iElevator5Height2) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
		}
		break;
	case 36:
		if (!m_pDX02->iElevator6Height1) {
			m_niElevatorCase++; m_tiElevatorLoop.Set_LoopTime(5000);
		}
		break;
	case 37:
		if (!m_pDX02->iElevator7Height1) {
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_Elevator Complete");
			m_niElevatorCase = 90; m_tiElevatorLoop.Set_LoopTime(5000);
		}
		break;


	case 90:	// Initial Complete
		return TRUE;
	}

	// 1. (Error : 1100)
	if (m_tiElevatorLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1100 + m_niElevatorCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 2. (Error : 1200)
BOOL CSequenceInit::Initial_Transfer()
{
	switch (m_niTransferCase) {
	case 0:		// Wait
		return TRUE;

	case 1:
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_Transfer Start");
		m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(5000);
		break;

	case 2:
		g_objAJinAXL.Home_Search(AX_TRANSFER_Z1);
		g_objAJinAXL.Home_Search(AX_TRANSFER_Z2);

		m_pDY03->oTransferLGrabOpen = TRUE; m_pDY03->oTransferLGrabClose = FALSE;
		m_pDY03->oTransferRGrabOpen = TRUE; m_pDY03->oTransferRGrabClose = FALSE;
		m_pDY03->oAlignMasterIn = FALSE;	m_pDY03->oAlignMasterOut = TRUE;
		m_pDY03->oAlignSlave1In = FALSE;	m_pDY03->oAlignSlave1Out = TRUE;
		m_pDY03->oAlignSlave2In = FALSE;	m_pDY03->oAlignSlave2Out = TRUE;
		g_objAJinAXL.Write_Output(3);
		m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(5000);
		break;
	case 3:
		if (m_pDX03->iTransferLGrab1Open && !m_pDX03->iTransferLGrab1Close) {
			if (m_pDX03->iTransferLGrab2Open && !m_pDX03->iTransferLGrab2Close) {
				m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 4:
		if (m_pDX03->iTransferRGrab1Open && !m_pDX03->iTransferRGrab1Close) {
			if (m_pDX03->iTransferRGrab2Open && !m_pDX03->iTransferRGrab2Close) {
				m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(10000);
			}
		}
		break;
	case 5:
		if (!m_pDX03->iAlignMasterIn && m_pDX03->iAlignMasterOut) {
			if (!m_pDX03->iAlignSlave1In && m_pDX03->iAlignSlave1Out) {
				if (!m_pDX03->iAlignSlave2In && m_pDX03->iAlignSlave2Out) {
					if (!m_tiTransferLoop.Waiting_Time(3000)) break;
					m_niTransferCase = 11; m_tiTransferLoop.Set_LoopTime(5000);
				}
			}
		}
		break;

	case 11:
		g_objAJinAXL.Home_Search(AX_TRANSFER_X1);
		g_objAJinAXL.Home_Search(AX_TRANSFER_X2);
		m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(30000);
		break;
	case 12:
		if (g_objAJinAXL.Is_Home(AX_TRANSFER_Z1)) {
			g_objCommon.Move_Position(AX_TRANSFER_Z1, 0);
			m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Home(AX_TRANSFER_Z2)) {
			g_objCommon.Move_Position(AX_TRANSFER_Z2, 0);
			m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objCommon.Check_Position(AX_TRANSFER_Z1, 0) && g_objCommon.Check_Position(AX_TRANSFER_Z2, 0) ) {
//			g_objAJinAXL.Home_Search(AX_TRANSFER_X1);
//			g_objAJinAXL.Home_Search(AX_TRANSFER_X2);
			m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(60000);
		}
	case 15:
		if (g_objAJinAXL.Is_Home(AX_TRANSFER_X1)) {
			gData.nTransferX1Pos = 3; //Load1
			g_objCommon.Move_Position(AX_TRANSFER_X1, 3);	//Load1
			m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(60000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Home(AX_TRANSFER_X2)) {
			gData.nTransferX2Pos = 6; //Empty-Good
			g_objCommon.Move_Position(AX_TRANSFER_X2, 2);	//Empty-Good
			m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objCommon.Check_Position(AX_TRANSFER_X1, 3) ) {
			m_niTransferCase++; m_tiTransferLoop.Set_LoopTime(30000);
		}
		break;
	case 18:
		if (g_objCommon.Check_Position(AX_TRANSFER_X2, 2) ) {
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_Transfer Complete");
			m_niTransferCase = 90; m_tiTransferLoop.Set_LoopTime(5000);
		}
		break;
		
	case 90:	// Initial Complete
		return TRUE;
	}

	// 2. (Error : 1200)
	if (m_tiTransferLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1200 + m_niTransferCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 3. (Error : 1300)
BOOL CSequenceInit::Initial_LoadStage()
{
	switch (m_niLoadStageCase) {
	case 0:		// Wait
		return TRUE;

	case 1:		// Loading Initial Start
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_LoadStage Start");
		m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(5000);
		break;

	case 2:
		m_pDY04->oLoadStage1MasterIn = FALSE; m_pDY04->oLoadStage1MasterOut = TRUE;
		m_pDY04->oLoadStage1SlaveIn = FALSE;  m_pDY04->oLoadStage1SlaveOut = TRUE;
		m_pDY04->oLoadStage2MasterIn = FALSE; m_pDY04->oLoadStage2MasterOut = TRUE;
		m_pDY04->oLoadStage2SlaveIn = FALSE;  m_pDY04->oLoadStage2SlaveOut = TRUE;
		g_objAJinAXL.Write_Output(4);
		m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(5000);
		break;
	case 3:
		if (!m_pDX04->iLoadStage1MasterIn && m_pDX04->iLoadStage1MasterOut) {
			if (!m_pDX04->iLoadStage1SlaveIn && m_pDX04->iLoadStage1SlaveOut) {
				m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 4:
		if (!m_pDX04->iLoadStage2MasterIn && m_pDX04->iLoadStage2MasterOut) {
			if (!m_pDX04->iLoadStage2SlaveIn && m_pDX04->iLoadStage2SlaveOut) {
				m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 5:
		if ((m_pDX04->iLoadStage1Up && !m_pDX04->iLoadStage1Down) ||
			(!m_pDX04->iLoadStage1Up && m_pDX04->iLoadStage1Down) ) {
			m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(5000);
		}
		break;
	case 6:
		if ((m_pDX04->iLoadStage2Up && !m_pDX04->iLoadStage2Down) ||
			(!m_pDX04->iLoadStage2Up && m_pDX04->iLoadStage2Down) ) {
			m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(5000);
		}
		break;
	case 7:
		if	(m_pDX04->iLoadStage1Up   && m_pDX04->iLoadStage2Up) {
			m_pDY04->oLoadStage2Up = FALSE;  m_pDY04->oLoadStage2Down = TRUE;
			g_objAJinAXL.Write_Output(4);
			m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(30000);
		} else if (m_pDX04->iLoadStage1Down && m_pDX04->iLoadStage2Down) {
			m_pDY04->oLoadStage1Up = TRUE;  m_pDY04->oLoadStage1Down = FALSE;
			g_objAJinAXL.Write_Output(4);
			m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(30000);
		} else {
			m_niLoadStageCase = 11; m_tiLoadStageLoop.Set_LoopTime(60000);
		}
		break;
	case 8:
		if ((m_pDX04->iLoadStage1Up  && !m_pDX04->iLoadStage1Down) && 
			(!m_pDX04->iLoadStage2Up && m_pDX04->iLoadStage2Down) ) {
			m_niLoadStageCase = 11; m_tiLoadStageLoop.Set_LoopTime(60000);
		}
		break;

	case 11:
		if (m_niTransferCase > 12) {
			if (g_objCommon.Get_LoadPickerUp()) {
				g_objAJinAXL.Home_Search(AX_LOAD_STAGE_Y1);
				g_objAJinAXL.Home_Search(AX_LOAD_STAGE_Y2);
				m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(60000);
			}
		}
		break;
	case 12:
		if (g_objAJinAXL.Is_Home(AX_LOAD_STAGE_Y1) ) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, 0);
			m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Home(AX_LOAD_STAGE_Y2) ) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 1);
			m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 0) && g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 1)) {
			m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(30000);
		}
		break;
	case 15:
		m_pDY04->oLoadStage1Up = TRUE;  m_pDY04->oLoadStage1Down = FALSE;
		m_pDY04->oLoadStage2Up = FALSE; m_pDY04->oLoadStage2Down = TRUE;
		g_objAJinAXL.Write_Output(4);
		m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(30000);
		break;
	case 16:
		if ((m_pDX04->iLoadStage1Up  && !m_pDX04->iLoadStage1Down) && 
			(!m_pDX04->iLoadStage2Up && m_pDX04->iLoadStage2Down) ) {
			g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, 0);
			m_niLoadStageCase++; m_tiLoadStageLoop.Set_LoopTime(5000);
		}
		break;
	case 17:
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 0) && g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 0)) {
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_LoadStage Complete");
			m_niLoadStageCase = 90; m_tiLoadStageLoop.Set_LoopTime(5000);
		}
		break;

	case 90:	// Initial Complete
		return TRUE;
	}

	// 3. (Error : 1300)
	if (m_tiLoadStageLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1300 + m_niLoadStageCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 4. (Error : 1400)
BOOL CSequenceInit::Initial_LoadPicker()
{
	switch (m_niLoadPickerCase) {
	case 0:		// Wait
		return TRUE;

	case 1:		// Loading Initial Start
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_LoadPicker Start");
		m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(5000);
		break;
	case 2:
		g_objCommon.Set_LoadPickerUp();
		m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objCommon.Get_LoadPickerUp(1)) {
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(5000);
		}
	case 4:
		if (g_objCommon.Get_LoadPickerUp(2)) {
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(5000);
		}
	case 5:
		g_objCommon.Set_LoadPickerOpen();
		m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(5000);
		break;
	case 6:
		if (g_objCommon.Get_LoadPickerOpen(1)) {
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(5000);
		}
	case 7:
		if (g_objCommon.Get_LoadPickerOpen(2)) {
			m_niLoadPickerCase = 11; m_tiLoadPickerLoop.Set_LoopTime(60000);
		}
		break;

	case 11:
		g_objAJinAXL.Home_Search(AX_BTM_ANGLE_Y);

		g_objAJinAXL.Home_Search(AX_LOAD_PICKER_Z1);
		g_objAJinAXL.Home_Search(AX_LOAD_PICKER_Z2);
		m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		break;
	case 12:
		if (g_objAJinAXL.Is_Home(AX_LOAD_PICKER_Z1) && g_objAJinAXL.Is_Home(AX_LOAD_PICKER_Z2) ) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, 0);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, 0);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0) && g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0) ) {
			g_objAJinAXL.Home_Search(AX_LOAD_PICKER_Y1);
			g_objAJinAXL.Home_Search(AX_LOAD_PICKER_Y2);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objAJinAXL.Is_Home(AX_LOAD_PICKER_Y1) && g_objAJinAXL.Is_Home(AX_LOAD_PICKER_Y2) ) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, 0);
			g_objCommon.Move_Position(AX_LOAD_PICKER_Y2, 0);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0) && g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0) ) {
			g_objAJinAXL.Home_Search(AX_LOAD_PICKER_P1);
			g_objAJinAXL.Home_Search(AX_LOAD_PICKER_P2);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Home(AX_LOAD_PICKER_P1) && g_objAJinAXL.Is_Home(AX_LOAD_PICKER_P2) ) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_P1, 0);
			g_objCommon.Move_Position(AX_LOAD_PICKER_P2, 0);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_P1, 0) && g_objCommon.Check_Position(AX_LOAD_PICKER_P2, 0) ) {
			g_objAJinAXL.Home_Search(AX_LOAD_PICKER_X1);
			g_objAJinAXL.Home_Search(AX_LOAD_PICKER_X2);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(60000);
		}
		break;
	case 18:
		if (g_objAJinAXL.Is_Home(AX_LOAD_PICKER_X1) && g_objAJinAXL.Is_Home(AX_LOAD_PICKER_X2) ) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_X1, 1);	//Load
			g_objCommon.Move_Position(AX_LOAD_PICKER_X2, 1);	//Load
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 19:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_X1, 1) && g_objCommon.Check_Position(AX_LOAD_PICKER_X2, 1) ) {
			g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, 1);	//Load
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 20:
		if (g_objAJinAXL.Is_Home(AX_BTM_ANGLE_Y) ) {
			g_objCommon.Move_Position(AX_BTM_ANGLE_Y, 1);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 21:
		if (g_objCommon.Check_Position(AX_BTM_ANGLE_Y, 1) ) {
			g_objAJinAXL.Home_Search(AX_BTM_FOCUS_Z);
			g_objAJinAXL.Home_Search(AX_BTM_LIGHT_Z);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 22:
		if (g_objAJinAXL.Is_Home(AX_BTM_FOCUS_Z) && g_objAJinAXL.Is_Home(AX_BTM_LIGHT_Z) ) {
			g_objCommon.Move_Position(AX_BTM_LIGHT_Z, 1);
			g_objCommon.Move_Position(AX_BTM_FOCUS_Z, 1);
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 23:
		if (g_objCommon.Check_Position(AX_BTM_LIGHT_Z, 1) && g_objCommon.Check_Position(AX_BTM_FOCUS_Z, 1) ) {
			m_niLoadPickerCase++; m_tiLoadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 24:
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 1) ) {
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_LoadPicker Complete");
			m_niLoadPickerCase = 90; m_tiLoadPickerLoop.Set_LoopTime(5000);
		}
		break;

	case 90:	// Initial Complete
		return TRUE;
	}

	// 4. (Error : 1400)
	if (m_tiLoadPickerLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1400 + m_niLoadPickerCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 5. (Error : 1500)
BOOL CSequenceInit::Initial_VisionStage()
{
	switch (m_niVisionStageCase) {
	case 0:		// Wait
		return TRUE;

	case 1:		// Loading Initial Start
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_VisionStage Start");
		m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
		break;
	case 2:
#ifdef NEW_FINAL
#else
		g_objAJinAXL.Home_Search(AX_TOP1_ANGLE_Y);
#endif
		g_objAJinAXL.Home_Search(AX_TOP2_VISION_Z);

		if (m_pDX07->iInspectStage1Down) {
			m_pDY07->oInspectStage1Yin = FALSE; m_pDY07->oInspectStage1YOut = TRUE;
			g_objAJinAXL.Write_Output(7);
		}
		if (m_pDX08->iInspectStage4Down) {
			m_pDY08->oInspectStage4Yin = FALSE; m_pDY08->oInspectStage4YOut = TRUE;
			g_objAJinAXL.Write_Output(8);
		}
		m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
		break;
	case 3:
		if ((m_pDX07->iInspectStage1YOut) || (m_pDX08->iInspectStage4YOut) ||
			(m_pDX07->iInspectStage1Up && m_pDX08->iInspectStage4Up) ) {
			if (!m_tiVisionStageLoop.Waiting_Time(3000)) break;

			m_pDY07->oInspectStage1Up = FALSE;  m_pDY07->oInspectStage1Down = TRUE;
			g_objAJinAXL.Write_Output(7);

			m_pDY08->oInspectStage4Up = FALSE;  m_pDY08->oInspectStage4Down = TRUE;
			g_objAJinAXL.Write_Output(8);

			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
		}
		break;
	case 4:
		if (!m_pDX07->iInspectStage1Up && m_pDX07->iInspectStage1Down) {
			m_pDY07->oInspectStage1Yin = FALSE; m_pDY07->oInspectStage1YOut = TRUE;
			m_pDY07->oInspectStage1Deg0 = TRUE; m_pDY07->oInspectStage1Deg90 = FALSE;
			m_pDY07->oInspectStage2Deg0 = TRUE; m_pDY07->oInspectStage2Deg90 = FALSE;
			m_pDY07->oInspectStage1Vac1On = FALSE;
			m_pDY07->oInspectStage1Vac2On = FALSE;
			m_pDY07->oInspectStage1Vac3On = FALSE;
			m_pDY07->oInspectStage1Vac4On = FALSE;
			m_pDY07->oInspectStage1Vac5On = FALSE;
			m_pDY07->oInspectStage1Vac6On = FALSE;
			m_pDY07->oInspectStage1Vac7On = FALSE;
			m_pDY07->oInspectStage1Vac8On = FALSE;
			m_pDY07->oInspectStage2Vac1On = FALSE;
			m_pDY07->oInspectStage2Vac2On = FALSE;
			m_pDY07->oInspectStage2Vac3On = FALSE;
			m_pDY07->oInspectStage2Vac4On = FALSE;
			m_pDY07->oInspectStage2Vac5On = FALSE;
			m_pDY07->oInspectStage2Vac6On = FALSE;
			m_pDY07->oInspectStage2Vac7On = FALSE;
			m_pDY07->oInspectStage2Vac8On = FALSE;
			g_objAJinAXL.Write_Output(7);
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (!m_pDX08->iInspectStage4Up && m_pDX08->iInspectStage4Down) {
			m_pDY08->oInspectStage4Yin = FALSE; m_pDY08->oInspectStage4YOut = TRUE;
			m_pDY08->oInspectStage3Deg0 = TRUE; m_pDY08->oInspectStage3Deg90 = FALSE;
			m_pDY08->oInspectStage4Deg0 = TRUE; m_pDY08->oInspectStage4Deg90 = FALSE;
			m_pDY08->oInspectStage3Vac1On = FALSE;
			m_pDY08->oInspectStage3Vac2On = FALSE;
			m_pDY08->oInspectStage3Vac3On = FALSE;
			m_pDY08->oInspectStage3Vac4On = FALSE;
			m_pDY08->oInspectStage3Vac5On = FALSE;
			m_pDY08->oInspectStage3Vac6On = FALSE;
			m_pDY08->oInspectStage3Vac7On = FALSE;
			m_pDY08->oInspectStage3Vac8On = FALSE;
			m_pDY08->oInspectStage4Vac1On = FALSE;
			m_pDY08->oInspectStage4Vac2On = FALSE;
			m_pDY08->oInspectStage4Vac3On = FALSE;
			m_pDY08->oInspectStage4Vac4On = FALSE;
			m_pDY08->oInspectStage4Vac5On = FALSE;
			m_pDY08->oInspectStage4Vac6On = FALSE;
			m_pDY08->oInspectStage4Vac7On = FALSE;
			m_pDY08->oInspectStage4Vac8On = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
		}
		break;
	case 6:
		if (!m_pDX07->iInspectStage1Yin && m_pDX07->iInspectStage1YOut) {
			if (!m_pDX08->iInspectStage4Yin && m_pDX08->iInspectStage4YOut) {
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 7:
		if ((m_pDX07->iInspectStage2Up  && !m_pDX07->iInspectStage2Down) ||
			(!m_pDX07->iInspectStage2Up && m_pDX07->iInspectStage2Down) ) {
			if ((m_pDX08->iInspectStage3Up  && !m_pDX08->iInspectStage3Down) ||
				(!m_pDX08->iInspectStage3Up && m_pDX08->iInspectStage3Down) ) {
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 8:
		if (m_pDX07->iInspectStage2Up && m_pDX08->iInspectStage3Up) {
			m_pDY07->oInspectStage2Up = FALSE;  m_pDY07->oInspectStage2Down = TRUE;
			g_objAJinAXL.Write_Output(7);
		}
		if (m_pDX07->iInspectStage2Down && m_pDX08->iInspectStage3Down) {
			m_pDY07->oInspectStage2Up = TRUE;  m_pDY07->oInspectStage2Down = FALSE;
			g_objAJinAXL.Write_Output(7);
		}
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
		break;
	case 9:
		if ((m_pDX07->iInspectStage2Up   && m_pDX08->iInspectStage3Down) ||
			(m_pDX07->iInspectStage2Down && m_pDX08->iInspectStage3Up) ) {
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
		}
		break;
	case 10:
		if (g_objAJinAXL.Is_Home(AX_TOP2_VISION_Z) ) {
			g_objCommon.Move_Position(AX_TOP2_VISION_Z, 0);
			m_niVisionStageCase = 11; m_tiVisionStageLoop.Set_LoopTime(60000);
		}
		break;

	case 11:
		if (g_objCommon.Get_LoadPickerUp()) {
			if (g_objCommon.Get_UnloadPickerUp(1) && g_objCommon.Get_UnloadPickerUp(2)) {
				g_objAJinAXL.Home_Search(AX_INSPECT_STAGE_X1);
				g_objAJinAXL.Home_Search(AX_INSPECT_STAGE_X4);
				g_objAJinAXL.Home_Search(AX_INSPECT_STAGE_X2);
				g_objAJinAXL.Home_Search(AX_INSPECT_STAGE_X3);
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(60000);
			}
		}
		break;
	case 12:
		if (g_objAJinAXL.Is_Home(AX_INSPECT_STAGE_X1) && g_objAJinAXL.Is_Home(AX_INSPECT_STAGE_X4) ) {
			for(int i=0; i<2; i++) for(int j=0; j<5; j++) gData.nVisionPos[i][j] = 0;
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(60000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Home(AX_INSPECT_STAGE_X2) && g_objAJinAXL.Is_Home(AX_INSPECT_STAGE_X3) ) {
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 3);	//Unload
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, 0);	//Load_Align
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 2);	//Top2
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 1);	//Top1
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
		}
		break;
	case 14:
#ifdef NEW_FINAL
		m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
#else
		if (g_objAJinAXL.Is_Home(AX_TOP1_ANGLE_Y)) {
			g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, 1);
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
		}
#endif
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3) && g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 2) && g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 1)) {
#ifdef NEW_FINAL
				g_objAJinAXL.Home_Search(AX_TOP1_VISION_Z);
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 1) ) {
				g_objAJinAXL.Home_Search(AX_TOP1_LIGHT_Z);
				g_objAJinAXL.Home_Search(AX_TOP1_VISION_Z);
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
			}
#endif
		}
		break;
	case 16:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) ) {
//			m_pDY07->oInspectStage1Yin = TRUE; m_pDY07->oInspectStage1YOut = FALSE;
			m_pDY07->oInspectStage2Up = TRUE; m_pDY07->oInspectStage2Down = FALSE;
			g_objAJinAXL.Write_Output(7);
			m_pDY08->oInspectStage3Up = FALSE; m_pDY08->oInspectStage3Down = TRUE;
//			m_pDY08->oInspectStage4Yin = TRUE; m_pDY08->oInspectStage4YOut = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
		}
		break;
	case 17:
		if (!m_pDX07->iInspectStage1Yin && m_pDX07->iInspectStage1YOut) {
			if (!m_pDX08->iInspectStage4Yin && m_pDX08->iInspectStage4YOut) {
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(5000);
			}
		}
		break;
	case 18:
		if (m_pDX07->iInspectStage2Up && !m_pDX07->iInspectStage2Down) {
			if (!m_pDX08->iInspectStage3Up && m_pDX08->iInspectStage3Down) {
				g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, 0);
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
			}
		}
		break;
	case 19:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0) ) {
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, 1);
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
		}
		break;
	case 20:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 1) ) {
			g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, 2);
			m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
		}
		break;
	case 21:
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 2) ) {
#ifdef NEW_FINAL
			if (g_objAJinAXL.Is_Home(AX_TOP1_VISION_Z)) {
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
			}
#else
			if (g_objAJinAXL.Is_Home(AX_TOP1_LIGHT_Z) && g_objAJinAXL.Is_Home(AX_TOP1_VISION_Z)) {
				g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, 1);
				g_objCommon.Move_Position(AX_TOP1_VISION_Z, 1);
				m_niVisionStageCase++; m_tiVisionStageLoop.Set_LoopTime(30000);
			}
#endif
		}
		break;
	case 22:
		if (g_objCommon.Check_Position(AX_TOP1_VISION_Z, 1) && g_objCommon.Check_Position(AX_TOP2_VISION_Z, 0) ) {
#ifdef NEW_FINAL
				gData.nVisionPos[1][0] = 2;
				gData.nVisionPos[0][0] = 4;	gData.nVisionPos[0][1] = 3;	gData.nVisionPos[0][2] = 1;
				g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_VisionStage Complete");
				m_niVisionStageCase = 90; m_tiVisionStageLoop.Set_LoopTime(5000);
#else
			if (g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 1) && g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 1) ) {
				gData.nVisionPos[1][0] = 2;
				gData.nVisionPos[0][0] = 4;	gData.nVisionPos[0][1] = 3;	gData.nVisionPos[0][2] = 1;
				g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_VisionStage Complete");
				m_niVisionStageCase = 90; m_tiVisionStageLoop.Set_LoopTime(5000);
			}
#endif
		}
		break;

	case 90:	// Initial Complete
		return TRUE;
	}

	// 5. (Error : 1500)
	if (m_tiVisionStageLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1500 + m_niVisionStageCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 6. (Error : 1600)
BOOL CSequenceInit::Initial_UnloadPicker()
{	
	switch (m_niUnloadPickerCase) {
	case 0:		// Wait
		return TRUE;

	case 1:		// Loading Initial Start
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_UnloadPicker Start");
		m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(5000);
		break;
	case 2:
		g_objCommon.Set_UnloadPickerUp();
		m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objCommon.Get_UnloadPickerUp(1)) {
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(5000);
		}
	case 4:
		if (g_objCommon.Get_UnloadPickerUp(2)) {
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(5000);
		}
	case 5:
		g_objCommon.Set_UnloadPickerOpen(0);
		m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(5000);
		break;
	case 6:
		if (g_objCommon.Get_UnloadPickerOpen(1)) {
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(5000);
		}
	case 7:
		if (g_objCommon.Get_UnloadPickerOpen(2)) {
			m_niUnloadPickerCase = 11; m_tiUnloadPickerLoop.Set_LoopTime(60000);
		}
		break;

	case 11:
		g_objAJinAXL.Home_Search(AX_UNLOAD_PICKER_Z1);
		g_objAJinAXL.Home_Search(AX_UNLOAD_PICKER_Z2);
		m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(30000);
		break;
	case 12:
		if (g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_Z1) && g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_Z2) ) {
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z1, 0);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z2, 0);
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0) ) {
			g_objAJinAXL.Home_Search(AX_UNLOAD_PICKER_Y1);
			g_objAJinAXL.Home_Search(AX_UNLOAD_PICKER_Y2);
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_Y1) && g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_Y2) ) {
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y1, 0);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y2, 0);
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, 0) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, 0) ) {
			g_objAJinAXL.Home_Search(AX_UNLOAD_PICKER_P1);
			g_objAJinAXL.Home_Search(AX_UNLOAD_PICKER_P2);
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_P1) && g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_P2) ) {
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_P1, 0);
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_P2, 0);
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_P1, 0) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_P2, 0) ) {
			g_objAJinAXL.Home_Search(AX_UNLOAD_PICKER_X1);
			g_objAJinAXL.Home_Search(AX_UNLOAD_PICKER_X2);
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(60000);
		}
		break;
	case 18:
		if (g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_X1) && g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_X2) ) {
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_X1, 1);	//Stage1
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_X2, 1);	//Stage1
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 19:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_X1, 1) && g_objCommon.Check_Position(AX_UNLOAD_PICKER_X2, 1) ) {
			g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y1, 1);
			m_niUnloadPickerCase++; m_tiUnloadPickerLoop.Set_LoopTime(30000);
		}
		break;
	case 20:
		if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, 1) ) {
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_UnloadPicker Complete");
			m_niUnloadPickerCase = 90; m_tiUnloadPickerLoop.Set_LoopTime(5000);
		}
		break;

	case 90:	// Initial Complete
		return TRUE;
	}

	// 6. (Error : 1600)
	if (m_tiUnloadPickerLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1600 + m_niUnloadPickerCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 7. (Error : 1700)
BOOL CSequenceInit::Initial_NGStage()
{	
	switch (m_niNGStageCase) {
	case 0:		// Wait
		return TRUE;

	case 1:		// Initial_NGStage Start
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_NGStage Start");
		m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
		break;

	case 2:
		if (!m_pDX12->iNGStage1TrayExist) {
			m_pDY12->oNGStage1MasterIn = FALSE; m_pDY12->oNGStage1MasterOut = TRUE;
			m_pDY12->oNGStage1SlaveIn = FALSE;  m_pDY12->oNGStage1SlaveOut = TRUE;
		} else {
			m_pDY12->oNGStage1MasterIn = TRUE; m_pDY12->oNGStage1MasterOut = FALSE;
			m_pDY12->oNGStage1SlaveIn = TRUE;  m_pDY12->oNGStage1SlaveOut = FALSE;
		}
			g_objAJinAXL.Write_Output(11);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
		break;
	case 3:
		if (!m_pDX12->iNGStage1TrayExist) {
			if (!m_pDX12->iNGStage1MasterIn && m_pDX12->iNGStage1MasterOut) {
				if (!m_pDX12->iNGStage1SlaveIn && m_pDX12->iNGStage1SlaveOut) {
					m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
				}
			}
		} else {
			if (m_pDX12->iNGStage1MasterIn && !m_pDX12->iNGStage1MasterOut) {
				if (m_pDX12->iNGStage1SlaveIn && !m_pDX12->iNGStage1SlaveOut) {
					m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
				}
			}
		}
		break;
	case 4:
		if (!m_pDX12->iNGStage2TrayExist) {
			m_pDY12->oNGStage2MasterIn = FALSE; m_pDY12->oNGStage2MasterOut = TRUE;
			m_pDY12->oNGStage2SlaveIn = FALSE;  m_pDY12->oNGStage2SlaveOut = TRUE;
		} else {
			m_pDY12->oNGStage2MasterIn = TRUE; m_pDY12->oNGStage2MasterOut = FALSE;
			m_pDY12->oNGStage2SlaveIn = TRUE;  m_pDY12->oNGStage2SlaveOut = FALSE;
		}
			g_objAJinAXL.Write_Output(11);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
		break;
	case 5:
		if (!m_pDX12->iNGStage2TrayExist) {
			if (!m_pDX12->iNGStage2MasterIn && m_pDX12->iNGStage2MasterOut) {
				if (!m_pDX12->iNGStage2SlaveIn && m_pDX12->iNGStage2SlaveOut) {
					m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
				}
			}
		} else {
			if (m_pDX12->iNGStage2MasterIn && !m_pDX12->iNGStage2MasterOut) {
				if (m_pDX12->iNGStage2SlaveIn && !m_pDX12->iNGStage2SlaveOut) {
					m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
				}
			}
		}
		break;
	case 6:
		if ((m_pDX12->iNGStage1Up && !m_pDX12->iNGStage1Down) ||
			(!m_pDX12->iNGStage1Up && m_pDX12->iNGStage1Down) ) {
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
		}
		break;
	case 7:
		if ((m_pDX12->iNGStage2Up && !m_pDX12->iNGStage2Down) ||
			(!m_pDX12->iNGStage2Up && m_pDX12->iNGStage2Down) ) {
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
		}
		break;
	case 8:
		if (m_pDX12->iNGStage1Up && m_pDX12->iNGStage2Up) {
			m_pDY12->oNGStage2Up = FALSE; m_pDY12->oNGStage2Down = TRUE;
			g_objAJinAXL.Write_Output(11);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(30000);
		} else if (m_pDX12->iNGStage1Down && m_pDX12->iNGStage2Down) {
			m_pDY12->oNGStage1Up = TRUE;  m_pDY12->oNGStage1Down = FALSE;
			g_objAJinAXL.Write_Output(11);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(30000);
		} else {
			m_niNGStageCase = 11; m_tiNGStageLoop.Set_LoopTime(30000);
		}
		break;
	case 9:
		if ((m_pDX12->iNGStage1Up  && !m_pDX12->iNGStage1Down) && 
			(!m_pDX12->iNGStage2Up && m_pDX12->iNGStage2Down) ) {
			m_niNGStageCase = 11; m_tiNGStageLoop.Set_LoopTime(30000);
		}
		break;

	case 11:
		if (g_objCommon.Get_UnloadPickerUp(1) && g_objCommon.Get_UnloadPickerUp(2)) {
			g_objAJinAXL.Home_Search(AX_SHIP_ALIGN_X);
			g_objAJinAXL.Home_Search(AX_NG_STAGE_Y1);
			g_objAJinAXL.Home_Search(AX_NG_STAGE_Y2);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(60000);
		}
		break;
	case 12:
		if (g_objAJinAXL.Is_Home(AX_NG_STAGE_Y1) ) {
			g_objCommon.Move_Position(AX_NG_STAGE_Y1, 0);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Home(AX_NG_STAGE_Y2) ) {
			g_objCommon.Move_Position(AX_NG_STAGE_Y2, 2);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objCommon.Check_Position(AX_NG_STAGE_Y1, 0) && g_objCommon.Check_Position(AX_NG_STAGE_Y2, 2)) {
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(30000);
		}
		break;
	case 15:
		m_pDY12->oNGStage1Up = TRUE;  m_pDY12->oNGStage1Down = FALSE;
		m_pDY12->oNGStage2Up = FALSE; m_pDY12->oNGStage2Down = TRUE;
		g_objAJinAXL.Write_Output(11);
		m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(30000);
		break;
	case 16:
		if ((m_pDX12->iNGStage1Up  && !m_pDX12->iNGStage1Down) && 
			(!m_pDX12->iNGStage2Up && m_pDX12->iNGStage2Down) ) {
			g_objCommon.Move_Position(AX_NG_STAGE_Y2, 0);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(5000);
		}
		break;
	case 17:
		if (g_objCommon.Check_Position(AX_NG_STAGE_Y1, 0) && g_objCommon.Check_Position(AX_NG_STAGE_Y2, 0)) {
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(30000);
		}
		break;
	case 18:
		if (g_objAJinAXL.Is_Home(AX_SHIP_ALIGN_X) ) {
			g_objCommon.Move_Position(AX_SHIP_ALIGN_X, 0);
			m_niNGStageCase++; m_tiNGStageLoop.Set_LoopTime(30000);
		}
		break;
	case 19:
		if (g_objCommon.Check_Position(AX_SHIP_ALIGN_X, 0)) {
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_NGStage Complete");
			m_niNGStageCase = 90; m_tiNGStageLoop.Set_LoopTime(5000);
		}
		break;

	case 90:	// Initial Complete
		return TRUE;
	}

	// 7. (Error : 1700)
	if (m_tiNGStageLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1700 + m_niNGStageCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// 8. (Error : 1800)
BOOL CSequenceInit::Initial_GoodStage()
{
	switch (m_niGoodStageCase) {
	case 0:		// Wait
		return TRUE;

	case 1:		// Initial_GoodStage Start
		g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_GoodStage Start");
		m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
		break;

	case 2:
		if (!m_pDX11->iGoodStage1TrayExist) {
			m_pDY11->oGoodStage1MasterIn = FALSE; m_pDY11->oGoodStage1MasterOut = TRUE;
			m_pDY11->oGoodStage1SlaveIn = FALSE;  m_pDY11->oGoodStage1SlaveOut = TRUE;
		} else {
			m_pDY11->oGoodStage1MasterIn = TRUE; m_pDY11->oGoodStage1MasterOut = FALSE;
			m_pDY11->oGoodStage1SlaveIn = TRUE;  m_pDY11->oGoodStage1SlaveOut = FALSE;
		}
			g_objAJinAXL.Write_Output(12);
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
		break;
	case 3:
		if (!m_pDX11->iGoodStage1TrayExist) {
			if (!m_pDX11->iGoodStage1MasterIn && m_pDX11->iGoodStage1MasterOut) {
				if (!m_pDX11->iGoodStage1SlaveIn && m_pDX11->iGoodStage1SlaveOut) {
					m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
				}
			}
		} else {
			if (m_pDX11->iGoodStage1MasterIn && !m_pDX11->iGoodStage1MasterOut) {
				if (m_pDX11->iGoodStage1SlaveIn && !m_pDX11->iGoodStage1SlaveOut) {
					m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
				}
			}
		}
		break;
	case 4:
		if (!m_pDX11->iGoodStage2TrayExist) {
			m_pDY11->oGoodStage2MasterIn = FALSE; m_pDY11->oGoodStage2MasterOut = TRUE;
			m_pDY11->oGoodStage2SlaveIn = FALSE;  m_pDY11->oGoodStage2SlaveOut = TRUE;
		} else {
			m_pDY11->oGoodStage2MasterIn = TRUE; m_pDY11->oGoodStage2MasterOut = FALSE;
			m_pDY11->oGoodStage2SlaveIn = TRUE;  m_pDY11->oGoodStage2SlaveOut = FALSE;
		}
			g_objAJinAXL.Write_Output(12);
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
		break;
	case 5:
		if (!m_pDX11->iGoodStage2TrayExist) {
			if (!m_pDX11->iGoodStage2MasterIn && m_pDX11->iGoodStage2MasterOut) {
				if (!m_pDX11->iGoodStage2SlaveIn && m_pDX11->iGoodStage2SlaveOut) {
					m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
				}
			}
		} else {
			if (m_pDX11->iGoodStage2MasterIn && !m_pDX11->iGoodStage2MasterOut) {
				if (m_pDX11->iGoodStage2SlaveIn && !m_pDX11->iGoodStage2SlaveOut) {
					m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
				}
			}
		}
		break;
	case 6:
		if ((m_pDX11->iGoodStage1Up && !m_pDX11->iGoodStage1Down) ||
			(!m_pDX11->iGoodStage1Up && m_pDX11->iGoodStage1Down) ) {
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
		}
		break;
	case 7:
		if ((m_pDX11->iGoodStage2Up && !m_pDX11->iGoodStage2Down) ||
			(!m_pDX11->iGoodStage2Up && m_pDX11->iGoodStage2Down) ) {
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
		}
		break;
	case 8:
		if (m_pDX11->iGoodStage1Up && m_pDX11->iGoodStage2Up) {
			m_pDY11->oGoodStage2Up = FALSE; m_pDY11->oGoodStage2Down = TRUE;
			g_objAJinAXL.Write_Output(12);
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(30000);
		} else if (m_pDX11->iGoodStage1Down && m_pDX11->iGoodStage2Down)  {
			m_pDY11->oGoodStage1Up = TRUE;  m_pDY11->oGoodStage1Down = FALSE;
			g_objAJinAXL.Write_Output(12);
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(30000);
		} else {
			m_niGoodStageCase = 11; m_tiGoodStageLoop.Set_LoopTime(30000);
		}
		break;
	case 9:
		if ((m_pDX11->iGoodStage1Up  && !m_pDX11->iGoodStage1Down) && 
			(!m_pDX11->iGoodStage2Up && m_pDX11->iGoodStage2Down) ) {
			m_niGoodStageCase = 11; m_tiGoodStageLoop.Set_LoopTime(30000);
		}
		break;

	case 11:
		if (g_objCommon.Get_UnloadPickerUp(1) && g_objCommon.Get_UnloadPickerUp(2)) {
			g_objAJinAXL.Home_Search(AX_GOOD_STAGE_Y1);
			g_objAJinAXL.Home_Search(AX_GOOD_STAGE_Y2);
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(60000);
		}
		break;
	case 12:
		if (g_objAJinAXL.Is_Home(AX_GOOD_STAGE_Y1) ) {
			g_objCommon.Move_Position(AX_GOOD_STAGE_Y1, 0);
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Home(AX_GOOD_STAGE_Y2) ) {
			g_objCommon.Move_Position(AX_GOOD_STAGE_Y2, 2);
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 0) && g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 2)) {
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(30000);
		}
		break;
	case 15:
		m_pDY11->oGoodStage1Up = TRUE;  m_pDY11->oGoodStage1Down = FALSE;
		m_pDY11->oGoodStage2Up = FALSE; m_pDY11->oGoodStage2Down = TRUE;
		g_objAJinAXL.Write_Output(12);
		m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(30000);
		break;
	case 16:
		if ((m_pDX11->iGoodStage1Up  && !m_pDX11->iGoodStage1Down) && 
			(!m_pDX11->iGoodStage2Up && m_pDX11->iGoodStage2Down) ) {
			g_objCommon.Move_Position(AX_GOOD_STAGE_Y2, 0);
			m_niGoodStageCase++; m_tiGoodStageLoop.Set_LoopTime(5000);
		}
		break;
	case 17:
		if (g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 0) && g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 0)) {
			g_objLogFile.Save_HandlerLog("[Initial Sequence] - Initial_GoodStage Complete");
			m_niGoodStageCase = 90; m_tiGoodStageLoop.Set_LoopTime(5000);
		}
		break;

	case 90:	// Initial Complete
		return TRUE;
	}

	// 8. (Error : 1800)
	if (m_tiGoodStageLoop.Over_LoopTime()) {
		g_objCommon.Show_Error(1800 + m_niGoodStageCase);
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
BOOL CSequenceInit::Initial_Simulation()
{
#ifdef AJIN_BOARD_USE
	return TRUE;
#endif

	Sleep(SIM_WAITTIMES);
	if (m_niMainCase == 5) {
		g_objCommon.Set_VisionVacuumOff(1);
		g_objCommon.Set_VisionVacuumOff(2);
		g_objCommon.Set_VisionVacuumOff(3);
		g_objCommon.Set_VisionVacuumOff(4);
	}

	if (m_niMainCase == 90) {
		m_pDX00->iElevator1SlideClose = TRUE;
		m_pDX00->iElevator2SlideClose = TRUE;
		m_pDX01->iElevator3SlideClose = TRUE;
		m_pDX01->iElevator4SlideClose = TRUE;
		m_pDX02->iElevator5SlideClose = TRUE;
		m_pDX02->iElevator6SlideClose = TRUE;
		m_pDX02->iElevator7SlideClose = TRUE;
	}
	return TRUE;
}
