// ManualInspDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ManualInspDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "Common.h"
#include "SequenceMain.h"

// CManualInspDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualInspDlg, CDialogEx)

CManualInspDlg::CManualInspDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManualInspDlg::IDD, pParent)
{
}

CManualInspDlg::~CManualInspDlg()
{
}

void CManualInspDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i <12; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_BTN_INSP_X1_0 + i, m_btnInspectionX1[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_BTN_INSP_X2_0 + i, m_btnInspectionX2[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_BTN_INSP_X3_0 + i, m_btnInspectionX3[i]);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_BTN_INSP_X4_0 + i, m_btnInspectionX4[i]);

	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_TOP1_Z_0 + i, m_btnTop1Z[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_TOP2_Z_0 + i, m_btnTop2Z[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_TOP1_LIGHT_0 + i, m_btnTop1LightZ[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_BTN_TOP1_ANGLE_0 + i, m_btnTop1AngleY[i]);

	for (int i = 0; i <9; i++) DDX_Control(pDX, IDC_BTN_INSP1_VAC_ON_0 + i, m_btnInsp1VaccumOn[i]);
	for (int i = 0; i <9; i++) DDX_Control(pDX, IDC_BTN_INSP1_VAC_OFF_0 + i, m_btnInsp1VaccumOff[i]);
	for (int i = 0; i <9; i++) DDX_Control(pDX, IDC_BTN_INSP2_VACON_0 + i, m_btnInsp2VaccumOn[i]);
	for (int i = 0; i <9; i++) DDX_Control(pDX, IDC_BTN_INSP2_VACOF_0 + i, m_btnInsp2VaccumOff[i]);
	for (int i = 0; i <9; i++) DDX_Control(pDX, IDC_BTN_INSP3_VACON_0 + i, m_btnInsp3VaccumOn[i]);
	for (int i = 0; i <9; i++) DDX_Control(pDX, IDC_BTN_INSP3_VACOF_0 + i, m_btnInsp3VaccumOff[i]);
	for (int i = 0; i <9; i++) DDX_Control(pDX, IDC_BTN_INSP4_VACON_0 + i, m_btnInsp4VaccumOn[i]);
	for (int i = 0; i <9; i++) DDX_Control(pDX, IDC_BTN_INSP4_VACOF_0 + i, m_btnInsp4VaccumOff[i]);

	for (int i = 0; i <8; i++) DDX_Control(pDX, IDC_LED_INSP1_VAC_ON_0 + i, m_ledInsp1VacuumOn[i]);
	for (int i = 0; i <8; i++) DDX_Control(pDX, IDC_LED_INSP2_VACON_0 + i, m_ledInsp2VacuumOn[i]);
	for (int i = 0; i <8; i++) DDX_Control(pDX, IDC_LED_INSP3_VACON_0 + i, m_ledInsp3VacuumOn[i]);
	for (int i = 0; i <8; i++) DDX_Control(pDX, IDC_LED_INSP4_VACON_0 + i, m_ledInsp4VacuumOn[i]);

	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_BTN_INSP1_IO_0 + i, m_btnInsp1IO[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_BTN_INSP2_IO_0 + i, m_btnInsp2IO[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_BTN_INSP3_IO_0 + i, m_btnInsp3IO[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_BTN_INSP4_IO_0 + i, m_btnInsp4IO[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_LED_INSP1_IO_0 + i, m_ledInsp1IO[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_LED_INSP2_IO_0 + i, m_ledInsp2IO[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_LED_INSP3_IO_0 + i, m_ledInsp3IO[i]);
	for (int i = 0; i <6; i++) DDX_Control(pDX, IDC_LED_INSP4_IO_0 + i, m_ledInsp4IO[i]);
}

BEGIN_MESSAGE_MAP(CManualInspDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP_X1_0, IDC_BTN_INSP_X1_6, OnBtnInspectionX1Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP_X2_0, IDC_BTN_INSP_X2_6, OnBtnInspectionX2Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP_X3_0, IDC_BTN_INSP_X3_6, OnBtnInspectionX3Click)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP_X4_0, IDC_BTN_INSP_X4_6, OnBtnInspectionX4Click)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TOP1_Z_0, IDC_BTN_TOP1_Z_4, OnBtnTop1ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TOP2_Z_0, IDC_BTN_TOP2_Z_4, OnBtnTop2ZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TOP1_LIGHT_0, IDC_BTN_TOP1_LIGHT_4, OnBtnTop1LightZClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_TOP1_ANGLE_0, IDC_BTN_TOP1_ANGLE_4, OnBtnTop1AngleYClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP1_IO_0, IDC_BTN_INSP1_IO_5, OnBtnInsp1IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP2_IO_0, IDC_BTN_INSP2_IO_5, OnBtnInsp2IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP3_IO_0, IDC_BTN_INSP3_IO_5, OnBtnInsp3IOClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP4_IO_0, IDC_BTN_INSP4_IO_5, OnBtnInsp4IOClick)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP1_VAC_ON_0, IDC_BTN_INSP1_VAC_ON_8, OnBtnInsp1VacuumOnClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP1_VAC_OFF_0, IDC_BTN_INSP1_VAC_OFF_8, OnBtnInsp1VacuumOffClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP2_VACON_0, IDC_BTN_INSP2_VACON_8, OnBtnInsp2VacuumOnClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP2_VACOF_0, IDC_BTN_INSP2_VACOF_8, OnBtnInsp2VacuumOffClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP3_VACON_0, IDC_BTN_INSP3_VACON_8, OnBtnInsp3VacuumOnClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP3_VACOF_0, IDC_BTN_INSP3_VACOF_8, OnBtnInsp3VacuumOffClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP4_VACON_0, IDC_BTN_INSP4_VACON_8, OnBtnInsp4VacuumOnClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_INSP4_VACOF_0, IDC_BTN_INSP4_VACOF_8, OnBtnInsp4VacuumOffClick)

END_MESSAGE_MAP()

// CManualInspDlg 메시지 처리기입니다.
BOOL CManualInspDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CManualInspDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CManualInspDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

#ifdef NEW_FINAL
		m_Group[11].ShowWindow(FALSE);
		m_Label[6].ShowWindow(FALSE);
		m_stcAxisPos[6].ShowWindow(FALSE);
		for(int i=0; i<5; i++) m_btnTop1LightZ[i].ShowWindow(FALSE);
		m_Group[9].ShowWindow(FALSE);
		m_Label[7].ShowWindow(FALSE);
		m_stcAxisPos[7].ShowWindow(FALSE);
		for(int i=0; i<5; i++) m_btnTop1AngleY[i].ShowWindow(FALSE);
#endif

	Display_Status();

	m_strLog.Format("[Manual inspection] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualInspDlg::Initial_Controls() 
{
	for (int i = 0; i <8; i++) m_Group[i].Init_Ctrl("Arial", 11, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 8; i <12; i++) m_Group[i].Init_Ctrl("Arial", 9, TRUE, RGB(0xD0, 0x10, 0x10), COLOR_DEFAULT);
	for (int i = 0; i <8; i++) m_Label[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, RGB(0xB0, 0xB0, 0xB0));
	for (int i = 0; i <8; i++) m_stcAxisPos[i].Init_Ctrl("Arial", 10, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x10, 0x10, 0x60));
	for (int i = 0; i <7; i++) m_btnInspectionX1[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <7; i++) m_btnInspectionX2[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <7; i++) m_btnInspectionX3[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <7; i++) m_btnInspectionX4[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);

	for (int i = 0; i <5; i++) m_btnTop1Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <5; i++) m_btnTop2Z[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <5; i++) m_btnTop1LightZ[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <5; i++) m_btnTop1AngleY[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);

	for (int i = 0; i <6; i++) m_btnInsp1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <6; i++) m_btnInsp2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <6; i++) m_btnInsp3IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <6; i++) m_btnInsp4IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <6; i++) m_ledInsp1IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <6; i++) m_ledInsp2IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <6; i++) m_ledInsp3IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <6; i++) m_ledInsp4IO[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);

	for (int i = 0; i <9; i++) m_btnInsp1VaccumOn[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <9; i++) m_btnInsp1VaccumOff[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <9; i++) m_btnInsp2VaccumOn[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <9; i++) m_btnInsp2VaccumOff[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <9; i++) m_btnInsp3VaccumOn[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <9; i++) m_btnInsp3VaccumOff[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <9; i++) m_btnInsp4VaccumOn[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	for (int i = 0; i <9; i++) m_btnInsp4VaccumOff[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);

	for (int i = 0; i <8; i++) m_ledInsp1VacuumOn[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <8; i++) m_ledInsp2VacuumOn[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <8; i++) m_ledInsp3VacuumOn[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
	for (int i = 0; i <8; i++) m_ledInsp4VacuumOn[i].Init_Ctrl("Arial", 10, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em16);
}

void CManualInspDlg::Display_Status()
{
	CString strPos;
	double  dPos;
	for (int i = 0; i < 4; i++) {
		dPos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X1 + i);
		strPos.Format("%0.3lf", dPos);
		m_stcAxisPos[i].SetWindowText(strPos);
	}
	dPos = g_objAJinAXL.Get_Position(AX_TOP1_VISION_Z);	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[4].SetWindowText(strPos);
	dPos = g_objAJinAXL.Get_Position(AX_TOP2_VISION_Z);	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[5].SetWindowText(strPos);
	dPos = g_objAJinAXL.Get_Position(AX_TOP1_LIGHT_Z);	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[6].SetWindowText(strPos);
	dPos = g_objAJinAXL.Get_Position(AX_TOP1_ANGLE_Y);	strPos.Format("%0.3lf", dPos);
	m_stcAxisPos[7].SetWindowText(strPos);

	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();

	m_ledInsp1VacuumOn[0].Set_On(pDX07->iInspectStage1Vac1On);
	m_ledInsp1VacuumOn[1].Set_On(pDX07->iInspectStage1Vac2On);
	m_ledInsp1VacuumOn[2].Set_On(pDX07->iInspectStage1Vac3On);
	m_ledInsp1VacuumOn[3].Set_On(pDX07->iInspectStage1Vac4On);
	m_ledInsp1VacuumOn[4].Set_On(pDX07->iInspectStage1Vac5On);
	m_ledInsp1VacuumOn[5].Set_On(pDX07->iInspectStage1Vac6On);
	m_ledInsp1VacuumOn[6].Set_On(pDX07->iInspectStage1Vac7On);
	m_ledInsp1VacuumOn[7].Set_On(pDX07->iInspectStage1Vac8On);

	m_ledInsp2VacuumOn[0].Set_On(pDX07->iInspectStage2Vac1On);
	m_ledInsp2VacuumOn[1].Set_On(pDX07->iInspectStage2Vac2On);
	m_ledInsp2VacuumOn[2].Set_On(pDX07->iInspectStage2Vac3On);
	m_ledInsp2VacuumOn[3].Set_On(pDX07->iInspectStage2Vac4On);
	m_ledInsp2VacuumOn[4].Set_On(pDX07->iInspectStage2Vac5On);
	m_ledInsp2VacuumOn[5].Set_On(pDX07->iInspectStage2Vac6On);
	m_ledInsp2VacuumOn[6].Set_On(pDX07->iInspectStage2Vac7On);
	m_ledInsp2VacuumOn[7].Set_On(pDX07->iInspectStage2Vac8On);

	m_ledInsp3VacuumOn[0].Set_On(pDX08->iInspectStage3Vac1On);
	m_ledInsp3VacuumOn[1].Set_On(pDX08->iInspectStage3Vac2On);
	m_ledInsp3VacuumOn[2].Set_On(pDX08->iInspectStage3Vac3On);
	m_ledInsp3VacuumOn[3].Set_On(pDX08->iInspectStage3Vac4On);
	m_ledInsp3VacuumOn[4].Set_On(pDX08->iInspectStage3Vac5On);
	m_ledInsp3VacuumOn[5].Set_On(pDX08->iInspectStage3Vac6On);
	m_ledInsp3VacuumOn[6].Set_On(pDX08->iInspectStage3Vac7On);
	m_ledInsp3VacuumOn[7].Set_On(pDX08->iInspectStage3Vac8On);

	m_ledInsp4VacuumOn[0].Set_On(pDX08->iInspectStage4Vac1On);
	m_ledInsp4VacuumOn[1].Set_On(pDX08->iInspectStage4Vac2On);
	m_ledInsp4VacuumOn[2].Set_On(pDX08->iInspectStage4Vac3On);
	m_ledInsp4VacuumOn[3].Set_On(pDX08->iInspectStage4Vac4On);
	m_ledInsp4VacuumOn[4].Set_On(pDX08->iInspectStage4Vac5On);
	m_ledInsp4VacuumOn[5].Set_On(pDX08->iInspectStage4Vac6On);
	m_ledInsp4VacuumOn[6].Set_On(pDX08->iInspectStage4Vac7On);
	m_ledInsp4VacuumOn[7].Set_On(pDX08->iInspectStage4Vac8On);

	m_ledInsp1IO[0].Set_On(pDX07->iInspectStage1Up);
	m_ledInsp1IO[1].Set_On(pDX07->iInspectStage1Down);
	m_ledInsp1IO[2].Set_On(pDX07->iInspectStage1Deg0);
	m_ledInsp1IO[3].Set_On(pDX07->iInspectStage1Deg90);
	m_ledInsp1IO[4].Set_On(pDX07->iInspectStage1Yin);
	m_ledInsp1IO[5].Set_On(pDX07->iInspectStage1YOut);

	m_ledInsp2IO[0].Set_On(pDX07->iInspectStage2Up);
	m_ledInsp2IO[1].Set_On(pDX07->iInspectStage2Down);
	m_ledInsp2IO[2].Set_On(pDX07->iInspectStage2Deg0);
	m_ledInsp2IO[3].Set_On(pDX07->iInspectStage2Deg90);

	m_ledInsp3IO[0].Set_On(pDX08->iInspectStage3Up);
	m_ledInsp3IO[1].Set_On(pDX08->iInspectStage3Down);
	m_ledInsp3IO[2].Set_On(pDX08->iInspectStage3Deg0);
	m_ledInsp3IO[3].Set_On(pDX08->iInspectStage3Deg90);

	m_ledInsp4IO[0].Set_On(pDX08->iInspectStage4Up);
	m_ledInsp4IO[1].Set_On(pDX08->iInspectStage4Down);
	m_ledInsp4IO[2].Set_On(pDX08->iInspectStage4Deg0);
	m_ledInsp4IO[3].Set_On(pDX08->iInspectStage4Deg90);
	m_ledInsp4IO[4].Set_On(pDX08->iInspectStage4Yin);
	m_ledInsp4IO[5].Set_On(pDX08->iInspectStage4YOut);

}

///////////////////////////////////////////////////////////////////////////////
void CManualInspDlg::OnBtnInspectionX1Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_INSPECT_STAGE_X1)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_INSP_X1_0;
	if (Check_VisionStage(1, nIndex)==FALSE) return;

	if (nIndex == 5 || nIndex == 6) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 5 ? -1 : 1);
		double dMove = pEquipData->dPitchTop * nDir;
		g_objAJinAXL.Move_Relative(AX_INSPECT_STAGE_X1, dMove);
	} else {
		g_objCommon.Move_Position(AX_INSPECT_STAGE_X1, nIndex);
	}

	m_strLog.Format("[Manual Inspection] Inspection X1 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
	Set_VisionPostion(1, nIndex);
}
void CManualInspDlg::OnBtnInspectionX2Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_INSPECT_STAGE_X2)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_INSP_X2_0;
	if (Check_VisionStage(2, nIndex)==FALSE) return;

	if (nIndex == 5 || nIndex == 6) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 5 ? -1 : 1);
		double dMove = pEquipData->dPitchTop * nDir;
		g_objAJinAXL.Move_Relative(AX_INSPECT_STAGE_X2, dMove);
	} else {
		g_objCommon.Move_Position(AX_INSPECT_STAGE_X2, nIndex);
	}

	m_strLog.Format("[Manual Inspection] Inspection X2 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
	Set_VisionPostion(2, nIndex);
}
void CManualInspDlg::OnBtnInspectionX3Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_INSPECT_STAGE_X3)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_INSP_X3_0;
	if (Check_VisionStage(3, nIndex)==FALSE) return;

	if (nIndex == 5 || nIndex == 6) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 5 ? -1 : 1);
		double dMove = pEquipData->dPitchTop * nDir;
		g_objAJinAXL.Move_Relative(AX_INSPECT_STAGE_X3, dMove);
	} else {
		g_objCommon.Move_Position(AX_INSPECT_STAGE_X3, nIndex);
	}

	m_strLog.Format("[Manual Inspection] Inspection X3 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
	Set_VisionPostion(3, nIndex);
}
void CManualInspDlg::OnBtnInspectionX4Click(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_INSPECT_STAGE_X4)) return;
	if (!g_objCommon.Check_MainDoor()) return;

	int nIndex = nID - IDC_BTN_INSP_X4_0;
	if (Check_VisionStage(4, nIndex)==FALSE) return;

	if (nIndex == 5 || nIndex == 6) {
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		int nDir = (nIndex == 5 ? -1 : 1);
		double dMove = pEquipData->dPitchTop * nDir;
		g_objAJinAXL.Move_Relative(AX_INSPECT_STAGE_X4, dMove);
	} else {
		g_objCommon.Move_Position(AX_INSPECT_STAGE_X4, nIndex);
	}

	m_strLog.Format("[Manual Inspection] Inspection X4 (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
	Set_VisionPostion(4, nIndex);
}

void CManualInspDlg::OnBtnTop1ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TOP1_VISION_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TOP1_Z_0;

#ifdef NEW_FINAL
#else
	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 1)) {
			AfxMessageBox(_T("Top1 Angle Y축이 Vision 위치에서 진행이 가능합니다..."));
			return;
		}
	}
#endif
	g_objCommon.Move_Position(AX_TOP1_VISION_Z, nIndex);

	m_strLog.Format("[Manual Inspection] Top1 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnTop2ZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TOP2_VISION_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TOP2_Z_0;

	g_objCommon.Move_Position(AX_TOP2_VISION_Z, nIndex);

	m_strLog.Format("[Manual Inspection] Top2 Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnTop1LightZClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TOP1_LIGHT_Z)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TOP1_LIGHT_0;

	if (nIndex == 0 || nIndex == 1) {
		if (!g_objCommon.Check_Position(AX_TOP1_ANGLE_Y, 1)) {
			AfxMessageBox(_T("Top1 Angle Y축이 Vision 위치에서 진행이 가능합니다..."));
			return;
		}
	}
	g_objCommon.Move_Position(AX_TOP1_LIGHT_Z, nIndex);

	m_strLog.Format("[Manual Inspection] Top1 Light Z (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnTop1AngleYClick(UINT nID)
{
	if (!g_objAJinAXL.Is_Home(AX_TOP1_ANGLE_Y)) return;
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_TOP1_ANGLE_0;

	if (nIndex == 2) {
		if (!g_objCommon.Check_Position(AX_TOP1_LIGHT_Z, 2)) {
			AfxMessageBox(_T("Top1 Light Z축이 Angle 위치에서 진행이 가능합니다..."));
			return;
		}
		if (!g_objCommon.Check_Position(AX_TOP1_VISION_Z, 2)) {
			AfxMessageBox(_T("Top1 Focus Z축이 Angle 위치에서 진행이 가능합니다..."));
			return;
		}
	}

	g_objCommon.Move_Position(AX_TOP1_ANGLE_Y, nIndex);

	m_strLog.Format("[Manual Inspection] Top1 Angle Y (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualInspDlg::OnBtnInsp1VacuumOnClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP1_VAC_ON_0 + 1;

	if (nIndex == 9) nIndex = 0;
	g_objCommon.Set_VisionVacuumOn(1, nIndex);

	m_strLog.Format("[Manual Inspection] Inspection 1 Vacuum On (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnInsp1VacuumOffClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP1_VAC_OFF_0 + 1;

	if (nIndex == 9) nIndex = 0;
	g_objCommon.Set_VisionVacuumOff(1, nIndex);

	m_strLog.Format("[Manual Inspection] Inspection 1 Vacuum Off (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnInsp2VacuumOnClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP2_VACON_0 + 1;

	if (nIndex == 9) nIndex = 0;
	g_objCommon.Set_VisionVacuumOn(2, nIndex);

	m_strLog.Format("[Manual Inspection] Inspection 2 Vacuum On (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnInsp2VacuumOffClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP2_VACOF_0 + 1;

	if (nIndex == 9) nIndex = 0;
	g_objCommon.Set_VisionVacuumOff(2, nIndex);

	m_strLog.Format("[Manual Inspection] Inspection 2 Vacuum Off (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnInsp3VacuumOnClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP3_VACON_0 + 1;

	if (nIndex == 9) nIndex = 0;
	g_objCommon.Set_VisionVacuumOn(3, nIndex);

	m_strLog.Format("[Manual Inspection] Inspection 3 Vacuum On (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnInsp3VacuumOffClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP3_VACOF_0 + 1;

	if (nIndex == 9) nIndex = 0;
	g_objCommon.Set_VisionVacuumOff(3, nIndex);

	m_strLog.Format("[Manual Inspection] Inspection 3 Vacuum Off (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnInsp4VacuumOnClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP4_VACON_0 + 1;

	if (nIndex == 9) nIndex = 0;
	g_objCommon.Set_VisionVacuumOn(4, nIndex);

	m_strLog.Format("[Manual Inspection] Inspection 4 Vacuum On (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}
void CManualInspDlg::OnBtnInsp4VacuumOffClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP4_VACOF_0 + 1;

	if (nIndex == 9) nIndex = 0;
	g_objCommon.Set_VisionVacuumOff(4, nIndex);

	m_strLog.Format("[Manual Inspection] Inspection 4 Vacuum Off (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CManualInspDlg::OnBtnInsp1IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP1_IO_0;

	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
	DY_DATA_07 *pDY07 = g_objAJinAXL.Get_pDY07();

	if (nIndex == 0 || nIndex == 1 || nIndex == 4 || nIndex == 5) {
		if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 1)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 2)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 4)) {
			AfxMessageBox(_T("Stage 동작은 정위치에서만(Aling,Top1,TOP2,Buffer,Unload) 작업 가능합니다....."));
			return;
		}
	}
	if (nIndex == 0 || nIndex == 1) { //Up/Down
		if (pDX07->iInspectStage1Yin) {
			if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)) {
				AfxMessageBox(_T("Stage Up/Down은 Align/Unload 또는 Stage_Out 위치에서만 가능합니다....."));
				return;
			}
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0)) {
				if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
					AfxMessageBox(_T("Stage간 Interlock으로 작업을 진행할수 었습니다..."));
					return;
				}
			}
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)) {
				if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
					AfxMessageBox(_T("Stage간 Interlock으로 작업을 진행할수 었습니다..."));
					return;
				}
			}
		} else {
			if (nIndex == 0) {
				AfxMessageBox(_T("Stage In상태에서만 작업가능합니다....."));
				return;
			}
		}
	}
	if (nIndex == 4 || nIndex == 5) { //YIn/Out
		if (pDX07->iInspectStage1Up) {
			AfxMessageBox(_T("Stage Down시에만 In-Out 작업 가능합니다....."));
			return;
		}
	}
	if (nIndex == 4) { //YIn
		if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)) {
			AfxMessageBox(_T("Stage Align, Unload 위치에서 In 작업 가능합니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0)) {
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
				AfxMessageBox(_T("Align위치에 Stage가 있어 In 작업을 할수없습니다...."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)) {
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
				AfxMessageBox(_T("Align위치에 Stage가 있어 In 작업을 할수없습니다...."));
				return;
			}
		}
	}

	if (nIndex == 0) { pDY07->oInspectStage1Up = TRUE;		pDY07->oInspectStage1Down = FALSE; }
	if (nIndex == 1) { pDY07->oInspectStage1Up = FALSE;		pDY07->oInspectStage1Down = TRUE; }
	if (nIndex == 2) { pDY07->oInspectStage1Deg0 = TRUE;	pDY07->oInspectStage1Deg90 = FALSE; }
	if (nIndex == 3) { pDY07->oInspectStage1Deg0 = FALSE;	pDY07->oInspectStage1Deg90 = TRUE; }
	if (nIndex == 4) { pDY07->oInspectStage1Yin = TRUE;		pDY07->oInspectStage1YOut = FALSE; }
	if (nIndex == 5) { pDY07->oInspectStage1Yin = FALSE;	pDY07->oInspectStage1YOut = TRUE; }
					
	g_objAJinAXL.Write_Output(7);

	m_strLog.Format("[Manual Inspection] Inspection 1 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
	Set_VisionUpDown(1, nIndex);
}
void CManualInspDlg::OnBtnInsp2IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP2_IO_0;

	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
	DY_DATA_07 *pDY07 = g_objAJinAXL.Get_pDY07();

	if (nIndex == 0 || nIndex == 1 || nIndex == 4 || nIndex == 5) {
		if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 1)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 2)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 4)) {
			AfxMessageBox(_T("Stage 동작은 정위치에서만(Aling,Top1,TOP2,Buffer,Unload) 작업 가능합니다....."));
			return;
		}
	}
	if (nIndex == 0 || nIndex == 1) { //Up/Down
		if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3)) {
			AfxMessageBox(_T("Stage Up/Down은 Align/Unload 또는 Stage_Out 위치에서만 가능합니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0)) {
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
				AfxMessageBox(_T("Stage간 Interlock으로 작업을 진행할수 었습니다..."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3)) {
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
				AfxMessageBox(_T("Stage간 Interlock으로 작업을 진행할수 었습니다..."));
				return;
			}
		}
	}

	if (nIndex == 0) { pDY07->oInspectStage2Up = TRUE;		pDY07->oInspectStage2Down = FALSE; }
	if (nIndex == 1) { pDY07->oInspectStage2Up = FALSE;		pDY07->oInspectStage2Down = TRUE; }
	if (nIndex == 2) { pDY07->oInspectStage2Deg0 = TRUE;	pDY07->oInspectStage2Deg90 = FALSE; }
	if (nIndex == 3) { pDY07->oInspectStage2Deg0 = FALSE;	pDY07->oInspectStage2Deg90 = TRUE; }
					
	g_objAJinAXL.Write_Output(7);

	m_strLog.Format("[Manual Inspection] Inspection 2 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
	Set_VisionUpDown(2, nIndex);
}
void CManualInspDlg::OnBtnInsp3IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP3_IO_0;

	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
	DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();

	if (nIndex == 0 || nIndex == 1 || nIndex == 4 || nIndex == 5) {
		if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 1)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 2)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 4)) {
			AfxMessageBox(_T("Stage 동작은 정위치에서만(Aling,Top1,TOP2,Buffer,Unload) 작업 가능합니다....."));
			return;
		}
	}
	if (nIndex == 0 || nIndex == 1) { //Up/Down
		if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3)) {
			AfxMessageBox(_T("Stage Up/Down은 Align/Unload 또는 Stage_Out 위치에서만 가능합니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0)) {
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
				AfxMessageBox(_T("Stage간 Interlock으로 작업을 진행할수 었습니다..."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3)) {
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
				AfxMessageBox(_T("Stage간 Interlock으로 작업을 진행할수 었습니다..."));
				return;
			}
		}
	}

	if (nIndex == 0) { pDY08->oInspectStage3Up = TRUE;		pDY08->oInspectStage3Down = FALSE; }
	if (nIndex == 1) { pDY08->oInspectStage3Up = FALSE;		pDY08->oInspectStage3Down = TRUE; }
	if (nIndex == 2) { pDY08->oInspectStage3Deg0 = TRUE;	pDY08->oInspectStage3Deg90 = FALSE; }
	if (nIndex == 3) { pDY08->oInspectStage3Deg0 = FALSE;	pDY08->oInspectStage3Deg90 = TRUE; }
					
	g_objAJinAXL.Write_Output(8);

	m_strLog.Format("[Manual Inspection] Inspection 3 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
	Set_VisionUpDown(3, nIndex);
}
void CManualInspDlg::OnBtnInsp4IOClick(UINT nID)
{
	if (!g_objCommon.Check_MainDoor()) return;
	int nIndex = nID - IDC_BTN_INSP4_IO_0;

	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
	DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();

	if (nIndex == 0 || nIndex == 1 || nIndex == 4 || nIndex == 5) {
		if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 1)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 2)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)  && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 4)) {
			AfxMessageBox(_T("Stage 동작은 정위치에서만(Aling,Top1,TOP2,Buffer,Unload) 작업 가능합니다....."));
			return;
		}
	}
	if (nIndex == 0 || nIndex == 1) { //Up/Down
		if (pDX08->iInspectStage4Yin) {
			if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
				AfxMessageBox(_T("Stage Up/Down은 Align/Unload 또는 Stage_Out 위치에서만 가능합니다....."));
				return;
			}
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
				if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0)) {
					AfxMessageBox(_T("Stage간 Interlock으로 작업을 진행할수 었습니다..."));
					return;
				}
			}
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
				if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)) {
					AfxMessageBox(_T("Stage간 Interlock으로 작업을 진행할수 었습니다..."));
					return;
				}
			}
		} else {
			if (nIndex == 0) {
				AfxMessageBox(_T("Stage In상태에서만 작업가능합니다....."));
				return;
			}
		}
	}
	if (nIndex == 4 || nIndex == 5) { //YIn/Out
		if (pDX08->iInspectStage4Up) {
			AfxMessageBox(_T("Stage Down시에만 In-Out 작업 가능합니다....."));
			return;
		}
	}
	if (nIndex == 4) { //YIn
		if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0) && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
			AfxMessageBox(_T("Stage Align, Unload 위치에서 In 작업 가능합니다....."));
			return;
		}
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0)) {
				AfxMessageBox(_T("Align위치에 Stage가 있어 In 작업을 할수없습니다...."));
				return;
			}
		}
		if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
			if (g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3) || g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)) {
				AfxMessageBox(_T("Align위치에 Stage가 있어 In 작업을 할수없습니다...."));
				return;
			}
		}
	}

	if (nIndex == 0) { pDY08->oInspectStage4Up = TRUE;		pDY08->oInspectStage4Down = FALSE; }
	if (nIndex == 1) { pDY08->oInspectStage4Up = FALSE;		pDY08->oInspectStage4Down = TRUE; }
	if (nIndex == 2) { pDY08->oInspectStage4Deg0 = TRUE;	pDY08->oInspectStage4Deg90 = FALSE; }
	if (nIndex == 3) { pDY08->oInspectStage4Deg0 = FALSE;	pDY08->oInspectStage4Deg90 = TRUE; }
	if (nIndex == 4) { pDY08->oInspectStage4Yin = TRUE;		pDY08->oInspectStage4YOut = FALSE; }
	if (nIndex == 5) { pDY08->oInspectStage4Yin = FALSE;	pDY08->oInspectStage4YOut = TRUE; }
					
	g_objAJinAXL.Write_Output(8);

	m_strLog.Format("[Manual Inspection] Inspection 4 IO (%d) Click", nIndex);
	g_objLogFile.Save_HandlerLog(m_strLog);
	Set_VisionUpDown(4, nIndex);
}

///////////////////////////////////////////////////////////////////////////////

BOOL CManualInspDlg::Check_VisionStage(int nStageNo, int nToPos)
{
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
	DY_DATA_07 *pDY07 = g_objAJinAXL.Get_pDY07();

	if (nStageNo == 1 && pDX07->iInspectStage1Up || nStageNo == 2 && pDX07->iInspectStage2Up ||
		nStageNo == 3 && pDX08->iInspectStage3Up || nStageNo == 4 && pDX08->iInspectStage4Up ) {
		if (g_objCommon.Get_LoadPickerUp()==FALSE) {
			AfxMessageBox(_T("Load Picker 1,2 All Up상태에서 작업 가능합니다....."));
			return FALSE;
		}
		if (g_objCommon.Get_UnloadPickerUp(1)==FALSE || g_objCommon.Get_UnloadPickerUp(2)==FALSE) {
			AfxMessageBox(_T("Unload Picker 1,2 All Up상태에서 작업 가능합니다....."));
			return FALSE;
		}
		if (pDX03->iAlignMasterIn || !pDX03->iAlignMasterOut || pDX03->iAlignSlave1In || !pDX03->iAlignSlave1Out || pDX03->iAlignSlave2In || !pDX03->iAlignSlave2Out) {
			AfxMessageBox(_T("Align Out 상태에서 작업 가능합니다....."));
			return FALSE;
		}
	}
	if (nStageNo == 1 && pDX07->iInspectStage1Down && pDX07->iInspectStage1YOut) return TRUE;
	if (nStageNo == 4 && pDX08->iInspectStage4Down && pDX08->iInspectStage4YOut) return TRUE;
	if (nStageNo == 2 || nStageNo == 3) {
		if ((pDX07->iInspectStage2Up   && pDX08->iInspectStage3Down) ||
			(pDX07->iInspectStage2Down && pDX08->iInspectStage3Up)) {
			if (pDX07->iInspectStage1YOut && pDX08->iInspectStage4YOut) return TRUE;
		} else {
			AfxMessageBox(_T("Stage 2,3은 Up-Down 상태에서 작업 가능합니다....."));
			return FALSE;
		}
	}

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	double dC1Pos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X1);
	double dC2Pos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X2);
	double dC3Pos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X3);
	double dC4Pos = g_objAJinAXL.Get_Position(AX_INSPECT_STAGE_X4);
	double dCxPos;
	if (nStageNo == 1) dCxPos = dC1Pos;
	if (nStageNo == 2) dCxPos = dC2Pos;
	if (nStageNo == 3) dCxPos = dC3Pos;
	if (nStageNo == 4) dCxPos = dC4Pos;

	if (nToPos == 0) {	//Align
		if (nStageNo == 1 && pDX07->iInspectStage1Up || nStageNo == 2 && pDX07->iInspectStage2Up ||
			nStageNo == 3 && pDX08->iInspectStage3Up || nStageNo == 4 && pDX08->iInspectStage4Up ) {
			if (nStageNo != 1 && pDX07->iInspectStage1Up && dC1Pos < dCxPos) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 2 && pDX07->iInspectStage2Up && dC2Pos < dCxPos) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 3 && pDX08->iInspectStage3Up && dC3Pos < dCxPos) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 4 && pDX08->iInspectStage4Up && dC4Pos < dCxPos) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		} else {
			if (nStageNo != 1 && pDX07->iInspectStage1Down && dC1Pos < dCxPos) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 2 && pDX07->iInspectStage2Down && dC2Pos < dCxPos) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 3 && pDX08->iInspectStage3Down && dC3Pos < dCxPos) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 4 && pDX08->iInspectStage4Down && dC4Pos < dCxPos) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		}
	}
	if (nToPos == 1) {	//Top 1
		if (nStageNo == 1 && pDX07->iInspectStage1Up || nStageNo == 2 && pDX07->iInspectStage2Up ||
			nStageNo == 3 && pDX08->iInspectStage3Up || nStageNo == 4 && pDX08->iInspectStage4Up ) {
			if (nStageNo != 1 && pDX07->iInspectStage1Up && dC1Pos < dCxPos && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0)) {
				AfxMessageBox(_T("Stage 1 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 2 && pDX07->iInspectStage2Up && dC2Pos < dCxPos && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0)) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 3 && pDX08->iInspectStage3Up && dC3Pos < dCxPos && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0)) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 4 && pDX08->iInspectStage4Up && dC4Pos < dCxPos && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		} else {
			if (nStageNo != 1 && pDX07->iInspectStage1Down && dC1Pos < dCxPos && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0)) {
				AfxMessageBox(_T("Stage 1 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 2 && pDX07->iInspectStage2Down && dC2Pos < dCxPos && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0)) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 3 && pDX08->iInspectStage3Down && dC3Pos < dCxPos && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0)) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 4 && pDX08->iInspectStage4Down && dC4Pos < dCxPos && !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0)) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		}
	}
	if (nToPos == 2) {	//Top 2
		if (nStageNo == 1 && pDX07->iInspectStage1Up || nStageNo == 2 && pDX07->iInspectStage2Up ||
			nStageNo == 3 && pDX08->iInspectStage3Up || nStageNo == 4 && pDX08->iInspectStage4Up ) {
			if ((nStageNo != 1 && pDX07->iInspectStage1Up && dC1Pos < dCxPos && dC1Pos > pMoveData->dVisionStageX1[1]+1.0) ||
				(nStageNo != 1 && pDX07->iInspectStage1Up && dC1Pos > dCxPos && dC1Pos < pMoveData->dVisionStageX1[4]-1.0) ) {
				AfxMessageBox(_T("Stage 1 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 2 && pDX07->iInspectStage2Up && dC2Pos < dCxPos && dC2Pos > pMoveData->dVisionStageX2[1]+1.0) ||
				(nStageNo != 2 && pDX07->iInspectStage2Up && dC2Pos > dCxPos && dC2Pos < pMoveData->dVisionStageX2[4]-1.0) ) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 3 && pDX08->iInspectStage3Up && dC3Pos < dCxPos && dC3Pos > pMoveData->dVisionStageX3[1]+1.0) ||
				(nStageNo != 3 && pDX08->iInspectStage3Up && dC3Pos > dCxPos && dC3Pos < pMoveData->dVisionStageX3[4]-1.0) ) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 4 && pDX08->iInspectStage4Up && dC4Pos < dCxPos && dC4Pos > pMoveData->dVisionStageX4[1]+1.0) ||
				(nStageNo != 4 && pDX08->iInspectStage4Up && dC4Pos > dCxPos && dC4Pos < pMoveData->dVisionStageX4[4]-1.0) ) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		} else {
			if ((nStageNo != 1 && pDX07->iInspectStage1Down && dC1Pos < dCxPos && dC1Pos > pMoveData->dVisionStageX1[1]+1.0) ||
				(nStageNo != 1 && pDX07->iInspectStage1Down && dC1Pos > dCxPos && dC1Pos < pMoveData->dVisionStageX1[4]-1.0) ) {
				AfxMessageBox(_T("Stage 1 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 2 && pDX07->iInspectStage2Down && dC2Pos < dCxPos && dC2Pos > pMoveData->dVisionStageX2[1]+1.0) ||
				(nStageNo != 2 && pDX07->iInspectStage2Down && dC2Pos > dCxPos && dC2Pos < pMoveData->dVisionStageX2[4]-1.0) ) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 3 && pDX08->iInspectStage3Down && dC3Pos < dCxPos && dC3Pos > pMoveData->dVisionStageX3[1]+1.0) ||
				(nStageNo != 3 && pDX08->iInspectStage3Down && dC3Pos > dCxPos && dC3Pos < pMoveData->dVisionStageX3[4]-1.0) ) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 4 && pDX08->iInspectStage4Down && dC4Pos < dCxPos && dC4Pos > pMoveData->dVisionStageX4[1]+1.0) ||
				(nStageNo != 4 && pDX08->iInspectStage4Down && dC4Pos > dCxPos && dC4Pos < pMoveData->dVisionStageX4[4]-1.0) ) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		}
	}
	if (nToPos == 3) {	//Unload
		if (nStageNo == 1 && pDX07->iInspectStage1Up || nStageNo == 2 && pDX07->iInspectStage2Up ||
			nStageNo == 3 && pDX08->iInspectStage3Up || nStageNo == 4 && pDX08->iInspectStage4Up ) {
			if (nStageNo != 1 && pDX07->iInspectStage1Up && dC1Pos > dCxPos) {
				AfxMessageBox(_T("Stage 1 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 2 && pDX07->iInspectStage2Up && dC2Pos > dCxPos) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 3 && pDX08->iInspectStage3Up && dC3Pos > dCxPos) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 4 && pDX08->iInspectStage4Up && dC4Pos > dCxPos) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		} else {
			if (nStageNo != 1 && pDX07->iInspectStage1Down && dC1Pos > dCxPos) {
				AfxMessageBox(_T("Stage 1 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 2 && pDX07->iInspectStage2Down && dC2Pos > dCxPos) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 3 && pDX08->iInspectStage3Down && dC3Pos > dCxPos) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if (nStageNo != 4 && pDX08->iInspectStage4Down && dC4Pos > dCxPos) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		}
	}
	if (nToPos == 4) {	//Buffer
		if (nStageNo == 1 && pDX07->iInspectStage1Up || nStageNo == 2 && pDX07->iInspectStage2Up ||
			nStageNo == 3 && pDX08->iInspectStage3Up || nStageNo == 4 && pDX08->iInspectStage4Up ) {
			if ((nStageNo != 1 && pDX07->iInspectStage1Up && dC1Pos < dCxPos && dC1Pos > pMoveData->dVisionStageX1[2]+1.0) ||
				(nStageNo != 1 && pDX07->iInspectStage1Up && dC1Pos > dCxPos && dC1Pos < pMoveData->dVisionStageX1[3]-1.0) ) {
				AfxMessageBox(_T("Stage 1 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 2 && pDX07->iInspectStage2Up && dC2Pos < dCxPos && dC2Pos > pMoveData->dVisionStageX2[2]+1.0) ||
				(nStageNo != 2 && pDX07->iInspectStage2Up && dC2Pos > dCxPos && dC2Pos < pMoveData->dVisionStageX2[3]-1.0) ) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 3 && pDX08->iInspectStage3Up && dC3Pos < dCxPos && dC3Pos > pMoveData->dVisionStageX3[2]+1.0) ||
				(nStageNo != 3 && pDX08->iInspectStage3Up && dC3Pos > dCxPos && dC3Pos < pMoveData->dVisionStageX3[3]-1.0) ) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 4 && pDX08->iInspectStage4Up && dC4Pos < dCxPos && dC4Pos > pMoveData->dVisionStageX4[2]+1.0) ||
				(nStageNo != 4 && pDX08->iInspectStage4Up && dC4Pos > dCxPos && dC4Pos < pMoveData->dVisionStageX4[3]-1.0) ) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		} else {
			if ((nStageNo != 1 && pDX07->iInspectStage1Down && dC1Pos < dCxPos && dC1Pos > pMoveData->dVisionStageX1[2]+1.0) ||
				(nStageNo != 1 && pDX07->iInspectStage1Down && dC1Pos > dCxPos && dC1Pos < pMoveData->dVisionStageX1[3]-1.0) ) {
				AfxMessageBox(_T("Stage 1 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 2 && pDX07->iInspectStage2Down && dC2Pos < dCxPos && dC2Pos > pMoveData->dVisionStageX2[2]+1.0) ||
				(nStageNo != 2 && pDX07->iInspectStage2Down && dC2Pos > dCxPos && dC2Pos < pMoveData->dVisionStageX2[3]-1.0) ) {
				AfxMessageBox(_T("Stage 2 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 3 && pDX08->iInspectStage3Down && dC3Pos < dCxPos && dC3Pos > pMoveData->dVisionStageX3[2]+1.0) ||
				(nStageNo != 3 && pDX08->iInspectStage3Down && dC3Pos > dCxPos && dC3Pos < pMoveData->dVisionStageX3[3]-1.0) ) {
				AfxMessageBox(_T("Stage 3 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
			if ((nStageNo != 4 && pDX08->iInspectStage4Down && dC4Pos < dCxPos && dC4Pos > pMoveData->dVisionStageX4[2]+1.0) ||
				(nStageNo != 4 && pDX08->iInspectStage4Down && dC4Pos > dCxPos && dC4Pos < pMoveData->dVisionStageX4[3]-1.0) ) {
				AfxMessageBox(_T("Stage 4 간섭으로 이동이 불가합니다.."));
				return FALSE;
			}
		}
	}
	if (nToPos == 5 || nToPos == 6) {	//Pitch 이동
		if (nStageNo == 1 && pDX07->iInspectStage1Down || nStageNo == 2 && pDX07->iInspectStage2Down ||
			nStageNo == 3 && pDX08->iInspectStage3Down || nStageNo == 4 && pDX08->iInspectStage4Down) {
			AfxMessageBox(_T("Stage Up 상태에서 간격이동이 가능합니다....."));
			return FALSE;
		}
		if ((nStageNo == 1 && nToPos == 5 && dC1Pos < pMoveData->dVisionStageX1[1] + 1.0 ) ||
			(nStageNo == 2 && nToPos == 5 && dC2Pos < pMoveData->dVisionStageX2[1] + 1.0 ) ||
			(nStageNo == 3 && nToPos == 5 && dC3Pos < pMoveData->dVisionStageX3[1] + 1.0 ) ||
			(nStageNo == 4 && nToPos == 5 && dC4Pos < pMoveData->dVisionStageX4[1] + 1.0 ) ) {
			AfxMessageBox(_T("Top1 위치에서는 간격좌로는 할 수 없습니다...."));
			return FALSE;
		}
		if ((nStageNo == 1 && (dC1Pos < pMoveData->dVisionStageX1[1] - 1.0 || dC1Pos > pMoveData->dVisionStageX1[4] - 1.0)) ||
			(nStageNo == 2 && (dC2Pos < pMoveData->dVisionStageX2[1] - 1.0 || dC2Pos > pMoveData->dVisionStageX2[4] - 1.0)) ||
			(nStageNo == 3 && (dC3Pos < pMoveData->dVisionStageX3[1] - 1.0 || dC3Pos > pMoveData->dVisionStageX3[4] - 1.0)) ||
			(nStageNo == 4 && (dC4Pos < pMoveData->dVisionStageX4[1] - 1.0 || dC4Pos > pMoveData->dVisionStageX4[4] - 1.0)) ) {
			AfxMessageBox(_T("Top1, Top2위치에서만 간격이동이 가능합니다....."));
			return FALSE;
		}

		if (nStageNo != 1 && pDX07->iInspectStage1Up) {
			if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 0) || !g_objCommon.Check_Position(AX_INSPECT_STAGE_X1, 3)) {
				AfxMessageBox(_T("Stage 1의 위치가 Aling 또는 Unload인 경우만 간격이동이 가능합니다....."));
				return FALSE;
			}
		}
		if (nStageNo != 2 && pDX07->iInspectStage2Up) {
			if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 0) || !g_objCommon.Check_Position(AX_INSPECT_STAGE_X2, 3)) {
				AfxMessageBox(_T("Stage 2의 위치가 Aling 또는 Unload인 경우만 간격이동이 가능합니다....."));
				return FALSE;
			}
		}
		if (nStageNo != 3 && pDX08->iInspectStage3Up) {
			if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 0) || !g_objCommon.Check_Position(AX_INSPECT_STAGE_X3, 3)) {
				AfxMessageBox(_T("Stage 3의 위치가 Aling 또는 Unload인 경우만 간격이동이 가능합니다....."));
				return FALSE;
			}
		}
		if (nStageNo != 4 && pDX08->iInspectStage4Up) {
			if (!g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 0) || !g_objCommon.Check_Position(AX_INSPECT_STAGE_X4, 3)) {
				AfxMessageBox(_T("Stage 4의 위치가 Aling 또는 Unload인 경우만 간격이동이 가능합니다....."));
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CManualInspDlg::Set_VisionPostion(int nStageNo, int nToPos)
{
	//nStageNo(1~4), nToPos(0~4)
	if (nToPos > 4) return;

	for(int i=0; i<2; i++) {
		for(int j=0; j<5; j++) {
			if (gData.nVisionPos[i][j] == nStageNo) {
				gData.nVisionPos[i][j] = 0;
				gData.nVisionPos[i][nToPos] = nStageNo;
				return;
			}
		}
	}
}

void CManualInspDlg::Set_VisionUpDown(int nStageNo, int nUpDown)
{
	//nStageNo(1~4), nUpDown(0~1)
	if (nUpDown > 1) return;
	int nToPos = 0;
	if (nUpDown == 0) nToPos = 1;
	if (nUpDown == 1) nToPos = 0;

	for(int i=0; i<2; i++) {
		for(int j=0; j<5; j++) {
			if (gData.nVisionPos[i][j] == nStageNo) {
				gData.nVisionPos[i][j] = 0;
				gData.nVisionPos[nToPos][j] = nStageNo;
				return;
			}
		}
	}
}