#include "StdAfx.h"
#include "DBDataObject.h"


CDBDataObject::CDBDataObject(bool bIsAddToMap):m_pclsTableInfoMap(nullptr)
											  ,m_pRowDataList(nullptr)
											  ,m_nCount(0)
{
}


CDBDataObject::~CDBDataObject(void)
{
}

bool CDBDataObject::ReflectTableInfoMap(int nIndex,CString strTableName,CString strField,E_DB_TYPE eType,void *pvData,bool bXmlData)
{
	map<CString, PDB_FIELD_INFO>::iterator clsIter;
	PDB_FIELD_INFO pDbFieldInfo = nullptr;
	if (pvData==NULL)
	{
		return false;
	}
	if (nullptr==m_pclsTableInfoMap)
	{
		m_pclsTableInfoMap=new map<CString, PDB_FIELD_INFO>();
	}
	if (!HasReflectTableInfoMap())
	{
		return FALSE;
	}
	clsIter = m_pclsTableInfoMap->find(strField);
	if (clsIter == m_pclsTableInfoMap->end())
	{
		pDbFieldInfo =  new DB_FIELD_INFO();
	}
	else
	{
		pDbFieldInfo = clsIter->second;
	}
	if (NULL == pDbFieldInfo)
	{
		return FALSE;
	}
	pDbFieldInfo->strTableName = strTableName;
	pDbFieldInfo->strField = strField;
	pDbFieldInfo->eType = eType;
	pDbFieldInfo->pvData = pvData;
	pDbFieldInfo->bFlag = FALSE;
	pDbFieldInfo->nSorting = nIndex;
	pDbFieldInfo->bPk = FALSE;
	pDbFieldInfo->nDataLen = 0;
	pDbFieldInfo->bXmlData = bXmlData; 
	m_pclsTableInfoMap->insert(pair<CString, PDB_FIELD_INFO>(strField,pDbFieldInfo)); 
	m_nCount++;
	return TRUE;
}

bool CDBDataObject::HasReflectTableInfoMap()
{
	if (nullptr!=m_pclsTableInfoMap)
	{
		return true;
	}
	return false;
}

void CDBDataObject::ReflectFieldEx()
{

}

void CDBDataObject::ClearReflect()
{

}

void CDBDataObject::RegiestFieldEx()
{

}

void CDBDataObject::RegiestXMLFieldEx()
{

}

bool CDBDataObject::UnRegiestFieldEx()
{
	return false;
}

E_DB_TYPE CDBDataObject::GetFileType(const CString& strName)
{
	map<CString, PDB_FIELD_INFO>::iterator iter=m_pclsTableInfoMap->find(strName);
	if (iter!=m_pclsTableInfoMap->end())
	{
		PDB_FIELD_INFO pInfo=iter->second;
		return pInfo->eType;
	}
	return DB_TYPE_NULL;
}
