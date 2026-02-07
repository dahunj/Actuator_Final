// ManualReverseDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualReverseDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"

// CManualReverseDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualReverseDlg, CDialogEx)

CManualReverseDlg::CManualReverseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualReverseDlg::IDD, pParent)
{
}

CManualReverseDlg::~CManualReverseDlg()
{
}

void CManualReverseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_REVERSE1_Z_0 + i, m_btnReverse1Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_REVERSE1_R_0 + i, m_btnReverse1R[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_REVERSE2_Z_0 + i, m_btnReverse2Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_REVERSE2_R_0 + i, m_btnReverse2R[i]);
	for (int i = 0; i < 28; i++) DDX_Control(pDX, IDC_BTN_REVERSE_IO_0 + i, m_btnReverseIo[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LED_REVERSE_IO_0 + i, m_ledReverseIo[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_DROP_TABLE_Y_0 + i, m_btnDropTableY[i]);
}

BEGIN_MESSAGE_MAP(CManualReverseDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REVERSE1_Z_0, IDC_BTN_REVERSE1_Z_4, OnBtnReverse1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REVERSE1_R_0, IDC_BTN_REVERSE1_R_1, OnBtnReverse1RClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REVERSE2_Z_0, IDC_BTN_REVERSE2_Z_4, OnBtnReverse2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REVERSE2_R_0, IDC_BTN_REVERSE2_R_1, OnBtnReverse2RClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REVERSE_IO_0, IDC_BTN_REVERSE_IO_27, OnBtnReverseIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_DROP_TABLE_Y_0, IDC_BTN_DROP_TABLE_Y_4, OnBtnDropTableYClick)
END_MESSAGE_MAP()

// CManualCapDlg 메시지 처리기입니다.

BOOL CManualReverseDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualReverseDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualReverseDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	m_strLog.Format("[Manual Cap] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualReverseDlg::Initial_Controls() 
{
	for (int i = 0; i < 4; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 4; i < 6; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 6; i < 7; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 0; i < 5; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 5; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i < 5; i++) m_btnReverse1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnReverse1R[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++) m_btnReverse2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnReverse2R[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 28; i++) m_btnReverseIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 12; i++) m_ledReverseIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 5; i++) m_btnDropTableY[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
}

void CManualReverseDlg::Display_Status()
{
	CString strPos;
	for (int i = 0; i < 5; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_REVERSE1_Z + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	DX_DATA_10 *pDX10 = g_objAJinAXL.Get_pDX10();

	m_ledReverseIo[0].Set_On(pDX10->iReverse1Vacuum1Chk);
	m_ledReverseIo[1].Set_On(pDX10->iReverse1Vacuum2Chk);
	m_ledReverseIo[2].Set_On(pDX10->iReverse1Vacuum3Chk);
	m_ledReverseIo[3].Set_On(pDX10->iReverse1Grip1Open);
	m_ledReverseIo[4].Set_On(pDX10->iReverse1Grip2Open);
	m_ledReverseIo[5].Set_On(pDX10->iReverse1Grip3Open);
	m_ledReverseIo[6].Set_On(pDX10->iReverse2Vacuum1Chk);
	m_ledReverseIo[7].Set_On(pDX10->iReverse2Vacuum2Chk);
	m_ledReverseIo[8].Set_On(pDX10->iReverse2Vacuum3Chk);
	m_ledReverseIo[9].Set_On(pDX10->iReverse2Grip1Open);
	m_ledReverseIo[10].Set_On(pDX10->iReverse2Grip2Open);
	m_ledReverseIo[11].Set_On(pDX10->iReverse2Grip3Open);
}

///////////////////////////////////////////////////////////////////////////////

void CManualReverseDlg::OnBtnReverse1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_REVERSE1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_REVERSE1_Z_0;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	if (nIndex > 1) { //Ship Down & Pitch Move
		if (g_objCommon.Check_Position(AX_REVERSE1_R, 1) && g_objAJinAXL.Get_Position(AX_SHIP_PICKER1_X) < pMoveData->dShipPicker1X[0] + 1.0) {
			if (nIndex == 3) {
				double dMove = pMoveData->dReverse1Z[2] - pEquipData->dPitchReverse;
				g_objAJinAXL.Move_Absolute(AX_REVERSE1_Z, dMove);
			} else
				g_objCommon.Move_Position(AX_REVERSE1_Z, 2);
		} else
			AfxMessageBox(_T("Reverse1 R Axis Position Error...."));
	} else
		g_objCommon.Move_Position(AX_REVERSE1_Z, nIndex);

	m_strLog.Format("[Manual Reverse] Reverse1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualReverseDlg::OnBtnReverse1RClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_REVERSE1_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_REVERSE1_R_0;

	if (g_objCommon.Check_Position(AX_REVERSE1_Z, 0)) {
		g_objCommon.Move_Position(AX_REVERSE1_R, nIndex);
	} else {
		AfxMessageBox(_T("Reverse1 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Reverse] Reverse1 R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualReverseDlg::OnBtnReverse2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_REVERSE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_REVERSE2_Z_0;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	if (nIndex > 1) { //Ship Down & Pitch Move
		if (g_objCommon.Check_Position(AX_REVERSE2_R, 1) && g_objAJinAXL.Get_Position(AX_SHIP_PICKER2_X) < pMoveData->dShipPicker2X[0] + 1.0) {
			if (nIndex == 3) {
				double dMove = pMoveData->dReverse2Z[2] - pEquipData->dPitchReverse;
				g_objAJinAXL.Move_Absolute(AX_REVERSE2_Z, dMove);
			} else
				g_objCommon.Move_Position(AX_REVERSE2_Z, 2);
		} else
			AfxMessageBox(_T("Reverse2 R Axis Position Error...."));
	} else
		g_objCommon.Move_Position(AX_REVERSE2_Z, nIndex);

	m_strLog.Format("[Manual Reverse] Reverse2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualReverseDlg::OnBtnReverse2RClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_REVERSE2_R)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_REVERSE2_R_0;

	if (g_objCommon.Check_Position(AX_REVERSE2_Z, 0)) {
		g_objCommon.Move_Position(AX_REVERSE2_R, nIndex);
	} else {
		AfxMessageBox(_T("Reverse2 Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Reverse] Reverse2 R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualReverseDlg::OnBtnReverseIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_REVERSE_IO_0;

	DY_DATA_10 *pDY10 = g_objAJinAXL.Get_pDY10();

	if (nIndex == 0)  { pDY10->oReverse1Vacuum1On = TRUE; pDY10->oReverse1Vacuum1Air = FALSE; }
	if (nIndex == 1)  { pDY10->oReverse1Vacuum1On = FALSE; pDY10->oReverse1Vacuum1Air = TRUE; }
	if (nIndex == 1)  { g_objAJinAXL.Write_Output(10); Sleep(100); }
	if (nIndex == 1)  { pDY10->oReverse1Vacuum1Air = FALSE; }

	if (nIndex == 2)  { pDY10->oReverse1Vacuum2On = TRUE; pDY10->oReverse1Vacuum2Air = FALSE; }
	if (nIndex == 3)  { pDY10->oReverse1Vacuum2On = FALSE; pDY10->oReverse1Vacuum2Air = TRUE; }
	if (nIndex == 3)  { g_objAJinAXL.Write_Output(10); Sleep(100); }
	if (nIndex == 3)  { pDY10->oReverse1Vacuum2Air = FALSE; }

	if (nIndex == 4)  { pDY10->oReverse1Vacuum3On = TRUE; pDY10->oReverse1Vacuum3Air = FALSE; }
	if (nIndex == 5)  { pDY10->oReverse1Vacuum3On = FALSE; pDY10->oReverse1Vacuum3Air = TRUE; }
	if (nIndex == 5)  { g_objAJinAXL.Write_Output(10); Sleep(100); }
	if (nIndex == 5)  { pDY10->oReverse1Vacuum3Air = FALSE; }

	if (nIndex == 6  || nIndex == 12) { pDY10->oReverse1Grip1Open = TRUE; pDY10->oReverse1Grip1Close = FALSE; }
	if (nIndex == 7  || nIndex == 13) { pDY10->oReverse1Grip1Open = FALSE; pDY10->oReverse1Grip1Close = TRUE; }
	if (nIndex == 8  || nIndex == 12) { pDY10->oReverse1Grip2Open = TRUE; pDY10->oReverse1Grip2Close = FALSE; }
	if (nIndex == 9  || nIndex == 13) { pDY10->oReverse1Grip2Open = FALSE; pDY10->oReverse1Grip2Close = TRUE; }
	if (nIndex == 10 || nIndex == 12) { pDY10->oReverse1Grip3Open = TRUE; pDY10->oReverse1Grip3Close = FALSE; }
	if (nIndex == 11 || nIndex == 13) { pDY10->oReverse1Grip3Open = FALSE; pDY10->oReverse1Grip3Close = TRUE; }

	if (nIndex == 14) { pDY10->oReverse2Vacuum1On = TRUE; pDY10->oReverse2Vacuum1Air = FALSE; }
	if (nIndex == 15) { pDY10->oReverse2Vacuum1On = FALSE; pDY10->oReverse2Vacuum1Air = TRUE; }
	if (nIndex == 15) { g_objAJinAXL.Write_Output(10); Sleep(100); }
	if (nIndex == 15) { pDY10->oReverse2Vacuum1Air = FALSE; }

	if (nIndex == 16) { pDY10->oReverse2Vacuum2On = TRUE; pDY10->oReverse2Vacuum2Air = FALSE; }
	if (nIndex == 17) { pDY10->oReverse2Vacuum2On = FALSE; pDY10->oReverse2Vacuum2Air = TRUE; }
	if (nIndex == 17) { g_objAJinAXL.Write_Output(10); Sleep(100); }
	if (nIndex == 17) { pDY10->oReverse2Vacuum2Air = FALSE; }

	if (nIndex == 18) { pDY10->oReverse2Vacuum3On = TRUE; pDY10->oReverse2Vacuum3Air = FALSE; }
	if (nIndex == 19) { pDY10->oReverse2Vacuum3On = FALSE; pDY10->oReverse2Vacuum3Air = TRUE; }
	if (nIndex == 19) { g_objAJinAXL.Write_Output(10); Sleep(100); }
	if (nIndex == 19) { pDY10->oReverse2Vacuum3Air = FALSE; }

	if (nIndex == 20 || nIndex == 26) { pDY10->oReverse2Grip1Open = TRUE; pDY10->oReverse2Grip1Close = FALSE; }
	if (nIndex == 21 || nIndex == 27) { pDY10->oReverse2Grip1Open = FALSE; pDY10->oReverse2Grip1Close = TRUE; }
	if (nIndex == 22 || nIndex == 26) { pDY10->oReverse2Grip2Open = TRUE; pDY10->oReverse2Grip2Close = FALSE; }
	if (nIndex == 23 || nIndex == 27) { pDY10->oReverse2Grip2Open = FALSE; pDY10->oReverse2Grip2Close = TRUE; }
	if (nIndex == 24 || nIndex == 26) { pDY10->oReverse2Grip3Open = TRUE; pDY10->oReverse2Grip3Close = FALSE; }
	if (nIndex == 25 || nIndex == 27) { pDY10->oReverse2Grip3Open = FALSE; pDY10->oReverse2Grip3Close = TRUE; }

	g_objAJinAXL.Write_Output(10);

	m_strLog.Format("[Manual Reverse] Reverse IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualReverseDlg::OnBtnDropTableYClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_DROP_TABLE_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_DROP_TABLE_Y_0;

	g_objCommon.Move_Position(AX_DROP_TABLE_Y, nIndex);

	m_strLog.Format("[Manual Reverse] Drop Table Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
