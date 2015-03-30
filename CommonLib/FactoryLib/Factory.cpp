#include "StdAfx.h"
#include "Factory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
map<string,Func>* CFactoryObject::m_MapFunc=new MapFunction;
bool CFactoryObject::Register( const char* chClassName,Func pFunc )
{
	(*m_MapFunc)[chClassName]=pFunc;
	return true;
}

CFactoryObject::~CFactoryObject()
{
}

CFactoryObject::CFactoryObject()
{
	
}

CFactoryObject* CFactoryObject::GetInstance( const char* chClassName )
{
	auto it= m_MapFunc->find(chClassName);
	if (it!=m_MapFunc->end())
	{
		return it->second();
	}
	return nullptr;
}

void CFactoryObject::RelaseInstance()
{
	if (nullptr!=m_MapFunc)
	{
		m_MapFunc->clear();
		delete m_MapFunc;
		m_MapFunc=nullptr;
	}
}
