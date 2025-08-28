// Dispatcher.h : 헤더 파일
//
#pragma once

// CDispatcher

class CDispatcher : public CWnd
{
	DECLARE_DYNAMIC(CDispatcher)

public:
	CDispatcher();
	virtual ~CDispatcher();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnUdpClientReceive(WPARAM wLocalPort, LPARAM lParam);

private:
	CUdpRecvCS	m_UdpRecv;
	CUdpSendCS	m_UdpSend;

	CString	m_strRecvCmd;
	BOOL	m_bConnected;
	int		m_nMdjIndex;
	
	BOOL	m_bJudgeReq[6][20][40];		// 판정 요청
	BOOL	m_bJudgeDone[6][20][40];	// 판정 완료
	DWORD	m_dwReqStart[6][20][40];	// 요청 시작
	DWORD	m_dwTimeStart[6][20][40];	// TimeOver Check시작
	int		m_nPortNo;

	void Get_ConnectRequest(CString sIp);
	void Get_ConnectReply(CString sIp);
	void Get_ConnectEnd(CString sIp);
	void Get_StatusRequest(CString sIp);
	void Get_StatusReply(CString sStatus);
	void Get_StatusUpdate(CString sStatus);
	void Get_InfoRequest(CString sIp);
	void Get_JudgeReply(CString sModel, CString sLotId, CString sPortNo, CString sTrayNo, CString sCmNo, CString sBarcode, CString sCode, CString sJudge);

	void Send_Command(CString sIp, CString sSend);

public:
	BOOL Initialize();
	void Terminate();
	void Reset(int nPortNo);

	void Set_ConnectRequest();
	void Set_ConnectReply(CString sIp);
	void Set_ConnectEnd(CString sIp);
	void Set_StatusRequest();
	void Set_StatusReply(CString sIp, int nStatus);
	void Set_StatusUpdate(int nStatus);
	void Set_LotStart(int nPortNo);
	void Set_LotEnd(int nPortNo);
	void Set_InfoReply(CString sIp);
	void Set_JudgeRequest(int nPortNo, int nTrayNo, int nCmNo);
	void Set_TimeUpdate();
	void Set_TimeOver(int nPortNo, int nTrayNo, int nCmNo);

	BOOL Is_JudgeDone(int nPortNo, int nTrayNo, int nCmNo);
	BOOL Is_Connected() { return m_bConnected; }
	void Set_Connected(BOOL bOn) { m_bConnected = bOn; }

	void Test_Command(int nNo);
};

extern CDispatcher g_objDispatcher;

///////////////////////////////////////////////////////////////////////////////
