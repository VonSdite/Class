#ifndef __THREAD__
#define __THREAD__

#include <Windows.h>
#include <tchar.h>
#include <process.h>

class Thread 
{  
protected:
   
    HANDLE hThread;
    unsigned uiThreadId;

    static unsigned __stdcall _run(void * pThis)
    {
        Thread * pthX = (Thread *)pThis;  
        pthX->run();           
        return 1;  
    }

    virtual void run() = 0;

public:  

    void start(DWORD nTimeOutMs=-1)
    {
        this->hThread = (HANDLE) _beginthreadex(
            NULL,
            0,
            Thread::_run,
            this,
            CREATE_SUSPENDED,
            &uiThreadId
            );

        ResumeThread(hThread);
        if (nTimeOutMs != -1 && nTimeOutMs >= 0)
            WaitForSingleObject(hThread, nTimeOutMs);
    }
    
};  

#endif