///////////////////////////////////////////////////////////////////////////////
// AJinDefine.h : AJin Structure
#pragma once

///////////////////////////////////////////////////////////////////////////////
// Motion Axis
#ifdef NEW_FINAL
	const int AXIS_COUNT = 43;		// Motion Module (RTEX)
#else
	const int AXIS_COUNT = 45;		// Motion Module (RTEX)
#endif

const int AX_ELEVATOR_Z1		= 0;	//Load1(좌)
const int AX_ELEVATOR_Z2		= 1;	//Load2
const int AX_ELEVATOR_Z3		= 2;	//Empty-NG
const int AX_ELEVATOR_Z4		= 3;	//Empty-Good
const int AX_ELEVATOR_Z5		= 4;	//Buffer-NG
const int AX_ELEVATOR_Z6		= 5;	//Unload1
const int AX_ELEVATOR_Z7		= 6;	//Unload2(우)
const int AX_TRANSFER_X1		= 7;	//좌
const int AX_TRANSFER_Z1		= 8;
const int AX_TRANSFER_X2		= 9;	//우
const int AX_TRANSFER_Z2		= 10;
const int AX_LOAD_STAGE_Y1		= 11;
const int AX_LOAD_STAGE_Y2		= 12;
const int AX_LOAD_PICKER_X1		= 13;	//앞
const int AX_LOAD_PICKER_Y1		= 14;
const int AX_LOAD_PICKER_Z1		= 15;
const int AX_LOAD_PICKER_P1		= 16;
const int AX_LOAD_PICKER_X2		= 17;	//뒤
const int AX_LOAD_PICKER_Y2		= 18;
const int AX_LOAD_PICKER_Z2		= 19;
const int AX_LOAD_PICKER_P2		= 20;
const int AX_BTM_FOCUS_Z		= 21;
const int AX_BTM_LIGHT_Z		= 22;
const int AX_BTM_ANGLE_Y		= 23;
const int AX_TOP1_VISION_Z		= 24;
const int AX_TOP2_VISION_Z		= 25;
const int AX_INSPECT_STAGE_X1	= 26;	//앞
const int AX_INSPECT_STAGE_X2	= 27;
const int AX_INSPECT_STAGE_X3	= 28;
const int AX_INSPECT_STAGE_X4	= 29;	//뒤
const int AX_UNLOAD_PICKER_X1	= 30;	//앞
const int AX_UNLOAD_PICKER_Y1	= 31;
const int AX_UNLOAD_PICKER_Z1	= 32;
const int AX_UNLOAD_PICKER_P1	= 33;
const int AX_UNLOAD_PICKER_X2	= 34;
const int AX_UNLOAD_PICKER_Y2	= 35;
const int AX_UNLOAD_PICKER_Z2	= 36;
const int AX_UNLOAD_PICKER_P2	= 37;
const int AX_GOOD_STAGE_Y1		= 38;
const int AX_GOOD_STAGE_Y2		= 39;
const int AX_NG_STAGE_Y1		= 40;
const int AX_NG_STAGE_Y2		= 41;
const int AX_SHIP_ALIGN_X		= 42;
const int AX_TOP1_LIGHT_Z		= 43;
const int AX_TOP1_ANGLE_Y		= 44;

///////////////////////////////////////////////////////////////////////////////
// Motion Status

typedef struct tag_AXIS_STATUS {
	double dPos;		// Motor Current Position
	double dVel;		// Motor Current Velocity
	BOOL bSOn;			// Servo On Status
	BOOL bOrg;			// Origin Sensor
	BOOL bELP;			// End Limit Positive
	BOOL bELN;			// End Limit Negative
	BOOL bALM;			// Driver Alarm
	BOOL bInP;			// In Position
	BOOL bRun;			// Running
	BOOL bHom;			// Home Complete
} AXIS_STATUS;

///////////////////////////////////////////////////////////////////////////////
// Motion Parameter

typedef struct tag_AXIS_PARAM {
	double dSpeedM;	// Move Speed
	double dSpeedJ;	// Jog Speed
	double dAccel;	// Move Accel
} AXIS_PARAM;

///////////////////////////////////////////////////////////////////////////////
// DIO Count

const long DIO_MODULE_COUNT = 15;		// IO Module (PCI-DI64R 2EA, PCI-DO64R 2EA)

///////////////////////////////////////////////////////////////////////////////
// 변환 타입

typedef union tag_DXY_DATA {
	DWORD nValue;
	struct {
		DWORD b0000: 1;		// 0000
		DWORD b0001: 1;		// 0001
		DWORD b0002: 1;		// 0002
		DWORD b0003: 1;		// 0003
		DWORD b0004: 1;		// 0004
		DWORD b0005: 1;		// 0005
		DWORD b0006: 1;		// 0006
		DWORD b0007: 1;		// 0007
		DWORD b0008: 1;		// 0008
		DWORD b0009: 1;		// 0009
		DWORD b0010: 1;		// 0010
		DWORD b0011: 1;		// 0011
		DWORD b0012: 1;		// 0012
		DWORD b0013: 1;		// 0013
		DWORD b0014: 1;		// 0014
		DWORD b0015: 1;		// 0015
		DWORD b0016: 1;		// 0016
		DWORD b0017: 1;		// 0017
		DWORD b0018: 1;		// 0018
		DWORD b0019: 1;		// 0019
		DWORD b0020: 1;		// 0020
		DWORD b0021: 1;		// 0021
		DWORD b0022: 1;		// 0022
		DWORD b0023: 1;		// 0023
		DWORD b0024: 1;		// 0024
		DWORD b0025: 1;		// 0025
		DWORD b0026: 1;		// 0026
		DWORD b0027: 1;		// 0027
		DWORD b0028: 1;		// 0028
		DWORD b0029: 1;		// 0029
		DWORD b0030: 1;		// 0030
		DWORD b0031: 1;		// 0031
	};
} DXY_DATA;	// Digital Input Output

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
typedef union tag_DX_DATA_00 {
	DWORD nValue;
	struct {
		DWORD iElevator1Clamp1On: 1;		// X0000
		DWORD iElevator1Clamp1Off: 1;		// X0001
		DWORD iElevator1Clamp2On: 1;		// X0002
		DWORD iElevator1Clamp2Off: 1;		// X0003
		DWORD iElevator1Height1: 1;			// X0004
		DWORD i0005: 1;						// X0005
		DWORD iElevator1Height2: 1;			// X0006
		DWORD i0007: 1;						// X0007
		DWORD iElevator1SlideClose: 1;		// X0008
		DWORD iElevator1SlideOpen: 1;		// X0009
		DWORD iElevator1TrayExist: 1;		// X0010
		DWORD i0011: 1;						// X0011
		DWORD i0012: 1;						// X0012
		DWORD iElevator1SlideLock: 1;		// X0013
		DWORD iElevator1SlideUnlock: 1;		// X0014
		DWORD i0015: 1;						// X0015
		DWORD iElevator2Clamp1On: 1;		// X0016
		DWORD iElevator2Clamp1Off: 1;		// X0017
		DWORD iElevator2Clamp2On: 1;		// X0018
		DWORD iElevator2Clamp2Off: 1;		// X0019
		DWORD iElevator2Height1: 1;			// X0020
		DWORD i0021: 1;						// X0021
		DWORD iElevator2Height2: 1;			// X0022
		DWORD i0023: 1;						// X0023
		DWORD iElevator2SlideClose: 1;		// X0024
		DWORD iElevator2SlideOpen: 1;		// X0025
		DWORD iElevator2TrayExist: 1;		// X0026
		DWORD i0027: 1;						// X0027
		DWORD i0028: 1;						// X0028
		DWORD iElevator2SlideLock: 1;		// X0029
		DWORD iElevator2SlideUnlock: 1;		// X0030
		DWORD i0031: 1;						// X0031
	};
} DX_DATA_00;

typedef union tag_DX_DATA_01 {
	DWORD nValue;
	struct {
		DWORD iElevator3Clamp1On: 1;		// X0100
		DWORD iElevator3Clamp1Off: 1;		// X0101
		DWORD iElevator3Clamp2On: 1;		// X0102
		DWORD iElevator3Clamp2Off: 1;		// X0103
		DWORD iElevator3Height1: 1;			// X0104
		DWORD i0105: 1;						// X0105
		DWORD iElevator3Height2: 1;			// X0106
		DWORD i0107: 1;						// X0107
		DWORD iElevator3SlideClose: 1;		// X0108
		DWORD iElevator3SlideOpen: 1;		// X0109
		DWORD iElevator3TrayExist: 1;		// X0110
		DWORD i0111: 1;						// X0111
		DWORD i0112: 1;						// X0112
		DWORD iElevator3SlideLock: 1;		// X0113
		DWORD iElevator3SlideUnlock: 1;		// X0114
		DWORD i0115: 1;						// X0115
		DWORD iElevator4Clamp1On: 1;		// X0116
		DWORD iElevator4Clamp1Off: 1;		// X0117
		DWORD iElevator4Clamp2On: 1;		// X0118
		DWORD iElevator4Clamp2Off: 1;		// X0119
		DWORD iElevator4Height1: 1;			// X0120
		DWORD i0120: 1;						// X0121
		DWORD iElevator4Height2: 1;			// X0122
		DWORD i0123: 1;						// X0123
		DWORD iElevator4SlideClose: 1;		// X0124
		DWORD iElevator4SlideOpen: 1;		// X0125
		DWORD iElevator4TrayExist: 1;		// X0126
		DWORD i0127: 1;						// X0127
		DWORD i0128: 1;						// X0128
		DWORD iElevator4SlideLock: 1;		// X0129
		DWORD iElevator4SlideUnlock: 1;		// X0130
		DWORD i0131: 1;						// X0131
	};
} DX_DATA_01;

typedef union tag_DX_DATA_02 {
	DWORD nValue;
	struct {
		DWORD iElevator5Clamp1On: 1;		// X0200
		DWORD iElevator5Clamp1Off: 1;		// X0201
		DWORD iElevator5Clamp2On: 1;		// X0202
		DWORD iElevator5Clamp2Off: 1;		// X0203
		DWORD iElevator5Height1: 1;			// X0204
		DWORD i0205: 1;						// X0205
		DWORD iElevator5Height2: 1;			// X0206
		DWORD i0207: 1;						// X0207
		DWORD iElevator5SlideClose: 1;		// X0208
		DWORD iElevator5SlideOpen: 1;		// X0209
		DWORD iElevator5TrayExist: 1;		// X0210
		DWORD i0211: 1;						// X0211
		DWORD i0212: 1;						// X0212
		DWORD iElevator5SlideLock: 1;		// X0213
		DWORD iElevator5SlideUnlock: 1;		// X0214
		DWORD i0215: 1;						// X0215
		DWORD iElevator6Height1: 1;			// X0216
		DWORD i0217: 1;						// X0217
		DWORD iElevator6SlideClose: 1;		// X0218
		DWORD iElevator6SlideOpen: 1;		// X0219
		DWORD iElevator6TrayExist: 1;		// X0220
		DWORD i0221: 1;						// X0221
		DWORD i0222: 1;						// X0222
		DWORD i0223: 1;						// X0223
		DWORD iElevator7Height1: 1;			// X0224
		DWORD i0225: 1;						// X0225
		DWORD iElevator7SlideClose: 1;		// X0226
		DWORD iElevator7SlideOpen: 1;		// X0227
		DWORD iElevator7TrayExist: 1;		// X0228
		DWORD iElevator6SlideLock: 1;		// X0229
		DWORD iElevator6SlideUnlock: 1;		// X0230
		DWORD i0231: 1;						// X0231
	};
} DX_DATA_02;

typedef union tag_DX_DATA_03 {
	DWORD nValue;
	struct {
		DWORD iTransferLGrab1Open: 1;		// X0300
		DWORD iTransferLGrab1Close: 1;		// X0301
		DWORD iTransferLGrab2Open: 1;		// X0302
		DWORD iTransferLGrab2Close: 1;		// X0303
		DWORD iTransferLTrayExist: 1;		// X0304
		DWORD i0305: 1;						// X0305
		DWORD i0306: 1;						// X0306
		DWORD i0307: 1;						// X0307
		DWORD iTransferRGrab1Open: 1;		// X0308
		DWORD iTransferRGrab1Close: 1;		// X0309
		DWORD iTransferRGrab2Open: 1;		// X0310
		DWORD iTransferRGrab2Close: 1;		// X0311
		DWORD iTransferRTrayExist: 1;		// X0312
		DWORD i0313: 1;						// X0313
		DWORD i0314: 1;						// X0314
		DWORD i0315: 1;						// X0315
		DWORD iAlignMasterIn: 1;			// X0316
		DWORD iAlignMasterOut: 1;			// X0317
		DWORD iAlignSlave1In: 1;			// X0318
		DWORD iAlignSlave1Out: 1;			// X0319
#ifdef NEW_FINAL
		DWORD iAlignSlave2Out: 1;			// X0320
		DWORD iAlignSlave2In: 1;			// X0321
#else
		DWORD iAlignSlave2In: 1;			// X0320
		DWORD iAlignSlave2Out: 1;			// X0321
#endif
		DWORD i0322: 1;						// X0322
		DWORD i0323: 1;						// X0323
		DWORD iElevator7SlideLock: 1;		// X0324
		DWORD iElevator7SlideUnlock: 1;		// X0325
		DWORD i0326: 1;						// X0326
		DWORD i0327: 1;						// X0327
		DWORD i0328: 1;						// X0328
		DWORD i0329: 1;						// X0329
		DWORD i0330: 1;						// X0330
		DWORD i0331: 1;						// X0331
	};
} DX_DATA_03;

typedef union tag_DX_DATA_04 {
	DWORD nValue;
	struct {
		DWORD iLoadStage1Up: 1;				// X0400
		DWORD iLoadStage1Down: 1;			// X0401
		DWORD iLoadStage1MasterOut: 1;		// X0402
		DWORD iLoadStage1MasterIn: 1;		// X0403
		DWORD iLoadStage1SlaveOut: 1;		// X0404
		DWORD iLoadStage1SlaveIn: 1;		// X0405
		DWORD iLoadStage1TrayExist: 1;		// X0406
		DWORD i0407: 1;						// X0407
		DWORD i0408: 1;						// X0408
		DWORD i0409: 1;						// X0409
		DWORD i0410: 1;						// X0410
		DWORD i0411: 1;						// X0411
		DWORD i0412: 1;						// X0412
		DWORD i0413: 1;						// X0413
		DWORD i0414: 1;						// X0414
		DWORD i0415: 1;						// X0415
		DWORD iLoadStage2Up: 1;				// X0416
		DWORD iLoadStage2Down: 1;			// X0417
		DWORD iLoadStage2MasterOut: 1;		// X0418
		DWORD iLoadStage2MasterIn: 1;		// X0419
		DWORD iLoadStage2SlaveOut: 1;		// X0420
		DWORD iLoadStage2SlaveIn: 1;		// X0421
		DWORD iLoadStage2TrayExist: 1;		// X0422
		DWORD i0423: 1;						// X0423
		DWORD i0424: 1;						// X0424
		DWORD i0425: 1;						// X0425
		DWORD i0426: 1;						// X0426
		DWORD i0427: 1;						// X0427
		DWORD i0428: 1;						// X0428
		DWORD i0429: 1;						// X0429
		DWORD i0430: 1;						// X0430
		DWORD i0431: 1;						// X0431
	};
} DX_DATA_04;

typedef union tag_DX_DATA_05 {
	DWORD nValue;
	struct {
		DWORD iLoadPicker1Down1: 1;			// X0500
		DWORD iLoadPicker1Up1: 1;			// X0501
		DWORD iLoadPicker1Down2: 1;			// X0502
		DWORD iLoadPicker1Up2: 1;			// X0503
		DWORD iLoadPicker1Down3: 1;			// X0504
		DWORD iLoadPicker1Up3: 1;			// X0505
		DWORD iLoadPicker1Down4: 1;			// X0506
		DWORD iLoadPicker1Up4: 1;			// X0507
		DWORD iLoadPicker1Down5: 1;			// X0508
		DWORD iLoadPicker1Up5: 1;			// X0509
		DWORD iLoadPicker1Down6: 1;			// X0510
		DWORD iLoadPicker1Up6: 1;			// X0511
		DWORD iLoadPicker1Down7: 1;			// X0512
		DWORD iLoadPicker1Up7: 1;			// X0513
		DWORD iLoadPicker1Down8: 1;			// X0514
		DWORD iLoadPicker1Up8: 1;			// X0515
		DWORD iLoadPicker1Open1: 1;			// X0516
		DWORD iLoadPicker1Open2: 1;			// X0517
		DWORD iLoadPicker1Open3: 1;			// X0518
		DWORD iLoadPicker1Open4: 1;			// X0519
		DWORD iLoadPicker1Open5: 1;			// X0520
		DWORD iLoadPicker1Open6: 1;			// X0521
		DWORD iLoadPicker1Open7: 1;			// X0522
		DWORD iLoadPicker1Open8: 1;			// X0523
		DWORD iLoadPicker1Exist1: 1;		// X0524
		DWORD iLoadPicker1Exist2: 1;		// X0525
		DWORD iLoadPicker1Exist3: 1;		// X0526
		DWORD iLoadPicker1Exist4: 1;		// X0527
		DWORD iLoadPicker1Exist5: 1;		// X0528
		DWORD iLoadPicker1Exist6: 1;		// X0529
		DWORD iLoadPicker1Exist7: 1;		// X0530
		DWORD iLoadPicker1Exist8: 1;		// X0531
	};
} DX_DATA_05;

typedef union tag_DX_DATA_06 {
	DWORD nValue;
	struct {
		DWORD iLoadPicker2Down1: 1;			// X0600
		DWORD iLoadPicker2Up1: 1;			// X0601
		DWORD iLoadPicker2Down2: 1;			// X0602
		DWORD iLoadPicker2Up2: 1;			// X0603
		DWORD iLoadPicker2Down3: 1;			// X0604
		DWORD iLoadPicker2Up3: 1;			// X0605
		DWORD iLoadPicker2Down4: 1;			// X0606
		DWORD iLoadPicker2Up4: 1;			// X0607
		DWORD iLoadPicker2Down5: 1;			// X0608
		DWORD iLoadPicker2Up5: 1;			// X0609
		DWORD iLoadPicker2Down6: 1;			// X0610
		DWORD iLoadPicker2Up6: 1;			// X0611
		DWORD iLoadPicker2Down7: 1;			// X0612
		DWORD iLoadPicker2Up7: 1;			// X0613
		DWORD iLoadPicker2Down8: 1;			// X0614
		DWORD iLoadPicker2Up8: 1;			// X0615
		DWORD iLoadPicker2Open1: 1;			// X0616
		DWORD iLoadPicker2Open2: 1;			// X0617
		DWORD iLoadPicker2Open3: 1;			// X0618
		DWORD iLoadPicker2Open4: 1;			// X0619
		DWORD iLoadPicker2Open5: 1;			// X0620
		DWORD iLoadPicker2Open6: 1;			// X0621
		DWORD iLoadPicker2Open7: 1;			// X0622
		DWORD iLoadPicker2Open8: 1;			// X0623
		DWORD iLoadPicker2Exist1: 1;		// X0624
		DWORD iLoadPicker2Exist2: 1;		// X0625
		DWORD iLoadPicker2Exist3: 1;		// X0626
		DWORD iLoadPicker2Exist4: 1;		// X0627
		DWORD iLoadPicker2Exist5: 1;		// X0628
		DWORD iLoadPicker2Exist6: 1;		// X0629
		DWORD iLoadPicker2Exist7: 1;		// X0630
		DWORD iLoadPicker2Exist8: 1;		// X0631
	};
} DX_DATA_06;

typedef union tag_DX_DATA_07 {
	DWORD nValue;
	struct {
		DWORD iInspectStage1Up: 1;			// X0700
		DWORD iInspectStage1Down: 1;		// X0701
		DWORD iInspectStage1Deg90: 1;		// X0702
		DWORD iInspectStage1Deg0: 1;		// X0703
		DWORD iInspectStage1Yin: 1;			// X0704
		DWORD iInspectStage1YOut: 1;		// X0705
		DWORD i0706: 1;						// X0706
		DWORD i0707: 1;						// X0707
		DWORD iInspectStage1Vac1On: 1;		// X0708
		DWORD iInspectStage1Vac2On: 1;		// X0709
		DWORD iInspectStage1Vac3On: 1;		// X0710
		DWORD iInspectStage1Vac4On: 1;		// X0711
		DWORD iInspectStage1Vac5On: 1;		// X0712
		DWORD iInspectStage1Vac6On: 1;		// X0713
		DWORD iInspectStage1Vac7On: 1;		// X0714
		DWORD iInspectStage1Vac8On: 1;		// X0715
		DWORD iInspectStage2Up: 1;			// X0716
		DWORD iInspectStage2Down: 1;		// X0717
		DWORD iInspectStage2Deg90: 1;		// X0718
		DWORD iInspectStage2Deg0: 1;		// X0719
		DWORD i0720: 1;						// X0720
		DWORD i0721: 1;						// X0721
		DWORD i0722: 1;						// X0722
		DWORD i0723: 1;						// X0723
		DWORD iInspectStage2Vac1On: 1;		// X0724
		DWORD iInspectStage2Vac2On: 1;		// X0725
		DWORD iInspectStage2Vac3On: 1;		// X0726
		DWORD iInspectStage2Vac4On: 1;		// X0727
		DWORD iInspectStage2Vac5On: 1;		// X0728
		DWORD iInspectStage2Vac6On: 1;		// X0729
		DWORD iInspectStage2Vac7On: 1;		// X0730
		DWORD iInspectStage2Vac8On: 1;		// X0731
	};
} DX_DATA_07;

typedef union tag_DX_DATA_08 {
	DWORD nValue;
	struct {
		DWORD iInspectStage3Up: 1;			// X0800
		DWORD iInspectStage3Down: 1;		// X0801
		DWORD iInspectStage3Deg90: 1;		// X0802
		DWORD iInspectStage3Deg0: 1;		// X0803
		DWORD i0804: 1;						// X0804
		DWORD i0805: 1;						// X0805
		DWORD i0806: 1;						// X0806
		DWORD i0807: 1;						// X0807
		DWORD iInspectStage3Vac1On: 1;		// X0808
		DWORD iInspectStage3Vac2On: 1;		// X0809
		DWORD iInspectStage3Vac3On: 1;		// X0810
		DWORD iInspectStage3Vac4On: 1;		// X0811
		DWORD iInspectStage3Vac5On: 1;		// X0812
		DWORD iInspectStage3Vac6On: 1;		// X0813
		DWORD iInspectStage3Vac7On: 1;		// X0814
		DWORD iInspectStage3Vac8On: 1;		// X0815
		DWORD iInspectStage4Up: 1;			// X0816
		DWORD iInspectStage4Down: 1;		// X0817
		DWORD iInspectStage4Deg90: 1;		// X0818
		DWORD iInspectStage4Deg0: 1;		// X0819
		DWORD iInspectStage4Yin: 1;			// X0820
		DWORD iInspectStage4YOut: 1;		// X0821
		DWORD i0822: 1;						// X0822
		DWORD i0823: 1;						// X0823
		DWORD iInspectStage4Vac1On: 1;		// X0824
		DWORD iInspectStage4Vac2On: 1;		// X0825
		DWORD iInspectStage4Vac3On: 1;		// X0826
		DWORD iInspectStage4Vac4On: 1;		// X0827
		DWORD iInspectStage4Vac5On: 1;		// X0828
		DWORD iInspectStage4Vac6On: 1;		// X0829
		DWORD iInspectStage4Vac7On: 1;		// X0830
		DWORD iInspectStage4Vac8On: 1;		// X0831
	};
} DX_DATA_08;

typedef union tag_DX_DATA_09 {
	DWORD nValue;
	struct {
		DWORD iUnloadPicker1Down1: 1;		// X0900
		DWORD iUnloadPicker1Up1: 1;			// X0901
		DWORD iUnloadPicker1Down2: 1;		// X0902
		DWORD iUnloadPicker1Up2: 1;			// X0903
		DWORD iUnloadPicker1Down3: 1;		// X0904
		DWORD iUnloadPicker1Up3: 1;			// X0905
		DWORD iUnloadPicker1Down4: 1;		// X0906
		DWORD iUnloadPicker1Up4: 1;			// X0907
		DWORD iUnloadPicker1Down5: 1;		// X0908
		DWORD iUnloadPicker1Up5: 1;			// X0909
		DWORD iUnloadPicker1Down6: 1;		// X0910
		DWORD iUnloadPicker1Up6: 1;			// X0911
		DWORD iUnloadPicker1Down7: 1;		// X0912
		DWORD iUnloadPicker1Up7: 1;			// X0913
		DWORD iUnloadPicker1Down8: 1;		// X0914
		DWORD iUnloadPicker1Up8: 1;			// X0915
		DWORD iUnloadPicker1Open1: 1;		// X0916
		DWORD iUnloadPicker1Open2: 1;		// X0917
		DWORD iUnloadPicker1Open3: 1;		// X0918
		DWORD iUnloadPicker1Open4: 1;		// X0919
		DWORD iUnloadPicker1Open5: 1;		// X0920
		DWORD iUnloadPicker1Open6: 1;		// X0921
		DWORD iUnloadPicker1Open7: 1;		// X0922
		DWORD iUnloadPicker1Open8: 1;		// X0923
		DWORD iUnloadPicker1Exist1: 1;		// X0924
		DWORD iUnloadPicker1Exist2: 1;		// X0925
		DWORD iUnloadPicker1Exist3: 1;		// X0926
		DWORD iUnloadPicker1Exist4: 1;		// X0927
		DWORD iUnloadPicker1Exist5: 1;		// X0928
		DWORD iUnloadPicker1Exist6: 1;		// X0929
		DWORD iUnloadPicker1Exist7: 1;		// X0930
		DWORD iUnloadPicker1Exist8: 1;		// X0931
	};
} DX_DATA_09;

typedef union tag_DX_DATA_10 {
	DWORD nValue;
	struct {
		DWORD iUnloadPicker2Down1: 1;		// X1000
		DWORD iUnloadPicker2Up1: 1;			// X1001
		DWORD iUnloadPicker2Down2: 1;		// X1002
		DWORD iUnloadPicker2Up2: 1;			// X1003
		DWORD iUnloadPicker2Down3: 1;		// X1004
		DWORD iUnloadPicker2Up3: 1;			// X1005
		DWORD iUnloadPicker2Down4: 1;		// X1006
		DWORD iUnloadPicker2Up4: 1;			// X1007
		DWORD iUnloadPicker2Down5: 1;		// X1008
		DWORD iUnloadPicker2Up5: 1;			// X1009
		DWORD iUnloadPicker2Down6: 1;		// X1010
		DWORD iUnloadPicker2Up6: 1;			// X1011
		DWORD iUnloadPicker2Down7: 1;		// X1012
		DWORD iUnloadPicker2Up7: 1;			// X1013
		DWORD iUnloadPicker2Down8: 1;		// X1014
		DWORD iUnloadPicker2Up8: 1;			// X1015
		DWORD iUnloadPicker2Open1: 1;		// X1016
		DWORD iUnloadPicker2Open2: 1;		// X1017
		DWORD iUnloadPicker2Open3: 1;		// X1018
		DWORD iUnloadPicker2Open4: 1;		// X1019
		DWORD iUnloadPicker2Open5: 1;		// X1020
		DWORD iUnloadPicker2Open6: 1;		// X1021
		DWORD iUnloadPicker2Open7: 1;		// X1022
		DWORD iUnloadPicker2Open8: 1;		// X1023
		DWORD iUnloadPicker2Exist1: 1;		// X1024
		DWORD iUnloadPicker2Exist2: 1;		// X1025
		DWORD iUnloadPicker2Exist3: 1;		// X1026
		DWORD iUnloadPicker2Exist4: 1;		// X1027
		DWORD iUnloadPicker2Exist5: 1;		// X1028
		DWORD iUnloadPicker2Exist6: 1;		// X1029
		DWORD iUnloadPicker2Exist7: 1;		// X1030
		DWORD iUnloadPicker2Exist8: 1;		// X1031
	};
} DX_DATA_10;

typedef union tag_DX_DATA_11 {
	DWORD nValue;
	struct {
		DWORD iNGStage1Up: 1;				// X1100
		DWORD iNGStage1Down: 1;				// X1101
		DWORD iNGStage1MasterOut: 1;		// X1102
		DWORD iNGStage1MasterIn: 1;			// X1103
		DWORD iNGStage1SlaveOut: 1;			// X1104
		DWORD iNGStage1SlaveIn: 1;			// X1105
		DWORD iNGStage1TrayExist: 1;		// X1106
		DWORD i1107: 1;						// X1107
		DWORD i1108: 1;						// X1108
		DWORD i1109: 1;						// X1109
		DWORD i1110: 1;						// X1110
		DWORD i1111: 1;						// X1111
		DWORD i1112: 1;						// X1112
		DWORD i1113: 1;						// X1113
		DWORD i1114: 1;						// X1114
		DWORD i1115: 1;						// X1115
		DWORD iNGStage2Up: 1;				// X1116
		DWORD iNGStage2Down: 1;				// X1117
		DWORD iNGStage2MasterOut: 1;		// X1118
		DWORD iNGStage2MasterIn: 1;			// X1119
		DWORD iNGStage2SlaveOut: 1;			// X1120
		DWORD iNGStage2SlaveIn: 1;			// X1121
		DWORD iNGStage2TrayExist: 1;		// X1122
		DWORD i1123: 1;						// X1123
		DWORD i1124: 1;						// X1124
		DWORD i1125: 1;						// X1125
		DWORD i1126: 1;						// X1126
		DWORD i1127: 1;						// X1127
		DWORD i1128: 1;						// X1128
		DWORD i1129: 1;						// X1129
		DWORD i1130: 1;						// X1130
		DWORD i1131: 1;						// X1131
	};
} DX_DATA_11;

typedef union tag_DX_DATA_12 {
	DWORD nValue;
	struct {
		DWORD iGoodStage1Up: 1;				// X1200
		DWORD iGoodStage1Down: 1;			// X1201
		DWORD iGoodStage1MasterOut: 1;		// X1202
		DWORD iGoodStage1MasterIn: 1;		// X1203
		DWORD iGoodStage1SlaveOut: 1;		// X1204
		DWORD iGoodStage1SlaveIn: 1;		// X1205
		DWORD iGoodStage1TrayExist: 1;		// X1206
		DWORD i1207: 1;						// X1207
		DWORD i1208: 1;						// X1208
		DWORD i1209: 1;						// X1209
		DWORD i1210: 1;						// X1210
		DWORD i1211: 1;						// X1211
		DWORD i1212: 1;						// X1212
		DWORD i1213: 1;						// X1213
		DWORD i1214: 1;						// X1214
		DWORD i1215: 1;						// X1215
		DWORD iGoodStage2Up: 1;				// X1216
		DWORD iGoodStage2Down: 1;			// X1217
		DWORD iGoodStage2MasterOut: 1;		// X1218
		DWORD iGoodStage2MasterIn: 1;		// X1219
		DWORD iGoodStage2SlaveOut: 1;		// X1220
		DWORD iGoodStage2SlaveIn: 1;		// X1221
		DWORD iGoodStage2TrayExist: 1;		// X1222
		DWORD i1223: 1;						// X1223
		DWORD i1224: 1;						// X1224
		DWORD i1225: 1;						// X1225
		DWORD i1226: 1;						// X1226
		DWORD i1227: 1;						// X1227
		DWORD i1228: 1;						// X1228
		DWORD i1229: 1;						// X1229
		DWORD i1230: 1;						// X1230
		DWORD i1231: 1;						// X1231
	};
} DX_DATA_12;

typedef union tag_DX_DATA_13 {
	DWORD nValue;
	struct {
		DWORD iEmgSw1: 1;					// X1300
		DWORD iEmgSw2: 1;					// X1301
		DWORD iEmgSw3: 1;					// X1302
		DWORD iEmgSw4: 1;					// X1303
		DWORD iEmgSw5: 1;					// X1304
		DWORD iEmgSw6: 1;					// X1305
		DWORD iMainAir1: 1;					// X1306
		DWORD iMainAir2: 1;					// X1307
		DWORD iMainAir3: 1;					// X1308
		DWORD i1309: 1;						// X1309
		DWORD i1310: 1;						// X1310
		DWORD i1311: 1;						// X1311
		DWORD iStartSw: 1;					// X1312
		DWORD i1313: 1;						// X1313
		DWORD i1314: 1;						// X1314
		DWORD iStopSw: 1;					// X1315
		DWORD i1316: 1;						// X1316
		DWORD i1317: 1;						// X1317
		DWORD iResetSw: 1;					// X1318
		DWORD i1319: 1;						// X1319
		DWORD i1320: 1;						// X1320
		DWORD i1321: 1;						// X1321
		DWORD i1322: 1;						// X1322
		DWORD i1323: 1;						// X1323
		DWORD iElevator1Sw: 1;				// X1324
		DWORD iElevator2Sw: 1;				// X1325
		DWORD iElevator3Sw: 1;				// X1326
		DWORD iElevator4Sw: 1;				// X1327
		DWORD iElevator5Sw: 1;				// X1328
		DWORD iElevator6Sw: 1;				// X1329
		DWORD iElevator7Sw: 1;				// X1330
		DWORD i1331: 1;						// X1331
	};											
} DX_DATA_13;

typedef union tag_DX_DATA_14 {
	DWORD nValue;
	struct {
		DWORD iDoor01Unlock: 1;				// X1400
		DWORD iDoor02Unlock: 1;				// X1401
		DWORD iDoor03Unlock: 1;				// X1402
		DWORD iDoor04Unlock: 1;				// X1403
		DWORD iDoor05Unlock: 1;				// X1404
		DWORD iDoor06Unlock: 1;				// X1405
		DWORD iDoor07Unlock: 1;				// X1406
		DWORD iDoor08Unlock: 1;				// X1407
		DWORD iDoor09Unlock: 1;				// X1408
		DWORD iDoor10Unlock: 1;				// X1409
		DWORD iDoor11Unlock: 1;				// X1410
		DWORD iDoor12Unlock: 1;				// X1411
		DWORD iDoor13Unlock: 1;				// X1412
		DWORD iDoor14Unlock: 1;				// X1413
		DWORD iDoor15Unlock: 1;				// X1414
		DWORD iDoor16Unlock: 1;				// X1415
		DWORD iDoor17Unlock: 1;				// X1416
		DWORD iDoor18Unlock: 1;				// X1417
		DWORD iDoor19Unlock: 1;				// X1418
		DWORD iDoor20Unlock: 1;				// X1419
		DWORD iDoor21Unlock: 1;				// X1420
		DWORD i1421: 1;						// X1421
		DWORD i1422: 1;						// X1422
		DWORD i1423: 1;						// X1423
		DWORD iLightCurtain1: 1;			// X1424
		DWORD iLightCurtain2: 1;			// X1425
		DWORD iLightCurtain3: 1;			// X1426
		DWORD i1427: 1;						// X1427
		DWORD i1428: 1;						// X1428
		DWORD i1429: 1;						// X1429
		DWORD i1430: 1;						// X1430
		DWORD i1431: 1;						// X1431
	};
} DX_DATA_14;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
typedef union tag_DY_DATA_00 {
	DWORD nValue;
	struct {
		DWORD oElevator1Clamp1On: 1;		// Y0000
		DWORD oElevator1Clamp1Off: 1;		// Y0001
		DWORD oElevator1Clamp2On: 1;		// Y0002
		DWORD oElevator1Clamp2Off: 1;		// Y0003
		DWORD o0004: 1;						// Y0004
		DWORD o0005: 1;						// Y0005
		DWORD o0006: 1;						// Y0006
		DWORD o0007: 1;						// Y0007
		DWORD o0008: 1;						// Y0008
		DWORD o0009: 1;						// Y0009
		DWORD o0010: 1;						// Y0010
		DWORD o0011: 1;						// Y0011
		DWORD o0012: 1;						// Y0012
		DWORD o0013: 1;						// Y0013
		DWORD o0014: 1;						// Y0014
		DWORD o0015: 1;						// Y0015
		DWORD oElevator2Clamp1On: 1;		// Y0016
		DWORD oElevator2Clamp1Off: 1;		// Y0017
		DWORD oElevator2Clamp2On: 1;		// Y0018
		DWORD oElevator2Clamp2Off: 1;		// Y0019
		DWORD oElevator1SlideLock: 1;		// Y0020
		DWORD oElevator1SlideUnlock: 1;		// Y0021
		DWORD o0022: 1;						// Y0022
		DWORD o0023: 1;						// Y0023
		DWORD o0024: 1;						// Y0024
		DWORD o0025: 1;						// Y0025
		DWORD o0026: 1;						// Y0026
		DWORD o0027: 1;						// Y0027
		DWORD o0028: 1;						// Y0028
		DWORD o0029: 1;						// Y0029
		DWORD o0030: 1;						// Y0030
		DWORD o0031: 1;						// Y0031
	};
} DY_DATA_00;

typedef union tag_DY_DATA_01 {
	DWORD nValue;
	struct {
		DWORD oElevator3Clamp1On: 1;		// Y0100
		DWORD oElevator3Clamp1Off: 1;		// Y0101
		DWORD oElevator3Clamp2On: 1;		// Y0102
		DWORD oElevator3Clamp2Off: 1;		// Y0103
		DWORD oElevator2SlideLock: 1;		// Y0104
		DWORD oElevator2SlideUnlock: 1;		// Y0105
		DWORD o0106: 1;						// Y0106
		DWORD o0107: 1;						// Y0107
		DWORD o0108: 1;						// Y0108
		DWORD o0109: 1;						// Y0109
		DWORD o0110: 1;						// Y0110
		DWORD o0111: 1;						// Y0111
		DWORD o0112: 1;						// Y0112
		DWORD o0113: 1;						// Y0113
		DWORD o0114: 1;						// Y0114
		DWORD o0115: 1;						// Y0115
		DWORD oElevator4Clamp1On: 1;		// Y0116
		DWORD oElevator4Clamp1Off: 1;		// Y0117
		DWORD oElevator4Clamp2On: 1;		// Y0118
		DWORD oElevator4Clamp2Off: 1;		// Y0119
		DWORD oElevator3SlideLock: 1;		// Y0120
		DWORD oElevator3SlideUnlock: 1;		// Y0121
		DWORD o0122: 1;						// Y0122
		DWORD o0123: 1;						// Y0123
		DWORD o0124: 1;						// Y0124
		DWORD o0125: 1;						// Y0125
		DWORD o0126: 1;						// Y0126
		DWORD o0127: 1;						// Y0127
		DWORD o0128: 1;						// Y0128
		DWORD o0129: 1;						// Y0129
		DWORD o0130: 1;						// Y0130
		DWORD o0131: 1;						// Y0131
	};
} DY_DATA_01;

typedef union tag_DY_DATA_02 {
	DWORD nValue;
	struct {
		DWORD oElevator5Clamp1On: 1;		// Y0200
		DWORD oElevator5Clamp1Off: 1;		// Y0201
		DWORD oElevator5Clamp2On: 1;		// Y0202
		DWORD oElevator5Clamp2Off: 1;		// Y0203
		DWORD oElevator4SlideLock: 1;		// Y0204
		DWORD oElevator4SlideUnlock: 1;		// Y0205
		DWORD o0206: 1;						// Y0206
		DWORD o0207: 1;						// Y0207
		DWORD o0208: 1;						// Y0208
		DWORD o0209: 1;						// Y0209
		DWORD o0210: 1;						// Y0210
		DWORD o0211: 1;						// Y0211
		DWORD o0212: 1;						// Y0212
		DWORD oElevator5SlideLock: 1;		// Y0213
		DWORD oElevator5SlideUnlock: 1;		// Y0214
		DWORD o0215: 1;						// Y0215
		DWORD o0216: 1;						// Y0216
		DWORD o0217: 1;						// Y0217
		DWORD o0218: 1;						// Y0218
		DWORD o0219: 1;						// Y0219
		DWORD o0220: 1;						// Y0220
		DWORD o0221: 1;						// Y0221
		DWORD o0222: 1;						// Y0222
		DWORD o0223: 1;						// Y0223
		DWORD o0224: 1;						// Y0224
		DWORD o0225: 1;						// Y0225
		DWORD o0226: 1;						// Y0226
		DWORD o0227: 1;						// Y0227
		DWORD o0228: 1;						// Y0228
		DWORD oElevator6SlideLock: 1;		// Y0229
		DWORD oElevator6SlideUnlock: 1;		// Y0230
		DWORD o0231: 1;						// Y0231
	};
} DY_DATA_02;

typedef union tag_DY_DATA_03 {
	DWORD nValue;
	struct {
		DWORD oTransferLGrabOpen: 1;		// Y0300
		DWORD oTransferLGrabClose: 1;		// Y0301
		DWORD o0302: 1;						// Y0302
		DWORD o0303: 1;						// Y0303
		DWORD o0304: 1;						// Y0304
		DWORD o0305: 1;						// Y0305
		DWORD o0306: 1;						// Y0306
		DWORD o0307: 1;						// Y0307
		DWORD oTransferRGrabOpen: 1;		// Y0308
		DWORD oTransferRGrabClose: 1;		// Y0309
		DWORD o0310: 1;						// Y0310
		DWORD o0311: 1;						// Y0311
		DWORD o0312: 1;						// Y0312
		DWORD o0313: 1;						// Y0313
		DWORD o0314: 1;						// Y0314
		DWORD o0315: 1;						// Y0315
		DWORD oAlignMasterIn: 1;			// Y0316
		DWORD oAlignMasterOut: 1;			// Y0317
		DWORD oAlignSlave1In: 1;			// Y0318
		DWORD oAlignSlave1Out: 1;			// Y0319
#ifdef NEW_FINAL
		DWORD oAlignSlave2Out: 1;			// Y0320
		DWORD oAlignSlave2In: 1;			// Y0321
#else
		DWORD oAlignSlave2In: 1;			// Y0320
		DWORD oAlignSlave2Out: 1;			// Y0321
#endif
		DWORD o0322: 1;						// Y0322
		DWORD o0323: 1;						// Y0323
		DWORD oElevator7SlideLock: 1;		// Y0324
		DWORD oElevator7SlideUnlock: 1;		// Y0325
		DWORD o0326: 1;						// Y0326
		DWORD o0327: 1;						// Y0327
		DWORD o0328: 1;						// Y0328
		DWORD o0329: 1;						// Y0329
		DWORD o0330: 1;						// Y0330
		DWORD o0331: 1;						// Y0331
	};
} DY_DATA_03;

typedef union tag_DY_DATA_04 {
	DWORD nValue;
	struct {
		DWORD oLoadStage1Up: 1;				// Y0400
		DWORD oLoadStage1Down: 1;			// Y0401
		DWORD oLoadStage1MasterOut: 1;		// Y0402
		DWORD oLoadStage1MasterIn: 1;		// Y0403
		DWORD oLoadStage1SlaveOut: 1;		// Y0404
		DWORD oLoadStage1SlaveIn: 1;		// Y0405
		DWORD o0406: 1;						// Y0406
		DWORD o0407: 1;						// Y0407
		DWORD oBTMIonizerOn: 1;				// Y0408
		DWORD oBTMIonizerBlow: 1;			// Y0409
		DWORD oBTMSuctionOn: 1;				// Y0410
		DWORD o0411: 1;						// Y0411
		DWORD o0412: 1;						// Y0412
		DWORD o0413: 1;						// Y0413
		DWORD o0414: 1;						// Y0414
		DWORD o0415: 1;						// Y0415
		DWORD oLoadStage2Up: 1;				// Y0416
		DWORD oLoadStage2Down: 1;			// Y0417
		DWORD oLoadStage2MasterOut: 1;		// Y0418
		DWORD oLoadStage2MasterIn: 1;		// Y0419
		DWORD oLoadStage2SlaveOut: 1;		// Y0420
		DWORD oLoadStage2SlaveIn: 1;		// Y0421
		DWORD o0422: 1;						// Y0422
		DWORD o0423: 1;						// Y0423
		DWORD oTOPIonizerOn: 1;				// Y0424
		DWORD oTOPIonizerBlow: 1;			// Y0425
		DWORD oTOPSuctionOn: 1;				// Y0426
		DWORD o0427: 1;						// Y0427
		DWORD oLoadIonizerOn: 1;			// Y0428
		DWORD o0429: 1;						// Y0429
		DWORD o0430: 1;						// Y0430
		DWORD o0431: 1;						// Y0431
	};
} DY_DATA_04;

typedef union tag_DY_DATA_05 {
	DWORD nValue;
	struct {
		DWORD oLoadPicker1Down1: 1;			// Y0500
		DWORD oLoadPicker1Up1: 1;			// Y0501
		DWORD oLoadPicker1Down2: 1;			// Y0502
		DWORD oLoadPicker1Up2: 1;			// Y0503
		DWORD oLoadPicker1Down3: 1;			// Y0504
		DWORD oLoadPicker1Up3: 1;			// Y0505
		DWORD oLoadPicker1Down4: 1;			// Y0506
		DWORD oLoadPicker1Up4: 1;			// Y0507
		DWORD oLoadPicker1Down5: 1;			// Y0508
		DWORD oLoadPicker1Up5: 1;			// Y0509
		DWORD oLoadPicker1Down6: 1;			// Y0510
		DWORD oLoadPicker1Up6: 1;			// Y0511
		DWORD oLoadPicker1Down7: 1;			// Y0512
		DWORD oLoadPicker1Up7: 1;			// Y0513
		DWORD oLoadPicker1Down8: 1;			// Y0514
		DWORD oLoadPicker1Up8: 1;			// Y0515
		DWORD oLoadPicker1Open1: 1;			// Y0516
		DWORD oLoadPicker1Close1: 1;		// Y0517
		DWORD oLoadPicker1Open2: 1;			// Y0518
		DWORD oLoadPicker1Close2: 1;		// Y0519
		DWORD oLoadPicker1Open3: 1;			// Y0520
		DWORD oLoadPicker1Close3: 1;		// Y0521
		DWORD oLoadPicker1Open4: 1;			// Y0522
		DWORD oLoadPicker1Close4: 1;		// Y0523
		DWORD oLoadPicker1Open5: 1;			// Y0524
		DWORD oLoadPicker1Close5: 1;		// Y0525
		DWORD oLoadPicker1Open6: 1;			// Y0526
		DWORD oLoadPicker1Close6: 1;		// Y0527
		DWORD oLoadPicker1Open7: 1;			// Y0528
		DWORD oLoadPicker1Close7: 1;		// Y0529
		DWORD oLoadPicker1Open8: 1;			// Y0530
		DWORD oLoadPicker1Close8: 1;		// Y0531
	};
} DY_DATA_05;

typedef union tag_DY_DATA_06 {
	DWORD nValue;
	struct {
		DWORD oLoadPicker2Down1: 1;			// Y0600
		DWORD oLoadPicker2Up1: 1;			// Y0601
		DWORD oLoadPicker2Down2: 1;			// Y0602
		DWORD oLoadPicker2Up2: 1;			// Y0603
		DWORD oLoadPicker2Down3: 1;			// Y0604
		DWORD oLoadPicker2Up3: 1;			// Y0605
		DWORD oLoadPicker2Down4: 1;			// Y0606
		DWORD oLoadPicker2Up4: 1;			// Y0607
		DWORD oLoadPicker2Down5: 1;			// Y0608
		DWORD oLoadPicker2Up5: 1;			// Y0609
		DWORD oLoadPicker2Down6: 1;			// Y0610
		DWORD oLoadPicker2Up6: 1;			// Y0611
		DWORD oLoadPicker2Down7: 1;			// Y0612
		DWORD oLoadPicker2Up7: 1;			// Y0613
		DWORD oLoadPicker2Down8: 1;			// Y0614
		DWORD oLoadPicker2Up8: 1;			// Y0615
		DWORD oLoadPicker2Open1: 1;			// Y0616
		DWORD oLoadPicker2Close1: 1;		// Y0617
		DWORD oLoadPicker2Open2: 1;			// Y0618
		DWORD oLoadPicker2Close2: 1;		// Y0619
		DWORD oLoadPicker2Open3: 1;			// Y0620
		DWORD oLoadPicker2Close3: 1;		// Y0621
		DWORD oLoadPicker2Open4: 1;			// Y0622
		DWORD oLoadPicker2Close4: 1;		// Y0623
		DWORD oLoadPicker2Open5: 1;			// Y0624
		DWORD oLoadPicker2Close5: 1;		// Y0625
		DWORD oLoadPicker2Open6: 1;			// Y0626
		DWORD oLoadPicker2Close6: 1;		// Y0627
		DWORD oLoadPicker2Open7: 1;			// Y0628
		DWORD oLoadPicker2Close7: 1;		// Y0629
		DWORD oLoadPicker2Open8: 1;			// Y0630
		DWORD oLoadPicker2Close8: 1;		// Y0631
	};
} DY_DATA_06;

typedef union tag_DY_DATA_07 {
	DWORD nValue;
	struct {
		DWORD oInspectStage1Up: 1;			// Y0700
		DWORD oInspectStage1Down: 1;		// Y0701
		DWORD oInspectStage1Deg90: 1;		// Y0702
		DWORD oInspectStage1Deg0: 1;		// Y0703
		DWORD oInspectStage1Yin: 1;			// Y0704
		DWORD oInspectStage1YOut: 1;		// Y0705
		DWORD o0706: 1;						// Y0706
		DWORD o0707: 1;						// Y0707
		DWORD oInspectStage1Vac1On: 1;		// Y0708
		DWORD oInspectStage1Vac2On: 1;		// Y0709
		DWORD oInspectStage1Vac3On: 1;		// Y0710
		DWORD oInspectStage1Vac4On: 1;		// Y0711
		DWORD oInspectStage1Vac5On: 1;		// Y0712
		DWORD oInspectStage1Vac6On: 1;		// Y0713
		DWORD oInspectStage1Vac7On: 1;		// Y0714
		DWORD oInspectStage1Vac8On: 1;		// Y0715
		DWORD oInspectStage2Up: 1;			// Y0716
		DWORD oInspectStage2Down: 1;		// Y0717
		DWORD oInspectStage2Deg90: 1;		// Y0718
		DWORD oInspectStage2Deg0: 1;		// Y0719
		DWORD o0720: 1;						// Y0720
		DWORD o0721: 1;						// Y0721
		DWORD o0722: 1;						// Y0722
		DWORD o0723: 1;						// Y0723
		DWORD oInspectStage2Vac1On: 1;		// Y0724
		DWORD oInspectStage2Vac2On: 1;		// Y0725
		DWORD oInspectStage2Vac3On: 1;		// Y0726
		DWORD oInspectStage2Vac4On: 1;		// Y0727
		DWORD oInspectStage2Vac5On: 1;		// Y0728
		DWORD oInspectStage2Vac6On: 1;		// Y0729
		DWORD oInspectStage2Vac7On: 1;		// Y0730
		DWORD oInspectStage2Vac8On: 1;		// Y0731
	};
} DY_DATA_07;

typedef union tag_DY_DATA_08 {
	DWORD nValue;
	struct {
		DWORD oInspectStage3Up: 1;			// Y0800
		DWORD oInspectStage3Down: 1;		// Y0801
		DWORD oInspectStage3Deg90: 1;		// Y0802
		DWORD oInspectStage3Deg0: 1;		// Y0803
		DWORD o0804: 1;						// Y0804
		DWORD o0805: 1;						// Y0805
		DWORD o0806: 1;						// Y0806
		DWORD o0807: 1;						// Y0807
		DWORD oInspectStage3Vac1On: 1;		// Y0808
		DWORD oInspectStage3Vac2On: 1;		// Y0809
		DWORD oInspectStage3Vac3On: 1;		// Y0810
		DWORD oInspectStage3Vac4On: 1;		// Y0811
		DWORD oInspectStage3Vac5On: 1;		// Y0812
		DWORD oInspectStage3Vac6On: 1;		// Y0813
		DWORD oInspectStage3Vac7On: 1;		// Y0814
		DWORD oInspectStage3Vac8On: 1;		// Y0815
		DWORD oInspectStage4Up: 1;			// Y0816
		DWORD oInspectStage4Down: 1;		// Y0817
		DWORD oInspectStage4Deg90: 1;		// Y0818
		DWORD oInspectStage4Deg0: 1;		// Y0819
		DWORD oInspectStage4Yin: 1;			// Y0820
		DWORD oInspectStage4YOut: 1;		// Y0821
		DWORD o0822: 1;						// Y0822
		DWORD o0823: 1;						// Y0823
		DWORD oInspectStage4Vac1On: 1;		// Y0824
		DWORD oInspectStage4Vac2On: 1;		// Y0825
		DWORD oInspectStage4Vac3On: 1;		// Y0826
		DWORD oInspectStage4Vac4On: 1;		// Y0827
		DWORD oInspectStage4Vac5On: 1;		// Y0828
		DWORD oInspectStage4Vac6On: 1;		// Y0829
		DWORD oInspectStage4Vac7On: 1;		// Y0830
		DWORD oInspectStage4Vac8On: 1;		// Y0831
	};
} DY_DATA_08;

typedef union tag_DY_DATA_09 {
	DWORD nValue;
	struct {
		DWORD oUnloadPicker1Down1: 1;		// Y0900
		DWORD oUnloadPicker1Up1: 1;			// Y0901
		DWORD oUnloadPicker1Down2: 1;		// Y0902
		DWORD oUnloadPicker1Up2: 1;			// Y0903
		DWORD oUnloadPicker1Down3: 1;		// Y0904
		DWORD oUnloadPicker1Up3: 1;			// Y0905
		DWORD oUnloadPicker1Down4: 1;		// Y0906
		DWORD oUnloadPicker1Up4: 1;			// Y0907
		DWORD oUnloadPicker1Down5: 1;		// Y0908
		DWORD oUnloadPicker1Up5: 1;			// Y0909
		DWORD oUnloadPicker1Down6: 1;		// Y0910
		DWORD oUnloadPicker1Up6: 1;			// Y0911
		DWORD oUnloadPicker1Down7: 1;		// Y0912
		DWORD oUnloadPicker1Up7: 1;			// Y0913
		DWORD oUnloadPicker1Down8: 1;		// Y0914
		DWORD oUnloadPicker1Up8: 1;			// Y0915
		DWORD oUnloadPicker1Open1: 1;		// Y0916
		DWORD oUnloadPicker1Close1: 1;		// Y0917
		DWORD oUnloadPicker1Open2: 1;		// Y0918
		DWORD oUnloadPicker1Close2: 1;		// Y0919
		DWORD oUnloadPicker1Open3: 1;		// Y0920
		DWORD oUnloadPicker1Close3: 1;		// Y0921
		DWORD oUnloadPicker1Open4: 1;		// Y0922
		DWORD oUnloadPicker1Close4: 1;		// Y0923
		DWORD oUnloadPicker1Open5: 1;		// Y0924
		DWORD oUnloadPicker1Close5: 1;		// Y0925
		DWORD oUnloadPicker1Open6: 1;		// Y0926
		DWORD oUnloadPicker1Close6: 1;		// Y0927
		DWORD oUnloadPicker1Open7: 1;		// Y0928
		DWORD oUnloadPicker1Close7: 1;		// Y0929
		DWORD oUnloadPicker1Open8: 1;		// Y0930
		DWORD oUnloadPicker1Close8: 1;		// Y0931
	};
} DY_DATA_09;

typedef union tag_DY_DATA_10 {
	DWORD nValue;
	struct {
		DWORD oUnloadPicker2Down1: 1;		// Y1000
		DWORD oUnloadPicker2Up1: 1;			// Y1001
		DWORD oUnloadPicker2Down2: 1;		// Y1002
		DWORD oUnloadPicker2Up2: 1;			// Y1003
		DWORD oUnloadPicker2Down3: 1;		// Y1004
		DWORD oUnloadPicker2Up3: 1;			// Y1005
		DWORD oUnloadPicker2Down4: 1;		// Y1006
		DWORD oUnloadPicker2Up4: 1;			// Y1007
		DWORD oUnloadPicker2Down5: 1;		// Y1008
		DWORD oUnloadPicker2Up5: 1;			// Y1009
		DWORD oUnloadPicker2Down6: 1;		// Y1010
		DWORD oUnloadPicker2Up6: 1;			// Y1011
		DWORD oUnloadPicker2Down7: 1;		// Y1012
		DWORD oUnloadPicker2Up7: 1;			// Y1013
		DWORD oUnloadPicker2Down8: 1;		// Y1014
		DWORD oUnloadPicker2Up8: 1;			// Y1015
		DWORD oUnloadPicker2Open1: 1;		// Y1016
		DWORD oUnloadPicker2Close1: 1;		// Y1017
		DWORD oUnloadPicker2Open2: 1;		// Y1018
		DWORD oUnloadPicker2Close2: 1;		// Y1019
		DWORD oUnloadPicker2Open3: 1;		// Y1020
		DWORD oUnloadPicker2Close3: 1;		// Y1021
		DWORD oUnloadPicker2Open4: 1;		// Y1022
		DWORD oUnloadPicker2Close4: 1;		// Y1023
		DWORD oUnloadPicker2Open5: 1;		// Y1024
		DWORD oUnloadPicker2Close5: 1;		// Y1025
		DWORD oUnloadPicker2Open6: 1;		// Y1026
		DWORD oUnloadPicker2Close6: 1;		// Y1027
		DWORD oUnloadPicker2Open7: 1;		// Y1028
		DWORD oUnloadPicker2Close7: 1;		// Y1029
		DWORD oUnloadPicker2Open8: 1;		// Y1030
		DWORD oUnloadPicker2Close8: 1;		// Y1031
	};
} DY_DATA_10;

typedef union tag_DY_DATA_11 {
	DWORD nValue;
	struct {
		DWORD oNGStage1Up: 1;				// Y1100
		DWORD oNGStage1Down: 1;				// Y1101
		DWORD oNGStage1MasterOut: 1;		// Y1102
		DWORD oNGStage1MasterIn: 1;			// Y1103
		DWORD oNGStage1SlaveOut: 1;			// Y1104
		DWORD oNGStage1SlaveIn: 1;			// Y1105
		DWORD o1106: 1;						// Y1106
		DWORD o1107: 1;						// Y1107
		DWORD o1108: 1;						// Y1108
		DWORD o1109: 1;						// Y1109
		DWORD o1110: 1;						// Y1110
		DWORD o1111: 1;						// Y1111
		DWORD o1112: 1;						// Y1112
		DWORD o1113: 1;						// Y1113
		DWORD o1114: 1;						// Y1114
		DWORD o1115: 1;						// Y1115
		DWORD oNGStage2Up: 1;				// Y1116
		DWORD oNGStage2Down: 1;				// Y1117
		DWORD oNGStage2MasterOut: 1;		// Y1118
		DWORD oNGStage2MasterIn: 1;			// Y1119
		DWORD oNGStage2SlaveOut: 1;			// Y1120
		DWORD oNGStage2SlaveIn: 1;			// Y1121
		DWORD o1122: 1;						// Y1122
		DWORD o1123: 1;						// Y1123
		DWORD o1124: 1;						// Y1124
		DWORD o1125: 1;						// Y1125
		DWORD o1126: 1;						// Y1126
		DWORD o1127: 1;						// Y1127
		DWORD o1128: 1;						// Y1128
		DWORD o1129: 1;						// Y1129
		DWORD o1130: 1;						// Y1130
		DWORD o1131: 1;						// Y1131
	};
} DY_DATA_11;

typedef union tag_DY_DATA_12 {
	DWORD nValue;
	struct {
		DWORD oGoodStage1Up: 1;				// Y1200
		DWORD oGoodStage1Down: 1;			// Y1201
		DWORD oGoodStage1MasterOut: 1;		// Y1202
		DWORD oGoodStage1MasterIn: 1;		// Y1203
		DWORD oGoodStage1SlaveOut: 1;		// Y1204
		DWORD oGoodStage1SlaveIn: 1;		// Y1205
		DWORD o1206: 1;						// Y1206
		DWORD o1207: 1;						// Y1207
		DWORD o1208: 1;						// Y1208
		DWORD o1209: 1;						// Y1209
		DWORD o1210: 1;						// Y1210
		DWORD o1211: 1;						// Y1211
		DWORD o1212: 1;						// Y1212
		DWORD o1213: 1;						// Y1213
		DWORD o1214: 1;						// Y1214
		DWORD o1215: 1;						// Y1215
		DWORD oGoodStage2Up: 1;				// Y1216
		DWORD oGoodStage2Down: 1;			// Y1217
		DWORD oGoodStage2MasterOut: 1;		// Y1218
		DWORD oGoodStage2MasterIn: 1;		// Y1219
		DWORD oGoodStage2SlaveOut: 1;		// Y1220
		DWORD oGoodStage2SlaveIn: 1;		// Y1221
		DWORD o1222: 1;						// Y1222
		DWORD o1223: 1;						// Y1223
		DWORD o1224: 1;						// Y1224
		DWORD o1225: 1;						// Y1225
		DWORD o1226: 1;						// Y1226
		DWORD o1227: 1;						// Y1227
		DWORD oGoodIonizerOn: 1;			// Y1228
		DWORD o1229: 1;						// Y1229
		DWORD o1230: 1;						// Y1230
		DWORD o1231: 1;						// Y1231
	};
} DY_DATA_12;

typedef union tag_DY_DATA_13 {
	DWORD nValue;
	struct {
		DWORD oTowerGreen1: 1;				// Y1300
		DWORD oTowerYellow1: 1;				// Y1301
		DWORD oTowerRed1: 1;				// Y1302
		DWORD oBuzzerBit0: 1;				// Y1303
		DWORD oBuzzerBit1: 1;				// Y1304
		DWORD oBuzzerBit2: 1;				// Y1305
		DWORD oBuzzerBit3: 1;				// Y1306
		DWORD oBuzzerBit4: 1;				// Y1307
		DWORD oTowerGreen2: 1;				// Y1308
		DWORD oTowerYellow2: 1;				// Y1309
		DWORD oTowerRed2: 1; 				// Y1310
		DWORD o1311: 1; 					// Y1311
		DWORD oStartLamp1: 1;	 			// Y1312
		DWORD oStartLamp2: 1;				// Y1313
		DWORD oStartLamp3: 1; 				// Y1314
		DWORD oStopLamp1: 1;				// Y1315
		DWORD oStopLamp2: 1;				// Y1316
		DWORD oStopLamp3: 1;				// Y1317
		DWORD oResetLamp1: 1; 				// Y1318
		DWORD oResetLamp2: 1; 				// Y1319
		DWORD oResetLamp3: 1;				// Y1320
		DWORD o1321: 1;						// Y1321
		DWORD o1322: 1;						// Y1322
		DWORD o1323: 1;						// Y1323
		DWORD oElevator1Lamp: 1;			// Y1324
		DWORD oElevator2Lamp: 1;			// Y1325
		DWORD oElevator3Lamp: 1;			// Y1326
		DWORD oElevator4Lamp: 1;			// Y1327
		DWORD oElevator5Lamp: 1;			// Y1328
		DWORD oElevator6Lamp: 1;			// Y1329
		DWORD oElevator7Lamp: 1;			// Y1330
		DWORD o1331: 1;						// Y1331
	};
} DY_DATA_13;

typedef union tag_DY_DATA_14 {
	DWORD nValue;
	struct {
		DWORD oDoor01Unlock: 1;				// Y1400
		DWORD oDoor02Unlock: 1;				// Y1401
		DWORD oDoor03Unlock: 1; 			// Y1402
		DWORD oDoor04Unlock: 1; 			// Y1403
		DWORD oDoor05Unlock: 1; 			// Y1404
		DWORD oDoor06Unlock: 1;				// Y1405
		DWORD oDoor07Unlock: 1;				// Y1406
		DWORD oDoor08Unlock: 1; 			// Y1407
		DWORD oDoor09Unlock: 1; 			// Y1408
		DWORD oDoor10Unlock: 1; 			// Y1409
		DWORD oDoor11Unlock: 1;				// Y1410
		DWORD oDoor12Unlock: 1;				// Y1411
		DWORD oDoor13Unlock: 1; 			// Y1412
		DWORD oDoor14Unlock: 1; 			// Y1413
		DWORD oDoor15Unlock: 1; 			// Y1414
		DWORD oDoor16Unlock: 1;				// Y1415
		DWORD oDoor17Unlock: 1;				// Y1416
		DWORD oDoor18Unlock: 1; 			// Y1417
		DWORD oDoor19Unlock: 1; 			// Y1418
		DWORD oDoor20Unlock: 1; 			// Y1419
		DWORD oDoor21Unlock: 1; 			// Y1420
		DWORD o1421: 1;						// Y1421
		DWORD o1422: 1;						// Y1422
		DWORD o1423: 1;						// Y1423
		DWORD oInsideLight: 1;				// Y1424
		DWORD oSafetyReset: 1;				// Y1425
		DWORD oModeSelect: 1;				// Y1426
		DWORD o1427: 1;						// Y1427
		DWORD o1428: 1;						// Y1428
		DWORD o1429: 1;						// Y1429
		DWORD o1430: 1;						// Y1430
		DWORD o1431: 1;						// Y1431
	};
} DY_DATA_14;

///////////////////////////////////////////////////////////////////////////////

