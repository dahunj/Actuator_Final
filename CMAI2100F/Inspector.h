// Inspector.h : 헤더 파일
//
#pragma once

const int INSPECTOR_ALL		= 0;	// ALL PC
const int INSPECTOR_PC1		= 1;	// Bottom,(Align1,2)
const int INSPECTOR_PC2		= 2;	// Top1-1
const int INSPECTOR_PC3		= 3;	// Top2-1
const int INSPECTOR_PC4		= 4;	// Top1-2
const int INSPECTOR_PC5		= 5;	// Top2-2

// CInspector

class CInspector : public CWnd
{
	DECLARE_DYNAMIC(CInspector)

public:
	CInspector();
	virtual ~CInspector();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnUdpReceive(WPARAM wLocalPort, LPARAM lParam);

	static UINT Thread_MotionB1(LPVOID lpVoid);
	static UINT Thread_MotionT1(LPVOID lpVoid);
	static UINT Thread_MotionT2(LPVOID lpVoid);

private:
	CUdpSocketCS	m_UdpVisionPC1, m_UdpVisionPC2, m_UdpVisionPC3, m_UdpVisionPC4, m_UdpVisionPC5;

	CString		m_strRecvCmd;

	BOOL	m_bConnectVisionPC1, m_bConnectVisionPC2, m_bConnectVisionPC3, m_bConnectVisionPC4, m_bConnectVisionPC5;
	int		m_nStatusVisionPC1, m_nStatusVisionPC2, m_nStatusVisionPC3, m_nStatusVisionPC4, m_nStatusVisionPC5;	// Vision PC1 상태 (0:Not Ready, 1:Ready)
	BOOL	m_bLotReady1, m_bLotReady2, m_bLotReady3, m_bLotReady4, m_bLotReady5, m_bScanEnd[5][2];
	DWORD	m_dwT2ScanDone[6][20][40];	// T2 Scan Done

	CString	m_sB1, m_sT1, m_sT2;
	int		m_nB1, m_nT1, m_nT2;
	double	m_dB1, m_dT1, m_dT2;

	void DoEvents(int nSleep = 0);

	void Get_ConnectRequest(int nInspector);
	void Get_ConnectReply(int nInspector);
	void Get_ConnectEnd(int nInspector);
	void Get_StatusRequest(int nInspector);
	void Get_StatusReply(int nInspector, CString sStatus);
	void Get_StatusUpdate(int nInspector, CString sStatus);
	void Get_LotReady(int nInspector, CString sLotID, CString sPortNo, CString sPgVer, CString sPaVer, CString sRcpName);
	void Get_ScanComplete(int nInspector, CString sType, CString sLotID, CString sPortNo, CString sTrayNo, CString sCMNo);
	void Get_InspectComplete(int nInspector, CString sType, CString sLotID, CString sPortNo, CString sTrayNo, CString sCMNo, CString sJudge, CString sNGCode, CString sImageCnt1, CString sImageCnt2, CString sMarginal, CString sRcvData);
	void Get_AMoveRequest(int nInspector, CString sType, CString strZ);
	void Get_PositionRequest(int nInspector, CString sType);
	void Get_BarcodeResult(int nInspector, CString sLotID, CString sPortNo, CString sTrayNo, CString sCMNo, CString sBarCode);
	void Get_ErrorRequest(int nInspector, CString sType, CString sLotId, CString sPortNo, CString sTrayNo, CString sCMNo, CString sErrNo, CString sErrMsg);
	void Get_HeartBeat(int nInspector);
	void Get_AlignComplete(int nInspector, CString sType, CString sRcvData);
	void Get_LotEnd(int nInspector, CString sLotID, CString sPortNo, CString sDeepData1, CString sDeepData2, CString sDeepData3, CString sDeepData4, CString sDeepData5);
		
	void Get_RecipeUpdata();

	void Send_Command(int nInspector, CString strSend);
	void Exception_Log(CString sFunc, CString sGbn, int nCase);	// Recevie Exception Log

public:
	void Initialize();
	void Terminate();

	void Set_ConnectRequest(int nInspector);
	void Set_ConnectReply(int nInspector);
	void Set_ConnectEnd(int nInspector);
	void Set_StatusRequest(int nInspector);
	void Set_StatusReply(int nInspector, int nStatus);
	void Set_StatusUpdate(int nInspector, int nStatus);
	void Set_LotStart(int nInspector, CString sLotID, int nPortNo, int nTrayCnt, int nCMCnt, CString sRcp, CString sPro, CString sPara, BOOL nMarginal);
	void Set_LotEnd(int nInspector, CString sLotID, int nPortNo);
	void Set_LoadComplete(int nInspector, CString sType, CString sLotID, int nPortNo, int nTrayNo1, int nCMNo1, int nTrayNo2, int nCMNo2);
	void Set_MoveComplete(int nInspector, CString sType, double dZ);
	void Set_PositionReply(int nInspector, CString sType, double dZ);
	void Set_BarcodeUpdate(int nInspector, CString sLotID, CString sPortNo, CString sTrayNo, CString sCMNo, CString sBarCode);
	void Set_TimeUpdate(int nInspector);	
	void Set_InitialRequest(int nInspector);
	void Set_CycleStop(int nInspector);
	void Set_AlignRequest(int nInspector, CString sType, CString sLotID, int nPortNo, int nTrayNo, int nSeqNo);
	void Set_HistoryReply(int nInspector, CString sData);

	int	 Get_VisionStatus(int nInspector);
	BOOL Check_LotReady();
	void Set_LotReadyFalse();
	void Set_MotionB1(int nInspector, CString sType, double dData);
	void Set_MotionT1(int nInspector, CString sType, double dData);
	void Set_MotionT2(int nInspector, CString sType, double dData);

	void Test_Command();
};

extern CInspector g_objInspector;

///////////////////////////////////////////////////////////////////////////////
