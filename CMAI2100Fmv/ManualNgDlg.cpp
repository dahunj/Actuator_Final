// ManualNgDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualNgDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

// CManualNgDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualNgDlg, CDialogEx)

CManualNgDlg::CManualNgDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualNgDlg::IDD, pParent)
{
}

CManualNgDlg::~CManualNgDlg()
{
}

void CManualNgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 21; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_NG_PICKER1_Y_0 + i, m_btnNgPicker1Y[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_NG_PICKER1_X_0 + i, m_btnNgPicker1X[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_NG_PICKER1_Z_0 + i, m_btnNgPicker1Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_NG_PICKER1_R_0 + i, m_btnNgPicker1R[i]);
	for (int i = 0; i < 5; i++)	DDX_Control(pDX, IDC_BTN_NG_PICKER2_Y_0 + i, m_btnNgPicker2Y[i]);
	for (int i = 0; i < 2; i++)	DDX_Control(pDX, IDC_BTN_NG_PICKER2_X_0 + i, m_btnNgPicker2X[i]);
	for (int i = 0; i < 3; i++)	DDX_Control(pDX, IDC_BTN_NG_PICKER2_Z_0 + i, m_btnNgPicker2Z[i]);
	for (int i = 0; i < 2; i++)	DDX_Control(pDX, IDC_BTN_NG_PICKER2_R_0 + i, m_btnNgPicker2R[i]);
	for (int i = 0; i < 28; i++) DDX_Control(pDX, IDC_BTN_NG_PICKER_IO_0 + i, m_btnNgPickerIo[i]);
	for (int i = 0; i < 18; i++) DDX_Control(pDX, IDC_LED_NG_PICKER_IO_0 + i, m_ledNgPickerIo[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_NG_PORT_IO_0 + i, m_btnNgPortIo[i]);
	for (int i = 0; i < 18; i++) DDX_Control(pDX, IDC_LED_NG_PORT_IO_0 + i, m_ledNgPortIo[i]);
	for (int i = 0; i < 6; i++)	DDX_Control(pDX, IDC_BTN_NG_TRAY1_X_0 + i, m_btnNgTray1X[i]);
	for (int i = 0; i < 4; i++)	DDX_Control(pDX, IDC_BTN_NG_TRAY1_Z_0 + i, m_btnNgTray1Z[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_NG_TRAY2_X_0 + i, m_btnNgTray2X[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_NG_TRAY2_Z_0 + i, m_btnNgTray2Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_NG_TRAY1_PITCH_0 + i, m_btnNgTray1Pitch[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_NG_TRAY2_PITCH_0 + i, m_btnNgTray2Pitch[i]);
	for (int i = 0; i < 8; i++)	DDX_Control(pDX, IDC_BTN_NG_TRAY_IO_0 + i, m_btnNgTrayIo[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LED_NG_TRAY_IO_0 + i, m_ledNgTrayIo[i]);
}

BEGIN_MESSAGE_MAP(CManualNgDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER1_Y_0, IDC_BTN_NG_PICKER1_Y_4, OnBtnNgPicker1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER1_X_0, IDC_BTN_NG_PICKER1_X_1, OnBtnNgPicker1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER1_Z_0, IDC_BTN_NG_PICKER1_Z_2, OnBtnNgPicker1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER1_R_0, IDC_BTN_NG_PICKER1_R_1, OnBtnNgPicker1RClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER2_Y_0, IDC_BTN_NG_PICKER2_Y_4, OnBtnNgPicker2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER2_X_0, IDC_BTN_NG_PICKER2_X_1, OnBtnNgPicker2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER2_Z_0, IDC_BTN_NG_PICKER2_Z_2, OnBtnNgPicker2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER2_R_0, IDC_BTN_NG_PICKER2_R_1, OnBtnNgPicker2RClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PICKER_IO_0, IDC_BTN_NG_PICKER_IO_27, OnBtnNgPickerIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_PORT_IO_0, IDC_BTN_NG_PORT_IO_5, OnBtnNgPortIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY1_X_0, IDC_BTN_NG_TRAY1_X_5, OnBtnNgTray1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY1_Z_0, IDC_BTN_NG_TRAY1_Z_3, OnBtnNgTray1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY2_X_0, IDC_BTN_NG_TRAY2_X_5, OnBtnNgTray2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY2_Z_0, IDC_BTN_NG_TRAY2_Z_3, OnBtnNgTray2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY1_PITCH_0, IDC_BTN_NG_TRAY1_PITCH_1, OnBtnNgTray1PitchClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY2_PITCH_0, IDC_BTN_NG_TRAY2_PITCH_1, OnBtnNgTray2PitchClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_TRAY_IO_0, IDC_BTN_NG_TRAY_IO_7, OnBtnNgTrayIoClick)
END_MESSAGE_MAP()

// CManualNgDlg 메시지 처리기입니다.

BOOL CManualNgDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualNgDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualNgDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	m_strLog.Format("[Manual NG] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::Initial_Controls() 
{
	for (int i = 0; i < 10; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 10; i < 13; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 13; i < 19; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 19; i < 21; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 0; i < 12; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 12; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i < 5; i++)  m_btnNgPicker1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++)  m_btnNgPicker1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++)  m_btnNgPicker1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++)  m_btnNgPicker1R[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++)  m_btnNgPicker2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++)  m_btnNgPicker2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++)  m_btnNgPicker2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++)  m_btnNgPicker2R[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 28; i++)  m_btnNgPickerIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 18; i++)  m_ledNgPickerIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++)  m_btnNgPortIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 18; i++) m_ledNgPortIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++)  m_btnNgTray1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++)  m_btnNgTray1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++)  m_btnNgTray2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++)  m_btnNgTray2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++)  m_btnNgTray1Pitch[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++)  m_btnNgTray2Pitch[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++)  m_btnNgTrayIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 12; i++)  m_ledNgTrayIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CManualNgDlg::Display_Status()
{
	CString strPos;
	for (int i = 0; i < 12; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_NG_TRAY1_X + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	DX_DATA_05 *pDX05 = g_objAJinAXL.Get_pDX05();
	DX_DATA_06 *pDX06 = g_objAJinAXL.Get_pDX06();
	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();

	m_ledNgPickerIo[0].Set_On(pDX07->iNgPicker1Vacuum1Chk);
	m_ledNgPickerIo[1].Set_On(pDX07->iNgPicker1Vacuum2Chk);
	m_ledNgPickerIo[2].Set_On(pDX07->iNgPicker1Vacuum3Chk);
	m_ledNgPickerIo[3].Set_On(pDX07->iNgPicker1Pick1Up);
	m_ledNgPickerIo[4].Set_On(pDX07->iNgPicker1Pick1Down);
	m_ledNgPickerIo[5].Set_On(pDX07->iNgPicker1Pick2Up);
	m_ledNgPickerIo[6].Set_On(pDX07->iNgPicker1Pick2Down);
	m_ledNgPickerIo[7].Set_On(pDX07->iNgPicker1Pick3Up);
	m_ledNgPickerIo[8].Set_On(pDX07->iNgPicker1Pick3Down);
	m_ledNgPickerIo[9].Set_On(pDX07->iNgPicker2Vacuum1Chk);
	m_ledNgPickerIo[10].Set_On(pDX07->iNgPicker2Vacuum2Chk);
	m_ledNgPickerIo[11].Set_On(pDX07->iNgPicker2Vacuum3Chk);
	m_ledNgPickerIo[12].Set_On(pDX07->iNgPicker2Pick1Up);
	m_ledNgPickerIo[13].Set_On(pDX07->iNgPicker2Pick1Down);
	m_ledNgPickerIo[14].Set_On(pDX07->iNgPicker2Pick2Up);
	m_ledNgPickerIo[15].Set_On(pDX07->iNgPicker2Pick2Down);
	m_ledNgPickerIo[16].Set_On(pDX07->iNgPicker2Pick3Up);
	m_ledNgPickerIo[17].Set_On(pDX07->iNgPicker2Pick3Down);

	m_ledNgPortIo[0].Set_On(pDX05->iNgPort1Support1In);
	m_ledNgPortIo[1].Set_On(pDX05->iNgPort1Support1Out);
	m_ledNgPortIo[2].Set_On(pDX05->iNgPort1Support2In);
	m_ledNgPortIo[3].Set_On(pDX05->iNgPort1Support2Out);
	m_ledNgPortIo[4].Set_On(pDX05->iNgPort1TrayExist);
	m_ledNgPortIo[5].Set_On(pDX05->iNgPort1FullCheck);
	m_ledNgPortIo[6].Set_On(pDX05->iNgPort2Support1In);
	m_ledNgPortIo[7].Set_On(pDX05->iNgPort2Support1Out);
	m_ledNgPortIo[8].Set_On(pDX05->iNgPort2Support2In);
	m_ledNgPortIo[9].Set_On(pDX05->iNgPort2Support2Out);
	m_ledNgPortIo[10].Set_On(pDX05->iNgPort2TrayExist);
	m_ledNgPortIo[11].Set_On(pDX05->iNgPort2FullCheck);
	m_ledNgPortIo[12].Set_On(pDX05->iNgPort3Support1In);
	m_ledNgPortIo[13].Set_On(pDX05->iNgPort3Support1Out);
	m_ledNgPortIo[14].Set_On(pDX05->iNgPort3Support2In);
	m_ledNgPortIo[15].Set_On(pDX05->iNgPort3Support2Out);
	m_ledNgPortIo[16].Set_On(pDX05->iNgPort3TrayExist);
	m_ledNgPortIo[17].Set_On(pDX05->iNgPort3FullCheck);

	m_ledNgTrayIo[0].Set_On(pDX06->iNgTray1MasterIn);
	m_ledNgTrayIo[1].Set_On(pDX06->iNgTray1MasterOut);
	m_ledNgTrayIo[2].Set_On(pDX06->iNgTray1SlaveIn);
	m_ledNgTrayIo[3].Set_On(pDX06->iNgTray1SlaveOut);
	m_ledNgTrayIo[4].Set_On(pDX06->iNgTray1TrayExist1);
	m_ledNgTrayIo[5].Set_On(pDX06->iNgTray1TrayExist2);
	m_ledNgTrayIo[6].Set_On(pDX06->iNgTray2MasterIn);
	m_ledNgTrayIo[7].Set_On(pDX06->iNgTray2MasterOut);
	m_ledNgTrayIo[8].Set_On(pDX06->iNgTray2SlaveIn);
	m_ledNgTrayIo[9].Set_On(pDX06->iNgTray2SlaveOut);
	m_ledNgTrayIo[10].Set_On(pDX06->iNgTray2TrayExist1);
	m_ledNgTrayIo[11].Set_On(pDX06->iNgTray2TrayExist2);
}

///////////////////////////////////////////////////////////////////////////////

void CManualNgDlg::OnBtnNgPicker1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER1_Y_0;

	if (g_objCommon.Check_Position(AX_NG_PICKER1_Z, 0) && g_objCommon.Get_NgPickerUp(1, 0)) {
		if (nIndex == 3 || nIndex == 4) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dCmTrayPitchY * nDir;
			g_objAJinAXL.Move_Relative(AX_NG_PICKER1_Y, dMove);

		} else if (nIndex == 0) {
			if (g_objCommon.Check_Position(AX_NG_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_NG_TRAY1_Z, 1)) {
				g_objCommon.Move_Position(AX_NG_PICKER1_Y, nIndex);
			} else {
				AfxMessageBox(_T("NG Tray 1 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
			}

		} else if (nIndex == 1) {
			if (g_objCommon.Check_Position(AX_NG_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_NG_TRAY2_Z, 1)) {
				g_objCommon.Move_Position(AX_NG_PICKER1_Y, nIndex);
			} else {
				AfxMessageBox(_T("NG Tray 2 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
			}
		} else if (nIndex == 2) {
			g_objCommon.Move_Position(AX_NG_PICKER1_Y, nIndex);
		}
	} else {
		AfxMessageBox(_T("NG Picker 1 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual NG] NG Picker1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPicker1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER1_X_0;

	if (g_objCommon.Check_Position(AX_NG_PICKER1_Z, 0) && g_objCommon.Get_NgPickerUp(1, 0)) {
		g_objCommon.Move_Position(AX_NG_PICKER1_X, nIndex);
	} else {
		AfxMessageBox(_T("NG Picker 1 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual NG] NG Picker1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPicker1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER1_Z_0;

	g_objCommon.Move_Position(AX_NG_PICKER1_Z, nIndex);

	m_strLog.Format("[Manual NG] NG Picker1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPicker1RClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER1_R_0;

	if (g_objCommon.Check_Position(AX_NG_PICKER1_Z, 0) && g_objCommon.Get_NgPickerUp(1, 0)) {
		g_objCommon.Move_Position(AX_NG_PICKER1_R, nIndex);
	} else {
		AfxMessageBox(_T("NG Picker 1 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual NG] NG Picker1 R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPicker2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER2_Y_0;

	if (g_objCommon.Check_Position(AX_NG_PICKER2_Z, 0) && g_objCommon.Get_NgPickerUp(2, 0)) {
		if (nIndex == 3 || nIndex == 4) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dCmTrayPitchY * nDir;
			g_objAJinAXL.Move_Relative(AX_NG_PICKER2_Y, dMove);

		} else if (nIndex == 0) {
			if (g_objCommon.Check_Position(AX_NG_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_NG_TRAY1_Z, 1)) {
				g_objCommon.Move_Position(AX_NG_PICKER2_Y, nIndex);
			} else {
				AfxMessageBox(_T("NG Tray 1 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
			}

		} else if (nIndex == 1) {
			if (g_objCommon.Check_Position(AX_NG_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_NG_TRAY2_Z, 1)) {
				g_objCommon.Move_Position(AX_NG_PICKER2_Y, nIndex);
			} else {
				AfxMessageBox(_T("NG Tray 2 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
			}
		} else if (nIndex == 2) {
			g_objCommon.Move_Position(AX_NG_PICKER2_Y, nIndex);
		}
	} else {
		AfxMessageBox(_T("NG Picker 2 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual NG] NG Picker2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPicker2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER2_X_0;

	if (g_objCommon.Check_Position(AX_NG_PICKER2_Z, 0) && g_objCommon.Get_NgPickerUp(2, 0)) {
		g_objCommon.Move_Position(AX_NG_PICKER2_X, nIndex);
	} else {
		AfxMessageBox(_T("NG Picker 2 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual NG] NG Picker2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPicker2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER2_Z_0;

	g_objCommon.Move_Position(AX_NG_PICKER2_Z, nIndex);

	m_strLog.Format("[Manual NG] NG Picker2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPicker2RClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER2_R_0;

	if (g_objCommon.Check_Position(AX_NG_PICKER2_Z, 0) && g_objCommon.Get_NgPickerUp(2, 0)) {
		g_objCommon.Move_Position(AX_NG_PICKER2_R, nIndex);
	} else {
		AfxMessageBox(_T("NG Picker 2 Z Ready Up 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual NG] NG Picker2 R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPickerIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PICKER_IO_0;

	DY_DATA_07 *pDY07 = g_objAJinAXL.Get_pDY07();

	if (nIndex == 0) { pDY07->oNgPicker1Vacuum1On = TRUE; pDY07->oNgPicker1Vacuum1Air = FALSE; }
	if (nIndex == 1) { pDY07->oNgPicker1Vacuum1On = FALSE; pDY07->oNgPicker1Vacuum1Air = TRUE; }
	if (nIndex == 1) { g_objAJinAXL.Write_Output(7); Sleep(100); }
	if (nIndex == 1) { pDY07->oNgPicker1Vacuum1Air = FALSE; }
	if (nIndex == 2) { pDY07->oNgPicker1Vacuum2On = TRUE; pDY07->oNgPicker1Vacuum2Air = FALSE; }
	if (nIndex == 3) { pDY07->oNgPicker1Vacuum2On = FALSE; pDY07->oNgPicker1Vacuum2Air = TRUE; }
	if (nIndex == 3) { g_objAJinAXL.Write_Output(7); Sleep(100); }
	if (nIndex == 3) { pDY07->oNgPicker1Vacuum2Air = FALSE; }
	if (nIndex == 4) { pDY07->oNgPicker1Vacuum3On = TRUE; pDY07->oNgPicker1Vacuum3Air = FALSE; }
	if (nIndex == 5) { pDY07->oNgPicker1Vacuum3On = FALSE; pDY07->oNgPicker1Vacuum3Air = TRUE; }
	if (nIndex == 5) { g_objAJinAXL.Write_Output(7); Sleep(100); }
	if (nIndex == 5) { pDY07->oNgPicker1Vacuum3Air = FALSE; }

	if (nIndex == 6  || nIndex == 12) { pDY07->oNgPicker1Pick1Up = TRUE; pDY07->oNgPicker1Pick1Down = FALSE; }
	if (nIndex == 7  || nIndex == 13) { pDY07->oNgPicker1Pick1Up = FALSE; pDY07->oNgPicker1Pick1Down = TRUE; }
	if (nIndex == 8  || nIndex == 12) { pDY07->oNgPicker1Pick2Up = TRUE; pDY07->oNgPicker1Pick2Down = FALSE; }
	if (nIndex == 9  || nIndex == 13) { pDY07->oNgPicker1Pick2Up = FALSE; pDY07->oNgPicker1Pick2Down = TRUE; }
	if (nIndex == 10 || nIndex == 12) { pDY07->oNgPicker1Pick3Up = TRUE; pDY07->oNgPicker1Pick3Down = FALSE; }
	if (nIndex == 11 || nIndex == 13) { pDY07->oNgPicker1Pick3Up = FALSE; pDY07->oNgPicker1Pick3Down = TRUE; }

	if (nIndex == 14) { pDY07->oNgPicker2Vacuum1On = TRUE; pDY07->oNgPicker2Vacuum1Air = FALSE; }
	if (nIndex == 15) { pDY07->oNgPicker2Vacuum1On = FALSE; pDY07->oNgPicker2Vacuum1Air = TRUE; }
	if (nIndex == 15) { g_objAJinAXL.Write_Output(7); Sleep(100); }
	if (nIndex == 15) { pDY07->oNgPicker2Vacuum1Air = FALSE; }
	if (nIndex == 16) { pDY07->oNgPicker2Vacuum2On = TRUE; pDY07->oNgPicker2Vacuum2Air = FALSE; }
	if (nIndex == 17) { pDY07->oNgPicker2Vacuum2On = FALSE; pDY07->oNgPicker2Vacuum2Air = TRUE; }
	if (nIndex == 17) { g_objAJinAXL.Write_Output(7); Sleep(100); }
	if (nIndex == 17) { pDY07->oNgPicker2Vacuum2Air = FALSE; }
	if (nIndex == 18) { pDY07->oNgPicker2Vacuum3On = TRUE; pDY07->oNgPicker2Vacuum3Air = FALSE; }
	if (nIndex == 19) { pDY07->oNgPicker2Vacuum3On = FALSE; pDY07->oNgPicker2Vacuum3Air = TRUE; }
	if (nIndex == 19) { g_objAJinAXL.Write_Output(7); Sleep(100); }
	if (nIndex == 19) { pDY07->oNgPicker2Vacuum3Air = FALSE; }

	if (nIndex == 20 || nIndex == 26) { pDY07->oNgPicker2Pick1Up = TRUE; pDY07->oNgPicker2Pick1Down = FALSE; }
	if (nIndex == 21 || nIndex == 27) { pDY07->oNgPicker2Pick1Up = FALSE; pDY07->oNgPicker2Pick1Down = TRUE; }
	if (nIndex == 22 || nIndex == 26) { pDY07->oNgPicker2Pick2Up = TRUE; pDY07->oNgPicker2Pick2Down = FALSE; }
	if (nIndex == 23 || nIndex == 27) { pDY07->oNgPicker2Pick2Up = FALSE; pDY07->oNgPicker2Pick2Down = TRUE; }
	if (nIndex == 24 || nIndex == 26) { pDY07->oNgPicker2Pick3Up = TRUE; pDY07->oNgPicker2Pick3Down = FALSE; }
	if (nIndex == 25 || nIndex == 27) { pDY07->oNgPicker2Pick3Up = FALSE; pDY07->oNgPicker2Pick3Down = TRUE; }

	g_objAJinAXL.Write_Output(7);

	m_strLog.Format("[Manual NG] NG Picker IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgPortIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_PORT_IO_0;

	DY_DATA_05 *pDY05 = g_objAJinAXL.Get_pDY05();

	if (nIndex == 0) { pDY05->oNgPort1SupportIn = TRUE; pDY05->oNgPort1SupportOut = FALSE; }
	if (nIndex == 1) { pDY05->oNgPort1SupportIn = FALSE; pDY05->oNgPort1SupportOut = TRUE; }
	if (nIndex == 2) { pDY05->oNgPort2SupportIn = TRUE; pDY05->oNgPort2SupportOut = FALSE; }
	if (nIndex == 3) { pDY05->oNgPort2SupportIn = FALSE; pDY05->oNgPort2SupportOut = TRUE; }
	if (nIndex == 4) { pDY05->oNgPort3SupportIn = TRUE; pDY05->oNgPort3SupportOut = FALSE; }
	if (nIndex == 5) { pDY05->oNgPort3SupportIn = FALSE; pDY05->oNgPort3SupportOut = TRUE; }

	g_objAJinAXL.Write_Output(5);

	m_strLog.Format("[Manual NG] NG Port IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgTray1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_TRAY1_X_0;

	if ((!g_objCommon.Check_Position(AX_NG_TRAY1_X, 3) && !g_objCommon.Check_Position(AX_NG_TRAY2_X, 3)) &&
		((g_objCommon.Check_Position(AX_NG_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_NG_TRAY2_Z, 0)) ||
		(g_objCommon.Check_Position(AX_NG_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_NG_TRAY2_Z, 1)))) {
		AfxMessageBox(_T("NG Tray1, Tray2 Z Axis Position Error...."));
		return;
	}

	if ((g_objCommon.Check_Position(AX_NG_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_NG_TRAY1_Z, 1)) ) {
		if (nIndex == 4 || nIndex == 5) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dCmTrayPitchX * nDir;
			g_objAJinAXL.Move_Relative(AX_NG_TRAY1_X, dMove);
		} else {
			g_objCommon.Move_Position(AX_NG_TRAY1_X, nIndex);
		}
	} else {
		AfxMessageBox(_T("NG Tray1 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual NG] NG Tray1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgTray1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_X)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_TRAY1_Z_0;

	if ((g_objCommon.Check_Position(AX_NG_TRAY1_X, 0) && g_objCommon.Check_Position(AX_NG_TRAY2_X, 0)) ||
		(g_objCommon.Check_Position(AX_NG_TRAY1_X, 1) && g_objCommon.Check_Position(AX_NG_TRAY2_X, 1))) {
		AfxMessageBox(_T("NG Tray1 X, Tray2 X Axis Position Error...."));
		return;
	}

	if (nIndex == 2 || nIndex == 3) {
		if (g_objCommon.Check_Position(AX_NG_TRAY1_X, 0) || g_objCommon.Check_Position(AX_NG_TRAY1_X, 2)) {
			g_objCommon.Move_Position(AX_NG_TRAY1_Z, nIndex);
		} else {
			AfxMessageBox(_T("NG Tray1 X Axis Position Error...."));
		}
	} else {
		g_objCommon.Move_Position(AX_NG_TRAY1_Z, nIndex);
	}

	m_strLog.Format("[Manual NG] NG Tray1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgTray2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_TRAY2_X_0;

	if ((!g_objCommon.Check_Position(AX_NG_TRAY1_X, 3) && !g_objCommon.Check_Position(AX_NG_TRAY2_X, 3)) &&
		((g_objCommon.Check_Position(AX_NG_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_NG_TRAY2_Z, 0)) ||
		(g_objCommon.Check_Position(AX_NG_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_NG_TRAY2_Z, 1)))) {
		AfxMessageBox(_T("NG Tray1, Tray2 Z Axis Position Error...."));
		return;
	}

	if ((g_objCommon.Check_Position(AX_NG_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_NG_TRAY2_Z, 1)) ) {
		if (nIndex == 4 || nIndex == 5) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dCmTrayPitchX * nDir;
			g_objAJinAXL.Move_Relative(AX_NG_TRAY2_X, dMove);
		} else {
			g_objCommon.Move_Position(AX_NG_TRAY2_X, nIndex);
		}
	} else {
		AfxMessageBox(_T("NG Tray2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual NG] NG Tray2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgTray2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_X)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_TRAY2_Z_0;

	if ((g_objCommon.Check_Position(AX_NG_TRAY1_X, 0) && g_objCommon.Check_Position(AX_NG_TRAY2_X, 0)) ||
		(g_objCommon.Check_Position(AX_NG_TRAY1_X, 1) && g_objCommon.Check_Position(AX_NG_TRAY2_X, 1))) {
		AfxMessageBox(_T("NG Tray1 X, Tray2 X Axis Position Error...."));
		return;
	}

	if (nIndex == 2 || nIndex == 3) {
		if (g_objCommon.Check_Position(AX_NG_TRAY2_X, 0) || g_objCommon.Check_Position(AX_NG_TRAY2_X, 2)) {
			g_objCommon.Move_Position(AX_NG_TRAY2_Z, nIndex);
		} else {
			AfxMessageBox(_T("NG Tray2 X Axis Position Error...."));
		}
	} else {
		g_objCommon.Move_Position(AX_NG_TRAY2_Z, nIndex);
	}

	m_strLog.Format("[Manual NG] NG Tray2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgTray1PitchClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	int nIndex = nID - IDC_BTN_NG_TRAY1_PITCH_0;
	int nDir = (nIndex == 0 ? -1 : 1);
	double dMove = pEquipData->dPitchNgPicker * nDir;

	if ((!g_objCommon.Check_Position(AX_NG_TRAY1_X, 3) && !g_objCommon.Check_Position(AX_NG_TRAY2_X, 3)) &&
		((g_objCommon.Check_Position(AX_NG_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_NG_TRAY2_Z, 0)) ||
		(g_objCommon.Check_Position(AX_NG_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_NG_TRAY2_Z, 1)))) {
		AfxMessageBox(_T("NG Tray1, Tray2 Z Axis Position Error...."));
		return;
	}

	if ((g_objCommon.Check_Position(AX_NG_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_NG_TRAY1_Z, 1)) ) {
		g_objAJinAXL.Move_Relative(AX_NG_TRAY1_X, dMove);
	} else {
		AfxMessageBox(_T("NG Tray1 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual NG] NG Tray1 Picker Pitch (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgTray2PitchClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	int nIndex = nID - IDC_BTN_NG_TRAY2_PITCH_0;
	int nDir = (nIndex == 0 ? -1 : 1);
	double dMove = pEquipData->dPitchNgPicker * nDir;

	if ((!g_objCommon.Check_Position(AX_NG_TRAY1_X, 3) && !g_objCommon.Check_Position(AX_NG_TRAY2_X, 3)) &&
		((g_objCommon.Check_Position(AX_NG_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_NG_TRAY2_Z, 0)) ||
		(g_objCommon.Check_Position(AX_NG_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_NG_TRAY2_Z, 1)))) {
		AfxMessageBox(_T("NG Tray1, Tray2 Z Axis Position Error...."));
		return;
	}

	if ((g_objCommon.Check_Position(AX_NG_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_NG_TRAY2_Z, 1)) ) {
		g_objAJinAXL.Move_Relative(AX_NG_TRAY2_X, dMove);
	} else {
		AfxMessageBox(_T("NG Tray2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual NG] NG Tray2 Picker Pitch (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualNgDlg::OnBtnNgTrayIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_NG_TRAY_IO_0;

	DY_DATA_06 *pDY06 = g_objAJinAXL.Get_pDY06();

	if (nIndex == 0) { pDY06->oNgTray1MasterIn = TRUE; pDY06->oNgTray1MasterOut = FALSE; }
	if (nIndex == 1) { pDY06->oNgTray1MasterIn = FALSE; pDY06->oNgTray1MasterOut = TRUE; }
	if (nIndex == 2) { pDY06->oNgTray1SlaveIn = TRUE; pDY06->oNgTray1SlaveOut = FALSE; }
	if (nIndex == 3) { pDY06->oNgTray1SlaveIn = FALSE; pDY06->oNgTray1SlaveOut = TRUE; }
	if (nIndex == 4) { pDY06->oNgTray2MasterIn = TRUE; pDY06->oNgTray2MasterOut = FALSE; }
	if (nIndex == 5) { pDY06->oNgTray2MasterIn = FALSE; pDY06->oNgTray2MasterOut = TRUE; }
	if (nIndex == 6) { pDY06->oNgTray2SlaveIn = TRUE; pDY06->oNgTray2SlaveOut = FALSE; }
	if (nIndex == 7) { pDY06->oNgTray2SlaveIn = FALSE; pDY06->oNgTray2SlaveOut = TRUE; }

	g_objAJinAXL.Write_Output(6);

	m_strLog.Format("[Manual NG] NG Tray IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
