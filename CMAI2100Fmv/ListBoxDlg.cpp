// ListBoxDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ListBoxDlg.h"
#include "afxdialogex.h"

// CListBoxDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CListBoxDlg, CDialogEx)

CListBoxDlg::CListBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListBoxDlg::IDD, pParent)
{
}

CListBoxDlg::~CListBoxDlg()
{
}

void CListBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK,		m_btnOK);
	DDX_Control(pDX, IDCANCEL,	m_btnCancel);
	DDX_Control(pDX, IDC_LST_LOT_LIST, m_lstLotList);
}

BEGIN_MESSAGE_MAP(CListBoxDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_LBN_SELCHANGE(IDC_LST_LOT_LIST, &CListBoxDlg::OnLbnSelchangeLstList)
	ON_BN_CLICKED(IDOK, &CListBoxDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CListBoxDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// CListBoxDlg 메시지 처리기입니다.

BOOL CListBoxDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	Initial_Controls();
	gData.sListName = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CListBoxDlg::PreTranslateMessage(MSG* pMsg) 
{
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CListBoxDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		m_nDCnt = 0;
		Display_List();
		if (m_nDCnt> 0) {
			m_lstLotList.SetCurSel(0);
			OnLbnSelchangeLstList();
		}
	}
}

void CListBoxDlg::OnLbnSelchangeLstList()
{
	int nSelect = m_lstLotList.GetCurSel();
	CString strModel;
	m_lstLotList.GetText(nSelect, strModel);
	gData.sListName = strModel;
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CListBoxDlg::Initial_Controls() 
{
	m_btnOK.Init_Ctrl("바탕", 20, TRUE, RGB(0xFF, 0x00, 0xFF), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnCancel.Init_Ctrl("바탕", 20, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, IDI_CANCEL, CButtonCS::emLeft);
	m_lstLotList.Init_Ctrl("바탕", 20, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xFF));
}
/*
void CListBoxDlg::Set_Message(int nBtnCnt, CString strMsg) 
{
	m_nBtnCnt = nBtnCnt;
	m_strMsg = strMsg;
}
*/
///////////////////////////////////////////////////////////////////////////////


void CListBoxDlg::OnBnClickedOk()
{
	EndDialog(IDOK);
}


void CListBoxDlg::OnBnClickedCancel()
{
	gData.sListName = "";
	EndDialog(IDCANCEL);
}

void CListBoxDlg::Display_List()
{
	m_lstLotList.ResetContent();

	CString strModelFile, sFolder;
	int nFileLength;

	CFileFind Finder;
	
	sFolder.Format("LOG/Print/%s/%s/%s/*.txt", gData.sYYMMDD.Mid(0, 4), gData.sYYMMDD.Mid(4, 2), gData.sYYMMDD.Mid(6, 2));

	BOOL bContinue = Finder.FindFile(sFolder, NULL);
	while (bContinue) {
		bContinue = Finder.FindNextFile();
		if (Finder.IsDots()) continue;
		else if (Finder.IsDirectory()) continue;
		else {
			strModelFile = Finder.GetFileName();
//			if (strModelFile.Find(gData.sYYMMDD) > 1) {
			if (strModelFile.GetLength() > 4) {
				nFileLength = strModelFile.GetLength() - 4;
				m_lstLotList.AddString(strModelFile.Left(nFileLength));
				m_nDCnt++;
			}
		}
	}
}