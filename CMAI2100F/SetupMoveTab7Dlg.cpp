// SetupMoveTab7Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupMoveTab7Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"

#include "AJinDefine.h"

// CSetupMoveTab7Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab7Dlg, CDialogEx)

CSetupMoveTab7Dlg::CSetupMoveTab7Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab7Dlg::IDD, pParent)
{
}

CSetupMoveTab7Dlg::~CSetupMoveTab7Dlg()
{
}

void CSetupMoveTab7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 32; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_ALN_SHIP_PICK1_X_0 + i, m_stcAlnShipPick1X[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_ALN_SHIP_PICK1_Y_0 + i, m_stcAlnShipPick1Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_ALN_SHIP_PICK2_X_0 + i, m_stcAlnShipPick2X[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_ALN_SHIP_PICK2_Y_0 + i, m_stcAlnShipPick2Y[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ALN_SHIP_PITCH_X_0 + i, m_stcAlnShipPitchX[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ALN_SHIP_PITCH_Y_0 + i, m_stcAlnShipPitchY[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ALN_SHIP_OFFSET_X_0 + i, m_stcAlnShipOffsetX[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ALN_SHIP_OFFSET_Y_0 + i, m_stcAlnShipOffsetY[i]);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab7Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ALN_SHIP_PICK1_X_0, IDC_STC_ALN_SHIP_PICK1_X_5, OnStcAlnShipPick1XClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ALN_SHIP_PICK1_Y_0, IDC_STC_ALN_SHIP_PICK1_Y_5, OnStcAlnShipPick1YClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ALN_SHIP_PICK2_X_0, IDC_STC_ALN_SHIP_PICK2_X_5, OnStcAlnShipPick2XClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ALN_SHIP_PICK2_Y_0, IDC_STC_ALN_SHIP_PICK2_Y_5, OnStcAlnShipPick2YClick)
END_MESSAGE_MAP()

// CSetupMoveTab7Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab7Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab7Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab7Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab7");
}

void CSetupMoveTab7Dlg::OnStcAlnShipPick1XClick(UINT nID)
{
	int ID = nID - IDC_STC_ALN_SHIP_PICK1_X_0;

	CString strOld, strNew;
	m_stcAlnShipPick1X[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER1_X) != IDOK) return;

	m_stcAlnShipPick1X[ID].SetWindowText(strNew);
}

void CSetupMoveTab7Dlg::OnStcAlnShipPick1YClick(UINT nID)
{
	int ID = nID - IDC_STC_ALN_SHIP_PICK1_Y_0;

	CString strOld, strNew;
	m_stcAlnShipPick1Y[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER1_Y) != IDOK) return;

	m_stcAlnShipPick1Y[ID].SetWindowText(strNew);
}

void CSetupMoveTab7Dlg::OnStcAlnShipPick2XClick(UINT nID)
{
	int ID = nID - IDC_STC_ALN_SHIP_PICK2_X_0;

	CString strOld, strNew;
	m_stcAlnShipPick2X[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER2_X) != IDOK) return;

	m_stcAlnShipPick2X[ID].SetWindowText(strNew);
}

void CSetupMoveTab7Dlg::OnStcAlnShipPick2YClick(UINT nID)
{
	int ID = nID - IDC_STC_ALN_SHIP_PICK2_Y_0;

	CString strOld, strNew;
	m_stcAlnShipPick2Y[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_PICKER2_Y) != IDOK) return;

	m_stcAlnShipPick2Y[ID].SetWindowText(strNew);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab7Dlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 24; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 24; i < 32; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x60, 0x00));

	for (int i = 0; i < 3; i++) m_stcAlnShipPick1X[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));
	for (int i = 3; i < 6; i++) m_stcAlnShipPick1X[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));

	for (int i = 0; i < 3; i++) m_stcAlnShipPick1Y[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));
	for (int i = 3; i < 6; i++) m_stcAlnShipPick1Y[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));

	for (int i = 0; i < 3; i++) m_stcAlnShipPick2X[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 3; i < 6; i++) m_stcAlnShipPick2X[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));

	for (int i = 0; i < 3; i++) m_stcAlnShipPick2Y[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 3; i < 6; i++) m_stcAlnShipPick2Y[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));

	for (int i = 0; i < 4; i++) m_stcAlnShipPitchX[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 4; i++) m_stcAlnShipPitchY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 4; i++) m_stcAlnShipOffsetX[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 4; i++) m_stcAlnShipOffsetY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
}

void CSetupMoveTab7Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;

	for (int i = 0; i < 6; i++) { strData.Format("%0.3lf", pMoveData->dAlnShipPick1X[i]);	m_stcAlnShipPick1X[i].SetWindowText(strData); }
	for (int i = 0; i < 6; i++) { strData.Format("%0.3lf", pMoveData->dAlnShipPick1Y[i]);	m_stcAlnShipPick1Y[i].SetWindowText(strData); }
	for (int i = 0; i < 6; i++) { strData.Format("%0.3lf", pMoveData->dAlnShipPick2X[i]);	m_stcAlnShipPick2X[i].SetWindowText(strData); }
	for (int i = 0; i < 6; i++) { strData.Format("%0.3lf", pMoveData->dAlnShipPick2Y[i]);	m_stcAlnShipPick2Y[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShipPitchX[i]);	m_stcAlnShipPitchX[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShipPitchY[i]);	m_stcAlnShipPitchY[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShipOffsetX[i]);	m_stcAlnShipOffsetX[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShipOffsetY[i]);	m_stcAlnShipOffsetY[i].SetWindowText(strData); }
}

void CSetupMoveTab7Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return;
	}

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);	m_stcAlnShipPick1X[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("ALN_SHIP_PICK1_X", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);	m_stcAlnShipPick1Y[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("ALN_SHIP_PICK1_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);	m_stcAlnShipPick2X[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("ALN_SHIP_PICK2_X", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);	m_stcAlnShipPick2Y[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("ALN_SHIP_PICK2_Y", strKey, dData, "%0.3lf"); }

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 7] save");

	Cancel_MoveData();
}

void CSetupMoveTab7Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
