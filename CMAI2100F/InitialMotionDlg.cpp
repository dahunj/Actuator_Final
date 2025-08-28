// InitialMotionDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "InitialMotionDlg.h"
#include "afxdialogex.h"

#include "AJinAXL.h"

// CInitialMotionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CInitialMotionDlg, CDialogEx)

CInitialMotionDlg::CInitialMotionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitialMotionDlg::IDD, pParent)
{
}

CInitialMotionDlg::~CInitialMotionDlg()
{
}

void CInitialMotionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 1; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 45; i++) DDX_Control(pDX, IDC_STC_AXIS_NAME_0 + i, m_stcAxisName[i]); 
	for (int i = 0; i < 45; i++) DDX_Control(pDX, IDC_LED_AXIS_RUN_0 + i, m_ledAxisRun[i]);
	for (int i = 0; i < 45; i++) DDX_Control(pDX, IDC_LED_AXIS_HOM_0 + i, m_ledAxisHom[i]);
}

BEGIN_MESSAGE_MAP(CInitialMotionDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CInitialMotionDlg 메시지 처리기입니다.

BOOL CInitialMotionDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CInitialMotionDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CInitialMotionDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
#ifdef NEW_FINAL
		m_stcAxisName[43].ShowWindow(FALSE);
		m_ledAxisRun[43].ShowWindow(FALSE);
		m_ledAxisHom[43].ShowWindow(FALSE);
		m_stcAxisName[44].ShowWindow(FALSE);
		m_ledAxisRun[44].ShowWindow(FALSE);
		m_ledAxisHom[44].ShowWindow(FALSE);
#endif

		for (int i = 0; i < AXIS_COUNT; i++) {
			CString strName = g_objAJinAXL.Get_AxisName(i);
			m_stcAxisName[i].SetWindowText(" " + strName);

/*			
			if (i == 22 || i == 23) {
				m_stcAxisName[i].ShowWindow(SW_HIDE);
				m_ledAxisRun[i].ShowWindow(SW_HIDE);
				m_ledAxisHom[i].ShowWindow(SW_HIDE);
			}
*/
		}
		SetTimer(0, 100, NULL);

	} else {
		KillTimer(0);
	}
}

void CInitialMotionDlg::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(0);

	Display_Status();

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CInitialMotionDlg::Initial_Controls() 
{
	for (int i = 0; i < 1; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 0; i < 6; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF),RGB(0x80, 0x80, 0x80));

	for (int i = 0; i < 45; i++) m_stcAxisName[i].Init_Ctrl("바탕", 9, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));
	for (int i = 0; i < 45; i++) m_ledAxisRun[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 45; i++) m_ledAxisHom[i].SetColor(RGB(0x00, 0xFF, 0x00), RGB(0x40, 0x40, 0x40));
}

void CInitialMotionDlg::Display_Status()
{
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (g_objAJinAXL.Get_MotorRun(i)) m_ledAxisRun[i].On();
		else m_ledAxisRun[i].Off();

		if (g_objAJinAXL.Get_HomeDone(i)) m_ledAxisHom[i].On();
		else m_ledAxisHom[i].Off();
	}
}

///////////////////////////////////////////////////////////////////////////////
