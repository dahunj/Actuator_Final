// ManualShipDlg.h : 헤더 파일
//
#pragma once

// CManualShipAlnDlg 대화 상자입니다.

class CManualShipAlnDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualShipAlnDlg)

public:
	CManualShipAlnDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualShipAlnDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_SHIP_ALN_DLG };
	CGroupCS	m_Group[4];
	CLabelCS	m_Label[4];
	CStaticCS	m_stcAxisPos[4];
	CButtonCS	m_btnAlnShipPick1X[6];
	CButtonCS	m_btnAlnShipPick1Y[6];
	CButtonCS	m_btnAlnShipPick2X[6];
	CButtonCS	m_btnAlnShipPick2Y[6];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnAlnShipPick1XClick(UINT nID);
	afx_msg void OnBtnAlnShipPick1YClick(UINT nID);
	afx_msg void OnBtnAlnShipPick2XClick(UINT nID);
	afx_msg void OnBtnAlnShipPick2YClick(UINT nID);

private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
