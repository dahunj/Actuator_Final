// SetupMoveTab6Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab6Dlg 대화 상자입니다.

class CSetupMoveTab6Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab6Dlg)

public:
	CSetupMoveTab6Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab6Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB6_DLG };
	CGroupCS	m_Group[17];
	CLabelCS	m_Label[63];
	CStaticCS	m_stcShipTray1Y[3];
	CStaticCS	m_stcShipTray1Z[4];
	CStaticCS	m_stcShipTray2Y[3];
	CStaticCS	m_stcShipTray2Z[4];
	CStaticCS	m_stcShipPicker1X[8];
	CStaticCS	m_stcShipPicker1Y[3];
	CStaticCS	m_stcShipPicker1Z[4];
	CStaticCS	m_stcShipPicker1R[2];
	CStaticCS	m_stcShipPicker2X[8];
	CStaticCS	m_stcShipPicker2Y[3];
	CStaticCS	m_stcShipPicker2Z[4];
	CStaticCS	m_stcShipPicker2R[2];
	CStaticCS	m_stcReverse1Z[3];
	CStaticCS	m_stcReverse1R[2];
	CStaticCS	m_stcReverse2Z[3];
	CStaticCS	m_stcReverse2R[2];
	CStaticCS	m_stcDropTableY[5];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStcShipTray1YClick(UINT nID);
	afx_msg void OnStcShipTray1ZClick(UINT nID);
	afx_msg void OnStcShipTray2YClick(UINT nID);
	afx_msg void OnStcShipTray2ZClick(UINT nID);
	afx_msg void OnStcShipPicker1XClick(UINT nID);
	afx_msg void OnStcShipPicker1YClick(UINT nID);
	afx_msg void OnStcShipPicker1ZClick(UINT nID);
	afx_msg void OnStcShipPicker1RClick(UINT nID);
	afx_msg void OnStcShipPicker2XClick(UINT nID);
	afx_msg void OnStcShipPicker2YClick(UINT nID);
	afx_msg void OnStcShipPicker2ZClick(UINT nID);
	afx_msg void OnStcShipPicker2RClick(UINT nID);
	afx_msg void OnStcReverse1ZClick(UINT nID);
	afx_msg void OnStcReverse1RClick(UINT nID);
	afx_msg void OnStcReverse2ZClick(UINT nID);
	afx_msg void OnStcReverse2RClick(UINT nID);
	afx_msg void OnStcDropTableYClick(UINT nID);

private:
	void Initial_Controls();
	void Display_MoveData();

public:
	void Save_MoveData();
	void Cancel_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
