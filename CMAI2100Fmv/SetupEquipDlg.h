// SetupEquipDlg.h : 헤더 파일
//
#pragma once

// CSetupEquipDlg 대화 상자입니다.

class CSetupEquipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetupEquipDlg)

public:
	CSetupEquipDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSetupEquipDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_SETUP_EQUIP_DLG };
	CGroupCS	m_Group[7];
	CLabelCS	m_Label[37];
	CStaticCS	m_stcEquipName;
	CStaticCS	m_stcEquipModel;
	CComboCS	m_cboModelChange;
	CComboCS	m_cboLotBarcodePort;
	CLabelCS	m_lblDoorLock;
	CRadioCS	m_rdoDoorLock[2];
	CLabelCS	m_lblTaktLog;
	CRadioCS	m_rdoTaktLog[2];
	CRadioCS	m_rdoLightCur[2];
	CRadioCS	m_rdoCosmeticNG[2];
	CLabelCS	m_lblPickup;
	CCheckCS	m_chkDryRun;
	CCheckCS	m_chkUseInspectBtm;
	CCheckCS	m_chkUseInspectTop1;
	CCheckCS	m_chkUseInspectTop2;
	CCheckCS	m_chkUseInspectAl1;
	CCheckCS	m_chkUseInspectAl2;
	CCheckCS	m_chkUseInspectRos;
	CCheckCS	m_chkUseInspectBtmAngle;
	CCheckCS	m_chkUseInspectTop1Angle;
	CCheckCS	m_chkUseCMCheck;
	CCheckCS	m_chkUseNGSort;
	CCheckCS	m_chkUseNGSize;
	CCheckCS	m_chkUseGoodSort;
	CCheckCS	m_chkUseEleAlign;
	CCheckCS	m_chkUseAirBlow;
	CCheckCS	m_chkUsePassGood;
	CStaticCS	m_stcCmTrayData[5];
	CStaticCS	m_stcTimeOver[5];
	CStaticCS	m_stcNGCodeMC[5];
	CStaticCS	m_stcDropTableData[4];
	CStaticCS	m_stcPitchData[6];
	CStaticCS	m_stcDelayTime[10];
	CGroupCS	m_grpTower;
	CLabelCS	m_lblTower[13];
	CCheckCS	m_chkTower[6][7];
	CGroupCS	m_grpBuzzer;
	CLabelCS	m_lblBuzzer[7];
	CCheckCS	m_chkBuzzer[2][5];
	CGroupCS	m_grpHidden;
	CLabelCS	m_lblPasswordMt;
	CStaticCS	m_stcPasswordMt;
	CLabelCS	m_lblPasswordSi;
	CEditCS		m_edtPasswordSi;
	CLabelCS	m_lblDryRunTest;
	CEditCS		m_edtDryRunTest;
	CButtonCS	m_btnVisionTimeUpdate;
	CLabelCS	m_lblLanguage;
	CRadioCS	m_rdoLanguage[2];
	CLabelCS	m_lblMESUse;
	CRadioCS	m_rdoMESUse[2];
	CLabelCS	m_lblMESUse2;
	CRadioCS	m_rdoMESUse2[2];
	CStaticCS	m_stcNoWorkTime;
	CCheckCS	m_chkUseAuotSkip;
	CListCS		m_lstMdjIp;
	CButtonCS	m_btnMdjDelete;
	CButtonCS	m_btnMdjRefresh;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnStnClickedStcEquipName();
	afx_msg void OnStcCmTrayDataClick(UINT nID);
	afx_msg void OnStcCapTrayDataClick(UINT nID);
	afx_msg void OnStcShipTrayDataClick(UINT nID);
	afx_msg void OnStcPitchDataClick(UINT nID);
	afx_msg void OnStcDelayTimeClick(UINT nID);

	afx_msg void OnStnClickedStcShowHidden();
	afx_msg void OnStnClickedStcPasswordMt();
	afx_msg void OnBnClickedBtnVisionTimeUpdate();
	afx_msg void OnStnClickedStcNoworkTime();

	afx_msg void OnBnClickedBtnMdjDelete();
	afx_msg void OnBnClickedBtnMdjRefresh();

private:
	CString m_strLog;
	void Initial_Controls();
	void Display_EquipData();

public:
	void InitModelComboBox();
	void Save_EquipData();
	void Save_ModelEquipData(CString sPath);
	void Cancel_EquipData();
	void Save_MESData(BOOL bUse, BOOL bChange);
	void Set_MESData(CString sPath, BOOL bUse, BOOL bChange);
	afx_msg void OnStnClickedStcEquipModel();
	afx_msg void OnBnClickedButtonModelAdd();
	afx_msg void OnCbnDropdownCboModelChange();
	afx_msg void OnCbnSelchangeCboModelChange();
};

///////////////////////////////////////////////////////////////////////////////
