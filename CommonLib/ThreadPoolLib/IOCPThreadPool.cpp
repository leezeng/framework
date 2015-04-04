#include "StdAfx.h"
#include "IOCPThreadPool.h"
#include "Woker.h"
static unsigned int __stdcall ThreadFunc( void* param )
{
	CIOCPThreadPool* pThreadPool=(CIOCPThreadPool*)(param);
	if (NULL!=pThreadPool)
	{
		pThreadPool->ThreadProc();
		return 1;
	}
	return 0;
}

CIOCPThreadPool::CIOCPThreadPool(void):m_dwCurrentExitThreadId(0)
									,m_hIOCPort(NULL)
{
	m_hShutEvent=CreateEvent(NULL,FALSE,FALSE,NULL);	
}


CIOCPThreadPool::~CIOCPThreadPool(void)
{
	CloseHandle(m_hShutEvent);
}

BOOL CIOCPThreadPool::ThreadProc()
{
	DWORD dwBytesTransfered;
	ULONG_PTR dwCompletionKey;
	OVERLAPPED* pOverlapped;
	{
		CWoker woker;
		while(GetQueuedCompletionStatus(m_hIOCPort,&dwBytesTransfered,&dwCompletionKey,&pOverlapped,INFINITE))
		{
			if (-1==(int)(pOverlapped))
			{
				break;
			}
			else
			{
				woker.Execute((DWORD_PTR)dwCompletionKey);
			}
		}
	}
	m_dwCurrentExitThreadId = GetCurrentThreadId();
	SetEvent(m_hShutEvent);
	return TRUE;
}

BOOL CIOCPThreadPool::Initialize()
{
	CAutoLock autoLock(&m_lock);
	if (NULL!=m_hIOCPort)
	{
		return FALSE;
	}

	DWORD dwNum=GetThreadCount();
	m_hIOCPort=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,dwNum);
	if (NULL==m_hIOCPort)
	{
		return FALSE;
	}
	InternalInitializePool(dwNum);
	return TRUE;
}

DWORD CIOCPThreadPool::GetThreadCount()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	DWORD dwNumber=systemInfo.dwNumberOfProcessors;
	dwNumber=dwNumber>1?dwNumber-1:1;
	return dwNumber;
}

HRESULT CIOCPThreadPool::InternalInitializePool( DWORD dwNum )
{
	DWORD dwCurrThreadNum=(DWORD)m_mapThread.size();
	if (dwNum<dwCurrThreadNum)
	{
		DWORD dwShutNum=dwCurrThreadNum-dwNum;
		for (;dwShutNum>0;dwShutNum--)
		{
			if (PostQueuedCompletionStatus(m_hIOCPort,0,0,(LPOVERLAPPED)-1))
			{	
				DWORD dwRet=WaitForSingleObject(m_hShutEvent,INFINITE);
				if (dwRet==WAIT_OBJECT_0)
				{
					map<unsigned int,HANDLE>::iterator iter=m_mapThread.find(m_dwCurrentExitThreadId);
					if (iter!=m_mapThread.end())
					{
						if(WAIT_OBJECT_0==WaitForSingleObject(iter->second,INFINITE))
						{
							m_mapThread.erase(iter);
						}
					}
				}
			}
		}
	}
	else
	{
		unsigned int nThreadId;
		for (;dwCurrThreadNum<dwNum;dwCurrThreadNum++)
		{
		 	HANDLE hThread =(HANDLE)_beginthreadex(NULL,0,&ThreadFunc,this,0,&nThreadId);
			if (NULL==hThread)
			{
				HRESULT hr = GetLastError();
				ASSERT(hr != S_OK);
				return hr;
			} 
			m_mapThread.insert(pair<unsigned int,HANDLE>(nThreadId,hThread));
		}
	}
	return S_OK;  
}

BOOL CIOCPThreadPool::QueueRequest( DWORD_PTR dwPtr )
{
	if (NULL!=dwPtr)
	{
		if (PostQueuedCompletionStatus(m_hIOCPort,0,(ULONG_PTR)dwPtr,NULL))
		{
			return TRUE;
		}
	}
	return FALSE;
}

void CIOCPThreadPool::ShutDown()
{
	if (NULL!=m_hIOCPort)
	{
		CAutoLock _auto(&m_lock);
		InternalInitializePool(0);
		CloseHandle(m_hIOCPort);
		m_hIOCPort=NULL;
	}
}

void CIOCPThreadPool::Exit()
{
	if (NULL!=m_hIOCPort)
	{
		CAutoLock _auto(&m_lock);
		CloseHandle(m_hIOCPort);
		m_hIOCPort=NULL;
		for (map<unsigned int,HANDLE>::iterator iter=m_mapThread.begin();iter!=m_mapThread.end();iter++)
		{
			DWORD dwExitCode;
			GetExitCodeThread(iter->second,&dwExitCode);
			while(dwExitCode == STILL_ACTIVE)  
			{
				GetExitCodeThread(iter->second, &dwExitCode);
			}
			CloseHandle(iter->second);
		}
		m_mapThread.clear();
	}
}

BOOL CIOCPThreadPool::IsThreadPoolAlive()
{
	return NULL==m_hIOCPort?FALSE:TRUE;
}

