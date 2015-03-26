#pragma once
#include "DBBase.h"
#include "sqlite3.h"
#include "SQLiteStatement.h"
#include "SqliteQuery.h"
class __declspec(dllexport) CDBSQLite:public CDBBase
{
public:
	CDBSQLite(void);
	~CDBSQLite(void);
	void bindNull( int nParam );
	void statementSQL( const char* szSQL );
	CDBQueryBase* execQuery();
	CDBQueryBase* execQuery(const char* szSQL);
	void bind(int nParam, const char* szValue);
	void bind(int nParam, const INT32 nValue);
	void bind(int nParam, const double dValue);
	void bind(int nParam, const INT64 nValue);
	void bind( int nParam, const unsigned char* blobValue, int nLen );
	INT64 lastRowId();
	int commitBegin();
	bool compileStatement( const char* szSQL);
	void resetStatement();
	void finalizeStatement();
	int commitEnd();
	int execScalar( const char* chSql);
	int rollBack();
	void close();
	void setBusyTimeout( int nMillisecs);
	int execDML( const char* szSQL);
	void open( const char* chConn);
	bool tableExists( const char* szTable );
	int execDML(void);
	void setBusyTimeOut(int nTimeOut);
private:
	sqlite3_stmt* compile(const char* szSql);
private:
	sqlite3* m_pDB;
	int m_nBusyTimeOut;
	const bool m_bIsDelErrMsg;
	CSQLiteStatement* m_pStatemet;
};