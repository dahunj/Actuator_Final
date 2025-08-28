// CMAI2100Dlg.h : 헤더 파일
//
#pragma once

#define	MODE_OPERATOR		0
#define MODE_INITIAL		1
#define MODE_WORK			2
#define MODE_MANUAL			3
#define MODE_SETUP			4
#define MODE_PROHIBIT		5

#define TIMER_DATE_TIME		0
#define TIMER_TOWER_FLKR	1
#define TIMER_SLIDE_CHECK	2
#define TIMER_DOOR_LOCK		3

#define STATE_NONE			0
#define STATE_INITEND		1
#define STATE_RUN			2
#define STATE_LOTEND		3
#define STATE_ALARM			4
#define STATE_EMER			5

#define EXIT_SYSTEM_NONE	0
#define EXIT_SYSTEM_AJIN	1
#define EXIT_SYSTEM_BARCODE	2

#define YEAR	0
#define MONTH	1
#define DAY		1

// CCMAI2100Dlg 대화 상자
class CCMAI2100Dlg : public CDialogEx
{
// 생성입니다.
public:
	CCMAI2100Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CMAI2100_DIALOG };
	CPictureCS	m_imgLgLogo;
	CPictureCS	m_picMainLogo;
	CStaticCS	m_stcMainEquip;
	CStaticCS	m_stcMainMode;
	CStaticCS	m_stcMainOpEng;
	CStaticCS	m_stcMainDate;
	CStaticCS	m_stcMainTime;
	CStaticCS	m_stcMainVer;
	CStaticCS	m_stcMainTower[3];
	CPictureCS	m_picModeBack;
	CButtonCS	m_btnMainOperator;
	CRadioCS	m_rdoMainInitial;
	CRadioCS	m_rdoMainWork;
	CRadioCS	m_rdoMainManual;
	CRadioCS	m_rdoMainSetup;
	CRadioCS	m_rdoMainProhibit;
	CButtonCS	m_btnMainMonitor;
	CButtonCS	m_btnMainExit;
	CStaticCS	m_stcDoorLock;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnMainOperator();
	afx_msg void OnBnClickedRdoMainInitial();
	afx_msg void OnBnClickedRdoMainWork();
	afx_msg void OnBnClickedRdoMainManual();
	afx_msg void OnBnClickedRdoMainSetup();
	afx_msg void OnBnClickedRdoMainProhibit();
	afx_msg void OnBnClickedBtnMainMonitor();
	afx_msg void OnBnClickedBtnMainExit();
	afx_msg void OnStnClickedImgLgLogo();
private:
	CBitmap	m_bmpLgLogo;

	int m_nMainMode;
	int m_nMainState;

	BOOL m_bTowerOn;
	BOOL m_bBuzzerOn;

	DWORD	m_dwEquipRunStart;

	BOOL	m_bNoWorkPopup;
	DWORD	m_dwNoWorkTime;

private:
	void Initial_Controls();
	void Hide_ModeWindows(int nMode);

public:
	void Set_CurrentMode(int nMode);
	void Check_PMScreen(int nMode);

	void Set_MainState(int nState);
	int  Get_MainState() { return m_nMainState; }

	void Set_TowerFlicker(BOOL bEnable);
	void Enable_ModeButton(BOOL bEnable);

	void Set_NoWork();					// 비가동 집계 팝업
	void Set_NoWorkTimer(DWORD dwTimer) {m_dwNoWorkTime = dwTimer;}		// Nowork Timer

	void Display_EquipName();
	void Display_DateTime();
	void Exit_System(int nExitNo);

	void Set_EquipRunStart();
	void Save_EquipRunTime();
	void Clear_EquipRunTime();
	void Clear_JobData();
	void LogAllDelete();
	void LogFileDelete(CString sPath);
	void Capture_Screen();
	void Check_SlideOpen();
	void Set_DoorLock();

	void StdLogAllDelete();
	void StdLogDelete(CString strDir, int nDelData, BOOL bType);
	BOOL RemoveDir(CString strDir, BOOL bOnlyFile);
	int GetDirFilesNum(CString strDir);
};


///////////////////////////////////////////////////////////////////////////////
