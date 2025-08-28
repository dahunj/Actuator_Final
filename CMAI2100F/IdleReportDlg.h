// IdleReportDlg.h : 헤더 파일
//
#pragma once

// CIdleReportDlg 대화 상자입니다.

class CIdleReportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CIdleReportDlg)

public:
	CIdleReportDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CIdleReportDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IDLE_REPORT_DLG };
	CGroupCS	m_Group;
	CLabelCS	m_Label[8];
	CStaticCS	m_stcSHH[5];
	CStaticCS	m_stcSMM[5];
	CStaticCS	m_stcSSS[5];
	CStaticCS	m_stcEHH[5];
	CStaticCS	m_stcEMM[5];
	CStaticCS	m_stcESS[5];
	CStaticCS	m_stcText[5];
	CListCS		m_lstIdleList;

	CButtonCS	m_btnOK;
	CButtonCS	m_btnCancel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStcClick(UINT nID);
	afx_msg void OnBnClickedBtnOk();
	afx_msg void OnBnClickedBtnCancel();

private:
	CBrush		m_brushBack;
	int			m_nBtnCnt;
	CString		m_strMsg;

	void Initial_Controls();
	void Display_List();
};

///////////////////////////////////////////////////////////////////////////////
