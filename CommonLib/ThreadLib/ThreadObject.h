#pragma once
#include "NotifyObject.h"
#include "AutoLock.h"
class __declspec(dllexport) ThreadObject:public CNotifyObject
{
public:
	ThreadObject();
	~ThreadObject(void);
	bool CreateThread(void* pVSercurity=nullptr,unsigned int uStackSize=0,unsigned uInitFlag=0);
	bool RestartThread(void* pVSercurity=nullptr,unsigned int uStackSize=0,unsigned uInitFlag=0);
	int GetPriority();
	void SetPriority(int nPriority);
	DWORD Suspend();
	unsigned int GetThreadID();
	void Exit();
	bool IsRuning();
protected:
	static friend unsigned int __stdcall ThreadFunc(void* param);
	virtual void ThreadProc();
	virtual void OnMessage(UINT msg,WPARAM wParam,LPARAM lParam)=0;
private:
	HANDLE m_hThread;
	unsigned int m_uThreadId;
protected:
	bool m_bIsRuning;
};

