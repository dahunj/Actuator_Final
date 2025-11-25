// DataManager.cpp: 구현 파일
//
#include "stdafx.h"
#include "DataManager.h"
#include "LogFile.h"

// CDataManager
CDataManager g_objDataManager;

CDataManager::CDataManager()
{
	Reset_EquipData();
	Reset_MoveData();
	Reset_MoveInput();
	Reset_IdleData();
	Reset_RosData();
}

CDataManager::~CDataManager()
{
}

void CDataManager::Reset_EquipData()
{
	m_EquipData.sEquipName = "";
	m_EquipData.nLotBarcodePort = 0;
	m_EquipData.bUseDoorLock = FALSE;
	m_EquipData.bUseTaktLog = TRUE;
	m_EquipData.nNoWorkTime = 0;

	m_EquipData.bUseAlign1 = FALSE;
	m_EquipData.bUseAlign2 = FALSE;
	m_EquipData.bUseBottom = FALSE;
	m_EquipData.bUseTop1 = FALSE;
	m_EquipData.bUseTop2 = FALSE;
	m_EquipData.bUseBotAng = FALSE;
	m_EquipData.bUseTopAng = FALSE;
	m_EquipData.bUseMesNg = FALSE;
	m_EquipData.bUseCMCheck = TRUE;
	m_EquipData.bUseNGSort = FALSE;
	m_EquipData.bUseNGSize = FALSE;

	m_EquipData.nTrayCountX = 0;
	m_EquipData.nTrayCountY = 0;
	m_EquipData.dTrayPitchX = 0.0;
	m_EquipData.dTrayPitchY = 0.0;

	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) m_EquipData.bTower[i][j] = FALSE;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 5; j++) m_EquipData.bBuzzer[i][j] = FALSE;

	m_EquipData.sPasswordMt = "";
	m_EquipData.sPasswordSi = "";

	m_EquipData.nDryRunNg = 0;
	for (int i = 0; i < 11; i++) m_EquipData.nDelayTime[i] = 100;
}

void CDataManager::Reset_MoveData()
{
	for (int i = 0; i < 5; i++) m_MoveData.dElevatorZ1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dElevatorZ2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dElevatorZ3[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dElevatorZ4[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dElevatorZ5[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dElevatorZ6[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dElevatorZ7[i] = 0.0;
	for (int i = 0; i <10; i++) m_MoveData.dTransferX1[i] = 0.0;
	for (int i = 0; i <15; i++) m_MoveData.dTransferZ1[i] = 0.0;
	for (int i = 0; i <15; i++) m_MoveData.dTransferX2[i] = 0.0;
	for (int i = 0; i <15; i++) m_MoveData.dTransferZ2[i] = 0.0;
	for (int i = 0; i < 7; i++) m_MoveData.dLoadStageY1[i] = 0.0;
	for (int i = 0; i < 7; i++) m_MoveData.dLoadStageY2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerX1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerY1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerZ1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerP1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerX2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerY2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerZ2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dLoadPickerP2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dBTMFocusZ[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dBTMLightZ[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dBTMAngleY[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dTOPVisionZ1[i] = 0.0;
	for (int i = 0; i < 7; i++) m_MoveData.dTOPVisionZ2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dVisionStageX1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dVisionStageX2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dVisionStageX3[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dVisionStageX4[i] = 0.0;
	for (int i = 0; i <20; i++) m_MoveData.dUnloadPickerX1[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveData.dUnloadPickerY1[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveData.dUnloadPickerZ1[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveData.dUnloadPickerP1[i] = 0.0;
	for (int i = 0; i <20; i++) m_MoveData.dUnloadPickerX2[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveData.dUnloadPickerY2[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveData.dUnloadPickerZ2[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveData.dUnloadPickerP2[i] = 0.0;
	for (int i = 0; i < 6; i++) m_MoveData.dGoodStageY1[i] = 0.0;
	for (int i = 0; i < 6; i++) m_MoveData.dGoodStageY2[i] = 0.0;
	for (int i = 0; i < 6; i++) m_MoveData.dNGStageY1[i] = 0.0;
	for (int i = 0; i < 6; i++) m_MoveData.dNGStageY2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dShiipAling[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dTop1LightZ[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveData.dTop1AngleY[i] = 0.0;
}

void CDataManager::Reset_MoveInput()
{
	for (int i = 0; i < 5; i++) m_MoveInput.dElevatorZ1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dElevatorZ2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dElevatorZ3[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dElevatorZ4[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dElevatorZ5[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dElevatorZ6[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dElevatorZ7[i] = 0.0;
	for (int i = 0; i <10; i++) m_MoveInput.dTransferX1[i] = 0.0;
	for (int i = 0; i <15; i++) m_MoveInput.dTransferZ1[i] = 0.0;
	for (int i = 0; i <15; i++) m_MoveInput.dTransferX2[i] = 0.0;
	for (int i = 0; i <15; i++) m_MoveInput.dTransferZ2[i] = 0.0;
	for (int i = 0; i < 7; i++) m_MoveInput.dLoadStageY1[i] = 0.0;
	for (int i = 0; i < 7; i++) m_MoveInput.dLoadStageY2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dLoadPickerX1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dLoadPickerY1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dLoadPickerZ1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dLoadPickerP1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dLoadPickerX2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dLoadPickerY2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dLoadPickerZ2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dLoadPickerP2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dBTMFocusZ[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dBTMLightZ[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dBTMAngleY[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dTOPVisionZ1[i] = 0.0;
	for (int i = 0; i < 7; i++) m_MoveInput.dTOPVisionZ2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dVisionStageX1[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dVisionStageX2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dVisionStageX3[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dVisionStageX4[i] = 0.0;
	for (int i = 0; i <20; i++) m_MoveInput.dUnloadPickerX1[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveInput.dUnloadPickerY1[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveInput.dUnloadPickerZ1[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveInput.dUnloadPickerP1[i] = 0.0;
	for (int i = 0; i <20; i++) m_MoveInput.dUnloadPickerX2[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveInput.dUnloadPickerY2[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveInput.dUnloadPickerZ2[i] = 0.0;
	for (int i = 0; i < 9; i++) m_MoveInput.dUnloadPickerP2[i] = 0.0;
	for (int i = 0; i < 6; i++) m_MoveInput.dGoodStageY1[i] = 0.0;
	for (int i = 0; i < 6; i++) m_MoveInput.dGoodStageY2[i] = 0.0;
	for (int i = 0; i < 6; i++) m_MoveInput.dNGStageY1[i] = 0.0;
	for (int i = 0; i < 6; i++) m_MoveInput.dNGStageY2[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dShiipAling[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dTop1LightZ[i] = 0.0;
	for (int i = 0; i < 5; i++) m_MoveInput.dTop1AngleY[i] = 0.0;
}

void CDataManager::Reset_IdleData()
{
	m_IdleData.nCount = 0;
	for (int i = 0; i < 100; i++) m_IdleData.sCode[i] = "";
	for (int i = 0; i < 100; i++) m_IdleData.sText[i] = "";
}

void CDataManager::Reset_RosData()
{
	m_RosData.sHandlerIp = "0.0.0.0";
	m_RosData.nJudgeTimeOver = 10000;
	m_RosData.lstMdjIp.RemoveAll();
}

BOOL CDataManager::Read_EquipData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("EquipData.ini File Not Found!!!");
		return FALSE;
	}

	m_EquipData.sPCID = INI.Get_String("EQUIPMENT", "PC_NAME", "");
	m_EquipData.sMachineCode = INI.Get_String("EQUIPMENT", "MACHINE_CODE", "");
	g_objLogFile.Set_ID(m_EquipData.sPCID, m_EquipData.sMachineCode);
	m_EquipData.sEquipName = INI.Get_String("EQUIPMENT", "NAME", "");
	m_EquipData.sModelName = INI.Get_String("EQUIPMENT", "MODEL", "");	gData.sRecipeName = m_EquipData.sModelName;
	m_EquipData.nLotBarcodePort = INI.Get_Integer("EQUIPMENT", "LOT_BARCODE", 1);
	m_EquipData.bUseDoorLock = INI.Get_Bool("EQUIPMENT", "DOOR_LOCK", FALSE);
	m_EquipData.bUseCosmeticNG = INI.Get_Bool("EQUIPMENT", "TAKT_LOG", FALSE);
	m_EquipData.nNoWorkTime = INI.Get_Integer("EQUIPMENT", "NOWORK_TIME", 0);
	m_EquipData.sPROG_VER = INI.Get_String("EQUIPMENT", "VIS_PROG_VER", "");
	m_EquipData.sPARA_VER = INI.Get_String("EQUIPMENT", "VIS_PARA_VER", "");
	m_EquipData.nLogDate = INI.Get_Integer("EQUIPMENT", "LOT_DELETE_DATE", 90);
	m_EquipData.bUseLightCurtain = INI.Get_Bool("EQUIPMENT", "LIGHT_CURTAIN", FALSE);

	gData.bUseDryRun = INI.Get_Bool("OPTION", "DRY_RUN_USE", FALSE);
	m_EquipData.bUseAlign1 = INI.Get_Bool("OPTION", "ALIGN_1", FALSE);
	m_EquipData.bUseAlign2 = INI.Get_Bool("OPTION", "ALIGN_2", FALSE);
	m_EquipData.bUseROS    = INI.Get_Bool("OPTION", "ROS_USE", FALSE);
	m_EquipData.bUseBottom = INI.Get_Bool("OPTION", "INSPECT_BTM", FALSE);
	m_EquipData.bUseTop1   = INI.Get_Bool("OPTION", "INSPECT_TOP1", FALSE);
	m_EquipData.bUseTop2   = INI.Get_Bool("OPTION", "INSPECT_TOP2", FALSE);
	m_EquipData.bUseBotAng = INI.Get_Bool("OPTION", "INSPECT_BAG", FALSE);
	m_EquipData.bUseTopAng = INI.Get_Bool("OPTION", "INSPECT_TAG", FALSE);
	m_EquipData.bUseCMCheck = INI.Get_Bool("OPTION", "CM_CHECK", TRUE);
	m_EquipData.bUseNGSort  = INI.Get_Bool("OPTION", "NG_SORT", FALSE);
	m_EquipData.bUseNGSize  = INI.Get_Bool("OPTION", "NG_SIZE", FALSE);
	m_EquipData.bUseGoodSort = INI.Get_Bool("OPTION", "GOOD_SORT", FALSE);
	m_EquipData.bUseMesNg		= INI.Get_Bool("OPTION", "MES_NG", FALSE);
	m_EquipData.bUseMES			= INI.Get_Bool("OPTION", "MES_USE", FALSE);
	m_EquipData.bUseMESRcpCheck = INI.Get_Bool("OPTION", "MES_CNTCHECK", FALSE);
	gAlm.dMotionChkPos			= INI.Get_Double("OPTION", "MOTION_CHECK", 0.0);
	gData.nRejectMaxCount       = INI.Get_Integer("OPTION", "REJECT_COUNT", 0);
	m_EquipData.bUseDisplay = INI.Get_Bool("OPTION", "DISPLAY", TRUE);
	m_EquipData.dTranZOverride	= INI.Get_Double("OPTION", "OVERRIDE_DISTANCE", 0.0);
	m_EquipData.dSpeedZOverride	= INI.Get_Double("OPTION", "OVERRIDE_SPEED", 0.0);
	gData.nSlideTime			= INI.Get_Integer("OPTION", "SLIDE_CHECK", 0) * 1000;
	gData.nDoorLockTime			= INI.Get_Integer("OPTION", "DOOR_LOCK_TIME", 0);
	gData.dAlignX				= INI.Get_Double("OPTION", "SHIPALIGN_XAXIS", 0.1);
	gData.dAlignY				= INI.Get_Double("OPTION", "SHIPALIGN_YAXIS", 0.1);
	gData.dElevatorDown			= INI.Get_Double("OPTION", "ELEVATOR_DOWN", 0.0);
	m_EquipData.bElevatorAlign	= INI.Get_Bool("OPTION", "ELEVATOR_ALIGN", FALSE);
	m_EquipData.bUseInspectBlow	= INI.Get_Bool("OPTION", "INSPECT_BLOW", FALSE);
	m_EquipData.bUsePassGood	= INI.Get_Bool("OPTION", "PASS_GOOD", FALSE);
	m_EquipData.bUseOppAlarm	= INI.Get_Bool("OPTION", "OPP_ALARM", FALSE);

	if (gIt.nOpenStart == 0 && m_EquipData.bUseDoorLock == FALSE) g_objLogFile.Save_Interlock(2);
	if (gIt.nOpenStart == 1 && m_EquipData.bUseDoorLock == TRUE)  g_objLogFile.Save_Interlock(3);

	CString sLanguage		= INI.Get_String("OPTION", "LANGUAGE", "");
	if (sLanguage == "ENG") gData.nLanguage = 1;
	else					gData.nLanguage = 0;
	gData.nNG_MC[0][0]      = INI.Get_Integer("OPTION", "NG_MC", 0);
	gData.nNG_MC[1][0]      = INI.Get_Integer("OPTION", "NG_GF", 0);
	gData.nNG_MC[2][0]      = INI.Get_Integer("OPTION", "NG_BAC", 0);
	gData.nNG_MC[3][0]      = INI.Get_Integer("OPTION", "NG_VIS", 0);
	gData.nNG_MC[4][0]      = INI.Get_Integer("OPTION", "NG_MES", 0);
	gData.nMgnTrayCount     = INI.Get_Integer("OPTION", "MARGINAL_TRAY", 0);

	m_EquipData.nTrayCountX = INI.Get_Integer("TRAY", "COUNT_X", 0);
	m_EquipData.nTrayCountY = INI.Get_Integer("TRAY", "COUNT_Y", 0);
	m_EquipData.dTrayPitchX = INI.Get_Double("TRAY", "PITCH_X", 0.0);
	m_EquipData.dTrayPitchY = INI.Get_Double("TRAY", "PITCH_Y", 0.0);

	m_EquipData.dPitchBtm = INI.Get_Double("PITCH", "BTM_SCAN", 0.0);
	m_EquipData.dPitchTop = INI.Get_Double("PITCH", "TOP_SCAN", 0.0);

	CString strKey, strData, strTemp;
	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) { strKey.Format("%d%d", i, j); m_EquipData.bTower[i][j] = INI.Get_Bool("TOWER", strKey, FALSE); }
	for (int i = 0; i < 2; i++) for (int j = 0; j < 5; j++) { strKey.Format("%d%d", i, j); m_EquipData.bBuzzer[i][j] = INI.Get_Bool("BUZZER", strKey, FALSE); }

	m_EquipData.sPasswordMt = INI.Get_String("HIDDEN", "PASSWORD_MT", "");
	m_EquipData.sPasswordSi = INI.Get_String("HIDDEN", "PASSWORD_SI", "");
	m_EquipData.sPasswordPm = INI.Get_String("HIDDEN", "PASSWORD_PM", "");

	m_EquipData.nDryRunNg = INI.Get_Integer("DRY_RUN", "NG_RATIO", 0);

	m_EquipData.nDelayTime[0]       = INI.Get_Integer("DELAY_TIME", "OPEN_DELAY", 0);
	m_EquipData.nDelayTime[1]       = INI.Get_Integer("DELAY_TIME", "CLOSE_DELAY", 0);
	m_EquipData.nDelayTime[2]       = INI.Get_Integer("DELAY_TIME", "BTM_SCAN_DELAY", 0);
	m_EquipData.nDelayTime[3]       = INI.Get_Integer("DELAY_TIME", "TOP_SCAN_DELAY", 0);
	m_EquipData.nDelayTime[4]       = INI.Get_Integer("DELAY_TIME", "VACUUM_ON_DELAY", 0);
	m_EquipData.nDelayTime[5]       = INI.Get_Integer("DELAY_TIME", "ALIGN_DELAY", 0);
	m_EquipData.nDelayTime[6]       = INI.Get_Integer("DELAY_TIME", "ALIGN_SHIP", 0);
	m_EquipData.nDelayTime[7]       = INI.Get_Integer("DELAY_TIME", "OPEN_UNLOAD", 0);
	m_EquipData.nDelayTime[8]       = INI.Get_Integer("DELAY_TIME", "CLOSE_UNLOAD", 0);
	m_EquipData.nDelayTime[9]       = INI.Get_Integer("DELAY_TIME", "TOP2_SCAN_DELAY", 0);
	m_EquipData.nDelayTime[10]      = INI.Get_Integer("DELAY_TIME", "LOADPICKER_CHECK", 0);
	m_EquipData.nTimeOver[0]        = INI.Get_Integer("TIME_OVER", "INSPECTION", 0);
	m_EquipData.nTimeOver[1]        = INI.Get_Integer("TIME_OVER", "ROS", 0);
	m_EquipData.bUseAutoSkip		= INI.Get_Bool("TIME_OVER", "AUTO_SKIP", FALSE);

	// Log 표준화
	gData.nStdEqNo = INI.Get_Integer("STD_LOG", "STD_EQ_NO", 0);
	gData.nStdLotNo = INI.Get_Integer("STD_LOG", "STD_LOT_NO", 0);
	gData.nStdLogDay = INI.Get_Integer("STD_LOG", "STD_LOG_DAY", 0);

	SYSTEMTIME time;
	GetLocalTime(&time);
	if (gData.nStdLogDay != time.wDay) {
		gData.nStdLotNo = 0;
		gData.nStdLogDay = (int)time.wDay;
		INI.Set_Integer("STD_LOG", "STD_LOT_NO", gData.nStdLotNo);
		INI.Set_Integer("STD_LOG", "STD_LOG_DAY", gData.nStdLogDay);
		for(int i=0; i<6; i++) gData.nTotLotNo[i] = 0;
	}

	// Barcode Sort
	gData.bUseBarSort  = INI.Get_Bool("BARCODE_SORT", "BAR_SORT", FALSE);
	gData.nBarSortTray = INI.Get_Integer("BARCODE_SORT", "SORT_TRAY", 0);	//1:MG, 2:Good

	Read_NGTraySort();
	return TRUE;
}

BOOL CDataManager::Read_ModelEquipData(CString strPath)
{
	CIniFileCS INI(strPath + "EquipData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("EquipData.ini File Not Found!!!!");
		return FALSE;
	}

	m_EquipData.sEquipName = INI.Get_String("EQUIPMENT", "NAME", "");
	m_EquipData.sModelName = INI.Get_String("EQUIPMENT", "MODEL", "");	gData.sRecipeName = m_EquipData.sModelName;
	m_EquipData.nLotBarcodePort = INI.Get_Integer("EQUIPMENT", "LOT_BARCODE", 1);
	m_EquipData.bUseDoorLock = INI.Get_Bool("EQUIPMENT", "DOOR_LOCK", FALSE);
	m_EquipData.bUseCosmeticNG = INI.Get_Bool("EQUIPMENT", "TAKT_LOG", FALSE);
	m_EquipData.nNoWorkTime = INI.Get_Integer("EQUIPMENT", "NOWORK_TIME", 0);
	m_EquipData.sPROG_VER = INI.Get_String("EQUIPMENT", "VIS_PROG_VER", "");
	m_EquipData.sPARA_VER = INI.Get_String("EQUIPMENT", "VIS_PARA_VER", "");
	m_EquipData.bUseLightCurtain = INI.Get_Bool("EQUIPMENT", "LIGHT_CURTAIN", FALSE);

	gData.bUseDryRun = INI.Get_Bool("OPTION", "DRY_RUN_USE", FALSE);
	m_EquipData.bUseAlign1 = INI.Get_Bool("OPTION", "ALIGN_1", FALSE);
	m_EquipData.bUseAlign2 = INI.Get_Bool("OPTION", "ALIGN_2", FALSE);
	m_EquipData.bUseROS    = INI.Get_Bool("OPTION", "ROS_USE", FALSE);
	m_EquipData.bUseBottom = INI.Get_Bool("OPTION", "INSPECT_BTM", FALSE);
	m_EquipData.bUseTop1   = INI.Get_Bool("OPTION", "INSPECT_TOP1", FALSE);
	m_EquipData.bUseTop2   = INI.Get_Bool("OPTION", "INSPECT_TOP2", FALSE);
	m_EquipData.bUseBotAng = INI.Get_Bool("OPTION", "INSPECT_BAG", FALSE);
	m_EquipData.bUseTopAng = INI.Get_Bool("OPTION", "INSPECT_TAG", FALSE);
	m_EquipData.bUseCMCheck = INI.Get_Bool("OPTION", "CM_CHECK", TRUE);
	m_EquipData.bUseNGSort  = INI.Get_Bool("OPTION", "NG_SORT", FALSE);
	m_EquipData.bUseNGSize  = INI.Get_Bool("OPTION", "NG_SIZE", FALSE);
	m_EquipData.bUseGoodSort = INI.Get_Bool("OPTION", "GOOD_SORT", FALSE);
	m_EquipData.bUseMesNg		= INI.Get_Bool("OPTION", "MES_NG", FALSE);
	m_EquipData.bUseMES			= INI.Get_Bool("OPTION", "MES_USE", FALSE);
	m_EquipData.bUseMESRcpCheck = INI.Get_Bool("OPTION", "MES_CNTCHECK", FALSE);
	gAlm.dMotionChkPos			= INI.Get_Double("OPTION", "MOTION_CHECK", 0.0);
	gData.nRejectMaxCount       = INI.Get_Integer("OPTION", "REJECT_COUNT", 0);
	m_EquipData.bUseDisplay		= INI.Get_Bool("OPTION", "DISPLAY", TRUE);
	m_EquipData.dTranZOverride	= INI.Get_Double("OPTION", "OVERRIDE_DISTANCE", 0.0);
	m_EquipData.dSpeedZOverride	= INI.Get_Double("OPTION", "OVERRIDE_SPEED", 0.0);
	gData.dElevatorDown			= INI.Get_Double("OPTION", "ELEVATOR_DOWN", 0.0);
	m_EquipData.bUsePassGood	= INI.Get_Bool("OPTION", "PASS_GOOD", FALSE);
	m_EquipData.bUseOppAlarm	= INI.Get_Bool("OPTION", "OPP_ALARM", FALSE);

	m_EquipData.nTrayCountX = INI.Get_Integer("TRAY", "COUNT_X", 0);
	m_EquipData.nTrayCountY = INI.Get_Integer("TRAY", "COUNT_Y", 0);
	m_EquipData.dTrayPitchX = INI.Get_Double("TRAY", "PITCH_X", 0.0);
	m_EquipData.dTrayPitchY = INI.Get_Double("TRAY", "PITCH_Y", 0.0);

	m_EquipData.dPitchBtm = INI.Get_Double("PITCH", "BTM_SCAN", 0.0);
	m_EquipData.dPitchTop = INI.Get_Double("PITCH", "TOP_SCAN", 0.0);

	CString strKey;
	for (int i = 0; i < 6; i++) for (int j = 0; j < 7; j++) { strKey.Format("%d%d", i, j); m_EquipData.bTower[i][j] = INI.Get_Bool("TOWER", strKey, FALSE); }
	for (int i = 0; i < 2; i++) for (int j = 0; j < 5; j++) { strKey.Format("%d%d", i, j); m_EquipData.bBuzzer[i][j] = INI.Get_Bool("BUZZER", strKey, FALSE); }

	m_EquipData.sPasswordMt = INI.Get_String("HIDDEN", "PASSWORD_MT", "");
	m_EquipData.sPasswordSi = INI.Get_String("HIDDEN", "PASSWORD_SI", "");
	m_EquipData.sPasswordPm = INI.Get_String("HIDDEN", "PASSWORD_PM", "");

	m_EquipData.nDryRunNg = INI.Get_Integer("DRY_RUN", "NG_RATIO", 0);

	m_EquipData.nDelayTime[0]       = INI.Get_Integer("DELAY_TIME", "OPEN_DELAY", 0);
	m_EquipData.nDelayTime[1]       = INI.Get_Integer("DELAY_TIME", "CLOSE_DELAY", 0);
	m_EquipData.nDelayTime[2]       = INI.Get_Integer("DELAY_TIME", "BTM_SCAN_DELAY", 0);
	m_EquipData.nDelayTime[3]       = INI.Get_Integer("DELAY_TIME", "TOP_SCAN_DELAY", 0);
	m_EquipData.nDelayTime[4]       = INI.Get_Integer("DELAY_TIME", "VACUUM_ON_DELAY", 0);
	m_EquipData.nDelayTime[5]       = INI.Get_Integer("DELAY_TIME", "ALIGN_DELAY", 0);
	m_EquipData.nDelayTime[6]       = INI.Get_Integer("DELAY_TIME", "ALIGN_SHIP", 0);
	m_EquipData.nDelayTime[7]       = INI.Get_Integer("DELAY_TIME", "OPEN_UNLOAD", 0);
	m_EquipData.nDelayTime[8]       = INI.Get_Integer("DELAY_TIME", "CLOSE_UNLOAD", 0);
	m_EquipData.nDelayTime[9]       = INI.Get_Integer("DELAY_TIME", "TOP2_SCAN_DELAY", 0);
	m_EquipData.nDelayTime[10]      = INI.Get_Integer("DELAY_TIME", "LOADPICKER_CHECK", 0);

	m_EquipData.nTimeOver[0]        = INI.Get_Integer("TIME_OVER", "INSPECTION", 0);
	m_EquipData.nTimeOver[1]        = INI.Get_Integer("TIME_OVER", "ROS", 0);
	m_EquipData.bUseAutoSkip		= INI.Get_Bool("TIME_OVER", "AUTO_SKIP", FALSE);

	return TRUE;
}

BOOL CDataManager::Save_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return FALSE;
	}

	CString strKey;
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("00_ELEVATOR_Z1",		strKey, m_MoveData.dElevatorZ1[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("01_ELEVATOR_Z2",		strKey, m_MoveData.dElevatorZ2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("02_ELEVATOR_Z3",		strKey, m_MoveData.dElevatorZ3[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("03_ELEVATOR_Z4",		strKey, m_MoveData.dElevatorZ4[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("04_ELEVATOR_Z5",		strKey, m_MoveData.dElevatorZ5[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("05_ELEVATOR_Z6",		strKey, m_MoveData.dElevatorZ6[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("06_ELEVATOR_Z7",		strKey, m_MoveData.dElevatorZ7[i],	 "%0.3lf"); }
	for (int i = 0; i <10; i++) { strKey.Format("%02d", i);		INI.Set_Double("07_TRANSFER_X1",		strKey, m_MoveData.dTransferX1[i],	 "%0.3lf"); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i);		INI.Set_Double("08_TRANSFER_Z1",		strKey, m_MoveData.dTransferZ1[i],	 "%0.3lf"); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i);		INI.Set_Double("09_TRANSFER_X2",		strKey, m_MoveData.dTransferX2[i],	 "%0.3lf"); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i);		INI.Set_Double("10_TRANSFER_Z2",		strKey, m_MoveData.dTransferZ2[i],	 "%0.3lf"); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i);		INI.Set_Double("11_LOAD_STAGE_Y1",		strKey, m_MoveData.dLoadStageY1[i],	 "%0.3lf"); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i);		INI.Set_Double("12_LOAD_STAGE_Y2",		strKey, m_MoveData.dLoadStageY2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("13_LOAD_PICKER_X1",		strKey, m_MoveData.dLoadPickerX1[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("14_LOAD_PICKER_Y1",		strKey, m_MoveData.dLoadPickerY1[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("15_LOAD_PICKER_Z1",		strKey, m_MoveData.dLoadPickerZ1[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("16_LOAD_PICKER_P1",		strKey, m_MoveData.dLoadPickerP1[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("17_LOAD_PICKER_X2",		strKey, m_MoveData.dLoadPickerX2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("18_LOAD_PICKER_Y2",		strKey, m_MoveData.dLoadPickerY2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("19_LOAD_PICKER_Z2",		strKey, m_MoveData.dLoadPickerZ2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("20_LOAD_PICKER_P2",		strKey, m_MoveData.dLoadPickerP2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("21_BTM_CAMERA_Z",		strKey, m_MoveData.dBTMFocusZ[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("22_BTM_LIGHT_Z",		strKey, m_MoveData.dBTMLightZ[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("23_BTM_ANGLE_Y",		strKey, m_MoveData.dBTMAngleY[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("24_TOP1_VISION_Z",		strKey, m_MoveData.dTOPVisionZ1[i],	 "%0.3lf"); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i);		INI.Set_Double("25_TOP2_VISION_Z",		strKey, m_MoveData.dTOPVisionZ2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("26_INSPECT_STAGE_X1",	strKey, m_MoveData.dVisionStageX1[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("27_INSPECT_STAGE_X2",	strKey, m_MoveData.dVisionStageX2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("28_INSPECT_STAGE_X3",	strKey, m_MoveData.dVisionStageX3[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("29_INSPECT_STAGE_X4",	strKey, m_MoveData.dVisionStageX4[i],	 "%0.3lf"); }
	for (int i = 0; i <20; i++) { strKey.Format("%02d", i);		INI.Set_Double("30_UNLOAD_PICKER_X1",	strKey, m_MoveData.dUnloadPickerX1[i],	 "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		INI.Set_Double("31_UNLOAD_PICKER_Y1",	strKey, m_MoveData.dUnloadPickerY1[i],	 "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		INI.Set_Double("32_UNLOAD_PICKER_Z1",	strKey, m_MoveData.dUnloadPickerZ1[i],	 "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		INI.Set_Double("33_UNLOAD_PICKER_P1",	strKey, m_MoveData.dUnloadPickerP1[i],	 "%0.3lf"); }
	for (int i = 0; i <20; i++) { strKey.Format("%02d", i);		INI.Set_Double("34_UNLOAD_PICKER_X2",	strKey, m_MoveData.dUnloadPickerX2[i],	 "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		INI.Set_Double("35_UNLOAD_PICKER_Y2",	strKey, m_MoveData.dUnloadPickerY2[i],	 "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		INI.Set_Double("36_UNLOAD_PICKER_Z2",	strKey, m_MoveData.dUnloadPickerZ2[i],	 "%0.3lf"); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i);		INI.Set_Double("37_UNLOAD_PICKER_P2",	strKey, m_MoveData.dUnloadPickerP2[i],	 "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		INI.Set_Double("38_GOOD_STAGE_Y1",		strKey, m_MoveData.dGoodStageY1[i],	 "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		INI.Set_Double("39_GOOD_STAGE_Y2",		strKey, m_MoveData.dGoodStageY2[i],	 "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		INI.Set_Double("40_NG_STAGE_Y1",		strKey, m_MoveData.dNGStageY1[i],	 "%0.3lf"); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i);		INI.Set_Double("41_NG_STAGE_Y2",		strKey, m_MoveData.dNGStageY2[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("42_SHIP_ALIGN_X",		strKey, m_MoveData.dShiipAling[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("43_TOP1_LIGHT_Z",		strKey, m_MoveData.dTop1LightZ[i],	 "%0.3lf"); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);		INI.Set_Double("44_TOP1_ANGLE_Y",		strKey, m_MoveData.dTop1AngleY[i],	 "%0.3lf"); }
	return TRUE;
}


BOOL CDataManager::Read_MoveData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return FALSE;
	}

	CString strKey;
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ1[i]		= INI.Get_Double("00_ELEVATOR_Z1",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ2[i]		= INI.Get_Double("01_ELEVATOR_Z2",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ3[i]		= INI.Get_Double("02_ELEVATOR_Z3",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ4[i]		= INI.Get_Double("03_ELEVATOR_Z4",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ5[i]		= INI.Get_Double("04_ELEVATOR_Z5",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ6[i]		= INI.Get_Double("05_ELEVATOR_Z6",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ7[i]		= INI.Get_Double("06_ELEVATOR_Z7",		strKey, 0.0); }
	for (int i = 0; i <10; i++) { strKey.Format("%02d", i); m_MoveData.dTransferX1[i]		= INI.Get_Double("07_TRANSFER_X1",		strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveData.dTransferZ1[i]		= INI.Get_Double("08_TRANSFER_Z1",		strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveData.dTransferX2[i]		= INI.Get_Double("09_TRANSFER_X2",		strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveData.dTransferZ2[i]		= INI.Get_Double("10_TRANSFER_Z2",		strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveData.dLoadStageY1[i]		= INI.Get_Double("11_LOAD_STAGE_Y1",	strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveData.dLoadStageY2[i]		= INI.Get_Double("12_LOAD_STAGE_Y2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerX1[i]		= INI.Get_Double("13_LOAD_PICKER_X1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerY1[i]		= INI.Get_Double("14_LOAD_PICKER_Y1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerZ1[i]		= INI.Get_Double("15_LOAD_PICKER_Z1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerP1[i]		= INI.Get_Double("16_LOAD_PICKER_P1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerX2[i]		= INI.Get_Double("17_LOAD_PICKER_X2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerY2[i]		= INI.Get_Double("18_LOAD_PICKER_Y2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerZ2[i]		= INI.Get_Double("19_LOAD_PICKER_Z2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerP2[i]		= INI.Get_Double("20_LOAD_PICKER_P2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBTMFocusZ[i]		= INI.Get_Double("21_BTM_CAMERA_Z",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBTMLightZ[i]		= INI.Get_Double("22_BTM_LIGHT_Z",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBTMAngleY[i]		= INI.Get_Double("23_BTM_ANGLE_Y",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dTOPVisionZ1[i]		= INI.Get_Double("24_TOP1_VISION_Z",	strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveData.dTOPVisionZ2[i]		= INI.Get_Double("25_TOP2_VISION_Z",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dVisionStageX1[i]	= INI.Get_Double("26_INSPECT_STAGE_X1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dVisionStageX2[i]	= INI.Get_Double("27_INSPECT_STAGE_X2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dVisionStageX3[i]	= INI.Get_Double("28_INSPECT_STAGE_X3",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dVisionStageX4[i]	= INI.Get_Double("29_INSPECT_STAGE_X4",	strKey, 0.0); }
	for (int i = 0; i <20; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerX1[i]	= INI.Get_Double("30_UNLOAD_PICKER_X1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerY1[i]	= INI.Get_Double("31_UNLOAD_PICKER_Y1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerZ1[i]	= INI.Get_Double("32_UNLOAD_PICKER_Z1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerP1[i]	= INI.Get_Double("33_UNLOAD_PICKER_P1",	strKey, 0.0); }
	for (int i = 0; i <20; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerX2[i]	= INI.Get_Double("34_UNLOAD_PICKER_X2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerY2[i]	= INI.Get_Double("35_UNLOAD_PICKER_Y2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerZ2[i]	= INI.Get_Double("36_UNLOAD_PICKER_Z2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerP2[i]	= INI.Get_Double("37_UNLOAD_PICKER_P2",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveData.dGoodStageY1[i]		= INI.Get_Double("38_GOOD_STAGE_Y1",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveData.dGoodStageY2[i]		= INI.Get_Double("39_GOOD_STAGE_Y2",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveData.dNGStageY1[i]		= INI.Get_Double("40_NG_STAGE_Y1",		strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveData.dNGStageY2[i]		= INI.Get_Double("41_NG_STAGE_Y2",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dShiipAling[i]		= INI.Get_Double("42_SHIP_ALIGN_X",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_MoveData.dTop1LightZ[i]		= INI.Get_Double("43_TOP1_LIGHT_Z",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_MoveData.dTop1AngleY[i]		= INI.Get_Double("44_TOP1_ANGLE_Y",		strKey, 0.0); }

	if (Read_MoveInput()==FALSE) Reset_MoveInput();

	return TRUE;
}

BOOL CDataManager::Read_MoveInput()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\MoveInput.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveInput.ini File Not Found!!!");
		return FALSE;
	}

	CString strKey;
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dElevatorZ1[i]		= INI.Get_Double("00_ELEVATOR_Z1",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dElevatorZ2[i]		= INI.Get_Double("01_ELEVATOR_Z2",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dElevatorZ3[i]		= INI.Get_Double("02_ELEVATOR_Z3",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dElevatorZ4[i]		= INI.Get_Double("03_ELEVATOR_Z4",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dElevatorZ5[i]		= INI.Get_Double("04_ELEVATOR_Z5",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dElevatorZ6[i]		= INI.Get_Double("05_ELEVATOR_Z6",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dElevatorZ7[i]		= INI.Get_Double("06_ELEVATOR_Z7",		strKey, 0.0); }
	for (int i = 0; i <10; i++) { strKey.Format("%02d", i); m_MoveInput.dTransferX1[i]		= INI.Get_Double("07_TRANSFER_X1",		strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveInput.dTransferZ1[i]		= INI.Get_Double("08_TRANSFER_Z1",		strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveInput.dTransferX2[i]		= INI.Get_Double("09_TRANSFER_X2",		strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveInput.dTransferZ2[i]		= INI.Get_Double("10_TRANSFER_Z2",		strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadStageY1[i]		= INI.Get_Double("11_LOAD_STAGE_Y1",	strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadStageY2[i]		= INI.Get_Double("12_LOAD_STAGE_Y2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadPickerX1[i]	= INI.Get_Double("13_LOAD_PICKER_X1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadPickerY1[i]	= INI.Get_Double("14_LOAD_PICKER_Y1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadPickerZ1[i]	= INI.Get_Double("15_LOAD_PICKER_Z1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadPickerP1[i]	= INI.Get_Double("16_LOAD_PICKER_P1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadPickerX2[i]	= INI.Get_Double("17_LOAD_PICKER_X2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadPickerY2[i]	= INI.Get_Double("18_LOAD_PICKER_Y2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadPickerZ2[i]	= INI.Get_Double("19_LOAD_PICKER_Z2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dLoadPickerP2[i]	= INI.Get_Double("20_LOAD_PICKER_P2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dBTMFocusZ[i]		= INI.Get_Double("21_BTM_CAMERA_Z",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dBTMLightZ[i]		= INI.Get_Double("22_BTM_LIGHT_Z",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dBTMAngleY[i]		= INI.Get_Double("23_BTM_ANGLE_Y",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dTOPVisionZ1[i]		= INI.Get_Double("24_TOP1_VISION_Z",	strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveInput.dTOPVisionZ2[i]		= INI.Get_Double("25_TOP2_VISION_Z",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dVisionStageX1[i]	= INI.Get_Double("26_INSPECT_STAGE_X1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dVisionStageX2[i]	= INI.Get_Double("27_INSPECT_STAGE_X2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dVisionStageX3[i]	= INI.Get_Double("28_INSPECT_STAGE_X3",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dVisionStageX4[i]	= INI.Get_Double("29_INSPECT_STAGE_X4",	strKey, 0.0); }
	for (int i = 0; i <20; i++) { strKey.Format("%02d", i); m_MoveInput.dUnloadPickerX1[i]	= INI.Get_Double("30_UNLOAD_PICKER_X1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveInput.dUnloadPickerY1[i]	= INI.Get_Double("31_UNLOAD_PICKER_Y1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveInput.dUnloadPickerZ1[i]	= INI.Get_Double("32_UNLOAD_PICKER_Z1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveInput.dUnloadPickerP1[i]	= INI.Get_Double("33_UNLOAD_PICKER_P1",	strKey, 0.0); }
	for (int i = 0; i <20; i++) { strKey.Format("%02d", i); m_MoveInput.dUnloadPickerX2[i]	= INI.Get_Double("34_UNLOAD_PICKER_X2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveInput.dUnloadPickerY2[i]	= INI.Get_Double("35_UNLOAD_PICKER_Y2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveInput.dUnloadPickerZ2[i]	= INI.Get_Double("36_UNLOAD_PICKER_Z2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveInput.dUnloadPickerP2[i]	= INI.Get_Double("37_UNLOAD_PICKER_P2",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveInput.dGoodStageY1[i]		= INI.Get_Double("38_GOOD_STAGE_Y1",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveInput.dGoodStageY2[i]		= INI.Get_Double("39_GOOD_STAGE_Y2",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveInput.dNGStageY1[i]		= INI.Get_Double("40_NG_STAGE_Y1",		strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveInput.dNGStageY2[i]		= INI.Get_Double("41_NG_STAGE_Y2",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveInput.dShiipAling[i]		= INI.Get_Double("42_SHIP_ALIGN_X",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_MoveInput.dTop1LightZ[i]		= INI.Get_Double("43_TOP1_LIGHT_Z",		strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_MoveInput.dTop1AngleY[i]		= INI.Get_Double("44_TOP1_ANGLE_Y",		strKey, 0.0); }

	return TRUE;
}

BOOL CDataManager::Read_ModelMoveData(CString strPath)
{
	CIniFileCS INI(strPath + "MoveData.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("MoveData.ini File Not Found!!!");
		return FALSE;
	}

	CString strKey;
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ1[i]		= INI.Get_Double("00_ELEVATOR_Z1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ2[i]		= INI.Get_Double("01_ELEVATOR_Z2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ3[i]		= INI.Get_Double("02_ELEVATOR_Z3",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ4[i]		= INI.Get_Double("03_ELEVATOR_Z4",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ5[i]		= INI.Get_Double("04_ELEVATOR_Z5",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ6[i]		= INI.Get_Double("05_ELEVATOR_Z6",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dElevatorZ7[i]		= INI.Get_Double("06_ELEVATOR_Z7",	strKey, 0.0); }
	for (int i = 0; i <10; i++) { strKey.Format("%02d", i); m_MoveData.dTransferX1[i]		= INI.Get_Double("07_TRANSFER_X1",	strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveData.dTransferZ1[i]		= INI.Get_Double("08_TRANSFER_Z1",	strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveData.dTransferX2[i]	= INI.Get_Double("09_TRANSFER_X2",	strKey, 0.0); }
	for (int i = 0; i <15; i++) { strKey.Format("%02d", i); m_MoveData.dTransferZ2[i]	= INI.Get_Double("10_TRANSFER_Z2",	strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveData.dLoadStageY1[i]	= INI.Get_Double("11_LOAD_STAGE_Y1",	strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveData.dLoadStageY2[i]	= INI.Get_Double("12_LOAD_STAGE_Y2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerX1[i]	= INI.Get_Double("13_LOAD_PICKER_X1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerY1[i]	= INI.Get_Double("14_LOAD_PICKER_Y1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerZ1[i]	= INI.Get_Double("15_LOAD_PICKER_Z1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerP1[i]	= INI.Get_Double("16_LOAD_PICKER_P1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerX2[i]	= INI.Get_Double("17_LOAD_PICKER_X2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerY2[i]	= INI.Get_Double("18_LOAD_PICKER_Y2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerZ2[i]	= INI.Get_Double("19_LOAD_PICKER_Z2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dLoadPickerP2[i]	= INI.Get_Double("20_LOAD_PICKER_P2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBTMFocusZ[i]		= INI.Get_Double("21_BTM_CAMERA_Z",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBTMLightZ[i]		= INI.Get_Double("22_BTM_LIGHT_Z",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dBTMAngleY[i]		= INI.Get_Double("23_BTM_ANGLE_Y",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dTOPVisionZ1[i]	= INI.Get_Double("24_TOP1_VISION_Z",	strKey, 0.0); }
	for (int i = 0; i < 7; i++) { strKey.Format("%02d", i); m_MoveData.dTOPVisionZ2[i]	= INI.Get_Double("25_TOP2_VISION_Z",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dVisionStageX1[i]	= INI.Get_Double("26_INSPECT_STAGE_X1",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dVisionStageX2[i]	= INI.Get_Double("27_INSPECT_STAGE_X2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dVisionStageX3[i]	= INI.Get_Double("28_INSPECT_STAGE_X3",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dVisionStageX4[i]	= INI.Get_Double("29_INSPECT_STAGE_X4",	strKey, 0.0); }
	for (int i = 0; i <20; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerX1[i]	= INI.Get_Double("30_UNLOAD_PICKER_X1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerY1[i]	= INI.Get_Double("31_UNLOAD_PICKER_Y1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerZ1[i]	= INI.Get_Double("32_UNLOAD_PICKER_Z1",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerP1[i]	= INI.Get_Double("33_UNLOAD_PICKER_P1",	strKey, 0.0); }
	for (int i = 0; i <20; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerX2[i]	= INI.Get_Double("34_UNLOAD_PICKER_X2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerY2[i]	= INI.Get_Double("35_UNLOAD_PICKER_Y2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerZ2[i]	= INI.Get_Double("36_UNLOAD_PICKER_Z2",	strKey, 0.0); }
	for (int i = 0; i < 9; i++) { strKey.Format("%02d", i); m_MoveData.dUnloadPickerP2[i]	= INI.Get_Double("37_UNLOAD_PICKER_P2",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveData.dGoodStageY1[i]	= INI.Get_Double("38_GOOD_STAGE_Y1",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveData.dGoodStageY2[i]	= INI.Get_Double("39_GOOD_STAGE_Y2",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveData.dNGStageY1[i]		= INI.Get_Double("40_NG_STAGE_Y1",	strKey, 0.0); }
	for (int i = 0; i < 6; i++) { strKey.Format("%02d", i); m_MoveData.dNGStageY2[i]		= INI.Get_Double("41_NG_STAGE_Y2",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i); m_MoveData.dShiipAling[i]		= INI.Get_Double("42_SHIP_ALIGN_X",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_MoveData.dTop1LightZ[i]		= INI.Get_Double("43_TOP1_LIGHT_Z",	strKey, 0.0); }
	for (int i = 0; i < 5; i++) { strKey.Format("%02d", i);	m_MoveData.dTop1AngleY[i]		= INI.Get_Double("44_TOP1_ANGLE_Y",	strKey, 0.0); }

	return TRUE;
}

BOOL CDataManager::Read_IdleData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\IdleCodeList.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("IdleCodeList.ini File Not Found!!!");
		return FALSE;
	}

	char chSep = ',';
	CString strKey, sData, sCode, sText;

	m_IdleData.nCount = INI.Get_Integer("IDELCODE", "COUNT", 0);
	if (m_IdleData.nCount < 1 || m_IdleData.nCount > 99) return FALSE;

	for (int i = 0; i < m_IdleData.nCount; i++) {
		strKey.Format("%02d", i + 1);
		sData = INI.Get_String("IDELCODE", strKey, "");

		AfxExtractSubString(sCode, sData, 0, chSep);
		AfxExtractSubString(sText, sData, 1, chSep);

		m_IdleData.sCode[i] = sCode;
		m_IdleData.sText[i] = sText;
	}

	return TRUE;
}

BOOL CDataManager::Read_RosData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\RosData.ini");
	if (!INI.Check_File()) { AfxMessageBox("RosData.ini File Not Found!!!"); return FALSE; }

	m_RosData.sHandlerIp = INI.Get_String("DISPATCHER", "HANDLER_IP", "0.0.0.0");
	m_RosData.nJudgeTimeOver = INI.Get_Integer("DISPATCHER", "TIME_OVER", 10000);

	CString strKey, strIp;
	for (int i = 0; i < 50; i++) {
		strKey.Format("%02d", i);
		strIp = INI.Get_String("MDJ_LIST", strKey, "");
		if (strIp == "") break;
		m_RosData.lstMdjIp.AddTail(strIp);
	}

	return TRUE;
}

void CDataManager::Save_RosData()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\RosData.ini");
	if (!INI.Check_File()) { AfxMessageBox("RosData.ini File Not Found!!!"); return; }

	CString strKey, strIp;
	for (int i = 0; i < 50; i++) {
		strKey.Format("%02d", i);
		POSITION pos = m_RosData.lstMdjIp.FindIndex(i);
		strIp = (pos ? m_RosData.lstMdjIp.GetAt(pos) : "");
		INI.Set_String("MDJ_LIST", strKey, strIp);
	}
}

BOOL CDataManager::Read_NGTraySort()
{
	CString strKey, strData, strTemp;

	CIniFileCS INI_NG(gsCurrentDir + "\\System\\NGTraySort.ini");
	if (!INI_NG.Check_File()) {
		g_objLogFile.Save_HandlerLog("NGTraySort.ini File Not Found!!!");
		AfxMessageBox("NGTraySort.ini File Not Found!!!");
		return FALSE;
	}
	for(int i=0; i<10; i++) {
		strKey.Format("%02d", i+1);
		strData = INI_NG.Get_String("NGTRAY", strKey, "");

		char chSep = ',';
		int  x = 3;
		for(int j=0; j<4; j++) {
			AfxExtractSubString(strTemp, strData, j, chSep);
			if		(strTemp == "A") m_EquipData.nTrayBase[i][x] = 11;	//허수불량,MES_NG
			else if (strTemp == "B") m_EquipData.nTrayBase[i][x] = 12;	//BARCODE_NOREAD
			else if (strTemp == "C") m_EquipData.nTrayBase[i][x] = 15;	//Marginal
			else					 m_EquipData.nTrayBase[i][x] = atoi(strTemp);
			x--;
			if (strTemp.GetLength() != 1) {
				g_objLogFile.Save_HandlerLog("NGTraySort.ini File Data Error..!!");
				AfxMessageBox("NGTraySort.ini File Data Error..!!");
				return FALSE;
			}
		}
	}
	// Value Validation Check
	int nValue[20] = { 0, };
	for(int i=0; i<10; i++) {
		for(int j=0; j<4; j++) {
			if (m_EquipData.nTrayBase[i][j] < 0 || m_EquipData.nTrayBase[i][j] > 15) {
				g_objLogFile.Save_HandlerLog("NGTraySort.ini File Data Error..!!!");
				return FALSE;
			}
			int nNo = m_EquipData.nTrayBase[i][j];
			nValue[nNo] = 1;
		}
	}
	// 0:공백, 3:NG, ROS-NG, 4:ROS재검, ROS Timeout
	// 5:GRAB_FAIL, ROI_FAIL, MCBTM, Vision Result Timeout
	// A:허수불량, MES_NG, B:BARCODE_NOREAD,
	// C:Marginal
	if (nValue[1] == 1 || nValue[2] == 1 || nValue[3] == 0 || nValue[4] == 0 || nValue[5] == 0 ||
		nValue[6] == 1 || nValue[7] == 1 || nValue[8] == 1 || nValue[9] == 1 || nValue[10] == 1 ||
		nValue[11] == 0 || nValue[12] == 0 || nValue[15] == 0) {
		g_objLogFile.Save_HandlerLog("NGTraySort.ini File Data Error..!!!!!!!!!");
		AfxMessageBox("NGTraySort.ini File Data Error..!!!!!!!!!");
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
