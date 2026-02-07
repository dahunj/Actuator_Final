// SetupMoveTab1Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab1Dlg 대화 상자입니다.

class CSetupMoveTab1Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab1Dlg)

public:
	CSetupMoveTab1Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab1Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB1_DLG };
	CGroupCS	m_Group[11];
	CLabelCS	m_Label[68];
	CStaticCS	m_stcElevator[21];
	CStaticCS	m_stcTransfreX1[8];
	CStaticCS	m_stcTransfreX2[13];
	CStaticCS	m_stcTransfreZ1[11];
	CStaticCS	m_stcTransfreZ2[15];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStcElevatorClick(UINT nID);
	afx_msg void OnStcTransferX1Click(UINT nID);
	afx_msg void OnStcTransferX2Click(UINT nID);
	afx_msg void OnStcTransferZ1Click(UINT nID);
	afx_msg void OnStcTransferZ2Click(UINT nID);

private:
	CString	m_strLog;
	void Initial_Controls();
	void Display_MoveData();

public:
	void Save_MoveData();
	void Save_ModelMoveData();
	void Cancel_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
