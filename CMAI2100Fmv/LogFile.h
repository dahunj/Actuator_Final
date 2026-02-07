// LogFile.h : 헤더 파일
//
#pragma once

class CLogFile  
{
public:
	CLogFile();
	virtual ~CLogFile();

private:
	CString sLogLotID[6];
	int		nLotSeqNo[6];
	CString m_sPCID;
	CString m_sMachineCode;

public:
	void Create_Folder(CString sPath);

	void Save_AlarmLog(CString sLog);
	void Save_AlarmResetLog(CString strLog);
	void Save_AlarmECMLog(int nType, CString strLog);	//nType:1[Reset], 0[Set]
	void Save_HandlerLog(CString sLog);
	void Save_InspectorLog(CString sLog);
	void Save_JobListLog(CString sLog);
	void Save_MCCLog(CString sLog);
	void Save_TackLog(CString sLog);
	void Save_LotResult(CString sLog);
	void Save_DispatcherLog(CString sLog);
	void Save_MesAgentLog(CString sLog);
	void Save_MesNgLog(CString sLog, int nPortIdx);
	void Save_LotLog();
	void Save_OutTray(CString strLotID, CString strOut, int nPosX, int nPosY, int nMzNo, int nCarNo, int nLineNo, int nPickNo);
	void Save_ECMLog(int nType, CString strLog);	//nType:1[Alarm], 2[Joblist]
	void Save_ECMOutPut(int nPNo, int nTNo, int nMNo, int nType);	//0:G, 1:NG
	void Save_ECMDailyLot(CString sLog);
	void Save_TestLog(CString sLog);
	void Save_DailyLot(CString sLog);
	void Save_LotLog(int nPortNo);
	void Save_OperatingRatio(CString sLog);

	void Save_OutTrayGLog(int nPortNo, int nTrayNo, int nCMNo);
	void Save_OutTrayNLog(int nPortNo, int nTrayNo, int nCMNo);
	void Save_SpcMccLog(CString sLog, CString sLotID);
	void Save_SpcMotionLog(CString sLog, CString sLotID);
	void Save_SpcErrorLog(CString sLog, CString sLotID);
	void Save_Interlock(int nType);					//nType:0[등록], 1[정시], 2[해제] 3[설정]

	void Save_StdMotionLog(CString sLotID, CString sType, int nZone, int nCase, int nValue, CString sZone, CString sMsg);
	void Save_EfficiencyLog(CString sLotID, CString sStatus, CString strZone, int nCode, CString sNote);
	void Get_ZoneMsg(int nZone, int nCase, CString &sLotID, int &nPortNo, int &nSeqNo, CString &sZone, CString &sMsg, CString &sType);
	void Clear_LogData();
	void Set_ID(CString sPCID, CString sMCode) { m_sPCID = sPCID; m_sMachineCode = sMCode; }
};

extern CLogFile g_objLogFile;

///////////////////////////////////////////////////////////////////////////////
