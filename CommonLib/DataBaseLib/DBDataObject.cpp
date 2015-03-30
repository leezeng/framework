#include "StdAfx.h"
#include "DBDataObject.h"


CDBDataObject::CDBDataObject(bool bIsAddToMap):m_pclsTableInfoMap(nullptr)
											  ,m_pRowDataList(nullptr)
											  ,m_nCount(0)
{
	m_strClassName="CDBDataObject";
}


CDBDataObject::~CDBDataObject(void)
{
}

bool CDBDataObject::ReflectTableInfoMap(int nIndex,string strTableName,string strField,E_DB_TYPE eType,void *pvData,bool bIsPk,bool bXmlData)
{
	map<string, PDB_FIELD_INFO>::iterator clsIter;
	PDB_FIELD_INFO pDbFieldInfo = nullptr;
	if (pvData==NULL)
	{
		return false;
	}
	if (nullptr==m_pclsTableInfoMap)
	{
		m_pclsTableInfoMap=new map<string, PDB_FIELD_INFO>();
	}
	if (!HasReflectMap())
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
	pDbFieldInfo->bPk = bIsPk;
	pDbFieldInfo->nDataLen = 0;
	pDbFieldInfo->bXmlData = bXmlData; 
	m_pclsTableInfoMap->insert(pair<string, PDB_FIELD_INFO>(strField,pDbFieldInfo)); 
	m_nCount++;
	return TRUE;
}


void CDBDataObject::ClearReflect()
{
	if (HasReflectMap())
	{
		DeleteReflectMap();
	}
}

 

E_DB_TYPE CDBDataObject::GetFiledType(const string& strName)
{
	map<string, PDB_FIELD_INFO>::iterator iter=m_pclsTableInfoMap->find(strName);
	if (iter!=m_pclsTableInfoMap->end())
	{
		PDB_FIELD_INFO pInfo=iter->second;
		return pInfo->eType;
	}
	return DB_TYPE_NULL;
}

const char* CDBDataObject::GetClassName()
{
	return m_strClassName.c_str();
}

void* CDBDataObject::GetFiledValue( const string& strName )
{
	map<string, PDB_FIELD_INFO>::iterator iter=m_pclsTableInfoMap->find(strName);
	if (iter!=m_pclsTableInfoMap->end())
	{
		PDB_FIELD_INFO pInfo=iter->second;
		return pInfo->pvData;
	}
	return nullptr;
}

bool CDBDataObject::SetFieldAllEx( bool bIsDbData )
{
	ReflectDBField();
	if (bIsDbData)
	{
		ReflectDBFieldEx();
	}
	else
	{
		ReflectXMLField();
	}
	return true;
}

void CDBDataObject::ReflectDBField()
{

}

void CDBDataObject::ReflectDBFieldEx()
{

}

void CDBDataObject::ReflectXMLField()
{

}

bool CDBDataObject::UnReflectDBFieldEx()
{
	return true;
}

bool CDBDataObject::HasReflectMap()
{
	if (nullptr!=m_pclsTableInfoMap)
	{
		return true;
	}
	return false;
}

void CDBDataObject::DeleteReflectMap()
{
	for (map<string, PDB_FIELD_INFO>::iterator iter=m_pclsTableInfoMap->begin();iter!=m_pclsTableInfoMap->end();iter++)
	{
		PDB_FIELD_INFO pInfo=iter->second;
		delete pInfo;
		pInfo=nullptr;
	}
	m_pclsTableInfoMap->clear();
}

void CDBDataObject::UnSetFieldAllEx()
{
	ClearReflect();
}

void CDBDataObject::GetConditionList( map<string,string>& pPkMap )
{
	string strTemp;
	string strCondition;
	list<string> lstTableName;
	string strCurrTableName="";
	if (!HasReflectMap())
	{
		return;
	}
	for (map<string,PDB_FIELD_INFO>::iterator iter=m_pclsTableInfoMap->begin();iter!=m_pclsTableInfoMap->end();iter++)
	{
		PDB_FIELD_INFO pFieldInfo=iter->second;
		if (nullptr!=pFieldInfo)
		{
			if (true==pFieldInfo->bPk)
			{
				strCurrTableName=pFieldInfo->strTableName;
				if (strCurrTableName=="")
				{
					continue;
				}
				lstTableName.push_back(strCurrTableName);
			}
		}
	}
	lstTableName.unique();
	for (list<string>::iterator it=lstTableName.begin();it!=lstTableName.end();it++)
	{
		list<string> lstPk;
		for (map<string,PDB_FIELD_INFO>::iterator iter=m_pclsTableInfoMap->begin();iter!=m_pclsTableInfoMap->end();iter++)
		{
			PDB_FIELD_INFO pFieldInfo=iter->second;
			if (nullptr!=pFieldInfo)
			{
				strCurrTableName=pFieldInfo->strTableName;
				if (strCurrTableName=="")
				{
					continue;
				}
				if(pFieldInfo->bPk==true&&strCurrTableName==(*it))
				{
					strTemp=strCurrTableName+".";
					strTemp+=pFieldInfo->strField;
					strTemp+="=";
					switch(pFieldInfo->eType)
					{
					case DB_TYPE_INT32:
						{ 
							int nValue=*((int*)(pFieldInfo->pvData));
							char ch[8];
							sprintf_s(ch,"%d",nValue);
							string str(ch);
							strTemp+=str;
						}
						break;
					case DB_TYPE_INT64:
						break;
					case DB_TYPE_DOUBLE:
						break;
					case DB_TYPE_CHAR:
						break;
					case DB_TYPE_TIME:
						break;
					case DB_TYPE_STRING:
						break;
					case DB_TYPE_BOOL:
						break;
					case DB_TYPE_BLOB:
						break;
					case DB_TYPE_NULL:
						break;
					}
				}
			}
		}
	}

	
}

void CDBDataObject::GetSqlStr( list<string>& lstStrSql,CDBOperation* pOperation )
{
	map<string,string> mapCondition;
	
	GetConditionList(mapCondition);


	switch(m_eOperType)
	{
	case DB_SELECT:
		{
			string strTableName;

		}
		break;
	case DB_INSERT:
		break;
	case DB_UPDATE:
		break;
	case DB_DELETE:
		break;
	}
}

void CDBDataObject::SetOperatorType( E_OPERATOR_TYPE eOperType )
{
	m_eOperType=eOperType;
}

//PDB_FIELD_INFO CDBDataObject::GetBeginDBFiledInfo()
//{
//	if (HasReflectMap())
//	{
//	    map<string, PDB_FIELD_INFO>::iterator iter=m_pclsTableInfoMap->begin();
//		if (iter!=m_pclsTableInfoMap->end())
//		{
//			return iter->second;
//		}
//	}
//	return nullptr;
//}
//
//PDB_FIELD_INFO CDBDataObject::GetNextDBFiledInfo()
//{
//
//}
//
//PDB_FIELD_INFO CDBDataObject::GetFirstDBFiledInfo()
//{
//
//}

 