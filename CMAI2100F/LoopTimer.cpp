// LoopTimer.cpp : 구현 파일
//
#include "StdAfx.h"
#include "LoopTimer.h"
#include "LogFile.h"
#include "DataManager.h"

CLoopTimer::CLoopTimer()
{
	m_dwLoopStart = 0;
	m_dwLoopTerm = 0;

	m_bWaitingRun = FALSE;
	m_dwWaitingStart = 0;
}

CLoopTimer::~CLoopTimer()
{
}

void CLoopTimer::Set_LoopTime(DWORD msec)
{
	m_dwLoopStart = GetTickCount();
	m_dwLoopTerm = msec;
}

BOOL CLoopTimer::Over_LoopTime()
{
	//return FALSE;	// No Timeout Error

	DWORD dwTerm = GetTickCount() - m_dwLoopStart;
	if (dwTerm >= m_dwLoopTerm)
		return TRUE;
	else
		return FALSE;
}

BOOL CLoopTimer::Delay_LoopTime(DWORD msec)
{
	DWORD dwTerm = GetTickCount() - m_dwLoopStart;
	if (dwTerm >= msec) return TRUE;
	else return FALSE;
}

///////////////////////////////////////////////////////////////////////////////

BOOL CLoopTimer::Waiting_Time(DWORD msec)
{
	if (!m_bWaitingRun) {
		m_bWaitingRun = TRUE;
		m_dwWaitingStart = GetTickCount();
	}

	DWORD dwTerm = GetTickCount() - m_dwWaitingStart;
	if (dwTerm < msec) return FALSE;
	
	m_bWaitingRun = FALSE;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

void CLoopTimer::Takt_Start(int nFun, int nId, BOOL bFirst)
{
	int nSeqTotal = 0;
	int nPortNo = 0;
	CString strFun, strLog, strMsg, strInfo, strLotId, strType;

	g_objLogFile.Get_ZoneMsg(nFun, nId, strLotId, nPortNo, nSeqTotal, strFun, strMsg, strType);
	if (bFirst) g_objLogFile.Save_StdMotionLog(strLotId, "Y", nFun, nId, 1, strFun, strMsg);
	g_objLogFile.Save_StdMotionLog(strLotId, strType, nFun, nId, 1, strFun, strMsg);

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseTaktLog) return;

	m_dwTakt = GetTickCount();
}

void CLoopTimer::Takt_Save(int nFun, int nId, BOOL bLast)
{
	int nSeqTotal = 0;
	int nPortNo = 0;
	CString strFun, strLog, strMsg, strInfo, strLotId, strType;

	g_objLogFile.Get_ZoneMsg(nFun, nId, strLotId, nPortNo, nSeqTotal, strFun, strMsg, strType);
	g_objLogFile.Save_StdMotionLog(strLotId, strType, nFun, nId, 0, strFun, strMsg);
	if (bLast) g_objLogFile.Save_StdMotionLog(strLotId, "Y", nFun, nId, 0, strFun, strMsg);

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (!pEquipData->bUseTaktLog) return;

	double dTime = (GetTickCount() - m_dwTakt) / 1000.0;	if (dTime > 60.0) return;
	strInfo = Add_ModuleInfo(nFun, nId);

	strLog.Format("MCC,(%02d),%s,%s,%s,%02d/%02d,%s,%0.3lf", nFun, strLotId, strInfo, strFun, nId, nSeqTotal, strMsg, dTime);
	g_objLogFile.Save_SpcMccLog(strLog, strLotId);
}

CString CLoopTimer::Add_ModuleInfo(int nFun, int nId)
{
	int nModuleCount = 0;
	CString strReturn, strTemp, strBarcode, strPort, strTray, strCm;
	strReturn = strTemp = strBarcode = strPort = strTray = strCm = "";

	if (nFun == 12) {	// Load Picker1 X,Y,Z
		int nNo = gData.InfoLoadPick[0][9];
		if (nNo > 0) {
			for (int i = 0; i < 8; i++) {
				if (gData.InfoLoadPick[0][i] > 0) {
					strTemp.Format("%d;", gData.nPortNo_LoadPicker[0]); strPort += strTemp;
					strTemp.Format("%d;", gData.nTrayNo_LoadPicker[0]); strTray += strTemp;
					strTemp.Format("%d;", nNo+i);						strCm += strTemp;
					strTemp.Format(";");								  strBarcode += strTemp;
					nModuleCount++;
				}
			}
		}
	}
	if (nFun == 13) {	// Load Picker2 X,Y,Z
		int nNo = gData.InfoLoadPick[1][9];
		if (nNo > 0) {
			for (int i = 0; i < 8; i++) {
				if (gData.InfoLoadPick[1][i] > 0) {
					strTemp.Format("%d;", gData.nPortNo_LoadPicker[1]); strPort += strTemp;
					strTemp.Format("%d;", gData.nTrayNo_LoadPicker[1]); strTray += strTemp;
					strTemp.Format("%d;", nNo+i);						strCm += strTemp;
					strTemp.Format(";");								  strBarcode += strTemp;
					nModuleCount++;
				}
			}
		}
	}
	if (nFun >= 14 && nFun <= 17) {	// Inspection Stage X
		int nX = nFun - 14;
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
	if (nFun == 18) {	// Unload Picker1 X,Y,Z
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
	if (nFun == 19) {	// Unload Picker2 X,Y,Z
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

	if (strBarcode.Right(1) == ';') strBarcode.Delete(strBarcode.GetLength()-1);
	if (strPort.Right(1) == ';') strPort.Delete(strPort.GetLength()-1);
	if (strTray.Right(1) == ';') strTray.Delete(strTray.GetLength()-1);
	if (strCm.Right(1) == ';') strCm.Delete(strCm.GetLength()-1);

	strReturn.Format("%s,%s,%s,%s,%d", strBarcode, strPort, strTray, strCm, nModuleCount);
	return strReturn;
}

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
