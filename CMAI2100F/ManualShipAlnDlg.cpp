// ManualShipAlnDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualShipAlnDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

// CManualShipAlnDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualShipAlnDlg, CDialogEx)

CManualShipAlnDlg::CManualShipAlnDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualShipAlnDlg::IDD, pParent)
{
}

CManualShipAlnDlg::~CManualShipAlnDlg()
{
}

void CManualShipAlnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_ALN_SHIP_PICK1_X_0 + i, m_btnAlnShipPick1X[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_ALN_SHIP_PICK1_Y_0 + i, m_btnAlnShipPick1Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_ALN_SHIP_PICK2_X_0 + i, m_btnAlnShipPick2X[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_ALN_SHIP_PICK2_Y_0 + i, m_btnAlnShipPick2Y[i]);
}

BEGIN_MESSAGE_MAP(CManualShipAlnDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ALN_SHIP_PICK1_X_0, IDC_BTN_ALN_SHIP_PICK1_X_5, OnBtnAlnShipPick1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ALN_SHIP_PICK1_Y_0, IDC_BTN_ALN_SHIP_PICK1_Y_5, OnBtnAlnShipPick1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ALN_SHIP_PICK2_X_0, IDC_BTN_ALN_SHIP_PICK2_X_5, OnBtnAlnShipPick2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ALN_SHIP_PICK2_Y_0, IDC_BTN_ALN_SHIP_PICK2_Y_5, OnBtnAlnShipPick2YClick)
END_MESSAGE_MAP()

// CManualShipAlnDlg 메시지 처리기입니다.

BOOL CManualShipAlnDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualShipAlnDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualShipAlnDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	m_strLog.Format("[Manual Ship Align] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipAlnDlg::Initial_Controls() 
{
	for (int i = 0; i < 2; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 2; i < 4; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 0; i < 4; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 4; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i < 6; i++) m_btnAlnShipPick1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnAlnShipPick1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnAlnShipPick2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnAlnShipPick2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
}

void CManualShipAlnDlg::Display_Status()
{
	CString strPos;
	double dPos[4] = { 0.0 };

	dPos[0] = g_objAJinAXL.Get_Position(AX_SHIP_PICKER1_X);
	dPos[1] = g_objAJinAXL.Get_Position(AX_SHIP_PICKER1_Y);
	dPos[2] = g_objAJinAXL.Get_Position(AX_SHIP_PICKER2_X);
	dPos[3] = g_objAJinAXL.Get_Position(AX_SHIP_PICKER2_Y);

	for (int i = 0; i < 4; i++) {
		strPos.Format("%0.3lf", dPos[i]);
		m_stcAxisPos[i].SetWindowText(strPos);
	}
}

///////////////////////////////////////////////////////////////////////////////

void CManualShipAlnDlg::OnBtnAlnShipPick1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_ALN_SHIP_PICK1_X_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER1_Z, 0)) {
		if (g_objCommon.Check_Position(AX_SHIP_PICKER2_Y, 0)) {
			MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
			g_objAJinAXL.Move_Absolute(AX_SHIP_PICKER1_X, pMoveData->dAlnShipPick1X[nIndex]);

		} else {
			AfxMessageBox(_T("Ship Picker2 Y축 Reverse 위치 확인 후 진행하세요....."));
		}
	} else {
		AfxMessageBox(_T("Ship Picker1 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship Align] Align Ship Picker1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipAlnDlg::OnBtnAlnShipPick1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_ALN_SHIP_PICK1_Y_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER1_Z, 0)) {
		MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
		g_objAJinAXL.Move_Absolute(AX_SHIP_PICKER1_Y, pMoveData->dAlnShipPick1Y[nIndex]);
	} else {
		AfxMessageBox(_T("Ship Picker1 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship Align] Align Ship Picker1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipAlnDlg::OnBtnAlnShipPick2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_ALN_SHIP_PICK2_X_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER2_Z, 0)) {
		if (g_objCommon.Check_Position(AX_SHIP_PICKER1_Y, 0)) {
			MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
			g_objAJinAXL.Move_Absolute(AX_SHIP_PICKER2_X, pMoveData->dAlnShipPick2X[nIndex]);

		} else {
			AfxMessageBox(_T("Ship Picker1 Y축 Reverse 위치 확인 후 진행하세요....."));
		}
	} else {
		AfxMessageBox(_T("Ship Picker2 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship Align] Align Ship Picker2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipAlnDlg::OnBtnAlnShipPick2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_ALN_SHIP_PICK2_Y_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER2_Z, 0)) {
		MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
		g_objAJinAXL.Move_Absolute(AX_SHIP_PICKER2_Y, pMoveData->dAlnShipPick2Y[nIndex]);
	} else {
		AfxMessageBox(_T("Ship Picker2 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship Align] Align Ship Picker2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
