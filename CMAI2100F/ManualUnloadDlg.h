// ManualUnloadDlg.h : 헤더 파일
//
#pragma once

// CManualUnloadDlg 대화 상자입니다.

class CManualUnloadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualUnloadDlg)

public:
	CManualUnloadDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualUnloadDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_UNLOAD_DLG };
	CGroupCS	m_Group[19];
	CLabelCS	m_Label[13];
	CStaticCS	m_stcAxisPos[13];
	CButton		m_btnUnloadPicker1X[18];
	CButtonCS	m_btnUnloadPicker1Y[9];
	CButtonCS	m_btnUnloadPicker1Z[9];
	CButtonCS	m_btnUnloadPicker1P[3];
	CButtonCS	m_btnUnloadPicker1IO[36];
	CButton		m_btnUnloadPicker2X[18];
	CButtonCS	m_btnUnloadPicker2Y[9];
	CButtonCS	m_btnUnloadPicker2Z[9];
	CButtonCS	m_btnUnloadPicker2P[3];
	CButtonCS	m_btnUnloadPicker2IO[36];
	CButtonCS	m_btnGoodStage1Y[8];
	CButtonCS	m_btnGoodStage1IO[6];
	CButtonCS	m_btnGoodStage2Y[8];
	CButtonCS	m_btnGoodStage2IO[6];
	CButtonCS	m_btnNGStage1Y[8];
	CButtonCS	m_btnNGStage1IO[6];
	CButtonCS	m_btnNGStage2Y[8];
	CButtonCS	m_btnNGStage2IO[6];
	CButtonCS	m_btnUnloadVisionX[4];

	CLedCS		m_ledUnloadPicker1IO[32];
	CLedCS		m_ledUnloadPicker2IO[32];
	CLedCS		m_ledGoodStage1IO[7];
	CLedCS		m_ledGoodStage2IO[7];
	CLedCS		m_ledNGStage1IO[7];
	CLedCS		m_ledNGStage2IO[7];


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnUnloadPicker1XClick(UINT nID);
	afx_msg void OnBtnUnloadPicker1YClick(UINT nID);
	afx_msg void OnBtnUnloadPicker1ZClick(UINT nID);
	afx_msg void OnBtnUnloadPicker1PClick(UINT nID);
	afx_msg void OnBtnUnloadPicker1IOClick(UINT nID);
	afx_msg void OnBtnUnloadPicker2XClick(UINT nID);
	afx_msg void OnBtnUnloadPicker2YClick(UINT nID);
	afx_msg void OnBtnUnloadPicker2ZClick(UINT nID);
	afx_msg void OnBtnUnloadPicker2PClick(UINT nID);
	afx_msg void OnBtnUnloadPicker2IOClick(UINT nID);
	afx_msg void OnBtnGoodStage1YClick(UINT nID);
	afx_msg void OnBtnGoodStage1IOClick(UINT nID);
	afx_msg void OnBtnGoodStage2YClick(UINT nID);
	afx_msg void OnBtnGoodStage2IOClick(UINT nID);
	afx_msg void OnBtnNGStage1YClick(UINT nID);
	afx_msg void OnBtnNGStage1IOClick(UINT nID);
	afx_msg void OnBtnNGStage2YClick(UINT nID);
	afx_msg void OnBtnNGStage2IOClick(UINT nID);
	afx_msg void OnBtnUnloadVisionXClick(UINT nID);

private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
