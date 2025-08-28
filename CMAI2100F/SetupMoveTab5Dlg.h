// SetupMoveTab5Dlg.h : 헤더 파일
//
#pragma once

// CSetupMoveTab5Dlg 대화 상자입니다.

class CSetupMoveTab5Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupMoveTab5Dlg)

public:
	CSetupMoveTab5Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupMoveTab5Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_MOVE_TAB5_DLG };
	CGroupCS	m_Group[9];
	CLabelCS	m_Label[35];
	CStaticCS	m_stcInfor[3];
	CStaticCS	m_stcOffset[32];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStcOffsetClick(UINT nID);

private:
	CString	m_strLog;
	void Initial_Controls();
	void Display_MoveData();

public:
	void Save_MoveData();
	void Cancel_MoveData();
};

///////////////////////////////////////////////////////////////////////////////
