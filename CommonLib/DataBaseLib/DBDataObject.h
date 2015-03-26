#pragma once
#include "DataObject.h"
#include <list>
using std::list;
using std::pair;
enum E_DB_TYPE
{
	DB_TYPE_INT32=0,
	DB_TYPE_INT64,
	DB_TYPE_DOUBLE,
	DB_TYPE_CHAR,
	DB_TYPE_TIME,
	DB_TYPE_STRING,
	DB_TYPE_BOOL,
	DB_TYPE_BLOB,
	DB_TYPE_NULL
};
typedef struct STRUCT_DB_FIELD_INFO
{
	CString strTableName;
	CString strField;
	void* pvData;
	bool bFlag;
	int nDataLen;
	int nSorting;
	E_DB_TYPE eType;
	bool bPk;
	bool bXmlData;
}DB_FIELD_INFO,*PDB_FIELD_INFO;
class __declspec(dllexport) CDBDataObject:public CDataObject
{
private:
	CString m_strClassName;
	map<CString, PDB_FIELD_INFO> *m_pclsTableInfoMap; //table
	list<map<CString,void*>> *m_pRowDataList; //row
	bool HasReflectTableInfoMap();
public:
	CDBDataObject(bool bIsAddToMap);
	~CDBDataObject(void);
	bool ReflectTableInfoMap(int nIndex,CString strTableName,CString strField,E_DB_TYPE eType,void *pvData,bool bXmlData);
	bool SetFieldAllEx(BOOL bDBData=TRUE);
	BOOL UnSetFieldAllEx();
	virtual void ClearReflect();
	virtual void ReflectFieldEx();
	virtual void RegiestFieldEx();
	virtual void RegiestXMLFieldEx();
	virtual bool UnRegiestFieldEx();
 	E_DB_TYPE GetFileType(const CString& strName);
private:
	int m_nCount;
};

