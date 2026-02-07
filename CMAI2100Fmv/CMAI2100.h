// CMAI2100.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

#define UM_DEVICE_SCAN	WM_USER+10

// CCMAI2100App:
// 이 클래스의 구현에 대해서는 CMAI2100.cpp을 참조하십시오.
//
class CCMAI2100App : public CWinApp
{
public:
	CCMAI2100App();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
	DECLARE_MESSAGE_MAP()

public:
	void DoEvents();
	void uSleep(int msec);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CCMAI2100App theApp;
