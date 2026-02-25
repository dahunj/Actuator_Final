#include "stdafx.h"

#include "FifoTaskProcessor.h"
#include <process.h> // _beginthreadex
#include <stdio.h>   // printf (데모 로그)

#include "AJinAXL.h"

FifoTaskProcessor proc;


// ------ 정적 멤버 초기화 ------
CRITICAL_SECTION FifoTaskProcessor::s_csCounter;
int              FifoTaskProcessor::s_nCounter = 0;

// ------ 생성/소멸 ------
FifoTaskProcessor::FifoTaskProcessor()
	:m_stop(false),
	m_worker(0),
	m_runningCount(0)
{
	InitializeCriticalSection(&m_cs);
	InitializeCriticalSection(&m_csCompleted);
	InitializeCriticalSection(&m_csRunning);

	// 전역(정적) 카운터용 CRITICAL_SECTION은 한 번만 초기화되길 원하지만
	// 데모 단순화를 위해 여기서 보수적으로 초기화 (다중 인스턴스 환경이면 가드 필요)
	static bool s_inited = false;
	if (!s_inited)
	{
		InitializeCriticalSection(&s_csCounter);
		s_inited = true;
	}
	m_head = 0;
	
	m_evtNewTask = CreateEvent(NULL, FALSE, FALSE, NULL); // auto-reset
}

FifoTaskProcessor::~FifoTaskProcessor()
{
	Stop();
	if (m_evtNewTask) CloseHandle(m_evtNewTask);
	DeleteCriticalSection(&m_csCompleted);
	DeleteCriticalSection(&m_csRunning);
	DeleteCriticalSection(&m_cs);
	// s_csCounter는 프로세스 종료 시 OS가 회수 (여기선 해제 생략)
}

// ------ 시작/종료 ------
bool FifoTaskProcessor::Start()
{
	if (m_worker) return true; // 이미 시작됨

	m_stop = false;

	unsigned int tid = 0;
	m_worker = (HANDLE)_beginthreadex(NULL, 0, &FifoTaskProcessor::WorkerThread, this, 0, &tid);
	return (m_worker != 0);
}

void FifoTaskProcessor::Stop()
{
	// 종료 플래그 set + worker 깨우기
	
	EnterCriticalSection(&m_cs);
	m_stop = true;
	LeaveCriticalSection(&m_cs);
	if (m_evtNewTask) SetEvent(m_evtNewTask);

	if (m_worker)
	{
		WaitForSingleObject(m_worker, INFINITE);
		CloseHandle(m_worker);
		m_worker = 0;
	}
	

	// 큐 정리
	EnterCriticalSection(&m_cs);
	m_tasks.clear();
	m_head = 0;				
	

	
	LeaveCriticalSection(&m_cs);

	// 실행 카운터 정리
	EnterCriticalSection(&m_csRunning);
	m_runningCount = 0;
	LeaveCriticalSection(&m_csRunning);

	// 완료 큐는 남겨두면 호출자가 수거 가능 (필요 시 비워도 됨)
}

// ------ 생산자 API ------
void FifoTaskProcessor::Enqueue(const Task& t)
{
	EnterCriticalSection(&m_cs);
	m_tasks.push_back(t);
	LeaveCriticalSection(&m_cs);

	SetEvent(m_evtNewTask); // 워커 깨우기
}

void FifoTaskProcessor::GetCompletedIds(std::vector<int>& outCompleted)
{
	outCompleted.clear();
	EnterCriticalSection(&m_csCompleted);
	if (!m_completedIds.empty())
		outCompleted.swap(m_completedIds); // 한번에 비우기
	LeaveCriticalSection(&m_csCompleted);
}

int FifoTaskProcessor::RunningCount() const
{
	EnterCriticalSection(&m_csRunning);
	int n = m_runningCount;
	LeaveCriticalSection(&m_csRunning);
	return n;
}

size_t FifoTaskProcessor::PendingCount() const
{
	size_t pending = 0;
	EnterCriticalSection(&m_cs);
	if (m_head < m_tasks.size()) pending = m_tasks.size() - m_head;
	LeaveCriticalSection(&m_cs);
	return pending;
}

// ------ 내부 구현 ------
unsigned int __stdcall FifoTaskProcessor::WorkerThread(void* pThis)
{
	FifoTaskProcessor* self = (FifoTaskProcessor*)pThis;
	self->Run();
	return 0;
}

void FifoTaskProcessor::Run()
{
	for (;;)
	{
		// 1) 종료 조건/작업 유무 확인
		Task t;
		bool haveTask = false;
		
		EnterCriticalSection(&m_cs);
		if (m_stop && m_head >= m_tasks.size())
		{
			LeaveCriticalSection(&m_cs);
			break; // 큐 비었고 정지면 종료
		}
		haveTask = TryDequeue_NoLock(t); // m_cs 보유 상태에서 호출
		
		LeaveCriticalSection(&m_cs);

		if (haveTask)
		{
			// 실행 카운트 +1
			EnterCriticalSection(&m_csRunning);
			++m_runningCount;
			LeaveCriticalSection(&m_csRunning);

			// 2) 실제 작업 처리(순차)
			EnterCriticalSection(&s_csCounter);			
			g_objAJinAXL.Get_pStatus(t.nAxis)->bRun = TRUE;
			g_objAJinAXL.StartThread(t.nType, t.nAxis, t.dPos);	

			LeaveCriticalSection(&s_csCounter);

			//// 완료 큐에 적재
			//EnterCriticalSection(&m_csCompleted);
			//m_completedIds.push_back(t.id);
			//LeaveCriticalSection(&m_csCompleted);

			// 실행 카운트 -1
			EnterCriticalSection(&m_csRunning);
			if (m_runningCount > 0) --m_runningCount;
			LeaveCriticalSection(&m_csRunning);

			continue; // 다음 루프
		}

		// 3) 대기: 새 작업 또는 주기적 타임아웃으로 정지 플래그 재확인
		WaitForSingleObject(m_evtNewTask, 1);

	}
	//Final End
}

bool FifoTaskProcessor::TryDequeue_NoLock(Task& out)
{

	if (m_head < m_tasks.size())
	{
		int nHeadNo = m_head;
		int nAxis = m_tasks[m_head].nAxis;
		if(g_objAJinAXL.Get_pStatus(nAxis)->bRun) 
		{
			return FALSE;
		}


		out = m_tasks[m_head++]; // head가 많이 전진했으면 압축(잔여만 앞으로)
		
		if (m_head > 1024 && m_head * 2 > m_tasks.size())
		{
			std::vector<Task> tmp(m_tasks.begin() + m_head, m_tasks.end());
			m_tasks.swap(tmp);
			m_head = 0;
		}
		return true;
	}	
	return false;
}