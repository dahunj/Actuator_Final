// SetupMoveTab2Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab2Dlg 대화 상자입니다.

class CSetupMoveTab2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab2Dlg)

public:
	CSetupMoveTab2Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab2Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB2_DLG };
	CGroupCS	m_Group[13];
	CLabelCS	m_Label[55];
	CStaticCS	m_stcLoadPickX1[4];
	CStaticCS	m_stcLoadPickY1[5];
	CStaticCS	m_stcLoadPickZ1[5];
	CStaticCS	m_stcLoadPickP1[3];
	CStaticCS	m_stcLoadPickX2[4];
	CStaticCS	m_stcLoadPickY2[5];
	CStaticCS	m_stcLoadPickZ2[5];
	CStaticCS	m_stcLoadPickP2[3];
	CStaticCS	m_stcLoadStageY1[6];
	CStaticCS	m_stcLoadStageY2[6];
	CStaticCS	m_stcBtmFocusZ[3];
	CStaticCS	m_stcBtmLightZ[3];
	CStaticCS	m_stcBtmAngleY[3];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStcLoadPickX1Click(UINT nID);
	afx_msg void OnStcLoadPickY1Click(UINT nID);
	afx_msg void OnStcLoadPickZ1Click(UINT nID);
	afx_msg void OnStcLoadPickP1Click(UINT nID);
	afx_msg void OnStcLoadPickX2Click(UINT nID);
	afx_msg void OnStcLoadPickY2Click(UINT nID);
	afx_msg void OnStcLoadPickZ2Click(UINT nID);
	afx_msg void OnStcLoadPickP2Click(UINT nID);
	afx_msg void OnStcLoadStageY1Click(UINT nID);
	afx_msg void OnStcLoadStageY2Click(UINT nID);
	afx_msg void OnstcBtmFocusZClick(UINT nID);
	afx_msg void OnstcBtmLightZClick(UINT nID);
	afx_msg void OnstcBtmAngleYClick(UINT nID);

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
