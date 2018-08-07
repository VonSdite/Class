## CThreadPool ##

MFC提供了一个叫做`CThreadPool` 的类，这是一个模板类，基于完成端口开发的一个线程池。

### 以下是CThreadPool的使用介绍

主要的伪代码如下
**线程池要操作的任务通过实现CTaskBase的DoTask函数来完成**
```C++
#include "CWorker.h" 	// 包含头文件
#define THREADPOOL_SIZE 5

// 实例化线程池对象，CWorker是自己定义的Worker类， MSDN中定义了它的原型，它必须包含下面
// 所列的几个函数Initialize,Execute,Terminate；具体Worker定义见下面代码
CThreadPool<CWorker> threadPool; 
	
threadPool.Initialize(NULL, THREADPOOL_SIZE);	// 初始化线程池
CTaskBase *pTask = NULL;
pTask = new CTask();							// 创建任务
threadPool.QueueRequest((CParseWorker::RequestType) pTask); // 执行线程池任务

/*
CThreadPool 调用Initialize，调用此方法来初始化线程池。
HRESULT Initialize(
    void* pvWorkerParam = NULL,
    int nNumThreads = 0,
    DWORD dwStackSize = 0,
    HANDLE hCompletion = INVALID_HANDLE_VALUE) throw();
参数
pvWorkerParam
辅助参数传递给辅助线程对象Initialize， Execute，和Terminate方法。

nNumThreads
请求的池中的线程数。

如果nNumThreads是负数，其绝对值的数值将乘以中要获取的线程总数的计算机的处理器数。

如果nNumThreads为零，ATLS_DEFAULT_THREADSPERPROC 将乘以中要获取的线程总数的计算机的处理器数。 默认值为每个处理器的 2 个线程。 如有必要，可以包括 atlutil.h 之前定义此符号自己正整数值。
dwStackSize
在池中每个线程堆栈大小。

hCompletion
若要将与完成端口相关联的对象的句柄。

返回值
返回成功，则为 S_OK 或失败时的错误 HRESULT。
*/


```

**CWoker.h**
```C++
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
```

**CWorker.cpp**
```C++
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

```