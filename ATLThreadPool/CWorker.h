#pragma once
#include <atlutil.h>

class CTaskBase;
class CTask;

class CWorker
{
public:
    typedef DWORD_PTR RequestType;

    CWorker();

    virtual BOOL Initialize(void *pvParam);

    virtual void Terminate(void* /*pvParam*/);

    void Execute(RequestType dw, void *pvParam, OVERLAPPED* pOverlapped) throw();

    virtual BOOL GetWorkerData(DWORD /*dwParam*/, void ** /*ppvData*/);

protected:
    DWORD	m_dwExecs;
    LONG	m_lId;
}; // CWorker

class CTaskBase
{
public:
    virtual void DoTask(void *pvParam, OVERLAPPED *pOverlapped)=0;
};

class CTask : public CTaskBase
{
public:
    void DoTask(void *pvParam, OVERLAPPED *pOverlapped);
};

