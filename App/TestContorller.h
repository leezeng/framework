#pragma once
#include "NotifyObject.h"
#include "NotifierManager.h"
#include "Message.h"
class CTestContorller:public CNotifyObject
{
public:
	CTestContorller(void);
	virtual ~CTestContorller(void);
	LRESULT OnTestMessage(WPARAM wParam,LPARAM lParam);
	virtual void InitMessageMap( void );

};

