#include "stdafx.h"
#include "DataObjectManager.h"

CDataObjectManager* CDataObjectManager::m_pDataObjectManger=nullptr;
CDataObjectManager::CDataObjectManager():m_ulCurrId(begin)
										,m_pMapDataObj(new hash_map<unsigned long,CDataObject*>())
{
}


CDataObjectManager::~CDataObjectManager()
{
	if (nullptr!=m_pMapDataObj)
	{
		delete m_pMapDataObj;
		m_pMapDataObj=NULL;
	}
}

CDataObjectManager* CDataObjectManager::GetInstance()
{
	if (nullptr==m_pDataObjectManger)
	{
		m_pDataObjectManger=new CDataObjectManager();
	}
	return m_pDataObjectManger;
}

void CDataObjectManager::RelaseInstance()
{
	if (m_pDataObjectManger)
	{
		delete m_pDataObjectManger;
		m_pDataObjectManger=nullptr;
	}
}

unsigned long CDataObjectManager::Add( CDataObject* pObj )
{
	CAutoLock autoLock(&m_lock);
	m_ulCurrId++;
	if (m_ulCurrId==end)
	{
		m_ulCurrId=begin;
		while(true)
		{
			hash_map<unsigned long,CDataObject*>::iterator it=m_pMapDataObj->find(m_ulCurrId);
			if (it!=m_pMapDataObj->end())
			{
				m_ulCurrId++;
			}
			else
			{
				break;
			}
		}
	}
	m_pMapDataObj->insert(pair<unsigned long,CDataObject*>(m_ulCurrId,pObj));
	return m_ulCurrId;
}

void CDataObjectManager::Remove( unsigned long ulObjId )
{
	CAutoLock autoLock(&m_lock);
	hash_map<unsigned long,CDataObject*>::iterator it=m_pMapDataObj->find(ulObjId);
	if (it!=m_pMapDataObj->end())
	{
		m_pMapDataObj->erase(it);
	}
}

CDataObject* CDataObjectManager::GetDataObject( unsigned long ulObjId )
{
	hash_map<unsigned long,CDataObject*>::iterator it=m_pMapDataObj->find(ulObjId);
	if (it!=m_pMapDataObj->end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}


CDataObjectManager::CInternal::CInternal()
{

}

CDataObjectManager::CInternal::~CInternal()
{
	CDataObjectManager::RelaseInstance();
}
