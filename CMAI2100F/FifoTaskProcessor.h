#pragma once
#include "AJinDefine.h"
#include <windows.h>
#include <vector>

// ===== 작업 정의 =====
// 필요 시 사용자 정의 필드를 더 추가해도 됨 (예: 함수 포인터, 컨텍스트 포인터 등)
struct Task
{
	int			id;
	int			nType;
	int			nAxis; 
	double		dPos;	
};

// ===== FIFO 작업 처리기 =====
// - std::vector를 큐처럼 사용 (head 인덱스 전진 + 주기적 압축)
// - Start()로 워커 스레드 시작, Enqueue()로 작업 추가
// - GetCompletedIds()로 완료된 작업 ID 수거(순서 무관)
// - Stop()으로 안전 종료(잔여 작업 소진 후 종료)
class FifoTaskProcessor
{
public:
	FifoTaskProcessor();
	~FifoTaskProcessor();

	// 워커 스레드 시작/종료
	bool Start();
	void Stop();

	// 작업 추가(생산자 측 호출)
	void Enqueue(const Task& t);

	// 완료된 작업 ID들을 out 벡터로 넘기고 내부 큐는 비움
	void GetCompletedIds(std::vector<int>& outCompleted);

	// 현재 실행 중인(워커가 처리 중 + 대기 큐 포함) 대략적 개수 정보
	int    RunningCount() const;   // 워커가 처리 중인 수 (여기선 0/1 추정 + 큐 길이 반영)
	size_t PendingCount() const;   // 대기 큐 길이(대략치)

private:
	// 복사 금지
	FifoTaskProcessor(const FifoTaskProcessor&);
	FifoTaskProcessor& operator=(const FifoTaskProcessor&);

	// 워커 스레드 진입점
	static unsigned int __stdcall WorkerThread(void* pThis);
	void Run();

	// m_cs 보유 상태에서만 호출
	bool TryDequeue_NoLock(Task& out);

private:
	// --- 큐(벡터) + head 인덱스 ---
	std::vector<Task> m_tasks;
	size_t            m_head;

	// --- 동기화/제어 ---
	mutable CRITICAL_SECTION  m_cs;             // 큐 보호
	HANDLE            m_evtNewTask;   // 새 작업 도착 알림 (auto-reset)
	volatile bool     m_stop;         // 종료 플래그
	HANDLE            m_worker;       // 워커 스레드 핸들

	// --- 완료 ID 큐 ---
	mutable CRITICAL_SECTION  m_csCompleted;
	std::vector<int>  m_completedIds;

	// --- 실행 개수 추정치 ---
	mutable CRITICAL_SECTION m_csRunning;
	int               m_runningCount;

	// 데모용 공유 카운터(작업 수행 중 증가/로그용)
	static CRITICAL_SECTION s_csCounter;
	static int              s_nCounter;
};

extern FifoTaskProcessor proc;