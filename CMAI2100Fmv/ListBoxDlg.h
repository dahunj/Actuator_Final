// ListBoxDlg.h : 헤더 파일
//
#pragma once

// CListBoxDlg 대화 상자입니다.

class CListBoxDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListBoxDlg)

public:
	CListBoxDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CListBoxDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LIST_BOX_DLG };
	CButtonCS	m_btnOK;
	CButtonCS	m_btnCancel;
	CListCS		m_lstLotList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLbnSelchangeLstList();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
private:
	int	m_nDCnt;
	void Initial_Controls();

public:
	void Display_List();
};

///////////////////////////////////////////////////////////////////////////////
