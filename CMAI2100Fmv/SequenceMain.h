// SequenceMain.h : 헤더 파일
//
#pragma once

#include "AJinAXL.h"
#include "DataManager.h"
#include "LoopTimer.h"

class CSequenceMain  
{
public:
	CSequenceMain();
	virtual ~CSequenceMain();
	
private:
	AXIS_STATUS *m_pStatus[AXIS_COUNT];
	AXIS_PARAM	*m_pParam[AXIS_COUNT];
	
	DX_DATA_00	*m_pDX00;	// Input (X0000 - X0031)
	DX_DATA_01	*m_pDX01;	// Input (X0100 - X0131)
	DX_DATA_02	*m_pDX02;	// Input (X0200 - X0231)
	DX_DATA_03	*m_pDX03;	// Input (X0300 - X0331)
	DX_DATA_04	*m_pDX04;	// Input (X0400 - X0431)
	DX_DATA_05	*m_pDX05;	// Input (X0500 - X0531)
	DX_DATA_06	*m_pDX06;	// Input (X0600 - X0631)
	DX_DATA_07	*m_pDX07;	// Input (X0700 - X0731)
	DX_DATA_08	*m_pDX08;	// Input (X0800 - X0831)
	DX_DATA_09	*m_pDX09;	// Input (X0900 - X0931)
	DX_DATA_10	*m_pDX10;	// Input (X1000 - X1031)
	DX_DATA_11	*m_pDX11;	// Input (X1100 - X1131)
	DX_DATA_12	*m_pDX12;	// Input (X1200 - X1231)
	DX_DATA_13	*m_pDX13;	// Input (X1300 - X1331)
	DX_DATA_14	*m_pDX14;	// Input (X1400 - X1431)

	DY_DATA_00	*m_pDY00;	// Output (Y0000 - Y0031)
	DY_DATA_01	*m_pDY01;	// Output (Y0100 - Y0131)
	DY_DATA_02	*m_pDY02;	// Output (Y0200 - Y0231)
	DY_DATA_03	*m_pDY03;	// Output (Y0300 - Y0331)
	DY_DATA_04	*m_pDY04;	// Output (Y0400 - Y0431)
	DY_DATA_05	*m_pDY05;	// Output (Y0500 - Y0531)
	DY_DATA_06	*m_pDY06;	// Output (Y0600 - Y0631)
	DY_DATA_07	*m_pDY07;	// Output (Y0700 - Y0731)
	DY_DATA_08	*m_pDY08;	// Output (Y0800 - Y0831)
	DY_DATA_09	*m_pDY09;	// Output (Y0900 - Y0931)
	DY_DATA_10	*m_pDY10;	// Output (Y1000 - Y1031)
	DY_DATA_11	*m_pDY11;	// Output (Y1100 - Y1131)
	DY_DATA_12	*m_pDY12;	// Output (Y1200 - Y1231)
	DY_DATA_13	*m_pDY13;	// Output (Y1300 - Y1331)
	DY_DATA_14	*m_pDY14;	// Output (Y1400 - Y1431)
	
	EQUIP_DATA	*m_pEquipData;
	MOVE_DATA	*m_pMoveData;
	ROS_DATA	*m_pRosData;

	int			m_nRcpPortNo;
	CString		m_sLog;

protected:
	BOOL		m_bThreadMainRun;
	CWinThread	*m_pThreadMainRun;
	static UINT	Thread_MainRun(LPVOID lpVoid);

private:
	int			m_nElevator1Case;		//  1. (Error : 2100)
	int			m_nElevator2Case;		//  2. (Error : 2200)
	int			m_nElevator3Case;		//  3. (Error : 2300)
	int			m_nElevator4Case;		//  4. (Error : 2400)
	int			m_nElevator5Case;		//  5. (Error : 2500)
	int			m_nElevator6Case;		//  6. (Error : 2600)
	int			m_nElevator7Case;		//  7. (Error : 2700)
	int			m_nTransfer1Case;		//  8. (Error : 3000)
	int			m_nTransfer2Case;		//  9. (Error : 3500)
	int			m_nLoadStage1Case;		// 10. (Error : 4000)
	int			m_nLoadStage2Case;		// 11. (Error : 4500)
	int			m_nLoadPicker1Case;		// 12. (Error : 5000)
	int			m_nLoadPicker2Case;		// 13. (Error : 5500)
	int			m_nVisionStage1Case;	// 14. (Error : 6000)
	int			m_nVisionStage2Case;	// 15. (Error : 6200)
	int			m_nVisionStage3Case;	// 16. (Error : 6400)
	int			m_nVisionStage4Case;	// 17. (Error : 6600)
	int			m_nUnloadPicker1Case;	// 18. (Error : 7000)
	int			m_nUnloadPicker2Case;	// 19. (Error : 7500)
	int			m_nNGStage1Case;		// 20. (Error : 8000)
	int			m_nNGStage2Case;		// 21. (Error : 8200)
	int			m_nGoodStage1Case;		// 22. (Error : 8400)
	int			m_nGoodStage2Case;		// 23. (Error : 8600)
	int			m_nShipAlignCase;		// 24. (Error : 8800)

	CLoopTimer	m_tElevator1Loop;		//  1. (Error : 2100)
	CLoopTimer	m_tElevator2Loop;		//  2. (Error : 2200)
	CLoopTimer	m_tElevator3Loop;		//  3. (Error : 2300)
	CLoopTimer	m_tElevator4Loop;		//  4. (Error : 2400)
	CLoopTimer	m_tElevator5Loop;		//  5. (Error : 2500)
	CLoopTimer	m_tElevator6Loop;		//  6. (Error : 2600)
	CLoopTimer	m_tElevator7Loop;		//  7. (Error : 2700)
	CLoopTimer	m_tTransfer1Loop;		//  8. (Error : 3000)
	CLoopTimer	m_tTransfer2Loop;		//  9. (Error : 3500)
	CLoopTimer	m_tLoadStage1Loop;		// 10. (Error : 4000)
	CLoopTimer	m_tLoadStage2Loop;		// 11. (Error : 4500)
	CLoopTimer	m_tLoadPicker1Loop;		// 12. (Error : 5000)
	CLoopTimer	m_tLoadPicker2Loop;		// 13. (Error : 5500)
	CLoopTimer	m_tVisionStage1Loop;	// 14. (Error : 6000)
	CLoopTimer	m_tVisionStage2Loop;	// 15. (Error : 6200)
	CLoopTimer	m_tVisionStage3Loop;	// 16. (Error : 6400)
	CLoopTimer	m_tVisionStage4Loop;	// 17. (Error : 6600)
	CLoopTimer	m_tUnloadPicker1Loop;	// 18. (Error : 7000)
	CLoopTimer	m_tUnloadPicker2Loop;	// 19. (Error : 7500)
	CLoopTimer	m_tNGStage1Loop;		// 20. (Error : 8000)
	CLoopTimer	m_tNGStage2Loop;		// 21. (Error : 8200)
	CLoopTimer	m_tGoodStage1Loop;		// 22. (Error : 8400)
	CLoopTimer	m_tGoodStage2Loop;		// 23. (Error : 8600)
	CLoopTimer	m_tShipAlignLoop;		// 24. (Error : 8800)

private:
	BOOL Run_Elevator1();				//  1. (Error : 2100)
	BOOL Run_Elevator2();				//  2. (Error : 2200)
	BOOL Run_Elevator3();				//  3. (Error : 2300)
	BOOL Run_Elevator4();				//  4. (Error : 2400)
	BOOL Run_Elevator5();				//  5. (Error : 2500)
	BOOL Run_Elevator6();				//  6. (Error : 2600)
	BOOL Run_Elevator7();				//  7. (Error : 2700)
	BOOL Run_Transfer1();				//  8. (Error : 3000)
	BOOL Run_Transfer2();				//  9. (Error : 3500)
	BOOL Run_LoadStage1();				// 10. (Error : 4000)
	BOOL Run_LoadStage2();				// 11. (Error : 4500)
	BOOL Run_LoadPicker1();				// 12. (Error : 5000)
	BOOL Run_LoadPicker2();				// 13. (Error : 5500)
	BOOL Run_VisionStage1();			// 14. (Error : 6000)
	BOOL Run_VisionStage2();			// 15. (Error : 6200)
	BOOL Run_VisionStage3();			// 16. (Error : 6400)
	BOOL Run_VisionStage4();			// 17. (Error : 6600)
	BOOL Run_UnloadPicker1();			// 18. (Error : 7000)
	BOOL Run_UnloadPicker2();			// 19. (Error : 7500)
	BOOL Run_NGStage1();				// 20. (Error : 8000)
	BOOL Run_NGStage2();				// 21. (Error : 8200)
	BOOL Run_GoodStage1();				// 22. (Error : 8400)
	BOOL Run_GoodStage2();				// 23. (Error : 8600)
	BOOL Run_ShipAlign();				// 24. (Error : 8800)
	BOOL Run_Simulation();				// 99.

	BOOL Check_Transfer1(int &nFmTarget, int &nToTarget, int &nPortNo);
	BOOL Check_Transfer2(int &nFmTarget, int &nToTarget, int &nPortNo);
	BOOL Check_TrayEmpty();
	BOOL Check_LotEndUnloadPicker(CString sLotID, int nPortNo);
	BOOL Check_LotEndUnloadNG(CString sLotID, int nPortNo, int nPickNo);
	BOOL Check_LotEndNGTray(CString sLotID, int nPortNo, int nNo);
	BOOL Check_LotEndENGTray(CString sLotID, int nPortNo);
	BOOL Check_LotEndTray(CString sLotID, int nPortNo);
	BOOL Check_Load12Empy();
	BOOL Check_AlignData(int nPortNo);
	BOOL Check_AlignDataAdd(int nPortNo);
	BOOL Check_LoadModule(int &nYNo);
	BOOL Check_EmptyUnloadPicker();
	BOOL Check_EmptyLoadTray();
	BOOL Check_ModuleEmpty();
	BOOL Check_InspectDone(int nPNo, int nPortNo, int nTrayNo);
	BOOL Check_ROSDone(int nPNo, int nPortNo, int nTrayNo);
	BOOL Check_JudgeDone(int nPNo, int nPortNo, int nTrayNo);
	BOOL Check_ShipAlign(int &nJobNo);
	int  Check_NGExist(int nPNo, int &nJNo);
	int  Check_GoodExist(int nPNo, int &nPosX, int &nPosY);
	BOOL Select_NGTrayPoketNo(int nType, int &nPosX, int &nPosY);
	BOOL Select_GoodTrayPoketNo(int nPNo, int nTNo, int &nPosX, int &nPosY);
	BOOL Check_NGTrayFull();
	BOOL Check_GooodTrayFull();
	BOOL LotEnd_Run();
	BOOL Check_EemptyLoadPicker(int nPNo);
	BOOL Check_EemptyVisionStage(int nVNo);
	BOOL Check_ElevatorSearch(int nENo);
	BOOL Check_EmptyNGTray();
	BOOL Check_EmptyGoodTray();
	BOOL Check_LotRun(int nSNo, int nPortNo);
	BOOL Check_LotEndNG();
	BOOL Search_Module(CString sLotID, CString sModuleID);
	int  Get_NGCmCount(int nStageNo);

	void Set_NextLot(CString sLotID, DWORD dwTime);
	void Set_AlignData(int nPortNo);
	void Set_AlignToStage(int nPortNo);

public:
	double	m_dBtmZ, m_dTop1Z, m_dTop2Z;

	void Begin_MainRunThread();
	void End_MainRunThread();
	void Run_Replay();
	
	BOOL Is_MainThreadRun() { return m_bThreadMainRun; }
	
	void Reset_MainRunCase();
	int *Get_pMainRunCase();
	int  Get_MainRunCase(int nRun);
	void Set_MainRunCase(int nRun, int nCase);
	void Set_MainRunLoop(int nRun, int nLoop);

	BOOL Get_IsAutoRun();
	void Set_ClearRunData(int nType);

	void Init_AlignTray();
	void Init_LoadTray();
	void Init_NgTray(int nStageNo);
	void Init_GoodTray(int nStageNo);
	void Init_ShiipAlignData(int nJobNo);

	BOOL Set_LotStart(CString sLotID, int nPortNo);
	void Set_LotEnd(CString sLotID, int nPortNo);
	void Set_InspectDone(int nPNo, int nPortNo, int nTrayNo);
	void Set_ReInspectDone(int nPNo, int nPortNo, int nTrayNo);
	void Set_ROSDone(int nPNo, int nPortNo, int nTrayNo);
	void Set_ROSTime(int nPNo, int nPortNo, int nTrayNo);
	void Beep_Post(int nTime);
	BOOL Get_TrayPosition(int nPNo, int nJobNo, int nPosX, int nPosY, double &dToPosX, double &dToPosY); //nJobNo(1~4)
};

extern CSequenceMain g_objSequenceMain;

///////////////////////////////////////////////////////////////////////////////
