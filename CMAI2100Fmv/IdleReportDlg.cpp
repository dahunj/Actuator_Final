// IdleReportDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "IdleReportDlg.h"
#include "afxdialogex.h"

#include "LogFile.h"
#include "Common.h"
#include "DataManager.h"

// CIdleReportDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CIdleReportDlg, CDialogEx)

CIdleReportDlg::CIdleReportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIdleReportDlg::IDD, pParent)
{
}

CIdleReportDlg::~CIdleReportDlg()
{
}

void CIdleReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GROUP_0, m_Group);
	for (int i=0; i<8; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i=0; i<5; i++) DDX_Control(pDX, IDC_STC_START_HH_0 + i, m_stcSHH[i]);
	for (int i=0; i<5; i++) DDX_Control(pDX, IDC_STC_START_MM_0 + i, m_stcSMM[i]);
	for (int i=0; i<5; i++) DDX_Control(pDX, IDC_STC_START_SS_0 + i, m_stcSSS[i]);
	for (int i=0; i<5; i++) DDX_Control(pDX, IDC_STC_END_HH_0 + i, m_stcEHH[i]);
	for (int i=0; i<5; i++) DDX_Control(pDX, IDC_STC_END_MM_0 + i, m_stcEMM[i]);
	for (int i=0; i<5; i++) DDX_Control(pDX, IDC_STC_END_SS_0 + i, m_stcESS[i]);
	for (int i=0; i<5; i++) DDX_Control(pDX, IDC_STC_IDLE_TEXT_0 + i, m_stcText[i]);

	DDX_Control(pDX, IDC_LIST_IDLE_TEXT, m_lstIdleList);
	DDX_Control(pDX, IDC_BTN_OK, m_btnOK);
	DDX_Control(pDX, IDC_BTN_CANCEL, m_btnCancel);
}

BEGIN_MESSAGE_MAP(CIdleReportDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_CONTROL_RANGE(STN_CLICKED, IDC_STC_START_HH_0, IDC_STC_IDLE_TEXT_4, OnStcClick)
	ON_BN_CLICKED(IDC_BTN_OK, &CIdleReportDlg::OnBnClickedBtnOk)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CIdleReportDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()

// CIdleReportDlg 메시지 처리기입니다.

BOOL CIdleReportDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	Initial_Controls();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CIdleReportDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CIdleReportDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow) {
		Display_List();
	}
}

HBRUSH CIdleReportDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_DLG)
		return (HBRUSH)m_brushBack;

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void CIdleReportDlg::OnStcClick(UINT nID)
{
	int		ID, nData;
	CString strOld, strNew;;

	if (nID >= IDC_STC_START_HH_0 && nID <= IDC_STC_START_HH_4) {
		ID = nID - IDC_STC_START_HH_0;

		m_stcSHH[ID].GetWindowText(strOld);
		if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;
		nData = atoi(strNew);
		if (nData < 0 || nData > 23) {
			AfxMessageBox("Start Time(HH) Input Error......(0~23)");
			return;
		}

		m_stcSHH[ID].SetWindowText(strNew);
		return;
	}
	if (nID >= IDC_STC_START_MM_0 && nID <= IDC_STC_START_MM_4) {
		ID = nID - IDC_STC_START_MM_0;

		m_stcSMM[ID].GetWindowText(strOld);
		if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;
		nData = atoi(strNew);
		if (nData < 0 || nData > 59) {
			AfxMessageBox("Start Time(MM) Input Error......(0~59)");
			return;
		}

		m_stcSMM[ID].SetWindowText(strNew);
		return;
	}
	if (nID >= IDC_STC_START_SS_0 && nID <= IDC_STC_START_SS_4) {
		ID = nID - IDC_STC_START_SS_0;

		m_stcSSS[ID].GetWindowText(strOld);
		if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;
		nData = atoi(strNew);
		if (nData < 0 || nData > 59) {
			AfxMessageBox("Start Time(SS) Input Error......(0~59)");
			return;
		}

		m_stcSSS[ID].SetWindowText(strNew);
		return;
	}

	if (nID >= IDC_STC_END_HH_0 && nID <= IDC_STC_END_HH_4) {
		ID = nID - IDC_STC_END_HH_0;

		m_stcEHH[ID].GetWindowText(strOld);
		if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;
		nData = atoi(strNew);
		if (nData < 0 || nData > 23) {
			AfxMessageBox("End Time(HH) Input Error......(0~23)");
			return;
		}

		m_stcEHH[ID].SetWindowText(strNew);
		return;
	}
	if (nID >= IDC_STC_END_MM_0 && nID <= IDC_STC_END_MM_4) {
		ID = nID - IDC_STC_END_MM_0;

		m_stcEMM[ID].GetWindowText(strOld);
		if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;
		nData = atoi(strNew);
		if (nData < 0 || nData > 59) {
			AfxMessageBox("End Time(MM) Input Error......(0~59)");
			return;
		}

		m_stcEMM[ID].SetWindowText(strNew);
		return;
	}
	if (nID >= IDC_STC_END_SS_0 && nID <= IDC_STC_END_SS_4) {
		ID = nID - IDC_STC_END_SS_0;

		m_stcESS[ID].GetWindowText(strOld);
		if (g_objCommon.Show_NumPad(strOld, strNew) != IDOK) return;
		nData = atoi(strNew);
		if (nData < 0 || nData > 59) {
			AfxMessageBox("End Time(SS) Input Error......(0~59)");
			return;
		}

		m_stcESS[ID].SetWindowText(strNew);
		return;
	}

	if (nID >= IDC_STC_IDLE_TEXT_0 && nID <= IDC_STC_IDLE_TEXT_4) {
		IDLE_DATA *pIdleData = g_objDataManager.Get_pIdleData();
		ID = nID - IDC_STC_IDLE_TEXT_0;

		nData = m_lstIdleList.GetCurSel();
		if (nData < 0 || nData > pIdleData->nCount) {
			AfxMessageBox(" ==> Idle Code Select.............");
			return;
		}

		strNew.Format("%s,%s", pIdleData->sCode[nData], pIdleData->sText[nData]);
		m_stcText[ID].SetWindowText(strNew);
		return;
	}

	g_objLogFile.Save_HandlerLog("[Idle Report] STC Click.");
}

void CIdleReportDlg::OnBnClickedBtnOk()
{
	char chSep = ',';
	int	nCount, nSHH[5], nSMM[5], nSSS[5], nEHH[5], nEMM[5], nESS[5];
	CString sStime[5], sEtime[5], sCode[5], sText[5], sData;
	
	nCount = 0;
	for (int i=0; i<5; i++) {
		sStime[i] = sEtime[i] = sCode[i] = sText[i] = "";
	}

	CTime CurTime = CTime::GetCurrentTime();
	for (int i=0; i<5; i++) {
		m_stcSHH[i].GetWindowText(sData);	nSHH[i] = atoi(sData);
		m_stcSMM[i].GetWindowText(sData);	nSMM[i] = atoi(sData);
		m_stcSSS[i].GetWindowText(sData);	nSSS[i] = atoi(sData);
		m_stcEHH[i].GetWindowText(sData);	nEHH[i] = atoi(sData);
		m_stcEMM[i].GetWindowText(sData);	nEMM[i] = atoi(sData);
		m_stcESS[i].GetWindowText(sData);	nESS[i] = atoi(sData);
		m_stcText[i].GetWindowText(sData);

		AfxExtractSubString(sCode[i], sData, 0, chSep);
		AfxExtractSubString(sText[i], sData, 1, chSep);
		sStime[i].Format("%04d%02d%02d%02d%02d%02d", CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay(), nSHH[i], nSMM[i], nSSS[i]);
		sEtime[i].Format("%04d%02d%02d%02d%02d%02d", CurTime.GetYear(), CurTime.GetMonth(), CurTime.GetDay(), nEHH[i], nEMM[i], nESS[i]);

		if (sCode[i].GetLength() < 1) break;
		nCount++;
	}
	if (nCount < 1) {
		AfxMessageBox(" Input Time or Text Error......");
		return;
	}

	CTime DaySTime, DayETime;
	for(int i=0; i<nCount; i++) {
		DaySTime = CurTime - CTimeSpan(0, nSHH[i], nSMM[i], nSSS[i]);
		DayETime = CurTime - CTimeSpan(0, nEHH[i], nEMM[i], nESS[i]);
		if (DaySTime <= DayETime) {
			sData.Format(" No %d ==> Input Time Error......", i+1);
			AfxMessageBox(sData);
			return;
		}
	}

	if (nCount>2) nCount=2;
//	g_objMES.Set_IdleReport(gCM.sOperID, nCount, sStime[0], sEtime[0], sCode[0], sText[0], sStime[1], sEtime[1], sCode[1], sText[1]);
	EndDialog(IDCANCEL);

	g_objLogFile.Save_HandlerLog("[Idle Report] OK Button Click.");
}

void CIdleReportDlg::OnBnClickedBtnCancel()
{
	EndDialog(IDCANCEL);
	g_objLogFile.Save_HandlerLog("[Idle Report] Cancel Button Click.");
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CIdleReportDlg::Initial_Controls() 
{
	m_Group.Init_Ctrl("바탕", 14, TRUE, COLOR_DEFAULT, COLOR_DEFAULT);
	for (int i=0; i<8; i++) m_Label[i].Init_Ctrl("바탕", 8, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));

	for (int i=0; i<5; i++) m_stcSHH[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i=0; i<5; i++) m_stcSMM[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i=0; i<5; i++) m_stcSSS[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i=0; i<5; i++) m_stcEHH[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i=0; i<5; i++) m_stcEMM[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i=0; i<5; i++) m_stcESS[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));
	for (int i=0; i<5; i++) m_stcText[i].Init_Ctrl("바탕", 11, TRUE, COLOR_DEFAULT, RGB(0xFF, 0xEF, 0xD5));

	m_lstIdleList.Init_Ctrl("바탕", 14, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xF0, 0xF0, 0xFF));
	m_btnOK.Init_Ctrl("바탕", 14, TRUE, RGB(0xFF, 0x00, 0xFF), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnCancel.Init_Ctrl("바탕", 14, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT, IDI_CANCEL, CButtonCS::emLeft);
}

///////////////////////////////////////////////////////////////////////////////

void CIdleReportDlg::Display_List()
{
	CString sData;
	IDLE_DATA *pIdleData = g_objDataManager.Get_pIdleData();

	m_lstIdleList.ResetContent();

	for (int i=0; i<pIdleData->nCount; i++) {
		sData.Format("%d ==> %s : %s", (i+1), pIdleData->sCode[i], pIdleData->sText[i]);
		m_lstIdleList.AddString(sData);
	}
}
