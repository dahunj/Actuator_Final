// InitialDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "InitialDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "Common.h"
#include "Inspector.h"
#include "Dispatcher.h"
#include "SequenceInit.h"
#include "Dispatcher.h"
#include "OperatorDlg.h"
#include "CMAI2100Dlg.h"

// CInitialDlg 대화 상자입니다.
CInitialDlg g_dlgInitial;

IMPLEMENT_DYNAMIC(CInitialDlg, CDialogEx)

CInitialDlg::CInitialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitialDlg::IDD, pParent)
{
}

CInitialDlg::~CInitialDlg()
{
}

void CInitialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	DDX_Control(pDX, IDC_RDO_INIT_START, m_rdoInitStart);
	DDX_Control(pDX, IDC_RDO_INIT_STOP, m_rdoInitStop);
	DDX_Control(pDX, IDC_LED_INITIAL_OK, m_ledInitialOK);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_IMAGE_0 + i, m_Image[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_PIC_INIT_FLOW_0 + i, m_picInitFlow[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_STC_INIT_FLOW_0 + i, m_stcInitFlow[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_MAIN_AIR_0 + i, m_ledMainAir[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_EMG_SW_0 + i, m_ledEmgSw[i]);
	for (int i = 0; i < 21; i++) DDX_Control(pDX, IDC_LED_DOOR_UNLOCK_0 + i, m_ledDoorUnlock[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_STC_INIT_CASE_0 + i, m_stcInitCase[i]);
}

BEGIN_MESSAGE_MAP(CInitialDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RDO_INIT_START, &CInitialDlg::OnBnClickedRdoInitStart)
	ON_BN_CLICKED(IDC_RDO_INIT_STOP, &CInitialDlg::OnBnClickedRdoInitStop)
	ON_BN_CLICKED(IDC_BUTTON1, &CInitialDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CInitialDlg 메시지 처리기입니다.

BOOL CInitialDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 75, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_pInitialMotionDlg = new CInitialMotionDlg(this);
	m_pInitialMotionDlg->Create(IDD_INITIAL_MOTION_DLG, this);

	for (int i = 0; i < 9; i++) m_stcInitCase[i].SetWindowText("000");

	m_bInitialRunning = FALSE;
	m_rdoInitStop.SetCheck(TRUE);
	m_rdoInitStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CInitialDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CInitialDlg::OnDestroy() 
{
	CDialogEx::OnDestroy();

	KillTimer(0);

	m_pInitialMotionDlg->DestroyWindow();
	delete m_pInitialMotionDlg;
	m_pInitialMotionDlg = NULL;
}

void CInitialDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		m_pInitialMotionDlg->ShowWindow(SW_SHOW);
		g_objCommon.Locking_MainDoor(TRUE);
		SetTimer(0, 100, NULL);

	} else {
		KillTimer(0);
		m_pInitialMotionDlg->ShowWindow(SW_HIDE);
	}
}

void CInitialDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	DX_DATA_13 *pDX13 = g_objAJinAXL.Get_pDX13();

	if (pDX13->iStartSw && !m_rdoInitStart.GetCheck()) {
		g_objLogFile.Save_HandlerLog("[Initial Mode] START S/W Push");
		m_rdoInitStart.SetCheck(TRUE);

	} else if (pDX13->iStopSw && !m_rdoInitStop.GetCheck()) {
		g_objLogFile.Save_HandlerLog("[Initial Mode] STOP S/W Push");
		m_rdoInitStop.SetCheck(TRUE);
	}

	Display_Status();

	if (m_rdoInitStart.GetCheck()) {
		if (!m_bInitialRunning) {	// First Start
			CString sText;
			if (gData.nLanguage == 0) sText.Format("초기화를 하시겠습니까?");
			else					  sText.Format("Do you want to Initialize?");

			if (g_objCommon.Show_MsgBox(2, sText) == IDOK) {
				if (g_objCommon.Check_TraySlide(9)) {
					m_bInitialRunning = TRUE;

					g_objCommon.Locking_MainDoor(TRUE, TRUE);
					pMainDlg->Enable_ModeButton(FALSE);

					//비전에 초기화 커맨드 날려줌...?? 필요한지..
					g_objInspector.Set_StatusUpdate(INSPECTOR_ALL, 0);
					g_objInspector.Set_InitialRequest(INSPECTOR_ALL);

					m_rdoInitStart.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
					m_rdoInitStop.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);

					m_nBackColorLoop = 0;
					Set_StatusColor(0, 2);	// Green
					for (int i = 1; i < 10; i++) Set_StatusColor(i, 0);	// White

					g_objSequenceInit.Begin_InitialThread();
				} else {
					m_rdoInitStop.SetCheck(TRUE);
				}
			} else {
				m_rdoInitStop.SetCheck(TRUE);
			}

		} else {					// Running
			Display_Initial();

			if (g_objSequenceInit.Get_InitComplete()) {
				m_bInitialRunning = FALSE;

				m_rdoInitStop.SetCheck(TRUE);
				m_rdoInitStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
				m_rdoInitStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);

				for (int i = 1; i < 10; i++) Set_StatusColor(i, 2);	// Green

				g_objLogFile.Save_HandlerLog("[Initial Mode] Initialization is complete");

				if (gData.nLanguage == 0) g_objCommon.Show_MsgBox(1, "초기화 완료 하였습니다.");
				else					  g_objCommon.Show_MsgBox(1, "Initialization is complete.");
				g_objCommon.Save_MotionPos();

				g_objInspector.Set_StatusUpdate(INSPECTOR_ALL, 1);
				g_objInspector.Set_TimeUpdate(INSPECTOR_ALL);
				g_objDispatcher.Set_StatusUpdate(0);	// 0:Stop, 1:Run, 2:Error

				pMainDlg->Enable_ModeButton(TRUE);
				pMainDlg->Set_CurrentMode(MODE_OPERATOR);

				g_dlgOperator.ShowWindow(SW_SHOW);
				return;

			} else if (!g_objSequenceInit.Get_ThreadInitial()) {
				g_objLogFile.Save_HandlerLog("[Initial Mode] Auto STOP");
				m_rdoInitStop.SetCheck(TRUE);
			}
		}

	} else if (m_rdoInitStop.GetCheck()) {	
		if (m_bInitialRunning) {	// First Stop
			m_bInitialRunning = FALSE;

			m_rdoInitStart.Set_Color(RGB(0x00, 0x00, 0x00), COLOR_DEFAULT);
			m_rdoInitStop.Set_Color(RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
			g_objSequenceInit.End_InitialThread();

			int nState = pMainDlg->Get_MainState();
			pMainDlg->Enable_ModeButton(TRUE);
			g_objCommon.Locking_MainDoor(FALSE);

		} else {
			int nState = pMainDlg->Get_MainState();
			if (nState != STATE_ALARM && nState != STATE_EMER) g_objCommon.Check_MainEmgAir();	// Emg & Main Air
		}
	}

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CInitialDlg::OnBnClickedRdoInitStart()
{
	g_objLogFile.Save_HandlerLog("[Initial Mode] START Button push");
}

void CInitialDlg::OnBnClickedRdoInitStop()
{
	g_objLogFile.Save_HandlerLog("[Initial Mode] STOP Button push");
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CInitialDlg::Initial_Controls()
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);

	m_rdoInitStart.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_rdoInitStop.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);

	m_ledInitialOK.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x00, 0xA0),COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em32);

	for (int i = 0; i < 3; i++) m_bmpImage[i].LoadBitmap(IDB_ARW4_DN);
	for (int i = 0; i < 3; i++) m_Image[i].SetBitmap(m_bmpImage[i]);
	for (int i = 0; i < 3; i++) m_Image[i].SetWindowPos(NULL, 0, 0, 36, 36, SWP_NOZORDER | SWP_NOMOVE);

	for (int i = 0; i < 10; i++) m_picInitFlow[i].Init_Ctrl(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xFF));
	for (int i = 0; i < 10; i++) m_stcInitFlow[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));

	for (int i = 0; i < 4; i++) m_ledMainAir[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++) m_ledEmgSw[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emRed, CLedCS::em16);
	for (int i = 0; i <21; i++) m_ledDoorUnlock[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	m_stcInitCase[0].Init_Ctrl("바탕", 10, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x80, 0x80, 0x80));
	for (int i = 1; i < 9; i++) m_stcInitCase[i].Init_Ctrl("바탕", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x80));
}

void CInitialDlg::Display_Status()
{
	DX_DATA_13 *pDX13 = g_objAJinAXL.Get_pDX13();
	DX_DATA_14 *pDX14 = g_objAJinAXL.Get_pDX14();

	m_ledMainAir[0].Set_On(pDX13->iMainAir1);
	m_ledMainAir[1].Set_On(pDX13->iMainAir2);
	m_ledMainAir[2].Set_On(pDX13->iMainAir3);

	m_ledEmgSw[0].Set_On(pDX13->iEmgSw1);
	m_ledEmgSw[1].Set_On(pDX13->iEmgSw2);
	m_ledEmgSw[2].Set_On(pDX13->iEmgSw3);
	m_ledEmgSw[3].Set_On(pDX13->iEmgSw4);
	m_ledEmgSw[4].Set_On(pDX13->iEmgSw5);
	m_ledEmgSw[5].Set_On(pDX13->iEmgSw6);

	m_ledDoorUnlock[ 0].Set_On(pDX14->iDoor01Unlock);
	m_ledDoorUnlock[ 1].Set_On(pDX14->iDoor02Unlock);
	m_ledDoorUnlock[ 2].Set_On(pDX14->iDoor03Unlock);
	m_ledDoorUnlock[ 3].Set_On(pDX14->iDoor04Unlock);
	m_ledDoorUnlock[ 4].Set_On(pDX14->iDoor05Unlock);
	m_ledDoorUnlock[ 5].Set_On(pDX14->iDoor06Unlock);
	m_ledDoorUnlock[ 6].Set_On(pDX14->iDoor07Unlock);
	m_ledDoorUnlock[ 7].Set_On(pDX14->iDoor08Unlock);
	m_ledDoorUnlock[ 8].Set_On(pDX14->iDoor09Unlock);
	m_ledDoorUnlock[ 9].Set_On(pDX14->iDoor10Unlock);
	m_ledDoorUnlock[10].Set_On(pDX14->iDoor11Unlock);
	m_ledDoorUnlock[11].Set_On(pDX14->iDoor12Unlock);
	m_ledDoorUnlock[12].Set_On(pDX14->iDoor13Unlock);
	m_ledDoorUnlock[13].Set_On(pDX14->iDoor14Unlock);
	m_ledDoorUnlock[14].Set_On(pDX14->iDoor15Unlock);
	m_ledDoorUnlock[15].Set_On(pDX14->iDoor16Unlock);
	m_ledDoorUnlock[16].Set_On(pDX14->iDoor17Unlock);
	m_ledDoorUnlock[17].Set_On(pDX14->iDoor18Unlock);
	m_ledDoorUnlock[18].Set_On(pDX14->iDoor19Unlock);
	m_ledDoorUnlock[19].Set_On(pDX14->iDoor20Unlock);
	m_ledDoorUnlock[20].Set_On(pDX14->iDoor21Unlock);

	BOOL bOk = g_objSequenceInit.Get_InitComplete();
	m_ledInitialOK.Set_On(bOk);
}

void CInitialDlg::Display_Initial() 
{
	int *pCase = g_objSequenceInit.Get_InitialCase();

	CString strCase;
	for (int i = 0; i < 9; i++) {
		strCase.Format("%03d", *(pCase + i));
		m_stcInitCase[i].SetWindowText(strCase);
	}

	if (m_nBackColorLoop == 10) m_nBackColorLoop = 0;
	m_nBackColorLoop++;

	if (*(pCase + 0) == 0) return;							// Main
	
	if (*(pCase + 0) < 50) {								// Main
		if (m_nBackColorLoop == 1) Set_StatusColor(1, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(1, 3);	// Blue
	} else if (*(pCase + 0) == 50) {
		if (m_nBackColorLoop == 1) Set_StatusColor(1, 2);	// Green
	}

	if (*(pCase + 0) < 50) return;							// Main

	if (*(pCase + 1) < 90) {								// Elevator
		if (m_nBackColorLoop == 1) Set_StatusColor(2, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(2, 3);	// Blue
	} else {
		if (m_nBackColorLoop == 1) Set_StatusColor(2, 2);	// Green
	}

	if (*(pCase + 2) < 90) {								// Transfer
		if (m_nBackColorLoop == 1) Set_StatusColor(3, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(3, 3);	// Blue
	} else {
		if (m_nBackColorLoop == 1) Set_StatusColor(3, 2);	// Green
	}

	if (*(pCase + 3) < 90 ) {								// load Stage
		if (m_nBackColorLoop == 1) Set_StatusColor(4, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(4, 3);	// Blue
	} else {
		if (m_nBackColorLoop == 1) Set_StatusColor(4, 2);	// Green
	}

	if (*(pCase + 4) < 90) {								// Load Picerk
		if (m_nBackColorLoop == 1) Set_StatusColor(5, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(5, 3);	// Blue
	} else {
		if (m_nBackColorLoop == 1) Set_StatusColor(5, 2);	// Green
	}

	if (*(pCase + 5) < 90) {								// Inspection Stage
		if (m_nBackColorLoop == 1) Set_StatusColor(6, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(6, 3);	// Blue
	} else {
		if (m_nBackColorLoop == 1) Set_StatusColor(6, 2);	// Green
	}

	if (*(pCase + 6) < 90) {								// Unload picker
		if (m_nBackColorLoop == 1) Set_StatusColor(7, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(7, 3);	// Blue
	} else {
		if (m_nBackColorLoop == 1) Set_StatusColor(7, 2);	// Green
	}

	if (*(pCase + 7) < 90 || *(pCase + 8) < 90) {			// Good, NG Stage
		if (m_nBackColorLoop == 1) Set_StatusColor(8, 1);	// Red
		if (m_nBackColorLoop == 6) Set_StatusColor(8, 3);	// Blue
	} else {
		if (m_nBackColorLoop == 1) Set_StatusColor(8, 2);	// Green
	}
}

void CInitialDlg::Set_StatusColor(int nIdx, int nColor)
{
	COLORREF colorBack = RGB(0xFF, 0xFF, 0xFF);			// White
	if (nColor == 1) colorBack = RGB(0xFF, 0x00, 0x00);	// Red
	if (nColor == 2) colorBack = RGB(0x00, 0xFF, 0x00);	// Green
	if (nColor == 3) colorBack = RGB(0x00, 0x00, 0xFF);	// Blue

	m_picInitFlow[nIdx].Set_Color(COLOR_DEFAULT, colorBack);
	m_stcInitFlow[nIdx].Invalidate(FALSE);
}
///////////////////////////////////////////////////////////////////////////////

void CInitialDlg::OnBnClickedButton1()
{
// 	g_objSequenceInit.Set_InitComplete(TRUE);
// 	g_objCommon.Show_Error(3428);
// 	g_objCommon.Show_Alarm("Test");
}
