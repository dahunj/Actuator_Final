// OperatorDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "OperatorDlg.h"
#include "afxdialogex.h"
#include "LogFile.h"
#include "Common.h"
#include "SequenceInit.h"
#include "SequenceMain.h"
#include "MesAgent.h"
#include "WorkDlg.h"
#include "SetupDlg.h"
#include "MonitorDlg.h"
#include "CMAI2100Dlg.h"

// COperatorDlg 대화 상자입니다.
COperatorDlg g_dlgOperator;

IMPLEMENT_DYNAMIC(COperatorDlg, CDialogEx)

COperatorDlg::COperatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COperatorDlg::IDD, pParent)
{
}

COperatorDlg::~COperatorDlg()
{
}

void COperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 15; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_PIC_OPERATOR_0 + i, m_picOperator[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_OPER_ALM_TIME_0 + i, m_stcOperAlmTime[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_OPER_ALM_LIST_0 + i, m_stcOperAlmList[i]);
	DDX_Control(pDX, IDC_STC_OPER_LOT_ID, m_stcOperLotId);
	DDX_Control(pDX, IDC_STC_OPER_OPER_ID, m_stcOperOperId);
	DDX_Control(pDX, IDC_STC_OPER_MODEL, m_stcOperModel);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_OPER_RESULT_0 + i, m_stcOperResult[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_OPER_DOOR_0 + i, m_stcOperDoor[i]);
	DDX_Control(pDX, IDC_STC_OPER_LOAD_TRAY, m_stcOperLoadTray);
	DDX_Control(pDX, IDC_GRD_OPER_LOAD_TRAY, m_grdOperLoadTray);
	DDX_Control(pDX, IDC_STC_OPER_NG_TRAY, m_stcOperNgTray);
	DDX_Control(pDX, IDC_GRD_OPER_NG_TRAY, m_grdOperNgTray);
	DDX_Control(pDX, IDC_STC_OPER_SHIP_TRAY, m_stcOperShipTray);
	DDX_Control(pDX, IDC_GRD_OPER_SHIP_TRAY, m_grdOperShipTray);
	DDX_Control(pDX, IDC_BTN_OPER_START, m_btnOperStart);
	DDX_Control(pDX, IDC_BTN_OPER_STOP, m_btnOperStop);
	DDX_Control(pDX, IDC_BTN_OPER_CYCLE_STOP, m_btnOperCycleStop);
	DDX_Control(pDX, IDC_BTN_OPER_INITIAL, m_btnOperInitial);
	DDX_Control(pDX, IDC_BTN_OPER_WORK, m_btnOperWork);
	DDX_Control(pDX, IDC_BTN_OPER_MANUAL, m_btnOperManual);
	DDX_Control(pDX, IDC_BTN_OPER_SETUP, m_btnOperSetup);
	DDX_Control(pDX, IDC_BTN_OPER_MONITOR, m_btnOperMonitor);
	DDX_Control(pDX, IDC_BTN_OPER_EXIT, m_btnOperExit);
}

BEGIN_MESSAGE_MAP(COperatorDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_STN_CLICKED(IDC_STC_OPER_LOT_ID, &COperatorDlg::OnStnClickedStcOperLotId)
	ON_STN_CLICKED(IDC_STC_OPER_OPER_ID, &COperatorDlg::OnStnClickedStcOperOperId)
	ON_BN_CLICKED(IDC_BTN_OPER_START, &COperatorDlg::OnBnClickedBtnOperStart)
	ON_BN_CLICKED(IDC_BTN_OPER_STOP, &COperatorDlg::OnBnClickedBtnOperStop)
	ON_BN_CLICKED(IDC_BTN_OPER_CYCLE_STOP, &COperatorDlg::OnBnClickedBtnOperCycleStop)
	ON_BN_CLICKED(IDC_BTN_OPER_INITIAL, &COperatorDlg::OnBnClickedBtnOperInitial)
	ON_BN_CLICKED(IDC_BTN_OPER_WORK, &COperatorDlg::OnBnClickedBtnOperWork)
	ON_BN_CLICKED(IDC_BTN_OPER_MANUAL, &COperatorDlg::OnBnClickedBtnOperManual)
	ON_BN_CLICKED(IDC_BTN_OPER_SETUP, &COperatorDlg::OnBnClickedBtnOperSetup)
	ON_BN_CLICKED(IDC_BTN_OPER_MONITOR, &COperatorDlg::OnBnClickedBtnOperMonitor)
	ON_BN_CLICKED(IDC_BTN_OPER_EXIT, &COperatorDlg::OnBnClickedBtnOperExit)
	ON_BN_CLICKED(IDC_BTN_OPER_TEST, &COperatorDlg::OnBnClickedBtnOperTest)
END_MESSAGE_MAP()

// COperatorDlg 메시지 처리기입니다.

BOOL COperatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 75, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL COperatorDlg::PreTranslateMessage(MSG* pMsg)
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void COperatorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

		if (pEquipData->bUseDoorLock) {
			m_stcOperDoor[0].Set_Color(RGB(0x00, 0x00, 0x00),RGB(0x00, 0xFF, 0x00));
			m_stcOperDoor[1].Set_Color(RGB(0x00, 0x00, 0x00),RGB(0xF0, 0xF0, 0xF0));
		} else {
			m_stcOperDoor[0].Set_Color(RGB(0x00, 0x00, 0x00),RGB(0xF0, 0xF0, 0xF0));
			m_stcOperDoor[1].Set_Color(RGB(0x00, 0x00, 0x00),RGB(0xFF, 0x00, 0x00));
		}

		CString strText;

//		m_stcOperModel.SetWindowText("AVI");
		m_stcOperModel.SetWindowText(pEquipData->sModelName);
		if (gData.sOperID.GetLength() < 1) gData.sOperID = "11111";

		Display_Status();

		if (g_dlgWork.GetSafeHwnd()) g_dlgWork.SetTimer(0, 100, NULL);
		SetTimer(0, 200, NULL);
	} else {
		if (g_dlgWork.GetSafeHwnd()) g_dlgWork.KillTimer(0);
		KillTimer(0);
	}
}

void COperatorDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);

	Display_Status();

	SetTimer(0, 200, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void COperatorDlg::OnStnClickedStcOperLotId()
{
/*
	CString strKey;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;

	m_stcOperLotId.SetWindowText(strKey);
	g_dlgWork.m_stcLotIdS.SetWindowText(strKey);

	CString sLog;
	sLog.Format("[Operator] Lot ID Input....  LotID[%s] CM[%d] OperID[%s]", gData.sLotID, TRAY_MAX_CM, gData.sOperID);
	g_objLogFile.Save_HandlerLog(sLog);
*/
}

void COperatorDlg::OnStnClickedStcOperOperId()
{
	CString strKey;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;

	gData.sOperID = strKey;
	m_stcOperOperId.SetWindowText(strKey);
	g_objMesAgent.Set_OperUpdate(gData.sOperID);

	CString sLog;
	sLog.Format("[Operator] Operator ID Input....  OperID[%s]", gData.sOperID);
	g_objLogFile.Save_HandlerLog(sLog);
}

void COperatorDlg::OnBnClickedBtnOperStart()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	if (gData.bCycleStop) {
		if (g_objCommon.Show_MsgBox(2, "Are you sure you want to Start by Cycle Stop .....") != IDOK) return;
	}

	CString strUser;
	m_stcOperOperId.GetWindowText(strUser);
	if (strUser.GetLength() < 1) {
		g_objCommon.Show_MsgBox(1, "Input Operator ID");
		return;
	}

	g_dlgWork.m_rdoWorkStart.SetCheck(TRUE);
	Enable_OpModeButton(FALSE);

	CString sLog;
	sLog.Format("[Operator] START button push....  OperID[%s]", gData.sOperID);
	g_objLogFile.Save_HandlerLog(sLog);
}

void COperatorDlg::OnBnClickedBtnOperStop()
{
	g_dlgWork.m_rdoWorkStop.SetCheck(TRUE);
	Enable_OpModeButton(TRUE);

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Set_MainState(STATE_INITEND);

	CString sLog;
	sLog.Format("[Operator] STOP button push....  OperID[%s]", gData.sOperID);
	g_objLogFile.Save_HandlerLog(sLog);
}

void COperatorDlg::OnBnClickedBtnOperCycleStop()
{
	if (gData.bCycleStop) return;

	if (g_dlgWork.m_rdoWorkStart.GetCheck()) {
		g_objCommon.Show_MsgBox(1, "Not allowed Cycle Stop in Auto Run.");
		return;
	}

	if (g_objCommon.Show_MsgBox(2, "Are you sure you want to Cycle Stop?") != IDOK) return;

	g_dlgWork.m_chkCycleStop.SetCheck(TRUE);
	g_dlgWork.m_chkCycleStop.Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
	m_btnOperCycleStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x80, 0xFF, 0xFF));
	gData.bCycleStop = TRUE;

	CString sLog;
	sLog.Format("[Operator] Cycle Stop button push....  OperID[%s]", gData.sOperID);
	g_objLogFile.Save_HandlerLog(sLog);
}

void COperatorDlg::OnBnClickedBtnOperInitial()
{
	ShowWindow(SW_HIDE);
	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Set_CurrentMode(MODE_INITIAL);
}

void COperatorDlg::OnBnClickedBtnOperWork()
{
//	int nUser = 0;
//	if (g_objCommon.Show_Password(nUser) != IDOK) return;

	ShowWindow(SW_HIDE);
	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Set_CurrentMode(MODE_WORK);
}

void COperatorDlg::OnBnClickedBtnOperManual()
{
	int nUser = 0;
	if (g_objCommon.Show_Password(nUser) != IDOK) return;

	ShowWindow(SW_HIDE);
	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Set_CurrentMode(MODE_MANUAL);
}

void COperatorDlg::OnBnClickedBtnOperSetup()
{
	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	if (gData.bUseDryRun) {
		ShowWindow(SW_HIDE);
		g_dlgSetup.Set_LoginUser(2);	// SI
		pMainDlg->Set_CurrentMode(MODE_SETUP);
		return;
	}

	int nUser = 0;
	if (g_objCommon.Show_Password(nUser) != IDOK) return;

	ShowWindow(SW_HIDE);
	pMainDlg->Set_CurrentMode(MODE_SETUP);
}

void COperatorDlg::OnBnClickedBtnOperMonitor()
{
	if (g_dlgMonitor.IsWindowVisible()) g_dlgMonitor.ShowWindow(SW_HIDE);
	else g_dlgMonitor.ShowWindow(SW_SHOW);	
}

void COperatorDlg::OnBnClickedBtnOperExit()
{
	if (g_objCommon.Show_MsgBox(2, "Are you sure you want to exit the program?") != IDOK) return;

	CString sLog;
	sLog.Format("[Operator] Program Exit button push....  OperID[%s]", gData.sOperID);
	g_objLogFile.Save_HandlerLog(sLog);

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Exit_System(EXIT_SYSTEM_NONE);
}

void COperatorDlg::OnBnClickedBtnOperEngineer()
{
	int nUser = 0;
	if (g_objCommon.Show_Password(nUser) != IDOK) return;
	ShowWindow(SW_HIDE);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void COperatorDlg::Initial_Controls() 
{
	for (int i = 0; i < 15; i++) m_Label[i].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	for (int i = 0; i < 4; i++) m_picOperator[i].Init_Ctrl(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xFF));
	for (int i = 0; i < 3; i++) m_stcOperAlmTime[i].Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	for (int i = 0; i < 3; i++) m_stcOperAlmList[i].Init_Ctrl("Segoe UI", 10, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	m_stcOperLotId.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	m_stcOperOperId.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	m_stcOperModel.Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE6, 0xE6, 0xE6));
	for (int i = 0; i < 3; i++) m_stcOperResult[i].Init_Ctrl("Segoe UI", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	for (int i = 0; i < 2; i++) m_stcOperDoor[i].Init_Ctrl("Segoe UI", 20, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xF0));
	m_stcOperLoadTray.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	Initial_Grid(&m_grdOperLoadTray, TRAY_CM_Y, TRAY_CM_X);
	m_stcOperNgTray.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	Initial_Grid(&m_grdOperNgTray, TRAY_CM_Y, TRAY_CM_X);
	m_stcOperShipTray.Init_Ctrl("Segoe UI", 12, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xFF));
	Initial_Grid(&m_grdOperShipTray, TRAY_CM_Y, TRAY_CM_X);
	m_btnOperStart.Init_Ctrl("Segoe UI", 40, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperStop.Init_Ctrl("Segoe UI", 40, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperCycleStop.Init_Ctrl("Segoe UI", 30, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperInitial.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperWork.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperManual.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperSetup.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperMonitor.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
	m_btnOperExit.Init_Ctrl("Segoe UI", 22, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7), NULL, CButtonCS::emTop);
}

void COperatorDlg::Initial_Grid(CGridCS *pGrid, int nRows, int nCols)
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

void COperatorDlg::Enable_OpModeButton(BOOL bEnable)
{
	m_btnOperInitial.EnableWindow(bEnable);
	m_btnOperManual.EnableWindow(bEnable);
	m_btnOperSetup.EnableWindow(bEnable);
}

void COperatorDlg::Display_Status()
{
	CTime datetime = CTime::GetCurrentTime();

	for (int i = 0; i < 3; i++) m_stcOperAlmTime[i].SetWindowText(gData.sAlarmTime[i]);
	for (int i = 0; i < 3; i++) m_stcOperAlmList[i].SetWindowText(gData.sAlarmList[i]);

	if (g_dlgWork.m_rdoWorkStart.GetCheck()) {
		m_btnOperStart.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0x00, 0xFF, 0x00));
		m_btnOperStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7));
		Enable_OpModeButton(FALSE);
	}

	if (g_dlgWork.m_rdoWorkStop.GetCheck()) {
		m_btnOperStop.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xFF, 0x00, 0x00));
		m_btnOperStart.Set_Color(RGB(0x00, 0x00, 0x00), RGB(0xD7, 0xD7, 0xD7));
		Enable_OpModeButton(TRUE);
	}

	COLORREF crCycleStop = (gData.bCycleStop ? RGB(0x80, 0xFF, 0xFF) : RGB(0xD7, 0xD7, 0xD7));
	m_btnOperCycleStop.Set_Color(RGB(0x00, 0x00, 0x00), crCycleStop);

	CString strText;

	for (int i = 0; i < 6; i++) {
		if (gLot.nCmCount[i] > 0) {
			m_stcOperLotId.SetWindowText(gLot.sLotID[i]);

			strText.Format("%d", gLot.nGoodCount[i]);
			m_stcOperResult[0].SetWindowText(strText);

			strText.Format("%d", gLot.nNgCount[i]);
			m_stcOperResult[1].SetWindowText(strText);

			int nTotal = gLot.nGoodCount[i] + gLot.nNgCount[i];
			if (nTotal < 1) strText = "0.0%";
			else strText.Format("%0.1lf%%", gLot.nGoodCount[i] * 100.0 / nTotal);
			m_stcOperResult[2].SetWindowText(strText);
			return;
		}
	}
	m_stcOperLotId.SetWindowText("");
	m_stcOperResult[0].SetWindowText("");
	m_stcOperResult[1].SetWindowText("");
	m_stcOperResult[2].SetWindowText("");
}

void COperatorDlg::Update_TrayInfo(int nTray)
{
	int nj;
	CString strText;

//	strText.Format("%d", gData.nCarrierLine);
	m_stcOperLoadTray.SetWindowText(strText);

//	strText.Format("%d", gData.nNGLine);
	m_stcOperNgTray.SetWindowText(strText);

//	strText.Format("%d", gData.nGoodLine);
	m_stcOperShipTray.SetWindowText(strText);

	for (int i = 0; i < TRAY_CM_Y; i++) {
		for (int j = 0; j <TRAY_CM_X; j++) {
			if (j == 0) nj = 3; if (j == 1) nj = 2; if (j == 2) nj = 1; if (j == 3) nj = 0;
			if		(gData.InfoLoadTray[i][j] > 0)	m_grdOperLoadTray.Set_CellBackClr(i, nj, RGB(0xFF, 0x80, 0xFF));
			else									m_grdOperLoadTray.Set_CellBackClr(i, nj, RGB(0xFF, 0xFF, 0xFF));	// 0 Empty

			if		(gData.InfoNgTray[i][j] > 0)	m_grdOperNgTray.Set_CellBackClr(i, nj, RGB(0xFF, 0x00, 0x00));
			else									m_grdOperNgTray.Set_CellBackClr(i, nj, RGB(0xFF, 0xFF, 0xFF));	// 0 Empty

			if		(gData.InfoGoodTray[i][j] > 0)	m_grdOperShipTray.Set_CellBackClr(i, nj, RGB(0x00, 0xFF, 0x00));
			else									m_grdOperShipTray.Set_CellBackClr(i, nj, RGB(0xFF, 0xFF, 0xFF));	// 0 Empty

		}
	}
}

///////////////////////////////////////////////////////////////////////////////

void COperatorDlg::OnBnClickedBtnOperTest()
{
//	g_objSequenceInit.Set_InitComplete(TRUE);
//	g_objCommon.Show_Error(2221);
//	g_objCommon.Show_Alarm("TEST");
//	gLot.nGoodCount++;
//	gLot.nNgCount++;
}

///////////////////////////////////////////////////////////////////////////////
