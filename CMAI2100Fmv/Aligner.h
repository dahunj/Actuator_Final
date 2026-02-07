// Aligner.h : 헤더 파일
//
#pragma once

const int ALIGNER_ALL	= 0;
const int ALIGNER_LD1	= 1;
const int ALIGNER_LD2	= 2;
const int ALIGNER_MD1	= 3;
const int ALIGNER_MD2	= 4;
const int ALIGNER_CP1	= 5;
const int ALIGNER_CP2	= 6;
const int ALIGNER_MAIN	= 7;

// CAligner

class CAligner : public CWnd
{
	DECLARE_DYNAMIC(CAligner)

public:
	CAligner();
	virtual ~CAligner();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnUdpReceive(WPARAM wLocalPort, LPARAM lParam);

private:
	CUdpSocketCS	m_UdpAlignerLd1;
	CUdpSocketCS	m_UdpAlignerLd2;
	CUdpSocketCS	m_UdpAlignerMd1;
	CUdpSocketCS	m_UdpAlignerMd2;
	CUdpSocketCS	m_UdpAlignerCp1;
	CUdpSocketCS	m_UdpAlignerCp2;
	CUdpSocketCS	m_UdpAlignerMain;

	CString		m_strRecvCmd;

	BOOL	m_bConnectAlignerLd1, m_bConnectAlignerLd2;
	BOOL	m_bConnectAlignerMd1, m_bConnectAlignerMd2;
	BOOL	m_bConnectAlignerCp1, m_bConnectAlignerCp2;
	int		m_nStatusAlignerLd1, m_nStatusAlignerLd2;
	int		m_nStatusAlignerMd1, m_nStatusAlignerMd2;
	int		m_nStatusAlignerCp1, m_nStatusAlignerCp2;

	void DoEvents(int nSleep = 0);

	void Get_ConnectRequest(int nAligner);
	void Get_ConnectReply(int nAligner);
	void Get_ConnectEnd(int nAligner);
	void Get_StatusRequest(int nAligner);
	void Get_StatusReply(int nAligner, CString sStatus);
	void Get_StatusUpdate(int nAligner, CString sStatus);
	void Get_ScanComplete(int nAligner, CString sLotId, CString sMainNo, CString sSubNo, CString sGbn);
	void Get_AlignComplete(int nAligner, CString sLotId, CString sMainNo, CString sSubNo, CString sGbn, CString sJurge, CString sX, CString sY, CString sA);
	void Get_TMoveRequest(int nAligner, CString sGbn, CString sA);
	void Get_TimeUpdate(int nAligner, CString sTime);

	void Send_Command(int nAligner, CString strSend);

public:
	void Initialize();
	void Terminate();

	void Set_ConnectRequest(int nAligner);
	void Set_ConnectReply(int nAligner);
	void Set_ConnectEnd(int nAligner);
	void Set_StatusRequest(int nAligner);
	void Set_StatusReply(int nAligner, int nStatus);
	void Set_StatusUpdate(int nAligner, int nStatus);
	void Set_LotStart(int nAligner);
	void Set_LotEnd(int nAligner);
	void Set_LoadComplete(int nAligner, int nMainNo, int nSubNo, CString sGbn);
	void Set_MoveComplete(int nAligner, CString sGbn);
	void Set_TimeUpdate(int nAligner);

	int Get_VisionStatus(int nAligner);

	void Test_Command(int nNo);
};

extern CAligner g_objAligner;

///////////////////////////////////////////////////////////////////////////////
