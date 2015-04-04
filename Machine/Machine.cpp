// Machine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Defined.h"
#include "Message.h"
#include <Windows.h>
int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hEvent=NULL;
	hEvent=OpenEvent(EVENT_ALL_ACCESS,false,_T("14F8430F-E688-4736-9A3B-43C1421C29D1"));
	if (hEvent!=NULL)
	{
		return 0;
	}
	CreateEvent(NULL,false,false,_T("14F8430F-E688-4736-9A3B-43C1421C29D1"));

	printf("machine start\r\n");
	while(true)
	{
		HWND hWnd=FindWindow(DRIVE_WND,NULL);
		if (hWnd==nullptr)
		{
			printf("machine disconnnet !\r\n");
			Sleep(1000);
			continue;
		}
		for (int i=E_START;i<=E_END;i++)
		{
			printf("state id:%d\r\n",i);
			::PostMessage(hWnd,WM_DEVICE_NOTIFY,i,0);
			Sleep(1000);
		}
	}
	printf("machine shutdown.\r\n");
	return 0;
}

