// ManualCapDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualCapDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

#include "CMAI2100Dlg.h"
#include "WorkDlg.h"
#include "Aligner.h"
#include "SequenceMain.h"
#include "SequenceInit.h"

// CManualCapDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualCapDlg, CDialogEx)

CManualCapDlg::CManualCapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualCapDlg::IDD, pParent)
{
}

CManualCapDlg::~CManualCapDlg()
{
}

void CManualCapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 24; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER1_Y_0 + i, m_btnCapPicker1Y[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER1_X_0 + i, m_btnCapPicker1X[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER1_Z_0 + i, m_btnCapPicker1Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER1_R_0 + i, m_btnCapPicker1R[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER2_Y_0 + i, m_btnCapPicker2Y[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER2_X_0 + i, m_btnCapPicker2X[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER2_Z_0 + i, m_btnCapPicker2Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER2_R_0 + i, m_btnCapPicker2R[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_CAP_PICK1_PITCH_0 + i, m_btnCapPick1Pitch[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_CAP_PICK2_PITCH_0 + i, m_btnCapPick2Pitch[i]);
	for (int i = 0; i < 28; i++) DDX_Control(pDX, IDC_BTN_CAP_PICKER_IO_0 + i, m_btnCapPickerIo[i]);
	for (int i = 0; i < 18; i++) DDX_Control(pDX, IDC_LED_CAP_PICKER_IO_0 + i, m_ledCapPickerIo[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_CAP_PICK1_ALIGN_0 + i, m_stcCapPick1Align[i]);
	DDX_Control(pDX, IDC_BTN_CAP_PICK1_ALIGN, m_btnCapPick1Align);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_CAP_PICK2_ALIGN_0 + i, m_stcCapPick2Align[i]);
	DDX_Control(pDX, IDC_BTN_CAP_PICK2_ALIGN, m_btnCapPick2Align);
	for (int i = 0; i < 4; i++)  DDX_Control(pDX, IDC_BTN_CAP_PORT_IO_0 + i, m_btnCapPortIo[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LED_CAP_PORT_IO_0 + i, m_ledCapPortIo[i]);
	for (int i = 0; i < 5; i++)  DDX_Control(pDX, IDC_BTN_CAP_TRAY1_X_0 + i, m_btnCapTray1X[i]);
	for (int i = 0; i < 4; i++)  DDX_Control(pDX, IDC_BTN_CAP_TRAY1_Z_0 + i, m_btnCapTray1Z[i]);
	for (int i = 0; i < 5; i++)  DDX_Control(pDX, IDC_BTN_CAP_TRAY2_X_0 + i, m_btnCapTray2X[i]);
	for (int i = 0; i < 4; i++)  DDX_Control(pDX, IDC_BTN_CAP_TRAY2_Z_0 + i, m_btnCapTray2Z[i]);
	for (int i = 0; i < 8; i++)  DDX_Control(pDX, IDC_BTN_CAP_TRAY_IO_0 + i, m_btnCapTrayIo[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LED_CAP_TRAY_IO_0 + i, m_ledCapTrayIo[i]);
	DDX_Control(pDX, IDC_STC_CAP_TRAY1_CASE, m_stcCapTray1Case);
	DDX_Control(pDX, IDC_STC_CAP_TRAY2_CASE, m_stcCapTray2Case);
	DDX_Control(pDX, IDC_CHK_CAP_TRAY1_CLEAR, m_chkCapTray1Clear);
	DDX_Control(pDX, IDC_CHK_CAP_TRAY2_CLEAR, m_chkCapTray2Clear);
}

BEGIN_MESSAGE_MAP(CManualCapDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER1_Y_0, IDC_BTN_CAP_PICKER1_Y_5, OnBtnCapPicker1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER1_X_0, IDC_BTN_CAP_PICKER1_X_2, OnBtnCapPicker1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER1_Z_0, IDC_BTN_CAP_PICKER1_Z_3, OnBtnCapPicker1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER1_R_0, IDC_BTN_CAP_PICKER1_R_1, OnBtnCapPicker1RClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER2_Y_0, IDC_BTN_CAP_PICKER2_Y_5, OnBtnCapPicker2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER2_X_0, IDC_BTN_CAP_PICKER2_X_2, OnBtnCapPicker2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER2_Z_0, IDC_BTN_CAP_PICKER2_Z_3, OnBtnCapPicker2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER2_R_0, IDC_BTN_CAP_PICKER2_R_1, OnBtnCapPicker2RClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICK1_PITCH_0, IDC_BTN_CAP_PICK1_PITCH_1, OnBtnCapPick1PitchClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICK2_PITCH_0, IDC_BTN_CAP_PICK2_PITCH_1, OnBtnCapPick2PitchClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PICKER_IO_0, IDC_BTN_CAP_PICKER_IO_27, OnBtnCapPickerIoClick)
	ON_BN_CLICKED(IDC_BTN_CAP_PICK1_ALIGN, &CManualCapDlg::OnBnClickedBtnCapPick1Align)
	ON_BN_CLICKED(IDC_BTN_CAP_PICK2_ALIGN, &CManualCapDlg::OnBnClickedBtnCapPick2Align)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_PORT_IO_0, IDC_BTN_CAP_PORT_IO_3, OnBtnCapPortIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_TRAY1_X_0, IDC_BTN_CAP_TRAY1_X_4, OnBtnCapTray1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_TRAY1_Z_0, IDC_BTN_CAP_TRAY1_Z_3, OnBtnCapTray1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_TRAY2_X_0, IDC_BTN_CAP_TRAY2_X_4, OnBtnCapTray2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_TRAY2_Z_0, IDC_BTN_CAP_TRAY2_Z_3, OnBtnCapTray2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_CAP_TRAY_IO_0, IDC_BTN_CAP_TRAY_IO_7, OnBtnCapTrayIoClick)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHK_CAP_TRAY1_CLEAR, &CManualCapDlg::OnBnClickedChkCapTray1Clear)
	ON_BN_CLICKED(IDC_CHK_CAP_TRAY2_CLEAR, &CManualCapDlg::OnBnClickedChkCapTray2Clear)
END_MESSAGE_MAP()

// CManualCapDlg 메시지 처리기입니다.

BOOL CManualCapDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_nCapTray1Case = 0;
	m_nCapTray2Case = 0;
	m_bCapTrayClearRun = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualCapDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualCapDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) { KillTimer(0); return; }

	Display_Status();

	m_strLog.Format("[Manual Cap] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);

	SetTimer(0, 100, NULL);
}

void CManualCapDlg::Initial_Controls() 
{
	for (int i = 0; i < 10; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 10; i < 12; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 12; i < 14; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 14; i < 22; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 22; i < 24; i++) m_Group[i].Init_Ctrl("Arial", 12, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 0; i < 12; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 12; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i < 6; i++) m_btnCapPicker1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnCapPicker1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnCapPicker1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnCapPicker1R[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnCapPicker2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnCapPicker2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnCapPicker2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnCapPicker2R[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnCapPick1Pitch[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnCapPick2Pitch[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 28; i++) m_btnCapPickerIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 18; i++) m_ledCapPickerIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 3; i++) m_stcCapPick1Align[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
	m_btnCapPick1Align.Init_Ctrl("Arial", 11, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_stcCapPick2Align[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
	m_btnCapPick2Align.Init_Ctrl("Arial", 11, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnCapPortIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 12; i++) m_ledCapPortIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 5; i++) m_btnCapTray1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnCapTray1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++) m_btnCapTray2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnCapTray2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnCapTrayIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 12; i++) m_ledCapTrayIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	m_stcCapTray1Case.Init_Ctrl("Arial", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_stcCapTray2Case.Init_Ctrl("Arial", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
	m_chkCapTray1Clear.Init_Ctrl("Arial", 12, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	m_chkCapTray2Clear.Init_Ctrl("Arial", 12, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

void CManualCapDlg::Display_Status()
{
	CString strPos;
	for (int i = 0; i < 8; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_CAP_PICKER1_Y + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	for (int i = 0; i < 4; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_CAP_TRAY1_X + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i + 8].SetWindowText(strPos);
	}

	DX_DATA_09 *pDX09 = g_objAJinAXL.Get_pDX09();

	m_ledCapPickerIo[0].Set_On(pDX09->iCapPicker1Vacuum1Chk);
	m_ledCapPickerIo[1].Set_On(pDX09->iCapPicker1Vacuum2Chk);
	m_ledCapPickerIo[2].Set_On(pDX09->iCapPicker1Vacuum3Chk);
	m_ledCapPickerIo[3].Set_On(pDX09->iCapPicker1Pick1Up);
	m_ledCapPickerIo[4].Set_On(pDX09->iCapPicker1Pick1Down);
	m_ledCapPickerIo[5].Set_On(pDX09->iCapPicker1Pick2Up);
	m_ledCapPickerIo[6].Set_On(pDX09->iCapPicker1Pick2Down);
	m_ledCapPickerIo[7].Set_On(pDX09->iCapPicker1Pick3Up);
	m_ledCapPickerIo[8].Set_On(pDX09->iCapPicker1Pick3Down);
	m_ledCapPickerIo[9].Set_On(pDX09->iCapPicker2Vacuum1Chk);
	m_ledCapPickerIo[10].Set_On(pDX09->iCapPicker2Vacuum2Chk);
	m_ledCapPickerIo[11].Set_On(pDX09->iCapPicker2Vacuum3Chk);
	m_ledCapPickerIo[12].Set_On(pDX09->iCapPicker2Pick1Up);
	m_ledCapPickerIo[13].Set_On(pDX09->iCapPicker2Pick1Down);
	m_ledCapPickerIo[14].Set_On(pDX09->iCapPicker2Pick2Up);
	m_ledCapPickerIo[15].Set_On(pDX09->iCapPicker2Pick2Down);
	m_ledCapPickerIo[16].Set_On(pDX09->iCapPicker2Pick3Up);
	m_ledCapPickerIo[17].Set_On(pDX09->iCapPicker2Pick3Down);

	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();

	m_ledCapPortIo[0].Set_On(pDX08->iCapPort1Support1In);
	m_ledCapPortIo[1].Set_On(pDX08->iCapPort1Support1Out);
	m_ledCapPortIo[2].Set_On(pDX08->iCapPort1Support2In);
	m_ledCapPortIo[3].Set_On(pDX08->iCapPort1Support2Out);
	m_ledCapPortIo[4].Set_On(pDX08->iCapPort1TrayExist);
	m_ledCapPortIo[5].Set_On(pDX08->iCapPort1FullCheck);
	m_ledCapPortIo[6].Set_On(pDX08->iCapPort2Support1In);
	m_ledCapPortIo[7].Set_On(pDX08->iCapPort2Support1Out);
	m_ledCapPortIo[8].Set_On(pDX08->iCapPort2Support2In);
	m_ledCapPortIo[9].Set_On(pDX08->iCapPort2Support2Out);
	m_ledCapPortIo[10].Set_On(pDX08->iCapPort2TrayExist);
	m_ledCapPortIo[11].Set_On(pDX08->iCapPort2FullCheck);

	m_ledCapTrayIo[0].Set_On(pDX08->iCapTray1MasterIn);
	m_ledCapTrayIo[1].Set_On(pDX08->iCapTray1MasterOut);
	m_ledCapTrayIo[2].Set_On(pDX08->iCapTray1SlaveIn);
	m_ledCapTrayIo[3].Set_On(pDX08->iCapTray1SlaveOut);
	m_ledCapTrayIo[4].Set_On(pDX08->iCapTray1TrayExist1);
	m_ledCapTrayIo[5].Set_On(pDX08->iCapTray1TrayExist2);
	m_ledCapTrayIo[6].Set_On(pDX08->iCapTray2MasterIn);
	m_ledCapTrayIo[7].Set_On(pDX08->iCapTray2MasterOut);
	m_ledCapTrayIo[8].Set_On(pDX08->iCapTray2SlaveIn);
	m_ledCapTrayIo[9].Set_On(pDX08->iCapTray2SlaveOut);
	m_ledCapTrayIo[10].Set_On(pDX08->iCapTray2TrayExist1);
	m_ledCapTrayIo[11].Set_On(pDX08->iCapTray2TrayExist2);
}

///////////////////////////////////////////////////////////////////////////////

void CManualCapDlg::OnBtnCapPicker1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER1_Y_0;

	if (g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 0) && g_objCommon.Get_CapPickerUp(1, 0)) {
		if (nIndex == 4 || nIndex == 5) { //Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dPitchCapPicker * nDir;
			g_objAJinAXL.Move_Relative(AX_CAP_PICKER1_Y, dMove);
		} else if (nIndex == 0) {
			if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1)) {
				g_objCommon.Move_Position(AX_CAP_PICKER1_Y, nIndex);
			} else {
				AfxMessageBox(_T("Cap Tray 1 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
			}
		} else if (nIndex == 1) {
			if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1)) {
				g_objCommon.Move_Position(AX_CAP_PICKER1_Y, nIndex);
			} else {
				AfxMessageBox(_T("Cap Tray 2 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
			}
		} else {
			g_objCommon.Move_Position(AX_CAP_PICKER1_Y, nIndex);
		}
	} else {
		AfxMessageBox(_T("Cap Picker1 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Picker1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPicker1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER1_X_0;

	if (g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 0) && g_objCommon.Get_CapPickerUp(1, 0)) {
		g_objCommon.Move_Position(AX_CAP_PICKER1_X, nIndex);
	} else {
		AfxMessageBox(_T("Cap Picker1 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Picker1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPicker1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER1_Z_0;

	g_objCommon.Move_Position(AX_CAP_PICKER1_Z, nIndex);

	m_strLog.Format("[Manual Cap] Cap Picker1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPicker1RClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER1_R_0;

	if (g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 0) && g_objCommon.Get_CapPickerUp(1, 0)) {
		g_objCommon.Move_Position(AX_CAP_PICKER1_R, nIndex);
	} else {
		AfxMessageBox(_T("Cap Picker1 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Picker1 R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPicker2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER2_Y_0;

	if (g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 0) && g_objCommon.Get_CapPickerUp(2, 0)) {
		if (nIndex == 4 || nIndex == 5) { //Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dPitchCapPicker * nDir;
			g_objAJinAXL.Move_Relative(AX_CAP_PICKER2_Y, dMove);
		} else if (nIndex == 0) {
			if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1)) {
				g_objCommon.Move_Position(AX_CAP_PICKER2_Y, nIndex);
			} else {
				AfxMessageBox(_T("Cap Tray 1 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
			}
		} else if (nIndex == 1) {
			if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1)) {
				g_objCommon.Move_Position(AX_CAP_PICKER2_Y, nIndex);
			} else {
				AfxMessageBox(_T("Cap Tray 2 Z축 Moving Up 또는 Moving Down 위치 확인 후 진행하세요....."));
			}
		} else {
			g_objCommon.Move_Position(AX_CAP_PICKER2_Y, nIndex);
		}
	} else {
		AfxMessageBox(_T("Cap Picker2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Picker2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPicker2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER2_X_0;

	if (g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 0) && g_objCommon.Get_CapPickerUp(2, 0)) {
		g_objCommon.Move_Position(AX_CAP_PICKER2_X, nIndex);
	} else {
		AfxMessageBox(_T("Cap Picker2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Picker2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPicker2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER2_Z_0;

	g_objCommon.Move_Position(AX_CAP_PICKER2_Z, nIndex);

	m_strLog.Format("[Manual Cap] Cap Picker2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPicker2RClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER2_R_0;

	if (g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 0) && g_objCommon.Get_CapPickerUp(2, 0)) {
		g_objCommon.Move_Position(AX_CAP_PICKER2_R, nIndex);
	} else {
		AfxMessageBox(_T("Cap Picker2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Picker2 R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPick1PitchClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	int nIndex = nID - IDC_BTN_CAP_PICK1_PITCH_0;
	int nDir = (nIndex == 0 ? -1 : 1);
	double dMove = pEquipData->dCapTrayPitchX * nDir;

	if (!g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 0) && g_objCommon.Get_CapPickerUp(1, 0)) {
		AfxMessageBox(_T("Cap Picker1 Z Axis Position Error...."));
		return;
	}

	if ((g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1)) ||
		(g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0))) {
			g_objAJinAXL.Move_Relative(AX_CAP_PICKER1_Y, dMove);
	} else {
		AfxMessageBox(_T("Cap Tray1, Tray2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Picker1 Tray Pitch (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPick2PitchClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	int nIndex = nID - IDC_BTN_CAP_PICK2_PITCH_0;
	int nDir = (nIndex == 0 ? -1 : 1);
	double dMove = pEquipData->dCapTrayPitchX * nDir;

	if (!g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 0) && g_objCommon.Get_CapPickerUp(2, 0)) {
		AfxMessageBox(_T("Cap Picker2 Z Axis Position Error...."));
		return;
	}

	if ((g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1)) ||
		(g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0))) {
			g_objAJinAXL.Move_Relative(AX_CAP_PICKER2_Y, dMove);
	} else {
		AfxMessageBox(_T("Cap Tray1, Tray2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Picker2 Tray Pitch (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPickerIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PICKER_IO_0;

	DY_DATA_09 *pDY09 = g_objAJinAXL.Get_pDY09();

	if (nIndex == 0)  { pDY09->oCapPicker1Vacuum1On = TRUE; pDY09->oCapPicker1Vacuum1Air = FALSE; }
	if (nIndex == 1)  { pDY09->oCapPicker1Vacuum1On = FALSE; pDY09->oCapPicker1Vacuum1Air = TRUE; }
	if (nIndex == 1)  { g_objAJinAXL.Write_Output(9); Sleep(100); }
	if (nIndex == 1)  { pDY09->oCapPicker1Vacuum1Air = FALSE; }

	if (nIndex == 2)  { pDY09->oCapPicker1Vacuum2On = TRUE; pDY09->oCapPicker1Vacuum2Air = FALSE; }
	if (nIndex == 3)  { pDY09->oCapPicker1Vacuum2On = FALSE; pDY09->oCapPicker1Vacuum2Air = TRUE; }
	if (nIndex == 3)  { g_objAJinAXL.Write_Output(9); Sleep(100); }
	if (nIndex == 3)  { pDY09->oCapPicker1Vacuum2Air = FALSE; }

	if (nIndex == 4)  { pDY09->oCapPicker1Vacuum3On = TRUE; pDY09->oCapPicker1Vacuum3Air = FALSE; }
	if (nIndex == 5)  { pDY09->oCapPicker1Vacuum3On = FALSE; pDY09->oCapPicker1Vacuum3Air = TRUE; }
	if (nIndex == 5)  { g_objAJinAXL.Write_Output(9); Sleep(100); }
	if (nIndex == 5)  { pDY09->oCapPicker1Vacuum3Air = FALSE; }

	if (nIndex == 6  || nIndex == 12) { pDY09->oCapPicker1Pick1Up = TRUE; pDY09->oCapPicker1Pick1Down = FALSE; }
	if (nIndex == 7  || nIndex == 13) { pDY09->oCapPicker1Pick1Up = FALSE; pDY09->oCapPicker1Pick1Down = TRUE; }
	if (nIndex == 8  || nIndex == 12) { pDY09->oCapPicker1Pick2Up = TRUE; pDY09->oCapPicker1Pick2Down = FALSE; }
	if (nIndex == 9  || nIndex == 13) { pDY09->oCapPicker1Pick2Up = FALSE; pDY09->oCapPicker1Pick2Down = TRUE; }
	if (nIndex == 10 || nIndex == 12) { pDY09->oCapPicker1Pick3Up = TRUE; pDY09->oCapPicker1Pick3Down = FALSE; }
	if (nIndex == 11 || nIndex == 13) { pDY09->oCapPicker1Pick3Up = FALSE; pDY09->oCapPicker1Pick3Down = TRUE; }

	if (nIndex == 14) { pDY09->oCapPicker2Vacuum1On = TRUE; pDY09->oCapPicker2Vacuum1Air = FALSE; }
	if (nIndex == 15) { pDY09->oCapPicker2Vacuum1On = FALSE; pDY09->oCapPicker2Vacuum1Air = TRUE; }
	if (nIndex == 15) { g_objAJinAXL.Write_Output(9); Sleep(100); }
	if (nIndex == 15) { pDY09->oCapPicker2Vacuum1Air = FALSE; }

	if (nIndex == 16) { pDY09->oCapPicker2Vacuum2On = TRUE; pDY09->oCapPicker2Vacuum2Air = FALSE; }
	if (nIndex == 17) { pDY09->oCapPicker2Vacuum2On = FALSE; pDY09->oCapPicker2Vacuum2Air = TRUE; }
	if (nIndex == 17) { g_objAJinAXL.Write_Output(9); Sleep(100); }
	if (nIndex == 17) { pDY09->oCapPicker2Vacuum2Air = FALSE; }

	if (nIndex == 18) { pDY09->oCapPicker2Vacuum3On = TRUE; pDY09->oCapPicker2Vacuum3Air = FALSE; }
	if (nIndex == 19) { pDY09->oCapPicker2Vacuum3On = FALSE; pDY09->oCapPicker2Vacuum3Air = TRUE; }
	if (nIndex == 19) { g_objAJinAXL.Write_Output(9); Sleep(100); }
	if (nIndex == 19) { pDY09->oCapPicker2Vacuum3Air = FALSE; }

	if (nIndex == 20 || nIndex == 26) { pDY09->oCapPicker2Pick1Up = TRUE; pDY09->oCapPicker2Pick1Down = FALSE; }
	if (nIndex == 21 || nIndex == 27) { pDY09->oCapPicker2Pick1Up = FALSE; pDY09->oCapPicker2Pick1Down = TRUE; }
	if (nIndex == 22 || nIndex == 26) { pDY09->oCapPicker2Pick2Up = TRUE; pDY09->oCapPicker2Pick2Down = FALSE; }
	if (nIndex == 23 || nIndex == 27) { pDY09->oCapPicker2Pick2Up = FALSE; pDY09->oCapPicker2Pick2Down = TRUE; }
	if (nIndex == 24 || nIndex == 26) { pDY09->oCapPicker2Pick3Up = TRUE; pDY09->oCapPicker2Pick3Down = FALSE; }
	if (nIndex == 25 || nIndex == 27) { pDY09->oCapPicker2Pick3Up = FALSE; pDY09->oCapPicker2Pick3Down = TRUE; }

	g_objAJinAXL.Write_Output(9);

	m_strLog.Format("[Manual Cap] Cap Picker IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBnClickedBtnCapPick1Align()
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseAlignCap) { AfxMessageBox("장비 설정 [Align Cap]이 On 상태인지 확인하여 주십시오."); return; }

	if (g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 2)) {
		m_stcCapPick1Align[0].SetWindowText("0.000");
		m_stcCapPick1Align[1].SetWindowText("0.000");
		m_stcCapPick1Align[2].SetWindowText("0.000");

		MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
		int nSub = -1;
		if		(g_objAJinAXL.Is_MoveDone(AX_CAP_PICKER1_Y, pMoveData->dCapPicker1Y[2] - 0 * pEquipData->dPitchCapPicker)) nSub = 0;
		else if (g_objAJinAXL.Is_MoveDone(AX_CAP_PICKER1_Y, pMoveData->dCapPicker1Y[2] - 1 * pEquipData->dPitchCapPicker)) nSub = 1;
		else if (g_objAJinAXL.Is_MoveDone(AX_CAP_PICKER1_Y, pMoveData->dCapPicker1Y[2] - 2 * pEquipData->dPitchCapPicker)) nSub = 2;
		if (nSub == -1) { AfxMessageBox("Cap Picker1 Y축 Align 위치를 확인하여 주십시오."); return; }

		gData.bAlignDone[4] = FALSE;
		g_objAligner.Set_LoadComplete(ALIGNER_CP1, 1, nSub+1, "AC1");

		DWORD dwStart = GetTickCount();
		while (!gData.bAlignDone[4]) {
			if (GetTickCount() - dwStart > 2000) { AfxMessageBox("얼라인 비전 프로그램 타임아웃(2초) 입니다."); return; }
			theApp.DoEvents();
		}

		CString strData;
		strData.Format("%0.3lf", gData.dAlignX[4]); m_stcCapPick1Align[0].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignY[4]); m_stcCapPick1Align[1].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignR[4]); m_stcCapPick1Align[2].SetWindowText(strData);

		if (!g_objSequenceMain.Get_IsAutoRun()) {
			double dPickY = pMoveData->dCapPicker1Y[3] + gData.dAlignY[4] - nSub * pEquipData->dPitchCapPicker;
			double dPickX = pMoveData->dCapPicker1X[2] + gData.dAlignX[4];
			double dPickR = pMoveData->dCapPicker1R[1] + gData.dAlignR[4];

			g_objCommon.Move_Position(AX_CAP_PICKER1_Z, 0);		// Ready Up Pos
			g_objAJinAXL.Move_Absolute(AX_CAP_PICKER1_Y, dPickY);	// Stage Pos
			g_objAJinAXL.Move_Absolute(AX_CAP_PICKER1_X, dPickX);	// Stage Pos
			g_objAJinAXL.Move_Absolute(AX_CAP_PICKER1_R, dPickR);	// Stage Pos
		}

	} else {
		AfxMessageBox("Cap Picker 1 Z축이 Align Down 위치인지 확인하여 주십시오.");
	}

	m_strLog.Format("[Manual Cap] Cap Picker1 Align Move Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBnClickedBtnCapPick2Align()
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseAlignCap) { AfxMessageBox("장비 설정 [Align Cap]이 On 상태인지 확인하여 주십시오."); return; }

	if (g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 2)) {
		m_stcCapPick2Align[0].SetWindowText("0.000");
		m_stcCapPick2Align[1].SetWindowText("0.000");
		m_stcCapPick2Align[2].SetWindowText("0.000");

		MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
		int nSub = -1;
		if		(g_objAJinAXL.Is_MoveDone(AX_CAP_PICKER2_Y, pMoveData->dCapPicker2Y[2] - 0 * pEquipData->dPitchCapPicker)) nSub = 0;
		else if (g_objAJinAXL.Is_MoveDone(AX_CAP_PICKER2_Y, pMoveData->dCapPicker2Y[2] - 1 * pEquipData->dPitchCapPicker)) nSub = 1;
		else if (g_objAJinAXL.Is_MoveDone(AX_CAP_PICKER2_Y, pMoveData->dCapPicker2Y[2] - 2 * pEquipData->dPitchCapPicker)) nSub = 2;
		if (nSub == -1) { AfxMessageBox("Cap Picker2 Y축 Align 위치를 확인하여 주십시오."); return; }

		gData.bAlignDone[5] = FALSE;
		g_objAligner.Set_LoadComplete(ALIGNER_CP2, 2, nSub+1, "AC2");

		DWORD dwStart = GetTickCount();
		while (!gData.bAlignDone[5]) {
			if (GetTickCount() - dwStart > 2000) { AfxMessageBox("얼라인 비전 프로그램 타임아웃(2초) 입니다."); return; }
			theApp.DoEvents();
		}

		CString strData;
		strData.Format("%0.3lf", gData.dAlignX[5]); m_stcCapPick2Align[0].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignY[5]); m_stcCapPick2Align[1].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignR[5]); m_stcCapPick2Align[2].SetWindowText(strData);

		if (!g_objSequenceMain.Get_IsAutoRun()) {
			double dPickY = pMoveData->dCapPicker2Y[3] + gData.dAlignY[5] - nSub * pEquipData->dPitchCapPicker;
			double dPickX = pMoveData->dCapPicker2X[2] + gData.dAlignX[5];
			double dPickR = pMoveData->dCapPicker2R[1] + gData.dAlignR[5];

			g_objCommon.Move_Position(AX_CAP_PICKER2_Z, 0);		// Ready Up Pos
			g_objAJinAXL.Move_Absolute(AX_CAP_PICKER2_Y, dPickY);	// Stage Pos
			g_objAJinAXL.Move_Absolute(AX_CAP_PICKER2_X, dPickX);	// Stage Pos
			g_objAJinAXL.Move_Absolute(AX_CAP_PICKER2_R, dPickR);	// Stage Pos
		}

	} else {
		AfxMessageBox("Cap Picker 2 Z축이 Align Down 위치인지 확인하여 주십시오.");
	}

	m_strLog.Format("[Manual Cap] Cap Picker2 Align Move Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapPortIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_PORT_IO_0;

	DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();

	if (nIndex == 0) { pDY08->oCapPort1SupportIn = TRUE; pDY08->oCapPort1SupportOut = FALSE; }
	if (nIndex == 1) { pDY08->oCapPort1SupportIn = FALSE; pDY08->oCapPort1SupportOut = TRUE; }
	if (nIndex == 2) { pDY08->oCapPort2SupportIn = TRUE; pDY08->oCapPort2SupportOut = FALSE; }
	if (nIndex == 3) { pDY08->oCapPort2SupportIn = FALSE; pDY08->oCapPort2SupportOut = TRUE; }

	g_objAJinAXL.Write_Output(8);

	m_strLog.Format("[Manual Cap] Cap Port IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapTray1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_TRAY1_X_0;

	if ((g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0)) ||
		(g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1))) {
			AfxMessageBox(_T("CAP Tray1, Tray2 Z Axis Position Error...."));
			return;
	}

	if ((g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0) || g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1)) ) {
		if (nIndex == 3 || nIndex == 4) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dCapTrayPitchY * nDir;
			g_objAJinAXL.Move_Relative(AX_CAP_TRAY1_X, dMove);
		} else {
			g_objCommon.Move_Position(AX_CAP_TRAY1_X, nIndex);
		}
	} else {
		AfxMessageBox(_T("CAP Tray1 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Tray1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapTray1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_X)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_TRAY1_Z_0;

	if ((g_objCommon.Check_Position(AX_CAP_TRAY1_X, 0) && g_objCommon.Check_Position(AX_CAP_TRAY2_X, 0)) ||
		(g_objCommon.Check_Position(AX_CAP_TRAY1_X, 1) && g_objCommon.Check_Position(AX_CAP_TRAY2_X, 1)) ||
		(g_objCommon.Check_Position(AX_CAP_TRAY1_X, 2) && g_objCommon.Check_Position(AX_CAP_TRAY2_X, 2))) {
			AfxMessageBox(_T("CAP Tray1 X, Tray2 X Axis Position Error...."));
			return;
	}

	if (nID == IDC_BTN_CAP_TRAY1_Z_2 || nID == IDC_BTN_CAP_TRAY1_Z_3) {
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_X, 0) || g_objCommon.Check_Position(AX_CAP_TRAY1_X, 2)) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_Z, nIndex);
		} else {
			AfxMessageBox(_T("CAP Tray1 X Axis Position Error...."));
		}
	} else {
		g_objCommon.Move_Position(AX_CAP_TRAY1_Z, nIndex);
	}

	m_strLog.Format("[Manual Cap] Cap Tray1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapTray2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_TRAY2_X_0;

	if ((g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0)) ||
		(g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1))) {
			AfxMessageBox(_T("CAP Tray1, Tray2 Z Axis Position Error...."));
			return;
	}

	if ((g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0) || g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1)) ) {
		if (nIndex == 3 || nIndex == 4) {	// Pitch Move
			EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
			int nDir = (nIndex == 4 ? -1 : 1);
			double dMove = pEquipData->dCapTrayPitchY * nDir;
			g_objAJinAXL.Move_Relative(AX_CAP_TRAY2_X, dMove);
		} else {
			g_objCommon.Move_Position(AX_CAP_TRAY2_X, nIndex);
		}
	} else {
		AfxMessageBox(_T("CAP Tray2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Cap] Cap Tray2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapTray2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_TRAY2_X)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_TRAY2_Z_0;

	if ((g_objCommon.Check_Position(AX_CAP_TRAY1_X, 0) && g_objCommon.Check_Position(AX_CAP_TRAY2_X, 0)) ||
		(g_objCommon.Check_Position(AX_CAP_TRAY1_X, 1) && g_objCommon.Check_Position(AX_CAP_TRAY2_X, 1)) ||
		(g_objCommon.Check_Position(AX_CAP_TRAY1_X, 2) && g_objCommon.Check_Position(AX_CAP_TRAY2_X, 2))) {
			AfxMessageBox(_T("CAP Tray1 X, Tray2 X Axis Position Error...."));
			return;
	}

	if (nID == IDC_BTN_CAP_TRAY2_Z_2 || nID == IDC_BTN_CAP_TRAY2_Z_3) {
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_X, 0) || g_objCommon.Check_Position(AX_CAP_TRAY2_X, 2)) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_Z, nIndex);
		} else {
			AfxMessageBox(_T("CAP Tray2 X Axis Position Error...."));
		}
	} else {
		g_objCommon.Move_Position(AX_CAP_TRAY2_Z, nIndex);
	}

	m_strLog.Format("[Manual Cap] Cap Tray2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualCapDlg::OnBtnCapTrayIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_CAP_TRAY_IO_0;

	DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();

	if (nIndex == 0) { pDY08->oCapTray1MasterIn = TRUE; pDY08->oCapTray1MasterOut = FALSE; }
	if (nIndex == 1) { pDY08->oCapTray1MasterIn = FALSE; pDY08->oCapTray1MasterOut = TRUE; }
	if (nIndex == 2) { pDY08->oCapTray1SlaveIn = TRUE; pDY08->oCapTray1SlaveOut = FALSE; }
	if (nIndex == 3) { pDY08->oCapTray1SlaveIn = FALSE; pDY08->oCapTray1SlaveOut = TRUE; }
	if (nIndex == 4) { pDY08->oCapTray2MasterIn = TRUE; pDY08->oCapTray2MasterOut = FALSE; }
	if (nIndex == 5) { pDY08->oCapTray2MasterIn = FALSE; pDY08->oCapTray2MasterOut = TRUE; }
	if (nIndex == 6) { pDY08->oCapTray2SlaveIn = TRUE; pDY08->oCapTray2SlaveOut = FALSE; }
	if (nIndex == 7) { pDY08->oCapTray2SlaveIn = FALSE; pDY08->oCapTray2SlaveOut = TRUE; }

	g_objAJinAXL.Write_Output(8);

	m_strLog.Format("[Manual Cap] Cap Tray IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////

void CManualCapDlg::OnBnClickedChkCapTray1Clear()
{
	if (!m_chkCapTray1Clear.GetCheck()) return;

	if (m_chkCapTray2Clear.GetCheck()) { m_chkCapTray1Clear.SetCheck(FALSE); return; }

	if (!g_objCommon.Check_MainEmgAir()) { m_chkCapTray1Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_MainDoor())   { m_chkCapTray1Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_ServoOn())    { m_chkCapTray1Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_DirveAlarm()) { m_chkCapTray1Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_EndLimit())   { m_chkCapTray1Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_HomeDone())   { m_chkCapTray1Clear.SetCheck(FALSE); return; }

	if (!g_objSequenceInit.Get_InitComplete()) { g_objCommon.Show_MsgBox(1, "Check Initial Complete."); m_chkCapTray1Clear.SetCheck(FALSE); return; }

	int nTray1Case = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_1);
	int nTray2Case = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_2);

	if (nTray1Case == 10) {
		if (nTray2Case != 20 && nTray2Case != 50) { g_objCommon.Show_MsgBox(1, "Check Cap Tray2 State (20 or 50)."); m_chkCapTray1Clear.SetCheck(FALSE); return; }
	} else if (nTray1Case == 20) {
		if (nTray2Case != 0 && nTray2Case != 10 && nTray2Case != 50) { g_objCommon.Show_MsgBox(1, "Check Cap Tray2 State (0 or 10 or 50)."); m_chkCapTray1Clear.SetCheck(FALSE); return; }
	} else {
		g_objCommon.Show_MsgBox(1, "Check Cap Tray1 State (10 or 20)."); m_chkCapTray1Clear.SetCheck(FALSE); return;
	}

	m_bCapTrayClearRun = FALSE;
	if (m_nCapTray1Case == 0) m_nCapTray1Case = 1;
}

void CManualCapDlg::OnBnClickedChkCapTray2Clear()
{
	if (!m_chkCapTray2Clear.GetCheck()) return;

	if (m_chkCapTray1Clear.GetCheck()) { m_chkCapTray2Clear.SetCheck(FALSE); return; }

	if (!g_objCommon.Check_MainEmgAir()) { m_chkCapTray2Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_MainDoor())   { m_chkCapTray2Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_ServoOn())    { m_chkCapTray2Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_DirveAlarm()) { m_chkCapTray2Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_EndLimit())   { m_chkCapTray2Clear.SetCheck(FALSE); return; }
	if (!g_objCommon.Check_HomeDone())   { m_chkCapTray2Clear.SetCheck(FALSE); return; }

	if (!g_objSequenceInit.Get_InitComplete()) { g_objCommon.Show_MsgBox(1, "Check Initial Complete."); m_chkCapTray2Clear.SetCheck(FALSE); return; }

	int nTray2Case = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_2);
	int nTray1Case = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_1);

	if (nTray2Case == 10) {
		if (nTray1Case != 20 && nTray1Case != 50) { g_objCommon.Show_MsgBox(1, "Check Cap Tray1 State (20 or 50)."); m_chkCapTray2Clear.SetCheck(FALSE); return; }
	} else if (nTray2Case == 20) {
		if (nTray1Case != 0 && nTray1Case != 10 && nTray1Case != 50) { g_objCommon.Show_MsgBox(1, "Check Cap Tray1 State (0 or 10 or 50)."); m_chkCapTray2Clear.SetCheck(FALSE); return; }
	} else {
		g_objCommon.Show_MsgBox(1, "Check Cap Tray2 State (10 or 20)."); m_chkCapTray2Clear.SetCheck(FALSE); return;
	}

	m_bCapTrayClearRun = FALSE;
	if (m_nCapTray2Case == 0) m_nCapTray2Case = 1;
}

///////////////////////////////////////////////////////////////////////////////

void CManualCapDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	if (m_chkCapTray1Clear.GetCheck() || m_chkCapTray2Clear.GetCheck()) {
		if (!m_bCapTrayClearRun) {	// First Run
			m_bCapTrayClearRun = TRUE;
			pMainDlg->Enable_ModeButton(FALSE);
		} else {					// Running
			BOOL bShowError = FALSE;
			if (!g_objCommon.Check_MainEmgAir()) bShowError = TRUE;
			if (!g_objCommon.Check_MainDoor()) bShowError = TRUE;
			if (!g_objCommon.Check_ServoOn()) bShowError = TRUE;
			if (!g_objCommon.Check_DirveAlarm()) bShowError = TRUE;
			if (!g_objCommon.Check_EndLimit()) bShowError = TRUE;
			if (!g_objCommon.Check_HomeDone()) bShowError = TRUE;

			if (bShowError) {
				if (m_chkCapTray1Clear.GetCheck()) m_chkCapTray1Clear.SetCheck(FALSE);
				if (m_chkCapTray2Clear.GetCheck()) m_chkCapTray2Clear.SetCheck(FALSE);
			} else {
				if (m_chkCapTray1Clear.GetCheck()) if (!CapTray1_Clear()) m_chkCapTray1Clear.SetCheck(FALSE);
				if (m_chkCapTray2Clear.GetCheck()) if (!CapTray2_Clear()) m_chkCapTray2Clear.SetCheck(FALSE);
			}
		}

	} else {
		if (m_bCapTrayClearRun) {	// First Stop
			m_bCapTrayClearRun = FALSE;
			pMainDlg->Enable_ModeButton(TRUE);
		}
	}

	// Run Case Display
	CString strText;
	strText.Format("%03d", m_nCapTray1Case); m_stcCapTray1Case.SetWindowText(strText);
	strText.Format("%03d", m_nCapTray2Case); m_stcCapTray2Case.SetWindowText(strText);

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

///////////////////////////////////////////////////////////////////////////////

BOOL CManualCapDlg::CapTray1_Clear()
{
	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
	DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();

	switch (m_nCapTray1Case) {
	case 0:		// Start 시 1로 진행
		return TRUE;

	case 1:		// Tray1 Job Select
		if (pDX08->iCapTray1TrayExist1 && pDX08->iCapTray1TrayExist2) {
			int nMainTray1 = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_1);
			if (nMainTray1 == 10) { m_nCapTray1Case = 2;  m_tCapTray1Loop.Set_LoopTime(5000); }
			if (nMainTray1 == 20) { m_nCapTray1Case = 11; m_tCapTray1Loop.Set_LoopTime(5000); }
		}
		break;

	// Tray1 반납 (Port1)
	case 2:		// Tray1 Z Move to Support Down Position
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_X, 0)) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_Z, 3);	// Support Down
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(10000);
		}
		break;
	case 3:		// Port1 Support Out
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 3)) {
			pDY08->oCapPort1SupportIn = FALSE; pDY08->oCapPort1SupportOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(5000);
		}
		break;
	case 4:		// Tray1 Z Move to Support Up Position
		if (!pDX08->iCapPort1Support1In && pDX08->iCapPort1Support1Out && !pDX08->iCapPort1Support2In && pDX08->iCapPort1Support2Out) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_Z, 2);	// Support Up
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(10000);
		}
		break;
	case 5:		// Tray1 Slave Out
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 2)) {
			pDY08->oCapTray1SlaveIn = FALSE; pDY08->oCapTray1SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(5000);
		}
		break;
	case 6:		// Tray1 Master Out
		if (!pDX08->iCapTray1SlaveIn && pDX08->iCapTray1SlaveOut) {
			pDY08->oCapTray1MasterIn = FALSE; pDY08->oCapTray1MasterOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(5000);
		}
		break;
	case 7:		// Port1 Support In
		if (!pDX08->iCapTray1MasterIn && pDX08->iCapTray1MasterOut) {
			pDY08->oCapPort1SupportIn = TRUE; pDY08->oCapPort1SupportOut = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(5000);
		}
		break;
	case 8:		// Tray1 Z Move to Moving Up Position
		if (pDX08->iCapPort1Support1In && !pDX08->iCapPort1Support1Out && pDX08->iCapPort1Support2In && !pDX08->iCapPort1Support2Out) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_Z, 0);	// Moving Up
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(10000);
		}
		break;
	case 9:		// Check Tray1 Z Moving Up
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0)) {
			if (!pDX08->iCapTray1TrayExist1 && !pDX08->iCapTray1TrayExist2) {
				g_objSequenceMain.Set_MainRunCase(AUTO_CAP_TRAY_1, 0);
				m_chkCapTray1Clear.SetCheck(FALSE);
				m_nCapTray1Case = 0; m_tCapTray1Loop.Set_LoopTime(5000);
				return TRUE;
			}
		}
		break;

	// Tray1 Unloading (Port2)
	case 11:	// Tray1 Z Move to Moving Down Position
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_X, 0) || g_objCommon.Check_Position(AX_CAP_TRAY2_X, 2)) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_Z, 1);	// Moving Down Pos
			int nMainTray2 = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_2);
			if (nMainTray2 == 50) g_objCommon.Move_Position(AX_CAP_TRAY2_Z, 0);	// Moving Up Pos
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(10000);
		}
		break;
	case 12:	// Tray1 X Move to Unload Position
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1) && g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0)) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_X, 2);	// Unload Pos
			int nMainTray2 = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_2);
			if (nMainTray2 == 50) g_objCommon.Move_Position(AX_CAP_TRAY2_X, 0);	// Load Pos
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(20000);
		}
		break;
	case 13:	// Tray1 Z Move to Support Down Position
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_X, 2) && g_objCommon.Check_Position(AX_CAP_TRAY2_X, 0)) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_Z, 3);	// Support Down
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(10000);
		}
		break;
	case 14:	// Port2 Support Out
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 3)) {
			pDY08->oCapPort2SupportIn = FALSE; pDY08->oCapPort2SupportOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(5000);
		}
		break;
	case 15:	// Tray1 Z Move to Support Up Position
		if (!pDX08->iCapPort2Support1In && pDX08->iCapPort2Support1Out && !pDX08->iCapPort2Support2In && pDX08->iCapPort2Support2Out) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_Z, 2);	// Support Up
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(10000);
		}
		break;
	case 16:	// Tray1 Slave Out
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 2)) {
			pDY08->oCapTray1SlaveIn = FALSE; pDY08->oCapTray1SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(5000);
		}
		break;
	case 17:	// Tray1 Master Out
		if (!pDX08->iCapTray1SlaveIn && pDX08->iCapTray1SlaveOut) {
			pDY08->oCapTray1MasterIn = FALSE; pDY08->oCapTray1MasterOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(5000);
		}
		break;
	case 18:	// Port2 Support In
		if (!pDX08->iCapTray1MasterIn && pDX08->iCapTray1MasterOut) {
			pDY08->oCapPort2SupportIn = TRUE; pDY08->oCapPort2SupportOut = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(5000);
		}
		break;
	case 19:	// Tray1 Z Move to Moving Down Position
		if (pDX08->iCapPort2Support1In && !pDX08->iCapPort2Support1Out && pDX08->iCapPort2Support2In && !pDX08->iCapPort2Support2Out) {
			g_objCommon.Move_Position(AX_CAP_TRAY1_Z, 1);	// Moving Down
			m_nCapTray1Case++; m_tCapTray1Loop.Set_LoopTime(10000);
		}
		break;
	case 20:	// Check Tray1 Z Moving Down
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 1)) {
			if (!pDX08->iCapTray1TrayExist1 && !pDX08->iCapTray1TrayExist2) {
				g_objSequenceMain.Set_MainRunCase(AUTO_CAP_TRAY_1, 50);
				int nMainTray2 = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_2);
				if (nMainTray2 == 50) g_objSequenceMain.Set_MainRunCase(AUTO_CAP_TRAY_2, 0);
				memset(gData.InfoCapTray, 0x00, sizeof(int) * 14 * 8);
				g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 4, NULL);
				m_chkCapTray1Clear.SetCheck(FALSE);
				m_nCapTray1Case = 0; m_tCapTray1Loop.Set_LoopTime(5000);
				return TRUE;
			}
		}
		break;
	}

	// 1. (Error : 5600)
	if (m_tCapTray1Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(5600 + m_nCapTray1Case);
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
BOOL CManualCapDlg::CapTray2_Clear()
{
	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
	DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();

	switch (m_nCapTray2Case) {
	case 0:		// Start 시 1로 진행
		return TRUE;

	case 1:		// Tray2 Job Select
		if (pDX08->iCapTray2TrayExist1 && pDX08->iCapTray2TrayExist2) {
			int nMainTray2 = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_2);
			if (nMainTray2 == 10) { m_nCapTray2Case = 2;  m_tCapTray2Loop.Set_LoopTime(5000); }
			if (nMainTray2 == 20) { m_nCapTray2Case = 11; m_tCapTray2Loop.Set_LoopTime(5000); }
		}
		break;

	// Tray2 반납 (Port1)
	case 2:		// Tray2 Z Move to Support Down Position
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_X, 0)) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_Z, 3);	// Support Down
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(10000);
		}
		break;
	case 3:		// Port1 Support Out
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 3)) {
			pDY08->oCapPort1SupportIn = FALSE; pDY08->oCapPort1SupportOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(5000);
		}
		break;
	case 4:		// Tray2 Z Move to Support Up Position
		if (!pDX08->iCapPort1Support1In && pDX08->iCapPort1Support1Out && !pDX08->iCapPort1Support2In && pDX08->iCapPort1Support2Out) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_Z, 2);	// Support Up
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(10000);
		}
		break;
	case 5:		// Tray2 Slave Out
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 2)) {
			pDY08->oCapTray2SlaveIn = FALSE; pDY08->oCapTray2SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(5000);
		}
		break;
	case 6:		// Tray2 Master Out
		if (!pDX08->iCapTray2SlaveIn && pDX08->iCapTray2SlaveOut) {
			pDY08->oCapTray2MasterIn = FALSE; pDY08->oCapTray2MasterOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(5000);
		}
		break;
	case 7:		// Port1 Support In
		if (!pDX08->iCapTray2MasterIn && pDX08->iCapTray2MasterOut) {
			pDY08->oCapPort1SupportIn = TRUE; pDY08->oCapPort1SupportOut = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(5000);
		}
		break;
	case 8:		// Tray2 Z Move to Moving Up Position
		if (pDX08->iCapPort1Support1In && !pDX08->iCapPort1Support1Out && pDX08->iCapPort1Support2In && !pDX08->iCapPort1Support2Out) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_Z, 0);	// Moving Up
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(10000);
		}
		break;
	case 9:		// Check Tray2 Z Moving Up
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 0)) {
			if (!pDX08->iCapTray2TrayExist1 && !pDX08->iCapTray2TrayExist2) {
				g_objSequenceMain.Set_MainRunCase(AUTO_CAP_TRAY_2, 0);
				m_chkCapTray2Clear.SetCheck(FALSE);
				m_nCapTray2Case = 0; m_tCapTray2Loop.Set_LoopTime(5000);
				return TRUE;
			}
		}
		break;

	// Tray2 Unload (Port2)
	case 11:	// Tray2 Z Move to Moving Down Position
		if (g_objCommon.Check_Position(AX_CAP_TRAY1_X, 0) || g_objCommon.Check_Position(AX_CAP_TRAY1_X, 2)) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_Z, 1);	// Moving Down Pos
			int nMainTray1 = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_1);
			if (nMainTray1 == 50) g_objCommon.Move_Position(AX_CAP_TRAY1_Z, 0);	// Moving Up Pos
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(10000);
		}
		break;
	case 12:	// Tray2 X Move to Unload Position
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1) && g_objCommon.Check_Position(AX_CAP_TRAY1_Z, 0)) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_X, 2);	// Unload Pos
			int nMainTray1 = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_1);
			if (nMainTray1 == 50) g_objCommon.Move_Position(AX_CAP_TRAY1_X, 0);	// Load Pos
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(20000);
		}
		break;
	case 13:	// Tray2 Z Move to Support Down Position
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_X, 2) && g_objCommon.Check_Position(AX_CAP_TRAY1_X, 0)) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_Z, 3);	// Support Down
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(10000);
		}
		break;
	case 14:	// Port2 Support Out
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 3)) {
			pDY08->oCapPort2SupportIn = FALSE; pDY08->oCapPort2SupportOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(5000);
		}
		break;
	case 15:	// Tray2 Z Move to Support Up Position
		if (!pDX08->iCapPort2Support1In && pDX08->iCapPort2Support1Out && !pDX08->iCapPort2Support2In && pDX08->iCapPort2Support2Out) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_Z, 2);	// Support Up
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(10000);
		}
		break;
	case 16:	// Tray2 Slave Out
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 2)) {
			pDY08->oCapTray2SlaveIn = FALSE; pDY08->oCapTray2SlaveOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(5000);
		}
		break;
	case 17:	// Tray2 Master Out
		if (!pDX08->iCapTray2SlaveIn && pDX08->iCapTray2SlaveOut) {
			pDY08->oCapTray2MasterIn = FALSE; pDY08->oCapTray2MasterOut = TRUE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(5000);
		}
		break;
	case 18:	// Port2 Support In
		if (!pDX08->iCapTray2MasterIn && pDX08->iCapTray2MasterOut) {
			pDY08->oCapPort2SupportIn = TRUE; pDY08->oCapPort2SupportOut = FALSE;
			g_objAJinAXL.Write_Output(8);
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(5000);
		}
		break;
	case 19:	// Tray2 Z Move to Moving Down Position
		if (pDX08->iCapPort2Support1In && !pDX08->iCapPort2Support1Out && pDX08->iCapPort2Support2In && !pDX08->iCapPort2Support2Out) {
			g_objCommon.Move_Position(AX_CAP_TRAY2_Z, 1);	// Moving Down
			m_nCapTray2Case++; m_tCapTray2Loop.Set_LoopTime(10000);
		}
		break;
	case 20:	// Check Tray2 Z Moving Down
		if (g_objCommon.Check_Position(AX_CAP_TRAY2_Z, 1)) {
			if (!pDX08->iCapTray2TrayExist1 && !pDX08->iCapTray2TrayExist2) {
				g_objSequenceMain.Set_MainRunCase(AUTO_CAP_TRAY_2, 50);
				int nMainTray1 = g_objSequenceMain.Get_MainRunCase(AUTO_CAP_TRAY_1);
				if (nMainTray1 == 50) g_objSequenceMain.Set_MainRunCase(AUTO_CAP_TRAY_1, 0);
				memset(gData.InfoCapTray, 0x00, sizeof(int) * 14 * 8);
				g_dlgWork.PostMessage(UM_UPDATE_TRAY_INFO, 4, NULL);
				m_chkCapTray2Clear.SetCheck(FALSE);
				m_nCapTray2Case = 0; m_tCapTray2Loop.Set_LoopTime(5000);
				return TRUE;
			}
		}
		break;
	}

	// 2. (Error : 5700)
	if (m_tCapTray2Loop.Over_LoopTime()) {
		g_objCommon.Show_Error(5700 + m_nCapTray2Case);
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
