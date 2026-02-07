// ManualTransDlg.h : 헤더 파일
//
#pragma once

// CManualTransDlg 대화 상자입니다.

class CManualTransDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualTransDlg)

public:
	CManualTransDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualTransDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_TRANS_DLG };
	CGroupCS	m_Group[23];
	CLabelCS	m_Label[20];
	CStaticCS	m_stcAxisPos[20];
	CButtonCS	m_btnTransPickerX[3];
	CButtonCS	m_btnTransPickerZ[4];
	CButtonCS	m_btnTransPickerR1[3];
	CButtonCS	m_btnTransPickerR2[3];
	CButtonCS	m_btnTransPickerIo[4];
	CLedCS		m_ledTransPickerIo[2];
	CButtonCS	m_btnTransStage1X[8];
	CButtonCS	m_btnTransStage1Y[2];
	CButtonCS	m_btnTransStage2X[8];
	CButtonCS	m_btnTransStage2Z[2];
	CButtonCS	m_btnTransStage3X[8];
	CButtonCS	m_btnTransStage3Y[2];
	CButtonCS	m_btnTransStage4X[8];
	CButtonCS	m_btnTransStage4Z[2];
	CButtonCS	m_btnTransStageIo[24];
	CLedCS		m_ledTransStageIo[18];
	CStaticCS	m_stcTransStg1Align[3];
	CButtonCS	m_btnTransStg1Align;
	CStaticCS	m_stcTransStg2Align[3];
	CButtonCS	m_btnTransStg2Align;
	CStaticCS	m_stcTransStg3Align[3];
	CButtonCS	m_btnTransStg3Align;
	CStaticCS	m_stcTransStg4Align[3];
	CButtonCS	m_btnTransStg4Align;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnTransPickerXClick(UINT nID);
	afx_msg void OnBtnTransPickerZClick(UINT nID);
	afx_msg void OnBtnTransPickerR1Click(UINT nID);
	afx_msg void OnBtnTransPickerR2Click(UINT nID);
	afx_msg void OnBtnTransPickerIoClick(UINT nID);
	afx_msg void OnBtnTransStage1XClick(UINT nID);
	afx_msg void OnBtnTransStage1YClick(UINT nID);
	afx_msg void OnBtnTransStage2XClick(UINT nID);
	afx_msg void OnBtnTransStage2ZClick(UINT nID);
	afx_msg void OnBtnTransStage3XClick(UINT nID);
	afx_msg void OnBtnTransStage3YClick(UINT nID);
	afx_msg void OnBtnTransStage4XClick(UINT nID);
	afx_msg void OnBtnTransStage4ZClick(UINT nID);
	afx_msg void OnBtnTransStageIoClick(UINT nID);
	afx_msg void OnBnClickedBtnTransStg1Align();
	afx_msg void OnBnClickedBtnTransStg2Align();
	afx_msg void OnBnClickedBtnTransStg3Align();
	afx_msg void OnBnClickedBtnTransStg4Align();

private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
