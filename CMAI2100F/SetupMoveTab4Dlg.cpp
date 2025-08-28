// SetupMoveTab4Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupMoveTab4Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"

#include "AJinDefine.h"

// CSetupMoveTab4Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab4Dlg, CDialogEx)

CSetupMoveTab4Dlg::CSetupMoveTab4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab4Dlg::IDD, pParent)
{
}

CSetupMoveTab4Dlg::~CSetupMoveTab4Dlg()
{
}

void CSetupMoveTab4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 13; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 86; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 16; i++) DDX_Control(pDX, IDC_STC_UNLOADPICK_X1_0 + i, m_stcUnloadPickX1[i]);
	for (int i = 0; i <  9; i++) DDX_Control(pDX, IDC_STC_UNLOADPICK_Y1_0 + i, m_stcUnloadPickY1[i]);
	for (int i = 0; i <  9; i++) DDX_Control(pDX, IDC_STC_UNLOADPICK_Z1_0 + i, m_stcUnloadPickZ1[i]);
	for (int i = 0; i <  3; i++) DDX_Control(pDX, IDC_STC_UNLOADPICK_P1_0 + i, m_stcUnloadPickP1[i]);
	for (int i = 0; i < 16; i++) DDX_Control(pDX, IDC_STC_UNLOADPICK_X2_0 + i, m_stcUnloadPickX2[i]);
	for (int i = 0; i <  9; i++) DDX_Control(pDX, IDC_STC_UNLOADPICK_Y2_0 + i, m_stcUnloadPickY2[i]);
	for (int i = 0; i <  9; i++) DDX_Control(pDX, IDC_STC_UNLOADPICK_Z2_0 + i, m_stcUnloadPickZ2[i]);
	for (int i = 0; i <  3; i++) DDX_Control(pDX, IDC_STC_UNLOADPICK_P2_0 + i, m_stcUnloadPickP2[i]);
	for (int i = 0; i <  6; i++) DDX_Control(pDX, IDC_STC_NGSTAGE_Y1_0 + i, m_stcNGStageY1[i]);
	for (int i = 0; i <  6; i++) DDX_Control(pDX, IDC_STC_NGSTAGE_Y2_0 + i, m_stcNGStageY2[i]);
	for (int i = 0; i <  6; i++) DDX_Control(pDX, IDC_STC_GOODSTAGE_Y1_0 + i, m_stcGoodStageY1[i]);
	for (int i = 0; i <  6; i++) DDX_Control(pDX, IDC_STC_GOODSTAGE_Y2_0 + i, m_stcGoodStageY2[i]);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab4Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_UNLOADPICK_X1_0, IDC_STC_UNLOADPICK_X1_15, OnStcUnloadPickX1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_UNLOADPICK_Y1_0, IDC_STC_UNLOADPICK_Y1_8, OnStcUnloadPickY1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_UNLOADPICK_Z1_0, IDC_STC_UNLOADPICK_Z1_8, OnStcUnloadPickZ1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_UNLOADPICK_P1_0, IDC_STC_UNLOADPICK_P1_2, OnStcUnloadPickP1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_UNLOADPICK_X2_0, IDC_STC_UNLOADPICK_X2_15, OnStcUnloadPickX2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_UNLOADPICK_Y2_0, IDC_STC_UNLOADPICK_Y2_8, OnStcUnloadPickY2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_UNLOADPICK_Z2_0, IDC_STC_UNLOADPICK_Z2_8, OnStcUnloadPickZ2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_UNLOADPICK_P2_0, IDC_STC_UNLOADPICK_P2_2, OnStcUnloadPickP2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_NGSTAGE_Y1_0, IDC_STC_NGSTAGE_Y1_5, OnStcNGStageY1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_NGSTAGE_Y2_0, IDC_STC_NGSTAGE_Y2_5, OnStcNGStageY2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_GOODSTAGE_Y1_0, IDC_STC_GOODSTAGE_Y1_5, OnStcGoodStageY1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_GOODSTAGE_Y2_0, IDC_STC_GOODSTAGE_Y2_5, OnStcGoodStageY2Click)
END_MESSAGE_MAP()

// CSetupMoveTab4Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab4Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab4Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab4Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab4");
}

void CSetupMoveTab4Dlg::OnStcUnloadPickX1Click(UINT nID)			
{
	int ID = nID - IDC_STC_UNLOADPICK_X1_0;

	CString strOld, strNew;
	m_stcUnloadPickX1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_UNLOAD_PICKER_X1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_UNLOAD_PICKER_X1, ID+1, strNew)==FALSE) return;

	m_stcUnloadPickX1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcUnloadPickX1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcUnloadPickY1Click(UINT nID)			
{
	int ID = nID - IDC_STC_UNLOADPICK_Y1_0;

	CString strOld, strNew;
	m_stcUnloadPickY1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_UNLOAD_PICKER_Y1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_UNLOAD_PICKER_Y1, ID, strNew)==FALSE) return;

	m_stcUnloadPickY1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcUnloadPickY1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcUnloadPickZ1Click(UINT nID)			
{
	int ID = nID - IDC_STC_UNLOADPICK_Z1_0;

	CString strOld, strNew;
	m_stcUnloadPickZ1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_UNLOAD_PICKER_Z1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_UNLOAD_PICKER_Z1, ID, strNew)==FALSE) return;

	m_stcUnloadPickZ1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcUnloadPickZ1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcUnloadPickP1Click(UINT nID)			
{
	int ID = nID - IDC_STC_UNLOADPICK_P1_0;

	CString strOld, strNew;
	m_stcUnloadPickP1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_UNLOAD_PICKER_P1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_UNLOAD_PICKER_P1, ID, strNew)==FALSE) return;

	m_stcUnloadPickP1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcUnloadPickP1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcUnloadPickX2Click(UINT nID)			
{
	int ID = nID - IDC_STC_UNLOADPICK_X2_0;

	CString strOld, strNew;
	m_stcUnloadPickX2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_UNLOAD_PICKER_X2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_UNLOAD_PICKER_X2, ID+1, strNew)==FALSE) return;

	m_stcUnloadPickX2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcUnloadPickX2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcUnloadPickY2Click(UINT nID)			
{
	int ID = nID - IDC_STC_UNLOADPICK_Y2_0;

	CString strOld, strNew;
	m_stcUnloadPickY2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_UNLOAD_PICKER_Y2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_UNLOAD_PICKER_Y2, ID, strNew)==FALSE) return;

	m_stcUnloadPickY2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcUnloadPickY2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcUnloadPickZ2Click(UINT nID)			
{
	int ID = nID - IDC_STC_UNLOADPICK_Z2_0;

	CString strOld, strNew;
	m_stcUnloadPickZ2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_UNLOAD_PICKER_Z2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_UNLOAD_PICKER_Z2, ID, strNew)==FALSE) return;

	m_stcUnloadPickZ2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcUnloadPickZ2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcUnloadPickP2Click(UINT nID)			
{
	int ID = nID - IDC_STC_UNLOADPICK_P2_0;

	CString strOld, strNew;
	m_stcUnloadPickP2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_UNLOAD_PICKER_P2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_UNLOAD_PICKER_P2, ID, strNew)==FALSE) return;

	m_stcUnloadPickP2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcUnloadPickP2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcNGStageY1Click(UINT nID)			
{
	int ID = nID - IDC_STC_NGSTAGE_Y1_0;

	CString strOld, strNew;
	m_stcNGStageY1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_NG_STAGE_Y1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_NG_STAGE_Y1, ID, strNew)==FALSE) return;

	m_stcNGStageY1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcNGStageY1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcNGStageY2Click(UINT nID)			
{
	int ID = nID - IDC_STC_NGSTAGE_Y2_0;

	CString strOld, strNew;
	m_stcNGStageY2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_NG_STAGE_Y2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_NG_STAGE_Y2, ID, strNew)==FALSE) return;

	m_stcNGStageY2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcNGStageY2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcGoodStageY1Click(UINT nID)			
{
	int ID = nID - IDC_STC_GOODSTAGE_Y1_0;

	CString strOld, strNew;
	m_stcGoodStageY1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_GOOD_STAGE_Y1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_GOOD_STAGE_Y1, ID, strNew)==FALSE) return;

	m_stcGoodStageY1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcGoodStageY1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab4Dlg::OnStcGoodStageY2Click(UINT nID)			
{
	int ID = nID - IDC_STC_GOODSTAGE_Y2_0;

	CString strOld, strNew;
	m_stcGoodStageY2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_GOOD_STAGE_Y2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_GOOD_STAGE_Y2, ID, strNew)==FALSE) return;

	m_stcGoodStageY2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcGoodStageY2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab4Dlg::Initial_Controls() 
{
	for (int i = 0; i < 13; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i < 86; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 16; i++) m_stcUnloadPickX1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 9; i++) m_stcUnloadPickY1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 9; i++) m_stcUnloadPickZ1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 3; i++) m_stcUnloadPickP1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));

	for (int i = 0; i < 16; i++) m_stcUnloadPickX2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 9; i++) m_stcUnloadPickY2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 9; i++) m_stcUnloadPickZ2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));
	for (int i = 0; i < 3; i++) m_stcUnloadPickP2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xC0, 0xFF, 0xF0));

	for (int i = 0; i < 6; i++) m_stcNGStageY1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));
	for (int i = 0; i < 6; i++) m_stcNGStageY2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xE0, 0xE0));

	for (int i = 0; i < 6; i++) m_stcGoodStageY1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 6; i++) m_stcGoodStageY2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
}

void CSetupMoveTab4Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;
	for (int i = 0; i <16; i++) { strData.Format("%0.3lf", pMoveData->dUnloadPickerX1[i+1]);	m_stcUnloadPickX1[i].SetWindowText(strData); }
	for (int i = 0; i < 9; i++) { strData.Format("%0.3lf", pMoveData->dUnloadPickerY1[i]);		m_stcUnloadPickY1[i].SetWindowText(strData); }
	for (int i = 0; i < 9; i++) { strData.Format("%0.3lf", pMoveData->dUnloadPickerZ1[i]);		m_stcUnloadPickZ1[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++) { strData.Format("%0.3lf", pMoveData->dUnloadPickerP1[i]);		m_stcUnloadPickP1[i].SetWindowText(strData); }

	for (int i = 0; i <16; i++) { strData.Format("%0.3lf", pMoveData->dUnloadPickerX2[i+1]);	m_stcUnloadPickX2[i].SetWindowText(strData); }
	for (int i = 0; i < 9; i++) { strData.Format("%0.3lf", pMoveData->dUnloadPickerY2[i]);		m_stcUnloadPickY2[i].SetWindowText(strData); }
	for (int i = 0; i < 9; i++) { strData.Format("%0.3lf", pMoveData->dUnloadPickerZ2[i]);		m_stcUnloadPickZ2[i].SetWindowText(strData); }
	for (int i = 0; i < 3; i++) { strData.Format("%0.3lf", pMoveData->dUnloadPickerP2[i]);		m_stcUnloadPickP2[i].SetWindowText(strData); }

	for (int i = 0; i < 6; i++) { strData.Format("%0.3lf", pMoveData->dNGStageY1[i]);			m_stcNGStageY1[i].SetWindowText(strData); }
	for (int i = 0; i < 6; i++) { strData.Format("%0.3lf", pMoveData->dNGStageY2[i]);			m_stcNGStageY2[i].SetWindowText(strData); }
	for (int i = 0; i < 6; i++) { strData.Format("%0.3lf", pMoveData->dGoodStageY1[i]);			m_stcGoodStageY1[i].SetWindowText(strData); }
	for (int i = 0; i < 6; i++) { strData.Format("%0.3lf", pMoveData->dGoodStageY2[i]);			m_stcGoodStageY2[i].SetWindowText(strData); }
}

void CSetupMoveTab4Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return;
	}

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");

	CString strKey, strData;
	double dData;

	for (int i = 0; i <16; i++) { strKey.Format("%02d", i+1);	m_stcUnloadPickX1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("30_UNLOAD_PICKER_X1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		m_stcUnloadPickY1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("31_UNLOAD_PICKER_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		m_stcUnloadPickZ1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("32_UNLOAD_PICKER_Z1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);		m_stcUnloadPickP1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("33_UNLOAD_PICKER_P1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i <16; i++) { strKey.Format("%02d", i+1);	m_stcUnloadPickX2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("34_UNLOAD_PICKER_X2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		m_stcUnloadPickY2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("35_UNLOAD_PICKER_Y2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		m_stcUnloadPickZ2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("36_UNLOAD_PICKER_Z2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);		m_stcUnloadPickP2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("37_UNLOAD_PICKER_P2", strKey, dData, "%0.3lf"); }

	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		m_stcGoodStageY1[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("38_GOOD_STAGE_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		m_stcGoodStageY2[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("39_GOOD_STAGE_Y2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		m_stcNGStageY1[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("40_NG_STAGE_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		m_stcNGStageY2[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("41_NG_STAGE_Y2", strKey, dData, "%0.3lf"); }

//	Save_ModelMoveData();

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 4] save");

	Cancel_MoveData();
}

void CSetupMoveTab4Dlg::Save_ModelMoveData()
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

	for (int i = 0; i <16; i++) { strKey.Format("%02d", i+1);	m_stcUnloadPickX1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("30_UNLOAD_PICKER_X1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		m_stcUnloadPickY1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("31_UNLOAD_PICKER_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		m_stcUnloadPickZ1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("32_UNLOAD_PICKER_Z1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);		m_stcUnloadPickP1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("33_UNLOAD_PICKER_P1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i <16; i++) { strKey.Format("%02d", i+1);	m_stcUnloadPickX2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("34_UNLOAD_PICKER_X2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		m_stcUnloadPickY2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("35_UNLOAD_PICKER_Y2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		m_stcUnloadPickZ2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("36_UNLOAD_PICKER_Z2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 3; i++) { strKey.Format("%02d", i);		m_stcUnloadPickP2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("37_UNLOAD_PICKER_P2", strKey, dData, "%0.3lf"); }

	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		m_stcGoodStageY1[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("38_GOOD_STAGE_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		m_stcGoodStageY2[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("39_GOOD_STAGE_Y2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		m_stcNGStageY1[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("40_NG_STAGE_Y1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		m_stcNGStageY2[i].GetWindowText(strData);		dData = atof(strData);	INI.Set_Double("41_NG_STAGE_Y2", strKey, dData, "%0.3lf"); }

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 4] Model save");
}

void CSetupMoveTab4Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();

	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
