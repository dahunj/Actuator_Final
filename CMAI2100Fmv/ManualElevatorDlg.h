// ManualElevatorDlg.h : 헤더 파일
//
#pragma once

#include "LoopTimer.h"
// CManualElevatorDlg 대화 상자입니다.

class CManualElevatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualElevatorDlg)

public:
	CManualElevatorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualElevatorDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_ELEVATOR_DLG };
	CGroupCS	m_Group[20];
	CLabelCS	m_Label[11];
	CStaticCS	m_stcAxisPos[11];
	CButtonCS	m_btnLoad1ElevatorZ[2];
	CButtonCS	m_btnLoad1ElevatorIO[4];
	CButtonCS	m_btnLoad2ElevatorZ[2];
	CButtonCS	m_btnLoad2ElevatorIO[4];
	CButtonCS	m_btnNGEmptyElevatorZ[2];
	CButtonCS	m_btnNGEmptyElevatorIO[4];
	CButtonCS	m_btnGoodEmptyElevatorZ[2];
	CButtonCS	m_btnGoodEmptyElevatorIO[4];
	CButtonCS	m_btnNGBufferElevatorZ[2];
	CButtonCS	m_btnNGBufferElevatorIO[4];
	CButtonCS	m_btnGood1ElevatorZ[2];
	CButtonCS	m_btnGood1ElevatorIO[4];
	CButtonCS	m_btnGood2ElevatorZ[2];
	CButtonCS	m_btnGood2ElevatorIO[4];
	CButtonCS	m_btnTrayTrans1X[8];
	CButtonCS	m_btnTrayTrans1Z[11];
	CButtonCS	m_btnTrayTrans1IO[2];
	CButtonCS	m_btnTrayTrans2X[13];
	CButtonCS	m_btnTrayTrans2Z[15];
	CButtonCS	m_btnTrayTrans2IO[2];

	CLedCS		m_ledLoad1Elevator[11];
	CLedCS		m_ledLoad2Elevator[11];
	CLedCS		m_ledNGEmptyElevator[11];
	CLedCS		m_ledGoodEmptyElevator[11];
	CLedCS		m_ledNGBufferElevator[11];
	CLedCS		m_ledGood1Elevator[11];
	CLedCS		m_ledGood2Elevator[11];
	CLedCS		m_ledTrayTrans1[5];
	CLedCS		m_ledTrayTrans2[5];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnbtnLoad1ElevatorZClick(UINT nID);
	afx_msg void OnbtnLoad1ElevatorIOClick(UINT nID);
	afx_msg void OnbtnLoad2ElevatorZClick(UINT nID);
	afx_msg void OnbtnLoad2ElevatorIOClick(UINT nID);
	afx_msg void OnbtnNGEmptyElevatorZClick(UINT nID);
	afx_msg void OnbtnNGEmptyElevatorIOClick(UINT nID);
	afx_msg void OnbtnGoodEmptyElevatorZClick(UINT nID);
	afx_msg void OnbtnGoodEmptyElevatorIOClick(UINT nID);
	afx_msg void OnbtnNGBufferElevatorZClick(UINT nID);
	afx_msg void OnbtnNGBufferElevatorIOClick(UINT nID);
	afx_msg void OnbtnGood1ElevatorZClick(UINT nID);
	afx_msg void OnbtnGood1ElevatorIOClick(UINT nID);
	afx_msg void OnbtnGood2ElevatorZClick(UINT nID);
	afx_msg void OnbtnGood2ElevatorIOClick(UINT nID);
	afx_msg void OnbtnTrayTrans1XClick(UINT nID);
	afx_msg void OnbtnTrayTrans1ZClick(UINT nID);
	afx_msg void OnbtnTrayTrans1IOClick(UINT nID);
	afx_msg void OnbtnTrayTrans2XClick(UINT nID);
	afx_msg void btnTrayTrans2ZClick(UINT nID);
	afx_msg void btnTrayTrans2IOClick(UINT nID);

private:
	CString		m_strLog;
	int			m_nRunCase1, m_nRunCase2, m_nRunCase3, m_nRunCase4, m_nRunCase5, m_nRunCase6, m_nRunCase7;	// Run Case
	CLoopTimer	m_tEleLoop1, m_tEleLoop2, m_tEleLoop3, m_tEleLoop4, m_tEleLoop5, m_tEleLoop6, m_tEleLoop7;

	void Initial_Controls();
	BOOL Manual_ElevatorRun1();
	BOOL Manual_ElevatorRun2();
	BOOL Manual_ElevatorRun3();
	BOOL Manual_ElevatorRun4();
	BOOL Manual_ElevatorRun5();
	BOOL Manual_ElevatorRun6();
	BOOL Manual_ElevatorRun7();

protected:
	BOOL		m_bThreadElevator;
	CWinThread	*m_pThreadElevator;
	static UINT	Thread_Elevator(LPVOID lpVoid);

public:
	void Display_Status();
	afx_msg void OnBnClickedBtnElevator10();
	afx_msg void OnBnClickedBtnElevatorIn10();

	void Begin_ElevatorThread();
	void End_ElevatorThread();
};
