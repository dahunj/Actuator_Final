// ManualUnloadDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualUnloadDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"

// CManualUnloadDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualUnloadDlg, CDialogEx)

CManualUnloadDlg::CManualUnloadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualUnloadDlg::IDD, pParent)
{
}

CManualUnloadDlg::~CManualUnloadDlg()
{
}

void CManualUnloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i <19; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i <13; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i <13; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i <18; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER1_X_0 + i,	m_btnUnloadPicker1X[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER1_Y_0 + i,	m_btnUnloadPicker1Y[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER1_Z_0 + i,	m_btnUnloadPicker1Z[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER1_P_0 + i,	m_btnUnloadPicker1P[i]);
	for (int i = 0; i <36; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER1_IO_0 + i,	m_btnUnloadPicker1IO[i]);
	for (int i = 0; i <18; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER2_X_0 + i,	m_btnUnloadPicker2X[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER2_Y_0 + i,	m_btnUnloadPicker2Y[i]);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER2_Z_0 + i,	m_btnUnloadPicker2Z[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER2_P_0 + i,	m_btnUnloadPicker2P[i]);
	for (int i = 0; i <36; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_PICKER2_IO_0 + i,	m_btnUnloadPicker2IO[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_GOOD_STAGE1_Y_0 + i,		m_btnGoodStage1Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_GOOD_STAGE1_IO_0 + i,		m_btnGoodStage1IO[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_GOOD_STAGE2_Y_0 + i,		m_btnGoodStage2Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_GOOD_STAGE2_IO_0 + i,		m_btnGoodStage2IO[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_NG_STAGE1_Y_0 + i,			m_btnNGStage1Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_NG_STAGE1_IO_0 + i,		m_btnNGStage1IO[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_NG_STAGE2_Y_0 + i,			m_btnNGStage2Y[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_BTN_NG_STAGE2_IO_0 + i,		m_btnNGStage2IO[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_UNLOAD_VISION_X_0 + i,		m_btnUnloadVisionX[i]);

	for (int i = 0; i <32; i++) DDX_Control(pDX, IDC_LED_UNLOAD_PICKER1_IO_0 + i,	m_ledUnloadPicker1IO[i]);
	for (int i = 0; i <32; i++) DDX_Control(pDX, IDC_LED_UNLOAD_PICKER2_IO_0 + i,	m_ledUnloadPicker2IO[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LED_GOOD_STAGE1_IO_0 + i,		m_ledGoodStage1IO[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LED_GOOD_STAGE2_IO_0 + i,		m_ledGoodStage2IO[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LED_NG_STAGE1_IO_0 + i,		m_ledNGStage1IO[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LED_NG_STAGE2_IO_0 + i,		m_ledNGStage2IO[i]);
}

BEGIN_MESSAGE_MAP(CManualUnloadDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER1_X_0, IDC_BTN_UNLOAD_PICKER1_X_17,    OnBtnUnloadPicker1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER1_Y_0, IDC_BTN_UNLOAD_PICKER1_Y_8,    OnBtnUnloadPicker1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER1_Z_0, IDC_BTN_UNLOAD_PICKER1_Z_8,    OnBtnUnloadPicker1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER1_P_0, IDC_BTN_UNLOAD_PICKER1_P_2,    OnBtnUnloadPicker1PClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER1_IO_0, IDC_BTN_UNLOAD_PICKER1_IO_35,	OnBtnUnloadPicker1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER2_X_0, IDC_BTN_UNLOAD_PICKER2_X_17,    OnBtnUnloadPicker2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER2_Y_0, IDC_BTN_UNLOAD_PICKER2_Y_8,    OnBtnUnloadPicker2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER2_Z_0, IDC_BTN_UNLOAD_PICKER2_Z_8,    OnBtnUnloadPicker2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER2_P_0, IDC_BTN_UNLOAD_PICKER2_P_2,    OnBtnUnloadPicker2PClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_PICKER2_IO_0, IDC_BTN_UNLOAD_PICKER2_IO_35,  OnBtnUnloadPicker2IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_STAGE1_Y_0, IDC_BTN_GOOD_STAGE1_Y_7,			OnBtnGoodStage1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_STAGE1_IO_0, IDC_BTN_GOOD_STAGE1_IO_5,		OnBtnGoodStage1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_STAGE2_Y_0, IDC_BTN_GOOD_STAGE2_Y_7,			OnBtnGoodStage2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_STAGE2_IO_0, IDC_BTN_GOOD_STAGE2_IO_5,		OnBtnGoodStage2IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_STAGE1_Y_0, IDC_BTN_NG_STAGE1_Y_7,				OnBtnNGStage1YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_STAGE1_IO_0, IDC_BTN_NG_STAGE1_IO_5,			OnBtnNGStage1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_STAGE2_Y_0, IDC_BTN_NG_STAGE2_Y_7,				OnBtnNGStage2YClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_STAGE2_IO_0, IDC_BTN_NG_STAGE2_IO_5,			OnBtnNGStage2IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_UNLOAD_VISION_X_0, IDC_BTN_UNLOAD_VISION_X_3,		OnBtnUnloadVisionXClick)
END_MESSAGE_MAP()

// CManualUnloadDlg 메시지 처리기입니다.
BOOL CManualUnloadDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualUnloadDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualUnloadDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	m_strLog.Format("[Manual Unload] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::Initial_Controls() 
{
	for (int i = 0; i < 5; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 5; i <10; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x90, 0x00), COLOR_DEFAULT);
	for (int i =10; i <12; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xC0, 0x80, 0xFF), COLOR_DEFAULT);
	for (int i =12; i <14; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xE0, 0x90, 0x00), COLOR_DEFAULT);
	for (int i =14; i <16; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xC0, 0x80, 0xFF), COLOR_DEFAULT);
	for (int i =16; i <18; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xE0, 0x90, 0x00), COLOR_DEFAULT);
	for (int i =18; i <19; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x80, 0x30, 0x10), COLOR_DEFAULT);
	for (int i = 0; i <13; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i <13; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
//	for (int i = 0; i < 5; i++) m_btnUnloadPicker1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 9; i++) m_btnUnloadPicker1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 9; i++) m_btnUnloadPicker1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnUnloadPicker1P[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <36; i++) m_btnUnloadPicker1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
// 	for (int i = 0; i < 5; i++) m_btnUnloadPicker2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 9; i++) m_btnUnloadPicker2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 9; i++) m_btnUnloadPicker2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnUnloadPicker2P[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <36; i++) m_btnUnloadPicker2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnGoodStage1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnGoodStage1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnGoodStage2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnGoodStage2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnNGStage1Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnNGStage1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnNGStage2Y[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 6; i++) m_btnNGStage2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 4; i++) m_btnUnloadVisionX[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	
	for (int i = 0; i <32; i++) m_ledUnloadPicker1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <32; i++) m_ledUnloadPicker2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 7; i++) m_ledGoodStage1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 7; i++) m_ledGoodStage2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 7; i++) m_ledNGStage1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 7; i++) m_ledNGStage2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CManualUnloadDlg::Display_Status()
{
	CString strPos;
	for (int i = 0; i < 13; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X1 + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	DX_DATA_09 *pDX09 = g_objAJinAXL.Get_pDX09();
	DX_DATA_10 *pDX10 = g_objAJinAXL.Get_pDX10();
	DX_DATA_11 *pDX11 = g_objAJinAXL.Get_pDX11();
	DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();

	//Good Stage1/2
	m_ledGoodStage1IO[0].Set_On(pDX12->iGoodStage1Up);
	m_ledGoodStage1IO[1].Set_On(pDX12->iGoodStage1Down);
	m_ledGoodStage1IO[2].Set_On(pDX12->iGoodStage1MasterIn);
	m_ledGoodStage1IO[3].Set_On(pDX12->iGoodStage1MasterOut);
	m_ledGoodStage1IO[4].Set_On(pDX12->iGoodStage1SlaveIn);
	m_ledGoodStage1IO[5].Set_On(pDX12->iGoodStage1SlaveOut);
	m_ledGoodStage1IO[6].Set_On(pDX12->iGoodStage1TrayExist);

	m_ledGoodStage2IO[0].Set_On(pDX12->iGoodStage2Up);
	m_ledGoodStage2IO[1].Set_On(pDX12->iGoodStage2Down);
	m_ledGoodStage2IO[2].Set_On(pDX12->iGoodStage2MasterIn);
	m_ledGoodStage2IO[3].Set_On(pDX12->iGoodStage2MasterOut);
	m_ledGoodStage2IO[4].Set_On(pDX12->iGoodStage2SlaveIn);
	m_ledGoodStage2IO[5].Set_On(pDX12->iGoodStage2SlaveOut);
	m_ledGoodStage2IO[6].Set_On(pDX12->iGoodStage2TrayExist);

	//NG Stage1/2
	m_ledNGStage1IO[0].Set_On(pDX11->iNGStage1Up);
	m_ledNGStage1IO[1].Set_On(pDX11->iNGStage1Down);
	m_ledNGStage1IO[2].Set_On(pDX11->iNGStage1MasterIn);
	m_ledNGStage1IO[3].Set_On(pDX11->iNGStage1MasterOut);
	m_ledNGStage1IO[4].Set_On(pDX11->iNGStage1SlaveIn);
	m_ledNGStage1IO[5].Set_On(pDX11->iNGStage1SlaveOut);
	m_ledNGStage1IO[6].Set_On(pDX11->iNGStage1TrayExist);

	m_ledNGStage2IO[0].Set_On(pDX11->iNGStage2Up);
	m_ledNGStage2IO[1].Set_On(pDX11->iNGStage2Down);
	m_ledNGStage2IO[2].Set_On(pDX11->iNGStage2MasterIn);
	m_ledNGStage2IO[3].Set_On(pDX11->iNGStage2MasterOut);
	m_ledNGStage2IO[4].Set_On(pDX11->iNGStage2SlaveIn);
	m_ledNGStage2IO[5].Set_On(pDX11->iNGStage2SlaveOut);
	m_ledNGStage2IO[6].Set_On(pDX11->iNGStage2TrayExist);

	//Unload Picker1
	m_ledUnloadPicker1IO[0].Set_On(pDX09->iUnloadPicker1Up1);
	m_ledUnloadPicker1IO[1].Set_On(pDX09->iUnloadPicker1Up2);
	m_ledUnloadPicker1IO[2].Set_On(pDX09->iUnloadPicker1Up3);
	m_ledUnloadPicker1IO[3].Set_On(pDX09->iUnloadPicker1Up4);
	m_ledUnloadPicker1IO[4].Set_On(pDX09->iUnloadPicker1Up5);
	m_ledUnloadPicker1IO[5].Set_On(pDX09->iUnloadPicker1Up6);
	m_ledUnloadPicker1IO[6].Set_On(pDX09->iUnloadPicker1Up7);
	m_ledUnloadPicker1IO[7].Set_On(pDX09->iUnloadPicker1Up8);

	m_ledUnloadPicker1IO[ 8].Set_On(pDX09->iUnloadPicker1Down1);
	m_ledUnloadPicker1IO[ 9].Set_On(pDX09->iUnloadPicker1Down2);
	m_ledUnloadPicker1IO[10].Set_On(pDX09->iUnloadPicker1Down3);
	m_ledUnloadPicker1IO[11].Set_On(pDX09->iUnloadPicker1Down4);
	m_ledUnloadPicker1IO[12].Set_On(pDX09->iUnloadPicker1Down5);
	m_ledUnloadPicker1IO[13].Set_On(pDX09->iUnloadPicker1Down6);
	m_ledUnloadPicker1IO[14].Set_On(pDX09->iUnloadPicker1Down7);
	m_ledUnloadPicker1IO[15].Set_On(pDX09->iUnloadPicker1Down8);

	m_ledUnloadPicker1IO[16].Set_On(pDX09->iUnloadPicker1Open1);
	m_ledUnloadPicker1IO[17].Set_On(pDX09->iUnloadPicker1Open2);
	m_ledUnloadPicker1IO[18].Set_On(pDX09->iUnloadPicker1Open3);
	m_ledUnloadPicker1IO[19].Set_On(pDX09->iUnloadPicker1Open4);
	m_ledUnloadPicker1IO[20].Set_On(pDX09->iUnloadPicker1Open5);
	m_ledUnloadPicker1IO[21].Set_On(pDX09->iUnloadPicker1Open6);
	m_ledUnloadPicker1IO[22].Set_On(pDX09->iUnloadPicker1Open7);
	m_ledUnloadPicker1IO[23].Set_On(pDX09->iUnloadPicker1Open8);

	m_ledUnloadPicker1IO[24].Set_On(pDX09->iUnloadPicker1Exist1);
	m_ledUnloadPicker1IO[25].Set_On(pDX09->iUnloadPicker1Exist2);
	m_ledUnloadPicker1IO[26].Set_On(pDX09->iUnloadPicker1Exist3);
	m_ledUnloadPicker1IO[27].Set_On(pDX09->iUnloadPicker1Exist4);
	m_ledUnloadPicker1IO[28].Set_On(pDX09->iUnloadPicker1Exist5);
	m_ledUnloadPicker1IO[29].Set_On(pDX09->iUnloadPicker1Exist6);
	m_ledUnloadPicker1IO[30].Set_On(pDX09->iUnloadPicker1Exist7);
	m_ledUnloadPicker1IO[31].Set_On(pDX09->iUnloadPicker1Exist8);

	//Unload Picker2
	m_ledUnloadPicker2IO[0].Set_On(pDX10->iUnloadPicker2Up1);
	m_ledUnloadPicker2IO[1].Set_On(pDX10->iUnloadPicker2Up2);
	m_ledUnloadPicker2IO[2].Set_On(pDX10->iUnloadPicker2Up3);
	m_ledUnloadPicker2IO[3].Set_On(pDX10->iUnloadPicker2Up4);
	m_ledUnloadPicker2IO[4].Set_On(pDX10->iUnloadPicker2Up5);
	m_ledUnloadPicker2IO[5].Set_On(pDX10->iUnloadPicker2Up6);
	m_ledUnloadPicker2IO[6].Set_On(pDX10->iUnloadPicker2Up7);
	m_ledUnloadPicker2IO[7].Set_On(pDX10->iUnloadPicker2Up8);

	m_ledUnloadPicker2IO[ 8].Set_On(pDX10->iUnloadPicker2Down1);
	m_ledUnloadPicker2IO[ 9].Set_On(pDX10->iUnloadPicker2Down2);
	m_ledUnloadPicker2IO[10].Set_On(pDX10->iUnloadPicker2Down3);
	m_ledUnloadPicker2IO[11].Set_On(pDX10->iUnloadPicker2Down4);
	m_ledUnloadPicker2IO[12].Set_On(pDX10->iUnloadPicker2Down5);
	m_ledUnloadPicker2IO[13].Set_On(pDX10->iUnloadPicker2Down6);
	m_ledUnloadPicker2IO[14].Set_On(pDX10->iUnloadPicker2Down7);
	m_ledUnloadPicker2IO[15].Set_On(pDX10->iUnloadPicker2Down8);

	m_ledUnloadPicker2IO[16].Set_On(pDX10->iUnloadPicker2Open1);
	m_ledUnloadPicker2IO[17].Set_On(pDX10->iUnloadPicker2Open2);
	m_ledUnloadPicker2IO[18].Set_On(pDX10->iUnloadPicker2Open3);
	m_ledUnloadPicker2IO[19].Set_On(pDX10->iUnloadPicker2Open4);
	m_ledUnloadPicker2IO[20].Set_On(pDX10->iUnloadPicker2Open5);
	m_ledUnloadPicker2IO[21].Set_On(pDX10->iUnloadPicker2Open6);
	m_ledUnloadPicker2IO[22].Set_On(pDX10->iUnloadPicker2Open7);
	m_ledUnloadPicker2IO[23].Set_On(pDX10->iUnloadPicker2Open8);

	m_ledUnloadPicker2IO[24].Set_On(pDX10->iUnloadPicker2Exist1);
	m_ledUnloadPicker2IO[25].Set_On(pDX10->iUnloadPicker2Exist2);
	m_ledUnloadPicker2IO[26].Set_On(pDX10->iUnloadPicker2Exist3);
	m_ledUnloadPicker2IO[27].Set_On(pDX10->iUnloadPicker2Exist4);
	m_ledUnloadPicker2IO[28].Set_On(pDX10->iUnloadPicker2Exist5);
	m_ledUnloadPicker2IO[29].Set_On(pDX10->iUnloadPicker2Exist6);
	m_ledUnloadPicker2IO[30].Set_On(pDX10->iUnloadPicker2Exist7);
	m_ledUnloadPicker2IO[31].Set_On(pDX10->iUnloadPicker2Exist8);
}

///////////////////////////////////////////////////////////////////////////////
void CManualUnloadDlg::OnBtnUnloadPicker1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_X1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER1_X_0 + 1;

	// Interlock
	if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0)) {
		AfxMessageBox(_T("Unload Picker1 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	// Y축이 둘다 준비위치가 아닐때
	if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, 0) && !g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, 0)) {
		AfxMessageBox(_T("Unload Picker1/2 Y축 모두 Ready 위치가 아닙니다....."));
		return;
	}
	if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, 0) && !g_objCommon.Get_UnloadPickerUp(1)) {
		AfxMessageBox(_T("Unload Picker1 Picker Up 위치가 아닙니다....."));
		return;
	}

	if (nIndex == 17 || nIndex == 18) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 17 ? -1 : 1);
		double dMove = pEquipData->dTrayPitchX * nDir;
		g_objAJinAXL.Move_Relative(AX_UNLOAD_PICKER_X1, dMove);
	} else {
		g_objCommon.Move_Position(AX_UNLOAD_PICKER_X1, nIndex);
	}

	m_strLog.Format("[Manual Unload] Unload Picker1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_Y1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER1_Y_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0)) {
		AfxMessageBox(_T("Unload Picker1 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	if (!g_objCommon.Get_UnloadPickerUp(1)) {
		AfxMessageBox(_T("Unload Picker1 Picker Up 위치가 아닙니다....."));
		return;
	}
	if (nIndex != 0) {
		double dCurPosX1 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X1);
		double dCurPosX2 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X2);
		if (dCurPosX1 >= dCurPosX2 && ((dCurPosX1 - dCurPosX2) < 400)) {
			AfxMessageBox(_T("Unload Picker2 X축의 Interlock 위치가 아닙니다....."));
			return;
		}
		if (dCurPosX1 <= dCurPosX2 && ((dCurPosX2 - dCurPosX1) < 400)) {
			AfxMessageBox(_T("Unload Picker2 X축의 Interlock 위치가 아닙니다....."));
			return;
		}
	}	

	g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y1, nIndex);

	m_strLog.Format("[Manual Unload] Unload Picker1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_Z1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER1_Z_0;

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	double dCurPosX1 = 0.0, dPicker1WorkPosS = 0.0, dPicker1WorkPosE = 0.0;

	// Interlock
	if (nIndex != 0 && !g_objCommon.Check_Position(AX_UNLOAD_PICKER_X1, nIndex)) {
		if (nIndex == 1) { AfxMessageBox(_T("Unload Picker1 X축이 Stage1 위치가 아닙니다.....")); return; }
		if (nIndex == 2) { AfxMessageBox(_T("Unload Picker1 X축이 Stage2 위치가 아닙니다.....")); return; }
		if (nIndex == 3) { AfxMessageBox(_T("Unload Picker1 X축이 Stage3 위치가 아닙니다.....")); return; }
		if (nIndex == 4) { AfxMessageBox(_T("Unload Picker1 X축이 Stage4 위치가 아닙니다.....")); return; }

		if (nIndex == 5) {
			dCurPosX1 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X1);
			dPicker1WorkPosS = pMoveData->dUnloadPickerX1[5] - pEquipData->dTrayPitchX * 3.0 - 0.1;	// 1번 Picker가 Tray 4번 위치까지
			dPicker1WorkPosE = pMoveData->dUnloadPickerX1[5] + pEquipData->dTrayPitchX * 7.0 + 0.1;	// 8번 Picker가 Tray 1번 위치까지
			if ( !((dPicker1WorkPosS < dCurPosX1) && (dCurPosX1 < dPicker1WorkPosE)) ) {
				AfxMessageBox(_T("Unload Picker1 X축이 NG Tray1 위치가 아닙니다.....")); return;
			}
		}
		if (nIndex == 6) {
			dCurPosX1 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X1);
			dPicker1WorkPosS = pMoveData->dUnloadPickerX1[6] - pEquipData->dTrayPitchX * 3.0 - 0.1;	// 1번 Picker가 Tray 4번 위치까지
			dPicker1WorkPosE = pMoveData->dUnloadPickerX1[6] + pEquipData->dTrayPitchX * 7.0 + 0.1;	// 8번 Picker가 Tray 1번 위치까지
			if ( !((dPicker1WorkPosS < dCurPosX1) && (dCurPosX1 < dPicker1WorkPosE)) ) {
				AfxMessageBox(_T("Unload Picker1 X축이 NG Tray2 위치가 아닙니다.....")); return;
			}
		}
		if (nIndex == 7) {
			dCurPosX1 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X1);
			dPicker1WorkPosS = pMoveData->dUnloadPickerX1[7] - pEquipData->dTrayPitchX * 3.0 - 0.1;	// 1번 Picker가 Tray 4번 위치까지
			dPicker1WorkPosE = pMoveData->dUnloadPickerX1[7] + pEquipData->dTrayPitchX * 7.0 + 0.1;	// 8번 Picker가 Tray 1번 위치까지
			if ( !((dPicker1WorkPosS < dCurPosX1) && (dCurPosX1 < dPicker1WorkPosE)) ) {
				AfxMessageBox(_T("Unload Picker1 X축이 Good Tray1 위치가 아닙니다.....")); return; 
			}
		}
		if (nIndex == 8) {
			dCurPosX1 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X1);
			dPicker1WorkPosS = pMoveData->dUnloadPickerX1[8] - pEquipData->dTrayPitchX * 3.0 - 0.1;	// 1번 Picker가 Tray 4번 위치까지
			dPicker1WorkPosE = pMoveData->dUnloadPickerX1[8] + pEquipData->dTrayPitchX * 7.0 + 0.1;	// 8번 Picker가 Tray 1번 위치까지
			if ( !((dPicker1WorkPosS < dCurPosX1) && (dCurPosX1 < dPicker1WorkPosE)) ) {
				AfxMessageBox(_T("Unload Picker1 X축이 Good Tray2 위치가 아닙니다.....")); return;
			}
		}
	}	
	if (nIndex != 0) {
		if (!g_objCommon.Get_UnloadPickerUp(1, 0) && !g_objCommon.Get_UnloadPickerOpen(1, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
	}

	g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z1, nIndex);

	m_strLog.Format("[Manual Unload] Unload Picker1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker1PClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_P1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER1_P_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0)) {
		AfxMessageBox(_T("Unload Picker1 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}

	g_objCommon.Move_Position(AX_UNLOAD_PICKER_P1, nIndex);

	m_strLog.Format("[Manual Unload] Unload Picker1 P (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker1IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER1_IO_0;

	if (nIndex >= 0 && nIndex < 8) {
		g_objCommon.Set_UnloadPickerUp(1, nIndex+1);
	}

	if (nIndex >= 8 && nIndex < 16){
		if (g_objCommon.Get_UnloadPickerClose(1, nIndex-7) && !g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
		g_objCommon.Set_UnloadPickerDown(1, nIndex-7);
	}

	if (nIndex >= 16 && nIndex < 24) {
		g_objCommon.Set_UnloadPickerOpen(1, nIndex-15);
	}

	if (nIndex >= 24 && nIndex < 32) {
		g_objCommon.Set_UnloadPickerClose(1, nIndex-23);
	}

	if (nIndex == 32) g_objCommon.Set_UnloadPickerUp(1, 0);
	if (nIndex == 33) {
		if (!g_objCommon.Get_UnloadPickerOpen(1, 0) && !g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z1, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
		g_objCommon.Set_UnloadPickerDown(1, 0);
	}
	if (nIndex == 34) g_objCommon.Set_UnloadPickerOpen(1, 0);
	if (nIndex == 35) g_objCommon.Set_UnloadPickerClose(1, 0);

	m_strLog.Format("[Manual Unload] Unload Picker1 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_X2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER2_X_0 + 1;

	// Interlock
	if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0)) {
		AfxMessageBox(_T("Unload Picker2 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	// Y축이 둘다 준비위치가 아닐때
	if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y1, 0) && !g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, 0)) {
		AfxMessageBox(_T("Unload Picker1/2 Y축 모두 Ready 위치가 아닙니다....."));
		return;
	}
	if (g_objCommon.Check_Position(AX_UNLOAD_PICKER_Y2, 0) && !g_objCommon.Get_UnloadPickerUp(2)) {
		AfxMessageBox(_T("Unload Picker2 Picker Up 위치가 아닙니다....."));
		return;
	}

	if (nIndex == 17 || nIndex == 18) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 17 ? -1 : 1);
		double dMove = pEquipData->dTrayPitchX * nDir;
		g_objAJinAXL.Move_Relative(AX_UNLOAD_PICKER_X2, dMove);
	} else {
		g_objCommon.Move_Position(AX_UNLOAD_PICKER_X2, nIndex);
	}

	m_strLog.Format("[Manual Unload] Unload Picker2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_Y2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER2_Y_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0)) {
		AfxMessageBox(_T("Unload Picker2 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}
	if (!g_objCommon.Get_UnloadPickerUp(2)) {
		AfxMessageBox(_T("Unload Picker2 Picker Up 위치가 아닙니다....."));
		return;
	}
	if (nIndex != 0) {
		double dCurPosX1 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X1);
		double dCurPosX2 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X2);
		if (dCurPosX1 >= dCurPosX2 && ((dCurPosX1 - dCurPosX2) < 400)) {
			AfxMessageBox(_T("Unload Picker1 X축의 Interlock 위치가 아닙니다....."));
			return;
		}
		if (dCurPosX1 <= dCurPosX2 && ((dCurPosX2 - dCurPosX1) < 400)) {
			AfxMessageBox(_T("Unload Picker1 X축의 Interlock 위치가 아닙니다....."));
			return;
		}
	}	

	g_objCommon.Move_Position(AX_UNLOAD_PICKER_Y2, nIndex);

	m_strLog.Format("[Manual Unload] Unload Picker2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_Z2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER2_Z_0;

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	double dCurPosX2 = 0.0, dPicker2WorkPosS = 0.0, dPicker2WorkPosE = 0.0;

	// Interlock
	if (nIndex != 0 && !g_objCommon.Check_Position(AX_UNLOAD_PICKER_X2, nIndex)) {
		if (nIndex == 1) { AfxMessageBox(_T("Unload Picker2 X축이 Stage1 위치가 아닙니다.....")); return; }
		if (nIndex == 2) { AfxMessageBox(_T("Unload Picker2 X축이 Stage2 위치가 아닙니다.....")); return; }
		if (nIndex == 3) { AfxMessageBox(_T("Unload Picker2 X축이 Stage3 위치가 아닙니다.....")); return; }
		if (nIndex == 4) { AfxMessageBox(_T("Unload Picker2 X축이 Stage4 위치가 아닙니다.....")); return; }
		
		if (nIndex == 5) {
			dCurPosX2 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X2);
			dPicker2WorkPosS = pMoveData->dUnloadPickerX2[5] - pEquipData->dTrayPitchX * 3.0 - 0.1;	// 1번 Picker가 Tray 4번 위치까지
			dPicker2WorkPosE = pMoveData->dUnloadPickerX2[5] + pEquipData->dTrayPitchX * 7.0 + 0.1;	// 8번 Picker가 Tray 1번 위치까지
			if ( !((dPicker2WorkPosS < dCurPosX2) && (dCurPosX2 < dPicker2WorkPosE)) ) {
				AfxMessageBox(_T("Unload Picker2 X축이 NG Tray1 위치가 아닙니다.....")); return;
			}
		}
		if (nIndex == 6) {
			dCurPosX2 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X2);
			dPicker2WorkPosS = pMoveData->dUnloadPickerX2[6] - pEquipData->dTrayPitchX * 3.0 - 0.1;	// 1번 Picker가 Tray 4번 위치까지
			dPicker2WorkPosE = pMoveData->dUnloadPickerX2[6] + pEquipData->dTrayPitchX * 7.0 + 0.1;	// 8번 Picker가 Tray 1번 위치까지
			if ( !((dPicker2WorkPosS < dCurPosX2) && (dCurPosX2 < dPicker2WorkPosE)) ) {
				AfxMessageBox(_T("Unload Picker2 X축이 NG Tray2 위치가 아닙니다.....")); return;
			}
		}
		if (nIndex == 7) {
			dCurPosX2 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X2);
			dPicker2WorkPosS = pMoveData->dUnloadPickerX2[7] - pEquipData->dTrayPitchX * 3.0 - 0.1;	// 1번 Picker가 Tray 4번 위치까지
			dPicker2WorkPosE = pMoveData->dUnloadPickerX2[7] + pEquipData->dTrayPitchX * 7.0 + 0.1;	// 8번 Picker가 Tray 1번 위치까지
			if ( !((dPicker2WorkPosS < dCurPosX2) && (dCurPosX2 < dPicker2WorkPosE)) ) {
				AfxMessageBox(_T("Unload Picker2 X축이 Good Tray1 위치가 아닙니다.....")); return; 
			}
		}
		if (nIndex == 8) {
			dCurPosX2 = g_objAJinAXL.Get_Position(AX_UNLOAD_PICKER_X2);
			dPicker2WorkPosS = pMoveData->dUnloadPickerX2[8] - pEquipData->dTrayPitchX * 3.0 - 0.1;	// 1번 Picker가 Tray 4번 위치까지
			dPicker2WorkPosE = pMoveData->dUnloadPickerX2[8] + pEquipData->dTrayPitchX * 7.0 + 0.1;	// 8번 Picker가 Tray 1번 위치까지
			if ( !((dPicker2WorkPosS < dCurPosX2) && (dCurPosX2 < dPicker2WorkPosE)) ) {
				AfxMessageBox(_T("Unload Picker2 X축이 Good Tray2 위치가 아닙니다.....")); return;
			}
		}
	}	
	if (nIndex != 0) {
		if (!g_objCommon.Get_UnloadPickerUp(2, 0) && !g_objCommon.Get_UnloadPickerOpen(2, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
	}

	g_objCommon.Move_Position(AX_UNLOAD_PICKER_Z2, nIndex);

	m_strLog.Format("[Manual Unload] Unload Picker2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker2PClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_UNLOAD_PICKER_P2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER2_P_0;

	// Interlock
	if (!g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0)) {
		AfxMessageBox(_T("Unload Picker2 Z축 Ready Up 위치가 아닙니다....."));
		return;
	}

	g_objCommon.Move_Position(AX_UNLOAD_PICKER_P2, nIndex);

	m_strLog.Format("[Manual Unload] Unload Picker2 P (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnUnloadPicker2IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_PICKER2_IO_0;

	if (nIndex >= 0 && nIndex < 8) {
		g_objCommon.Set_UnloadPickerUp(2, nIndex+1);
	}

	if (nIndex >= 8 && nIndex < 16){
		if (g_objCommon.Get_UnloadPickerClose(2, nIndex-7) && !g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
		g_objCommon.Set_UnloadPickerDown(2, nIndex-7);
	}

	if (nIndex >= 16 && nIndex < 24) {
		g_objCommon.Set_UnloadPickerOpen(2, nIndex-15);
	}

	if (nIndex >= 24 && nIndex < 32) {
		g_objCommon.Set_UnloadPickerClose(2, nIndex-23);
	}

	if (nIndex == 32) g_objCommon.Set_UnloadPickerUp(2, 0);
	if (nIndex == 33) {
		if (!g_objCommon.Get_UnloadPickerOpen(2, 0) && !g_objCommon.Check_Position(AX_UNLOAD_PICKER_Z2, 0)) {
			if (g_objCommon.Show_MsgBox(2, "Picker Close 상태입니다. Down 하시겠습니까?") != IDOK) return;
		}
		g_objCommon.Set_UnloadPickerDown(2, 0);
	}
	if (nIndex == 34) g_objCommon.Set_UnloadPickerOpen(2, 0);
	if (nIndex == 35) g_objCommon.Set_UnloadPickerClose(2, 0);

	m_strLog.Format("[Manual Unload] Unload Picker2 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnGoodStage1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_GOOD_STAGE_Y1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_GOOD_STAGE1_Y_0;

	DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();

	// Interlock
	if ((pDX12->iGoodStage1Up && pDX12->iGoodStage2Up) || (pDX12->iGoodStage1Down && pDX12->iGoodStage2Down) ) {
		AfxMessageBox(_T("Good Stage 1/2 같은 높이에 있습니다....."));
		return;
	}
	if (!pDX12->iGoodStage1Up && !pDX12->iGoodStage1Down) {
		AfxMessageBox(_T("Good Stage1 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}
	if (!pDX12->iGoodStage2Up && !pDX12->iGoodStage2Down) {
		AfxMessageBox(_T("Load Stage2 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}

	if (nIndex == 6 || nIndex == 7) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 6 ? 1 : -1);
		double dMove = pEquipData->dTrayPitchY * nDir;
		g_objAJinAXL.Move_Relative(AX_GOOD_STAGE_Y1, dMove);
	} else {
		g_objCommon.Move_Position(AX_GOOD_STAGE_Y1, nIndex);
	}

	m_strLog.Format("[Manual Unload] Good Stage1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnGoodStage1IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_GOOD_STAGE1_IO_0;

	DY_DATA_12 *pDY12 = g_objAJinAXL.Get_pDY12();

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	double dCurPosY1 = g_objAJinAXL.Get_Position(AX_GOOD_STAGE_Y1);
	double dCurPosY2 = g_objAJinAXL.Get_Position(AX_GOOD_STAGE_Y2);
	double dTray1WorkPosS = pMoveData->dGoodStageY1[3] - 0.1;
	double dTray1WorkPosE = pMoveData->dGoodStageY1[3] + pEquipData->dTrayPitchY * 9.0 + 0.1;
	double dTray2WorkPosS = pMoveData->dGoodStageY2[3] - 0.1;
	double dTray2WorkPosE = pMoveData->dGoodStageY2[3] + pEquipData->dTrayPitchY * 9.0 + 0.1;

	// Interlock
	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 1) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 2) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE)) ) {
			AfxMessageBox(_T("Good Stage1 Y축 Tray Load/Align/Wait/Tray(1x1) 위치가 아닙니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 0)) {
			if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 1) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 2) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) ){
				AfxMessageBox(_T("Good Stage2 Y축 Wait/Unload/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 1)) {
			if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 2) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) ){
				AfxMessageBox(_T("Good Stage2 Y축 Load/Unload/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 2)) {
			if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 1) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) ){
				AfxMessageBox(_T("Good Stage2 Y축 Load/Wait/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if ((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE)) {
			if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 1) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 2)){
				AfxMessageBox(_T("Good Stage2 Y축 Load/Wait/Unload 위치가 아닙니다....."));
				return;
			}
		}
		if (nIndex == 0) { pDY12->oGoodStage1Up = TRUE;  pDY12->oGoodStage1Down = FALSE; }
		if (nIndex == 1) { pDY12->oGoodStage1Up = FALSE; pDY12->oGoodStage1Down = TRUE; }

	} else {
		if (nIndex == 2) { pDY12->oGoodStage1MasterIn = TRUE;  pDY12->oGoodStage1MasterOut = FALSE; }
		if (nIndex == 3) { pDY12->oGoodStage1MasterIn = FALSE; pDY12->oGoodStage1MasterOut = TRUE; }
		if (nIndex == 4) { pDY12->oGoodStage1SlaveIn = TRUE;   pDY12->oGoodStage1SlaveOut = FALSE; }
		if (nIndex == 5) { pDY12->oGoodStage1SlaveIn = FALSE;  pDY12->oGoodStage1SlaveOut = TRUE; }
	}

	g_objAJinAXL.Write_Output(12);

	m_strLog.Format("[Manual Unload] Good Stage1 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnGoodStage2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_GOOD_STAGE_Y2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_GOOD_STAGE2_Y_0;

	DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();

	// Interlock
	if ((pDX12->iGoodStage1Up && pDX12->iGoodStage2Up) || (pDX12->iGoodStage1Down && pDX12->iGoodStage2Down) ) {
		AfxMessageBox(_T("Good Stage 1/2 같은 높이에 있습니다....."));
		return;
	}
	if (!pDX12->iGoodStage1Up && !pDX12->iGoodStage1Down) {
		AfxMessageBox(_T("Good Stage1 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}
	if (!pDX12->iGoodStage2Up && !pDX12->iGoodStage2Down) {
		AfxMessageBox(_T("Load Stage2 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}

	if (nIndex == 6 || nIndex == 7) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 6 ? 1 : -1);
		double dMove = pEquipData->dTrayPitchY * nDir;
		g_objAJinAXL.Move_Relative(AX_GOOD_STAGE_Y2, dMove);
	} else {
		g_objCommon.Move_Position(AX_GOOD_STAGE_Y2, nIndex);
	}

	m_strLog.Format("[Manual Unload] Good Stage2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnGoodStage2IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_GOOD_STAGE2_IO_0;

	DY_DATA_12 *pDY12 = g_objAJinAXL.Get_pDY12();

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	double dCurPosY1 = g_objAJinAXL.Get_Position(AX_GOOD_STAGE_Y1);
	double dCurPosY2 = g_objAJinAXL.Get_Position(AX_GOOD_STAGE_Y2);
	double dTray1WorkPosS = pMoveData->dGoodStageY1[3] - 0.1;
	double dTray1WorkPosE = pMoveData->dGoodStageY1[3] + pEquipData->dTrayPitchY * 9.0 + 0.1;
	double dTray2WorkPosS = pMoveData->dGoodStageY2[3] - 0.1;
	double dTray2WorkPosE = pMoveData->dGoodStageY2[3] + pEquipData->dTrayPitchY * 9.0 + 0.1;

	// Interlock
	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 1) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 2) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) ) {
			AfxMessageBox(_T("Good Stage2 Y축 Tray Load/Align/Wait/Tray(1x1) 위치가 아닙니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 0)) {
			if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 1) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 2) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE))){
				AfxMessageBox(_T("Good Stage1 Y축 Wait/Unload/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 1)) {
			if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 2) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE))){
				AfxMessageBox(_T("Good Stage1 Y축 Load/Unload/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_GOOD_STAGE_Y2, 2)) {
			if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 1) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE))){
				AfxMessageBox(_T("Good Stage1 Y축 Load/Wait/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if ((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) {
			if (!g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 1) && !g_objCommon.Check_Position(AX_GOOD_STAGE_Y1, 2)){
				AfxMessageBox(_T("Good Stage1 Y축 Load/Wait/Unload 위치가 아닙니다....."));
				return;
			}
		}
		if (nIndex == 0) { pDY12->oGoodStage2Up = TRUE;  pDY12->oGoodStage2Down = FALSE; }
		if (nIndex == 1) { pDY12->oGoodStage2Up = FALSE; pDY12->oGoodStage2Down = TRUE; }

	} else {
		if (nIndex == 2) { pDY12->oGoodStage2MasterIn = TRUE;  pDY12->oGoodStage2MasterOut = FALSE; }
		if (nIndex == 3) { pDY12->oGoodStage2MasterIn = FALSE; pDY12->oGoodStage2MasterOut = TRUE; }
		if (nIndex == 4) { pDY12->oGoodStage2SlaveIn = TRUE;   pDY12->oGoodStage2SlaveOut = FALSE; }
		if (nIndex == 5) { pDY12->oGoodStage2SlaveIn = FALSE;  pDY12->oGoodStage2SlaveOut = TRUE; }
	}

	g_objAJinAXL.Write_Output(12);

	m_strLog.Format("[Manual Unload] Good Stage2 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnNGStage1YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_STAGE_Y1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_NG_STAGE1_Y_0;

	DX_DATA_11 *pDX11 = g_objAJinAXL.Get_pDX11();

	// Interlock
	if ((pDX11->iNGStage1Up && pDX11->iNGStage2Up) || (pDX11->iNGStage1Down && pDX11->iNGStage2Down) ) {
		AfxMessageBox(_T("NG Stage 1/2 같은 높이에 있습니다....."));
		return;
	}
	if (!pDX11->iNGStage1Up && !pDX11->iNGStage1Down) {
		AfxMessageBox(_T("NG Stage1 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}
	if (!pDX11->iNGStage2Up && !pDX11->iNGStage2Down) {
		AfxMessageBox(_T("NG Stage2 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}

	if (nIndex == 6 || nIndex == 7) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 6 ? 1 : -1);
		double dMove = pEquipData->dTrayPitchY * nDir;
		g_objAJinAXL.Move_Relative(AX_NG_STAGE_Y1, dMove);
	} else {
		g_objCommon.Move_Position(AX_NG_STAGE_Y1, nIndex);
	}

	m_strLog.Format("[Manual Unload] NG Stage1 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnNGStage1IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_NG_STAGE1_IO_0;

	DY_DATA_11 *pDY11 = g_objAJinAXL.Get_pDY11();

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	double dCurPosY1 = g_objAJinAXL.Get_Position(AX_NG_STAGE_Y1);
	double dCurPosY2 = g_objAJinAXL.Get_Position(AX_NG_STAGE_Y2);
	double dTray1WorkPosS = pMoveData->dNGStageY1[3] - 0.1;
	double dTray1WorkPosE = pMoveData->dNGStageY1[3] + pEquipData->dTrayPitchY * 9.0 + 0.1;
	double dTray2WorkPosS = pMoveData->dNGStageY2[3] - 0.1;
	double dTray2WorkPosE = pMoveData->dNGStageY2[3] + pEquipData->dTrayPitchY * 9.0 + 0.1;

	// Interlock
	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_NG_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_NG_STAGE_Y1, 1) && !g_objCommon.Check_Position(AX_NG_STAGE_Y1, 2) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE))) {
			AfxMessageBox(_T("NG Stage1 Y축 Tray Load/Align/Wait/Tray(1x1) 위치가 아닙니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_NG_STAGE_Y1, 0)) {
			if (!g_objCommon.Check_Position(AX_NG_STAGE_Y2, 1) && !g_objCommon.Check_Position(AX_NG_STAGE_Y2, 2) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE))){
				AfxMessageBox(_T("NG Stage2 Y축 Align/Wait/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_NG_STAGE_Y1, 1)) {
			if (!g_objCommon.Check_Position(AX_NG_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_NG_STAGE_Y2, 2) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE))){
				AfxMessageBox(_T("NG Stage2 Y축 Tray Load/Wait/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_NG_STAGE_Y1, 2)) {
			if (!g_objCommon.Check_Position(AX_NG_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_NG_STAGE_Y2, 1) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE))){
				AfxMessageBox(_T("NG Stage2 Y축 Tray Load/Align/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if ((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE)) {
			if (!g_objCommon.Check_Position(AX_NG_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_NG_STAGE_Y2, 1) && !g_objCommon.Check_Position(AX_NG_STAGE_Y2, 2)){
				AfxMessageBox(_T("NG Stage2 Y축 Tray Load/Align/Wait 위치가 아닙니다....."));
				return;
			}
		}
		if (nIndex == 0) { pDY11->oNGStage1Up = TRUE;  pDY11->oNGStage1Down = FALSE; }
		if (nIndex == 1) { pDY11->oNGStage1Up = FALSE; pDY11->oNGStage1Down = TRUE; }

	} else {
		if (nIndex == 2) { pDY11->oNGStage1MasterIn = TRUE;  pDY11->oNGStage1MasterOut = FALSE; }
		if (nIndex == 3) { pDY11->oNGStage1MasterIn = FALSE; pDY11->oNGStage1MasterOut = TRUE; }
		if (nIndex == 4) { pDY11->oNGStage1SlaveIn = TRUE;   pDY11->oNGStage1SlaveOut = FALSE; }
		if (nIndex == 5) { pDY11->oNGStage1SlaveIn = FALSE;  pDY11->oNGStage1SlaveOut = TRUE; }
	}

	g_objAJinAXL.Write_Output(11);

	m_strLog.Format("[Manual Unload] NG Stage1 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnNGStage2YClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_NG_STAGE_Y2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_NG_STAGE2_Y_0;

	DX_DATA_11 *pDX11 = g_objAJinAXL.Get_pDX11();

	// Interlock
	if ((pDX11->iNGStage1Up && pDX11->iNGStage2Up) || (pDX11->iNGStage1Down && pDX11->iNGStage2Down) ) {
		AfxMessageBox(_T("NG Stage 1/2 같은 높이에 있습니다....."));
		return;
	}
	if (!pDX11->iNGStage1Up && !pDX11->iNGStage1Down) {
		AfxMessageBox(_T("NG Stage1 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}
	if (!pDX11->iNGStage2Up && !pDX11->iNGStage2Down) {
		AfxMessageBox(_T("NG Stage2 Up/Down 센서 감지 되지 않습니다....."));
		return;
	}

	if (nIndex == 6 || nIndex == 7) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 6 ? 1 : -1);
		double dMove = pEquipData->dTrayPitchY * nDir;
		g_objAJinAXL.Move_Relative(AX_NG_STAGE_Y2, dMove);
	} else {
		g_objCommon.Move_Position(AX_NG_STAGE_Y2, nIndex);
	}

	m_strLog.Format("[Manual Unload] NG Stage2 Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualUnloadDlg::OnBtnNGStage2IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_NG_STAGE2_IO_0;

	DY_DATA_11 *pDY11 = g_objAJinAXL.Get_pDY11();

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	double dCurPosY1 = g_objAJinAXL.Get_Position(AX_NG_STAGE_Y1);
	double dCurPosY2 = g_objAJinAXL.Get_Position(AX_NG_STAGE_Y2);
	double dTray1WorkPosS = pMoveData->dNGStageY1[3] - 0.1;
	double dTray1WorkPosE = pMoveData->dNGStageY1[3] + pEquipData->dTrayPitchY * 9.0 + 0.1;
	double dTray2WorkPosS = pMoveData->dNGStageY2[3] - 0.1;
	double dTray2WorkPosE = pMoveData->dNGStageY2[3] + pEquipData->dTrayPitchY * 9.0 + 0.1;

	// Interlock
	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_NG_STAGE_Y2, 0) && !g_objCommon.Check_Position(AX_NG_STAGE_Y2, 1) && !g_objCommon.Check_Position(AX_NG_STAGE_Y2, 2) && !((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) ) {
			AfxMessageBox(_T("NG Stage2 Y축 Tray Load/Align/Wait/Tray(1x1) 위치가 아닙니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_NG_STAGE_Y2, 0)) {
			if (!g_objCommon.Check_Position(AX_NG_STAGE_Y1, 1) && !g_objCommon.Check_Position(AX_NG_STAGE_Y1, 2) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE))){
				AfxMessageBox(_T("NG Stage1 Y축 Align/Wait/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_NG_STAGE_Y2, 1)) {
			if (!g_objCommon.Check_Position(AX_NG_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_NG_STAGE_Y1, 2) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE))){
				AfxMessageBox(_T("NG Stage1 Y축 Tray Load/Wait/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_NG_STAGE_Y2, 2)) {
			if (!g_objCommon.Check_Position(AX_NG_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_NG_STAGE_Y1, 1) && !((dTray1WorkPosS < dCurPosY1) && (dCurPosY1 < dTray1WorkPosE))){
				AfxMessageBox(_T("NG Stage1 Y축 Tray Load/Align/Tray(1x1) 위치가 아닙니다....."));
				return;
			}
		}
		if ((dTray2WorkPosS < dCurPosY2) && (dCurPosY2 < dTray2WorkPosE)) {
			if (!g_objCommon.Check_Position(AX_NG_STAGE_Y1, 0) && !g_objCommon.Check_Position(AX_NG_STAGE_Y1, 1) && !g_objCommon.Check_Position(AX_NG_STAGE_Y1, 2)){
				AfxMessageBox(_T("NG Stage1 Y축 Tray Load/Align/Wait 위치가 아닙니다....."));
				return;
			}
		}
		if (nIndex == 0) { pDY11->oNGStage2Up = TRUE;  pDY11->oNGStage2Down = FALSE; }
		if (nIndex == 1) { pDY11->oNGStage2Up = FALSE; pDY11->oNGStage2Down = TRUE; }

	} else {
		if (nIndex == 2) { pDY11->oNGStage2MasterIn = TRUE;  pDY11->oNGStage2MasterOut = FALSE; }
		if (nIndex == 3) { pDY11->oNGStage2MasterIn = FALSE; pDY11->oNGStage2MasterOut = TRUE; }
		if (nIndex == 4) { pDY11->oNGStage2SlaveIn = TRUE;   pDY11->oNGStage2SlaveOut = FALSE; }
		if (nIndex == 5) { pDY11->oNGStage2SlaveIn = FALSE;  pDY11->oNGStage2SlaveOut = TRUE; }
	}

	g_objAJinAXL.Write_Output(11);

	m_strLog.Format("[Manual Unload] NG Stage2 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualUnloadDlg::OnBtnUnloadVisionXClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SHIP_ALIGN_X)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_UNLOAD_VISION_X_0;

	g_objCommon.Move_Position(AX_SHIP_ALIGN_X, nIndex);

	m_strLog.Format("[Manual Unload] Unload Ship Vision X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
