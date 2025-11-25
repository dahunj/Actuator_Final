// CMAI2100Dlg.cpp : 구현 파일
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "CMAI2100Dlg.h"
#include "afxdialogex.h"
#include "SplashDlg.h"
#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "OperatorDlg.h"
#include "InitialDlg.h"
#include "WorkDlg.h"
#include "ManualDlg.h"
#include "SetupDlg.h"
#include "ProhibitDlg.h"
#include "MonitorDlg.h"
#include "ErrorDlg.h"
#include "AlarmDlg.h"
#include "Inspector.h"
#include "MesAgent.h"
#include "Dispatcher.h"
#include "BarcodeLot.h"
#include "SequenceInit.h"
#include "SequenceMain.h"
#include "NoWorkDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCMAI2100Dlg 대화 상자

CCMAI2100Dlg::CCMAI2100Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCMAI2100Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCMAI2100Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMG_LG_LOGO, m_imgLgLogo);
	DDX_Control(pDX, IDC_PIC_MAIN_LOGO, m_picMainLogo);
	DDX_Control(pDX, IDC_STC_MAIN_EQUIP, m_stcMainEquip);
	DDX_Control(pDX, IDC_STC_MAIN_MODE, m_stcMainMode);
	DDX_Control(pDX, IDC_STC_MAIN_OP_ENG, m_stcMainOpEng);
	DDX_Control(pDX, IDC_STC_MAIN_DATE, m_stcMainDate);
	DDX_Control(pDX, IDC_STC_MAIN_TIME, m_stcMainTime);
	DDX_Control(pDX, IDC_STC_MAIN_VER, m_stcMainVer);
	DDX_Control(pDX, IDC_STC_DOOR_LOCK, m_stcDoorLock);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_MAIN_TOWER_0 + i, m_stcMainTower[i]);
	DDX_Control(pDX, IDC_PIC_MODE_BACK, m_picModeBack);
	DDX_Control(pDX, IDC_BTN_MAIN_OPERATOR, m_btnMainOperator);
	DDX_Control(pDX, IDC_RDO_MAIN_INITIAL, m_rdoMainInitial);
	DDX_Control(pDX, IDC_RDO_MAIN_WORK, m_rdoMainWork);
	DDX_Control(pDX, IDC_RDO_MAIN_MANUAL, m_rdoMainManual);
	DDX_Control(pDX, IDC_RDO_MAIN_SETUP, m_rdoMainSetup);
	DDX_Control(pDX, IDC_RDO_MAIN_PROHIBIT, m_rdoMainProhibit);
	DDX_Control(pDX, IDC_BTN_MAIN_MONITOR, m_btnMainMonitor);
	DDX_Control(pDX, IDC_BTN_MAIN_EXIT, m_btnMainExit);
}

BEGIN_MESSAGE_MAP(CCMAI2100Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_MAIN_OPERATOR, &CCMAI2100Dlg::OnBnClickedBtnMainOperator)
	ON_BN_CLICKED(IDC_RDO_MAIN_INITIAL, &CCMAI2100Dlg::OnBnClickedRdoMainInitial)
	ON_BN_CLICKED(IDC_RDO_MAIN_WORK, &CCMAI2100Dlg::OnBnClickedRdoMainWork)
	ON_BN_CLICKED(IDC_RDO_MAIN_MANUAL, &CCMAI2100Dlg::OnBnClickedRdoMainManual)
	ON_BN_CLICKED(IDC_RDO_MAIN_SETUP, &CCMAI2100Dlg::OnBnClickedRdoMainSetup)
	ON_BN_CLICKED(IDC_RDO_MAIN_PROHIBIT, &CCMAI2100Dlg::OnBnClickedRdoMainProhibit)
	ON_BN_CLICKED(IDC_BTN_MAIN_MONITOR, &CCMAI2100Dlg::OnBnClickedBtnMainMonitor)
	ON_BN_CLICKED(IDC_BTN_MAIN_EXIT, &CCMAI2100Dlg::OnBnClickedBtnMainExit)
	ON_STN_DBLCLK(IDC_IMG_LG_LOGO, &CCMAI2100Dlg::OnStnClickedImgLgLogo)
END_MESSAGE_MAP()

// CCMAI2100Dlg 메시지 처리기

BOOL CCMAI2100Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetWindowText("CMAI2100_Handler");

	Initial_Controls();

	m_bTowerOn = FALSE;
	m_bBuzzerOn = FALSE;

	m_dwEquipRunStart = 0;

	g_objCommon.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);
	g_objInspector.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);
	g_objBarcodeLot.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);
	g_objMesAgent.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);
	g_objDispatcher.Create(NULL, NULL, WS_CHILD, CRect(0,0,0,0), this, 0);

	g_dlgOperator.Create(COperatorDlg::IDD, this);
	g_dlgInitial.Create(CInitialDlg::IDD, this);
	g_dlgWork.Create(CWorkDlg::IDD, this);
	g_dlgManual.Create(CManualDlg::IDD, this);
	g_dlgSetup.Create(CSetupDlg::IDD, this);
	g_dlgProhibit.Create(CProhibitDlg::IDD, this);
	g_dlgMonitor.Create(CMonitorDlg::IDD, this);
	g_dlgError.Create(CErrorDlg::IDD, this);
	g_dlgAlarm.Create(CAlarmDlg::IDD, this);
	g_dlgNoWork.Create(CNoWorkDlg::IDD, this);

	CString strLog;
	strLog.Format("[Main Dialog] Program Start.  Version: %s", MAIN_VERSION);
	g_objLogFile.Save_HandlerLog(strLog);

	SetTimer(TIMER_DATE_TIME, 500, NULL);
	SetTimer(TIMER_SLIDE_CHECK, 900, NULL);
	SetTimer(TIMER_DOOR_LOCK, 1000, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCMAI2100Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCMAI2100Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CCMAI2100Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CCMAI2100Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	g_objInspector.Set_StatusUpdate(INSPECTOR_ALL, 0);
	g_objDispatcher.Set_StatusUpdate(0);	// 0:Stop, 1:Run, 2:Error

	g_dlgAlarm.DestroyWindow();
	g_dlgError.DestroyWindow();
	g_dlgMonitor.DestroyWindow();
	g_dlgProhibit.DestroyWindow();
	g_dlgSetup.DestroyWindow();
	g_dlgManual.DestroyWindow();
	g_dlgWork.DestroyWindow();
	g_dlgInitial.DestroyWindow();
	g_dlgOperator.DestroyWindow();
	g_dlgNoWork.DestroyWindow();

	g_objBarcodeLot.DestroyWindow();
	g_objInspector.DestroyWindow();
	g_objDispatcher.DestroyWindow();
	g_objMesAgent.DestroyWindow();
	g_objCommon.DestroyWindow();
}

void CCMAI2100Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	CSplashDlg dlgSplash;
	dlgSplash.Create(IDD_SPLASH_DLG, NULL);
	dlgSplash.ShowWindow(SW_SHOW);

	char myCom[256];
	gethostname(myCom, sizeof(myCom));
	gData.sComName.Format("%s", myCom);
	g_objCommon.MakeFolder(ECM_LOG);
	g_objCommon.MakeFolder(ECM_ME_LOG);
	g_objLogFile.Save_Interlock(0);

	g_objDataManager.Read_EquipData();
	g_objDataManager.Read_MoveData();
	g_objDataManager.Read_IdleData();
	g_objDataManager.Read_RosData();

	if (!g_objAJinAXL.Initialize()) { Exit_System(EXIT_SYSTEM_AJIN); return; }

	g_objInspector.Initialize();
	g_objDispatcher.Initialize();

//	CIniFileCS INI_MES("D:\\MESAgent\\Run\\System\\Config.ini");
//	gCM.nPortClient = INI_MES.Get_Integer("SERVER", "HANDLER_PORT", 0);

	CIniFileCS INI_EQP(gsCurrentDir + "\\System\\EquipData.ini");
	if (!INI_EQP.Check_File()) {
		gData.nDay_TotalCnt = 0;
		gData.nDay_NGCnt = 0;
		gData.nDay_GoodCnt = 0;
	} else {
		gData.nDay_TotalCnt = INI_EQP.Get_Integer("DAY_TOTAL", "COUNT", 0);
		gData.nDay_NGCnt = INI_EQP.Get_Integer("DAY_TOTAL", "NG_COUNT", 0);
		gData.nDay_GoodCnt = INI_EQP.Get_Integer("DAY_TOTAL", "GOOD_COUNT", 0);
	}

	g_objMesAgent.Initialize();
//	if (!g_objBarcodeLot.Initialize()) { Exit_System(EXIT_SYSTEM_BARCODE); return; }
	if (!g_objBarcodeLot.Initialize()) {
		if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "바코드 초기화를 실패했습니다.");
		else					  g_objCommon.Show_MsgBox(1, "Fail to barcode initialization.");
	}

	Display_EquipName();
	if (g_objCommon.Read_FocusOffset() == FALSE) {
		g_objCommon.Show_MsgBox(1, "Vision Stage Offset 파일을 확인해 주세요.");
	}

	CString strVersion;
	strVersion.Format("%s", MAIN_VERSION);
	m_stcMainVer.SetWindowText(strVersion);

	m_rdoMainInitial.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	g_objInspector.Set_StatusUpdate(INSPECTOR_ALL, 0);
	g_objInspector.Set_StatusRequest(INSPECTOR_ALL);
	g_objDispatcher.Set_StatusUpdate(0);	// 0:Stop, 1:Run, 2:Error
	if (gData.bUseDryRun) {
		DY_DATA_14 *pDY14 = g_objAJinAXL.Get_pDY14();
		pDY14->oInsideLight = TRUE;
		g_objAJinAXL.Write_Output(0);
	}
	for(int i=0; i<7; i++) gData.dwSlideTime[i] = 0;
	gBar.nCount = gMes.nMarStatus = gMes.nManualEnd = 0;
	gMes.sHostNGConfig = "";

	theApp.uSleep(1000);

	Clear_JobData();
	dlgSplash.DestroyWindow();
	gData.nSelectNo = 1;
	Set_MainState(STATE_NONE);
	Set_CurrentMode(MODE_INITIAL);
}

void CCMAI2100Dlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent) {
	case TIMER_DATE_TIME:
		Display_DateTime();
		g_objCommon.Check_InsideLamp();
		g_objCommon.Check_MainDoor();
		if (!gData.bUseDryRun) {
			Set_NoWork();
		}
		break;
	case TIMER_TOWER_FLKR:
		Set_TowerFlicker(TRUE);
		break;
	case TIMER_SLIDE_CHECK:
		Check_SlideOpen();
		break;
	case TIMER_DOOR_LOCK:
		Set_DoorLock();
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CCMAI2100Dlg::OnBnClickedBtnMainOperator()
{
	if (m_nMainMode == MODE_PROHIBIT) {
		int nUser = 0;
		if (g_objCommon.Show_Password(nUser) == IDOK) {
			if (nUser != 3) return;
		} else {
			return;
		}
	}
	if (m_nMainMode == MODE_OPERATOR) {
		int nUser = 0;
		if (g_objCommon.Show_Password(nUser) == IDOK) {
//			g_dlgSetup.Set_LoginUser(nUser);
			Set_CurrentMode(MODE_WORK);
		}
	} else {
		Set_CurrentMode(MODE_OPERATOR);
	}
}

void CCMAI2100Dlg::OnBnClickedRdoMainInitial()
{
	if (m_nMainMode == MODE_PROHIBIT) {
		int nUser = 0;
		if (g_objCommon.Show_Password(nUser) == IDOK) {
			if (nUser != 3) return;
		} else {
			return;
		}
	}
	Set_CurrentMode(MODE_INITIAL);
}

void CCMAI2100Dlg::OnBnClickedRdoMainWork()
{
	if (m_nMainMode == MODE_PROHIBIT) {
		int nUser = 0;
		if (g_objCommon.Show_Password(nUser) == IDOK) {
			if (nUser != 3) return;
		} else {
			return;
		}
	}
	Set_CurrentMode(MODE_WORK);
}

void CCMAI2100Dlg::OnBnClickedRdoMainManual()
{
	if (m_nMainMode == MODE_PROHIBIT) {
		int nUser = 0;
		if (g_objCommon.Show_Password(nUser) == IDOK) {
			if (nUser != 3) return;
		} else {
			return;
		}
	}
	Set_CurrentMode(MODE_MANUAL);
}

void CCMAI2100Dlg::OnBnClickedRdoMainSetup()
{
	if (gData.bUseDryRun) {
		g_dlgSetup.Set_LoginUser(2);	// SI
		Set_CurrentMode(MODE_SETUP);
		return;
	}

	if (m_nMainMode == MODE_PROHIBIT) {
		int nUser = 0;
		if (g_objCommon.Show_Password(nUser) == IDOK) {
			if (nUser != 3) return;
		} else {
			return;
		}
	}

	int nUser = 0;
	if (g_objCommon.Show_Password(nUser) == IDOK) {
		g_dlgSetup.Set_LoginUser(nUser);
		Set_CurrentMode(MODE_SETUP);

	} else {
		if (m_nMainMode == MODE_INITIAL) m_rdoMainInitial.SetCheck(TRUE);
		if (m_nMainMode == MODE_WORK) m_rdoMainWork.SetCheck(TRUE);
		if (m_nMainMode == MODE_MANUAL) m_rdoMainManual.SetCheck(TRUE);
		if (m_nMainMode == MODE_SETUP) m_rdoMainSetup.SetCheck(TRUE);
		if (m_nMainMode == MODE_PROHIBIT) m_rdoMainProhibit.SetCheck(TRUE);
	}
}

void CCMAI2100Dlg::OnBnClickedRdoMainProhibit()
{
	Set_CurrentMode(MODE_PROHIBIT);
}

void CCMAI2100Dlg::OnBnClickedBtnMainMonitor()
{
	if (g_dlgMonitor.IsWindowVisible()) g_dlgMonitor.ShowWindow(SW_HIDE);
	else g_dlgMonitor.ShowWindow(SW_SHOW);	
}

void CCMAI2100Dlg::OnBnClickedBtnMainExit()
{
	if (gMes.nMarStatus == 2) {
		AfxMessageBox(_T("NG-Lot 미완공 정보가 있습니다. 수동완공후 종료가능합니다..."));
		return;
	}

	if (gData.nLanguage == 0) {
		if (g_objCommon.Show_MsgBox(2, "프로그램을 종료 하시겠습니까?") != IDOK) return;
	} else {
		if (g_objCommon.Show_MsgBox(2, "Do you want to exit the program?") != IDOK) return;
	}
	
	Exit_System(EXIT_SYSTEM_NONE);
}

/////////////////////////////////////////////////////////////////////////////
// User Functions

void CCMAI2100Dlg::Initial_Controls() 
{
	CIniFileCS INI_EQP(gsCurrentDir + "\\System\\EquipData.ini");
	gData.bJahwa = INI_EQP.Get_Bool("EQUIPMENT", "JAHWA", FALSE);

	if (gData.bJahwa) m_bmpLgLogo.LoadBitmap(IDB_JAHWA_LOGO);
	else			  m_bmpLgLogo.LoadBitmap(IDB_LGINNOTEK_LOGO);
	m_imgLgLogo.SetBitmap(m_bmpLgLogo);
	m_imgLgLogo.SetWindowPos(this, 5, 8, 315, 60, SWP_NOZORDER);

	m_picMainLogo.Init_Ctrl(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xFF));
	m_stcMainEquip.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcMainMode.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcMainOpEng.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcMainDate.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcMainTime.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcMainVer.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	m_stcDoorLock.Init_Ctrl("Segoe UI", 20, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	for (int i = 0; i < 3; i++) m_stcMainTower[i].Init_Ctrl("Segoe UI", 14, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xFF));

	if (gData.bUseDryRun) m_stcMainEquip.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));

	m_picModeBack.Init_Ctrl(COLOR_DEFAULT, COLOR_DEFAULT);
	m_btnMainOperator.Init_Ctrl("Segoe UI", 14, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoMainInitial.Init_Ctrl("Segoe UI", 14, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoMainWork.Init_Ctrl("Segoe UI", 14, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoMainManual.Init_Ctrl("Segoe UI", 14, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoMainSetup.Init_Ctrl("Segoe UI", 14, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_rdoMainProhibit.Init_Ctrl("Segoe UI", 14, TRUE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_btnMainMonitor.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0xA0, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnMainExit.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
}

void CCMAI2100Dlg::Hide_ModeWindows(int nMode)
{
	m_rdoMainInitial.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMainWork.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMainManual.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMainSetup.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
	m_rdoMainProhibit.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

	int nShow = (nMode == MODE_OPERATOR ? SW_HIDE : SW_SHOW);
	m_rdoMainInitial.ShowWindow(nShow);
	m_rdoMainWork.ShowWindow(nShow);
	m_rdoMainManual.ShowWindow(nShow);
	m_rdoMainSetup.ShowWindow(nShow);
	m_rdoMainProhibit.ShowWindow(nShow);
	m_btnMainMonitor.ShowWindow(nShow);

	if (m_nMainMode == MODE_OPERATOR) g_dlgOperator.ShowWindow(SW_HIDE);
	if (m_nMainMode == MODE_INITIAL) g_dlgInitial.ShowWindow(SW_HIDE);
	if (m_nMainMode == MODE_WORK) g_dlgWork.ShowWindow(SW_HIDE);
	if (m_nMainMode == MODE_MANUAL) g_dlgManual.ShowWindow(SW_HIDE);
	if (m_nMainMode == MODE_SETUP) g_dlgSetup.ShowWindow(SW_HIDE);
	if (m_nMainMode == MODE_PROHIBIT) g_dlgProhibit.ShowWindow(SW_HIDE);
}

///////////////////////////////////////////////////////////////////////////////

void CCMAI2100Dlg::Set_CurrentMode(int nMode)
{
	if (m_nMainMode == nMode) return;
	Hide_ModeWindows(nMode);

	m_nMainMode = nMode;

	if (m_nMainMode == MODE_OPERATOR) m_btnMainOperator.SetWindowText("Engineer");
	else m_btnMainOperator.SetWindowText("Operator");

	if (m_nMainMode == MODE_OPERATOR) {
		g_dlgOperator.ShowWindow(SW_SHOW);
		m_stcMainMode.SetWindowText("Operator");
		m_stcMainOpEng.SetWindowText("Operator Mode");
		m_rdoMainInitial.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
// 		if (!m_rdoMainInitial.GetCheck()) m_rdoMainInitial.SetCheck(TRUE);
// 		g_objLogFile.Save_HandlerLog("[Main Dialog] Initial Mode start");

	} else if (m_nMainMode == MODE_INITIAL) {
		g_dlgInitial.ShowWindow(SW_SHOW);
		m_stcMainMode.SetWindowText("Initial");
		m_stcMainOpEng.SetWindowText("Engineer Mode");
		m_rdoMainInitial.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainInitial.GetCheck()) m_rdoMainInitial.SetCheck(TRUE);
		g_objLogFile.Save_HandlerLog("[Main Dialog] Initial Mode start");

	} else if (m_nMainMode == MODE_WORK) {
		g_dlgWork.ShowWindow(SW_SHOW);
		m_stcMainMode.SetWindowText("Main");
		m_stcMainOpEng.SetWindowText("Engineer Mode");
		m_rdoMainWork.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainWork.GetCheck()) m_rdoMainWork.SetCheck(TRUE);
		g_objLogFile.Save_HandlerLog("[Main Dialog] Work Mode start");

	} else if (m_nMainMode == MODE_MANUAL) {
		g_dlgManual.ShowWindow(SW_SHOW);
		m_stcMainMode.SetWindowText("Manual");
		m_stcMainOpEng.SetWindowText("Engineer Mode");
		m_rdoMainManual.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainManual.GetCheck()) m_rdoMainManual.SetCheck(TRUE);
		g_objLogFile.Save_HandlerLog("[Main Dialog] Manual Mode start");

	} else if (m_nMainMode == MODE_SETUP) {
		g_dlgSetup.ShowWindow(SW_SHOW);
		m_stcMainMode.SetWindowText("Setup");
		m_stcMainOpEng.SetWindowText("Engineer Mode");
		m_rdoMainSetup.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainSetup.GetCheck()) m_rdoMainSetup.SetCheck(TRUE);
		g_objLogFile.Save_HandlerLog("[Main Dialog] Setup Mode start");

	} else if (m_nMainMode == MODE_PROHIBIT) {
		g_dlgProhibit.ShowWindow(SW_SHOW);
		m_stcMainMode.SetWindowText("Prohibit");
		m_stcMainOpEng.SetWindowText("Engineer Mode");
		m_rdoMainProhibit.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
		if (!m_rdoMainProhibit.GetCheck()) m_rdoMainProhibit.SetCheck(TRUE);
		g_objLogFile.Save_HandlerLog("[Main Dialog] Prohibit Start");
	}
}

void CCMAI2100Dlg::Set_MainState(int nState)
{
	KillTimer(TIMER_TOWER_FLKR);

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();

	gData.m_nMS = nState;
	gData.m_bTowerOn = gData.m_bBuzzerOff = FALSE;

	// Tower
	pDY13->oTowerGreen1 = pDY13->oTowerGreen2 = pEquipData->bTower[gData.m_nMS][0];
	pDY13->oTowerYellow1 = pDY13->oTowerYellow2 = pEquipData->bTower[gData.m_nMS][1];
	pDY13->oTowerRed1 = pDY13->oTowerRed2 = pEquipData->bTower[gData.m_nMS][2];

	// Buzzer
	BOOL bBuzzer1 = pEquipData->bTower[gData.m_nMS][4];
	BOOL bBuzzer2 = pEquipData->bTower[gData.m_nMS][5];

	if (bBuzzer1 == FALSE && bBuzzer2 == FALSE) {
		pDY13->oBuzzerBit0 = FALSE;
		pDY13->oBuzzerBit1 = FALSE;
		pDY13->oBuzzerBit2 = FALSE;
		pDY13->oBuzzerBit3 = FALSE;
		pDY13->oBuzzerBit4 = FALSE;
	} else {
		int nAlmType = 0;
		if (bBuzzer2) nAlmType = 1;

		pDY13->oBuzzerBit0 = pEquipData->bBuzzer[nAlmType][0];
		pDY13->oBuzzerBit1 = pEquipData->bBuzzer[nAlmType][1];
		pDY13->oBuzzerBit2 = pEquipData->bBuzzer[nAlmType][2];
		pDY13->oBuzzerBit3 = pEquipData->bBuzzer[nAlmType][3];
		pDY13->oBuzzerBit4 = pEquipData->bBuzzer[nAlmType][4];
	}

	// Start, Stop, Reset SW
	switch (gData.m_nMS) {
	case STATE_NONE:
		pDY13->oStartLamp1 = pDY13->oStartLamp2 = pDY13->oStartLamp3 = FALSE;
		pDY13->oStopLamp1 = pDY13->oStopLamp2 = pDY13->oStopLamp3 = FALSE;
		pDY13->oResetLamp1 = pDY13->oResetLamp2 = pDY13->oResetLamp3 = FALSE;
		break;
	case STATE_INITEND:
	case STATE_LOTEND:
		pDY13->oStartLamp1 = pDY13->oStartLamp2 = pDY13->oStartLamp3 = FALSE;
		pDY13->oStopLamp1 = pDY13->oStopLamp2 = pDY13->oStopLamp3 = TRUE;
		pDY13->oResetLamp1 = pDY13->oResetLamp2 = pDY13->oResetLamp3 = FALSE;
		g_dlgWork.Set_AutoRun(FALSE);
		break;
	case STATE_RUN:
		pDY13->oStartLamp1 = pDY13->oStartLamp2 = pDY13->oStartLamp3 = TRUE;
		pDY13->oStopLamp1 = pDY13->oStopLamp2 = pDY13->oStopLamp3 = FALSE;
		pDY13->oResetLamp1 = pDY13->oResetLamp2 = pDY13->oResetLamp3 = FALSE;
		break;
	case STATE_ALARM:
	case STATE_EMER:
		pDY13->oStartLamp1 = pDY13->oStartLamp2 = pDY13->oStartLamp3 = FALSE;
		pDY13->oStopLamp1 = pDY13->oStopLamp2 = pDY13->oStopLamp3 = FALSE;
		pDY13->oResetLamp1 = pDY13->oResetLamp2 = pDY13->oResetLamp3 = TRUE;
		g_dlgWork.Set_AutoRun(FALSE);
		break;
	}
	g_objAJinAXL.Write_Output(13);

	// Flicker
	if (pEquipData->bTower[nState][3] || pEquipData->bTower[nState][6]) SetTimer(TIMER_TOWER_FLKR, 500, NULL);
}

void CCMAI2100Dlg::Set_TowerFlicker(BOOL bEnable)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();

	if (gData.m_bTowerOn) {
		gData.m_bTowerOn = FALSE;
		if (pEquipData->bTower[gData.m_nMS][3]) {
			pDY13->oTowerGreen1 = pDY13->oTowerGreen2 = FALSE;
			pDY13->oTowerYellow1 = pDY13->oTowerYellow2 = FALSE;
			pDY13->oTowerRed1 = pDY13->oTowerRed2 = FALSE;
		}		
		if (pEquipData->bTower[gData.m_nMS][6]) {
			pDY13->oBuzzerBit0 = FALSE;
			pDY13->oBuzzerBit1 = FALSE;
			pDY13->oBuzzerBit2 = FALSE;
			pDY13->oBuzzerBit3 = FALSE;
			pDY13->oBuzzerBit4 = FALSE;
		}
	} else {
		gData.m_bTowerOn = TRUE;
		if (pEquipData->bTower[gData.m_nMS][3]) {
			pDY13->oTowerGreen1 = pDY13->oTowerGreen2 = pEquipData->bTower[gData.m_nMS][0];
			pDY13->oTowerYellow1 = pDY13->oTowerYellow2 = pEquipData->bTower[gData.m_nMS][1];
			pDY13->oTowerRed1 = pDY13->oTowerRed2 = pEquipData->bTower[gData.m_nMS][2];
		}
		if (pEquipData->bTower[gData.m_nMS][6]) {
			BOOL bBuzzer1 = pEquipData->bTower[gData.m_nMS][4];
			BOOL bBuzzer2 = pEquipData->bTower[gData.m_nMS][5];

			if (bBuzzer1 == FALSE && bBuzzer2 == FALSE) {
				pDY13->oBuzzerBit0 = FALSE;
				pDY13->oBuzzerBit1 = FALSE;
				pDY13->oBuzzerBit2 = FALSE;
				pDY13->oBuzzerBit3 = FALSE;
				pDY13->oBuzzerBit4 = FALSE;
			} else {
				int nAlmType = 0;
				if (bBuzzer2) nAlmType = 1;

				pDY13->oBuzzerBit0 = pEquipData->bBuzzer[nAlmType][0];
				pDY13->oBuzzerBit1 = pEquipData->bBuzzer[nAlmType][1];
				pDY13->oBuzzerBit2 = pEquipData->bBuzzer[nAlmType][2];
				pDY13->oBuzzerBit3 = pEquipData->bBuzzer[nAlmType][3];
				pDY13->oBuzzerBit4 = pEquipData->bBuzzer[nAlmType][4];
			}
		}
	}
	if (gData.m_bBuzzerOff == TRUE) {
		pDY13->oBuzzerBit0 = FALSE;
		pDY13->oBuzzerBit1 = FALSE;
		pDY13->oBuzzerBit2 = FALSE;
		pDY13->oBuzzerBit3 = FALSE;
		pDY13->oBuzzerBit4 = FALSE;
	}
	g_objAJinAXL.Write_Output(13);
}

void CCMAI2100Dlg::Enable_ModeButton(BOOL bEnable)
{
	m_rdoMainInitial.EnableWindow(bEnable);
	m_rdoMainWork.EnableWindow(bEnable);
	m_rdoMainManual.EnableWindow(bEnable);
	m_rdoMainSetup.EnableWindow(bEnable);
	m_rdoMainProhibit.EnableWindow(bEnable);
}

void CCMAI2100Dlg::Set_NoWork()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	if (pEquipData->nNoWorkTime < 1 || g_dlgNoWork.m_bStart){ m_dwNoWorkTime = GetTickCount(); return; }

	int nState = gData.m_nMS;
	if (nState != STATE_NONE && nState != STATE_INITEND) { m_dwNoWorkTime = GetTickCount(); return; }

	if (g_dlgNoWork.IsWindowVisible()) { m_dwNoWorkTime = GetTickCount(); return; }

	int nTerm = (int)(GetTickCount() - m_dwNoWorkTime);
	if (nTerm < pEquipData->nNoWorkTime * 1000) return;	// 초 -> 밀리초

	g_dlgNoWork.m_bStart = TRUE;

	CTime CurTime = CTime::GetCurrentTime(); 
	CurTime -= pEquipData->nNoWorkTime;
	g_dlgNoWork.m_dwStartTime = GetTickCount();
	g_dlgNoWork.m_strStartTime.Format("%04d%02d%02d%02d%02d%02d", CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay(), CurTime.GetHour(), CurTime.GetMinute(), CurTime.GetSecond());

	CString strLog;
	strLog.Format("비가동 집계 시작\t%s", g_dlgNoWork.m_strStartTime);
	g_objLogFile.Save_HandlerLog(strLog);

	g_dlgNoWork.ShowWindow(TRUE);
}

void CCMAI2100Dlg::Display_EquipName()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	CString str;
	str.Format("%s / %s", pEquipData->sEquipName, pEquipData->sModelName);
	m_stcMainEquip.SetWindowText(str);
}

void CCMAI2100Dlg::Display_DateTime()
{
	CTime datetime = CTime::GetCurrentTime();

	CString strDate = datetime.Format("%Y-%m-%d");
	m_stcMainDate.SetWindowText(strDate);

	CString strTime = datetime.Format("%H:%M:%S");
	m_stcMainTime.SetWindowText(strTime);

	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	COLORREF crTowerR = (pDY13->oTowerRed1 ? RGB(0xFF, 0x00, 0x00) : RGB(0xF0, 0xF0, 0xF0));
	COLORREF crTowerY = (pDY13->oTowerYellow1 ? RGB(0xFF, 0xFF, 0x00) : RGB(0xF0, 0xF0, 0xF0));
	COLORREF crTowerG = (pDY13->oTowerGreen1 ? RGB(0x00, 0xFF, 0x00) : RGB(0xF0, 0xF0, 0xF0));
	m_stcMainTower[0].Set_Color(COLOR_DEFAULT, crTowerR);
	m_stcMainTower[1].Set_Color(COLOR_DEFAULT, crTowerY);
	m_stcMainTower[2].Set_Color(COLOR_DEFAULT, crTowerG);

	static int nUphClear = 0;
	if (datetime.GetHour() == 7) {	// 클리어
		if (nUphClear == 1) return;
		nUphClear = 1;
		Save_EquipRunTime();
		Clear_EquipRunTime();
		LogAllDelete();
	} else nUphClear = 0;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseDoorLock) { m_stcDoorLock.Set_Text("Door 잠금"); m_stcDoorLock.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00)); }
	else						  { m_stcDoorLock.Set_Text("Door 해제"); m_stcDoorLock.Set_Color(RGB(0xFF, 0xFF, 0x00), RGB(0xFF, 0x00, 0x00)); }

	if (gIt.nLogMM >=1 && gIt.nLogMM <=12 && gIt.nLogHH != datetime.GetHour()) {
		g_objLogFile.Save_Interlock(1);
	}
}

void CCMAI2100Dlg::Exit_System(int nExitNo) 
{
	if (gData.nLanguage == 0) {
		if (nExitNo == EXIT_SYSTEM_AJIN) g_objCommon.Show_MsgBox(1, "모션 초기화를 실패 하였습니다.");
		if (nExitNo == EXIT_SYSTEM_BARCODE) g_objCommon.Show_MsgBox(1, "바코드 초기화를 실패 하였습니다.");
	} else {
		if (nExitNo == EXIT_SYSTEM_AJIN) g_objCommon.Show_MsgBox(1, "Fail to motion initialization.");
		if (nExitNo == EXIT_SYSTEM_BARCODE) g_objCommon.Show_MsgBox(1, "Fail to barcode initialization.");
	}

	CString strLog;
	strLog.Format("[Main Dialog] Program Exit.  Version: %s", MAIN_VERSION);
	g_objLogFile.Save_HandlerLog(strLog);

	g_dlgWork.End_ElevatorRunThread();
	g_objSequenceMain.End_MainRunThread();
	g_objSequenceInit.End_InitialThread();
	g_objCommon.Stop_Elevator();
	g_objCommon.BuzzerOff();

	DY_DATA_04 *pDY04 = g_objAJinAXL.Get_pDY04();
	pDY04->oLoadIonizerOn = FALSE;
	pDY04->oBTMIonizerOn = FALSE;
	pDY04->oBTMIonizerBlow = FALSE;
	pDY04->oBTMSuctionOn = FALSE;
	pDY04->oTOPIonizerOn = FALSE;
	pDY04->oTOPIonizerBlow = FALSE;
	pDY04->oTOPSuctionOn = FALSE;
	g_objAJinAXL.Write_Output(4);

	DY_DATA_12 *pDY12 = g_objAJinAXL.Get_pDY12();
	pDY12->oGoodIonizerOn = FALSE;
	g_objAJinAXL.Write_Output(12);

	DY_DATA_14 *pDY14 = g_objAJinAXL.Get_pDY14();
	pDY14->oInsideLight = FALSE;
	g_objAJinAXL.Write_Output(14);

	g_objInspector.Terminate();
	g_objDispatcher.Terminate();
	g_objMesAgent.Terminate();
	g_objAJinAXL.Terminate();
	g_objBarcodeLot.Terminate();

	KillTimer(TIMER_TOWER_FLKR);
	KillTimer(TIMER_DATE_TIME);
	KillTimer(TIMER_SLIDE_CHECK);
	KillTimer(TIMER_DOOR_LOCK);

	delete gNG;
	DestroyWindow();
}

void CCMAI2100Dlg::Set_EquipRunStart()
{
	m_dwEquipRunStart = GetTickCount();

	g_objLogFile.Save_HandlerLog("[Equipment Run Time] Start Run Time");
}

void CCMAI2100Dlg::Save_EquipRunTime()
{
	if (m_dwEquipRunStart == 0) return;

	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	int nRunTime = INI.Get_Integer("EQUIPMENT", "RUN_TIME", 0);

	DWORD dwTime = GetTickCount() - m_dwEquipRunStart;
	nRunTime += (int)(dwTime);

	INI.Set_Integer("EQUIPMENT", "RUN_TIME", nRunTime);

	CString strLog;
	int nHour = nRunTime / 3600000;
	int nMin = (nRunTime - nHour * 3600000) / 60000;
	int nSec = (nRunTime - nHour * 3600000 - nMin * 60000) / 1000;
	strLog.Format("[Equipment Run Time] Save Run Time ==> %02d:%02d:%02d", nHour, nMin, nSec);
	g_objLogFile.Save_HandlerLog(strLog);

	m_dwEquipRunStart = 0;
}

void CCMAI2100Dlg::Clear_EquipRunTime()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	INI.Set_Integer("EQUIPMENT", "RUN_TIME", 0);
	m_dwEquipRunStart = 0;

	g_objLogFile.Save_HandlerLog("[Equipment Run Time] Clear Run Time");
}

void CCMAI2100Dlg::Clear_JobData()
{
	gLot.nJobNo = 0;
	for(int i=0; i<10; i++) {
		gLot.nJobPortNo[i] = gLot.nJobCmCount[i] = gLot.nJobGoodCount[i] = gLot.nJobNgCount[i] = 0;
		gLot.sJobLotID[i] = gLot.sJobStartTime[i] = gLot.sJobEndTime[i] = "";
		gLot.dJobRate[1] = gLot.dJobTack[i] = 0.0;
	}
}

void CCMAI2100Dlg::Check_SlideOpen()
{
#ifdef AJIN_BOARD_USE
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if (gData.nSlideTime < 5000) return;
	if (pDX00->iElevator1SlideClose || pDX00->iElevator1SlideOpen) gData.dwSlideTime[0] = 0;
	if (pDX00->iElevator2SlideClose || pDX00->iElevator2SlideOpen) gData.dwSlideTime[1] = 0;
	if (pDX01->iElevator3SlideClose || pDX01->iElevator3SlideOpen) gData.dwSlideTime[2] = 0;
	if (pDX01->iElevator4SlideClose || pDX01->iElevator4SlideOpen) gData.dwSlideTime[3] = 0;
	if (pDX02->iElevator5SlideClose || pDX02->iElevator5SlideOpen) gData.dwSlideTime[4] = 0;
	if (pDX02->iElevator6SlideClose || pDX02->iElevator6SlideOpen) gData.dwSlideTime[5] = 0;
	if (pDX02->iElevator7SlideClose || pDX02->iElevator7SlideOpen) gData.dwSlideTime[6] = 0;

	if (!pDX00->iElevator1SlideClose && !pDX00->iElevator1SlideOpen && gData.dwSlideTime[0]==0) gData.dwSlideTime[0] = GetTickCount();
	if (!pDX00->iElevator2SlideClose && !pDX00->iElevator2SlideOpen && gData.dwSlideTime[1]==0) gData.dwSlideTime[1] = GetTickCount();
	if (!pDX01->iElevator3SlideClose && !pDX01->iElevator3SlideOpen && gData.dwSlideTime[2]==0) gData.dwSlideTime[2] = GetTickCount();
	if (!pDX01->iElevator4SlideClose && !pDX01->iElevator4SlideOpen && gData.dwSlideTime[3]==0) gData.dwSlideTime[3] = GetTickCount();
	if (!pDX02->iElevator5SlideClose && !pDX02->iElevator5SlideOpen && gData.dwSlideTime[4]==0) gData.dwSlideTime[4] = GetTickCount();
	if (!pDX02->iElevator6SlideClose && !pDX02->iElevator6SlideOpen && gData.dwSlideTime[5]==0) gData.dwSlideTime[5] = GetTickCount();
	if (!pDX02->iElevator7SlideClose && !pDX02->iElevator7SlideOpen && gData.dwSlideTime[6]==0) gData.dwSlideTime[6] = GetTickCount();
	
	for(int i=0; i<7; i++) {
		if (gData.dwSlideTime[i] > 0) {
			if (int(GetTickCount() - gData.dwSlideTime[i]) >= gData.nSlideTime) { g_objCommon.Show_Error(i+81); return; }
		}
	}
#endif
}

void CCMAI2100Dlg::Set_DoorLock()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseDoorLock) return;
	if (gData.dwDoorStartTime <= 0) gData.dwDoorStartTime = GetTickCount();

	DWORD dwCurrentTime = GetTickCount();
	DWORD dwDoorEndTime = DWORD(gData.nDoorLockTime) * 1000;
	if (dwCurrentTime - gData.dwDoorStartTime >= dwDoorEndTime) {
		CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
		if (!INI.Check_File()) return;
		INI.Set_Bool("EQUIPMENT", "DOOR_LOCK", TRUE);

		if (gData.nLanguage == 0) g_objLogFile.Save_HandlerLog("Door Lock을 Auto로 설정 하였습니다...");
		else					  g_objLogFile.Save_HandlerLog("The door lock has been Auto set On...");

		gData.dwDoorStartTime = 0;
		g_objDataManager.Read_EquipData();

		g_dlgWork.PostMessage(UM_UPDATE_MODEL, NULL, NULL);
	}
}

///////////////////////////////////////////////////////////////////////////////
void CCMAI2100Dlg::LogAllDelete()
{
	CString strPath;
	strPath.Format("%s\\LOG\\Alarm",		gsCurrentDir);		LogFileDelete(strPath);
	strPath.Format("%s\\LOG\\Handler",		gsCurrentDir);		LogFileDelete(strPath);
	strPath.Format("%s\\LOG\\Inspector",	gsCurrentDir);		LogFileDelete(strPath);
	strPath.Format("%s\\LOG\\JobList",		gsCurrentDir);		LogFileDelete(strPath);
//	strPath.Format("%s\\LOG\\MCC",			gsCurrentDir);		LogFileDelete(strPath);
	strPath.Format("%s\\LOG\\MESAgent",		gsCurrentDir);		LogFileDelete(strPath);
	strPath.Format("%s\\LOG\\OutTray",		gsCurrentDir);		LogFileDelete(strPath);
	strPath.Format("%s\\LOG\\Dispatcher",	gsCurrentDir);		LogFileDelete(strPath);
	strPath.Format("%s\\LOG\\Screen",		gsCurrentDir);		LogFileDelete(strPath);
	StdLogAllDelete();
}

void CCMAI2100Dlg::LogFileDelete(CString sPath)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
    CTime CurTime = CTime::GetCurrentTime();
    CTime DayXTime;
    DayXTime = CurTime - CTimeSpan(pEquipData->nLogDate, 0, 0, 0);
    CString path, file_path, file_name;
    path.Format("%s\\*.*", sPath);
    CFileFind finder;
    BOOL bRes;
    bRes = finder.FindFile(path);

    while(bRes)
    {
        bRes = finder.FindNextFile();
        if(!finder.IsDirectory())
        {
            bool bDelete = true;

            file_name = finder.GetFileName();
            file_path.Format("%s\\%s", sPath, file_name);

            if(file_name.GetLength() >= 8) {
                int nLogYear = _ttoi(file_name.Left(4));
                int nLogMonth = _ttoi(file_name.Mid(4, 2));
                int nLogDay = _ttoi(file_name.Mid(6, 2));
				
				if (nLogYear>2000 && nLogMonth > 0 && nLogMonth < 13 && nLogDay > 0 && nLogDay < 32) {
					CTime LogTime(nLogYear, nLogMonth, nLogDay, 0, 0, 0, 0);
					if(LogTime >= DayXTime) bDelete = false;
				}
            }   

            if(bDelete) DeleteFile(file_path);
        }
    }
}

void CCMAI2100Dlg::OnStnClickedImgLgLogo()
{
	Capture_Screen();
}

void CCMAI2100Dlg::Capture_Screen()
{
	CWnd *pDeskTopWnd = GetDesktopWindow();
	if (!pDeskTopWnd) return;
	CWindowDC DeskTopDC(pDeskTopWnd);

	CImage imgScreen;
	int nX = GetSystemMetrics(SM_CXSCREEN);
	int nY = GetSystemMetrics(SM_CYSCREEN);
	if (!imgScreen.Create(nX, nY, 32)) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strMsg, strFile;
	CString strPath = gsCurrentDir + "\\Log\\Screen";
	g_objLogFile.Create_Folder(strPath);
	strFile.Format("%s\\%04d%02d%02d_%02d%02d%02d.jpg", strPath, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	HDC hDC = imgScreen.GetDC();
	BitBlt(hDC, 0, 0, nX, nY, DeskTopDC, 0, 0, SRCCOPY);

	imgScreen.Save(strFile, Gdiplus::ImageFormatJPEG);
	imgScreen.ReleaseDC();

	strMsg.Format("%s\nScreen Capture Completed.", strFile);
	g_objCommon.Show_MsgBox(1, strMsg);
}

void CCMAI2100Dlg::StdLogAllDelete()
{
	CString strFileName, strPath, strDir;

	// 현재 날짜 확인
	int nCurYear, nCurMonth, nCurDay;
	CTime CurTime = CTime::GetCurrentTime();

	nCurYear = CurTime.GetYear();
	nCurMonth = CurTime.GetMonth();
	nCurDay = CurTime.GetDay();

	// 현재 날짜 - 저장기간, 삭제해야하는 연/월/일 확인
	CTime DayXTime;
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	DayXTime = CurTime - CTimeSpan(pEquipData->nLogDate, 0, 0, 0);

	int nDelYear, nDelMonth, nDelDay;
	nDelYear  = DayXTime.GetYear();
	nDelMonth = DayXTime.GetMonth();
	nDelDay   = DayXTime.GetDay();

	// 기간 지난 년/월/일 Log 삭제
	char szPcName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName(szPcName, &dwNameSize);
	CString strDirYear, strDirMonth, strDirDay;

	// Motion Log
	strDirYear.Format(_T("%s\\LOG\\Motion\\*.*"), gsCurrentDir);
	strDirMonth.Format(_T("%s\\LOG\\Motion\\%04d\\*.*"), gsCurrentDir, nDelYear);
	strDirDay.Format(_T("%s\\LOG\\Motion\\%04d\\%02d\\*.*"), gsCurrentDir, nDelYear, nDelMonth);
	StdLogDelete(strDirYear, nDelYear, YEAR);
	StdLogDelete(strDirMonth, nDelMonth, MONTH);
	StdLogDelete(strDirDay, nDelDay, DAY);		

	// MCC Log
	strDirYear.Format(_T("%s\\LOG\\MCC\\*.*"), gsCurrentDir);
	strDirMonth.Format(_T("%s\\LOG\\MCC\\%04d\\*.*"), gsCurrentDir, nDelYear);
	strDirDay.Format(_T("%s\\LOG\\MCC\\%04d\\%02d\\*.*"), gsCurrentDir, nDelYear, nDelMonth);
	StdLogDelete(strDirYear, nDelYear, YEAR);
	StdLogDelete(strDirMonth, nDelMonth, MONTH);
	StdLogDelete(strDirDay, nDelDay, DAY);		

/*
	// Motion Log
	strDirYear.Format(_T("D:\\MCSC\\%s\\*.*"), szPcName);
	strDirMonth.Format(_T("D:\\MCSC\\%s\\%04d\\*.*"), szPcName, nDelYear);
	strDirDay.Format(_T("D:\\MCSC\\%s\\%04d\\%02d\\*.*"), szPcName, nDelYear, nDelMonth);
	StdLogDelete(strDirYear, nDelYear, YEAR);
	StdLogDelete(strDirMonth, nDelMonth, MONTH);
	StdLogDelete(strDirDay, nDelDay, DAY);		

	// Efficiency Log
	strDirYear.Format(_T("D:\\Efficiency\\%s\\*.*"), szPcName);
	strDirMonth.Format(_T("D:\\Efficiency\\%s\\%04d\\*.*"), szPcName, nDelYear);
	strDirDay.Format(_T("D:\\Efficiency\\%s\\%04d\\%02d\\*.*"), szPcName, nDelYear, nDelMonth);
	StdLogDelete(strDirYear, nDelYear, YEAR);
	StdLogDelete(strDirMonth, nDelMonth, MONTH);
	StdLogDelete(strDirDay, nDelDay, DAY);	
*/	
}

void CCMAI2100Dlg::StdLogDelete(CString strDir, int nDelData, BOOL bType)
{
	CFileFind finder;
	CString sDirPath;
	BOOL bWorking;
	int nDirName, nCnt;

	if (bType == YEAR) nCnt = 4;
	else			   nCnt = 2;

	bWorking = finder.FindFile(strDir);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDots())
			continue;

		if (finder.IsDirectory()) {
			sDirPath = finder.GetFilePath();
			nDirName = atoi(sDirPath.Right(nCnt));
			if (nDelData > nDirName) {
				RemoveDir(sDirPath, FALSE);
			}
		}
	}
}

BOOL CCMAI2100Dlg::RemoveDir(CString strDir, BOOL bOnlyFile)
{
	CFileFind finder;
	BOOL bWorking = TRUE;
	CString strDirFile = strDir + CString(_T("\\*.*"));

	if (finder.FindFile(strDir, TRUE) == false)
	{
		return FALSE;
	}

	bWorking = finder.FindFile(strDirFile);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDots())
			continue;

		if (finder.IsDirectory() && !bOnlyFile)
			RemoveDir(finder.GetFilePath(), false);
		else
			::DeleteFile(finder.GetFilePath());
	}

	finder.Close();

	if (!bOnlyFile)
		::RemoveDirectory(strDir);

	return TRUE;
}

int CCMAI2100Dlg::GetDirFilesNum(CString strDir)
{
    int count = 0;
    CFileFind finder;
       
    BOOL bWorking = finder.FindFile(strDir + "/*.*");
 
    while(bWorking)
    {
		bWorking = finder.FindNextFile();
		if(finder.IsDots())
			continue;

		count++;
 
    }
    finder.Close();
 
    return count;
}