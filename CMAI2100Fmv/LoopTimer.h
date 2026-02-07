// LoopTimer.h : 헤더 파일
//
#pragma once

class CLoopTimer
{
public:
	CLoopTimer();
	virtual ~CLoopTimer();

private:
	DWORD	m_dwLoopStart;
	DWORD	m_dwLoopTerm;
	DWORD	m_dwTakt;

	BOOL	m_bWaitingRun;
	DWORD	m_dwWaitingStart;

public:
	void Set_LoopTime(DWORD msec);
	BOOL Over_LoopTime();
	BOOL Delay_LoopTime(DWORD msec);

	void Takt_Start(int nFun, int nId, BOOL bFirst=FALSE);
	void Takt_Save(int nFun, int nId, BOOL bLast=FALSE);
	CString Add_ModuleInfo(int nFun, int nId);

	//////////////////////////////
	BOOL Waiting_Time(DWORD msec);
};

///////////////////////////////////////////////////////////////////////////////
