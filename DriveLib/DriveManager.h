#pragma once
//#include "ThreadObject.h"
#include "LowDriveInterface.h"
class __declspec(dllexport) CDriveManager
{
private:
	CDriveManager(void);
	~CDriveManager(void);
public:
	static CDriveManager* GetInstance()
	{
		static CDriveManager m_DriverManager;
		return &m_DriverManager;
	};
	void InitializeDeviceDriver();
private:
	CLowDriveInterface* m_pDriverInterface;
};

