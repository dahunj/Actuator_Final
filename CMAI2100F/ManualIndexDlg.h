// ManualIndexDlg.h : 헤더 파일
//
#pragma once

// CManualIndexDlg 대화 상자입니다.

class CManualIndexDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualIndexDlg)

public:
	CManualIndexDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualIndexDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MANUAL_INDEX_DLG };
	CGroupCS	m_Group[30];
	CLabelCS	m_Label[23];
	CStaticCS	m_stcAxisPos[23];
	CButtonCS	m_btnMainIndexR[2];
	CStaticCS	m_stcMainIndexPos;
	CLedCS		m_ledMainIndexPos[4];
	CButtonCS	m_btnMainIdxVacIo[26];
	CLedCS		m_ledMainIdxVacIo[12];
	CStaticCS	m_stcMainIdxJigNo[12];
	CButtonCS	m_btnMainIdxRemove[11];
	CButtonCS	m_btnFormingX1[2];
	CButtonCS	m_btnFormingX2[3];
	CButtonCS	m_btnFormingZ1[3];
	CButtonCS	m_btnFormingZ2[2];
	CButtonCS	m_btnVisionTop1Z[1];
	CButtonCS	m_btnVisionAngle1Z[1];
	CButtonCS	m_btnVisionAngle2Z[1];
	CButtonCS	m_btnVisionSide1Z[1];
	CButtonCS	m_btnVisionSide2Z[1];
	CButtonCS	m_btnVisionTop2Z[1];
	CButtonCS	m_btnVisionAngle3Z[1];
	CButtonCS	m_btnVisionWi3DZ[1];
	CButtonCS	m_btnVisionSide3Z[1];
	CButtonCS	m_btnVisionSide4Z[1];
	CButtonCS	m_btnAngle12TurnA[2];
	CButtonCS	m_btnAngle12StopZ[2];
	CButtonCS	m_btnSide12TurnA[2];
	CButtonCS	m_btnSide12StopZ[2];
	CButtonCS	m_btnA3WiTurnA[2];
	CButtonCS	m_btnA3WiStopZ[2];
	CButtonCS	m_btnSide34TurnA[2];
	CButtonCS	m_btnSide34StifZ[2];
	CButtonCS	m_btnVisionAllZ;
	CLedCS		m_ledMainIdxIonIo;
	CButtonCS	m_btnMainIdxIonIo[4];
	CButtonCS	m_btnIndexPartIo[10];
	CLedCS		m_ledIndexPartIo[5];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBtnMainIndexRClick(UINT nID);
	afx_msg void OnBtnMainIdxVacIoClick(UINT nID);
	afx_msg void OnBtnMainIdxRemoveClick(UINT nID);
	afx_msg void OnBtnFormingX1Click(UINT nID);
	afx_msg void OnBtnFormingX2Click(UINT nID);
	afx_msg void OnBtnFormingZ1Click(UINT nID);
	afx_msg void OnBtnFormingZ2Click(UINT nID);
	afx_msg void OnBtnVisionTop1ZClick(UINT nID);
	afx_msg void OnBtnVisionAngle1ZClick(UINT nID);
	afx_msg void OnBtnVisionAngle2ZClick(UINT nID);
	afx_msg void OnBtnVisionSide1ZClick(UINT nID);
	afx_msg void OnBtnVisionSide2ZClick(UINT nID);
	afx_msg void OnBtnVisionTop2ZClick(UINT nID);
	afx_msg void OnBtnVisionAngle3ZClick(UINT nID);
	afx_msg void OnBtnVisionWi3DZClick(UINT nID);
	afx_msg void OnBtnVisionSide3ZClick(UINT nID);
	afx_msg void OnBtnVisionSide4ZClick(UINT nID);
	afx_msg void OnBtnAngle12TurnAClick(UINT nID);
	afx_msg void OnBtnAngle12StopZClick(UINT nID);
	afx_msg void OnBtnSide12TurnAClick(UINT nID);
	afx_msg void OnBtnSide12StopZClick(UINT nID);
	afx_msg void OnBtnA3WiTurnAClick(UINT nID);
	afx_msg void OnBtnA3WiStopZClick(UINT nID);
	afx_msg void OnBtnSide34TurnAClick(UINT nID);
	afx_msg void OnBtnSide34StifZClick(UINT nID);
	afx_msg void OnBnClickedBtnVisionAllZ();
	afx_msg void OnBtnMainIdxIonIoClick(UINT nID);
	afx_msg void OnBtnIndexPartIoClick(UINT nID);

private:
	CString m_strLog;
	void Initial_Controls();

public:
	void Display_Status();
};
