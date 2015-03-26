#include "StdAfx.h"
#include "SQLiteStatement.h"
#include "SqLiteException.h"

CSQLiteStatement::CSQLiteStatement(void):m_pVM(nullptr),m_pDB(nullptr)
{
}

CSQLiteStatement::CSQLiteStatement( const CSQLiteStatement& rStatement )
{

}

CSQLiteStatement::CSQLiteStatement( sqlite3* pDb,sqlite3_stmt* pVm ):m_pDB(pDb),m_pVM(pVm)
{
}


CSQLiteStatement::~CSQLiteStatement(void)
{
}

bool CSQLiteStatement::execQuery(CSqliteQuery*& pSqliteQuery)
{
	return true;
}
