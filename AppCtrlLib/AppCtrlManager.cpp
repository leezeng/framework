#include "StdAfx.h"
#include "AppCtrlManager.h"


CAppCtrlManager::CAppCtrlManager(void):m_pAppCtrlController(nullptr)
{
	m_pAppCtrlController=new CAppCtrlController;
}


CAppCtrlManager::~CAppCtrlManager(void)
{
}

void CAppCtrlManager::InitCtrl()
{
	if (nullptr!=m_pAppCtrlController)
	{
		m_pAppCtrlController->InitCtrl();
	}
}
