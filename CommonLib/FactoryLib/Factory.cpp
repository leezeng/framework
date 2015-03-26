#include "StdAfx.h"
#include "Factory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool CFactoryObject::Register( const char* chClassName,Func pFunc )
{
	g_MapFunc[chClassName]=pFunc;
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
	auto it= g_MapFunc.find(chClassName);
	if (it!=g_MapFunc.end())
	{
		return it->second();
	}
	return nullptr;
}
