// InitialMotionDlg.h : 헤더 파일
//
#pragma once

// CInitialMotionDlg 대화 상자입니다.

class CInitialMotionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitialMotionDlg)

public:
	CInitialMotionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInitialMotionDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INITIAL_MOTION_DLG };
	CGroupCS	m_Group[1];
	CLabelCS	m_Label[6];
	CStaticCS	m_stcAxisName[45];
	CLedStatic	m_ledAxisRun[45];
	CLedStatic	m_ledAxisHom[45];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	void Initial_Controls();
	void Display_Status();
};

///////////////////////////////////////////////////////////////////////////////
