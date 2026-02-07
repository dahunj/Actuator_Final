// SetupMoveTab5Dlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "SetupMoveTab5Dlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "DataManager.h"
#include "Common.h"

#include "AJinDefine.h"

// CSetupMoveTab5Dlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSetupMoveTab5Dlg, CDialogEx)

CSetupMoveTab5Dlg::CSetupMoveTab5Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupMoveTab5Dlg::IDD, pParent)
{
}

CSetupMoveTab5Dlg::~CSetupMoveTab5Dlg()
{
}

void CSetupMoveTab5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 9; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 35; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 3; i++) DDX_Control(pDX, IDC_STC_VISION_OFFSET_0 + i, m_stcInfor[i]);
	for (int i = 0; i < 32; i++) DDX_Control(pDX, IDC_STC_STAGE_OFFSET_0 + i, m_stcOffset[i]);
}

BEGIN_MESSAGE_MAP(CSetupMoveTab5Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_STAGE_OFFSET_0, IDC_STC_STAGE_OFFSET_31, OnStcOffsetClick)
END_MESSAGE_MAP()

// CSetupMoveTab5Dlg 메시지 처리기입니다.

BOOL CSetupMoveTab5Dlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 5, 65, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CSetupMoveTab5Dlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CSetupMoveTab5Dlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (!bShow) return;

	Display_MoveData();

	g_objLogFile.Save_HandlerLog("[Setup Move] Show Window - Tab5");
}

void CSetupMoveTab5Dlg::OnStcOffsetClick(UINT nID)
{
	int ID = nID - IDC_STC_STAGE_OFFSET_0;

	CString strOld, strNew;
	m_stcOffset[ID].GetWindowText(strOld);
	if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;

	m_stcOffset[ID].SetWindowText(strNew);

	m_strLog.Format("[Setup - MoveTab Dialog] OnStcOffsetClick - Data(%d-%s)", ID, strNew);
	g_objLogFile.Save_HandlerLog(m_strLog);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CSetupMoveTab5Dlg::Initial_Controls() 
{
	for (int i = 0; i < 9; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i = 0; i <35; i++) m_Label[i].Init_Ctrl("바탕", 11, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i = 0; i < 3; i++) m_stcInfor[i].Init_Ctrl("바탕", 14, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
	for (int i = 0; i <32; i++) m_stcOffset[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xA0, 0xF0, 0xC0));
}

void CSetupMoveTab5Dlg::Display_MoveData()
{
	CString strData;

	for (int i = 0; i < 3; i++) { m_stcInfor[i].SetWindowText(gData.sOffsetInfor[i]); }

	int x = 0, y = 0;
	for (int i = 0; i < 16; i++) {
		strData.Format("%0.3lf", gData.dFocusOffset[x][y]);	m_stcOffset[i].SetWindowText(strData);
		y++;
		if (y == 4) { x++; y = 0; }
	}

	x = 0; y = 4;
	for (int i = 16; i < 32; i++) {
		strData.Format("%0.3lf", gData.dFocusOffset[x][y]);	m_stcOffset[i].SetWindowText(strData);
		y++;
		if (y == 8) { x++; y = 4; }
	}
}

void CSetupMoveTab5Dlg::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\VisionStageOffset.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("VisionStageOffset.ini File Not Found!!!");
		return;
	}

	if (g_objCommon.Read_FocusOffset() == FALSE) {
		g_objCommon.Show_MsgBox(1, "Vision Stage Offset 파일을 확인해 주세요.");
		return;
	}

	int nVNo = atoi(gData.sOffsetInfor[1]) + 1;
	gData.sOffsetInfor[1].Format("%d", nVNo);

	SYSTEMTIME time;
	GetLocalTime(&time);
	gData.sOffsetInfor[2].Format("%04d%02d%02d-%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	INI.Set_String("INFORMATION", "VERSION", gData.sOffsetInfor[1]);
	INI.Set_String("INFORMATION", "UPDATE",  gData.sOffsetInfor[2]);

	CString strKey, strApp, strData;
	double dData;

	int x = 0, y = 0;
	for (int i = 0; i < 16; i++) {
		strApp.Format("STAGE%d", x+1);		strKey.Format("%02d", y+1);
		m_stcOffset[i].GetWindowText(strData);	dData = atof(strData);
		INI.Set_Double(strApp, strKey, dData, "%0.3lf");

		y++;
		if (y == 4) { x++; y = 0; }
	}

	x = 0; y = 4;
	for (int i = 16; i < 32; i++) {
		strApp.Format("STAGE%d", x+1);		strKey.Format("%02d", y+1);
		m_stcOffset[i].GetWindowText(strData);	dData = atof(strData);
		INI.Set_Double(strApp, strKey, dData, "%0.3lf");

		y++;
		if (y == 8) { x++; y = 4; }
	}

	g_objLogFile.Save_HandlerLog("[Setup - MoveTab Dialog 5] save");
	Cancel_MoveData();
}

void CSetupMoveTab5Dlg::Cancel_MoveData()
{
	g_objCommon.Read_FocusOffset();
	Display_MoveData();
}

///////////////////////////////////////////////////////////////////////////////
