// SetupMoveTab7Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab7Dlg 대화 상자입니다.

class CSetupMoveTab7Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab7Dlg)

public:
	CSetupMoveTab7Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab7Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB7_DLG };
	CGroupCS	m_Group[5];
	CLabelCS	m_Label[32];
	CStaticCS	m_stcAlnShipPick1X[6];
	CStaticCS	m_stcAlnShipPick1Y[6];
	CStaticCS	m_stcAlnShipPick2X[6];
	CStaticCS	m_stcAlnShipPick2Y[6];
	CStaticCS	m_stcAlnShipPitchX[4];
	CStaticCS	m_stcAlnShipPitchY[4];
	CStaticCS	m_stcAlnShipOffsetX[4];
	CStaticCS	m_stcAlnShipOffsetY[4];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStcAlnShipPick1XClick(UINT nID);
	afx_msg void OnStcAlnShipPick1YClick(UINT nID);
	afx_msg void OnStcAlnShipPick2XClick(UINT nID);
	afx_msg void OnStcAlnShipPick2YClick(UINT nID);

private:
	void Initial_Controls();
	void Display_MoveData();

public:
	void Save_MoveData();
	void Cancel_MoveData();
};
