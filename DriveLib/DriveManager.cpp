#include "StdAfx.h"
#include "DriveManager.h"


CDriveManager::CDriveManager(void):m_pDriverInterface(nullptr)
{
}


CDriveManager::~CDriveManager(void)
{
}

void CDriveManager::InitializeDeviceDriver()
{
	if (m_pDriverInterface==nullptr)
	{
		m_pDriverInterface=new CLowDriveInterface;
		m_pDriverInterface->Initialize();
	}
}
