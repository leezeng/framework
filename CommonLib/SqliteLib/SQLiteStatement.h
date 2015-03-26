#pragma once
#include "sqlite3.h"
#include "SqliteQuery.h"
class __declspec(dllexport) CSQLiteStatement
{
public:
	CSQLiteStatement(void);
	~CSQLiteStatement(void);
	CSQLiteStatement(const CSQLiteStatement& rStatement);
	CSQLiteStatement(sqlite3* pDb,sqlite3_stmt* pVm);
	bool execQuery(CSqliteQuery*& pSqliteQuery);
private:
	sqlite3_stmt* m_pVM;
	sqlite3* m_pDB;
};

