// SetupMoveTab3Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupMoveTab3Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"

#include "AJinDefine.h"

// CSetupMoveTab3Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab3Dlg, CDialogEx)

CSetupMoveTab3Dlg::CSetupMoveTab3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab3Dlg::IDD, pParent)
{
}

CSetupMoveTab3Dlg::~CSetupMoveTab3Dlg()
{
}

void CSetupMoveTab3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 44; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_INSPECTION_X1_0 + i, m_stcInspectionX1[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_INSPECTION_X2_0 + i, m_stcInspectionX2[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_INSPECTION_X3_0 + i, m_stcInspectionX3[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_INSPECTION_X4_0 + i, m_stcInspectionX4[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TOP_Z1_0 + i, m_stcTOPZ1[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TOP1_LIGHT_Z_0 + i, m_stcTOP1LightZ[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TOP1_ANGLE_Y_0 + i, m_stcTOP1AngleY[i]);
	for (int i = 0; i < 5; i++) DDX_Control(pDX, IDC_STC_TOP_Z2_0 + i, m_stcTOPZ2[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_SHIPALIGN_X_0 + i, m_stcShipAlignX[i]);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab3Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_INSPECTION_X1_0, IDC_STC_INSPECTION_X1_4, OnStcInspectionX1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_INSPECTION_X2_0, IDC_STC_INSPECTION_X2_4, OnStcInspectionX2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_INSPECTION_X3_0, IDC_STC_INSPECTION_X3_4, OnStcInspectionX3Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_INSPECTION_X4_0, IDC_STC_INSPECTION_X4_4, OnStcInspectionX4Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TOP_Z1_0, IDC_STC_TOP_Z1_4, OnStcTopZ1Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TOP1_LIGHT_Z_0, IDC_STC_TOP1_LIGHT_Z_4, OnStcTop1LightZClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TOP1_ANGLE_Y_0, IDC_STC_TOP1_ANGLE_Y_4, OnStcTop1AngleYClick)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_TOP_Z2_0, IDC_STC_TOP_Z2_4, OnStcTopZ2Click)
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_SHIPALIGN_X_0, IDC_STC_SHIPALIGN_X_3, OnStcShipAlignXClick)
END_MESSAGE_MAP()

// CSetupMoveTab3Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab3Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab3Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab3Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

#ifdef NEW_FINAL
		m_Group[7].ShowWindow(FALSE);
		for(int i=34; i<37; i++) m_Label[i].ShowWindow(FALSE);
		for(int i=0; i<5; i++) m_stcTOP1LightZ[i].ShowWindow(FALSE);
		m_Group[8].ShowWindow(FALSE);
		m_Label[39].ShowWindow(FALSE);
		m_Label[40].ShowWindow(FALSE);
		m_Label[43].ShowWindow(FALSE);
		for(int i=0; i<5; i++) m_stcTOP1AngleY[i].ShowWindow(FALSE);
#endif

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab3");
}

void CSetupMoveTab3Dlg::OnStcInspectionX1Click(UINT nID)
{
	int ID = nID - IDC_STC_INSPECTION_X1_0;

	CString strOld, strNew;
	m_stcInspectionX1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_INSPECT_STAGE_X1) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_INSPECT_STAGE_X1, ID, strNew)==FALSE) return;

	m_stcInspectionX1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcInspectionX1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab3Dlg::OnStcInspectionX2Click(UINT nID)
{
	int ID = nID - IDC_STC_INSPECTION_X2_0;

	CString strOld, strNew;
	m_stcInspectionX2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_INSPECT_STAGE_X2) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_INSPECT_STAGE_X2, ID, strNew)==FALSE) return;

	m_stcInspectionX2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcInspectionX2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab3Dlg::OnStcInspectionX3Click(UINT nID)
{
	int ID = nID - IDC_STC_INSPECTION_X3_0;

	CString strOld, strNew;
	m_stcInspectionX3[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_INSPECT_STAGE_X3) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_INSPECT_STAGE_X3, ID, strNew)==FALSE) return;

	m_stcInspectionX3[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcInspectionX3Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab3Dlg::OnStcInspectionX4Click(UINT nID)
{
	int ID = nID - IDC_STC_INSPECTION_X4_0;

	CString strOld, strNew;
	m_stcInspectionX4[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_INSPECT_STAGE_X4) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_INSPECT_STAGE_X4, ID, strNew)==FALSE) return;

	m_stcInspectionX4[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcInspectionX4Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab3Dlg::OnStcTopZ1Click(UINT nID)
{
	int ID = nID - IDC_STC_TOP_Z1_0;

	CString strOld, strNew;
	m_stcTOPZ1[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TOP1_VISION_Z) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_TOP1_VISION_Z, ID, strNew)==FALSE) return;

	m_stcTOPZ1[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcTopZ1Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab3Dlg::OnStcTop1LightZClick(UINT nID)
{
	int ID = nID - IDC_STC_TOP1_LIGHT_Z_0;

	CString strOld, strNew;
	m_stcTOP1LightZ[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TOP1_LIGHT_Z) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_TOP1_LIGHT_Z, ID, strNew)==FALSE) return;

	m_stcTOP1LightZ[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcTop1LightZClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab3Dlg::OnStcTop1AngleYClick(UINT nID)
{
	int ID = nID - IDC_STC_TOP1_ANGLE_Y_0;

	CString strOld, strNew;
	m_stcTOP1AngleY[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TOP1_ANGLE_Y) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_TOP1_ANGLE_Y, ID, strNew)==FALSE) return;

	m_stcTOP1AngleY[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcTop1AngleYClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab3Dlg::OnStcTopZ2Click(UINT nID)
{
	int ID = nID - IDC_STC_TOP_Z2_0;

	CString strOld, strNew;
	m_stcTOPZ2[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_TOP2_VISION_Z) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_TOP2_VISION_Z, ID, strNew)==FALSE) return;

	m_stcTOPZ2[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcTopZ2Click - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

void CSetupMoveTab3Dlg::OnStcShipAlignXClick(UINT nID)
{
	int ID = nID - IDC_STC_SHIPALIGN_X_0;

	CString strOld, strNew;
	m_stcShipAlignX[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew, AX_SHIP_ALIGN_X) != IDOK) return;
	if (g_objCommon.Check_MoveData(AX_SHIP_ALIGN_X, ID, strNew)==FALSE) return;

	m_stcShipAlignX[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcShipAlignXClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab3Dlg::Initial_Controls() 
{
	for (int i =  0; i <  9; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i =  0; i < 44; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 5; i++) m_stcInspectionX1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 5; i++) m_stcInspectionX2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 5; i++) m_stcInspectionX3[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i = 0; i < 5; i++) m_stcInspectionX4[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));

	for (int i = 0; i < 5; i++) m_stcTOPZ1[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++) m_stcTOP1LightZ[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++) m_stcTOP1AngleY[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 5; i++) m_stcTOPZ2[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i < 4; i++) m_stcShipAlignX[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
}

void CSetupMoveTab3Dlg::Display_MoveData()
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	CString strData;
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dVisionStageX1[i]);	m_stcInspectionX1[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dVisionStageX2[i]);	m_stcInspectionX2[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dVisionStageX3[i]);	m_stcInspectionX3[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dVisionStageX4[i]);	m_stcInspectionX4[i].SetWindowText(strData); }

	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTOPVisionZ1[i]);	m_stcTOPZ1[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTop1LightZ[i]);	m_stcTOP1LightZ[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTop1AngleY[i]);	m_stcTOP1AngleY[i].SetWindowText(strData); }
	for (int i = 0; i < 5; i++) { strData.Format("%0.3lf", pMoveData->dTOPVisionZ2[i]);	m_stcTOPZ2[i].SetWindowText(strData); }
	for (int i = 0; i < 4; i++) { strData.Format("%0.3lf", pMoveData->dShiipAling[i]);	m_stcShipAlignX[i].SetWindowText(strData); }
}

void CSetupMoveTab3Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return;
	}

	g_objCommon.Backup_File(gsCurrentDir + "\\System", "MoveData");

	CString strKey, strData;
	double dData;

	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcInspectionX1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("26_INSPECT_STAGE_X1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcInspectionX2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("27_INSPECT_STAGE_X2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcInspectionX3[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("28_INSPECT_STAGE_X3", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcInspectionX4[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("29_INSPECT_STAGE_X4", strKey, dData, "%0.3lf"); }
	
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTOPZ1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("24_TOP1_VISION_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTOP1LightZ[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("43_TOP1_LIGHT_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTOP1AngleY[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("44_TOP1_ANGLE_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTOPZ2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("25_TOP2_VISION_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 4; i++) { strKey.Format("%02d", i);	m_stcShipAlignX[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("42_SHIP_ALIGN_X", strKey, dData, "%0.3lf"); }

//	Save_ModelMoveData();

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 3] save");

	Cancel_MoveData();
}

void CSetupMoveTab3Dlg::Save_ModelMoveData()
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

	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcInspectionX1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("26_INSPECT_STAGE_X1", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcInspectionX2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("27_INSPECT_STAGE_X2", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcInspectionX3[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("28_INSPECT_STAGE_X3", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcInspectionX4[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("29_INSPECT_STAGE_X4", strKey, dData, "%0.3lf"); }
	
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTOPZ1[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("24_TOP1_VISION_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTOP1LightZ[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("43_TOP1_LIGHT_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTOP1AngleY[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("44_TOP1_ANGLE_Y", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_stcTOPZ2[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("25_TOP2_VISION_Z", strKey, dData, "%0.3lf"); }
	for (int i = 0; i < 4; i++) { strKey.Format("%02d", i);	m_stcShipAlignX[i].GetWindowText(strData);	dData = atof(strData);	INI.Set_Double("42_SHIP_ALIGN_X", strKey, dData, "%0.3lf"); }

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 3] Model save");
}

void CSetupMoveTab3Dlg::Cancel_MoveData()
{
	g_objDataManager.Read_MoveData();

	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
