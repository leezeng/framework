#include "StdAfx.h"
#include "SqliteQuery.h"
#include <stdexcept>

CSqliteQuery::CSqliteQuery(void)
{
}

CSqliteQuery::CSqliteQuery( sqlite3* pDB,sqlite3_stmt* pVM,bool bEof,int nCols,bool bOwnVM/*=true*/ ):m_pDB(pDB),
																							m_pVM(pVM),
																							m_bEof(bEof),
																							m_bOwnVM(bOwnVM),
																							m_nCols(nCols)
{

}


CSqliteQuery::~CSqliteQuery(void)
{
}

int CSqliteQuery::numFields()
{
	return m_nCols;
}

int CSqliteQuery::fieldIndex( const char* szField )
{
	throw std::logic_error("The method or operation is not implemented.");
}

const char* CSqliteQuery::fieldName( int nCol )
{
	return sqlite3_column_name(m_pVM,nCol);
}

const char* CSqliteQuery::fieldDeclType( int nCol )
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSqliteQuery::fieldDataType( int nCol )
{
	return sqlite3_column_type(m_pVM,nCol);
}

const char* CSqliteQuery::fieldValue( int nField )
{
	throw std::logic_error("The method or operation is not implemented.");
}

const char* CSqliteQuery::fieldValue( const char* szField )
{
	throw std::logic_error("The method or operation is not implemented.");
}

int CSqliteQuery::getIntField( int nField, int nNullValue/*=0*/ )
{
	return sqlite3_column_int(m_pVM,nField);
}

int CSqliteQuery::getIntField( const char* szField, int nNullValue/*=0*/ )
{
	throw std::logic_error("The method or operation is not implemented.");
}

long CSqliteQuery::getInt64Field( int nField, int nNullValue /*= 0*/ )
{ 
	return (long)sqlite3_column_int64(m_pVM,nField);
}

double CSqliteQuery::getFloatField( int nField, double fNullValue/*=0.0*/ )
{
	return sqlite3_column_double(m_pVM,nField);
}

double CSqliteQuery::getFloatField( const char* szField, double fNullValue/*=0.0*/ )
{
	throw std::logic_error("The method or operation is not implemented.");
}

const char* CSqliteQuery::getStringField( int nField, const char* szNullValue/*=""*/ )
{
	return (const char*)sqlite3_column_text(m_pVM,nField);
}

const char* CSqliteQuery::getStringField( const char* szField, const char* szNullValue/*=""*/ )
{
	throw std::logic_error("The method or operation is not implemented.");
}

const unsigned char* CSqliteQuery::getBlobField( int nField, int& nLen )
{
	throw std::logic_error("The method or operation is not implemented.");
}

const unsigned char* CSqliteQuery::getBlobField( const char* szField, int& nLen )
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CSqliteQuery::fieldIsNull( int nField )
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CSqliteQuery::fieldIsNull( const char* szField )
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool CSqliteQuery::eof()
{
	return m_bEof;
}

void CSqliteQuery::nextRow()
{
	int nRet=sqlite3_step(m_pVM);
	if (nRet==SQLITE_DONE)
	{
		m_bEof=true;
	}
	else if(nRet==SQLITE_ROW)
	{
		m_bEof=false;
	}
	else
	{
		nRet=sqlite3_finalize(m_pVM);
	}
}

void CSqliteQuery::finalize()
{
	sqlite3_finalize(m_pVM);
}

void CSqliteQuery::GetValue( int nIndex,E_DB_TYPE eType,void* pVoid)
{
	if (nullptr==pVoid)
	{
		return;
	}
	int nType=fieldDataType(nIndex);
	switch (nType)
	{
	case SQLITE_INTEGER:
		{
			switch(eType)
			{
			case DB_TYPE_INT32:
				*((INT32*)(pVoid))=getIntField(nIndex);
				break;
			case DB_TYPE_INT64:
				*((INT64*)(pVoid))=getIntField(nIndex);
				break;
			}
		}
	case SQLITE_FLOAT:
		{
			switch(eType)
			{
			case  DB_TYPE_DOUBLE:
				*((double*)(pVoid))=getFloatField(nIndex);
				break;
			}
		}
		break;
	case SQLITE_BLOB:
		{
			switch(eType)
			{
			case DB_TYPE_BLOB:
				break;
			}
		}
	case SQLITE_TEXT:
		{
			switch(eType)
			{
			case DB_TYPE_CHAR:
				break;
			case DB_TYPE_STRING:
				*((CString*)(pVoid))=CString(CUtill::ANSIToUnicode(getStringField(nIndex)).c_str());
				break;
			}
		}
		break;
	}
}

