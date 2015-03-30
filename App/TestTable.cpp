#include "StdAfx.h"
#include "TestTable.h"
#include <stdexcept>
using std::logic_error;
IMPLEMENT_FACTORYCLASS(CTestTable)
CTestTable::CTestTable(void):CDBDataObject(true),m_nId(0),m_strName(_T("")),m_dValue(0)
{
	m_strClassName="CTestTable";
}


CTestTable::~CTestTable(void)
{
}

bool CTestTable::UnRegiestFieldEx()
{
	throw std::logic_error("The method or operation is not implemented.");
}

 

void CTestTable::ReflectDBField()
{
	 
}

void CTestTable::ReflectXMLFieldEx()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CTestTable::ReflectDBFieldEx()
{
	ReflectTableInfoMap(1,TABLE_NAME,"id",DB_TYPE_INT32,&m_nId,true,false);
	ReflectTableInfoMap(2,TABLE_NAME,"name",DB_TYPE_STRING,&m_strName,false,false);
	ReflectTableInfoMap(3,TABLE_NAME,"value",DB_TYPE_DOUBLE,&m_dValue,true,false);
}

 
