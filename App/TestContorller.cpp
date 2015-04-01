#include "StdAfx.h"
#include "TestContorller.h"


CTestContorller::CTestContorller(void)
{
}


CTestContorller::~CTestContorller(void)
{
	CNotifierManager* pNotiferManager=CNotifierManager::GetInstance();
	pNotiferManager->UnRegisterMessage(this,0);
}

void CTestContorller::InitMessageMap( void )
{
	CNotifierManager* pNotiferManager=CNotifierManager::GetInstance();
	pNotiferManager->RegisterMessage(this,0,WM_TEST_MSG,E_NORMAL);
	MappingMessageFunction(WM_TEST_MSG,(P_NOTIFY_MSG_FUNC)&CTestContorller::OnTestMessage);

}

LRESULT CTestContorller::OnTestMessage( WPARAM wParam,LPARAM lParam )
{
	return TRUE;
}
