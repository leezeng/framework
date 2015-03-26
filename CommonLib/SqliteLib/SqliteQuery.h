#pragma once
#include "DBQueryBase.h"
#include "sqlite3.h"
class __declspec(dllexport) CSqliteQuery:public CDBQueryBase
{
public:
	CSqliteQuery(void);
	CSqliteQuery(sqlite3* pDB,sqlite3_stmt* pVM,bool bEof,int nCols,bool bOwnVM=true);
	virtual ~CSqliteQuery(void);
	virtual int numFields();
	virtual int fieldIndex(const char* szField);
	virtual const char* fieldName(int nCol);
	virtual const char* fieldDeclType(int nCol);
	virtual int fieldDataType(int nCol);
	virtual const char* fieldValue(int nField);
	virtual const char* fieldValue(const char* szField);
	virtual int getIntField(int nField, int nNullValue=0);
	virtual int getIntField(const char* szField, int nNullValue=0);
	virtual long getInt64Field(int nField, int nNullValue = 0);
	virtual double getFloatField(int nField, double fNullValue=0.0);
	virtual double getFloatField(const char* szField, double fNullValue=0.0);
	virtual const char* getStringField(int nField, const char* szNullValue="");
	virtual const char* getStringField(const char* szField, const char* szNullValue="");
	virtual const unsigned char* getBlobField(int nField, int& nLen);
	virtual const unsigned char* getBlobField(const char* szField, int& nLen);
	virtual bool fieldIsNull(int nField);
	virtual bool fieldIsNull(const char* szField);
	virtual bool eof();
	virtual void nextRow();
	virtual void finalize();

private:
	sqlite3* m_pDB;
	sqlite3_stmt* m_pVM;
	bool m_bEof;
	int m_nCols;
	bool m_bOwnVM;
};

