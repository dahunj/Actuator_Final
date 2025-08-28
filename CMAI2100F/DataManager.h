// DataManager.h : 헤더 파일
//
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Equip Data
typedef struct tag_EQUIP_DATA {
	CString sPCID;
	CString sMachineCode;
	CString sEquipName;
	CString sModelName;
	int		nLotBarcodePort;
	BOOL	bUseDoorLock;
	BOOL	bUseTaktLog;
	BOOL	bUseMES;
	BOOL	bUseMESRcpCheck;
	BOOL	bUseLightCurtain;
	BOOL	bUseCosmeticNG;
	int		nNoWorkTime;
	int		nLogDate;

	BOOL	bUseAlign1;
	BOOL	bUseAlign2;
	BOOL	bUseBottom;
	BOOL	bUseTop1;
	BOOL	bUseTop2;
	BOOL	bUseBotAng;
	BOOL	bUseTopAng;
	BOOL	bUseROS;
	BOOL	bUseCMCheck;	// CM Check가 안되는 샘플이 있어 추가.
	BOOL	bUseNGSort;
	BOOL	bUseNGSize;
	BOOL	bUseGoodSort;
	BOOL	bElevatorAlign;
	BOOL	bUseInspectBlow;
	BOOL	bUsePassGood;
	BOOL	bUseOppAlarm;
	int		nTrayBase[10][4];

	int		nTrayCountX;	//4
	int		nTrayCountY;	//10
	double	dTrayPitchX;		
	double	dTrayPitchY;

	double	dPitchBtm;
	double	dPitchTop;

	BOOL	bTower[6][7];	// [0:None,1:Init,2:Ready,3:Run,4:Alarm,5:Emer][0:Green,1:Yellow,2:Red,3:Flicker,4:Buzz1,5:Buzz2,6:Flicker]
	BOOL	bBuzzer[2][5];	// [0::Alarm,1:Error][0:Bit0,1:Bit1,2:Bit2,3:Bit3,4:Bit4]
	CString	sPasswordMt;
	CString	sPasswordSi;
	CString	sPasswordPm;
	int		nDryRunNg;		// DryRun Test NG Ratio (0~100)

	int		nDelayTime[11];	//0:Load Oepn,1:Load Close,2:BTM Scan,3:Top1 Scan,4:Vacuum On Delay Time,
							//5:Load Align,6:Ship Align,7:Unload Oepn,8:Unload Close,9:Top2 Scan, 10:LoadPicker CM Check
	int		nTimeOver[2];	//0:Insepction, 1:ROS
	BOOL	bUseAutoSkip;
	BOOL	bUseMesNg;
	BOOL	bUseDisplay;
	double	dTranZOverride;
	double	dSpeedZOverride;
	CString sPROG_VER;
	CString sPARA_VER;
} EQUIP_DATA;

///////////////////////////////////////////////////////////////////////////////
// Move Data
typedef struct tag_MOVE_DATA {
	double  dElevatorZ1[5];			// AXIS 00
	double  dElevatorZ2[5];			// AXIS 01
	double  dElevatorZ3[5];			// AXIS 02
	double  dElevatorZ4[5];			// AXIS 03
	double  dElevatorZ5[5];			// AXIS 04
	double  dElevatorZ6[5];			// AXIS 05
	double  dElevatorZ7[5];			// AXIS 06
	double  dTransferX1[10];		// AXIS 07
	double  dTransferZ1[15];		// AXIS 08
	double  dTransferX2[15];		// AXIS 09
	double  dTransferZ2[15];		// AXIS 10
	double  dLoadStageY1[7];		// AXIS 11
	double  dLoadStageY2[7];		// AXIS 12
	double  dLoadPickerX1[5];		// AXIS 13
	double  dLoadPickerY1[5];		// AXIS 14
	double  dLoadPickerZ1[5];		// AXIS 15
	double  dLoadPickerP1[5];		// AXIS 16
	double  dLoadPickerX2[5];		// AXIS 17
	double  dLoadPickerY2[5];		// AXIS 18
	double  dLoadPickerZ2[5];		// AXIS 19
	double  dLoadPickerP2[5];		// AXIS 20
	double  dBTMFocusZ[5];			// AXIS 21
	double  dBTMLightZ[5];			// AXIS 22
	double  dBTMAngleY[5];			// AXIS 23
	double  dTOPVisionZ1[5];		// AXIS 24
	double  dTOPVisionZ2[5];		// AXIS 25
	double  dVisionStageX1[5];		// AXIS 26
	double  dVisionStageX2[5];		// AXIS 27
	double  dVisionStageX3[5];		// AXIS 28
	double  dVisionStageX4[5];		// AXIS 29
	double  dUnloadPickerX1[20];	// AXIS 30
	double  dUnloadPickerY1[9];		// AXIS 31
	double  dUnloadPickerZ1[9];		// AXIS 32
	double  dUnloadPickerP1[9];		// AXIS 33
	double  dUnloadPickerX2[20];	// AXIS 34
	double  dUnloadPickerY2[9];		// AXIS 35
	double  dUnloadPickerZ2[9];		// AXIS 36
	double  dUnloadPickerP2[9];		// AXIS 37
	double  dGoodStageY1[6];		// AXIS 38
	double  dGoodStageY2[6];		// AXIS 39
	double  dNGStageY1[6];			// AXIS 40
	double  dNGStageY2[6];			// AXIS 41
	double  dShiipAling[5];			// AXIS 42
	double  dTop1LightZ[5];			// AXIS 43
	double  dTop1AngleY[5];			// AXIS 44
} MOVE_DATA;

/////////////////////////////////////////////////////////////////////////////////
// Idle Code Data
typedef struct tag_IDLE_DATA {
	int		nCount;
	CString	sCode[100];
	CString	sText[100];
} IDLE_DATA;

///////////////////////////////////////////////////////////////////////////////
// ROS Data
typedef struct tag_ROS_DATA {
	CString sHandlerIp;
	int		nJudgeTimeOver;
	CList<CString, CString&> lstMdjIp;
} ROS_DATA;

///////////////////////////////////////////////////////////////////////////////

class CDataManager
{
public:
	CDataManager();
	virtual ~CDataManager();

private:
	EQUIP_DATA	m_EquipData;
	MOVE_DATA	m_MoveData;
	MOVE_DATA	m_MoveInput;
	IDLE_DATA	m_IdleData;
	ROS_DATA	m_RosData;

public:	
	void Reset_EquipData();
	void Reset_MoveData();
	void Reset_MoveInput();
	void Reset_IdleData();
	void Reset_RosData();

	BOOL Read_EquipData();
	BOOL Read_ModelEquipData(CString strPath);
	BOOL Save_MoveData();
	BOOL Read_MoveData();
	BOOL Read_MoveInput();
	BOOL Read_ModelMoveData(CString strPath);
	BOOL Read_IdleData();
	BOOL Read_RosData();
	BOOL Read_NGTraySort();
	void Save_RosData();

	EQUIP_DATA *Get_pEquipData() { return &m_EquipData; }
	MOVE_DATA *Get_pMoveData() { return &m_MoveData; }
	MOVE_DATA *Get_pMoveInput() { return &m_MoveInput; }
	IDLE_DATA *Get_pIdleData() { return &m_IdleData; }
	ROS_DATA *Get_pRosData() { return &m_RosData; }
};

extern CDataManager g_objDataManager;

///////////////////////////////////////////////////////////////////////////////
