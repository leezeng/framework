
// App.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CAppApp:
// See App.cpp for the implementation of this class
//

class CAppApp : public CWinApp
{
public:
	CAppApp();

// Overrides
public:
	virtual BOOL InitInstance();
private:
	void OnNotifyThreadMsg(WPARAM wParam, LPARAM lParam);
// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAppApp theApp;