#pragma once
#include "AutoLock.h"
#include <map>
#include <Windows.h>
using std::map;
using std::pair;
class __declspec(dllexport) CIOCPThreadPool
{
public:
	CIOCPThreadPool(void);
	~CIOCPThreadPool(void);
	BOOL Initialize();
	BOOL QueueRequest(DWORD_PTR dwPtr);
	void ShutDown();
	void Exit();
	BOOL IsThreadPoolAlive();
protected:
	static friend unsigned __stdcall ThreadFunc(void* param);
	BOOL ThreadProc();
private:
	HRESULT InternalInitializePool(DWORD dwNum);
	DWORD GetThreadCount();
private:
	DWORD m_dwCurrentExitThreadId;
	map<unsigned int,HANDLE> m_mapThread;
	HANDLE m_hIOCPort;
	CAutoLock::CLock m_lock;
	HANDLE m_hShutEvent;
};

