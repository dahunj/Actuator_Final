// Common.cpp : 구현 파일입니다.
//
#include "stdafx.h"
#include "CMAI2100.h"
#include "Common.h"
#include "LogFile.h"
#include "AJinAXL.h"
#include "DataManager.h"
#include "ErrorDlg.h"
#include "AlarmDlg.h"
#include "MsgBoxDlg.h"
#include "NumPadDlg.h"
#include "KeyPadDlg.h"
#include "PasswordDlg.h"
#include "Dispatcher.h"
#include "SequenceMain.h"
#include "CMAI2100Dlg.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Wininet.h"
#include "WorkDlg.h"

// CCommon
CCommon g_objCommon;

IMPLEMENT_DYNAMIC(CCommon, CWnd)

CCriticalSection g_csShowError;
CCriticalSection g_csShowAlarm;

CCommon::CCommon()
{
	m_bInsideLight = FALSE;

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	m_nFreq = freq.QuadPart;
}

CCommon::~CCommon()
{
}

BEGIN_MESSAGE_MAP(CCommon, CWnd)
END_MESSAGE_MAP()

// CCommon 메시지 처리기입니다.

void CCommon::DoEvents()
{
	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void CCommon::uSleep(int msec)
{
	LARGE_INTEGER tStart, tNow;
	LONGLONG lTerm = 0;
	QueryPerformanceCounter(&tStart);

	while (TRUE) {
		QueryPerformanceCounter(&tNow);
		lTerm = (tNow.QuadPart - tStart.QuadPart) * 1000 / m_nFreq;
		if (lTerm > msec) break;
		DoEvents();
	}
}

void CCommon::MakeFolder(CString sPath)	//"D:\\Run\\Log\\LotData\\YYYY\\MM\\DD\\";
{
	CString sTemp;
	int nIdx = 0;

	while(true) {
		nIdx = sPath.Find("\\");
		sTemp += sPath.Mid(0, nIdx) + "\\";
		CreateDirectory(sTemp,FALSE);
		sPath = sPath.Mid(nIdx+1, sPath.GetLength());
		if(nIdx<0) break;
	}
}

void CCommon::Save_MotionPos()
{
	uSleep(1500);
	Save_MotionPosIO();
	if (Save_MotionPosMo()==0) return;

	uSleep(1000);
	Save_MotionPosIO();
	if (Save_MotionPosMo()==0) return;

	uSleep(2000);
	Save_MotionPosIO();
	if (Save_MotionPosMo()==0) return;
}

void CCommon::Save_MotionPosIO()
{
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	DX_DATA_04 *pDX04 = g_objAJinAXL.Get_pDX04();
	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
	DX_DATA_11 *pDX11 = g_objAJinAXL.Get_pDX11();
	DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();
	gAlm.bStage[ 0] = pDX04->iLoadStage1Up;
	gAlm.bStage[ 1] = pDX04->iLoadStage2Up;
	gAlm.bStage[ 2] = pDX07->iInspectStage1Up;
	gAlm.bStage[ 3] = pDX07->iInspectStage2Up;
	gAlm.bStage[ 4] = pDX08->iInspectStage3Up;
	gAlm.bStage[ 5] = pDX08->iInspectStage4Up;
	gAlm.bStage[ 6] = pDX07->iInspectStage1Yin;
	gAlm.bStage[ 7] = pDX08->iInspectStage4Yin;
	gAlm.bStage[ 8] = pDX11->iNGStage1Up;
	gAlm.bStage[ 9] = pDX11->iNGStage2Up;
	gAlm.bStage[10] = pDX12->iGoodStage1Up;
	gAlm.bStage[11] = pDX12->iGoodStage2Up;
	gAlm.bStage[12] = pDX03->iAlignMasterIn;
	gAlm.bStage[13] = pDX03->iAlignSlave1In;
	gAlm.bStage[14] = pDX03->iAlignSlave2In;
}

int CCommon::Save_MotionPosMo()
{
	int nCount = 0;
	for(int i=0; i<AXIS_COUNT; i++) {
		if(g_objAJinAXL.Is_Done(i)) { gAlm.dMotionPos[i] = g_objAJinAXL.Get_Position(i); }
		else						{ gAlm.dMotionPos[i] = -100.0; nCount++; }
	}
	return nCount;
}

int CCommon::Check_MotionPos()
{
	int		nMotionNo = 99;
	double	dCurrentPos, dCheckPos;
	double	dRange = gAlm.dMotionChkPos;
	if (dRange < 0.05) return nMotionNo;

	for(int i=0; i<AXIS_COUNT; i++) {
		if (i < 7) continue;
		if (i == AX_BTM_FOCUS_Z || i == AX_TOP1_VISION_Z || i == AX_TOP2_VISION_Z) continue;
		if (gAlm.dMotionPos[i] < -10.0) continue;
		if (!g_objAJinAXL.Is_Done(i)) continue;

		dCheckPos   = gAlm.dMotionPos[i];
		dCurrentPos = g_objAJinAXL.Get_Position(i);
		if (fabs(dCurrentPos - dCheckPos) > dRange) return i;
	}
	return nMotionNo;
}

BOOL CCommon::Check_StageUpDown(CString &sMsg)
{
	if (gAlm.dMotionChkPos < 0.02) return TRUE;

	CString sStage[15] = {"Load Stage1","Load Stage2","Inspection Stage1","Inspection Stage2","Inspection Stage3","Inspection Stage4","Inspection Stage1","Inspection Stage4","NG Stage1","NG Stage2","Good Stage1","Good Stage2","Align Master","Align Slave1","Align Slave2"};

	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();
	DX_DATA_04 *pDX04 = g_objAJinAXL.Get_pDX04();
	DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
	DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
	DX_DATA_11 *pDX11 = g_objAJinAXL.Get_pDX11();
	DX_DATA_12 *pDX12 = g_objAJinAXL.Get_pDX12();

	int		nErrNo = 0;
	if (gAlm.bStage[ 0] != pDX04->iLoadStage1Up)		nErrNo = 1;
	if (gAlm.bStage[ 1] != pDX04->iLoadStage2Up)		nErrNo = 2;
	if (gAlm.bStage[ 2] != pDX07->iInspectStage1Up)		nErrNo = 3;
	if (gAlm.bStage[ 3] != pDX07->iInspectStage2Up)		nErrNo = 4;
	if (gAlm.bStage[ 4] != pDX08->iInspectStage3Up)		nErrNo = 5;
	if (gAlm.bStage[ 5] != pDX08->iInspectStage4Up)		nErrNo = 6;
	if (gAlm.bStage[ 6] != pDX07->iInspectStage1Yin)	nErrNo = 7;
	if (gAlm.bStage[ 7] != pDX08->iInspectStage4Yin)	nErrNo = 8;
	if (gAlm.bStage[ 8] != pDX11->iNGStage1Up)			nErrNo = 9;
	if (gAlm.bStage[ 9] != pDX11->iNGStage2Up)			nErrNo = 10;
	if (gAlm.bStage[10] != pDX12->iGoodStage1Up)		nErrNo = 11;
	if (gAlm.bStage[11] != pDX12->iGoodStage2Up)		nErrNo = 12;
//	if (gAlm.bStage[12] != pDX03->iAlignMasterIn)		nErrNo = 13;
//	if (gAlm.bStage[13] != pDX03->iAlignSlave1In)		nErrNo = 14;
//	if (gAlm.bStage[14] != pDX03->iAlignSlave2In)		nErrNo = 15;

	if (nErrNo > 0) {
		if (nErrNo == 7 || nErrNo == 8 || nErrNo == 13 || nErrNo == 14 || nErrNo == 15)
				sMsg.Format("%s In-Out 위치가 변경되었습니다. 확인해 주세요.", sStage[nErrNo-1]);
		else	sMsg.Format("%s Up-Down 위치가 변경되었습니다. 확인해 주세요.", sStage[nErrNo-1]);
		return FALSE;
	}
	return TRUE;
}

BOOL CCommon::Check_Position(int nAxis, int nMoveIdx, double dRange)
{
	double dCurrentPos = g_objAJinAXL.Get_Position(nAxis);
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	double dCheckPos = -1.0;

	if (g_objAJinAXL.Is_Done(nAxis)) {
		if (nAxis == AX_ELEVATOR_Z1)		dCheckPos = pMoveData->dElevatorZ1[nMoveIdx];		// AXIS 00
		if (nAxis == AX_ELEVATOR_Z2)		dCheckPos = pMoveData->dElevatorZ2[nMoveIdx];		// AXIS 01
		if (nAxis == AX_ELEVATOR_Z3)		dCheckPos = pMoveData->dElevatorZ3[nMoveIdx];		// AXIS 02
		if (nAxis == AX_ELEVATOR_Z4)		dCheckPos = pMoveData->dElevatorZ4[nMoveIdx];		// AXIS 03
		if (nAxis == AX_ELEVATOR_Z5)		dCheckPos = pMoveData->dElevatorZ5[nMoveIdx];		// AXIS 04
		if (nAxis == AX_ELEVATOR_Z6)		dCheckPos = pMoveData->dElevatorZ6[nMoveIdx];		// AXIS 05
		if (nAxis == AX_ELEVATOR_Z7)		dCheckPos = pMoveData->dElevatorZ7[nMoveIdx];		// AXIS 06
		if (nAxis == AX_TRANSFER_X1)		dCheckPos = pMoveData->dTransferX1[nMoveIdx];		// AXIS 07
		if (nAxis == AX_TRANSFER_Z1)		dCheckPos = pMoveData->dTransferZ1[nMoveIdx];		// AXIS 08
		if (nAxis == AX_TRANSFER_X2)		dCheckPos = pMoveData->dTransferX2[nMoveIdx];		// AXIS 09
		if (nAxis == AX_TRANSFER_Z2)		dCheckPos = pMoveData->dTransferZ2[nMoveIdx];		// AXIS 10
		if (nAxis == AX_LOAD_STAGE_Y1)		dCheckPos = pMoveData->dLoadStageY1[nMoveIdx];		// AXIS 11
		if (nAxis == AX_LOAD_STAGE_Y2)		dCheckPos = pMoveData->dLoadStageY2[nMoveIdx];		// AXIS 12
		if (nAxis == AX_LOAD_PICKER_X1)		dCheckPos = pMoveData->dLoadPickerX1[nMoveIdx];		// AXIS 13
		if (nAxis == AX_LOAD_PICKER_Y1)		dCheckPos = pMoveData->dLoadPickerY1[nMoveIdx];		// AXIS 14
		if (nAxis == AX_LOAD_PICKER_Z1)		dCheckPos = pMoveData->dLoadPickerZ1[nMoveIdx];		// AXIS 15
		if (nAxis == AX_LOAD_PICKER_P1)		dCheckPos = pMoveData->dLoadPickerP1[nMoveIdx];		// AXIS 16
		if (nAxis == AX_LOAD_PICKER_X2)		dCheckPos = pMoveData->dLoadPickerX2[nMoveIdx];		// AXIS 17
		if (nAxis == AX_LOAD_PICKER_Y2)		dCheckPos = pMoveData->dLoadPickerY2[nMoveIdx];		// AXIS 18
		if (nAxis == AX_LOAD_PICKER_Z2)		dCheckPos = pMoveData->dLoadPickerZ2[nMoveIdx];		// AXIS 19
		if (nAxis == AX_LOAD_PICKER_P2)		dCheckPos = pMoveData->dLoadPickerP2[nMoveIdx];		// AXIS 20
		if (nAxis == AX_BTM_FOCUS_Z)		dCheckPos = pMoveData->dBTMFocusZ[nMoveIdx];		// AXIS 21
		if (nAxis == AX_BTM_LIGHT_Z)		dCheckPos = pMoveData->dBTMLightZ[nMoveIdx];		// AXIS 22
		if (nAxis == AX_BTM_ANGLE_Y)		dCheckPos = pMoveData->dBTMAngleY[nMoveIdx];		// AXIS 23
		if (nAxis == AX_TOP1_VISION_Z)		dCheckPos = pMoveData->dTOPVisionZ1[nMoveIdx];		// AXIS 24
		if (nAxis == AX_TOP2_VISION_Z)		dCheckPos = pMoveData->dTOPVisionZ2[nMoveIdx];		// AXIS 25
		if (nAxis == AX_INSPECT_STAGE_X1)	dCheckPos = pMoveData->dVisionStageX1[nMoveIdx];	// AXIS 26
		if (nAxis == AX_INSPECT_STAGE_X2)	dCheckPos = pMoveData->dVisionStageX2[nMoveIdx];	// AXIS 27
		if (nAxis == AX_INSPECT_STAGE_X3)	dCheckPos = pMoveData->dVisionStageX3[nMoveIdx];	// AXIS 28
		if (nAxis == AX_INSPECT_STAGE_X4)	dCheckPos = pMoveData->dVisionStageX4[nMoveIdx];	// AXIS 29
		if (nAxis == AX_UNLOAD_PICKER_X1)	dCheckPos = pMoveData->dUnloadPickerX1[nMoveIdx];	// AXIS 30
		if (nAxis == AX_UNLOAD_PICKER_Y1)	dCheckPos = pMoveData->dUnloadPickerY1[nMoveIdx];	// AXIS 31
		if (nAxis == AX_UNLOAD_PICKER_Z1)	dCheckPos = pMoveData->dUnloadPickerZ1[nMoveIdx];	// AXIS 32
		if (nAxis == AX_UNLOAD_PICKER_P1)	dCheckPos = pMoveData->dUnloadPickerP1[nMoveIdx];	// AXIS 33
		if (nAxis == AX_UNLOAD_PICKER_X2)	dCheckPos = pMoveData->dUnloadPickerX2[nMoveIdx];	// AXIS 34
		if (nAxis == AX_UNLOAD_PICKER_Y2)	dCheckPos = pMoveData->dUnloadPickerY2[nMoveIdx];	// AXIS 35
		if (nAxis == AX_UNLOAD_PICKER_Z2)	dCheckPos = pMoveData->dUnloadPickerZ2[nMoveIdx];	// AXIS 36
		if (nAxis == AX_UNLOAD_PICKER_P2)	dCheckPos = pMoveData->dUnloadPickerP2[nMoveIdx];	// AXIS 37
		if (nAxis == AX_GOOD_STAGE_Y1)		dCheckPos = pMoveData->dGoodStageY1[nMoveIdx];		// AXIS 38
		if (nAxis == AX_GOOD_STAGE_Y2)		dCheckPos = pMoveData->dGoodStageY2[nMoveIdx];		// AXIS 39
		if (nAxis == AX_NG_STAGE_Y1)		dCheckPos = pMoveData->dNGStageY1[nMoveIdx];		// AXIS 40
		if (nAxis == AX_NG_STAGE_Y2)		dCheckPos = pMoveData->dNGStageY2[nMoveIdx];		// AXIS 41
		if (nAxis == AX_SHIP_ALIGN_X)		dCheckPos = pMoveData->dShiipAling[nMoveIdx];		// AXIS 42
		if (nAxis == AX_TOP1_LIGHT_Z)		dCheckPos = pMoveData->dTop1LightZ[nMoveIdx];		// AXIS 43
		if (nAxis == AX_TOP1_ANGLE_Y)		dCheckPos = pMoveData->dTop1AngleY[nMoveIdx];		// AXIS 44

		if (fabs(dCurrentPos - dCheckPos) < dRange) return TRUE;

	} else return FALSE;

	return FALSE;
}

void CCommon::Move_Position(int nAxis, int nMoveIdx, double dSpeed)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	double dMovePos = -999.0;

	if (nAxis == AX_ELEVATOR_Z1)		dMovePos = pMoveData->dElevatorZ1[nMoveIdx];		// AXIS 00
	if (nAxis == AX_ELEVATOR_Z2)		dMovePos = pMoveData->dElevatorZ2[nMoveIdx];		// AXIS 01
	if (nAxis == AX_ELEVATOR_Z3)		dMovePos = pMoveData->dElevatorZ3[nMoveIdx];		// AXIS 02
	if (nAxis == AX_ELEVATOR_Z4)		dMovePos = pMoveData->dElevatorZ4[nMoveIdx];		// AXIS 03
	if (nAxis == AX_ELEVATOR_Z5)		dMovePos = pMoveData->dElevatorZ5[nMoveIdx];		// AXIS 04
	if (nAxis == AX_ELEVATOR_Z6)		dMovePos = pMoveData->dElevatorZ6[nMoveIdx];		// AXIS 05
	if (nAxis == AX_ELEVATOR_Z7)		dMovePos = pMoveData->dElevatorZ7[nMoveIdx];		// AXIS 06
	if (nAxis == AX_TRANSFER_X1)		dMovePos = pMoveData->dTransferX1[nMoveIdx];		// AXIS 07
	if (nAxis == AX_TRANSFER_Z1)		dMovePos = pMoveData->dTransferZ1[nMoveIdx];		// AXIS 08
	if (nAxis == AX_TRANSFER_X2)		dMovePos = pMoveData->dTransferX2[nMoveIdx];		// AXIS 09
	if (nAxis == AX_TRANSFER_Z2)		dMovePos = pMoveData->dTransferZ2[nMoveIdx];		// AXIS 10
	if (nAxis == AX_LOAD_STAGE_Y1)		dMovePos = pMoveData->dLoadStageY1[nMoveIdx];		// AXIS 11
	if (nAxis == AX_LOAD_STAGE_Y2)		dMovePos = pMoveData->dLoadStageY2[nMoveIdx];		// AXIS 12
	if (nAxis == AX_LOAD_PICKER_X1)		dMovePos = pMoveData->dLoadPickerX1[nMoveIdx];		// AXIS 13
	if (nAxis == AX_LOAD_PICKER_Y1)		dMovePos = pMoveData->dLoadPickerY1[nMoveIdx];		// AXIS 14
	if (nAxis == AX_LOAD_PICKER_Z1)		dMovePos = pMoveData->dLoadPickerZ1[nMoveIdx];		// AXIS 15
	if (nAxis == AX_LOAD_PICKER_P1)		dMovePos = pMoveData->dLoadPickerP1[nMoveIdx];		// AXIS 16
	if (nAxis == AX_LOAD_PICKER_X2)		dMovePos = pMoveData->dLoadPickerX2[nMoveIdx];		// AXIS 17
	if (nAxis == AX_LOAD_PICKER_Y2)		dMovePos = pMoveData->dLoadPickerY2[nMoveIdx];		// AXIS 18
	if (nAxis == AX_LOAD_PICKER_Z2)		dMovePos = pMoveData->dLoadPickerZ2[nMoveIdx];		// AXIS 19
	if (nAxis == AX_LOAD_PICKER_P2)		dMovePos = pMoveData->dLoadPickerP2[nMoveIdx];		// AXIS 20
	if (nAxis == AX_BTM_FOCUS_Z)		dMovePos = pMoveData->dBTMFocusZ[nMoveIdx];		// AXIS 21
	if (nAxis == AX_BTM_LIGHT_Z)		dMovePos = pMoveData->dBTMLightZ[nMoveIdx];		// AXIS 22
	if (nAxis == AX_BTM_ANGLE_Y)		dMovePos = pMoveData->dBTMAngleY[nMoveIdx];		// AXIS 23
	if (nAxis == AX_TOP1_VISION_Z)		dMovePos = pMoveData->dTOPVisionZ1[nMoveIdx];		// AXIS 24
	if (nAxis == AX_TOP2_VISION_Z)		dMovePos = pMoveData->dTOPVisionZ2[nMoveIdx];		// AXIS 25
	if (nAxis == AX_INSPECT_STAGE_X1)	dMovePos = pMoveData->dVisionStageX1[nMoveIdx];	// AXIS 26
	if (nAxis == AX_INSPECT_STAGE_X2)	dMovePos = pMoveData->dVisionStageX2[nMoveIdx];	// AXIS 27
	if (nAxis == AX_INSPECT_STAGE_X3)	dMovePos = pMoveData->dVisionStageX3[nMoveIdx];	// AXIS 28
	if (nAxis == AX_INSPECT_STAGE_X4)	dMovePos = pMoveData->dVisionStageX4[nMoveIdx];	// AXIS 29
	if (nAxis == AX_UNLOAD_PICKER_X1)	dMovePos = pMoveData->dUnloadPickerX1[nMoveIdx];	// AXIS 30
	if (nAxis == AX_UNLOAD_PICKER_Y1)	dMovePos = pMoveData->dUnloadPickerY1[nMoveIdx];	// AXIS 31
	if (nAxis == AX_UNLOAD_PICKER_Z1)	dMovePos = pMoveData->dUnloadPickerZ1[nMoveIdx];	// AXIS 32
	if (nAxis == AX_UNLOAD_PICKER_P1)	dMovePos = pMoveData->dUnloadPickerP1[nMoveIdx];	// AXIS 33
	if (nAxis == AX_UNLOAD_PICKER_X2)	dMovePos = pMoveData->dUnloadPickerX2[nMoveIdx];	// AXIS 34
	if (nAxis == AX_UNLOAD_PICKER_Y2)	dMovePos = pMoveData->dUnloadPickerY2[nMoveIdx];	// AXIS 35
	if (nAxis == AX_UNLOAD_PICKER_Z2)	dMovePos = pMoveData->dUnloadPickerZ2[nMoveIdx];	// AXIS 36
	if (nAxis == AX_UNLOAD_PICKER_P2)	dMovePos = pMoveData->dUnloadPickerP2[nMoveIdx];	// AXIS 37
	if (nAxis == AX_GOOD_STAGE_Y1)		dMovePos = pMoveData->dGoodStageY1[nMoveIdx];		// AXIS 38
	if (nAxis == AX_GOOD_STAGE_Y2)		dMovePos = pMoveData->dGoodStageY2[nMoveIdx];		// AXIS 39
	if (nAxis == AX_NG_STAGE_Y1)		dMovePos = pMoveData->dNGStageY1[nMoveIdx];		// AXIS 40
	if (nAxis == AX_NG_STAGE_Y2)		dMovePos = pMoveData->dNGStageY2[nMoveIdx];		// AXIS 41
	if (nAxis == AX_SHIP_ALIGN_X)		dMovePos = pMoveData->dShiipAling[nMoveIdx];		// AXIS 42
	if (nAxis == AX_TOP1_LIGHT_Z)		dMovePos = pMoveData->dTop1LightZ[nMoveIdx];		// AXIS 43
	if (nAxis == AX_TOP1_ANGLE_Y)		dMovePos = pMoveData->dTop1AngleY[nMoveIdx];		// AXIS 44

	if (dMovePos == -999) return;
	if (nMoveIdx > 0 && (nAxis == AX_TRANSFER_Z1 || nAxis == AX_TRANSFER_Z2)) {
		g_objAJinAXL.Move_Abs_Override(nAxis, dMovePos, (dMovePos-pEquipData->dTranZOverride), pEquipData->dSpeedZOverride);
	} else {
		g_objAJinAXL.Move_Absolute(nAxis, dMovePos, dSpeed);
	}
}

void CCommon::Move_Override(int nAxis, int nMoveIdx, double dAt)
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();

	double dMovePos = -999.0;

	if (nAxis == AX_ELEVATOR_Z1)		dMovePos = pMoveData->dElevatorZ1[nMoveIdx];		// AXIS 00
	if (nAxis == AX_ELEVATOR_Z2)		dMovePos = pMoveData->dElevatorZ2[nMoveIdx];		// AXIS 01
	if (nAxis == AX_ELEVATOR_Z3)		dMovePos = pMoveData->dElevatorZ3[nMoveIdx];		// AXIS 02
	if (nAxis == AX_ELEVATOR_Z4)		dMovePos = pMoveData->dElevatorZ4[nMoveIdx];		// AXIS 03
	if (nAxis == AX_ELEVATOR_Z5)		dMovePos = pMoveData->dElevatorZ5[nMoveIdx];		// AXIS 04
	if (nAxis == AX_ELEVATOR_Z6)		dMovePos = pMoveData->dElevatorZ6[nMoveIdx];		// AXIS 05
	if (nAxis == AX_ELEVATOR_Z7)		dMovePos = pMoveData->dElevatorZ7[nMoveIdx];		// AXIS 06
	if (nAxis == AX_TRANSFER_X1)		dMovePos = pMoveData->dTransferX1[nMoveIdx];		// AXIS 07
	if (nAxis == AX_TRANSFER_Z1)		dMovePos = pMoveData->dTransferZ1[nMoveIdx];		// AXIS 08
	if (nAxis == AX_TRANSFER_X2)		dMovePos = pMoveData->dTransferX2[nMoveIdx];		// AXIS 09
	if (nAxis == AX_TRANSFER_Z2)		dMovePos = pMoveData->dTransferZ2[nMoveIdx];		// AXIS 10
	if (nAxis == AX_LOAD_STAGE_Y1)		dMovePos = pMoveData->dLoadStageY1[nMoveIdx];		// AXIS 11
	if (nAxis == AX_LOAD_STAGE_Y2)		dMovePos = pMoveData->dLoadStageY2[nMoveIdx];		// AXIS 12
	if (nAxis == AX_LOAD_PICKER_X1)		dMovePos = pMoveData->dLoadPickerX1[nMoveIdx];		// AXIS 13
	if (nAxis == AX_LOAD_PICKER_Y1)		dMovePos = pMoveData->dLoadPickerY1[nMoveIdx];		// AXIS 14
	if (nAxis == AX_LOAD_PICKER_Z1)		dMovePos = pMoveData->dLoadPickerZ1[nMoveIdx];		// AXIS 15
	if (nAxis == AX_LOAD_PICKER_P1)		dMovePos = pMoveData->dLoadPickerP1[nMoveIdx];		// AXIS 16
	if (nAxis == AX_LOAD_PICKER_X2)		dMovePos = pMoveData->dLoadPickerX2[nMoveIdx];		// AXIS 17
	if (nAxis == AX_LOAD_PICKER_Y2)		dMovePos = pMoveData->dLoadPickerY2[nMoveIdx];		// AXIS 18
	if (nAxis == AX_LOAD_PICKER_Z2)		dMovePos = pMoveData->dLoadPickerZ2[nMoveIdx];		// AXIS 19
	if (nAxis == AX_LOAD_PICKER_P2)		dMovePos = pMoveData->dLoadPickerP2[nMoveIdx];		// AXIS 20
	if (nAxis == AX_BTM_FOCUS_Z)		dMovePos = pMoveData->dBTMFocusZ[nMoveIdx];		// AXIS 21
	if (nAxis == AX_BTM_LIGHT_Z)		dMovePos = pMoveData->dBTMLightZ[nMoveIdx];		// AXIS 22
	if (nAxis == AX_BTM_ANGLE_Y)		dMovePos = pMoveData->dBTMAngleY[nMoveIdx];		// AXIS 23
	if (nAxis == AX_TOP1_VISION_Z)		dMovePos = pMoveData->dTOPVisionZ1[nMoveIdx];		// AXIS 24
	if (nAxis == AX_TOP2_VISION_Z)		dMovePos = pMoveData->dTOPVisionZ2[nMoveIdx];		// AXIS 25
	if (nAxis == AX_INSPECT_STAGE_X1)	dMovePos = pMoveData->dVisionStageX1[nMoveIdx];	// AXIS 26
	if (nAxis == AX_INSPECT_STAGE_X2)	dMovePos = pMoveData->dVisionStageX2[nMoveIdx];	// AXIS 27
	if (nAxis == AX_INSPECT_STAGE_X3)	dMovePos = pMoveData->dVisionStageX3[nMoveIdx];	// AXIS 28
	if (nAxis == AX_INSPECT_STAGE_X4)	dMovePos = pMoveData->dVisionStageX4[nMoveIdx];	// AXIS 29
	if (nAxis == AX_UNLOAD_PICKER_X1)	dMovePos = pMoveData->dUnloadPickerX1[nMoveIdx];	// AXIS 30
	if (nAxis == AX_UNLOAD_PICKER_Y1)	dMovePos = pMoveData->dUnloadPickerY1[nMoveIdx];	// AXIS 31
	if (nAxis == AX_UNLOAD_PICKER_Z1)	dMovePos = pMoveData->dUnloadPickerZ1[nMoveIdx];	// AXIS 32
	if (nAxis == AX_UNLOAD_PICKER_P1)	dMovePos = pMoveData->dUnloadPickerP1[nMoveIdx];	// AXIS 33
	if (nAxis == AX_UNLOAD_PICKER_X2)	dMovePos = pMoveData->dUnloadPickerX2[nMoveIdx];	// AXIS 34
	if (nAxis == AX_UNLOAD_PICKER_Y2)	dMovePos = pMoveData->dUnloadPickerY2[nMoveIdx];	// AXIS 35
	if (nAxis == AX_UNLOAD_PICKER_Z2)	dMovePos = pMoveData->dUnloadPickerZ2[nMoveIdx];	// AXIS 36
	if (nAxis == AX_UNLOAD_PICKER_P2)	dMovePos = pMoveData->dUnloadPickerP2[nMoveIdx];	// AXIS 37
	if (nAxis == AX_GOOD_STAGE_Y1)		dMovePos = pMoveData->dGoodStageY1[nMoveIdx];		// AXIS 38
	if (nAxis == AX_GOOD_STAGE_Y2)		dMovePos = pMoveData->dGoodStageY2[nMoveIdx];		// AXIS 39
	if (nAxis == AX_NG_STAGE_Y1)		dMovePos = pMoveData->dNGStageY1[nMoveIdx];		// AXIS 40
	if (nAxis == AX_NG_STAGE_Y2)		dMovePos = pMoveData->dNGStageY2[nMoveIdx];		// AXIS 41
	if (nAxis == AX_SHIP_ALIGN_X)		dMovePos = pMoveData->dShiipAling[nMoveIdx];		// AXIS 42
	if (nAxis == AX_TOP1_LIGHT_Z)		dMovePos = pMoveData->dTop1LightZ[nMoveIdx];		// AXIS 43
	if (nAxis == AX_TOP1_ANGLE_Y)		dMovePos = pMoveData->dTop1AngleY[nMoveIdx];		// AXIS 44

	if (dMovePos == -999) return;
	g_objAJinAXL.Move_Abs_Override(nAxis, dMovePos, (dMovePos-dAt));
}

BOOL CCommon::Check_MoveData(int nAxis, int nMoveIdx, CString sData)
{
	double dData = atof(sData);

	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	MOVE_DATA *pMoveInput = g_objDataManager.Get_pMoveInput();

	double dCheckPos = -1.0;
	if (nAxis == AX_ELEVATOR_Z1)		dCheckPos = pMoveInput->dElevatorZ1[nMoveIdx];		// AXIS 00
	if (nAxis == AX_ELEVATOR_Z2)		dCheckPos = pMoveInput->dElevatorZ2[nMoveIdx];		// AXIS 01
	if (nAxis == AX_ELEVATOR_Z3)		dCheckPos = pMoveInput->dElevatorZ3[nMoveIdx];		// AXIS 02
	if (nAxis == AX_ELEVATOR_Z4)		dCheckPos = pMoveInput->dElevatorZ4[nMoveIdx];		// AXIS 03
	if (nAxis == AX_ELEVATOR_Z5)		dCheckPos = pMoveInput->dElevatorZ5[nMoveIdx];		// AXIS 04
	if (nAxis == AX_ELEVATOR_Z6)		dCheckPos = pMoveInput->dElevatorZ6[nMoveIdx];		// AXIS 05
	if (nAxis == AX_ELEVATOR_Z7)		dCheckPos = pMoveInput->dElevatorZ7[nMoveIdx];		// AXIS 06
	if (nAxis == AX_TRANSFER_X1)		dCheckPos = pMoveInput->dTransferX1[nMoveIdx];		// AXIS 07
	if (nAxis == AX_TRANSFER_Z1)		dCheckPos = pMoveInput->dTransferZ1[nMoveIdx];		// AXIS 08
	if (nAxis == AX_TRANSFER_X2)		dCheckPos = pMoveInput->dTransferX2[nMoveIdx];		// AXIS 09
	if (nAxis == AX_TRANSFER_Z2)		dCheckPos = pMoveInput->dTransferZ2[nMoveIdx];		// AXIS 10
	if (nAxis == AX_LOAD_STAGE_Y1)		dCheckPos = pMoveInput->dLoadStageY1[nMoveIdx];		// AXIS 11
	if (nAxis == AX_LOAD_STAGE_Y2)		dCheckPos = pMoveInput->dLoadStageY2[nMoveIdx];		// AXIS 12
	if (nAxis == AX_LOAD_PICKER_X1)		dCheckPos = pMoveInput->dLoadPickerX1[nMoveIdx];		// AXIS 13
	if (nAxis == AX_LOAD_PICKER_Y1)		dCheckPos = pMoveInput->dLoadPickerY1[nMoveIdx];		// AXIS 14
	if (nAxis == AX_LOAD_PICKER_Z1)		dCheckPos = pMoveInput->dLoadPickerZ1[nMoveIdx];		// AXIS 15
	if (nAxis == AX_LOAD_PICKER_P1)		dCheckPos = pMoveInput->dLoadPickerP1[nMoveIdx];		// AXIS 16
	if (nAxis == AX_LOAD_PICKER_X2)		dCheckPos = pMoveInput->dLoadPickerX2[nMoveIdx];		// AXIS 17
	if (nAxis == AX_LOAD_PICKER_Y2)		dCheckPos = pMoveInput->dLoadPickerY2[nMoveIdx];		// AXIS 18
	if (nAxis == AX_LOAD_PICKER_Z2)		dCheckPos = pMoveInput->dLoadPickerZ2[nMoveIdx];		// AXIS 19
	if (nAxis == AX_LOAD_PICKER_P2)		dCheckPos = pMoveInput->dLoadPickerP2[nMoveIdx];		// AXIS 20
	if (nAxis == AX_BTM_FOCUS_Z)		dCheckPos = pMoveInput->dBTMFocusZ[nMoveIdx];		// AXIS 21
	if (nAxis == AX_BTM_LIGHT_Z)		dCheckPos = pMoveInput->dBTMLightZ[nMoveIdx];		// AXIS 22
	if (nAxis == AX_BTM_ANGLE_Y)		dCheckPos = pMoveInput->dBTMAngleY[nMoveIdx];		// AXIS 23
	if (nAxis == AX_TOP1_VISION_Z)		dCheckPos = pMoveInput->dTOPVisionZ1[nMoveIdx];		// AXIS 24
	if (nAxis == AX_TOP2_VISION_Z)		dCheckPos = pMoveInput->dTOPVisionZ2[nMoveIdx];		// AXIS 25
	if (nAxis == AX_INSPECT_STAGE_X1)	dCheckPos = pMoveInput->dVisionStageX1[nMoveIdx];	// AXIS 26
	if (nAxis == AX_INSPECT_STAGE_X2)	dCheckPos = pMoveInput->dVisionStageX2[nMoveIdx];	// AXIS 27
	if (nAxis == AX_INSPECT_STAGE_X3)	dCheckPos = pMoveInput->dVisionStageX3[nMoveIdx];	// AXIS 28
	if (nAxis == AX_INSPECT_STAGE_X4)	dCheckPos = pMoveInput->dVisionStageX4[nMoveIdx];	// AXIS 29
	if (nAxis == AX_UNLOAD_PICKER_X1)	dCheckPos = pMoveInput->dUnloadPickerX1[nMoveIdx];	// AXIS 30
	if (nAxis == AX_UNLOAD_PICKER_Y1)	dCheckPos = pMoveInput->dUnloadPickerY1[nMoveIdx];	// AXIS 31
	if (nAxis == AX_UNLOAD_PICKER_Z1)	dCheckPos = pMoveInput->dUnloadPickerZ1[nMoveIdx];	// AXIS 32
	if (nAxis == AX_UNLOAD_PICKER_P1)	dCheckPos = pMoveInput->dUnloadPickerP1[nMoveIdx];	// AXIS 33
	if (nAxis == AX_UNLOAD_PICKER_X2)	dCheckPos = pMoveInput->dUnloadPickerX2[nMoveIdx];	// AXIS 34
	if (nAxis == AX_UNLOAD_PICKER_Y2)	dCheckPos = pMoveInput->dUnloadPickerY2[nMoveIdx];	// AXIS 35
	if (nAxis == AX_UNLOAD_PICKER_Z2)	dCheckPos = pMoveInput->dUnloadPickerZ2[nMoveIdx];	// AXIS 36
	if (nAxis == AX_UNLOAD_PICKER_P2)	dCheckPos = pMoveInput->dUnloadPickerP2[nMoveIdx];	// AXIS 37
	if (nAxis == AX_GOOD_STAGE_Y1)		dCheckPos = pMoveInput->dGoodStageY1[nMoveIdx];		// AXIS 38
	if (nAxis == AX_GOOD_STAGE_Y2)		dCheckPos = pMoveInput->dGoodStageY2[nMoveIdx];		// AXIS 39
	if (nAxis == AX_NG_STAGE_Y1)		dCheckPos = pMoveInput->dNGStageY1[nMoveIdx];		// AXIS 40
	if (nAxis == AX_NG_STAGE_Y2)		dCheckPos = pMoveInput->dNGStageY2[nMoveIdx];		// AXIS 41
	if (nAxis == AX_SHIP_ALIGN_X)		dCheckPos = pMoveInput->dShiipAling[nMoveIdx];		// AXIS 42
	if (nAxis == AX_TOP1_LIGHT_Z)		dCheckPos = pMoveInput->dTop1LightZ[nMoveIdx];		// AXIS 43
	if (nAxis == AX_TOP1_ANGLE_Y)		dCheckPos = pMoveInput->dTop1AngleY[nMoveIdx];		// AXIS 44
	if (dCheckPos < 0.0) return FALSE;
	if (dCheckPos == 0.0) return TRUE;

	double dMovePos = -999.0;
	if (nAxis == AX_ELEVATOR_Z1)		dMovePos = pMoveData->dElevatorZ1[nMoveIdx];		// AXIS 00
	if (nAxis == AX_ELEVATOR_Z2)		dMovePos = pMoveData->dElevatorZ2[nMoveIdx];		// AXIS 01
	if (nAxis == AX_ELEVATOR_Z3)		dMovePos = pMoveData->dElevatorZ3[nMoveIdx];		// AXIS 02
	if (nAxis == AX_ELEVATOR_Z4)		dMovePos = pMoveData->dElevatorZ4[nMoveIdx];		// AXIS 03
	if (nAxis == AX_ELEVATOR_Z5)		dMovePos = pMoveData->dElevatorZ5[nMoveIdx];		// AXIS 04
	if (nAxis == AX_ELEVATOR_Z6)		dMovePos = pMoveData->dElevatorZ6[nMoveIdx];		// AXIS 05
	if (nAxis == AX_ELEVATOR_Z7)		dMovePos = pMoveData->dElevatorZ7[nMoveIdx];		// AXIS 06
	if (nAxis == AX_TRANSFER_X1)		dMovePos = pMoveData->dTransferX1[nMoveIdx];		// AXIS 07
	if (nAxis == AX_TRANSFER_Z1)		dMovePos = pMoveData->dTransferZ1[nMoveIdx];		// AXIS 08
	if (nAxis == AX_TRANSFER_X2)		dMovePos = pMoveData->dTransferX2[nMoveIdx];		// AXIS 09
	if (nAxis == AX_TRANSFER_Z2)		dMovePos = pMoveData->dTransferZ2[nMoveIdx];		// AXIS 10
	if (nAxis == AX_LOAD_STAGE_Y1)		dMovePos = pMoveData->dLoadStageY1[nMoveIdx];		// AXIS 11
	if (nAxis == AX_LOAD_STAGE_Y2)		dMovePos = pMoveData->dLoadStageY2[nMoveIdx];		// AXIS 12
	if (nAxis == AX_LOAD_PICKER_X1)		dMovePos = pMoveData->dLoadPickerX1[nMoveIdx];		// AXIS 13
	if (nAxis == AX_LOAD_PICKER_Y1)		dMovePos = pMoveData->dLoadPickerY1[nMoveIdx];		// AXIS 14
	if (nAxis == AX_LOAD_PICKER_Z1)		dMovePos = pMoveData->dLoadPickerZ1[nMoveIdx];		// AXIS 15
	if (nAxis == AX_LOAD_PICKER_P1)		dMovePos = pMoveData->dLoadPickerP1[nMoveIdx];		// AXIS 16
	if (nAxis == AX_LOAD_PICKER_X2)		dMovePos = pMoveData->dLoadPickerX2[nMoveIdx];		// AXIS 17
	if (nAxis == AX_LOAD_PICKER_Y2)		dMovePos = pMoveData->dLoadPickerY2[nMoveIdx];		// AXIS 18
	if (nAxis == AX_LOAD_PICKER_Z2)		dMovePos = pMoveData->dLoadPickerZ2[nMoveIdx];		// AXIS 19
	if (nAxis == AX_LOAD_PICKER_P2)		dMovePos = pMoveData->dLoadPickerP2[nMoveIdx];		// AXIS 20
	if (nAxis == AX_BTM_FOCUS_Z)		dMovePos = pMoveData->dBTMFocusZ[nMoveIdx];		// AXIS 21
	if (nAxis == AX_BTM_LIGHT_Z)		dMovePos = pMoveData->dBTMLightZ[nMoveIdx];		// AXIS 22
	if (nAxis == AX_BTM_ANGLE_Y)		dMovePos = pMoveData->dBTMAngleY[nMoveIdx];		// AXIS 23
	if (nAxis == AX_TOP1_VISION_Z)		dMovePos = pMoveData->dTOPVisionZ1[nMoveIdx];		// AXIS 24
	if (nAxis == AX_TOP2_VISION_Z)		dMovePos = pMoveData->dTOPVisionZ2[nMoveIdx];		// AXIS 25
	if (nAxis == AX_INSPECT_STAGE_X1)	dMovePos = pMoveData->dVisionStageX1[nMoveIdx];	// AXIS 26
	if (nAxis == AX_INSPECT_STAGE_X2)	dMovePos = pMoveData->dVisionStageX2[nMoveIdx];	// AXIS 27
	if (nAxis == AX_INSPECT_STAGE_X3)	dMovePos = pMoveData->dVisionStageX3[nMoveIdx];	// AXIS 28
	if (nAxis == AX_INSPECT_STAGE_X4)	dMovePos = pMoveData->dVisionStageX4[nMoveIdx];	// AXIS 29
	if (nAxis == AX_UNLOAD_PICKER_X1)	dMovePos = pMoveData->dUnloadPickerX1[nMoveIdx];	// AXIS 30
	if (nAxis == AX_UNLOAD_PICKER_Y1)	dMovePos = pMoveData->dUnloadPickerY1[nMoveIdx];	// AXIS 31
	if (nAxis == AX_UNLOAD_PICKER_Z1)	dMovePos = pMoveData->dUnloadPickerZ1[nMoveIdx];	// AXIS 32
	if (nAxis == AX_UNLOAD_PICKER_P1)	dMovePos = pMoveData->dUnloadPickerP1[nMoveIdx];	// AXIS 33
	if (nAxis == AX_UNLOAD_PICKER_X2)	dMovePos = pMoveData->dUnloadPickerX2[nMoveIdx];	// AXIS 34
	if (nAxis == AX_UNLOAD_PICKER_Y2)	dMovePos = pMoveData->dUnloadPickerY2[nMoveIdx];	// AXIS 35
	if (nAxis == AX_UNLOAD_PICKER_Z2)	dMovePos = pMoveData->dUnloadPickerZ2[nMoveIdx];	// AXIS 36
	if (nAxis == AX_UNLOAD_PICKER_P2)	dMovePos = pMoveData->dUnloadPickerP2[nMoveIdx];	// AXIS 37
	if (nAxis == AX_GOOD_STAGE_Y1)		dMovePos = pMoveData->dGoodStageY1[nMoveIdx];		// AXIS 38
	if (nAxis == AX_GOOD_STAGE_Y2)		dMovePos = pMoveData->dGoodStageY2[nMoveIdx];		// AXIS 39
	if (nAxis == AX_NG_STAGE_Y1)		dMovePos = pMoveData->dNGStageY1[nMoveIdx];		// AXIS 40
	if (nAxis == AX_NG_STAGE_Y2)		dMovePos = pMoveData->dNGStageY2[nMoveIdx];		// AXIS 41
	if (nAxis == AX_SHIP_ALIGN_X)		dMovePos = pMoveData->dShiipAling[nMoveIdx];		// AXIS 42
	if (nAxis == AX_TOP1_LIGHT_Z)		dMovePos = pMoveData->dTop1LightZ[nMoveIdx];		// AXIS 43
	if (nAxis == AX_TOP1_ANGLE_Y)		dMovePos = pMoveData->dTop1AngleY[nMoveIdx];		// AXIS 44
	if (dMovePos < -990.0) return FALSE;

	if (fabs(dData - dMovePos) <= dCheckPos) return TRUE;

	CString sTxt;
	sTxt.Format("Position Data 입력범위를 (%0.1lf) Over하였습니다....", dCheckPos);
	AfxMessageBox(sTxt);
	return FALSE;
}
void CCommon::Show_Error(int nErrNo)
{
	g_csShowError.Lock();
	if (gData.bAlarmShow == FALSE) {
		if (!g_dlgError.IsWindowVisible()) {
			Show_ErrorT(nErrNo);
		}
	}
	g_csShowError.Unlock();
/*
	if (!g_dlgError.IsWindowVisible() && !g_dlgAlarm.IsWindowVisible()) {
		g_dlgError.Set_ErrorNumber(nErrNo);
		g_dlgError.ShowWindow(SW_SHOW);
	}
	
*/
}

void CCommon::Show_ErrorT(int nErrNo)
{
	g_dlgError.Set_ErrorNumber(nErrNo);
	AfxBeginThread(Thread_ErrorShow, this);
}

UINT CCommon::Thread_ErrorShow(LPVOID lpVoid)
{
	g_dlgError.ShowWindow(SW_SHOW);
	return 0;
}

void CCommon::Set_ErrorSubMessage(CString sErrSubMsg)
{
	g_dlgError.Set_ErrorSubMessage(sErrSubMsg);
}

void CCommon::Show_Alarm(CString sMsg, int nFm)
{
	g_csShowAlarm.Lock();
	if (!g_dlgAlarm.IsWindowVisible()) {
		Show_AlarmT(sMsg, nFm);	//nFm=1:Host
	}
	g_csShowAlarm.Unlock();
}

void CCommon::Show_AlarmT(CString sMsg, int nFm)
{
	g_dlgAlarm.Set_AlarmMessage(sMsg, nFm);
	AfxBeginThread(Thread_AlarmShow, this);
}

UINT CCommon::Thread_AlarmShow(LPVOID lpVoid)
{
	g_dlgAlarm.ShowWindow(SW_SHOW);
	return 0;
}

int CCommon::Show_MsgBox(int nBtnCnt, CString sMsg)
{
	CMsgBoxDlg dlgMsgBox;
	dlgMsgBox.Set_Message(nBtnCnt, sMsg);
	return dlgMsgBox.DoModal();
}

int CCommon::Show_NumPad(CString sOld, CString &sNew, int nAxis)
{
	CNumPadDlg dlgNumPad;
	dlgNumPad.Set_OldValue(sOld, nAxis);
	if (dlgNumPad.DoModal() != IDOK) return IDCANCEL;

	sNew = g_strReturnNumPad;
	return IDOK;
}

int CCommon::Show_KeyPad(CString &sKey)
{
	CKeyPadDlg dlgKeyPad;
	if (dlgKeyPad.DoModal() != IDOK) return IDCANCEL;

	sKey = g_strReturnKeyPad;
	return IDOK;
}

int CCommon::Show_Password(int &nUser)
{
	CPasswordDlg dlgPassword;
	if (dlgPassword.DoModal() != IDOK) return IDCANCEL;

	nUser = g_nLoginUser;
	return IDOK;
}

BOOL CCommon::Check_MainEmgAir()
{
#ifdef AJIN_BOARD_USE
	DX_DATA_13 *pDX13 = g_objAJinAXL.Get_pDX13();
	if (!pDX13->iMainAir1)	{ Show_Error(1); return FALSE; }
	if (!pDX13->iMainAir2)	{ Show_Error(2); return FALSE; }
	if (!pDX13->iMainAir3)	{ Show_Error(3); return FALSE; }

	if (pDX13->iEmgSw1)	{ Show_Error(5); return FALSE; }
	if (pDX13->iEmgSw2)	{ Show_Error(6); return FALSE; }
	if (pDX13->iEmgSw3)	{ Show_Error(7); return FALSE; }
	if (pDX13->iEmgSw4)	{ Show_Error(8); return FALSE; }
	if (pDX13->iEmgSw5)	{ Show_Error(9); return FALSE; }
	if (pDX13->iEmgSw6)	{ Show_Error(10); return FALSE; }

	//Light curtain
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	DX_DATA_14 *pDX14 = g_objAJinAXL.Get_pDX14();

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (pEquipData->bUseLightCurtain) {
		if (!pDX14->iLightCurtain1) { Show_Error(91); return FALSE; }
		if (!pDX14->iLightCurtain2) { Show_Error(92); return FALSE; }
		if (!pDX14->iLightCurtain3) { Show_Error(93); return FALSE; }
	} else {
		if (!pDX14->iLightCurtain1) {
			if ((!pDX00->iElevator1SlideClose && !pDX00->iElevator1SlideOpen) ||
				(!pDX00->iElevator2SlideClose && !pDX00->iElevator2SlideOpen) ||
				(gData.nElevatorOpen[1] == 2) || (gData.nElevatorOpen[2] == 2) ) {
			} else {
				if (pDX14->iDoor02Unlock) { Show_Error(91); return FALSE; }
			}
		}
		if (!pDX14->iLightCurtain2) {
			if ((!pDX01->iElevator3SlideClose && !pDX01->iElevator3SlideOpen) ||
				(!pDX01->iElevator4SlideClose && !pDX01->iElevator4SlideOpen) ||
				(!pDX02->iElevator5SlideClose && !pDX02->iElevator5SlideOpen) ||
				(gData.nElevatorOpen[3] == 2) || (gData.nElevatorOpen[4] == 2) || (gData.nElevatorOpen[5] == 2) ) {
			} else {
				if (pDX14->iDoor03Unlock) { Show_Error(92); return FALSE; }
				if (pDX14->iDoor04Unlock) { Show_Error(92); return FALSE; }
			}
		}
		if (!pDX14->iLightCurtain3) {
			if ((!pDX02->iElevator6SlideClose && !pDX02->iElevator6SlideOpen) ||
				(!pDX02->iElevator7SlideClose && !pDX02->iElevator7SlideOpen) ||
				(gData.nElevatorOpen[6] == 2) || (gData.nElevatorOpen[7] == 2) ) {
			} else {
				if (pDX14->iDoor05Unlock) { Show_Error(93); return FALSE; }
			}
		}
	}
#endif
	return TRUE;
}

BOOL CCommon::Check_MainDoor(BOOL bAuto)
{
//	if (gData.bUseDryRun) return TRUE;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseDoorLock) return TRUE;

#ifdef AJIN_BOARD_USE
	DX_DATA_14 *pDX14 = g_objAJinAXL.Get_pDX14();

	if (pDX14->iDoor01Unlock) { Show_Error(11); return FALSE; }
	if (!(gData.nElevatorOpen[1] == 2 || gData.nElevatorOpen[2] == 2)) {
		if (pDX14->iDoor02Unlock) { Show_Error(12); return FALSE; }
	}
	if (!(gData.nElevatorOpen[3] == 2 || gData.nElevatorOpen[4] == 2 || gData.nElevatorOpen[5] == 2)) {
		if (pDX14->iDoor03Unlock) { Show_Error(13); return FALSE; }
		if (pDX14->iDoor04Unlock) { Show_Error(14); return FALSE; }
	}
	if (!(gData.nElevatorOpen[6] == 2 || gData.nElevatorOpen[7] == 2)) {
		if (pDX14->iDoor05Unlock) { Show_Error(15); return FALSE; }	
	}
	if (pDX14->iDoor06Unlock) { Show_Error(16); return FALSE; }
	if (pDX14->iDoor07Unlock) { Show_Error(17); return FALSE; }
	if (pDX14->iDoor08Unlock) { Show_Error(18); return FALSE; }
	if (pDX14->iDoor09Unlock) { Show_Error(19); return FALSE; }
	if (pDX14->iDoor10Unlock) { Show_Error(20); return FALSE; }
	if (pDX14->iDoor11Unlock) { Show_Error(21); return FALSE; }
	if (pDX14->iDoor12Unlock) { Show_Error(22); return FALSE; }
	if (pDX14->iDoor13Unlock) { Show_Error(23); return FALSE; }
	if (pDX14->iDoor14Unlock) { Show_Error(24); return FALSE; }
	if (pDX14->iDoor15Unlock) { Show_Error(25); return FALSE; }
	if (pDX14->iDoor16Unlock) { Show_Error(26); return FALSE; }
	if (pDX14->iDoor17Unlock) { Show_Error(27); return FALSE; }
	if (pDX14->iDoor18Unlock) { Show_Error(28); return FALSE; }
	if (pDX14->iDoor19Unlock) { Show_Error(29); return FALSE; }
	if (pDX14->iDoor20Unlock) { Show_Error(30); return FALSE; }
	if (pDX14->iDoor21Unlock) { Show_Error(31); return FALSE; }
#endif
	return TRUE;
}

void CCommon::Locking_TrayDoor(BOOL bLock, int nElevtorNo)
{
	DY_DATA_14 *pDY14 = g_objAJinAXL.Get_pDY14();

	if (bLock) {
		if		(nElevtorNo == 1 || nElevtorNo == 2) pDY14->oDoor02Unlock = FALSE;
		else if (nElevtorNo == 6 || nElevtorNo == 7) pDY14->oDoor05Unlock = FALSE;
		else										{pDY14->oDoor03Unlock = pDY14->oDoor04Unlock = FALSE; }
		g_objAJinAXL.Write_Output(14);
	} else {
		if		(nElevtorNo == 1 || nElevtorNo == 2) pDY14->oDoor02Unlock = TRUE;
		else if (nElevtorNo == 6 || nElevtorNo == 7) pDY14->oDoor05Unlock = TRUE;
		else										{pDY14->oDoor03Unlock = pDY14->oDoor04Unlock = TRUE; }
		g_objAJinAXL.Write_Output(14);
	}
}

BOOL CCommon::Check_TraySlide(int nType)
{
#ifdef AJIN_BOARD_USE
	int nErrNo = 0;
	CString sErrMsg;

	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	if (!pDX00->iElevator1SlideClose) { nErrNo = 51; sErrMsg.Format("Load 1 Elevator Slide를 Close해 주세요."); }
	if (pDX00->iElevator1SlideOpen)   { nErrNo = 52; sErrMsg.Format("Load 1 Elevator Slide를 Close해 주세요."); }
	if (!pDX00->iElevator2SlideClose) { nErrNo = 53; sErrMsg.Format("Load 2 Elevator Slide를 Close해 주세요."); }
	if (pDX00->iElevator2SlideOpen)   { nErrNo = 54; sErrMsg.Format("Load 2 Elevator Slide를 Close해 주세요."); }
	if (!pDX01->iElevator3SlideClose) { nErrNo = 55; sErrMsg.Format("Empty NG Elevator Slide를 Close해 주세요."); }
	if (pDX01->iElevator3SlideOpen)   { nErrNo = 56; sErrMsg.Format("Empty NG Elevator Slide를 Close해 주세요."); }
	if (!pDX01->iElevator4SlideClose) { nErrNo = 57; sErrMsg.Format("Empty Good Elevator Slide를 Close해 주세요."); }
	if (pDX01->iElevator4SlideOpen)   { nErrNo = 58; sErrMsg.Format("Empty Good Elevator Slide를 Close해 주세요."); }
	if (!pDX02->iElevator5SlideClose) { nErrNo = 59; sErrMsg.Format("NG Buffer Elevator Slide를 Close해 주세요."); }
	if (pDX02->iElevator5SlideOpen)   { nErrNo = 60; sErrMsg.Format("NG Buffer Elevator Slide를 Close해 주세요."); }
	if (!pDX02->iElevator6SlideClose) { nErrNo = 61; sErrMsg.Format("NG Tray Elevator Slide를 Close해 주세요."); }
	if (pDX02->iElevator6SlideOpen)   { nErrNo = 62; sErrMsg.Format("NG Tray Elevator Slide를 Close해 주세요."); }
	if (!pDX02->iElevator7SlideClose) { nErrNo = 63; sErrMsg.Format("Good Tray Elevator Slide를 Close해 주세요."); }
	if (pDX02->iElevator7SlideOpen)   { nErrNo = 64; sErrMsg.Format("Good Tray Elevator Slide를 Close해 주세요."); }

	if (nErrNo == 0) return TRUE;

	if (nType == 9) { g_objCommon.Show_MsgBox(1, sErrMsg); return FALSE; }	//화면
	if (nType == 1) { Show_Error(nErrNo); return FALSE; }					//초기화
	if (nType == 0) {														//Main
		if (gData.nElevatorOpen[1] > 0 && (nErrNo == 51 || nErrNo == 52)) nErrNo = 0;
		if (gData.nElevatorOpen[2] > 0 && (nErrNo == 53 || nErrNo == 54)) nErrNo = 0;
		if (gData.nElevatorOpen[3] > 0 && (nErrNo == 55 || nErrNo == 56)) nErrNo = 0;
		if (gData.nElevatorOpen[4] > 0 && (nErrNo == 57 || nErrNo == 58)) nErrNo = 0;
		if (gData.nElevatorOpen[5] > 0 && (nErrNo == 59 || nErrNo == 60)) nErrNo = 0;
		if (gData.nElevatorOpen[6] > 0 && (nErrNo == 61 || nErrNo == 62)) nErrNo = 0;
		if (gData.nElevatorOpen[7] > 0 && (nErrNo == 63 || nErrNo == 64)) nErrNo = 0;
		if (nErrNo > 0) { Show_Error(nErrNo); return FALSE; }
	}

#endif
	return TRUE;
}

BOOL CCommon::Check_EmptyTray()
{
	int nErrNo = 0;
#ifdef AJIN_BOARD_USE
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();

	if (gData.nElevatorOpen[3] == 0 && !pDX01->iElevator3TrayExist) { Show_Error(71); return FALSE; }	//NG-Empty
	if (gData.nElevatorOpen[4] == 0 && !pDX01->iElevator4TrayExist) { Show_Error(72); return FALSE; }	//Good-Empty
#endif
	return TRUE;
}

BOOL CCommon::Check_Elevator()
{
	double dPos;
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();

	int *pCase = g_objSequenceMain.Get_pMainRunCase();
	dPos = g_objAJinAXL.Get_Position(AX_ELEVATOR_Z1);
	if (*(pCase+0) != 20 && dPos < (gData.dElevatorDown + 1.0) && pDX00->iElevator1SlideClose && (pDX00->iElevator1Height1 || pDX00->iElevator1Height2)) { Show_Error(2180); return FALSE; }
	dPos = g_objAJinAXL.Get_Position(AX_ELEVATOR_Z2);
	if (*(pCase+1) != 20 && dPos < (gData.dElevatorDown + 1.0) && pDX00->iElevator2SlideClose && (pDX00->iElevator2Height1 || pDX00->iElevator2Height2)) { Show_Error(2280); return FALSE; }
	dPos = g_objAJinAXL.Get_Position(AX_ELEVATOR_Z3);
	if (*(pCase+2) != 20 && dPos < (gData.dElevatorDown + 1.0) && pDX01->iElevator3SlideClose && (pDX01->iElevator3Height1 || pDX01->iElevator3Height2)) { Show_Error(2380); return FALSE; }
	dPos = g_objAJinAXL.Get_Position(AX_ELEVATOR_Z4);
	if (*(pCase+3) != 20 && dPos < (gData.dElevatorDown + 1.0) && pDX01->iElevator4SlideClose && (pDX01->iElevator4Height1 || pDX01->iElevator4Height2)) { Show_Error(2480); return FALSE; }
	dPos = g_objAJinAXL.Get_Position(AX_ELEVATOR_Z5);
	if (*(pCase+4) != 20 && dPos < (gData.dElevatorDown + 1.0) && pDX02->iElevator5SlideClose && (pDX02->iElevator5Height1 || pDX02->iElevator5Height2)) { Show_Error(2580); return FALSE; }
	dPos = g_objAJinAXL.Get_Position(AX_ELEVATOR_Z6);
	if (*(pCase+5) != 20 && dPos < (gData.dElevatorDown + 1.0) && pDX02->iElevator6SlideClose && (pDX02->iElevator6Height1)) { Show_Error(2680); return FALSE; }
	dPos = g_objAJinAXL.Get_Position(AX_ELEVATOR_Z7);
	if (*(pCase+6) != 20 && dPos < (gData.dElevatorDown + 1.0) && pDX02->iElevator7SlideClose && (pDX02->iElevator7Height1)) { Show_Error(2780); return FALSE; }

	return TRUE;
}

// Servo On Error : Error (100 - 181)
BOOL CCommon::Check_ServoOn()
{
#ifdef AJIN_BOARD_USE
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (!g_objAJinAXL.Get_ServoOn(i)) { Show_Error(i + 100); return FALSE; }
	}
#endif
	return TRUE;
}

// Drive Alarm : Error(200 - 281)
BOOL CCommon::Check_DirveAlarm()
{
#ifdef AJIN_BOARD_USE
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (!g_objAJinAXL.Is_ServoAxis(i)) continue;
		if (g_objAJinAXL.Get_AmpAlarm(i)) { Show_Error(i + 200); return FALSE; }
	}
#endif
	return TRUE;
}

// Limit Check : Error ELN(300 - 381), ELP(400 - 481)
BOOL CCommon::Check_EndLimit()
{
#ifdef AJIN_BOARD_USE
//	for (int i = 7; i < AXIS_COUNT; i++) {
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (g_objAJinAXL.Get_EndLimitPos(i)) { Show_Error(i + 300); return FALSE; }
		if (g_objAJinAXL.Get_EndLimitNeg(i)) { Show_Error(i + 400); return FALSE; }
	}
#endif
	return TRUE;
}

// Home Check : Error (500 - 581)
BOOL CCommon::Check_HomeDone()
{
#ifdef AJIN_BOARD_USE
	for (int i = 0; i < AXIS_COUNT; i++) {
		if (!g_objAJinAXL.Get_HomeDone(i)) { Show_Error(i + 500); return FALSE; }
	}
#endif
	return TRUE;
}

BOOL CCommon::Read_FocusOffset()
{
	CIniFileCS INI(gsCurrentDir + "\\System\\VisionStageOffset.ini");
	if (!INI.Check_File()) {
		for(int i=0; i<4; i++) for(int j=0; j<8; j++) gData.dFocusOffset[i][j] = 0.0;
		return FALSE;
	}

	gData.sOffsetInfor[0] = INI.Get_String("INFORMATION", "EQUIPNAME", "");
	gData.sOffsetInfor[1] = INI.Get_String("INFORMATION", "VERSION", "");
	gData.sOffsetInfor[2] = INI.Get_String("INFORMATION", "UPDATE", "");
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (gData.sOffsetInfor[0] != pEquipData->sEquipName) {
		for(int i=0; i<4; i++) for(int j=0; j<8; j++) gData.dFocusOffset[i][j] = 0.0;
		return FALSE;
	}

	CString strKey, strApp;
	for(int i=0; i<4; i++) {
		strApp.Format("STAGE%d", i+1);
		for(int j=0; j<8; j++) {
			strKey.Format("%02d", j+1);
			gData.dFocusOffset[i][j] = INI.Get_Double(strApp, strKey, 0.0);
		}
	}
	return TRUE;
}

BOOL CCommon::Check_SlideLock(int nElevNo)	//nElevNo:0~7
{
	int nErrNo = 0;
	return TRUE;	//gjc
	DX_DATA_00 *pDX00 = g_objAJinAXL.Get_pDX00();
	DX_DATA_01 *pDX01 = g_objAJinAXL.Get_pDX01();
	DX_DATA_02 *pDX02 = g_objAJinAXL.Get_pDX02();
	DX_DATA_03 *pDX03 = g_objAJinAXL.Get_pDX03();

	if (nElevNo==0 || nElevNo==1) { if (gData.nElevatorOpen[1] == 0 && (!pDX00->iElevator1SlideLock || pDX00->iElevator1SlideUnlock)) return FALSE; }
	if (nElevNo==0 || nElevNo==2) { if (gData.nElevatorOpen[2] == 0 && (!pDX00->iElevator2SlideLock || pDX00->iElevator2SlideUnlock)) return FALSE; }
	if (nElevNo==0 || nElevNo==3) { if (gData.nElevatorOpen[3] == 0 && (!pDX01->iElevator3SlideLock || pDX01->iElevator3SlideUnlock)) return FALSE; }
	if (nElevNo==0 || nElevNo==4) { if (gData.nElevatorOpen[4] == 0 && (!pDX01->iElevator4SlideLock || pDX01->iElevator4SlideUnlock)) return FALSE; }
	if (nElevNo==0 || nElevNo==5) { if (gData.nElevatorOpen[5] == 0 && (!pDX02->iElevator5SlideLock || pDX02->iElevator5SlideUnlock)) return FALSE; }
	if (nElevNo==0 || nElevNo==6) { if (gData.nElevatorOpen[6] == 0 && (!pDX02->iElevator6SlideLock || pDX02->iElevator6SlideUnlock)) return FALSE; }
	if (nElevNo==0 || nElevNo==7) { if (gData.nElevatorOpen[7] == 0 && (!pDX03->iElevator7SlideLock || pDX03->iElevator7SlideUnlock)) return FALSE; }

	return TRUE;
}

void CCommon::Stop_Elevator()
{
	return;
	g_objAJinAXL.Stop_Motion(AX_ELEVATOR_Z1);
	g_objAJinAXL.Stop_Motion(AX_ELEVATOR_Z2);
	g_objAJinAXL.Stop_Motion(AX_ELEVATOR_Z3);
	g_objAJinAXL.Stop_Motion(AX_ELEVATOR_Z4);
	g_objAJinAXL.Stop_Motion(AX_ELEVATOR_Z5);
	g_objAJinAXL.Stop_Motion(AX_ELEVATOR_Z6);
	g_objAJinAXL.Stop_Motion(AX_ELEVATOR_Z7);

	int *pCase = g_objSequenceMain.Get_pMainRunCase();
	if (*(pCase+0) != 20) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_1, 1);
	if (*(pCase+1) != 20) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_2, 1);
	if (*(pCase+2) != 20) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_3, 1);
	if (*(pCase+3) != 20) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_4, 1);
	if (*(pCase+4) != 20) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_5, 1);
	if (*(pCase+5) != 20) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_6, 1);
	if (*(pCase+6) != 20) g_objSequenceMain.Set_MainRunCase(AUTO_ELEVATOR_7, 1);
}

void CCommon::BuzzerOn()
{
	gData.m_bBuzzerOff = FALSE;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();

	pDY13->oBuzzerBit0 = pEquipData->bBuzzer[1][0];
	pDY13->oBuzzerBit1 = pEquipData->bBuzzer[1][1];
	pDY13->oBuzzerBit2 = pEquipData->bBuzzer[1][2];
	pDY13->oBuzzerBit3 = pEquipData->bBuzzer[1][3];
	pDY13->oBuzzerBit4 = pEquipData->bBuzzer[1][4];
	g_objAJinAXL.Write_Output(13);
}

void CCommon::BuzzerOff()
{
	gData.m_bBuzzerOff = TRUE;

	DY_DATA_13 *pDY13 = g_objAJinAXL.Get_pDY13();
	pDY13->oBuzzerBit0 = FALSE;
	pDY13->oBuzzerBit1 = FALSE;
	pDY13->oBuzzerBit2 = FALSE;
	pDY13->oBuzzerBit3 = FALSE;
	pDY13->oBuzzerBit4 = FALSE;
	g_objAJinAXL.Write_Output(13);

}

void CCommon::Check_InsideLamp()
{
	DX_DATA_14 *pDX14 = g_objAJinAXL.Get_pDX14();
	DY_DATA_14 *pDY14 = g_objAJinAXL.Get_pDY14();

	if (pDX14->iDoor01Unlock ||	pDX14->iDoor02Unlock || pDX14->iDoor03Unlock || pDX14->iDoor04Unlock || pDX14->iDoor05Unlock ||
		pDX14->iDoor06Unlock || pDX14->iDoor07Unlock || pDX14->iDoor08Unlock || pDX14->iDoor09Unlock || pDX14->iDoor10Unlock ||
		pDX14->iDoor11Unlock || pDX14->iDoor12Unlock || pDX14->iDoor13Unlock || pDX14->iDoor14Unlock || pDX14->iDoor15Unlock ||
		pDX14->iDoor16Unlock || pDX14->iDoor17Unlock || pDX14->iDoor18Unlock || pDX14->iDoor19Unlock || pDX14->iDoor20Unlock ||
		pDX14->iDoor21Unlock ) {
		gData.bDoorOpen = TRUE;
		if (!m_bInsideLight) {
			m_bInsideLight = TRUE;
			pDY14->oInsideLight = TRUE;
			g_objAJinAXL.Write_Output(14);
		}
	} else {
		if (m_bInsideLight) {
			m_bInsideLight = FALSE;
			pDY14->oInsideLight = FALSE;
			g_objAJinAXL.Write_Output(14);
		}
		EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
		if (gData.bDoorOpen && !pEquipData->bUseDoorLock) {
			CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
			if (INI.Check_File()) {
				INI.Set_Bool("EQUIPMENT", "DOOR_LOCK", TRUE);
			}
			pEquipData->bUseDoorLock = TRUE;
			gData.dwDoorStartTime = 0;
			g_objDataManager.Read_EquipData();
		}
		gData.bDoorOpen = FALSE;
	}
}

void CCommon::Locking_MainDoor(BOOL bLock, BOOL bAuto)
{
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseDoorLock && bLock && !bAuto) return;
	if (pEquipData->bUseDoorLock && !bLock && !bAuto) return;

	DY_DATA_14 *pDY14 = g_objAJinAXL.Get_pDY14();

	if (bLock) {	//LOCK
		pDY14->oDoor01Unlock = FALSE;
		pDY14->oDoor02Unlock = FALSE;
		pDY14->oDoor03Unlock = FALSE;
		pDY14->oDoor04Unlock = FALSE;
		pDY14->oDoor05Unlock = FALSE;
		pDY14->oDoor06Unlock = FALSE;
		pDY14->oDoor07Unlock = FALSE;
		pDY14->oDoor08Unlock = FALSE;
		pDY14->oDoor09Unlock = FALSE;
		pDY14->oDoor10Unlock = FALSE;
		pDY14->oDoor11Unlock = FALSE;
		pDY14->oDoor12Unlock = FALSE;
		pDY14->oDoor13Unlock = FALSE;
		pDY14->oDoor14Unlock = FALSE;
		pDY14->oDoor15Unlock = FALSE;
		pDY14->oDoor16Unlock = FALSE;
		pDY14->oDoor17Unlock = FALSE;
		pDY14->oDoor18Unlock = FALSE;
		pDY14->oDoor19Unlock = FALSE;
		pDY14->oDoor20Unlock = FALSE;
		pDY14->oDoor21Unlock = FALSE;
		g_objAJinAXL.Write_Output(14);
	} else {	//Unloack
		pDY14->oDoor01Unlock = TRUE;
		pDY14->oDoor02Unlock = TRUE;
		pDY14->oDoor03Unlock = TRUE;
		pDY14->oDoor04Unlock = TRUE;
		pDY14->oDoor05Unlock = TRUE;
		pDY14->oDoor06Unlock = TRUE;
		pDY14->oDoor07Unlock = TRUE;
		pDY14->oDoor08Unlock = TRUE;
		pDY14->oDoor09Unlock = TRUE;
		pDY14->oDoor10Unlock = TRUE;
		pDY14->oDoor11Unlock = TRUE;
		pDY14->oDoor12Unlock = TRUE;
		pDY14->oDoor13Unlock = TRUE;
		pDY14->oDoor14Unlock = TRUE;
		pDY14->oDoor15Unlock = TRUE;
		pDY14->oDoor16Unlock = TRUE;
		pDY14->oDoor17Unlock = TRUE;
		pDY14->oDoor18Unlock = TRUE;
		pDY14->oDoor19Unlock = TRUE;
		pDY14->oDoor20Unlock = TRUE;
		pDY14->oDoor21Unlock = TRUE;
		g_objAJinAXL.Write_Output(14);
	}
	gData.bDoorLock = bLock;
}

void CCommon::Locking_Slide(BOOL bLock, int nElevNo)
{
	DY_DATA_00 *pDY00 = g_objAJinAXL.Get_pDY00();
	DY_DATA_01 *pDY01 = g_objAJinAXL.Get_pDY01();
	DY_DATA_02 *pDY02 = g_objAJinAXL.Get_pDY02();
	DY_DATA_03 *pDY03 = g_objAJinAXL.Get_pDY03();

	if (bLock) {	//LOCK
		if (nElevNo==0 || nElevNo==1) { pDY00->oElevator1SlideLock = TRUE; pDY00->oElevator1SlideUnlock = FALSE; }
		if (nElevNo==0 || nElevNo==2) { pDY01->oElevator2SlideLock = TRUE; pDY01->oElevator2SlideUnlock = FALSE; }
		if (nElevNo==0 || nElevNo==3) { pDY01->oElevator3SlideLock = TRUE; pDY01->oElevator3SlideUnlock = FALSE; }
		if (nElevNo==0 || nElevNo==4) { pDY02->oElevator4SlideLock = TRUE; pDY02->oElevator4SlideUnlock = FALSE; }
		if (nElevNo==0 || nElevNo==5) { pDY02->oElevator5SlideLock = TRUE; pDY02->oElevator5SlideUnlock = FALSE; }
		if (nElevNo==0 || nElevNo==6) { pDY02->oElevator6SlideLock = TRUE; pDY02->oElevator6SlideUnlock = FALSE; }
		if (nElevNo==0 || nElevNo==7) { pDY03->oElevator7SlideLock = TRUE; pDY03->oElevator7SlideUnlock = FALSE; }
	} else {	//Unloack
		if (nElevNo==0 || nElevNo==1) { pDY00->oElevator1SlideLock = FALSE; pDY00->oElevator1SlideUnlock = TRUE; }
		if (nElevNo==0 || nElevNo==2) { pDY01->oElevator2SlideLock = FALSE; pDY01->oElevator2SlideUnlock = TRUE; }
		if (nElevNo==0 || nElevNo==3) { pDY01->oElevator3SlideLock = FALSE; pDY01->oElevator3SlideUnlock = TRUE; }
		if (nElevNo==0 || nElevNo==4) { pDY02->oElevator4SlideLock = FALSE; pDY02->oElevator4SlideUnlock = TRUE; }
		if (nElevNo==0 || nElevNo==5) { pDY02->oElevator5SlideLock = FALSE; pDY02->oElevator5SlideUnlock = TRUE; }
		if (nElevNo==0 || nElevNo==6) { pDY02->oElevator6SlideLock = FALSE; pDY02->oElevator6SlideUnlock = TRUE; }
		if (nElevNo==0 || nElevNo==7) { pDY03->oElevator7SlideLock = FALSE; pDY03->oElevator7SlideUnlock = TRUE; }
	}

	if (nElevNo==0 || nElevNo==1)							  g_objAJinAXL.Write_Output(0);
	if (nElevNo==0 || nElevNo==2 || nElevNo==3)				  g_objAJinAXL.Write_Output(1);
	if (nElevNo==0 || nElevNo==4 || nElevNo==5 || nElevNo==6) g_objAJinAXL.Write_Output(2);
	if (nElevNo==0 || nElevNo==7)							  g_objAJinAXL.Write_Output(3);
}

/////////////////////////////////////////////////////////////////////////////

void CCommon::Wait_Time(int msec)
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	INT64 nFrequency = freq.QuadPart;

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	INT64 timeS = counter.QuadPart;
	double dTerm = 0.0;

	do {
		DoEvents();
		QueryPerformanceCounter(&counter);
		INT64 timeE = counter.QuadPart;
		dTerm = (timeE - timeS) / nFrequency * 1000.0;
	} while (dTerm < msec);
}

int CCommon::Get_Random(int nStart, int nEnd)
{
	static BOOL bSeed = FALSE;
	if (nStart >= nEnd) return 0;
	if (!bSeed) { srand((unsigned)time(NULL)); bSeed = TRUE; }
	return (rand() % (nEnd - nStart + 1) + nStart);
}

void CCommon::Backup_File(CString strPath, CString strName)
{
	g_objLogFile.Create_Folder(strPath + "\\Backup");

	CString strOriginFile, strTargetFile, strDateTime;

	SYSTEMTIME time;
	GetLocalTime(&time);
	strDateTime.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

	strOriginFile.Format("%s\\%s.ini", strPath, strName);
	strTargetFile.Format("%s\\Backup\\%s_%s.ini", strPath, strName, strDateTime);

	if (!CopyFile(strOriginFile, strTargetFile, FALSE)) return;
}

void CCommon::Add_NGCodeCount(int nNo, CString sJudge, CString sNGCode)
{
	/*
	CString sNGCodeList[15] = {"Terminal Solder Over", "Terminal Solder Lack", "Terminal Solder None", "York Solder Over", "York Solder Lack", "York Solder None",
							   "HTTC Crack", "HTTC Solder", "HTTC Epoxy Over", "Sensor Crack", "ETC", "Board Protrusion L", "Board Protrusion M", "Board Protrusion H", "G_ETC"};

	if (sJudge == "G" && sNGCode.GetLength() < 5) return;

	int nFind = 99;
	for(int i=0; i<15; i++) {
		if (sNGCodeList[i] == sNGCode) {
			nFind = i;
			break;
		}
	}
	if (nFind < 15) {		gLot.nNgCodeCnt[nNo][nFind]++;
	} else {
		if (sJudge == "N")	gLot.nNgCodeCnt[nNo][10]++;	//ETC
		else				gLot.nNgCodeCnt[nNo][14]++;	//G_ETC
	} */		
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CCommon::Check_NGTrayFull()
{
	for(int i=0; i<TRAY_CM_Y; i++) {
		for(int j=0; j<TRAY_CM_X; j++) {
			if (gData.InfoNgTray[i][j] == 0) return FALSE;
		}
	}
	return TRUE;
}

void CCommon::Set_LotDataClear(int nPortNo)	//nPortNo:0~5;
{	
	if (nPortNo < 0 || nPortNo > 5) return;

	int nNo = nPortNo;
	gLot.nCmCount[nNo] = gLot.nTrayCount[nNo] = gLot.nLastCount[nNo] = gLot.nLotStatus[nNo] = gLot.nTrayOutCnt[nNo] = gLot.nGoodCount[nNo] = gLot.nNgCount[nNo] = 0;
	gLot.nUnlGdTrayCount[nNo] = gLot.nUnlNGTrayCount[nNo] = gLot.nOutTrayCnt[nNo][0] = gLot.nOutTrayCnt[nNo][1] = gLot.nSkipCount[nNo] = gLot.nAlignCount[nNo] = 0;
	gLot.nErrorCount[nNo] = gLot.dwErrorTime[nNo] = gLot.dwStopTime[nNo] = gMes.nLotStatus[nNo] = 0;
	gLot.sLotID[nNo] = gLot.sLLStartTime[nNo] = gLot.sLLEndTime[nNo] = "";
	gLot.bEmptyTray[nNo] = gLot.bEmptyNGTray[nNo] = FALSE;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 40; j++) {
			gMes.nCmResult[nNo][i][j] = gLot.nJudge_R[nNo][i][j] = gLot.nImageCnt[nNo][i][j] = gLot.nMarginal[nNo][i][j] = 0; gLot.sBarCode[nNo][i][j] = "";
			for (int k = 0; k < 6; k++) { gLot.nJudge_I[nNo][i][j][k] = 0; gLot.sNGCode_I[nNo][i][j][k] = ""; }
			for (int k = 0; k <10; k++)	  gLot.nHistory[nNo][i][j][k] = 0;
		}
	}
	for (int i = 0; i <13; i++) gLot.nRosJugCount[nNo][i] = 0;
	for (int i = 0; i < 3; i++) gLot.nTrayPutCnt[nNo][i] = 0;
	for (int j = 0; j < 16; j++) for (int k = 0; k < 40; k++) for (int m = 0; m < 5; m++) for (int n = 0; n < 10; n++) gNG->sNGCode[nNo][j][k][m][n] = "";
	for (int j = 0; j <640; j++) for (int k = 0; k < 10; k++) gNG->sModuleID[nNo][j][k] = "";
	g_objDispatcher.Reset(nNo+1);
}

void CCommon::Display_MESRecipe(CString sRecipe)
{
	CIniFileCS INI(gsCurrentDir + "\\System\\EquipData.ini");
	INI.Set_String("EQUIPMENT", "MODEL", sRecipe);
	g_objDataManager.Read_EquipData();

	CCMAI2100Dlg *pMainDlg = (CCMAI2100Dlg*)AfxGetMainWnd();
	pMainDlg->Display_EquipName();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
void CCommon::Set_LoadPickerOpen(int nPickNo, int nType, int nNo)
{	
	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	if (nPickNo ==  1) {
		DY_DATA_05 *pDY05 = g_objAJinAXL.Get_pDY05();
		if (nType == 9) {
			if (nNo == 0 || nNo == 1)	{ pDY05->oLoadPicker1Open1 = TRUE; pDY05->oLoadPicker1Close1 = FALSE; }
			if (nNo == 0 || nNo == 2)	{ pDY05->oLoadPicker1Open2 = TRUE; pDY05->oLoadPicker1Close2 = FALSE; }
			if (nNo == 0 || nNo == 3)	{ pDY05->oLoadPicker1Open3 = TRUE; pDY05->oLoadPicker1Close3 = FALSE; }
			if (nNo == 0 || nNo == 4)	{ pDY05->oLoadPicker1Open4 = TRUE; pDY05->oLoadPicker1Close4 = FALSE; }
			if (nNo == 0 || nNo == 5)	{ pDY05->oLoadPicker1Open5 = TRUE; pDY05->oLoadPicker1Close5 = FALSE; }
			if (nNo == 0 || nNo == 6)	{ pDY05->oLoadPicker1Open6 = TRUE; pDY05->oLoadPicker1Close6 = FALSE; }
			if (nNo == 0 || nNo == 7)	{ pDY05->oLoadPicker1Open7 = TRUE; pDY05->oLoadPicker1Close7 = FALSE; }
			if (nNo == 0 || nNo == 8)	{ pDY05->oLoadPicker1Open8 = TRUE; pDY05->oLoadPicker1Close8 = FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ pDY05->oLoadPicker1Open1 = TRUE; pDY05->oLoadPicker1Close1 = FALSE; pDY05->oLoadPicker1Open2 = TRUE; pDY05->oLoadPicker1Close2 = FALSE; }
			if (nNo == 0 || nNo == 2)	{ pDY05->oLoadPicker1Open3 = TRUE; pDY05->oLoadPicker1Close3 = FALSE; pDY05->oLoadPicker1Open4 = TRUE; pDY05->oLoadPicker1Close4 = FALSE; }
			if (nNo == 0 || nNo == 3)	{ pDY05->oLoadPicker1Open5 = TRUE; pDY05->oLoadPicker1Close5 = FALSE; pDY05->oLoadPicker1Open6 = TRUE; pDY05->oLoadPicker1Close6 = FALSE; }
			if (nNo == 0 || nNo == 4)	{ pDY05->oLoadPicker1Open7 = TRUE; pDY05->oLoadPicker1Close7 = FALSE; pDY05->oLoadPicker1Open8 = TRUE; pDY05->oLoadPicker1Close8 = FALSE; }
		}
		g_objAJinAXL.Write_Output(5);
	}
	if (nPickNo ==  2) {
		DY_DATA_06 *pDY06 = g_objAJinAXL.Get_pDY06();
		if (nType == 9) {
			if (nNo == 0 || nNo == 1)	{ pDY06->oLoadPicker2Open1 = TRUE; pDY06->oLoadPicker2Close1 = FALSE; }
			if (nNo == 0 || nNo == 2)	{ pDY06->oLoadPicker2Open2 = TRUE; pDY06->oLoadPicker2Close2 = FALSE; }
			if (nNo == 0 || nNo == 3)	{ pDY06->oLoadPicker2Open3 = TRUE; pDY06->oLoadPicker2Close3 = FALSE; }
			if (nNo == 0 || nNo == 4)	{ pDY06->oLoadPicker2Open4 = TRUE; pDY06->oLoadPicker2Close4 = FALSE; }
			if (nNo == 0 || nNo == 5)	{ pDY06->oLoadPicker2Open5 = TRUE; pDY06->oLoadPicker2Close5 = FALSE; }
			if (nNo == 0 || nNo == 6)	{ pDY06->oLoadPicker2Open6 = TRUE; pDY06->oLoadPicker2Close6 = FALSE; }
			if (nNo == 0 || nNo == 7)	{ pDY06->oLoadPicker2Open7 = TRUE; pDY06->oLoadPicker2Close7 = FALSE; }
			if (nNo == 0 || nNo == 8)	{ pDY06->oLoadPicker2Open8 = TRUE; pDY06->oLoadPicker2Close8 = FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ pDY06->oLoadPicker2Open1 = TRUE; pDY06->oLoadPicker2Close1 = FALSE; pDY06->oLoadPicker2Open2 = TRUE; pDY06->oLoadPicker2Close2 = FALSE; }
			if (nNo == 0 || nNo == 2)	{ pDY06->oLoadPicker2Open3 = TRUE; pDY06->oLoadPicker2Close3 = FALSE; pDY06->oLoadPicker2Open4 = TRUE; pDY06->oLoadPicker2Close4 = FALSE; }
			if (nNo == 0 || nNo == 3)	{ pDY06->oLoadPicker2Open5 = TRUE; pDY06->oLoadPicker2Close5 = FALSE; pDY06->oLoadPicker2Open6 = TRUE; pDY06->oLoadPicker2Close6 = FALSE; }
			if (nNo == 0 || nNo == 4)	{ pDY06->oLoadPicker2Open7 = TRUE; pDY06->oLoadPicker2Close7 = FALSE; pDY06->oLoadPicker2Open8 = TRUE; pDY06->oLoadPicker2Close8 = FALSE; }
		}
		g_objAJinAXL.Write_Output(6);
	}
}

void CCommon::Set_LoadPickerClose(int nPickNo, int nType, int nNo)
{	
	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	if (nPickNo ==  1) {
		DY_DATA_05 *pDY05 = g_objAJinAXL.Get_pDY05();
		if (nType == 9) {
			if (nNo == 0 || nNo == 1)	{ pDY05->oLoadPicker1Open1 = FALSE; pDY05->oLoadPicker1Close1 = TRUE; }
			if (nNo == 0 || nNo == 2)	{ pDY05->oLoadPicker1Open2 = FALSE; pDY05->oLoadPicker1Close2 = TRUE; }
			if (nNo == 0 || nNo == 3)	{ pDY05->oLoadPicker1Open3 = FALSE; pDY05->oLoadPicker1Close3 = TRUE; }
			if (nNo == 0 || nNo == 4)	{ pDY05->oLoadPicker1Open4 = FALSE; pDY05->oLoadPicker1Close4 = TRUE; }
			if (nNo == 0 || nNo == 5)	{ pDY05->oLoadPicker1Open5 = FALSE; pDY05->oLoadPicker1Close5 = TRUE; }
			if (nNo == 0 || nNo == 6)	{ pDY05->oLoadPicker1Open6 = FALSE; pDY05->oLoadPicker1Close6 = TRUE; }
			if (nNo == 0 || nNo == 7)	{ pDY05->oLoadPicker1Open7 = FALSE; pDY05->oLoadPicker1Close7 = TRUE; }
			if (nNo == 0 || nNo == 8)	{ pDY05->oLoadPicker1Open8 = FALSE; pDY05->oLoadPicker1Close8 = TRUE; }
			g_objAJinAXL.Write_Output(5);
			return;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo == 1) { pDY05->oLoadPicker1Open1 = FALSE; pDY05->oLoadPicker1Close1 = TRUE; }
				if (nNo == 2) { pDY05->oLoadPicker1Open3 = FALSE; pDY05->oLoadPicker1Close3 = TRUE; }
				if (nNo == 3) { pDY05->oLoadPicker1Open5 = FALSE; pDY05->oLoadPicker1Close5 = TRUE; }
				if (nNo == 4) { pDY05->oLoadPicker1Open7 = FALSE; pDY05->oLoadPicker1Close7 = TRUE; }
			} else {
				if (nNo == 1) { pDY05->oLoadPicker1Open2 = FALSE; pDY05->oLoadPicker1Close2 = TRUE; }
				if (nNo == 2) { pDY05->oLoadPicker1Open4 = FALSE; pDY05->oLoadPicker1Close4 = TRUE; }
				if (nNo == 3) { pDY05->oLoadPicker1Open6 = FALSE; pDY05->oLoadPicker1Close6 = TRUE; }
				if (nNo == 4) { pDY05->oLoadPicker1Open8 = FALSE; pDY05->oLoadPicker1Close8 = TRUE; }
			}
			g_objAJinAXL.Write_Output(5);
			return;
		}
		if (gData.bMemphis) {
			if (nType ==  0 || nType ==  1) { pDY05->oLoadPicker1Open1 = FALSE; pDY05->oLoadPicker1Close1 = TRUE;
											  pDY05->oLoadPicker1Open3 = FALSE; pDY05->oLoadPicker1Close3 = TRUE; }
			if (nType ==  0 || nType ==  2) { pDY05->oLoadPicker1Open5 = FALSE; pDY05->oLoadPicker1Close5 = TRUE;
											  pDY05->oLoadPicker1Open7 = FALSE; pDY05->oLoadPicker1Close7 = TRUE; }
		} else {
			if (nType ==  0 || nType ==  1) { pDY05->oLoadPicker1Open2 = FALSE; pDY05->oLoadPicker1Close2 = TRUE;
											  pDY05->oLoadPicker1Open4 = FALSE; pDY05->oLoadPicker1Close4 = TRUE; }
			if (nType ==  0 || nType ==  2) { pDY05->oLoadPicker1Open6 = FALSE; pDY05->oLoadPicker1Close6 = TRUE;
											  pDY05->oLoadPicker1Open8 = FALSE; pDY05->oLoadPicker1Close8 = TRUE; }
		}
		g_objAJinAXL.Write_Output(5);
	}
	if (nPickNo ==  2) {
		DY_DATA_06 *pDY06 = g_objAJinAXL.Get_pDY06();
		if (nType == 9) {
			if (nNo == 0 || nNo == 1)	{ pDY06->oLoadPicker2Open1 = FALSE; pDY06->oLoadPicker2Close1 = TRUE; }
			if (nNo == 0 || nNo == 2)	{ pDY06->oLoadPicker2Open2 = FALSE; pDY06->oLoadPicker2Close2 = TRUE; }
			if (nNo == 0 || nNo == 3)	{ pDY06->oLoadPicker2Open3 = FALSE; pDY06->oLoadPicker2Close3 = TRUE; }
			if (nNo == 0 || nNo == 4)	{ pDY06->oLoadPicker2Open4 = FALSE; pDY06->oLoadPicker2Close4 = TRUE; }
			if (nNo == 0 || nNo == 5)	{ pDY06->oLoadPicker2Open5 = FALSE; pDY06->oLoadPicker2Close5 = TRUE; }
			if (nNo == 0 || nNo == 6)	{ pDY06->oLoadPicker2Open6 = FALSE; pDY06->oLoadPicker2Close6 = TRUE; }
			if (nNo == 0 || nNo == 7)	{ pDY06->oLoadPicker2Open7 = FALSE; pDY06->oLoadPicker2Close7 = TRUE; }
			if (nNo == 0 || nNo == 8)	{ pDY06->oLoadPicker2Open8 = FALSE; pDY06->oLoadPicker2Close8 = TRUE; }
			g_objAJinAXL.Write_Output(6);
			return;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo == 1) { pDY06->oLoadPicker2Open1 = FALSE; pDY06->oLoadPicker2Close1 = TRUE; }
				if (nNo == 2) { pDY06->oLoadPicker2Open3 = FALSE; pDY06->oLoadPicker2Close3 = TRUE; }
				if (nNo == 3) { pDY06->oLoadPicker2Open5 = FALSE; pDY06->oLoadPicker2Close5 = TRUE; }
				if (nNo == 4) { pDY06->oLoadPicker2Open7 = FALSE; pDY06->oLoadPicker2Close7 = TRUE; }
			} else {	
				if (nNo == 1) { pDY06->oLoadPicker2Open2 = FALSE; pDY06->oLoadPicker2Close2 = TRUE; }
				if (nNo == 2) { pDY06->oLoadPicker2Open4 = FALSE; pDY06->oLoadPicker2Close4 = TRUE; }
				if (nNo == 3) { pDY06->oLoadPicker2Open6 = FALSE; pDY06->oLoadPicker2Close6 = TRUE; }
				if (nNo == 4) { pDY06->oLoadPicker2Open8 = FALSE; pDY06->oLoadPicker2Close8 = TRUE; }
			}
			g_objAJinAXL.Write_Output(6);
			return;
		}
		if (gData.bMemphis) {
			if (nType ==  0 || nType ==  1) { pDY06->oLoadPicker2Open1 = FALSE; pDY06->oLoadPicker2Close1 = TRUE;
											  pDY06->oLoadPicker2Open3 = FALSE; pDY06->oLoadPicker2Close3 = TRUE; }
			if (nType ==  0 || nType ==  2) { pDY06->oLoadPicker2Open5 = FALSE; pDY06->oLoadPicker2Close5 = TRUE;
											  pDY06->oLoadPicker2Open7 = FALSE; pDY06->oLoadPicker2Close7 = TRUE; }
		} else {	
			if (nType ==  0 || nType ==  1) { pDY06->oLoadPicker2Open2 = FALSE; pDY06->oLoadPicker2Close2 = TRUE;
											  pDY06->oLoadPicker2Open4 = FALSE; pDY06->oLoadPicker2Close4 = TRUE; }
			if (nType ==  0 || nType ==  2) { pDY06->oLoadPicker2Open6 = FALSE; pDY06->oLoadPicker2Close6 = TRUE;
											  pDY06->oLoadPicker2Open8 = FALSE; pDY06->oLoadPicker2Close8 = TRUE; }
		}
		g_objAJinAXL.Write_Output(6);
	}
}

void CCommon::Set_LoadPickerUp(int nPickNo, int nType, int nNo)
{	
	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	if (nPickNo == 0 || nPickNo ==  1) {
		DY_DATA_05 *pDY05 = g_objAJinAXL.Get_pDY05();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY05->oLoadPicker1Up1 = TRUE; pDY05->oLoadPicker1Down1 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY05->oLoadPicker1Up2 = TRUE; pDY05->oLoadPicker1Down2 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY05->oLoadPicker1Up3 = TRUE; pDY05->oLoadPicker1Down3 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY05->oLoadPicker1Up4 = TRUE; pDY05->oLoadPicker1Down4 = FALSE; }
			if (nNo == 0 || nNo ==  5) { pDY05->oLoadPicker1Up5 = TRUE; pDY05->oLoadPicker1Down5 = FALSE; }
			if (nNo == 0 || nNo ==  6) { pDY05->oLoadPicker1Up6 = TRUE; pDY05->oLoadPicker1Down6 = FALSE; }
			if (nNo == 0 || nNo ==  7) { pDY05->oLoadPicker1Up7 = TRUE; pDY05->oLoadPicker1Down7 = FALSE; }
			if (nNo == 0 || nNo ==  8) { pDY05->oLoadPicker1Up8 = TRUE; pDY05->oLoadPicker1Down8 = FALSE; }
		} else {
			if (nNo == 0 || nNo ==  1) { pDY05->oLoadPicker1Up1 = TRUE; pDY05->oLoadPicker1Down1 = FALSE; pDY05->oLoadPicker1Up2 = TRUE; pDY05->oLoadPicker1Down2 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY05->oLoadPicker1Up3 = TRUE; pDY05->oLoadPicker1Down3 = FALSE; pDY05->oLoadPicker1Up4 = TRUE; pDY05->oLoadPicker1Down4 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY05->oLoadPicker1Up5 = TRUE; pDY05->oLoadPicker1Down5 = FALSE; pDY05->oLoadPicker1Up6 = TRUE; pDY05->oLoadPicker1Down6 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY05->oLoadPicker1Up7 = TRUE; pDY05->oLoadPicker1Down7 = FALSE; pDY05->oLoadPicker1Up8 = TRUE; pDY05->oLoadPicker1Down8 = FALSE; }
		}
		g_objAJinAXL.Write_Output(5);
	}
	if (nPickNo == 0 || nPickNo ==  2) {
		DY_DATA_06 *pDY06 = g_objAJinAXL.Get_pDY06();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY06->oLoadPicker2Up1 = TRUE; pDY06->oLoadPicker2Down1 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY06->oLoadPicker2Up2 = TRUE; pDY06->oLoadPicker2Down2 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY06->oLoadPicker2Up3 = TRUE; pDY06->oLoadPicker2Down3 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY06->oLoadPicker2Up4 = TRUE; pDY06->oLoadPicker2Down4 = FALSE; }
			if (nNo == 0 || nNo ==  5) { pDY06->oLoadPicker2Up5 = TRUE; pDY06->oLoadPicker2Down5 = FALSE; }
			if (nNo == 0 || nNo ==  6) { pDY06->oLoadPicker2Up6 = TRUE; pDY06->oLoadPicker2Down6 = FALSE; }
			if (nNo == 0 || nNo ==  7) { pDY06->oLoadPicker2Up7 = TRUE; pDY06->oLoadPicker2Down7 = FALSE; }
			if (nNo == 0 || nNo ==  8) { pDY06->oLoadPicker2Up8 = TRUE; pDY06->oLoadPicker2Down8 = FALSE; }
		} else {					
			if (nNo == 0 || nNo ==  1) { pDY06->oLoadPicker2Up1 = TRUE; pDY06->oLoadPicker2Down1 = FALSE; pDY06->oLoadPicker2Up2 = TRUE; pDY06->oLoadPicker2Down2 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY06->oLoadPicker2Up3 = TRUE; pDY06->oLoadPicker2Down3 = FALSE; pDY06->oLoadPicker2Up4 = TRUE; pDY06->oLoadPicker2Down4 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY06->oLoadPicker2Up5 = TRUE; pDY06->oLoadPicker2Down5 = FALSE; pDY06->oLoadPicker2Up6 = TRUE; pDY06->oLoadPicker2Down6 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY06->oLoadPicker2Up7 = TRUE; pDY06->oLoadPicker2Down7 = FALSE; pDY06->oLoadPicker2Up8 = TRUE; pDY06->oLoadPicker2Down8 = FALSE; }
		}
		g_objAJinAXL.Write_Output(6);
	}
}

void CCommon::Set_LoadPickerDown(int nPickNo, int nType, int nNo)
{	
	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	if (nPickNo ==  1) {
		DY_DATA_05 *pDY05 = g_objAJinAXL.Get_pDY05();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1)	{ pDY05->oLoadPicker1Up1 = FALSE; pDY05->oLoadPicker1Down1 = TRUE; }
			if (nNo == 0 || nNo ==  2)	{ pDY05->oLoadPicker1Up2 = FALSE; pDY05->oLoadPicker1Down2 = TRUE; }
			if (nNo == 0 || nNo ==  3)	{ pDY05->oLoadPicker1Up3 = FALSE; pDY05->oLoadPicker1Down3 = TRUE; }
			if (nNo == 0 || nNo ==  4)	{ pDY05->oLoadPicker1Up4 = FALSE; pDY05->oLoadPicker1Down4 = TRUE; }
			if (nNo == 0 || nNo ==  5)	{ pDY05->oLoadPicker1Up5 = FALSE; pDY05->oLoadPicker1Down5 = TRUE; }
			if (nNo == 0 || nNo ==  6)	{ pDY05->oLoadPicker1Up6 = FALSE; pDY05->oLoadPicker1Down6 = TRUE; }
			if (nNo == 0 || nNo ==  7)	{ pDY05->oLoadPicker1Up7 = FALSE; pDY05->oLoadPicker1Down7 = TRUE; }
			if (nNo == 0 || nNo ==  8)	{ pDY05->oLoadPicker1Up8 = FALSE; pDY05->oLoadPicker1Down8 = TRUE; }
			g_objAJinAXL.Write_Output(5);
			return;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo ==  1) { pDY05->oLoadPicker1Up1 = FALSE; pDY05->oLoadPicker1Down1 = TRUE; }
				if (nNo ==  2) { pDY05->oLoadPicker1Up3 = FALSE; pDY05->oLoadPicker1Down3 = TRUE; }
				if (nNo ==  3) { pDY05->oLoadPicker1Up5 = FALSE; pDY05->oLoadPicker1Down5 = TRUE; }
				if (nNo ==  4) { pDY05->oLoadPicker1Up7 = FALSE; pDY05->oLoadPicker1Down7 = TRUE; }
			} else {	
				if (nNo ==  1) { pDY05->oLoadPicker1Up2 = FALSE; pDY05->oLoadPicker1Down2 = TRUE; }
				if (nNo ==  2) { pDY05->oLoadPicker1Up4 = FALSE; pDY05->oLoadPicker1Down4 = TRUE; }
				if (nNo ==  3) { pDY05->oLoadPicker1Up6 = FALSE; pDY05->oLoadPicker1Down6 = TRUE; }
				if (nNo ==  4) { pDY05->oLoadPicker1Up8 = FALSE; pDY05->oLoadPicker1Down8 = TRUE; }
			}
			g_objAJinAXL.Write_Output(5);
			return;
		}
		if (gData.bMemphis) {
			if (nType ==  0 || nType ==  1) { pDY05->oLoadPicker1Up1 = FALSE; pDY05->oLoadPicker1Down1 = TRUE;
											  pDY05->oLoadPicker1Up3 = FALSE; pDY05->oLoadPicker1Down3 = TRUE; }
			if (nType ==  0 || nType ==  2) { pDY05->oLoadPicker1Up5 = FALSE; pDY05->oLoadPicker1Down5 = TRUE;
											  pDY05->oLoadPicker1Up7 = FALSE; pDY05->oLoadPicker1Down7 = TRUE; }
		} else {	
			if (nType ==  0 || nType ==  1) { pDY05->oLoadPicker1Up2 = FALSE; pDY05->oLoadPicker1Down2 = TRUE;
											  pDY05->oLoadPicker1Up4 = FALSE; pDY05->oLoadPicker1Down4 = TRUE; }
			if (nType ==  0 || nType ==  2) { pDY05->oLoadPicker1Up6 = FALSE; pDY05->oLoadPicker1Down6 = TRUE;
											  pDY05->oLoadPicker1Up8 = FALSE; pDY05->oLoadPicker1Down8 = TRUE; }
		}
		g_objAJinAXL.Write_Output(5);
	}
	if (nPickNo ==  2) {
		DY_DATA_06 *pDY06 = g_objAJinAXL.Get_pDY06();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1)	{ pDY06->oLoadPicker2Up1 = FALSE; pDY06->oLoadPicker2Down1 = TRUE; }
			if (nNo == 0 || nNo ==  2)	{ pDY06->oLoadPicker2Up2 = FALSE; pDY06->oLoadPicker2Down2 = TRUE; }
			if (nNo == 0 || nNo ==  3)	{ pDY06->oLoadPicker2Up3 = FALSE; pDY06->oLoadPicker2Down3 = TRUE; }
			if (nNo == 0 || nNo ==  4)	{ pDY06->oLoadPicker2Up4 = FALSE; pDY06->oLoadPicker2Down4 = TRUE; }
			if (nNo == 0 || nNo ==  5)	{ pDY06->oLoadPicker2Up5 = FALSE; pDY06->oLoadPicker2Down5 = TRUE; }
			if (nNo == 0 || nNo ==  6)	{ pDY06->oLoadPicker2Up6 = FALSE; pDY06->oLoadPicker2Down6 = TRUE; }
			if (nNo == 0 || nNo ==  7)	{ pDY06->oLoadPicker2Up7 = FALSE; pDY06->oLoadPicker2Down7 = TRUE; }
			if (nNo == 0 || nNo ==  8)	{ pDY06->oLoadPicker2Up8 = FALSE; pDY06->oLoadPicker2Down8 = TRUE; }
			g_objAJinAXL.Write_Output(6);
			return;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo ==  1) { pDY06->oLoadPicker2Up1 = FALSE; pDY06->oLoadPicker2Down1 = TRUE; }
				if (nNo ==  2) { pDY06->oLoadPicker2Up3 = FALSE; pDY06->oLoadPicker2Down3 = TRUE; }
				if (nNo ==  3) { pDY06->oLoadPicker2Up5 = FALSE; pDY06->oLoadPicker2Down5 = TRUE; }
				if (nNo ==  4) { pDY06->oLoadPicker2Up7 = FALSE; pDY06->oLoadPicker2Down7 = TRUE; }
			} else {	
				if (nNo ==  1) { pDY06->oLoadPicker2Up2 = FALSE; pDY06->oLoadPicker2Down2 = TRUE; }
				if (nNo ==  2) { pDY06->oLoadPicker2Up4 = FALSE; pDY06->oLoadPicker2Down4 = TRUE; }
				if (nNo ==  3) { pDY06->oLoadPicker2Up6 = FALSE; pDY06->oLoadPicker2Down6 = TRUE; }
				if (nNo ==  4) { pDY06->oLoadPicker2Up8 = FALSE; pDY06->oLoadPicker2Down8 = TRUE; }
			}
			g_objAJinAXL.Write_Output(6);
			return;
		}
		if (gData.bMemphis) {
			if (nType ==  0 || nType ==  1) { pDY06->oLoadPicker2Up1 = FALSE; pDY06->oLoadPicker2Down1 = TRUE;
											  pDY06->oLoadPicker2Up3 = FALSE; pDY06->oLoadPicker2Down3 = TRUE; }
			if (nType ==  0 || nType ==  2) { pDY06->oLoadPicker2Up5 = FALSE; pDY06->oLoadPicker2Down5 = TRUE;
											  pDY06->oLoadPicker2Up7 = FALSE; pDY06->oLoadPicker2Down7 = TRUE; }
		} else {	
			if (nType ==  0 || nType ==  1) { pDY06->oLoadPicker2Up2 = FALSE; pDY06->oLoadPicker2Down2 = TRUE;
											  pDY06->oLoadPicker2Up4 = FALSE; pDY06->oLoadPicker2Down4 = TRUE; }
			if (nType ==  0 || nType ==  2) { pDY06->oLoadPicker2Up6 = FALSE; pDY06->oLoadPicker2Down6 = TRUE;
											  pDY06->oLoadPicker2Up8 = FALSE; pDY06->oLoadPicker2Down8 = TRUE; }
		}
		g_objAJinAXL.Write_Output(6);
	}
}

BOOL CCommon::Get_LoadPickerOpen(int nPickNo, int nType, int nNo)
{	
	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	if (nPickNo ==  1) {
		for(int i=0; i<8; i++) gData.nLoadPicker1ErrNo[i] = 0;
		DX_DATA_05 *pDX05 = g_objAJinAXL.Get_pDX05();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1)	{ if (!pDX05->iLoadPicker1Open1) return FALSE; }
			if (nNo == 0 || nNo ==  2)	{ if (!pDX05->iLoadPicker1Open2) return FALSE; }
			if (nNo == 0 || nNo ==  3)	{ if (!pDX05->iLoadPicker1Open3) return FALSE; }
			if (nNo == 0 || nNo ==  4)	{ if (!pDX05->iLoadPicker1Open4) return FALSE; }
			if (nNo == 0 || nNo ==  5)	{ if (!pDX05->iLoadPicker1Open5) return FALSE; }
			if (nNo == 0 || nNo ==  6)	{ if (!pDX05->iLoadPicker1Open6) return FALSE; }
			if (nNo == 0 || nNo ==  7)	{ if (!pDX05->iLoadPicker1Open7) return FALSE; }
			if (nNo == 0 || nNo ==  8)	{ if (!pDX05->iLoadPicker1Open8) return FALSE; }
			return TRUE;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo ==  1) { if (!pDX05->iLoadPicker1Open1) return FALSE; }
				if (nNo ==  2) { if (!pDX05->iLoadPicker1Open3) return FALSE; }
				if (nNo ==  3) { if (!pDX05->iLoadPicker1Open5) return FALSE; }
				if (nNo ==  4) { if (!pDX05->iLoadPicker1Open7) return FALSE; }
			} else {	
				if (nNo ==  1) { if (!pDX05->iLoadPicker1Open2) return FALSE; } 
				if (nNo ==  2) { if (!pDX05->iLoadPicker1Open4) return FALSE; }
				if (nNo ==  3) { if (!pDX05->iLoadPicker1Open6) return FALSE; } 
				if (nNo ==  4) { if (!pDX05->iLoadPicker1Open8) return FALSE; }
			}
			return TRUE;
		}
		if (gData.bMemphis) {
			if (nType == 0 || nType ==  1) { if (!pDX05->iLoadPicker1Open1) return FALSE; }
			if (nType == 0 || nType ==  1) { if (!pDX05->iLoadPicker1Open3) return FALSE; }
			if (nType == 0 || nType ==  2) { if (!pDX05->iLoadPicker1Open5) return FALSE; }
			if (nType == 0 || nType ==  2) { if (!pDX05->iLoadPicker1Open7) return FALSE; }
		} else {	
			if (nType == 0 || nType ==  1) { if (!pDX05->iLoadPicker1Open2) return FALSE; } 
			if (nType == 0 || nType ==  1) { if (!pDX05->iLoadPicker1Open4) return FALSE; }
			if (nType == 0 || nType ==  2) { if (!pDX05->iLoadPicker1Open6) return FALSE; } 
			if (nType == 0 || nType ==  2) { if (!pDX05->iLoadPicker1Open8) return FALSE; }
		}
	}
	if (nPickNo ==  2) {
		for(int i=0; i<8; i++) gData.nLoadPicker2ErrNo[i] = 0;
		DX_DATA_06 *pDX06 = g_objAJinAXL.Get_pDX06();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1)	{ if (!pDX06->iLoadPicker2Open1) return FALSE; }
			if (nNo == 0 || nNo ==  2)	{ if (!pDX06->iLoadPicker2Open2) return FALSE; }
			if (nNo == 0 || nNo ==  3)	{ if (!pDX06->iLoadPicker2Open3) return FALSE; }
			if (nNo == 0 || nNo ==  4)	{ if (!pDX06->iLoadPicker2Open4) return FALSE; }
			if (nNo == 0 || nNo ==  5)	{ if (!pDX06->iLoadPicker2Open5) return FALSE; }
			if (nNo == 0 || nNo ==  6)	{ if (!pDX06->iLoadPicker2Open6) return FALSE; }
			if (nNo == 0 || nNo ==  7)	{ if (!pDX06->iLoadPicker2Open7) return FALSE; }
			if (nNo == 0 || nNo ==  8)	{ if (!pDX06->iLoadPicker2Open8) return FALSE; }
			return TRUE;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo ==  1) { if (!pDX06->iLoadPicker2Open1) return FALSE; }
				if (nNo ==  2) { if (!pDX06->iLoadPicker2Open3) return FALSE; }
				if (nNo ==  3) { if (!pDX06->iLoadPicker2Open5) return FALSE; } 
				if (nNo ==  4) { if (!pDX06->iLoadPicker2Open7) return FALSE; }
			} else {	
				if (nNo ==  1) { if (!pDX06->iLoadPicker2Open2) return FALSE; } 
				if (nNo ==  2) { if (!pDX06->iLoadPicker2Open4) return FALSE; }
				if (nNo ==  3) { if (!pDX06->iLoadPicker2Open6) return FALSE; } 
				if (nNo ==  4) { if (!pDX06->iLoadPicker2Open8) return FALSE; }
			}
			return TRUE;
		}
		if (gData.bMemphis) {
			if (nType == 0 || nType ==  1) { if (!pDX06->iLoadPicker2Open1) return FALSE; }
			if (nType == 0 || nType ==  1) { if (!pDX06->iLoadPicker2Open3) return FALSE; }
			if (nType == 0 || nType ==  2) { if (!pDX06->iLoadPicker2Open5) return FALSE; } 
			if (nType == 0 || nType ==  2) { if (!pDX06->iLoadPicker2Open7) return FALSE; }
		} else {	
			if (nType == 0 || nType ==  1) { if (!pDX06->iLoadPicker2Open2) return FALSE; } 
			if (nType == 0 || nType ==  1) { if (!pDX06->iLoadPicker2Open4) return FALSE; }
			if (nType == 0 || nType ==  2) { if (!pDX06->iLoadPicker2Open6) return FALSE; } 
			if (nType == 0 || nType ==  2) { if (!pDX06->iLoadPicker2Open8) return FALSE; }
		}
	}
	return TRUE;
}

BOOL CCommon::Get_LoadPickerClose(int nPickNo, int nType, int nNo)
{	
	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	int nRet = TRUE;
	if (nPickNo ==  1) {
		for(int i=0; i<8; i++) gData.nLoadPicker1ErrNo[i] = 0;
		DX_DATA_05 *pDX05 = g_objAJinAXL.Get_pDX05();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1)	{ if (pDX05->iLoadPicker1Open1) { gData.nLoadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  2)	{ if (pDX05->iLoadPicker1Open2) { gData.nLoadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  3)	{ if (pDX05->iLoadPicker1Open3) { gData.nLoadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  4)	{ if (pDX05->iLoadPicker1Open4) { gData.nLoadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  5)	{ if (pDX05->iLoadPicker1Open5) { gData.nLoadPicker1ErrNo[4] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  6)	{ if (pDX05->iLoadPicker1Open6) { gData.nLoadPicker1ErrNo[5] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  7)	{ if (pDX05->iLoadPicker1Open7) { gData.nLoadPicker1ErrNo[6] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  8)	{ if (pDX05->iLoadPicker1Open8) { gData.nLoadPicker1ErrNo[7] = 1; nRet =  FALSE; }}
			return nRet;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo ==  1) { if (pDX05->iLoadPicker1Open1) { gData.nLoadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
				if (nNo ==  2) { if (pDX05->iLoadPicker1Open3) { gData.nLoadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
				if (nNo ==  3) { if (pDX05->iLoadPicker1Open5) { gData.nLoadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
				if (nNo ==  4) { if (pDX05->iLoadPicker1Open7) { gData.nLoadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
			} else {	
				if (nNo ==  1) { if (pDX05->iLoadPicker1Open2) { gData.nLoadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
				if (nNo ==  2) { if (pDX05->iLoadPicker1Open4) { gData.nLoadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
				if (nNo ==  3) { if (pDX05->iLoadPicker1Open6) { gData.nLoadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
				if (nNo ==  4) { if (pDX05->iLoadPicker1Open8) { gData.nLoadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
			}
			return nRet;
		}
		if (gData.bMemphis) {
			if (nType == 0 || nType ==  1) { if (pDX05->iLoadPicker1Open1) { gData.nLoadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  1) { if (pDX05->iLoadPicker1Open3) { gData.nLoadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  2) { if (pDX05->iLoadPicker1Open5) { gData.nLoadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  2) { if (pDX05->iLoadPicker1Open7) { gData.nLoadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
		} else {	
			if (nType == 0 || nType ==  1) { if (pDX05->iLoadPicker1Open2) { gData.nLoadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  1) { if (pDX05->iLoadPicker1Open4) { gData.nLoadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  2) { if (pDX05->iLoadPicker1Open6) { gData.nLoadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  2) { if (pDX05->iLoadPicker1Open8) { gData.nLoadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
		}
	}
	if (nPickNo ==  2) {
		for(int i=0; i<8; i++) gData.nLoadPicker2ErrNo[i] = 0;
		DX_DATA_06 *pDX06 = g_objAJinAXL.Get_pDX06();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1)	{ if (pDX06->iLoadPicker2Open1) { gData.nLoadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  2)	{ if (pDX06->iLoadPicker2Open2) { gData.nLoadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  3)	{ if (pDX06->iLoadPicker2Open3) { gData.nLoadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  4)	{ if (pDX06->iLoadPicker2Open4) { gData.nLoadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  5)	{ if (pDX06->iLoadPicker2Open5) { gData.nLoadPicker2ErrNo[4] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  6)	{ if (pDX06->iLoadPicker2Open6) { gData.nLoadPicker2ErrNo[5] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  7)	{ if (pDX06->iLoadPicker2Open7) { gData.nLoadPicker2ErrNo[6] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo ==  8)	{ if (pDX06->iLoadPicker2Open8) { gData.nLoadPicker2ErrNo[7] = 1; nRet =  FALSE; }}
			return nRet;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo ==  1) { if (pDX06->iLoadPicker2Open1) { gData.nLoadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
				if (nNo ==  2) { if (pDX06->iLoadPicker2Open3) { gData.nLoadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
				if (nNo ==  3) { if (pDX06->iLoadPicker2Open5) { gData.nLoadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
				if (nNo ==  4) { if (pDX06->iLoadPicker2Open7) { gData.nLoadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
			} else {	
				if (nNo ==  1) { if (pDX06->iLoadPicker2Open2) { gData.nLoadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
				if (nNo ==  2) { if (pDX06->iLoadPicker2Open4) { gData.nLoadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
				if (nNo ==  3) { if (pDX06->iLoadPicker2Open6) { gData.nLoadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
				if (nNo ==  4) { if (pDX06->iLoadPicker2Open8) { gData.nLoadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
			}
			return nRet;
		}
		if (gData.bMemphis) {
			if (nType == 0 || nType ==  1) { if (pDX06->iLoadPicker2Open1) { gData.nLoadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  1) { if (pDX06->iLoadPicker2Open3) { gData.nLoadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  2) { if (pDX06->iLoadPicker2Open5) { gData.nLoadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  2) { if (pDX06->iLoadPicker2Open7) { gData.nLoadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
		} else {	
			if (nType == 0 || nType ==  1) { if (pDX06->iLoadPicker2Open2) { gData.nLoadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  1) { if (pDX06->iLoadPicker2Open4) { gData.nLoadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  2) { if (pDX06->iLoadPicker2Open6) { gData.nLoadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
			if (nType == 0 || nType ==  2) { if (pDX06->iLoadPicker2Open8) { gData.nLoadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
		}
	}
	return nRet;
}

BOOL CCommon::Get_LoadPickerUp(int nPickNo)
{	
	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	if (nPickNo == 0 || nPickNo ==  1) {
		for(int i=0; i<8; i++) gData.nLoadPicker1ErrNo[i] = 0;
		DX_DATA_05 *pDX05 = g_objAJinAXL.Get_pDX05();
		if (!pDX05->iLoadPicker1Up1 || pDX05->iLoadPicker1Down1) return FALSE; 
		if (!pDX05->iLoadPicker1Up2 || pDX05->iLoadPicker1Down2) return FALSE; 
		if (!pDX05->iLoadPicker1Up3 || pDX05->iLoadPicker1Down3) return FALSE; 
		if (!pDX05->iLoadPicker1Up4 || pDX05->iLoadPicker1Down4) return FALSE; 
		if (!pDX05->iLoadPicker1Up5 || pDX05->iLoadPicker1Down5) return FALSE; 
		if (!pDX05->iLoadPicker1Up6 || pDX05->iLoadPicker1Down6) return FALSE; 
		if (!pDX05->iLoadPicker1Up7 || pDX05->iLoadPicker1Down7) return FALSE; 
		if (!pDX05->iLoadPicker1Up8 || pDX05->iLoadPicker1Down8) return FALSE; 
	}
	if (nPickNo == 0 || nPickNo ==  2) {
		for(int i=0; i<8; i++) gData.nLoadPicker2ErrNo[i] = 0;
		DX_DATA_06 *pDX06 = g_objAJinAXL.Get_pDX06();
		if (!pDX06->iLoadPicker2Up1 || pDX06->iLoadPicker2Down1) return FALSE; 
		if (!pDX06->iLoadPicker2Up2 || pDX06->iLoadPicker2Down2) return FALSE; 
		if (!pDX06->iLoadPicker2Up3 || pDX06->iLoadPicker2Down3) return FALSE; 
		if (!pDX06->iLoadPicker2Up4 || pDX06->iLoadPicker2Down4) return FALSE; 
		if (!pDX06->iLoadPicker2Up5 || pDX06->iLoadPicker2Down5) return FALSE; 
		if (!pDX06->iLoadPicker2Up6 || pDX06->iLoadPicker2Down6) return FALSE; 
		if (!pDX06->iLoadPicker2Up7 || pDX06->iLoadPicker2Down7) return FALSE; 
		if (!pDX06->iLoadPicker2Up8 || pDX06->iLoadPicker2Down8) return FALSE; 
	}
	return TRUE;
}

BOOL CCommon::Get_LoadPickerDown(int nPickNo, int nType, int nNo)
{	
	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	if (nPickNo ==  1) {
		for(int i=0; i<8; i++) gData.nLoadPicker1ErrNo[i] = 0;
		DX_DATA_05 *pDX05 = g_objAJinAXL.Get_pDX05();
		if (nType == 9) {
			if (nNo == 1) { if (pDX05->iLoadPicker1Up1 || !pDX05->iLoadPicker1Down1) return FALSE; }
			if (nNo == 2) { if (pDX05->iLoadPicker1Up2 || !pDX05->iLoadPicker1Down2) return FALSE; }
			if (nNo == 3) { if (pDX05->iLoadPicker1Up3 || !pDX05->iLoadPicker1Down3) return FALSE; }
			if (nNo == 4) { if (pDX05->iLoadPicker1Up4 || !pDX05->iLoadPicker1Down4) return FALSE; }
			if (nNo == 5) { if (pDX05->iLoadPicker1Up5 || !pDX05->iLoadPicker1Down5) return FALSE; }
			if (nNo == 6) { if (pDX05->iLoadPicker1Up6 || !pDX05->iLoadPicker1Down6) return FALSE; }
			if (nNo == 7) { if (pDX05->iLoadPicker1Up7 || !pDX05->iLoadPicker1Down7) return FALSE; }
			if (nNo == 8) { if (pDX05->iLoadPicker1Up8 || !pDX05->iLoadPicker1Down8) return FALSE; }
			return TRUE;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo == 1) { if (pDX05->iLoadPicker1Up1 || !pDX05->iLoadPicker1Down1) return FALSE; }
				if (nNo == 2) { if (pDX05->iLoadPicker1Up3 || !pDX05->iLoadPicker1Down3) return FALSE; }
				if (nNo == 3) { if (pDX05->iLoadPicker1Up5 || !pDX05->iLoadPicker1Down5) return FALSE; }
				if (nNo == 4) { if (pDX05->iLoadPicker1Up7 || !pDX05->iLoadPicker1Down7) return FALSE; }
			} else {
				if (nNo == 1) { if (pDX05->iLoadPicker1Up2 || !pDX05->iLoadPicker1Down2) return FALSE; }
				if (nNo == 2) { if (pDX05->iLoadPicker1Up4 || !pDX05->iLoadPicker1Down4) return FALSE; }
				if (nNo == 3) { if (pDX05->iLoadPicker1Up6 || !pDX05->iLoadPicker1Down6) return FALSE; }
				if (nNo == 4) { if (pDX05->iLoadPicker1Up8 || !pDX05->iLoadPicker1Down8) return FALSE; }
			}
			return TRUE;
		}
		if (gData.bMemphis) {
			if (nType == 0 || nType ==  1) { if (pDX05->iLoadPicker1Up1 || !pDX05->iLoadPicker1Down1) return FALSE; }
			if (nType == 0 || nType ==  1) { if (pDX05->iLoadPicker1Up3 || !pDX05->iLoadPicker1Down3) return FALSE; }
			if (nType == 0 || nType ==  2) { if (pDX05->iLoadPicker1Up5 || !pDX05->iLoadPicker1Down5) return FALSE; }
			if (nType == 0 || nType ==  2) { if (pDX05->iLoadPicker1Up7 || !pDX05->iLoadPicker1Down7) return FALSE; }
		} else {
			if (nType == 0 || nType ==  1) { if (pDX05->iLoadPicker1Up2 || !pDX05->iLoadPicker1Down2) return FALSE; }
			if (nType == 0 || nType ==  1) { if (pDX05->iLoadPicker1Up4 || !pDX05->iLoadPicker1Down4) return FALSE; }
			if (nType == 0 || nType ==  2) { if (pDX05->iLoadPicker1Up6 || !pDX05->iLoadPicker1Down6) return FALSE; }
			if (nType == 0 || nType ==  2) { if (pDX05->iLoadPicker1Up8 || !pDX05->iLoadPicker1Down8) return FALSE; }
		}
	}
	if (nPickNo ==  2) {
		for(int i=0; i<8; i++) gData.nLoadPicker2ErrNo[i] = 0;
		DX_DATA_06 *pDX06 = g_objAJinAXL.Get_pDX06();
		if (nType == 9) {
			if (nNo == 1) { if (pDX06->iLoadPicker2Up1 || !pDX06->iLoadPicker2Down1) return FALSE; }
			if (nNo == 2) { if (pDX06->iLoadPicker2Up2 || !pDX06->iLoadPicker2Down2) return FALSE; }
			if (nNo == 3) { if (pDX06->iLoadPicker2Up3 || !pDX06->iLoadPicker2Down3) return FALSE; }
			if (nNo == 4) { if (pDX06->iLoadPicker2Up4 || !pDX06->iLoadPicker2Down4) return FALSE; }
			if (nNo == 5) { if (pDX06->iLoadPicker2Up5 || !pDX06->iLoadPicker2Down5) return FALSE; }
			if (nNo == 6) { if (pDX06->iLoadPicker2Up6 || !pDX06->iLoadPicker2Down6) return FALSE; }
			if (nNo == 7) { if (pDX06->iLoadPicker2Up7 || !pDX06->iLoadPicker2Down7) return FALSE; }
			if (nNo == 8) { if (pDX06->iLoadPicker2Up8 || !pDX06->iLoadPicker2Down8) return FALSE; }
			return TRUE;
		}
		if (nType == 8) {
			if (gData.bMemphis) {
				if (nNo == 1) { if (pDX06->iLoadPicker2Up1 || !pDX06->iLoadPicker2Down1) return FALSE; }
				if (nNo == 2) { if (pDX06->iLoadPicker2Up3 || !pDX06->iLoadPicker2Down3) return FALSE; }
				if (nNo == 3) { if (pDX06->iLoadPicker2Up5 || !pDX06->iLoadPicker2Down5) return FALSE; }
				if (nNo == 4) { if (pDX06->iLoadPicker2Up7 || !pDX06->iLoadPicker2Down7) return FALSE; }
			} else {
				if (nNo == 1) { if (pDX06->iLoadPicker2Up2 || !pDX06->iLoadPicker2Down2) return FALSE; }
				if (nNo == 2) { if (pDX06->iLoadPicker2Up4 || !pDX06->iLoadPicker2Down4) return FALSE; }
				if (nNo == 3) { if (pDX06->iLoadPicker2Up6 || !pDX06->iLoadPicker2Down6) return FALSE; }
				if (nNo == 4) { if (pDX06->iLoadPicker2Up8 || !pDX06->iLoadPicker2Down8) return FALSE; }
			}
			return TRUE;
		}
		if (gData.bMemphis) {
			if (nType == 0 || nType ==  1) { if (pDX06->iLoadPicker2Up1 || !pDX06->iLoadPicker2Down1) return FALSE; }
			if (nType == 0 || nType ==  1) { if (pDX06->iLoadPicker2Up3 || !pDX06->iLoadPicker2Down3) return FALSE; }
			if (nType == 0 || nType ==  2) { if (pDX06->iLoadPicker2Up5 || !pDX06->iLoadPicker2Down5) return FALSE; }
			if (nType == 0 || nType ==  2) { if (pDX06->iLoadPicker2Up7 || !pDX06->iLoadPicker2Down7) return FALSE; }
		} else {
			if (nType == 0 || nType ==  1) { if (pDX06->iLoadPicker2Up2 || !pDX06->iLoadPicker2Down2) return FALSE; }
			if (nType == 0 || nType ==  1) { if (pDX06->iLoadPicker2Up4 || !pDX06->iLoadPicker2Down4) return FALSE; }
			if (nType == 0 || nType ==  2) { if (pDX06->iLoadPicker2Up6 || !pDX06->iLoadPicker2Down6) return FALSE; }
			if (nType == 0 || nType ==  2) { if (pDX06->iLoadPicker2Up8 || !pDX06->iLoadPicker2Down8) return FALSE; }
		}
	}
	return TRUE;
}

BOOL CCommon::Get_LoadPickerCheck(int nPickNo, int nType, int nNo, int *nCMInfo)
{	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (gData.bUseDryRun || pEquipData->bUseCMCheck == FALSE) return TRUE;

	int nInfo[8] = {0,};
	if (nCMInfo == NULL) nCMInfo = nInfo;

	int nRet = TRUE;
	if (nPickNo ==  1) {
		for(int i=0; i<8; i++) gData.nLoadPicker1ErrNo[i] = 0;
		DX_DATA_05 *pDX05 = g_objAJinAXL.Get_pDX05();
		if (nType == 9) {
			if (gData.bMemphis) {
				if (nNo == 1 || nCMInfo[0] > 0)	{ if (!pDX05->iLoadPicker1Exist1) { gData.nLoadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
				if (nNo == 2 || nCMInfo[1] > 0)	{ if (!pDX05->iLoadPicker1Exist3) { gData.nLoadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
				if (nNo == 3 || nCMInfo[2] > 0)	{ if (!pDX05->iLoadPicker1Exist5) { gData.nLoadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
				if (nNo == 4 || nCMInfo[3] > 0)	{ if (!pDX05->iLoadPicker1Exist7) { gData.nLoadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
			} else {
				if (nNo == 1 || nCMInfo[0] > 0)	{ if (!pDX05->iLoadPicker1Exist2) { gData.nLoadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
				if (nNo == 2 || nCMInfo[1] > 0)	{ if (!pDX05->iLoadPicker1Exist4) { gData.nLoadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
				if (nNo == 3 || nCMInfo[2] > 0)	{ if (!pDX05->iLoadPicker1Exist6) { gData.nLoadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
				if (nNo == 4 || nCMInfo[3] > 0)	{ if (!pDX05->iLoadPicker1Exist8) { gData.nLoadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
			}
		}
	}
	if (nPickNo ==  2) {
		for(int i=0; i<8; i++) gData.nLoadPicker2ErrNo[i] = 0;
		DX_DATA_06 *pDX06 = g_objAJinAXL.Get_pDX06();
		if (nType == 9) {
			if (gData.bMemphis) {
				if (nNo == 1 || nCMInfo[0] > 0)	{ if (!pDX06->iLoadPicker2Exist1) { gData.nLoadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
				if (nNo == 2 || nCMInfo[1] > 0)	{ if (!pDX06->iLoadPicker2Exist3) { gData.nLoadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
				if (nNo == 3 || nCMInfo[2] > 0)	{ if (!pDX06->iLoadPicker2Exist5) { gData.nLoadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
				if (nNo == 4 || nCMInfo[3] > 0)	{ if (!pDX06->iLoadPicker2Exist7) { gData.nLoadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
			} else {
				if (nNo == 1 || nCMInfo[0] > 0)	{ if (!pDX06->iLoadPicker2Exist2) { gData.nLoadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
				if (nNo == 2 || nCMInfo[1] > 0)	{ if (!pDX06->iLoadPicker2Exist4) { gData.nLoadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
				if (nNo == 3 || nCMInfo[2] > 0)	{ if (!pDX06->iLoadPicker2Exist6) { gData.nLoadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
				if (nNo == 4 || nCMInfo[3] > 0)	{ if (!pDX06->iLoadPicker2Exist8) { gData.nLoadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
			}
		}
	}
	return nRet;
}

///////////////////////////////////////////////////////////////////////////////
void CCommon::Set_VisionVacuumOn(int nVisionNo, int nType, int nNo)
{	//nVisionNo(1,2,3,4) nNo(0,1~8,9)
	if (nVisionNo == 1) {
		DY_DATA_07 *pDY07 = g_objAJinAXL.Get_pDY07();
		if (nType == 9) {
				if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage1Vac1On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage1Vac2On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage1Vac3On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage1Vac4On = TRUE; }
				if (nNo == 0 || nNo == 5)	{ pDY07->oInspectStage1Vac5On = TRUE; }
				if (nNo == 0 || nNo == 6)	{ pDY07->oInspectStage1Vac6On = TRUE; }
				if (nNo == 0 || nNo == 7)	{ pDY07->oInspectStage1Vac7On = TRUE; }
				if (nNo == 0 || nNo == 8)	{ pDY07->oInspectStage1Vac8On = TRUE; }
		} else {
			if (gData.bMemphis) {
				if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage1Vac1On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage1Vac3On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage1Vac5On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage1Vac7On = TRUE; }
			} else {
				if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage1Vac2On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage1Vac4On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage1Vac6On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage1Vac8On = TRUE; }
			}
		}
		g_objAJinAXL.Write_Output(7);
	}
	if (nVisionNo == 2) {
		DY_DATA_07 *pDY07 = g_objAJinAXL.Get_pDY07();
		if (nType == 9) {
				if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage2Vac1On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage2Vac2On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage2Vac3On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage2Vac4On = TRUE; }
				if (nNo == 0 || nNo == 5)	{ pDY07->oInspectStage2Vac5On = TRUE; }
				if (nNo == 0 || nNo == 6)	{ pDY07->oInspectStage2Vac6On = TRUE; }
				if (nNo == 0 || nNo == 7)	{ pDY07->oInspectStage2Vac7On = TRUE; }
				if (nNo == 0 || nNo == 8)	{ pDY07->oInspectStage2Vac8On = TRUE; }
		} else {
			if (gData.bMemphis) {
				if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage2Vac1On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage2Vac3On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage2Vac5On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage2Vac7On = TRUE; }
			} else {
				if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage2Vac2On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage2Vac4On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage2Vac6On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage2Vac8On = TRUE; }
			}
		}
		g_objAJinAXL.Write_Output(7);
	}
	if (nVisionNo == 3) {
		DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();
		if (nType == 9) {
				if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage3Vac1On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage3Vac2On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage3Vac3On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage3Vac4On = TRUE; }
				if (nNo == 0 || nNo == 5)	{ pDY08->oInspectStage3Vac5On = TRUE; }
				if (nNo == 0 || nNo == 6)	{ pDY08->oInspectStage3Vac6On = TRUE; }
				if (nNo == 0 || nNo == 7)	{ pDY08->oInspectStage3Vac7On = TRUE; }
				if (nNo == 0 || nNo == 8)	{ pDY08->oInspectStage3Vac8On = TRUE; }
		} else {
			if (gData.bMemphis) {
				if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage3Vac1On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage3Vac3On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage3Vac5On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage3Vac7On = TRUE; }
			} else {
				if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage3Vac2On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage3Vac4On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage3Vac6On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage3Vac8On = TRUE; }
			}
		}
		g_objAJinAXL.Write_Output(8);
	}
	if (nVisionNo == 4) {
		DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();
		if (nType == 9) {
				if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage4Vac1On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage4Vac2On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage4Vac3On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage4Vac4On = TRUE; }
				if (nNo == 0 || nNo == 5)	{ pDY08->oInspectStage4Vac5On = TRUE; }
				if (nNo == 0 || nNo == 6)	{ pDY08->oInspectStage4Vac6On = TRUE; }
				if (nNo == 0 || nNo == 7)	{ pDY08->oInspectStage4Vac7On = TRUE; }
				if (nNo == 0 || nNo == 8)	{ pDY08->oInspectStage4Vac8On = TRUE; }
		} else {
			if (gData.bMemphis) {
				if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage4Vac1On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage4Vac3On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage4Vac5On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage4Vac7On = TRUE; }
			} else {
				if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage4Vac2On = TRUE; }
				if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage4Vac4On = TRUE; }
				if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage4Vac6On = TRUE; }
				if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage4Vac8On = TRUE; }
			}
		}
		g_objAJinAXL.Write_Output(8);
	}
}

void CCommon::Set_VisionVacuumOff(int nVisionNo, int nType, int nNo)
{	//nVisionNo(1,2,3,4) nNo(0,1~8,9)
	if (nVisionNo == 1) {
		DY_DATA_07 *pDY07 = g_objAJinAXL.Get_pDY07();
		if (nType == 9) {
				if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage1Vac1On = FALSE; }
				if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage1Vac2On = FALSE; }
				if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage1Vac3On = FALSE; }
				if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage1Vac4On = FALSE; }
				if (nNo == 0 || nNo == 5)	{ pDY07->oInspectStage1Vac5On = FALSE; }
				if (nNo == 0 || nNo == 6)	{ pDY07->oInspectStage1Vac6On = FALSE; }
				if (nNo == 0 || nNo == 7)	{ pDY07->oInspectStage1Vac7On = FALSE; }
				if (nNo == 0 || nNo == 8)	{ pDY07->oInspectStage1Vac8On = FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage1Vac1On = FALSE; pDY07->oInspectStage1Vac2On = FALSE; }
			if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage1Vac3On = FALSE; pDY07->oInspectStage1Vac4On = FALSE; }
			if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage1Vac5On = FALSE; pDY07->oInspectStage1Vac6On = FALSE; }
			if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage1Vac7On = FALSE; pDY07->oInspectStage1Vac8On = FALSE; }
		}
		g_objAJinAXL.Write_Output(7);
	}
	if (nVisionNo == 2) {
		DY_DATA_07 *pDY07 = g_objAJinAXL.Get_pDY07();
		if (nType == 9) {
				if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage2Vac1On = FALSE; }
				if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage2Vac2On = FALSE; }
				if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage2Vac3On = FALSE; }
				if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage2Vac4On = FALSE; }
				if (nNo == 0 || nNo == 5)	{ pDY07->oInspectStage2Vac5On = FALSE; }
				if (nNo == 0 || nNo == 6)	{ pDY07->oInspectStage2Vac6On = FALSE; }
				if (nNo == 0 || nNo == 7)	{ pDY07->oInspectStage2Vac7On = FALSE; }
				if (nNo == 0 || nNo == 8)	{ pDY07->oInspectStage2Vac8On = FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ pDY07->oInspectStage2Vac1On = FALSE; pDY07->oInspectStage2Vac2On = FALSE; }
			if (nNo == 0 || nNo == 2)	{ pDY07->oInspectStage2Vac3On = FALSE; pDY07->oInspectStage2Vac4On = FALSE; }
			if (nNo == 0 || nNo == 3)	{ pDY07->oInspectStage2Vac5On = FALSE; pDY07->oInspectStage2Vac6On = FALSE; }
			if (nNo == 0 || nNo == 4)	{ pDY07->oInspectStage2Vac7On = FALSE; pDY07->oInspectStage2Vac8On = FALSE; }
		}
		g_objAJinAXL.Write_Output(7);
	}
	if (nVisionNo == 3) {
		DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();
		if (nType == 9) {
				if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage3Vac1On = FALSE; }
				if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage3Vac2On = FALSE; }
				if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage3Vac3On = FALSE; }
				if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage3Vac4On = FALSE; }
				if (nNo == 0 || nNo == 5)	{ pDY08->oInspectStage3Vac5On = FALSE; }
				if (nNo == 0 || nNo == 6)	{ pDY08->oInspectStage3Vac6On = FALSE; }
				if (nNo == 0 || nNo == 7)	{ pDY08->oInspectStage3Vac7On = FALSE; }
				if (nNo == 0 || nNo == 8)	{ pDY08->oInspectStage3Vac8On = FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage3Vac1On = FALSE; pDY08->oInspectStage3Vac2On = FALSE; }
			if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage3Vac3On = FALSE; pDY08->oInspectStage3Vac4On = FALSE; }
			if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage3Vac5On = FALSE; pDY08->oInspectStage3Vac6On = FALSE; }
			if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage3Vac7On = FALSE; pDY08->oInspectStage3Vac8On = FALSE; }
		}
		g_objAJinAXL.Write_Output(8);
	}
	if (nVisionNo == 4) {
		DY_DATA_08 *pDY08 = g_objAJinAXL.Get_pDY08();
		if (nType == 9) {
				if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage4Vac1On = FALSE; }
				if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage4Vac2On = FALSE; }
				if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage4Vac3On = FALSE; }
				if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage4Vac4On = FALSE; }
				if (nNo == 0 || nNo == 5)	{ pDY08->oInspectStage4Vac5On = FALSE; }
				if (nNo == 0 || nNo == 6)	{ pDY08->oInspectStage4Vac6On = FALSE; }
				if (nNo == 0 || nNo == 7)	{ pDY08->oInspectStage4Vac7On = FALSE; }
				if (nNo == 0 || nNo == 8)	{ pDY08->oInspectStage4Vac8On = FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ pDY08->oInspectStage4Vac1On = FALSE; pDY08->oInspectStage4Vac2On = FALSE; }
			if (nNo == 0 || nNo == 2)	{ pDY08->oInspectStage4Vac3On = FALSE; pDY08->oInspectStage4Vac4On = FALSE; }
			if (nNo == 0 || nNo == 3)	{ pDY08->oInspectStage4Vac5On = FALSE; pDY08->oInspectStage4Vac6On = FALSE; }
			if (nNo == 0 || nNo == 4)	{ pDY08->oInspectStage4Vac7On = FALSE; pDY08->oInspectStage4Vac8On = FALSE; }
		}
		g_objAJinAXL.Write_Output(8);
	}
}

BOOL CCommon::Get_VisionVacuumOn(int nVisionNo, int nNo, int *nCMInfo)
{	//nVisionNo(1,2,3,4) nNo(0,1~8,9)
	if (gData.bUseDryRun) return TRUE;
	
	int nRet = TRUE;
	gData.nVisionStageNo = nVisionNo;
	for(int i=0; i<8; i++) gData.nVisionVacErrNo[i] = 0;
	if (nVisionNo == 1) {
		DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX07->iInspectStage1Vac1On) { gData.nVisionVacErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX07->iInspectStage1Vac3On) { gData.nVisionVacErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX07->iInspectStage1Vac5On) { gData.nVisionVacErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX07->iInspectStage1Vac7On) { gData.nVisionVacErrNo[3] = 1; nRet =  FALSE; }}
		} else {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX07->iInspectStage1Vac2On) { gData.nVisionVacErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX07->iInspectStage1Vac4On) { gData.nVisionVacErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX07->iInspectStage1Vac6On) { gData.nVisionVacErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX07->iInspectStage1Vac8On) { gData.nVisionVacErrNo[3] = 1; nRet =  FALSE; }}
		}
	}
	if (nVisionNo == 2) {
		DX_DATA_07 *pDX07 = g_objAJinAXL.Get_pDX07();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX07->iInspectStage2Vac1On) { gData.nVisionVacErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX07->iInspectStage2Vac3On) { gData.nVisionVacErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX07->iInspectStage2Vac5On) { gData.nVisionVacErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX07->iInspectStage2Vac7On) { gData.nVisionVacErrNo[3] = 1; nRet =  FALSE; }}
		} else {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX07->iInspectStage2Vac2On) { gData.nVisionVacErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX07->iInspectStage2Vac4On) { gData.nVisionVacErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX07->iInspectStage2Vac6On) { gData.nVisionVacErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX07->iInspectStage2Vac8On) { gData.nVisionVacErrNo[3] = 1; nRet =  FALSE; }}
		}
	}
	if (nVisionNo == 3) {
		DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX08->iInspectStage3Vac1On) { gData.nVisionVacErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX08->iInspectStage3Vac3On) { gData.nVisionVacErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX08->iInspectStage3Vac5On) { gData.nVisionVacErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX08->iInspectStage3Vac7On) { gData.nVisionVacErrNo[3] = 1; nRet =  FALSE; }}
		} else {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX08->iInspectStage3Vac2On) { gData.nVisionVacErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX08->iInspectStage3Vac4On) { gData.nVisionVacErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX08->iInspectStage3Vac6On) { gData.nVisionVacErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX08->iInspectStage3Vac8On) { gData.nVisionVacErrNo[3] = 1; nRet =  FALSE; }}
		}
	}
	if (nVisionNo == 4) {
		DX_DATA_08 *pDX08 = g_objAJinAXL.Get_pDX08();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX08->iInspectStage4Vac1On) { gData.nVisionVacErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX08->iInspectStage4Vac3On) { gData.nVisionVacErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX08->iInspectStage4Vac5On) { gData.nVisionVacErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX08->iInspectStage4Vac7On) { gData.nVisionVacErrNo[3] = 1; nRet =  FALSE; }}
		} else {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX08->iInspectStage4Vac2On) { gData.nVisionVacErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX08->iInspectStage4Vac4On) { gData.nVisionVacErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX08->iInspectStage4Vac6On) { gData.nVisionVacErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX08->iInspectStage4Vac8On) { gData.nVisionVacErrNo[3] = 1; nRet =  FALSE; }}
		}
	}
	return nRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCommon::Set_UnloadPickerUp(int nPickNo, int nType, int nNo)
{	 //nPickNo(0,1,2) nNo(0~8)
	if (nPickNo == 0 || nPickNo ==  1) {
		DY_DATA_09 *pDY09 = g_objAJinAXL.Get_pDY09();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Up1 = TRUE; pDY09->oUnloadPicker1Down1 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Up2 = TRUE; pDY09->oUnloadPicker1Down2 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Up3 = TRUE; pDY09->oUnloadPicker1Down3 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Up4 = TRUE; pDY09->oUnloadPicker1Down4 = FALSE; }
			if (nNo == 0 || nNo ==  5) { pDY09->oUnloadPicker1Up5 = TRUE; pDY09->oUnloadPicker1Down5 = FALSE; }
			if (nNo == 0 || nNo ==  6) { pDY09->oUnloadPicker1Up6 = TRUE; pDY09->oUnloadPicker1Down6 = FALSE; }
			if (nNo == 0 || nNo ==  7) { pDY09->oUnloadPicker1Up7 = TRUE; pDY09->oUnloadPicker1Down7 = FALSE; }
			if (nNo == 0 || nNo ==  8) { pDY09->oUnloadPicker1Up8 = TRUE; pDY09->oUnloadPicker1Down8 = FALSE; }
		} else {
			if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Up1 = TRUE; pDY09->oUnloadPicker1Down1 = FALSE; pDY09->oUnloadPicker1Up2 = TRUE; pDY09->oUnloadPicker1Down2 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Up3 = TRUE; pDY09->oUnloadPicker1Down3 = FALSE; pDY09->oUnloadPicker1Up4 = TRUE; pDY09->oUnloadPicker1Down4 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Up5 = TRUE; pDY09->oUnloadPicker1Down5 = FALSE; pDY09->oUnloadPicker1Up6 = TRUE; pDY09->oUnloadPicker1Down6 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Up7 = TRUE; pDY09->oUnloadPicker1Down7 = FALSE; pDY09->oUnloadPicker1Up8 = TRUE; pDY09->oUnloadPicker1Down8 = FALSE; }
		}
		g_objAJinAXL.Write_Output(9);
	}
	if (nPickNo == 0 || nPickNo ==  2) {
		DY_DATA_10 *pDY10 = g_objAJinAXL.Get_pDY10();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Up1 = TRUE; pDY10->oUnloadPicker2Down1 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Up2 = TRUE; pDY10->oUnloadPicker2Down2 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Up3 = TRUE; pDY10->oUnloadPicker2Down3 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Up4 = TRUE; pDY10->oUnloadPicker2Down4 = FALSE; }
			if (nNo == 0 || nNo ==  5) { pDY10->oUnloadPicker2Up5 = TRUE; pDY10->oUnloadPicker2Down5 = FALSE; }
			if (nNo == 0 || nNo ==  6) { pDY10->oUnloadPicker2Up6 = TRUE; pDY10->oUnloadPicker2Down6 = FALSE; }
			if (nNo == 0 || nNo ==  7) { pDY10->oUnloadPicker2Up7 = TRUE; pDY10->oUnloadPicker2Down7 = FALSE; }
			if (nNo == 0 || nNo ==  8) { pDY10->oUnloadPicker2Up8 = TRUE; pDY10->oUnloadPicker2Down8 = FALSE; }
		} else {
			if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Up1 = TRUE; pDY10->oUnloadPicker2Down1 = FALSE; pDY10->oUnloadPicker2Up2 = TRUE; pDY10->oUnloadPicker2Down2 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Up3 = TRUE; pDY10->oUnloadPicker2Down3 = FALSE; pDY10->oUnloadPicker2Up4 = TRUE; pDY10->oUnloadPicker2Down4 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Up5 = TRUE; pDY10->oUnloadPicker2Down5 = FALSE; pDY10->oUnloadPicker2Up6 = TRUE; pDY10->oUnloadPicker2Down6 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Up7 = TRUE; pDY10->oUnloadPicker2Down7 = FALSE; pDY10->oUnloadPicker2Up8 = TRUE; pDY10->oUnloadPicker2Down8 = FALSE; }
		}
		g_objAJinAXL.Write_Output(10);
	}
}

void CCommon::Set_UnloadPickerDown(int nPickNo, int nType, int nNo)
{	//nPickNo(1,2) nNo(0,1~8,9) nSPNo(1~8) nSTNo(1~4)
	if (nPickNo == 1) {
		DY_DATA_09 *pDY09 = g_objAJinAXL.Get_pDY09();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Up1 = FALSE; pDY09->oUnloadPicker1Down1 = TRUE; }
			if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Up2 = FALSE; pDY09->oUnloadPicker1Down2 = TRUE; }
			if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Up3 = FALSE; pDY09->oUnloadPicker1Down3 = TRUE; }
			if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Up4 = FALSE; pDY09->oUnloadPicker1Down4 = TRUE; }
			if (nNo == 0 || nNo ==  5) { pDY09->oUnloadPicker1Up5 = FALSE; pDY09->oUnloadPicker1Down5 = TRUE; }
			if (nNo == 0 || nNo ==  6) { pDY09->oUnloadPicker1Up6 = FALSE; pDY09->oUnloadPicker1Down6 = TRUE; }
			if (nNo == 0 || nNo ==  7) { pDY09->oUnloadPicker1Up7 = FALSE; pDY09->oUnloadPicker1Down7 = TRUE; }
			if (nNo == 0 || nNo ==  8) { pDY09->oUnloadPicker1Up8 = FALSE; pDY09->oUnloadPicker1Down8 = TRUE; }
		} else {
			if (gData.bMemphis) {
				if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Up1 = FALSE; pDY09->oUnloadPicker1Down1 = TRUE; }
				if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Up3 = FALSE; pDY09->oUnloadPicker1Down3 = TRUE; }
				if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Up5 = FALSE; pDY09->oUnloadPicker1Down5 = TRUE; }
				if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Up7 = FALSE; pDY09->oUnloadPicker1Down7 = TRUE; }
			} else {
				if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Up2 = FALSE; pDY09->oUnloadPicker1Down2 = TRUE; }
				if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Up4 = FALSE; pDY09->oUnloadPicker1Down4 = TRUE; }
				if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Up6 = FALSE; pDY09->oUnloadPicker1Down6 = TRUE; }
				if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Up8 = FALSE; pDY09->oUnloadPicker1Down8 = TRUE; }
			}
		}
		g_objAJinAXL.Write_Output(9);
		gData.nUnloadPick1DownCnt = 1;
	}
	if (nPickNo == 2) {
		DY_DATA_10 *pDY10 = g_objAJinAXL.Get_pDY10();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Up1 = FALSE; pDY10->oUnloadPicker2Down1 = TRUE; }
			if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Up2 = FALSE; pDY10->oUnloadPicker2Down2 = TRUE; }
			if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Up3 = FALSE; pDY10->oUnloadPicker2Down3 = TRUE; }
			if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Up4 = FALSE; pDY10->oUnloadPicker2Down4 = TRUE; }
			if (nNo == 0 || nNo ==  5) { pDY10->oUnloadPicker2Up5 = FALSE; pDY10->oUnloadPicker2Down5 = TRUE; }
			if (nNo == 0 || nNo ==  6) { pDY10->oUnloadPicker2Up6 = FALSE; pDY10->oUnloadPicker2Down6 = TRUE; }
			if (nNo == 0 || nNo ==  7) { pDY10->oUnloadPicker2Up7 = FALSE; pDY10->oUnloadPicker2Down7 = TRUE; }
			if (nNo == 0 || nNo ==  8) { pDY10->oUnloadPicker2Up8 = FALSE; pDY10->oUnloadPicker2Down8 = TRUE; }
		} else {
			if (gData.bMemphis) {
				if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Up1 = FALSE; pDY10->oUnloadPicker2Down1 = TRUE; }
				if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Up3 = FALSE; pDY10->oUnloadPicker2Down3 = TRUE; }
				if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Up5 = FALSE; pDY10->oUnloadPicker2Down5 = TRUE; }
				if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Up7 = FALSE; pDY10->oUnloadPicker2Down7 = TRUE; }
			} else {
				if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Up2 = FALSE; pDY10->oUnloadPicker2Down2 = TRUE; }
				if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Up4 = FALSE; pDY10->oUnloadPicker2Down4 = TRUE; }
				if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Up6 = FALSE; pDY10->oUnloadPicker2Down6 = TRUE; }
				if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Up8 = FALSE; pDY10->oUnloadPicker2Down8 = TRUE; }
			}
		}
		g_objAJinAXL.Write_Output(10);
		gData.nUnloadPick2DownCnt = 1;
	}
}

void CCommon::Set_UnloadPickerClose(int nPickNo, int nType, int nNo)
{	 //nPickNo(0,1,2) nNo(0~8)
	if (nPickNo == 0 || nPickNo ==  1) {
		DY_DATA_09 *pDY09 = g_objAJinAXL.Get_pDY09();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Open1 = FALSE; pDY09->oUnloadPicker1Close1 = TRUE; }
			if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Open2 = FALSE; pDY09->oUnloadPicker1Close2 = TRUE; }
			if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Open3 = FALSE; pDY09->oUnloadPicker1Close3 = TRUE; }
			if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Open4 = FALSE; pDY09->oUnloadPicker1Close4 = TRUE; }
			if (nNo == 0 || nNo ==  5) { pDY09->oUnloadPicker1Open5 = FALSE; pDY09->oUnloadPicker1Close5 = TRUE; }
			if (nNo == 0 || nNo ==  6) { pDY09->oUnloadPicker1Open6 = FALSE; pDY09->oUnloadPicker1Close6 = TRUE; }
			if (nNo == 0 || nNo ==  7) { pDY09->oUnloadPicker1Open7 = FALSE; pDY09->oUnloadPicker1Close7 = TRUE; }
			if (nNo == 0 || nNo ==  8) { pDY09->oUnloadPicker1Open8 = FALSE; pDY09->oUnloadPicker1Close8 = TRUE; }
		} else {
			if (gData.bMemphis) {
				if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Open1 = FALSE; pDY09->oUnloadPicker1Close1 = TRUE; }
				if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Open3 = FALSE; pDY09->oUnloadPicker1Close3 = TRUE; }
				if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Open5 = FALSE; pDY09->oUnloadPicker1Close5 = TRUE; }
				if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Open7 = FALSE; pDY09->oUnloadPicker1Close7 = TRUE; }
			} else {
				if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Open2 = FALSE; pDY09->oUnloadPicker1Close2 = TRUE; }
				if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Open4 = FALSE; pDY09->oUnloadPicker1Close4 = TRUE; }
				if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Open6 = FALSE; pDY09->oUnloadPicker1Close6 = TRUE; }
				if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Open8 = FALSE; pDY09->oUnloadPicker1Close8 = TRUE; }
			}
		}
		g_objAJinAXL.Write_Output(9);
	}
	if (nPickNo == 0 || nPickNo ==  2) {
		DY_DATA_10 *pDY10 = g_objAJinAXL.Get_pDY10();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Open1 = FALSE; pDY10->oUnloadPicker2Close1 = TRUE; }
			if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Open2 = FALSE; pDY10->oUnloadPicker2Close2 = TRUE; }
			if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Open3 = FALSE; pDY10->oUnloadPicker2Close3 = TRUE; }
			if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Open4 = FALSE; pDY10->oUnloadPicker2Close4 = TRUE; }
			if (nNo == 0 || nNo ==  5) { pDY10->oUnloadPicker2Open5 = FALSE; pDY10->oUnloadPicker2Close5 = TRUE; }
			if (nNo == 0 || nNo ==  6) { pDY10->oUnloadPicker2Open6 = FALSE; pDY10->oUnloadPicker2Close6 = TRUE; }
			if (nNo == 0 || nNo ==  7) { pDY10->oUnloadPicker2Open7 = FALSE; pDY10->oUnloadPicker2Close7 = TRUE; }
			if (nNo == 0 || nNo ==  8) { pDY10->oUnloadPicker2Open8 = FALSE; pDY10->oUnloadPicker2Close8 = TRUE; }
		} else {
			if (gData.bMemphis) {
				if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Open1 = FALSE; pDY10->oUnloadPicker2Close1 = TRUE; }
				if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Open3 = FALSE; pDY10->oUnloadPicker2Close3 = TRUE; }
				if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Open5 = FALSE; pDY10->oUnloadPicker2Close5 = TRUE; }
				if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Open7 = FALSE; pDY10->oUnloadPicker2Close7 = TRUE; }
			} else {
				if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Open2 = FALSE; pDY10->oUnloadPicker2Close2 = TRUE; }
				if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Open4 = FALSE; pDY10->oUnloadPicker2Close4 = TRUE; }
				if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Open6 = FALSE; pDY10->oUnloadPicker2Close6 = TRUE; }
				if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Open8 = FALSE; pDY10->oUnloadPicker2Close8 = TRUE; }
			}
		}
		g_objAJinAXL.Write_Output(10);
	}
}

void CCommon::Set_UnloadPickerOpen(int nPickNo, int nType, int nNo)
{	//nPickNo(1,2) nNo(0,1~8,9) nSPNo(1~8) nSTNo(1~4)
	if (nPickNo == 0 || nPickNo == 1) {
		DY_DATA_09 *pDY09 = g_objAJinAXL.Get_pDY09();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Open1 = TRUE; pDY09->oUnloadPicker1Close1 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Open2 = TRUE; pDY09->oUnloadPicker1Close2 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Open3 = TRUE; pDY09->oUnloadPicker1Close3 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Open4 = TRUE; pDY09->oUnloadPicker1Close4 = FALSE; }
			if (nNo == 0 || nNo ==  5) { pDY09->oUnloadPicker1Open5 = TRUE; pDY09->oUnloadPicker1Close5 = FALSE; }
			if (nNo == 0 || nNo ==  6) { pDY09->oUnloadPicker1Open6 = TRUE; pDY09->oUnloadPicker1Close6 = FALSE; }
			if (nNo == 0 || nNo ==  7) { pDY09->oUnloadPicker1Open7 = TRUE; pDY09->oUnloadPicker1Close7 = FALSE; }
			if (nNo == 0 || nNo ==  8) { pDY09->oUnloadPicker1Open8 = TRUE; pDY09->oUnloadPicker1Close8 = FALSE; }
		} else {
			if (nNo == 0 || nNo ==  1) { pDY09->oUnloadPicker1Close1 = FALSE; pDY09->oUnloadPicker1Open1 = TRUE; pDY09->oUnloadPicker1Close2 = FALSE; pDY09->oUnloadPicker1Open2 = TRUE; }
			if (nNo == 0 || nNo ==  2) { pDY09->oUnloadPicker1Close3 = FALSE; pDY09->oUnloadPicker1Open3 = TRUE; pDY09->oUnloadPicker1Close4 = FALSE; pDY09->oUnloadPicker1Open4 = TRUE; }
			if (nNo == 0 || nNo ==  3) { pDY09->oUnloadPicker1Close5 = FALSE; pDY09->oUnloadPicker1Open5 = TRUE; pDY09->oUnloadPicker1Close6 = FALSE; pDY09->oUnloadPicker1Open6 = TRUE; }
			if (nNo == 0 || nNo ==  4) { pDY09->oUnloadPicker1Close7 = FALSE; pDY09->oUnloadPicker1Open7 = TRUE; pDY09->oUnloadPicker1Close8 = FALSE; pDY09->oUnloadPicker1Open8 = TRUE; }
		}
		g_objAJinAXL.Write_Output(9);
	}
	if (nPickNo == 0 || nPickNo == 2) {
		DY_DATA_10 *pDY10 = g_objAJinAXL.Get_pDY10();
		if (nType == 9) {
			if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Open1 = TRUE; pDY10->oUnloadPicker2Close1 = FALSE; }
			if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Open2 = TRUE; pDY10->oUnloadPicker2Close2 = FALSE; }
			if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Open3 = TRUE; pDY10->oUnloadPicker2Close3 = FALSE; }
			if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Open4 = TRUE; pDY10->oUnloadPicker2Close4 = FALSE; }
			if (nNo == 0 || nNo ==  5) { pDY10->oUnloadPicker2Open5 = TRUE; pDY10->oUnloadPicker2Close5 = FALSE; }
			if (nNo == 0 || nNo ==  6) { pDY10->oUnloadPicker2Open6 = TRUE; pDY10->oUnloadPicker2Close6 = FALSE; }
			if (nNo == 0 || nNo ==  7) { pDY10->oUnloadPicker2Open7 = TRUE; pDY10->oUnloadPicker2Close7 = FALSE; }
			if (nNo == 0 || nNo ==  8) { pDY10->oUnloadPicker2Open8 = TRUE; pDY10->oUnloadPicker2Close8 = FALSE; }
		} else {
			if (nNo == 0 || nNo ==  1) { pDY10->oUnloadPicker2Close1 = FALSE; pDY10->oUnloadPicker2Open1 = TRUE; pDY10->oUnloadPicker2Close2 = FALSE; pDY10->oUnloadPicker2Open2 = TRUE; }
			if (nNo == 0 || nNo ==  2) { pDY10->oUnloadPicker2Close3 = FALSE; pDY10->oUnloadPicker2Open3 = TRUE; pDY10->oUnloadPicker2Close4 = FALSE; pDY10->oUnloadPicker2Open4 = TRUE; }
			if (nNo == 0 || nNo ==  3) { pDY10->oUnloadPicker2Close5 = FALSE; pDY10->oUnloadPicker2Open5 = TRUE; pDY10->oUnloadPicker2Close6 = FALSE; pDY10->oUnloadPicker2Open6 = TRUE; }
			if (nNo == 0 || nNo ==  4) { pDY10->oUnloadPicker2Close7 = FALSE; pDY10->oUnloadPicker2Open7 = TRUE; pDY10->oUnloadPicker2Close8 = FALSE; pDY10->oUnloadPicker2Open8 = TRUE; }
		}
		g_objAJinAXL.Write_Output(10);
	}
	gData.nUnloadPick1OpenCnt = 1;
}

BOOL CCommon::Get_UnloadPickerOpen(int nPickNo, int nNo)
{	//nPickNo(1,2) nNo(0,1~8,9) nSPNo(1~8) nSTNo(1~4)
	if (nPickNo == 1) {
		DX_DATA_09 *pDX09 = g_objAJinAXL.Get_pDX09();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1)	{ if (!pDX09->iUnloadPicker1Open1) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (!pDX09->iUnloadPicker1Open3) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (!pDX09->iUnloadPicker1Open5) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (!pDX09->iUnloadPicker1Open7) return FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ if (!pDX09->iUnloadPicker1Open2) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (!pDX09->iUnloadPicker1Open4) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (!pDX09->iUnloadPicker1Open6) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (!pDX09->iUnloadPicker1Open8) return FALSE; }
		}
	}
	if (nPickNo == 2) {
		DX_DATA_10 *pDX10 = g_objAJinAXL.Get_pDX10();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1)	{ if (!pDX10->iUnloadPicker2Open1) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (!pDX10->iUnloadPicker2Open3) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (!pDX10->iUnloadPicker2Open5) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (!pDX10->iUnloadPicker2Open7) return FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ if (!pDX10->iUnloadPicker2Open2) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (!pDX10->iUnloadPicker2Open4) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (!pDX10->iUnloadPicker2Open6) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (!pDX10->iUnloadPicker2Open8) return FALSE; }
		}
	}
	return TRUE;
}

BOOL CCommon::Get_UnloadPickerClose(int nPickNo, int nNo)
{	//nPickNo(1,2) nType(0,1~8)
	if (nPickNo == 0 || nPickNo == 1) {
		DX_DATA_09 *pDX09 = g_objAJinAXL.Get_pDX09();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1)	{ if (pDX09->iUnloadPicker1Open1) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (pDX09->iUnloadPicker1Open3) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (pDX09->iUnloadPicker1Open5) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (pDX09->iUnloadPicker1Open7) return FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ if (pDX09->iUnloadPicker1Open2) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (pDX09->iUnloadPicker1Open4) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (pDX09->iUnloadPicker1Open6) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (pDX09->iUnloadPicker1Open8) return FALSE; }
		}
	}
	if (nPickNo == 0 || nPickNo == 2) {
		DX_DATA_10 *pDX10 = g_objAJinAXL.Get_pDX10();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1)	{ if (pDX10->iUnloadPicker2Open1) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (pDX10->iUnloadPicker2Open3) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (pDX10->iUnloadPicker2Open5) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (pDX10->iUnloadPicker2Open7) return FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ if (pDX10->iUnloadPicker2Open2) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (pDX10->iUnloadPicker2Open4) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (pDX10->iUnloadPicker2Open6) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (pDX10->iUnloadPicker2Open8) return FALSE; }
		}
	}
	return TRUE;
}

BOOL CCommon::Get_UnloadPickerUp(int nPickNo, int nNo)
{	//nPickNo(1,2) nType(0,1~8)
	if (nPickNo == 0 || nPickNo == 1) {
		DX_DATA_09 *pDX09 = g_objAJinAXL.Get_pDX09();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1)	{ if (!pDX09->iUnloadPicker1Up1 || pDX09->iUnloadPicker1Down1) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (!pDX09->iUnloadPicker1Up3 || pDX09->iUnloadPicker1Down3) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (!pDX09->iUnloadPicker1Up5 || pDX09->iUnloadPicker1Down5) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (!pDX09->iUnloadPicker1Up7 || pDX09->iUnloadPicker1Down7) return FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ if (!pDX09->iUnloadPicker1Up2 || pDX09->iUnloadPicker1Down2) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (!pDX09->iUnloadPicker1Up4 || pDX09->iUnloadPicker1Down4) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (!pDX09->iUnloadPicker1Up6 || pDX09->iUnloadPicker1Down6) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (!pDX09->iUnloadPicker1Up8 || pDX09->iUnloadPicker1Down8) return FALSE; }
		}
	}
	if (nPickNo == 0 || nPickNo == 2) {
		DX_DATA_10 *pDX10 = g_objAJinAXL.Get_pDX10();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1)	{ if (!pDX10->iUnloadPicker2Up1 || pDX10->iUnloadPicker2Down1) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (!pDX10->iUnloadPicker2Up3 || pDX10->iUnloadPicker2Down3) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (!pDX10->iUnloadPicker2Up5 || pDX10->iUnloadPicker2Down5) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (!pDX10->iUnloadPicker2Up7 || pDX10->iUnloadPicker2Down7) return FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ if (!pDX10->iUnloadPicker2Up2 || pDX10->iUnloadPicker2Down2) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (!pDX10->iUnloadPicker2Up4 || pDX10->iUnloadPicker2Down4) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (!pDX10->iUnloadPicker2Up6 || pDX10->iUnloadPicker2Down6) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (!pDX10->iUnloadPicker2Up8 || pDX10->iUnloadPicker2Down8) return FALSE; }
		}
	}
	return TRUE;
}

BOOL CCommon::Get_UnloadPickerDown(int nPickNo, int nNo)
{	//nPickNo(1,2) nNo(0,1~8,9) nSPNo(1~8) nSTNo(1~4)
	if (nPickNo == 1) {
		DX_DATA_09 *pDX09 = g_objAJinAXL.Get_pDX09();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1)	{ if (pDX09->iUnloadPicker1Up1 || !pDX09->iUnloadPicker1Down1) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (pDX09->iUnloadPicker1Up3 || !pDX09->iUnloadPicker1Down3) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (pDX09->iUnloadPicker1Up5 || !pDX09->iUnloadPicker1Down5) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (pDX09->iUnloadPicker1Up7 || !pDX09->iUnloadPicker1Down7) return FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ if (pDX09->iUnloadPicker1Up2 || !pDX09->iUnloadPicker1Down2) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (pDX09->iUnloadPicker1Up4 || !pDX09->iUnloadPicker1Down4) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (pDX09->iUnloadPicker1Up6 || !pDX09->iUnloadPicker1Down6) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (pDX09->iUnloadPicker1Up8 || !pDX09->iUnloadPicker1Down8) return FALSE; }
		}
	}
	if (nPickNo == 2) {
		DX_DATA_10 *pDX10 = g_objAJinAXL.Get_pDX10();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1)	{ if (pDX10->iUnloadPicker2Up1 || !pDX10->iUnloadPicker2Down1) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (pDX10->iUnloadPicker2Up3 || !pDX10->iUnloadPicker2Down3) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (pDX10->iUnloadPicker2Up5 || !pDX10->iUnloadPicker2Down5) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (pDX10->iUnloadPicker2Up7 || !pDX10->iUnloadPicker2Down7) return FALSE; }
		} else {
			if (nNo == 0 || nNo == 1)	{ if (pDX10->iUnloadPicker2Up2 || !pDX10->iUnloadPicker2Down2) return FALSE; }
			if (nNo == 0 || nNo == 2)	{ if (pDX10->iUnloadPicker2Up4 || !pDX10->iUnloadPicker2Down4) return FALSE; }
			if (nNo == 0 || nNo == 3)	{ if (pDX10->iUnloadPicker2Up6 || !pDX10->iUnloadPicker2Down6) return FALSE; }
			if (nNo == 0 || nNo == 4)	{ if (pDX10->iUnloadPicker2Up8 || !pDX10->iUnloadPicker2Down8) return FALSE; }
		}
	}
	return TRUE;
}

BOOL CCommon::Get_UnloadPickerCheck(int nPickNo, int nNo, int *nCMInfo)
{	//nPickNo(1,2) nNo(0,1~8,9)
	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (gData.bUseDryRun || pEquipData->bUseCMCheck == FALSE) return TRUE;

	int nRet = TRUE;
	if (nPickNo == 1) {
		for(int i=0; i<8; i++) gData.nUnloadPicker1ErrNo[i] = 0;
		DX_DATA_09 *pDX09 = g_objAJinAXL.Get_pDX09();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX09->iUnloadPicker1Exist1) { gData.nUnloadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX09->iUnloadPicker1Exist3) { gData.nUnloadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX09->iUnloadPicker1Exist5) { gData.nUnloadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX09->iUnloadPicker1Exist7) { gData.nUnloadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
		} else {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX09->iUnloadPicker1Exist2) { gData.nUnloadPicker1ErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX09->iUnloadPicker1Exist4) { gData.nUnloadPicker1ErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX09->iUnloadPicker1Exist6) { gData.nUnloadPicker1ErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX09->iUnloadPicker1Exist8) { gData.nUnloadPicker1ErrNo[3] = 1; nRet =  FALSE; }}
		}
	}
	if (nPickNo == 2) {
		for(int i=0; i<8; i++) gData.nUnloadPicker2ErrNo[i] = 0;
		DX_DATA_10 *pDX10 = g_objAJinAXL.Get_pDX10();
		if (gData.bMemphis) {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX10->iUnloadPicker2Exist1) { gData.nUnloadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX10->iUnloadPicker2Exist3) { gData.nUnloadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX10->iUnloadPicker2Exist5) { gData.nUnloadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX10->iUnloadPicker2Exist7) { gData.nUnloadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
		} else {
			if (nNo == 0 || nNo == 1 || (nNo == 9 && nCMInfo[0] > 0))	{ if (!pDX10->iUnloadPicker2Exist2) { gData.nUnloadPicker2ErrNo[0] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 2 || (nNo == 9 && nCMInfo[1] > 0))	{ if (!pDX10->iUnloadPicker2Exist4) { gData.nUnloadPicker2ErrNo[1] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 3 || (nNo == 9 && nCMInfo[2] > 0))	{ if (!pDX10->iUnloadPicker2Exist6) { gData.nUnloadPicker2ErrNo[2] = 1; nRet =  FALSE; }}
			if (nNo == 0 || nNo == 4 || (nNo == 9 && nCMInfo[3] > 0))	{ if (!pDX10->iUnloadPicker2Exist8) { gData.nUnloadPicker2ErrNo[3] = 1; nRet =  FALSE; }}
		}
	}
	return nRet;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void CCommon::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while(GetTickCount() - dwStart < dwMillisecond)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
void CCommon::Save_Motion(int nAxis, int nMoveIdx, double dTraget)
{
	MOVE_DATA *pMoveData = g_objDataManager.Get_pMoveData();
	
	int nModuleCount = 0;
	CString strAxis, strLog, strInfo, strTemp, strLotId, strBarcode, strPort, strTray, strCm;
	double dCheckPos, dCurrentPos;

	dCurrentPos = g_objAJinAXL.Get_Position(nAxis);
	
	switch(nAxis) {
	case  0: strAxis = "Elevator1,Z"; break;
	case  1: strAxis = "Elevator2,Z"; break;
	case  2: strAxis = "Elevator3,Z"; break;
	case  3: strAxis = "Elevator4,Z"; break;
	case  4: strAxis = "Elevator5,Z"; break;
	case  5: strAxis = "Elevator6,Z"; break;
	case  6: strAxis = "Elevator7,Z"; break;
	case  7: strAxis = "Transfer1,X"; break;
	case  8: strAxis = "Transfer1,Z"; break;
	case  9: strAxis = "Transfer2,X"; break;
	case 10: strAxis = "Transfer2,Z"; break;
	case 11: strAxis = "LoadStage1,Y"; break;
	case 12: strAxis = "LoadStage2,Y"; break;
	case 13: strAxis = "LoadPicker1,X"; break;
	case 14: strAxis = "LoadPicker1,Y"; break;
	case 15: strAxis = "LoadPicker1,Z"; break;
	case 16: strAxis = "LoadPicker1,P"; break;
	case 17: strAxis = "LoadPicker2,X"; break;
	case 18: strAxis = "LoadPicker2,Y"; break;
	case 19: strAxis = "LoadPicker2,Z"; break;
	case 20: strAxis = "LoadPicker2,P"; break;
	case 21: strAxis = "BottomCamera,Z"; break;
	case 22: strAxis = "BottomLight,Z"; break;
	case 23: strAxis = "BottomMirror,Y"; break;
	case 24: strAxis = "Top1,Z"; break;
	case 25: strAxis = "Top2,Z"; break;
	case 26: strAxis = "InspecStage1,X"; break;
	case 27: strAxis = "InspecStage2,X"; break;
	case 28: strAxis = "InspecStage3,X"; break;
	case 29: strAxis = "InspecStage4,X"; break;
	case 30: strAxis = "UnloadPicker1,X"; break;
	case 31: strAxis = "UnloadPicker1,Y"; break;
	case 32: strAxis = "UnloadPicker1,Z"; break;
	case 33: strAxis = "UnloadPicker1,P"; break;
	case 34: strAxis = "UnloadPicker2,X"; break;
	case 35: strAxis = "UnloadPicker2,Y"; break;
	case 36: strAxis = "UnloadPicker2,Z"; break;
	case 37: strAxis = "UnloadPicker2,P"; break;
	case 38: strAxis = "GoodStage1,Y"; break;
	case 39: strAxis = "GoodStage2,Y"; break;
	case 40: strAxis = "NgStage1,Y"; break;
	case 41: strAxis = "NgStage2,Y"; break;
	case 42: strAxis = "ShipAlign,X"; break;
	case 43: strAxis = "TopLight1,Z"; break;
	case 44: strAxis = "TopMirror1,Y"; break;
	}

	if (nMoveIdx != -1) {	// Check_Position 
		switch(nAxis) {
		case  0: dCheckPos = pMoveData->dElevatorZ1[nMoveIdx];		break;
		case  1: dCheckPos = pMoveData->dElevatorZ2[nMoveIdx];		break;
		case  2: dCheckPos = pMoveData->dElevatorZ3[nMoveIdx];		break;
		case  3: dCheckPos = pMoveData->dElevatorZ4[nMoveIdx];		break;
		case  4: dCheckPos = pMoveData->dElevatorZ5[nMoveIdx];		break;
		case  5: dCheckPos = pMoveData->dElevatorZ6[nMoveIdx];		break;
		case  6: dCheckPos = pMoveData->dElevatorZ7[nMoveIdx];		break;
		case  7: dCheckPos = pMoveData->dTransferX1[nMoveIdx];		break;
		case  8: dCheckPos = pMoveData->dTransferZ1[nMoveIdx];		break;
		case  9: dCheckPos = pMoveData->dTransferX2[nMoveIdx];		break;
		case 10: dCheckPos = pMoveData->dTransferZ2[nMoveIdx];		break;
		case 11: dCheckPos = pMoveData->dLoadStageY1[nMoveIdx];		break;
		case 12: dCheckPos = pMoveData->dLoadStageY2[nMoveIdx];		break;
		case 13: dCheckPos = pMoveData->dLoadPickerX1[nMoveIdx];	break;
		case 14: dCheckPos = pMoveData->dLoadPickerY1[nMoveIdx];	break;
		case 15: dCheckPos = pMoveData->dLoadPickerZ1[nMoveIdx];	break;
		case 16: dCheckPos = pMoveData->dLoadPickerP1[nMoveIdx];	break;
		case 17: dCheckPos = pMoveData->dLoadPickerX2[nMoveIdx];	break;
		case 18: dCheckPos = pMoveData->dLoadPickerY2[nMoveIdx];	break;
		case 19: dCheckPos = pMoveData->dLoadPickerZ2[nMoveIdx];	break;
		case 20: dCheckPos = pMoveData->dLoadPickerP2[nMoveIdx];	break;
		case 21: dCheckPos = pMoveData->dBTMFocusZ[nMoveIdx];		break;
		case 22: dCheckPos = pMoveData->dBTMLightZ[nMoveIdx];		break;
		case 23: dCheckPos = pMoveData->dBTMAngleY[nMoveIdx];		break;
		case 24: dCheckPos = pMoveData->dTOPVisionZ1[nMoveIdx];		break;
		case 25: dCheckPos = pMoveData->dTOPVisionZ2[nMoveIdx];		break;
		case 26: dCheckPos = pMoveData->dVisionStageX1[nMoveIdx];	break;
		case 27: dCheckPos = pMoveData->dVisionStageX2[nMoveIdx];	break;
		case 28: dCheckPos = pMoveData->dVisionStageX3[nMoveIdx];	break;
		case 29: dCheckPos = pMoveData->dVisionStageX4[nMoveIdx];	break;
		case 30: dCheckPos = pMoveData->dUnloadPickerX1[nMoveIdx];	break;
		case 31: dCheckPos = pMoveData->dUnloadPickerY1[nMoveIdx];	break;
		case 32: dCheckPos = pMoveData->dUnloadPickerZ1[nMoveIdx];	break;
		case 33: dCheckPos = pMoveData->dUnloadPickerP1[nMoveIdx];	break;
		case 34: dCheckPos = pMoveData->dUnloadPickerX2[nMoveIdx];	break;
		case 35: dCheckPos = pMoveData->dUnloadPickerY2[nMoveIdx];	break;
		case 36: dCheckPos = pMoveData->dUnloadPickerZ2[nMoveIdx];	break;
		case 37: dCheckPos = pMoveData->dUnloadPickerP2[nMoveIdx];	break;
		case 38: dCheckPos = pMoveData->dGoodStageY1[nMoveIdx];		break;
		case 39: dCheckPos = pMoveData->dGoodStageY2[nMoveIdx];		break;
		case 40: dCheckPos = pMoveData->dNGStageY1[nMoveIdx];		break;
		case 41: dCheckPos = pMoveData->dNGStageY2[nMoveIdx];		break;
		case 42: dCheckPos = pMoveData->dShiipAling[nMoveIdx];		break;
		case 43: dCheckPos = pMoveData->dTop1LightZ[nMoveIdx];		break;
		case 44: dCheckPos = pMoveData->dTop1AngleY[nMoveIdx];		break;
		}
	} else {
		dCheckPos = dTraget;
	}

	strInfo = strTemp = strLotId = strBarcode = strPort = strTray = strCm = "";
	if (nAxis >= 13 && nAxis <= 15) {	// Load Picker1 X,Y,Z
		int nNo = gData.InfoLoadPick[0][9];
		if (nNo > 0) {
			for (int i = 0; i < 4; i++) {
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
	if (nAxis >= 17 && nAxis <= 19) {	// Load Picker2 X,Y,Z
		int nNo = gData.InfoLoadPick[1][9];
		if (nNo > 0) {
			for (int i = 0; i < 4; i++) {
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
	if (nAxis >= 26 && nAxis <= 29) {	// Inspection Stage X
		int nX = nAxis - 26;
		int nNo = gData.InfoVision[nX][9];
		if (nNo > 0) {
			for (int i = 0; i < 4; i++) {
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
	if (nAxis >= 30 && nAxis <= 32) {	// Unload Picker1 X,Y,Z
		int nNo = gData.InfoUnloadPick[0][9];
		if (nNo > 0) {
			for (int i = 0; i < 4; i++) {
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
	if (nAxis >= 34 && nAxis <= 36) {	// Unload Picker2 X,Y,Z
		int nNo = gData.InfoUnloadPick[1][9];
		if (nNo > 0) {
			for (int i = 0; i < 4; i++) {
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

	if (strBarcode.Right(1) == ';') strBarcode.Delete(strBarcode.GetLength()-1);
	if (strPort.Right(1) == ';') strPort.Delete(strPort.GetLength()-1);
	if (strTray.Right(1) == ';') strTray.Delete(strTray.GetLength()-1);
	if (strCm.Right(1) == ';') strCm.Delete(strCm.GetLength()-1);

	strLotId = "";
	if (nAxis >=  7 && nAxis <=  8) { strLotId = gData.sLotID_Tansfer[0];		if (strLotId == "") strLotId = gData.sLotID_Tansfer[2]; }
	if (nAxis >=  9 && nAxis <= 10) { strLotId = gData.sLotID_Tansfer[1];		if (strLotId == "") strLotId = gData.sLotID_Tansfer[2]; }
	if (nAxis == 11)				{ strLotId = gData.sLotID_LoadStage[0];		if (strLotId == "") strLotId = gData.sLotID_LoadStage[2]; }
	if (nAxis == 12)				{ strLotId = gData.sLotID_LoadStage[1];		if (strLotId == "") strLotId = gData.sLotID_LoadStage[2]; }
	if (nAxis >= 13 && nAxis <= 16) { strLotId = gData.sLotID_LoadPicker[0];	if (strLotId == "") strLotId = gData.sLotID_LoadPicker[2]; }
	if (nAxis >= 17 && nAxis <= 20) { strLotId = gData.sLotID_LoadPicker[1];	if (strLotId == "") strLotId = gData.sLotID_LoadPicker[2]; }
	if (nAxis == 26)				{ strLotId = gData.sLotID_VisionStage[0];	if (strLotId == "") strLotId = gData.sLotID_VisionStage[4]; }
	if (nAxis == 27)				{ strLotId = gData.sLotID_VisionStage[1];	if (strLotId == "") strLotId = gData.sLotID_VisionStage[4]; }
	if (nAxis == 28)				{ strLotId = gData.sLotID_VisionStage[2];	if (strLotId == "") strLotId = gData.sLotID_VisionStage[4]; }
	if (nAxis == 29)				{ strLotId = gData.sLotID_VisionStage[3];	if (strLotId == "") strLotId = gData.sLotID_VisionStage[4]; }
	if (nAxis >= 30 && nAxis <= 33) { strLotId = gData.sLotID_UnloadPicker[0];	if (strLotId == "") strLotId = gData.sLotID_UnloadPicker[2]; }
	if (nAxis >= 34 && nAxis <= 37) { strLotId = gData.sLotID_UnloadPicker[1];	if (strLotId == "") strLotId = gData.sLotID_UnloadPicker[2]; }
	if (nAxis == 38)				{ strLotId = gData.sLotID_GoodTray[0];		if (strLotId == "") strLotId = gData.sLotID_GoodTray[2]; }
	if (nAxis == 39)				{ strLotId = gData.sLotID_GoodTray[1];		if (strLotId == "") strLotId = gData.sLotID_GoodTray[2]; }
	if (nAxis == 40)				{ strLotId = gData.sLotID_NGTray[0];		if (strLotId == "") strLotId = gData.sLotID_NGTray[2]; }
	if (nAxis == 41)				{ strLotId = gData.sLotID_NGTray[1];		if (strLotId == "") strLotId = gData.sLotID_NGTray[2]; }
	if (strLotId == "") strLotId = gData.sLotID_Start;

	strInfo.Format("%s,%s,%s,%s,%s,%d", strLotId, strBarcode, strPort, strTray, strCm, nModuleCount);
	strLog.Format("%s,%s,%0.3lf,%0.3lf", strInfo, strAxis, dCheckPos, dCurrentPos);

	g_objLogFile.Save_SpcMotionLog(strLog, strLotId);
}

void CCommon::Set_LotCount(int nPortNo, CString sLotID, int nCount)
{
	g_dlgWork.Set_LotCount(nPortNo, sLotID, nCount);
}


void CCommon::Copy_File(CString strPath, CString strName)
{	
	CString strOriginFile, strTargetFile, strDateTime;

	g_objLogFile.Create_Folder("D:\\RMS");
	strOriginFile.Format("%s\\%s.ini", strPath, strName);
	strTargetFile.Format("D:\\RMS\\%s.ini", strName);

	if (!CopyFile(strOriginFile, strTargetFile, FALSE)) return;
}

