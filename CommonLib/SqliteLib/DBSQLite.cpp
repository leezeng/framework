#include "StdAfx.h"
#include "DBSQLite.h"
#include "SqLiteException.h"
#include <stdexcept>

CDBSQLite::CDBSQLite(void):m_nBusyTimeOut(5000)
							,m_bIsDelErrMsg(false)
							,m_pStatemet(nullptr)
							,m_pDB(nullptr)
{
}


CDBSQLite::~CDBSQLite(void)
{
}

void CDBSQLite::bindNull( int nParam )
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::statementSQL( const char* szSQL )
{
	throw std::logic_error("The method or operation is not implemented.");
}

CDBQueryBase* CDBSQLite::execQuery()
{
	throw std::logic_error("The method or operation is not implemented.");
}

CDBQueryBase* CDBSQLite::execQuery( const char* szSQL )
{
	CSqliteQuery* pSqlQuery=nullptr;
	sqlite3_stmt* pVM = compile(szSQL);
	int nRet=sqlite3_step(pVM);
	if (nRet==SQLITE_DONE)
	{
		int nCols= sqlite3_column_count(pVM);
		pSqlQuery=new CSqliteQuery(m_pDB,pVM,true,nCols,false);
	}
	else if(nRet==SQLITE_ROW)
	{
		int nCols= sqlite3_column_count(pVM);
		pSqlQuery=new CSqliteQuery(m_pDB,pVM,false,nCols,false);
	}
	else
	{
		nRet=sqlite3_reset(pVM);
		const char* pChErr=sqlite3_errmsg(m_pDB);
		throw CSqLiteException(nRet,(char*)pChErr);
	} 
	return pSqlQuery;
}

void CDBSQLite::bind( int nParam, const unsigned char* blobValue, int nLen )
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::bind( int nParam, const char* szValue )
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::bind( int nParam, const INT32 nValue )
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::bind( int nParam, const double dValue )
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::bind( int nParam, const INT64 nValue )
{
	throw std::logic_error("The method or operation is not implemented.");
}

INT64 CDBSQLite::lastRowId()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CDBSQLite::commitBegin()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CDBSQLite::compileStatement( const char* szSQL )
{
	try
	{
		sqlite3_stmt* pVM=compile(szSQL);
		m_pStatemet=new CSQLiteStatement(m_pDB,pVM);
	}
	catch (...)
	{
		return false;
	}
	return true;
}

void CDBSQLite::resetStatement()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::finalizeStatement()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CDBSQLite::commitEnd()
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CDBSQLite::execScalar( const char* chSql )
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CDBSQLite::rollBack()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::close()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::setBusyTimeout( int nMillisecs )
{
	m_nBusyTimeOut=nMillisecs;
}

int CDBSQLite::execDML( const char* szSQL )
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CDBSQLite::execDML( void )
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::open( const char* chConn )
{
	const int ret=sqlite3_open(chConn,&m_pDB);
	if (ret!=SQLITE_OK)
	{
		const char* chErrMsg=sqlite3_errmsg(m_pDB);
		throw CSqLiteException(ret,(char*)(chErrMsg),m_bIsDelErrMsg);
	}
	setBusyTimeout(m_nBusyTimeOut);
}

bool CDBSQLite::tableExists( const char* szTable )
{
	throw std::logic_error("The method or operation is not implemented.");
}

void CDBSQLite::setBusyTimeOut( int nTimeOut )
{
	m_nBusyTimeOut=nTimeOut;
}

sqlite3_stmt* CDBSQLite::compile( const char* szSql )
{
	sqlite3_stmt* pVm;
	const char* szTail=0;
	char* szError=0;
	int nRet=sqlite3_prepare_v2(m_pDB,szSql,-1,&pVm,&szTail);
	if (nRet!=SQLITE_OK)
	{
		throw CSqLiteException(nRet,szError);
	}
	return pVm;
}
