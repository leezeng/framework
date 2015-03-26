#pragma once
#include "DBQueryBase.h"
class __declspec(dllexport) CDBBase
{
public:
	CDBBase(void);
	virtual ~CDBBase(void);
	virtual void open(const char* chConn)=0;
	virtual void close()=0;
	virtual int execScalar(const char* chSql)=0;
	virtual int commitBegin()=0;
	virtual int commitEnd()=0;
	virtual int rollBack()=0;
	virtual bool tableExists(const char* szTable) = 0;
	virtual void bind(int nParam, const char* szValue) = 0;
	virtual void bind(int nParam, const INT32 nValue) = 0;
	virtual void bind(int nParam, const double dValue) = 0;
	virtual void bind(int nParam, const INT64 nValue) = 0;
	virtual void bind(int nParam, const unsigned char* blobValue, int nLen) = 0;
	virtual void bindNull(int nParam) = 0;
	virtual bool compileStatement(const char* szSQL) = 0;
	virtual void resetStatement() = 0;
	virtual void finalizeStatement() = 0;
	virtual void statementSQL(const char* szSQL) = 0;
	virtual int execDML() = 0;
	virtual int execDML(const char* szSQL) = 0;
	virtual INT64 lastRowId() = 0;
	virtual void setBusyTimeout(int nMillisecs) = 0;
	virtual CDBQueryBase* execQuery(const char* szSQL) = 0;
	virtual CDBQueryBase* execQuery() = 0;
};

