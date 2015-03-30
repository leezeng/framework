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

bool CSqliteDBOperation::ExecQuery( vector<CDBDataObject*>& vecDBobject,const char* pChClassName)
{
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
	  CDBDataObject* pDBObject=(CDBDataObject*)CDBDataObject::GetInstance(pChClassName);
	  pDBObject->SetFieldAllEx(true);
	  if (pDBObject==NULL)
	  {
		  pQuery->finalize();
		  return false;
	  }
	  for (int i=0;i<pQuery->numFields();i++)
	  {
		  const char* fieldName=pQuery->fieldName(i);
		  E_DB_TYPE eType= pDBObject->GetFiledType(fieldName);
		  //获得在ReflectFieldEx的时候绑定的类成员指针void*。
		  void* pVoid=pDBObject->GetFiledValue(fieldName);
		  //从数据库查询到值，并将值给void*
		  pQuery->GetValue(i,eType,pVoid);
	  }
	  vecDBobject.push_back(pDBObject);
	  pDBObject->UnSetFieldAllEx();
	  pQuery->nextRow();
	}
	pQuery->finalize();
	return true;
}

bool CSqliteDBOperation::ExecQuery( CDBDataObject* pDbDataObject )
{
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

bool CSqliteDBOperation::ExecteSqlByPrimaryKey( CDBDataObject* pDBObject )
{
	if (nullptr==pDBObject)
	{
		return false;
	}
	pDBObject->SetFieldAllEx(true);
	list<string> lstStrSql;
	pDBObject->GetSqlStr(lstStrSql,this);
	return false;
}
