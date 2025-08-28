// KeyPadDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "KeyPadDlg.h"
#include "afxdialogex.h"

// CKeyPadDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CKeyPadDlg, CDialogEx)

CString g_strReturnKeyPad;

CKeyPadDlg::CKeyPadDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeyPadDlg::IDD, pParent)
{
}

CKeyPadDlg::~CKeyPadDlg()
{
}

void CKeyPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LABEL_0, m_Label);
	DDX_Control(pDX, IDC_STC_KEY_NAME, m_stcKeyName);
	DDX_Control(pDX, IDC_BTN_BACK, m_btnBack);
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btnClear);
	for (int i = 0; i < 38; i++) DDX_Control(pDX, IDC_BTN_KEY_0 + i, m_btnKey[i]);
	DDX_Control(pDX, IDC_BTN_OK, m_btnOK);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CKeyPadDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_BACK, &CKeyPadDlg::OnBnClickedBtnBack)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CKeyPadDlg::OnBnClickedBtnClear)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BTN_KEY_0, IDC_BTN_KEY_37, OnBtnKeyClick)
	ON_BN_CLICKED(IDC_BTN_OK, &CKeyPadDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CKeyPadDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CKeyPadDlg 메시지 처리기입니다.

BOOL CKeyPadDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	Initial_Controls();

	g_strReturnKeyPad = "";

	m_stcKeyName.SetWindowText("");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CKeyPadDlg::PreTranslateMessage(MSG* pMsg) 
{
//	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
//		return TRUE;
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_ESCAPE) return TRUE;
		if (pMsg->wParam == VK_RETURN) { OnBnClickedBtnOk(); return TRUE; }
		if (pMsg->wParam == VK_BACK) { OnBnClickedBtnBack(); return TRUE; }
		if (pMsg->wParam == VK_DELETE) { OnBnClickedBtnBack(); return TRUE; }
	}

	if (pMsg->message == WM_CHAR) {
		TCHAR tChar[256];
		tChar[0] = pMsg->wParam;
		tChar[1] = NULL;

		if ((tChar[0] >= '0' && tChar[0] <= '9') ||
			(tChar[0] >= 'a' && tChar[0] <= 'z') ||
			(tChar[0] >= 'A' && tChar[0] <= 'Z') ||
			(tChar[0] == '-') || (tChar[0] == '_')) {
			CString strKeyName, sData;
			sData = tChar;	sData.MakeUpper();
			m_stcKeyName.GetWindowText(strKeyName);
			m_stcKeyName.SetWindowText(strKeyName + sData);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

HBRUSH CKeyPadDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)m_brushBack;

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CKeyPadDlg::OnBnClickedBtnBack()
{
	CString strKeyName;
	m_stcKeyName.GetWindowText(strKeyName);
	int nLen = strKeyName.GetLength();
	if (nLen > 0) m_stcKeyName.SetWindowText(strKeyName.Left(nLen - 1));
}

void CKeyPadDlg::OnBnClickedBtnClear()
{
	m_stcKeyName.SetWindowText("");
}

void CKeyPadDlg::OnBtnKeyClick(UINT nID)
{
	int ID = nID - IDC_BTN_KEY_0;

	CString strKeyName, strKey;
	m_stcKeyName.GetWindowText(strKeyName);
	m_btnKey[ID].GetWindowText(strKey);
	m_stcKeyName.SetWindowText(strKeyName + strKey);
}

void CKeyPadDlg::OnBnClickedBtnOk()
{
	CString strKeyName;
	m_stcKeyName.GetWindowText(strKeyName);
//	if (strKeyName == "") return;
	g_strReturnKeyPad = strKeyName;
	EndDialog(IDOK);
}

void CKeyPadDlg::OnBnClickedBtnCancel()
{
	EndDialog(IDCANCEL);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CKeyPadDlg::Initial_Controls() 
{
	m_brushBack.CreateSolidBrush(RGB(0x90, 0x80, 0xC0));

	m_Label.Init_Ctrl("바탕", 15, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_stcKeyName.Init_Ctrl("바탕", 20, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xFF, 0xB0));

	m_btnBack.Init_Ctrl("바탕", 15, TRUE, RGB(0x80, 0x80, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnClear.Init_Ctrl("바탕", 15, TRUE, RGB(0x00, 0x80, 0x00), COLOR_DEFAULT, 0, 0);

	for (int i = 0; i < 38; i++) m_btnKey[i].Init_Ctrl("바탕", 20, TRUE, RGB(0xB0, 0x50, 0x00), COLOR_DEFAULT, 0, 0);

	m_btnOK.Init_Ctrl("바탕", 20, TRUE, RGB(0xFF, 0x00, 0xFF), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnCancel.Init_Ctrl("바탕", 20, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, IDI_CANCEL, CButtonCS::emLeft);
}

///////////////////////////////////////////////////////////////////////////////

