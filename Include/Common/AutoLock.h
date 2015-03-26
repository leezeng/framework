#pragma once
#include <windows.h>
class __declspec(dllexport) CAutoLock
{
public:
	class __declspec(dllexport) CLock
	{
	private:
		CLock& operator=(CLock&){return *this;}
		CLock(CLock&){};
	public:
		CLock()
		{
			::InitializeCriticalSection(&m_cs);
		};
		~CLock()
		{
			::DeleteCriticalSection(&m_cs);
		};
		void Lock()
		{
			::EnterCriticalSection(&m_cs);
		};
		void Unlock()
		{
			::LeaveCriticalSection(&m_cs);
		};
	private:
		CRITICAL_SECTION m_cs;
	};
public:
	CAutoLock(CLock* lock):m_lock(lock){
		  m_lock->Lock(); 
	};
	~CAutoLock()
	{
		  m_lock->Unlock();
		  m_lock=nullptr;
	};
	 
private:
	CLock* m_lock;
};

