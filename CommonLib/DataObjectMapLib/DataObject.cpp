#include "stdafx.h"
#include "DataObject.h"
#include "DataObjectManager.h"
//IMPLEMENT_FACTORYCLASS(CDataObject)
CDataObject::CDataObject(bool bAddToObjMap):m_bIsAddToObjMap(bAddToObjMap)
{
	if (bAddToObjMap)
	{
		m_ulObjId=CDataObjectManager::GetInstance()->Add(this);
	}
	
}


CDataObject::~CDataObject(void)
{
}
