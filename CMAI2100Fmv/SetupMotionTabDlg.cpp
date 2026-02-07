// SetupMotionTabDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupMotionTabDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "AJinAXL.h"
#include "Common.h"

#include "SetupDlg.h"

// CSetupMotionTabDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMotionTabDlg, CDialogEx)

CSetupMotionTabDlg::CSetupMotionTabDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMotionTabDlg::IDD, pParent)
{
}

CSetupMotionTabDlg::~CSetupMotionTabDlg()
{
}

void CSetupMotionTabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 10; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 62; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_AXIS_NAME_0 + i, m_stcAxisName[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_AXIS_POS_0 + i, m_stcAxisPos[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_AXIS_VEL_0 + i, m_stcAxisVel[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_AXIS_SON_0 + i, m_ledAxisSOn[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_AXIS_ORG_0 + i, m_ledAxisOrg[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_AXIS_ELP_0 + i, m_ledAxisElp[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_AXIS_ELN_0 + i, m_ledAxisEln[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_AXIS_ALM_0 + i, m_ledAxisAlm[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_AXIS_INP_0 + i, m_ledAxisInP[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_AXIS_RUN_0 + i, m_ledAxisRun[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LED_AXIS_HOM_0 + i, m_ledAxisHom[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_CHK_S_ON_0 + i, m_chkSOn[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_RESET_0 + i, m_btnReset[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_HOME_0 + i, m_btnHome[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_STOP_0 + i, m_btnStop[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_JOG_P_0 + i, m_btnJogP[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_JOG_N_0 + i, m_btnJogN[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_ABS_DIST_0 + i, m_stcAbsDist[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_ABS_MOVE_0 + i, m_btnAbsMove[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_REL_DIST_0 + i, m_stcRelDist[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_REL_MOVE_P_0 + i, m_btnRelMoveP[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_BTN_REL_MOVE_N_0 + i, m_btnRelMoveN[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_SPEED_M_0 + i, m_stcSpeedM[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_SPEED_J_0 + i, m_stcSpeedJ[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_STC_ACCEL_0 + i, m_stcAccel[i]);
}

BEGIN_MESSAGE_MAP(CSetupMotionTabDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHK_S_ON_0, IDC_CHK_S_ON_7, OnChkSOnClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_RESET_0, IDC_BTN_RESET_7, OnBtnResetClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_HOME_0, IDC_BTN_HOME_7, OnBtnHomeClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_STOP_0, IDC_BTN_STOP_7, OnBtnStopClick)
	ON_MESSAGE(UM_CS_LBUTTON_DOWN, OnCsLButtonDown)
	ON_MESSAGE(UM_CS_LBUTTON_UP, OnCsLButtonUp)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ABS_DIST_0, IDC_STC_ABS_DIST_7, OnStcAbsDistClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_ABS_MOVE_0, IDC_BTN_ABS_MOVE_7, OnBtnAbsMoveClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_REL_DIST_0, IDC_STC_REL_DIST_7, OnStcRelDistClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REL_MOVE_P_0, IDC_BTN_REL_MOVE_P_7, OnBtnRelMovePClick)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_REL_MOVE_N_0, IDC_BTN_REL_MOVE_N_7, OnBtnRelMoveNClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SPEED_M_0, IDC_STC_SPEED_M_7, OnStcSpeedMClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SPEED_J_0, IDC_STC_SPEED_J_7, OnStcSpeedJClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_ACCEL_0, IDC_STC_ACCEL_7, OnStcAccelClick)
END_MESSAGE_MAP()

// CSetupMotionTabDlg 메시지 처리기입니다.

BOOL CSetupMotionTabDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	m_nMotionTab = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMotionTabDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMotionTabDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

#ifdef NEW_FINAL
	int nMaxAxis = (m_nMotionTab == 5 ? 3 : 8);
#else
	int nMaxAxis = (m_nMotionTab == 5 ? 5 : 8);
#endif
	BOOL bVisible = (nMaxAxis < 4 ? FALSE : TRUE);

	m_Group[1].ShowWindow(bVisible);
	for (int i = 0; i < 11; i++) m_Label[i + 11].ShowWindow(bVisible);

	for (int i = 0; i < 8; i++) {
		bVisible = (i < nMaxAxis ? TRUE : FALSE);

		m_stcAxisName[i].ShowWindow(bVisible);
		m_stcAxisPos[i].ShowWindow(bVisible);
		m_stcAxisVel[i].ShowWindow(bVisible);
		m_ledAxisSOn[i].ShowWindow(bVisible);
		m_ledAxisOrg[i].ShowWindow(bVisible);
		m_ledAxisElp[i].ShowWindow(bVisible);
		m_ledAxisEln[i].ShowWindow(bVisible);
		m_ledAxisAlm[i].ShowWindow(bVisible);
		m_ledAxisInP[i].ShowWindow(bVisible);
		m_ledAxisRun[i].ShowWindow(bVisible);
		m_ledAxisHom[i].ShowWindow(bVisible);

		m_Group[i + 2].ShowWindow(bVisible);
		for (int j = 0; j < 5; j++) m_Label[i * 5 + j + 22].ShowWindow(bVisible);

		m_chkSOn[i].ShowWindow(bVisible);
		m_btnReset[i].ShowWindow(bVisible);
		m_btnHome[i].ShowWindow(bVisible);
		m_btnStop[i].ShowWindow(bVisible);
		m_btnJogP[i].ShowWindow(bVisible);
		m_btnJogN[i].ShowWindow(bVisible);
		m_stcAbsDist[i].ShowWindow(bVisible);
		m_btnAbsMove[i].ShowWindow(bVisible);
		m_stcRelDist[i].ShowWindow(bVisible);
		m_btnRelMoveP[i].ShowWindow(bVisible);
		m_btnRelMoveN[i].ShowWindow(bVisible);
		m_stcSpeedM[i].ShowWindow(bVisible);
		m_stcSpeedJ[i].ShowWindow(bVisible);
		m_stcAccel[i].ShowWindow(bVisible);

		if (!bVisible) continue;

		CString strName, strText;

		strName = g_objAJinAXL.Get_AxisName(m_nMotionTab * 8 + i);
		m_stcAxisName[i].SetWindowText(" " + strName);
		m_Group[i + 2].SetWindowText(strName);

		g_objAJinAXL.Is_ServoAxis(m_nMotionTab * 8 + i) ? m_ledAxisAlm[i].ShowWindow(SW_SHOW) : m_ledAxisAlm[i].ShowWindow(SW_HIDE);
		g_objAJinAXL.Is_ServoAxis(m_nMotionTab * 8 + i) ? m_ledAxisInP[i].ShowWindow(SW_SHOW) : m_ledAxisInP[i].ShowWindow(SW_HIDE);
		g_objAJinAXL.Use_OrgAxis(m_nMotionTab * 8 + i) ? m_ledAxisOrg[i].ShowWindow(SW_SHOW) : m_ledAxisOrg[i].ShowWindow(SW_HIDE);
		g_objAJinAXL.Use_ElpAxis(m_nMotionTab * 8 + i) ? m_ledAxisElp[i].ShowWindow(SW_SHOW) : m_ledAxisElp[i].ShowWindow(SW_HIDE);
		g_objAJinAXL.Use_ElnAxis(m_nMotionTab * 8 + i) ? m_ledAxisEln[i].ShowWindow(SW_SHOW) : m_ledAxisEln[i].ShowWindow(SW_HIDE);
		g_objAJinAXL.Is_ServoAxis(m_nMotionTab * 8 + i) ? m_btnReset[i].ShowWindow(SW_SHOW) : m_btnReset[i].ShowWindow(SW_HIDE);
		g_objAJinAXL.Get_ServoOn(m_nMotionTab * 8 + i) ? m_chkSOn[i].SetCheck(TRUE) : m_chkSOn[i].SetCheck(FALSE);

		m_stcAbsDist[i].SetWindowText("0.000");
		m_stcRelDist[i].SetWindowText("0.000");

		AXIS_PARAM *pParam = g_objAJinAXL.Get_pParam(m_nMotionTab * 8 + i);
		strText.Format("%0.1lf", pParam->dSpeedM);
		m_stcSpeedM[i].SetWindowText(strText);

		strText.Format("%0.1lf", pParam->dSpeedJ);
		m_stcSpeedJ[i].SetWindowText(strText);			

		strText.Format("%0.1lf", pParam->dAccel);
		m_stcAccel[i].SetWindowText(strText);

		if (g_dlgSetup.Get_LoginUser() == 2) {	// SI User
			m_btnHome[i].EnableWindow(TRUE);	// 작업자 접근권한 변경
			m_stcAbsDist[i].EnableWindow(TRUE);
			m_btnAbsMove[i].EnableWindow(TRUE);
			m_btnJogP[i].EnableWindow(TRUE);
			m_btnJogN[i].EnableWindow(TRUE);
		} else {
			m_btnHome[i].EnableWindow(FALSE);	// 작업자 접근권한 변경
			m_stcAbsDist[i].EnableWindow(FALSE);
			m_btnAbsMove[i].EnableWindow(FALSE);
			m_btnJogP[i].EnableWindow(FALSE);
			m_btnJogN[i].EnableWindow(FALSE);
		}
	}

	m_strLog.Format("[Setup Motion] Show Window - Tab (%d)", m_nMotionTab);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnChkSOnClick(UINT nID)
{
	int ID = nID - IDC_CHK_S_ON_0;
	if (m_chkSOn[ID].GetCheck()) g_objAJinAXL.Set_ServoOn(m_nMotionTab * 8 + ID);
	else g_objAJinAXL.Set_ServoOff(m_nMotionTab * 8 + ID);

	m_strLog.Format("[Setup Motion] OnChkSOnClick - Tab(%d) Data(%d)", m_nMotionTab, ID);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnBtnResetClick(UINT nID)
{
	int ID = nID - IDC_BTN_RESET_0;
	g_objAJinAXL.Stop_Motion(m_nMotionTab * 8 + ID);
	g_objAJinAXL.Alarm_Reset(m_nMotionTab * 8 + ID);

	m_strLog.Format("[Setup Motion] OnBtnResetClick - Tab(%d) Data(%d)", m_nMotionTab, ID);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnBtnHomeClick(UINT nID)
{
	int ID = nID - IDC_BTN_HOME_0;
	int nAxis = m_nMotionTab * 8 + ID;

	if(PositionCheck(nAxis)==FALSE) return;

	g_objAJinAXL.Home_Search(nAxis);

	m_strLog.Format("[Setup Motion] OnBtnHomeClick - Tab(%d) Data(%d-%d)", m_nMotionTab, ID, nAxis);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnBtnStopClick(UINT nID)
{
	int ID = nID - IDC_BTN_STOP_0;
	g_objAJinAXL.Stop_Motion(m_nMotionTab * 8 + ID);

	m_strLog.Format("[Setup Motion] OnBtnStopClick - Tab(%d) Data(%d)", m_nMotionTab, ID);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

LRESULT CSetupMotionTabDlg::OnCsLButtonDown(WPARAM wParam, LPARAM lParam)
{
	UINT nID = (int)wParam;
	if (nID >= IDC_BTN_JOG_P_0 && nID <= IDC_BTN_JOG_P_7) {			// Jog +
		int ID = nID - IDC_BTN_JOG_P_0;
		g_objAJinAXL.Jog_Positive(m_nMotionTab * 8 + ID);

	} else if (nID >= IDC_BTN_JOG_N_0 && nID <= IDC_BTN_JOG_N_7) {	// Jog -
		int ID = nID - IDC_BTN_JOG_N_0;
		g_objAJinAXL.Jog_Negative(m_nMotionTab * 8 + ID);
	}
	return 0;
}

LRESULT CSetupMotionTabDlg::OnCsLButtonUp(WPARAM wParam, LPARAM lParam)
{
	UINT nID = (int)wParam;

	if (nID >= IDC_BTN_JOG_P_0 && nID <= IDC_BTN_JOG_P_7) {			// Jog +
		int ID = nID - IDC_BTN_JOG_P_0;
		g_objAJinAXL.Stop_Motion(m_nMotionTab * 8 + ID);

	} else if (nID >= IDC_BTN_JOG_N_0 && nID <= IDC_BTN_JOG_N_7) {	// Jog -
		int ID = nID - IDC_BTN_JOG_N_0;
		g_objAJinAXL.Stop_Motion(m_nMotionTab * 8 + ID);
	}
	return 0;
}

void CSetupMotionTabDlg::OnStcAbsDistClick(UINT nID)
{
	int ID = nID - IDC_STC_ABS_DIST_0;
	CString strOld, strNew;
	m_stcAbsDist[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcAbsDist[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Motion] OnStcAbsDistClick - Tab(%d) Data(%d-%s)", m_nMotionTab, ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnBtnAbsMoveClick(UINT nID)
{
	int ID = nID - IDC_BTN_ABS_MOVE_0;

	CString strText;
	m_stcAbsDist[ID].GetWindowText(strText);
	double dDist = atof(strText);

	g_objAJinAXL.Move_Absolute(m_nMotionTab * 8 + ID, dDist);

	m_strLog.Format("[Setup Motion] OnBtnAbsMoveClick - Tab(%d) Data(%d-%0.3lf)", m_nMotionTab, ID, dDist);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnStcRelDistClick(UINT nID)
{
	int ID = nID - IDC_STC_REL_DIST_0;

	CString strOld, strNew;
	m_stcRelDist[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	if (g_dlgSetup.Get_LoginUser() != 2) {
		double dNew = atof(strNew);
		if (dNew > 5.0) strNew = strOld;
	}
	m_stcRelDist[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Motion] OnStcRelDistClick - Tab(%d) Data(%d-%s)", m_nMotionTab, ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnBtnRelMovePClick(UINT nID)
{
	int ID = nID - IDC_BTN_REL_MOVE_P_0;

	CString strText;
	m_stcRelDist[ID].GetWindowText(strText);
	double dDist = atof(strText);

	g_objAJinAXL.Move_Relative(m_nMotionTab * 8 + ID, dDist);

	m_strLog.Format("[Setup Motion] OnBtnRelMovePClick - Tab(%d) Data(%d-%0.3lf)", m_nMotionTab, ID, dDist);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnBtnRelMoveNClick(UINT nID)
{
	int ID = nID - IDC_BTN_REL_MOVE_N_0;

	CString strText;
	m_stcRelDist[ID].GetWindowText(strText);
	double dDist = atof(strText) * -1.0;

	g_objAJinAXL.Move_Relative(m_nMotionTab * 8 + ID, dDist);

	m_strLog.Format("[Setup Motion] OnBtnRelMoveNClick - Tab(%d) Data(%d-%0.3lf)", m_nMotionTab, ID, dDist);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnStcSpeedMClick(UINT nID)
{
	int ID = nID - IDC_STC_SPEED_M_0;

	CString strOld, strNew;
	m_stcSpeedM[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcSpeedM[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Motion] OnStcSpeedMClick - Tab(%d) Data(%d-%s)", m_nMotionTab, ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnStcSpeedJClick(UINT nID)
{
	int ID = nID - IDC_STC_SPEED_J_0;

	CString strOld, strNew;
	m_stcSpeedJ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcSpeedJ[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Motion] OnStcSpeedJClick - Tab(%d) Data(%d-%s)", m_nMotionTab, ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMotionTabDlg::OnStcAccelClick(UINT nID)
{
	int ID = nID - IDC_STC_ACCEL_0;

	CString strOld, strNew;
	m_stcAccel[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcAccel[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Motion] OnStcAccelClick - Tab(%d) Data(%d-%s)", m_nMotionTab, ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMotionTabDlg::Initial_Controls() 
{
	for (int i = 0; i < 10; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 0; i < 62; i++) m_Label[i].Init_Ctrl("바탕", 10, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 8; i++) m_stcAxisName[i].Init_Ctrl("바탕", 10, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));
	for (int i = 0; i < 8; i++) m_stcAxisPos[i].Init_Ctrl("바탕", 11, TRUE, RGB(0xFF, 0x00, 0x00), RGB(0xE0, 0xE0, 0xE0));
	for (int i = 0; i < 8; i++) m_stcAxisVel[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xE0, 0xE0, 0xE0));

	for (int i = 0; i < 8; i++) m_ledAxisSOn[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 8; i++) m_ledAxisOrg[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 8; i++) m_ledAxisElp[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 8; i++) m_ledAxisEln[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 8; i++) m_ledAxisAlm[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 8; i++) m_ledAxisInP[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 8; i++) m_ledAxisRun[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 8; i++) m_ledAxisHom[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));

	for (int i = 0; i < 8; i++) m_chkSOn[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x63, 0x47), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnReset[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x80, 0x00), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnHome[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x22, 0x8B, 0x22), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnStop[i].Init_Ctrl("바탕", 12, TRUE, RGB(0xFF, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnJogP[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x80, 0x00, 0x80), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnJogN[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x80, 0x00, 0x80), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_stcAbsDist[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xFF, 0xC0));
	for (int i = 0; i < 8; i++) m_btnAbsMove[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_stcRelDist[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x80, 0xFF, 0xC0));
	for (int i = 0; i < 8; i++) m_btnRelMoveP[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);
	for (int i = 0; i < 8; i++) m_btnRelMoveN[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, 0, 0);

	for (int i = 0; i < 8; i++) m_stcSpeedM[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 8; i++) m_stcSpeedJ[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 8; i++) m_stcAccel[i].Init_Ctrl("바탕", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xFF, 0xF0));
}

void CSetupMotionTabDlg::Display_Status()
{
#ifdef NEW_FINAL
	int nMaxAxis = (m_nMotionTab == 5 ? 3 : 8);
#else
	int nMaxAxis = (m_nMotionTab == 5 ? 5 : 8);
#endif

	CString strPos, strVel;

	for (int i = 0; i < nMaxAxis; i++) {
		AXIS_STATUS *pStatus = g_objAJinAXL.Get_pStatus(m_nMotionTab * 8 + i);

		strPos.Format("%0.3lf", pStatus->dPos);
		m_stcAxisPos[i].SetWindowText(strPos);

		strVel.Format("%0.3lf", pStatus->dVel);
		m_stcAxisVel[i].SetWindowText(strVel);

		pStatus->bSOn ? m_ledAxisSOn[i].On() : m_ledAxisSOn[i].Off();
		pStatus->bOrg ? m_ledAxisOrg[i].On() : m_ledAxisOrg[i].Off();
		pStatus->bELP ? m_ledAxisElp[i].On() : m_ledAxisElp[i].Off();
		pStatus->bELN ? m_ledAxisEln[i].On() : m_ledAxisEln[i].Off();
		pStatus->bALM ? m_ledAxisAlm[i].On() : m_ledAxisAlm[i].Off();
		pStatus->bInP ? m_ledAxisInP[i].On() : m_ledAxisInP[i].Off();
		pStatus->bRun ? m_ledAxisRun[i].On() : m_ledAxisRun[i].Off();
		pStatus->bHom ? m_ledAxisHom[i].On() : m_ledAxisHom[i].Off();
	}
}

void CSetupMotionTabDlg::Save_MotionData(int nTab) 
{
#ifdef NEW_FINAL
	int nEnd = (nTab == 5 ? 3 : 8);
#else
	int nEnd = (nTab == 5 ? 5 : 8);
#endif

	CString strValue;
	double dSpeedM, dSpeedJ, dAccel;
	for (int i = 0; i < nEnd; i++) {
		m_stcSpeedM[i].GetWindowText(strValue);	dSpeedM = atof(strValue);
		m_stcSpeedJ[i].GetWindowText(strValue);	dSpeedJ = atof(strValue);
		m_stcAccel[i].GetWindowText(strValue);	dAccel = atof(strValue);
		g_objAJinAXL.Save_MotionParam(m_nMotionTab * 8 + i, dSpeedM, dSpeedJ, dAccel);
	}

	m_strLog.Format("[Setup Motion] Save - Tab (%d)", m_nMotionTab);
	g_objLogFile.Save_HandlerLog(m_strLog);

	Cancel_MotionData(nTab);
}

void CSetupMotionTabDlg::Cancel_MotionData(int nTab) 
{
#ifdef NEW_FINAL
	int nEnd = (nTab == 5 ? 3 : 8);
#else
	int nEnd = (nTab == 5 ? 5 : 8);
#endif

	CString strValue;
	for (int i = 0; i < nEnd; i++) {
		g_objAJinAXL.Read_MotionParam(m_nMotionTab * 8 + i);
		AXIS_PARAM *pParam = g_objAJinAXL.Get_pParam(m_nMotionTab * 8 + i);

		strValue.Format("%0.1lf", pParam->dSpeedM);	m_stcSpeedM[i].SetWindowText(strValue);
		strValue.Format("%0.1lf", pParam->dSpeedJ);	m_stcSpeedJ[i].SetWindowText(strValue);
		strValue.Format("%0.1lf", pParam->dAccel);	m_stcAccel[i].SetWindowText(strValue);
	}
}

//순환 스테이지 홈써치할때 위치 체크
BOOL CSetupMotionTabDlg::PositionCheck(int nAxis)
{/*/
	if (nAxis==AX_INSPECTION_Y1 || nAxis==AX_INSPECTION_Y2){
		if((g_objCommon.Check_Position(AX_INSPECTION_Z1, 0) && g_objCommon.Check_Position(AX_INSPECTION_Z2, 0)) ||
			(g_objCommon.Check_Position(AX_INSPECTION_Z1, 1) && g_objCommon.Check_Position(AX_INSPECTION_Z2, 1)) ) {
				if (gData.nLanguage == 0) AfxMessageBox(_T("Inspection 1,2번 Z축이 같은 높이에서는 Y축을 이동할수 없습니다......"));
				else					  AfxMessageBox(_T("Inspection 1,2 Z-axis cannot be moved at the same height."));
				return FALSE;
		}

		if (g_objAJinAXL.Get_Position(AX_INSPECTION_Z1) < g_objAJinAXL.Get_Position(AX_INSPECTION_Z2)) {
			if( (!g_objCommon.Check_Position(AX_INSPECTION_Z1, 1) || !g_objCommon.Check_Position(AX_INSPECTION_Z2, 0)) ) {
				if (gData.nLanguage == 0) AfxMessageBox(_T("Inspection 1,2번 Z축이 Up이나 Down위치가 아니여서 Y축을 이동할수 없습니다......"));
				else					  AfxMessageBox(_T("Inspection 1,2 Z-axis are not in the Up or Down position, so the Y-axis cannot be moved."));
				return FALSE;
			}
		} else {
			if(	(!g_objCommon.Check_Position(AX_INSPECTION_Z1, 0) || !g_objCommon.Check_Position(AX_INSPECTION_Z2, 1)) ) {
				if (gData.nLanguage == 0) AfxMessageBox(_T("Inspection 1,2번 Z축이 Up이나 Down위치가 아니여서 Y축을 이동할수 없습니다......"));
				else					  AfxMessageBox(_T("Inspection 1,2 Z-axis are not in the Up or Down position, so the Y-axis cannot be moved."));
				return FALSE;
			}
		}
	}

	if (nAxis==AX_INSPECTION_Z1 || nAxis==AX_INSPECTION_Z2){
		if((g_objCommon.Check_Position(AX_INSPECTION_Y1, 0) && g_objCommon.Check_Position(AX_INSPECTION_Y2, 0)) ||
			(g_objCommon.Check_Position(AX_INSPECTION_Y1, 1) && g_objCommon.Check_Position(AX_INSPECTION_Y2, 1)) ||
			(g_objCommon.Check_Position(AX_INSPECTION_Y1, 2) && g_objCommon.Check_Position(AX_INSPECTION_Y2, 2)) ||
			(g_objCommon.Check_Position(AX_INSPECTION_Y1, 3) && g_objCommon.Check_Position(AX_INSPECTION_Y2, 3)) ) {
				if (gData.nLanguage == 0) AfxMessageBox(_T("Inspection 1,2번 Y축이 같은 위치에서는 Z축을 이동할수 없습니다......"));
				else					  AfxMessageBox(_T("You cannot move the Z axis in the same position as Inspection 1,2 Y axis."));
				return FALSE;
		}
	}

	if (nAxis==AX_TRAY_Y1 || nAxis==AX_TRAY_Y2){
		if((g_objCommon.Check_Position(AX_TRAY_Z1, 0) && g_objCommon.Check_Position(AX_TRAY_Z2, 0)) ||
			(g_objCommon.Check_Position(AX_TRAY_Z1, 1) && g_objCommon.Check_Position(AX_TRAY_Z2, 1)) ) {
				if (gData.nLanguage == 0) AfxMessageBox(_T("Tray 1,2번 Z축이 같은 높이에서는 Y축을 이동할수 없습니다......"));
				else					  AfxMessageBox(_T("Tray 1,2 Z-axis cannot be moved at the same height."));
				return FALSE;
		}
		if (g_objAJinAXL.Get_Position(AX_TRAY_Z1) < g_objAJinAXL.Get_Position(AX_TRAY_Z2)) {
			if( (!g_objCommon.Check_Position(AX_TRAY_Z1, 1) || !g_objCommon.Check_Position(AX_TRAY_Z2, 0)) ) {
				if (gData.nLanguage == 0) AfxMessageBox(_T("Tray 1,2번 Z축이 Up이나 Down위치가 아니여서 Y축을 이동할수 없습니다......"));
				else					  AfxMessageBox(_T("Tray 1,2 Z-axis are not in the Up or Down position, so the Y-axis cannot be moved."));
				return FALSE;
			}
		} else {
			if(	(!g_objCommon.Check_Position(AX_TRAY_Z1, 0) || !g_objCommon.Check_Position(AX_TRAY_Z2, 1)) ) {
				if (gData.nLanguage == 0) AfxMessageBox(_T("Tray 1,2번 Z축이 Up이나 Down위치가 아니여서 Y축을 이동할수 없습니다......"));
				else					  AfxMessageBox(_T("Tray 1,2 Z-axis are not in the Up or Down position, so the Y-axis cannot be moved."));
				return FALSE;
			}
		}
	}

	if (nAxis==AX_TRAY_Z1 || nAxis==AX_TRAY_Z2){
		if((g_objCommon.Check_Position(AX_TRAY_Y1, 0) && g_objCommon.Check_Position(AX_TRAY_Y2, 0)) ||
			(g_objCommon.Check_Position(AX_TRAY_Y1, 1) && g_objCommon.Check_Position(AX_TRAY_Y2, 1)) ||
			(g_objCommon.Check_Position(AX_TRAY_Y1, 2) && g_objCommon.Check_Position(AX_TRAY_Y2, 2)) ||
			(g_objCommon.Check_Position(AX_TRAY_Y1, 3) && g_objCommon.Check_Position(AX_TRAY_Y2, 3)) ||
			(g_objCommon.Check_Position(AX_TRAY_Y1, 4) && g_objCommon.Check_Position(AX_TRAY_Y2, 4)) ) {
				if (gData.nLanguage == 0) AfxMessageBox(_T("Tray 1,2번 Y축이 같은 위치에서는 Z축을 이동할수 없습니다......"));
				else					  AfxMessageBox(_T("You cannot move the Z axis in the same position as Tray 1,2 Y axis."));
				return FALSE;
		}
	}
	/*/
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
