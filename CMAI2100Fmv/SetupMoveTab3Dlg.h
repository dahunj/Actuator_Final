// SetupMoveTab3Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab3Dlg 대화 상자입니다.

class CSetupMoveTab3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab3Dlg)

public:
	CSetupMoveTab3Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab3Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB3_DLG };
	CGroupCS	m_Group[9];
	CLabelCS	m_Label[44];
	CStaticCS	m_stcInspectionX1[5];
	CStaticCS	m_stcInspectionX2[5];
	CStaticCS	m_stcInspectionX3[5];
	CStaticCS	m_stcInspectionX4[5];
	CStaticCS	m_stcTOPZ1[5];
	CStaticCS	m_stcTOP1LightZ[5];
	CStaticCS	m_stcTOP1AngleY[5];
	CStaticCS	m_stcTOPZ2[5];
	CStaticCS	m_stcShipAlignX[4];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStcInspectionX1Click(UINT nID);
	afx_msg void OnStcInspectionX2Click(UINT nID);
	afx_msg void OnStcInspectionX3Click(UINT nID);
	afx_msg void OnStcInspectionX4Click(UINT nID);
	afx_msg void OnStcTopZ1Click(UINT nID);
	afx_msg void OnStcTop1LightZClick(UINT nID);
	afx_msg void OnStcTop1AngleYClick(UINT nID);
	afx_msg void OnStcTopZ2Click(UINT nID);
	afx_msg void OnStcShipAlignXClick(UINT nID);
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
