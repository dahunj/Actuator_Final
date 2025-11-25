// AJinAXL.cpp : 구현 파일
//
#include "stdafx.h"
#include "AJinAXL.h"
#include "CMAI2100.h"
#include <math.h>

// AJin Board Library
#include "AXL.h"
#include "AXM.h"
#include "AXD.h"
#include "AXDev.h"
#pragma comment (lib, "AXL.lib")

#define DPRAM_COMMON_CMD_SIIIH_SCAN		0x74
#define RESCAN_TIMEOUT					20000
#define RESCAN_MAX_TIME					10000

CAJinAXL g_objAJinAXL;

CAJinAXL::CAJinAXL(void)
{
	for (int i = 0; i < DIO_MODULE_COUNT; i++) { DXY_DATA *pDX = Get_pDX(i); pDX->nValue = 0; }
	for (int i = 0; i < DIO_MODULE_COUNT; i++) { DXY_DATA *pDY = Get_pDY(i); pDY->nValue = 0; }

	for (int i = 0; i < AXIS_COUNT; i++) m_strAxisName[i] = _T("");

	m_pThreadAJin = NULL;
	m_bThreadAJin = FALSE;

	m_bReadVelocity = FALSE;
}

CAJinAXL::~CAJinAXL(void)
{
}

BOOL CAJinAXL::Initialize()
{
#ifdef AJIN_BOARD_USE
	DWORD dwReturn;

	dwReturn = AxlOpenNoReset(7);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;

	// DIO
	long lDIOCount;
	dwReturn = AxdInfoGetModuleCount(&lDIOCount);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;
	if (lDIOCount < DIO_MODULE_COUNT) return FALSE;

	Read_Input();
	Read_Output();

	// Door Interlock
	m_DY14.oModeSelect = TRUE; Write_Output(14); theApp.uSleep(500);
	m_DY14.oSafetyReset = TRUE;  Write_Output(14); theApp.uSleep(500);
	m_DY14.oSafetyReset = FALSE; Write_Output(14); theApp.uSleep(500);
	m_DY14.oSafetyReset = TRUE;  Write_Output(14); theApp.uSleep(500);
	m_DY14.oSafetyReset = FALSE; Write_Output(14); theApp.uSleep(500);
	m_DY04.oLoadIonizerOn = TRUE; Write_Output(4);
	m_DY12.oGoodIonizerOn = TRUE; Write_Output(12);
/*
	// 네트워크 통신 에러 추가
	if (!g_objAJinAXL.Device_Check()) {
		HWND pWnd = ::FindWindow(NULL,"Splash");

		::PostMessage(pWnd, UM_DEVICE_SCAN, (WPARAM)1, NULL);

		if (!g_objAJinAXL.Device_Rescan()) {
			if (gData.nLanguage == 0) AfxMessageBox("AJin SSCNET 보드 재검색에 실패하였습니다.");
			else					  AfxMessageBox("AJin SSCNET board rescan failed.");
			return FALSE;
		}

		::PostMessage(pWnd, UM_DEVICE_SCAN, (WPARAM)0, NULL);
	}
*/
	Alarm_Reset(-1);	// All Reset
	
	// Motion
	long lAxisCount;
	dwReturn = AxmInfoGetAxisCount(&lAxisCount);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;
	if (lAxisCount < AXIS_COUNT) return FALSE;

	CString strMotFile = gsCurrentDir + "\\System\\AJinSetting.mot";
	dwReturn = AxmMotLoadParaAll((LPSTR)(LPCSTR)strMotFile);
	if (dwReturn != AXT_RT_SUCCESS) return FALSE;
#else
	Sim_SetOutToIn(99);
#endif

	Read_AxisList();	// Axis Name & Param

	for (long i = 0; i < AXIS_COUNT; i++) Set_ServoOn(i);

	m_bThreadAJin = TRUE;
	m_pThreadAJin = AfxBeginThread(Thread_AJin, NULL);

	return TRUE;
}

void CAJinAXL::Terminate()
{
	if (m_pThreadAJin) {
		m_bThreadAJin = FALSE;
		WaitForSingleObject(m_pThreadAJin->m_hThread, INFINITE);
	}

	for (long i = 0; i < AXIS_COUNT; i++) Set_ServoOff(i);

#ifdef AJIN_BOARD_USE
	if (AxlIsOpened()) AxlClose();
#endif
}

BOOL CAJinAXL::Device_Check()
{
#ifdef AJIN_BOARD_USE
//	int nAxis[3] = { 31, 42, 87 };	// 각 보드의 마지막 축
	Read_MotionStatus();
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (Get_AmpAlarm(i)) return FALSE;
	}
#endif
	return TRUE;
}

BOOL CAJinAXL::Device_Rescan()
{
#ifdef AJIN_BOARD_USE
	for (int i = 0; i < AXIS_COUNT; i++) AxmMoveEStop(i);
	Sleep(200);
	for (int i = 0; i < AXIS_COUNT; i++) AxmSignalServoAlarmReset(i, TRUE);
	Sleep(200);
	for (int i = 0; i < AXIS_COUNT; i++) AxmSignalServoAlarmReset(i, FALSE);

	return Device_Check();
#endif
	return TRUE;
}

void CAJinAXL::Read_Input()
{
#ifdef AJIN_BOARD_USE
	AxdiReadInportDword( 0, 0, &m_DX00.nValue);
	AxdiReadInportDword( 1, 0, &m_DX01.nValue);
	AxdiReadInportDword( 2, 0, &m_DX02.nValue);
	AxdiReadInportDword( 3, 0, &m_DX03.nValue);
	AxdiReadInportDword( 4, 0, &m_DX04.nValue);
	AxdiReadInportDword( 5, 0, &m_DX05.nValue);
	AxdiReadInportDword( 6, 0, &m_DX06.nValue);
	AxdiReadInportDword( 7, 0, &m_DX07.nValue);
	AxdiReadInportDword( 8, 0, &m_DX08.nValue);
	AxdiReadInportDword( 9, 0, &m_DX09.nValue);
	AxdiReadInportDword(10, 0, &m_DX10.nValue);
	AxdiReadInportDword(11, 0, &m_DX11.nValue);
	AxdiReadInportDword(12, 0, &m_DX12.nValue);
	AxdiReadInportDword(13, 0, &m_DX13.nValue);
	AxdiReadInportDword(14, 0, &m_DX14.nValue);
#endif
}

void CAJinAXL::Read_Output()
{
#ifdef AJIN_BOARD_USE
	AxdoReadOutportDword(15, 0, &m_DY00.nValue);
	AxdoReadOutportDword(16, 0, &m_DY01.nValue);
	AxdoReadOutportDword(17, 0, &m_DY02.nValue);
	AxdoReadOutportDword(18, 0, &m_DY03.nValue);
	AxdoReadOutportDword(19, 0, &m_DY04.nValue);
	AxdoReadOutportDword(20, 0, &m_DY05.nValue);
	AxdoReadOutportDword(21, 0, &m_DY06.nValue);
	AxdoReadOutportDword(22, 0, &m_DY07.nValue);
	AxdoReadOutportDword(23, 0, &m_DY08.nValue);
	AxdoReadOutportDword(24, 0, &m_DY09.nValue);
	AxdoReadOutportDword(25, 0, &m_DY10.nValue);
	AxdoReadOutportDword(26, 0, &m_DY11.nValue);
	AxdoReadOutportDword(27, 0, &m_DY12.nValue);
	AxdoReadOutportDword(28, 0, &m_DY13.nValue);
	AxdoReadOutportDword(29, 0, &m_DY14.nValue);
#endif
}

void CAJinAXL::Write_Output(int nModule)
{
#ifdef AJIN_BOARD_USE
	if (nModule ==  0) AxdoWriteOutportDword(15, 0, m_DY00.nValue);
	if (nModule ==  1) AxdoWriteOutportDword(16, 0, m_DY01.nValue);
	if (nModule ==  2) AxdoWriteOutportDword(17, 0, m_DY02.nValue);
	if (nModule ==  3) AxdoWriteOutportDword(18, 0, m_DY03.nValue);
	if (nModule ==  4) AxdoWriteOutportDword(19, 0, m_DY04.nValue);
	if (nModule ==  5) AxdoWriteOutportDword(20, 0, m_DY05.nValue);
	if (nModule ==  6) AxdoWriteOutportDword(21, 0, m_DY06.nValue);
	if (nModule ==  7) AxdoWriteOutportDword(22, 0, m_DY07.nValue);
	if (nModule ==  8) AxdoWriteOutportDword(23, 0, m_DY08.nValue);
	if (nModule ==  9) AxdoWriteOutportDword(24, 0, m_DY09.nValue);
	if (nModule == 10) AxdoWriteOutportDword(25, 0, m_DY10.nValue);
	if (nModule == 11) AxdoWriteOutportDword(26, 0, m_DY11.nValue);
	if (nModule == 12) AxdoWriteOutportDword(27, 0, m_DY12.nValue);
	if (nModule == 13) AxdoWriteOutportDword(28, 0, m_DY13.nValue);
	if (nModule == 14) AxdoWriteOutportDword(29, 0, m_DY14.nValue);
#else
	Sim_SetOutToIn(nModule);
#endif
}

void CAJinAXL::Read_MotionStatus()
{
#ifdef AJIN_BOARD_USE
	DWORD dwStatus;
	for (int i = 0; i < AXIS_COUNT; i++) {
		// Position Reading
		//if (Is_ServoAxis(i)) AxmStatusGetActPos(i, &m_Status[i].dPos);
		//else AxmStatusGetCmdPos(i, &m_Status[i].dPos);
		AxmStatusGetActPos(i, &m_Status[i].dPos);

		// Velocity Reading
		if (m_bReadVelocity) AxmStatusReadVel(i, &m_Status[i].dVel);

		// Servo-On Reading
		AxmSignalIsServoOn(i, &dwStatus);
		m_Status[i].bSOn = (BOOL)dwStatus;

		// Origin Limit
		AxmSignalReadInputBit(i, UIO_INP0, &dwStatus);		// In0 : Home
		m_Status[i].bOrg = (BOOL)dwStatus;

		// Mechanical Input
		AxmStatusReadMechanical(i, &dwStatus);
		
		// Positive Limit
		m_Status[i].bELP = (BOOL)((dwStatus >> 0) & 1);	// bit0

		// Negative Limit
		m_Status[i].bELN = (BOOL)((dwStatus >> 1) & 1);	// bit1

		// Alarm
		m_Status[i].bALM = (BOOL)((dwStatus >> 4) & 1);	// bit4

		// In-Position
		m_Status[i].bInP = (BOOL)((dwStatus >> 5) & 1);	// bit5

		// Motion Running
		AxmStatusReadInMotion(i, &dwStatus);
		m_Status[i].bRun = (BOOL)dwStatus;

		// Home Done
		AxmHomeGetResult(i, &dwStatus);
		m_Status[i].bHom = (dwStatus == HOME_SUCCESS ? TRUE : FALSE);
	}
#endif
}

void CAJinAXL::Set_ServoOn(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveEStop(nAxis);
	AxmSignalServoOn(nAxis, TRUE);
#else
	m_Status[nAxis].bSOn = TRUE;
#endif
}

void CAJinAXL::Set_ServoOff(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveEStop(nAxis);
	AxmSignalServoOn(nAxis, FALSE);
#else
	m_Status[nAxis].bSOn = FALSE;
#endif
}

void CAJinAXL::Set_EncoderType(int nAxis, int nType)
{
	if (gData.nLanguage == 0) return;	//구미는 미적용
#ifdef AJIN_BOARD_USE
	AxmSignalSetEncoderType(nAxis, nType);	// ENCODER_TYPE_INCREMENTAL(0), ENCODER_TYPE_ABSOLUTE(1)
	Sleep(10);		// 추가 2017.07.28
#endif
}

BOOL CAJinAXL::Get_EncoderTypeInc(int nAxis)
{
	if (gData.nLanguage == 0) return TRUE;
#ifdef AJIN_BOARD_USE
	DWORD dwpEncoderType;
	AxmSignalGetEncoderType(nAxis, &dwpEncoderType);	// ENCODER_TYPE_INCREMENTAL(0), ENCODER_TYPE_ABSOLUTE(1)
	if (dwpEncoderType == ENCODER_TYPE_INCREMENTAL) return TRUE;
	return FALSE;
#endif
	return TRUE;
}

BOOL CAJinAXL::Get_EncoderTypeAbs(int nAxis)
{
	if (gData.nLanguage == 0) return TRUE;
#ifdef AJIN_BOARD_USE
	DWORD dwpEncoderType;
	AxmSignalGetEncoderType(nAxis, &dwpEncoderType);	// ENCODER_TYPE_INCREMENTAL(0), ENCODER_TYPE_ABSOLUTE(1)
	if (dwpEncoderType == ENCODER_TYPE_ABSOLUTE) return TRUE;
	return FALSE;
#endif
	return TRUE;
}

void CAJinAXL::Home_Search(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmHomeSetStart(nAxis);
	m_Status[nAxis].bHom = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	m_Status[nAxis].bHom = TRUE;
#endif
}

void CAJinAXL::Set_Home(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmStatusSetActPos(nAxis, 0.0);
	AxmStatusSetCmdPos(nAxis, 0.0);
	AxmHomeSetResult(nAxis, HOME_SUCCESS);
#endif
}

void CAJinAXL::Set_CVActPos(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmStatusSetActPos(nAxis, 0.0);
	AxmStatusSetCmdPos(nAxis, 0.0);
	Sleep(10);
#else
	Sim_SetMotion(1, nAxis, 0.0);
#endif
}

void CAJinAXL::Move_Absolute(int nAxis, double dPos, double dSpeed)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	if (dSpeed <= 0.0) dSpeed = 1.0;
	double	dVel = m_Param[nAxis].dSpeedM * dSpeed;
	double	dAcc = m_Param[nAxis].dAccel * dSpeed;
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(1, nAxis, dPos);
#endif
}

void CAJinAXL::Move_Relative(int nAxis, double dPos, double dSpeed)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_REL_MODE);
	if (dSpeed <= 0.0) dSpeed = 1.0;
	double	dVel = m_Param[nAxis].dSpeedM * dSpeed;
	double	dAcc = m_Param[nAxis].dAccel * dSpeed;
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(2, nAxis, dPos);
#endif
}

void CAJinAXL::Jog_Positive(int nAxis, double dSpeed)
{
#ifdef AJIN_BOARD_USE
	double	dVel = m_Param[nAxis].dSpeedJ;
	if (dSpeed >= 1.0) dVel = dSpeed;
	double	dAcc = dVel * 4.0;
	AxmMoveVel(nAxis, dVel, dAcc, dAcc);
#endif
}

void CAJinAXL::Jog_Negative(int nAxis, double dSpeed)
{
#ifdef AJIN_BOARD_USE
	double	dVel = m_Param[nAxis].dSpeedJ;
	if (dSpeed >= 1.0) dVel = dSpeed;
	double	dAcc = dVel * 4.0;
	AxmMoveVel(nAxis, (dVel*-1.0), dAcc, dAcc);
#endif
}

void CAJinAXL::Stop_Motion(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveSStop(nAxis);
#endif
}

void CAJinAXL::EStop_Motion(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmMoveEStop(nAxis);
#endif
}

void CAJinAXL::Alarm_Reset(int nAxis)
{
#ifdef AJIN_BOARD_USE
	int nAxStart = (nAxis == -1 ? 0 : nAxis);
	int nAxEnd = (nAxis == -1 ? AXIS_COUNT : nAxis + 1);
	for (int i = nAxStart; i < nAxEnd; i++) AxmMoveEStop(i);
	Sleep(200);
	for (int i = nAxStart; i < nAxEnd; i++) AxmSignalServoAlarmReset(i, TRUE);
	Sleep(200);
	for (int i = nAxStart; i < nAxEnd; i++) AxmSignalServoAlarmReset(i, FALSE);
#endif
}

void CAJinAXL::Move_Abs_Override(int nAxis, double dPos, double dAt, double dSpeed)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	double dVel = m_Param[nAxis].dSpeedM;
	double dAcc = m_Param[nAxis].dAccel;
	double dMaxVel;
	AxmMotGetMaxVel(nAxis, &dMaxVel);

	AxmOverrideSetMaxVel(nAxis, dMaxVel);	// 오버라이드 최대값 설정
	AxmOverrideVelAtPos (nAxis, dPos, dVel, dAcc, dAcc, dAt, dVel*dSpeed, COMMAND);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#else
	Sim_SetMotion(3, nAxis, dPos);
#endif
}

void CAJinAXL::Move_Rel_Override(int nAxis, double dPos, double dAt)
{
#ifdef AJIN_BOARD_USE
	AxmMotSetAbsRelMode(nAxis, POS_REL_MODE);
	double	dVel = m_Param[nAxis].dSpeedM;
	double	dAcc = m_Param[nAxis].dAccel;
	double dMaxVel;
	AxmMotGetMaxVel(nAxis, &dMaxVel);
	
	AxmOverrideSetMaxVel(nAxis, dMaxVel);	// 오버라이드 최대값 설정
	AxmOverrideVelAtPos (nAxis, dPos, dVel, dAcc, dAcc, dAt, dVel/5.0, COMMAND);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#endif
}

BOOL CAJinAXL::Is_Done(int nAxis)
{
#ifdef AJIN_BOARD_USE
	if (m_Status[nAxis].bRun) return FALSE;
	if (!m_Status[nAxis].bInP) return FALSE;
#endif
	return TRUE;
}

BOOL CAJinAXL::Is_Home(int nAxis)
{
#ifdef AJIN_BOARD_USE
	if (!m_Status[nAxis].bHom) return FALSE;
	if (m_Status[nAxis].bRun) return FALSE;
#endif
	return TRUE;
}

BOOL CAJinAXL::Is_MoveDone(int nAxis, double dPos, double dRange)
{
#ifdef AJIN_BOARD_USE
	if (!Is_Done(nAxis)) return FALSE;
	if (fabs(m_Status[nAxis].dPos - dPos) > dRange) return FALSE;
#endif
	return TRUE;
}

void CAJinAXL::Start_Trigger(int nAxis, double dStartPos, double dEndPos, double dPeriod, double dWidth)
{
#ifdef AJIN_BOARD_USE
	AxmTriggerSetReset(nAxis);

	double dTrigTime = dWidth / m_Param[nAxis].dSpeedM * 1000000.0;	// mm->usec

	// 1. Command Position ****************************************************
// 	AxmTriggerSetTimeLevel(nAxis, dTrigTime, HIGH, COMMAND, DISABLE);
	// 2. Actual Position *****************************************************
	AxmTriggerSetTimeLevel(nAxis, dTrigTime, HIGH, ACTUAL, DISABLE);
	//*************************************************************************
	
	DWORD dwCode = AxmTriggerSetBlock(nAxis, dStartPos, dEndPos, dPeriod);
	if (dwCode != AXT_RT_SUCCESS) AfxMessageBox("Trigger Setting Error");
#endif
}

void CAJinAXL::Stop_Trigger(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmTriggerSetReset(nAxis);
#endif
}

void CAJinAXL::Start_Scan(int nAxis, double dPos, double dVel, double dTrigStart, double dTrigEnd, double dPeriod, double dWidth)
{
#ifdef AJIN_BOARD_USE
	// Trigger Setting
	AxmTriggerSetReset(nAxis);
	
	dPeriod /= 1000;
	dWidth /= 1000;

	double dTrigTime = dWidth / dVel * 1000000.0;	// mm->usec

	//dTrigTime = 20.0;	// mm->usec

	// 1. Command Position ****************************************************
// 	AxmTriggerSetTimeLevel(nAxis, dTrigTime, HIGH, COMMAND, DISABLE);
	// 2. Actual Position *****************************************************
	AxmTriggerSetTimeLevel(nAxis, dTrigTime, HIGH, ACTUAL, DISABLE);
	//*************************************************************************
	
	DWORD dwCode = AxmTriggerSetBlock(nAxis, dTrigStart, dTrigEnd, dPeriod);
	if (dwCode != AXT_RT_SUCCESS) AfxMessageBox("Trigger Setting Error");

	// Scan Move
	AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	double	dAcc = dVel * 10.0;
	AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	m_Status[nAxis].bInP = FALSE; m_Status[nAxis].bRun = TRUE;
#endif
}

void CAJinAXL::Stop_Scan(int nAxis)
{
#ifdef AJIN_BOARD_USE
	AxmTriggerSetReset(nAxis);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Motion Param Read / Write Function

void CAJinAXL::Read_AxisList()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\AxisList.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("AxisList.ini File Not Found!!!");
		return;
	}

	CString strSection, strName;
	for (int i = 0; i < AXIS_COUNT; i++) {
		strSection.Format("AXIS_%02d", i);

		strName = INI.Get_String(strSection, "NAME", "");
		m_strAxisName[i].Format("[%02d] %s", i, strName);
		m_Param[i].dSpeedM = INI.Get_Double(strSection, "MOVE", 0.0);
		m_Param[i].dSpeedJ = INI.Get_Double(strSection, "JOG", 0.0);
		m_Param[i].dAccel = INI.Get_Double(strSection, "ACC", 0.0);
	}
}

void CAJinAXL::Read_MotionParam(int nAxis)
{
	CIniFileCS INI(gsCurrentDir + "\\System\\AxisList.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("AxisList.ini File Not Found!!!");
		return;
	}
	
	CString strSection;
	strSection.Format("AXIS_%02d", nAxis);
	m_Param[nAxis].dSpeedM = INI.Get_Double(strSection, "MOVE", 0.0);
	m_Param[nAxis].dSpeedJ = INI.Get_Double(strSection, "JOG", 0.0);
	m_Param[nAxis].dAccel = INI.Get_Double(strSection, "ACC", 0.0);
}

void CAJinAXL::Save_MotionParam(int nAxis, double dSpeedM, double dSpeedJ, double dAccel)
{
	CIniFileCS INI(gsCurrentDir + "\\System\\AxisList.ini");
	if (!INI.Check_File()) {
		AfxMessageBox("AxisList.ini File Not Found!!!");
		return;
	}
	
	CString strSection;
	strSection.Format("AXIS_%02d", nAxis);
	INI.Set_Double(strSection, "MOVE", dSpeedM, "%0.3lf");
	INI.Set_Double(strSection, "JOG", dSpeedJ, "%0.3lf");
	INI.Set_Double(strSection, "ACC", dAccel, "%0.3lf");
}

/////////////////////////////////////////////////////////////////////////////
// Thread Function 
UINT CAJinAXL::Thread_AJin(LPVOID lpVoid)
{
	while (g_objAJinAXL.m_bThreadAJin) {
		g_objAJinAXL.Read_Input();
		g_objAJinAXL.Read_MotionStatus();
		Sleep(5);
	}
	g_objAJinAXL.m_bThreadAJin = FALSE;
	g_objAJinAXL.m_pThreadAJin = NULL;
	return 0;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CAJinAXL::Is_ServoAxis(int nAxis)
{
	return TRUE;
}

BOOL CAJinAXL::Use_OrgAxis(int nAxis)
{
	return FALSE;

	switch (nAxis) {
	case AX_LOAD_PICKER_P1:
	case AX_LOAD_PICKER_P2:
	case AX_UNLOAD_PICKER_P1:
	case AX_UNLOAD_PICKER_P2:
		return TRUE;
	default:
		return FALSE;
	}
}

BOOL CAJinAXL::Use_ElpAxis(int nAxis)
{
	if (Use_OrgAxis(nAxis)) return FALSE;
	else return TRUE;
}

BOOL CAJinAXL::Use_ElnAxis(int nAxis)
{
	if (Use_OrgAxis(nAxis)) return FALSE;
	else return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

DXY_DATA *CAJinAXL::Get_pDX(int nIndex)
{
	if (nIndex ==  0) return (DXY_DATA*)&m_DX00;
	if (nIndex ==  1) return (DXY_DATA*)&m_DX01;
	if (nIndex ==  2) return (DXY_DATA*)&m_DX02;
	if (nIndex ==  3) return (DXY_DATA*)&m_DX03;
	if (nIndex ==  4) return (DXY_DATA*)&m_DX04;
	if (nIndex ==  5) return (DXY_DATA*)&m_DX05;
	if (nIndex ==  6) return (DXY_DATA*)&m_DX06;
	if (nIndex ==  7) return (DXY_DATA*)&m_DX07;
	if (nIndex ==  8) return (DXY_DATA*)&m_DX08;
	if (nIndex ==  9) return (DXY_DATA*)&m_DX09;
	if (nIndex == 10) return (DXY_DATA*)&m_DX10;
	if (nIndex == 11) return (DXY_DATA*)&m_DX11;
	if (nIndex == 12) return (DXY_DATA*)&m_DX12;
	if (nIndex == 13) return (DXY_DATA*)&m_DX13;
	if (nIndex == 14) return (DXY_DATA*)&m_DX14;
	return NULL;
}

DXY_DATA *CAJinAXL::Get_pDY(int nIndex)
{
	if (nIndex ==  0) return (DXY_DATA*)&m_DY00;
	if (nIndex ==  1) return (DXY_DATA*)&m_DY01;
	if (nIndex ==  2) return (DXY_DATA*)&m_DY02;
	if (nIndex ==  3) return (DXY_DATA*)&m_DY03;
	if (nIndex ==  4) return (DXY_DATA*)&m_DY04;
	if (nIndex ==  5) return (DXY_DATA*)&m_DY05;
	if (nIndex ==  6) return (DXY_DATA*)&m_DY06;
	if (nIndex ==  7) return (DXY_DATA*)&m_DY07;
	if (nIndex ==  8) return (DXY_DATA*)&m_DY08;
	if (nIndex ==  9) return (DXY_DATA*)&m_DY09;
	if (nIndex == 10) return (DXY_DATA*)&m_DY10;
	if (nIndex == 11) return (DXY_DATA*)&m_DY11;
	if (nIndex == 12) return (DXY_DATA*)&m_DY12;
	if (nIndex == 13) return (DXY_DATA*)&m_DY13;
	if (nIndex == 14) return (DXY_DATA*)&m_DY14;
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void CAJinAXL::Sim_SetMotion(int nNo, int nAxis, double dPos)
{
	Sleep(SIM_WAITTIMEM);
	if		(nNo == 1)	g_objAJinAXL.m_Status[nAxis].dPos = dPos;
	else if (nNo == 2)	g_objAJinAXL.m_Status[nAxis].dPos = g_objAJinAXL.m_Status[nAxis].dPos + dPos;
	else if (nNo == 3)	g_objAJinAXL.m_Status[nAxis].dPos = dPos;
}

void CAJinAXL::Sim_SetOutToIn(int nNo)
{
	Sleep(SIM_WAITTIMES);
	BOOL bT = TRUE;
	BOOL bF = FALSE;

	if (nNo==0) {
		m_DX00.iElevator1Clamp1On	= m_DY00.oElevator1Clamp1On;
		m_DX00.iElevator1Clamp1Off	= m_DY00.oElevator1Clamp1Off;
		m_DX00.iElevator1Clamp2On	= m_DY00.oElevator1Clamp2On;
		m_DX00.iElevator1Clamp2Off	= m_DY00.oElevator1Clamp2Off;
		m_DX00.iElevator2Clamp1On	= m_DY00.oElevator2Clamp1On;
		m_DX00.iElevator2Clamp1Off	= m_DY00.oElevator2Clamp1Off;
		m_DX00.iElevator2Clamp2On	= m_DY00.oElevator2Clamp2On;
		m_DX00.iElevator2Clamp2Off	= m_DY00.oElevator2Clamp2Off;

		m_DX00.iElevator1SlideLock	= m_DY00.oElevator1SlideLock;
		m_DX00.iElevator1SlideUnlock= m_DY00.oElevator1SlideUnlock;
	}
	if (nNo==1) {
		m_DX01.iElevator3Clamp1On	= m_DY01.oElevator3Clamp1On;
		m_DX01.iElevator3Clamp1Off	= m_DY01.oElevator3Clamp1Off;
		m_DX01.iElevator3Clamp2On	= m_DY01.oElevator3Clamp2On;
		m_DX01.iElevator3Clamp2Off	= m_DY01.oElevator3Clamp2Off;
		m_DX01.iElevator4Clamp1On	= m_DY01.oElevator4Clamp1On;
		m_DX01.iElevator4Clamp1Off	= m_DY01.oElevator4Clamp1Off;
		m_DX01.iElevator4Clamp2On	= m_DY01.oElevator4Clamp2On;
		m_DX01.iElevator4Clamp2Off	= m_DY01.oElevator4Clamp2Off;

		m_DX00.iElevator2SlideLock	= m_DY01.oElevator2SlideLock;
		m_DX00.iElevator2SlideUnlock= m_DY01.oElevator2SlideUnlock;
		m_DX01.iElevator3SlideLock	= m_DY01.oElevator3SlideLock;
		m_DX01.iElevator3SlideUnlock= m_DY01.oElevator3SlideUnlock;
	}
	if (nNo==2) {
		m_DX02.iElevator5Clamp1On	= m_DY02.oElevator5Clamp1On;
		m_DX02.iElevator5Clamp1Off	= m_DY02.oElevator5Clamp1Off;
		m_DX02.iElevator5Clamp2On	= m_DY02.oElevator5Clamp2On;
		m_DX02.iElevator5Clamp2Off	= m_DY02.oElevator5Clamp2Off;

		m_DX01.iElevator4SlideLock	= m_DY02.oElevator4SlideLock;
		m_DX01.iElevator4SlideUnlock= m_DY02.oElevator4SlideUnlock;
		m_DX02.iElevator5SlideLock	= m_DY02.oElevator5SlideLock;
		m_DX02.iElevator5SlideUnlock= m_DY02.oElevator5SlideUnlock;
		m_DX02.iElevator6SlideLock	= m_DY02.oElevator6SlideLock;
		m_DX02.iElevator6SlideUnlock= m_DY02.oElevator6SlideUnlock;
	}
	if (nNo==3) {
		m_DX03.iTransferLGrab1Open	= m_DY03.oTransferLGrabOpen;
		m_DX03.iTransferLGrab1Close	= m_DY03.oTransferLGrabClose;
		m_DX03.iTransferLGrab2Open	= m_DY03.oTransferLGrabOpen;
		m_DX03.iTransferLGrab2Close	= m_DY03.oTransferLGrabClose;
		m_DX03.iTransferRGrab1Open	= m_DY03.oTransferRGrabOpen;
		m_DX03.iTransferRGrab1Close	= m_DY03.oTransferRGrabClose;
		m_DX03.iTransferRGrab2Open	= m_DY03.oTransferRGrabOpen;
		m_DX03.iTransferRGrab2Close	= m_DY03.oTransferRGrabClose;
		m_DX03.iAlignMasterIn		= m_DY03.oAlignMasterIn;
		m_DX03.iAlignMasterOut		= m_DY03.oAlignMasterOut;
		m_DX03.iAlignSlave1In		= m_DY03.oAlignSlave1In;
		m_DX03.iAlignSlave1Out		= m_DY03.oAlignSlave1Out;
		m_DX03.iAlignSlave2In		= m_DY03.oAlignSlave2In;
		m_DX03.iAlignSlave2Out		= m_DY03.oAlignSlave2Out;

		m_DX03.iElevator7SlideLock	= m_DY03.oElevator7SlideLock;
		m_DX03.iElevator7SlideUnlock= m_DY03.oElevator7SlideUnlock;
	}
	if (nNo==4) {
		m_DX04.iLoadStage1Up		= m_DY04.oLoadStage1Up;
		m_DX04.iLoadStage1Down		= m_DY04.oLoadStage1Down;
		m_DX04.iLoadStage1MasterOut	= m_DY04.oLoadStage1MasterOut;
		m_DX04.iLoadStage1MasterIn	= m_DY04.oLoadStage1MasterIn;
		m_DX04.iLoadStage1SlaveOut	= m_DY04.oLoadStage1SlaveOut; 
		m_DX04.iLoadStage1SlaveIn	= m_DY04.oLoadStage1SlaveIn;
		m_DX04.iLoadStage2Up		= m_DY04.oLoadStage2Up;	
		m_DX04.iLoadStage2Down		= m_DY04.oLoadStage2Down;
		m_DX04.iLoadStage2MasterOut	= m_DY04.oLoadStage2MasterOut;
		m_DX04.iLoadStage2MasterIn	= m_DY04.oLoadStage2MasterIn;
		m_DX04.iLoadStage2SlaveOut	= m_DY04.oLoadStage2SlaveOut;
		m_DX04.iLoadStage2SlaveIn	= m_DY04.oLoadStage2SlaveIn;
	}
	if (nNo==5) {
		m_DX05.iLoadPicker1Down1	= m_DY05.oLoadPicker1Down1;
		m_DX05.iLoadPicker1Up1		= m_DY05.oLoadPicker1Up1;
		m_DX05.iLoadPicker1Down2	= m_DY05.oLoadPicker1Down2;
		m_DX05.iLoadPicker1Up2		= m_DY05.oLoadPicker1Up2;
		m_DX05.iLoadPicker1Down3	= m_DY05.oLoadPicker1Down3;
		m_DX05.iLoadPicker1Up3		= m_DY05.oLoadPicker1Up3;
		m_DX05.iLoadPicker1Down4	= m_DY05.oLoadPicker1Down4;
		m_DX05.iLoadPicker1Up4		= m_DY05.oLoadPicker1Up4;
		m_DX05.iLoadPicker1Down5	= m_DY05.oLoadPicker1Down5;
		m_DX05.iLoadPicker1Up5		= m_DY05.oLoadPicker1Up5;
		m_DX05.iLoadPicker1Down6	= m_DY05.oLoadPicker1Down6;
		m_DX05.iLoadPicker1Up6		= m_DY05.oLoadPicker1Up6;
		m_DX05.iLoadPicker1Down7	= m_DY05.oLoadPicker1Down7;
		m_DX05.iLoadPicker1Up7		= m_DY05.oLoadPicker1Up7;
		m_DX05.iLoadPicker1Down8	= m_DY05.oLoadPicker1Down8;
		m_DX05.iLoadPicker1Up8		= m_DY05.oLoadPicker1Up8;
		m_DX05.iLoadPicker1Open1	= m_DY05.oLoadPicker1Open1;
		m_DX05.iLoadPicker1Open2	= m_DY05.oLoadPicker1Open2;
		m_DX05.iLoadPicker1Open3	= m_DY05.oLoadPicker1Open3;
		m_DX05.iLoadPicker1Open4	= m_DY05.oLoadPicker1Open4;
		m_DX05.iLoadPicker1Open5	= m_DY05.oLoadPicker1Open5;
		m_DX05.iLoadPicker1Open6	= m_DY05.oLoadPicker1Open6;
		m_DX05.iLoadPicker1Open7	= m_DY05.oLoadPicker1Open7;
		m_DX05.iLoadPicker1Open8	= m_DY05.oLoadPicker1Open8;

		if (m_DX05.iLoadPicker1Open1) m_DX05.iLoadPicker1Exist1 = FALSE; else m_DX05.iLoadPicker1Exist1 = TRUE;
		if (m_DX05.iLoadPicker1Open2) m_DX05.iLoadPicker1Exist2 = FALSE; else m_DX05.iLoadPicker1Exist2 = TRUE;
		if (m_DX05.iLoadPicker1Open3) m_DX05.iLoadPicker1Exist3 = FALSE; else m_DX05.iLoadPicker1Exist3 = TRUE;
		if (m_DX05.iLoadPicker1Open4) m_DX05.iLoadPicker1Exist4 = FALSE; else m_DX05.iLoadPicker1Exist4 = TRUE;
		if (m_DX05.iLoadPicker1Open5) m_DX05.iLoadPicker1Exist5 = FALSE; else m_DX05.iLoadPicker1Exist5 = TRUE;
		if (m_DX05.iLoadPicker1Open6) m_DX05.iLoadPicker1Exist6 = FALSE; else m_DX05.iLoadPicker1Exist6 = TRUE;
		if (m_DX05.iLoadPicker1Open7) m_DX05.iLoadPicker1Exist7 = FALSE; else m_DX05.iLoadPicker1Exist7 = TRUE;
		if (m_DX05.iLoadPicker1Open8) m_DX05.iLoadPicker1Exist8 = FALSE; else m_DX05.iLoadPicker1Exist8 = TRUE;
	}
	if (nNo==6) {
		m_DX06.iLoadPicker2Down1	= m_DY06.oLoadPicker2Down1;
		m_DX06.iLoadPicker2Up1		= m_DY06.oLoadPicker2Up1;
		m_DX06.iLoadPicker2Down2	= m_DY06.oLoadPicker2Down2;
		m_DX06.iLoadPicker2Up2		= m_DY06.oLoadPicker2Up2;
		m_DX06.iLoadPicker2Down3	= m_DY06.oLoadPicker2Down3;
		m_DX06.iLoadPicker2Up3		= m_DY06.oLoadPicker2Up3;
		m_DX06.iLoadPicker2Down4	= m_DY06.oLoadPicker2Down4;
		m_DX06.iLoadPicker2Up4		= m_DY06.oLoadPicker2Up4;
		m_DX06.iLoadPicker2Down5	= m_DY06.oLoadPicker2Down5;
		m_DX06.iLoadPicker2Up5		= m_DY06.oLoadPicker2Up5;
		m_DX06.iLoadPicker2Down6	= m_DY06.oLoadPicker2Down6;
		m_DX06.iLoadPicker2Up6		= m_DY06.oLoadPicker2Up6;
		m_DX06.iLoadPicker2Down7	= m_DY06.oLoadPicker2Down7;
		m_DX06.iLoadPicker2Up7		= m_DY06.oLoadPicker2Up7;
		m_DX06.iLoadPicker2Down8	= m_DY06.oLoadPicker2Down8;
		m_DX06.iLoadPicker2Up8		= m_DY06.oLoadPicker2Up8;
		m_DX06.iLoadPicker2Open1	= m_DY06.oLoadPicker2Open1;
		m_DX06.iLoadPicker2Open2	= m_DY06.oLoadPicker2Open2;
		m_DX06.iLoadPicker2Open3	= m_DY06.oLoadPicker2Open3;
		m_DX06.iLoadPicker2Open4	= m_DY06.oLoadPicker2Open4;
		m_DX06.iLoadPicker2Open5	= m_DY06.oLoadPicker2Open5;
		m_DX06.iLoadPicker2Open6	= m_DY06.oLoadPicker2Open6;
		m_DX06.iLoadPicker2Open7	= m_DY06.oLoadPicker2Open7;
		m_DX06.iLoadPicker2Open8	= m_DY06.oLoadPicker2Open8;

		if (m_DX06.iLoadPicker2Open1) m_DX06.iLoadPicker2Exist1 = FALSE; else m_DX06.iLoadPicker2Exist1 = TRUE;
		if (m_DX06.iLoadPicker2Open2) m_DX06.iLoadPicker2Exist2 = FALSE; else m_DX06.iLoadPicker2Exist2 = TRUE;
		if (m_DX06.iLoadPicker2Open3) m_DX06.iLoadPicker2Exist3 = FALSE; else m_DX06.iLoadPicker2Exist3 = TRUE;
		if (m_DX06.iLoadPicker2Open4) m_DX06.iLoadPicker2Exist4 = FALSE; else m_DX06.iLoadPicker2Exist4 = TRUE;
		if (m_DX06.iLoadPicker2Open5) m_DX06.iLoadPicker2Exist5 = FALSE; else m_DX06.iLoadPicker2Exist5 = TRUE;
		if (m_DX06.iLoadPicker2Open6) m_DX06.iLoadPicker2Exist6 = FALSE; else m_DX06.iLoadPicker2Exist6 = TRUE;
		if (m_DX06.iLoadPicker2Open7) m_DX06.iLoadPicker2Exist7 = FALSE; else m_DX06.iLoadPicker2Exist7 = TRUE;
		if (m_DX06.iLoadPicker2Open8) m_DX06.iLoadPicker2Exist8 = FALSE; else m_DX06.iLoadPicker2Exist8 = TRUE;
	}
	if (nNo==7) {
		m_DX07.iInspectStage1Up		= m_DY07.oInspectStage1Up;	
		m_DX07.iInspectStage1Down	= m_DY07.oInspectStage1Down;
		m_DX07.iInspectStage1Deg90	= m_DY07.oInspectStage1Deg90;
		m_DX07.iInspectStage1Deg0	= m_DY07.oInspectStage1Deg0;
		m_DX07.iInspectStage1Yin	= m_DY07.oInspectStage1Yin;
		m_DX07.iInspectStage1YOut	= m_DY07.oInspectStage1YOut;
		m_DX07.iInspectStage1Vac1On	= m_DY07.oInspectStage1Vac1On;
		m_DX07.iInspectStage1Vac2On	= m_DY07.oInspectStage1Vac2On;
		m_DX07.iInspectStage1Vac3On	= m_DY07.oInspectStage1Vac3On;
		m_DX07.iInspectStage1Vac4On	= m_DY07.oInspectStage1Vac4On;
		m_DX07.iInspectStage1Vac5On	= m_DY07.oInspectStage1Vac5On;
		m_DX07.iInspectStage1Vac6On	= m_DY07.oInspectStage1Vac6On;
		m_DX07.iInspectStage1Vac7On	= m_DY07.oInspectStage1Vac7On;
		m_DX07.iInspectStage1Vac8On	= m_DY07.oInspectStage1Vac8On;
		m_DX07.iInspectStage2Up		= m_DY07.oInspectStage2Up;
		m_DX07.iInspectStage2Down	= m_DY07.oInspectStage2Down;
		m_DX07.iInspectStage2Deg90	= m_DY07.oInspectStage2Deg90;
		m_DX07.iInspectStage2Deg0	= m_DY07.oInspectStage2Deg0;
		m_DX07.iInspectStage2Vac1On	= m_DY07.oInspectStage2Vac1On;
		m_DX07.iInspectStage2Vac2On	= m_DY07.oInspectStage2Vac2On;
		m_DX07.iInspectStage2Vac3On	= m_DY07.oInspectStage2Vac3On;
		m_DX07.iInspectStage2Vac4On	= m_DY07.oInspectStage2Vac4On;
		m_DX07.iInspectStage2Vac5On	= m_DY07.oInspectStage2Vac5On;
		m_DX07.iInspectStage2Vac6On	= m_DY07.oInspectStage2Vac6On;
		m_DX07.iInspectStage2Vac7On	= m_DY07.oInspectStage2Vac7On;
		m_DX07.iInspectStage2Vac8On	= m_DY07.oInspectStage2Vac8On;
	}
	if (nNo==8) {
		m_DX08.iInspectStage3Up		= m_DY08.oInspectStage3Up;
		m_DX08.iInspectStage3Down	= m_DY08.oInspectStage3Down;
		m_DX08.iInspectStage3Deg90	= m_DY08.oInspectStage3Deg90;
		m_DX08.iInspectStage3Deg0	= m_DY08.oInspectStage3Deg0;
		m_DX08.iInspectStage3Vac1On	= m_DY08.oInspectStage3Vac1On;
		m_DX08.iInspectStage3Vac2On	= m_DY08.oInspectStage3Vac2On;
		m_DX08.iInspectStage3Vac3On	= m_DY08.oInspectStage3Vac3On;
		m_DX08.iInspectStage3Vac4On	= m_DY08.oInspectStage3Vac4On;
		m_DX08.iInspectStage3Vac5On	= m_DY08.oInspectStage3Vac5On;
		m_DX08.iInspectStage3Vac6On	= m_DY08.oInspectStage3Vac6On;
		m_DX08.iInspectStage3Vac7On	= m_DY08.oInspectStage3Vac7On;
		m_DX08.iInspectStage3Vac8On	= m_DY08.oInspectStage3Vac8On;
		m_DX08.iInspectStage4Up		= m_DY08.oInspectStage4Up;
		m_DX08.iInspectStage4Down	= m_DY08.oInspectStage4Down;
		m_DX08.iInspectStage4Deg90	= m_DY08.oInspectStage4Deg90;
		m_DX08.iInspectStage4Deg0	= m_DY08.oInspectStage4Deg0;
		m_DX08.iInspectStage4Yin	= m_DY08.oInspectStage4Yin;
		m_DX08.iInspectStage4YOut	= m_DY08.oInspectStage4YOut;
		m_DX08.iInspectStage4Vac1On	= m_DY08.oInspectStage4Vac1On;
		m_DX08.iInspectStage4Vac2On	= m_DY08.oInspectStage4Vac2On;
		m_DX08.iInspectStage4Vac3On	= m_DY08.oInspectStage4Vac3On;
		m_DX08.iInspectStage4Vac4On	= m_DY08.oInspectStage4Vac4On;
		m_DX08.iInspectStage4Vac5On	= m_DY08.oInspectStage4Vac5On;
		m_DX08.iInspectStage4Vac6On	= m_DY08.oInspectStage4Vac6On;
		m_DX08.iInspectStage4Vac7On	= m_DY08.oInspectStage4Vac7On;
		m_DX08.iInspectStage4Vac8On	= m_DY08.oInspectStage4Vac8On;
	}
	if (nNo==9) {
		m_DX09.iUnloadPicker1Down1	= m_DY09.oUnloadPicker1Down1;
		m_DX09.iUnloadPicker1Up1	= m_DY09.oUnloadPicker1Up1;
		m_DX09.iUnloadPicker1Down2	= m_DY09.oUnloadPicker1Down2;
		m_DX09.iUnloadPicker1Up2	= m_DY09.oUnloadPicker1Up2;
		m_DX09.iUnloadPicker1Down3	= m_DY09.oUnloadPicker1Down3;
		m_DX09.iUnloadPicker1Up3	= m_DY09.oUnloadPicker1Up3;
		m_DX09.iUnloadPicker1Down4	= m_DY09.oUnloadPicker1Down4;
		m_DX09.iUnloadPicker1Up4	= m_DY09.oUnloadPicker1Up4;
		m_DX09.iUnloadPicker1Down5	= m_DY09.oUnloadPicker1Down5;
		m_DX09.iUnloadPicker1Up5	= m_DY09.oUnloadPicker1Up5;
		m_DX09.iUnloadPicker1Down6	= m_DY09.oUnloadPicker1Down6;
		m_DX09.iUnloadPicker1Up6	= m_DY09.oUnloadPicker1Up6;
		m_DX09.iUnloadPicker1Down7	= m_DY09.oUnloadPicker1Down7;
		m_DX09.iUnloadPicker1Up7	= m_DY09.oUnloadPicker1Up7;
		m_DX09.iUnloadPicker1Down8	= m_DY09.oUnloadPicker1Down8;
		m_DX09.iUnloadPicker1Up8	= m_DY09.oUnloadPicker1Up8;
		m_DX09.iUnloadPicker1Open1	= m_DY09.oUnloadPicker1Open1;
		m_DX09.iUnloadPicker1Open2	= m_DY09.oUnloadPicker1Open2;
		m_DX09.iUnloadPicker1Open3	= m_DY09.oUnloadPicker1Open3;
		m_DX09.iUnloadPicker1Open4	= m_DY09.oUnloadPicker1Open4;
		m_DX09.iUnloadPicker1Open5	= m_DY09.oUnloadPicker1Open5;
		m_DX09.iUnloadPicker1Open6	= m_DY09.oUnloadPicker1Open6;
		m_DX09.iUnloadPicker1Open7	= m_DY09.oUnloadPicker1Open7;
		m_DX09.iUnloadPicker1Open8	= m_DY09.oUnloadPicker1Open8;

		if (m_DX09.iUnloadPicker1Open1) m_DX09.iUnloadPicker1Exist1 = FALSE; else m_DX09.iUnloadPicker1Exist1 = TRUE;
		if (m_DX09.iUnloadPicker1Open2) m_DX09.iUnloadPicker1Exist2 = FALSE; else m_DX09.iUnloadPicker1Exist2 = TRUE;
		if (m_DX09.iUnloadPicker1Open3) m_DX09.iUnloadPicker1Exist3 = FALSE; else m_DX09.iUnloadPicker1Exist3 = TRUE;
		if (m_DX09.iUnloadPicker1Open4) m_DX09.iUnloadPicker1Exist4 = FALSE; else m_DX09.iUnloadPicker1Exist4 = TRUE;
		if (m_DX09.iUnloadPicker1Open5) m_DX09.iUnloadPicker1Exist5 = FALSE; else m_DX09.iUnloadPicker1Exist5 = TRUE;
		if (m_DX09.iUnloadPicker1Open6) m_DX09.iUnloadPicker1Exist6 = FALSE; else m_DX09.iUnloadPicker1Exist6 = TRUE;
		if (m_DX09.iUnloadPicker1Open7) m_DX09.iUnloadPicker1Exist7 = FALSE; else m_DX09.iUnloadPicker1Exist7 = TRUE;
		if (m_DX09.iUnloadPicker1Open8) m_DX09.iUnloadPicker1Exist8 = FALSE; else m_DX09.iUnloadPicker1Exist8 = TRUE;
	}
	if (nNo==10) {
		m_DX10.iUnloadPicker2Down1	= m_DY10.oUnloadPicker2Down1;
		m_DX10.iUnloadPicker2Up1	= m_DY10.oUnloadPicker2Up1;
		m_DX10.iUnloadPicker2Down2	= m_DY10.oUnloadPicker2Down2;
		m_DX10.iUnloadPicker2Up2	= m_DY10.oUnloadPicker2Up2;
		m_DX10.iUnloadPicker2Down3	= m_DY10.oUnloadPicker2Down3;
		m_DX10.iUnloadPicker2Up3	= m_DY10.oUnloadPicker2Up3;
		m_DX10.iUnloadPicker2Down4	= m_DY10.oUnloadPicker2Down4;
		m_DX10.iUnloadPicker2Up4	= m_DY10.oUnloadPicker2Up4;
		m_DX10.iUnloadPicker2Down5	= m_DY10.oUnloadPicker2Down5;
		m_DX10.iUnloadPicker2Up5	= m_DY10.oUnloadPicker2Up5;
		m_DX10.iUnloadPicker2Down6	= m_DY10.oUnloadPicker2Down6;
		m_DX10.iUnloadPicker2Up6	= m_DY10.oUnloadPicker2Up6;
		m_DX10.iUnloadPicker2Down7	= m_DY10.oUnloadPicker2Down7;
		m_DX10.iUnloadPicker2Up7	= m_DY10.oUnloadPicker2Up7;
		m_DX10.iUnloadPicker2Down8	= m_DY10.oUnloadPicker2Down8;
		m_DX10.iUnloadPicker2Up8	= m_DY10.oUnloadPicker2Up8;
		m_DX10.iUnloadPicker2Open1	= m_DY10.oUnloadPicker2Open1;
		m_DX10.iUnloadPicker2Open2	= m_DY10.oUnloadPicker2Open2;
		m_DX10.iUnloadPicker2Open3	= m_DY10.oUnloadPicker2Open3;
		m_DX10.iUnloadPicker2Open4	= m_DY10.oUnloadPicker2Open4;
		m_DX10.iUnloadPicker2Open5	= m_DY10.oUnloadPicker2Open5;
		m_DX10.iUnloadPicker2Open6	= m_DY10.oUnloadPicker2Open6;
		m_DX10.iUnloadPicker2Open7	= m_DY10.oUnloadPicker2Open7;
		m_DX10.iUnloadPicker2Open8	= m_DY10.oUnloadPicker2Open8;

		if (m_DX10.iUnloadPicker2Open1) m_DX10.iUnloadPicker2Exist1 = FALSE; else m_DX10.iUnloadPicker2Exist1 = TRUE;
		if (m_DX10.iUnloadPicker2Open2) m_DX10.iUnloadPicker2Exist2 = FALSE; else m_DX10.iUnloadPicker2Exist2 = TRUE;
		if (m_DX10.iUnloadPicker2Open3) m_DX10.iUnloadPicker2Exist3 = FALSE; else m_DX10.iUnloadPicker2Exist3 = TRUE;
		if (m_DX10.iUnloadPicker2Open4) m_DX10.iUnloadPicker2Exist4 = FALSE; else m_DX10.iUnloadPicker2Exist4 = TRUE;
		if (m_DX10.iUnloadPicker2Open5) m_DX10.iUnloadPicker2Exist5 = FALSE; else m_DX10.iUnloadPicker2Exist5 = TRUE;
		if (m_DX10.iUnloadPicker2Open6) m_DX10.iUnloadPicker2Exist6 = FALSE; else m_DX10.iUnloadPicker2Exist6 = TRUE;
		if (m_DX10.iUnloadPicker2Open7) m_DX10.iUnloadPicker2Exist7 = FALSE; else m_DX10.iUnloadPicker2Exist7 = TRUE;
		if (m_DX10.iUnloadPicker2Open8) m_DX10.iUnloadPicker2Exist8 = FALSE; else m_DX10.iUnloadPicker2Exist8 = TRUE;
	}
	if (nNo==11) {
		m_DX11.iNGStage1Up			= m_DY11.oNGStage1Up;
		m_DX11.iNGStage1Down		= m_DY11.oNGStage1Down;
		m_DX11.iNGStage1MasterOut	= m_DY11.oNGStage1MasterOut;
		m_DX11.iNGStage1MasterIn	= m_DY11.oNGStage1MasterIn;
		m_DX11.iNGStage1SlaveOut	= m_DY11.oNGStage1SlaveOut;
		m_DX11.iNGStage1SlaveIn		= m_DY11.oNGStage1SlaveIn;
		m_DX11.iNGStage2Up			= m_DY11.oNGStage2Up;
		m_DX11.iNGStage2Down		= m_DY11.oNGStage2Down;
		m_DX11.iNGStage2MasterOut	= m_DY11.oNGStage2MasterOut;
		m_DX11.iNGStage2MasterIn	= m_DY11.oNGStage2MasterIn;
		m_DX11.iNGStage2SlaveOut	= m_DY11.oNGStage2SlaveOut;
		m_DX11.iNGStage2SlaveIn		= m_DY11.oNGStage2SlaveIn;
	}
	if (nNo==12) {
		m_DX12.iGoodStage1Up		= m_DY12.oGoodStage1Up;
		m_DX12.iGoodStage1Down		= m_DY12.oGoodStage1Down;
		m_DX12.iGoodStage1MasterOut	= m_DY12.oGoodStage1MasterOut;
		m_DX12.iGoodStage1MasterIn	= m_DY12.oGoodStage1MasterIn;
		m_DX12.iGoodStage1SlaveOut	= m_DY12.oGoodStage1SlaveOut;
		m_DX12.iGoodStage1SlaveIn	= m_DY12.oGoodStage1SlaveIn;
		m_DX12.iGoodStage2Up		= m_DY12.oGoodStage2Up;	
		m_DX12.iGoodStage2Down		= m_DY12.oGoodStage2Down;
		m_DX12.iGoodStage2MasterOut	= m_DY12.oGoodStage2MasterOut;
		m_DX12.iGoodStage2MasterIn	= m_DY12.oGoodStage2MasterIn;
		m_DX12.iGoodStage2SlaveOut	= m_DY12.oGoodStage2SlaveOut;
		m_DX12.iGoodStage2SlaveIn	= m_DY12.oGoodStage2SlaveIn;
	}
	if (nNo==13) {
		m_DX13.iEmgSw1		 = bF;
		m_DX13.iEmgSw2		 = bF;
		m_DX13.iEmgSw3		 = bF;
		m_DX13.iEmgSw4		 = bF;
		m_DX13.iEmgSw5		 = bF;
		m_DX13.iEmgSw6		 = bF;

		m_DX13.iStartSw		 = bF;
		m_DX13.iStopSw		 = bF;
		m_DX13.iResetSw		 = bF;
	}
	if (nNo==14) {
		m_DX14.iDoor01Unlock = m_DY14.oDoor01Unlock;
		m_DX14.iDoor02Unlock = m_DY14.oDoor02Unlock;
		m_DX14.iDoor03Unlock = m_DY14.oDoor03Unlock;
		m_DX14.iDoor04Unlock = m_DY14.oDoor04Unlock;
		m_DX14.iDoor05Unlock = m_DY14.oDoor05Unlock;
		m_DX14.iDoor06Unlock = m_DY14.oDoor06Unlock;
		m_DX14.iDoor07Unlock = m_DY14.oDoor07Unlock;
		m_DX14.iDoor08Unlock = m_DY14.oDoor08Unlock;
		m_DX14.iDoor09Unlock = m_DY14.oDoor09Unlock;
		m_DX14.iDoor10Unlock = m_DY14.oDoor10Unlock;
		m_DX14.iDoor11Unlock = m_DY14.oDoor11Unlock;
		m_DX14.iDoor12Unlock = m_DY14.oDoor12Unlock;
		m_DX14.iDoor13Unlock = m_DY14.oDoor13Unlock;
		m_DX14.iDoor14Unlock = m_DY14.oDoor14Unlock;
		m_DX14.iDoor15Unlock = m_DY14.oDoor15Unlock;
		m_DX14.iDoor16Unlock = m_DY14.oDoor16Unlock;
		m_DX14.iDoor17Unlock = m_DY14.oDoor17Unlock;
		m_DX14.iDoor18Unlock = m_DY14.oDoor18Unlock;
		m_DX14.iDoor19Unlock = m_DY14.oDoor19Unlock;
		m_DX14.iDoor20Unlock = m_DY14.oDoor20Unlock;
		m_DX14.iDoor21Unlock = m_DY14.oDoor21Unlock;
	}

	if (nNo==99) {
		m_DX07.iInspectStage1Up		= m_DY07.oInspectStage1Up	= bT;
		m_DX07.iInspectStage1Down	= m_DY07.oInspectStage1Down	= bF;
		m_DX07.iInspectStage2Up		= m_DY07.oInspectStage2Up	= bF;
		m_DX07.iInspectStage2Down	= m_DY07.oInspectStage2Down	= bT;
		m_DX08.iInspectStage3Up		= m_DY08.oInspectStage3Up	= bT;
		m_DX08.iInspectStage3Down	= m_DY08.oInspectStage3Down	= bF;
		m_DX08.iInspectStage4Up		= m_DY08.oInspectStage4Up	= bF;
		m_DX08.iInspectStage4Down	= m_DY08.oInspectStage4Down	= bT;

		m_DX04.iLoadStage1Up		= m_DY04.oLoadStage1Up		= bT;
		m_DX04.iLoadStage1Down		= m_DY04.oLoadStage1Down	= bF;
		m_DX04.iLoadStage2Up		= m_DY04.oLoadStage2Up		= bF;	
		m_DX04.iLoadStage2Down		= m_DY04.oLoadStage2Down	= bT;

		m_DX11.iNGStage1Up			= m_DY11.oNGStage1Up		= bT;
		m_DX11.iNGStage1Down		= m_DY11.oNGStage1Down		= bF;
		m_DX11.iNGStage2Up			= m_DY11.oNGStage2Up		= bF;
		m_DX11.iNGStage2Down		= m_DY11.oNGStage2Down		= bT;

		m_DX12.iGoodStage1Up		= m_DY12.oGoodStage1Up		= bT;
		m_DX12.iGoodStage1Down		= m_DY12.oGoodStage1Down	= bF;
		m_DX12.iGoodStage2Up		= m_DY12.oGoodStage2Up		= bF;
		m_DX12.iGoodStage2Down		= m_DY12.oGoodStage2Down	= bT;

		m_DX13.iMainAir1	 = bT;
		m_DX13.iMainAir2	 = bT;
		m_DX13.iMainAir3	 = bT;
	}
}
