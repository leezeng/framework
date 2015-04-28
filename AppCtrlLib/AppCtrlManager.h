#pragma once
#include "AppCtrlController.h"
class __declspec(dllexport) CAppCtrlManager
{
private:
	CAppCtrlManager(void);
	~CAppCtrlManager(void);
public:
	static CAppCtrlManager* GetInstance()
	{
		static CAppCtrlManager appCtrlManager;
		return &appCtrlManager;
	}

	void InitCtrl();
private:
	CAppCtrlController *m_pAppCtrlController;
};

