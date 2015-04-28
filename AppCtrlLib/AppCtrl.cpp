#include "StdAfx.h"
#include "AppCtrl.h"
#include "DriveManager.h"

CAppCtrl::CAppCtrl(void)
{
}


CAppCtrl::~CAppCtrl(void)
{
}

bool CAppCtrl::Receive( E_MACHINE_STATE eState )
{
	switch(eState)
	{
	case E_START:
		break;
	case E_INIT:
		break;
	case E_ADJUST:
		break;
	case E_CALCULATION:
		break;
	case E_SAVE:
		break;
	case E_END:
		break;
	}
	return false;
}

void CAppCtrl::Initialize()
{
	CDriveManager* pDriveManager=CDriveManager::GetInstance();
	pDriveManager->InitializeDeviceDriver(this);
}
