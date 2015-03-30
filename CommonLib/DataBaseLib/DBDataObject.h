#pragma once
#include "DBDefined.h"
#include "DataObject.h"
#include <list>
#include <string>
#include <map>
class CDBOperation;
using std::map;
using std::string;
using std::list;
using std::pair;

typedef struct STRUCT_DB_FIELD_INFO
{
	string strTableName;
	string strField;
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
	bool HasReflectMap();
	void DeleteReflectMap();
	void GetConditionList(map<string,string>& pPkMap);

	/*PDB_FIELD_INFO GetBeginDBFiledInfo();
	PDB_FIELD_INFO GetNextDBFiledInfo();
	PDB_FIELD_INFO GetFirstDBFiledInfo();*/

public:
	const char* GetClassName();
	CDBDataObject(bool bIsAddToMap);
	~CDBDataObject(void);
	bool ReflectTableInfoMap(int nIndex,string strTableName,string strField,E_DB_TYPE eType,void *pvData,bool bIsPk,bool bXmlData);
	/************************************************************************/
	/* 支持XML和DB                                                                     */
	/************************************************************************/
	bool SetFieldAllEx(bool bIsDbData);
	void UnSetFieldAllEx();
	E_DB_TYPE GetFiledType(const string& strName);
	void* GetFiledValue(const string& strName);

	void GetSqlStr(list<string>& lstStrSql,CDBOperation* pOperation);
	void SetOperatorType(E_OPERATOR_TYPE eOperType);

	//受保护继承，不能在外面提供直接的访问，只能通过SetFiledAllEx。UnSetFileAllEx。访问。只能在继承类里面操作。
protected:
	virtual void ReflectDBField();
	virtual void ReflectDBFieldEx();
	virtual bool UnReflectDBFieldEx();
	virtual void ReflectXMLField();
	void ClearReflect();
protected:
	string m_strClassName;
private:
	map<string, PDB_FIELD_INFO> *m_pclsTableInfoMap; //table
	list<map<string,void*>> *m_pRowDataList; //row
	int m_nCount;
	E_OPERATOR_TYPE m_eOperType;
};

