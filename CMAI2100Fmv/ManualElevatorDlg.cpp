// ManualElevatorDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualElevatorDlg.h"
#include "afxdialogex.h"
#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"

// CManualElevatorDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualElevatorDlg, CDialogEx)

CManualElevatorDlg::CManualElevatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualElevatorDlg::IDD, pParent)
{
}

CManualElevatorDlg::~CManualElevatorDlg()
{
}

void CManualElevatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i <20; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_LOAD1_ELEVATOR_Z_0 + i, m_btnLoad1ElevatorZ[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_LOAD1_ELEVATOR_IO_0 + i, m_btnLoad1ElevatorIO[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_LOAD2_ELEVATOR_Z_0 + i, m_btnLoad2ElevatorZ[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_LOAD2_ELEVATOR_IO_0 + i, m_btnLoad2ElevatorIO[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_NG_EMPTY_Z_0 + i, m_btnNGEmptyElevatorZ[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_NG_EMPTY_IO_0 + i, m_btnNGEmptyElevatorIO[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_GOOD_EMPTY_Z_0 + i, m_btnGoodEmptyElevatorZ[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_GOOD_EMPTY_IO_0 + i, m_btnGoodEmptyElevatorIO[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_NG_BUFFER_Z_0 + i, m_btnNGBufferElevatorZ[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_NG_BUFFER_IO_0 + i, m_btnNGBufferElevatorIO[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_GOOD1_ELEVATOR_Z_0 + i, m_btnGood1ElevatorZ[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_GOOD1_ELEVATOR_IO_0 + i, m_btnGood1ElevatorIO[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_GOOD2_ELEVATOR_Z_0 + i, m_btnGood2ElevatorZ[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_GOOD2_ELEVATOR_IO_0 + i, m_btnGood2ElevatorIO[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_TRAY_TRANSFER1_X_0 + i, m_btnTrayTrans1X[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_BTN_TRAY_TRANSFER1_Z_0 + i, m_btnTrayTrans1Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_TRAY_TRANSFER1_IO_0 + i, m_btnTrayTrans1IO[i]);
	for (int i = 0; i <13; i++) DDX_Control(pDX, IDC_BTN_TRAY_TRANSFER2_X_0 + i, m_btnTrayTrans2X[i]);
	for (int i = 0; i <15; i++) DDX_Control(pDX, IDC_BTN_TRAY_TRANSFER2_Z_0 + i, m_btnTrayTrans2Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_TRAY_TRANSFER2_IO_0 + i, m_btnTrayTrans2IO[i]);
	

	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_LED_LOAD1_ELEVATOR_IO_0 + i, m_ledLoad1Elevator[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_LED_LOAD2_ELEVATOR_IO_0 + i, m_ledLoad2Elevator[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_LED_NG_EMPTY_IO_0 + i, m_ledNGEmptyElevator[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_LED_GOOD_EMPTY_IO_0 + i, m_ledGoodEmptyElevator[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_LED_NG_BUFFER_IO_0 + i, m_ledNGBufferElevator[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_LED_GOOD1_ELEVATOR_IO_0 + i, m_ledGood1Elevator[i]);
	for (int i = 0; i <11; i++) DDX_Control(pDX, IDC_LED_GOOD2_ELEVATOR_IO_0 + i, m_ledGood2Elevator[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_LED_TRAY_TRANS_IO_0 + i, m_ledTrayTrans1[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_LED_TRAY_TRANS2_IO_0 + i, m_ledTrayTrans2[i]);
}

BEGIN_MESSAGE_MAP(CManualElevatorDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD1_ELEVATOR_Z_0, IDC_BTN_LOAD1_ELEVATOR_Z_1, OnbtnLoad1ElevatorZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD1_ELEVATOR_IO_0, IDC_BTN_LOAD1_ELEVATOR_IO_3, OnbtnLoad1ElevatorIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD2_ELEVATOR_Z_0, IDC_BTN_LOAD2_ELEVATOR_Z_1, OnbtnLoad2ElevatorZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_LOAD2_ELEVATOR_IO_0, IDC_BTN_LOAD2_ELEVATOR_IO_3, OnbtnLoad2ElevatorIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_EMPTY_Z_0, IDC_BTN_NG_EMPTY_Z_1, OnbtnNGEmptyElevatorZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_EMPTY_IO_0, IDC_BTN_NG_EMPTY_IO_3,OnbtnNGEmptyElevatorIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_EMPTY_Z_0, IDC_BTN_GOOD_EMPTY_Z_1, OnbtnGoodEmptyElevatorZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD_EMPTY_IO_0, IDC_BTN_GOOD_EMPTY_IO_3, OnbtnGoodEmptyElevatorIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_BUFFER_Z_0, IDC_BTN_NG_BUFFER_Z_1, OnbtnNGBufferElevatorZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_NG_BUFFER_IO_0, IDC_BTN_NG_BUFFER_IO_3, OnbtnNGBufferElevatorIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD1_ELEVATOR_Z_0, IDC_BTN_GOOD1_ELEVATOR_Z_1, OnbtnGood1ElevatorZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD1_ELEVATOR_IO_0, IDC_BTN_GOOD1_ELEVATOR_IO_3, OnbtnGood1ElevatorIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD2_ELEVATOR_Z_0, IDC_BTN_GOOD2_ELEVATOR_Z_1, OnbtnGood2ElevatorZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_GOOD2_ELEVATOR_IO_0, IDC_BTN_GOOD2_ELEVATOR_IO_3, OnbtnGood2ElevatorIOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRAY_TRANSFER1_X_0, IDC_BTN_TRAY_TRANSFER1_X_7, OnbtnTrayTrans1XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRAY_TRANSFER1_Z_0, IDC_BTN_TRAY_TRANSFER1_Z_10, OnbtnTrayTrans1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRAY_TRANSFER1_IO_0, IDC_BTN_TRAY_TRANSFER1_IO_1, OnbtnTrayTrans1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRAY_TRANSFER2_X_0, IDC_BTN_TRAY_TRANSFER2_X_12, OnbtnTrayTrans2XClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRAY_TRANSFER2_Z_0, IDC_BTN_TRAY_TRANSFER2_Z_14, btnTrayTrans2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TRAY_TRANSFER2_IO_0, IDC_BTN_TRAY_TRANSFER2_IO_1, btnTrayTrans2IOClick)
	

END_MESSAGE_MAP()

// CManualElevatorDlg 메시지 처리기입니다.
BOOL CManualElevatorDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	m_nRunCase1 = m_nRunCase2 = m_nRunCase3 = m_nRunCase4 = m_nRunCase5 = m_nRunCase6 = m_nRunCase7 = 0;
	m_bThreadElevator = FALSE;
	m_pThreadElevator = NULL;
	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualElevatorDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualElevatorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) { End_ElevatorThread(); return; }

	m_nRunCase1 = m_nRunCase2 = m_nRunCase3 = m_nRunCase4 = m_nRunCase5 = m_nRunCase6 = m_nRunCase7 = 0;
	Display_Status();

	m_strLog.Format("[Manual Elevator] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::Initial_Controls() 
{
	for (int i = 0; i < 20; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i =14; i < 17; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xFF), COLOR_DEFAULT);
	for (int i =17; i < 20; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x90, 0x00), COLOR_DEFAULT);
	for (int i = 0; i < 11; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 11; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i <  2; i++) m_btnLoad1ElevatorZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  4; i++) m_btnLoad1ElevatorIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  2; i++) m_btnLoad2ElevatorZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  4; i++) m_btnLoad2ElevatorIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  2; i++) m_btnNGEmptyElevatorZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  4; i++) m_btnNGEmptyElevatorIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  2; i++) m_btnGoodEmptyElevatorZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  4; i++) m_btnGoodEmptyElevatorIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  2; i++) m_btnNGBufferElevatorZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  4; i++) m_btnNGBufferElevatorIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  2; i++) m_btnGood1ElevatorZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  4; i++) m_btnGood1ElevatorIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  2; i++) m_btnGood2ElevatorZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  4; i++) m_btnGood2ElevatorIO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  8; i++) m_btnTrayTrans1X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 11; i++) m_btnTrayTrans1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  2; i++) m_btnTrayTrans1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 13; i++) m_btnTrayTrans2X[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 15; i++) m_btnTrayTrans2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <  2; i++) m_btnTrayTrans2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);


	for (int i = 0; i <11; i++) m_ledLoad1Elevator[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <11; i++) m_ledLoad2Elevator[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <11; i++) m_ledNGEmptyElevator[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <11; i++) m_ledGoodEmptyElevator[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <11; i++) m_ledNGBufferElevator[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <11; i++) m_ledGood1Elevator[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <11; i++) m_ledGood2Elevator[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 5; i++) m_ledTrayTrans1[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 5; i++) m_ledTrayTrans2[i].Init_Ctrl("Arial", 9, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CManualElevatorDlg::Display_Status()
{
	CString strPos;
	for (int i = 0; i < 11; i++) {
		double dPos = g_objAJinAXL.Get_Position(AX_ELEVATOR_Z1 + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	m_ledLoad1Elevator[0].Set_On(pDX00->iElevator1SlideOpen);
	m_ledLoad1Elevator[1].Set_On(pDX00->iElevator1SlideClose);
	m_ledLoad1Elevator[2].Set_On(pDX00->iElevator1Height1);
	m_ledLoad1Elevator[3].Set_On(pDX00->iElevator1Height2);
	m_ledLoad1Elevator[4].Set_On(pDX00->iElevator1TrayExist);
	m_ledLoad1Elevator[5].Set_On(pDX00->iElevator1Clamp1On);
	m_ledLoad1Elevator[6].Set_On(pDX00->iElevator1Clamp1Off);
	m_ledLoad1Elevator[7].Set_On(pDX00->iElevator1Clamp2On);
	m_ledLoad1Elevator[8].Set_On(pDX00->iElevator1Clamp2Off);
	m_ledLoad1Elevator[9].Set_On(pDX00->iElevator1SlideLock);
	m_ledLoad1Elevator[10].Set_On(pDX00->iElevator1SlideUnlock);

	m_ledLoad2Elevator[0].Set_On(pDX00->iElevator2SlideOpen);
	m_ledLoad2Elevator[1].Set_On(pDX00->iElevator2SlideClose);
	m_ledLoad2Elevator[2].Set_On(pDX00->iElevator2Height1);
	m_ledLoad2Elevator[3].Set_On(pDX00->iElevator2Height2);
	m_ledLoad2Elevator[4].Set_On(pDX00->iElevator2TrayExist);
	m_ledLoad2Elevator[5].Set_On(pDX00->iElevator2Clamp1On);
	m_ledLoad2Elevator[6].Set_On(pDX00->iElevator2Clamp1Off);
	m_ledLoad2Elevator[7].Set_On(pDX00->iElevator2Clamp2On);
	m_ledLoad2Elevator[8].Set_On(pDX00->iElevator2Clamp2Off);
	m_ledLoad2Elevator[9].Set_On(pDX00->iElevator2SlideLock);
	m_ledLoad2Elevator[10].Set_On(pDX00->iElevator2SlideUnlock);

	m_ledNGEmptyElevator[0].Set_On(pDX01->iElevator3SlideOpen);
	m_ledNGEmptyElevator[1].Set_On(pDX01->iElevator3SlideClose);
	m_ledNGEmptyElevator[2].Set_On(pDX01->iElevator3Height1);
	m_ledNGEmptyElevator[3].Set_On(pDX01->iElevator3Height2);
	m_ledNGEmptyElevator[4].Set_On(pDX01->iElevator3TrayExist);
	m_ledNGEmptyElevator[5].Set_On(pDX01->iElevator3Clamp1On);
	m_ledNGEmptyElevator[6].Set_On(pDX01->iElevator3Clamp1Off);
	m_ledNGEmptyElevator[7].Set_On(pDX01->iElevator3Clamp2On);
	m_ledNGEmptyElevator[8].Set_On(pDX01->iElevator3Clamp2Off);
	m_ledNGEmptyElevator[9].Set_On(pDX01->iElevator3SlideLock);
	m_ledNGEmptyElevator[10].Set_On(pDX01->iElevator3SlideUnlock);

	m_ledGoodEmptyElevator[0].Set_On(pDX01->iElevator4SlideOpen);
	m_ledGoodEmptyElevator[1].Set_On(pDX01->iElevator4SlideClose);
	m_ledGoodEmptyElevator[2].Set_On(pDX01->iElevator4Height1);
	m_ledGoodEmptyElevator[3].Set_On(pDX01->iElevator4Height2);
	m_ledGoodEmptyElevator[4].Set_On(pDX01->iElevator4TrayExist);
	m_ledGoodEmptyElevator[5].Set_On(pDX01->iElevator4Clamp1On);
	m_ledGoodEmptyElevator[6].Set_On(pDX01->iElevator4Clamp1Off);
	m_ledGoodEmptyElevator[7].Set_On(pDX01->iElevator4Clamp2On);
	m_ledGoodEmptyElevator[8].Set_On(pDX01->iElevator4Clamp2Off);
	m_ledGoodEmptyElevator[9].Set_On(pDX01->iElevator4SlideLock);
	m_ledGoodEmptyElevator[10].Set_On(pDX01->iElevator4SlideUnlock);

	m_ledNGBufferElevator[0].Set_On(pDX02->iElevator5SlideOpen);
	m_ledNGBufferElevator[1].Set_On(pDX02->iElevator5SlideClose);
	m_ledNGBufferElevator[2].Set_On(pDX02->iElevator5Height1);
	m_ledNGBufferElevator[3].Set_On(pDX02->iElevator5Height2);
	m_ledNGBufferElevator[4].Set_On(pDX02->iElevator5TrayExist);
	m_ledNGBufferElevator[5].Set_On(pDX02->iElevator5Clamp1On);
	m_ledNGBufferElevator[6].Set_On(pDX02->iElevator5Clamp1Off);
	m_ledNGBufferElevator[7].Set_On(pDX02->iElevator5Clamp2On);
	m_ledNGBufferElevator[8].Set_On(pDX02->iElevator5Clamp2Off);
	m_ledNGBufferElevator[9].Set_On(pDX02->iElevator5SlideLock);
	m_ledNGBufferElevator[10].Set_On(pDX02->iElevator5SlideUnlock);

	m_ledGood1Elevator[0].Set_On(pDX02->iElevator6SlideOpen);
	m_ledGood1Elevator[1].Set_On(pDX02->iElevator6SlideClose);
	m_ledGood1Elevator[2].Set_On(pDX02->iElevator6Height1);
//	m_ledGood1Elevator[3].Set_On(pDX02->iElevator6Height2);
	m_ledGood1Elevator[4].Set_On(pDX02->iElevator6TrayExist);
// 	m_ledGood1Elevator[5].Set_On(pDX02->iElevator6Clamp1On);
// 	m_ledGood1Elevator[6].Set_On(pDX02->iElevator6Clamp1Off);
// 	m_ledGood1Elevator[7].Set_On(pDX02->iElevator6Clamp2On);
// 	m_ledGood1Elevator[8].Set_On(pDX02->iElevator6Clamp2Off);
	m_ledGood1Elevator[9].Set_On(pDX02->iElevator6SlideLock);
	m_ledGood1Elevator[10].Set_On(pDX02->iElevator6SlideUnlock);

	m_ledGood2Elevator[0].Set_On(pDX02->iElevator7SlideOpen);
	m_ledGood2Elevator[1].Set_On(pDX02->iElevator7SlideClose);
	m_ledGood2Elevator[2].Set_On(pDX02->iElevator7Height1);
// 	m_ledGood2Elevator[3].Set_On(pDX02->iElevator7Height2);
	m_ledGood2Elevator[4].Set_On(pDX02->iElevator7TrayExist);
// 	m_ledGood2Elevator[5].Set_On(pDX02->iElevator7Clamp1On);
// 	m_ledGood2Elevator[6].Set_On(pDX02->iElevator7Clamp1Off);
// 	m_ledGood2Elevator[7].Set_On(pDX02->iElevator7Clamp2On);
// 	m_ledGood2Elevator[8].Set_On(pDX02->iElevator7Clamp2Off);
	m_ledGood2Elevator[9].Set_On(pDX03->iElevator7SlideLock);
	m_ledGood2Elevator[10].Set_On(pDX03->iElevator7SlideUnlock);

	m_ledTrayTrans1[0].Set_On(pDX03->iTransferLTrayExist);
	m_ledTrayTrans1[1].Set_On(pDX03->iTransferLGrab1Open);
	m_ledTrayTrans1[2].Set_On(pDX03->iTransferLGrab1Close);
	m_ledTrayTrans1[3].Set_On(pDX03->iTransferLGrab2Open);
	m_ledTrayTrans1[4].Set_On(pDX03->iTransferLGrab2Close);

	m_ledTrayTrans2[0].Set_On(pDX03->iTransferRTrayExist);
	m_ledTrayTrans2[1].Set_On(pDX03->iTransferRGrab1Open);
	m_ledTrayTrans2[2].Set_On(pDX03->iTransferRGrab1Close);
	m_ledTrayTrans2[3].Set_On(pDX03->iTransferRGrab2Open);
	m_ledTrayTrans2[4].Set_On(pDX03->iTransferRGrab2Close);	
}

///////////////////////////////////////////////////////////////////////////////
void CManualElevatorDlg::OnbtnLoad1ElevatorZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ELEVATOR_Z1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD1_ELEVATOR_Z_0;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	if (pDX00->iElevator1Clamp1On || pDX00->iElevator1Clamp2On) {
		AfxMessageBox(_T("Load1 Elevator Clamp On 상태 입니다....."));
		return;
	}
	if (!pDX00->iElevator1Clamp1On && !pDX00->iElevator1Clamp1Off) {
		AfxMessageBox(_T("Load1 Elevator Clamp1 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (pDX00->iElevator1Clamp2On && pDX00->iElevator1Clamp2Off) {
		AfxMessageBox(_T("Load1 Elevator Clamp2 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (!g_objCommon.Check_SlideLock(1)) {
		AfxMessageBox(_T("Load1 Elevator Slide Lock후 진행해 주세요...."));
		return;
	}

	if (nIndex == 0) {
		m_nRunCase1 = 0;
		g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z1, gData.dElevatorDown);
	} else {
		if (!pDX00->iElevator1TrayExist) {
			AfxMessageBox(_T("Elevator 1 -> Tray를 넣어 주세요......"));
			return;
		}
		m_nRunCase1 = 1;
		if (m_pThreadElevator == NULL) Begin_ElevatorThread();
	}
	gData.nElevatorOpen[1] = 0; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_1, 51);
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oElevator1Lamp = FALSE;
	g_objAJinAXL.Write_Output(13);

	m_strLog.Format("[Manual Elevator] Load1 Elevator Z1 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnLoad1ElevatorIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD1_ELEVATOR_IO_0;	

	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();

	if (nIndex == 0) {
		pDY00->oElevator1Clamp1On  = pDY00->oElevator1Clamp2On = TRUE;
		pDY00->oElevator1Clamp1Off = pDY00->oElevator1Clamp2Off = FALSE;
	} else if (nIndex == 1) {
		pDY00->oElevator1Clamp1On  = pDY00->oElevator1Clamp2On = FALSE;
		pDY00->oElevator1Clamp1Off = pDY00->oElevator1Clamp2Off = TRUE;
	} else if (nIndex == 2) {
		pDY00->oElevator1SlideLock = TRUE;	pDY00->oElevator1SlideUnlock = FALSE;
	} else if (nIndex == 3) {
		pDY00->oElevator1SlideLock = FALSE;	pDY00->oElevator1SlideUnlock = TRUE;
	}
	g_objAJinAXL.Write_Output(0);

	m_strLog.Format("[Manual Elevator] Load1 Elevator IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnLoad2ElevatorZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ELEVATOR_Z2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD2_ELEVATOR_Z_0;	

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	if (pDX00->iElevator2Clamp1On || pDX00->iElevator2Clamp2On) {
		AfxMessageBox(_T("Load2 Elevator Clamp On 상태 입니다....."));
		return;
	}
	if (!pDX00->iElevator2Clamp1On && !pDX00->iElevator2Clamp1Off) {
		AfxMessageBox(_T("Load2 Elevator Clamp1 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (pDX00->iElevator2Clamp2On && pDX00->iElevator2Clamp2Off) {
		AfxMessageBox(_T("Load2 Elevator Clamp2 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (!g_objCommon.Check_SlideLock(2)) {
		AfxMessageBox(_T("Load2 Elevator Slide Lock후 진행해 주세요...."));
		return;
	}

	if (nIndex == 0) {
		m_nRunCase2 = 0;
		g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z2, gData.dElevatorDown);
	} else {
		if (!pDX00->iElevator2TrayExist) {
			AfxMessageBox(_T("Elevator 2 -> Tray를 넣어 주세요......"));
			return;
		}
		m_nRunCase2 = 1;
		if (m_pThreadElevator == NULL) Begin_ElevatorThread();
	}
	gData.nElevatorOpen[2] = 0; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_2, 51);
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oElevator2Lamp = FALSE;
	g_objAJinAXL.Write_Output(13);

	m_strLog.Format("[Manual Elevator] Load2 Elevator Z2 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnLoad2ElevatorIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_LOAD2_ELEVATOR_IO_0;	

	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	
	if (nIndex == 0) {
		pDY00->oElevator2Clamp1On  = pDY00->oElevator2Clamp2On = TRUE;
		pDY00->oElevator2Clamp1Off = pDY00->oElevator2Clamp2Off = FALSE;
		g_objAJinAXL.Write_Output(0);
	} else if (nIndex == 1) {
		pDY00->oElevator2Clamp1On  = pDY00->oElevator2Clamp2On = FALSE;
		pDY00->oElevator2Clamp1Off = pDY00->oElevator2Clamp2Off = TRUE;
		g_objAJinAXL.Write_Output(0);
	} else if (nIndex == 2) {
		pDY01->oElevator2SlideLock = TRUE;	pDY01->oElevator2SlideUnlock = FALSE;
		g_objAJinAXL.Write_Output(1);
	} else if (nIndex == 3) {
		pDY01->oElevator2SlideLock = FALSE;	pDY01->oElevator2SlideUnlock = TRUE;
		g_objAJinAXL.Write_Output(1);
	}

	m_strLog.Format("[Manual Elevator] Load2 Elevator IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnNGEmptyElevatorZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ELEVATOR_Z3)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_NG_EMPTY_Z_0;	

	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if (pDX01->iElevator3Clamp1On || pDX01->iElevator3Clamp2On) {
		AfxMessageBox(_T("NG Empty Elevator Clamp On 상태 입니다....."));
		return;
	}
	if (!pDX01->iElevator3Clamp1On && !pDX01->iElevator3Clamp1Off) {
		AfxMessageBox(_T("NG Empty Elevator Clamp1 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (pDX01->iElevator3Clamp2On && pDX01->iElevator3Clamp2Off) {
		AfxMessageBox(_T("NG Empty Elevator Clamp2 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (!g_objCommon.Check_SlideLock(3)) {
		AfxMessageBox(_T("NG Empty Elevator Slide Lock후 진행해 주세요...."));
		return;
	}

	if (nIndex == 0) {
		m_nRunCase3 = 0;
		g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z3, gData.dElevatorDown);
	} else {
		if (!pDX01->iElevator3TrayExist) {
			AfxMessageBox(_T("Elevator 3 -> Tray를 넣어 주세요......"));
			return;
		}
		m_nRunCase3 = 1;
		if (m_pThreadElevator == NULL) Begin_ElevatorThread();
	}
	gData.nElevatorOpen[3] = 0; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_3, 51);
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oElevator3Lamp = FALSE;
	g_objAJinAXL.Write_Output(13);

	m_strLog.Format("[Manual Elevator] NG Empty Elevator Z3 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnNGEmptyElevatorIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_NG_EMPTY_IO_0;	

	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();

	if (nIndex == 0) {
		pDY01->oElevator3Clamp1On  = pDY01->oElevator3Clamp2On = TRUE;
		pDY01->oElevator3Clamp1Off = pDY01->oElevator3Clamp2Off = FALSE;
	} else if (nIndex == 1) {
		pDY01->oElevator3Clamp1On  = pDY01->oElevator3Clamp2On = FALSE;
		pDY01->oElevator3Clamp1Off = pDY01->oElevator3Clamp2Off = TRUE;
	} else if (nIndex == 2) {
		pDY01->oElevator3SlideLock = TRUE;	pDY01->oElevator3SlideUnlock = FALSE;
	} else if (nIndex == 3) {
		pDY01->oElevator3SlideLock = FALSE;	pDY01->oElevator3SlideUnlock = TRUE;
	}
	g_objAJinAXL.Write_Output(1);

	m_strLog.Format("[Manual Elevator] NG Empty Elevator IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnGoodEmptyElevatorZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ELEVATOR_Z4)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_GOOD_EMPTY_Z_0;	

	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	if (pDX01->iElevator4Clamp1On || pDX01->iElevator4Clamp2On) {
		AfxMessageBox(_T("Good Empty Elevator Clamp On 상태 입니다....."));
		return;
	}
	if (!pDX01->iElevator4Clamp1On && !pDX01->iElevator4Clamp1Off) {
		AfxMessageBox(_T("Good Empty Elevator Clamp1 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (pDX01->iElevator4Clamp2On && pDX01->iElevator4Clamp2Off) {
		AfxMessageBox(_T("Good Empty Elevator Clamp2 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (!g_objCommon.Check_SlideLock(4)) {
		AfxMessageBox(_T("Good Empty Elevator Slide Lock후 진행해 주세요...."));
		return;
	}

	if (nIndex == 0) {
		m_nRunCase4 = 0;
		g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z4, gData.dElevatorDown);
	} else {
		if (!pDX01->iElevator4TrayExist) {
			AfxMessageBox(_T("Elevator 4 -> Tray를 넣어 주세요......"));
			return;
		}
		m_nRunCase4 = 1;
		if (m_pThreadElevator == NULL) Begin_ElevatorThread();
	}
	gData.nElevatorOpen[4] = 0; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_4, 51);
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oElevator4Lamp = FALSE;
	g_objAJinAXL.Write_Output(13);

	m_strLog.Format("[Manual Elevator] Good Empty Elevator Z4 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnGoodEmptyElevatorIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_GOOD_EMPTY_IO_0;	

	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	if (nIndex == 0) {
		pDY01->oElevator4Clamp1On  = pDY01->oElevator4Clamp2On = TRUE;
		pDY01->oElevator4Clamp1Off = pDY01->oElevator4Clamp2Off = FALSE;
		g_objAJinAXL.Write_Output(1);
	} else if (nIndex == 1) {
		pDY01->oElevator4Clamp1On  = pDY01->oElevator4Clamp2On = FALSE;
		pDY01->oElevator4Clamp1Off = pDY01->oElevator4Clamp2Off = TRUE;
		g_objAJinAXL.Write_Output(1);
	} else if (nIndex == 2) {
		pDY02->oElevator4SlideLock = TRUE;	pDY02->oElevator4SlideUnlock = FALSE;
		g_objAJinAXL.Write_Output(2);
	} else if (nIndex == 3) {
		pDY02->oElevator4SlideLock = FALSE;	pDY02->oElevator4SlideUnlock = TRUE;
		g_objAJinAXL.Write_Output(2);
	}

	m_strLog.Format("[Manual Elevator] Good Empty Elevator IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnNGBufferElevatorZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ELEVATOR_Z5)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_NG_BUFFER_Z_0;	

	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	if (pDX02->iElevator5Clamp1On || pDX02->iElevator5Clamp2On) {
		AfxMessageBox(_T("NG Buffer Elevator Clamp On 상태 입니다....."));
		return;
	}
	if (!pDX02->iElevator5Clamp1On && !pDX02->iElevator5Clamp1Off) {
		AfxMessageBox(_T("NG Buffer Elevator Clamp1 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (pDX02->iElevator5Clamp2On && pDX02->iElevator5Clamp2Off) {
		AfxMessageBox(_T("NG Buffer Elevator Clamp2 Sensor 감지가 되지 않습니다....."));
		return;
	}
	if (!g_objCommon.Check_SlideLock(5)) {
		AfxMessageBox(_T("NG Buffer Elevator Slide Lock후 진행해 주세요...."));
		return;
	}

	if (nIndex == 0) {
		m_nRunCase5 = 0;
		g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z5, gData.dElevatorDown);
	} else {
		if (!pDX02->iElevator5TrayExist) {
			AfxMessageBox(_T("Elevator 5 -> Tray를 넣어 주세요......"));
			return;
		}
		m_nRunCase5 = 1;
		if (m_pThreadElevator == NULL) Begin_ElevatorThread();
	}
	gData.nElevatorOpen[5] = 0; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_5, 51);
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oElevator5Lamp = FALSE;
	g_objAJinAXL.Write_Output(13);

	m_strLog.Format("[Manual Elevator] NG Buffer Elevator Z5 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnNGBufferElevatorIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_NG_BUFFER_IO_0;	

	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	if (nIndex == 0) {
		pDY02->oElevator5Clamp1On  = pDY02->oElevator5Clamp2On = TRUE;
		pDY02->oElevator5Clamp1Off = pDY02->oElevator5Clamp2Off = FALSE;
	} else if (nIndex == 1) {
		pDY02->oElevator5Clamp1On  = pDY02->oElevator5Clamp2On = FALSE;
		pDY02->oElevator5Clamp1Off = pDY02->oElevator5Clamp2Off = TRUE;
	} else if (nIndex == 2) {
		pDY02->oElevator5SlideLock = TRUE;	pDY02->oElevator5SlideUnlock = FALSE;
	} else if (nIndex == 3) {
		pDY02->oElevator5SlideLock = FALSE;	pDY02->oElevator5SlideUnlock = TRUE;
	}
	g_objAJinAXL.Write_Output(2);

	m_strLog.Format("[Manual Elevator] NG Buffer Elevator IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnGood1ElevatorZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ELEVATOR_Z6)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	if (!g_objCommon.Check_SlideLock(6)) {
		AfxMessageBox(_T("Unload1 Elevator Slide Lock후 진행해 주세요...."));
		return;
	}

	int nIndex = nID - IDC_BTN_GOOD1_ELEVATOR_Z_0;	
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if (nIndex == 0) {
		m_nRunCase6 = 0;
		g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z6, gData.dElevatorDown);
	} else {
		if (!pDX02->iElevator6TrayExist) {
			AfxMessageBox(_T("Elevator 6 -> Tray를 넣어 주세요......"));
			return;
		}
		m_nRunCase6 = 1;
		if (m_pThreadElevator == NULL) Begin_ElevatorThread();
	}
	gData.nElevatorOpen[6] = 0; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_6, 51);
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oElevator6Lamp = FALSE;
	g_objAJinAXL.Write_Output(13);

	m_strLog.Format("[Manual Elevator] Good1 Elevator Z6 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnGood1ElevatorIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_GOOD1_ELEVATOR_IO_0;	

	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	if (nIndex == 0) {
	} else if (nIndex == 1) {
	} else if (nIndex == 2) {
		pDY02->oElevator6SlideLock = TRUE;	pDY02->oElevator6SlideUnlock = FALSE;
	} else if (nIndex == 3) {
		pDY02->oElevator6SlideLock = FALSE;	pDY02->oElevator6SlideUnlock = TRUE;
	}
	g_objAJinAXL.Write_Output(2);

	m_strLog.Format("[Manual Elevator] Good1 Elevator IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnGood2ElevatorZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ELEVATOR_Z7)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	if (!g_objCommon.Check_SlideLock(7)) {
		AfxMessageBox(_T("Unload2 Elevator Slide Lock후 진행해 주세요...."));
		return;
	}

	int nIndex = nID - IDC_BTN_GOOD2_ELEVATOR_Z_0;	
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if (nIndex == 0) {
		m_nRunCase7 = 0;
		g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z7, gData.dElevatorDown);
	} else {
		if (!pDX02->iElevator7TrayExist) {
			AfxMessageBox(_T("Elevator 7 -> Tray를 넣어 주세요......"));
			return;
		}
		m_nRunCase7 = 1;
		if (m_pThreadElevator == NULL) Begin_ElevatorThread();
	}
	gData.nElevatorOpen[7] = 0; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_7, 51);
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oElevator7Lamp = FALSE;
	g_objAJinAXL.Write_Output(13);

	m_strLog.Format("[Manual Elevator] Good2 Elevator Z7 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnGood2ElevatorIOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_GOOD2_ELEVATOR_IO_0;	

	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();

	if (nIndex == 0) {
	} else if (nIndex == 1) {
	} else if (nIndex == 2) {
		pDY03->oElevator7SlideLock = TRUE;	pDY03->oElevator7SlideUnlock = FALSE;
	} else if (nIndex == 3) {
		pDY03->oElevator7SlideLock = FALSE;	pDY03->oElevator7SlideUnlock = TRUE;
	}
	g_objAJinAXL.Write_Output(3);

	m_strLog.Format("[Manual Elevator] Good2 Elevator IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);

}

void CManualElevatorDlg::OnbtnTrayTrans1XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANSFER_X1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_TRAY_TRANSFER1_X_0 + 1;	

	// Interlock
	if (!g_objCommon.Check_Position(AX_TRANSFER_Z1, 0)) {
		AfxMessageBox(_T("Transfer1 Z축 Ready Up 위치에서만 작업 가능합니다....."));
		return;
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	double dTrans2XPos = g_objAJinAXL.Get_Position(AX_TRANSFER_X2);
	double dCheckPos = 0.0;

	//Transfer1 X축은 Good Empty Elevator까지 움직인다.
	// Load Stage1,2 Transfer2 X축 위치 확인 안해도된다.
	if (nIndex == 3 || nIndex == 4) {	//Load1, Load2 Elevator Transfer2 X축은 Load1/2 Elevator 까지 오지 않아 NG Empty 이후에 있으면된다.
		dCheckPos = pMoveData->dTransferX2[1] + 1.0;	//NG Empty
		if (dCheckPos < dTrans2XPos) {
			AfxMessageBox(_T("충돌 위험!! Transfer2 X축이 NG Empty Elevator 위치를 넘어가 있습니다....."));
			return;
		}
	}
	if (nIndex == 5) {	//NG Empty
		dCheckPos = pMoveData->dTransferX2[2] + 1.0;	//Good Empty
		if (dCheckPos < dTrans2XPos) {
			AfxMessageBox(_T("충돌 위험!! Transfer2 X축이 Good Empty Elevator 위치를 넘어가 있습니다....."));
			return;
		}
	}
	if (nIndex == 6) {	//Good Empty
		dCheckPos = pMoveData->dTransferX2[3] + 1.0;	// NG Buffer
		if (dCheckPos < dTrans2XPos) {
			AfxMessageBox(_T("충돌 위험!! Transfer2 X축이 NG Empty Elevator 위치를 넘어가 있습니다....."));
			return;
		}
	}	
	
	// Move
	g_objCommon.Move_Position(AX_TRANSFER_X1, nIndex);

	m_strLog.Format("[Manual Elevator] Tray Transfer1 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnTrayTrans1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANSFER_Z1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_TRAY_TRANSFER1_Z_0;

	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	// Interlock
	if (nIndex == 1 || nIndex == 9) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X1, 1)) {
			AfxMessageBox(_T("Transfer1 X축이 Load Stage1 위치가 아닙니다....."));
			return;
		}
	} else if (nIndex == 2 || nIndex == 10) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X1, 2)) {
			AfxMessageBox(_T("Transfer1 X축이 Load Stage2 위치가 아닙니다....."));
			return;
		}
	} else {
		if (nIndex != 0 && !g_objCommon.Check_Position(AX_TRANSFER_X1, nIndex)) {
			if (nIndex == 3) { AfxMessageBox(_T("Transfer1 X축이 Load1 Elevator 위치가 아닙니다.....")); return; }
			if (nIndex == 4) { AfxMessageBox(_T("Transfer1 X축이 Load2 Elevator 위치가 아닙니다.....")); return; }
			if (nIndex == 5) { AfxMessageBox(_T("Transfer1 X축이 NG Empty Elevator 위치가 아닙니다.....")); return; }
			if (nIndex == 6) { AfxMessageBox(_T("Transfer1 X축이 Good Empty Elevator 위치가 아닙니다.....")); return; }
			if (nIndex == 7) { AfxMessageBox(_T("Transfer1 X축이 NG Stage1 위치가 아닙니다.....")); return; }
			if (nIndex == 8) { AfxMessageBox(_T("Transfer1 X축이 NG Stage2 위치가 아닙니다.....")); return; }		
		}
	}

	if (nIndex != 0) {	// Ready Up 외 Down할때 Clamp 확인.
		if (!pDX03->iTransferLGrab1Open || !pDX03->iTransferLGrab2Open) {
			if (g_objCommon.Show_MsgBox(2, "Transfer1 Clamp Open 상태가 아닙니다. Z축 Down 하시겠습니까?") != IDOK) return;
		}
	}

	// Move
	g_objCommon.Move_Position(AX_TRANSFER_Z1, nIndex);

	m_strLog.Format("[Manual Elevator] Tray Transfer1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);

}

void CManualElevatorDlg::OnbtnTrayTrans1IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_TRAY_TRANSFER1_IO_0;	

	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();

	if (nIndex == 0) {
		pDY03->oTransferLGrabOpen = TRUE;
		pDY03->oTransferLGrabClose = FALSE;
	} else {
		pDY03->oTransferLGrabOpen = FALSE;
		pDY03->oTransferLGrabClose = TRUE;
	}
	g_objAJinAXL.Write_Output(3);

	m_strLog.Format("[Manual Elevator] Tray Transfer1 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::OnbtnTrayTrans2XClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANSFER_X2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_TRAY_TRANSFER2_X_0 + 1;	

	// Interlock
	if (!g_objCommon.Check_Position(AX_TRANSFER_Z2, 0)) {
		AfxMessageBox(_T("Transfer2 Z축 Ready Up 위치에서만 작업 가능합니다....."));
		return;
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	double dTrans1XPos = g_objAJinAXL.Get_Position(AX_TRANSFER_X1);
	double dCheckPos = 0.0;

	//Transfer2 X축은 NG Empty Elevator까지 움직인다.
	// Good Stage1,2 Transfer2 X축 위치 확인 안해도된다.
	if (nIndex == 1) {	//NG Empty
		dCheckPos = pMoveData->dTransferX1[4] + 1.0;	//Load2
		if (dCheckPos < dTrans1XPos) {
			AfxMessageBox(_T("충돌 위험!! Transfer1 X축이 Load2 Elevator 위치를 넘어가 있습니다....."));
			return;
		}
	}
	if (nIndex == 2) {	//Good Empty
		dCheckPos = pMoveData->dTransferX1[5] + 1.0;	//NG Empty
		if (dCheckPos < dTrans1XPos) {
			AfxMessageBox(_T("충돌 위험!! Transfer1 X축이 NG Empty Elevator 위치를 넘어가 있습니다....."));
			return;
		}
	}
	if (nIndex == 3 || nIndex == 4 || nIndex == 5 || nIndex == 6 || nIndex == 7) {	//NG Buffer, Good1/2, NG Stage1/2
		dCheckPos = pMoveData->dTransferX1[6] + 1.0;	// Good Empty
		if (dCheckPos < dTrans1XPos) {
			AfxMessageBox(_T("충돌 위험!! Transfer2 X축이 Good Empty Elevator 위치를 넘어가 있습니다....."));
			return;
		}
	}

	// Move
	g_objCommon.Move_Position(AX_TRANSFER_X2, nIndex);

	m_strLog.Format("[Manual Elevator] Tray Transfer2 X (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::btnTrayTrans2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TRANSFER_Z2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_TRAY_TRANSFER2_Z_0;

	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	// Interlock
	if (nIndex == 3 || nIndex == 10) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X2, 3)) {
			AfxMessageBox(_T("Transfer2 X축이 NG Buffer Elevator 위치가 아닙니다....."));
			return;
		}
	} else if (nIndex == 6 || nIndex == 11) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X2, 6)) {
			AfxMessageBox(_T("Transfer2 X축이 NG Stage1 위치가 아닙니다....."));
			return;
		}
	} else if (nIndex == 7 || nIndex == 12) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X2, 7)) {
			AfxMessageBox(_T("Transfer2 X축이 NG Stage2 위치가 아닙니다....."));
			return;
		}
	} else if (nIndex == 8 || nIndex == 13) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X2, 8)) {
			AfxMessageBox(_T("Transfer2 X축이 Good Stage1 위치가 아닙니다....."));
			return;
		}
	} else if (nIndex == 9 || nIndex == 14) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X2, 9)) {
			AfxMessageBox(_T("Transfer2 X축이 Good Stage2 위치가 아닙니다....."));
			return;
		}
	} else if (nIndex == 4) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X2, 4) && !g_objCommon.Check_Position(AX_TRANSFER_X2, 10) && !g_objCommon.Check_Position(AX_TRANSFER_X2, 11)) {
			AfxMessageBox(_T("Transfer2 X축이 Unload1 Elevator 위치가 아닙니다....."));
			return;
		}
	} else if (nIndex == 5) {
		if (!g_objCommon.Check_Position(AX_TRANSFER_X2, 5) && !g_objCommon.Check_Position(AX_TRANSFER_X2, 12) && !g_objCommon.Check_Position(AX_TRANSFER_X2, 13)) {
			AfxMessageBox(_T("Transfer2 X축이 Unload2 Elevator 위치가 아닙니다....."));
			return;
		}
	} else {
		if (nIndex != 0 && !g_objCommon.Check_Position(AX_TRANSFER_X2, nIndex)) {
			if (nIndex == 1) { AfxMessageBox(_T("Transfer2 X축이 NG Empty Elevator 위치가 아닙니다.....")); return; }
			if (nIndex == 2) { AfxMessageBox(_T("Transfer2 X축이 Good Empty Elevator 위치가 아닙니다.....")); return; }
		}
	}

	if (nIndex != 0) {	// Ready Up 외 Down할때 Clamp 확인.
		if (!pDX03->iTransferRGrab1Open || !pDX03->iTransferRGrab2Open) {
			if (g_objCommon.Show_MsgBox(2, "Transfer2 Clamp Open 상태가 아닙니다. Z축 Down 하시겠습니까?") != IDOK) return;
		}
	}

	// Move
	g_objCommon.Move_Position(AX_TRANSFER_Z2, nIndex);

	m_strLog.Format("[Manual Elevator] Tray Transfer2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualElevatorDlg::btnTrayTrans2IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_TRAY_TRANSFER2_IO_0;	

	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();

	if (nIndex == 0) {
		pDY03->oTransferRGrabOpen = TRUE;
		pDY03->oTransferRGrabClose = FALSE;
	} else {
		pDY03->oTransferRGrabOpen = FALSE;
		pDY03->oTransferRGrabClose = TRUE;
	}
	g_objAJinAXL.Write_Output(3);

	m_strLog.Format("[Manual Elevator] Tray Transfer2 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
void CManualElevatorDlg::Begin_ElevatorThread()
{
	g_objCommon.Locking_MainDoor(TRUE);
	if (m_pThreadElevator) return;

	m_tEleLoop1.Set_LoopTime(3000);
	m_tEleLoop2.Set_LoopTime(3000);
	m_tEleLoop3.Set_LoopTime(3000);
	m_tEleLoop4.Set_LoopTime(3000);
	m_tEleLoop5.Set_LoopTime(3000);
	m_tEleLoop6.Set_LoopTime(3000);
	m_tEleLoop7.Set_LoopTime(3000);

//	if (m_pThreadElevator) End_ElevatorThread();
	m_bThreadElevator = TRUE;
	m_pThreadElevator = AfxBeginThread(Thread_Elevator, this);
}

void CManualElevatorDlg::End_ElevatorThread()
{
	if (m_pThreadElevator) {
		m_bThreadElevator = FALSE;
		WaitForSingleObject(m_pThreadElevator->m_hThread, INFINITE);
	}
}

/////////////////////////////////////////////////////////////////////////////
// InspectMold Thread Function 
UINT CManualElevatorDlg::Thread_Elevator(LPVOID lpVoid)
{
	CManualElevatorDlg *pDlg = (CManualElevatorDlg*)lpVoid;

	while (pDlg->m_bThreadElevator) {
		if (!g_objCommon.Check_MainDoor()) break;
		if (!g_objCommon.Check_TraySlide()) break;

		if (!pDlg->Manual_ElevatorRun1()) break;
		if (!pDlg->Manual_ElevatorRun2()) break;
		if (!pDlg->Manual_ElevatorRun3()) break;
		if (!pDlg->Manual_ElevatorRun4()) break;
		if (!pDlg->Manual_ElevatorRun5()) break;
		if (!pDlg->Manual_ElevatorRun6()) break;
		if (!pDlg->Manual_ElevatorRun7()) break;
		Sleep(5);
	}
	pDlg->m_bThreadElevator = FALSE;
	pDlg->m_pThreadElevator = NULL;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CManualElevatorDlg::Manual_ElevatorRun1()
{
	CString strVel, strMsg;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	switch (m_nRunCase1) 
	{
	case 0:
		m_tEleLoop1.Set_LoopTime(3000);
		break;

	case 1:
//			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z1, gData.dElevatorDown);
			m_nRunCase1 = 4; m_tEleLoop1.Set_LoopTime(30000);
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z1)) {
			m_nRunCase1++; m_tEleLoop1.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (pDX00->iElevator1TrayExist) {
			m_nRunCase1 = 10; m_tEleLoop1.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (pDX00->iElevator1Height1 || pDX00->iElevator1Height2) {
			m_nRunCase1 = 12; m_tEleLoop1.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z1, ELEVATOR_UD);
			m_nRunCase1++; m_tEleLoop1.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z1)) {
			m_nRunCase1 = 10; m_tEleLoop1.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (pDX00->iElevator1Height1 || pDX00->iElevator1Height2) {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z1, ELEVATOR_DN*-1.0);
			m_nRunCase1++; m_tEleLoop1.Set_LoopTime(30000);
		} else {
			m_nRunCase1 = 14; m_tEleLoop1.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z1)) {
			m_nRunCase1 = 12; m_tEleLoop1.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (pDX00->iElevator1Height1 && pDX00->iElevator1Height2) {
			m_nRunCase1 = 16; m_tEleLoop1.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z1, ELEVATOR_SL);
			m_nRunCase1++; m_tEleLoop1.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z1)) {
			m_nRunCase1 = 14; m_tEleLoop1.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z1)) {
			double dElelavtorZ = pMoveData->dElevatorZ1[2];
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z1, dElelavtorZ);
			m_nRunCase1++; m_tEleLoop1.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z1)) {
			m_nRunCase1 = 20; m_tEleLoop1.Set_LoopTime(30000);
		}
		break;

	case 20:
		m_nRunCase1 = 0;
		g_objCommon.Show_MsgBox(1, "Manual Elevator1 End.....");
		return TRUE;

	}

	if (m_tEleLoop1.Over_LoopTime()) {
		if		(m_nRunCase1 ==  5) strMsg = "Elevator 1 -> Tray를 넣어 주세요.";
		else if (m_nRunCase1 == 11) strMsg = "Elevator 1 -> High 센서 미 감지........";
		else if (m_nRunCase1 == 14) strMsg = "Elevator 1 -> High 센서 미 감지........";
		else strMsg.Format("AX_ELEVATOR_Z1 미 완료 => [%d]", m_nRunCase1);
		m_nRunCase1 = 0;
		g_objCommon.Show_MsgBox(1, strMsg);
		return TRUE;
	}
	return TRUE;
}

BOOL CManualElevatorDlg::Manual_ElevatorRun2()
{
	CString strVel, strMsg;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();

	switch (m_nRunCase2) 
	{
	case 0:
		m_tEleLoop2.Set_LoopTime(3000);
		break;

	case 1:
//			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z2, gData.dElevatorDown);
			m_nRunCase2 = 4; m_tEleLoop2.Set_LoopTime(30000);
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z2)) {
			m_nRunCase2++; m_tEleLoop2.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (pDX00->iElevator2TrayExist) {
			m_nRunCase2 = 10; m_tEleLoop2.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (pDX00->iElevator2Height1 || pDX00->iElevator2Height2) {
			m_nRunCase2 = 12; m_tEleLoop2.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z2, ELEVATOR_UD);
			m_nRunCase2++; m_tEleLoop2.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z2)) {
			m_nRunCase2 = 10; m_tEleLoop2.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (pDX00->iElevator2Height1 || pDX00->iElevator2Height2) {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z2, ELEVATOR_DN*-1.0);
			m_nRunCase2++; m_tEleLoop2.Set_LoopTime(30000);
		} else {
			m_nRunCase2 = 14; m_tEleLoop2.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z2)) {
			m_nRunCase2 = 12; m_tEleLoop2.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (pDX00->iElevator2Height1 && pDX00->iElevator2Height2) {
			m_nRunCase2 = 16; m_tEleLoop2.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z2, ELEVATOR_SL);
			m_nRunCase2++; m_tEleLoop2.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z2)) {
			m_nRunCase2 = 14; m_tEleLoop2.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z2)) {
			double dElelavtorZ = pMoveData->dElevatorZ2[2];
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z2, dElelavtorZ);
			m_nRunCase2++; m_tEleLoop2.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z2)) {
			m_nRunCase2 = 20; m_tEleLoop2.Set_LoopTime(30000);
		}
		break;

	case 20:
		m_nRunCase2 = 0;
		g_objCommon.Show_MsgBox(1, "Manual Elevator2 End.....");
		return TRUE;

	}

	if (m_tEleLoop2.Over_LoopTime()) {
		if		(m_nRunCase2 ==  5) strMsg = "Elevator 2 -> Tray를 넣어 주세요.";
		else if (m_nRunCase2 == 11) strMsg = "Elevator 2 -> High 센서 미 감지........";
		else if (m_nRunCase2 == 14) strMsg = "Elevator 2 -> High 센서 미 감지........";
		else strMsg.Format("AX_ELEVATOR_Z2 미 완료 => [%d]", m_nRunCase2);
		m_nRunCase2 = 0;
		g_objCommon.Show_MsgBox(1, strMsg);
		return TRUE;
	}
	return TRUE;
}

BOOL CManualElevatorDlg::Manual_ElevatorRun3()
{
	CString strVel, strMsg;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();

	switch (m_nRunCase3) 
	{
	case 0:
		m_tEleLoop3.Set_LoopTime(3000);
		break;

	case 1:
//			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z3, gData.dElevatorDown);
			m_nRunCase3 = 4; m_tEleLoop3.Set_LoopTime(30000);
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z3)) {
			m_nRunCase3++; m_tEleLoop3.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (pDX01->iElevator3TrayExist) {
			m_nRunCase3 = 10; m_tEleLoop3.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (pDX01->iElevator3Height1 || pDX01->iElevator3Height2) {
			m_nRunCase3 = 12; m_tEleLoop3.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z3, ELEVATOR_UD);
			m_nRunCase3++; m_tEleLoop3.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z3)) {
			m_nRunCase3 = 10; m_tEleLoop3.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (pDX01->iElevator3Height1 || pDX01->iElevator3Height2) {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z3, ELEVATOR_DN*-1.0);
			m_nRunCase3++; m_tEleLoop3.Set_LoopTime(30000);
		} else {
			m_nRunCase3 = 14; m_tEleLoop3.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z3)) {
			m_nRunCase3 = 12; m_tEleLoop3.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (pDX01->iElevator3Height1 && pDX01->iElevator3Height2) {
			m_nRunCase3 = 16; m_tEleLoop3.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z3, ELEVATOR_SL);
			m_nRunCase3++; m_tEleLoop3.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z3)) {
			m_nRunCase3 = 14; m_tEleLoop3.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z3)) {
			double dElelavtorZ = pMoveData->dElevatorZ3[2];
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z3, dElelavtorZ);
			m_nRunCase3++; m_tEleLoop3.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z3)) {
			m_nRunCase3 = 20; m_tEleLoop3.Set_LoopTime(30000);
		}
		break;

	case 20:
		m_nRunCase3 = 0;
		g_objCommon.Show_MsgBox(1, "Manual Elevator3 End.....");
		return TRUE;

	}

	if (m_tEleLoop3.Over_LoopTime()) {
		if		(m_nRunCase3 ==  5) strMsg = "Elevator 3 -> Tray를 넣어 주세요.";
		else if (m_nRunCase3 == 11) strMsg = "Elevator 3 -> High 센서 미 감지........";
		else if (m_nRunCase3 == 14) strMsg = "Elevator 3 -> High 센서 미 감지........";
		else strMsg.Format("AX_ELEVATOR_Z3 미 완료 => [%d]", m_nRunCase3);
		m_nRunCase3 = 0;
		g_objCommon.Show_MsgBox(1, strMsg);
		return TRUE;
	}
	return TRUE;
}

BOOL CManualElevatorDlg::Manual_ElevatorRun4()
{
	CString strVel, strMsg;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();

	switch (m_nRunCase4) 
	{
	case 0:
		m_tEleLoop4.Set_LoopTime(3000);
		break;

	case 1:
//			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z4, gData.dElevatorDown);
			m_nRunCase4 = 4; m_tEleLoop4.Set_LoopTime(30000);
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z4)) {
			m_nRunCase4++; m_tEleLoop4.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (pDX01->iElevator4TrayExist) {
			m_nRunCase4 = 10; m_tEleLoop4.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (pDX01->iElevator4Height1 || pDX01->iElevator4Height2) {
			m_nRunCase4 = 12; m_tEleLoop4.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z4, ELEVATOR_UD);
			m_nRunCase4++; m_tEleLoop4.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z4)) {
			m_nRunCase4 = 10; m_tEleLoop4.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (pDX01->iElevator4Height1 || pDX01->iElevator4Height2) {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z4, ELEVATOR_DN*-1.0);
			m_nRunCase4++; m_tEleLoop4.Set_LoopTime(30000);
		} else {
			m_nRunCase4 = 14; m_tEleLoop4.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z4)) {
			m_nRunCase4 = 12; m_tEleLoop4.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (pDX01->iElevator4Height1 && pDX01->iElevator4Height2) {
			m_nRunCase4 = 16; m_tEleLoop4.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z4, ELEVATOR_SL);
			m_nRunCase4++; m_tEleLoop4.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z4)) {
			m_nRunCase4 = 14; m_tEleLoop4.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z4)) {
			double dElelavtorZ = pMoveData->dElevatorZ4[2];
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z4, dElelavtorZ);
			m_nRunCase4++; m_tEleLoop4.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z4)) {
			m_nRunCase4 = 20; m_tEleLoop4.Set_LoopTime(30000);
		}
		break;

	case 20:
		m_nRunCase4 = 0;
		g_objCommon.Show_MsgBox(1, "Manual Elevator4 End.....");
		return TRUE;

	}

	if (m_tEleLoop4.Over_LoopTime()) {
		if		(m_nRunCase4 ==  5) strMsg = "Elevator 4 -> Tray를 넣어 주세요.";
		else if (m_nRunCase4 == 11) strMsg = "Elevator 4 -> High 센서 미 감지........";
		else if (m_nRunCase4 == 14) strMsg = "Elevator 4 -> High 센서 미 감지........";
		else strMsg.Format("AX_ELEVATOR_Z4 미 완료 => [%d]", m_nRunCase4);
		m_nRunCase4 = 0;
		g_objCommon.Show_MsgBox(1, strMsg);
		return TRUE;
	}
	return TRUE;
}

BOOL CManualElevatorDlg::Manual_ElevatorRun5()
{
	CString strVel, strMsg;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	switch (m_nRunCase5) 
	{
	case 0:
		m_tEleLoop5.Set_LoopTime(3000);
		break;

	case 1:
//			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z5, gData.dElevatorDown);
			m_nRunCase5 = 4; m_tEleLoop5.Set_LoopTime(30000);
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z5)) {
			m_nRunCase5++; m_tEleLoop5.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (pDX02->iElevator5TrayExist) {
			m_nRunCase5 = 10; m_tEleLoop5.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (pDX02->iElevator5Height1 || pDX02->iElevator5Height2) {
			m_nRunCase5 = 12; m_tEleLoop5.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z5, ELEVATOR_UD);
			m_nRunCase5++; m_tEleLoop5.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z5)) {
			m_nRunCase5 = 10; m_tEleLoop5.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (pDX02->iElevator5Height1 || pDX02->iElevator5Height2) {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z5, ELEVATOR_DN*-1.0);
			m_nRunCase5++; m_tEleLoop5.Set_LoopTime(30000);
		} else {
			m_nRunCase5 = 14; m_tEleLoop5.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z5)) {
			m_nRunCase5 = 12; m_tEleLoop5.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (pDX02->iElevator5Height1 && pDX02->iElevator5Height2) {
			m_nRunCase5 = 16; m_tEleLoop5.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z5, ELEVATOR_SL);
			m_nRunCase5++; m_tEleLoop5.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z5)) {
			m_nRunCase5 = 14; m_tEleLoop5.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z5)) {
			double dElelavtorZ = pMoveData->dElevatorZ5[2];
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z5, dElelavtorZ);
			m_nRunCase5++; m_tEleLoop5.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z5)) {
			m_nRunCase5 = 20; m_tEleLoop5.Set_LoopTime(30000);
		}
		break;

	case 20:
		m_nRunCase5 = 0;
		g_objCommon.Show_MsgBox(1, "Manual Elevator5 End.....");
		return TRUE;
	}

	if (m_tEleLoop5.Over_LoopTime()) {
		if		(m_nRunCase5 ==  5) strMsg = "Elevator 5 -> Tray를 넣어 주세요.";
		else if (m_nRunCase5 == 11) strMsg = "Elevator 5 -> High 센서 미 감지........";
		else if (m_nRunCase5 == 14) strMsg = "Elevator 5 -> High 센서 미 감지........";
		else strMsg.Format("AX_ELEVATOR_Z5 미 완료 => [%d]", m_nRunCase5);
		m_nRunCase5 = 0;
		g_objCommon.Show_MsgBox(1, strMsg);
		return TRUE;
	}
	return TRUE;
}

BOOL CManualElevatorDlg::Manual_ElevatorRun6()
{
	CString strVel, strMsg;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	switch (m_nRunCase6) 
	{
	case 0:
		m_tEleLoop6.Set_LoopTime(3000);
		break;

	case 1:
//			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z6, gData.dElevatorDown);
			m_nRunCase6 = 4; m_tEleLoop6.Set_LoopTime(30000);
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z6)) {
			m_nRunCase6++; m_tEleLoop6.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (pDX02->iElevator6TrayExist) {
			m_nRunCase6 = 10; m_tEleLoop6.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (pDX02->iElevator6Height1) {
			m_nRunCase6 = 12; m_tEleLoop6.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z6, ELEVATOR_UD);
			m_nRunCase6++; m_tEleLoop6.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z6)) {
			m_nRunCase6 = 10; m_tEleLoop6.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (pDX02->iElevator6Height1) {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z6, ELEVATOR_DN*-1.0);
			m_nRunCase6++; m_tEleLoop6.Set_LoopTime(30000);
		} else {
			m_nRunCase6 = 14; m_tEleLoop6.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z6)) {
			m_nRunCase6 = 12; m_tEleLoop6.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (pDX02->iElevator6Height1) {
			m_nRunCase6 = 16; m_tEleLoop6.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z6, ELEVATOR_SL);
			m_nRunCase6++; m_tEleLoop6.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z6)) {
			m_nRunCase6 = 14; m_tEleLoop6.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z6)) {
			double dElelavtorZ = pMoveData->dElevatorZ6[2];
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z6, dElelavtorZ);
			m_nRunCase6++; m_tEleLoop6.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z6)) {
			m_nRunCase6 = 20; m_tEleLoop6.Set_LoopTime(30000);
		}
		break;

	case 20:
		m_nRunCase6 = 0;
		g_objCommon.Show_MsgBox(1, "Manual Elevator6 End.....");
		return TRUE;

	}

	if (m_tEleLoop6.Over_LoopTime()) {
		if		(m_nRunCase6 ==  5) strMsg = "Elevator 6 -> Tray를 넣어 주세요.";
		else if (m_nRunCase6 == 11) strMsg = "Elevator 6 -> High 센서 미 감지........";
		else if (m_nRunCase6 == 14) strMsg = "Elevator 6 -> High 센서 미 감지........";
		else strMsg.Format("AX_ELEVATOR_Z6 미 완료 => [%d]", m_nRunCase6);
		m_nRunCase6 = 0;
		g_objCommon.Show_MsgBox(1, strMsg);
		return TRUE;
	}
	return TRUE;
}

BOOL CManualElevatorDlg::Manual_ElevatorRun7()
{
	CString strVel, strMsg;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	switch (m_nRunCase7) 
	{
	case 0:
		m_tEleLoop7.Set_LoopTime(3000);
		break;

	case 1:
//			g_objAJinAXL.Move_Absolute(AX_ELEVATOR_Z7, gData.dElevatorDown);
			m_nRunCase7 = 4; m_tEleLoop7.Set_LoopTime(30000);
		break;
	case 4:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z7)) {
			m_nRunCase7++; m_tEleLoop7.Set_LoopTime(5000);
		}
		break;
	case 5:
		if (pDX02->iElevator7TrayExist) {
			m_nRunCase7 = 10; m_tEleLoop7.Set_LoopTime(5000);
		}
		break;

	case 10:
		if (pDX02->iElevator7Height1) {
			m_nRunCase7 = 12; m_tEleLoop7.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z7, ELEVATOR_UD);
			m_nRunCase7++; m_tEleLoop7.Set_LoopTime(30000);
		}
		break;
	case 11:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z7)) {
			m_nRunCase7 = 10; m_tEleLoop7.Set_LoopTime(30000);
		}
		break;
	case 12:
		if (pDX02->iElevator7Height1) {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z7, ELEVATOR_DN*-1.0);
			m_nRunCase7++; m_tEleLoop7.Set_LoopTime(30000);
		} else {
			m_nRunCase7 = 14; m_tEleLoop7.Set_LoopTime(30000);
		}
		break;
	case 13:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z7)) {
			m_nRunCase7 = 12; m_tEleLoop7.Set_LoopTime(30000);
		}
		break;
	case 14:
		if (pDX02->iElevator7Height1) {
			m_nRunCase7 = 16; m_tEleLoop7.Set_LoopTime(30000);
		} else {
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z7, ELEVATOR_SL);
			m_nRunCase7++; m_tEleLoop7.Set_LoopTime(30000);
		}
		break;
	case 15:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z7)) {
			m_nRunCase7 = 14; m_tEleLoop7.Set_LoopTime(30000);
		}
		break;
	case 16:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z7)) {
			double dElelavtorZ = pMoveData->dElevatorZ7[2];
			g_objAJinAXL.Move_Relative(AX_ELEVATOR_Z7, dElelavtorZ);
			m_nRunCase7++; m_tEleLoop7.Set_LoopTime(30000);
		}
		break;
	case 17:
		if (g_objAJinAXL.Is_Done(AX_ELEVATOR_Z7)) {
			m_nRunCase7 = 20; m_tEleLoop7.Set_LoopTime(30000);
		}
		break;

	case 20:
		m_nRunCase7 = 0;
		g_objCommon.Show_MsgBox(1, "Manual Elevator7 End.....");
		return TRUE;

	}

	if (m_tEleLoop7.Over_LoopTime()) {
		if		(m_nRunCase7 ==  5) strMsg = "Elevator 7 -> Tray를 넣어 주세요.";
		else if (m_nRunCase7 == 11) strMsg = "Elevator 7 -> High 센서 미 감지........";
		else if (m_nRunCase7 == 14) strMsg = "Elevator 7 -> High 센서 미 감지........";
		else strMsg.Format("AX_ELEVATOR_Z7 미 완료 => [%d]", m_nRunCase7);
		m_nRunCase7 = 0;
		g_objCommon.Show_MsgBox(1, strMsg);
		return TRUE;
	}
	return TRUE;
}
