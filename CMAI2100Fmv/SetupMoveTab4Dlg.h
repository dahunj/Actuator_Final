// SetupMoveTab4Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab4Dlg 대화 상자입니다.

class CSetupMoveTab4Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab4Dlg)

public:
	CSetupMoveTab4Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab4Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB4_DLG };
	CGroupCS	m_Group[13];
	CLabelCS	m_Label[86];
	CStaticCS	m_stcUnloadPickX1[16];
	CStaticCS	m_stcUnloadPickY1[9];
	CStaticCS	m_stcUnloadPickZ1[9];
	CStaticCS	m_stcUnloadPickP1[3];
	CStaticCS	m_stcUnloadPickX2[16];
	CStaticCS	m_stcUnloadPickY2[9];
	CStaticCS	m_stcUnloadPickZ2[9];
	CStaticCS	m_stcUnloadPickP2[3];
	CStaticCS	m_stcNGStageY1[6];
	CStaticCS	m_stcNGStageY2[6];
	CStaticCS	m_stcGoodStageY1[6];
	CStaticCS	m_stcGoodStageY2[6];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStcUnloadPickX1Click(UINT nID);
	afx_msg void OnStcUnloadPickY1Click(UINT nID);
	afx_msg void OnStcUnloadPickZ1Click(UINT nID);
	afx_msg void OnStcUnloadPickP1Click(UINT nID);
	afx_msg void OnStcUnloadPickX2Click(UINT nID);
	afx_msg void OnStcUnloadPickY2Click(UINT nID);
	afx_msg void OnStcUnloadPickZ2Click(UINT nID);
	afx_msg void OnStcUnloadPickP2Click(UINT nID);
	afx_msg void OnStcNGStageY1Click(UINT nID);
	afx_msg void OnStcNGStageY2Click(UINT nID);
	afx_msg void OnStcGoodStageY1Click(UINT nID);
	afx_msg void OnStcGoodStageY2Click(UINT nID);
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
