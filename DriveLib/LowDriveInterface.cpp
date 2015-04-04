#include "StdAfx.h"
#include "LowDriveInterface.h"
#include "Message.h"
static unsigned int __stdcall ThreadFunc( void* pVoid )
{
	CLowDriveInterface* pLowDriver=new CLowDriveInterface;
	if (pLowDriver!=nullptr)
	{
		pLowDriver->ThreadProc();
	}
	return 1;
}


CLowDriveInterface::CLowDriveInterface(void):m_hThread(nullptr),m_hWnd(nullptr),m_uThreadId(0)
{
}


CLowDriveInterface::~CLowDriveInterface(void)
{
}

void CLowDriveInterface::ThreadProc()
{
	WNDCLASS wc={0};
	wc.lpfnWndProc=&CLowDriveInterface::CallWndProc;
	wc.hInstance=GetModuleHandle(NULL);
	wc.lpszClassName=DRIVE_WND;
	RegisterClass(&wc);
	HWND hWnd=NULL;
	hWnd=CreateWindow(DRIVE_WND,nullptr,0,0,0,1,1,nullptr,nullptr,GetModuleHandle(nullptr),this);
	SetWindowLongPtr(hWnd,GWLP_USERDATA,(LONG_PTR)this);
	this->m_hWnd=hWnd;
	ShowWindow(m_hWnd,SW_HIDE);
	MSG msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK CLowDriveInterface::CallWndProc( HWND hWnd,unsigned int uMsg,WPARAM wParam,LPARAM lParam )
{
	CLowDriveInterface* pThis=(CLowDriveInterface*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
	switch(uMsg)
	{
	case WM_DEVICE_NOTIFY:
		{
			CString strMsgId;
			strMsgId.Format(_T("%d\r\n"),(int)wParam);
			AfxOutputDebugString(strMsgId);
		}
		break;
	}
	return TRUE;
}

void CLowDriveInterface::Initialize()
{
	if (m_hThread==nullptr)
	{
		m_hThread=(HANDLE)_beginthreadex(nullptr,0,ThreadFunc,this,0,&m_uThreadId);

	}
	
}

