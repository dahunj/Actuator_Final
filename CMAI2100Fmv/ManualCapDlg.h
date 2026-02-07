// ManualCapDlg.h : 헤더 파일
//
#pragma once

#include "LoopTimer.h"

// CManualCapDlg 대화 상자입니다.

class CManualCapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualCapDlg)

public:
	CManualCapDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualCapDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_CAP_DLG };
	CGroupCS	m_Group[24];
	CLabelCS	m_Label[12];
	CStaticCS	m_stcAxisPos[12];
	CButtonCS	m_btnCapPicker1Y[6];
	CButtonCS	m_btnCapPicker1X[3];
	CButtonCS	m_btnCapPicker1Z[4];
	CButtonCS	m_btnCapPicker1R[2];
	CButtonCS	m_btnCapPicker2Y[6];
	CButtonCS	m_btnCapPicker2X[3];
	CButtonCS	m_btnCapPicker2Z[4];
	CButtonCS	m_btnCapPicker2R[2];
	CButtonCS	m_btnCapPick1Pitch[2];
	CButtonCS	m_btnCapPick2Pitch[2];
	CButtonCS	m_btnCapPickerIo[28];
	CLedCS		m_ledCapPickerIo[18];
	CStaticCS	m_stcCapPick1Align[3];
	CButtonCS	m_btnCapPick1Align;
	CStaticCS	m_stcCapPick2Align[3];
	CButtonCS	m_btnCapPick2Align;
	CButtonCS	m_btnCapPortIo[4];
	CLedCS		m_ledCapPortIo[12];
	CButtonCS	m_btnCapTray1X[5];
	CButtonCS	m_btnCapTray1Z[4];
	CButtonCS	m_btnCapTray2X[5];
	CButtonCS	m_btnCapTray2Z[4];
	CButtonCS	m_btnCapTrayIo[8];
	CLedCS		m_ledCapTrayIo[12];
	CStaticCS	m_stcCapTray1Case;
	CStaticCS	m_stcCapTray2Case;
	CCheckCS	m_chkCapTray1Clear;
	CCheckCS	m_chkCapTray2Clear;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnCapPicker1YClick(UINT nID);
	afx_msg void OnBtnCapPicker1XClick(UINT nID);
	afx_msg void OnBtnCapPicker1ZClick(UINT nID);
	afx_msg void OnBtnCapPicker1RClick(UINT nID);
	afx_msg void OnBtnCapPicker2YClick(UINT nID);
	afx_msg void OnBtnCapPicker2XClick(UINT nID);
	afx_msg void OnBtnCapPicker2ZClick(UINT nID);
	afx_msg void OnBtnCapPicker2RClick(UINT nID);
	afx_msg void OnBtnCapPick1PitchClick(UINT nID);
	afx_msg void OnBtnCapPick2PitchClick(UINT nID);
	afx_msg void OnBtnCapPickerIoClick(UINT nID);
	afx_msg void OnBnClickedBtnCapPick1Align();
	afx_msg void OnBnClickedBtnCapPick2Align();
	afx_msg void OnBtnCapPortIoClick(UINT nID);
	afx_msg void OnBtnCapTray1XClick(UINT nID);
	afx_msg void OnBtnCapTray1ZClick(UINT nID);
	afx_msg void OnBtnCapTray2XClick(UINT nID);
	afx_msg void OnBtnCapTray2ZClick(UINT nID);
	afx_msg void OnBtnCapTrayIoClick(UINT nID);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedChkCapTray1Clear();
	afx_msg void OnBnClickedChkCapTray2Clear();

private:
	CString m_strLog;
	void Initial_Controls();

	int  m_nCapTray1Case;
	int  m_nCapTray2Case;
	CLoopTimer m_tCapTray1Loop;
	CLoopTimer m_tCapTray2Loop;

	BOOL m_bCapTrayClearRun;
	BOOL CapTray1_Clear();
	BOOL CapTray2_Clear();

public:
	void Display_Status();
};
