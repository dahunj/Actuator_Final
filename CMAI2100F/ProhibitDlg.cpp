// ProhibitDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ProhibitDlg.h"
#include "afxdialogex.h"

// CProhibitDlg 대화 상자입니다.

CProhibitDlg g_dlgProhibit;

IMPLEMENT_DYNAMIC(CProhibitDlg, CDialogEx)

CProhibitDlg::CProhibitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProhibitDlg::IDD, pParent)
{
}

CProhibitDlg::~CProhibitDlg()
{
}

void CProhibitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STC_PROHIBIT_TITLE, m_stcProhibitTitle);
	DDX_Control(pDX, IDC_STC_PROHIBIT_MESSAGE, m_stcProhibitMessage);
}

BEGIN_MESSAGE_MAP(CProhibitDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CProhibitDlg 메시지 처리기입니다.

BOOL CProhibitDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(this, 0, 75, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CProhibitDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

HBRUSH CProhibitDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)m_brushBack;

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CProhibitDlg::Initial_Controls() 
{
//	m_brushBack.CreateSolidBrush(RGB(0x00, 0x00, 0x00));
	m_brushBack.CreateSolidBrush(RGB(0xFF, 0x00, 0x00));

	m_stcProhibitTitle.Init_Ctrl("바탕", 30, TRUE, RGB(0xFF, 0xFF, 0x00), RGB(0x00, 0x00, 0x00));
	m_stcProhibitMessage.Init_Ctrl("바탕", 30, FALSE, RGB(0xFF, 0x00, 0x00), RGB(0x00, 0x00, 0x00));

	m_stcProhibitTitle.SetWindowText("Prohibit Operation !!!\n조작하지 마세요.");
	m_stcProhibitMessage.SetWindowText("We are checking on this equipment !!!\n설비 점검 중입니다.");
}

///////////////////////////////////////////////////////////////////////////////
