// ManualNgDlg.h : 헤더 파일
//
#pragma once

// CManualNgDlg 대화 상자입니다.

class CManualNgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualNgDlg)

public:
	CManualNgDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualNgDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_NG_DLG };
	CGroupCS	m_Group[21];
	CLabelCS	m_Label[12];
	CStaticCS	m_stcAxisPos[12];
	CButtonCS	m_btnNgPicker1Y[5];
	CButtonCS	m_btnNgPicker1X[2];
	CButtonCS	m_btnNgPicker1Z[3];
	CButtonCS	m_btnNgPicker1R[2];
	CButtonCS	m_btnNgPicker2Y[5];
	CButtonCS	m_btnNgPicker2X[2];
	CButtonCS	m_btnNgPicker2Z[3];
	CButtonCS	m_btnNgPicker2R[2];
	CButtonCS	m_btnNgPickerIo[28];
	CLedCS		m_ledNgPickerIo[18];
	CButtonCS	m_btnNgPortIo[6];
	CLedCS		m_ledNgPortIo[18];
	CButtonCS	m_btnNgTray1X[6];
	CButtonCS	m_btnNgTray1Z[4];
	CButtonCS	m_btnNgTray2X[6];
	CButtonCS	m_btnNgTray2Z[4];
	CButtonCS	m_btnNgTray1Pitch[2];
	CButtonCS	m_btnNgTray2Pitch[2];
	CButtonCS	m_btnNgTrayIo[8];
	CLedCS		m_ledNgTrayIo[12];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnNgPicker1YClick(UINT nID);
	afx_msg void OnBtnNgPicker1XClick(UINT nID);
	afx_msg void OnBtnNgPicker1ZClick(UINT nID);
	afx_msg void OnBtnNgPicker1RClick(UINT nID);
	afx_msg void OnBtnNgPicker2YClick(UINT nID);
	afx_msg void OnBtnNgPicker2XClick(UINT nID);
	afx_msg void OnBtnNgPicker2ZClick(UINT nID);
	afx_msg void OnBtnNgPicker2RClick(UINT nID);
	afx_msg void OnBtnNgPickerIoClick(UINT nID);
	afx_msg void OnBtnNgPortIoClick(UINT nID);
	afx_msg void OnBtnNgTray1XClick(UINT nID);
	afx_msg void OnBtnNgTray1ZClick(UINT nID);
	afx_msg void OnBtnNgTray2XClick(UINT nID);
	afx_msg void OnBtnNgTray2ZClick(UINT nID);
	afx_msg void OnBtnNgTray1PitchClick(UINT nID);
	afx_msg void OnBtnNgTray2PitchClick(UINT nID);
	afx_msg void OnBtnNgTrayIoClick(UINT nID);

private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
