// LogFile.cpp: implementation of the CLogFile class.
//
#include "stdafx.h"
#include "LogFile.h"
#include "Inspector.h"
#include "AJinAXL.h"
#include "DataManager.h"

// CLogFile
CLogFile g_objLogFile;

CCriticalSection g_csAlarmLog;
CCriticalSection g_csHandlerLog;
CCriticalSection g_csInspectorLog;
CCriticalSection g_csJobListLog;
CCriticalSection g_csAlignerLog;
CCriticalSection g_csMesAgentLog;
CCriticalSection g_csDispatcherLog;
CCriticalSection g_csDailyLotLog;
CCriticalSection g_csOperatingRatioLog;
CCriticalSection g_csStdMotionLog;
CCriticalSection g_csEfficiencyLog;
CCriticalSection g_csSeqLog;

CLogFile::CLogFile()
{
}

CLogFile::~CLogFile()
{
}

///////////////////////////////////////////////////////////////////////////////

void CLogFile::Create_Folder(CString sPath)
{
	if (sPath == _T("")) return;
	if (sPath.Right(1) == _T("\\")) sPath = sPath.Left(sPath.GetLength() - 1);
	if (GetFileAttributes(sPath) != -1) return;	// Directory Exist!!!

	int nFound = sPath.ReverseFind('\\');
	Create_Folder(sPath.Left(nFound));

	CreateDirectory(sPath, NULL);
}

///////////////////////////////////////////////////////////////////////////////

void CLogFile::Save_AlarmLog(CString sLog)
{
	g_csAlarmLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\Alarm";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csAlarmLog.Unlock();
}

void CLogFile::Save_AlarmResetLog(CString strLog)
{
	Save_AlarmECMLog(1, strLog);
}

void CLogFile::Save_AlarmECMLog(int nType, CString strLog)	//nType:1[Reset], 0[Set]
{
	CString strFile, sTitle, strTime1, strTime2, strSave, sNGCodeList, sTitleTemp;

	SYSTEMTIME time;
	GetLocalTime(&time);
	strTime1.Format("%04d%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour);
	strTime2.Format("%02d:%02d:%02d.%03d", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	sTitle.Format("Time,LotNum,Code,Alarm,Start,End,Duration,min,Unit,Group,Detail Items\r\n");
	strFile.Format("%s%s_%s_Alarm.csv", ECM_LOG, gAlm.sLotID, strTime1);

	
	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());

		if (nType == 0) strSave.Format("%s,%s,,,,,%s,%s,%s\r\n", strTime2, strLog, gAlm.sUnit, gAlm.sGroup, gAlm.sItems);
		else			strSave.Format("%s,%s,%s,%s,%s\r\n", strTime2, strLog, gAlm.sUnit, gAlm.sGroup, gAlm.sItems);

		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_HandlerLog(CString sLog)
{
	g_csHandlerLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\Handler";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d.csv", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csHandlerLog.Unlock();
}

void CLogFile::Save_InspectorLog(CString sLog)
{
	g_csInspectorLog.Lock();

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strSave;
	strPath.Format("%s\\LOG\\Inspector\\%04d\\%02d\\%02d", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	strFile.Format("%s\\%04d%02d%02d-%02d.csv", strPath, time.wYear, time.wMonth, time.wDay, time.wHour);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csInspectorLog.Unlock();
}


void CLogFile::Save_JobListLog(CString sLog)
{
	g_csJobListLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\JobList";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, sTitle, strSave;

	strFile.Format("%s\\%04d%02d%02d.csv", strPath, time.wYear, time.wMonth, time.wDay);
	if (time.wHour < 7) {
		CTime PreDay(time);
		PreDay -= CTimeSpan(1,0,0,0);	//CTimeSpan(??,??,??,??)
		strFile.Format("%s\\%04d%02d%02d.csv", strPath,  PreDay.GetYear(), PreDay.GetMonth(), PreDay.GetDay());
	}

//	sTitle.Format("Time,PortNo,LotID,Count,NG_Count,Good_Count,Rate,Start_Time,End_Time,Tack\r\n");
	sTitle.Format("Time,PortNo,LotID,Count,NG_Count,Good_Count,Rate,Skip_Count,Bar_NoRead,RosJudge,RosGood,RosNG,RosRepair,RosTimeOver,Start_Time,End_Time,Tack,FAI_NG\r\n");

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			CString strSave;
			if (file.GetLength() <= 0) {
				strSave.Format("%s%02d:%02d:%02d %03d,%s\r\n", sTitle, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);
			} else {
				strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);
			}

			file.SeekToEnd();	
			file.Write(strSave, strSave.GetLength());
			file.Close();
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csJobListLog.Unlock();
}

void CLogFile::Save_ECMLog(int nType, CString strLog)	//nType:1[Alarm], 2[Joblist]
{
	CString strFile, sTitle, strTime, strDate, strTime2, strTime1, strSave;

	SYSTEMTIME time;
	GetLocalTime(&time);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	strDate.Format("%04d-%02d-%02d", time.wYear, time.wMonth, time.wDay);
	strTime2.Format("%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
	strTime1.Format("%02d:%02d:%02d.%03d", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	sTitle.Format("Time,Station,SensorID,Barcode,Date,Time2,Machine_Code,Time,LotNum,PortNo,Count,NG_Count,Good_Count,Rate,Skip_Count,Bar_NoRead,RosJudge,RosGood,RosNG,RosRepair,RosTimeOver,Start_Time,End_Time,Tack,FAI_NG\r\n");
	strFile.Format("%s%s_%04d%02d%02d%02d_JobList.csv", ECM_LOG, gLot.sELotID, time.wYear, time.wMonth, time.wDay, time.wHour);

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());

		strSave.Format("%s,%s,,,%s,%s,%s,%s,%s,%s\r\n", strTime, m_sPCID, strDate, strTime2, m_sMachineCode, strTime1, gLot.sELotID, strLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_ECMOutPut(int nPNo, int nTNo, int nMNo, int nType)
{
	CString sLotID, strFile, sTitle, strTime, strDate, strTime2, strTime1, strSave, sData1, sData2, sData3;
	if (nPNo < 1 || nPNo > 6) return;
	if (nTNo < 1 || nTNo > 20) return;
	if (nMNo < 1 || nMNo > 40) return;
	sLotID = gLot.sLotID[nPNo-1];

	SYSTEMTIME time;
	GetLocalTime(&time);
	strTime.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	strDate.Format("%04d-%02d-%02d", time.wYear, time.wMonth, time.wDay);
	strTime2.Format("%02d:%02d:%02d", time.wHour, time.wMinute, time.wSecond);
	strTime1.Format("%02d:%02d:%02d.%03d", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	sTitle.Format("Time,Station,SensorID,Barcode,Date,Time2,Machine_Code,Time,LotNum,LoadPort,LoadTray,LoadPos,LoadPicker,LoadPickerNo,VisionStage,VisionStageNo,UnloadPicker,UnloadPickerNo,Output,OutTray,OutPos,Judge,JudgeB1,DefectCodeB1,JudgeAG,DefectCodeAG,JudgeT1,DefectCodeT1,JudgeTG,DefectCodeTG,JudgeT2,DefectCodeT2,ADJ Result,Flow Time,BTM Vision Process Time,Top1 Vision Process Time,Top2 Vision Process Time,ULD delay,ROS Operator,ROS Images,ROS Result,ROS Judge Time,ROS Response Time,???? ???? ????? ???,LoadMZID,InputCarrierID,OutputCarrierID,Repair,MN-Code\r\n");
	strFile.Format("%s%s_%04d%02d%02d%02d_Output.csv", ECM_LOG, sLotID, time.wYear, time.wMonth, time.wDay, time.wHour);

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());

		int		nOutTray;
		CString sOutput, sJudge[6], sCode[6], sRosJ;

		if (nType == 1) {	//NG
			nOutTray = gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][6]; sOutput = "NG Tray"; sJudge[0] = "N"; sCode[0] = gLot.sNGCode_I[nPNo-1][nTNo-1][nMNo-1][0];
		} else {			//Good
			nOutTray = gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][5]; sOutput = "OK Tray"; sJudge[0] = "G"; sCode[0] = "";
			
		}
		for(int i=1; i<6; i++) {
			sJudge[i] = "G"; sCode[i] = "";
			if (gLot.nJudge_I[nPNo-1][nTNo-1][nMNo-1][i] > 2) {
				sJudge[i] = "N"; sCode[i] = gLot.sNGCode_I[nPNo-1][nTNo-1][nMNo-1][i];
			}
		}
		sRosJ = "";
		if (gLot.nJudge_R[nPNo-1][nTNo-1][nMNo-1] == 2) sRosJ = "G";
		if (gLot.nJudge_R[nPNo-1][nTNo-1][nMNo-1] == 3) sRosJ = "N";
		if (gLot.nJudge_R[nPNo-1][nTNo-1][nMNo-1] == 4) sRosJ = "R";

		sData1.Format("%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%d,", nPNo, nTNo, nMNo, 
				gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][3], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2],
				gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][4], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], sOutput, nOutTray, gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][7]);

		sData2.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,", sJudge[0], sJudge[1], sCode[1], sJudge[2], sCode[2], sJudge[3], sCode[3], sJudge[4], sCode[4], sJudge[5], sCode[5]);

		//ROS Images,ROS Result,ROS Judge Time,ROS Response Time,???? ???? ????? ???,LoadMZID,InputCarrierID,OutputCarrierID,Repair,MN-Code\r\n");
		sData3.Format(",,,,,,,%d,%s,,,%s,,,,,%s", gLot.nImageCnt[nPNo-1][nTNo-1][nMNo-1], sRosJ, sJudge[0], sCode[0]);

		strSave.Format("%s,%s,,%s,%s,%s,%s,%s,%s,%s%s%s\r\n", strTime, m_sPCID, gLot.sBarCode[nPNo-1][nTNo-1][nMNo-1], strDate, strTime2, m_sMachineCode, strTime1, sLotID, sData1, sData2, sData3);

		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_MCCLog(CString sLog)
{
	CString strPath = gsCurrentDir + "\\LOG\\MCC";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, sTitle, strSave;
	strFile.Format("%s\\%04d%02d%02d.csv", strPath, time.wYear, time.wMonth, time.wDay);
	sTitle.Format("Time,Fun_No,Funtion,List_No,List_Text,Tack_Time\r\n");

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			CString strSave;
			if (file.GetLength() <= 0) {
				strSave.Format("%s%02d:%02d:%02d %03d,%s\r\n", sTitle, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);
			} else {
				strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);
			}

			file.SeekToEnd();	
			file.Write(strSave, strSave.GetLength());
			file.Close();
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_TackLog(CString sLog)
{
	CString strPath = gsCurrentDir + "\\LOG\\Tack";
	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, sTitle, strSave;
	strFile.Format("%s\\%04d%02d%02d.csv", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			CString strSave;
			strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.SeekToEnd();	
			file.Write(strSave, strSave.GetLength());
			file.Close();
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_LotResult(CString sLog)
{
	CString strPath = gsCurrentDir + "\\LOG\\LotResult";

	Create_Folder(strPath);

	CTime tNow = CTime::GetCurrentTime();
	CTime tLog = tNow - CTimeSpan(7 * 60 * 60);

	CString strFile, strTitle, strDate, strSave;
	strFile.Format("%s\\%04d%02d%02d.csv", strPath, tLog.GetYear(), tLog.GetMonth(), tLog.GetDay());

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	if (gData.nLanguage == 0) strTitle.Format("???,Lot Start,Lot End,Term,???,Lot ID,?????,?????,?????,?????,HREN(H),HREP(P),Spider(S),BA(B),Chip(C),MES(M)\r\n");
	else					  strTitle.Format("Date,Lot Start,Lot End,Term,No,Lot ID,Number of inputs,Number of good,Number of NG,Defect rate,HREN(H),HREP(P),Spider(S),BA(B),Chip(C),MES(M)\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strDate.Format("%02d/%02d", tNow.GetMonth(), tNow.GetDay());

		strSave.Format("%s,%s\r\n", strDate, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_MesAgentLog(CString sLog)
{
	g_csMesAgentLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\MESAgent";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d.csv", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csMesAgentLog.Unlock();
}

void CLogFile::Save_MesNgLog(CString sLog, int nPortIdx)
{
	CString strPath1 = "D:\\EVMS\\TP\\Log";
	CString strPath2 = "D:\\EVMS\\TP\\Backup";
	CString strPath3 = gsCurrentDir + "\\LOG\\MES_NG";

	Create_Folder(strPath1);
	Create_Folder(strPath2);
	Create_Folder(strPath3);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile1, strFile2, strFile3, strTitle, strSave;
	strFile1.Format("%s\\%s_%04d%02d%02d%02d_MESNG.csv", strPath1, gLot.sLotID[nPortIdx], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile2.Format("%s\\%s_%04d%02d%02d%02d_MESNG.csv", strPath2, gLot.sLotID[nPortIdx], time.wYear, time.wMonth, time.wDay, time.wHour);
	strFile3.Format("%s\\%04d%02d%02d.csv", strPath3, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (!file.Open(strFile1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	strTitle.Format("Date,Lot ID,Module ID,MES Judge,NG Code,NG Text\r\n");

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

		CopyFile(strFile1, strFile2, FALSE);	// Backup

	} catch (CFileException *pEx) {
		pEx->Delete();
	}

	if (!file.Open(strFile3, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	try{
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();
	}
	catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_DispatcherLog(CString sLog)
{
	g_csDispatcherLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\Dispatcher";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csDispatcherLog.Unlock();
}

void CLogFile::Save_OutTray(CString strLotID, CString strOut, int nPosX, int nPosY, int nMzNo, int nCarNo, int nLineNo, int nPickNo)
{
	if (nPosX < 1 || nPosY < 1 || nMzNo < 1 || nCarNo < 1 || nLineNo < 1 || nPickNo < 1) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strPath, strFile, strTitle, strSave;
	strPath.Format("%s\\LOG\\OutTray\\%04d-%02d-%02d", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strPath);

	strFile.Format("%s\\%s_%s.csv", strPath, strLotID, strOut);	// LotID, NG/GOOD

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	strTitle.Format("TRAY_X,TRAY_Y,MZ_NO,CARRIER_NO,LINE_NO,PICK_NO,JUDGE\r\n");
	/*
	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

		//????? (0:Empty, 1:Good, 2:NG)
		int nJudge = gData.InfoUnloadPick[nPickNo-1];
		strSave.Format("%d,%d,%d,%d,%d,%d,%d\r\n", nPosX, nPosY, nMzNo, nCarNo, nLineNo, nPickNo, nJudge);

		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}/*/
}

///////////////////////////////////////////////////////////////////////////////

void CLogFile::Save_TestLog(CString sLog)
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("Test\\%04d%02d%02d_000000_Test.csv", time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_LotLog()
{
/*
	CString sFileName, strFile, strCreDate, sCreFile, sTemp, sData, sInsResult, sBarResult;
	SYSTEMTIME time;
	GetLocalTime(&time);

	if (gLot.sLotID == "") gLot.sLotID = "LOT_ID_DEFAULT";
	strCreDate.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	strFile.Format("LOG/LotData/%04d/%02d/%02d/%s_%s.txt", time.wYear, time.wMonth, time.wDay, gLot.sLotID, strCreDate);
	sFileName = strFile;

	sCreFile.Format("%s\\LOG\\LotData\\%04d\\%02d\\%02d\\", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	MakeFolder(sCreFile);

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	sTemp.Format("LotID,%s,Start_Time,%s,End_Time,%s,Tray_Count,%02d,CM_Count,%04d,Tack,%0.7lf,\r\n\r\n", gLot.sLotID, gLot.sStartTime, gLot.sEndTime, gLot.nTrayCount, gLot.nCmCount, gLot.dTackTime);
	sData.Format("%sTray_No,Pocket_No,ID,Inspetion Result,ID Result,\r\n", sTemp);
	file.Write(sData, sData.GetLength());

	try {
		int	nCmCount = 0;
		for(int i=0; i<30; i++) {
			if (nCmCount > gLot.nCmCount) break;

			for(int j=0; j<42; j++){
				nCmCount++;
				if (nCmCount > gLot.nCmCount) break;

				file.SeekToEnd();

				sData.Format("%d,%d,%s,%s,%s,\r\n", i+1, j+1, gCM.sBarID[i][j], gCM.sJudge[i][j], gCM.sNGCode[i][j]);
				file.Write(sData, sData.GetLength());
			}
		}

		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
*/
}

void CLogFile::Save_DailyLot(CString sLog)
{
	g_csDailyLotLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\DailyLot";
	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave, strTitle;
	strFile.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) {
				strTitle.Format("Time \tLot_ID \tTotal \tGood \tNG \tRate \tSkip \tBar_NoRead \tRosRequest \tRosGood \tRosNg \tRosRepair \tRosTimeOut \tFiltering1 \tFiltering2 \tRateAvi \tRunTime \tTack\r\n");
				file.Write(strTitle, strTitle.GetLength());
			}

			strSave.Format("[%02d:%02d:%02d %03d] %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csDailyLotLog.Unlock();
}

void CLogFile::Save_ECMDailyLot(CString sLog)
{
	CString strFile, sTitle, strSave;

	SYSTEMTIME time;
	GetLocalTime(&time);

	strFile.Format("%s%s_%04d%02d%02d%02d_DailyLot.csv", ECM_LOG, gLot.sELotID, time.wYear, time.wMonth, time.wDay, time.wHour);

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) {
			sTitle.Format("Time,Lot_ID,Total,Good,NG,Rate,Skip,Bar_NoRead,RosRequest,RosGood,RosNg,RosRepair,RosTimeOut,Filtering1,Filtering2,RateAvi,RunTime,Tack\r\n");
			file.Write(sTitle, sTitle.GetLength());
		}

		strSave.Format("%02d:%02d:%02d %03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_LotLog(int nPortNo)
{
	CString sFileName, strFile, strCreDate, sCreFile, sTemp, sData, sInsResult, sBarResult, sJudge;
	SYSTEMTIME time;
	GetLocalTime(&time);

	if (gLot.sLotID[nPortNo-1] == "") gLot.sLotID[nPortNo-1] = "LOT_ID_DEFAULT";
	sCreFile.Format("%s\\LOG\\LotData\\%04d\\%02d\\%02d\\", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(sCreFile);

	strCreDate.Format("%04d%02d%02d_%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	strFile.Format("LOG/LotData/%04d/%02d/%02d/%s_%s.txt", time.wYear, time.wMonth, time.wDay, gLot.sLotID[nPortNo-1], strCreDate);
	sFileName = strFile;

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) return;

	sTemp.Format("LotID,%s,Start_Time,%s,End_Time,%s,Tray_Count,%02d,CM_Count,%04d,Tack,%0.7lf,\r\n\r\n", gLot.sLotID[nPortNo-1], gLot.sLLStartTime[nPortNo-1], gLot.sLLEndTime[nPortNo-1], gLot.nTrayCount[nPortNo-1] - 1, gLot.nCmCount[nPortNo-1], gLot.dLLTackTime[nPortNo-1]);
	sData.Format("%sTray_No,Pocket_No,ID,Inspetion Result,ID Result,\r\n", sTemp);
	file.Write(sData, sData.GetLength());

	try {
		int	nCmCount = 0;
		for (int i = 0; i < gLot.nTrayCount[nPortNo-1]-1; i++) {
			for (int j = 0; j < 40; j++) {
				if (gLot.nJudge_I[nPortNo-1][i][j][0] == 0) continue;

				file.SeekToEnd();
				sJudge = (gLot.nJudge_I[nPortNo-1][i][j][0] <= 2 ? "" : "N");
				sData.Format("%d,%d,%s,%s,%s,\r\n", i+1, j+1, gLot.sBarCode[nPortNo-1][i][j], sJudge, gLot.sNGCode_I[nPortNo-1][i][j][0]);
				file.Write(sData, sData.GetLength());
			}
		}
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}

void CLogFile::Save_OperatingRatio(CString sLog)	// ?????? ??? ??
{
	g_csOperatingRatioLog.Lock();

	CString strPath = gsCurrentDir + "\\LOG\\OperatingRatio";
	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile,strFile2, strSave, strTitle;
	strFile.Format("%s\\%04d%02d%02d.csv", strPath, time.wYear, time.wMonth, time.wDay);
	strFile2.Format("%s\\%04d%02d%02d.txt", strPath, time.wYear, time.wMonth, time.wDay);

	strTitle.Format("Time,???,Lot ID,Lot Start,Lot End,Cycle Time,LM(EA),Run Time,Stop Time,Error Time,Error Count,????,UPH,MTB\r\n");
	strSave.Format("[%02d:%02d:%02d %03d]%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();
			if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	if (file.Open(strFile2, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();
			if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csOperatingRatioLog.Unlock();
}


void CLogFile::Save_SeqLog(CString sLog)
{
	CString strPath = gsCurrentDir + "\\LOG\\Seq";

	Create_Folder(strPath);

	SYSTEMTIME time;
	GetLocalTime(&time);

	CString strFile, strSave;
	strFile.Format("%s\\%04d%02d%02d_Seq.csv", strPath, time.wYear, time.wMonth, time.wDay);

	g_csSeqLog.Lock();

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) 
	{
		try 
		{
			file.SeekToEnd();

			strSave.Format("[%02d:%02d:%02d %03d], %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} 
		catch (CFileException *pEx)
		{
			pEx->Delete();
		}
	}
	g_csSeqLog.Unlock();
}

///////////////////////////////////////////////////////////////////////////////

void CLogFile::Save_OutTrayGLog(int nPNo, int nTNo, int nMNo)
{
	CString sLotID, strFile, strTitle, strFolder, strSave, sRosJ;
	if (nPNo < 1 || nPNo > 6) return;
	if (nTNo < 1 || nTNo > 20) return;
	if (nMNo < 1 || nMNo > 40) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	strFolder.Format("%s\\LOG\\OutTray\\%04d-%02d-%02d\\", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strFolder);

	sLotID = gLot.sLotID[nPNo-1];
	strFile.Format("LOG/OutTray/%04d-%02d-%02d/%s_Good.csv", time.wYear, time.wMonth, time.wDay, sLotID);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) {
				strTitle.Format("LoadPort,LoadTray,LoadPos,Barcode,LoadPicker,LoadPickerNo,VisionStage,VisionStageNo,UnloadPicker,UnloadPickerNo,GoodTray,GoodPos,Judge,ROSJudge\r\n");
				file.Write(strTitle, strTitle.GetLength());
			}
			sRosJ = "";
			if (gLot.nJudge_R[nPNo-1][nTNo-1][nMNo-1] == 2) sRosJ = "G";

			strSave.Format("%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,G,%s\r\n",
				nPNo, nTNo, nMNo, gLot.sBarCode[nPNo-1][nTNo-1][nMNo-1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][3], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], 
				gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][4], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][5], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][7], sRosJ);

			file.Write(strSave, strSave.GetLength());
			file.Close();

			//PortNo(1~6),LoadTrayNo(1~8),LoadPorket(1~40),Barcode,LoadPickerNo(1,2),LoadPickerIndex(1~8),VisionStageNo(1~4),VisionStageIndex(1~8),
			//UnloadPickerNo(1,2),UnloadPickerIndex(1~8),Judge(N,G),GoodTrayNo(1~8),GoodTrayPorket(1~40),NGTrayNo(1~8),NGTrayPorket(1~40)
			strSave.Format("%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,G,%d,%d,-1,-1",
				nPNo, nTNo, nMNo, gLot.sBarCode[nPNo-1][nTNo-1][nMNo-1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][3], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], 
				gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][4], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][5], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][7]);
			g_objInspector.Set_HistoryReply(INSPECTOR_ALL, strSave);

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	Save_ECMOutPut(nPNo, nTNo, nMNo, 0);
}

void CLogFile::Save_OutTrayNLog(int nPNo, int nTNo, int nMNo)
{
	CString sLotID, strFile, strTitle, strFolder, strSave, sJurge, sJudge[5], sCode[5], sRosRepair, sNGCode, sNGCode20[3];
	if (nPNo < 1 || nPNo > 6) return;
	if (nTNo < 1 || nTNo > 16) return;
	if (nMNo < 1 || nMNo > 40) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	strFolder.Format("%s\\LOG\\OutTray\\%04d-%02d-%02d\\", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strFolder);

	sLotID = gLot.sLotID[nPNo-1];
	strFile.Format("LOG/OutTray/%04d-%02d-%02d/%s_NG.csv", time.wYear, time.wMonth, time.wDay, sLotID);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) {
				sNGCode20[0] = "";
				if (gData.bJahwa==FALSE) {
					for(int i=0; i<5; i++) {
						if (i==0) sNGCode20[1] = "B1";
						if (i==1) sNGCode20[1] = "AG";
						if (i==2) sNGCode20[1] = "T1";
						if (i==3) sNGCode20[1] = "TG";
						if (i==4) sNGCode20[1] = "T2";
						for(int j=0; j<10; j++) {
							sNGCode20[2].Format(",%sNGCode%02d", sNGCode20[1], j+1);
							sNGCode20[0] = sNGCode20[0] + sNGCode20[2];
						}
					}
				}
				
				strTitle.Format("LoadPort,LoadTray,LoadPos,Barcode,LoadPicker,LoadPickerNo,VisionStage,VisionStageNo,UnloadPicker,UnloadPickerNo,NGTray,NGPos,Judge,JudgeB1,DefectCodeB1,JudgeAG,DefectCodeAG,JudgeT1,DefectCodeT1,JudgeTG,DefectCodeTG,JudgeT2,DefectCodeT2,Repair,MN-Code%s\r\n", sNGCode20[0]);
				file.Write(strTitle, strTitle.GetLength());
			}

			for(int i=1; i<6; i++) {
				sJudge[i-1] = "G"; sCode[i-1] = "";
				if (gLot.nJudge_I[nPNo-1][nTNo-1][nMNo-1][i] > 2) {
					sJudge[i-1] = "N";
					sCode[i-1]  = gLot.sNGCode_I[nPNo-1][nTNo-1][nMNo-1][i];
				}
			}
			
			if (gLot.nJudge_R[nPNo-1][nTNo-1][nMNo-1] == 4) sRosRepair = "R"; else sRosRepair = "";
			sNGCode = gLot.sNGCode_I[nPNo-1][nTNo-1][nMNo-1][0];
			if (gLot.nMarginal[nPNo-1][nTNo-1][nMNo-1] > 0) sJurge = "Cosmetic NG"; else sJurge = "N";

			sNGCode20[0] = "";
			if (gData.bJahwa==FALSE) {
				for(int i=0; i<5; i++) {
					for(int j=0; j<10; j++) {
						sNGCode20[2].Format(",%s", gNG->sNGCode[nPNo-1][nTNo-1][nMNo-1][i][j]);
						sNGCode20[0] = sNGCode20[0] + sNGCode20[2];
					}
				}
			}

			strSave.Format("%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s%s\r\n",
				nPNo, nTNo, nMNo, gLot.sBarCode[nPNo-1][nTNo-1][nMNo-1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][3], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], 
				gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][4], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][6], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][7],
				sJurge, sJudge[0], sCode[0], sJudge[1], sCode[1], sJudge[2], sCode[2], sJudge[3], sCode[3], sJudge[4], sCode[4], sRosRepair, sNGCode, sNGCode20[0]);

			file.Write(strSave, strSave.GetLength());
			file.Close();

			//PortNo(1~6),LoadTrayNo(1~8),LoadPorket(1~40),Barcode,LoadPickerNo(1,2),LoadPickerIndex(1~8),VisionStageNo(1~4),VisionStageIndex(1~8),
			//UnloadPickerNo(1,2),UnloadPickerIndex(1~8),Judge(N,G),GoodTrayNo(1~8),GoodTrayPorket(1~40),NGTrayNo(1~8),NGTrayPorket(1~40)
			strSave.Format("%d,%d,%d,%s,%d,%d,%d,%d,%d,%d,N,-1,-1,%d,%d",
				nPNo, nTNo, nMNo, gLot.sBarCode[nPNo-1][nTNo-1][nMNo-1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][1], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][3], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], 
				gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][4], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][2], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][6], gLot.nHistory[nPNo-1][nTNo-1][nMNo-1][7]);
			g_objInspector.Set_HistoryReply(INSPECTOR_ALL, strSave);

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	Save_ECMOutPut(nPNo, nTNo, nMNo, 1);
}

void CLogFile::Save_SpcMccLog(CString sLog, CString sLotID)
{
	CString strFile, strTitle, strFolder, strSave;
	if (sLotID.GetLength() < 1) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	strFolder.Format("%s\\LOG\\MCC\\%04d\\%02d\\%02d\\", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strFolder);

	strFile.Format("LOG/MCC/%04d/%02d/%02d/%s.txt", time.wYear, time.wMonth, time.wDay, sLotID);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) {
				strTitle.Format("Time,,Seq No,Lot ID,Barcode,Port No,Tray No,Cm No,Cm Count,Seq Name,Seq No,Category,Text,Cycle,Time,ErrorTime\r\n");
				file.Write(strTitle, strTitle.GetLength());
			}
			strSave.Format("%02d:%02d:%02d.%03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_SpcMotionLog(CString sLog, CString sLotID)
{
	CString strFile, strTitle, strFolder, strSave;
	if (sLotID.GetLength() < 1) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	strFolder.Format("%s\\LOG\\Motion\\%04d\\%02d\\%02d\\", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strFolder);

	strFile.Format("LOG/Motion/%04d/%02d/%02d/%s.txt", time.wYear, time.wMonth, time.wDay, sLotID);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) {
				strTitle.Format("Time,Lot ID,Barcode,Port No,Tray No,Cm No,Cm Count,Category,Axis,Reference Value,Encoder Value\r\n");
				file.Write(strTitle, strTitle.GetLength());
			}

			strSave.Format("%02d:%02d:%02d.%03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_SpcErrorLog(CString sLog, CString sLotID)
{
	CString strFile, strTitle, strFolder, strSave;
	if (sLotID.GetLength() < 1) return;

	SYSTEMTIME time;
	GetLocalTime(&time);

	strFolder.Format("%s\\LOG\\Error\\%04d\\%02d\\%02d\\", gsCurrentDir, time.wYear, time.wMonth, time.wDay);
	Create_Folder(strFolder);

	strFile.Format("LOG/Error/%04d/%02d/%02d/%s.txt", time.wYear, time.wMonth, time.wDay, sLotID);

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone)) {
		try {
			file.SeekToEnd();

			if (file.GetLength() < 1) {
				strTitle.Format("Time,Lot ID,ErrorCode,Category,LotID,Barcode,Port No,Tray No,Cm No,Cm Count,Text,StartTime,EndTime,UseTime\r\n");
				file.Write(strTitle, strTitle.GetLength());
			}

			strSave.Format("%02d:%02d:%02d.%03d,%s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, sLog);

			file.Write(strSave, strSave.GetLength());
			file.Close();

		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
}

void CLogFile::Save_StdMotionLog(CString sLotID, CString sType, int nZone, int nCase, int nValue, CString sZone, CString sMsg)
{
	g_csStdMotionLog.Lock();

	int nSeqNo, nPortNo;
	CString strLotId, strPath, strFile, strKey, strCycle, strTitle, strLog, strSave, sData;

	strLotId = sLotID; nSeqNo = nPortNo = 0;
	if (strLotId == "") strLotId = gData.sLotID_Start;
	for (int i=0; i<6; i++) {
		if (strLotId == gLot.sLotID[i]) {
			nSeqNo = gData.nTotLotNo[i];
			nPortNo = i+1;
			if (nSeqNo == 0) nSeqNo = gData.nStdLotNo + 1;
			break;
		}
	}
	if (nSeqNo == 0) {
		for (int i=0; i<6; i++) {
			if (strLotId == sLogLotID[i]) { nSeqNo = nLotSeqNo[i]; break; }
		}
	}
	if (strLotId == "" || nSeqNo == 0) { g_csStdMotionLog.Unlock(); return; }
	
	SYSTEMTIME time;
	GetLocalTime(&time);

	// ????? : LotID_????????????_??????_Normal_#??????_PC???_????_????.csv => Lot Start?? ????
	gData.sStdMotionFile.Format("%s_%04d%02d%02d%02d_AVI_Normal_#%04d_%s_%s_%04d.csv",
						strLotId, time.wYear, time.wMonth, time.wDay, time.wHour, gData.nStdEqNo, gsComputerName, gData.sRecipeName, nSeqNo);
	strFile.Format("%s%s", ECM_ME_LOG, gData.sStdMotionFile);

	strKey.Format("[CH_DV]%s%03d%03d[1]", sType, nZone, nCase);
	if (sType == "Y" && nValue == 1) strCycle = "";	// ?????? (????? ????)
	else strCycle.Format("%s%03d%03d", sType, nZone, nCase-1);	// ?????? ???

	int nNo = sMsg.Find(",");
	if (nNo > 0) sData = sMsg.Left(nNo);
	else		 sData = sMsg;
	strLog.Format("%s,%d,%s,%s,%s", strKey, nValue, sZone, strCycle, sData);
	strTitle = "Time,Key,Value,Index,CycleIndex,Note\r\n";

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();
			if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());
			strSave.Format("%04d%02d%02d%02d%02d%02d.%03d,%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);
			file.Write(strSave, strSave.GetLength());
			file.Close();
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}

	if (nPortNo >= 1 && nPortNo <= 6) {
		sLogLotID[nPortNo-1] = strLotId;
		nLotSeqNo[nPortNo-1] = nSeqNo;
	}

	g_csStdMotionLog.Unlock();
}

void CLogFile::Clear_LogData()
{
	for(int i=0; i<6; i++) {
		sLogLotID[i] = "";
		nLotSeqNo[i] = 0;
	}
}

void CLogFile::Save_EfficiencyLog(CString sLotID, CString sStatus, CString strZone, int nCode, CString sNote)
{
	g_csEfficiencyLog.Lock();

	int nSeqNo, nPortNo;
	CString strFile, strTitle, strLog, strSave, strLotId;

	strLotId = sLotID; nSeqNo = nPortNo = 0;
	if (strLotId == "") strLotId = gData.sLotID_Start;
	for (int i=0; i<6; i++) {
		if (strLotId == gLot.sLotID[i]) {
			nSeqNo = gData.nTotLotNo[i];
			nPortNo = i+1;
			if (nSeqNo == 0) nSeqNo= gData.nStdLotNo + 1;
			break;
		}
	}
	if (nSeqNo == 0) {
		for (int i=0; i<6; i++) {
			if (strLotId == sLogLotID[i]) { nSeqNo = nLotSeqNo[i]; break; }
		}
	}
	if (strLotId == "" || nSeqNo == 0) { g_csEfficiencyLog.Unlock(); return; }

	SYSTEMTIME time;
	GetLocalTime(&time);

	//????? : LotID_????????????_??????_Efficiency_#??????_PC???_????_????.csv
	gData.sEfficiencyFile.Format("%s_%04d%02d%02d%02d_AVI_Efficiency_#%04d_%s_%s_%04d.csv",
						strLotId, time.wYear, time.wMonth, time.wDay, time.wHour, gData.nStdEqNo, gsComputerName, gData.sRecipeName, nSeqNo);
	strFile.Format("%s%s", ECM_ME_LOG, gData.sEfficiencyFile);

	strLog.Format("%s-%s-%04d,%s", sStatus, strZone, nCode, sNote);
	strTitle = "Time,Code,Comment\r\n";

	CFile file;
	if (file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) {
		try {
			file.SeekToEnd();
			if (file.GetLength() < 1) file.Write(strTitle, strTitle.GetLength());
			strSave.Format("%04d-%02d-%02d-%02d-%02d-%02d.%03d,%s\r\n",
				time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, strLog);
			file.Write(strSave, strSave.GetLength());
			file.Close();
		} catch (CFileException *pEx) {
			pEx->Delete();
		}
	}
	g_csEfficiencyLog.Unlock();
}

void CLogFile::Get_ZoneMsg(int nFun, int nId, CString &sLotID, int &nPortNo, int &nSeqTotal, CString &strFun, CString &strMsg, CString &sType)
{
	nPortNo = nSeqTotal = 0; sType = "X";	//X:????,????? ????, M:???©£???, B:??????©£?, Y:Unit Tack
	switch (nFun) {
	case 1:
		strFun = "Elevator_1"; nSeqTotal = 4;
		switch (nId) {
		case  1: sType = "X"; strMsg = "High Sensor On First Move,start"; break;
		case  2: sType = "X"; strMsg = "High Sensor Off Move,ing"; break;
		case  3: sType = "X"; strMsg = "High Sensor On Last Move,ing"; break;
		case  4: sType = "X"; strMsg = "Elevator Post Position Move,end"; break;
		}
		break;
	case 2:
		strFun = "Elevator_2"; nSeqTotal = 4;
		switch (nId) {
		case  1: sType = "X"; strMsg = "High Sensor On First Move,start"; break;
		case  2: sType = "X"; strMsg = "High Sensor Off Move,ing"; break;
		case  3: sType = "X"; strMsg = "High Sensor On Last Move,ing"; break;
		case  4: sType = "X"; strMsg = "Elevator Post Position Move,end"; break;
		}
		break;
	case 3:
		strFun = "Elevator_3"; nSeqTotal = 4;
		switch (nId) {
		case  1: sType = "X"; strMsg = "High Sensor On First Move,start"; break;
		case  2: sType = "X"; strMsg = "High Sensor Off Move,ing"; break;
		case  3: sType = "X"; strMsg = "High Sensor On Last Move,ing"; break;
		case  4: sType = "X"; strMsg = "Elevator Post Position Move,end"; break;
		}
		break;
	case 4:
		strFun = "Elevator_4"; nSeqTotal = 4;
		switch (nId) {
		case  1: sType = "X"; strMsg = "High Sensor On First Move,start"; break;
		case  2: sType = "X"; strMsg = "High Sensor Off Move,ing"; break;
		case  3: sType = "X"; strMsg = "High Sensor On Last Move,ing"; break;
		case  4: sType = "X"; strMsg = "Elevator Post Position Move,end"; break;
		}
		break;
	case 5:
		strFun = "Elevator_5"; nSeqTotal = 4;
		switch (nId) {
		case  1: sType = "X"; strMsg = "High Sensor On First Move,start"; break;
		case  2: sType = "X"; strMsg = "High Sensor Off Move,ing"; break;
		case  3: sType = "X"; strMsg = "High Sensor On Last Move,ing"; break;
		case  4: sType = "X"; strMsg = "Elevator Post Position Move,end"; break;
		}
		break;
	case 6:
		strFun = "Elevator_6"; nSeqTotal = 4;
		switch (nId) {
		case  1: sType = "X"; strMsg = "High Sensor On First Move,start"; break;
		case  2: sType = "X"; strMsg = "High Sensor Off Move,ing"; break;
		case  3: sType = "X"; strMsg = "High Sensor On Last Move,ing"; break;
		case  4: sType = "X"; strMsg = "Elevator Post Position Move,end"; break;
		}
		break;
	case 7:
		strFun = "Elevator_7"; nSeqTotal = 4;
		switch (nId) {
		case  1: sType = "X"; strMsg = "High Sensor On First Move,start"; break;
		case  2: sType = "X"; strMsg = "High Sensor Off Move,ing"; break;
		case  3: sType = "X"; strMsg = "High Sensor On Last Move,ing"; break;
		case  4: sType = "X"; strMsg = "Elevator Post Position Move,end"; break;
		}
		break;
	case 8:
		strFun = "Transfer_1"; nSeqTotal = 39;
		switch (nId) {
		case  1: sType = "X"; strMsg = "X1 Axis Move to Work Position,start"; break;
		case  2: sType = "B"; strMsg = "X1 Axis Wait for Work,ing"; break;
		case  3: sType = "X"; strMsg = "Z1 Axis Move to Down Position,ing"; break;
		case  4: sType = "X"; strMsg = "Grib Close,ing"; break;
		case  5: sType = "X"; strMsg = "Z1 Axis Move to Ready Up Position,ing"; break;
		case  6: sType = "B"; strMsg = "X1 Axis Wait for Load1,ing"; break;
		case  7: sType = "X"; strMsg = "Elevator1 Clamp Off,ing"; break;
		case  8: sType = "B"; strMsg = "X1 Axis Wait for Load1,ing"; break;
		case  9: sType = "X"; strMsg = "Z1 Axis Move to Load1 Down Position,ing"; break;
		case 10: sType = "X"; strMsg = "Grib Close,ing"; break;
		case 11: sType = "X"; strMsg = "Z1 Axis Move to Ready Up Position,ing"; break;
		case 12: sType = "B"; strMsg = "X1 Axis Wait for Load2,ing"; break;
		case 13: sType = "X"; strMsg = "Elevator2 Clamp Off,ing"; break;
		case 14: sType = "B"; strMsg = "X1 Axis Wait for Load2,ing"; break;
		case 15: sType = "X"; strMsg = "Z1 Axis Move to Load2 Down Position,ing"; break;
		case 16: sType = "X"; strMsg = "Grib Close,ing"; break;
		case 17: sType = "X"; strMsg = "Z1 Axis Move to Ready Up Position,ing"; break;
		case 18: sType = "B"; strMsg = "X1 Axis Wait for Stage,ing"; break;
		case 19: sType = "X"; strMsg = "X1 Axis Move to Stage Position,ing"; break;
		case 20: sType = "X"; strMsg = "Z1 Axis Move to Stage Down Position,ing"; break;
		case 21: sType = "X"; strMsg = "Grib Close,ing"; break;
		case 22: sType = "X"; strMsg = "Z1 Axis Move to Ready Up Position,ing"; break;
		case 23: sType = "B"; strMsg = "X1 Axis Wait for Empty-NG,ing"; break;
		case 24: sType = "B"; strMsg = "X1 Axis Wait for Empty-NG,ing"; break;
		case 25: sType = "X"; strMsg = "X1 Axis Move to Load2 Position,ing"; break;
		case 26: sType = "X"; strMsg = "X1 Axis Move to Empty-NG Position,ing"; break;
		case 27: sType = "B"; strMsg = "X1 Axis Wait for Empty-NG Elveator,ing"; break;
		case 28: sType = "X"; strMsg = "Z1 Axis Move to Empty-NG Down Position,ing"; break;
		case 29: sType = "X"; strMsg = "Grib Open,ing"; break;
		case 30: sType = "X"; strMsg = "Z1 Axis Move to Ready Up Position,ing"; break;
		case 31: sType = "B"; strMsg = "X1 Axis Wait for Empty-Good,ing"; break;
		case 32: sType = "B"; strMsg = "X1 Axis Wait for Empty-Good,ing"; break;
		case 33: sType = "X"; strMsg = "X1 Axis Move to Load2 Position,ing"; break;
		case 34: sType = "X"; strMsg = "X1 Axis Move to Empty-Good Position,ing"; break;
		case 35: sType = "B"; strMsg = "X1 Axis Wait for Empty-Good Elveator,ing"; break;
		case 36: sType = "X"; strMsg = "Z1 Axis Move to Empty-Good Down Position,ing"; break;
		case 37: sType = "X"; strMsg = "Grib Open,ing"; break;
		case 38: sType = "X"; strMsg = "Z1 Axis Move to Ready Up Position,ing"; break;
		case 39: sType = "X"; strMsg = "Seq End,end"; break;
		}
		break;
	case 9:
		strFun = "Transfer_2"; nSeqTotal = 43;
		switch (nId) {
		case  1: sType = "X"; strMsg = "X2 Axis Move to Work-Up Position,start"; break;
		case  2: sType = "B"; strMsg = "X2 Axis Wait for Empty-NG,ing"; break;
		case  3: sType = "X"; strMsg = "Z2 Axis Move to Empty-NG Position,ing"; break;
		case  4: sType = "X"; strMsg = "Grib Close,ing"; break;
		case  5: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case  6: sType = "X"; strMsg = "Elevator3 Clamp Off,ing"; break;
		case  7: sType = "B"; strMsg = "X2 Axis Wait for Empty-Good,ing"; break;
		case  8: sType = "X"; strMsg = "Z2 Axis Move to Empty-Good Position,ing"; break;
		case  9: sType = "X"; strMsg = "Grib Close,ing"; break;
		case 10: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case 11: sType = "X"; strMsg = "Elevator4 Clamp Off,ing"; break;
		case 12: sType = "B"; strMsg = "X2 Axis Wait for Buffer-NG,ing"; break;
		case 13: sType = "X"; strMsg = "Z2 Axis Move to Buffer-NG Position,ing"; break;
		case 14: sType = "X"; strMsg = "Grib Close,ing"; break;
		case 15: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case 16: sType = "X"; strMsg = "Elevator5 Clamp Off,ing"; break;
		case 17: sType = "B"; strMsg = "X2 Axis Wait for NG-Stage,ing"; break;
		case 18: sType = "X"; strMsg = "Z2 Axis Move to NG-Stage Position,ing"; break;
		case 19: sType = "X"; strMsg = "Grib Close,ing"; break;
		case 20: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case 21: sType = "B"; strMsg = "X2 Axis Wait for Good-Stage,ing"; break;
		case 22: sType = "X"; strMsg = "Z2 Axis Move to Good-Stage Position,ing"; break;
		case 23: sType = "X"; strMsg = "Grib Close,ing"; break;
		case 24: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case 25: sType = "B"; strMsg = "X2 Axis Wait for Work,ing"; break;
		case 26: sType = "X"; strMsg = "X2 Axis Move to Work-Down Position,ing"; break;
		case 27: sType = "B"; strMsg = "X2 Axis Wait for Buffer-NG,ing"; break;
		case 28: sType = "X"; strMsg = "Z2 Axis Move to Buffer-NG Position,ing"; break;
		case 29: sType = "X"; strMsg = "Grib Open,ing"; break;
		case 30: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case 31: sType = "B"; strMsg = "X2 Axis Wait for Unload,ing"; break;
		case 32: sType = "X"; strMsg = "Z2 Axis Move to Unload Position,ing"; break;
		case 33: sType = "X"; strMsg = "Grib Open,ing"; break;
		case 34: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case 35: sType = "B"; strMsg = "X2 Axis Wait for NG-Stage,ing"; break;
		case 36: sType = "X"; strMsg = "Z2 Axis Move to NG-Stage Position,ing"; break;
		case 37: sType = "X"; strMsg = "Grib Open,ing"; break;
		case 38: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case 39: sType = "B"; strMsg = "X2 Axis Wait for Good-Stage,ing"; break;
		case 40: sType = "X"; strMsg = "Z2 Axis Move to Good-Stage Position,ing"; break;
		case 41: sType = "X"; strMsg = "Grib Open,ing"; break;
		case 42: sType = "X"; strMsg = "Z2 Axis Move to Ready Up Position,ing"; break;
		case 43: sType = "X"; strMsg = "Seq End,end"; break;
		}
		break;
	case 10:
		strFun = "LoadStage_1"; nSeqTotal = 19;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Master In,start"; break;
		case  2: sType = "X"; strMsg = "Slave In,ing"; break;
		case  3: sType = "B"; strMsg = "Align Wait,ing"; break;
		case  4: sType = "X"; strMsg = "Y1 Axis Move to Align1 Position,ing"; break;
		case  5: sType = "M"; strMsg = "Y1 Axis Align1 Scan Complete,ing"; break;
		case  6: sType = "X"; strMsg = "Y1 Axis Move to Align2 Position,ing"; break;
		case  7: sType = "M"; strMsg = "Y1 Axis Align2 Scan Complete,ing"; break;
		case  8: sType = "X"; strMsg = "Y1 Axis Move to Align3 Position,ing"; break;
		case  9: sType = "M"; strMsg = "Y1 Axis Align3 Scan Done,ing"; break;
		case 10: sType = "B"; strMsg = "Y1 Axis Move to Wait Position,ing"; break;
		case 11: sType = "X"; strMsg = "Y1 Axis Move to Unload Position,ing"; break;
		case 12: sType = "B"; strMsg = "Wait for Load Picker Work,ing"; break;
		case 13: sType = "X"; strMsg = "Y1 Stage Down,ing"; break;
		case 14: sType = "X"; strMsg = "Y1 Axis Move to Load Position,ing"; break;
		case 15: sType = "B"; strMsg = "Wait for Align,ing"; break;
		case 16: sType = "X"; strMsg = "Y1 Stage Up,ing"; break;
		case 17: sType = "X"; strMsg = "Slave Out,ing"; break;
		case 18: sType = "X"; strMsg = "Master Out,ing"; break;
		case 19: sType = "X"; strMsg = "Seq End,end"; break;
		}
		break;
	case 11:
		strFun = "LoadStage_2"; nSeqTotal = 19;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Master In,start"; break;
		case  2: sType = "X"; strMsg = "Slave In,ing"; break;
		case  3: sType = "B"; strMsg = "Align Wait,ing"; break;
		case  4: sType = "X"; strMsg = "Y2 Axis Move to Align1 Position,ing"; break;
		case  5: sType = "M"; strMsg = "Y2 Axis Align1 Scan Complete,ing"; break;
		case  6: sType = "X"; strMsg = "Y2 Axis Move to Align2 Position,ing"; break;
		case  7: sType = "M"; strMsg = "Y2 Axis Align2 Scan Complete,ing"; break;
		case  8: sType = "X"; strMsg = "Y2 Axis Move to Align3 Position,ing"; break;
		case  9: sType = "M"; strMsg = "Y2 Axis Align3 Scan Done,ing"; break;
		case 10: sType = "B"; strMsg = "Y2 Axis Move to Wait Position,ing"; break;
		case 11: sType = "X"; strMsg = "Y2 Axis Move to Unload Position,ing"; break;
		case 12: sType = "B"; strMsg = "Wait for Load Picker Work,ing"; break;
		case 13: sType = "X"; strMsg = "Y2 Stage Down,ing"; break;
		case 14: sType = "X"; strMsg = "Y2 Axis Move to Load Position,ing"; break;
		case 15: sType = "B"; strMsg = "Wait for Align,ing"; break;
		case 16: sType = "X"; strMsg = "Y2 Stage Up,ing"; break;
		case 17: sType = "X"; strMsg = "Slave Out,ing"; break;
		case 18: sType = "X"; strMsg = "Master Out,ing"; break;
		case 19: sType = "X"; strMsg = "Seq End,end"; break;
		}
		break;
	case 12:
		strFun = "Load_Picker_1"; nSeqTotal = 32;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Load Stage Y Axis Move to 1 Position,start"; break;
		case  2: sType = "X"; strMsg = "Load Picker 1-4 Down,ing"; break;
		case  3: sType = "X"; strMsg = "Load Picker Z Axis Move to Down Position,ing"; break;
		case  4: sType = "X"; strMsg = "Load Picker 1-4 Close,ing"; break;
		case  5: sType = "X"; strMsg = "Load Picker 1-4 Up,ing"; break;
		case  6: sType = "B"; strMsg = "Load Picker X Axis Wait,ing"; break;
		case  7: sType = "X"; strMsg = "Load Picker X Axis Move to 5 Position,ing"; break;
		case  8: sType = "X"; strMsg = "Load Picker Z Axis Move to Down Position,ing"; break;
		case  9: sType = "X"; strMsg = "Load Picker 5-8 Close,ing"; break;
		case 10: sType = "X"; strMsg = "Load Picker 5-8 Up,ing"; break;
		case 11: sType = "B"; strMsg = "Move Wait to BTM,ing"; break;
		case 12: sType = "X"; strMsg = "BTM Angle Y Move Postion,ing"; break;
		case 13: sType = "X"; strMsg = "BTM Light-Focus Move Postion,ing"; break;
		case 14: sType = "X"; strMsg = "BTM Pitch Move,ing"; break;
		case 15: sType = "M"; strMsg = "BTM Pitch Scan Complete,ing"; break;
		case 16: sType = "X"; strMsg = "BTM Angle Light-Focus Move Postion,ing"; break;
		case 17: sType = "X"; strMsg = "BTM Angle Y Move Position,ing"; break;
		case 18: sType = "X"; strMsg = "BTM Angle Pitch Move,ing"; break;
		case 19: sType = "M"; strMsg = "BTM Angle Pitch Scan Complete,ing"; break;
		case 20: sType = "B"; strMsg = "Move Wait to Align,ing"; break;
		case 21: sType = "X"; strMsg = "Load Picker X Axis Move to Align Position,ing"; break;
		case 22: sType = "B"; strMsg = "Move Wait to Inspection Stage,ing"; break;
		case 23: sType = "X"; strMsg = "Load Picker Down,ing"; break;
		case 24: sType = "X"; strMsg = "Load Picker Z Axis Down Position,ing"; break;
		case 25: sType = "X"; strMsg = "Load Picker Open,ing"; break;
		case 26: sType = "X"; strMsg = "Load Picker Up,ing"; break;
		case 27: sType = "X"; strMsg = "Align Master In,ing"; break;
		case 28: sType = "X"; strMsg = "Align Slave In,ing"; break;
		case 29: sType = "X"; strMsg = "Align Slave Out,ing"; break;
		case 30: sType = "X"; strMsg = "Align Master Out,ing"; break;
		case 31: sType = "X"; strMsg = "Load Picker Y Axis Ready Position,ing"; break;
		case 32: sType = "X"; strMsg = "Load Picker X Axis Load Position,end"; break;
		}
		break;
	case 13:
		strFun = "Load_Picker_2"; nSeqTotal = 32;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Load Stage Y Axis Move to 1 Position,start"; break;
		case  2: sType = "X"; strMsg = "Load Picker 1-4 Down,ing"; break;
		case  3: sType = "X"; strMsg = "Load Picker Z Axis Move to Down Position,ing"; break;
		case  4: sType = "X"; strMsg = "Load Picker 1-4 Close,ing"; break;
		case  5: sType = "X"; strMsg = "Load Picker 1-4 Up,ing"; break;
		case  6: sType = "B"; strMsg = "Load Picker X Axis Wait,ing"; break;
		case  7: sType = "X"; strMsg = "Load Picker X Axis Move to 5 Position,ing"; break;
		case  8: sType = "X"; strMsg = "Load Picker Z Axis Move to Down Position,ing"; break;
		case  9: sType = "X"; strMsg = "Load Picker 5-8 Close,ing"; break;
		case 10: sType = "X"; strMsg = "Load Picker 5-8 Up,ing"; break;
		case 11: sType = "B"; strMsg = "Move Wait to BTM,ing"; break;
		case 12: sType = "X"; strMsg = "BTM Angle Y Move Postion,ing"; break;
		case 13: sType = "X"; strMsg = "BTM Light-Focus Move Postion,ing"; break;
		case 14: sType = "X"; strMsg = "BTM Pitch Move,ing"; break;
		case 15: sType = "M"; strMsg = "BTM Pitch Scan Complete,ing"; break;
		case 16: sType = "X"; strMsg = "BTM Angle Light-Focus Move Postion,ing"; break;
		case 17: sType = "X"; strMsg = "BTM Angle Y Move Position,ing"; break;
		case 18: sType = "X"; strMsg = "BTM Angle Pitch Move,ing"; break;
		case 19: sType = "M"; strMsg = "BTM Angle Pitch Scan Complete,ing"; break;
		case 20: sType = "B"; strMsg = "Move Wait to Align,ing"; break;
		case 21: sType = "X"; strMsg = "Load Picker X Axis Move to Align Position,ing"; break;
		case 22: sType = "B"; strMsg = "Move Wait to Inspection Stage,ing"; break;
		case 23: sType = "X"; strMsg = "Load Picker Down,ing"; break;
		case 24: sType = "X"; strMsg = "Load Picker Z Axis Down Position,ing"; break;
		case 25: sType = "X"; strMsg = "Load Picker Open,ing"; break;
		case 26: sType = "X"; strMsg = "Load Picker Up,ing"; break;
		case 27: sType = "X"; strMsg = "Align Master In,ing"; break;
		case 28: sType = "X"; strMsg = "Align Slave In,ing"; break;
		case 29: sType = "X"; strMsg = "Align Slave Out,ing"; break;
		case 30: sType = "X"; strMsg = "Align Master Out,ing"; break;
		case 31: sType = "X"; strMsg = "Load Picker Y Axis Ready Position,ing"; break;
		case 32: sType = "X"; strMsg = "Load Picker X Axis Load Position,end"; break;
		}
		break;
	case 14:
		strFun = "Inspect_Stage_1"; nSeqTotal = 28;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Stage 1 90 Degree 0 True & Degree 90 FALSE"; break;
		case  2: sType = "X"; strMsg = "Inspect Stage Move to Top1 or Align"; break;
		case  3: sType = "X"; strMsg = "Top1 Z focus Move or Move to Top1"; break;
		case  4: sType = "B"; strMsg = "Information Exchange"; break;
		case  5: sType = "B"; strMsg = "Wait for Top1 Scan,ing"; break;
		case  6: sType = "X"; strMsg = "Inspect Stage 1 Pitch Move"; break;
		case  7: sType = "B"; strMsg = "Set Load Complete T1"; break;
		case  8: sType = "M"; strMsg = "T1 Scan Complete"; break;
		case  9: sType = "B"; strMsg = "Top1 Vision Z Move Done"; break;
		case  10: sType = "X"; strMsg = "Inspect Stage 1 and Top1 Z move"; break;			
		case  11: sType = "B"; strMsg = "Set Load Complete TG"; break;
		case  12: sType = "M"; strMsg = "TG Scan Complete"; break;
		case  13: sType = "B"; strMsg = "Wait for front stage move to Buffer Pos"; break;
		case  14: sType = "X"; strMsg = "Stage 1 X Move to Top2 and Top2 Z focus move"; break;
		case  15: sType = "B"; strMsg = "Information Exchange"; break;
		case  16: sType = "X"; strMsg = "Stage 1 X Pitch Move and Top2 Z focus Move"; break;
		case  17: sType = "B"; strMsg = "Set Load Complete T2"; break;
		case  18: sType = "M"; strMsg = "T2 Scan Done"; break;
		case  19: sType = "B"; strMsg = "Wait Interlock buffer Pos"; break;
		case  20: sType = "B"; strMsg = "Wait Interlock until front stage move to unload"; break;
		case  21: sType = "X"; strMsg = "Inspect Stage 1 Move to Unload and deg 0"; break;
		case  22: sType = "B"; strMsg = "Information exchange"; break;
		case  23: sType = "X"; strMsg = "Stage X1 Move to buffer pos"; break;
		case  24: sType = "B"; strMsg = "Information exchange"; break;
		case  25: sType = "B"; strMsg = "wait for ROS Start"; break;
		case  26: sType = "B"; strMsg = "Wait Done ROS"; break;
		case  31: sType = "X"; strMsg = "Stage1 Down"; break;	
		case  32: sType = ""; strMsg = ""; break;
		case  33: sType = ""; strMsg = ""; break;
		case  34: sType = ""; strMsg = ""; break;
		case  35: sType = ""; strMsg = ""; break;
		case  36: sType = ""; strMsg = ""; break;
		case  37: sType = ""; strMsg = ""; break;
		case  38: sType = ""; strMsg = ""; break;
		case  39: sType = ""; strMsg = ""; break;
		case  40: sType = ""; strMsg = ""; break;
		case  41: sType = ""; strMsg = ""; break;
		case  42: sType = ""; strMsg = ""; break;
		case  43: sType = ""; strMsg = ""; break;
		case  44: sType = ""; strMsg = ""; break;
		case  45: sType = ""; strMsg = ""; break;
		case  46: sType = ""; strMsg = ""; break;
		case  47: sType = ""; strMsg = ""; break;
		case  48: sType = ""; strMsg = ""; break;
		case  49: sType = ""; strMsg = ""; break;
		case  50: sType = ""; strMsg = ""; break;
		case  51: sType = ""; strMsg = ""; break;
		case  52: sType = ""; strMsg = ""; break;
		case  53: sType = ""; strMsg = ""; break;
		case  54: sType = ""; strMsg = ""; break;
		case  55: sType = ""; strMsg = ""; break;
		case  56: sType = ""; strMsg = ""; break;
		case  57: sType = ""; strMsg = ""; break;
		case  58: sType = ""; strMsg = ""; break;
		case  59: sType = ""; strMsg = ""; break;
		case  60: sType = ""; strMsg = ""; break;
		case  61: sType = ""; strMsg = ""; break;
		case  62: sType = ""; strMsg = ""; break;
		case  63: sType = ""; strMsg = ""; break;
		case  64: sType = ""; strMsg = ""; break;
		case  65: sType = ""; strMsg = ""; break;
		case  66: sType = ""; strMsg = ""; break;
		case  67: sType = ""; strMsg = ""; break;
		case  68: sType = ""; strMsg = ""; break;
		case  69: sType = ""; strMsg = ""; break;
		
		
		
		
		}
		break;
	case 15:
		strFun = "Inspect_Stage_2"; nSeqTotal = 28;
		switch (nId) {
		case  1: sType = "X"; strMsg = "X2 Axis Move To Top1 Position,start"; break;
		case  2: sType = "B"; strMsg = "Wait for Top1 Scan,ing"; break;
		case  3: sType = "X"; strMsg = "X2 Axis Move To Top1 Pitch,ing"; break;
		case  4: sType = "M"; strMsg = "X2 Top1 Scan Complete,ing"; break;
		case  5: sType = "B"; strMsg = "Wait for Top1 Angle Scan,ing"; break;
		case  6: sType = "X"; strMsg = "X2 Axis Move To Top1 Angle Pitch,ing"; break;
		case  7: sType = "M"; strMsg = "X2 Top1 Angle Scan Complete,ing"; break;
		case  8: sType = "B"; strMsg = "Wait for Move Top2,ing"; break;
		case  9: sType = "X"; strMsg = "X2 Axis Move To Top2 Position,ing"; break;
		case 10: sType = "B"; strMsg = "Wait for Top2 Scan,ing"; break;
		case 11: sType = "X"; strMsg = "X2 Axis Move To Top2 Pitch,ing"; break;
		case 12: sType = "M"; strMsg = "X2 Top2 Scan Complete,ing"; break;
		case 13: sType = "B"; strMsg = "Wait for Move Buffer,ing"; break;
		case 14: sType = "X"; strMsg = "X2 Axis Move To Buffer Position,ing"; break;
		case 15: sType = "B"; strMsg = "Wait for Move Unload,ing"; break;
		case 16: sType = "X"; strMsg = "X2 Axis Move To Unload Position,ing"; break;
		case 17: sType = "B"; strMsg = "Wait for Work Unload_Picker,ing"; break;
		case 18: sType = "X"; strMsg = "X2 Stage Down,ing"; break;
		case 19: sType = "X"; strMsg = "X2 Stage Out,ing"; break;
		case 20: sType = "B"; strMsg = "Wait for Move Down-Top2,ing"; break;
		case 21: sType = "X"; strMsg = "X2 Axis Move Back Top2 Position,ing"; break;
		case 22: sType = "B"; strMsg = "Wait for Move Down-Top1,ing"; break;
		case 23: sType = "X"; strMsg = "X2 Axis Move Back Top1 Position,ing"; break;
		case 24: sType = "B"; strMsg = "Wait for Move Down-Align,ing"; break;
		case 25: sType = "X"; strMsg = "X2 Axis Move Back Align Position,ing"; break;
		case 26: sType = "B"; strMsg = "Wait for Stage In,ing"; break;
		case 27: sType = "X"; strMsg = "X2 Stage In,ing"; break;
		case 28: sType = "X"; strMsg = "X2 Stage Up,end"; break;
		}
		break;
	case 16:
		strFun = "Inspect_Stage_3"; nSeqTotal = 28;
		switch (nId) {
		case  1: sType = "X"; strMsg = "X3 Axis Move To Top1 Position,start"; break;
		case  2: sType = "B"; strMsg = "Wait for Top1 Scan,ing"; break;
		case  3: sType = "X"; strMsg = "X3 Axis Move To Top1 Pitch,ing"; break;
		case  4: sType = "M"; strMsg = "X3 Top1 Scan Complete,ing"; break;
		case  5: sType = "B"; strMsg = "Wait for Top1 Angle Scan,ing"; break;
		case  6: sType = "X"; strMsg = "X3 Axis Move To Top1 Angle Pitch,ing"; break;
		case  7: sType = "M"; strMsg = "X3 Top1 Angle Scan Complete,ing"; break;
		case  8: sType = "B"; strMsg = "Wait for Move Top2,ing"; break;
		case  9: sType = "X"; strMsg = "X3 Axis Move To Top2 Position,ing"; break;
		case 10: sType = "B"; strMsg = "Wait for Top2 Scan,ing"; break;
		case 11: sType = "X"; strMsg = "X3 Axis Move To Top2 Pitch,ing"; break;
		case 12: sType = "M"; strMsg = "X3 Top2 Scan Complete,ing"; break;
		case 13: sType = "B"; strMsg = "Wait for Move Buffer,ing"; break;
		case 14: sType = "X"; strMsg = "X3 Axis Move To Buffer Position,ing"; break;
		case 15: sType = "B"; strMsg = "Wait for Move Unload,ing"; break;
		case 16: sType = "X"; strMsg = "X3 Axis Move To Unload Position,ing"; break;
		case 17: sType = "B"; strMsg = "Wait for Work Unload_Picker,ing"; break;
		case 18: sType = "X"; strMsg = "X3 Stage Down,ing"; break;
		case 19: sType = "X"; strMsg = "X3 Stage Out,ing"; break;
		case 20: sType = "B"; strMsg = "Wait for Move Down-Top2,ing"; break;
		case 21: sType = "X"; strMsg = "X3 Axis Move Back Top2 Position,ing"; break;
		case 22: sType = "B"; strMsg = "Wait for Move Down-Top1,ing"; break;
		case 23: sType = "X"; strMsg = "X3 Axis Move Back Top1 Position,ing"; break;
		case 24: sType = "B"; strMsg = "Wait for Move Down-Align,ing"; break;
		case 25: sType = "X"; strMsg = "X3 Axis Move Back Align Position,ing"; break;
		case 26: sType = "B"; strMsg = "Wait for Stage In,ing"; break;
		case 27: sType = "X"; strMsg = "X3 Stage In,ing"; break;
		case 28: sType = "X"; strMsg = "X3 Stage Up,end"; break;
		}
		break;
	case 17:
		strFun = "Inspect_Stage_4"; nSeqTotal = 28;
		switch (nId) {
		case  1: sType = "X"; strMsg = "X4 Axis Move To Top1 Position,start"; break;
		case  2: sType = "B"; strMsg = "Wait for Top1 Scan,ing"; break;
		case  3: sType = "X"; strMsg = "X4 Axis Move To Top1 Pitch,ing"; break;
		case  4: sType = "M"; strMsg = "X4 Top1 Scan Complete,ing"; break;
		case  5: sType = "B"; strMsg = "Wait for Top1 Angle Scan,ing"; break;
		case  6: sType = "X"; strMsg = "X4 Axis Move To Top1 Angle Pitch,ing"; break;
		case  7: sType = "M"; strMsg = "X4 Top1 Angle Scan Complete,ing"; break;
		case  8: sType = "B"; strMsg = "Wait for Move Top2,ing"; break;
		case  9: sType = "X"; strMsg = "X4 Axis Move To Top2 Position,ing"; break;
		case 10: sType = "B"; strMsg = "Wait for Top2 Scan,ing"; break;
		case 11: sType = "X"; strMsg = "X4 Axis Move To Top2 Pitch,ing"; break;
		case 12: sType = "M"; strMsg = "X4 Top2 Scan Complete,ing"; break;
		case 13: sType = "B"; strMsg = "Wait for Move Buffer,ing"; break;
		case 14: sType = "X"; strMsg = "X4 Axis Move To Buffer Position,ing"; break;
		case 15: sType = "B"; strMsg = "Wait for Move Unload,ing"; break;
		case 16: sType = "X"; strMsg = "X4 Axis Move To Unload Position,ing"; break;
		case 17: sType = "B"; strMsg = "Wait for Work Unload_Picker,ing"; break;
		case 18: sType = "X"; strMsg = "X4 Stage Down,ing"; break;
		case 19: sType = "X"; strMsg = "X4 Stage Out,ing"; break;
		case 20: sType = "B"; strMsg = "Wait for Move Down-Top2,ing"; break;
		case 21: sType = "X"; strMsg = "X4 Axis Move Back Top2 Position,ing"; break;
		case 22: sType = "B"; strMsg = "Wait for Move Down-Top1,ing"; break;
		case 23: sType = "X"; strMsg = "X4 Axis Move Back Top1 Position,ing"; break;
		case 24: sType = "B"; strMsg = "Wait for Move Down-Align,ing"; break;
		case 25: sType = "X"; strMsg = "X4 Axis Move Back Align Position,ing"; break;
		case 26: sType = "B"; strMsg = "Wait for Stage In,ing"; break;
		case 27: sType = "X"; strMsg = "X4 Stage In,ing"; break;
		case 28: sType = "X"; strMsg = "X4 Stage Up,end"; break;
		}
		break;
	case 18:
		strFun = "Unload_Picker_1"; nSeqTotal = 24;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Unload Picker Down,start"; break;
		case  2: sType = "X"; strMsg = "Z1 Axis Move to Down Position,ing"; break;
		case  3: sType = "X"; strMsg = "Unload Picker Close,ing"; break;
		case  4: sType = "X"; strMsg = "Z1 Axis Move to Ready-Up Position,ing"; break;
		case  5: sType = "X"; strMsg = "Unload Picker Module Check,ing"; break;
		case  6: sType = "M"; strMsg = "Check Inspection Done,ing"; break;
		case  7: sType = "M"; strMsg = "Check ROS Done,ing"; break;
		case  8: sType = "B"; strMsg = "Wait NG Stage Work,ing"; break;
		case  9: sType = "X"; strMsg = "Picker NG X-Y Move to Work Position,ing"; break;
		case 10: sType = "X"; strMsg = "Z1 Axis Move to Down Position,ing"; break;
		case 11: sType = "X"; strMsg = "Unload Picker Down,ing"; break;
		case 12: sType = "X"; strMsg = "Unload Picker Open,ing"; break;
		case 13: sType = "X"; strMsg = "Unload Picker Up,ing"; break;
		case 14: sType = "B"; strMsg = "Wait Good Stage Work,ing"; break;
		case 15: sType = "X"; strMsg = "Picker Good X-Y Move to Work Position,ing"; break;
		case 16: sType = "X"; strMsg = "Z1 Axis Move to Down Position,ing"; break;
		case 17: sType = "X"; strMsg = "Unload Picker Down,ing"; break;
		case 18: sType = "X"; strMsg = "Unload Picker Open,ing"; break;
		case 19: sType = "X"; strMsg = "Unload Picker Up,ing"; break;
		case 20: sType = "X"; strMsg = "Unload Picker Picker Work End,ing"; break;
		case 21: sType = "X"; strMsg = "Y1 Axis Move to Ready Position,ing"; break;
		case 22: sType = "X"; strMsg = "X1 Axis Move to Stage Position,ing"; break;
		case 23: sType = "B"; strMsg = "Wait Unload Picker 2 Interlock,ing"; break;
		case 24: sType = "X"; strMsg = "Y1 Axis Move to Work Position,end"; break;
		}
		break;
	case 19:
		strFun = "Unload_Picker_2"; nSeqTotal = 24;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Unload Picker Down,start"; break;
		case  2: sType = "X"; strMsg = "Z1 Axis Move to Down Position,ing"; break;
		case  3: sType = "X"; strMsg = "Unload Picker Close,ing"; break;
		case  4: sType = "X"; strMsg = "Z1 Axis Move to Ready-Up Position,ing"; break;
		case  5: sType = "X"; strMsg = "Unload Picker Module Check,ing"; break;
		case  6: sType = "M"; strMsg = "Check Inspection Done,ing"; break;
		case  7: sType = "M"; strMsg = "Check ROS Done,ing"; break;
		case  8: sType = "B"; strMsg = "Wait NG Stage Work,ing"; break;
		case  9: sType = "X"; strMsg = "Picker NG X-Y Move to Work Position,ing"; break;
		case 10: sType = "X"; strMsg = "Z1 Axis Move to Down Position,ing"; break;
		case 11: sType = "X"; strMsg = "Unload Picker Down,ing"; break;
		case 12: sType = "X"; strMsg = "Unload Picker Open,ing"; break;
		case 13: sType = "X"; strMsg = "Unload Picker Up,ing"; break;
		case 14: sType = "B"; strMsg = "Wait Good Stage Work,ing"; break;
		case 15: sType = "X"; strMsg = "Picker Good X-Y Move to Work Position,ing"; break;
		case 16: sType = "X"; strMsg = "Z1 Axis Move to Down Position,ing"; break;
		case 17: sType = "X"; strMsg = "Unload Picker Down,ing"; break;
		case 18: sType = "X"; strMsg = "Unload Picker Open,ing"; break;
		case 19: sType = "X"; strMsg = "Unload Picker Up,ing"; break;
		case 20: sType = "X"; strMsg = "Unload Picker Picker Work End,ing"; break;
		case 21: sType = "X"; strMsg = "Y1 Axis Move to Ready Position,ing"; break;
		case 22: sType = "X"; strMsg = "X1 Axis Move to Stage Position,ing"; break;
		case 23: sType = "B"; strMsg = "Wait Unload Picker 2 Interlock,ing"; break;
		case 24: sType = "X"; strMsg = "Y1 Axis Move to Work Position,end"; break;
		}
		break;
	case 20:
		strFun = "NG_Stage_1"; nSeqTotal = 16;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Stage Master In,start"; break;
		case  2: sType = "X"; strMsg = "Stage Slave In,ing"; break;
		case  3: sType = "B"; strMsg = "Wait Align Move,ing"; break;
		case  4: sType = "X"; strMsg = "Y Axis Move to Align-1 Position,ing"; break;
		case  5: sType = "B"; strMsg = "Wait Align End,ing"; break;
		case  6: sType = "X"; strMsg = "Y Axis Move to Wait or Work Position,ing"; break;
		case  7: sType = "X"; strMsg = "Y Axis Move to Work Position,ing"; break;
		case  8: sType = "B"; strMsg = "Wait Unload Picker Work,ing"; break;
		case  9: sType = "X"; strMsg = "Stage Down,ing"; break;
		case 10: sType = "B"; strMsg = "Wait Move to Load Position,ing"; break;
		case 11: sType = "X"; strMsg = "Y Axis Move to Load Position,ing"; break;
		case 12: sType = "B"; strMsg = "Wait Stage Up,ing"; break;
		case 13: sType = "X"; strMsg = "Stage Up,ing"; break;
		case 14: sType = "X"; strMsg = "Stage Slave Out,ing"; break;
		case 15: sType = "X"; strMsg = "Stage Master Out,ing"; break;
		case 16: sType = "X"; strMsg = "Stage Work End,end"; break;
		}
		break;
	case 21:
		strFun = "NG_Stage_2"; nSeqTotal = 16;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Stage Master In,start"; break;
		case  2: sType = "X"; strMsg = "Stage Slave In,ing"; break;
		case  3: sType = "B"; strMsg = "Wait Align Move,ing"; break;
		case  4: sType = "X"; strMsg = "Y Axis Move to Align-1 Position,ing"; break;
		case  5: sType = "B"; strMsg = "Wait Align End,ing"; break;
		case  6: sType = "X"; strMsg = "Y Axis Move to Wait or Work Position,ing"; break;
		case  7: sType = "X"; strMsg = "Y Axis Move to Work Position,ing"; break;
		case  8: sType = "B"; strMsg = "Wait Unload Picker Work,ing"; break;
		case  9: sType = "X"; strMsg = "Stage Down,ing"; break;
		case 10: sType = "B"; strMsg = "Wait Move to Load Position,ing"; break;
		case 11: sType = "X"; strMsg = "Y Axis Move to Load Position,ing"; break;
		case 12: sType = "B"; strMsg = "Wait Stage Up,ing"; break;
		case 13: sType = "X"; strMsg = "Stage Up,ing"; break;
		case 14: sType = "X"; strMsg = "Stage Slave Out,ing"; break;
		case 15: sType = "X"; strMsg = "Stage Master Out,ing"; break;
		case 16: sType = "X"; strMsg = "Stage Work End,end"; break;
		}
		break;
	case 22:
		strFun = "Good_Stage_1"; nSeqTotal = 16;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Stage Master In,start"; break;
		case  2: sType = "X"; strMsg = "Stage Slave In,ing"; break;
		case  3: sType = "B"; strMsg = "Wait Align Move,ing"; break;
		case  4: sType = "X"; strMsg = "Y Axis Move to Align-1 Position,ing"; break;
		case  5: sType = "B"; strMsg = "Wait Align End,ing"; break;
		case  6: sType = "X"; strMsg = "Y Axis Move to Wait or Work Position,ing"; break;
		case  7: sType = "X"; strMsg = "Y Axis Move to Work Position,ing"; break;
		case  8: sType = "B"; strMsg = "Wait Unload Picker Work,ing"; break;
		case  9: sType = "X"; strMsg = "Stage Down,ing"; break;
		case 10: sType = "B"; strMsg = "Wait Move to Load Position,ing"; break;
		case 11: sType = "X"; strMsg = "Y Axis Move to Load Position,ing"; break;
		case 12: sType = "B"; strMsg = "Wait Stage Up,ing"; break;
		case 13: sType = "X"; strMsg = "Stage Up,ing"; break;
		case 14: sType = "X"; strMsg = "Stage Slave Out,ing"; break;
		case 15: sType = "X"; strMsg = "Stage Master Out,ing"; break;
		case 16: sType = "X"; strMsg = "Stage Work End,end"; break;
		}
		break;
	case 23:
		strFun = "Good_Stage_2"; nSeqTotal = 16;
		switch (nId) {
		case  1: sType = "X"; strMsg = "Stage Master In,start"; break;
		case  2: sType = "X"; strMsg = "Stage Slave In,ing"; break;
		case  3: sType = "B"; strMsg = "Wait Align Move,ing"; break;
		case  4: sType = "X"; strMsg = "Y Axis Move to Align-1 Position,ing"; break;
		case  5: sType = "B"; strMsg = "Wait Align End,ing"; break;
		case  6: sType = "X"; strMsg = "Y Axis Move to Wait or Work Position,ing"; break;
		case  7: sType = "X"; strMsg = "Y Axis Move to Work Position,ing"; break;
		case  8: sType = "B"; strMsg = "Wait Unload Picker Work,ing"; break;
		case  9: sType = "X"; strMsg = "Stage Down,ing"; break;
		case 10: sType = "B"; strMsg = "Wait Move to Load Position,ing"; break;
		case 11: sType = "X"; strMsg = "Y Axis Move to Load Position,ing"; break;
		case 12: sType = "B"; strMsg = "Wait Stage Up,ing"; break;
		case 13: sType = "X"; strMsg = "Stage Up,ing"; break;
		case 14: sType = "X"; strMsg = "Stage Slave Out,ing"; break;
		case 15: sType = "X"; strMsg = "Stage Master Out,ing"; break;
		case 16: sType = "X"; strMsg = "Stage Work End,end"; break;
		}
		break;
	case 24:
		strFun = "Ship_Align"; nSeqTotal = 6;
		switch (nId) {
		case 1: sType = "X"; strMsg = "Align 1 Position,start"; break;
		case 2: sType = "M"; strMsg = "Align 1 Complete,ing"; break;
		case 3: sType = "X"; strMsg = "Align 2 Position,ing"; break;
		case 4: sType = "M"; strMsg = "Align 2 Complete,ing"; break;
		case 5: sType = "X"; strMsg = "Align 3 Position,ing"; break;
		case 6: sType = "M"; strMsg = "Align 3 Complete,end"; break;
		}
		break;
	}

	sLotID = "";
	if (nFun ==  8) { sLotID = gData.sLotID_Tansfer[0];			if (sLotID == "") sLotID = gData.sLotID_Tansfer[2]; }
	if (nFun ==  9) { sLotID = gData.sLotID_Tansfer[1];			if (sLotID == "") sLotID = gData.sLotID_Tansfer[2]; }
	if (nFun == 10)	{ sLotID = gData.sLotID_LoadStage[0];		if (sLotID == "") sLotID = gData.sLotID_LoadStage[2]; }
	if (nFun == 11)	{ sLotID = gData.sLotID_LoadStage[1];		if (sLotID == "") sLotID = gData.sLotID_LoadStage[2]; }
	if (nFun == 12) { sLotID = gData.sLotID_LoadPicker[0];		if (sLotID == "") sLotID = gData.sLotID_LoadPicker[2]; }
	if (nFun == 13) { sLotID = gData.sLotID_LoadPicker[1];		if (sLotID == "") sLotID = gData.sLotID_LoadPicker[2]; }
	if (nFun == 14)	{ sLotID = gData.sLotID_VisionStage[0];		if (sLotID == "") sLotID = gData.sLotID_VisionStage[4]; }
	if (nFun == 15)	{ sLotID = gData.sLotID_VisionStage[1];		if (sLotID == "") sLotID = gData.sLotID_VisionStage[4]; }
	if (nFun == 16)	{ sLotID = gData.sLotID_VisionStage[2];		if (sLotID == "") sLotID = gData.sLotID_VisionStage[4]; }
	if (nFun == 17)	{ sLotID = gData.sLotID_VisionStage[3];		if (sLotID == "") sLotID = gData.sLotID_VisionStage[4]; }
	if (nFun == 18) { sLotID = gData.sLotID_UnloadPicker[0];	if (sLotID == "") sLotID = gData.sLotID_UnloadPicker[2]; }
	if (nFun == 19) { sLotID = gData.sLotID_UnloadPicker[1];	if (sLotID == "") sLotID = gData.sLotID_UnloadPicker[2]; }
	if (nFun == 20)	{ sLotID = gData.sLotID_NGTray[0];			if (sLotID == "") sLotID = gData.sLotID_NGTray[2]; }
	if (nFun == 21)	{ sLotID = gData.sLotID_NGTray[1];			if (sLotID == "") sLotID = gData.sLotID_NGTray[2]; }
	if (nFun == 22)	{ sLotID = gData.sLotID_GoodTray[0];		if (sLotID == "") sLotID = gData.sLotID_GoodTray[2]; }
	if (nFun == 23)	{ sLotID = gData.sLotID_GoodTray[1];		if (sLotID == "") sLotID = gData.sLotID_GoodTray[2]; }

	if (sLotID == "") sLotID = gData.sLotID_Start;
	if (sLotID == "") {
		for(int i=0; i<6; i++) {
			if (gLot.nCmCount[i] > 0) { sLotID = gLot.sLotID[i]; nPortNo = i+1; break; }
		}
	}
}

void CLogFile::Save_Interlock(int nType)	//nType:0[?????], 1[????], 2[????] 3[????]
{
	CString strFile, sTitle, sTitle1, strTime, strSave, strSave1, strSave2, strSave3, strSave4, strSave5, strLotID, strDoor[21], sInterUse;

	SYSTEMTIME time;
	GetLocalTime(&time);

	if (nType == 0) {
		gIt.nOpenTime = 0;
		gIt.nOpenStart = 0;
		gIt.nLogYY = time.wYear;	//??????
		gIt.nLogMM = time.wMonth;	//??????
		gIt.nLogDD = time.wDay;		//??????
		gIt.nLogHH = time.wHour;	//???©£???
	}
	if (gIt.nLogMM < 1 || gIt.nLogMM > 12) return;

	EQUIP_DATA *pEquipData = g_objDataManager.Get_pEquipData();
	if (nType == 1)	strTime.Format("%04d-%02d-%02d %02d:00:00.000",		 time.wYear, time.wMonth, time.wDay, time.wHour);
	else			strTime.Format("%04d-%02d-%02d %02d:%02d:%02d.%03d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	sTitle1 = "Door I/L 11,Door I/L 12,Door I/L 13,Door I/L 14,Door I/L 15,Door I/L 16,Door I/L 17,Door I/L 18,Door I/L 19,Door I/L 20,Door I/L 21,Door I/L 22,Door I/L 23,Door I/L 24,Door I/L 25,Door I/L 26,Door I/L 27,Door I/L 28,Door I/L 29,Door I/L 30";
	sTitle.Format("time,station,lotNum,barcode,SWversion,State,site,Line,Machine,operator,result,Interlock,Interlock off Time,Interlock Coverage,Door I/L 1,Door I/L 2,Door I/L 3,Door I/L 4,Door I/L 5,Door I/L 6,Door I/L 7,Door I/L 8,Door I/L 9,Door I/L 10,%s\r\n", sTitle1);
	strFile.Format("%sGSY848CP2C2N_%04d%02d%02d%02d_InterlockResult.csv", ECM_LOG, gIt.nLogYY, gIt.nLogMM, gIt.nLogDD, gIt.nLogHH);
	if (nType == 0) { DeleteFile(strFile); return; }

	if (gLot.nJobStatus > 0) strLotID = gData.sLotID_Start;
	else					 strLotID = "";

	int		nSite;
	CString sSite, sLine, sModel;
	if		(pEquipData->sMachineCode.Find("C4") >= 0) nSite = 4;
	else if (pEquipData->sMachineCode.Find("C5") >= 0) nSite = 5;
	else											   nSite = 0;
	if		(pEquipData->sMachineCode.Find("DFA") >= 0) sModel = "FOL";
	else											    sModel = "EOL";
	sSite.Format("Gumi Campus %d Area", nSite);
	sLine.Format("Campus %d %s", nSite, sModel);

	int	   nNGTime;
	double dTime, dPer;
	if (nType == 1) {
		if (gIt.nOpenStart == 1) {
			nNGTime = (GetTickCount() - gIt.dwOpenStartTime) / 1000;	//?????
			gIt.nOpenTime = gIt.nOpenTime + nNGTime;
		}
		if (gIt.nOpenTime > 0) {
			if (gIt.nOpenTime > 3600) gIt.nOpenTime = 3600;
			dTime = gIt.nOpenTime / 60.0;	//?¬Õ???
			dPer = ((3600.0 - gIt.nOpenTime) / 3600.0) * 100.0;
			if (dPer > 100.0) dPer = 100.0;
		} else {
			dTime = 0.0; dPer = 100.0;
		}
		gIt.dwOpenStartTime = GetTickCount();
		gIt.nOpenTime = 0;
		gIt.nLogYY = time.wYear;
		gIt.nLogMM = time.wMonth;
		gIt.nLogDD = time.wDay;
		gIt.nLogHH = time.wHour;

		if (pEquipData->bUseDoorLock) sInterUse = "OK";
		else						  sInterUse = "NG";
	}
	if (nType == 2) {
		sInterUse = "NG";
		gIt.nOpenStart = 1;
		gIt.dwOpenStartTime = GetTickCount();
	}
	if (nType == 3) {
		sInterUse = "OK";
		gIt.nOpenStart = 0;
		nNGTime = (GetTickCount() - gIt.dwOpenStartTime) / 1000;
		gIt.nOpenTime = gIt.nOpenTime + nNGTime;
	}

	CFile file;
	if (!file.Open(strFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite)) return;

	try {
		file.SeekToEnd();

		if (file.GetLength() < 1) file.Write(sTitle, sTitle.GetLength());

		strSave1.Format("%s,%s,%s,,%s,MP,%s,%s,%s,%s", strTime, gData.sComName, strLotID, MAIN_VERSION, sSite, sLine, pEquipData->sMachineCode, gData.sOperID);
		if (nType == 1) strSave2.Format("A1,%s,%0.2lf,%d%%", sInterUse, dTime, int(dPer+0.5));
		if (nType == 2) strSave2.Format("F,NG,,");
		if (nType >= 3) strSave2.Format("A2,OK,,");

		DX_DATA_14 *pDX14 = g_objAJinAXL.Get_pDX14();
		if (pDX14->iDoor01Unlock) strDoor[0] = "Open"; else strDoor[0] = "Close";
		if (pDX14->iDoor02Unlock) strDoor[1] = "Open"; else strDoor[1] = "Close";
		if (pDX14->iDoor03Unlock) strDoor[2] = "Open"; else strDoor[2] = "Close";
	 	if (pDX14->iDoor04Unlock) strDoor[3] = "Open"; else strDoor[3] = "Close";
	 	if (pDX14->iDoor05Unlock) strDoor[4] = "Open"; else strDoor[4] = "Close";
		if (pDX14->iDoor06Unlock) strDoor[5] = "Open"; else strDoor[5] = "Close";
		if (pDX14->iDoor07Unlock) strDoor[6] = "Open"; else strDoor[6] = "Close";
		if (pDX14->iDoor08Unlock) strDoor[7] = "Open"; else strDoor[7] = "Close";
		if (pDX14->iDoor09Unlock) strDoor[8] = "Open"; else strDoor[8] = "Close";
		if (pDX14->iDoor10Unlock) strDoor[9] = "Open"; else strDoor[9] = "Close";
		if (pDX14->iDoor11Unlock) strDoor[10] = "Open"; else strDoor[10] = "Close";
	 	if (pDX14->iDoor12Unlock) strDoor[11] = "Open"; else strDoor[11] = "Close";
	 	if (pDX14->iDoor13Unlock) strDoor[12] = "Open"; else strDoor[12] = "Close";
		if (pDX14->iDoor14Unlock) strDoor[13] = "Open"; else strDoor[13] = "Close";
		if (pDX14->iDoor15Unlock) strDoor[14] = "Open"; else strDoor[14] = "Close";
		if (pDX14->iDoor16Unlock) strDoor[15] = "Open"; else strDoor[15] = "Close";
		if (pDX14->iDoor17Unlock) strDoor[16] = "Open"; else strDoor[16] = "Close";
		if (pDX14->iDoor18Unlock) strDoor[17] = "Open"; else strDoor[17] = "Close";
		if (pDX14->iDoor19Unlock) strDoor[18] = "Open"; else strDoor[18] = "Close";
	 	if (pDX14->iDoor20Unlock) strDoor[19] = "Open"; else strDoor[19] = "Close";
	 	if (pDX14->iDoor21Unlock) strDoor[20] = "Open"; else strDoor[20] = "Close";

		strSave3.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",    strDoor[0],  strDoor[1],  strDoor[2],  strDoor[3],  strDoor[4],  strDoor[5],  strDoor[6],  strDoor[7],  strDoor[8],  strDoor[9]);
		strSave4.Format("%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s", strDoor[10], strDoor[11], strDoor[12], strDoor[13], strDoor[14], strDoor[15], strDoor[16], strDoor[17], strDoor[18], strDoor[19], strDoor[20]);
		strSave5.Format("-,-,-,-,-,-,-,-,-,");

		strSave.Format("%s,%s,%s,%s,%s\r\n", strSave1, strSave2, strSave3, strSave4, strSave5);
		file.Write(strSave, strSave.GetLength());
		file.Close();

	} catch (CFileException *pEx) {
		pEx->Delete();
	}
}