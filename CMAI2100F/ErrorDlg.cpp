// ErrorDlg.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "ErrorDlg.h"
#include "afxdialogex.h"
#include "LogFile.h"
#include "Common.h"
#include "Inspector.h"
#include "Dispatcher.h"
#include "SequenceInit.h"
#include "SequenceMain.h"
#include "WorkDlg.h"
#include "CMAI2100Dlg.h"
#include "MesAgent.h"

// CErrorDlg 대화 상자입니다.
CErrorDlg g_dlgError;

IMPLEMENT_DYNAMIC(CErrorDlg, CDialogEx)

CErrorDlg::CErrorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CErrorDlg::IDD, pParent)
{
}

CErrorDlg::~CErrorDlg()
{
}

void CErrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_GROUP_0 + i, m_Group[i]);
	for (int i = 0; i < 8; i++) DDX_Control(pDX, IDC_LABEL_0 + i, m_Label[i]);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_STC_ERR_BACK_0 + i, m_stcErrBack[i]);
	DDX_Control(pDX, IDC_STC_ERR_TITLE, m_stcErrTitle);
	DDX_Control(pDX, IDC_IMAGE_0, m_Image);
	for (int i = 0; i < 4; i++) DDX_Control(pDX, IDC_LED_MAIN_AIR_0 + i, m_ledMainAir[i]);
	for (int i = 0; i < 6; i++) DDX_Control(pDX, IDC_LED_EMG_SW_0 + i, m_ledEmgSw[i]);
	for (int i = 0; i < 21; i++) DDX_Control(pDX, IDC_LED_DOOR_UNLOCK_0 + i, m_ledDoorUnlock[i]);
	for (int i = 0; i < 14; i++) DDX_Control(pDX, IDC_STC_ERR_POS_0 + i, m_stcErrPos[i]);
	DDX_Control(pDX, IDC_STC_ERR_NO, m_stcErrNo);
	DDX_Control(pDX, IDC_STC_MSG_BACK, m_stcMsgBack);
	DDX_Control(pDX, IDC_STC_ERR_MSG, m_stcErrMsg);
	DDX_Control(pDX, IDC_BTN_ERR_BUZZ_OFF, m_btnErrBuzzOff);
	DDX_Control(pDX, IDC_BTN_ERR_SKIP, m_btnErrSkip);
	DDX_Control(pDX, IDC_BTN_ERR_TO_SHIP_TRAY, m_btnErrToShipTray);
	DDX_Control(pDX, IDC_BTN_ERR_RETRY, m_btnErrRetry);
	DDX_Control(pDX, IDC_BTN_ERR_OK, m_btnErrOK);
	DDX_Control(pDX, IDC_BTN_ERR_SYSTEM_EXIT, m_btnErrSystemExit);
}

BEGIN_MESSAGE_MAP(CErrorDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ERR_BUZZ_OFF, &CErrorDlg::OnBnClickedBtnErrBuzzOff)
	ON_BN_CLICKED(IDC_BTN_ERR_SKIP, &CErrorDlg::OnBnClickedBtnErrSkip)
	ON_BN_CLICKED(IDC_BTN_ERR_RETRY, &CErrorDlg::OnBnClickedBtnErrRetry)
	ON_BN_CLICKED(IDC_BTN_ERR_TO_SHIP_TRAY, &CErrorDlg::OnBnClickedBtnErrToShipTray)
	ON_BN_CLICKED(IDC_BTN_ERR_OK, &CErrorDlg::OnBnClickedBtnErrOk)
	ON_BN_CLICKED(IDC_BTN_ERR_SYSTEM_EXIT, &CErrorDlg::OnBnClickedBtnErrSystemExit)
END_MESSAGE_MAP()

// CErrorDlg 메시지 처리기입니다.

BOOL CErrorDlg::OnInitDialog() 
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	Initial_Controls();

	m_nErrNo = 0;
	m_nBackColorLoop = 0;
	m_strErrSubMsg = "";

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

BOOL CErrorDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE))
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CErrorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	if (bShow) {
		if (gData.bAlarmShow) return;
		gData.bAlarmShow = TRUE;

		BringWindowToTop();				// 화면 위로...
		m_btnErrOK.EnableWindow(TRUE);	//2018.8.24+

		g_objCommon.Stop_Elevator();

		CString strErrNo, strErrMsg, strErrPick, strShow, strLog, strNo, strCMNo, strInfo;
		if (m_nErrNo == 3007) m_nErrNo = 9000;
		strErrNo.Format("%04d", m_nErrNo);
		m_stcErrNo.SetWindowText(strErrNo);
		
		if (gData.nLanguage == 0) strErrPick = gsCurrentDir + "\\System\\ErrorList_KOR.ini";
		else					  strErrPick = gsCurrentDir + "\\System\\ErrorList_ENG.ini";
		CIniFileCS INI(strErrPick);
		if (!INI.Check_File()) {
			AfxMessageBox("ErrorList.ini File Not Found!!!");
			return;
		}

		strErrMsg = INI.Get_String("ERROR", strErrNo, "");

		if (m_nErrNo <= 20) pMainDlg->Set_MainState(STATE_EMER);
		else				pMainDlg->Set_MainState(STATE_ALARM);

		strErrPick = strNo = strCMNo = "";
		if (m_nErrNo >= 5 && m_nErrNo <= 10) g_objCommon.Locking_MainDoor(FALSE);
		if (m_nErrNo == 4006 || m_nErrNo == 4506) strErrPick.Format(" #==> Recipe[%s]", gData.sReadyRecipe);
		if (m_nErrNo == 4019 || m_nErrNo == 4519) {
			strErrPick.Format(" #==> LotID[%s] 수량 [%d] != Align 수량 [%d].", gLot.sLotID[gAlm.nPortNo-1], gLot.nCmCount[gAlm.nPortNo-1], gLot.nAlignCount[gAlm.nPortNo-1]);
			gLot.nAlignCount[gAlm.nPortNo-1] = gLot.nAlignCount[gAlm.nPortNo-1] - gAlm.nAlignCount;
		}
		if (m_nErrNo == 5010 || m_nErrNo == 5017 || m_nErrNo == 5022) {
			for(int i=0; i<8; i++){
				if(gData.nLoadPicker1ErrNo[i] == 1) {	
					strNo.Format(" %d. ", i+1);
					strCMNo = strCMNo + strNo;
				}
			}
			strErrPick.Format(" #==> No. [%s] Load Picker 1에 모듈이 있는지 확인해 주시고 #    모듈이 있으면 센서 확인후 OK or Retry 버튼을 눌러 주세요.", strCMNo);
		}
		if (m_nErrNo == 5510 || m_nErrNo == 5517 || m_nErrNo == 5522) {
			for(int i=0; i<8; i++){
				if(gData.nLoadPicker2ErrNo[i] == 1) {	
					strNo.Format(" %d. ", i+1);
					strCMNo = strCMNo + strNo;
				}
			}
			strErrPick.Format(" #==> No. [%s] Load Picker 2에 모듈이 있는지 확인해 주시고 #    모듈이 있으면 센서 확인후 OK or Retry 버튼을 눌러 주세요.", strCMNo);
		}
		if (m_nErrNo == 5047 || m_nErrNo == 5056 || m_nErrNo == 5547 || m_nErrNo == 5556) {
			for(int i=0; i<8; i++){
				if(gData.nVisionVacErrNo[i] == 1) {	
					strNo.Format(" %d. ", i+1);
					strCMNo = strCMNo + strNo;
				}
			}
			strErrPick.Format(" #==> Stage[%d]  No. [%s] 진공 확인해 주세요.", gData.nVisionStageNo, strCMNo);
		}

		if (m_nErrNo == 7007) {
			for(int i=0; i<8; i++){
				if(gData.nUnloadPicker1ErrNo[i] == 1) {	
					strNo.Format(" %d. ", i+1);
					strCMNo = strCMNo + strNo;
				}
			}
			strErrPick.Format(" #==> No. [%s] Unload Picker 1에 모듈이 있는지 확인해 주시고 #    모듈이 있으면 센서 확인후 OK or Retry 버튼을 눌러 주세요.", strCMNo);
		}
		if (m_nErrNo == 7507) {
			for(int i=0; i<8; i++){
				if(gData.nUnloadPicker2ErrNo[i] == 1) {	
					strNo.Format(" %d. ", i+1);
					strCMNo = strCMNo + strNo;
				}
			}
			strErrPick.Format(" #==> No. [%s] Unload Picker 2에 모듈이 있는지 확인해 주시고 #    모듈이 있으면 센서 확인후 OK or Retry 버튼을 눌러 주세요.", strCMNo);
		}
		if (m_nErrNo == 7099 || m_nErrNo == 7599) strErrPick.Format(" #==> TrayNo[%d] Position[%d]", gMes.nMarTrayCount, gData.nNoReadNo);
		
		if (m_nErrNo == 5028 || m_nErrNo == 5034) strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[1], gAlm.nAlmTNo[1], gAlm.nAlmPNo[1]);
		if (m_nErrNo == 5528 || m_nErrNo == 5534) strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[1], gAlm.nAlmTNo[1], gAlm.nAlmPNo[1]);
		if (m_nErrNo == 6008 || m_nErrNo == 6012) strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[2], gAlm.nAlmTNo[2], gAlm.nAlmPNo[2]);
		if (m_nErrNo == 6018)					  strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[3], gAlm.nAlmTNo[3], gAlm.nAlmPNo[3]);
		if (m_nErrNo == 6208 || m_nErrNo == 6212) strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[2], gAlm.nAlmTNo[2], gAlm.nAlmPNo[2]);
		if (m_nErrNo == 6218)					  strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[3], gAlm.nAlmTNo[3], gAlm.nAlmPNo[3]);
		if (m_nErrNo == 6408 || m_nErrNo == 6412) strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[2], gAlm.nAlmTNo[2], gAlm.nAlmPNo[2]);
		if (m_nErrNo == 6418)					  strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[3], gAlm.nAlmTNo[3], gAlm.nAlmPNo[3]);
		if (m_nErrNo == 6608 || m_nErrNo == 6612) strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[2], gAlm.nAlmTNo[2], gAlm.nAlmPNo[2]);
		if (m_nErrNo == 6618)					  strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[3], gAlm.nAlmTNo[3], gAlm.nAlmPNo[3]);
		if (m_nErrNo == 7012 || m_nErrNo == 7512) strErrPick.Format(" #==> LotID[%s] TrayNo[%d] Module[%d]", gAlm.sAlmLID[0], gAlm.nAlmTNo[0], gAlm.nAlmPNo[0]);

		if (m_nErrNo ==  992) strErrPick.Format(" #==> Code [%s] #     Text [%s] #           [%s]", gAlm.sAlmLotID[0], gAlm.sAlmLotID[1], gAlm.sAlmLotID[2]);
		if (m_nErrNo ==  993) strErrPick.Format(" #==> LotID[%s] != MES LotID[%s]", gAlm.sAlmLotID[0], gAlm.sAlmLotID[1]);
		if (m_nErrNo ==  994) strErrPick.Format(" #==> Count[%s] != MES Count[%s]", gAlm.sAlmLotID[0], gAlm.sAlmLotID[1]);
		if (m_nErrNo == 9000) strErrPick.Format(" #==> MES 정상연결이 되어있으면 Port-No[%s]의 제품수량을 다시 입력해 주세요", gAlm.sAlmLotID[1]);
		if (m_nErrNo == 9001 || m_nErrNo == 9009 || m_nErrNo == 9010) strErrPick.Format(" #==> LotID[%s] Recipe[%s] Count[%s]", gMes.sHostCancelLotId, gMes.sHostCancelCode, gMes.sHostCancelText);
		if (m_nErrNo == 9002) strErrPick.Format(" #==> LotID[%s] Code[%s] #   Text[%s]", gMes.sHostCancelLotId, gMes.sHostCancelCode, gMes.sHostCancelText);
		if (m_nErrNo == 9005) strErrPick.Format(" #==> LotID[%s] Module[%s] #   Code[%s] #   Text[%s]", gMes.sHostCancelLotId, gMes.sHostCancelModule, gMes.sHostCancelCode, gMes.sHostCancelText);
		if (m_nErrNo == 9007) strErrPick.Format(" #==> LotID[%s] Recipe[%s]", gMes.sHostCancelLotId, gMes.sHostCancelCode);
		if (m_nErrNo == 9008) strErrPick.Format(" #==> MES_Recipe[%s] != Equip Recipe[%s]", gMes.sHostCancelCode, gData.sRecipeName);
		if (m_nErrNo == 9022 || m_nErrNo == 9023) strErrPick.Format(" #==> LotID[%s]", gMes.sHostCancelLotId);
		if (m_nErrNo == 9117) strErrPick.Format(" #==> Run Config[%s] != New Config[%s]", gMes.sHostNGConfig, gMes.sMESConfig);
		if (m_nErrNo == 9180) strErrPick.Format(" #[%s]비전 PC에서 Groval Align Fail이 발생하였습니다.#제품 Loading 상태를 확인해 주세요.", gAlm.sAlmLotID[1]);
		if (m_nErrNo > 9200 && m_nErrNo < 9210) strErrPick.Format(" #==> [%s]비전에서 발생하였습니다.", gAlm.sAlmLotID[1]);
		if (m_nErrNo == 9211) strErrPick.Format(" #==> Barcode [%s] PortNo[%d] TrayNo[%d] Position[%d]", gAlm.sAlmLotID[1], gAlm.nTempPNo, gAlm.nTempTNo, gAlm.nTempMNo);
		
		// 로더/언로더 피커에서 버큠실패, 검사완료 실패, Laser Check
//		if (m_nErrNo == 5010 || m_nErrNo == 5017 || m_nErrNo == 5022 || m_nErrNo == 5047 || m_nErrNo == 5056 ||
//			m_nErrNo == 5510 || m_nErrNo == 5517 || m_nErrNo == 5522 || m_nErrNo == 5547 || m_nErrNo == 5556 ||
		if (m_nErrNo == 7012 || m_nErrNo == 7512) {
			m_btnErrSkip.EnableWindow(TRUE);
		} else {
			m_btnErrSkip.EnableWindow(FALSE);
		}
		if (m_nErrNo == 4014 || m_nErrNo == 4016 || m_nErrNo == 4018 || m_nErrNo == 4019 || m_nErrNo == 4514 || m_nErrNo == 4516 || m_nErrNo == 4518 ||  m_nErrNo == 4519 || 
			m_nErrNo == 5010 || m_nErrNo == 5017 || m_nErrNo == 5028 || m_nErrNo == 5034 ||
			m_nErrNo == 5510 || m_nErrNo == 5517 || m_nErrNo == 5528 || m_nErrNo == 5534 ||
			m_nErrNo == 6008 || m_nErrNo == 6012 || m_nErrNo == 6018 || m_nErrNo == 6208 || m_nErrNo == 6212 || m_nErrNo == 6218 ||
			m_nErrNo == 6408 || m_nErrNo == 6412 || m_nErrNo == 6418 || m_nErrNo == 6608 || m_nErrNo == 6612 || m_nErrNo == 6618 ||
			m_nErrNo == 7007 || m_nErrNo == 7507 ||
			m_nErrNo == 8804 || m_nErrNo == 8806 || m_nErrNo == 8808) {
			m_btnErrRetry.EnableWindow(TRUE);
		} else {
			m_btnErrRetry.EnableWindow(FALSE);
		}

		m_strErrMsg = strErrMsg + strErrPick + m_strErrSubMsg;

		strShow = m_strErrMsg;
		if (strShow.Left(1) == "#") strShow.Delete(0);
		strShow.Replace("#", "\n\n");
		m_stcErrMsg.SetWindowText(strShow);

		SYSTEMTIME time;
		GetLocalTime(&time);
		for (int i = 2; i > 0; i--) gData.sAlarmTime[i] = gData.sAlarmTime[i - 1];
		for (int i = 2; i > 0; i--) gData.sAlarmList[i] = gData.sAlarmList[i - 1];
		gData.sAlarmTime[0].Format("%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
		gData.sAlarmList[0].Format("[%s] %s", strErrNo, m_strErrMsg);

		g_objMesAgent.Set_ErrorUpdate(1, strErrNo);
		Set_SPCError(m_nErrNo, m_strErrMsg);
		Set_AlarmLog(m_nErrNo, m_strErrMsg);
		strLog.Format("%s,%s,%s", m_strLotID, strErrNo, m_strErrMsg);
		g_objLogFile.Save_AlarmLog(strLog);	g_objLogFile.Save_AlarmECMLog(0, strLog);

		int *pCase = g_objSequenceMain.Get_pMainRunCase();
		strLog.Format("[Error Mode] ErrorNo:%s SeqNo:%d-%d-%d-%d-%d  %d-%d-%d-%d-%d  %d-%d-%d-%d-%d  %d-%d-%d-%d-%d  %d-%d-%d-%d Version(%s)", strErrNo,
									*(pCase+0), *(pCase+1), *(pCase+2), *(pCase+3), *(pCase+4),
									*(pCase+5), *(pCase+6), *(pCase+7), *(pCase+8), *(pCase+9),
									*(pCase+10), *(pCase+11), *(pCase+12), *(pCase+13), *(pCase+14),
									*(pCase+15), *(pCase+16), *(pCase+17), *(pCase+18), *(pCase+19),
									*(pCase+20), *(pCase+21), *(pCase+22), *(pCase+23), MAIN_VERSION);
		g_objLogFile.Save_HandlerLog(strLog);

		m_nBackColorLoop = 0;
		int nErrorPos;
		if		(m_nErrNo > 2000 && m_nErrNo < 3000) nErrorPos =  1;	//  1.Run_Elevator1();	
		else if (m_nErrNo > 3000 && m_nErrNo < 3500) nErrorPos =  2;	//  2.Run_Transfer1();	
		else if (m_nErrNo > 3500 && m_nErrNo < 4000) nErrorPos = 11;	//  3.Run_Transfer2();	
		else if (m_nErrNo > 4000 && m_nErrNo < 5000) nErrorPos =  3;	//  4.Run_LoadStage1();	
		else if (m_nErrNo > 5000 && m_nErrNo < 6000) nErrorPos =  4;	//  5.Run_LoadPicker1();	
		else if (m_nErrNo > 6000 && m_nErrNo < 7000) nErrorPos =  5;	//  6.Run_VisionStage1();		
		else if (m_nErrNo > 7000 && m_nErrNo < 8000) nErrorPos =  6;	//  7.Run_UnloadPicker1();		
		else if (m_nErrNo > 8000 && m_nErrNo < 8400) nErrorPos =  7;	//  8.Run_NGStage1();		
		else if (m_nErrNo > 8400 && m_nErrNo < 8800) nErrorPos =  8;	//  9.Run_GoodStage1();
		else if (m_nErrNo > 8800 && m_nErrNo < 9000) nErrorPos =  9;	// 10.Run_ShipAlign();		
		else if (m_nErrNo > 9000 && m_nErrNo < 9999) nErrorPos = 10;	// 13.검사
		else nErrorPos = 0;
		m_stcErrPos[nErrorPos].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0xFF, 0x00, 0x00));
		
 		g_objInspector.Set_StatusUpdate(INSPECTOR_ALL, 4);
		g_objDispatcher.Set_StatusUpdate(2);	// 0:Stop, 1:Run, 2:Error
		SetTimer(0, 100, NULL);
		
	} else {
		KillTimer(0);

		m_strErrSubMsg = "";
		for (int i = 0; i < 14; i++) m_stcErrPos[i].Set_Color(RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));
		pMainDlg->Set_MainState(STATE_INITEND);
//		g_objMES.Set_Alarm(2, m_nErrNo, m_strErrMsg);
		gData.bAlarmShow = FALSE;
		g_objLogFile.Save_HandlerLog("[Error Mode] Close Error");

		g_objLogFile.Save_EfficiencyLog(m_strLotID, "Reset", m_strTitle, 905, "Error Reset");
		m_bErrShow = FALSE;
	}
}

void CErrorDlg::OnTimer(UINT_PTR nIDEvent) 
{
	KillTimer(0);

	DX_DATA_13 *pDX13 = g_objAJinAXL.Get_pDX13();
	DX_DATA_14 *pDX14 = g_objAJinAXL.Get_pDX14();

	if (pDX13->iResetSw) {
		//Retray 그립 알람때는 창을 닫지 않는다.
		if (m_nErrNo == 5010 || m_nErrNo == 5017 || m_nErrNo == 5510 || m_nErrNo == 5517 ||
			m_nErrNo == 7007 || m_nErrNo == 7507) { OnBnClickedBtnErrBuzzOff(); return; } 
		OnBnClickedBtnErrOk();
		return;
	}

	if (m_nBackColorLoop == 1) {
		for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0x00, 0x00, 0xFF));
	} else if (m_nBackColorLoop == 6) {
		for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0xFF, 0xFF, 0x00));
	} else if (m_nBackColorLoop == 10) m_nBackColorLoop = 0;
	m_nBackColorLoop++;

	m_ledMainAir[0].Set_On(pDX13->iMainAir1);
	m_ledMainAir[1].Set_On(pDX13->iMainAir2);
	m_ledMainAir[2].Set_On(pDX13->iMainAir3);

	m_ledEmgSw[0].Set_On(pDX13->iEmgSw1);
	m_ledEmgSw[1].Set_On(pDX13->iEmgSw2);
	m_ledEmgSw[2].Set_On(pDX13->iEmgSw3);
	m_ledEmgSw[3].Set_On(pDX13->iEmgSw4);
	m_ledEmgSw[4].Set_On(pDX13->iEmgSw5);
	m_ledEmgSw[5].Set_On(pDX13->iEmgSw6);

	for (int i = 0; i < 21; i++) m_ledDoorUnlock[i].Set_On((pDX14->nValue >> (i + 0)) & 1);

	SetTimer(0, 100, NULL);
	CDialogEx::OnTimer(nIDEvent);
}

void CErrorDlg::OnBnClickedBtnErrBuzzOff()
{
	g_objCommon.BuzzerOff();
}

void CErrorDlg::OnBnClickedBtnErrSkip()
{
	if (g_objCommon.Show_MsgBox(2, "Module Skip 처리를 하시겠습니까?") != IDOK) return;

	int nPNo=0, nSkipCount=0;
	switch (m_nErrNo) {
	case 5010:	// Load Picker1 Check Err
	case 5017:
	case 5022:
		for(int i=0; i<8; i++){
			if(gData.nLoadPicker1ErrNo[i]==1) {
				gData.InfoLoadPick[0][i] = 0;
				nPNo = gData.nPortNo_LoadPicker[0];
				gLot.nSkipCount[nPNo-1]++; nSkipCount++;
			}
			gData.nLoadPicker1ErrNo[i] = 0;	//clear
		}
		break;
	case 5047:	// Load Picker1 Vacuum Err
	case 5056:
		for(int i=0; i<8; i++){
			if(gData.nVisionVacErrNo[i]==1) {
				gData.InfoVision[gData.nVisionNo-1][i] = 0;
				nPNo = gData.nPortNo_VisionStage[gData.nVisionNo-1];
				gLot.nSkipCount[nPNo-1]++; nSkipCount++;
			}
			gData.nVisionVacErrNo[i] = 0;	//clear
		}
		break;

	case 5510:	// Load Picker2 Check Err
	case 5517:
	case 5522:
		for(int i=0; i<8; i++){
			if(gData.nLoadPicker2ErrNo[i]==1) {
				gData.InfoLoadPick[1][i] = 0;
				nPNo = gData.nPortNo_LoadPicker[1];
				gLot.nSkipCount[nPNo-1]++; nSkipCount++;
			}
			gData.nLoadPicker2ErrNo[i] = 0;	//clear
		}
		break;
	case 5547:	// Load Picker2 Vacuum Err
	case 5556:
		for(int i=0; i<8; i++){
			if(gData.nVisionVacErrNo[i]==1) {
				gData.InfoVision[gData.nVisionNo-1][i] = 0;
				nPNo = gData.nPortNo_VisionStage[gData.nVisionNo-1];
				gLot.nSkipCount[nPNo-1]++; nSkipCount++;
			}
			gData.nVisionVacErrNo[i] = 0;	//clear
		}
		break;

	case 7012:	// 검사미완료 Err
			g_objSequenceMain.Set_ReInspectDone(1, gData.nPortNo_UnloadPicker[0], gData.nTrayNo_UnloadPicker[0]);
		break;
	case 7512:	// 검사미완료 Err
			g_objSequenceMain.Set_ReInspectDone(2, gData.nPortNo_UnloadPicker[1], gData.nTrayNo_UnloadPicker[1]);
		break;
		
	}

	CString sLog;
	sLog.Format("[Error Mode] SKIP button push.. ErrNo[%d] Skip[%d] PortNo[%d]", m_nErrNo, nSkipCount, nPNo);
	g_objLogFile.Save_HandlerLog(sLog);

 	ShowWindow(SW_HIDE);
}

void CErrorDlg::OnBnClickedBtnErrRetry()
{
	g_objLogFile.Save_HandlerLog("[Error Mode] RETRY button push");

	switch (m_nErrNo) {
	case 4014:	// Load Stage1 Align Err
	case 4016:
	case 4018:
	case 4019:
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_1, 10);
		break;
	case 4514:	// Load Stage2 Align Err
	case 4516:
	case 4518:
	case 4519:
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_2, 10);
		break;

	case 5010:	// Load Picker1 Check Err
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_PICKER_1, 81);
		break;
	case 5017:	// Load Picker1 Check Err
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_PICKER_1, 85);
		break;
	case 5028:	// Load Picker1 Bottom Err
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_PICKER_1, 26); gData.nScanRetry[0] = 1;
		break;
	case 5034:	// Load Picker1 Bottom Err
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_PICKER_1, 32); gData.nScanRetry[0] = 1;
		break;

	case 5510:	// Load Picker2 Check Err
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_PICKER_2, 81);
		break;
	case 5517:	// Load Picker2 Check Err
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_PICKER_2, 85);
		break;
	case 5528:	// Load Picker2 Bottom Err
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_PICKER_2, 26); gData.nScanRetry[0] = 1;
		break;
	case 5534:	// Load Picker2 Bottom Err
		g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_PICKER_2, 32); gData.nScanRetry[0] = 1;
		break;

	case 6008:	// Vision1 Top1 Err
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_1, 6); gData.nScanRetry[1] = 1;
		break;
	case 6012:
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_1, 10); gData.nScanRetry[1] = 1;
		break;
	case 6018:
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_1, 16); gData.nScanRetry[2] = 1;
		break;
	case 6208:	// Vision2 Top1 Err
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_2, 6); gData.nScanRetry[1] = 1;
		break;
	case 6212:
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_2, 10); gData.nScanRetry[1] = 1;
		break;
	case 6218:
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_2, 16); gData.nScanRetry[2] = 1;
		break;
	case 6408:	// Vision3 Top1 Err
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_3, 6); gData.nScanRetry[1] = 1;
		break;
	case 6412:
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_3, 10); gData.nScanRetry[1] = 1;
		break;
	case 6418:
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_3, 16); gData.nScanRetry[2] = 1;
		break;
	case 6608:	// Vision4 Top1 Err
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_4, 6); gData.nScanRetry[1] = 1;
		break;
	case 6612:
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_4, 10); gData.nScanRetry[1] = 1;
		break;
	case 6618:
		g_objSequenceMain.Set_MainRunCase(AUTO_VISION_STAGE_4, 16); gData.nScanRetry[2] = 1;
		break;

	case 7007:	// UnLoad Picker1 Check Err
		g_objSequenceMain.Set_MainRunCase(AUTO_UNLOAD_PICKER_1, 81);
		break;
	case 7507:	// UnLoad Picker2 Check Err
		g_objSequenceMain.Set_MainRunCase(AUTO_UNLOAD_PICKER_2, 81);
		break;

	case 8804:	// Ship Align Err
	case 8806:
	case 8808:
		g_objSequenceMain.Set_MainRunCase(AUTO_SHIP_ALIGN, 1);
		break;

	}

	ShowWindow(SW_HIDE);
}

void CErrorDlg::OnBnClickedBtnErrOk()
{
	CString sLog;
	if (m_nErrNo==81) gData.dwSlideTime[0] = 0;
	if (m_nErrNo==82) gData.dwSlideTime[1] = 0;
	if (m_nErrNo==83) gData.dwSlideTime[2] = 0;
	if (m_nErrNo==84) gData.dwSlideTime[3] = 0;
	if (m_nErrNo==85) gData.dwSlideTime[4] = 0;
	if (m_nErrNo==86) gData.dwSlideTime[5] = 0;
	if (m_nErrNo==87) gData.dwSlideTime[6] = 0;

	if (m_nErrNo == 2118 || m_nErrNo == 2218 || m_nErrNo == 2318 || m_nErrNo == 2418 || m_nErrNo == 2518 || m_nErrNo == 2618 || m_nErrNo == 2718) {
		int nENo = 1;
		if (m_nErrNo == 2118) { nENo = 1; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_1, 51); }
		if (m_nErrNo == 2218) { nENo = 2; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_2, 51); }
		if (m_nErrNo == 2318) { nENo = 3; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_3, 51); }
		if (m_nErrNo == 2418) { nENo = 4; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_4, 51); }
		if (m_nErrNo == 2518) { nENo = 5; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_5, 51); }
		if (m_nErrNo == 2618) { nENo = 6; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_6, 51); }
		if (m_nErrNo == 2718) { nENo = 7; g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_7, 51); }

		sLog.Format("Check_ElevatorSearch No[%d] Fm[%0.3lf] To[%0.3lf]", nENo, gData.dElevatorZPos[0][nENo-1], gData.dElevatorZPos[1][nENo-1]);
		g_objLogFile.Save_HandlerLog(sLog);
	}

	if (m_nErrNo == 4006) g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_1, 5);
	if (m_nErrNo == 4506) g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_2, 5);
	if (m_nErrNo >= 4014 && m_nErrNo <= 4019) g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_1, 10);
	if (m_nErrNo >= 4514 && m_nErrNo <= 4519) g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_2, 10);
	if (m_nErrNo == 7016) g_objSequenceMain.Set_MainRunCase(AUTO_UNLOAD_PICKER_1, 14);
	if (m_nErrNo == 7516) g_objSequenceMain.Set_MainRunCase(AUTO_UNLOAD_PICKER_2, 14);

	if (m_nErrNo == 9121 || m_nErrNo == 9122) { 
		int nCase1 = g_objSequenceMain.Get_MainRunCase(AUTO_LOAD_STAGE_1);
		int nCase2 = g_objSequenceMain.Get_MainRunCase(AUTO_LOAD_STAGE_2);
		if (nCase1 > 10 && nCase1 < 20) g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_1, 10);
		if (nCase2 > 10 && nCase2 < 20) g_objSequenceMain.Set_MainRunCase(AUTO_LOAD_STAGE_2, 10);
	}
	if (m_nErrNo >= 8801 && m_nErrNo < 8810) g_objSequenceMain.Set_MainRunCase(AUTO_SHIP_ALIGN, 1);

	if (m_nErrNo == 9131 || m_nErrNo == 9132 || m_nErrNo == 3594) {
		g_objMesAgent.Set_LotEnd(gLot.nUnLastPortID, gLot.sUnLastLotID, "0", "0", "0", "0", "0");
		gData.bInpectLotEnd = TRUE;
	}
	if (m_nErrNo == 9024) { 
		int nCase1 = g_objSequenceMain.Get_MainRunCase(AUTO_UNLOAD_PICKER_1);
		int nCase2 = g_objSequenceMain.Get_MainRunCase(AUTO_UNLOAD_PICKER_2);
		if (nCase1 > 14 && nCase1 < 20) g_objSequenceMain.Set_MainRunCase(AUTO_UNLOAD_PICKER_1, 14);
		if (nCase2 > 14 && nCase2 < 20) g_objSequenceMain.Set_MainRunCase(AUTO_UNLOAD_PICKER_2, 14);
	}

/*	if ((m_nErrNo >= 9000 && m_nErrNo <= 9002) || (m_nErrNo >= 9007 && m_nErrNo <= 9008)) {
		if (gMes.nLotPortNo > 0 && gMes.nLotPortNo < 7) gMes.nLotStatus[gMes.nLotPortNo-1] = 0;
		g_objSequenceMain.Set_MainRunCase(AUTO_TRANSFER_1, 0);
		g_objCommon.Set_LotDataClear(gMes.nLotPortNo-1);
	}
*/
	g_objLogFile.Save_HandlerLog("[Error Mode] OK button push");
	ShowWindow(SW_HIDE);
}

void CErrorDlg::OnBnClickedBtnErrToShipTray()
{
	//사용안함
	g_objLogFile.Save_HandlerLog("[Error Mode] To Ship Tray button push");
	ShowWindow(SW_HIDE);
//	g_dlgWork.Set_AutoRun(TRUE);
}

void CErrorDlg::OnBnClickedBtnErrSystemExit()
{
	if (gData.nLanguage == 0) {
		if (g_objCommon.Show_MsgBox(2, "프로그램을 종료 하시겠습니까?") != IDOK) return;
	} else {
		if (g_objCommon.Show_MsgBox(2, "Do you want to exit the program?") != IDOK) return;
	}
}

void CErrorDlg::Set_AlarmLog(int nErrNo, CString sErrMsg)
{
	SYSTEMTIME time;

	gAlm.bBegin = TRUE;
	gAlm.nAlmNo = nErrNo;
	gAlm.sAlmMsg = sErrMsg;
	GetLocalTime(&time);
	gAlm.dwStartTime = GetTickCount();
	gAlm.sStartTime.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	gAlm.sLotID   = m_strLotID;
	gAlm.nPortNo  = m_nPortNo;
	gAlm.sSpcInfo = m_strsSpcInfo;
}

void CErrorDlg::ErrorTimeEdit()
{
	long lSTime, lETime, lTTime, laTime, lmax;
	if(m_nErrNo > 9900 || (m_nErrNo > 10 && m_nErrNo < 30) || (m_nErrNo > 1100 && m_nErrNo < 2000)) return;

	lmax = 4294960000;
	CIniFileCS Ini_LotData("System/LotData.ini");
	lSTime = Ini_LotData.Get_Long("TOTAL_DATA", "ERROR_STIME", 0);
	lTTime = Ini_LotData.Get_Long("TOTAL_DATA", "ERROR_MTIME", 0);

	lETime = GetTickCount();
	if(lETime >= lSTime) {
		laTime = lETime - lSTime;
	} else {
		laTime = lETime + (lmax - lSTime);
	}
	if (laTime < 1) return;

	if (lTTime <= 0) lTTime = laTime;
	else			 lTTime = (lTTime + laTime) / 2;

	Ini_LotData.Set_Long("TOTAL_DATA", "ERROR_STIME", lETime);
	Ini_LotData.Set_Long("TOTAL_DATA", "ERROR_MTIME", lTTime);
}

///////////////////////////////////////////////////////////////////////////////
// User Functions

void CErrorDlg::Initial_Controls() 
{
	for (int i = 0; i < 4; i++) m_Group[i].Init_Ctrl("바탕", 12, TRUE, RGB(0x00, 0x00, 0xFF), COLOR_DEFAULT);
	for (int i = 0; i < 8; i++) m_Label[i].Init_Ctrl("바탕", 20, TRUE, RGB(0xFF, 0xFF, 0xFF), RGB(0x60, 0x60, 0x60));
	for (int i = 0; i < 4; i++) m_stcErrBack[i].Set_Color(COLOR_DEFAULT, RGB(0x00, 0x00, 0xFF));

	m_stcErrTitle.Init_Ctrl("바탕", 24, TRUE, RGB(0xFF, 0xFF, 0xFF),RGB(0xFF, 0x00, 0x00));

	m_bmpImage.LoadBitmap(IDB_EQUIP_ERROR);
	m_Image.SetBitmap(m_bmpImage);
// 	m_Image.SetWindowPos(NULL, 0, 0, 1060, 600, SWP_NOZORDER | SWP_NOMOVE);	// 원본 960x540 (1680x945)
	m_Image.SetWindowPos(NULL, 0, 0, 1100, 620, SWP_NOZORDER | SWP_NOMOVE);	// 640x360 : 원본 960x540 (1680x945)

	for (int i = 0; i < 4; i++) m_ledMainAir[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em24);
	for (int i = 0; i < 6; i++) m_ledEmgSw[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emRed, CLedCS::em24);
	for (int i = 0; i < 21; i++) m_ledDoorUnlock[i].Init_Ctrl("바탕", 11, FALSE, COLOR_DEFAULT, COLOR_DEFAULT, CLedCS::emGreen, CLedCS::em24);

	for (int i = 0; i < 14; i++) m_stcErrPos[i].Init_Ctrl("바탕", 12, FALSE, RGB(0xFF, 0xFF, 0xFF), RGB(0x00, 0x00, 0x00));

	m_stcErrNo.Init_Ctrl("바탕", 30, TRUE, RGB(0x00, 0x00, 0xFF), RGB(0xFF, 0xF0, 0xE0));
	m_stcMsgBack.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE0, 0xF0, 0xF0));
	m_stcErrMsg.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), RGB(0xE0, 0xF0, 0xF0));

	m_btnErrBuzzOff.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrSkip.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrRetry.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrToShipTray.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
	m_btnErrOK.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, IDI_OK, CButtonCS::emLeft);
	m_btnErrSystemExit.Init_Ctrl("바탕", 16, TRUE, RGB(0x00, 0x00, 0x00), COLOR_DEFAULT, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////

void CErrorDlg::Set_SPCError(int nErrNo, CString sErrMsg)
{
	int nModuleCount = 0;
	CString strTemp, strTitle, strLotId, strBarcode, strPort, strTray, strCm, strLog;
	strTemp = strLotId = strBarcode = strPort = strTray = strCm = "";

	gAlm.sUnit = strTitle = "Common";
	if (nErrNo > 2100 && nErrNo < 2200) strTitle = "Elevator_1";
	if (nErrNo > 2200 && nErrNo < 2300) strTitle = "Elevator_2";
	if (nErrNo > 2300 && nErrNo < 2400) strTitle = "Elevator_3";
	if (nErrNo > 2400 && nErrNo < 2500) strTitle = "Elevator_4";
	if (nErrNo > 2500 && nErrNo < 2600) strTitle = "Elevator_5";
	if (nErrNo > 2600 && nErrNo < 2700) strTitle = "Elevator_6";
	if (nErrNo > 2700 && nErrNo < 2800) strTitle = "Elevator_7";
	if (nErrNo > 3000 && nErrNo < 3500) strTitle = "Transfer_1";
	if (nErrNo > 3500 && nErrNo < 4000) strTitle = "Transfer_2";
	if (nErrNo > 4000 && nErrNo < 4500) strTitle = "LoadStage_1";
	if (nErrNo > 4500 && nErrNo < 5000) strTitle = "LoadStage_2";

	if (nErrNo > 5000 && nErrNo < 5500) {
		strTitle = "LoadPicker_1";
		int nNo = gData.InfoLoadPick[0][9];
		if (nNo > 0) {
			for (int i = 0; i < 8; i++) {
				if (gData.InfoLoadPick[0][i] > 0) {
					strTemp.Format("%d;", gData.nPortNo_LoadPicker[0]); strPort += strTemp;
					strTemp.Format("%d;", gData.nTrayNo_LoadPicker[0]); strTray += strTemp;
					strTemp.Format("%d;", nNo+i);						strCm += strTemp;
					strTemp.Format(";");								strBarcode += strTemp;
					nModuleCount++;
				}
			}
		}
	}
	if (nErrNo > 5500 && nErrNo < 6000) {
		strTitle = "LoadPicker_2";
		int nNo = gData.InfoLoadPick[1][9];
		if (nNo > 0) {
			for (int i = 0; i < 8; i++) {
				if (gData.InfoLoadPick[1][i] > 0) {
					strTemp.Format("%d;", gData.nPortNo_LoadPicker[1]); strPort += strTemp;
					strTemp.Format("%d;", gData.nTrayNo_LoadPicker[1]); strTray += strTemp;
					strTemp.Format("%d;", nNo+i);						strCm += strTemp;
					strTemp.Format(";");								strBarcode += strTemp;
					nModuleCount++;
				}
			}
		}
	}
	if (nErrNo > 6000 && nErrNo < 7000) {
		int nX = 0;
		if (nErrNo > 6000 && nErrNo < 6200) { strTitle = "InspectStage_1"; nX = 0; }
		if (nErrNo > 6200 && nErrNo < 6400) { strTitle = "InspectStage_2"; nX = 1; }
		if (nErrNo > 6400 && nErrNo < 6600) { strTitle = "InspectStage_3"; nX = 2; }
		if (nErrNo > 6600 && nErrNo < 7000) { strTitle = "InspectStage_4"; nX = 3; }

		int nNo = gData.InfoVision[nX][9];
		if (nNo > 0) {
			for (int i = 0; i < 8; i++) {
				if (gData.InfoVision[nX][i] > 0) {
					strTemp.Format("%d;", gData.nPortNo_VisionStage[nX]); strPort += strTemp;
					strTemp.Format("%d;", gData.nTrayNo_VisionStage[nX]); strTray += strTemp;
					strTemp.Format("%d;", nNo+i);						  strCm += strTemp;
					strTemp.Format(";");								  strBarcode += strTemp;
					nModuleCount++;
				} 
			}
		}
	}
	if (nErrNo > 7000 && nErrNo < 7500) {
		strTitle = "UnloadPicker_1";
		int nNo = gData.InfoUnloadPick[0][9];
		if (nNo > 0) {
			for (int i = 0; i < 8; i++) {
				if (gData.InfoUnloadPick[0][i] > 0) {
					strTemp.Format("%d;", gData.nPortNo_UnloadPicker[0]); strPort += strTemp;
					strTemp.Format("%d;", gData.nTrayNo_UnloadPicker[0]); strTray += strTemp;
					strTemp.Format("%d;", nNo+i);						  strCm += strTemp;
					strTemp.Format("%s;", gLot.sBarCode[gData.nPortNo_UnloadPicker[0]-1][gData.nTrayNo_UnloadPicker[0]-1][nNo+i-1]); strBarcode += strTemp;
					nModuleCount++;
				}
			}
		}
	}
	if (nErrNo > 7500 && nErrNo < 8000) {
		strTitle = "UnloadPicker_2";
		int nNo = gData.InfoUnloadPick[1][9];
		if (nNo > 0) {
			for (int i = 0; i < 8; i++) {
				if (gData.InfoUnloadPick[1][i] > 0) {
					strTemp.Format("%d;", gData.nPortNo_UnloadPicker[1]); strPort += strTemp;
					strTemp.Format("%d;", gData.nTrayNo_UnloadPicker[1]); strTray += strTemp;
					strTemp.Format("%d;", nNo+i);						  strCm += strTemp;
					strTemp.Format("%s;", gLot.sBarCode[gData.nPortNo_UnloadPicker[1]-1][gData.nTrayNo_UnloadPicker[1]-1][nNo+i-1]); strBarcode += strTemp;
					nModuleCount++;
				}
			}
		}
	}

	if (nErrNo > 8000 && nErrNo < 8200) strTitle = "NGStage_1";
	if (nErrNo > 8200 && nErrNo < 8400) strTitle = "NGStage_1";
	if (nErrNo > 8400 && nErrNo < 8600) strTitle = "GoodStage_1";
	if (nErrNo > 8600 && nErrNo < 8800) strTitle = "GoodStage_2";
	if (nErrNo > 8800 && nErrNo < 9000) strTitle = "ShipAlign";
	if (nErrNo > 9000 && nErrNo < 9999) strTitle = "Vision";

	if (strBarcode.Right(1) == ';') strBarcode.Delete(strBarcode.GetLength()-1);
	if (strPort.Right(1) == ';') strPort.Delete(strPort.GetLength()-1);
	if (strTray.Right(1) == ';') strTray.Delete(strTray.GetLength()-1);
	if (strCm.Right(1) == ';') strCm.Delete(strCm.GetLength()-1);

	strLotId = ""; m_nPortNo = 0;
	if (nErrNo > 3000 && nErrNo < 3500) { strLotId = gData.sLotID_Tansfer[0];		if (strLotId == "") strLotId = gData.sLotID_Tansfer[2]; }
	if (nErrNo > 3500 && nErrNo < 4000) { strLotId = gData.sLotID_Tansfer[1];		if (strLotId == "") strLotId = gData.sLotID_Tansfer[2]; }
	if (nErrNo > 4000 && nErrNo < 4500) { strLotId = gData.sLotID_LoadStage[0];		if (strLotId == "") strLotId = gData.sLotID_LoadStage[2]; }
	if (nErrNo > 4500 && nErrNo < 5000) { strLotId = gData.sLotID_LoadStage[1];		if (strLotId == "") strLotId = gData.sLotID_LoadStage[2]; }
	if (nErrNo > 5000 && nErrNo < 5500) { strLotId = gData.sLotID_LoadPicker[0];	if (strLotId == "") strLotId = gData.sLotID_LoadPicker[2]; }
	if (nErrNo > 5500 && nErrNo < 6000) { strLotId = gData.sLotID_LoadPicker[1];	if (strLotId == "") strLotId = gData.sLotID_LoadPicker[2]; }
	if (nErrNo > 6000 && nErrNo < 6200) { strLotId = gData.sLotID_VisionStage[0];	if (strLotId == "") strLotId = gData.sLotID_VisionStage[4]; }
	if (nErrNo > 6200 && nErrNo < 6400) { strLotId = gData.sLotID_VisionStage[1];	if (strLotId == "") strLotId = gData.sLotID_VisionStage[4]; }
	if (nErrNo > 6400 && nErrNo < 6600) { strLotId = gData.sLotID_VisionStage[2];	if (strLotId == "") strLotId = gData.sLotID_VisionStage[4]; }
	if (nErrNo > 6600 && nErrNo < 7000) { strLotId = gData.sLotID_VisionStage[3];	if (strLotId == "") strLotId = gData.sLotID_VisionStage[4]; }
	if (nErrNo > 7000 && nErrNo < 7500) { strLotId = gData.sLotID_UnloadPicker[0];	if (strLotId == "") strLotId = gData.sLotID_UnloadPicker[2]; }
	if (nErrNo > 7500 && nErrNo < 8000) { strLotId = gData.sLotID_UnloadPicker[1];	if (strLotId == "") strLotId = gData.sLotID_UnloadPicker[2]; }
	if (nErrNo > 8000 && nErrNo < 8200) { strLotId = gData.sLotID_NGTray[0];		if (strLotId == "") strLotId = gData.sLotID_NGTray[2]; }
	if (nErrNo > 8200 && nErrNo < 8400) { strLotId = gData.sLotID_NGTray[1];		if (strLotId == "") strLotId = gData.sLotID_NGTray[2]; }
	if (nErrNo > 8400 && nErrNo < 8600) { strLotId = gData.sLotID_GoodTray[0];		if (strLotId == "") strLotId = gData.sLotID_GoodTray[2]; }
	if (nErrNo > 8600 && nErrNo < 8800) { strLotId = gData.sLotID_GoodTray[1];		if (strLotId == "") strLotId = gData.sLotID_GoodTray[2]; }
	if (nErrNo == 9180 || (nErrNo > 9200 && nErrNo < 9210)) strLotId = gAlm.sAlmLotID[0];

	if (gLot.nJobStatus == 0) { gAlm.sLotID = m_strLotID = ""; return; }

	if (strLotId == "") strLotId = gData.sLotID_Start;
	if (strLotId == "") {
		for(int i=0; i<6; i++) {
			if (gLot.nCmCount[i] > 0) {
				m_strLotID = strLotId = gLot.sLotID[i];
				m_nPortNo = i+1; break;
			}
		}
	} else {
		m_strLotID = strLotId;	m_nPortNo = 0;
		for(int i=0; i<6; i++) {
			if (m_strLotID == gLot.sLotID[i]) {
				m_nPortNo = i+1; break;
			}
		}
	}	

	m_strsSpcInfo.Format("%s,%s,%s,%s,%s,%s,%d", strTitle, strLotId, strBarcode, strPort, strTray, strCm, nModuleCount);
	strLog.Format("%s,%04d,%s,%s", strLotId, nErrNo, m_strsSpcInfo, sErrMsg);
	g_objLogFile.Save_SpcErrorLog(strLog, strLotId);

	gAlm.sItems = m_strTitle = strTitle;
	g_objLogFile.Save_EfficiencyLog(m_strLotID, "Down", strTitle, nErrNo, sErrMsg);

	if (nErrNo >= 9000 && nErrNo < 9100) gAlm.sGroup = "MES";
	else								 gAlm.sGroup = "Machine Touble";

	if (nErrNo > 2100 && nErrNo < 2800) gAlm.sUnit = "Elevator";
	if (nErrNo > 3000 && nErrNo < 4000) gAlm.sUnit = "Transfer";
	if (nErrNo > 4000 && nErrNo < 5000) gAlm.sUnit = "LoadStage";
	if (nErrNo > 5000 && nErrNo < 6000) gAlm.sUnit = "LoadPicker";
	if (nErrNo > 6000 && nErrNo < 7000) gAlm.sUnit = "InspectStage";
	if (nErrNo > 7000 && nErrNo < 8000) gAlm.sUnit = "UnloadPicker";
	if (nErrNo > 8000 && nErrNo < 8400) gAlm.sUnit = "NGStage";
	if (nErrNo > 8400 && nErrNo < 8800) gAlm.sUnit = "GoodStage";
	if (nErrNo > 8800 && nErrNo < 9000) gAlm.sUnit = "ShipAlign";
	if (nErrNo > 8999 && nErrNo < 9100) gAlm.sUnit = "MES";
	if (nErrNo > 9100 && nErrNo < 9999) gAlm.sUnit = "Vision";
}