// Common.h : 헤더 파일
//
#pragma once

#define AUTO_ELEVATOR_1			0
#define AUTO_ELEVATOR_2			1
#define AUTO_ELEVATOR_3			2
#define AUTO_ELEVATOR_4			3
#define AUTO_ELEVATOR_5			4
#define AUTO_ELEVATOR_6			5
#define AUTO_ELEVATOR_7			6
#define AUTO_TRANSFER_1			7
#define AUTO_TRANSFER_2			8
#define AUTO_LOAD_STAGE_1		9
#define AUTO_LOAD_STAGE_2		10
#define AUTO_LOAD_PICKER_1		11
#define AUTO_LOAD_PICKER_2		12
#define AUTO_VISION_STAGE_1		13
#define AUTO_VISION_STAGE_2		14
#define AUTO_VISION_STAGE_3		15
#define AUTO_VISION_STAGE_4		16
#define AUTO_UNLOAD_PICKER_1	17
#define AUTO_UNLOAD_PICKER_2	18
#define AUTO_NG_STAGE_1			19
#define AUTO_NG_STAGE_2			20
#define AUTO_GOOD_STAGE_1		21
#define AUTO_GOOD_STAGE_2		22
#define AUTO_SHIP_ALIGN			23

#define MANUAL_ELEVATOR1		31
#define MANUAL_ELEVATOR2		32
#define MANUAL_ELEVATOR3		33
#define MANUAL_ELEVATOR4		34
#define MANUAL_ELEVATOR5		35
#define MANUAL_ELEVATOR6		36
#define MANUAL_ELEVATOR7		37
// CCommon

enum E_USER
{
	E_USER_NONE = 0,
	E_USER_OP,
	E_USER_EN,
	E_USER_SY
};

class CCommon : public CWnd
{
	DECLARE_DYNAMIC(CCommon)

public:
	CCommon();
	virtual ~CCommon();

protected:
	DECLARE_MESSAGE_MAP()

private:
	BOOL		m_bInsideLight;	// Y0008 : Inside Light
	LONGLONG	m_nFreq;		// Frequence

protected:
	static UINT Thread_ErrorShow(LPVOID lpVoid);
	static UINT Thread_AlarmShow(LPVOID lpVoid);
public:
	CString	m_sMessage;

	void DoEvents();
	void uSleep(int msec);
	void MakeFolder(CString sPath);
	void Save_MotionPos();
	void Save_MotionPosIO();
	int  Save_MotionPosMo();
	int	 Check_MotionPos();
	BOOL Check_StageUpDown(CString &sMsg);
	BOOL Check_MoveData(int nAxis, int nMoveIdx, CString sData);

	BOOL Check_Position(int nAxis, int nMoveIdx, double dRange = 0.1);
	void Move_Position(int nAxis, int nMoveIdx, double dSpeed = 1.0);
	void Move_Override(int nAxis, int nMoveIdx, double dAt);

	void Show_Error(int nErrNo);
	void Show_ErrorT(int nErrNo);
	void Set_ErrorSubMessage(CString sErrSubMsg);
	void Show_Alarm(CString sMsg, int nFm=0);	//nFm=1:Host
	void Show_AlarmT(CString sMsg, int nFm=0);	//nFm=1:Host
	int Show_MsgBox(int nBtnCnt, CString sMsg);
	int Show_NumPad(CString sOld, CString &sNew, int nAxis = -1);
	int Show_KeyPad(CString &sKey);
	int Show_Password(int &nUser);

	BOOL Check_MainEmgAir();
	BOOL Check_MainDoor(BOOL bAuto=FALSE);
	BOOL Check_NGTrayFull();
	BOOL Check_TraySlide(int nType=0);	//0:Main, 1:초기화, 9:화면

	BOOL Check_ServoOn();
	BOOL Check_DirveAlarm();
	BOOL Check_EndLimit();
	BOOL Check_HomeDone();
	BOOL Check_EmptyTray();
	BOOL Check_Elevator();

	void Check_InsideLamp();
	void Stop_Elevator();
	void BuzzerOn();
	void BuzzerOff();
	void Locking_MainDoor(BOOL bLock, BOOL bAuto=FALSE);
	void Locking_TrayDoor(BOOL bLock, int nElevtorNo);
	void Set_LotDataClear(int nPortNo);	//nPortNo:0~5;
	void Locking_Slide(BOOL bLock, int nElevNo);	//nElevNo:0~7
	BOOL Check_SlideLock(int nElevNo=0);			//nElevNo:0~7
	BOOL Read_FocusOffset();
	void Display_MESRecipe(CString sRecipe);

	///////////////////////////////////////////////////////////////////////////

	void Wait_Time(int msec);
	int Get_Random(int nStart, int nEnd);
	void Backup_File(CString strPath, CString strName);	// System Folder
	void Add_NGCodeCount(int nNo, CString sJudge, CString sNGCode);

	///////////////////////////////////////////////////////////////////////////

	//nPickNo(0,1,2) nType(0,1,2,9(개별)) nNo(0~8)
	void Set_LoadPickerUp(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);
	void Set_LoadPickerClose(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);
	void Set_LoadPickerOpen(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);
	void Set_LoadPickerDown(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);
	BOOL Get_LoadPickerOpen(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);
	BOOL Get_LoadPickerClose(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);
	BOOL Get_LoadPickerUp(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);
	BOOL Get_LoadPickerDown(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);
	BOOL Get_LoadPickerCheck(int nPickNo=0, int nType=0, int nNo=0, int *nCMInfo=NULL);

	//nVisionNo(1,2,3,4) nNo(0,1~8,9)
	void Set_VisionVacuumOn(int nVisionNo, int nNo=0, int *nCMInfo=NULL);
	void Set_VisionVacuumOff(int nVisionNo, int nNo=0, int *nCMInfo=NULL);
	BOOL Get_VisionVacuumOn(int nVisionNo, int nNo=0, int *nCMInfo=NULL);
	BOOL Get_VisionVacuumOff(int nVisionNo, int nNo=0, int *nCMInfo=NULL);

	//nPickNo(0,1,2) nNo(0~8)
	void Set_UnloadPickerUp(int nPickNo=0, int nNo=0);
	void Set_UnloadPickerClose(int nPickNo=0, int nNo=0);
	//nPickNo(1,2) nNo(0,1~8,9) nSPNo(1~8) nSTNo(1~4)
	void Set_UnloadPickerDown(int nPickNo, int nNo=0, int nSPNo=0, int nSTNo=0, int *nCMInfo=NULL);
	void Set_UnloadPickerOpen(int nPickNo, int nNo=0, int nSPNo=0, int nSTNo=0, int *nCMInfo=NULL);
	BOOL Get_UnloadPickerDown(int nPickNo, int nNo=0, int nSPNo=0, int nSTNo=0, int *nCMInfo=NULL);
	BOOL Get_UnloadPickerOpen(int nPickNo, int nNo=0, int nSPNo=0, int nSTNo=0, int *nCMInfo=NULL);
	BOOL Get_UnloadPickerClose(int nPickNo, int nNo=0);
	BOOL Get_UnloadPickerUp(int nPickNo, int nNo=0);
	BOOL Get_UnloadPickerCheck(int nPickNo, int nNo=0, int *nCMInfo=NULL);

	///////////////////////////////////////////////////////////////////////////
	void Save_Motion(int nAxis, int nIdx, double dTraget = 0.0);		// SPC 로그 중 위치정밀도 기록용도
	void Wait(DWORD dwMillisecond);
	void Set_LotCount(int nPortNo, CString sLotID, int nCount);
	///////////////////////////////////////////////////////////////////////////
	BOOL	BarcodeRead();
	CString ReadLine(CFile& file);
	int		BarcodeFind(CString sBarcode);
};

extern CCommon g_objCommon;

///////////////////////////////////////////////////////////////////////////////
