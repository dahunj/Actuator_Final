// ManualInspDlg.h : 헤더 파일
//
#pragma once

// CManualInspDlg 대화 상자입니다.

class CManualInspDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualInspDlg)

public:
	CManualInspDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualInspDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_INSP_DLG };
	CGroupCS	m_Group[12];
	CLabelCS	m_Label[8];
	CStaticCS	m_stcAxisPos[8];
	CButtonCS	m_btnInspectionX1[7];
	CButtonCS	m_btnInspectionX2[7];
	CButtonCS	m_btnInspectionX3[7];
	CButtonCS	m_btnInspectionX4[7];
	CButtonCS	m_btnTop1Z[5];
	CButtonCS	m_btnTop2Z[5];
	CButtonCS	m_btnTop1LightZ[5];
	CButtonCS	m_btnTop1AngleY[5];

	CButtonCS	m_btnInsp1IO[6];
	CButtonCS	m_btnInsp2IO[6];
	CButtonCS	m_btnInsp3IO[6];
	CButtonCS	m_btnInsp4IO[6];
	CLedCS		m_ledInsp1IO[6];
	CLedCS		m_ledInsp2IO[6];
	CLedCS		m_ledInsp3IO[6];
	CLedCS		m_ledInsp4IO[6];

	CButtonCS	m_btnInsp1VaccumOn[9];
	CButtonCS	m_btnInsp1VaccumOff[9];
	CButtonCS	m_btnInsp2VaccumOn[9];
	CButtonCS	m_btnInsp2VaccumOff[9];
	CButtonCS	m_btnInsp3VaccumOn[9];
	CButtonCS	m_btnInsp3VaccumOff[9];
	CButtonCS	m_btnInsp4VaccumOn[9];
	CButtonCS	m_btnInsp4VaccumOff[9];
	CLedCS		m_ledInsp1VacuumOn[8];
	CLedCS		m_ledInsp2VacuumOn[8];
	CLedCS		m_ledInsp3VacuumOn[8];
	CLedCS		m_ledInsp4VacuumOn[8];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnInspectionX1Click(UINT nID);
	afx_msg void OnBtnInspectionX2Click(UINT nID);
	afx_msg void OnBtnInspectionX3Click(UINT nID);
	afx_msg void OnBtnInspectionX4Click(UINT nID);

	afx_msg void OnBtnTop1ZClick(UINT nID);
	afx_msg void OnBtnTop2ZClick(UINT nID);
	afx_msg void OnBtnTop1LightZClick(UINT nID);
	afx_msg void OnBtnTop1AngleYClick(UINT nID);

	afx_msg void OnBtnInsp1IOClick(UINT nID);
	afx_msg void OnBtnInsp2IOClick(UINT nID);
	afx_msg void OnBtnInsp3IOClick(UINT nID);
	afx_msg void OnBtnInsp4IOClick(UINT nID);

	afx_msg void OnBtnInsp1VacuumOnClick(UINT nID);
	afx_msg void OnBtnInsp1VacuumOffClick(UINT nID);
	afx_msg void OnBtnInsp2VacuumOnClick(UINT nID);
	afx_msg void OnBtnInsp2VacuumOffClick(UINT nID);
	afx_msg void OnBtnInsp3VacuumOnClick(UINT nID);
	afx_msg void OnBtnInsp3VacuumOffClick(UINT nID);
	afx_msg void OnBtnInsp4VacuumOnClick(UINT nID);
	afx_msg void OnBtnInsp4VacuumOffClick(UINT nID);

private:
	CString m_strLog;
	void Initial_Controls();
	BOOL Check_VisionStage(int nStageNo, int nToPos);
	void Set_VisionPostion(int nStageNo, int nToPos);
	void Set_VisionUpDown(int nStageNo, int nUpDown);

public:
	void Display_Status();
};
