#include "StdAfx.h"
#include "TestTable.h"
#include <stdexcept>
using std::logic_error;
IMPLEMENT_FACTORYCLASS(CTestTable)
CTestTable::CTestTable(void):CDBDataObject(true),m_nId(0),m_strName(_T("")),m_dValue(0)
{
}


CTestTable::~CTestTable(void)
{
}

bool CTestTable::UnRegiestFieldEx()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CTestTable::ClearReflect()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CTestTable::RegiestFieldEx()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CTestTable::RegiestXMLFieldEx()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CTestTable::ReflectFieldEx()
{
	ReflectTableInfoMap(1,TABLE_NAME,_T("id"),DB_TYPE_INT32,&m_nId,false);
	ReflectTableInfoMap(2,TABLE_NAME,_T("name"),DB_TYPE_STRING,&m_strName,false);
	ReflectTableInfoMap(3,TABLE_NAME,_T("value"),DB_TYPE_DOUBLE,&m_dValue,false);
}
