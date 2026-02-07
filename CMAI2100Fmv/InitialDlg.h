// InitialDlg.h : 헤더 파일
//
#pragma once

#include "InitialMotionDlg.h"

// CInitialDlg 대화 상자입니다.

class CInitialDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitialDlg)

public:
	CInitialDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CInitialDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INITIAL_DLG };
	CGroupCS	m_Group[5];
	CRadioCS	m_rdoInitStart;
	CRadioCS	m_rdoInitStop;
	CLedCS		m_ledInitialOK;
	CPictureCS	m_Image[3];
	CPictureCS	m_picInitFlow[10];
	CStaticCS	m_stcInitFlow[10];
	CLedCS		m_ledMainAir[4];
	CLedCS		m_ledEmgSw[6];
	CLedCS		m_ledDoorUnlock[21];
	CStaticCS	m_stcInitCase[9];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRdoInitStart();
	afx_msg void OnBnClickedRdoInitStop();
	afx_msg void OnBnClickedChkMotionTest();
	afx_msg void OnBnClickedButton1();

private:
	CInitialMotionDlg *m_pInitialMotionDlg;

	CBitmap	m_bmpImage[3];
	int		m_nBackColorLoop;
	BOOL	m_bInitialRunning;

	void Initial_Controls();
	void Display_Status();
	void Display_Initial();
	void Set_StatusColor(int nIdx, int nColor);	// nColor : 0:White,1:Red,2:Green,3:Blue
};

extern CInitialDlg g_dlgInitial;

///////////////////////////////////////////////////////////////////////////////
