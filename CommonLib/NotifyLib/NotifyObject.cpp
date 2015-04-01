#include "StdAfx.h"
#include "NotifyObject.h"


CNotifyObject::CNotifyObject(void):m_pThisObj(nullptr),m_nNotifyGroupId(0)
{
}


CNotifyObject::~CNotifyObject(void)
{
}

void CNotifyObject::MappingMessageFunction( unsigned int uMsgId,P_NOTIFY_MSG_FUNC pMsgFunc,void* pThisObj/*=nullptr*/ )
{
	if (nullptr!=pThisObj)
	{
		m_pThisObj=pThisObj;
	}
	m_mapMsgFunc.insert(pair<unsigned int,P_NOTIFY_MSG_FUNC>(uMsgId,pMsgFunc));
}

LRESULT CNotifyObject::ProcessNotify( unsigned int uMsgId,WPARAM wParam,LPARAM lParam )
{
	map<unsigned int,P_NOTIFY_MSG_FUNC>::iterator iter=m_mapMsgFunc.find(uMsgId);
	if (iter!=m_mapMsgFunc.end())
	{
		P_NOTIFY_MSG_FUNC pFunc=iter->second;
		if (nullptr!=pFunc)
		{
			if (m_pThisObj)
			{
				return (((CNotifyObject*)(m_pThisObj))->*pFunc)(wParam,lParam);
			}
			else
			{
				return (this->*pFunc)(wParam,lParam);
			}
		}
	}
	return FALSE;
}

int CNotifyObject::GetGroupId()
{
	return m_nNotifyGroupId;
}

void CNotifyObject::SetGroupId( int nGroupId )
{
	m_nNotifyGroupId=nGroupId;
}
