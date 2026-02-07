// ManualShipDlg.h : 헤더 파일
//
#pragma once

// CManualShipDlg 대화 상자입니다.

class CManualShipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualShipDlg)

public:
	CManualShipDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualShipDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_SHIP_DLG };
	CGroupCS	m_Group[18];
	CLabelCS	m_Label[12];
	CStaticCS	m_stcAxisPos[12];
	CButtonCS	m_btnShipPicker1X[10];
	CButtonCS	m_btnShipPicker1Y[3];
	CButtonCS	m_btnShipPicker1Z[6];
	CButtonCS	m_btnShipPicker1R[2];
	CButtonCS	m_btnShipPicker2X[10];
	CButtonCS	m_btnShipPicker2Y[3];
	CButtonCS	m_btnShipPicker2Z[6];
	CButtonCS	m_btnShipPicker2R[2];
	CButtonCS	m_btnShipPickerIo[12];
	CLedCS		m_ledShipPickerIo[10];
	CButtonCS	m_btnShipPortIo[4];
	CLedCS		m_ledShipPortIo[12];
	CButtonCS	m_btnShipTray1Y[5];
	CButtonCS	m_btnShipTray1Z[4];
	CButtonCS	m_btnShipTray2Y[5];
	CButtonCS	m_btnShipTray2Z[4];
	CButtonCS	m_btnShipTrayIo[8];
	CLedCS		m_ledShipTrayIo[12];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnShipPicker1XClick(UINT nID);
	afx_msg void OnBtnShipPicker1YClick(UINT nID);
	afx_msg void OnBtnShipPicker1ZClick(UINT nID);
	afx_msg void OnBtnShipPicker1RClick(UINT nID);
	afx_msg void OnBtnShipPicker2XClick(UINT nID);
	afx_msg void OnBtnShipPicker2YClick(UINT nID);
	afx_msg void OnBtnShipPicker2ZClick(UINT nID);
	afx_msg void OnBtnShipPicker2RClick(UINT nID);
	afx_msg void OnBtnShipPickerIoClick(UINT nID);
	afx_msg void OnBtnShipPortIoClick(UINT nID);
	afx_msg void OnBtnShipTray1YClick(UINT nID);
	afx_msg void OnBtnShipTray1ZClick(UINT nID);
	afx_msg void OnBtnShipTray2YClick(UINT nID);
	afx_msg void OnBtnShipTray2ZClick(UINT nID);
	afx_msg void OnBtnShipTrayIoClick(UINT nID);

private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
