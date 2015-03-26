#include "StdAfx.h"
#include "SqliteDBOperation.h"
#include "DBSQLite.h"
#include "Utill.h"
#include "Defined.h"

CSqliteDBOperation::CSqliteDBOperation(void)
{
	m_pDbBase=new CDBSQLite;
}


CSqliteDBOperation::~CSqliteDBOperation(void)
{
}

bool CSqliteDBOperation::openFile( const wchar_t* filename )
{
	wstring wstrDataDir=CUtill::GetEnvironmentVariableDirectory(APP_DATA);
	wstrDataDir+=_T("\\db\\test.db");
	string strDataDir=CUtill::UnicodeToANSI(wstrDataDir);
	m_pDbBase->open(strDataDir.c_str());

	return false;
}

bool CSqliteDBOperation::closeFile()
{
	return false;
}


bool CSqliteDBOperation::select( CDataObject* dataObject )
{
	return false;
}

bool CSqliteDBOperation::insert( CDataObject* dataObject )
{
	return false;
}

bool CSqliteDBOperation::ExecQuery()
{
	CDBDataObject* pClsData=nullptr;
	return false;
}

bool CSqliteDBOperation::ExecQuery( CDBDataObject* pDbDataObject )
{
	pDbDataObject->ReflectFieldEx();
	TCHAR* pChSql=_T("select * from TestTable");
	CDBQueryBase* pQuery=nullptr;
	pQuery=m_pDbBase->execQuery(CUtill::UnicodeToANSI(pChSql).c_str());
	if (nullptr==pQuery)
	{
		pQuery->finalize();
		return false;
	}
	while(!pQuery->eof())
	{
	  CDBDataObject* pDBObject=(CDBDataObject*)CDBDataObject::GetInstance("CTestTable");
	  pDBObject->ReflectFieldEx();
	  if (pDBObject==NULL)
	  {
		  pQuery->finalize();
		  return false;
	  }
	  for (int i=0;i<pQuery->numFields();i++)
	  {
		  const char* fieldName=pQuery->fieldName(i);
		  string str(fieldName);
		  wstring wstr= CUtill::ANSIToUnicode(str);
		  CString cstr;
		  cstr.Format(_T("%s"),wstr);
		  E_DB_TYPE eType= pDBObject->GetFileType(cstr);
	     
	  }
	  pQuery->nextRow();
	}

	return true;
}


bool CSqliteDBOperation::CompileStatement( const TCHAR* pchSQL )
{
	const char* chSql= CUtill::UnicodeToANSI(pchSQL).c_str();
	if (!m_pDbBase->compileStatement(chSql))
	{
		return false;
	}


	return true;
}
