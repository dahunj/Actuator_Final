// SetupMoveTab2Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupMoveTab2Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"

#include "AJinDefine.h"

// CSetupMoveTab2Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab2Dlg, CDialogEx)

CSetupMoveTab2Dlg::CSetupMoveTab2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab2Dlg::IDD, pParent)
{
}

CSetupMoveTab2Dlg::~CSetupMoveTab2Dlg()
{
}

void CSetupMoveTab2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 13; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 55; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_LOADPICK1_X_0 + i, m_stcLoadPickX1[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_LOADPICK1_Y_0 + i, m_stcLoadPickY1[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_LOADPICK1_Z_0 + i, m_stcLoadPickZ1[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_LOADPICK1_P_0 + i, m_stcLoadPickP1[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_LOADPICK2_X_0 + i, m_stcLoadPickX2[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_LOADPICK2_Y_0 + i, m_stcLoadPickY2[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_LOADPICK2_Z_0 + i, m_stcLoadPickZ2[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_LOADPICK2_P_0 + i, m_stcLoadPickP2[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_LOADSTAGE1_Y_0 + i, m_stcLoadStageY1[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_STC_LOADSTAGE2_Y_0 + i, m_stcLoadStageY2[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_BTM_FOCUS_Z_0 + i, m_stcBtmFocusZ[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_BTM_LIGHT_Z_0 + i, m_stcBtmLightZ[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_BTM_ANGLE_Y_0 + i, m_stcBtmAngleY[i]);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab2Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK1_X_0, IDC_STC_LOADPICK1_X_3, OnStcLoadPickX1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK1_Y_0, IDC_STC_LOADPICK1_Y_4, OnStcLoadPickY1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK1_Z_0, IDC_STC_LOADPICK1_Z_4, OnStcLoadPickZ1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK1_P_0, IDC_STC_LOADPICK1_P_2, OnStcLoadPickP1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK2_X_0, IDC_STC_LOADPICK2_X_3, OnStcLoadPickX2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK2_Y_0, IDC_STC_LOADPICK2_Y_4, OnStcLoadPickY2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK2_Z_0, IDC_STC_LOADPICK2_Z_4, OnStcLoadPickZ2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADPICK2_P_0, IDC_STC_LOADPICK2_P_2, OnStcLoadPickP2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADSTAGE1_Y_0, IDC_STC_LOADSTAGE1_Y_5, OnStcLoadStageY1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_LOADSTAGE2_Y_0, IDC_STC_LOADSTAGE2_Y_5, OnStcLoadStageY2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_BTM_FOCUS_Z_0, IDC_STC_BTM_FOCUS_Z_2, OnstcBtmFocusZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_BTM_LIGHT_Z_0, IDC_STC_BTM_LIGHT_Z_2, OnstcBtmLightZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_BTM_ANGLE_Y_0, IDC_STC_BTM_ANGLE_Y_2, OnstcBtmAngleYClick)
END_MESSAGE_MAP()

// CSetupMoveTab2Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab2Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab2Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab2Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab2");
}

void CSetupMoveTab2Dlg::OnStcLoadPickX1Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK1_X_0;

	CString strOld, strNew;
	m_stcLoadPickX1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_PICKER_X1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_PICKER_X1, ID+1, strNew)==FALSE) return;

	m_stcLoadPickX1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadPickX1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadPickY1Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK1_Y_0;

	CString strOld, strNew;
	m_stcLoadPickY1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_PICKER_Y1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_PICKER_Y1, ID, strNew)==FALSE) return;

	m_stcLoadPickY1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadPickY1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadPickZ1Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK1_Z_0;

	CString strOld, strNew;
	m_stcLoadPickZ1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_PICKER_Z1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_PICKER_Z1, ID, strNew)==FALSE) return;

	m_stcLoadPickZ1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadPickZ1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadPickP1Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK1_P_0;

	CString strOld, strNew;
	m_stcLoadPickP1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_PICKER_P1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_PICKER_P1, ID, strNew)==FALSE) return;

	m_stcLoadPickP1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadPickP1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadPickX2Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK2_X_0;

	CString strOld, strNew;
	m_stcLoadPickX2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_PICKER_X2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_PICKER_X2, ID+1, strNew)==FALSE) return;

	m_stcLoadPickX2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadPickX2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadPickY2Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK2_Y_0;

	CString strOld, strNew;
	m_stcLoadPickY2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_PICKER_Y2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_PICKER_Y2, ID, strNew)==FALSE) return;

	m_stcLoadPickY2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadPickY2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadPickZ2Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK2_Z_0;

	CString strOld, strNew;
	m_stcLoadPickZ2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_PICKER_Z2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_PICKER_Z2, ID, strNew)==FALSE) return;

	m_stcLoadPickZ2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadPickZ2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadPickP2Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADPICK2_P_0;

	CString strOld, strNew;
	m_stcLoadPickP2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_PICKER_P2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_PICKER_P2, ID, strNew)==FALSE) return;

	m_stcLoadPickP2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadPickP2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadStageY1Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADSTAGE1_Y_0;

	CString strOld, strNew;
	m_stcLoadStageY1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_STAGE_Y1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_STAGE_Y1, ID, strNew)==FALSE) return;

	m_stcLoadStageY1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadStageY1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnStcLoadStageY2Click(UINT nID)
{
	int ID = nID - IDC_STC_LOADSTAGE2_Y_0;

	CString strOld, strNew;
	m_stcLoadStageY2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_LOAD_STAGE_Y2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_LOAD_STAGE_Y2, ID, strNew)==FALSE) return;

	m_stcLoadStageY2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcLoadStageY2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnstcBtmFocusZClick(UINT nID)
{
	int ID = nID - IDC_STC_BTM_FOCUS_Z_0;

	CString strOld, strNew;
	m_stcBtmFocusZ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_BTM_FOCUS_Z) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_BTM_FOCUS_Z, ID, strNew)==FALSE) return;

	m_stcBtmFocusZ[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnstcBtmFocusZClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnstcBtmLightZClick(UINT nID)
{
	int ID = nID - IDC_STC_BTM_LIGHT_Z_0;

	CString strOld, strNew;
	m_stcBtmLightZ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_BTM_LIGHT_Z) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_BTM_LIGHT_Z, ID, strNew)==FALSE) return;

	m_stcBtmLightZ[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnstcBtmLightZClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab2Dlg::OnstcBtmAngleYClick(UINT nID)
{
	int ID = nID - IDC_STC_BTM_ANGLE_Y_0;

	CString strOld, strNew;
	m_stcBtmAngleY[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_BTM_ANGLE_Y) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_BTM_ANGLE_Y, ID, strNew)==FALSE) return;

	m_stcBtmAngleY[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnstcBtmAngleYClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab2Dlg::Initial_Controls() 
{
	for (int i = 0; i < 13; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 55; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 4; i++)  m_stcLoadPickX1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcLoadPickY1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcLoadPickZ1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 3; i++)  m_stcLoadPickP1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));

	for (int i = 0; i < 4; i++)  m_stcLoadPickX2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcLoadPickY2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++)  m_stcLoadPickZ2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 3; i++)  m_stcLoadPickP2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));

	for (int i = 0; i < 6; i++)  m_stcLoadStageY1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 6; i++)  m_stcLoadStageY2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));

	for (int i = 0; i < 3; i++)  m_stcBtmFocusZ[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 3; i++)  m_stcBtmLightZ[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 3; i++)  m_stcBtmAngleY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
}

void CSetupMoveTab2Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;

	for (int i = 0; i < 4; i++)  { strData.Format("%0.3lf", pMoveData->dLoadPickerX1[i+1]);	m_stcLoadPickX1[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++)  { strData.Format("%0.3lf", pMoveData->dLoadPickerY1[i]);	m_stcLoadPickY1[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++)  { strData.Format("%0.3lf", pMoveData->dLoadPickerZ1[i]);	m_stcLoadPickZ1[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dLoadPickerP1[i]);	m_stcLoadPickP1[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++)  { strData.Format("%0.3lf", pMoveData->dLoadPickerX2[i+1]);	m_stcLoadPickX2[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++)  { strData.Format("%0.3lf", pMoveData->dLoadPickerY2[i]);	m_stcLoadPickY2[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++)  { strData.Format("%0.3lf", pMoveData->dLoadPickerZ2[i]);	m_stcLoadPickZ2[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dLoadPickerP2[i]);	m_stcLoadPickP2[i].SetWindowText(strData); }

	for (int i = 0; i < 6; i++)  { strData.Format("%0.3lf", pMoveData->dLoadStageY1[i]);	m_stcLoadStageY1[i].SetWindowText(strData); }
	for (int i = 0; i < 6; i++)  { strData.Format("%0.3lf", pMoveData->dLoadStageY2[i]);	m_stcLoadStageY2[i].SetWindowText(strData); }

	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dBTMFocusZ[i]);	m_stcBtmFocusZ[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dBTMLightZ[i]);	m_stcBtmLightZ[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++)  { strData.Format("%0.3lf", pMoveData->dBTMAngleY[i]);	m_stcBtmAngleY[i].SetWindowText(strData); }
}

void CSetupMoveTab2Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return;
	}

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 4; i++)  { strKey.Format("%02d", i+1);	m_stcLoadPickX1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("13_LOAD_PICKER_X1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++)  { strKey.Format("%02d", i);	m_stcLoadPickY1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("14_LOAD_PICKER_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++)  { strKey.Format("%02d", i);	m_stcLoadPickZ1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("15_LOAD_PICKER_Z1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcLoadPickP1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("16_LOAD_PICKER_P1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 4; i++)  { strKey.Format("%02d", i+1);	m_stcLoadPickX2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("17_LOAD_PICKER_X2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++)  { strKey.Format("%02d", i);	m_stcLoadPickY2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("18_LOAD_PICKER_Y2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++)  { strKey.Format("%02d", i);	m_stcLoadPickZ2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("19_LOAD_PICKER_Z2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcLoadPickP2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("20_LOAD_PICKER_P2", strKey, dData, "%0.3lf"); }

	for (int i = 0; i < 6; i++)  { strKey.Format("%02d", i);	m_stcLoadStageY1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("11_LOAD_STAGE_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++)  { strKey.Format("%02d", i);	m_stcLoadStageY2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("12_LOAD_STAGE_Y2", strKey, dData, "%0.3lf"); }

	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcBtmFocusZ[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("21_BTM_CAMERA_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcBtmLightZ[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("22_BTM_LIGHT_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcBtmAngleY[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("23_BTM_ANGLE_Y", strKey, dData, "%0.3lf"); }

//	Save_ModelMoveData();

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 2] save");

	Cancel_MoveData();
}

void CSetupMoveTab2Dlg::Save_ModelMoveData()
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();

	CString strPath = gsCurrentDir + "\\System\\Model\\" + pEquipData->sModelName + "\\MoveData.ini";
	CIniFileCS INI(strPath);
	if (!INI.Check_File()) {
		AfxMessageBox("Model MoveData.ini File Not Found!!!");
		return;
	}

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 4; i++)  { strKey.Format("%02d", i+1);	m_stcLoadPickX1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("13_LOAD_PICKER_X1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++)  { strKey.Format("%02d", i);	m_stcLoadPickY1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("14_LOAD_PICKER_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++)  { strKey.Format("%02d", i);	m_stcLoadPickZ1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("15_LOAD_PICKER_Z1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcLoadPickP1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("16_LOAD_PICKER_P1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 4; i++)  { strKey.Format("%02d", i+1);	m_stcLoadPickX2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("17_LOAD_PICKER_X2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++)  { strKey.Format("%02d", i);	m_stcLoadPickY2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("18_LOAD_PICKER_Y2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++)  { strKey.Format("%02d", i);	m_stcLoadPickZ2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("19_LOAD_PICKER_Z2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcLoadPickP2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("20_LOAD_PICKER_P2", strKey, dData, "%0.3lf"); }

	for (int i = 0; i < 6; i++)  { strKey.Format("%02d", i);	m_stcLoadStageY1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("11_LOAD_STAGE_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++)  { strKey.Format("%02d", i);	m_stcLoadStageY2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("12_LOAD_STAGE_Y2", strKey, dData, "%0.3lf"); }

	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcBtmFocusZ[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("21_BTM_CAMERA_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcBtmLightZ[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("22_BTM_LIGHT_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++)  { strKey.Format("%02d", i);	m_stcBtmAngleY[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("23_BTM_ANGLE_Y", strKey, dData, "%0.3lf"); }

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 2] Model save");
}

void CSetupMoveTab2Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
