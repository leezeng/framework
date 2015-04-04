#pragma once
#include "Defined.h"
class __declspec(dllexport) CLowDriveInterface
{
public:
	CLowDriveInterface(void);
	void Initialize();
	void ThreadProc();
	virtual ~CLowDriveInterface(void);
private:
	friend static unsigned int __stdcall ThreadFunc(void* pVoid);
	static LRESULT CALLBACK CallWndProc(HWND hWnd,unsigned int uMsg,WPARAM wParam,LPARAM lParam);
	HWND m_hWnd;
	HANDLE m_hThread;
	unsigned int m_uThreadId;
};

