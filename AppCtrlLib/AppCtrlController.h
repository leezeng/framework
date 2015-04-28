#pragma once
#include "AppCtrl.h"
class __declspec(dllexport) CAppCtrlController
{
public:
	CAppCtrlController(void);
	~CAppCtrlController(void);
	void InitCtrl();
private:
	CAppCtrl m_AppCtrl;
};

