// ManualShipDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualShipDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

// CManualShipDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualShipDlg, CDialogEx)

CManualShipDlg::CManualShipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualShipDlg::IDD, pParent)
{
}

CManualShipDlg::~CManualShipDlg()
{
}

void CManualShipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 18; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER1_X_0 + i, m_btnShipPicker1X[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER1_Y_0 + i, m_btnShipPicker1Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER1_Z_0 + i, m_btnShipPicker1Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER1_R_0 + i, m_btnShipPicker1R[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER2_X_0 + i, m_btnShipPicker2X[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER2_Y_0 + i, m_btnShipPicker2Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER2_Z_0 + i, m_btnShipPicker2Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER2_R_0 + i, m_btnShipPicker2R[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_BTN_SHIP_PICKER_IO_0 + i, m_btnShipPickerIo[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_LED_SHIP_PICKER_IO_0 + i, m_ledShipPickerIo[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_SHIP_PORT_IO_0 + i, m_btnShipPortIo[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LED_SHIP_PORT_IO_0 + i, m_ledShipPortIo[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_SHIP_TRAY1_Y_0 + i, m_btnShipTray1Y[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_SHIP_TRAY1_Z_0 + i, m_btnShipTray1Z[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_SHIP_TRAY2_Y_0 + i, m_btnShipTray2Y[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_SHIP_TRAY2_Z_0 + i, m_btnShipTray2Z[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_SHIP_TRAY_IO_0 + i, m_btnShipTrayIo[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LED_SHIP_TRAY_IO_0 + i, m_ledShipTrayIo[i]);
}

BEGIN_MESSAGE_MAP(CManualShipDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER1_X_0, IDC_BTN_SHIP_PICKER1_X_9, OnBtnShipPicker1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER1_Y_0, IDC_BTN_SHIP_PICKER1_Y_2, OnBtnShipPicker1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER1_Z_0, IDC_BTN_SHIP_PICKER1_Z_5, OnBtnShipPicker1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER1_R_0, IDC_BTN_SHIP_PICKER1_R_1, OnBtnShipPicker1RClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER2_X_0, IDC_BTN_SHIP_PICKER2_X_9, OnBtnShipPicker2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER2_Y_0, IDC_BTN_SHIP_PICKER2_Y_2, OnBtnShipPicker2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER2_Z_0, IDC_BTN_SHIP_PICKER2_Z_5, OnBtnShipPicker2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER2_R_0, IDC_BTN_SHIP_PICKER2_R_1, OnBtnShipPicker2RClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PICKER_IO_0, IDC_BTN_SHIP_PICKER_IO_11, OnBtnShipPickerIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_PORT_IO_0, IDC_BTN_SHIP_PORT_IO_3, OnBtnShipPortIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_TRAY1_Y_0, IDC_BTN_SHIP_TRAY1_Y_4, OnBtnShipTray1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_TRAY1_Z_0, IDC_BTN_SHIP_TRAY1_Z_3, OnBtnShipTray1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_TRAY2_Y_0, IDC_BTN_SHIP_TRAY2_Y_4, OnBtnShipTray2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_TRAY2_Z_0, IDC_BTN_SHIP_TRAY2_Z_3, OnBtnShipTray2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SHIP_TRAY_IO_0, IDC_BTN_SHIP_TRAY_IO_7, OnBtnShipTrayIoClick)
END_MESSAGE_MAP()

// CManualShipDlg 메시지 처리기입니다.

BOOL CManualShipDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualShipDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualShipDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	m_strLog.Format("[Manual Ship] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::Initial_Controls() 
{
	for (int i = 0; i < 10; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 10; i < 12; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 12; i < 18; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 0; i < 12; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 12; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i < 10; i++) m_btnShipPicker1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnShipPicker1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnShipPicker1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnShipPicker1R[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 10; i++) m_btnShipPicker2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnShipPicker2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnShipPicker2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnShipPicker2R[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 12; i++) m_btnShipPickerIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 10; i++) m_ledShipPickerIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 4; i++) m_btnShipPortIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 12; i++) m_ledShipPortIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 5; i++) m_btnShipTray1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnShipTray1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++) m_btnShipTray2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnShipTray2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnShipTrayIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 12; i++) m_ledShipTrayIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CManualShipDlg::Display_Status()
{
	CString strPos;
	for (int i = 0; i < 12; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_SHIP_TRAY1_Y + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	DX_DATA_11 *pDX11 = g_objAJinAXL.Get_pDX11();
	DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();

	m_ledShipPickerIo[0].Set_On(pDX12->iShipPicker1Vacuum1Chk);
	m_ledShipPickerIo[1].Set_On(pDX12->iShipPicker1Vacuum2Chk);
	m_ledShipPickerIo[2].Set_On(pDX12->iShipPicker1Overload);
	m_ledShipPickerIo[3].Set_On(pDX12->iShipPicker1GripOpen);
	m_ledShipPickerIo[4].Set_On(pDX12->iShipPicker1CapCheck);
	m_ledShipPickerIo[5].Set_On(pDX12->iShipPicker2Vacuum1Chk);
	m_ledShipPickerIo[6].Set_On(pDX12->iShipPicker2Vacuum2Chk);
	m_ledShipPickerIo[7].Set_On(pDX12->iShipPicker2Overload);
	m_ledShipPickerIo[8].Set_On(pDX12->iShipPicker2GripOpen);
	m_ledShipPickerIo[9].Set_On(pDX12->iShipPicker2CapCheck);

	m_ledShipPortIo[0].Set_On(pDX11->iShipPort1Support1In);
	m_ledShipPortIo[1].Set_On(pDX11->iShipPort1Support1Out);
	m_ledShipPortIo[2].Set_On(pDX11->iShipPort1Support2In);
	m_ledShipPortIo[3].Set_On(pDX11->iShipPort1Support2Out);
	m_ledShipPortIo[4].Set_On(pDX11->iShipPort1TrayExist);
	m_ledShipPortIo[5].Set_On(pDX11->iShipPort1FullCheck);
	m_ledShipPortIo[6].Set_On(pDX11->iShipPort2Support1In);
	m_ledShipPortIo[7].Set_On(pDX11->iShipPort2Support1Out);
	m_ledShipPortIo[8].Set_On(pDX11->iShipPort2Support2In);
	m_ledShipPortIo[9].Set_On(pDX11->iShipPort2Support2Out);
	m_ledShipPortIo[10].Set_On(pDX11->iShipPort2TrayExist);
	m_ledShipPortIo[11].Set_On(pDX11->iShipPort2FullCheck);

	m_ledShipTrayIo[0].Set_On(pDX12->iShipTray1MasterIn);
	m_ledShipTrayIo[1].Set_On(pDX12->iShipTray1MasterOut);
	m_ledShipTrayIo[2].Set_On(pDX12->iShipTray1SlaveIn);
	m_ledShipTrayIo[3].Set_On(pDX12->iShipTray1SlaveOut);
	m_ledShipTrayIo[4].Set_On(pDX12->iShipTray1TrayExist1);
	m_ledShipTrayIo[5].Set_On(pDX12->iShipTray1TrayExist2);
	m_ledShipTrayIo[6].Set_On(pDX12->iShipTray2MasterIn);
	m_ledShipTrayIo[7].Set_On(pDX12->iShipTray2MasterOut);
	m_ledShipTrayIo[8].Set_On(pDX12->iShipTray2SlaveIn);
	m_ledShipTrayIo[9].Set_On(pDX12->iShipTray2SlaveOut);
	m_ledShipTrayIo[10].Set_On(pDX12->iShipTray2TrayExist1);
	m_ledShipTrayIo[11].Set_On(pDX12->iShipTray2TrayExist2);
}

///////////////////////////////////////////////////////////////////////////////

void CManualShipDlg::OnBtnShipPicker1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER1_X_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER1_Z, 0)) {
		if (nIndex == 8 || nIndex == 9) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 9 ? -1 : 1);
			double dMove = pEquipData->dShipTrayPitchX * nDir;
			g_objAJinAXL.Move_Relative(AX_SHIP_PICKER1_X, dMove);

		} else {
			if (g_objCommon.Check_Position(AX_SHIP_PICKER1_Y, 0) || g_objCommon.Check_Position(AX_SHIP_PICKER1_Y, 2)) {
				if (nIndex == 3) {
					if (g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 1)) {
						g_objCommon.Move_Position(AX_SHIP_PICKER1_X, nIndex);
					} else {
						AfxMessageBox(_T("Ship Tray 1 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
					}
				} else if (nIndex == 4) {
					if (g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 1)) {
						g_objCommon.Move_Position(AX_SHIP_PICKER1_X, nIndex);
					} else {
						AfxMessageBox(_T("Ship Tray 2 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
					}
				} else {
					g_objCommon.Move_Position(AX_SHIP_PICKER1_X, nIndex);
				}
			} else {
				AfxMessageBox(_T("Ship Picker1 Y축 Reverse 위치 확인 후 진행하세요....."));
			}
		}
	} else {
		AfxMessageBox(_T("Ship Picker 1 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship] Ship Picker1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPicker1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER1_Y_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER1_Z, 0)) {
		if (nIndex == 1) {
			if (g_objCommon.Check_Position(AX_SHIP_PICKER2_Y, 0)) {
				g_objCommon.Move_Position(AX_SHIP_PICKER1_Y, nIndex);
			} else {
				AfxMessageBox(_T("Ship Picker 2 Y Reverse 위치 확인 후 진행하세요....."));
			}
		} else {
			g_objCommon.Move_Position(AX_SHIP_PICKER1_Y, nIndex);
		}

	} else {
		AfxMessageBox(_T("Ship Picker 1 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship] Ship Picker1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPicker1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER1_Z_0;

	if (nIndex == 4 || nIndex == 5) { //Pitch Move
		if (g_objCommon.Check_Position(AX_SHIP_PICKER1_X, 0)) {
			if (nIndex == 4)
				g_objCommon.Move_Position(AX_SHIP_PICKER1_Z, 0);
			else {
				EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
				MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
				double dMove = pMoveData->dShipPicker1Z[0] + pEquipData->dPitchReverse;
				g_objAJinAXL.Move_Absolute(AX_SHIP_PICKER1_Z, dMove);
			}
		} else
			AfxMessageBox(_T("Ship Picker1 X Axis Position Error...."));
	} else
		g_objCommon.Move_Position(AX_SHIP_PICKER1_Z, nIndex);

	m_strLog.Format("[Manual Ship] Ship Picker1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPicker1RClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER1_R_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER1_Z, 0)) {
		g_objCommon.Move_Position(AX_SHIP_PICKER1_R, nIndex);
	} else {
		AfxMessageBox(_T("Ship Picker 1 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship] Ship Picker1 R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPicker2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER2_X_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER2_Z, 0)) {
		if (nIndex == 8 || nIndex == 9) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 9 ? -1 : 1);
			double dMove = pEquipData->dShipTrayPitchX * nDir;
			g_objAJinAXL.Move_Relative(AX_SHIP_PICKER2_X, dMove);

		} else {
			if (g_objCommon.Check_Position(AX_SHIP_PICKER2_Y, 0) || g_objCommon.Check_Position(AX_SHIP_PICKER2_Y, 2)) {
				if (nIndex == 3) {
					if (g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 1)) {
						g_objCommon.Move_Position(AX_SHIP_PICKER2_X, nIndex);
					} else {
						AfxMessageBox(_T("Ship Tray 1 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
					}
				} else if (nIndex == 4) {
					if (g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 1)) {
						g_objCommon.Move_Position(AX_SHIP_PICKER2_X, nIndex);
					} else {
						AfxMessageBox(_T("Ship Tray 2 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
					}
				} else {
					g_objCommon.Move_Position(AX_SHIP_PICKER2_X, nIndex);
				}
			} else {
				AfxMessageBox(_T("Ship Picker2 Y축 Reverse 위치 확인 후 진행하세요....."));
			}
		}
	} else {
		AfxMessageBox(_T("Ship Picker 2 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship] Ship Picker2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPicker2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER2_Y_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER2_Z, 0)) {
		if (nIndex == 1) {
			if (g_objCommon.Check_Position(AX_SHIP_PICKER1_Y, 0)) {
				g_objCommon.Move_Position(AX_SHIP_PICKER2_Y, nIndex);
			} else {
				AfxMessageBox(_T("Ship Picker 1 Y Reverse 위치 확인 후 진행하세요....."));
			}
		} else {
			g_objCommon.Move_Position(AX_SHIP_PICKER2_Y, nIndex);
		}
	} else {
		AfxMessageBox(_T("Ship Picker 2 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship] Ship Picker2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPicker2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER2_Z_0;

	if (nIndex == 4 || nIndex == 5) { //Pitch Move
		if (g_objCommon.Check_Position(AX_SHIP_PICKER2_X, 0)) {
			if (nIndex == 4)
				g_objCommon.Move_Position(AX_SHIP_PICKER2_Z, 0);
			else {
				EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
				MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
				double dMove = pMoveData->dShipPicker2Z[0] + pEquipData->dPitchReverse;
				g_objAJinAXL.Move_Absolute(AX_SHIP_PICKER2_Z, dMove);
			}
		} else
			AfxMessageBox(_T("Ship Picker2 X Axis Position Error...."));
	} else
		g_objCommon.Move_Position(AX_SHIP_PICKER2_Z, nIndex);

	m_strLog.Format("[Manual Ship] Ship Picker2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPicker2RClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_PICKER2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER2_R_0;

	if (g_objCommon.Check_Position(AX_SHIP_PICKER2_Z, 0)) {
		g_objCommon.Move_Position(AX_SHIP_PICKER2_R, nIndex);
	} else {
		AfxMessageBox(_T("Ship Picker 2 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Ship] Ship Picker2 R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPickerIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PICKER_IO_0;

	DY_DATA_12 *pDY12 = g_objAJinAXL.Get_pDY12();

	if (nIndex == 0)  { pDY12->oShipPicker1Vacuum1On = TRUE; pDY12->oShipPicker1Vacuum1Air = FALSE; }
	if (nIndex == 1)  { pDY12->oShipPicker1Vacuum1On = FALSE; pDY12->oShipPicker1Vacuum1Air = TRUE; }
	if (nIndex == 1)  { g_objAJinAXL.Write_Output(12); Sleep(100); }
	if (nIndex == 1)  { pDY12->oShipPicker1Vacuum1Air = FALSE; }
	if (nIndex == 2)  { pDY12->oShipPicker1Vacuum2On = TRUE; pDY12->oShipPicker1Vacuum2Air = FALSE; }
	if (nIndex == 3)  { pDY12->oShipPicker1Vacuum2On = FALSE; pDY12->oShipPicker1Vacuum2Air = TRUE; }
	if (nIndex == 3)  { g_objAJinAXL.Write_Output(12); Sleep(100); }
	if (nIndex == 3)  { pDY12->oShipPicker1Vacuum2Air = FALSE; }
	if (nIndex == 4)  { pDY12->oShipPicker1GripOpen = TRUE; pDY12->oShipPicker1GripClose = FALSE; }
	if (nIndex == 5)  { pDY12->oShipPicker1GripOpen = FALSE; pDY12->oShipPicker1GripClose = TRUE; }

	if (nIndex == 6)  { pDY12->oShipPicker2Vacuum1On = TRUE; pDY12->oShipPicker2Vacuum1Air = FALSE; }
	if (nIndex == 7)  { pDY12->oShipPicker2Vacuum1On = FALSE; pDY12->oShipPicker2Vacuum1Air = TRUE; }
	if (nIndex == 7)  { g_objAJinAXL.Write_Output(12); Sleep(100); }
	if (nIndex == 7)  { pDY12->oShipPicker2Vacuum1Air = FALSE; }
	if (nIndex == 8)  { pDY12->oShipPicker2Vacuum2On = TRUE; pDY12->oShipPicker2Vacuum2Air = FALSE; }
	if (nIndex == 9)  { pDY12->oShipPicker2Vacuum2On = FALSE; pDY12->oShipPicker2Vacuum2Air = TRUE; }
	if (nIndex == 9)  { g_objAJinAXL.Write_Output(12); Sleep(100); }
	if (nIndex == 9)  { pDY12->oShipPicker2Vacuum2Air = FALSE; }
	if (nIndex == 10) { pDY12->oShipPicker2GripOpen = TRUE; pDY12->oShipPicker2GripClose = FALSE; }
	if (nIndex == 11) { pDY12->oShipPicker2GripOpen = FALSE; pDY12->oShipPicker2GripClose = TRUE; }

	g_objAJinAXL.Write_Output(12);

	m_strLog.Format("[Manual Ship] Ship Picker IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipPortIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_PORT_IO_0;

	DY_DATA_11 *pDY11 = g_objAJinAXL.Get_pDY11();

	if (nIndex == 0) { pDY11->oShipPort1SupportIn = TRUE; pDY11->oShipPort1SupportOut = FALSE; }
	if (nIndex == 1) { pDY11->oShipPort1SupportIn = FALSE; pDY11->oShipPort1SupportOut = TRUE; }
	if (nIndex == 2) { pDY11->oShipPort2SupportIn = TRUE; pDY11->oShipPort2SupportOut = FALSE; }
	if (nIndex == 3) { pDY11->oShipPort2SupportIn = FALSE; pDY11->oShipPort2SupportOut = TRUE; }

	g_objAJinAXL.Write_Output(11);

	m_strLog.Format("[Manual Ship] Ship Port IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipTray1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_TRAY1_Y_0;

	if ((g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 0)) ||
		(g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 1))) {
			AfxMessageBox(_T("Ship Tray1, Tray2 Z Axis Position Error...."));
			return;
	}

	if ((g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 1)) ) {
		if (nIndex == 3 || nIndex == 4) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dShipTrayPitchY * nDir;
			g_objAJinAXL.Move_Relative(AX_SHIP_TRAY1_Y, dMove);
		} else {
			g_objCommon.Move_Position(AX_SHIP_TRAY1_Y, nIndex);
		}
	} else {
		AfxMessageBox(_T("Ship Tray1 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Ship] Ship Tray1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipTray1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY2_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_TRAY1_Z_0;

	if ((g_objCommon.Check_Position(AX_SHIP_TRAY1_Y, 0) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Y, 0)) ||
		(g_objCommon.Check_Position(AX_SHIP_TRAY1_Y, 1) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Y, 1)) ||
		(g_objCommon.Check_Position(AX_SHIP_TRAY1_Y, 2) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Y, 2))) {
			AfxMessageBox(_T("Ship Tray1 X, Tray2 X Axis Position Error...."));
			return;
	}

	if (nID == IDC_BTN_SHIP_TRAY1_Z_2 || nID == IDC_BTN_SHIP_TRAY1_Z_3) {
		if (g_objCommon.Check_Position(AX_SHIP_TRAY1_Y, 0) || g_objCommon.Check_Position(AX_SHIP_TRAY1_Y, 2)) {
			g_objCommon.Move_Position(AX_SHIP_TRAY1_Z, nIndex);
		} else {
			AfxMessageBox(_T("Ship Tray1 X Axis Position Error...."));
		}
	} else {
		g_objCommon.Move_Position(AX_SHIP_TRAY1_Z, nIndex);
	}

	m_strLog.Format("[Manual Ship] Ship Tray1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipTray2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_TRAY2_Y_0;

	if ((g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 0)) ||
		(g_objCommon.Check_Position(AX_SHIP_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 1))) {
			AfxMessageBox(_T("Ship Tray1, Tray2 Z Axis Position Error...."));
			return;
	}

	if ((g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_SHIP_TRAY2_Z, 1)) ) {
		if (nIndex == 3 || nIndex == 4) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dShipTrayPitchY * nDir;
			g_objAJinAXL.Move_Relative(AX_SHIP_TRAY2_Y, dMove);
		} else {
			g_objCommon.Move_Position(AX_SHIP_TRAY2_Y, nIndex);
		}
	} else {
		AfxMessageBox(_T("Ship Tray2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Ship] Ship Tray2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipTray2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_SHIP_TRAY2_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_TRAY2_Z_0;

	if ((g_objCommon.Check_Position(AX_SHIP_TRAY1_Y, 0) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Y, 0)) ||
		(g_objCommon.Check_Position(AX_SHIP_TRAY1_Y, 1) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Y, 1)) ||
		(g_objCommon.Check_Position(AX_SHIP_TRAY1_Y, 2) && g_objCommon.Check_Position(AX_SHIP_TRAY2_Y, 2))) {
			AfxMessageBox(_T("Ship Tray1 X, Tray2 X Axis Position Error...."));
			return;
	}

	if (nID == IDC_BTN_SHIP_TRAY2_Z_2 || nID == IDC_BTN_SHIP_TRAY2_Z_3) {
		if (g_objCommon.Check_Position(AX_SHIP_TRAY2_Y, 0) || g_objCommon.Check_Position(AX_SHIP_TRAY2_Y, 2)) {
			g_objCommon.Move_Position(AX_SHIP_TRAY2_Z, nIndex);
		} else {
			AfxMessageBox(_T("Ship Tray2 X Axis Position Error...."));
		}
	} else {
		g_objCommon.Move_Position(AX_SHIP_TRAY2_Z, nIndex);
	}

	m_strLog.Format("[Manual Ship] Ship Tray2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualShipDlg::OnBtnShipTrayIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SHIP_TRAY_IO_0;

	DY_DATA_12 *pDY12 = g_objAJinAXL.Get_pDY12();

	if (nIndex == 0) { pDY12->oShipTray1MasterIn = TRUE; pDY12->oShipTray1MasterOut = FALSE; }
	if (nIndex == 1) { pDY12->oShipTray1MasterIn = FALSE; pDY12->oShipTray1MasterOut = TRUE; }
	if (nIndex == 2) { pDY12->oShipTray1SlaveIn = TRUE; pDY12->oShipTray1SlaveOut = FALSE; }
	if (nIndex == 3) { pDY12->oShipTray1SlaveIn = FALSE; pDY12->oShipTray1SlaveOut = TRUE; }
	if (nIndex == 4) { pDY12->oShipTray2MasterIn = TRUE; pDY12->oShipTray2MasterOut = FALSE; }
	if (nIndex == 5) { pDY12->oShipTray2MasterIn = FALSE; pDY12->oShipTray2MasterOut = TRUE; }
	if (nIndex == 6) { pDY12->oShipTray2SlaveIn = TRUE; pDY12->oShipTray2SlaveOut = FALSE; }
	if (nIndex == 7) { pDY12->oShipTray2SlaveIn = FALSE; pDY12->oShipTray2SlaveOut = TRUE; }

	g_objAJinAXL.Write_Output(12);

	m_strLog.Format("[Manual Ship] Ship Tray IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
