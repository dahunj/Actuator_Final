// SetupMoveTab6Dlg.cpp : ±∏«ˆ ∆ƒ¿œ¿‘¥œ¥Ÿ.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupMoveTab6Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"

#include "AJinDefine.h"

// CSetupMoveTab6Dlg ¥Î»≠ ªÛ¿⁄¿‘¥œ¥Ÿ.

IMPLEMENT_DYNAMIC(CSetupMoveTab6Dlg, CDialogEx)

CSetupMoveTab6Dlg::CSetupMoveTab6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab6Dlg::IDD, pParent)
{
}

CSetupMoveTab6Dlg::~CSetupMoveTab6Dlg()
{
}

void CSetupMoveTab6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 17; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 63; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_SHIP_TRAY1_Y_0 + i, m_stcShipTray1Y[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_SHIP_TRAY1_Z_0 + i, m_stcShipTray1Z[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_SHIP_TRAY2_Y_0 + i, m_stcShipTray2Y[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_SHIP_TRAY2_Z_0 + i, m_stcShipTray2Z[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_SHIP_PICKER1_X_0 + i, m_stcShipPicker1X[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_SHIP_PICKER1_Y_0 + i, m_stcShipPicker1Y[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_SHIP_PICKER1_Z_0 + i, m_stcShipPicker1Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_SHIP_PICKER1_R_0 + i, m_stcShipPicker1R[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_SHIP_PICKER2_X_0 + i, m_stcShipPicker2X[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_SHIP_PICKER2_Y_0 + i, m_stcShipPicker2Y[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_SHIP_PICKER2_Z_0 + i, m_stcShipPicker2Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_SHIP_PICKER2_R_0 + i, m_stcShipPicker2R[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_REVERSE1_Z_0 + i, m_stcReverse1Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_REVERSE1_R_0 + i, m_stcReverse1R[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_REVERSE2_Z_0 + i, m_stcReverse2Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_STC_REVERSE2_R_0 + i, m_stcReverse2R[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_DROP_TABLE_Y_0 + i, m_stcDropTableY[i]);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab6Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_TRAY1_Y_0, IDC_STC_SHIP_TRAY1_Y_2, OnStcShipTray1YClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_TRAY1_Z_0, IDC_STC_SHIP_TRAY1_Z_3, OnStcShipTray1ZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_TRAY2_Y_0, IDC_STC_SHIP_TRAY2_Y_2, OnStcShipTray2YClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_TRAY2_Z_0, IDC_STC_SHIP_TRAY2_Z_3, OnStcShipTray2ZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_PICKER1_X_0, IDC_STC_SHIP_PICKER1_X_7, OnStcShipPicker1XClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_PICKER1_Y_0, IDC_STC_SHIP_PICKER1_Y_2, OnStcShipPicker1YClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_PICKER1_Z_0, IDC_STC_SHIP_PICKER1_Z_3, OnStcShipPicker1ZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_PICKER1_R_0, IDC_STC_SHIP_PICKER1_R_1, OnStcShipPicker1RClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_PICKER2_X_0, IDC_STC_SHIP_PICKER2_X_7, OnStcShipPicker2XClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_PICKER2_Y_0, IDC_STC_SHIP_PICKER2_Y_2, OnStcShipPicker2YClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_PICKER2_Z_0, IDC_STC_SHIP_PICKER2_Z_3, OnStcShipPicker2ZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_PICKER2_R_0, IDC_STC_SHIP_PICKER2_R_1, OnStcShipPicker2RClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_REVERSE1_Z_0, IDC_STC_REVERSE1_Z_2, OnStcReverse1ZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_REVERSE1_R_0, IDC_STC_REVERSE1_R_1, OnStcReverse1RClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_REVERSE2_Z_0, IDC_STC_REVERSE2_Z_2, OnStcReverse2ZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_REVERSE2_R_0, IDC_STC_REVERSE2_R_1, OnStcReverse2RClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_DROP_TABLE_Y_0, IDC_STC_DROP_TABLE_Y_4, OnStcDropTableYClick)
END_MESSAGE_MAP()

// CSetupMoveTab6Dlg ∏ﬁΩ√¡ˆ √≥∏Æ±‚¿‘¥œ¥Ÿ.

BOOL CSetupMoveTab6Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ø©±‚ø° √ﬂ∞° √ ±‚»≠ ¿€æ˜¿ª √ﬂ∞°«’¥œ¥Ÿ.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// øπø‹: OCX º”º∫ ∆‰¿Ã¡ˆ¥¬ FALSE∏¶ π›»Ø«ÿæﬂ «’¥œ¥Ÿ.
}

BOOL CSetupMoveTab6Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab6Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab6");
}

void CSetupMoveTab6Dlg::OnStcShipTray1YClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_TRAY1_Y_0;

	CString strOld, strNew;
	m_stcShipTray1Y[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_TRAY1_Y) != IDOK) return;

	m_stcShipTray1Y[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipTray1ZClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_TRAY1_Z_0;

	CString strOld, strNew;
	m_stcShipTray1Z[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_TRAY1_Z) != IDOK) return;

	m_stcShipTray1Z[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipTray2YClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_TRAY2_Y_0;

	CString strOld, strNew;
	m_stcShipTray2Y[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_TRAY2_Y) != IDOK) return;

	m_stcShipTray2Y[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipTray2ZClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_TRAY2_Z_0;

	CString strOld, strNew;
	m_stcShipTray2Z[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_TRAY2_Z) != IDOK) return;

	m_stcShipTray2Z[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipPicker1XClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_PICKER1_X_0;

	CString strOld, strNew;
	m_stcShipPicker1X[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER1_X) != IDOK) return;

	m_stcShipPicker1X[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipPicker1YClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_PICKER1_Y_0;

	CString strOld, strNew;
	m_stcShipPicker1Y[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER1_Y) != IDOK) return;

	m_stcShipPicker1Y[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipPicker1ZClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_PICKER1_Z_0;

	CString strOld, strNew;
	m_stcShipPicker1Z[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER1_Z) != IDOK) return;

	m_stcShipPicker1Z[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipPicker1RClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_PICKER1_R_0;

	CString strOld, strNew;
	m_stcShipPicker1R[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER1_R) != IDOK) return;

	m_stcShipPicker1R[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipPicker2XClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_PICKER2_X_0;

	CString strOld, strNew;
	m_stcShipPicker2X[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER2_X) != IDOK) return;

	m_stcShipPicker2X[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipPicker2YClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_PICKER2_Y_0;

	CString strOld, strNew;
	m_stcShipPicker2Y[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER2_Y) != IDOK) return;

	m_stcShipPicker2Y[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipPicker2ZClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_PICKER2_Z_0;

	CString strOld, strNew;
	m_stcShipPicker2Z[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER2_Z) != IDOK) return;

	m_stcShipPicker2Z[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcShipPicker2RClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_PICKER2_R_0;

	CString strOld, strNew;
	m_stcShipPicker2R[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER2_R) != IDOK) return;

	m_stcShipPicker2R[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcReverse1ZClick(UINT nID)
{
	int ID = nID - IDC_STC_REVERSE1_Z_0;

	CString strOld, strNew;
	m_stcReverse1Z[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_REVERSE1_Z) != IDOK) return;

	m_stcReverse1Z[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcReverse1RClick(UINT nID)
{
	int ID = nID - IDC_STC_REVERSE1_R_0;

	CString strOld, strNew;
	m_stcReverse1R[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_REVERSE1_R) != IDOK) return;

	m_stcReverse1R[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcReverse2ZClick(UINT nID)
{
	int ID = nID - IDC_STC_REVERSE2_Z_0;

	CString strOld, strNew;
	m_stcReverse2Z[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_REVERSE2_Z) != IDOK) return;

	m_stcReverse2Z[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcReverse2RClick(UINT nID)
{
	int ID = nID - IDC_STC_REVERSE2_R_0;

	CString strOld, strNew;
	m_stcReverse2R[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_REVERSE2_R) != IDOK) return;

	m_stcReverse2R[ID].SetWindowText(strNew);
}

void CSetupMoveTab6Dlg::OnStcDropTableYClick(UINT nID)
{
	int ID = nID - IDC_STC_DROP_TABLE_Y_0;

	CString strOld, strNew;
	m_stcDropTableY[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_DROP_TABLE_Y) != IDOK) return;

	m_stcDropTableY[ID].SetWindowText(strNew);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab6Dlg::Initial_Controls() 
{
	for (int i = 0; i < 17; i++) m_Group[i].Init_Ctrl("πŸ≈¡", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 63; i++) m_Label[i].Init_Ctrl("πŸ≈¡", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 3; i++) m_stcShipTray1Y[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 4; i++) m_stcShipTray1Z[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	
	for (int i = 0; i < 3; i++) m_stcShipTray2Y[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 4; i++) m_stcShipTray2Z[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	
	for (int i = 0; i < 8; i++) m_stcShipPicker1X[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));
	for (int i = 0; i < 3; i++) m_stcShipPicker1Y[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));
	for (int i = 0; i < 4; i++) m_stcShipPicker1Z[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));
	for (int i = 0; i < 2; i++) m_stcShipPicker1R[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));
	
	for (int i = 0; i < 8; i++) m_stcShipPicker2X[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 3; i++) m_stcShipPicker2Y[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 4; i++) m_stcShipPicker2Z[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 2; i++) m_stcShipPicker2R[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	
	for (int i = 0; i < 3; i++) m_stcReverse1Z[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 2; i++) m_stcReverse1R[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));

	for (int i = 0; i < 3; i++) m_stcReverse2Z[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 2; i++) m_stcReverse2R[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	
	for (int i = 0; i < 5; i++) m_stcDropTableY[i].Init_Ctrl("πŸ≈¡", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));
}

void CSetupMoveTab6Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;

	for (int i = 0; i < 3; i++) { strData.Format("%0.3lf", pMoveData->dShipTray1Y[i]);		m_stcShipTray1Y[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShipTray1Z[i]);		m_stcShipTray1Z[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++) { strData.Format("%0.3lf", pMoveData->dShipTray2Y[i]);		m_stcShipTray2Y[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShipTray2Z[i]);		m_stcShipTray2Z[i].SetWindowText(strData); }
	for (int i = 0; i < 8; i++) { strData.Format("%0.3lf", pMoveData->dShipPicker1X[i]);	m_stcShipPicker1X[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++) { strData.Format("%0.3lf", pMoveData->dShipPicker1Y[i]);	m_stcShipPicker1Y[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShipPicker1Z[i]);	m_stcShipPicker1Z[i].SetWindowText(strData); }
	for (int i = 0; i < 2; i++) { strData.Format("%0.3lf", pMoveData->dShipPicker1R[i]);	m_stcShipPicker1R[i].SetWindowText(strData); }
	for (int i = 0; i < 8; i++) { strData.Format("%0.3lf", pMoveData->dShipPicker2X[i]);	m_stcShipPicker2X[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++) { strData.Format("%0.3lf", pMoveData->dShipPicker2Y[i]);	m_stcShipPicker2Y[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShipPicker2Z[i]);	m_stcShipPicker2Z[i].SetWindowText(strData); }
	for (int i = 0; i < 2; i++) { strData.Format("%0.3lf", pMoveData->dShipPicker2R[i]);	m_stcShipPicker2R[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++) { strData.Format("%0.3lf", pMoveData->dReverse1Z[i]);		m_stcReverse1Z[i].SetWindowText(strData); }
	for (int i = 0; i < 2; i++) { strData.Format("%0.3lf", pMoveData->dReverse1R[i]);		m_stcReverse1R[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++) { strData.Format("%0.3lf", pMoveData->dReverse2Z[i]);		m_stcReverse2Z[i].SetWindowText(strData); }
	for (int i = 0; i < 2; i++) { strData.Format("%0.3lf", pMoveData->dReverse2R[i]);		m_stcReverse2R[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dDropTableY[i]);		m_stcDropTableY[i].SetWindowText(strData); }
}

void CSetupMoveTab6Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return;
	}

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);	m_stcShipTray1Y[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("67_SHIP_TRAY1_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 4; i++) { strKey.Format("%02d", i);	m_stcShipTray1Z[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("69_SHIP_TRAY1_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);	m_stcShipTray2Y[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("68_SHIP_TRAY2_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 4; i++) { strKey.Format("%02d", i);	m_stcShipTray2Z[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("70_SHIP_TRAY2_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 8; i++) { strKey.Format("%02d", i);	m_stcShipPicker1X[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("71_SHIP_PICKER1_X", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);	m_stcShipPicker1Y[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("72_SHIP_PICKER1_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 4; i++) { strKey.Format("%02d", i);	m_stcShipPicker1Z[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("73_SHIP_PICKER1_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 2; i++) { strKey.Format("%02d", i);	m_stcShipPicker1R[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("74_SHIP_PICKER1_R", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 8; i++) { strKey.Format("%02d", i);	m_stcShipPicker2X[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("75_SHIP_PICKER2_X", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);	m_stcShipPicker2Y[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("76_SHIP_PICKER2_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 4; i++) { strKey.Format("%02d", i);	m_stcShipPicker2Z[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("77_SHIP_PICKER2_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 2; i++) { strKey.Format("%02d", i);	m_stcShipPicker2R[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("78_SHIP_PICKER2_R", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);	m_stcReverse1Z[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("62_REVERSE1_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 2; i++) { strKey.Format("%02d", i);	m_stcReverse1R[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("63_REVERSE1_R", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);	m_stcReverse2Z[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("64_REVERSE2_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 2; i++) { strKey.Format("%02d", i);	m_stcReverse2R[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("65_REVERSE2_R", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcDropTableY[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("66_DROP_TABLE_Y", strKey, dData, "%0.3lf"); }

	// 3¡° Align ¿˙¿Â
	m_stcShipPicker1X[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double("ALN_SHIP_PICK1_X", "00", dData, "%0.3lf");	// Ship Picker1 X - Tray1
	m_stcShipPicker1X[4].GetWindowText(strData); dData = atof(strData); INI.Set_Double("ALN_SHIP_PICK1_X", "03", dData, "%0.3lf");	// Ship Picker1 X - Tray2
	m_stcShipPicker1Y[1].GetWindowText(strData); dData = atof(strData);	INI.Set_Double("ALN_SHIP_PICK1_Y", "00", dData, "%0.3lf");	// Ship Picker1 Y - Tray1
																		INI.Set_Double("ALN_SHIP_PICK1_Y", "03", dData, "%0.3lf");	// Ship Picker1 Y - Tray2
	m_stcShipPicker2X[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double("ALN_SHIP_PICK2_X", "00", dData, "%0.3lf");	// Ship Picker2 X - Tray1
	m_stcShipPicker2X[4].GetWindowText(strData); dData = atof(strData); INI.Set_Double("ALN_SHIP_PICK2_X", "03", dData, "%0.3lf");	// Ship Picker2 X - Tray2
	m_stcShipPicker2Y[1].GetWindowText(strData); dData = atof(strData);	INI.Set_Double("ALN_SHIP_PICK2_Y", "00", dData, "%0.3lf");	// Ship Picker2 Y - Tray1
																		INI.Set_Double("ALN_SHIP_PICK2_Y", "03", dData, "%0.3lf");	// Ship Picker2 Y - Tray2
	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 6] save");

	Cancel_MoveData();
}

void CSetupMoveTab6Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
