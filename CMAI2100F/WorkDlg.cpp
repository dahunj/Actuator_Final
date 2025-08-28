// WorkDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "WorkDlg.h"
#include "afxdialogex.h"
#include "LogFile.h"
#include "Common.h"
#include "Inspector.h"
#include "BarcodeLot.h"
#include "IdleReportDlg.h"
#include "MesAgent.h"
#include "Dispatcher.h"
#include "SequenceInit.h"
#include "SequenceMain.h"
#include "OperatorDlg.h"
#include "CMAI2100Dlg.h"
#include "NoWorkDlg.h"

// CWorkDlg 대화 상자입니다.
CWorkDlg g_dlgWork;

IMPLEMENT_DYNAMIC(CWorkDlg, CDialogEx)

CWorkDlg::CWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWorkDlg::IDD, pParent)
{
}

CWorkDlg::~CWorkDlg()
{
}

void CWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 16; i++) DDX_Control(pDX, IDC_LBL_LOT_0 + i, m_lblLot[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_RDO_SELECT_NO_0 + i, m_rdoSlectNo[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_LOTS_ID_S_0 + i, m_stcLotsIdS[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_CMS_COUNT_S_0 + i, m_stcCmsCountS[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_CMS_COUNT_T_0 + i, m_stcTrayCountS[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_STC_ELEVATOR_STS_0 + i, m_stcElevtorSts[i]);
	DDX_Control(pDX, IDC_IMG_EQUIPMENT, m_imgEquipment);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_LED_EQUIP_OPTION_0 + i, m_ledEquipOption[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_VISION_STATUS_0 + i, m_ledVisionSts[i]);
	DDX_Control(pDX, IDC_STC_EQUIP_TYPE, m_stcEquipType);
	for (int i = 0; i < 17; i++) DDX_Control(pDX, IDC_STC_TRAY_NO_0 + i, m_stcJobLotID[i]);
	for (int i = 0; i < 17; i++) DDX_Control(pDX, IDC_STC_LINE_NO_0 + i, m_stcJobCarNo[i]);
	DDX_Control(pDX, IDC_RDO_WORK_START, m_rdoWorkStart);
	DDX_Control(pDX, IDC_RDO_WORK_STOP, m_rdoWorkStop);
	DDX_Control(pDX, IDC_LED_INIT_COMPLETE, m_ledInitComplete);
	DDX_Control(pDX, IDC_CHK_CYCLE_STOP, m_chkCycleStop);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_PIC_TRAY_BACK_0 + i, m_picTrayBack[i]);
	DDX_Control(pDX, IDC_STC_ALIGN_TRAY_COUNT, m_stcAlignLine);
	DDX_Control(pDX, IDC_STC_NG_TRAY_COUNT, m_stcCarrierLine);
	DDX_Control(pDX, IDC_STC_CAP_TRAY_COUNT, m_stcNGLine);
	DDX_Control(pDX, IDC_STC_SHIP_TRAY_COUNT, m_stcGoodLine);
	DDX_Control(pDX, IDC_GRD_ALIGN_TRAY, m_grdAlign);
	DDX_Control(pDX, IDC_GRD_NG_TRAY, m_grdCarrier);
	DDX_Control(pDX, IDC_GRD_CAP_TRAY, m_grdNGTray);
	DDX_Control(pDX, IDC_GRD_SHIP_TRAY, m_grdGoodTray);
	DDX_Control(pDX, IDC_GRD_JOB_LIST, m_grdJob);
	for (int i = 0; i <24; i++) DDX_Control(pDX, IDC_STC_WORK_CASE_0 + i, m_stcWorkCase[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_LOAD_PICKER1_0 + i, m_ledLoadPicker1[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_LOAD_PICKER2_0 + i, m_ledLoadPicker2[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_LOAD_VISION1_0 + i, m_ledVision1[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_LOAD_VISION2_0 + i, m_ledVision2[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_LOAD_VISION3_0 + i, m_ledVision3[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_LOAD_VISION4_0 + i, m_ledVision4[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_UNLOAD_PICKER1_0 + i, m_ledUnloadPicker1[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_UNLOAD_PICKER2_0 + i, m_ledUnloadPicker2[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ELEVATOR_INFOR_0 + i, m_stcStageInfor[i]);
	for (int i = 0; i <15; i++) DDX_Control(pDX, IDC_LED_TRAY_CHECK_0 + i, m_ledTrayCheck[i]);

	DDX_Control(pDX, IDC_LBL_OPER_ID, m_lblOperId);
	DDX_Control(pDX, IDC_STC_OPER_ID, m_stcOperId);
	DDX_Control(pDX, IDC_STC_MES_CONNECT, m_stcMesConnect);
	DDX_Control(pDX, IDC_STC_MES_ONLINE, m_stcMesOnline);
	DDX_Control(pDX, IDC_BTN_NGLOT_END, m_btnNGLotEnd);
}

BEGIN_MESSAGE_MAP(CWorkDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOTS_ID_S_0, IDC_STC_LOTS_ID_S_5, OnStcLotsIdSClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_CMS_COUNT_S_0, IDC_STC_CMS_COUNT_S_5, OnStcCmsCountSClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_CMS_COUNT_T_0, IDC_STC_CMS_COUNT_T_5, OnStcTrayCountSClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_RDO_SELECT_NO_0, IDC_RDO_SELECT_NO_5, OnBnClickedRdoSlectNo)
	ON_BN_CLICKED(IDC_RDO_WORK_START, &CWorkDlg::OnBnClickedRdoWorkStart)
	ON_BN_CLICKED(IDC_RDO_WORK_STOP, &CWorkDlg::OnBnClickedRdoWorkStop)
	ON_BN_CLICKED(IDC_CHK_CYCLE_STOP, &CWorkDlg::OnBnClickedChkCycleStop)
	ON_MESSAGE(UM_UPDATE_MODEL, &CWorkDlg::OnUpdateModel)
	ON_MESSAGE(UM_UPDATE_TRAY_INFO, &CWorkDlg::OnUpdateTrayInfo)
	ON_MESSAGE(UM_UPDATE_BARCODE, &CWorkDlg::OnUpdateBarcode)
	ON_MESSAGE(UM_RESET_CYCLE_STOP, &CWorkDlg::OnResetCycleStop)
	ON_MESSAGE(UM_UPDATE_UPH, &CWorkDlg::OnUpdateUph)
	ON_MESSAGE(UM_JOB_COMPELTE, &CWorkDlg::OnJobComplete)
	ON_MESSAGE(UM_LOT_END_MSG, &CWorkDlg::OnShowLotEndMsg)
	ON_BN_CLICKED(IDC_BUTTON1, &CWorkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWorkDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BTN_BUZZER_OFF, &CWorkDlg::OnBnClickedBtnBuzzerOff)
	ON_BN_CLICKED(IDC_BTN_LOT_CANCEL, &CWorkDlg::OnBnClickedBtnLotCancel)

	ON_BN_CLICKED(IDC_BTN_MES_CONNECT, &CWorkDlg::OnBnClickedBtnMesConnect)
	ON_BN_CLICKED(IDC_BTN_MES_DISCONNECT, &CWorkDlg::OnBnClickedBtnMesDisconnect)
	ON_BN_CLICKED(IDC_BTN_MES_ONLINE, &CWorkDlg::OnBnClickedBtnMesOnline)
	ON_BN_CLICKED(IDC_BTN_MES_OFFLINE, &CWorkDlg::OnBnClickedBtnMesOffline)
	ON_STN_CLICKED(IDC_STC_OPER_ID, &CWorkDlg::OnStnClickedOperId)
	ON_BN_CLICKED(IDC_BTN_MES_ABORT, &CWorkDlg::OnBnClickedBtnMesAbort)
	ON_BN_CLICKED(IDC_BTN_IDLE_REPORT, &CWorkDlg::OnBnClickedBtnIdleReport)
	ON_BN_CLICKED(IDC_BTN_NGLOT_END, &CWorkDlg::OnBnClickedBtnNGLotEnd)

END_MESSAGE_MAP()

// CWorkDlg 메시지 처리기입니다.

BOOL CWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 75, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_bAutoRunning = FALSE;
	m_bShowWindow = TRUE;

	ReadJobList();

#ifdef RESULT_TEST
	gData.bResultTest = TRUE;
#else
	gData.bResultTest = FALSE;
#endif

	m_rdoWorkStop.SetCheck(TRUE);
	m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CWorkDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CWorkDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	KillTimer(0);

	SaveJobList();
}

void CWorkDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

		m_bmpEquipment.DeleteObject();
		if		(gData.bUseDryRun)			m_bmpEquipment.LoadBitmap(IDB_EQUIP_DOOR);
		else if (!pEquipData->bUseDoorLock) m_bmpEquipment.LoadBitmap(IDB_EQUIP_DOOR_KOR);
		else								m_bmpEquipment.LoadBitmap(IDB_EQUIP_WORK);
		m_imgEquipment.SetBitmap(m_bmpEquipment);

//		if (gData.bUseDryRun)				m_stcEquipType.SetWindowText("Dry Run Mode");
//		else if (!pEquipData->bUseDoorLock)	m_stcEquipType.SetWindowText("Door Unlock");
//		else								m_stcEquipType.SetWindowText("Run Mode");
		if (pEquipData->bUseROS) m_stcEquipType.ShowWindow(TRUE);
		else					 m_stcEquipType.ShowWindow(FALSE);

 		m_ledEquipOption[0].Set_On(pEquipData->bUseBottom);
		m_ledEquipOption[1].Set_On(pEquipData->bUseTop1);
		m_ledEquipOption[2].Set_On(pEquipData->bUseTop2);
		m_ledEquipOption[3].Set_On(pEquipData->bUseROS);
		m_ledEquipOption[4].Set_On(pEquipData->bUseAlign1);
//		m_ledEquipOption[5].Set_On(pEquipData->bUseAlign2);
		m_ledEquipOption[5].Set_On(pEquipData->bUseCosmeticNG);
		m_ledEquipOption[6].Set_On(pEquipData->bUseMES);
		m_ledEquipOption[7].Set_On(pEquipData->bUseBotAng);
		m_ledEquipOption[8].Set_On(pEquipData->bUseTopAng);
		g_objCommon.Locking_MainDoor(TRUE);

		m_bShowWindow = TRUE;
		OnBnClickedRdoSlectNo(gData.nSelectNo);
		m_bShowWindow = FALSE; 

//		m_nWorkEleatorCase1 = m_nWorkEleatorCase2 = m_nWorkEleatorCase3 = m_nWorkEleatorCase4 = m_nWorkEleatorCase5 = m_nWorkEleatorCase6 = m_nWorkEleatorCase7 = 0;
//		for(int i=0; i<10; i++) gData.nElevatorOpen[i] = 0;

		m_tWorkElevatorLoop1.Set_LoopTime(1000);
		m_tWorkElevatorLoop2.Set_LoopTime(1000);	
		m_tWorkElevatorLoop3.Set_LoopTime(1000);	
		m_tWorkElevatorLoop4.Set_LoopTime(1000);	
		m_tWorkElevatorLoop5.Set_LoopTime(1000);	
		m_tWorkElevatorLoop6.Set_LoopTime(1000);
		m_tWorkElevatorLoop7.Set_LoopTime(1000);
		Begin_ElevatorRunThread();

		m_stcOperId.SetWindowText(gData.sOperID);

		SetTimer(0, 100, NULL);
	} else {
		End_ElevatorRunThread();
/*
		if (m_nWorkEleatorCase1 > 0) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_1, 51);
		if (m_nWorkEleatorCase2 > 0) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_2, 51);
		if (m_nWorkEleatorCase3 > 0) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_3, 51);
		if (m_nWorkEleatorCase4 > 0) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_4, 51);
		if (m_nWorkEleatorCase5 > 0) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_5, 51);
		if (m_nWorkEleatorCase6 > 0) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_6, 51);
		if (m_nWorkEleatorCase7 > 0) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_7, 51);

		DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
		pDY13->oElevator1Lamp = FALSE;
		pDY13->oElevator2Lamp = FALSE;
		pDY13->oElevator3Lamp = FALSE;
		pDY13->oElevator4Lamp = FALSE;
		pDY13->oElevator5Lamp = FALSE;
		pDY13->oElevator6Lamp = FALSE;
		pDY13->oElevator7Lamp = FALSE;
		g_objAJinAXL.Write_Output(13);
*/
		KillTimer(0);
	}
}

void CWorkDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	DX_DATA_13 *pDX13 = g_objAJinAXL.Get_pDX13();
	if (pDX13->iStartSw && !m_rdoWorkStart.GetCheck()) {
		g_objLogFile.Save_HandlerLog("[Work Mode] START S/W push");
		m_rdoWorkStart.SetCheck(TRUE);
		g_objLogFile.Save_EfficiencyLog("", "Run", "Elevator", 903, "Run Start");
	} else if (pDX13->iStopSw && !m_rdoWorkStop.GetCheck()) {
		g_objLogFile.Save_HandlerLog("[Work Mode] STOP S/W push");
		m_rdoWorkStop.SetCheck(TRUE);
		pMainDlg->Set_MainState(STATE_INITEND);
		g_objLogFile.Save_EfficiencyLog("", "Stop", "Elevator", 903, "Stop Button Push");
	}
/*
	if (pDX13->iElevator1Sw) ElevatorOpen(1);
	if (pDX13->iElevator2Sw) ElevatorOpen(2);
	if (pDX13->iElevator3Sw) ElevatorOpen(3);
	if (pDX13->iElevator4Sw) ElevatorOpen(4);
	if (pDX13->iElevator5Sw) ElevatorOpen(5);
	if (pDX13->iElevator6Sw) ElevatorOpen(6);
	if (pDX13->iElevator7Sw) ElevatorOpen(7);
*/
	Display_Status();

	if (m_rdoWorkStart.GetCheck()) {
		if (!m_bAutoRunning) {		// First AutoRun
			if (!Work_Start()) { SetTimer(0, 100, NULL); m_rdoWorkStop.SetCheck(TRUE); return; }

			if (g_objSequenceInit.Get_InitComplete()) {
				m_bAutoRunning = TRUE;
				g_objCommon.Locking_MainDoor(TRUE, TRUE);
				pMainDlg->Enable_ModeButton(FALSE);
				if (gAlm.bBegin) Reset_AlarmLog();
				else {
					if (gLot.nRunPortNo > 0) gLot.dwStopTime[gLot.nRunPortNo-1] += (GetTickCount() - dwStopSTime);
				}
				pMainDlg->Set_MainState(STATE_RUN);

				g_objInspector.Set_StatusUpdate(INSPECTOR_ALL, 2);
				g_objDispatcher.Set_StatusUpdate(1);	// 0:Stop, 1:Run, 2:Error
				g_objSequenceMain.Begin_MainRunThread();

				pMainDlg->Set_EquipRunStart();
				g_objMesAgent.Set_EquipState(5);	//Run

			} else {
				g_objCommon.Show_Error(40);		// 초기화 완료 에러
			}

		} else {				// Auto Running
			if (!g_objSequenceMain.Is_MainThreadRun()) {
				g_objLogFile.Save_HandlerLog("[Work Mode] Auto STOP");
				pMainDlg->Set_MainState(STATE_INITEND);
			}
		}

	} else if (m_rdoWorkStop.GetCheck()) {
		if (m_bAutoRunning) {	// First AutoStop
			m_bAutoRunning = FALSE;

			g_objSequenceMain.End_MainRunThread();
			g_objCommon.Stop_Elevator();

			m_rdoWorkStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoWorkStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

			g_objDispatcher.Set_StatusUpdate(0);	// 0:Stop, 1:Run, 2:Error

			pMainDlg->Enable_ModeButton(TRUE);
			g_objCommon.Locking_MainDoor(FALSE);

			pMainDlg->Save_EquipRunTime();
			g_objCommon.Save_MotionPos();

		} else {				// Stop
			int nState = pMainDlg->Get_MainState();
			if (nState != STATE_ALARM && nState != STATE_EMER) g_objCommon.Check_MainEmgAir();
		}
	}

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CWorkDlg::OnStcLotsIdSClick(UINT nID)
{
	int ID = nID - IDC_STC_LOTS_ID_S_0;

	if (ID == 1 || ID == 2 || ID == 4 || ID == 5) {
		int		nNo;
		CString strTemp;
		if (ID == 1) nNo = 0;
		if (ID == 2) nNo = 1;
		if (ID == 4) nNo = 3;
		if (ID == 5) nNo = 4;
		m_stcLotsIdS[nNo].GetWindowText(strTemp);
		if (strTemp.GetLength() < 1) {
			AfxMessageBox(_T("상위 LotID부터 입력을 해야 합니다."));
			return;
		}
	}

	CString strKey, strNew, strMsg;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;
	if (strKey.Find("_") >= 0) {
		if (gData.nLanguage == 0) strMsg.Format("[%s] Lot ID ( _ ) 입력불가...", strKey);
		else					  strMsg.Format("[%s] Lot ID Unable to endter(_)...", strKey);
		g_objCommon.Show_MsgBox(1, strMsg);
		return;
	}

	m_stcLotsIdS[ID].SetWindowText(strKey);

	strNew.Format("[Work Mode] Lot ID Input(%d-%s)", ID, strKey);
	g_objLogFile.Save_HandlerLog(strNew);

	OnStcCmsCountSClick(IDC_STC_CMS_COUNT_S_0+ID);	//2018.9.11+
}

void CWorkDlg::OnStcCmsCountSClick(UINT nID)
{
	int ID = nID - IDC_STC_CMS_COUNT_S_0;
	CString strOld, strNew, strValue;
/*
	if (m_rdoWorkStart.GetCheck()) {
		if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "장비 Stop 상태에서 진행이 가능합니다.....");
		else					  g_objCommon.Show_MsgBox(1, "You can proceed with the equipment stopped.");
		return;
	}
*/
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseMES) {
		m_stcLotsIdS[ID].GetWindowText(strValue);
		if (strValue.GetLength() > 0 && (gMes.nLotStatus[ID] == 0 || gMes.nLotStatus[ID] == 9 || strValue != gLot.sLotID[ID])) {
			gLot.sLotID[ID] = strValue;
			g_objMesAgent.Set_LotStart(0, ID, gLot.sLotID[ID], gData.sRecipeName, gLot.nCmCount[ID]);
		}
		return;
	}

	m_stcCmsCountS[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	int nCmCnt = atoi(strNew);
	if (nCmCnt < 1 || nCmCnt > MAX_CM) {
		m_stcCmsCountS[ID].SetWindowText("");
		if (gData.nLanguage == 0) AfxMessageBox(_T("Lot당 CM수량은 640개이상 입력할수 없습니다.........."));
		else					  AfxMessageBox(_T("CM quantity per lot cannot be entered more than 640."));
		return;
	}
	strValue.Format("%d", nCmCnt);
	m_stcCmsCountS[ID].SetWindowText(strValue);

	int nTrayCnt = (nCmCnt / TRAY_MAX_CM) + 2;
	int nRenCnt  = nCmCnt % TRAY_MAX_CM;
	if (nRenCnt == 0) nTrayCnt--;
	strValue.Format("%d", nTrayCnt);
	m_stcTrayCountS[ID].SetWindowText(strValue);

	if (LotID_Check()==FALSE) { m_stcTrayCountS[ID].SetWindowText(""); m_stcTrayCountS[ID].SetWindowText(""); return; }
//	if (gMes.nLotStatus[ID] != 3) g_objMesAgent.Set_LotStart(0, ID, gLot.sLotID[ID], gData.sRecipeName, gLot.nCmCount[ID]);

	strNew.Format("[Work Mode] Module Count Input(%d-%d-%d-%s-%d-%d)", ID, nCmCnt, nTrayCnt, gLot.sLotID[ID], gLot.nCmCount[ID], gMes.nLotStatus[ID]);
	g_objLogFile.Save_HandlerLog(strNew);
}

void CWorkDlg::OnStcTrayCountSClick(UINT nID)
{
	int ID = nID - IDC_STC_CMS_COUNT_T_0;
	CString strOld, strNew, strValue;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseMES) return;

	m_stcCmsCountS[ID].GetWindowText(strOld);
	int nCmCnt = atoi(strOld);
	int nTrayGGCnt = (nCmCnt / TRAY_MAX_CM) + 2;
	int nRenCnt  = nCmCnt % TRAY_MAX_CM;
	if (nRenCnt == 0) nTrayGGCnt--;

	m_stcTrayCountS[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	int nTrayCnt = atoi(strNew);
	if (nTrayCnt < 2 || nTrayCnt > 17) {
		m_stcTrayCountS[ID].SetWindowText("");
		AfxMessageBox(_T("Lot당 Tray수량은 2~17개까지 입력할수 있습니다.........."));
		return;
	}
	if (nTrayCnt < nTrayGGCnt) {
		m_stcTrayCountS[ID].SetWindowText("");
		AfxMessageBox(_T("Lot Tray수량 입력 Error..."));
		return;
	}
	strValue.Format("%d", nTrayCnt);
	m_stcTrayCountS[ID].SetWindowText(strValue);

	if (LotID_Check()==FALSE) { m_stcTrayCountS[ID].SetWindowText(""); m_stcTrayCountS[ID].SetWindowText(""); return; }

	strNew.Format("[Work Mode] Tray Count Input(%d-%d-%d)", ID, nCmCnt, nTrayCnt);
	g_objLogFile.Save_HandlerLog(strNew);
}

void CWorkDlg::OnBnClickedRdoSlectNo(UINT nID)
{
	CString strTemp, strLog;
	int ID = nID - IDC_RDO_SELECT_NO_0;
	if (nID > 0 && nID < 7) ID = nID - 1;
/*
	if (m_rdoWorkStart.GetCheck()) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("장비 Stop 상태에서 진행이 가능합니다....."));
		else					  AfxMessageBox(_T("You can proceed with the equipment stopped."));
		m_rdoSlectNo[ID].SetCheck(FALSE);
		return;
	}
*/
	static int cnt[6] = {0, };
	static int time = GetTickCount();

	gData.nSelectNo = ID + 1;
	for (int i=0; i<6; i++) {
		if (i == ID) {
			m_rdoSlectNo[i].SetCheck(TRUE);
			if(m_bShowWindow==FALSE){
				if(GetTickCount()-time > 500){
					cnt[i] = 0;
					time = GetTickCount();
				}

				if(cnt[i] == 1){ /*
					if (g_objSequenceMain.Get_IsAutoRun()) {
						AfxMessageBox(_T("진행중인 Lot 완료후 다음 Lot 진행이 가능합니다."));
						m_rdoSlectNo[i].SetCheck(FALSE);
						m_bShowWindow = FALSE;
						return;
					}
					*/
					if (g_objCommon.Show_MsgBox(2, "Lot Data를 삭제 하시겠습니까?") != IDOK) return;

					m_stcLotsIdS[i].GetWindowText(strTemp);
					strLog.Format("[Work Mode] Lot Delete Click.. LotID[%s-%s] Count[%d] Sts[%d]", strTemp, gLot.sLotID[i], gLot.nCmCount[i], gMes.nLotStatus[i]);

					m_stcLotsIdS[i].SetWindowText("");
					m_stcCmsCountS[i].SetWindowText("");
					m_stcTrayCountS[i].SetWindowText("");

					//2018.11.13+ 자동모드 상태에서 LotID를 지우면서 밑의 변수들을 초기화 시켜주지 않아 투입 되면 안되는 Lot가 투입 된다.
					g_objCommon.Set_LotDataClear(i);
					/////////////////////////
					cnt[i] = 0;
					time = GetTickCount();

					g_objLogFile.Save_HandlerLog(strLog);
				} else {
					cnt[i]++;
					time = GetTickCount();
				}
			}

		} else m_rdoSlectNo[i].SetCheck(FALSE);
	}
}

void CWorkDlg::OnBnClickedRdoWorkStart()
{
	g_objLogFile.Save_EfficiencyLog("", "Run", "Elevator", 903, "Run Start");
	g_objLogFile.Save_HandlerLog("[Work Mode] START button push");
}

void CWorkDlg::OnBnClickedRdoWorkStop()
{
	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Set_MainState(STATE_INITEND);
	dwStopSTime = GetTickCount();
	g_objMesAgent.Set_EquipState(6);	//Pause

	g_objLogFile.Save_EfficiencyLog("", "Stop", "Elevator", 903, "Stop Button Push");
	g_objLogFile.Save_HandlerLog("[Work Mode] STOP button push");
}

void CWorkDlg::OnBnClickedChkCycleStop()
{
	if (m_rdoWorkStart.GetCheck()) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("장비 Stop 상태에서 진행이 가능합니다....."));
		else					  AfxMessageBox(_T("You can proceed with the equipment stopped."));
		m_chkCycleStop.SetCheck(FALSE);
		return;
	}

	if (m_chkCycleStop.GetCheck()) {
		m_chkCycleStop.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
		if (g_objCommon.Show_MsgBox(2, "Are you sure you want to Cycle Stop?") == IDOK) {
			gData.bCycleStop = TRUE;
			g_objLogFile.Save_HandlerLog("[Work Mode] OnBnClickedChkCycleStop = TRUE");
		} else {
			m_chkCycleStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xF0));
			m_chkCycleStop.SetCheck(FALSE);
		}
	} else {
		m_chkCycleStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xF0));
		gData.bCycleStop = FALSE;
		g_objLogFile.Save_HandlerLog("[Work Mode] OnBnClickedChkCycleStop = FALSE");
	}
}

//------------------MES------------------------------------------------------------//
void CWorkDlg::Set_LotCount(int nPortNo, CString sLotID, int nCount)
{
	CString sLog, strValue;

	strValue.Format("%d", nCount);
	m_stcCmsCountS[nPortNo-1].SetWindowText(strValue);

	int nTrayCnt = (nCount / TRAY_MAX_CM) + 2;
	int nRenCnt  = nCount % TRAY_MAX_CM;
	if (nRenCnt == 0) nTrayCnt--;
	strValue.Format("%d", nTrayCnt);
	m_stcTrayCountS[nPortNo-1].SetWindowText(strValue);

	if (LotID_Check()==FALSE) {
		sLog.Format("[Work Dialog] MES Lot Error. PortNo[%d] Lotid[%s] Count[%d] TaryCnt[%d]", nPortNo, sLotID, nCount, nTrayCnt);
		g_objLogFile.Save_HandlerLog(sLog);
		return;
	}

	sLog.Format("[Work Dialog] MES Lot Count. PortNo[%d] Lotid[%s] Count[%d] TaryCnt[%d]", nPortNo, sLotID, nCount, nTrayCnt);
	g_objLogFile.Save_HandlerLog(sLog);
}

void CWorkDlg::OnStnClickedOperId()
{
	CString strKey, sLog;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;

	m_stcOperId.SetWindowText(strKey);
	gData.sOperID = strKey;
	g_objMesAgent.Set_OperUpdate(gData.sOperID);
	g_dlgOperator.m_stcOperOperId.SetWindowText(strKey);

	sLog.Format("[Work Dialog] Oper ID Button Click. [%s]", gData.sOperID);
	g_objLogFile.Save_HandlerLog(sLog);
}

void CWorkDlg::OnBnClickedBtnMesConnect()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	g_objMesAgent.Initialize();
	g_objLogFile.Save_HandlerLog("[Work Dialog] MES Connect Button Click.");
}

void CWorkDlg::OnBnClickedBtnMesDisconnect()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	g_objMesAgent.Terminate();
	g_objLogFile.Save_HandlerLog("[Work Dialog] MES Disconnect Button Click.");
}

void CWorkDlg::OnBnClickedBtnMesOnline()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) return;

	g_objMesAgent.Set_ControlState(1, gData.sOperID);

	g_objLogFile.Save_HandlerLog("[Work Dialog] MES Online Button Click.");
}

void CWorkDlg::OnBnClickedBtnMesOffline()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	g_objMesAgent.Set_ControlState(2, gData.sOperID);

	g_objLogFile.Save_HandlerLog("[Work Dialog] MES Offline Button Click.");
}

void CWorkDlg::OnBnClickedBtnMesAbort()
{
	if (gData.sOperID.GetLength() < 4) { AfxMessageBox("Input the Operator ID....."); return; }

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) return;

	if (!g_objMesAgent.Is_Connected()) { AfxMessageBox("MES Disconnect 상태에서는 처리를 할수 없습니다."); return; }
	if (!g_objMesAgent.Is_HostOnline()) { AfxMessageBox("MES Offline 상태에서는 처리를 할수 없습니다."); return; }
	if (gData.nSelectNo < 1 || gData.nSelectNo > 6) { AfxMessageBox("Abort Lot을 먼저 선택해 주세요."); return; }
	if (!m_rdoWorkStop.GetCheck()) { AfxMessageBox("장비 Stop상태에서 Abort처리 하세요."); return; }
	if (gMes.nLotStatus[gData.nSelectNo-1] == 0) { AfxMessageBox("진행중인 Lot만 Abort처리가 가능합니다."); return; }

	CString sData;
	sData.Format("Are you want to cancel this Port[%d] Lot[%s]?", gData.nSelectNo, gLot.sLotID[gData.nSelectNo-1]);
	if (g_objCommon.Show_MsgBox(2, sData) != IDOK) return;

	gMes.nLotStatus[gData.nSelectNo-1] = 0;
	g_objMesAgent.Set_LotAbort(gLot.sLotID[gData.nSelectNo-1]);

	int nCase1 = g_objSequenceMain.Get_MainRunCase(AUTO_TRANSFER_1);
	if (nCase1 == 7) g_objSequenceMain.Set_MainRunCase(AUTO_TRANSFER_1, 0);

	m_stcLotsIdS[gData.nSelectNo-1].SetWindowText("");
	m_stcCmsCountS[gData.nSelectNo-1].SetWindowText("");
	m_stcTrayCountS[gData.nSelectNo-1].SetWindowText("");
	g_objCommon.Set_LotDataClear(gData.nSelectNo-1);

	sData.Format("[Work Dialog] MES Abort Button Click. PortNo[%d] LotID[%s]", gData.nSelectNo, gLot.sLotID[gData.nSelectNo-1]);
	g_objLogFile.Save_HandlerLog(sData);
}

void CWorkDlg::OnBnClickedBtnIdleReport()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) return;

	if (g_dlgNoWork.IsWindowVisible()) g_dlgNoWork.ShowWindow(SW_HIDE);
	else g_dlgNoWork.ShowWindow(SW_SHOW);	
}
//------------------MES------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////////
// User Functions

BOOL CWorkDlg::Work_Start()
{
	CString strTemp, strTemp2, sText, strMsg;

	g_objCommon.Locking_Slide(TRUE, 0);
	if (gData.bAlarmShow) {
		g_objCommon.Show_MsgBox(1, "Alaram 화면을 Close하고 Run 진행하세요.....");
		m_rdoWorkStop.SetCheck(TRUE);
		return FALSE;
	}

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseDoorLock==FALSE) {
		sText.Format("Door lock 해제 상태입니다.  진행하시겠습니까?");
		if (g_objCommon.Show_MsgBox(2, sText) != IDOK){
			m_rdoWorkStop.SetCheck(TRUE);
			return FALSE;
		}
	}
	if(gData.bUseDryRun) {
		sText.Format("Dry Run으로 설정되어 있습니다.\nDry Run으로 START 하시겠습니까?");
		if (g_objCommon.Show_MsgBox(2, sText) != IDOK){
			m_rdoWorkStop.SetCheck(TRUE);
			return FALSE;
		}
	}
#ifdef NEW_FINAL
	if (pEquipData->bUseBottom==FALSE || pEquipData->bUseTop1==FALSE || pEquipData->bUseTop2==FALSE || pEquipData->bUseBotAng==FALSE) {
#else
	if (pEquipData->bUseBottom==FALSE || pEquipData->bUseTop1==FALSE || pEquipData->bUseTop2==FALSE || pEquipData->bUseBotAng==FALSE || pEquipData->bUseTopAng==FALSE) {
#endif
		sText.Format("Vision Inspection을 사용하지 않고 START 하시겠습니까?");
		if (g_objCommon.Show_MsgBox(2, sText) != IDOK){
			m_rdoWorkStop.SetCheck(TRUE);
			return FALSE;
		}
	}
	if (pEquipData->bUseROS==FALSE) {
		sText.Format("ROS를 사용하지 않고 START 하시겠습니까?");
		if (g_objCommon.Show_MsgBox(2, sText) != IDOK){
			m_rdoWorkStop.SetCheck(TRUE);
			return FALSE;
		}
	} else {
		ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
		if (pRosData->lstMdjIp.GetCount() < 1) {
			g_objCommon.Show_MsgBox(1, "이 설비와 연결되 MDJ(ROS)가 없습니다. 확인후 Run 진행하세요.....");
			m_rdoWorkStop.SetCheck(TRUE);
			return FALSE;
		}
	}
	if (gAlm.dMotionChkPos < 0.01) {
		sText.Format("Motion Interlock 해제 상태입니다.\n그대로 START 하시겠습니까?");
		if (g_objCommon.Show_MsgBox(2, sText) != IDOK){
			m_rdoWorkStop.SetCheck(TRUE);
			return FALSE;
		}
	}
	if (gData.bUseBarSort) {
		if (gBar.nCount < 1) {
			m_rdoWorkStop.SetCheck(TRUE);
			strMsg.Format("EquipData 화면에서 Barcode Sort 사용으로 저장후, Lot 시작해 주세요.");
			g_objCommon.Show_MsgBox(1, strMsg);
			return FALSE;
		}
		sText.Format("Barcode Sorting 기능을 사용하여 Run을 START 하시겠습니까?");
		if (g_objCommon.Show_MsgBox(2, sText) != IDOK){
			m_rdoWorkStop.SetCheck(TRUE);
			return FALSE;
		}
	}

	for (int i=1; i<8; i++) {
		if (gData.nElevatorOpen[i] > 0) {
			m_rdoWorkStop.SetCheck(TRUE);
			strMsg.Format("Elevator %d Door 버턴을 눌러 주시고, Lot 시작해 주세요......", i);
			g_objCommon.Show_MsgBox(1, strMsg);
			return FALSE;
		}
	}

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	int nState = gData.m_nMS;
	if (nState == STATE_ALARM || nState == STATE_EMER) {
		m_rdoWorkStop.SetCheck(TRUE);
		return FALSE;
	}

	if (!g_objCommon.Check_MainDoor()) {
		m_rdoWorkStop.SetCheck(TRUE);
		return FALSE;
	}
	if (!g_objCommon.Check_TraySlide(9)) {
		m_rdoWorkStop.SetCheck(TRUE);
		return FALSE;
	}
	if (!g_objCommon.Check_SlideLock()) {
		if (gData.nLanguage == 0) sText.Format("Slide Lock 하시고 진행해 주세요.");
		else					  sText.Format("Slide lock and proceed.");
		g_objCommon.Show_MsgBox(1, sText);
		m_rdoWorkStop.SetCheck(TRUE);
		return FALSE;
	}

	int nMotionNo = g_objCommon.Check_MotionPos();
	if (nMotionNo < 99) {
		double dCurrentPos = g_objAJinAXL.Get_Position(nMotionNo);
		CString strName = g_objAJinAXL.Get_AxisName(nMotionNo);
		if (gData.nLanguage == 0) sText.Format("Motion(%s) 위치를 Check 하세요.\n이전위치(%0.3lf) != 현재위치(%0.3lf)", strName, gAlm.dMotionPos[nMotionNo], dCurrentPos);
		else					  sText.Format("Motion(%s) Check Position. => Pre-Position(%0.3lf) != Current-Position(%0.3lf)", strName, gAlm.dMotionPos[nMotionNo], dCurrentPos);
		g_objLogFile.Save_HandlerLog(sText);

		g_objCommon.Show_MsgBox(1, sText);
		m_rdoWorkStop.SetCheck(TRUE);
		return FALSE;
	}
	if (g_objCommon.Check_StageUpDown(sText)==FALSE) {
		g_objLogFile.Save_HandlerLog(sText);
		g_objCommon.Show_MsgBox(1, sText);
		m_rdoWorkStop.SetCheck(TRUE);
		return FALSE;
	}

	if (gData.sOperID.GetLength() < 1) {
		g_objCommon.Show_MsgBox(1, "Input Operator ID");
		return FALSE;
	}

	if (!pEquipData->bUseCosmeticNG && pEquipData->bUseNGSort) {
		if (g_objDataManager.Read_NGTraySort()==FALSE) {
			m_rdoWorkStop.SetCheck(TRUE);
			return FALSE;
		}
	}

	if (gLot.nJobStatus == 0) {
		if (pEquipData->bUseMES) { if (LotID_MESCheck() == FALSE) return FALSE; }
		if (LotID_Check() == FALSE) return FALSE;
	}
/*
	if (pEquipData->bUseMES && gMes.nLotPortNo > 0 && gMes.nLotPortNo < 7 && gMes.nLotStatus[gMes.nLotPortNo-1] == 1) {
		if (gLot.nCmCount[gMes.nLotPortNo-1] == gMes.nHostRcvCmCount) gMes.nLotStatus[gMes.nLotPortNo-1] = 2;
		else {
			sText.Format("MES Module 수량(%d)과 같아야 Lot 진행이 가능합니다.", gMes.nHostRcvCmCount);
			g_objLogFile.Save_HandlerLog(sText);
			g_objCommon.Show_MsgBox(1, sText);
			return FALSE;
		}
	}
*/
	if (pEquipData->bUseInspectBlow) {
		DY_DATA_04 *pDY04 = g_objAJinAXL.Get_pDY04();
		pDY04->oBTMIonizerOn = TRUE;
		pDY04->oBTMIonizerBlow = TRUE;
		pDY04->oBTMSuctionOn = TRUE;

		pDY04->oTOPIonizerOn = TRUE;
		pDY04->oTOPIonizerBlow = TRUE;
		pDY04->oTOPSuctionOn = TRUE;
		g_objAJinAXL.Write_Output(4);
	}

	// Job처음 Start시 Check
//	if (g_objSequenceMain.Get_IsAutoRun()) return TRUE;	// Auto Run이면 스킵 gjc
	if (gLot.nJobStatus > 0) return TRUE;

	for (int i=0; i<6; i++) {
		gLot.sRstLotID[i]   = "";
		gLot.nRstCmCount[i] = gLot.nRstGoodCount[i] = gLot.nRstNgCount[i] = 0;
		gLot.nUnlGdTrayCount[i] = gLot.nUnlNGTrayCount[i] = 0;
	}
	for (int i=0; i<6; i++) {
		if (gLot.nCmCount[i] > 0) { 
			gData.sLotID_Start = gLot.sLotID[i];
			gData.nTotLotNo[i] = gData.nStdLotNo + 1;
			break;
		}
	}

#ifdef AJIN_BOARD_USE
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if (gLot.nCmCount[0] > 0 || gLot.nCmCount[1] > 0 || gLot.nCmCount[2] > 0) {
		if (pDX00->iElevator1TrayExist == FALSE) {
			strMsg.Format("Elevator Load 1에 Tray를 넣어 주세요..........");
			g_objCommon.Show_MsgBox(1, strMsg);
			return FALSE;
		}
	}
	if (gLot.nCmCount[3] > 0 || gLot.nCmCount[4] > 0 || gLot.nCmCount[5] > 0) {
		if (pDX00->iElevator2TrayExist == FALSE) {
			strMsg.Format("Elevator Load 2에 Tray를 넣어 주세요..........");
			g_objCommon.Show_MsgBox(1, strMsg);
			return FALSE;
		}
	}
	if (pDX00->iElevator1TrayExist) {
		if (gLot.nCmCount[0] < 1) {
			strMsg.Format("Elevator Load 1에 정보와 실물이 맞지 않습니다.......");
			g_objCommon.Show_MsgBox(1, strMsg);
			return FALSE;
		}
	}
	if (pDX00->iElevator2TrayExist) {
		if (gLot.nCmCount[3] < 1) {
			strMsg.Format("Elevator Load 2에 정보와 실물이 맞지 않습니다.......");
			g_objCommon.Show_MsgBox(1, strMsg);
			return FALSE;
		}
	}

	if (!pDX01->iElevator3TrayExist) {
		m_rdoWorkStop.SetCheck(TRUE);
		g_objCommon.Show_MsgBox(1, "Elevator Empty NG에 Tray가 없습니다. 확인해 주세요.");	return FALSE;
	}
	if (!pDX01->iElevator4TrayExist) {
		m_rdoWorkStop.SetCheck(TRUE);
		g_objCommon.Show_MsgBox(1, "Elevator Empty Good에 Tray가 없습니다. 확인해 주세요.");	return FALSE;
	}
	if (pDX02->iElevator5TrayExist) {
		m_rdoWorkStop.SetCheck(TRUE);
		g_objCommon.Show_MsgBox(1, "Elevator Buffer NG에 Tray가 있습니다.. 비워주세요..");	return FALSE;
	}
	if (pDX02->iElevator6TrayExist) {
		m_rdoWorkStop.SetCheck(TRUE);
		g_objCommon.Show_MsgBox(1, "Elevator Good1 배출부에 Tray가 있습니다.. 비워주세요..");	return FALSE;
	}
	if (pDX02->iElevator7TrayExist) {
		m_rdoWorkStop.SetCheck(TRUE);
		g_objCommon.Show_MsgBox(1, "Elevator Good2 배출부에 Tray가 있습니다.. 비워주세요..");	return FALSE;
	}
#endif

	gLot.nJobStatus = 1;
	g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_1, 51);
	g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_2, 51);
	g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_3, 51);
	g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_4, 51);
	g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_5, 51);
	g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_6, 51);
	g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_7, 51);
	for(int i=0; i<3; i++) for(int j=0; j<2; j++) gNG->nTrayOX[i][j] = 0;

	return TRUE;
}

BOOL CWorkDlg::LotID_Check()
{
	int nCMCnt, nTrayCnt, nRenCnt, nLotCnt;
	CString strMsg, strTemp, strTemp2, strTemp3;

	BOOL bElevatorRun = FALSE;
	int *pCase = g_objSequenceMain.Get_pMainRunCase();
	for (int i = 0; i < 7; i++) {
		if (*(pCase + i) != 0 && *(pCase + i) != 20 && *(pCase + i) != 51) {
			bElevatorRun = TRUE; break;
		}
	}

	nLotCnt = 0;
	for(int i=0; i<6; i++) {
		m_stcLotsIdS[i].GetWindowText(strTemp);
		m_stcCmsCountS[i].GetWindowText(strTemp2);
		m_stcTrayCountS[i].GetWindowText(strTemp3);
		nCMCnt   = atoi(strTemp2);
		nTrayCnt = atoi(strTemp3);

		// Input Error Check
		if (nCMCnt > 0) {
			if (strTemp.GetLength() < 1) {
				if (gData.nLanguage == 0) strMsg.Format("[%d] Check Lot ID, 수량 ....................", i+1);
				else					  strMsg.Format("[%d] Check Lot ID, Quantity ....................", i+1);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}
			if (nTrayCnt < 2) {
				if (gData.nLanguage == 0) strMsg.Format("[%d] Check Lot ID, Tray 수량 ....................", i+1);
				else					  strMsg.Format("[%d] Check Lot ID, Tray Quantity ....................", i+1);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}
		} else {
			if (strTemp.GetLength() > 0) {
				if (gData.nLanguage == 0) strMsg.Format("[%d] Check Lot ID, 수량 ....................", i+1);
				else					  strMsg.Format("[%d] Check Lot ID, Quantity ....................", i+1);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}
			if (nTrayCnt > 0 ) {
				if (gData.nLanguage == 0) strMsg.Format("[%d] Check Lot ID, Tray 수량 ....................", i+1);
				else					  strMsg.Format("[%d] Check Lot ID, Tray Quantity ....................", i+1);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}
		}

		if (nCMCnt > 0) {
			gLot.sLotID[i] = strTemp;
			gLot.nCmCount[i] = nCMCnt;
			gLot.nTrayCount[i] = nTrayCnt;
			nLotCnt++;
			if (gLot.nLotStatus[i] == 3) gLot.bEmptyTray[i] = gLot.bEmptyNGTray[i] = FALSE;

			nRenCnt  = nCMCnt % TRAY_MAX_CM;
			if (nRenCnt > 0) gLot.nLastCount[i] = nRenCnt;
			else			 gLot.nLastCount[i] = TRAY_MAX_CM;

		} else {
			gLot.nCmCount[i] = gLot.nTrayCount[i] = gLot.nGoodCount[i] = gLot.nNgCount[i] = gLot.nLotStatus[i] = gLot.nSkipCount[i] = 0;
			gLot.sLotID[i] = "";
		}
	}
	if (nLotCnt < 1 && bElevatorRun == FALSE) {
		g_objCommon.Show_MsgBox(1, "Lot 정보를 입력해야 합니다.....");
		return FALSE;
	}

	for(int i=0; i<6; i++) {
		for(int j=0; j<6; j++) {
			if (i != j && gLot.sLotID[i].GetLength() > 0 && gLot.sLotID[i] == gLot.sLotID[j]) {
				gLot.nCmCount[j] = 0;
				if (gData.nLanguage == 0) strMsg.Format("[%d-%d]에 동일 Lot ID가 있습니다........", i+1, j+1);
				else					  strMsg.Format("[%d-%d] has the same Lot ID........", i+1, j+1);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CWorkDlg::LotID_MESCheck()
{
	CString strMsg, sLotID[6], sCMCount, sTyCount;

	for(int i=0; i<6; i++) m_stcLotsIdS[i].GetWindowText(sLotID[i]);
	for(int i=0; i<6; i++) {
		for(int j=0; j<6; j++) {
			if (i != j && sLotID[i].GetLength() > 0 && sLotID[i] == sLotID[j]) {
				if (gData.nLanguage == 0) strMsg.Format("[%d-%d]에 동일 Lot ID가 있습니다........", i+1, j+1);
				else					  strMsg.Format("[%d-%d] has the same Lot ID........", i+1, j+1);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}
		}
	}

	for(int i=0; i<6; i++) { 
		if (sLotID[i].GetLength() > 0) {
			m_stcCmsCountS[i].GetWindowText(sCMCount);
			m_stcTrayCountS[i].GetWindowText(sTyCount);

			int nCMCount = atoi(sCMCount);
			int nTyCount = atoi(sTyCount);
			if (nCMCount < 1) {
				strMsg.Format("Port(%d) LotID(%s)의 MES 수량정보 수신후 진행가능합니다.", i+1, sLotID[i]);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}
			if (nCMCount < 1 || nCMCount > MAX_CM) {
				strMsg.Format("Port(%d) LotID(%s)의 모듈수량(%d)에 문제가 있습니다.", i+1, sLotID[i], nCMCount);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}
			if (nTyCount < 2 || nTyCount > 20) {
				strMsg.Format("Port(%d) LotID(%s)의 Tray수량(%d)에 문제가 있습니다.", i+1, sLotID[i], nTyCount);
				g_objCommon.Show_MsgBox(1, strMsg);
				return FALSE;
			}

			gLot.sLotID[i] = sLotID[i];
			gLot.nCmCount[i] = nCMCount;
			gLot.nTrayCount[i] = nTyCount;
		}
	}
	return TRUE;
}

void CWorkDlg::Initial_Controls() 
{
	for (int i = 0; i < 7; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 4; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x80));		// Tray
	for (int i = 0; i < 16; i++) m_lblLot[i].Init_Ctrl("바탕", 8, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x20, 0x80));		// Lot Run
	for (int i = 0; i < 6; i++) m_stcLotsIdS[i].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));
	for (int i = 0; i < 6; i++) m_stcCmsCountS[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));
	for (int i = 0; i < 6; i++) m_stcTrayCountS[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));
	for (int i = 0; i < 7; i++) m_stcElevtorSts[i].Init_Ctrl("바탕", 10, TRUE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));
	for (int i = 0; i < 6; i++) m_rdoSlectNo[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
//	m_bmpEquipment.LoadBitmap(IDB_EQUIP_WORK);
//	m_imgEquipment.SetBitmap(m_bmpEquipment);
	for (int i = 0; i < 9; i++) m_ledEquipOption[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++) m_ledVisionSts[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
//	m_stcEquipType.Init_Ctrl("Arial", 10, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	m_stcEquipType.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x66, 0xFF, 0xCC));
//	for (int i = 0; i < 17; i++) m_stcJobLotID[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xD0, 0xD0));
//	for (int i = 0; i < 17; i++) m_stcJobCarNo[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD0, 0xD0, 0xD0));
	for (int i = 0; i < 17; i++) m_stcJobLotID[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xD0, 0xFF));
	for (int i = 0; i < 17; i++) m_stcJobCarNo[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xFF));

	m_rdoWorkStart.Init_Ctrl("바탕", 20, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoWorkStop.Init_Ctrl("바탕", 20, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_ledInitComplete.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em24);
	m_chkCycleStop.Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_picTrayBack[i].Set_Color(COLOR_DEFAULT, RGB(0xF0, 0xF0, 0xC0));
	m_stcAlignLine.Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_stcCarrierLine.Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_stcNGLine.Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_stcGoodLine.Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	Initial_Grid(&m_grdAlign, TRAY_CM_Y, TRAY_CM_X);
	Initial_Grid(&m_grdCarrier, TRAY_CM_Y, TRAY_CM_X);
	Initial_Grid(&m_grdGoodTray, TRAY_CM_Y, TRAY_CM_X);
	Initial_Grid(&m_grdNGTray, TRAY_CM_Y, TRAY_CM_X);
	Initial_JobGrid(&m_grdJob, 10, 9);
	for (int i = 0; i < 24; i++) m_stcWorkCase[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));

	for (int i = 0; i < 8; i++) m_ledLoadPicker1[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);	//CLedCS::emBlue
	for (int i = 0; i < 8; i++) m_ledLoadPicker2[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 8; i++) m_ledVision1[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 8; i++) m_ledVision2[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 8; i++) m_ledVision3[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 8; i++) m_ledVision4[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 8; i++) m_ledUnloadPicker1[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 8; i++) m_ledUnloadPicker2[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 4; i++) m_stcStageInfor[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
	for (int i = 0; i <15; i++) m_ledTrayCheck[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	m_stcMesConnect.Init_Ctrl("바탕", 8, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_stcMesOnline.Init_Ctrl("바탕", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_lblOperId.Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x20, 0x80));
	m_stcOperId.Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, RGB(0xD0, 0xD0, 0xD0));
	m_btnNGLotEnd.Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
}

void CWorkDlg::Initial_Grid(CGridCS *pGrid, int nRows, int nCols)
{
	pGrid->Set_RowCount(nRows);
	pGrid->Set_ColCount(nCols);
	pGrid->Set_FixRowCount(0);
	pGrid->Set_FixColCount(0);

	long lTotalW = pGrid->Get_GridWidth();
	long lTotalH = pGrid->Get_GridHeight();
	long lCellW = lTotalW / nCols;
	long lCellH = lTotalH / nRows;

	int nNo=1;
	CString str;
	for (int i=0; i<nRows; i++) {
		pGrid->Set_RowHeight(i, lCellH);
		for (int j = nCols-1; j>=0; j--) {
			if(i==0) pGrid->Set_ColWidth(j, lCellW);
			str.Format(_T("%d"), nNo++);
			pGrid->Set_CellText(i, j, str);
		}
	}
/*
	for (int j = nCols-1; j>=0; j--) {
		pGrid->Set_ColWidth(j, lCellW);
		for (int i = nRows-1; i>=0; i--) {
			if(j==nCols-1) pGrid->Set_RowHeight(i, lCellH);
			str.Format(_T("%d"), nNo++);
			pGrid->Set_CellText(i, j, str);
		}
	}
*/
}

void CWorkDlg::Initial_JobGrid(CGridCS *pGrid, int nRows, int nCols)
{
	pGrid->Set_RowCount(nRows);
	pGrid->Set_ColCount(nCols);
	pGrid->Set_FixRowCount(0);
	pGrid->Set_FixColCount(0);

	long lTotalW = pGrid->Get_GridWidth();
	long lTotalH = pGrid->Get_GridHeight();
	long lCellW = lTotalW / nCols;
	long lCellH = lTotalH / nRows;
	long  lWidth[9]= {   50,      150,     70,    70,   70,   74,     160,         160,      100};
	CString sTxt[9]= { "PortNo","Lot_ID","Count","Good","NG","Rate","Start_Time","End_Time","Tack"};

	for (int i=0; i<nRows; i++) {
		pGrid->Set_RowHeight(i, lCellH);
		for (int j=0; j<nCols; j++) {
			if(i==0) {
				pGrid->Set_ColWidth(j, lWidth[j]);
				pGrid->Set_CellText(i, j, sTxt[j]);
				pGrid->Set_CellBackClr(i, j, RGB(0xF0, 0xF0, 0xC0));
			}
		}
	}
}

void CWorkDlg::Display_Status()
{
	CString strTemp, strText;

	if (g_objMesAgent.Is_Connected()) { m_stcMesConnect.Set_Text("Connected"); m_stcMesConnect.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00)); }
	else { m_stcMesConnect.Set_Text("Disconnected"); m_stcMesConnect.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00)); }

	if (g_objMesAgent.Is_HostOnline()) { m_stcMesOnline.Set_Text("Online"); m_stcMesOnline.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00)); }
	else { m_stcMesOnline.Set_Text("Offline"); m_stcMesOnline.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00)); }

	BOOL bInitComplete = g_objSequenceInit.Get_InitComplete();
	m_ledInitComplete.Set_On(bInitComplete);

	//Inspection Stage 1,2,3,4 위치 Display
	for (int i=0; i<4; i++) {
		if		(gData.nVisionPos[0][i] > 0 && gData.nVisionPos[1][i] > 0) strText.Format("%d,%d", gData.nVisionPos[1][i], gData.nVisionPos[0][i]);
		else if (gData.nVisionPos[0][i] > 0)							   strText.Format("%d", gData.nVisionPos[0][i]);
		else if (gData.nVisionPos[1][i] > 0)							   strText.Format("%d", gData.nVisionPos[1][i]);
		else															   strText = "";
		m_stcStageInfor[i].SetWindowText(strText);
	}
	strText.Format("ROS 대기수량: %d", gData.nROSReqCount);
	m_stcEquipType.SetWindowText(strText);

	//Elevator 1~7 상태 Display
	if		(gData.nElevatorOpen[1] == 0) { if (g_objCommon.Check_SlideLock(1)) m_stcElevtorSts[0].SetWindowText("Lock"); else  m_stcElevtorSts[0].SetWindowText("Unlock"); }
	else if (gData.nElevatorOpen[1] == 1) m_stcElevtorSts[0].SetWindowText("Open");
	else if (gData.nElevatorOpen[1] == 2) m_stcElevtorSts[0].SetWindowText("Opened");
	if		(gData.nElevatorOpen[2] == 0) { if (g_objCommon.Check_SlideLock(2)) m_stcElevtorSts[1].SetWindowText("Lock"); else  m_stcElevtorSts[1].SetWindowText("Unlock"); }
	else if (gData.nElevatorOpen[2] == 1) m_stcElevtorSts[1].SetWindowText("Open");
	else if (gData.nElevatorOpen[2] == 2) m_stcElevtorSts[1].SetWindowText("Opened");
	if		(gData.nElevatorOpen[3] == 0) { if (g_objCommon.Check_SlideLock(3)) m_stcElevtorSts[2].SetWindowText("Lock"); else  m_stcElevtorSts[2].SetWindowText("Unlock"); }
	else if (gData.nElevatorOpen[3] == 1) m_stcElevtorSts[2].SetWindowText("Open");
	else if (gData.nElevatorOpen[3] == 2) m_stcElevtorSts[2].SetWindowText("Opened");
	if		(gData.nElevatorOpen[4] == 0) { if (g_objCommon.Check_SlideLock(4)) m_stcElevtorSts[3].SetWindowText("Lock"); else  m_stcElevtorSts[3].SetWindowText("Unlock"); }
	else if (gData.nElevatorOpen[4] == 1) m_stcElevtorSts[3].SetWindowText("Open");
	else if (gData.nElevatorOpen[4] == 2) m_stcElevtorSts[3].SetWindowText("Opened");
	if		(gData.nElevatorOpen[5] == 0) { if (g_objCommon.Check_SlideLock(5)) m_stcElevtorSts[4].SetWindowText("Lock"); else  m_stcElevtorSts[4].SetWindowText("Unlock"); }
	else if (gData.nElevatorOpen[5] == 1) m_stcElevtorSts[4].SetWindowText("Open");
	else if (gData.nElevatorOpen[5] == 2) m_stcElevtorSts[4].SetWindowText("Opened");
	if		(gData.nElevatorOpen[6] == 0) { if (g_objCommon.Check_SlideLock(6)) m_stcElevtorSts[5].SetWindowText("Lock"); else  m_stcElevtorSts[5].SetWindowText("Unlock"); }
	else if (gData.nElevatorOpen[6] == 1) m_stcElevtorSts[5].SetWindowText("Open");
	else if (gData.nElevatorOpen[6] == 2) m_stcElevtorSts[5].SetWindowText("Opened");
	if		(gData.nElevatorOpen[7] == 0) { if (g_objCommon.Check_SlideLock(7)) m_stcElevtorSts[6].SetWindowText("Lock"); else  m_stcElevtorSts[6].SetWindowText("Unlock"); }
	else if (gData.nElevatorOpen[7] == 1) m_stcElevtorSts[6].SetWindowText("Open");
	else if (gData.nElevatorOpen[7] == 2) m_stcElevtorSts[6].SetWindowText("Opened");
	for (int i=0; i<7; i++) {
		if (gData.nElevatorOpen[i+1] == 2)	m_stcElevtorSts[i].Set_Color(COLOR_DEFAULT, RGB(0x00, 0xFF, 0x00));
		else								m_stcElevtorSts[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0xF0, 0xF0));
	}

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	if (pDX00->iElevator1SlideOpen || !pDX00->iElevator1SlideClose) m_stcElevtorSts[0].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));
	if (pDX00->iElevator2SlideOpen || !pDX00->iElevator2SlideClose) m_stcElevtorSts[1].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));
	if (pDX01->iElevator3SlideOpen || !pDX01->iElevator3SlideClose) m_stcElevtorSts[2].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));
	if (pDX01->iElevator4SlideOpen || !pDX01->iElevator4SlideClose) m_stcElevtorSts[3].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));
	if (pDX02->iElevator5SlideOpen || !pDX02->iElevator5SlideClose) m_stcElevtorSts[4].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));
	if (pDX02->iElevator6SlideOpen || !pDX02->iElevator6SlideClose) m_stcElevtorSts[5].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));
	if (pDX02->iElevator7SlideOpen || !pDX02->iElevator7SlideClose) m_stcElevtorSts[6].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));

	m_stcJobLotID[ 0].SetWindowText(gData.sLotID_Tansfer[0]);
	m_stcJobLotID[ 1].SetWindowText(gData.sLotID_Tansfer[1]);
	m_stcJobLotID[ 2].SetWindowText(gData.sLotID_LoadStage[0]);
	m_stcJobLotID[ 3].SetWindowText(gData.sLotID_LoadStage[1]);
	m_stcJobLotID[ 4].SetWindowText(gData.sLotID_LoadPicker[0]);
	m_stcJobLotID[ 5].SetWindowText(gData.sLotID_LoadPicker[1]);
	m_stcJobLotID[ 6].SetWindowText(gData.sLotID_VisionStage[0]);
	m_stcJobLotID[ 7].SetWindowText(gData.sLotID_VisionStage[1]);
	m_stcJobLotID[ 8].SetWindowText(gData.sLotID_VisionStage[2]);
	m_stcJobLotID[ 9].SetWindowText(gData.sLotID_VisionStage[3]);
	m_stcJobLotID[10].SetWindowText(gData.sLotID_UnloadPicker[0]);
	m_stcJobLotID[11].SetWindowText(gData.sLotID_UnloadPicker[1]);
	m_stcJobLotID[12].SetWindowText(gData.sLotID_NGTray[0]);
	m_stcJobLotID[13].SetWindowText(gData.sLotID_NGTray[1]);
	m_stcJobLotID[14].SetWindowText(gData.sLotID_GoodTray[0]);
	m_stcJobLotID[15].SetWindowText(gData.sLotID_GoodTray[1]);
//	m_stcJobLotID[16].SetWindowText(gData.sLotID_NGBuffer);
	if (gMes.nMarStatus > 0) m_stcJobLotID[16].SetWindowText(gMes.sHostNGLotID);
	else					 m_stcJobLotID[16].SetWindowText("");

	if (gData.nPortNo_Tansfer[0] > 0) strText.Format("%d-%d", gData.nTrayNo_Tansfer[0], gData.nPortNo_Tansfer[0]);
	else						 strText = "";
	m_stcJobCarNo[0].SetWindowText(strText);
	if (gData.nPortNo_Tansfer[1] > 0) strText.Format("%d-%d", gData.nTrayNo_Tansfer[1], gData.nPortNo_Tansfer[1]);
	else						 strText = "";
	m_stcJobCarNo[1].SetWindowText(strText);
	if (gData.nPortNo_LoadStage[0] > 0) strText.Format("%d-%d", gData.nTrayNo_LoadStage[0], gData.nPortNo_LoadStage[0]);
	else						 strText = "";
	m_stcJobCarNo[2].SetWindowText(strText);
	if (gData.nPortNo_LoadStage[1] > 0) strText.Format("%d-%d", gData.nTrayNo_LoadStage[1], gData.nPortNo_LoadStage[1]);
	else						 strText = "";
	m_stcJobCarNo[3].SetWindowText(strText);
	if (gData.nPortNo_LoadPicker[0] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_LoadPicker[0], gData.nPortNo_LoadPicker[0], gData.InfoLoadPick[0][9]);
	else						 strText = "";
	m_stcJobCarNo[4].SetWindowText(strText);
	if (gData.nPortNo_LoadPicker[1] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_LoadPicker[1], gData.nPortNo_LoadPicker[1], gData.InfoLoadPick[1][9]);
	else						 strText = "";
	m_stcJobCarNo[5].SetWindowText(strText);

	if (gData.nPortNo_VisionStage[0] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_VisionStage[0], gData.nPortNo_VisionStage[0], gData.InfoVision[0][9]);
	else						 strText = "";
	m_stcJobCarNo[6].SetWindowText(strText);
	if (gData.nPortNo_VisionStage[1] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_VisionStage[1], gData.nPortNo_VisionStage[1], gData.InfoVision[1][9]);
	else						 strText = "";
	m_stcJobCarNo[7].SetWindowText(strText);
	if (gData.nPortNo_VisionStage[2] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_VisionStage[2], gData.nPortNo_VisionStage[2], gData.InfoVision[2][9]);
	else						 strText = "";
	m_stcJobCarNo[8].SetWindowText(strText);
	if (gData.nPortNo_VisionStage[3] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_VisionStage[3], gData.nPortNo_VisionStage[3], gData.InfoVision[3][9]);
	else						 strText = "";
	m_stcJobCarNo[9].SetWindowText(strText);

	if (gData.nPortNo_UnloadPicker[0] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_UnloadPicker[0], gData.nPortNo_UnloadPicker[0], gData.InfoUnloadPick[0][9]);
	else						 strText = "";
	m_stcJobCarNo[10].SetWindowText(strText);
	if (gData.nPortNo_UnloadPicker[1] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_UnloadPicker[1], gData.nPortNo_UnloadPicker[1], gData.InfoUnloadPick[1][9]);
	else						 strText = "";
	m_stcJobCarNo[11].SetWindowText(strText);
	if (gData.nPortNo_NGTray[0] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_NGTray[0], gData.nPortNo_NGTray[0], gLot.nOutTrayCnt[gData.nPortNo_NGTray[0]-1][1]);
	else						 strText = "";
	m_stcJobCarNo[12].SetWindowText(strText);
	if (gData.nPortNo_NGTray[1] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_NGTray[1], gData.nPortNo_NGTray[1], gLot.nOutTrayCnt[gData.nPortNo_NGTray[1]-1][1]);
	else						 strText = "";
	m_stcJobCarNo[13].SetWindowText(strText);
	if (gData.nPortNo_GoodTray[0] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_GoodTray[0], gData.nPortNo_GoodTray[0], gLot.nOutTrayCnt[gData.nPortNo_GoodTray[0]-1][0]);
	else						 strText = "";
	m_stcJobCarNo[14].SetWindowText(strText);
	if (gData.nPortNo_GoodTray[1] > 0) strText.Format("%d-%d-%d", gData.nTrayNo_GoodTray[1], gData.nPortNo_GoodTray[1], gLot.nOutTrayCnt[gData.nPortNo_GoodTray[1]-1][0]);
	else						 strText = "";
	m_stcJobCarNo[15].SetWindowText(strText);
//	if (gData.nPortNo_NGBuffer > 0) strText.Format("P%d-C%d", gData.nPortNo_NGBuffer, gData.nTrayNo_NGBuffer);
//	else						 strText = "";
//	m_stcJobCarNo[16].SetWindowText(strText);
	if		(gMes.nMarStatus == 1) strText.Format("요청-T%d-M%d", gMes.nMarTrayCount, gMes.nMarCount);
	else if (gMes.nMarStatus == 2) strText.Format("Run-T%d-M%d", gMes.nMarTrayCount, gMes.nMarCount);
	else if (gMes.nMarStatus == 3) strText.Format("완공-T%d-M%d", gMes.nMarTrayCount, gMes.nMarCount);
	else						   strText = "";
	m_stcJobCarNo[16].SetWindowText(strText);

	m_ledVisionSts[0].Set_On(g_objInspector.Get_VisionStatus(INSPECTOR_PC1));
	m_ledVisionSts[1].Set_On(g_objInspector.Get_VisionStatus(INSPECTOR_PC2));
	m_ledVisionSts[2].Set_On(g_objInspector.Get_VisionStatus(INSPECTOR_PC3));
	m_ledVisionSts[4].Set_On(g_objInspector.Get_VisionStatus(INSPECTOR_PC4));
	m_ledVisionSts[5].Set_On(g_objInspector.Get_VisionStatus(INSPECTOR_PC5));
	m_ledVisionSts[3].Set_On(g_objDispatcher.Is_Connected());

	if		(gLot.nLotStatus[0] == 1)		m_stcLotsIdS[0].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x00, 0xA0, 0x00));	//작업중일때
	else if (gMes.nLotStatus[0] == 3 || gMes.nLotStatus[0] == 4)		m_stcLotsIdS[0].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));	//매거진 있을때
	else if (gMes.nLotStatus[0] == 9)		m_stcLotsIdS[0].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));	//취소시
	else									m_stcLotsIdS[0].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));	//매거진 없을때
	if		(gLot.nLotStatus[1] == 1)		m_stcLotsIdS[1].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x00, 0xA0, 0x00));	//작업중일때
	else if (gMes.nLotStatus[1] == 3 || gMes.nLotStatus[1] == 4)		m_stcLotsIdS[1].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));	//매거진 있을때
	else if (gMes.nLotStatus[1] == 9)		m_stcLotsIdS[1].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));	//취소시
	else									m_stcLotsIdS[1].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));	//매거진 없을때
	if		(gLot.nLotStatus[2] == 1)		m_stcLotsIdS[2].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x00, 0xA0, 0x00));	//작업중일때
	else if (gMes.nLotStatus[2] == 3 || gMes.nLotStatus[2] == 4)		m_stcLotsIdS[2].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));	//매거진 있을때
	else if (gMes.nLotStatus[2] == 9)		m_stcLotsIdS[2].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));	//취소시
	else									m_stcLotsIdS[2].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));	//매거진 없을때
	if		(gLot.nLotStatus[3] == 1)		m_stcLotsIdS[3].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x00, 0xA0, 0x00));	//작업중일때
	else if (gMes.nLotStatus[3] == 3 || gMes.nLotStatus[3] == 4)		m_stcLotsIdS[3].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));	//매거진 있을때
	else if (gMes.nLotStatus[3] == 9)		m_stcLotsIdS[3].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));	//취소시
	else									m_stcLotsIdS[3].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));	//매거진 없을때
	if		(gLot.nLotStatus[4] == 1)		m_stcLotsIdS[4].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x00, 0xA0, 0x00));	//작업중일때
	else if (gMes.nLotStatus[4] == 3 || gMes.nLotStatus[4] == 4)		m_stcLotsIdS[4].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));	//매거진 있을때
	else if (gMes.nLotStatus[4] == 9)		m_stcLotsIdS[4].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));	//취소시
	else									m_stcLotsIdS[4].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));	//매거진 없을때
	if		(gLot.nLotStatus[5] == 1)		m_stcLotsIdS[5].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x00, 0xA0, 0x00));	//작업중일때
	else if (gMes.nLotStatus[5] == 3 || gMes.nLotStatus[5] == 4)		m_stcLotsIdS[5].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));	//매거진 있을때
	else if (gMes.nLotStatus[5] == 9)		m_stcLotsIdS[5].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0xFF, 0x00, 0x00));	//취소시
	else									m_stcLotsIdS[5].Init_Ctrl("Arial", 12, FALSE, COLOR_DEFAULT, RGB(0x80, 0xF0, 0xF0));	//매거진 없을때

	int *pCase = g_objSequenceMain.Get_pMainRunCase();
	CString strCase;
	for (int i = 0; i < 24; i++) {
		strCase.Format("%02d", *(pCase + i));
		m_stcWorkCase[i].SetWindowText(strCase);
	}

	strText = "";
	if (*(pCase +  9) > 18 && *(pCase +  9) < 30 && gData.nTrayNo_LoadStage[0] > 0) strText.Format("%d", gData.nTrayNo_LoadStage[0]);
	if (*(pCase + 10) > 30 && *(pCase + 10) < 30 && gData.nTrayNo_LoadStage[1] > 0) strText.Format("%d", gData.nTrayNo_LoadStage[1]);
	m_stcAlignLine.SetWindowText(strText);	//Align Tray

	strText = "";
	if (*(pCase +  9) == 30 && gData.nTrayNo_LoadStage[0] > 0) strText.Format("%d/%d", gData.nTrayNo_LoadStage[0], gLot.nTrayPutCnt[gData.nPortNo_LoadStage[0]-1][2]);
	if (*(pCase + 10) == 30 && gData.nTrayNo_LoadStage[1] > 0) strText.Format("%d/%d", gData.nTrayNo_LoadStage[1], gLot.nTrayPutCnt[gData.nPortNo_LoadStage[1]-1][2]);
	m_stcCarrierLine.SetWindowText(strText);	//Load Tray

	strText = "";
	if (*(pCase + 19) == 30 && gData.nTrayNo_NGTray[0] > 0) strText.Format("%d/%d", gLot.nOutTrayCnt[gData.nPortNo_NGTray[0]-1][1], gLot.nTrayPutCnt[gData.nPortNo_NGTray[0]-1][1]);
	if (*(pCase + 20) == 30 && gData.nTrayNo_NGTray[1] > 0) strText.Format("%d/%d", gLot.nOutTrayCnt[gData.nPortNo_NGTray[1]-1][1], gLot.nTrayPutCnt[gData.nPortNo_NGTray[1]-1][1]);
	m_stcNGLine.SetWindowText(strText);		//NG Tray

	strText = "";
	if (*(pCase + 21) == 30 && gData.nTrayNo_GoodTray[0] > 0) strText.Format("%d/%d", gLot.nOutTrayCnt[gData.nPortNo_GoodTray[0]-1][0], gLot.nTrayPutCnt[gData.nPortNo_GoodTray[0]-1][0]);
	if (*(pCase + 22) == 30 && gData.nTrayNo_GoodTray[1] > 0) strText.Format("%d/%d", gLot.nOutTrayCnt[gData.nPortNo_GoodTray[1]-1][0], gLot.nTrayPutCnt[gData.nPortNo_GoodTray[1]-1][0]);
	m_stcGoodLine.SetWindowText(strText);	//Good Tray

	Display_LoadPicker();
	Display_VisionStage();
	Display_UnloadPicker();
	Display_TrayCheck();

	g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 0, NULL);
}

void CWorkDlg::	Display_LoadPicker()
{
	DX_DATA_05 *pDX05 = g_objAJinAXL.Get_pDX05();
	DX_DATA_06 *pDX06 = g_objAJinAXL.Get_pDX06();

	m_ledLoadPicker1[0].Set_On(pDX05->iLoadPicker1Exist1);
	m_ledLoadPicker1[1].Set_On(pDX05->iLoadPicker1Exist2);
	m_ledLoadPicker1[2].Set_On(pDX05->iLoadPicker1Exist3);
	m_ledLoadPicker1[3].Set_On(pDX05->iLoadPicker1Exist4);
	m_ledLoadPicker1[4].Set_On(pDX05->iLoadPicker1Exist5);
	m_ledLoadPicker1[5].Set_On(pDX05->iLoadPicker1Exist6);
	m_ledLoadPicker1[6].Set_On(pDX05->iLoadPicker1Exist7);
	m_ledLoadPicker1[7].Set_On(pDX05->iLoadPicker1Exist8);

	m_ledLoadPicker2[0].Set_On(pDX06->iLoadPicker2Exist1);
	m_ledLoadPicker2[1].Set_On(pDX06->iLoadPicker2Exist2);
	m_ledLoadPicker2[2].Set_On(pDX06->iLoadPicker2Exist3);
	m_ledLoadPicker2[3].Set_On(pDX06->iLoadPicker2Exist4);
	m_ledLoadPicker2[4].Set_On(pDX06->iLoadPicker2Exist5);
	m_ledLoadPicker2[5].Set_On(pDX06->iLoadPicker2Exist6);
	m_ledLoadPicker2[6].Set_On(pDX06->iLoadPicker2Exist7);
	m_ledLoadPicker2[7].Set_On(pDX06->iLoadPicker2Exist8);
}

void CWorkDlg::Display_VisionStage()
{
	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();

	m_ledVision1[0].Set_On(pDX07->iInspectStage1Vac1On);
	m_ledVision1[1].Set_On(pDX07->iInspectStage1Vac2On);
	m_ledVision1[2].Set_On(pDX07->iInspectStage1Vac3On);
	m_ledVision1[3].Set_On(pDX07->iInspectStage1Vac4On);
	m_ledVision1[4].Set_On(pDX07->iInspectStage1Vac5On);
	m_ledVision1[5].Set_On(pDX07->iInspectStage1Vac6On);
	m_ledVision1[6].Set_On(pDX07->iInspectStage1Vac7On);
	m_ledVision1[7].Set_On(pDX07->iInspectStage1Vac8On);

	m_ledVision2[0].Set_On(pDX07->iInspectStage2Vac1On);
	m_ledVision2[1].Set_On(pDX07->iInspectStage2Vac2On);
	m_ledVision2[2].Set_On(pDX07->iInspectStage2Vac3On);
	m_ledVision2[3].Set_On(pDX07->iInspectStage2Vac4On);
	m_ledVision2[4].Set_On(pDX07->iInspectStage2Vac5On);
	m_ledVision2[5].Set_On(pDX07->iInspectStage2Vac6On);
	m_ledVision2[6].Set_On(pDX07->iInspectStage2Vac7On);
	m_ledVision2[7].Set_On(pDX07->iInspectStage2Vac8On);

	m_ledVision3[0].Set_On(pDX08->iInspectStage3Vac1On);
	m_ledVision3[1].Set_On(pDX08->iInspectStage3Vac2On);
	m_ledVision3[2].Set_On(pDX08->iInspectStage3Vac3On);
	m_ledVision3[3].Set_On(pDX08->iInspectStage3Vac4On);
	m_ledVision3[4].Set_On(pDX08->iInspectStage3Vac5On);
	m_ledVision3[5].Set_On(pDX08->iInspectStage3Vac6On);
	m_ledVision3[6].Set_On(pDX08->iInspectStage3Vac7On);
	m_ledVision3[7].Set_On(pDX08->iInspectStage3Vac8On);

	m_ledVision4[0].Set_On(pDX08->iInspectStage4Vac1On);
	m_ledVision4[1].Set_On(pDX08->iInspectStage4Vac2On);
	m_ledVision4[2].Set_On(pDX08->iInspectStage4Vac3On);
	m_ledVision4[3].Set_On(pDX08->iInspectStage4Vac4On);
	m_ledVision4[4].Set_On(pDX08->iInspectStage4Vac5On);
	m_ledVision4[5].Set_On(pDX08->iInspectStage4Vac6On);
	m_ledVision4[6].Set_On(pDX08->iInspectStage4Vac7On);
	m_ledVision4[7].Set_On(pDX08->iInspectStage4Vac8On);
}

void CWorkDlg::Display_UnloadPicker()
{
	DX_DATA_09 *pDX09 = g_objAJinAXL.Get_pDX09();
	DX_DATA_10 *pDX10 = g_objAJinAXL.Get_pDX10();

	m_ledUnloadPicker1[0].Set_On(pDX09->iUnloadPicker1Exist1);
	m_ledUnloadPicker1[1].Set_On(pDX09->iUnloadPicker1Exist2);
	m_ledUnloadPicker1[2].Set_On(pDX09->iUnloadPicker1Exist3);
	m_ledUnloadPicker1[3].Set_On(pDX09->iUnloadPicker1Exist4);
	m_ledUnloadPicker1[4].Set_On(pDX09->iUnloadPicker1Exist5);
	m_ledUnloadPicker1[5].Set_On(pDX09->iUnloadPicker1Exist6);
	m_ledUnloadPicker1[6].Set_On(pDX09->iUnloadPicker1Exist7);
	m_ledUnloadPicker1[7].Set_On(pDX09->iUnloadPicker1Exist8);

	m_ledUnloadPicker2[0].Set_On(pDX10->iUnloadPicker2Exist1);
	m_ledUnloadPicker2[1].Set_On(pDX10->iUnloadPicker2Exist2);
	m_ledUnloadPicker2[2].Set_On(pDX10->iUnloadPicker2Exist3);
	m_ledUnloadPicker2[3].Set_On(pDX10->iUnloadPicker2Exist4);
	m_ledUnloadPicker2[4].Set_On(pDX10->iUnloadPicker2Exist5);
	m_ledUnloadPicker2[5].Set_On(pDX10->iUnloadPicker2Exist6);
	m_ledUnloadPicker2[6].Set_On(pDX10->iUnloadPicker2Exist7);
	m_ledUnloadPicker2[7].Set_On(pDX10->iUnloadPicker2Exist8);

}

void CWorkDlg::Display_TrayCheck()
{
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	DX_DATA_04 *pDX04 = g_objAJinAXL.Get_pDX04();
	DX_DATA_11 *pDX11 = g_objAJinAXL.Get_pDX11();
	DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();

	m_ledTrayCheck[ 0].Set_On(pDX00->iElevator1TrayExist);
	m_ledTrayCheck[ 1].Set_On(pDX00->iElevator2TrayExist);
	m_ledTrayCheck[ 2].Set_On(pDX01->iElevator3TrayExist);
	m_ledTrayCheck[ 3].Set_On(pDX01->iElevator4TrayExist);
	m_ledTrayCheck[ 4].Set_On(pDX02->iElevator5TrayExist);
	m_ledTrayCheck[ 5].Set_On(pDX02->iElevator6TrayExist);
	m_ledTrayCheck[ 6].Set_On(pDX02->iElevator7TrayExist);
	m_ledTrayCheck[ 7].Set_On(pDX03->iTransferLTrayExist);
	m_ledTrayCheck[ 8].Set_On(pDX03->iTransferRTrayExist);
	m_ledTrayCheck[ 9].Set_On(pDX04->iLoadStage1TrayExist);
	m_ledTrayCheck[10].Set_On(pDX04->iLoadStage2TrayExist);
	m_ledTrayCheck[11].Set_On(pDX11->iNGStage1TrayExist);
	m_ledTrayCheck[12].Set_On(pDX11->iNGStage2TrayExist);
	m_ledTrayCheck[13].Set_On(pDX12->iGoodStage1TrayExist);
	m_ledTrayCheck[14].Set_On(pDX12->iGoodStage2TrayExist);
}

void CWorkDlg::Reset_AlarmLog()
{
	CString strLog, strErrNo;
	SYSTEMTIME time;

	gAlm.bBegin = FALSE;
	GetLocalTime(&time);

	gAlm.dwEndTime = GetTickCount();
	gAlm.sEndTime.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	gAlm.dwProcTime = gAlm.dwEndTime - gAlm.dwStartTime;
	strLog.Format("%s,%04d,%s,%s,%s,%d", gAlm.sLotID, gAlm.nAlmNo, gAlm.sAlmMsg, gAlm.sStartTime, gAlm.sEndTime, gAlm.dwProcTime);
	g_objLogFile.Save_AlarmLog(strLog);	// Alarm Reset

	double dSec, dMin;
	dSec = gAlm.dwProcTime / 1000.0;
	dMin = dSec / 60.0;
	strLog.Format("%s,%04d,%s,%s,%s,%0.3lf,%0.3lf", gAlm.sLotID, gAlm.nAlmNo, gAlm.sAlmMsg, gAlm.sStartTime, gAlm.sEndTime, dSec, dMin);
	g_objLogFile.Save_AlarmResetLog(strLog);

	strLog.Format(",,,,,,,,,,ErrorTime,,,%0.3lf", (double)(gAlm.dwProcTime/1000.0));
	g_objLogFile.Save_SpcMccLog(strLog, gAlm.sLotID);

	strLog.Format("%s,%04d,%s,%s,%s,%s,%d", gAlm.sLotID, gAlm.nAlmNo, gAlm.sSpcInfo, gAlm.sAlmMsg, gAlm.sStartTime, gAlm.sEndTime, gAlm.dwProcTime);
	g_objLogFile.Save_SpcErrorLog(strLog, gAlm.sLotID);

	strErrNo.Format("%04d", gAlm.nAlmNo);
	g_objMesAgent.Set_ErrorUpdate(0, strErrNo);

	if (gAlm.nPortNo > 0) {
		gLot.dwErrorTime[gAlm.nPortNo-1] += gAlm.dwProcTime; gLot.nErrorCount[gAlm.nPortNo-1]++;
	}
}

void CWorkDlg::Set_AutoRun(BOOL bAutoRun)
{
	if (bAutoRun) m_rdoWorkStart.SetCheck(TRUE);
	else m_rdoWorkStop.SetCheck(TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// Message

LRESULT CWorkDlg::OnUpdateModel(WPARAM wParam, LPARAM lParam)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	m_bmpEquipment.DeleteObject();
	if		(gData.bUseDryRun)			m_bmpEquipment.LoadBitmap(IDB_EQUIP_DOOR);
	else if (!pEquipData->bUseDoorLock) m_bmpEquipment.LoadBitmap(IDB_EQUIP_DOOR_KOR);
	else								m_bmpEquipment.LoadBitmap(IDB_EQUIP_WORK);
	m_imgEquipment.SetBitmap(m_bmpEquipment);

	return 0;
}

LRESULT CWorkDlg::OnUpdateTrayInfo(WPARAM nTray, LPARAM lParam)
{
	int nj;
	CString strText;

	for (int i = 0; i < TRAY_CM_Y; i++) {
		for (int j = 0; j <TRAY_CM_X; j++) {
			if (j == 0) nj = 3; if (j == 1) nj = 2; if (j == 2) nj = 1; if (j == 3) nj = 0;
			// (y,x) 0:Empty, 1:NG      2:Good
			if		(gData.InfoAlignTray[i][j] == 0)	m_grdAlign.Set_CellBackClr(i, nj, RGB(0xFF, 0xFF, 0xFF));	// 0 Empty
			else if (gData.InfoAlignTray[i][j] == 1)	m_grdAlign.Set_CellBackClr(i, nj, RGB(0xFF, 0x00, 0x00));	// 1 NG
			else if (gData.InfoAlignTray[i][j] == 2)	m_grdAlign.Set_CellBackClr(i, nj, RGB(0x00, 0xFF, 0x00));	// 2 Good

			// (y,x) 0:Empty, 1:Module, 2:Good, NG:3~
			if		(gData.InfoLoadTray[i][j] > 0)	m_grdCarrier.Set_CellBackClr(i, nj, RGB(0xFF, 0x80, 0xFF));
			else									m_grdCarrier.Set_CellBackClr(i, nj, RGB(0xFF, 0xFF, 0xFF));	// 0 Empty

			if		(gData.InfoNgTray[i][j] == 15)	m_grdNGTray.Set_CellBackClr(i, nj, RGB(0x00, 0x00, 0xFF));	//Marginal
			else if (gData.InfoNgTray[i][j] == 12)	m_grdNGTray.Set_CellBackClr(i, nj, RGB(0x00, 0xFF, 0x00));	//NoRead
			else if (gData.InfoNgTray[i][j] > 0)	m_grdNGTray.Set_CellBackClr(i, nj, RGB(0xFF, 0x00, 0x00));	//NG
			else									m_grdNGTray.Set_CellBackClr(i, nj, RGB(0xFF, 0xFF, 0xFF));	// 0 Empty

			if		(gData.InfoGoodTray[i][j] > 0)	m_grdGoodTray.Set_CellBackClr(i, nj, RGB(0x00, 0xFF, 0x00));
			else									m_grdGoodTray.Set_CellBackClr(i, nj, RGB(0xFF, 0xFF, 0xFF));	// 0 Empty

		}
	}
	g_dlgOperator.Update_TrayInfo(nTray);

/*
				if		(gData.InfoNgTray[i][j] == 1) m_grdNgTray.Set_CellBackClr(i, j, RGB(0xFF, 0x80, 0xFF));	// 1 Module
				else if	(gData.InfoNgTray[i][j] == 2) m_grdNgTray.Set_CellBackClr(i, j, RGB(0x00, 0xFF, 0x00));	// 2 Good
				else if (gData.InfoNgTray[i][j] == 3) m_grdNgTray.Set_CellBackClr(i, j, RGB(0xFF, 0x00, 0x00));	// 3 Normal NG
				else if (gData.InfoNgTray[i][j] == 4) m_grdNgTray.Set_CellBackClr(i, j, RGB(0xF0, 0xF0, 0x00));	// 4 MES 성능불량
				else if (gData.InfoNgTray[i][j] == 5) m_grdNgTray.Set_CellBackClr(i, j, RGB(0xFF, 0x60, 0xFF));	// 5 Barcode Mismatch
				else if (gData.InfoNgTray[i][j] == 6) m_grdNgTray.Set_CellBackClr(i, j, RGB(0x80, 0x40, 0xF0));	// 6 HREN
				else if (gData.InfoNgTray[i][j] == 7) m_grdNgTray.Set_CellBackClr(i, j, RGB(0x00, 0x80, 0xFF));	// 7 Spider
				else if (gData.InfoNgTray[i][j] == 8) m_grdNgTray.Set_CellBackClr(i, j, RGB(0x80, 0x40, 0x00));	// 8 HREP
				else if (gData.InfoNgTray[i][j] == 9) m_grdNgTray.Set_CellBackClr(i, j, RGB(0xC0, 0x80, 0x00));	// 9 Chipping
				else								  m_grdNgTray.Set_CellBackClr(i, j, RGB(0xFF, 0xFF, 0xFF));	// 0 Empty
*/

	return 0;
}

LRESULT CWorkDlg::OnUpdateBarcode(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	CString sData = g_objBarcodeLot.Get_BarcodeLot();
	if (sData.GetLength() < 1) return 0;
/*
	if (m_rdoWorkStart.GetCheck()) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("장비 Stop 상태에서 진행이 가능합니다....."));
		else					  AfxMessageBox(_T("You can proceed with the equipment stopped."));
		return 0;
	}*/
	if (gData.nSelectNo < 1 || gData.nSelectNo > 6) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("Lot을 먼저 선택후 진행하세요..."));
		else					  AfxMessageBox(_T("Select Lot first and proceed."));
		return 0;
	}

	m_stcLotsIdS[gData.nSelectNo-1].GetWindowText(strTemp);
	if (strTemp.GetLength() > 0) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("기존 Lot ID Clear를 먼저하고 진행하세요..."));
		else					  AfxMessageBox(_T("Please proceed with the existing Lot ID Clear first."));
		return 0;
	}

	//바코드 인식 후 작업 모델이 맞는지 확인.
	if(BarcodeLotID_Check(sData) == FALSE){
		if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "모델 확인 후 다시 입력해 주십시오.....");
		else					  g_objCommon.Show_MsgBox(1, "Please check the model and re-enter...");
		return 0;
	}
	///////////////////////////////////////
	m_stcLotsIdS[gData.nSelectNo-1].SetWindowText(sData);

	//2018.9.11+
	UINT nID = IDC_STC_CMS_COUNT_S_0+gData.nSelectNo-1;
	OnStcCmsCountSClick(nID);

//	g_objSequenceMain.Beep_Post(500);

//	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
//	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	return 0;
}

LRESULT CWorkDlg::OnResetCycleStop(WPARAM wParam, LPARAM lParam)
{
	gData.bCycleStop = FALSE;
	m_chkCycleStop.SetCheck(FALSE);
	m_chkCycleStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xF0));
	if (wParam == 1) g_objSequenceInit.Set_InitComplete(FALSE);	// 초기화 필요

	return 0;
}

LRESULT CWorkDlg::OnUpdateUph(WPARAM wParam, LPARAM lParam)
{
	int nStartNo = gLot.nJobNo - 1;
	int nDispyNo = 0;
	CString sTxt;
	if (nStartNo >= 0) {
		for(int i=nStartNo; i>=0; i--) {
			nDispyNo++; if (nDispyNo > 9) return 0;
			for(int j=0; j<9; j++) {
				if (gLot.nJobPortNo[i] > 0) {
					if (j == 0) sTxt.Format("%d", gLot.nJobPortNo[i]);
					if (j == 1) sTxt.Format("%s", gLot.sJobLotID[i]);
					if (j == 2) sTxt.Format("%d", gLot.nJobCmCount[i]);
					if (j == 3) sTxt.Format("%d", gLot.nJobGoodCount[i]);
					if (j == 4) sTxt.Format("%d", gLot.nJobNgCount[i]);
					if (j == 5) sTxt.Format("%0.2lf", gLot.dJobRate[i]);
					if (j == 6) sTxt.Format("%s", gLot.sJobStartTime[i]);
					if (j == 7) sTxt.Format("%s", gLot.sJobEndTime[i]);
					if (j == 8) sTxt.Format("%0.5lf", gLot.dJobTack[i]);
				} else sTxt = "";

				m_grdJob.Set_CellText(nDispyNo, j, sTxt);
			}
		}
	}
	for(int i=9; i>=nStartNo; i--) {
		nDispyNo++; if (nDispyNo > 9) return 0;
		for(int j=0; j<9; j++) {
			if (gLot.nJobPortNo[i] > 0) {
				if (j == 0) sTxt.Format("%d", gLot.nJobPortNo[i]);
				if (j == 1) sTxt.Format("%s", gLot.sJobLotID[i]);
				if (j == 2) sTxt.Format("%d", gLot.nJobCmCount[i]);
				if (j == 3) sTxt.Format("%d", gLot.nJobGoodCount[i]);
				if (j == 4) sTxt.Format("%d", gLot.nJobNgCount[i]);
				if (j == 5) sTxt.Format("%0.2lf", gLot.dJobRate[i]);
				if (j == 6) sTxt.Format("%s", gLot.sJobStartTime[i]);
				if (j == 7) sTxt.Format("%s", gLot.sJobEndTime[i]);
				if (j == 8) sTxt.Format("%0.5lf", gLot.dJobTack[i]);
			} else sTxt = "";

			m_grdJob.Set_CellText(nDispyNo, j, sTxt);
		}
	}

	return 0;
}

LRESULT CWorkDlg::OnJobComplete(WPARAM wParam, LPARAM lParam)
{
//	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	DY_DATA_04 *pDY04 = g_objAJinAXL.Get_pDY04();
	pDY04->oBTMIonizerOn = FALSE;
	pDY04->oBTMIonizerBlow = FALSE;
	pDY04->oBTMSuctionOn = FALSE;

	pDY04->oTOPIonizerOn = FALSE;
	pDY04->oTOPIonizerBlow = FALSE;
	pDY04->oTOPSuctionOn = FALSE;
	g_objAJinAXL.Write_Output(4);

	for (int i=0; i<6; i++) {
		m_stcLotsIdS[i].SetWindowText("");
		m_stcCmsCountS[i].SetWindowText("");
		m_stcTrayCountS[i].SetWindowText("");
		gLot.nCmCount[i] = gLot.nTrayCount[i] = gLot.nGoodCount[i] = gLot.nNgCount[i] = gLot.nLotStatus[i] = gLot.nSkipCount[i] = 0;
	}
	g_objSequenceMain.Beep_Post(1000);

	if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "Job 완료.");
	else					  g_objCommon.Show_MsgBox(1, "Job complete.");
	g_objMesAgent.Set_EquipState(4);	//Ready

	SYSTEMTIME time;
	GetLocalTime(&time);
	if (gData.nStdLogDay != time.wDay) {
		CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
		gData.nStdLotNo = 0;
		gData.nStdLogDay = (int)time.wDay;
		INI.Set_Integer("STD_LOG", "STD_LOT_NO", gData.nStdLotNo);
		INI.Set_Integer("STD_LOG", "STD_LOG_DAY", gData.nStdLogDay);
		for(int i=0; i<6; i++) gData.nTotLotNo[i] = 0;
	}
	g_objLogFile.Clear_LogData();

	return 0;
}

LRESULT CWorkDlg::OnShowLotEndMsg(WPARAM wParam, LPARAM lParam)
{
	CString sMsg;
	int nNo = wParam - 1;
	if (nNo >= 0) {
		m_stcLotsIdS[nNo].SetWindowText("");
		m_stcCmsCountS[nNo].SetWindowText("");
		m_stcTrayCountS[nNo].SetWindowText("");
		g_objCommon.Set_LotDataClear(nNo);
	}
/*
	int nNo2 = lParam;
	if(nNo2 == 0) {
		g_objSequenceMain.Beep_Post(1000);
		if (gData.nLanguage == 0) sMsg.Format("%d번 Port Lot이 끝났습니다.", nNo+1);
		else					  sMsg.Format("No%d Port Lot is complete.", nNo+1);
		g_objCommon.Show_MsgBox(1, sMsg);
	}
	if(nNo2 == 9) {
		if (gData.nLanguage == 0) sMsg.Format("Reject %dea 이상 검출!!!\nTag 부착후 검사자\n인계 바랍니다.(Reject=%d)", gData.nRejectMaxCount, gData.nRejectLotCount);
		else					  sMsg.Format("More than %d reject detected!!!\nPlease attach the tag and hand it\nover to the inspector.(Reject=%d)", gData.nRejectMaxCount, gData.nRejectLotCount);
		g_objCommon.Show_MsgBox(9, sMsg);
	}
*/
	return 0;
/*
	//g_dlgWork.PostMessage(UM_LOT_END_MSG, NULL, NULL);
	if(wParam == 1) {
		if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "Job이 끝나고 초기화 중 입니다.\n부저 및 완료 메세지가 뜰때까지 기다려 주세요.");
		else					  g_objCommon.Show_MsgBox(1, "Job is finished and initializing.\nPlease wait for the buzzer and completion message to appear.");
	}
	if(wParam == 2) {
		if (gData.nLanguage == 0) g_objCommon.Show_Alarm("Lot이 끝났습니다.\n입력수량과 검사수량이 맞지 않습니다.\n확인해 주세요");
		else					  g_objCommon.Show_Alarm("Lot is complete.\nThe input quantity and the inspection quantity do not match.\nPlease check.");
	}
	if(wParam == 9) {
		if (gData.nLanguage == 0) sMsg.Format("Reject %dea 이상 검출!!!\nTag 부착후 검사자\n인계 바랍니다.(Reject=%d)", gData.nRejectMaxCount, gData.nRejectLotCount);
		else					  sMsg.Format("More than %d reject detected!!!\nPlease attach the tag and hand it\nover to the inspector.(Reject=%d)", gData.nRejectMaxCount, gData.nRejectLotCount);
		g_objCommon.Show_MsgBox(9, sMsg);
	} else {
		if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "Lot이 끝났습니다.\nClear 후 꺼내 주세요.");
		else					  g_objCommon.Show_MsgBox(1, "Lot is complete.\nClear and take it out.");
	}
*/
}

///////////////////////////////////////////////////////////////////////////////
void CWorkDlg::ReadJobList()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\JobList.ini");
	if (!INI.Check_File()) {
		//AfxMessageBox("JobList.ini File Not Found!!!");
		return;
	}

	CString strSection;
	for (int i=0; i<6; i++) {
		strSection.Format("LOT_%d", i);
		m_sJobListLotID[i]  = INI.Get_String(strSection, "ID", "");
		m_sJobListLotCnt[i] = INI.Get_String(strSection, "CNT", "");
		m_sJobListTryCnt[i] = INI.Get_String(strSection, "TRY", "");

		 m_stcLotsIdS[i].SetWindowText(m_sJobListLotID[i]);
		 m_stcCmsCountS[i].SetWindowText(m_sJobListLotCnt[i]);
		 m_stcTrayCountS[i].SetWindowText(m_sJobListTryCnt[i]);
	}
}

void CWorkDlg::SaveJobList()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\JobList.ini");
	if (!INI.Check_File()) {
		//AfxMessageBox("JobList.ini File Not Found!!!");
		return;
	}

	CString strSection;
	for (int i=0; i<6; i++) {
		m_stcLotsIdS[i].GetWindowText(m_sJobListLotID[i]);
		m_stcCmsCountS[i].GetWindowText(m_sJobListLotCnt[i]);
		m_stcTrayCountS[i].GetWindowText(m_sJobListTryCnt[i]);

		strSection.Format("LOT_%d", i);
		INI.Set_String(strSection, "ID", m_sJobListLotID[i]);
		INI.Set_String(strSection, "CNT", m_sJobListLotCnt[i]);
		INI.Set_String(strSection, "TRY", m_sJobListTryCnt[i]);
	}
}

//바코드를 찍었을때 LotID가 설비 모델과 비교해준다.
BOOL CWorkDlg::BarcodeLotID_Check(CString sLotID)
{
	CString sPath, strKey;
	CString sData; // ini 파일에 있는 모델별 데이터

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	CIniFileCS INI(gsCurrentDir + "\\System\\BarcodeData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("EquipData.ini File Not Found!!!");
		return FALSE;
	}

	strKey = pEquipData->sModelName;
	
	sData = INI.Get_String(strKey, "DATA", "");

	if(sData == "") return TRUE;	// 데이터가 없으면 무조건 입력할수있게 해준다.
	if(sLotID.Find(sData) == 2) return TRUE; //같은 문자열 시작이 2이면 같은 모델임.(GSXXXX, XXXX가 모델별로 정해진 데이터)

	return FALSE;	//그외 나머지는 다른 모델인걸로 간주.
}

void CWorkDlg::OnBnClickedBtnLotCancel()
{
	if (m_rdoWorkStart.GetCheck()) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("장비 Stop 상태에서 진행이 가능합니다....."));
		else					  AfxMessageBox(_T("You can proceed with the equipment stopped."));
		return;
	}

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("MES 사용 설정후 진행이 가능합니다....."));
		else					  AfxMessageBox(_T("Unable to proceed while the mes is not used."));
		return;
	}

	if (gData.nLanguage == 0) {
		if (g_objCommon.Show_MsgBox(2, "Lot Cancel를 하시겠습니까?") != IDOK) return;
	} else {
		if (g_objCommon.Show_MsgBox(2, "Are you sure you want to Lot Cancel?") != IDOK) return;
	}

	int nCount = 0;
	for (int i=0; i<6; i++) {
		if (gLot.sLotID[i].GetLength() > 0 && gLot.nCmCount[i] > 0) {
//			g_objMesAgent.Set_LotCancel(gLot.sLotID[i], "O");
			nCount++;
		}
	}
	if (nCount == 0) {
		if (gData.nLanguage == 0) AfxMessageBox(_T("취소할 Lot이 없습니다....."));
		else					  AfxMessageBox(_T("There is no Lot to cancel.."));
		return;
	}

	CString sLog;
	if (gData.nLanguage == 0) sLog.Format("Lot Cancel OK...  => Lot 취소를 MES에 전송하였습니다.");
	else					  sLog.Format("Lot Cancel OK...  => Lot cancel has been send to MES.");
	AfxMessageBox(_T(sLog));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorkDlg::ElevatorOpen(int nEleNo)
{
	CString sLog;
	static DWORD dwSwitchOnTime[7] = {0,};

	if (dwSwitchOnTime[nEleNo-1] > 0 && (GetTickCount() - dwSwitchOnTime[nEleNo-1]) < 1000) return;
	dwSwitchOnTime[nEleNo-1] = GetTickCount();

	if (gData.nElevatorOpen[nEleNo] == 0) {
			if (g_objSequenceInit.Get_InitComplete()==FALSE) {
				g_objCommon.Show_MsgBox(1, "장비 초기화후 진행하세요....."); return;
			}
//			if (g_objCommon.Show_MsgBox(2, "Elevator Door를 Open 하시겠습니까?") != IDOK) return;

			//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)
			//if ((gData.nTransferX1Pos-2) == nEleNo) { g_objCommon.Show_MsgBox(1, "Transfer 1 Elevator 작업중입니다.  작업후 진행하세요."); return; }
			//if ((gData.nTransferX2Pos-2) == nEleNo) { g_objCommon.Show_MsgBox(1, "Transfer 2 Elevator 작업중입니다.  작업후 진행하세요."); return; }
//			if (!g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) { g_objSequenceMain.Beep_Post(500); g_objCommon.Show_MsgBox(1, "Transfer Z1 Up상태에서 작업가능합니다.."); return; }
//			if (!g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) { g_objSequenceMain.Beep_Post(500); g_objCommon.Show_MsgBox(1, "Transfer Z2 Up상태에서 작업가능합니다.."); return; }

			gData.nElevatorOpen[nEleNo] = 1;
			if (nEleNo == 1) { g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_1, 51); if (m_nWorkEleatorCase1==0) m_nWorkEleatorCase1 = 1; }
			if (nEleNo == 2) { g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_2, 51); if (m_nWorkEleatorCase2==0) m_nWorkEleatorCase2 = 1; }
			if (nEleNo == 3) { g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_3, 51); if (m_nWorkEleatorCase3==0) m_nWorkEleatorCase3 = 1; }
			if (nEleNo == 4) { g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_4, 51); if (m_nWorkEleatorCase4==0) m_nWorkEleatorCase4 = 1; }
			if (nEleNo == 5) { g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_5, 51); if (m_nWorkEleatorCase5==0) m_nWorkEleatorCase5 = 1; }
			if (nEleNo == 6) { g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_6, 51); if (m_nWorkEleatorCase6==0) m_nWorkEleatorCase6 = 1; }
			if (nEleNo == 7) { g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_7, 51); if (m_nWorkEleatorCase7==0) m_nWorkEleatorCase7 = 1; }

//			Begin_ElevatorRunThread();
	} else if (gData.nElevatorOpen[nEleNo] == 1) {
//			gData.nElevatorOpen[nEleNo] = 0;
//			g_objCommon.Show_MsgBox(1, "Elevator Open중입니다.  기다려 주세요."); return;
			return;
	} else if (gData.nElevatorOpen[nEleNo] == 2) {
			g_objCommon.Locking_TrayDoor(TRUE, nEleNo);
			g_objCommon.Locking_Slide(TRUE, nEleNo);
			gData.nElevatorOpen[nEleNo] = 0;

			if (nEleNo == 1) { g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z1, gData.dElevatorDown); m_nWorkEleatorCase1 = 0; }
			if (nEleNo == 2) { g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z2, gData.dElevatorDown); m_nWorkEleatorCase2 = 0; }
			if (nEleNo == 3) { g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z3, gData.dElevatorDown); m_nWorkEleatorCase3 = 0; }
			if (nEleNo == 4) { g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z4, gData.dElevatorDown); m_nWorkEleatorCase4 = 0; }
			if (nEleNo == 5) { g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z5, gData.dElevatorDown); m_nWorkEleatorCase5 = 0; }
			if (nEleNo == 6) { g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z6, gData.dElevatorDown); m_nWorkEleatorCase6 = 0; }
			if (nEleNo == 7) { g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z7, gData.dElevatorDown); m_nWorkEleatorCase7 = 0; }

			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13(); Sleep(500);
			if (nEleNo == 1) { pDY13->oElevator1Lamp = FALSE; }
			if (nEleNo == 2) { pDY13->oElevator2Lamp = FALSE; }
			if (nEleNo == 3) { pDY13->oElevator3Lamp = FALSE; }
			if (nEleNo == 4) { pDY13->oElevator4Lamp = FALSE; }
			if (nEleNo == 5) { pDY13->oElevator5Lamp = FALSE; }
			if (nEleNo == 6) { pDY13->oElevator6Lamp = FALSE; }
			if (nEleNo == 7) { pDY13->oElevator7Lamp = FALSE; }
			g_objAJinAXL.Write_Output(13);
	}

	sLog.Format("[Work Mode] ElevatorOpen button push. [%d-%d]", nEleNo, gData.nElevatorOpen[nEleNo]);
	g_objLogFile.Save_HandlerLog(sLog);
}

void CWorkDlg::Begin_ElevatorRunThread()
{
	if (m_pThreadElevatorRun) return;
	m_bThreadElevatorRun = TRUE;
	m_pThreadElevatorRun = AfxBeginThread(Thread_ElevatorRun, NULL);
}

void CWorkDlg::End_ElevatorRunThread()
{
	if (m_pThreadElevatorRun) {
		m_bThreadElevatorRun = FALSE;
		WaitForSingleObject(m_pThreadElevatorRun->m_hThread, INFINITE);
	}
}

UINT CWorkDlg::Thread_ElevatorRun(LPVOID lpVoid)
{
	DX_DATA_13 *pDX13 = g_objAJinAXL.Get_pDX13();
	while (g_dlgWork.m_bThreadElevatorRun) {
//		if (!g_objCommon.Check_ServoOn()) break;
//		if (!g_objCommon.Check_DirveAlarm()) break;
//		if (!g_objCommon.Check_EndLimit()) break;

		if (pDX13->iElevator1Sw) g_dlgWork.ElevatorOpen(1);
		if (pDX13->iElevator2Sw) g_dlgWork.ElevatorOpen(2);
		if (pDX13->iElevator3Sw) g_dlgWork.ElevatorOpen(3);
		if (pDX13->iElevator4Sw) g_dlgWork.ElevatorOpen(4);
		if (pDX13->iElevator5Sw) g_dlgWork.ElevatorOpen(5);
		if (pDX13->iElevator6Sw) g_dlgWork.ElevatorOpen(6);
		if (pDX13->iElevator7Sw) g_dlgWork.ElevatorOpen(7);

		if (!g_dlgWork.ElevatorOpen1()) break;
		if (!g_dlgWork.ElevatorOpen2()) break;
		if (!g_dlgWork.ElevatorOpen3()) break;
		if (!g_dlgWork.ElevatorOpen4()) break;
		if (!g_dlgWork.ElevatorOpen5()) break;
		if (!g_dlgWork.ElevatorOpen6()) break;
		if (!g_dlgWork.ElevatorOpen7()) break;

		Sleep(5);
	}

	g_dlgWork.m_bThreadElevatorRun = FALSE;
	g_dlgWork.m_pThreadElevatorRun = NULL;

	return 0;
}

BOOL CWorkDlg::ElevatorOpen1()
{
	int nElevNo = 1;
	int nMotionNo = AX_ELEVATOR_Z1;
	static DWORD dwSwitchTime1 = 0;

	if (gData.nElevatorOpen[nElevNo] != 1) return TRUE;
	if (m_nWorkEleatorCase1 > 1 && m_nWorkEleatorCase1 < 5) {
		if ((GetTickCount() - dwSwitchTime1) >= 400) {
			dwSwitchTime1 = GetTickCount();
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			if (pDY13->oElevator1Lamp == TRUE)	pDY13->oElevator1Lamp = FALSE;
			else								pDY13->oElevator1Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);
		}
	}

	switch (m_nWorkEleatorCase1) {
	case 0:		// Wait
		m_tWorkElevatorLoop1.Set_LoopTime(5000);
		return TRUE;

	case 1:
		dwSwitchTime1 = GetTickCount();
		g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen1 Start");
		m_nWorkEleatorCase1++; m_tWorkElevatorLoop1.Set_LoopTime(5000);
		break;

	case 2:
		g_objAJinAXL.Stop_Motion(nMotionNo);
		m_nWorkEleatorCase1++; m_tWorkElevatorLoop1.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			g_objAJinAXL.Move_Absolute(nMotionNo, gData.dElevatorDown);
			m_nWorkEleatorCase1++; m_tWorkElevatorLoop1.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			m_nWorkEleatorCase1++; m_tWorkElevatorLoop1.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			pDY13->oElevator1Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);

			g_objCommon.Locking_TrayDoor(FALSE, nElevNo);
			g_objCommon.Locking_Slide(FALSE, nElevNo);
			gData.nElevatorOpen[nElevNo] = 2;

			m_nWorkEleatorCase1 = 0; m_tWorkElevatorLoop1.Set_LoopTime(30000);
			g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen1 End");
		}
		break;
	}
	return TRUE;
}
BOOL CWorkDlg::ElevatorOpen2()
{
	int nElevNo = 2;
	int nMotionNo = AX_ELEVATOR_Z2;
	static DWORD dwSwitchTime2 = 0;

	if (gData.nElevatorOpen[nElevNo] != 1) return TRUE;
	if (m_nWorkEleatorCase2 > 1 && m_nWorkEleatorCase2 < 5) {
		if ((GetTickCount() - dwSwitchTime2) >= 400) {
			dwSwitchTime2 = GetTickCount();
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			if (pDY13->oElevator2Lamp == TRUE)	pDY13->oElevator2Lamp = FALSE;
			else								pDY13->oElevator2Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);
		}
	}

	switch (m_nWorkEleatorCase2) {
	case 0:		// Wait
		m_tWorkElevatorLoop2.Set_LoopTime(5000);
		return TRUE;

	case 1:
		dwSwitchTime2 = GetTickCount();
		g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen2 Start");
		m_nWorkEleatorCase2++; m_tWorkElevatorLoop2.Set_LoopTime(5000);
		break;

	case 2:
		g_objAJinAXL.Stop_Motion(nMotionNo);
		m_nWorkEleatorCase2++; m_tWorkElevatorLoop2.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			g_objAJinAXL.Move_Absolute(nMotionNo, gData.dElevatorDown);
			m_nWorkEleatorCase2++; m_tWorkElevatorLoop2.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			m_nWorkEleatorCase2++; m_tWorkElevatorLoop2.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			pDY13->oElevator2Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);

			g_objCommon.Locking_TrayDoor(FALSE, nElevNo);
			g_objCommon.Locking_Slide(FALSE, nElevNo);
			gData.nElevatorOpen[nElevNo] = 2;

			m_nWorkEleatorCase2 = 0; m_tWorkElevatorLoop2.Set_LoopTime(30000);
			g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen2 End");
		}
		break;
	}
	return TRUE;
}
BOOL CWorkDlg::ElevatorOpen3()
{
	int nElevNo = 3;
	int nMotionNo = AX_ELEVATOR_Z3;
	static DWORD dwSwitchTime3 = 0;

	if (gData.nElevatorOpen[nElevNo] != 1) return TRUE;
	if (m_nWorkEleatorCase3 > 1 && m_nWorkEleatorCase3 < 5) {
		if ((GetTickCount() - dwSwitchTime3) >= 400) {
			dwSwitchTime3 = GetTickCount();
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			if (pDY13->oElevator3Lamp == TRUE)	pDY13->oElevator3Lamp = FALSE;
			else								pDY13->oElevator3Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);
		}
	}

	switch (m_nWorkEleatorCase3) {
	case 0:		// Wait
		m_tWorkElevatorLoop3.Set_LoopTime(5000);
		return TRUE;

	case 1:
		dwSwitchTime3 = GetTickCount();
		g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen3 Start");
		m_nWorkEleatorCase3++; m_tWorkElevatorLoop3.Set_LoopTime(5000);
		break;

	case 2:
		g_objAJinAXL.Stop_Motion(nMotionNo);
		m_nWorkEleatorCase3++; m_tWorkElevatorLoop3.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			g_objAJinAXL.Move_Absolute(nMotionNo, gData.dElevatorDown);
			m_nWorkEleatorCase3++; m_tWorkElevatorLoop3.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			m_nWorkEleatorCase3++; m_tWorkElevatorLoop3.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			pDY13->oElevator3Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);

			g_objCommon.Locking_TrayDoor(FALSE, nElevNo);
			g_objCommon.Locking_Slide(FALSE, nElevNo);
			gData.nElevatorOpen[nElevNo] = 2;

			m_nWorkEleatorCase3 = 0; m_tWorkElevatorLoop3.Set_LoopTime(30000);
			g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen3 End");
		}
		break;
	}
	return TRUE;
}
BOOL CWorkDlg::ElevatorOpen4()
{
	int nElevNo = 4;
	int nMotionNo = AX_ELEVATOR_Z4;
	static DWORD dwSwitchTime4 = 0;

	if (gData.nElevatorOpen[nElevNo] != 1) return TRUE;
	if (m_nWorkEleatorCase4 > 1 && m_nWorkEleatorCase4 < 5) {
		if ((GetTickCount() - dwSwitchTime4) >= 400) {
			dwSwitchTime4 = GetTickCount();
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			if (pDY13->oElevator4Lamp == TRUE)	pDY13->oElevator4Lamp = FALSE;
			else								pDY13->oElevator4Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);
		}
	}

	switch (m_nWorkEleatorCase4) {
	case 0:		// Wait
		m_tWorkElevatorLoop4.Set_LoopTime(5000);
		return TRUE;

	case 1:
		dwSwitchTime4 = GetTickCount();
		g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen4 Start");
		m_nWorkEleatorCase4++; m_tWorkElevatorLoop4.Set_LoopTime(5000);
		break;

	case 2:
		g_objAJinAXL.Stop_Motion(nMotionNo);
		m_nWorkEleatorCase4++; m_tWorkElevatorLoop4.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			g_objAJinAXL.Move_Absolute(nMotionNo, gData.dElevatorDown);
			m_nWorkEleatorCase4++; m_tWorkElevatorLoop4.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			m_nWorkEleatorCase4++; m_tWorkElevatorLoop4.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			pDY13->oElevator4Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);

			g_objCommon.Locking_TrayDoor(FALSE, nElevNo);
			g_objCommon.Locking_Slide(FALSE, nElevNo);
			gData.nElevatorOpen[nElevNo] = 2;

			m_nWorkEleatorCase4 = 0; m_tWorkElevatorLoop4.Set_LoopTime(30000);
			g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen4 End");
		}
		break;
	}
	return TRUE;
}
BOOL CWorkDlg::ElevatorOpen5()
{
	int nElevNo = 5;
	int nMotionNo = AX_ELEVATOR_Z5;
	static DWORD dwSwitchTime5 = 0;

	if (gData.nElevatorOpen[nElevNo] != 1) return TRUE;
	if (m_nWorkEleatorCase5 > 1 && m_nWorkEleatorCase5 < 5) {
		if ((GetTickCount() - dwSwitchTime5) >= 400) {
			dwSwitchTime5 = GetTickCount();
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			if (pDY13->oElevator5Lamp == TRUE)	pDY13->oElevator5Lamp = FALSE;
			else								pDY13->oElevator5Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);
		}
	}

	switch (m_nWorkEleatorCase5) {
	case 0:		// Wait
		m_tWorkElevatorLoop5.Set_LoopTime(5000);
		return TRUE;

	case 1:
		dwSwitchTime5 = GetTickCount();
		g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen5 Start");
		m_nWorkEleatorCase5++; m_tWorkElevatorLoop5.Set_LoopTime(5000);
		break;

	case 2:
		g_objAJinAXL.Stop_Motion(nMotionNo);
		m_nWorkEleatorCase5++; m_tWorkElevatorLoop5.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			g_objAJinAXL.Move_Absolute(nMotionNo, gData.dElevatorDown);
			m_nWorkEleatorCase5++; m_tWorkElevatorLoop5.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			m_nWorkEleatorCase5++; m_tWorkElevatorLoop5.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			pDY13->oElevator5Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);

			g_objCommon.Locking_TrayDoor(FALSE, nElevNo);
			g_objCommon.Locking_Slide(FALSE, nElevNo);
			gData.nElevatorOpen[nElevNo] = 2;

			m_nWorkEleatorCase5 = 0; m_tWorkElevatorLoop5.Set_LoopTime(30000);
			g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen5 End");
		}
		break;
	}
	return TRUE;
}
BOOL CWorkDlg::ElevatorOpen6()
{
	int nElevNo = 6;
	int nMotionNo = AX_ELEVATOR_Z6;
	static DWORD dwSwitchTime6 = 0;

	if (gData.nElevatorOpen[nElevNo] != 1) return TRUE;
	if (m_nWorkEleatorCase6 > 1 && m_nWorkEleatorCase6 < 5) {
		if ((GetTickCount() - dwSwitchTime6) >= 400) {
			dwSwitchTime6 = GetTickCount();
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			if (pDY13->oElevator6Lamp == TRUE)	pDY13->oElevator6Lamp = FALSE;
			else								pDY13->oElevator6Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);
		}
	}

	switch (m_nWorkEleatorCase6) {
	case 0:		// Wait
		m_tWorkElevatorLoop6.Set_LoopTime(5000);
		return TRUE;

	case 1:
		dwSwitchTime6 = GetTickCount();
		g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen6 Start");
		m_nWorkEleatorCase6++; m_tWorkElevatorLoop6.Set_LoopTime(5000);
		break;

	case 2:
		g_objAJinAXL.Stop_Motion(nMotionNo);
		m_nWorkEleatorCase6++; m_tWorkElevatorLoop6.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			g_objAJinAXL.Move_Absolute(nMotionNo, gData.dElevatorDown);
			m_nWorkEleatorCase6++; m_tWorkElevatorLoop6.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			m_nWorkEleatorCase6++; m_tWorkElevatorLoop6.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			pDY13->oElevator6Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);

			g_objCommon.Locking_TrayDoor(FALSE, nElevNo);
			g_objCommon.Locking_Slide(FALSE, nElevNo);
			gData.nElevatorOpen[nElevNo] = 2;

			m_nWorkEleatorCase6 = 0; m_tWorkElevatorLoop6.Set_LoopTime(30000);
			g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen6 End");
		}
		break;
	}
	return TRUE;
}
BOOL CWorkDlg::ElevatorOpen7()
{
	int nElevNo = 7;
	int nMotionNo = AX_ELEVATOR_Z7;
	static DWORD dwSwitchTime7 = 0;

	if (gData.nElevatorOpen[nElevNo] != 1) return TRUE;
	if (m_nWorkEleatorCase7 > 1 && m_nWorkEleatorCase7 < 5) {
		if ((GetTickCount() - dwSwitchTime7) >= 400) {
			dwSwitchTime7 = GetTickCount();
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			if (pDY13->oElevator7Lamp == TRUE)	pDY13->oElevator7Lamp = FALSE;
			else								pDY13->oElevator7Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);
		}
	}

	switch (m_nWorkEleatorCase7) {
	case 0:		// Wait
		m_tWorkElevatorLoop7.Set_LoopTime(5000);
		return TRUE;

	case 1:
		dwSwitchTime7 = GetTickCount();
		g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen7 Start");
		m_nWorkEleatorCase7++; m_tWorkElevatorLoop7.Set_LoopTime(5000);
		break;

	case 2:
		g_objAJinAXL.Stop_Motion(nMotionNo);
		m_nWorkEleatorCase7++; m_tWorkElevatorLoop7.Set_LoopTime(5000);
		break;
	case 3:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			g_objAJinAXL.Move_Absolute(nMotionNo, gData.dElevatorDown);
			m_nWorkEleatorCase7++; m_tWorkElevatorLoop7.Set_LoopTime(30000);
		}
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			m_nWorkEleatorCase7++; m_tWorkElevatorLoop7.Set_LoopTime(30000);
		}
		break;
	case 5:
		if (g_objAJinAXL.Is_Done(nMotionNo)) {
			DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
			pDY13->oElevator7Lamp = TRUE;
			g_objAJinAXL.Write_Output(13);

			g_objCommon.Locking_TrayDoor(FALSE, nElevNo);
			g_objCommon.Locking_Slide(FALSE, nElevNo);
			gData.nElevatorOpen[nElevNo] = 2;

			m_nWorkEleatorCase7 = 0; m_tWorkElevatorLoop7.Set_LoopTime(30000);
			g_objLogFile.Save_HandlerLog("[Work Elevator] - ElevatorOpen7 End");
		}
		break;
	}

	return TRUE;
}

void CWorkDlg::DoEvents(int nSleep)
{
	MSG msg;
	if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (nSleep > 0) Sleep(nSleep);
}

void CWorkDlg::OnBnClickedButton1()
{
	DY_DATA_14 *pDY14 = g_objAJinAXL.Get_pDY14();

	if (pDY14->oInsideLight)	pDY14->oInsideLight = FALSE;
	else						pDY14->oInsideLight = TRUE;
	g_objAJinAXL.Write_Output(14);

	//double click //////////////////////////
	static int time = GetTickCount();
	static int cnt=0;
	if(GetTickCount()-time > 500){
		cnt = 0;
		time = GetTickCount();
	}

	if(cnt == 1){
		cnt = 0;
		time = GetTickCount();
	} else {
		cnt++;
		time = GetTickCount();
		return;
	}
	////////////////////////////////////////
}

void CWorkDlg::Clear_MainLotID()
{
	for(int i=0; i<6; i++) {
		m_stcLotsIdS[i].SetWindowText("");
		m_stcCmsCountS[i].SetWindowText("");
		m_stcTrayCountS[i].SetWindowText("");
		gLot.sLotID[i] = "";
	}
}

void CWorkDlg::OnBnClickedBtnNGLotEnd()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseMES) {
		AfxMessageBox(_T("MES 사용 설정 상태에서 작업이 가능합니다....."));
		return;
	}

	if (gMes.nMarStatus != 2) {
		AfxMessageBox(_T("NG-Lot 작업중에만 수동 완공처리가 가능합니다....."));
		return;
	}
	if (gMes.nManualEnd == 1) {
		AfxMessageBox(_T("NG-Lot 수동완공 진행중입니다....."));
		return;
	}

	if (g_objCommon.Show_MsgBox(2, "NG-Lot 수동 완공처리를 하시겠습니까?") != IDOK) return;

	int nCase1 = g_objSequenceMain.Get_MainRunCase(AUTO_UNLOAD_PICKER_1);
	int nCase2 = g_objSequenceMain.Get_MainRunCase(AUTO_UNLOAD_PICKER_2);

	CString sLog;
	if ((nCase1 == 0 && nCase2 == 50) || (nCase1 == 50 && nCase2 == 0)) {
		g_objMesAgent.Set_NGLotEnd(gMes.sHostNGLotID, gMes.nMarCount);
		gMes.nManualEnd = 0;

		sLog.Format("[Woark_NGLot-End] NGLot(%s) NGLot(%d-%d-%d-%d)",
				gMes.sHostNGLotID, gMes.nMarCount, gMes.nMarTrayCount, gData.nMgnTrayCount, gMes.nMarStatus);
		g_objLogFile.Save_HandlerLog(sLog);

		sLog.Format("NG-Lot 수동완공 되었습니다..\nNG-Lot(%s)\nNG수량(%d) Marginal수량(%d)\n바코드 NoRead 수량(%d)", gMes.sHostNGLotID, gMes.nNGLotCount-gMes.nMarCount, gMes.nMarCount, gMes.nNoReadCount);
		g_objCommon.Show_Alarm(sLog);
	} else {
		gMes.nManualEnd = 1;
	}
	
	sLog.Format("[Work NGLot-End] - NGLot(%s) Seq(%d-%d) Sts(%d) 수량(%d-%d-%d) Flag(%d)", gMes.sHostNGLotID, nCase1, nCase2, gMes.nMarStatus, gMes.nNGLotCount, gMes.nMarCount, gMes.nMarTrayCount, gMes.nManualEnd);
	g_objLogFile.Save_HandlerLog(sLog);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CWorkDlg::OnBnClickedButton2()
{
//	gLot.nJobNo = 0;
//	g_dlgWork.PostMessage(UM_UPDATE_UPH, 0, NULL);
//	g_objSequenceMain.Set_MainRunCase(AUTO_TRANSFER_1, 0);
//	g_objCommon.Show_Error(3501);
	/*
	gLot.nJobNo = 9;
	gLot.nJobPortNo[8] = 1;
	gLot.sJobLotID[8] = "aaa";
	gLot.nJobCmCount[8] = 1;
	gLot.nJobGoodCount[8] = 1;
	gLot.nJobNgCount[8] = 1;
	gLot.dJobRate[8] = 1.1;
	gLot.sJobStartTime[8] = "aaa";
	gLot.sJobEndTime[8] = "bbbb";
	gLot.dJobTack[8] = 1.222;
	
	
	CString sLog;
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			gData.InfoAlignTray[i][j] = gData.InfoLoadTray[i][j] = gData.InfoNgTray[i][j] = gData.InfoGoodTray[i][j] = 0;
		}
	}
	for(int i=0; i<1; i++) {
		gData.InfoAlignTray[i][0] = gData.InfoLoadTray[i][0] = gData.InfoNgTray[i][0] = gData.InfoGoodTray[i][0] = 1;
		gData.InfoAlignTray[i][1] = gData.InfoLoadTray[i][1] = gData.InfoNgTray[i][1] = gData.InfoGoodTray[i][1] = 2;
	}
	for(int i=1; i<2; i++) {
		for(int j=0; j<2; j++) {
			gData.InfoAlignTray[i][j] = gData.InfoLoadTray[i][j] = gData.InfoNgTray[i][j] = gData.InfoGoodTray[i][j] = 2;
		}
	}
	for(int i=2; i<3; i++) {
		for(int j=0; j<2; j++) {
			gData.InfoAlignTray[i][j] = gData.InfoLoadTray[i][j] = gData.InfoNgTray[i][j] = gData.InfoGoodTray[i][j] = 3;
		}
	}
	
//	ElevatorOpen(2);

	for(int i=0; i<4; i++) {
		for(int j=0; j<3; j++) {
			gData.dAlignVisionX[i][j] = 0.1;
			gData.dAlignVisionY[i][j] = 0.1;
		}
	}

	int    nPickerNo, nJobNo, nPosX, nPosY, nModuleNo;
	double dx, dy;
	nPickerNo = 2;	nJobNo    = 1;	nModuleNo = 1;
	nPosX     = 1;	nPosY     = 1;
	g_objSequenceMain.Get_TrayPosition(nPickerNo, nJobNo, nPosX, nPosY, dx, dy);
	dx = dx + (30.0 * (nModuleNo - nPosX));
	sLog.Format("A2 Data [Picker:%d Job:%d Option:%d] PosXY(%d,%d) => (%0.3lf,%0.3lf)", nPickerNo, nJobNo, nModuleNo, nPosX, nPosY, dx, dy);
	g_objLogFile.Save_HandlerLog(sLog);

	nPickerNo = 2;	nJobNo    = 1;	nModuleNo = 1;
	nPosX     = 4;	nPosY     = 1;
	g_objSequenceMain.Get_TrayPosition(nPickerNo, nJobNo, nPosX, nPosY, dx, dy);
	dx = dx + (30.0 * (nModuleNo - nPosX));
	sLog.Format("A2 Data [Picker:%d Job:%d Option:%d] PosXY(%d,%d) => (%0.3lf,%0.3lf)", nPickerNo, nJobNo, nModuleNo, nPosX, nPosY, dx, dy);
	g_objLogFile.Save_HandlerLog(sLog);

	nPickerNo = 2;	nJobNo    = 1;	nModuleNo = 4;
	nPosX     = 4;	nPosY     = 1;
	g_objSequenceMain.Get_TrayPosition(nPickerNo, nJobNo, nPosX, nPosY, dx, dy);
	dx = dx + (30.0 * (nModuleNo - nPosX));
	sLog.Format("A2 Data [Picker:%d Job:%d Option:%d] PosXY(%d,%d) => (%0.3lf,%0.3lf)", nPickerNo, nJobNo, nModuleNo, nPosX, nPosY, dx, dy);
	g_objLogFile.Save_HandlerLog(sLog);

	nPickerNo = 2;	nJobNo    = 1;	nModuleNo = 8;
	nPosX     = 4;	nPosY     = 1;
	g_objSequenceMain.Get_TrayPosition(nPickerNo, nJobNo, nPosX, nPosY, dx, dy);
	dx = dx + (30.0 * (nModuleNo - nPosX));
	sLog.Format("A2 Data [Picker:%d Job:%d Option:%d] PosXY(%d,%d) => (%0.3lf,%0.3lf)", nPickerNo, nJobNo, nModuleNo, nPosX, nPosY, dx, dy);
	g_objLogFile.Save_HandlerLog(sLog);
*/

}

void CWorkDlg::OnBnClickedBtnBuzzerOff()
{
	g_objCommon.BuzzerOff();

#ifdef AJIN_BOARD_USE
	return;
#endif

//	g_objCommon.Show_Alarm("Alarm Message Test", 0);
/*
	CString sBar[5], sBarData, sData;
	sBar[0] = "LG5F03501YA630D3QW5+CCQQR02102+1";
	sBar[1] = "LG5F03502C0Q30D3QW5+CCQQR00224+1";
	sBar[2] = "LG5F035027Y930D3QW5+CCQQR03721+1";
	sBar[3] = "LG5F06101BY4AVITEST+DDQPR05216+1";
	sBar[4] = "barcde";
	
	g_objCommon.BarcodeRead();

	CString sMsg;
	sMsg.Format("%d/%d", g_objCommon.BarcodeFind(sBar[3]), gBar.nCount);	AfxMessageBox(sMsg);
	sMsg.Format("%d/%d", g_objCommon.BarcodeFind(sBar[0]), gBar.nCount);	AfxMessageBox(sMsg);

/*
	int nNo = 0;
	gMes.sHostRecipe[nNo] = "RECIPE"; 
	gMes.nHostCmCount[nNo] = 100;
	gLot.nGoodCount[nNo] = 90;
	gLot.nNgCount[nNo] = 10;
	gLot.nRosJugCount[nNo][0] = 10;
	gLot.nRosJugCount[nNo][1] = 11;
	gLot.nRosJugCount[nNo][3] = 13;
	gLot.nRosJugCount[nNo][2] = 12;
	gLot.nRosJugCount[nNo][4] = 14;
	gLot.nRosJugCount[nNo][10] = 20;
	g_objMesAgent.Set_LotEnd(1, "AAAAA", "1", "2", "3", "4", "5");
*/
//	g_objSequenceMain.Set_ClearRunData(1);
//	g_dlgWork.PostMessage(UM_JOB_COMPELTE, NULL, NULL);
//	g_dlgWork.PostMessage(UM_LOT_END_MSG, 1, 9);
//	g_objCommon.Show_Error(9310);
/*
	CString sLog, sNGCode20[3];
	sNGCode20[0] = "";
	for(int i=0; i<5; i++) {
		if (i==0) sNGCode20[1] = "B1";
		if (i==1) sNGCode20[1] = "AG";
		if (i==2) sNGCode20[1] = "T1";
		if (i==3) sNGCode20[1] = "TG";
		if (i==4) sNGCode20[1] = "T2";
		for(int j=0; j<20; j++) {
			sNGCode20[2].Format(",%sNGCode%02d", sNGCode20[1], j+1);
			sNGCode20[0] = sNGCode20[0] + sNGCode20[2];
		}
	}
	AfxMessageBox(sNGCode20[0]);
*/
/*	
	CString sLog, sData, sData1, sData2, sData3, sData4;
	sData1 = "INSPECT,COMPLETE,AG,GPSAA1BBDC6A4A,1,2,16,G,G,0";
	sData2 = "INSPECT,COMPLETE,B1,GPSAA1BBDC6A4A,1,2,12,N,AB_B_DA,1";
	sData3 = "INSPECT,COMPLETE,B1,GPSAA1BBDC6A4A,1,2,12,N,AB_B_DA,1,,,,,,,,,,,,,,,,,,,,";
	sData4 = "INSPECT,COMPLETE,B1,GPSAA1BBDC6A4A,1,2,12,N,AB_B_DA,1,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,20";

	sData = sData4;
	CString strArg[10];
	for (int i = 0; i < 20; i++) AfxExtractSubString(gNG->sNGCode[0][0][0][0][i], sData, i + 10, ',');
	sLog.Format("[%s] [%s] [%s]", gNG->sNGCode[0][0][0][0][0], gNG->sNGCode[0][0][0][0][9], gNG->sNGCode[0][0][0][0][19]);
	AfxMessageBox(sLog);
*/
//	g_objInspector.Get_ConnectEnd(INSPECTOR_PC5);

//	g_objCommon.Show_Error(5001);
//	g_objCommon.Show_Error(5002);
//	g_objCommon.Show_Error(7007);
/*
	CString sLog, sData, sData1;
	sLog = "aaa,bbb";
	int nNo = sLog.Find(",");
	sData = sLog.Left(nNo);
	sData1 = sData;

	CString sLog;
	m_stcCmsCountS[0].GetWindowText(sLog);
	int nNo = atoi(sLog);
	int nPosX = nNo % TRAY_CM_X;	if (nPosX==0) nPosX = 4;
	int nPosY = nNo / TRAY_CM_X;	if (nPosX!=4) nPosY++;
	sLog.Format("[%d]  y[%d] x[%d]", nNo, nPosY, nPosX);
	AfxMessageBox(sLog);
*/
//	g_objCommon.Show_Error(9002);
/*
	g_objCommon.Show_Error(5010);
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	pDX00->iElevator1SlideClose = TRUE;
	pDX00->iElevator2SlideClose = TRUE;
	pDX01->iElevator3SlideClose = TRUE;
	pDX01->iElevator4SlideClose = TRUE;
	pDX02->iElevator5SlideClose = TRUE;
	pDX02->iElevator6SlideClose = TRUE;
	pDX02->iElevator7SlideClose = TRUE;
*/
//	g_objInspector.Set_MoveComplete(INSPECTOR_PC1, "B1");
//	ElevatorOpen(1);
//	ElevatorOpen(7);
//	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
//	pMainDlg->StdLogAllDelete();
}
