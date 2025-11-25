// ManualReverseDlg.h : 헤더 파일
//
#pragma once

// CManualReverseDlg 대화 상자입니다.

class CManualReverseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualReverseDlg)

public:
	CManualReverseDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualReverseDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_REVERSE_DLG };
	CGroupCS	m_Group[7];
	CLabelCS	m_Label[5];
	CStaticCS	m_stcAxisPos[5];
	CButtonCS	m_btnReverse1Z[5];
	CButtonCS	m_btnReverse1R[2];
	CButtonCS	m_btnReverse2Z[5];
	CButtonCS	m_btnReverse2R[2];
	CButtonCS	m_btnReverseIo[28];
	CLedCS		m_ledReverseIo[12];
	CButtonCS	m_btnDropTableY[5];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnReverse1ZClick(UINT nID);
	afx_msg void OnBtnReverse1RClick(UINT nID);
	afx_msg void OnBtnReverse2ZClick(UINT nID);
	afx_msg void OnBtnReverse2RClick(UINT nID);
	afx_msg void OnBtnReverseIoClick(UINT nID);
	afx_msg void OnBtnDropTableYClick(UINT nID);

private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
