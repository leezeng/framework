#pragma once
#include "Listener.h"
class __declspec(dllexport) CAppCtrl:public CListener
{
public:
	CAppCtrl(void);
	~CAppCtrl(void);
	virtual bool Receive( E_MACHINE_STATE eState );
	void Initialize();
};

