// ManualTransDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualTransDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "Aligner.h"
#include "SequenceMain.h"

// CManualTransDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualTransDlg, CDialogEx)

CManualTransDlg::CManualTransDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualTransDlg::IDD, pParent)
{
}

CManualTransDlg::~CManualTransDlg()
{
}

void CManualTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 23; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_TRANS_PICKER_X_0 + i, m_btnTransPickerX[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_TRANS_PICKER_Z_0 + i, m_btnTransPickerZ[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_TRANS_PICKER_R1_0 + i, m_btnTransPickerR1[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_TRANS_PICKER_R2_0 + i, m_btnTransPickerR2[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_TRANS_PICKER_IO_0 + i, m_btnTransPickerIo[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_LED_TRANS_PICKER_IO_0 + i, m_ledTransPickerIo[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE1_X_0 + i, m_btnTransStage1X[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE1_Y_0 + i, m_btnTransStage1Y[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE2_X_0 + i, m_btnTransStage2X[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE2_Z_0 + i, m_btnTransStage2Z[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE3_X_0 + i, m_btnTransStage3X[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE3_Y_0 + i, m_btnTransStage3Y[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE4_X_0 + i, m_btnTransStage4X[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE4_Z_0 + i, m_btnTransStage4Z[i]);
	for (int i = 0; i < 24; i++) DDX_Control(pDX, IDC_BTN_TRANS_STAGE_IO_0 + i, m_btnTransStageIo[i]);
	for (int i = 0; i < 18; i++) DDX_Control(pDX, IDC_LED_TRANS_STAGE_IO_0 + i, m_ledTransStageIo[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_TRANS_STG1_ALIGN_0 + i, m_stcTransStg1Align[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_TRANS_STG2_ALIGN_0 + i, m_stcTransStg2Align[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_TRANS_STG3_ALIGN_0 + i, m_stcTransStg3Align[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_TRANS_STG4_ALIGN_0 + i, m_stcTransStg4Align[i]);
	DDX_Control(pDX, IDC_BTN_TRANS_STG1_ALIGN, m_btnTransStg1Align);
	DDX_Control(pDX, IDC_BTN_TRANS_STG2_ALIGN, m_btnTransStg2Align);
	DDX_Control(pDX, IDC_BTN_TRANS_STG3_ALIGN, m_btnTransStg3Align);
	DDX_Control(pDX, IDC_BTN_TRANS_STG4_ALIGN, m_btnTransStg4Align);
}

BEGIN_MESSAGE_MAP(CManualTransDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_PICKER_X_0, IDC_BTN_TRANS_PICKER_X_2, OnBtnTransPickerXClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_PICKER_Z_0, IDC_BTN_TRANS_PICKER_Z_3, OnBtnTransPickerZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_PICKER_R1_0, IDC_BTN_TRANS_PICKER_R1_2, OnBtnTransPickerR1Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_PICKER_R2_0, IDC_BTN_TRANS_PICKER_R2_2, OnBtnTransPickerR2Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_PICKER_IO_0, IDC_BTN_TRANS_PICKER_IO_3, OnBtnTransPickerIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE1_X_0, IDC_BTN_TRANS_STAGE1_X_7, OnBtnTransStage1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE1_Y_0, IDC_BTN_TRANS_STAGE1_Y_1, OnBtnTransStage1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE2_X_0, IDC_BTN_TRANS_STAGE2_X_7, OnBtnTransStage2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE2_Z_0, IDC_BTN_TRANS_STAGE2_Z_1, OnBtnTransStage2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE3_X_0, IDC_BTN_TRANS_STAGE3_X_7, OnBtnTransStage3XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE3_Y_0, IDC_BTN_TRANS_STAGE3_Y_1, OnBtnTransStage3YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE4_X_0, IDC_BTN_TRANS_STAGE4_X_7, OnBtnTransStage4XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE4_Z_0, IDC_BTN_TRANS_STAGE4_Z_1, OnBtnTransStage4ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRANS_STAGE_IO_0, IDC_BTN_TRANS_STAGE_IO_23, OnBtnTransStageIoClick)
	ON_BN_CLICKED(IDC_BTN_TRANS_STG1_ALIGN, &CManualTransDlg::OnBnClickedBtnTransStg1Align)
	ON_BN_CLICKED(IDC_BTN_TRANS_STG2_ALIGN, &CManualTransDlg::OnBnClickedBtnTransStg2Align)
	ON_BN_CLICKED(IDC_BTN_TRANS_STG3_ALIGN, &CManualTransDlg::OnBnClickedBtnTransStg3Align)
	ON_BN_CLICKED(IDC_BTN_TRANS_STG4_ALIGN, &CManualTransDlg::OnBnClickedBtnTransStg4Align)
END_MESSAGE_MAP()

// CManualTransDlg 메시지 처리기입니다.

BOOL CManualTransDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualTransDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualTransDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	m_strLog.Format("[Manual Trans] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 5; i < 12; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 12; i < 19; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);
	for (int i = 19; i < 23; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 0; i < 12; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 12; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i < 3; i++) m_btnTransPickerX[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnTransPickerZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnTransPickerR1[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnTransPickerR2[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnTransPickerIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_ledTransPickerIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 8; i++) m_btnTransStage1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnTransStage1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnTransStage2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnTransStage2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnTransStage3X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnTransStage3Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnTransStage4X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnTransStage4Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 24; i++) m_btnTransStageIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 18; i++) m_ledTransStageIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 3; i++) m_stcTransStg1Align[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
	m_btnTransStg1Align.Init_Ctrl("Arial", 11, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_stcTransStg2Align[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
	m_btnTransStg2Align.Init_Ctrl("Arial", 11, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_stcTransStg3Align[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
	m_btnTransStg3Align.Init_Ctrl("Arial", 11, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_stcTransStg4Align[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0xFF));
	m_btnTransStg4Align.Init_Ctrl("Arial", 11, FALSE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
}

void CManualTransDlg::Display_Status()
{
	CString strPos;
	for (int i = 0; i < 12; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	DX_DATA_04 *pDX04 = g_objAJinAXL.Get_pDX04();

	m_ledTransPickerIo[0].Set_On(pDX04->iTransPicker1VacuumChk);
	m_ledTransPickerIo[1].Set_On(pDX04->iTransPicker2VacuumChk);

	m_ledTransStageIo[0].Set_On(pDX04->iTransStage1Vacuum1Chk);
	m_ledTransStageIo[1].Set_On(pDX04->iTransStage1Vacuum2Chk);
	m_ledTransStageIo[2].Set_On(pDX04->iTransStage1Vacuum3Chk);
	m_ledTransStageIo[3].Set_On(pDX04->iTransStage2Vacuum1Chk);
	m_ledTransStageIo[4].Set_On(pDX04->iTransStage2Vacuum2Chk);
	m_ledTransStageIo[5].Set_On(pDX04->iTransStage2Vacuum3Chk);
	m_ledTransStageIo[6].Set_On(pDX04->iTransStage3Vacuum1Chk);
	m_ledTransStageIo[7].Set_On(pDX04->iTransStage3Vacuum2Chk);
	m_ledTransStageIo[8].Set_On(pDX04->iTransStage3Vacuum3Chk);
	m_ledTransStageIo[9].Set_On(pDX04->iTransStage4Vacuum1Chk);
	m_ledTransStageIo[10].Set_On(pDX04->iTransStage4Vacuum2Chk);
	m_ledTransStageIo[11].Set_On(pDX04->iTransStage4Vacuum3Chk);
	m_ledTransStageIo[12].Set_On(pDX04->iTransLine1LaserHigh);
	m_ledTransStageIo[13].Set_On(pDX04->iTransLine2LaserPass);
	m_ledTransStageIo[14].Set_On(pDX04->iTransLine1LaserLow);
	m_ledTransStageIo[15].Set_On(pDX04->iTransLine2LaserHigh);
	m_ledTransStageIo[16].Set_On(pDX04->iTransLine1LaserPass);
	m_ledTransStageIo[17].Set_On(pDX04->iTransLine2LaserLow);
}

///////////////////////////////////////////////////////////////////////////////

void CManualTransDlg::OnBtnTransPickerXClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_PICKER_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_PICKER_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_PICKER_X_0;

	if (g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		g_objCommon.Move_Position(AX_TRANS_PICKER_X, nIndex);
	} else {
		AfxMessageBox(_T("Transfer Picker Z Ready Position 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Trans] Trans Picker X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransPickerZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_PICKER_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_PICKER_Z_0;

	g_objCommon.Move_Position(AX_TRANS_PICKER_Z, nIndex);

	m_strLog.Format("[Manual Trans] Trans Picker Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransPickerR1Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_PICKER_R1)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_PICKER_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_PICKER_R1_0;

	if (g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		g_objCommon.Move_Position(AX_TRANS_PICKER_R1, nIndex);
	} else {
		AfxMessageBox(_T("Transfer Picker Z Ready Position 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Trans] Trans Picker R1 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransPickerR2Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_PICKER_R2)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_PICKER_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_PICKER_R2_0;

	if (g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		g_objCommon.Move_Position(AX_TRANS_PICKER_R2, nIndex);
	} else {
		AfxMessageBox(_T("Transfer Picker Z Ready Position 위치 확인 후 진행하세요....."));
	}

	m_strLog.Format("[Manual Trans] Trans Picker R2 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransPickerIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_PICKER_IO_0;

	DY_DATA_04 *pDY04 = g_objAJinAXL.Get_pDY04();

	if (nIndex == 0) { pDY04->oTransPicker1VacuumOn = TRUE; pDY04->oTransPicker1VacuumAir = FALSE; }
	if (nIndex == 1) { pDY04->oTransPicker1VacuumOn = FALSE; pDY04->oTransPicker1VacuumAir = TRUE; }
	if (nIndex == 1) { g_objAJinAXL.Write_Output(4); Sleep(200); }
	if (nIndex == 1) { pDY04->oTransPicker1VacuumAir = FALSE; }

	if (nIndex == 2) { pDY04->oTransPicker2VacuumOn = TRUE; pDY04->oTransPicker2VacuumAir = FALSE; }
	if (nIndex == 3) { pDY04->oTransPicker2VacuumOn = FALSE; pDY04->oTransPicker2VacuumAir = TRUE; }
	if (nIndex == 3) { g_objAJinAXL.Write_Output(4); Sleep(200); }
	if (nIndex == 3) { pDY04->oTransPicker2VacuumAir = FALSE; }

	g_objAJinAXL.Write_Output(4);

	m_strLog.Format("[Manual Trans] Trans Picker IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStage1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE1_X_0;

	if (g_objCommon.Check_Position(AX_TRANS_STAGE1_Y, 1) && g_objCommon.Check_Position(AX_TRANS_STAGE2_Z, 1)) {
		AfxMessageBox(_T("Trans Stage1 Y, Stage2 Z Axis Position Error...."));
		return;
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	if (g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X) < pMoveData->dTransPickerX[1] + 1.0 || g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		if (g_objAJinAXL.Get_Position(AX_NG_PICKER2_Y) < pMoveData->dNgPicker2Y[1] + 10.0 || g_objCommon.Check_Position(AX_NG_PICKER2_Z, 0)) {
			if (g_objAJinAXL.Get_Position(AX_CAP_PICKER2_Y) < pMoveData->dCapPicker2Y[2] + 1.0 || g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 0)) {
				if (g_objCommon.Check_Position(AX_REVERSE1_Z, 0) || g_objCommon.Check_Position(AX_REVERSE1_R, 1)) {
					if (nIndex == 6 || nIndex == 7) {	// Pitch Move
						EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
						int nDir = (nIndex == 6 ? -1 : 1);
						double dMove = pEquipData->dPitchTranStage * nDir;
						g_objAJinAXL.Move_Relative(AX_TRANS_STAGE1_X, dMove);

					} else {
						g_objCommon.Move_Position(AX_TRANS_STAGE1_X, nIndex);
					}
				} else {
					AfxMessageBox(_T("Reverse1 Z Axis Position Error...."));
				}
			} else {
				AfxMessageBox(_T("Cap Picker2 Z Axis Position Error...."));
			}
		} else {
			AfxMessageBox(_T("NG Picker2 Z Axis Position Error...."));
		}
	} else {
		AfxMessageBox(_T("Transfer Picker Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Trans] Trans Stage1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStage1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE1_Y_0;

	for (int i = 0; i < 6; i++) {
		if (g_objCommon.Check_Position(AX_TRANS_STAGE1_X, i) && g_objCommon.Check_Position(AX_TRANS_STAGE2_X, i)) {
			AfxMessageBox(_T("Trans Stage1,2 X Axis Position Error...."));
			return;
		}
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	if (g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X) < pMoveData->dTransPickerX[1] + 1.0 || g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		if (g_objAJinAXL.Get_Position(AX_NG_PICKER2_Y) < pMoveData->dNgPicker2Y[1] + 10.0 || g_objCommon.Check_Position(AX_NG_PICKER2_Z, 0)) {
			if (g_objAJinAXL.Get_Position(AX_CAP_PICKER2_Y) < pMoveData->dCapPicker2Y[2] + 1.0 || g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 0)) {
				if (g_objCommon.Check_Position(AX_REVERSE1_Z, 0) || g_objCommon.Check_Position(AX_REVERSE1_R, 1)) {
					g_objCommon.Move_Position(AX_TRANS_STAGE1_Y, nIndex);
				} else {
					AfxMessageBox(_T("Reverse1 Z Axis Position Error...."));
				}
			} else {
				AfxMessageBox(_T("Cap Picker2 Z Axis Position Error...."));
			}
		} else {
			AfxMessageBox(_T("NG Picker2 Z Axis Position Error...."));
		}
	} else {
		AfxMessageBox(_T("Transfer Picker Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Trans] Trans Stage1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStage2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE1_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE2_X_0;

	if (g_objCommon.Check_Position(AX_TRANS_STAGE1_Y, 1) && g_objCommon.Check_Position(AX_TRANS_STAGE2_Z, 1)) {
		AfxMessageBox(_T("Trans Stage1 Y, Stage2 Z Axis Position Error...."));
		return;
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	if (g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X) < pMoveData->dTransPickerX[1] + 1.0 || g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		if (g_objAJinAXL.Get_Position(AX_NG_PICKER2_Y) < pMoveData->dNgPicker2Y[1] + 10.0 || g_objCommon.Check_Position(AX_NG_PICKER2_Z, 0)) {
			if (g_objAJinAXL.Get_Position(AX_CAP_PICKER2_Y) < pMoveData->dCapPicker2Y[2] + 1.0 || g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 0)) {
				if (g_objCommon.Check_Position(AX_REVERSE1_Z, 0) || g_objCommon.Check_Position(AX_REVERSE1_R, 1)) {
					if (nIndex == 6 || nIndex == 7) {	// Pitch Move
						EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
						int nDir = (nIndex == 6 ? -1 : 1);
						double dMove = pEquipData->dPitchTranStage * nDir;
						g_objAJinAXL.Move_Relative(AX_TRANS_STAGE2_X, dMove);

					} else {
						g_objCommon.Move_Position(AX_TRANS_STAGE2_X, nIndex);
					}
				} else {
					AfxMessageBox(_T("Reverse1 Z Axis Position Error...."));
				}
			} else {
				AfxMessageBox(_T("Cap Picker2 Z Axis Position Error...."));
			}
		} else {
			AfxMessageBox(_T("NG Picker2 Z Axis Position Error...."));
		}
	} else {
		AfxMessageBox(_T("Transfer Picker Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Trans] Trans Stage2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStage2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE2_Z_0;

	for (int i = 0; i < 6; i++) {
		if (g_objCommon.Check_Position(AX_TRANS_STAGE1_X, i) && g_objCommon.Check_Position(AX_TRANS_STAGE2_X, i)) {
			AfxMessageBox(_T("Trans Stage1,2 X Axis Position Error...."));
			return;
		}
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	if (g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X) < pMoveData->dTransPickerX[1] + 1.0 || g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		if (g_objAJinAXL.Get_Position(AX_NG_PICKER2_Y) < pMoveData->dNgPicker2Y[1] + 10.0 || g_objCommon.Check_Position(AX_NG_PICKER2_Z, 0)) {
			if (g_objAJinAXL.Get_Position(AX_CAP_PICKER2_Y) < pMoveData->dCapPicker2Y[2] + 1.0 || g_objCommon.Check_Position(AX_CAP_PICKER2_Z, 0)) {
				if (g_objCommon.Check_Position(AX_REVERSE1_Z, 0) || g_objCommon.Check_Position(AX_REVERSE1_R, 1)) {
					g_objCommon.Move_Position(AX_TRANS_STAGE2_Z, nIndex);
				} else {
					AfxMessageBox(_T("Reverse1 Z Axis Position Error...."));
				}
			} else {
				AfxMessageBox(_T("Cap Picker2 Z Axis Position Error...."));
			}
		} else {
			AfxMessageBox(_T("NG Picker2 Z Axis Position Error...."));
		}
	} else {
		AfxMessageBox(_T("Transfer Picker Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Trans] Trans Stage2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStage3XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE3_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE3_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE4_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE3_X_0;

	if (g_objCommon.Check_Position(AX_TRANS_STAGE3_Y, 1) && g_objCommon.Check_Position(AX_TRANS_STAGE4_Z, 1)) {
		AfxMessageBox(_T("Trans Stage3 Y, Stage4 Z Axis Position Error...."));
		return;
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	if (g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X) < pMoveData->dTransPickerX[1] + 1.0 || g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		if (g_objAJinAXL.Get_Position(AX_NG_PICKER1_Y) < pMoveData->dNgPicker1Y[1] + 10.0 || g_objCommon.Check_Position(AX_NG_PICKER1_Z, 0)) {
			if (g_objAJinAXL.Get_Position(AX_CAP_PICKER1_Y) < pMoveData->dCapPicker1Y[2] + 1.0 || g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 0)) {
				if (g_objCommon.Check_Position(AX_REVERSE2_Z, 0) || g_objCommon.Check_Position(AX_REVERSE2_R, 1)) {
					if (nIndex == 6 || nIndex == 7) {	// Pitch Move
						EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
						int nDir = (nIndex == 6 ? -1 : 1);
						double dMove = pEquipData->dPitchTranStage * nDir;
						g_objAJinAXL.Move_Relative(AX_TRANS_STAGE3_X, dMove);

					} else {
						g_objCommon.Move_Position(AX_TRANS_STAGE3_X, nIndex);
					}
				} else {
					AfxMessageBox(_T("Reverse2 Z Axis Position Error...."));
				}
			} else {
				AfxMessageBox(_T("Cap Picker1 Z Axis Position Error...."));
			}
		} else {
			AfxMessageBox(_T("NG Picker1 Z Axis Position Error...."));
		}
	} else {
		AfxMessageBox(_T("Transfer Picker Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Trans] Trans Stage3 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStage3YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE3_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE3_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE4_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE3_Y_0;

	for (int i = 0; i < 6; i++) {
		if (g_objCommon.Check_Position(AX_TRANS_STAGE3_X, i) && g_objCommon.Check_Position(AX_TRANS_STAGE4_X, i)) {
			AfxMessageBox(_T("Trans Stage3,4 X Axis Position Error...."));
			return;
		}
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	if (g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X) < pMoveData->dTransPickerX[1] + 1.0 || g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		if (g_objAJinAXL.Get_Position(AX_NG_PICKER1_Y) < pMoveData->dNgPicker1Y[1] + 10.0 || g_objCommon.Check_Position(AX_NG_PICKER1_Z, 0)) {
			if (g_objAJinAXL.Get_Position(AX_CAP_PICKER1_Y) < pMoveData->dCapPicker1Y[2] + 1.0 || g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 0)) {
				if (g_objCommon.Check_Position(AX_REVERSE2_Z, 0) || g_objCommon.Check_Position(AX_REVERSE2_R, 1)) {
					g_objCommon.Move_Position(AX_TRANS_STAGE3_Y, nIndex);
				} else {
					AfxMessageBox(_T("Reverse2 Z Axis Position Error...."));
				}
			} else {
				AfxMessageBox(_T("Cap Picker1 Z Axis Position Error...."));
			}
		} else {
			AfxMessageBox(_T("NG Picker1 Z Axis Position Error...."));
		}
	} else {
		AfxMessageBox(_T("Transfer Picker Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Trans] Trans Stage3 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStage4XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE4_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE3_Y)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE4_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE4_X_0;

	if (g_objCommon.Check_Position(AX_TRANS_STAGE3_Y, 1) && g_objCommon.Check_Position(AX_TRANS_STAGE4_Z, 1)) {
		AfxMessageBox(_T("Trans Stage3 Y, Stage4 Z Axis Position Error...."));
		return;
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	if (g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X) < pMoveData->dTransPickerX[1] + 1.0 || g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		if (g_objAJinAXL.Get_Position(AX_NG_PICKER1_Y) < pMoveData->dNgPicker1Y[1] + 10.0 || g_objCommon.Check_Position(AX_NG_PICKER1_Z, 0)) {
			if (g_objAJinAXL.Get_Position(AX_CAP_PICKER1_Y) < pMoveData->dCapPicker1Y[2] + 1.0 || g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 0)) {
				if (g_objCommon.Check_Position(AX_REVERSE2_Z, 0) || g_objCommon.Check_Position(AX_REVERSE2_R, 1)) {
					if (nIndex == 6 || nIndex == 7) {	// Pitch Move
						EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
						int nDir = (nIndex == 6 ? -1 : 1);
						double dMove = pEquipData->dPitchTranStage * nDir;
						g_objAJinAXL.Move_Relative(AX_TRANS_STAGE4_X, dMove);

					} else {
						g_objCommon.Move_Position(AX_TRANS_STAGE4_X, nIndex);
					}
				} else {
					AfxMessageBox(_T("Reverse2 Z Axis Position Error...."));
				}
			} else {
				AfxMessageBox(_T("Cap Picker1 Z Axis Position Error...."));
			}
		} else {
			AfxMessageBox(_T("NG Picker1 Z Axis Position Error...."));
		}
	} else {
		AfxMessageBox(_T("Transfer Picker Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Trans] Trans Stage4 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStage4ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE4_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE3_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE4_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_NG_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_CAP_PICKER1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_REVERSE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE4_Z_0;

	for (int i = 0; i < 6; i++) {
		if (g_objCommon.Check_Position(AX_TRANS_STAGE3_X, i) && g_objCommon.Check_Position(AX_TRANS_STAGE4_X, i)) {
			AfxMessageBox(_T("Trans Stage3,4 X Axis Position Error...."));
			return;
		}
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	if (g_objAJinAXL.Get_Position(AX_TRANS_PICKER_X) < pMoveData->dTransPickerX[1] + 1.0 || g_objCommon.Check_Position(AX_TRANS_PICKER_Z, 0)) {
		if (g_objAJinAXL.Get_Position(AX_NG_PICKER1_Y) < pMoveData->dNgPicker1Y[1] + 10.0 || g_objCommon.Check_Position(AX_NG_PICKER1_Z, 0)) {
			if (g_objAJinAXL.Get_Position(AX_CAP_PICKER1_Y) < pMoveData->dCapPicker1Y[2] + 1.0 || g_objCommon.Check_Position(AX_CAP_PICKER1_Z, 0)) {
				if (g_objCommon.Check_Position(AX_REVERSE2_Z, 0) || g_objCommon.Check_Position(AX_REVERSE2_R, 1)) {
					g_objCommon.Move_Position(AX_TRANS_STAGE4_Z, nIndex);
				} else {
					AfxMessageBox(_T("Reverse2 Z Axis Position Error...."));
				}
			} else {
				AfxMessageBox(_T("Cap Picker1 Z Axis Position Error...."));
			}
		} else {
			AfxMessageBox(_T("NG Picker1 Z Axis Position Error...."));
		}
	} else {
		AfxMessageBox(_T("Transfer Picker Z Axis Position Error...."));
	}

	m_strLog.Format("[Manual Trans] Trans Stage4 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBtnTransStageIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TRANS_STAGE_IO_0;

	DY_DATA_04 *pDY04 = g_objAJinAXL.Get_pDY04();

	if (nIndex == 0) pDY04->oTransStage1Vacuum1On = TRUE;
	if (nIndex == 1) pDY04->oTransStage1Vacuum1On = FALSE;
	if (nIndex == 2) pDY04->oTransStage1Vacuum2On = TRUE;
	if (nIndex == 3) pDY04->oTransStage1Vacuum2On = FALSE;
	if (nIndex == 4) pDY04->oTransStage1Vacuum3On = TRUE;
	if (nIndex == 5) pDY04->oTransStage1Vacuum3On = FALSE;

	if (nIndex == 6) pDY04->oTransStage2Vacuum1On = TRUE;
	if (nIndex == 7) pDY04->oTransStage2Vacuum1On = FALSE;
	if (nIndex == 8) pDY04->oTransStage2Vacuum2On = TRUE;
	if (nIndex == 9) pDY04->oTransStage2Vacuum2On = FALSE;
	if (nIndex == 10) pDY04->oTransStage2Vacuum3On = TRUE;
	if (nIndex == 11) pDY04->oTransStage2Vacuum3On = FALSE;
	
	if (nIndex == 12) pDY04->oTransStage3Vacuum1On = TRUE;
	if (nIndex == 13) pDY04->oTransStage3Vacuum1On = FALSE;
	if (nIndex == 14) pDY04->oTransStage3Vacuum2On = TRUE;
	if (nIndex == 15) pDY04->oTransStage3Vacuum2On = FALSE;
	if (nIndex == 16) pDY04->oTransStage3Vacuum3On = TRUE;
	if (nIndex == 17) pDY04->oTransStage3Vacuum3On = FALSE;
	
	if (nIndex == 18) pDY04->oTransStage4Vacuum1On = TRUE;
	if (nIndex == 19) pDY04->oTransStage4Vacuum1On = FALSE;
	if (nIndex == 20) pDY04->oTransStage4Vacuum2On = TRUE;
	if (nIndex == 21) pDY04->oTransStage4Vacuum2On = FALSE;
	if (nIndex == 22) pDY04->oTransStage4Vacuum3On = TRUE;
	if (nIndex == 23) pDY04->oTransStage4Vacuum3On = FALSE;

	g_objAJinAXL.Write_Output(4);

	m_strLog.Format("[Manual Trans] Trans Stage IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBnClickedBtnTransStg1Align()
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE1_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE1_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseAlignModule) { AfxMessageBox("장비 설정 [Align Module]이 On 상태인지 확인하여 주십시오."); return; }

	if (g_objCommon.Check_Position(AX_TRANS_STAGE1_X, 1) && g_objCommon.Check_Position(AX_TRANS_STAGE1_Y, 1)) {
		m_stcTransStg1Align[0].SetWindowText("0.000");
		m_stcTransStg1Align[1].SetWindowText("0.000");
		m_stcTransStg1Align[2].SetWindowText("0.000");

		MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
		int nSub = -1;
		if		(g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE1_X, pMoveData->dTransStage1X[1] + 0 * pEquipData->dPitchTranStage)) nSub = 2;
		else if (g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE1_X, pMoveData->dTransStage1X[1] + 1 * pEquipData->dPitchTranStage)) nSub = 1;
		else if (g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE1_X, pMoveData->dTransStage1X[1] + 2 * pEquipData->dPitchTranStage)) nSub = 0;
		if (nSub == -1) { AfxMessageBox("Trans Stage1 X축 Align 위치를 확인하여 주십시오."); return; }

		gData.bAlignDone[2] = FALSE;
		g_objAligner.Set_LoadComplete(ALIGNER_MD1, 1, nSub+1, "AM1");

		DWORD dwStart = GetTickCount();
		while (!gData.bAlignDone[2]) {
			if (GetTickCount() - dwStart > 2000) { AfxMessageBox("얼라인 비전 프로그램 타임아웃(2초) 입니다."); return; }
			theApp.DoEvents();
		}

		CString strData;
		strData.Format("%0.3lf", gData.dAlignX[2]); m_stcTransStg1Align[0].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignY[2]); m_stcTransStg1Align[1].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignR[2]); m_stcTransStg1Align[2].SetWindowText(strData);

		if (!g_objSequenceMain.Get_IsAutoRun()) {
			double dStgX = pMoveData->dTransStage1X[2] + gData.dAlignX[2] + (2-nSub) * pEquipData->dPitchTranStage;
			g_objAJinAXL.Move_Absolute(AX_TRANS_STAGE1_X, dStgX);	// Assembly Pos
		}

	} else {
		AfxMessageBox("Transfer Stage 1 X축, Y축이 Align 위치인지 확인하여 주십시오.");
	}

	m_strLog.Format("[Manual Trans] Trans Stage1 Align Move Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBnClickedBtnTransStg2Align()
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE2_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseAlignModule) { AfxMessageBox("장비 설정 [Align Module]이 On 상태인지 확인하여 주십시오."); return; }

	if (g_objCommon.Check_Position(AX_TRANS_STAGE2_X, 1) && g_objCommon.Check_Position(AX_TRANS_STAGE2_Z, 1)) {
		m_stcTransStg2Align[0].SetWindowText("0.000");
		m_stcTransStg2Align[1].SetWindowText("0.000");
		m_stcTransStg2Align[2].SetWindowText("0.000");

		MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
		int nSub = -1;
		if		(g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE2_X, pMoveData->dTransStage2X[1] + 0 * pEquipData->dPitchTranStage)) nSub = 2;
		else if (g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE2_X, pMoveData->dTransStage2X[1] + 1 * pEquipData->dPitchTranStage)) nSub = 1;
		else if (g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE2_X, pMoveData->dTransStage2X[1] + 2 * pEquipData->dPitchTranStage)) nSub = 0;
		if (nSub == -1) { AfxMessageBox("Trans Stage2 X축 Align 위치를 확인하여 주십시오."); return; }

		gData.bAlignDone[2] = FALSE;
		g_objAligner.Set_LoadComplete(ALIGNER_MD1, 2, nSub+1, "AM1");

		DWORD dwStart = GetTickCount();
		while (!gData.bAlignDone[2]) {
			if (GetTickCount() - dwStart > 2000) { AfxMessageBox("얼라인 비전 프로그램 타임아웃(2초) 입니다."); return; }
			theApp.DoEvents();
		}

		CString strData;
		strData.Format("%0.3lf", gData.dAlignX[2]); m_stcTransStg2Align[0].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignY[2]); m_stcTransStg2Align[1].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignR[2]); m_stcTransStg2Align[2].SetWindowText(strData);

		if (!g_objSequenceMain.Get_IsAutoRun()) {
			double dStgX = pMoveData->dTransStage2X[2] + gData.dAlignX[2] + (2-nSub) * pEquipData->dPitchTranStage;
			g_objAJinAXL.Move_Absolute(AX_TRANS_STAGE2_X, dStgX);	// Assembly Pos
		}

	} else {
		AfxMessageBox("Transfer Stage 2 X축, Z축이 Align 위치인지 확인하여 주십시오.");
	}

	m_strLog.Format("[Manual Trans] Trans Stage2 Align Move Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBnClickedBtnTransStg3Align()
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE3_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE3_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseAlignModule) { AfxMessageBox("장비 설정 [Align Module]이 On 상태인지 확인하여 주십시오."); return; }

	if (g_objCommon.Check_Position(AX_TRANS_STAGE3_X, 1) && g_objCommon.Check_Position(AX_TRANS_STAGE3_Y, 1)) {
		m_stcTransStg3Align[0].SetWindowText("0.000");
		m_stcTransStg3Align[1].SetWindowText("0.000");
		m_stcTransStg3Align[2].SetWindowText("0.000");

		MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
		int nSub = -1;
		if		(g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE3_X, pMoveData->dTransStage3X[1] + 0 * pEquipData->dPitchTranStage)) nSub = 2;
		else if (g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE3_X, pMoveData->dTransStage3X[1] + 1 * pEquipData->dPitchTranStage)) nSub = 1;
		else if (g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE3_X, pMoveData->dTransStage3X[1] + 2 * pEquipData->dPitchTranStage)) nSub = 0;
		if (nSub == -1) { AfxMessageBox("Trans Stage3 X축 Align 위치를 확인하여 주십시오."); return; }

		gData.bAlignDone[3] = FALSE;
		g_objAligner.Set_LoadComplete(ALIGNER_MD2, 3, nSub+1, "AM2");

		DWORD dwStart = GetTickCount();
		while (!gData.bAlignDone[3]) {
			if (GetTickCount() - dwStart > 2000) { AfxMessageBox("얼라인 비전 프로그램 타임아웃(2초) 입니다."); return; }
			theApp.DoEvents();
		}

		CString strData;
		strData.Format("%0.3lf", gData.dAlignX[3]); m_stcTransStg3Align[0].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignY[3]); m_stcTransStg3Align[1].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignR[3]); m_stcTransStg3Align[2].SetWindowText(strData);

		if (!g_objSequenceMain.Get_IsAutoRun()) {
			double dStgX = pMoveData->dTransStage3X[2] + gData.dAlignX[3] + (2-nSub) * pEquipData->dPitchTranStage;
			g_objAJinAXL.Move_Absolute(AX_TRANS_STAGE3_X, dStgX);	// Assembly Pos
		}

	} else {
		AfxMessageBox("Transfer Stage 3 X축, Y축이 Align 위치인지 확인하여 주십시오.");
	}

	m_strLog.Format("[Manual Trans] Trans Stage3 Align Move Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualTransDlg::OnBnClickedBtnTransStg4Align()
{
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE4_X)) return;
	if (!g_objAJinAXL.Is_Home(AX_TRANS_STAGE4_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseAlignModule) { AfxMessageBox("장비 설정 [Align Module]이 On 상태인지 확인하여 주십시오."); return; }

	if (g_objCommon.Check_Position(AX_TRANS_STAGE4_X, 1) && g_objCommon.Check_Position(AX_TRANS_STAGE4_Z, 1)) {
		m_stcTransStg4Align[0].SetWindowText("0.000");
		m_stcTransStg4Align[1].SetWindowText("0.000");
		m_stcTransStg4Align[2].SetWindowText("0.000");

		MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
		int nSub = -1;
		if		(g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE4_X, pMoveData->dTransStage4X[1] + 0 * pEquipData->dPitchTranStage)) nSub = 2;
		else if (g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE4_X, pMoveData->dTransStage4X[1] + 1 * pEquipData->dPitchTranStage)) nSub = 1;
		else if (g_objAJinAXL.Is_MoveDone(AX_TRANS_STAGE4_X, pMoveData->dTransStage4X[1] + 2 * pEquipData->dPitchTranStage)) nSub = 0;
		if (nSub == -1) { AfxMessageBox("Trans Stage4 X축 Align 위치를 확인하여 주십시오."); return; }

		gData.bAlignDone[3] = FALSE;
		g_objAligner.Set_LoadComplete(ALIGNER_MD2, 4, nSub+1, "AM2");

		DWORD dwStart = GetTickCount();
		while (!gData.bAlignDone[3]) {
			if (GetTickCount() - dwStart > 2000) { AfxMessageBox("얼라인 비전 프로그램 타임아웃(2초) 입니다."); return; }
			theApp.DoEvents();
		}

		CString strData;
		strData.Format("%0.3lf", gData.dAlignX[3]); m_stcTransStg4Align[0].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignY[3]); m_stcTransStg4Align[1].SetWindowText(strData);
		strData.Format("%0.3lf", gData.dAlignR[3]); m_stcTransStg4Align[2].SetWindowText(strData);

		if (!g_objSequenceMain.Get_IsAutoRun()) {
			double dStgX = pMoveData->dTransStage4X[2] + gData.dAlignX[3] + (2-nSub) * pEquipData->dPitchTranStage;
			g_objAJinAXL.Move_Absolute(AX_TRANS_STAGE4_X, dStgX);	// Assembly Pos
		}

	} else {
		AfxMessageBox("Transfer Stage 4 X축, Z축이 Align 위치인지 확인하여 주십시오.");
	}

	m_strLog.Format("[Manual Trans] Trans Stage4 Align Move Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
