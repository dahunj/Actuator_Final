// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.

#include <afxdisp.h>        // MFC 자동화 클래스입니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

///////////////////////////////////////////////////////////////////////////////

// Library Add
#include "LedStatic.h"
#include "CSControls.h"
#include "CSIniFile.h" 
#include "CSComPort.h"
#include "CSUdpSocket.h"
#include "CSServerSocket.h"
#include "CSClientSocket.h"
#include "CSGrid.h"
#include "CSUdpClient.h"
#ifdef _DEBUG
	#pragma comment(lib, "CSControlsD.lib")
	#pragma comment(lib, "CSIniFileD.lib")
	#pragma comment(lib, "CSComPortD.lib")
	#pragma comment(lib, "CSUdpSocketD.lib")
	#pragma comment(lib, "CSServerSocketD.lib")
	#pragma comment(lib, "CSClientSocketD.lib")
	#pragma comment(lib, "CSGridD.lib")
	#pragma comment(lib, "CSUdpClientD.lib")
#else
	#pragma comment(lib, "CSControlsR.lib")
	#pragma comment(lib, "CSIniFileR.lib")
	#pragma comment(lib, "CSComPortR.lib")
	#pragma comment(lib, "CSUdpSocketR.lib")
	#pragma comment(lib, "CSServerSocketR.lib")
	#pragma comment(lib, "CSClientSocketR.lib")
	#pragma comment(lib, "CSGridR.lib")
	#pragma comment(lib, "CSUdpClientR.lib")
#endif

//****************************************************************************
#define NEW_FINAL		//Final_New(Final2호기부터적용)
//****************************************************************************
//#define AJIN_BOARD_USE

#ifdef NEW_FINAL
	#define MAIN_VERSION	"Vf2 3.0.4"
#else
	#define MAIN_VERSION	"Vf1 3.0.4"
#endif
#define MES_WAITTIME	30000//5000	//10초
#define MAX_CM			640
#define TRAY_MAX_CM		40
#define TRAY_CM_X		4
#define TRAY_CM_Y		10
#define TRAY_PITCH		12
#define ELEVATOR_UD		5.0
#define ELEVATOR_DN		4.0
#define ELEVATOR_SL		0.5
#define ALIGN_TOP1_POS	30.0

#define ECM_LOG			"D:\\EVMS\\TP\\LOG\\"
#define ECM_ME_LOG		"D:\\EVMS\\TP\\LOGL\\"
#define SKIP_LOT		"GPQ"
#define SIM_WAITTIMES	 5		//
#define SIM_WAITTIMEM	 5		//


//****************************************************************************
//#define RESULT_TEST		// 비전 FOB 모드에서 전체 양품 처리가 안되어 추가함.
//#define ALIGN_TEST		// Align 반복 Test.
//****************************************************************************

extern CString gsCurrentDir;	// 현재 프로젝트 폴더
extern CString gsComputerName;	// 현재 컴퓨터 이름
typedef struct 
{
	// 검사결과 (0:Empty, 1:미검사, 2:Good, 3:NG, 4:ROS_NG, 5:Barcode, 6:MES_NG, 7:FAI치수불량)
	int		InfoAlignTray[10][4];		// (y,x) 0:Empty, 1:NG      2:Good
	int		InfoLoadTray[10][4];		// (y,x) 0:Empty, 1:Module, 2:Good, NG:3~
	int		InfoLoadPick[2][10];		//[0~7]:상태 [9]:Module시작번호 
	int		InfoVision[4][10];
	int		InfoUnloadPick[2][10];
	int		InfoNgTray[10][4];
	int		InfoGoodTray[10][4];

	CString	sLotID_Start;
	CString	sLotID_Tansfer[3];
	CString	sLotID_LoadStage[3];
	CString	sLotID_LoadPicker[3];
	CString	sLotID_VisionStage[5];
	CString	sLotID_UnloadPicker[3];
	CString	sLotID_NGTray[3];
	CString	sLotID_GoodTray[3];
	CString	sLotID_NGBuffer;
	int		nTrayNo_Tansfer[2];
	int		nTrayNo_LoadStage[2];
	int		nTrayNo_LoadPicker[2];
	int		nTrayNo_VisionStage[4];
	int		nTrayNo_UnloadPicker[2];
	int		nTrayNo_NGTray[2];
	int		nTrayNo_GoodTray[2];
	int		nTrayNo_NGBuffer;
	int		nPortNo_Tansfer[2];
	int		nPortNo_LoadStage[2];
	int		nPortNo_LoadPicker[2];
	int		nPortNo_VisionStage[4];
	int		nPortNo_UnloadPicker[2];
	int		nPortNo_NGTray[2];
	int		nPortNo_GoodTray[2];
	int		nPortNo_NGBuffer;
	int		nVisionPos[2][5];		//0:Down, 1:Up
	int		nElevatGDTray[2];		//0:Empty,1:LotTray, 2:LotEnd
	int		nNGLot_NGTray[2];		//1:LotEnd
	int		nNGLot_Transfer;		//1:LotEnd
	int		nNGLot_NGBuffer;		//1:LotEnd

	int		nUserLevel;				// OP , Engineer
	CString strUserName;			// LogIn 
	CString	sOperID;				// Operator
	CString	sRecipeName;			// Recipe Item
	BOOL	bCycleStop;				// Run 중간에 멈출때 (초기화 필요)
	BOOL	bUseDryRun;
	BOOL	bAlignScanDone;
	BOOL	bBTMScanDone;
	BOOL	bTop1ScanDone;
	BOOL	bTop2ScanDone;
	BOOL	bAlignA1Done;
	CString sAlarmTime[3];
	CString sAlarmList[3];
	int		m_nMS;
	BOOL	m_bTowerOn;
	BOOL	m_bBuzzerOff;
	BOOL	bDoorLock;
	BOOL	bAlarmShow;
	BOOL	bJahwa;
	BOOL	bDoorOpen;

	int		nTransferX1Pos;			//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)
	int		nTransferX2Pos;			//1(LS1),2(LS2),3(L1),4(L2),5(EN),6(EG),7(NB),8(U1),9(U2),10(NG1),11(NG2),12(Good1),13(Good2)
	int		nElevatorOpen[10];		//0:Stop,1:Open,2:Opened //1(L1),2(L2),3(EN),4(EG),5(NB),6(U1),7(U2)
	int		nUnloadPick1OpenCnt;
	int		nUnloadPick2OpenCnt;
	int		nUnloadPick1DownCnt;
	int		nUnloadPick2DownCnt;
	int		nTop1Cnt;
	int		nTop2Cnt;

	int		nLoadPicker1ErrNo[8];
	int		nLoadPicker2ErrNo[8];
	int		nVisionVacErrNo[8];
	int		nUnloadPicker1ErrNo[8];
	int		nUnloadPicker2ErrNo[8];
	int		nVisionStageNo;

	int		nDay_TotalCnt;
	int		nDay_NGCnt;
	int		nDay_GoodCnt;

	int		nSelectNo;
	CString sListName;
	CString sYYMMDD;

	int		nLanguage;			//0:Kor, 1:Eng
	CString	sComName;
	int		nRejectMaxCount;
	int		nRejectLotCount;

	//A2 3Point Align Data
	BOOL	bAlignShipDone;
	double	dAlignVisionX[4][3];
	double	dAlignVisionY[4][3];
	int		nLPCount1;
	int		nLPCount2;
	double	dAlignX;	//편차의기준값
	double	dAlignY;	//편차의기준값

	int		nSlideTime;		//Sec
	DWORD	dwSlideTime[7];
	int		nDoorLockTime;	//Min
	DWORD	dwDoorStartTime;

	BOOL	bInpectLotEnd;
	BOOL	bResultTest;	// 비전FOB 모드로 전체양품이 안되어 반복성을 돌릴수 없다.
	double	dElevatorDown;
	int		nVsNo[2];
	int		nVsIx[2];
	CString sOffsetInfor[3];
	double	dFocusOffset[4][8];	//Top1:1~4, Top2:5~8
	int		nVisionNo;
	double	dElevatorZPos[2][7];
	CString sReadyRecipe;
	int		nROSReqCount;
	int		nMgnTrayCount;

	CString sStdMotionFile;
	CString sEfficiencyFile;
	int		nStdEqNo;	// Log 표준화 (설비번호)
	int		nStdLotNo;	// Log 표준화 (하루 기준으로 작업한 Lot 번호)
	int		nStdLogDay;	// Log 표준화 (설비번호)
	int		nTotLotNo[6];
	int		nLoadAlignRetry;
	int		nScanRetry[3];	//0:BTM, 1:T1, 2:T2
	int		nNG_MC[5][2];	//0:MC, 1:GF, 2:Barcode, 3:Vision-timover, 4:MES_NG

	BOOL	bUseBarSort;
	int		nBarSortTray;	//1:MG, 2:Good
	int		nNoReadNo;

	bool		bRMSDone;
} GLOVAL_DATA;

typedef struct {
	int		nJobCycle;
	int		nJobStatus;		//0:Idle, 1:Run, 2:End
	CString	sLotID[6];
	int		nCmCount[6];
	CString	sRecipeName[6];
	int		nTrayCount[6];
	int		nLastCount[6];	//잔량
	int		nLotStatus[6];	//0:Wait, 1:Run, 3:Lot_End
	BOOL	bEmptyTray[6];
	BOOL	bEmptyNGTray[6];
	int		nTrayOutCnt[6];
	int		nOutTrayCnt[6][2];	//0:Good, 1:NG
	int		nTrayPutCnt[6][3];	//0:Good, 1:NG, 2:Load
	int		nGoodCount[6];
	int		nNgCount[6];
	int		nSkipCount[6];
	int		nJudge_I[6][20][40][6];	//2:G, 3:NG,     5:BAR_NOREAD, 6:MES_NG, 7:FAI치수불량
	int		nJudge_R[6][20][40];	//2:G, 3:ROS_NG, 4:ROS_Repair
	CString sNGCode_I[6][20][40][6];
//	CString sNGCode_R[6][20][40];
	CString sBarCode[6][20][40];
	int		nRosJugCount[6][13];		//0:Count, 1:Good, 2:RTOver 3:NG, 4:Repair, 5:Bar_NoRead,MES-NG,MC, 6:FAI_NG(치수불량), 7:Bar, 8:MES-NG, 9:MC, 10:Ros Skip, 11:허수배출, 12:Marginal
	int		nHistory[6][20][40][10];
	int		nAlignCount[6];
	//0:LoadStageNo(1,2),1:LoadPickerHeadNo(1,2),2:LoadPickerNo(1~8),3:VisionStageNo(1~4),4:UnloadPickerHeadNo(1,2),
	//5:GoodTrayNo(1~8),6:NGTrayNo(1~8),7:Unload_PorketNo(1~40),8:Unload_StagetNo(1,2)
	int		nImageCnt[6][20][40];
	int		nMarginal[6][20][40];		//1~5:Final_Marginal, 9:DFA_Marginal

	//Result
	CString	sRstLotID[6];
	int		nRstCmCount[6];
	int		nRstGoodCount[6];
	int		nRstNgCount[6];
	int		nUnlGdTrayCount[6];
	int		nUnlNGTrayCount[6];
	CString	sUnLastLotID;
	int		nUnLastPortID;

	CString sLLStartTime[6];
	CString sLLEndTime[6];
	DWORD	dwLLLotStart[6];
	DWORD	dwLLLotEnd[6];
	double  dLLTackTime[6];
	CString sLLSHHMMSS[6];
	CString sLLEHHMMSS[6];

	BOOL	bMESStart;
	CString sMESStartTime[6];
	CString sMESEndTime[6];
	CString	sELotID;
	int		nRunPortNo;
	int		nErrorCount[6];
	DWORD	dwErrorTime[6];
	DWORD	dwStopTime[6];

	//JobList
	int		nJobNo;
	int		nJobPortNo[10];
	CString	sJobLotID[10];
	int		nJobCmCount[10];
	int		nJobGoodCount[10];
	int		nJobNgCount[10];
	double	dJobRate[10];
	CString	sJobStartTime[10];
	CString	sJobEndTime[10];
	double	dJobTack[10];
} GLOVAL_LOT;

typedef struct {
	BOOL	bBegin;
	int		nAlmNo;
	int		nPortNo;
	CString sAlmMsg;
	CString sStartTime;
	CString sEndTime;
	CString sLotID;
	CString sSpcInfo;
	CString sUnit;
	CString sGroup;
	CString sItems;
	DWORD	dwStartTime;
	DWORD	dwEndTime;
	DWORD	dwProcTime;
	CString sAlmLotID[3];
	double  dMotionChkPos;
	double  dMotionPos[50];
	BOOL	bStage[20];
	int		nAlignCount;
	CString sAlmLID[5];	//0:검사,1;BTM,2:Top1,3:Top2
	int		nAlmTNo[5];	//0:검사,1;BTM,2:Top1,3:Top2
	int		nAlmPNo[5];	//0:검사,1;BTM,2:Top1,3:Top2

	int		nTempPNo;
	int		nTempTNo;
	int		nTempMNo;
} GLOVAL_ALM;

typedef struct {
	int		nLotStatus[6];					// 0:None, 1:Start Send, 2:Lot수신1, 3:Lot수신2, 4:Lot시작송신, 9:Lot취소
	DWORD	dwMesTime;

	// 장비 실적 Data
	int			nCmResult[6][20][40];		// 0:Not Receive, 1:Good Done, 2:NG Done

	// Host Data
	int			nHostRcvCmCount;			// Host 수신 Lot당 CM 총갯수
	CString		sHostRecipe[6];				// Host 수신 Recipe
	int			nHostCmCount[6];			// Host 수신 Lot당 CM 총갯수
	CString		sHostVendor;				// Host 수신 Vendor Type
	CString		sHostConfig;				// Host 수신 Config Code
	CString		sMESConfig;					// Host 수신 Config Code

	CString		sHostLotIDTemp;					// Host 수신 LotID
	CString		sHostRecipeTemp;				// Host 수신 Recipe

	// Cancel Data
	CString		sHostCancelLotId;
	CString		sHostCancelModule;			// Host Cancel 수신 code
	CString		sHostCancelCode;			// Host Cancel 수신 code
	CString		sHostCancelText;			// Host Cancel 수신 내용

	//NG LOT
	int			nMarStatus;					// 0:None, 1:요청, 2:Start수신 Run, 3:End송신
	int			nManualEnd;					// 0:None, 1:수동완공
	int			nNGLotCount;				// NGLot 모듈수량
	int			nMarCount;					// Marginal 모듈수량
	int			nMarTrayCount;				// Marginal Tray수량
	int			nNoReadCount;				// Barocode NoRead 수량
	CString		sHostNGLotID;				// Host 수신 NG LotID
	CString		sHostNGVendor;				// Host 수신 Vendor Type
	CString		sHostNGConfig;				// Host 수신 Config Code
	CString		sStartTime;					// NGLot 시작시간
	CString		sEndTime;					// NGLot 완공시간
	CString		sGUItNGLotID;				// 화면Display용 NG LotID
	int			nGUICount[5];				// 화면Display용 수량

	int			nLotConfirm[3];

	int			nRMSStep;
} GLOVAL_MES;

typedef struct {
	int		nCount;
	CString	sModuleID[5000];
} GLOVAL_BARCODE;

extern GLOVAL_DATA		gData;
extern GLOVAL_LOT		gLot;
extern GLOVAL_ALM		gAlm;
extern GLOVAL_MES		gMes;
extern GLOVAL_BARCODE	gBar;

/*
typedef struct {
	CString		sNGCode[6][16][40][5][10];	//Port[6],TrayNo[16],Module[40],Inspection[5],NG-Code[10]
	CString		sModuleID[6][640][10];		//Port[6],Module[640], //0:MODULEID,1:SITE,2:EQPID,3:EQPNAME,4:TOOL_CAVITY,5:PARA,6:DATE,7:ROS_JUDGE,8:DFA_LOTID,9:POCKETNO
	int			nTrayOX[3][2];				//1:Exist
} GLOVAL_NGCODE;
extern GLOVAL_NGCODE	gNG;
*/

typedef struct {
	CString		sNGCode[6][16][40][5][10];	//Port[6],TrayNo[20],Module[40],Inspection[5],NG-Code[10]
	CString		sModuleID[6][640][10];		//Port[6],Module[640], //0:MODULEID,1:SITE,2:EQPID,3:EQPNAME,4:TOOL_CAVITY,5:PARA,6:DATE,7:ROS_JUDGE,8:DFA_LOTID,9:POCKETNO
	int			nTrayOX[3][2];				//1:Exist
} GLOVAL_NGCODE;
extern GLOVAL_NGCODE* gNG;

#define LOAD_STAGE	0
#define GOOD_STAGE	2
#define NG_STAGE	1

typedef struct {
	int		nType;			//nType:1[정시], 2[해제] 3[설정]
	int		nOpenStart;		//1:Start
	DWORD	dwOpenStartTime;
	int		nOpenTime;
	int		nLogYY;		//등록년
	int		nLogMM;		//등록월
	int		nLogDD;		//등록날
	int		nLogHH;		//등록시간
} GLOVAL_INTERLOCKDATA;
extern  GLOVAL_INTERLOCKDATA	gIt;


#define UNLOAD_PICKER1_X_GOOD_STAGE1_1_1 5
#define UNLOAD_PICKER1_X_GOOD_STAGE2_1_1 6
#define UNLOAD_PICKER1_X_NG_STAGE1_1_1 7
#define UNLOAD_PICKER1_X_NG_STAGE2_1_1 8

#define UNLOAD_PICKER1_X_GOOD_STAGE1_4_1 9
#define UNLOAD_PICKER1_X_GOOD_STAGE1_4_10 10
#define UNLOAD_PICKER1_X_GOOD_STAGE2_4_1 11
#define UNLOAD_PICKER1_X_GOOD_STAGE2_4_10 12

#define UNLOAD_PICKER1_X_NG_STAGE1_4_1 13
#define UNLOAD_PICKER1_X_NG_STAGE1_4_10 14
#define UNLOAD_PICKER1_X_NG_STAGE2_4_1 15
#define UNLOAD_PICKER1_X_NG_STAGE2_4_10 16


#define UNLOAD_PICKER1_Y_GOOD_STAGE1 5
#define UNLOAD_PICKER1_Y_GOOD_STAGE2 6
#define UNLOAD_PICKER1_Y_NG_STAGE1 7
#define UNLOAD_PICKER1_Y_NG_STAGE2 8




#define UNLOAD_PICKER2_X_GOOD_STAGE1_1_1 5
#define UNLOAD_PICKER2_X_GOOD_STAGE2_1_1 6
#define UNLOAD_PICKER2_X_NG_STAGE1_1_1 7
#define UNLOAD_PICKER2_X_NG_STAGE2_1_1 8

<<<<<<< HEAD
#define UNLOAD_PICKER2_X_GOOD_STAGE1_4_1 9
#define UNLOAD_PICKER2_X_GOOD_STAGE1_4_10 10
#define UNLOAD_PICKER2_X_GOOD_STAGE2_4_1 11
#define UNLOAD_PICKER2_X_GOOD_STAGE2_4_10 12

#define UNLOAD_PICKER2_X_NG_STAGE1_4_1 13
#define UNLOAD_PICKER2_X_NG_STAGE1_4_10 14
#define UNLOAD_PICKER2_X_NG_STAGE2_4_1 15
#define UNLOAD_PICKER2_X_NG_STAGE2_4_10 16

#define UNLOAD_PICKER2_Y_GOOD_STAGE1 5
#define UNLOAD_PICKER2_Y_GOOD_STAGE2 6
#define UNLOAD_PICKER2_Y_NG_STAGE1 7
#define UNLOAD_PICKER2_Y_NG_STAGE2 8

#define UNLOAD_PICKER1_X_VISION_STG1 1
#define UNLOAD_PICKER1_X_VISION_STG2 2
#define UNLOAD_PICKER1_X_VISION_STG3 3
#define UNLOAD_PICKER1_X_VISION_STG4 4

#define UNLOAD_PICKER2_X_VISION_STG1 1
#define UNLOAD_PICKER2_X_VISION_STG2 2
#define UNLOAD_PICKER2_X_VISION_STG3 3
#define UNLOAD_PICKER2_X_VISION_STG4 4
=======

const int UNLOADPICKER1_X_Ready = 0;
const int UNLOADPICKER1_X_InspectionStage1 = 1;
const int UNLOADPICKER1_X_InspectionStage2 = 2;
const int UNLOADPICKER1_X_InspectionStage3 = 3;
const int UNLOADPICKER1_X_InspectionStage4 = 4;
const int UNLOADPICKER1_X_NGStage1_1_1 = 5;
const int UNLOADPICKER1_X_NGStage2_1_1 = 6;
const int UNLOADPICKER1_X_GoodStage1_1_1 = 7;
const int UNLOADPICKER1_X_GoodStage2_1_1 = 8;
const int UNLOADPICKER1_X_NGStage1_1_4 = 9;
const int UNLOADPICKER1_X_NGStage1_1_10 = 10;
const int UNLOADPICKER1_X_NGStage2_1_4 = 11;
const int UNLOADPICKER1_X_NGStage2_1_10 = 12;
const int UNLOADPICKER1_X_GoodStage1_1_4 = 13;
const int UNLOADPICKER1_X_GoodStage1_1_10 = 14;
const int UNLOADPICKER1_X_GoodStage2_1_4 = 15;
const int UNLOADPICKER1_X_GoodStage2_1_10 = 16;

const int UNLOADPICKER1_Y_Ready = 0;
const int UNLOADPICKER1_Y_InspectionStage1 = 1;
const int UNLOADPICKER1_Y_InspectionStage2 = 2;
const int UNLOADPICKER1_Y_InspectionStage3 = 3;
const int UNLOADPICKER1_Y_InspectionStage4 = 4;
const int UNLOADPICKER1_Y_NgStage1 = 5;
const int UNLOADPICKER1_Y_NgStage2 = 6;
const int UNLOADPICKER1_Y_GoodStage1 = 7;
const int UNLOADPICKER1_Y_GoodStage2 = 8;

const int UNLOADPICKER1_Z_Ready = 0;
const int UNLOADPICKER1_Z_InspectionStage1 = 1;
const int UNLOADPICKER1_Z_InspectionStage2 = 2;
const int UNLOADPICKER1_Z_InspectionStage3 = 3;
const int UNLOADPICKER1_Z_InspectionStage4 = 4;
const int UNLOADPICKER1_Z_NgStage1 = 5;
const int UNLOADPICKER1_Z_NgStage2 = 6;
const int UNLOADPICKER1_Z_GoodStage1 = 7;
const int UNLOADPICKER1_Z_GoodStage2 = 8;

const int UNLOADPICKER1_P_InspectionStage = 0;
const int UNLOADPICKER1_P_NGStage = 1;
const int UNLOADPICKER1_P_GoodStage = 2;


const int UNLOADPICKER2_X_Ready = 0;
const int UNLOADPICKER2_X_InspectionStage1 = 1;
const int UNLOADPICKER2_X_InspectionStage2 = 2;
const int UNLOADPICKER2_X_InspectionStage3 = 3;
const int UNLOADPICKER2_X_InspectionStage4 = 4;
const int UNLOADPICKER2_X_NGStage1_1_1 = 5;
const int UNLOADPICKER2_X_NGStage2_1_1 = 6;
const int UNLOADPICKER2_X_GoodStage1_1_1 = 7;
const int UNLOADPICKER2_X_GoodStage2_1_1 = 8;
const int UNLOADPICKER2_X_NGStage1_1_4 = 9;
const int UNLOADPICKER2_X_NGStage1_1_10 = 10;
const int UNLOADPICKER2_X_NGStage2_1_4 = 11;
const int UNLOADPICKER2_X_NGStage2_1_10 = 12;
const int UNLOADPICKER2_X_GoodStage1_1_4 = 13;
const int UNLOADPICKER2_X_GoodStage1_1_10 = 14;
const int UNLOADPICKER2_X_GoodStage2_1_4 = 15;
const int UNLOADPICKER2_X_GoodStage2_1_10 = 16;

const int UNLOADPICKER2_Y_Ready = 0;
const int UNLOADPICKER2_Y_InspectionStage1 = 1;
const int UNLOADPICKER2_Y_InspectionStage2 = 2;
const int UNLOADPICKER2_Y_InspectionStage3 = 3;
const int UNLOADPICKER2_Y_InspectionStage4 = 4;
const int UNLOADPICKER2_Y_NgStage1 = 5;
const int UNLOADPICKER2_Y_NgStage2 = 6;
const int UNLOADPICKER2_Y_GoodStage1 = 7;
const int UNLOADPICKER2_Y_GoodStage2 = 8;

const int UNLOADPICKER2_Z_Ready = 0;
const int UNLOADPICKER2_Z_InspectionStage1 = 1;
const int UNLOADPICKER2_Z_InspectionStage2 = 2;
const int UNLOADPICKER2_Z_InspectionStage3 = 3;
const int UNLOADPICKER2_Z_InspectionStage4 = 4;
const int UNLOADPICKER2_Z_NgStage1 = 5;
const int UNLOADPICKER2_Z_NgStage2 = 6;
const int UNLOADPICKER2_Z_GoodStage1 = 7;
const int UNLOADPICKER2_Z_GoodStage2 = 8;

const int UNLOADPICKER2_P_InspectionStage = 0;
const int UNLOADPICKER2_P_NGStage = 1;
const int UNLOADPICKER2_P_GoodStage = 2;
>>>>>>> develop/Vf3.0.6_UPHItem2
