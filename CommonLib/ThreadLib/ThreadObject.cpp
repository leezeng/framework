#include "StdAfx.h"
#include "ThreadObject.h"

unsigned int __stdcall  ThreadFunc( void* param )
{
	ThreadObject* pThreadObject=(ThreadObject*)param;
	if (nullptr!=pThreadObject)
	{ 
		if (pThreadObject->m_bIsRuning)
		{
			pThreadObject->ThreadProc();
		}
	}
	return 1;
}

ThreadObject::ThreadObject():m_uThreadId(0),m_bIsRuning(false)
{
}


ThreadObject::~ThreadObject(void)
{
} 


unsigned int ThreadObject::GetThreadID()
{
	return m_uThreadId;
}

void ThreadObject::Exit()
{
	if (m_bIsRuning)
	{
		m_bIsRuning=false;
		if (m_hThread!=nullptr)
		{
			
			DWORD dwExitCode=STILL_ACTIVE;
			while (dwExitCode==STILL_ACTIVE)
			{
				GetExitCodeThread(m_hThread,&dwExitCode);
			}
			CloseHandle(m_hThread);
		}
		m_uThreadId=0;
	}

}

bool ThreadObject::CreateThread(void* pVSercurity,unsigned int uStackSize,unsigned uInitFlag)
{
	if (m_bIsRuning==false)
	{
		m_bIsRuning=true;
		m_hThread=(HANDLE)_beginthreadex(pVSercurity,uStackSize,ThreadFunc,this,uInitFlag,&m_uThreadId);
		if (nullptr==m_hThread)
		{
			m_bIsRuning=false;
			m_uThreadId=0;
			return false;
		}
	}
	return true;
}

int ThreadObject::GetPriority()
{
	if (nullptr!=m_hThread)
	{
		return ::GetThreadPriority(m_hThread);
	}
	return THREAD_PRIORITY_ERROR_RETURN;
}

void ThreadObject::SetPriority( int nPriority )
{
	if (nullptr!=m_hThread)
	{
		::SetThreadPriority(m_hThread,nPriority);
	}
}

DWORD ThreadObject::Suspend()
{
	if (nullptr!=m_hThread)
	{
		return ::SuspendThread(m_hThread);
	}
	return 0;
}

void ThreadObject::ThreadProc()
{
	MSG msg;
	if(PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
	{
		OnMessage(msg.message,msg.wParam,msg.lParam);
	} 
}

bool ThreadObject::RestartThread(void* pVSercurity,unsigned int uStackSize,unsigned uInitFlag)
{
	Exit();
	return CreateThread(pVSercurity,uStackSize,uInitFlag);
}

bool ThreadObject::IsRuning()
{
	if(nullptr!=m_hThread)
	{
		return m_bIsRuning;
	}
	return false;
}

 