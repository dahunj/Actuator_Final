// SetupEquipDlg.cpp : ±¸Çö ÆÄÀÏÀÔ´Ï´Ù.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupEquipDlg.h"
#include "afxdialogex.h"
#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"
#include "SetupDlg.h"
#include "Inspector.h"
#include "SequenceMain.h"
#include "SequenceInit.h"
#include "CMAI2100Dlg.h"
#include "MesAgent.h"
#include "Dispatcher.h"

// CSetupEquipDlg ´ëÈ­ »óÀÚÀÔ´Ï´Ù.

IMPLEMENT_DYNAMIC(CSetupEquipDlg, CDialogEx)

CSetupEquipDlg::CSetupEquipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupEquipDlg::IDD, pParent)
{
}

CSetupEquipDlg::~CSetupEquipDlg()
{
}

void CSetupEquipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 37; i++) DDX_Control(pDX, IDC_LABEL_0 + i,  m_Label[i]);
	DDX_Control(pDX, IDC_STC_EQUIP_NAME, m_stcEquipName);
	DDX_Control(pDX, IDC_STC_EQUIP_MODEL, m_stcEquipModel);
	DDX_Control(pDX, IDC_CBO_MODEL_CHANGE, m_cboModelChange);
	DDX_Control(pDX, IDC_CBO_LOT_BARCODE_PORT, m_cboLotBarcodePort);
	DDX_Control(pDX, IDC_LBL_DOOR_LOCK,  m_lblDoorLock);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_DOOR_LOCK_0 + i, m_rdoDoorLock[i]);
	DDX_Control(pDX, IDC_LBL_TAKT_LOG,  m_lblTaktLog);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_TAKT_LOG_0 + i, m_rdoTaktLog[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_LIGHT_CUR_0 + i, m_rdoLightCur[i]);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_COSMETIC_0 + i, m_rdoCosmeticNG[i]);
	DDX_Control(pDX, IDC_LBL_PICKUP,  m_lblPickup);
	DDX_Control(pDX, IDC_CHK_DRY_RUN, m_chkDryRun);
	DDX_Control(pDX, IDC_STC_NOWORK_TIME, m_stcNoWorkTime);

	DDX_Control(pDX, IDC_CHK_USE_BTM, m_chkUseInspectBtm);
	DDX_Control(pDX, IDC_CHK_USE_TOP1, m_chkUseInspectTop1);
	DDX_Control(pDX, IDC_CHK_USE_TOP2, m_chkUseInspectTop2);
	DDX_Control(pDX, IDC_CHK_USE_ALIGN1, m_chkUseInspectAl1);
	DDX_Control(pDX, IDC_CHK_USE_ALIGN2, m_chkUseInspectAl2);
	DDX_Control(pDX, IDC_CHK_USE_ROS, m_chkUseInspectRos);
	DDX_Control(pDX, IDC_CHK_USE_BTM_ANGLE, m_chkUseInspectBtmAngle);
	DDX_Control(pDX, IDC_CHK_USE_TOP1_ANGLE, m_chkUseInspectTop1Angle);
	DDX_Control(pDX, IDC_CHK_USE_CM_CHECK, m_chkUseCMCheck);
	DDX_Control(pDX, IDC_CHK_USE_TRAY_SORT, m_chkUseNGSort);
	DDX_Control(pDX, IDC_CHK_USE_NG_SIZE,   m_chkUseNGSize);
	DDX_Control(pDX, IDC_CHK_USE_GOOD_SORT, m_chkUseGoodSort);
	DDX_Control(pDX, IDC_CHK_USE_ELEVATOR_ALIGN,	m_chkUseEleAlign);
	DDX_Control(pDX, IDC_CHK_USE_INSPECT_BLOW,		m_chkUseAirBlow);
	DDX_Control(pDX, IDC_CHK_USE_INSPECT_ALARM,		m_chkUseAuotSkip);
	DDX_Control(pDX, IDC_CHK_USE_PASS_GOOD,			m_chkUsePassGood);

	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_CM_TRAY_DATA_0 + i, m_stcCmTrayData[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_CAP_TRAY_DATA_0 + i, m_stcTimeOver[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_SHIP_TRAY_DATA_0 + i, m_stcNGCodeMC[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_PITCH_DATA_0 + i, m_stcPitchData[i]);
	for (int i = 0; i <10; i++) DDX_Control(pDX, IDC_STC_DELAY_TIME_0 + i, m_stcDelayTime[i]);

	DDX_Control(pDX, IDC_GRP_TOWER, m_grpTower);
	for (int i = 0; i < 13; i++) DDX_Control(pDX, IDC_LBL_TOWER_0 + i,  m_lblTower[i]);
	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) DDX_Control(pDX, IDC_CHK_TOWER_0_0 + i * 7 + j,  m_chkTower[i][j]);
	DDX_Control(pDX, IDC_GRP_BUZZER, m_grpBuzzer);
	for (int i = 0; i < 7; i++) DDX_Control(pDX, IDC_LBL_BUZZER_0 + i,  m_lblBuzzer[i]);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 5; j++) DDX_Control(pDX, IDC_CHK_BUZZER_0_0 + i * 5 + j,  m_chkBuzzer[i][j]);
	DDX_Control(pDX, IDC_GRP_HIDDEN, m_grpHidden);
	DDX_Control(pDX, IDC_LBL_PASSWORD_MT, m_lblPasswordMt);
	DDX_Control(pDX, IDC_STC_PASSWORD_MT, m_stcPasswordMt);
	DDX_Control(pDX, IDC_LBL_PASSWORD_SI, m_lblPasswordSi);
	DDX_Control(pDX, IDC_EDT_PASSWORD_SI, m_edtPasswordSi);

	DDX_Control(pDX, IDC_LBL_DRY_RUN_TEST_0, m_lblDryRunTest);
	DDX_Control(pDX, IDC_EDT_DRY_RUN_TEST_0, m_edtDryRunTest);
	DDX_Control(pDX, IDC_BTN_VISION_TIME_UPDATE, m_btnVisionTimeUpdate);

	DDX_Control(pDX, IDC_LBL_LANGUAGE,  m_lblLanguage);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_LANG_KOR + i, m_rdoLanguage[i]);
	DDX_Control(pDX, IDC_LBL_MESUSE,  m_lblMESUse);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_MES_NOT + i, m_rdoMESUse[i]);
	DDX_Control(pDX, IDC_LBL_MESUSE2,  m_lblMESUse2);
	for (int i = 0; i < 2; i++) DDX_Control(pDX, IDC_RDO_MES_NOT2 + i, m_rdoMESUse2[i]);

	DDX_Control(pDX, IDC_LST_MDJ_IP, m_lstMdjIp);
	DDX_Control(pDX, IDC_BTN_MDJ_DELETE, m_btnMdjDelete);
	DDX_Control(pDX, IDC_BTN_MDJ_REFRESH, m_btnMdjRefresh);
}

BEGIN_MESSAGE_MAP(CSetupEquipDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_STN_CLICKED(IDC_STC_EQUIP_NAME, &CSetupEquipDlg::OnStnClickedStcEquipName)
	ON_STN_CLICKED(IDC_STC_NOWORK_TIME, &CSetupEquipDlg::OnStnClickedStcNoworkTime)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_CM_TRAY_DATA_0, IDC_STC_CM_TRAY_DATA_4, OnStcCmTrayDataClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_CAP_TRAY_DATA_0, IDC_STC_CAP_TRAY_DATA_3, OnStcCapTrayDataClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIP_TRAY_DATA_0, IDC_STC_SHIP_TRAY_DATA_4, OnStcShipTrayDataClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_PITCH_DATA_0, IDC_STC_PITCH_DATA_5, OnStcPitchDataClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_DELAY_TIME_0, IDC_STC_DELAY_TIME_9, OnStcDelayTimeClick)

	ON_STN_CLICKED(IDC_STC_SHOW_HIDDEN, &CSetupEquipDlg::OnStnClickedStcShowHidden)
	ON_STN_CLICKED(IDC_STC_PASSWORD_MT, &CSetupEquipDlg::OnStnClickedStcPasswordMt)
	ON_BN_CLICKED(IDC_BTN_VISION_TIME_UPDATE, &CSetupEquipDlg::OnBnClickedBtnVisionTimeUpdate)
	ON_STN_CLICKED(IDC_STC_EQUIP_MODEL, &CSetupEquipDlg::OnStnClickedStcEquipModel)
	ON_BN_CLICKED(IDC_BUTTON_MODEL_ADD, &CSetupEquipDlg::OnBnClickedButtonModelAdd)
	ON_CBN_DROPDOWN(IDC_CBO_MODEL_CHANGE, &CSetupEquipDlg::OnCbnDropdownCboModelChange)
	ON_CBN_SELCHANGE(IDC_CBO_MODEL_CHANGE, &CSetupEquipDlg::OnCbnSelchangeCboModelChange)

	ON_BN_CLICKED(IDC_BTN_MDJ_DELETE, &CSetupEquipDlg::OnBnClickedBtnMdjDelete)
	ON_BN_CLICKED(IDC_BTN_MDJ_REFRESH, &CSetupEquipDlg::OnBnClickedBtnMdjRefresh)
END_MESSAGE_MAP()

// CSetupEquipDlg ¸Þ½ÃÁö Ã³¸®±âÀÔ´Ï´Ù.

BOOL CSetupEquipDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  ¿©±â¿¡ Ãß°¡ ÃÊ±âÈ­ ÀÛ¾÷À» Ãß°¡ÇÕ´Ï´Ù.
	SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ¿¹¿Ü: OCX ¼Ó¼º ÆäÀÌÁö´Â FALSE¸¦ ¹ÝÈ¯ÇØ¾ß ÇÕ´Ï´Ù.
}

BOOL CSetupEquipDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupEquipDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	if (gData.nLanguage == 0) {
//		m_lblPickup.SetWindowText(" ÇÈ¾÷ ½ÃÀÛ À§Ä¡");
		m_lblLanguage.SetWindowText(" »ç¿ë ¾ð¾î");
		m_rdoLanguage[0].SetWindowText("ÇÑ±¹¾î");	m_rdoLanguage[1].SetWindowText("¿µ¾î");
		m_lblMESUse.SetWindowText("MES »ç¿ë");
		m_rdoMESUse[0].SetWindowText("¹Ì»ç¿ë");		m_rdoMESUse[1].SetWindowText("»ç¿ë");
		m_lblMESUse2.SetWindowText("MES Model º¯°æ Check");
		m_rdoMESUse2[0].SetWindowText("¹Ì»ç¿ë");		m_rdoMESUse2[1].SetWindowText("»ç¿ë");
	} else {
//		m_lblPickup.SetWindowText(" Cosmetic NG");
		m_lblLanguage.SetWindowText(" Language");
		m_rdoLanguage[0].SetWindowText("Korean");	m_rdoLanguage[1].SetWindowText("English");
		m_lblMESUse.SetWindowText("MES Use");
		m_rdoMESUse[0].SetWindowText("Not Use");		m_rdoMESUse[1].SetWindowText("Use");
		m_lblMESUse2.SetWindowText("MES Model Change Check");
		m_rdoMESUse2[0].SetWindowText("Not Use");		m_rdoMESUse2[1].SetWindowText("Use");
	}

	Display_EquipData();

	m_grpHidden.ShowWindow(SW_HIDE);
	m_lblPasswordMt.ShowWindow(SW_HIDE);
	m_stcPasswordMt.ShowWindow(SW_HIDE);
	m_lblPasswordSi.ShowWindow(SW_HIDE);
	m_edtPasswordSi.ShowWindow(SW_HIDE);
/*
	if (gData.bUseDryRun) {
		for (int i = 0; i < 2; i++) m_lblDryRunTest[i].ShowWindow(SW_SHOW);
		for (int i = 0; i < 2; i++) m_edtDryRunTest[i].ShowWindow(SW_SHOW);
	} else {
		for (int i = 0; i < 2; i++) m_lblDryRunTest[i].ShowWindow(SW_HIDE);
		for (int i = 0; i < 2; i++) m_edtDryRunTest[i].ShowWindow(SW_HIDE);
	}
*/
	m_strLog.Format("[Setup Equip] Show Window");
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupEquipDlg::OnStnClickedStcEquipName()
{
	CString strKey;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;

	m_stcEquipName.SetWindowText(strKey);

	m_strLog.Format("[Setup Equip] OnStnClickedStcEquipName - Data(%s)", strKey);
	g_objLogFile.Save_HandlerLog(m_strLog);
}


void CSetupEquipDlg::OnStcCmTrayDataClick(UINT nID)
{
	int ID = nID - IDC_STC_CM_TRAY_DATA_0;

	CString strOld, strNew;
	m_stcCmTrayData[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcCmTrayData[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Equip] OnStcCmTrayDataClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupEquipDlg::OnStcCapTrayDataClick(UINT nID)
{
	int ID = nID - IDC_STC_CAP_TRAY_DATA_0;

	CString strOld, strNew;
	m_stcTimeOver[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcTimeOver[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Equip] OnStcCapTrayDataClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupEquipDlg::OnStcShipTrayDataClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIP_TRAY_DATA_0;

	CString strOld, strNew;
	m_stcNGCodeMC[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcNGCodeMC[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Equip] OnStcShipTrayDataClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupEquipDlg::OnStcPitchDataClick(UINT nID)
{
	int ID = nID - IDC_STC_PITCH_DATA_0;

	CString strOld, strNew;
	m_stcPitchData[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;
	if (ID == 3) {
		if (strNew != "0" && strNew != "0.1") {
			AfxMessageBox("Motion Check °ªÀº 0 or 0.1¸¸ ÀÔ·ÂÀÌ °¡´ÉÇÕ´Ï´Ù...");
			return;
		}
	}
	m_stcPitchData[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Equip] OnStcPitchDataClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupEquipDlg::OnStcDelayTimeClick(UINT nID)
{
	int ID = nID - IDC_STC_DELAY_TIME_0;

	CString strOld, strNew;
	m_stcDelayTime[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcDelayTime[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup Equip] OnStcDelayTimeClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupEquipDlg::OnStnClickedStcPasswordMt()
{
	CString strTemp, strData;

	if (g_objCommon.Show_NumPad("", strData) != IDOK) return;

	int nLen = strData.GetLength();
	if (nLen < 1) return;

	for (int i = 0; i < nLen; i++ ) {
		strTemp = strData.Mid(i, 1);
		if (strTemp < "0" || strTemp > "9") {
			AfxMessageBox("Password Input Error......");
			return;
		}
	}
	m_stcPasswordMt.SetWindowText(strData);
}

void CSetupEquipDlg::OnStnClickedStcShowHidden()
{
	if (m_grpHidden.IsWindowVisible()) {
		m_grpHidden.ShowWindow(SW_HIDE);
		m_lblPasswordMt.ShowWindow(SW_HIDE);
		m_stcPasswordMt.ShowWindow(SW_HIDE);

		if (g_dlgSetup.Get_LoginUser() != 2) return;

		m_lblPasswordSi.ShowWindow(SW_HIDE);
		m_edtPasswordSi.ShowWindow(SW_HIDE);

	} else {
		m_grpHidden.ShowWindow(SW_SHOW);
		m_lblPasswordMt.ShowWindow(SW_SHOW);
		m_stcPasswordMt.ShowWindow(SW_SHOW);

		if (g_dlgSetup.Get_LoginUser() != 2) return;

		m_lblPasswordSi.ShowWindow(SW_SHOW);
		m_edtPasswordSi.ShowWindow(SW_SHOW);
	}
}

void CSetupEquipDlg::OnBnClickedBtnVisionTimeUpdate()
{
	g_objInspector.Set_TimeUpdate(INSPECTOR_ALL);
}

void CSetupEquipDlg::OnStnClickedStcNoworkTime()
{
	CString strOld, strNew;
	m_stcNoWorkTime.GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcNoWorkTime.SetWindowText(strNew);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupEquipDlg::Initial_Controls() 
{
	CString strText;

	for (int i = 0; i < 8; i++) m_Group[i].Init_Ctrl("¹ÙÅÁ", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_Label[0].Init_Ctrl("¹ÙÅÁ", 13, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));								// Equip Name
	m_Label[28].Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));								// Model Name
	m_Label[29].Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x10, 0xC0));								// Model Change
	m_Label[1].Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xE0, 0x00));								// Barcode Port
	m_Label[2].Init_Ctrl("Arial", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xD0, 0xF0));								// Out Tray
	for (int i = 3; i < 7; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x20, 0x50, 0x00));	// CM Tray
	for (int i = 7; i < 12; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x20, 0x20));	// Cap Tray
	for (int i = 11; i < 15; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x40, 0x80));	// Ship Tray
	for (int i = 15; i < 19; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x00));	// Drop Table
	for (int i = 19; i < 22; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xC0, 0x80));	// Vacuum Off Delay
	for (int i = 22; i < 24; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 10, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x80, 0x80));	// Vacuum Off Delay
	for (int i = 24; i < 28; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x80)); // Pitch
	for (int i = 15; i < 19; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x80)); // Delay
	m_Label[23].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x80)); // Delay
	m_Label[27].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x80)); // Delay
	for (int i = 30; i < 36; i++) m_Label[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x80, 0x00, 0x80)); // Delay
	m_Label[36].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x20, 0x20));	// MDJ List

	m_stcEquipName.Init_Ctrl("¹ÙÅÁ", 15, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xE0, 0xFF, 0xE0));
	m_stcEquipModel.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xE0, 0xFF, 0xE0));
	m_cboModelChange.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xE0, 0x00));
	for (int i = 0; i < 4; i++) { strText.Format("COM%d", i + 1); m_cboLotBarcodePort.AddString(strText); }
	m_cboLotBarcodePort.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xFF, 0xE0, 0x00));
	m_lblDoorLock.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 2; i++) m_rdoDoorLock[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);
	m_lblTaktLog.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 2; i++) m_rdoTaktLog[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);
	m_Label[10].Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 2; i++) m_rdoLightCur[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);
	for (int i = 0; i < 2; i++) m_rdoCosmeticNG[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);
	m_chkDryRun.Init_Ctrl("¹ÙÅÁ", 12, TRUE, RGB(0xFF, 0x00, 0x00), RGB(0xFF, 0xFF, 0x00), CCheckCS::emRed, 0);
	m_lblPickup.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	m_chkUseInspectBtm.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseInspectTop1.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseInspectTop2.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseInspectAl1.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x90, 0x90, 0xF0), CCheckCS::emRed, 0);
	m_chkUseInspectAl2.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x90, 0x90, 0xF0), CCheckCS::emRed, 0);
	m_chkUseInspectRos.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x40, 0xF0, 0xFF), CCheckCS::emRed, 0);
	m_chkUseInspectBtmAngle.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseInspectTop1Angle.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseCMCheck.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseNGSort.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseNGSize.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseGoodSort.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);
	m_chkUseEleAlign.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x90, 0x90, 0xF0), CCheckCS::emRed, 0);
	m_chkUseAirBlow.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x90, 0x90, 0xF0), CCheckCS::emRed, 0);
	m_chkUseAuotSkip.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x90, 0x90, 0xF0), CCheckCS::emRed, 0);
	m_chkUsePassGood.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x00), RGB(0x60, 0xF0, 0x80), CCheckCS::emRed, 0);

	for (int i = 0; i < 5; i++) m_stcCmTrayData[i].Init_Ctrl("¹ÙÅÁ", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 4; i++) m_stcTimeOver[i].Init_Ctrl("¹ÙÅÁ", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 5; i++) m_stcNGCodeMC[i].Init_Ctrl("¹ÙÅÁ", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i < 6; i++) m_stcPitchData[i].Init_Ctrl("¹ÙÅÁ", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	for (int i = 0; i <10; i++) m_stcDelayTime[i].Init_Ctrl("¹ÙÅÁ", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xFF, 0xE0));
	m_stcNoWorkTime.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0x00, 0x00, 0x80), RGB(0xFF, 0xFF, 0xE0));

	m_grpTower.Init_Ctrl("¹ÙÅÁ", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 13; i++) m_lblTower[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) m_chkTower[i][j].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0x00, 0xF0, 0x00), CCheckCS::emRed, 0);

	m_grpBuzzer.Init_Ctrl("¹ÙÅÁ", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 7; i++) m_lblBuzzer[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x40, 0x40, 0x40));
	for (int i = 0; i < 2; i++) for (int j = 0; j < 5; j++) m_chkBuzzer[i][j].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0x00, 0xE0, 0xF0), CCheckCS::emRed, 0);

	m_grpHidden.Init_Ctrl("¹ÙÅÁ", 10, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_lblPasswordMt.Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_stcPasswordMt.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0xC0, 0xC0, 0xC0));
	m_lblPasswordSi.Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_edtPasswordSi.Init_Ctrl("¹ÙÅÁ", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_lblDryRunTest.Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	m_edtDryRunTest.Init_Ctrl("¹ÙÅÁ", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_btnVisionTimeUpdate.Init_Ctrl("¹ÙÅÁ", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	
	m_lblLanguage.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 2; i++) m_rdoLanguage[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);
	m_lblMESUse.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 2; i++) m_rdoMESUse[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);
	m_lblMESUse2.Init_Ctrl("¹ÙÅÁ", 11, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 2; i++) m_rdoMESUse2[i].Init_Ctrl("¹ÙÅÁ", 11, FALSE, RGB(0x00, 0x00, 0x00), RGB(0xC0, 0xC0, 0xC0), CRadioCS::emRed, 0);

	m_lstMdjIp.Init_Ctrl("¹ÙÅÁ", 11, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	m_btnMdjDelete.Init_Ctrl("¹ÙÅÁ", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
	m_btnMdjRefresh.Init_Ctrl("¹ÙÅÁ", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, 0, 0);
}

void CSetupEquipDlg::Display_EquipData()
{
	CString strData;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	m_stcEquipName.SetWindowText(pEquipData->sEquipName);
	m_stcEquipModel.SetWindowText(pEquipData->sModelName);

	m_cboLotBarcodePort.SetCurSel(pEquipData->nLotBarcodePort - 1);
	if (pEquipData->bUseDoorLock) m_rdoDoorLock[1].SetCheck(TRUE);
	else m_rdoDoorLock[0].SetCheck(TRUE);
//	if (pEquipData->bUseTaktLog) m_rdoTaktLog[1].SetCheck(TRUE);
//	else m_rdoTaktLog[0].SetCheck(TRUE);
	if (gData.bMemphis) m_rdoTaktLog[1].SetCheck(TRUE);
	else				m_rdoTaktLog[0].SetCheck(TRUE);
	if (pEquipData->bUseLightCurtain) m_rdoLightCur[1].SetCheck(TRUE);
	else m_rdoLightCur[0].SetCheck(TRUE);
	if (pEquipData->bUseCosmeticNG) m_rdoCosmeticNG[1].SetCheck(TRUE);
	else m_rdoCosmeticNG[0].SetCheck(TRUE);
	m_chkDryRun.SetCheck(gData.bUseDryRun);
	strData.Format("%d", pEquipData->nNoWorkTime); m_stcNoWorkTime.SetWindowText(strData);

	m_chkUseInspectBtm.SetCheck(pEquipData->bUseBottom);
	m_chkUseInspectTop1.SetCheck(pEquipData->bUseTop1);
	m_chkUseInspectTop2.SetCheck(pEquipData->bUseTop2);
	m_chkUseInspectAl1.SetCheck(pEquipData->bUseAlign1);
	m_chkUseInspectAl2.SetCheck(pEquipData->bUseAlign2);
	m_chkUseInspectRos.SetCheck(pEquipData->bUseROS);
	m_chkUseInspectBtmAngle.SetCheck(pEquipData->bUseBotAng);
	m_chkUseInspectTop1Angle.SetCheck(pEquipData->bUseTopAng);
	m_chkUseCMCheck.SetCheck(pEquipData->bUseCMCheck);
	m_chkUseNGSort.SetCheck(pEquipData->bUseNGSort);
	m_chkUseNGSize.SetCheck(pEquipData->bUseNGSize);
	m_chkUseGoodSort.SetCheck(pEquipData->bUseGoodSort);
	m_chkUseEleAlign.SetCheck(pEquipData->bElevatorAlign);
	m_chkUseAirBlow.SetCheck(pEquipData->bUseInspectBlow);
	m_chkUsePassGood.SetCheck(pEquipData->bUsePassGood);

	if (pEquipData->bUseMES) m_rdoMESUse[1].SetCheck(TRUE);
	else m_rdoMESUse[0].SetCheck(TRUE);
	if (pEquipData->bUseMESRcpCheck) m_rdoMESUse2[1].SetCheck(TRUE);
	else m_rdoMESUse2[0].SetCheck(TRUE);

	strData.Format("%d",     pEquipData->nTrayCountX); m_stcCmTrayData[0].SetWindowText(strData);
	strData.Format("%d",     pEquipData->nTrayCountY); m_stcCmTrayData[1].SetWindowText(strData);
	strData.Format("%0.2lf", pEquipData->dTrayPitchX); m_stcCmTrayData[2].SetWindowText(strData);
	strData.Format("%0.2lf", pEquipData->dTrayPitchY); m_stcCmTrayData[3].SetWindowText(strData);
	strData.Format("%0.2lf", pEquipData->dTrayPitchYm); m_stcCmTrayData[4].SetWindowText(strData);

	strData.Format("%d",	 gData.nRejectMaxCount); m_stcPitchData[2].SetWindowText(strData);
	strData.Format("%0.3lf", gAlm.dMotionChkPos);	 m_stcPitchData[3].SetWindowText(strData);
	strData.Format("%d",	 gData.nDoorLockTime);	 m_stcPitchData[4].SetWindowText(strData);

	strData.Format("%0.2lf", pEquipData->dPitchBtm[0]); m_stcPitchData[0].SetWindowText(strData);
	strData.Format("%0.2lf", pEquipData->dPitchTop[0]); m_stcPitchData[1].SetWindowText(strData);
	strData.Format("%0.2lf", pEquipData->dPitchBtm[1]); m_stcTimeOver[2].SetWindowText(strData);
	strData.Format("%0.2lf", pEquipData->dPitchTop[1]); m_stcTimeOver[3].SetWindowText(strData);

	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) m_chkTower[i][j].SetCheck(pEquipData->bTower[i][j]);
	for (int i = 0; i < 2; i++) for (int j = 0; j < 5; j++) m_chkBuzzer[i][j].SetCheck(pEquipData->bBuzzer[i][j]);

	m_stcPasswordMt.SetWindowText(pEquipData->sPasswordMt);
	m_edtPasswordSi.SetWindowText(pEquipData->sPasswordSi);

	for (int i = 0; i <10; i++) {
		strData.Format("%d", pEquipData->nDelayTime[i]);
		m_stcDelayTime[i].SetWindowText(strData);
	}
	for (int i = 0; i <2; i++) {
		strData.Format("%d", pEquipData->nTimeOver[i]);
		m_stcTimeOver[i].SetWindowText(strData);
	}
	m_chkUseAuotSkip.SetCheck(pEquipData->bUseAutoSkip);
	for (int i = 0; i <5; i++) {
		strData.Format("%d", gData.nNG_MC[i][0]);
		m_stcNGCodeMC[i].SetWindowText(strData);
	}
	strData.Format("%d", gData.nMgnTrayCount);	 m_stcPitchData[5].SetWindowText(strData);
	strData.Format("%d", pEquipData->nDryRunNg); m_edtDryRunTest.SetWindowText(strData);

	OnBnClickedBtnMdjRefresh();	// MDJ List Display
}

void CSetupEquipDlg::Save_EquipData()
{
	CString strKey, strData, strModel;
	int		nData;
	double	dData;

	if (m_rdoMESUse[1].GetCheck()) {
		if (m_chkUseGoodSort.GetCheck()) {
			AfxMessageBox("MES »ç¿ë½Ã Good-Sort ±â´ÉÀº ÇØÁ¦¸¦ ÇØ¾ßÇÕ´Ï´Ù.");
			return;
		}
	}
	m_stcTimeOver[0].GetWindowText(strData); nData = atoi(strData);
	if (nData < 1000) { AfxMessageBox("Inspection Time Over´Â 1000msec ÀÌ»ó ÀÔ·ÂÇØ¾ß ÇÕ´Ï´Ù."); return; }
	m_stcTimeOver[1].GetWindowText(strData); nData = atoi(strData);
	if (nData < 1000) { AfxMessageBox("ROS Time Over´Â 1000msec ÀÌ»ó ÀÔ·ÂÇØ¾ß ÇÕ´Ï´Ù."); return; }
	if (m_chkUsePassGood.GetCheck() && m_rdoMESUse[1].GetCheck()) { AfxMessageBox("Pass 100% Good°ú MES´Â °°ÀÌ »ç¿ëÀ» ÇÒ¼ö¾ø½À´Ï´Ù."); return; }
	m_stcPitchData[5].GetWindowText(strData); nData = atoi(strData);
	if (nData < 1 || nData > 25) { AfxMessageBox("Marginal ÀÚµ¿¿Ï°ø Tray ¼ö·®À» ÀÔ·ÂÇØ¾ß ÇÕ´Ï´Ù.(1~25)"); return; }

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("EquipData.ini File Not Found!");
		return;
	}

	if (m_rdoDoorLock[1].GetCheck()==FALSE) {
		m_stcPitchData[4].GetWindowText(strData); nData = atoi(strData);
		if (nData < 1) {
			AfxMessageBox("Door Lock TimeÀ» ÀÔ·ÂÇØ ÁÖ¼¼¿ä.....");
			return;
		}
		gData.dwDoorStartTime = 0;
		if (pEquipData->bUseDoorLock) {
			gData.dwDoorStartTime = GetTickCount();
		}
	} else {
		gData.dwDoorStartTime = 0;
	}

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "EquipData");

	m_stcEquipName.GetWindowText(strData); INI.Set_String("EQUIPMENT", "NAME", strData);
	m_stcEquipModel.GetWindowText(strModel); INI.Set_String("EQUIPMENT", "MODEL", strModel);

	nData = m_cboLotBarcodePort.GetCurSel(); INI.Set_Integer("EQUIPMENT", "LOT_BARCODE", nData + 1);
	INI.Set_Bool("EQUIPMENT", "DOOR_LOCK", m_rdoDoorLock[1].GetCheck());
	INI.Set_Bool("EQUIPMENT", "TAKT_LOG", TRUE);
	INI.Set_Bool("EQUIPMENT", "MEMPHIS_USE", m_rdoTaktLog[1].GetCheck());
	INI.Set_Bool("EQUIPMENT", "LIGHT_CURTAIN", m_rdoLightCur[1].GetCheck());
	INI.Set_Bool("EQUIPMENT", "COSMETICNG", m_rdoCosmeticNG[1].GetCheck());

	INI.Set_Bool("OPTION", "DRY_RUN_USE", m_chkDryRun.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_BTM", m_chkUseInspectBtm.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_TOP1", m_chkUseInspectTop1.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_TOP2", m_chkUseInspectTop2.GetCheck());
	INI.Set_Bool("OPTION", "ALIGN_1", m_chkUseInspectAl1.GetCheck());
	INI.Set_Bool("OPTION", "ALIGN_2", m_chkUseInspectAl2.GetCheck());
	INI.Set_Bool("OPTION", "ROS_USE", m_chkUseInspectRos.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_BAG", m_chkUseInspectBtmAngle.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_TAG", m_chkUseInspectTop1Angle.GetCheck());
	INI.Set_Bool("OPTION", "CM_CHECK", m_chkUseCMCheck.GetCheck());
	INI.Set_Bool("OPTION", "NG_SORT",  m_chkUseNGSort.GetCheck());
	INI.Set_Bool("OPTION", "NG_SIZE",  m_chkUseNGSize.GetCheck());
	INI.Set_Bool("OPTION", "GOOD_SORT",m_chkUseGoodSort.GetCheck());
	INI.Set_Bool("OPTION", "ELEVATOR_ALIGN",m_chkUseEleAlign.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_BLOW",  m_chkUseAirBlow.GetCheck());
	INI.Set_Bool("OPTION", "PASS_GOOD",  m_chkUsePassGood.GetCheck());

//	if		(m_rdoLanguage[0].GetCheck()) strData = "KOR";
//	else								  strData = "ENG";
//	INI.Set_String("OPTION", "LANGUAGE", strData);
	INI.Set_Bool("OPTION", "MES_USE",	   m_rdoMESUse[1].GetCheck());
	INI.Set_Bool("OPTION", "MES_CNTCHECK", m_rdoMESUse2[1].GetCheck());
//	if ((pEquipData->bUseMES != m_rdoMESUse[1].GetCheck()) || (pEquipData->bUseMESRcpCheck != m_rdoMESUse2[1].GetCheck()))
		Save_MESData(m_rdoMESUse[1].GetCheck(), m_rdoMESUse2[1].GetCheck());

	m_stcPitchData[2].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "REJECT_COUNT", nData);
	m_stcPitchData[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double("OPTION", "MOTION_CHECK", dData, "%0.3lf");
	m_stcPitchData[4].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "DOOR_LOCK_TIME", nData);

	m_stcNGCodeMC[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "NG_MC", nData);
	m_stcNGCodeMC[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "NG_GF", nData);
	m_stcNGCodeMC[2].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "NG_BAC", nData);
	m_stcNGCodeMC[3].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "NG_VIS", nData);
	m_stcNGCodeMC[4].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "NG_MES", nData);

	m_stcPitchData[5].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "MARGINAL_TRAY", nData);
	m_stcNoWorkTime.GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("EQUIPMENT", "NOWORK_TIME", nData);

	m_stcCmTrayData[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TRAY", "COUNT_X", nData);
	m_stcCmTrayData[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TRAY", "COUNT_Y", nData);
	m_stcCmTrayData[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRAY", "PITCH_X", dData, "%0.2lf");
	m_stcCmTrayData[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRAY", "PITCH_Y", dData, "%0.2lf");
	m_stcCmTrayData[4].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRAY", "PITCH_YMEM", dData, "%0.2lf");

	m_stcPitchData[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "BTM_SCAN", dData, "%0.2lf");
	m_stcPitchData[1].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "TOP_SCAN", dData, "%0.2lf");
	m_stcTimeOver[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "BTM_SCAN_MEM", dData, "%0.2lf");
	m_stcTimeOver[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "TOP_SCAN_MEM", dData, "%0.2lf");

	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) { strKey.Format("%d%d", i, j); INI.Set_Bool("TOWER", strKey, m_chkTower[i][j].GetCheck()); }
	for (int i = 0; i < 2; i++) for (int j = 0; j < 5; j++) { strKey.Format("%d%d", i, j); INI.Set_Bool("BUZZER", strKey, m_chkBuzzer[i][j].GetCheck()); }

	m_stcPasswordMt.GetWindowText(strData); INI.Set_String("HIDDEN", "PASSWORD_MT", strData);
	m_edtPasswordSi.GetWindowText(strData); INI.Set_String("HIDDEN", "PASSWORD_SI", strData);

	m_stcDelayTime[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "OPEN_DELAY", nData);
	m_stcDelayTime[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "CLOSE_DELAY", nData);
	m_stcDelayTime[2].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "BTM_SCAN_DELAY", nData);
	m_stcDelayTime[3].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "TOP_SCAN_DELAY", nData);
	m_stcDelayTime[4].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "VACUUM_ON_DELAY", nData);
	m_stcDelayTime[5].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "ALIGN_DELAY", nData);
	m_stcDelayTime[6].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "ALIGN_SHIP", nData);
	m_stcDelayTime[7].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "OPEN_UNLOAD", nData);
	m_stcDelayTime[8].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "CLOSE_UNLOAD", nData);
	m_stcDelayTime[9].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "TOP2_SCAN_DELAY", nData);

	m_stcTimeOver[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TIME_OVER", "INSPECTION", nData);
	m_stcTimeOver[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TIME_OVER", "ROS", nData);
	INI.Set_Bool("TIME_OVER", "AUTO_SKIP",  m_chkUseAuotSkip.GetCheck());

	m_edtDryRunTest.GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DRY_RUN", "NG_RATIO", nData);

	CString sPathSource;
	sPathSource = gsCurrentDir + "\\System\\Model\\";
	sPathSource += strModel;
	sPathSource += _T("\\");
	Save_ModelEquipData(sPathSource);

//	g_objDataManager.Save_MoveData();	//¸ðµ¨À» ¹Ù²å´Ù¸é ¹Ù²ï ¹«ºêµ¥ÀÌÅÍ º¯¼ö¸¦ ÆÄÀÏ¿¡´Ù°¡ ÀúÀåÇØÁà¾ßÇÑ´Ù.
	g_objLogFile.Save_HandlerLog("[Setup Equip] Save Click");

	Cancel_EquipData();
}

void CSetupEquipDlg::Save_ModelEquipData(CString sPath)
{
	CString strKey, strData;
	int nData;
	double dData;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	CIniFileCS INI(sPath + "EquipData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("EquipData.ini File Not Found!!");
		return;
	}

	m_stcEquipName.GetWindowText(strData); INI.Set_String("EQUIPMENT", "NAME", strData);
	m_stcEquipModel.GetWindowText(strData); INI.Set_String("EQUIPMENT", "MODEL", strData);
	nData = m_cboLotBarcodePort.GetCurSel(); INI.Set_Integer("EQUIPMENT", "LOT_BARCODE", nData + 1);
	INI.Set_Bool("EQUIPMENT", "DOOR_LOCK", m_rdoDoorLock[1].GetCheck());
	INI.Set_Bool("EQUIPMENT", "TAKT_LOG", TRUE);
	INI.Set_Bool("EQUIPMENT", "MEMPHIS_USE", m_rdoTaktLog[1].GetCheck());
	INI.Set_Bool("EQUIPMENT", "LIGHT_CURTAIN", m_rdoLightCur[1].GetCheck());
	INI.Set_Bool("EQUIPMENT", "COSMETICNG", m_rdoCosmeticNG[1].GetCheck());

	INI.Set_Bool("OPTION", "DRY_RUN_USE", m_chkDryRun.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_BTM", m_chkUseInspectBtm.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_TOP1", m_chkUseInspectTop1.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_TOP2", m_chkUseInspectTop2.GetCheck());
	INI.Set_Bool("OPTION", "ALIGN_1", m_chkUseInspectAl1.GetCheck());
	INI.Set_Bool("OPTION", "ALIGN_2", m_chkUseInspectAl2.GetCheck());
	INI.Set_Bool("OPTION", "ROS_USE", m_chkUseInspectRos.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_BAG", m_chkUseInspectBtmAngle.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_TAG", m_chkUseInspectTop1Angle.GetCheck());
	INI.Set_Bool("OPTION", "CM_CHECK", m_chkUseCMCheck.GetCheck());
	INI.Set_Bool("OPTION", "NG_SORT",  m_chkUseNGSort.GetCheck());
	INI.Set_Bool("OPTION", "NG_SIZE",  m_chkUseNGSize.GetCheck());
	INI.Set_Bool("OPTION", "GOOD_SORT",m_chkUseGoodSort.GetCheck());
	INI.Set_Bool("OPTION", "ELEVATOR_ALIGN",m_chkUseEleAlign.GetCheck());
	INI.Set_Bool("OPTION", "INSPECT_BLOW",  m_chkUseAirBlow.GetCheck());
	INI.Set_Bool("OPTION", "PASS_GOOD",  m_chkUsePassGood.GetCheck());

//	if		(m_rdoLanguage[0].GetCheck()) strData = "KOR";
//	else								  strData = "ENG";
//	INI.Set_String("OPTION", "LANGUAGE", strData);
	INI.Set_Bool("OPTION", "MES_USE",	   m_rdoMESUse[1].GetCheck());
	INI.Set_Bool("OPTION", "MES_CNTCHECK", m_rdoMESUse2[1].GetCheck());
	m_stcPitchData[2].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("OPTION", "REJECT_COUNT", nData);
	m_stcPitchData[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double("OPTION", "MOTION_CHECK", dData, "%0.3lf");

	m_stcCmTrayData[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TRAY", "COUNT_X", nData);
	m_stcCmTrayData[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TRAY", "COUNT_Y", nData);
	m_stcCmTrayData[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRAY", "PITCH_X", dData, "%0.2lf");
	m_stcCmTrayData[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRAY", "PITCH_Y", dData, "%0.2lf");
	m_stcCmTrayData[4].GetWindowText(strData); dData = atof(strData); INI.Set_Double ("TRAY", "PITCH_YMEM", dData, "%0.2lf");

	m_stcPitchData[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "BTM_SCAN", dData, "%0.2lf");
	m_stcPitchData[1].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "TOP_SCAN", dData, "%0.2lf");

	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) { strKey.Format("%d%d", i, j); INI.Set_Bool("TOWER", strKey, m_chkTower[i][j].GetCheck()); }
	for (int i = 0; i < 2; i++) for (int j = 0; j < 5; j++) { strKey.Format("%d%d", i, j); INI.Set_Bool("BUZZER", strKey, m_chkBuzzer[i][j].GetCheck()); }

	m_stcPasswordMt.GetWindowText(strData); INI.Set_String("HIDDEN", "PASSWORD_MT", strData);
	m_edtPasswordSi.GetWindowText(strData); INI.Set_String("HIDDEN", "PASSWORD_SI", strData);

	m_stcDelayTime[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "OPEN_DELAY", nData);
	m_stcDelayTime[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "CLOSE_DELAY", nData);
	m_stcDelayTime[2].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "BTM_SCAN_DELAY", nData);
	m_stcDelayTime[3].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "TOP_SCAN_DELAY", nData);
	m_stcDelayTime[4].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "VACUUM_ON_DELAY", nData);
	m_stcDelayTime[5].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "ALIGN_DELAY", nData);
	m_stcDelayTime[6].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "ALIGN_SHIP", nData);
	m_stcDelayTime[7].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "OPEN_UNLOAD", nData);
	m_stcDelayTime[8].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "CLOSE_UNLOAD", nData);
	m_stcDelayTime[9].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DELAY_TIME", "TOP2_SCAN_DELAY", nData);

	m_stcTimeOver[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TIME_OVER", "INSPECTION", nData);
	m_stcTimeOver[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TIME_OVER", "ROS", nData);
	INI.Set_Bool("TIME_OVER", "AUTO_SKIP",  m_chkUseAuotSkip.GetCheck());

	m_edtDryRunTest.GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("DRY_RUN", "NG_RATIO", nData);

	g_objLogFile.Save_HandlerLog("[Setup Equip] Model Save");
}

void CSetupEquipDlg::Cancel_EquipData()
{
	g_objDataManager.Read_EquipData();
	g_objDataManager.Read_IdleData();
	g_objDataManager.Read_MoveData();
	Display_EquipData();

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Display_EquipName();

	if (g_objCommon.Read_FocusOffset() == FALSE) {
		g_objCommon.Show_MsgBox(1, "Vision Stage Offset ÆÄÀÏÀ» È®ÀÎÇØ ÁÖ¼¼¿ä.");
	}

	g_objLogFile.Save_HandlerLog("[Setup Equip] Cancel Click");
}

///////////////////////////////////////////////////////////////////////////////

void CSetupEquipDlg::OnStnClickedStcEquipModel()
{
	CString strKey, strMsg;
	if (g_objCommon.Show_KeyPad(strKey) != IDOK) return;
	if (strKey.Find("-") >= 0) {
		strMsg.Format("[%s] Recipe Name ( - ) ÀÔ·ÂºÒ°¡...", strKey);
		g_objCommon.Show_MsgBox(1, strMsg);
		return;
	}
	if (strKey.Find(" ") >= 0) {
		strMsg.Format("[%s] Recipe Name (  ) ÀÔ·ÂºÒ°¡...", strKey);
		g_objCommon.Show_MsgBox(1, strMsg);
		return;
	}

	m_stcEquipModel.SetWindowText(strKey);

	m_strLog.Format("[Setup Equip] OnStnClickedStcEquipModel - Data(%s)", strKey);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupEquipDlg::InitModelComboBox()
{

	CString sPathSource;
	sPathSource = gsCurrentDir + "\\System\\Model";

	for(int i=m_cboModelChange.GetCount()-1; i>=0; i--)
	{
		m_cboModelChange.DeleteString(i);
	}

	if (GetFileAttributes(sPathSource) == -1) return;	// µð·ºÅä¸® ¾øÀ½

	int nIndex = 0 ;

	CFileFind ff;

	BOOL bFile = ff.FindFile(sPathSource + _T("\\*.*"));

	while(bFile)
	{
		bFile = ff.FindNextFile();

		CString str;	// = ff.GetFileName();

		if(ff.IsDots()) continue;

		if(ff.IsDirectory()){
			str = ff.GetFileName();
			m_cboModelChange.AddString(str);
		}

		//str = str.Left(str.ReverseFind(_T('.')));

		//m_cboModelChange.AddString(str);

	}
	ff.Close();
}

void CSetupEquipDlg::OnBnClickedButtonModelAdd()
{
	CString strModel;
	m_stcEquipModel.GetWindowText(strModel);

	if(!strModel.IsEmpty())
	{
		CString sPathSource;
		sPathSource = gsCurrentDir + "\\System\\Model";
		sPathSource += _T("\\");
		sPathSource += strModel;

		if (GetFileAttributes(sPathSource) == -1) {	// µð·ºÅä¸® ¾øÀ½
			g_objLogFile.Create_Folder(sPathSource);

			CString strOriginFile, strTargetFile;

			strOriginFile = gsCurrentDir + "\\System\\EquipData.ini";
			strTargetFile = sPathSource + "\\EquipData.ini";
			if (!CopyFile(strOriginFile, strTargetFile, FALSE)) {
				AfxMessageBox("EquipData.ini File Copy Fail!!!");
				return;
			}
/*
			strOriginFile = gsCurrentDir + "\\System\\MoveData.ini";
			strTargetFile = sPathSource + "\\MoveData.ini";
			if (!CopyFile(strOriginFile, strTargetFile, FALSE)) {
				AfxMessageBox("EquipData.ini File Copy Fail!!!");
				return;
			}
*/
		} else {
			if (gData.nLanguage == 0) AfxMessageBox("ÀÌ¹Ì °°Àº ¸ðµ¨ÀÌ ÀÖ½À´Ï´Ù.");
			else					  AfxMessageBox("You already have the same model.");
		}
		Save_EquipData();

		Display_EquipData();
	}
}


void CSetupEquipDlg::OnCbnDropdownCboModelChange()
{
	InitModelComboBox();
}


void CSetupEquipDlg::OnCbnSelchangeCboModelChange()
{
	CString strModel;
	int nSel = m_cboModelChange.GetCurSel();
	m_cboModelChange.GetLBText(nSel, strModel);

	if(!strModel.IsEmpty())
	{
		CString sPathSource;
		sPathSource = gsCurrentDir + "\\System\\Model";
		sPathSource += _T("\\");
		sPathSource += strModel;
		sPathSource += _T("\\");

		g_objDataManager.Read_ModelEquipData(sPathSource);
//		g_objDataManager.Read_ModelMoveData(sPathSource);

		Display_EquipData();
	}
}

void CSetupEquipDlg::Save_MESData(BOOL bUse, BOOL bChange)
{
	CString str, sPathSource, sRcipeData = "";

	sPathSource = gsCurrentDir + "\\System\\Model";
	if (GetFileAttributes(sPathSource) == -1) return;

	CFileFind ff;
	BOOL bFile = ff.FindFile(sPathSource + _T("\\*.*"));

	while(bFile)
	{
		bFile = ff.FindNextFile();
		if(ff.IsDots()) continue;

		if(ff.IsDirectory()) {
			str.Format("%s\\%s", sPathSource, ff.GetFileName());
			Set_MESData(str, bUse, bChange);
		}
	}
	ff.Close();

	g_objLogFile.Save_HandlerLog("[Setup Equip] Save_MESData Change");
}

void CSetupEquipDlg::Set_MESData(CString sPath, BOOL bUse, BOOL bChange)
{
	CIniFileCS INI(sPath + "\\EquipData.ini");
	if (!INI.Check_File()) return;

	INI.Set_Bool("OPTION", "MES_USE",	   bUse);
	INI.Set_Bool("OPTION", "MES_CNTCHECK", bChange);

	int		nData;
	double	dData;
	CString strData;
	m_stcTimeOver[0].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TIME_OVER", "INSPECTION", nData);
	m_stcTimeOver[1].GetWindowText(strData); nData = atoi(strData); INI.Set_Integer("TIME_OVER", "ROS", nData);
	INI.Set_Bool("TIME_OVER", "AUTO_SKIP",  m_chkUseAuotSkip.GetCheck());
	m_stcPitchData[0].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "BTM_SCAN", dData, "%0.2lf");
	m_stcPitchData[1].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "TOP_SCAN", dData, "%0.2lf");
	m_stcTimeOver[2].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "BTM_SCAN_MEM", dData, "%0.2lf");
	m_stcTimeOver[3].GetWindowText(strData); dData = atof(strData); INI.Set_Double("PITCH", "TOP_SCAN_MEM", dData, "%0.2lf");
}

void CSetupEquipDlg::OnBnClickedBtnMdjDelete()
{
	CString strIp;
	int nIdx = m_lstMdjIp.GetCurSel();
	m_lstMdjIp.GetText(nIdx, strIp);

	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	POSITION pos = pRosData->lstMdjIp.Find(strIp);
	if (pos) pRosData->lstMdjIp.RemoveAt(pos);

	if (pRosData->lstMdjIp.GetCount() < 1) g_objDispatcher.Set_Connected(FALSE);

	OnBnClickedBtnMdjRefresh();
}

void CSetupEquipDlg::OnBnClickedBtnMdjRefresh()
{
	m_lstMdjIp.ResetContent();

	ROS_DATA *pRosData = g_objDataManager.Get_pRosData();
	POSITION pos = pRosData->lstMdjIp.GetHeadPosition();
	while (pos) {
		CString strIp = pRosData->lstMdjIp.GetNext(pos);
		m_lstMdjIp.AddString(strIp);
	}
}
