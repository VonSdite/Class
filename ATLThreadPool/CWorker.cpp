#include "CWorker.h"

LONG g_lCurrId = -1;

void CTask::DoTask(void *pvParam, OVERLAPPED *pOverlapped)
{
    
}

CWorker::CWorker() : m_dwExecs( 0 )
{
    m_lId = InterlockedIncrement( &g_lCurrId );
}

BOOL CWorker::Initialize(void *pvParam)
{
    return TRUE;
}

void CWorker::Terminate(void* /*pvParam*/)
{
}

void CWorker::Execute(RequestType dw, void *pvParam, OVERLAPPED* pOverlapped) throw()
{
    CTaskBase* pTask = (CTaskBase*)(DWORD_PTR)dw;
    pTask->DoTask(pvParam, pOverlapped);
    m_dwExecs++;
    delete pTask;
}

BOOL CWorker::GetWorkerData(DWORD /*dwParam*/, void ** /*ppvData*/)
{
    return FALSE;
}
