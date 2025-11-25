// ManualIndexDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualIndexDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"

// CManualIndexDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualIndexDlg, CDialogEx)

CManualIndexDlg::CManualIndexDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualIndexDlg::IDD, pParent)
{
}

CManualIndexDlg::~CManualIndexDlg()
{
}

void CManualIndexDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 30; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 23; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 23; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_MAIN_INDEX_R_0 + i, m_btnMainIndexR[i]);
	DDX_Control(pDX, IDC_STC_MAIN_INDEX_POS, m_stcMainIndexPos);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_MAIN_INDEX_POS_0 + i, m_ledMainIndexPos[i]);
	for (int i = 0; i < 26; i++) DDX_Control(pDX, IDC_BTN_MAIN_IDX_VAC_IO_0 + i, m_btnMainIdxVacIo[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_LED_MAIN_IDX_VAC_IO_0 + i, m_ledMainIdxVacIo[i]);
	for (int i = 0; i < 12; i++) DDX_Control(pDX, IDC_STC_MAIN_IDX_JIG_NO_0 + i, m_stcMainIdxJigNo[i]);
	for (int i = 0; i < 11; i++) DDX_Control(pDX, IDC_BTN_MAIN_IDX_REMOVE_0 + i, m_btnMainIdxRemove[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_FORMING_X1_0 + i, m_btnFormingX1[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_FORMING_X2_0 + i, m_btnFormingX2[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_BTN_FORMING_Z1_0 + i, m_btnFormingZ1[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_FORMING_Z2_0 + i, m_btnFormingZ2[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_TOP1_Z_0 + i, m_btnVisionTop1Z[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_ANGLE1_Z_0 + i, m_btnVisionAngle1Z[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_ANGLE2_Z_0 + i, m_btnVisionAngle2Z[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_SIDE1_Z_0 + i, m_btnVisionSide1Z[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_SIDE2_Z_0 + i, m_btnVisionSide2Z[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_TOP2_Z_0 + i, m_btnVisionTop2Z[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_ANGLE3_Z_0 + i, m_btnVisionAngle3Z[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_WI3D_Z_0 + i, m_btnVisionWi3DZ[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_SIDE3_Z_0 + i, m_btnVisionSide3Z[i]);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_BTN_VISION_SIDE4_Z_0 + i, m_btnVisionSide4Z[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_ANGLE12_TURN_A_0 + i, m_btnAngle12TurnA[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_ANGLE12_STOP_Z_0 + i, m_btnAngle12StopZ[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_SIDE12_TURN_A_0 + i, m_btnSide12TurnA[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_SIDE12_STOP_Z_0 + i, m_btnSide12StopZ[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_A3_WI_TURN_A_0 + i, m_btnA3WiTurnA[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_A3_WI_STOP_Z_0 + i, m_btnA3WiStopZ[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_SIDE34_TURN_A_0 + i, m_btnSide34TurnA[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_BTN_SIDE34_STIF_Z_0 + i, m_btnSide34StifZ[i]);
	DDX_Control(pDX, IDC_BTN_VISION_ALL_Z, m_btnVisionAllZ);
	DDX_Control(pDX, IDC_LED_MAIN_IDX_ION_IO, m_ledMainIdxIonIo);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_BTN_MAIN_IDX_ION_IO_0 + i, m_btnMainIdxIonIo[i]);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_BTN_INDEX_PART_IO_0 + i, m_btnIndexPartIo[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_LED_INDEX_PART_IO_0 + i, m_ledIndexPartIo[i]);
}

BEGIN_MESSAGE_MAP(CManualIndexDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MAIN_INDEX_R_0, IDC_BTN_MAIN_INDEX_R_1, OnBtnMainIndexRClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MAIN_IDX_VAC_IO_0, IDC_BTN_MAIN_IDX_VAC_IO_25, OnBtnMainIdxVacIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MAIN_IDX_REMOVE_0, IDC_BTN_MAIN_IDX_REMOVE_10, OnBtnMainIdxRemoveClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_FORMING_X1_0, IDC_BTN_FORMING_X1_1, OnBtnFormingX1Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_FORMING_X2_0, IDC_BTN_FORMING_X2_2, OnBtnFormingX2Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_FORMING_Z1_0, IDC_BTN_FORMING_Z1_2, OnBtnFormingZ1Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_FORMING_Z2_0, IDC_BTN_FORMING_Z2_1, OnBtnFormingZ2Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_TOP1_Z_0, IDC_BTN_VISION_TOP1_Z_0, OnBtnVisionTop1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_ANGLE1_Z_0, IDC_BTN_VISION_ANGLE1_Z_0, OnBtnVisionAngle1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_ANGLE2_Z_0, IDC_BTN_VISION_ANGLE2_Z_0, OnBtnVisionAngle2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_SIDE1_Z_0, IDC_BTN_VISION_SIDE1_Z_0, OnBtnVisionSide1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_SIDE2_Z_0, IDC_BTN_VISION_SIDE2_Z_0, OnBtnVisionSide2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_TOP2_Z_0, IDC_BTN_VISION_TOP2_Z_0, OnBtnVisionTop2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_ANGLE3_Z_0, IDC_BTN_VISION_ANGLE3_Z_0, OnBtnVisionAngle3ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_WI3D_Z_0, IDC_BTN_VISION_WI3D_Z_0, OnBtnVisionWi3DZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_SIDE3_Z_0, IDC_BTN_VISION_SIDE3_Z_0, OnBtnVisionSide3ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_VISION_SIDE4_Z_0, IDC_BTN_VISION_SIDE4_Z_0, OnBtnVisionSide4ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ANGLE12_TURN_A_0, IDC_BTN_ANGLE12_TURN_A_1, OnBtnAngle12TurnAClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ANGLE12_STOP_Z_0, IDC_BTN_ANGLE12_STOP_Z_1, OnBtnAngle12StopZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SIDE12_TURN_A_0, IDC_BTN_SIDE12_TURN_A_1, OnBtnSide12TurnAClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SIDE12_STOP_Z_0, IDC_BTN_SIDE12_STOP_Z_1, OnBtnSide12StopZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_A3_WI_TURN_A_0, IDC_BTN_A3_WI_TURN_A_1, OnBtnA3WiTurnAClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_A3_WI_STOP_Z_0, IDC_BTN_A3_WI_STOP_Z_1, OnBtnA3WiStopZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SIDE34_TURN_A_0, IDC_BTN_SIDE34_TURN_A_1, OnBtnSide34TurnAClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_SIDE34_STIF_Z_0, IDC_BTN_SIDE34_STIF_Z_1, OnBtnSide34StifZClick)
	ON_BN_CLICKED(IDC_BTN_VISION_ALL_Z, &CManualIndexDlg::OnBnClickedBtnVisionAllZ)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_MAIN_IDX_ION_IO_0, IDC_BTN_MAIN_IDX_ION_IO_3, OnBtnMainIdxIonIoClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INDEX_PART_IO_0, IDC_BTN_INDEX_PART_IO_9, OnBtnIndexPartIoClick)
END_MESSAGE_MAP()

// CManualIndexDlg 메시지 처리기입니다.
BOOL CManualIndexDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualIndexDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualIndexDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_Status();

	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();
	for (int i = 0; i < 12; i++) {
		int nPos = g_objCommon.Get_MainIndexPos(i);
		if ((pDY03->nValue >> (nPos + 4)) & 1) m_stcMainIdxJigNo[i].Set_Color(RGB(0xFF, 0xFF, 0x00), RGB(0xFF, 0x00, 0x00));
		else m_stcMainIdxJigNo[i].Set_Color(RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	}

	m_strLog.Format("[Manual Index] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::Initial_Controls() 
{
	for (int i = 0; i < 3; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);		// Index
	for (int i = 3; i < 7; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);		// Forming
	for (int i = 7; i < 17; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0xD0), COLOR_DEFAULT);		// Vision
	for (int i = 17; i < 25; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0x10, 0x10, 0xD0), COLOR_DEFAULT);	// Turn/Stop
	m_Group[25].Init_Ctrl("Arial", 11, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);
	for (int i = 26; i < 30; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT);	// I/O
	for (int i = 0; i < 23; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i < 23; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i < 2; i++) m_btnMainIndexR[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_stcMainIndexPos.Init_Ctrl("Arial", 12, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	for (int i = 0; i < 4; i++) m_ledMainIndexPos[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 26; i++) m_btnMainIdxVacIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 12; i++) m_ledMainIdxVacIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i < 12; i++) m_stcMainIdxJigNo[i].Init_Ctrl("Arial", 12, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	for (int i = 0; i < 11; i++) m_btnMainIdxRemove[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnFormingX1[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnFormingX2[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 3; i++) m_btnFormingZ1[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnFormingZ2[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionTop1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionAngle1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionAngle2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionSide1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionSide2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionTop2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionAngle3Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionWi3DZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionSide3Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 1; i++) m_btnVisionSide4Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnAngle12TurnA[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnAngle12StopZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnSide12TurnA[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnSide12StopZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnA3WiTurnA[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnA3WiStopZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnSide34TurnA[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 2; i++) m_btnSide34StifZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_btnVisionAllZ.Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_ledMainIdxIonIo.Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emRed, CLedCS::em16);
	for (int i = 0; i < 4; i++) m_btnMainIdxIonIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 10; i++) m_btnIndexPartIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 5; i++) m_ledIndexPartIo[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CManualIndexDlg::Display_Status()
{
	double dPos;
	CString strPos;
	for (int i = 0; i < 2; i++) {
		dPos = g_objAJinAXL.Get_Position(AX_FORMING_X1 + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}

	for (int i = 0; i < 9; i++) {
		dPos = g_objAJinAXL.Get_Position(AX_MAIN_INDEX_R + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i + 2].SetWindowText(strPos);
	}

	for (int i = 0; i < 3; i++) {
		dPos = g_objAJinAXL.Get_Position(AX_FORMING_Z2 + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i + 11].SetWindowText(strPos);
	}

	for (int i = 0; i < 9; i++) {
		dPos = g_objAJinAXL.Get_Position(AX_SIDE34_STIF_Z + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i + 14].SetWindowText(strPos);
	}

	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	int nPos = g_objCommon.Get_MainIndexPos(1);	// Load Picker1 위치(Vacuum 1번 기준)
	strPos.Format("%d", nPos + 1);
	m_stcMainIndexPos.SetWindowText(strPos);

	for (int i = 0; i < 4; i++) m_ledMainIndexPos[i].Set_On((pDX03->nValue >> i) & 1);
	for (int i = 0; i < 12; i++) m_ledMainIdxVacIo[i].Set_On(g_objCommon.Get_MainIndexVacuum(i));
	for (int i = 0; i < 12; i++) { strPos.Format("%d", g_objCommon.Get_MainIndexPos(i) + 1); m_stcMainIdxJigNo[i].SetWindowText(strPos); }

	m_ledMainIdxIonIo.Set_On(pDX02->iIndexIonizerAlarm);

	m_ledIndexPartIo[0].Set_On(pDX03->iIndexCleanJigUp);
	m_ledIndexPartIo[1].Set_On(pDX03->iIndexCleanJigDown);
	m_ledIndexPartIo[2].Set_On(pDX03->iIndexTop2CoverSide);
	m_ledIndexPartIo[3].Set_On(pDX03->iIndexTop2CoverCen);
	m_ledIndexPartIo[4].Set_On(pDX03->iIndexTop2CoverUp);
}

///////////////////////////////////////////////////////////////////////////////

void CManualIndexDlg::OnBtnMainIndexRClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_MAIN_INDEX_R)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_MAIN_INDEX_R_0;

	if (!g_objSequenceMain.Check_IndexCylinder()) {
		if (gData.nErrIndxNo==21) AfxMessageBox("Jig Clean Block Up 후 진행하세요.");
		if (gData.nErrIndxNo==22) AfxMessageBox("Top2 Cover Side 후 진행하세요.");
		if (gData.nErrIndxNo==23) AfxMessageBox("Top2 Cover Up 후 진행하세요.");
		return;
	}

	if (!g_objSequenceMain.Check_IndexMotion()) {
		if (gData.nErrIndxNo==31) AfxMessageBox("Load Picker 1 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==32) AfxMessageBox("Load Picker 2 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==33) AfxMessageBox("Transfer Picker Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==34) AfxMessageBox("Vision Top1 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==35) AfxMessageBox("Vision Top2 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==36) AfxMessageBox("Vision Angle1 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==37) AfxMessageBox("Vision Angle2 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==38) AfxMessageBox("Vision Side1 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==39) AfxMessageBox("Vision Side2 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==40) AfxMessageBox("Vision Side3 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==41) AfxMessageBox("Vision Side4 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==42) AfxMessageBox("Vision Angle3 Z축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==43) AfxMessageBox("Vision Wi3D Z축 Ready Up후 진행하세요.");
		if (gData.nErrIndxNo==44) AfxMessageBox("Forming Z1축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==45) AfxMessageBox("Forming Z2축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==46) AfxMessageBox("Forming X1축 Ready Bwd 후 진행하세요.");
		if (gData.nErrIndxNo==47) AfxMessageBox("Forming X2축 Ready Bwd 후 진행하세요.");
		if (gData.nErrIndxNo==48) AfxMessageBox("Angle12 Turn A축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==49) AfxMessageBox("Angle12 Stop Z축 Up 후 진행하세요.");
		if (gData.nErrIndxNo==50) AfxMessageBox("Side12 Turn A축 Ready Up 후 진행하세요.");
		if (gData.nErrIndxNo==51) AfxMessageBox("Side12 Stop Z축 Up 후 진행하세요.");
		if (gData.nErrIndxNo==52) AfxMessageBox("Side34 Turn A축 Ready 후 진행하세요.");
		if (gData.nErrIndxNo==53) AfxMessageBox("Side34 Stif Z축 Up 후 진행하세요.");
		if (gData.nErrIndxNo==54) AfxMessageBox("A3 WI Turn A축 Ready 후 진행하세요.");
		if (gData.nErrIndxNo==55) AfxMessageBox("A3 WI Stop Z축 Up 후 진행하세요.");
		return;
	}

 	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
 	if (nIndex == 0) g_objAJinAXL.Move_Relative(AX_MAIN_INDEX_R, pMoveData->dMainIndexR[0]);	// 정방향
 	if (nIndex == 1) g_objAJinAXL.Move_Relative(AX_MAIN_INDEX_R, -pMoveData->dMainIndexR[0]);	// 역방향

	m_strLog.Format("[Manual Index] Main Index R (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnMainIdxVacIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_MAIN_IDX_VAC_IO_0;

	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();
	if (nIndex == 24) { pDY03->nValue |= 0x0000FFF0; g_objAJinAXL.Write_Output(3); }	// All On
	if (nIndex == 25) { pDY03->nValue &= 0xFFFF000F; g_objAJinAXL.Write_Output(3); }	// All Off
	if (nIndex > -1 && nIndex < 12) g_objCommon.Set_MainIndexVacuumOn(nIndex);
	if (nIndex > 11 && nIndex < 24) g_objCommon.Set_MainIndexVacuumOff(nIndex-12);

	int nIdx = nIndex % 12;
	if		(nIndex < 12) m_stcMainIdxJigNo[nIdx].Set_Color(RGB(0xFF, 0xFF, 0x00), RGB(0xFF, 0x00, 0x00));
	else if (nIndex < 24) m_stcMainIdxJigNo[nIdx].Set_Color(RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	else if (nIndex < 25) { for (int i = 0; i < 12; i++) m_stcMainIdxJigNo[i].Set_Color(RGB(0xFF, 0xFF, 0x00), RGB(0xFF, 0x00, 0x00)); }
	else if (nIndex < 26) { for (int i = 0; i < 12; i++) m_stcMainIdxJigNo[i].Set_Color(RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00)); }

	m_strLog.Format("[Manual Index] Main Index Vacuum IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnMainIdxRemoveClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_MAIN_IDX_REMOVE_0;

	if (gData.InfoMainIndex[nIndex] == 0) {
		g_objCommon.Show_MsgBox(1, "모듈이 이미 제거 되었습니다.");
		return;
	}

	if (g_objCommon.Get_MainIndexVacuum(nIndex)) {
		g_objCommon.Show_MsgBox(1, "Vacuum On 상태의 모듈은 제거할 수 없습니다.");
		return;
	}

	if (nIndex == 0 || nIndex == 1) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_LOAD_PICKER) != 32) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (LoadPick(32)"); return; }
	} else if (nIndex == 2) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_FORMING) != 15) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (Forming(15)"); return; }
	} else if (nIndex == 3) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_TOP1) != 20) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (Top1(20)"); return; }
	} else if (nIndex == 4) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_ANGLE1) != 21) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (Angle1(21)"); return; }
	} else if (nIndex == 5) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_SIDE1) != 21) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (Side1(21)"); return; }
	} else if (nIndex == 6) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_TOP2) != 22) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (Top2(22)"); return; }
	} else if (nIndex == 7) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_ANGLE3) != 21) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (Angle3(21)"); return; }
	} else if (nIndex == 8) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_SIDE3) != 22) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (Side3(22)"); return; }
	} else if (nIndex == 9 || nIndex == 10) {
		if (g_objSequenceMain.Get_MainRunCase(AUTO_TRANS_PICKER) != 2) { g_objCommon.Show_MsgBox(1, "모듈은 제거할 수 없습니다. (TransPick(2)"); return; }
	}

	gData.InfoMainIndex[nIndex] = 0;
	g_objCommon.Set_MainIndexVacuumOff(nIndex);
	if (nIndex == 10) g_objSequenceMain.Set_MainRunCase(AUTO_TRANS_PICKER, 1);

	m_strLog.Format("[Manual Index] Main Index Remove (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnFormingX1Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_FORMING_X1)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_FORMING_X1_0;

	g_objCommon.Move_Position(AX_FORMING_X1, nIndex);

	m_strLog.Format("[Manual Index] Forming X1 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnFormingX2Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_FORMING_X2)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_FORMING_X2_0;

	g_objCommon.Move_Position(AX_FORMING_X2, nIndex);

	m_strLog.Format("[Manual Index] Forming X2 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnFormingZ1Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_FORMING_Z1)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_FORMING_Z1_0;

	if (nIndex == 0) {
		if (g_objCommon.Check_Position(AX_FORMING_X1, 0) && g_objCommon.Check_Position(AX_FORMING_X2, 0)) {
			g_objCommon.Move_Position(AX_FORMING_Z1, nIndex);
		} else {
			AfxMessageBox("Forming X1, X2 Ready Bwd 후 진행하세요.");
		}
	} else {
		g_objCommon.Move_Position(AX_FORMING_Z1, nIndex);
	}

	m_strLog.Format("[Manual Index] Forming Z1 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnFormingZ2Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_FORMING_Z2)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_FORMING_Z2_0;

	g_objCommon.Move_Position(AX_FORMING_Z2, nIndex);

	m_strLog.Format("[Manual Index] Forming Z2 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionTop1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_TOP1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_TOP1_Z, 0);

	m_strLog.Format("[Manual Index] Vision Top1 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionAngle1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_ANGLE1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_ANGLE1_Z, 0);

	m_strLog.Format("[Manual Index] Vision Angle1 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionAngle2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_ANGLE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_ANGLE2_Z, 0);

	m_strLog.Format("[Manual Index] Vision Angle2 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionSide1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_SIDE1_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_SIDE1_Z, 0);

	m_strLog.Format("[Manual Index] Vision Side1 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionSide2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_SIDE2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_SIDE2_Z, 0);

	m_strLog.Format("[Manual Index] Vision Side2 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionTop2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_TOP2_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_TOP2_Z, 0);

	m_strLog.Format("[Manual Index] Vision Top2 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionAngle3ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_ANGLE3_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_ANGLE3_Z, 0);

	m_strLog.Format("[Manual Index] Vision Angle3 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionWi3DZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_WI3D_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_WI3D_Z, 0);

	m_strLog.Format("[Manual Index] Vision Wi3D Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionSide3ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_SIDE3_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_SIDE3_Z, 0);

	m_strLog.Format("[Manual Index] Vision Side3 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnVisionSide4ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_SIDE4_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_SIDE4_Z, 0);

	m_strLog.Format("[Manual Index] Vision Side4 Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnAngle12TurnAClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ANGLE12_TURN_A)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_ANGLE12_TURN_A_0;

	if (nIndex == 0) {			// Ready
		g_objCommon.Move_Position(AX_ANGLE12_TURN_A, 0);

	} else if (nIndex == 1) {	// Push
		int nPos = g_objCommon.Get_MainIndexPos(4);		// Angle12 ==> InfoMainIndex[4]
		g_objCommon.Move_Position(AX_ANGLE12_TURN_A, nPos + 1);
	}

	m_strLog.Format("[Manual Index] Angle12 Turn A (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnAngle12StopZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_ANGLE12_STOP_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_ANGLE12_STOP_Z_0;

	g_objCommon.Move_Position(AX_ANGLE12_STOP_Z, nIndex);

	m_strLog.Format("[Manual Index] Angle12 Stop Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnSide12TurnAClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SIDE12_TURN_A)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SIDE12_TURN_A_0;

	if (nIndex == 0) {			// Ready
		g_objCommon.Move_Position(AX_SIDE12_TURN_A, 0);

	} else if (nIndex == 1) {	// Push
		int nPos = g_objCommon.Get_MainIndexPos(5);		// Side12 ==> InfoMainIndex[5]
		g_objCommon.Move_Position(AX_SIDE12_TURN_A, nPos + 1);
	}

	m_strLog.Format("[Manual Index] Side12 Turn A (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnSide12StopZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SIDE12_STOP_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SIDE12_STOP_Z_0;

	g_objCommon.Move_Position(AX_SIDE12_STOP_Z, nIndex);

	m_strLog.Format("[Manual Index] Side12 Stop Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnA3WiTurnAClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_A3_WI_TURN_A)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_A3_WI_TURN_A_0;

	if (nIndex == 0) {			// Ready
		g_objCommon.Move_Position(AX_A3_WI_TURN_A, 0);

	} else if (nIndex == 1) {	// Push
		int nPos = g_objCommon.Get_MainIndexPos(7);		// A3-Wi ==> InfoMainIndex[7]
		g_objCommon.Move_Position(AX_A3_WI_TURN_A, nPos + 1);
	}

	m_strLog.Format("[Manual Index] A3-WI Turn A (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnA3WiStopZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_A3_WI_STOP_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_A3_WI_STOP_Z_0;

	g_objCommon.Move_Position(AX_A3_WI_STOP_Z, nIndex);

	m_strLog.Format("[Manual Index] A3-WI Stop Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnSide34TurnAClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SIDE34_TURN_A)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SIDE34_TURN_A_0;

	if (nIndex == 0) {			// Ready
		g_objCommon.Move_Position(AX_SIDE34_TURN_A, 0);

	} else if (nIndex == 1) {	// Push
		int nPos = g_objCommon.Get_MainIndexPos(8);	// Side34 ==> InfoMainIndex[8]
		g_objCommon.Move_Position(AX_SIDE34_TURN_A, nPos + 1);
	}

	m_strLog.Format("[Manual Index] Side34 Turn A (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnSide34StifZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_SIDE34_STIF_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_SIDE34_STIF_Z_0;

	g_objCommon.Move_Position(AX_SIDE34_STIF_Z, nIndex);

	m_strLog.Format("[Manual Index] Side34 Stif Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBnClickedBtnVisionAllZ()
{
	if (!g_objAJinAXL.Is_Home(AX_VISION_TOP1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_ANGLE1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_ANGLE2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_SIDE1_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_SIDE2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_TOP2_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_ANGLE3_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_WI3D_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_SIDE3_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_VISION_SIDE4_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_FORMING_Z1)) return;
	if (!g_objAJinAXL.Is_Home(AX_FORMING_Z2)) return;
	if (!g_objAJinAXL.Is_Home(AX_FORMING_X1)) return;
	if (!g_objAJinAXL.Is_Home(AX_FORMING_X2)) return;
	if (!g_objAJinAXL.Is_Home(AX_ANGLE12_TURN_A)) return;
	if (!g_objAJinAXL.Is_Home(AX_ANGLE12_STOP_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SIDE12_TURN_A)) return;
	if (!g_objAJinAXL.Is_Home(AX_SIDE12_STOP_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_A3_WI_TURN_A)) return;
	if (!g_objAJinAXL.Is_Home(AX_A3_WI_STOP_Z)) return;
	if (!g_objAJinAXL.Is_Home(AX_SIDE34_TURN_A)) return;
	if (!g_objAJinAXL.Is_Home(AX_SIDE34_STIF_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	g_objCommon.Move_Position(AX_VISION_TOP1_Z, 0);
	g_objCommon.Move_Position(AX_VISION_ANGLE1_Z, 0);
	g_objCommon.Move_Position(AX_VISION_ANGLE2_Z, 0);
	g_objCommon.Move_Position(AX_VISION_SIDE1_Z, 0);
	g_objCommon.Move_Position(AX_VISION_SIDE2_Z, 0);
	g_objCommon.Move_Position(AX_VISION_TOP2_Z, 0);
	g_objCommon.Move_Position(AX_VISION_ANGLE3_Z, 0);
	g_objCommon.Move_Position(AX_VISION_WI3D_Z, 0);
	g_objCommon.Move_Position(AX_VISION_SIDE3_Z, 0);
	g_objCommon.Move_Position(AX_VISION_SIDE4_Z, 0);
	g_objCommon.Move_Position(AX_FORMING_Z1, 0);
	g_objCommon.Move_Position(AX_FORMING_Z2, 0);
	g_objCommon.Move_Position(AX_FORMING_X1, 0);
	g_objCommon.Move_Position(AX_FORMING_X2, 0);
	g_objCommon.Move_Position(AX_ANGLE12_TURN_A, 0);
	g_objCommon.Move_Position(AX_ANGLE12_STOP_Z, 0);
	g_objCommon.Move_Position(AX_SIDE12_TURN_A, 0);
	g_objCommon.Move_Position(AX_SIDE12_STOP_Z, 0);
	g_objCommon.Move_Position(AX_A3_WI_TURN_A, 0);
	g_objCommon.Move_Position(AX_A3_WI_STOP_Z, 0);
	g_objCommon.Move_Position(AX_SIDE34_TURN_A, 0);
	g_objCommon.Move_Position(AX_SIDE34_STIF_Z, 0);

	m_strLog.Format("[Manual Index] Vision All Z Click");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnMainIdxIonIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_MAIN_IDX_ION_IO_0;

	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();

	if (nIndex == 0) pDY02->oIndexIonizerAirBlow = TRUE;
	if (nIndex == 1) pDY02->oIndexIonizerAirBlow = FALSE;
	if (nIndex == 2) pDY02->oIndexIonizerDischarge = TRUE;
	if (nIndex == 3) pDY02->oIndexIonizerDischarge = FALSE;

	g_objAJinAXL.Write_Output(2);

	m_strLog.Format("[Manual Index] Main Index ION IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualIndexDlg::OnBtnIndexPartIoClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INDEX_PART_IO_0;

	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();
	
	if (nIndex == 0)  { pDY03->oIndexCleanJigUp = TRUE; pDY03->oIndexCleanJigDown = FALSE; }
	if (nIndex == 1)  { pDY03->oIndexCleanJigUp = FALSE; pDY03->oIndexCleanJigDown = TRUE; }
	if (nIndex == 2)  pDY03->oIndexCleanJigBlow = TRUE;
	if (nIndex == 3)  pDY03->oIndexCleanJigBlow = FALSE;
	if (nIndex == 4)  pDY03->oIndexCleanCmBlow = TRUE;
	if (nIndex == 5)  pDY03->oIndexCleanCmBlow = FALSE;
	if (nIndex == 6) { pDY03->oIndexTop2CoverSide = TRUE; pDY03->oIndexTop2CoverCen = FALSE; }
	if (nIndex == 7) { pDY03->oIndexTop2CoverSide = FALSE; pDY03->oIndexTop2CoverCen = TRUE; }
	if (nIndex == 8) { pDY03->oIndexTop2CoverUp = TRUE; pDY03->oIndexTop2CoverDown = FALSE; }
	if (nIndex == 9) { pDY03->oIndexTop2CoverUp = FALSE; pDY03->oIndexTop2CoverDown = TRUE; }

	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	if (nIndex == 6 || nIndex == 7) {
		if (!pDX03->iIndexTop2CoverUp) {
			AfxMessageBox(_T("Top2 Cover Up 후 진행하세요."));
			return;
		}
	}

	g_objAJinAXL.Write_Output(3);
	//g_objAJinAXL.Write_Output(4);

	m_strLog.Format("[Manual Index] Index Part IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
