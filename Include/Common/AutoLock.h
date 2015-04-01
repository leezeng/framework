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
	CAutoLock(CLock* lock):m_pLock(lock){
		  m_pLock->Lock(); 
	};
	~CAutoLock()
	{
		  m_pLock->Unlock();
		  m_pLock=nullptr;
	};
	 
private:
	CLock* m_pLock;
};

