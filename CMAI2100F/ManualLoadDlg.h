// ManualLoadDlg.h : 헤더 파일
//
#pragma once

// CManualLoadDlg 대화 상자입니다.

class CManualLoadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualLoadDlg)

public:
	CManualLoadDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualLoadDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_LOAD_DLG };
	CGroupCS	m_Group[18];
	CLabelCS	m_Label[13];
	CStaticCS	m_stcAxisPos[13];
	CButtonCS	m_btnLoadPicker1X[7];
	CButtonCS	m_btnLoadPicker1Y[5];
	CButtonCS	m_btnLoadPicker1Z[5];
	CButtonCS	m_btnLoadPicker1P[3];
	CButtonCS	m_btnLoadPicker1IO[36];
	CButtonCS	m_btnLoadPicker2X[7];
	CButtonCS	m_btnLoadPicker2Y[5];
	CButtonCS	m_btnLoadPicker2Z[5];
	CButtonCS	m_btnLoadPicker2P[3];
	CButtonCS	m_btnLoadPicker2IO[36];
	CButtonCS	m_btnLoadStage1Y[8];
	CButtonCS	m_btnLoadStage1IO[6];
	CButtonCS	m_btnLoadStage2Y[8];
	CButtonCS	m_btnLoadStage2IO[6];
	CButtonCS	m_btnBtmFocusZ[3];
	CButtonCS	m_btnBtmLightZ[3];
	CButtonCS	m_btnBtmAngleY[3];
	CButtonCS	m_btnCMAlignIO[6];

	CLedCS		m_ledLoadPicker1IO[32];
	CLedCS		m_ledLoadPicker2IO[32];
	CLedCS		m_ledLoadStage1IO[7];
	CLedCS		m_ledLoadStage2IO[7];
	CLedCS		m_ledCMAlignIO[6];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnLoadPicker1XClick(UINT nID);
	afx_msg void OnBtnLoadPicker1YClick(UINT nID);
	afx_msg void OnBtnLoadPicker1ZClick(UINT nID);
	afx_msg void OnBtnLoadPicker1PClick(UINT nID);
	afx_msg void OnBtnLoadPicker1IOClick(UINT nID);
	afx_msg void OnBtnLoadPicker2XClick(UINT nID);
	afx_msg void OnBtnLoadPicker2YClick(UINT nID);
	afx_msg void OnBtnLoadPicker2ZClick(UINT nID);
	afx_msg void OnBtnLoadPicker2PClick(UINT nID);
	afx_msg void OnBtnLoadPicker2IOClick(UINT nID);
	afx_msg void OnBtnLoadStage1YClick(UINT nID);
	afx_msg void OnBtnLoadStage1IOClick(UINT nID);
	afx_msg void OnBtnLoadStage2YClick(UINT nID);
	afx_msg void OnBtnLoadStage2IOClick(UINT nID);
	afx_msg void OnBtnBtmFocusZClick(UINT nID);
	afx_msg void OnBtnBtmLightZClick(UINT nID);
	afx_msg void OnBtnBtmAlgleYClick(UINT nID);
	afx_msg void OnBtnCMAlignIOClick(UINT nID);
	afx_msg void OnBnClickedBtnModuleAlignIo6();

private:
	CString m_strLog;

	void DoEvents(int nSleep = 0);
	void Initial_Controls();
	void Set_Align();

public:
	void Display_Status();
};
