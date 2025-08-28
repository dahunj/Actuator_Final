// ManualLoadDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualLoadDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"

// CManualLoadDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualLoadDlg, CDialogEx)

CManualLoadDlg::CManualLoadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualLoadDlg::IDD, pParent)
{
}

CManualLoadDlg::~CManualLoadDlg()
{
}

void CManualLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i <18; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i <13; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i <13; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER1_X_0 + i, m_btnLoadPicker1X[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER1_Y_0 + i, m_btnLoadPicker1Y[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER1_Z_0 + i, m_btnLoadPicker1Z[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER1_P_0 + i, m_btnLoadPicker1P[i]);
	for (int i = 0; i <36; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER1_IO_0 + i, m_btnLoadPicker1IO[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER2_X_0 + i, m_btnLoadPicker2X[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER2_Y_0 + i, m_btnLoadPicker2Y[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER2_Z_0 + i, m_btnLoadPicker2Z[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER2_P_0 + i, m_btnLoadPicker2P[i]);
	for (int i = 0; i <36; i++) DDX_Control(pDX, IDC_BTN_LOAD_PICKER2_IO_0 + i, m_btnLoadPicker2IO[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_LOAD_STAGE1_Y_0 + i, m_btnLoadStage1Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_LOAD_STAGE1_IO_0 + i, m_btnLoadStage1IO[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_LOAD_STAGE2_Y_0 + i, m_btnLoadStage2Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_LOAD_STAGE2_IO_0 + i, m_btnLoadStage2IO[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_BTM_FOCUS_Z_0 + i, m_btnBtmFocusZ[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_BTM_LIGHT_Z_0 + i, m_btnBtmLightZ[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_BTM_ANGLE_Y_0 + i, m_btnBtmAngleY[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_MODULE_ALIGN_IO_0 + i, m_btnCMAlignIO[i]);

	for (int i = 0; i <32; i++) DDX_Control(pDX, IDC_LED_LOAD_PICKER1_IO_0 + i, m_ledLoadPicker1IO[i]);
	for (int i = 0; i <32; i++) DDX_Control(pDX, IDC_LED_LOAD_PICKER2_IO_0 + i, m_ledLoadPicker2IO[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LED_LOAD_STAGE1_IO_0 + i, m_ledLoadStage1IO[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LED_LOAD_STAGE2_IO_0 + i, m_ledLoadStage2IO[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_MODULE_ALIGN_IO_0 + i, m_ledCMAlignIO[i]);
}

BEGIN_MESSAGE_MAP(CManualLoadDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER1_X_0, IDC_BTN_LOAD_PICKER1_X_6,    OnBtnLoadPicker1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER1_Y_0, IDC_BTN_LOAD_PICKER1_Y_4,    OnBtnLoadPicker1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER1_Z_0, IDC_BTN_LOAD_PICKER1_Z_4,    OnBtnLoadPicker1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER1_P_0, IDC_BTN_LOAD_PICKER1_P_2,    OnBtnLoadPicker1PClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER1_IO_0, IDC_BTN_LOAD_PICKER1_IO_35, OnBtnLoadPicker1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER2_X_0, IDC_BTN_LOAD_PICKER2_X_6,    OnBtnLoadPicker2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER2_Y_0, IDC_BTN_LOAD_PICKER2_Y_4,    OnBtnLoadPicker2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER2_Z_0, IDC_BTN_LOAD_PICKER2_Z_4,    OnBtnLoadPicker2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER2_P_0, IDC_BTN_LOAD_PICKER2_P_2,    OnBtnLoadPicker2PClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_PICKER2_IO_0, IDC_BTN_LOAD_PICKER2_IO_35, OnBtnLoadPicker2IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_STAGE1_Y_0, IDC_BTN_LOAD_STAGE1_Y_7,      OnBtnLoadStage1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_STAGE1_IO_0, IDC_BTN_LOAD_STAGE1_IO_5,    OnBtnLoadStage1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_STAGE2_Y_0, IDC_BTN_LOAD_STAGE2_Y_7,      OnBtnLoadStage2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD_STAGE2_IO_0, IDC_BTN_LOAD_STAGE2_IO_5,    OnBtnLoadStage2IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_BTM_FOCUS_Z_0, IDC_BTN_BTM_FOCUS_Z_2,			OnBtnBtmFocusZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_BTM_LIGHT_Z_0, IDC_BTN_BTM_LIGHT_Z_2,			OnBtnBtmLightZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_BTM_ANGLE_Y_0, IDC_BTN_BTM_ANGLE_Y_2,			OnBtnBtmAlgleYClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MODULE_ALIGN_IO_0, IDC_BTN_MODULE_ALIGN_IO_5,  OnBtnCMAlignIOClick)

	ON_BN_CLICKED(IDC_BTN_MODULE_ALIGN_IO_6, &CManualLoadDlg::OnBnClickedBtnModuleAlignIo6)
END_MESSAGE_MAP()

// CManualLoadDlg 메시지 처리기입니다.
BOOL CManualLoadDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualLoadDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualLoadDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	m_strLog.Format("[Manual Load] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 5; i <10; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x90, 0x00), COLOR_DEFAULT);
	for (int i =10; i <12; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xC0, 0x80, 0xFF), COLOR_DEFAULT);
	for (int i =12; i <14; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xE0, 0x90, 0x00), COLOR_DEFAULT);
	for (int i =14; i <18; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x80, 0x30, 0x10), COLOR_DEFAULT);
	for (int i = 0; i <13; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i <13; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i < 7; i++) m_btnLoadPicker1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++) m_btnLoadPicker1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++) m_btnLoadPicker1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnLoadPicker1P[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <36; i++) m_btnLoadPicker1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 7; i++) m_btnLoadPicker2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++) m_btnLoadPicker2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++) m_btnLoadPicker2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnLoadPicker2P[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <36; i++) m_btnLoadPicker2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnLoadStage1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnLoadStage1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnLoadStage2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnLoadStage2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnBtmFocusZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnBtmLightZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnBtmAngleY[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnCMAlignIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);

	for (int i = 0; i <32; i++) m_ledLoadPicker1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <32; i++) m_ledLoadPicker2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 7; i++) m_ledLoadStage1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 7; i++) m_ledLoadStage2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 6; i++) m_ledCMAlignIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

}

void CManualLoadDlg::Display_Status()
{
	CString strPos;
	for (int i = 0; i < 13; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_LOAD_STAGE_Y1 + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	DX_DATA_04 *pDX04 = g_objAJinAXL.Get_pDX04();
	DX_DATA_05 *pDX05 = g_objAJinAXL.Get_pDX05();
	DX_DATA_06 *pDX06 = g_objAJinAXL.Get_pDX06();

	//Module Align
	m_ledCMAlignIO[0].Set_On(pDX03->iAlignMasterIn);
	m_ledCMAlignIO[1].Set_On(pDX03->iAlignMasterOut);
	m_ledCMAlignIO[2].Set_On(pDX03->iAlignSlave1In);
	m_ledCMAlignIO[3].Set_On(pDX03->iAlignSlave1Out);
	m_ledCMAlignIO[4].Set_On(pDX03->iAlignSlave2In);
	m_ledCMAlignIO[5].Set_On(pDX03->iAlignSlave2Out);

	//Load Stage1/2
	m_ledLoadStage1IO[0].Set_On(pDX04->iLoadStage1Up);
	m_ledLoadStage1IO[1].Set_On(pDX04->iLoadStage1Down);
	m_ledLoadStage1IO[2].Set_On(pDX04->iLoadStage1MasterIn);
	m_ledLoadStage1IO[3].Set_On(pDX04->iLoadStage1MasterOut);
	m_ledLoadStage1IO[4].Set_On(pDX04->iLoadStage1SlaveIn);
	m_ledLoadStage1IO[5].Set_On(pDX04->iLoadStage1SlaveOut);
	m_ledLoadStage1IO[6].Set_On(pDX04->iLoadStage1TrayExist);

	m_ledLoadStage2IO[0].Set_On(pDX04->iLoadStage2Up);
	m_ledLoadStage2IO[1].Set_On(pDX04->iLoadStage2Down);
	m_ledLoadStage2IO[2].Set_On(pDX04->iLoadStage2MasterIn);
	m_ledLoadStage2IO[3].Set_On(pDX04->iLoadStage2MasterOut);
	m_ledLoadStage2IO[4].Set_On(pDX04->iLoadStage2SlaveIn);
	m_ledLoadStage2IO[5].Set_On(pDX04->iLoadStage2SlaveOut);
	m_ledLoadStage2IO[6].Set_On(pDX04->iLoadStage2TrayExist);

	//Load Picker1
	m_ledLoadPicker1IO[0].Set_On(pDX05->iLoadPicker1Up1);
	m_ledLoadPicker1IO[1].Set_On(pDX05->iLoadPicker1Up2);
	m_ledLoadPicker1IO[2].Set_On(pDX05->iLoadPicker1Up3);
	m_ledLoadPicker1IO[3].Set_On(pDX05->iLoadPicker1Up4);
	m_ledLoadPicker1IO[4].Set_On(pDX05->iLoadPicker1Up5);
	m_ledLoadPicker1IO[5].Set_On(pDX05->iLoadPicker1Up6);
	m_ledLoadPicker1IO[6].Set_On(pDX05->iLoadPicker1Up7);
	m_ledLoadPicker1IO[7].Set_On(pDX05->iLoadPicker1Up8);

	m_ledLoadPicker1IO[ 8].Set_On(pDX05->iLoadPicker1Down1);
	m_ledLoadPicker1IO[ 9].Set_On(pDX05->iLoadPicker1Down2);
	m_ledLoadPicker1IO[10].Set_On(pDX05->iLoadPicker1Down3);
	m_ledLoadPicker1IO[11].Set_On(pDX05->iLoadPicker1Down4);
	m_ledLoadPicker1IO[12].Set_On(pDX05->iLoadPicker1Down5);
	m_ledLoadPicker1IO[13].Set_On(pDX05->iLoadPicker1Down6);
	m_ledLoadPicker1IO[14].Set_On(pDX05->iLoadPicker1Down7);
	m_ledLoadPicker1IO[15].Set_On(pDX05->iLoadPicker1Down8);

	m_ledLoadPicker1IO[16].Set_On(pDX05->iLoadPicker1Open1);
	m_ledLoadPicker1IO[17].Set_On(pDX05->iLoadPicker1Open2);
	m_ledLoadPicker1IO[18].Set_On(pDX05->iLoadPicker1Open3);
	m_ledLoadPicker1IO[19].Set_On(pDX05->iLoadPicker1Open4);
	m_ledLoadPicker1IO[20].Set_On(pDX05->iLoadPicker1Open5);
	m_ledLoadPicker1IO[21].Set_On(pDX05->iLoadPicker1Open6);
	m_ledLoadPicker1IO[22].Set_On(pDX05->iLoadPicker1Open7);
	m_ledLoadPicker1IO[23].Set_On(pDX05->iLoadPicker1Open8);

	m_ledLoadPicker1IO[24].Set_On(pDX05->iLoadPicker1Exist1);
	m_ledLoadPicker1IO[25].Set_On(pDX05->iLoadPicker1Exist2);
	m_ledLoadPicker1IO[26].Set_On(pDX05->iLoadPicker1Exist3);
	m_ledLoadPicker1IO[27].Set_On(pDX05->iLoadPicker1Exist4);
	m_ledLoadPicker1IO[28].Set_On(pDX05->iLoadPicker1Exist5);
	m_ledLoadPicker1IO[29].Set_On(pDX05->iLoadPicker1Exist6);
	m_ledLoadPicker1IO[30].Set_On(pDX05->iLoadPicker1Exist7);
	m_ledLoadPicker1IO[31].Set_On(pDX05->iLoadPicker1Exist8);

	//Load Picker2
	m_ledLoadPicker2IO[0].Set_On(pDX06->iLoadPicker2Up1);
	m_ledLoadPicker2IO[1].Set_On(pDX06->iLoadPicker2Up2);
	m_ledLoadPicker2IO[2].Set_On(pDX06->iLoadPicker2Up3);
	m_ledLoadPicker2IO[3].Set_On(pDX06->iLoadPicker2Up4);
	m_ledLoadPicker2IO[4].Set_On(pDX06->iLoadPicker2Up5);
	m_ledLoadPicker2IO[5].Set_On(pDX06->iLoadPicker2Up6);
	m_ledLoadPicker2IO[6].Set_On(pDX06->iLoadPicker2Up7);
	m_ledLoadPicker2IO[7].Set_On(pDX06->iLoadPicker2Up8);

	m_ledLoadPicker2IO[ 8].Set_On(pDX06->iLoadPicker2Down1);
	m_ledLoadPicker2IO[ 9].Set_On(pDX06->iLoadPicker2Down2);
	m_ledLoadPicker2IO[10].Set_On(pDX06->iLoadPicker2Down3);
	m_ledLoadPicker2IO[11].Set_On(pDX06->iLoadPicker2Down4);
	m_ledLoadPicker2IO[12].Set_On(pDX06->iLoadPicker2Down5);
	m_ledLoadPicker2IO[13].Set_On(pDX06->iLoadPicker2Down6);
	m_ledLoadPicker2IO[14].Set_On(pDX06->iLoadPicker2Down7);
	m_ledLoadPicker2IO[15].Set_On(pDX06->iLoadPicker2Down8);

	m_ledLoadPicker2IO[16].Set_On(pDX06->iLoadPicker2Open1);
	m_ledLoadPicker2IO[17].Set_On(pDX06->iLoadPicker2Open2);
	m_ledLoadPicker2IO[18].Set_On(pDX06->iLoadPicker2Open3);
	m_ledLoadPicker2IO[19].Set_On(pDX06->iLoadPicker2Open4);
	m_ledLoadPicker2IO[20].Set_On(pDX06->iLoadPicker2Open5);
	m_ledLoadPicker2IO[21].Set_On(pDX06->iLoadPicker2Open6);
	m_ledLoadPicker2IO[22].Set_On(pDX06->iLoadPicker2Open7);
	m_ledLoadPicker2IO[23].Set_On(pDX06->iLoadPicker2Open8);

	m_ledLoadPicker2IO[24].Set_On(pDX06->iLoadPicker2Exist1);
	m_ledLoadPicker2IO[25].Set_On(pDX06->iLoadPicker2Exist2);
	m_ledLoadPicker2IO[26].Set_On(pDX06->iLoadPicker2Exist3);
	m_ledLoadPicker2IO[27].Set_On(pDX06->iLoadPicker2Exist4);
	m_ledLoadPicker2IO[28].Set_On(pDX06->iLoadPicker2Exist5);
	m_ledLoadPicker2IO[29].Set_On(pDX06->iLoadPicker2Exist6);
	m_ledLoadPicker2IO[30].Set_On(pDX06->iLoadPicker2Exist7);
	m_ledLoadPicker2IO[31].Set_On(pDX06->iLoadPicker2Exist8);
}

///////////////////////////////////////////////////////////////////////////////
void CManualLoadDlg::OnBtnLoadPicker1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER_X1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER1_X_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) {
		AfxMessageBox(_T("Load Picker1 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	// Y축이 둘다 준비위치가 아닐때
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0) && !g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0)) {
		AfxMessageBox(_T("Load Picker1/2 Y축 모두 Ready 위치가 아닙니다....."));
		return;
	}
	if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0) && !g_objCommon.Get_LoadPickerUp(1)) {
		AfxMessageBox(_T("Load Picker1 Picker Up 위치가 아닙니다....."));
		return;
	}

	if (nIndex == 5 || nIndex == 6) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 5 ? -1 : 1);
		double dMove = pEquipData->dTrayPitchX * nDir;
		g_objAJinAXL.Move_Relative(AX_LOAD_PICKER_X1, dMove);
	} else {
		g_objCommon.Move_Position(AX_LOAD_PICKER_X1, nIndex);
	}

	m_strLog.Format("[Manual Load] Load Picker1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER_Y1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER1_Y_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) {
		AfxMessageBox(_T("Load Picker1 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	if (!g_objCommon.Get_LoadPickerUp(1)) {
		AfxMessageBox(_T("Load Picker1 Picker Up 위치가 아닙니다....."));
		return;
	}
	if (nIndex != 0) {
		double dCurPosX1 = g_objAJinAXL.Get_Position(AX_LOAD_PICKER_X1);
		double dCurPosX2 = g_objAJinAXL.Get_Position(AX_LOAD_PICKER_X2);
		if (dCurPosX1 >= dCurPosX2 && ((dCurPosX1 - dCurPosX2) < 400)) {
			AfxMessageBox(_T("Load Picker2 X축의 Interlock 위치가 아닙니다....."));
			return;
		}
		if (dCurPosX1 <= dCurPosX2 && ((dCurPosX2 - dCurPosX1) < 400)) {
			AfxMessageBox(_T("Load Picker2 X축의 Interlock 위치가 아닙니다....."));
			return;
		}
	}	

	g_objCommon.Move_Position(AX_LOAD_PICKER_Y1, nIndex);

	m_strLog.Format("[Manual Load] Load Picker1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER_Z1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER1_Z_0;

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	// Interlock
	if (nIndex != 0 && !g_objCommon.Check_Position(AX_LOAD_PICKER_X1, nIndex)) {
		if (nIndex == 1) {
			double dCurPosX1 = g_objAJinAXL.Get_Position(AX_LOAD_PICKER_X1);
			double dPicker1WorkPosS = pMoveData->dLoadPickerX1[1] - 0.1;
			double dPicker1WorkPosE = pMoveData->dLoadPickerX1[1] + pEquipData->dTrayPitchX * 4.0 + 0.1;
			if ( !((dPicker1WorkPosS < dCurPosX1) && (dCurPosX1 < dPicker1WorkPosE)) ) {
				AfxMessageBox(_T("Load Picker1 X축이 Stage1 위치가 아닙니다.....")); return; 
			}
		}
		if (nIndex == 2) {
			double dCurPosX1 = g_objAJinAXL.Get_Position(AX_LOAD_PICKER_X1);
			double dPicker1WorkPosS = pMoveData->dLoadPickerX1[2] - 0.1;
			double dPicker1WorkPosE = pMoveData->dLoadPickerX1[2] + pEquipData->dTrayPitchX * 4.0 + 0.1;
			if ( !((dPicker1WorkPosS < dCurPosX1) && (dCurPosX1 < dPicker1WorkPosE)) ) {
				AfxMessageBox(_T("Load Picker1 X축이 Stage2 위치가 아닙니다.....")); return;
			}
		}
//		if (nIndex == 3) { AfxMessageBox(_T("Load Picker1 X축이 Bottom Vision 위치가 아닙니다.....")); return; }
//		if (nIndex == 4) { AfxMessageBox(_T("Load Picker1 X축이 Align 위치가 아닙니다.....")); return; }
	}	
	if (nIndex == 1 || nIndex == 2 || nIndex == 4) {
		if (!g_objCommon.Get_LoadPickerUp(1, 0) && !g_objCommon.Get_LoadPickerOpen(1, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
	}

	g_objCommon.Move_Position(AX_LOAD_PICKER_Z1, nIndex);

	m_strLog.Format("[Manual Load] Load Picker1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker1PClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER_P1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER1_P_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) {
		AfxMessageBox(_T("Load Picker1 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	
	g_objCommon.Move_Position(AX_LOAD_PICKER_P1, nIndex);

	m_strLog.Format("[Manual Load] Load Picker1 P (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker1IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER1_IO_0;

	if (nIndex >= 0 && nIndex < 8) {
		g_objCommon.Set_LoadPickerUp(1, 9, nIndex+1, NULL);
	}

	if (nIndex >= 8 && nIndex < 16){
		if (g_objCommon.Get_LoadPickerClose(1, 9, nIndex-7) && !g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0)) {
			AfxMessageBox(_T("Load Picker1 Y축 현재위치에서 Down할수 없습니다..."));
			return;
		}
		g_objCommon.Set_LoadPickerDown(1, 9, nIndex-7);
	}

	if (nIndex >= 16 && nIndex < 24) {
		g_objCommon.Set_LoadPickerOpen(1, 9, nIndex-15);
	}

	if (nIndex >= 24 && nIndex < 32) {
		g_objCommon.Set_LoadPickerClose(1, 9, nIndex-23);
	}

	if (nIndex == 32) g_objCommon.Set_LoadPickerUp(1, 0);
	if (nIndex == 33) {
		if (!g_objCommon.Get_LoadPickerOpen(1, 0) && !g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0)) {
			AfxMessageBox(_T("Load Picker1 Y축 현재위치에서 Down할수 없습니다..."));
			return;
		}
		g_objCommon.Set_LoadPickerDown(1, 0);
	}
	if (nIndex == 34) g_objCommon.Set_LoadPickerOpen(1, 0);
	if (nIndex == 35) g_objCommon.Set_LoadPickerClose(1, 0);

	m_strLog.Format("[Manual Load] Load Picker1 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER_X2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER2_X_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) {
		AfxMessageBox(_T("Load Picker2 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	// Y축이 둘다 준비위치가 아닐때
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Y1, 0) && !g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0)) {
		AfxMessageBox(_T("Load Picker1/2 Y축 모두 Ready 위치가 아닙니다....."));
		return;
	}
	if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0) && !g_objCommon.Get_LoadPickerUp(2)) {
		AfxMessageBox(_T("Load Picker2 Picker Up 위치가 아닙니다....."));
		return;
	}

	if (nIndex == 5 || nIndex == 6) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 5 ? -1 : 1);
		double dMove = pEquipData->dTrayPitchX * nDir;
		g_objAJinAXL.Move_Relative(AX_LOAD_PICKER_X2, dMove);
	} else {
		g_objCommon.Move_Position(AX_LOAD_PICKER_X2, nIndex);
	}

	m_strLog.Format("[Manual Load] Load Picker2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER_Y2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER2_Y_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) {
		AfxMessageBox(_T("Load Picker2 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	if (!g_objCommon.Get_LoadPickerUp(2)) {
		AfxMessageBox(_T("Load Picker2 Picker Up 위치가 아닙니다....."));
		return;
	}
	if (nIndex != 0) {
		double dCurPosX1 = g_objAJinAXL.Get_Position(AX_LOAD_PICKER_X1);
		double dCurPosX2 = g_objAJinAXL.Get_Position(AX_LOAD_PICKER_X2);
		if (dCurPosX1 >= dCurPosX2 && ((dCurPosX1 - dCurPosX2) < 400)) {
			AfxMessageBox(_T("Load Picker1 X축의 Interlock 위치가 아닙니다....."));
			return;
		}
		if (dCurPosX1 <= dCurPosX2 && ((dCurPosX2 - dCurPosX1) < 400)) {
			AfxMessageBox(_T("Load Picker1 X축의 Interlock 위치가 아닙니다....."));
			return;
		}
	}	

	g_objCommon.Move_Position(AX_LOAD_PICKER_Y2, nIndex);

	m_strLog.Format("[Manual Load] Load Picker2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER_Z2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER2_Z_0;

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	// Interlock
	if (nIndex != 0 && !g_objCommon.Check_Position(AX_LOAD_PICKER_X2, nIndex)) {
		if (nIndex == 1) {
			double dCurPosX2 = g_objAJinAXL.Get_Position(AX_LOAD_PICKER_X2);
			double dPicker2WorkPosS = pMoveData->dLoadPickerX2[1] - 0.1;
			double dPicker2WorkPosE = pMoveData->dLoadPickerX2[1] + pEquipData->dTrayPitchX * 4.0 + 0.1;
			if ( !((dPicker2WorkPosS < dCurPosX2) && (dCurPosX2 < dPicker2WorkPosE)) ) {
				AfxMessageBox(_T("Load Picker2 X축이 Stage1 위치가 아닙니다.....")); return; 
			}
		}
		if (nIndex == 2) {
			double dCurPosX2 = g_objAJinAXL.Get_Position(AX_LOAD_PICKER_X2);
			double dPicker2WorkPosS = pMoveData->dLoadPickerX2[2] - 0.1;
			double dPicker2WorkPosE = pMoveData->dLoadPickerX2[2] + pEquipData->dTrayPitchX * 4.0 + 0.1;
			if ( !((dPicker2WorkPosS < dCurPosX2) && (dCurPosX2 < dPicker2WorkPosE)) ) {
				AfxMessageBox(_T("Load Picker2 X축이 Stage2 위치가 아닙니다.....")); return;
			}
		}
//		if (nIndex == 3) { AfxMessageBox(_T("Load Picker2 X축이 Bottom Vision 위치가 아닙니다.....")); return; }
//		if (nIndex == 4) { AfxMessageBox(_T("Load Picker2 X축이 Align 위치가 아닙니다.....")); return; }
	}	
	if (nIndex == 1 || nIndex == 2 || nIndex == 4) {
		if (!g_objCommon.Get_LoadPickerUp(2, 0) && !g_objCommon.Get_LoadPickerOpen(2, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
	}

	g_objCommon.Move_Position(AX_LOAD_PICKER_Z2, nIndex);

	m_strLog.Format("[Manual Load] Load Picker2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker2PClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_PICKER_P2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER2_P_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) {
		AfxMessageBox(_T("Load Picker2 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}

	g_objCommon.Move_Position(AX_LOAD_PICKER_P2, nIndex);

	m_strLog.Format("[Manual Load] Load Picker2 P (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadPicker2IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_PICKER2_IO_0;

	if (nIndex >= 0 && nIndex < 8) {
		g_objCommon.Set_LoadPickerUp(2, 9, nIndex+1);
	}

	if (nIndex >= 8 && nIndex < 16){
		if (g_objCommon.Get_LoadPickerClose(2, 9, nIndex-7) && !g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0)) {
			AfxMessageBox(_T("Load Picker2 Y축 현재위치에서 Down할수 없습니다..."));
			return;
		}
		g_objCommon.Set_LoadPickerDown(2, 9, nIndex-7);
	}

	if (nIndex >= 16 && nIndex < 24) {
		g_objCommon.Set_LoadPickerOpen(2, 9, nIndex-15);
	}

	if (nIndex >= 24 && nIndex < 32) {
		g_objCommon.Set_LoadPickerClose(2, 9, nIndex-23);
	}

	if (nIndex == 32) g_objCommon.Set_LoadPickerUp(2, 0);
	if (nIndex == 33) {
		if (!g_objCommon.Get_LoadPickerOpen(2, 0) && !g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
		if (g_objCommon.Check_Position(AX_LOAD_PICKER_Y2, 0)) {
			AfxMessageBox(_T("Load Picker2 Y축 현재위치에서 Down할수 없습니다..."));
			return;
		}
		g_objCommon.Set_LoadPickerDown(2, 0);
	}
	if (nIndex == 34) g_objCommon.Set_LoadPickerOpen(2, 0);
	if (nIndex == 35) g_objCommon.Set_LoadPickerClose(2, 0);

	m_strLog.Format("[Manual Load] Load Picker2 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadStage1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_STAGE_Y1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_STAGE1_Y_0;

	DX_DATA_04 *pDX04 = g_objAJinAXL.Get_pDX04();

	// Interlock
	if ((pDX04->iLoadStage1Up && pDX04->iLoadStage2Up) || (pDX04->iLoadStage1Down && pDX04->iLoadStage2Down) ) {
		AfxMessageBox(_T("Load Stage 1/2 같은 높이에 있습니다....."));
		return;
	}
	if (!pDX04->iLoadStage1Up && !pDX04->iLoadStage1Down) {
		AfxMessageBox(_T("Load Stage1 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}
	if (!pDX04->iLoadStage2Up && !pDX04->iLoadStage2Down) {
		AfxMessageBox(_T("Load Stage2 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}

	if (nIndex == 6 || nIndex == 7) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 6 ? 1 : -1);
		double dMove = pEquipData->dTrayPitchY * nDir;
		g_objAJinAXL.Move_Relative(AX_LOAD_STAGE_Y1, dMove);
	} else {
		g_objCommon.Move_Position(AX_LOAD_STAGE_Y1, nIndex);
	}

	m_strLog.Format("[Manual Load] Load Stage1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnLoadStage1IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_STAGE1_IO_0;

	DY_DATA_04 *pDY04 = g_objAJinAXL.Get_pDY04();

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	double dCurPosY1 = g_objAJinAXL.Get_Position(AX_LOAD_STAGE_Y1);
	double dCurPosY2 = g_objAJinAXL.Get_Position(AX_LOAD_STAGE_Y2);
	double dTray1WorkPosS = pMoveData->dLoadStageY1[2] - 0.1;
	double dTray1WorkPosE = pMoveData->dLoadStageY1[2] + pEquipData->dTrayPitchY * 9.0 + 0.1;
	double dTray2WorkPosS = pMoveData->dLoadStageY2[2] - 0.1;
	double dTray2WorkPosE = pMoveData->dLoadStageY2[2] + pEquipData->dTrayPitchY * 9.0 + 0.1;

	// Interlock
	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 1) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE))) {
			AfxMessageBox(_T("Load Stage1 Y축 Load/Wait/Unload 위치가 아닙니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 0)) {
			if (!g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 1) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) ){
				AfxMessageBox(_T("Load Stage2 Y축 Wait/Unload 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 1)) {
			if (!g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 0) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) ){
				AfxMessageBox(_T("Load Stage2 Y축 Load/Unload 위치가 아닙니다....."));
				return;
			}
		}
		if ((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE)) {
			if (!g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 1)){
				AfxMessageBox(_T("Load Stage2 Y축 Load/Wait 위치가 아닙니다....."));
				return;
			}
		}
		if (nIndex == 0) { pDY04->oLoadStage1Up = TRUE;  pDY04->oLoadStage1Down = FALSE; }
		if (nIndex == 1) { pDY04->oLoadStage1Up = FALSE; pDY04->oLoadStage1Down = TRUE; }

	} else {
		if (nIndex == 2) { pDY04->oLoadStage1MasterIn = TRUE;  pDY04->oLoadStage1MasterOut = FALSE; }
		if (nIndex == 3) { pDY04->oLoadStage1MasterIn = FALSE; pDY04->oLoadStage1MasterOut = TRUE; }
		if (nIndex == 4) { pDY04->oLoadStage1SlaveIn = TRUE;  pDY04->oLoadStage1SlaveOut = FALSE; }
		if (nIndex == 5) { pDY04->oLoadStage1SlaveIn = FALSE; pDY04->oLoadStage1SlaveOut = TRUE; }
	}

	g_objAJinAXL.Write_Output(4);

	m_strLog.Format("[Manual Load] Load Stage1 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualLoadDlg::OnBtnLoadStage2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_LOAD_STAGE_Y2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_STAGE2_Y_0;

	DX_DATA_04 *pDX04 = g_objAJinAXL.Get_pDX04();

	// Interlock
	if ((pDX04->iLoadStage1Up && pDX04->iLoadStage2Up) || (pDX04->iLoadStage1Down && pDX04->iLoadStage2Down) ) {
		AfxMessageBox(_T("Load Stage 1/2 같은 높이에 있습니다....."));
		return;
	}
	if (!pDX04->iLoadStage1Up && !pDX04->iLoadStage1Down) {
		AfxMessageBox(_T("Load Stage1 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}
	if (!pDX04->iLoadStage2Up && !pDX04->iLoadStage2Down) {
		AfxMessageBox(_T("Load Stage2 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}

	if (nIndex == 6 || nIndex == 7) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 6 ? 1 : -1);
		double dMove = pEquipData->dTrayPitchY * nDir;
		g_objAJinAXL.Move_Relative(AX_LOAD_STAGE_Y2, dMove);
	} else {
		g_objCommon.Move_Position(AX_LOAD_STAGE_Y2, nIndex);
	}

	m_strLog.Format("[Manual Load] Load Stage2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualLoadDlg::OnBtnLoadStage2IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD_STAGE2_IO_0;

	DY_DATA_04 *pDY04 = g_objAJinAXL.Get_pDY04();

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	double dCurPosY1 = g_objAJinAXL.Get_Position(AX_LOAD_STAGE_Y1);
	double dCurPosY2 = g_objAJinAXL.Get_Position(AX_LOAD_STAGE_Y2);
	double dTray1WorkPosS = pMoveData->dLoadStageY1[2] - 0.1;
	double dTray1WorkPosE = pMoveData->dLoadStageY1[2] + pEquipData->dTrayPitchY * 9.0 + 0.1;
	double dTray2WorkPosS = pMoveData->dLoadStageY2[2] - 0.1;
	double dTray2WorkPosE = pMoveData->dLoadStageY2[2] + pEquipData->dTrayPitchY * 9.0 + 0.1;

	// Interlock
	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 1) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) ) {
			AfxMessageBox(_T("Load Stage2 Y축 Load/Wait/Unload 위치가 아닙니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 0)) {
			if (!g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 1) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE)) ){
				AfxMessageBox(_T("Load Stage1 Y축 Wait/Unload 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_LOAD_STAGE_Y2, 1)) {
			if (!g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 0) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE)) ){
				AfxMessageBox(_T("Load Stage1 Y축 Load/Unload 위치가 아닙니다....."));
				return;
			}
		}
		if ((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) {
			if (!g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_LOAD_STAGE_Y1, 1)){
				AfxMessageBox(_T("Load Stage1 Y축 Load/Wait 위치가 아닙니다....."));
				return;
			}
		}
		if (nIndex == 0) { pDY04->oLoadStage2Up = TRUE;  pDY04->oLoadStage2Down = FALSE; }
		if (nIndex == 1) { pDY04->oLoadStage2Up = FALSE; pDY04->oLoadStage2Down = TRUE; }

	} else {
		if (nIndex == 2) { pDY04->oLoadStage2MasterIn = TRUE;  pDY04->oLoadStage2MasterOut = FALSE; }
		if (nIndex == 3) { pDY04->oLoadStage2MasterIn = FALSE; pDY04->oLoadStage2MasterOut = TRUE; }
		if (nIndex == 4) { pDY04->oLoadStage2SlaveIn = TRUE;  pDY04->oLoadStage2SlaveOut = FALSE; }
		if (nIndex == 5) { pDY04->oLoadStage2SlaveIn = FALSE; pDY04->oLoadStage2SlaveOut = TRUE; }
	}

	g_objAJinAXL.Write_Output(4);

	m_strLog.Format("[Manual Load] Load Stage2 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnBtmFocusZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_BTM_FOCUS_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_BTM_FOCUS_Z_0;

	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_BTM_ANGLE_Y, 1)) {
			AfxMessageBox(_T("BTM Angle Y축이 Vision 위치에서 진행이 가능합니다..."));
			return;
		}
	}
	g_objCommon.Move_Position(AX_BTM_FOCUS_Z, nIndex);

	m_strLog.Format("[Manual Load] Bottom Focus Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnBtmLightZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_BTM_LIGHT_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_BTM_LIGHT_Z_0;

	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_BTM_ANGLE_Y, 1)) {
			AfxMessageBox(_T("BTM Angle Y축이 Vision 위치에서 진행이 가능합니다..."));
			return;
		}
	}
	g_objCommon.Move_Position(AX_BTM_LIGHT_Z, nIndex);

	m_strLog.Format("[Manual Load] Bottom Light Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnBtmAlgleYClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_BTM_ANGLE_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_BTM_ANGLE_Y_0;

	if (nIndex == 2) {
		if (!g_objCommon.Check_Position(AX_BTM_LIGHT_Z, 2)) {
			AfxMessageBox(_T("BTM Light Z축이 Angle 위치에서 진행이 가능합니다..."));
			return;
		}
		if (!g_objCommon.Check_Position(AX_BTM_FOCUS_Z, 2)) {
			AfxMessageBox(_T("BTM Focus Z축이 Angle 위치에서 진행이 가능합니다..."));
			return;
		}
	}
	g_objCommon.Move_Position(AX_BTM_ANGLE_Y, nIndex);

	m_strLog.Format("[Manual Load] Bottom Angle Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualLoadDlg::OnBtnCMAlignIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_MODULE_ALIGN_IO_0;

	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();

	if (nIndex == 0) { pDY03->oAlignMasterIn = TRUE;  pDY03->oAlignMasterOut = FALSE; }
	if (nIndex == 1) { pDY03->oAlignMasterIn = FALSE; pDY03->oAlignMasterOut = TRUE; }
	if (nIndex == 2) { pDY03->oAlignSlave1In = TRUE;  pDY03->oAlignSlave1Out = FALSE; }
	if (nIndex == 3) { pDY03->oAlignSlave1In = FALSE; pDY03->oAlignSlave1Out = TRUE; }
	if (nIndex == 4) { pDY03->oAlignSlave2In = TRUE;  pDY03->oAlignSlave2Out = FALSE; }
	if (nIndex == 5) { pDY03->oAlignSlave2In = FALSE; pDY03->oAlignSlave2Out = TRUE; }

	g_objAJinAXL.Write_Output(3);

	m_strLog.Format("[Manual Load] Module Align IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
///////////////////////////////////////////////////////////////////////////////
void CManualLoadDlg::DoEvents(int nSleep)
{
	MSG msg;
	if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (nSleep > 0) Sleep(nSleep);
}

void CManualLoadDlg::Set_Align()
{
	if (!g_objCommon.Check_MainDoor()) return;

	int		nStageNo = 0;
	DWORD	dwStart;
	CString sLog;

	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();
	if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0)) {
		if (pDX07->iInspectStage1Up && !pDX07->iInspectStage1Down) {
			if (pDX07->iInspectStage1Yin && !pDX07->iInspectStage1YOut) {
				nStageNo = 1;
			}
		}
	}
	if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0)) {
		if (pDX07->iInspectStage2Up && !pDX07->iInspectStage2Down) {
			nStageNo = 2;
		}
	}
	if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0)) {
		if (pDX08->iInspectStage3Up && !pDX08->iInspectStage3Down) {
			nStageNo = 3;
		}
	}
	if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
		if (pDX08->iInspectStage4Up && !pDX08->iInspectStage4Down) {
			if (pDX08->iInspectStage4Yin && !pDX08->iInspectStage4YOut) {
				nStageNo = 4;
			}
		}
	}
	if (nStageNo == 0) {
		g_objCommon.Show_MsgBox(1, "Align위치에 Inspection Stage가 없습니다.");
		return;
	}
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Z1, 0)) {
		AfxMessageBox(_T("Load Picker1 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	if (!g_objCommon.Check_Position(AX_LOAD_PICKER_Z2, 0)) {
		AfxMessageBox(_T("Load Picker2 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}

	// Align-Out
	g_objCommon.Set_VisionVacuumOff(nStageNo);
	pDY03->oAlignSlave2In = FALSE; pDY03->oAlignSlave2Out = TRUE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(!pDX03->iAlignSlave2In && pDX03->iAlignSlave2Out)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}
	pDY03->oAlignSlave1In = FALSE; pDY03->oAlignSlave1Out = TRUE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(!pDX03->iAlignSlave1In && pDX03->iAlignSlave1Out)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}
	pDY03->oAlignMasterIn = FALSE; pDY03->oAlignMasterOut = TRUE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(!pDX03->iAlignMasterIn && pDX03->iAlignMasterOut)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}

	// Align-In
	g_objCommon.Set_VisionVacuumOff(nStageNo);
	pDY03->oAlignMasterIn = TRUE; pDY03->oAlignMasterOut = FALSE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(pDX03->iAlignMasterIn && !pDX03->iAlignMasterOut)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}
	if (!pDX03->iAlignMasterIn || pDX03->iAlignMasterOut) {
		AfxMessageBox(_T("Master In 미완료. 센서 확인해 주세요....."));
		return;
	}

	pDY03->oAlignSlave1In = TRUE; pDY03->oAlignSlave1Out = FALSE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(pDX03->iAlignSlave1In && !pDX03->iAlignSlave1Out)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}
	if (!pDX03->iAlignSlave1In || pDX03->iAlignSlave1Out) {
		AfxMessageBox(_T("Slave1 In 미완료. 센서 확인해 주세요....."));
		return;
	}

	pDY03->oAlignSlave2In = TRUE; pDY03->oAlignSlave2Out = FALSE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(pDX03->iAlignSlave2In && !pDX03->iAlignSlave2Out)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}
	if (!pDX03->iAlignSlave2In || pDX03->iAlignSlave2Out) {
		AfxMessageBox(_T("Slave2 In 미완료. 센서 확인해 주세요....."));
		return;
	}

	// Align-Out
	g_objCommon.Set_VisionVacuumOn(nStageNo);	Sleep(300);
	pDY03->oAlignSlave2In = FALSE; pDY03->oAlignSlave2Out = TRUE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(!pDX03->iAlignSlave2In && pDX03->iAlignSlave2Out)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}
	pDY03->oAlignSlave1In = FALSE; pDY03->oAlignSlave1Out = TRUE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(!pDX03->iAlignSlave1In && pDX03->iAlignSlave1Out)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}
	pDY03->oAlignMasterIn = FALSE; pDY03->oAlignMasterOut = TRUE;
	g_objAJinAXL.Write_Output(3);
	dwStart = GetTickCount();
	while (!(!pDX03->iAlignMasterIn && pDX03->iAlignMasterOut)) {
		if (GetTickCount() - dwStart > 3000) break;
		DoEvents();
	}

	//Vacuum On Check
	if (g_objCommon.Get_VisionVacuumOn(nStageNo, 0)) sLog.Format("Inspection Stage%d Align 완료하였습니다.\r\n상태: Vacuum On", nStageNo);
	else											 sLog.Format("Inspection Stage%d Align 완료하였습니다.\r\n상태: Vacuum Off", nStageNo);
	g_objCommon.Show_MsgBox(1, sLog);

	m_strLog.Format("[Manual Load] Set_Align Retray Click (%d)", nStageNo);
	g_objLogFile.Save_HandlerLog(m_strLog);
}


void CManualLoadDlg::OnBnClickedBtnModuleAlignIo6()
{
	Set_Align();
}
