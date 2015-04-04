#pragma once
#include "Factory.h"
class __declspec(dllexport) CDataObject:public CFactoryObject
{
public:
	//DECLARE_FACTORYCLASS(CDataObject)
	CDataObject(bool bAddToObjMap=true);
	virtual ~CDataObject(void);
private:
	unsigned long m_ulObjId;
	bool m_bIsAddToObjMap;
};

