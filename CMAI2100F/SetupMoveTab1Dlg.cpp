// SetupMoveTab1Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupMoveTab1Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"

#include "AJinDefine.h"

// CSetupMoveTab1Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab1Dlg, CDialogEx)

CSetupMoveTab1Dlg::CSetupMoveTab1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab1Dlg::IDD, pParent)
{
}

CSetupMoveTab1Dlg::~CSetupMoveTab1Dlg()
{
}

void CSetupMoveTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 68; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 21; i++) DDX_Control(pDX, IDC_STC_ELEVATOR_0 + i, m_stcElevator[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_TRANSFER_X1_0 + i, m_stcTransfreX1[i]);
	for (int i = 0; i < 13; i++) DDX_Control(pDX, IDC_STC_TRANSFER_X2_0 + i, m_stcTransfreX2[i]);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_STC_TRANSFER_Z1_0 + i, m_stcTransfreZ1[i]);
	for (int i = 0; i < 15; i++) DDX_Control(pDX, IDC_STC_TRANSFER_Z2_0 + i, m_stcTransfreZ2[i]);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab1Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ELEVATOR_0, IDC_STC_ELEVATOR_20, OnStcElevatorClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRANSFER_X1_0, IDC_STC_TRANSFER_X1_7, OnStcTransferX1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRANSFER_X2_0, IDC_STC_TRANSFER_X2_12, OnStcTransferX2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRANSFER_Z1_0, IDC_STC_TRANSFER_Z1_10, OnStcTransferZ1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TRANSFER_Z2_0, IDC_STC_TRANSFER_Z2_14, OnStcTransferZ2Click)
END_MESSAGE_MAP()

// CSetupMoveTab1Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab1Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab1Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab1Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab1");
}

void CSetupMoveTab1Dlg::OnStcElevatorClick(UINT nID)
{
	int ID = nID - IDC_STC_ELEVATOR_0;

	CString strOld, strNew;
	m_stcElevator[ID].GetWindowText(strOld);
	if (ID == 0 || ID == 1 || ID == 2) {
		if (g_objCommon.Show_NumPad(strOld, strNew, AX_ELEVATOR_Z1) != IDOK) return;
		if (g_objCommon.Check_MoveData(AX_ELEVATOR_Z1, ID, strNew)==FALSE) return;
	}
	if (ID == 3 || ID == 4 || ID == 5) {
		if (g_objCommon.Show_NumPad(strOld, strNew, AX_ELEVATOR_Z2) != IDOK) return;
		if (g_objCommon.Check_MoveData(AX_ELEVATOR_Z2, ID-3, strNew)==FALSE) return;
	}
	if (ID == 6 || ID == 7 || ID == 8) {
		if (g_objCommon.Show_NumPad(strOld, strNew, AX_ELEVATOR_Z3) != IDOK) return;
		if (g_objCommon.Check_MoveData(AX_ELEVATOR_Z3, ID-6, strNew)==FALSE) return;
	}
	if (ID == 9 || ID == 10 || ID == 11) {
		if (g_objCommon.Show_NumPad(strOld, strNew, AX_ELEVATOR_Z4) != IDOK) return;
		if (g_objCommon.Check_MoveData(AX_ELEVATOR_Z4, ID-9, strNew)==FALSE) return;
	}
	if (ID == 12 || ID == 13 || ID == 14) {
		if (g_objCommon.Show_NumPad(strOld, strNew, AX_ELEVATOR_Z5) != IDOK) return;
		if (g_objCommon.Check_MoveData(AX_ELEVATOR_Z5, ID-12, strNew)==FALSE) return;
	}
	if (ID == 15 || ID == 16 || ID == 17) {
		if (g_objCommon.Show_NumPad(strOld, strNew, AX_ELEVATOR_Z6) != IDOK) return;
		if (g_objCommon.Check_MoveData(AX_ELEVATOR_Z6, ID-15, strNew)==FALSE) return;
	}
	if (ID == 18 || ID == 19 || ID == 20) {
		if (g_objCommon.Show_NumPad(strOld, strNew, AX_ELEVATOR_Z7) != IDOK) return;
		if (g_objCommon.Check_MoveData(AX_ELEVATOR_Z7, ID-18, strNew)==FALSE) return;
	}

	m_stcElevator[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcElevatorClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab1Dlg::OnStcTransferX1Click(UINT nID)
{
	int ID = nID - IDC_STC_TRANSFER_X1_0;

	CString strOld, strNew;
	m_stcTransfreX1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TRANSFER_X1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_TRANSFER_X1, ID+1, strNew)==FALSE) return;

	m_stcTransfreX1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcTransferX1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab1Dlg::OnStcTransferX2Click(UINT nID)
{
	int ID = nID - IDC_STC_TRANSFER_X2_0;

	CString strOld, strNew;
	m_stcTransfreX2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TRANSFER_X2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_TRANSFER_X2, ID+1, strNew)==FALSE) return;

	m_stcTransfreX2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcTransferX2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab1Dlg::OnStcTransferZ1Click(UINT nID)
{
	int ID = nID - IDC_STC_TRANSFER_Z1_0;

	CString strOld, strNew;
	m_stcTransfreZ1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TRANSFER_Z1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_TRANSFER_Z1, ID, strNew)==FALSE) return;

	m_stcTransfreZ1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcTransferZ1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab1Dlg::OnStcTransferZ2Click(UINT nID)
{
	int ID = nID - IDC_STC_TRANSFER_Z2_0;

	CString strOld, strNew;
	m_stcTransfreZ2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TRANSFER_Z2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_TRANSFER_Z2, ID, strNew)==FALSE) return;

	m_stcTransfreZ2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcTransferZ2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab1Dlg::Initial_Controls() 
{
	for (int i = 0; i < 11; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 68; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 21; i++)  m_stcElevator[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 8; i++)  m_stcTransfreX1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 13; i++)  m_stcTransfreX2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 11; i++)  m_stcTransfreZ1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 15; i++)  m_stcTransfreZ2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
}

void CSetupMoveTab1Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dElevatorZ1[i]);		m_stcElevator[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dElevatorZ2[i]);		m_stcElevator[i+3].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dElevatorZ3[i]);		m_stcElevator[i+6].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dElevatorZ4[i]);		m_stcElevator[i+9].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dElevatorZ5[i]);		m_stcElevator[i+12].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dElevatorZ6[i]);		m_stcElevator[i+15].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dElevatorZ7[i]);		m_stcElevator[i+18].SetWindowText(strData); }
	for (int i = 0; i < 8; i++)  { strData.Format("%0.3lf", pMoveData->dTransferX1[i+1]);	m_stcTransfreX1[i].SetWindowText(strData); }
	for (int i = 0; i < 13; i++)  { strData.Format("%0.3lf", pMoveData->dTransferX2[i+1]);	m_stcTransfreX2[i].SetWindowText(strData); }
	for (int i = 0; i < 11; i++)  { strData.Format("%0.3lf", pMoveData->dTransferZ1[i]);	m_stcTransfreZ1[i].SetWindowText(strData); }
	for (int i = 0; i < 15; i++)  { strData.Format("%0.3lf", pMoveData->dTransferZ2[i]);	m_stcTransfreZ2[i].SetWindowText(strData); }
}

void CSetupMoveTab1Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return;
	}

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("00_ELEVATOR_Z1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+3].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("01_ELEVATOR_Z2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+6].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("02_ELEVATOR_Z3", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+9].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("03_ELEVATOR_Z4", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+12].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("04_ELEVATOR_Z5", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+15].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("05_ELEVATOR_Z6", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+18].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("06_ELEVATOR_Z7", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 8; i++)  { strKey.Format("%02d", i+1);	m_stcTransfreX1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("07_TRANSFER_X1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 13; i++)  { strKey.Format("%02d", i+1);	m_stcTransfreX2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("09_TRANSFER_X2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 11; i++)  { strKey.Format("%02d", i);	m_stcTransfreZ1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("08_TRANSFER_Z1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 15; i++)  { strKey.Format("%02d", i);	m_stcTransfreZ2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("10_TRANSFER_Z2", strKey, dData, "%0.3lf"); }

//	Save_ModelMoveData();

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 1] save");

	Cancel_MoveData();
}

void CSetupMoveTab1Dlg::Save_ModelMoveData()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	CString strPath = gsCurrentDir + "\\System\\Model\\" + pEquipData->sModelName + "\\MoveData.ini";
	CIniFileCS INI(strPath);
	if (!INI.Check_File()) {
		AfxMessageBox("Model MoveData.ini File Not Found!!!");
		return;
	}

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("00_ELEVATOR_Z1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+3].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("01_ELEVATOR_Z2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+6].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("02_ELEVATOR_Z3", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+9].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("03_ELEVATOR_Z4", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+12].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("04_ELEVATOR_Z5", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+15].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("05_ELEVATOR_Z6", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcElevator[i+18].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("06_ELEVATOR_Z7", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 8; i++)  { strKey.Format("%02d", i+1);	m_stcTransfreX1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("07_TRANSFER_X1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 13; i++)  { strKey.Format("%02d", i+1);	m_stcTransfreX2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("09_TRANSFER_X2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 11; i++)  { strKey.Format("%02d", i);	m_stcTransfreZ1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("08_TRANSFER_Z1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 15; i++)  { strKey.Format("%02d", i);	m_stcTransfreZ2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("10_TRANSFER_Z2", strKey, dData, "%0.3lf"); }

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 1] Model save");
}

void CSetupMoveTab1Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
