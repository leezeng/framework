#include "StdAfx.h"
#include "SqLiteException.h"
#include "sqlite3.h"

CSqLiteException::CSqLiteException(int nErrCode,char* chErrMsg,bool bDelMsg)
{
	m_chErrorMsg = sqlite3_mprintf("%s[%d]: %s",
		errorCodeAsString(nErrCode),
		nErrCode,
		chErrMsg ? chErrMsg : "");

	if (bDelMsg && chErrMsg)
	{
		sqlite3_free(chErrMsg);
	}
}

CSqLiteException::CSqLiteException( CSqLiteException& sqLiteException )
{
	if (this!=&sqLiteException)
	{
		m_nErrorCode=sqLiteException.m_nErrorCode;
		m_chErrorMsg=sqLiteException.m_chErrorMsg;
	}
}


CSqLiteException::~CSqLiteException(void)
{
	if (m_chErrorMsg)
	{
		sqlite3_free(m_chErrorMsg);
		m_nErrorCode =SQLITE_OK;
	}
}

const int CSqLiteException::errorCode()
{
	return m_nErrorCode;
}

const char* CSqLiteException::errorMessage()
{
	return m_chErrorMsg;
}

const char* CSqLiteException::errorCodeAsString( int nErrCode )
{
	switch (nErrCode)
	{
	case SQLITE_OK          : return "SQLITE_OK";
	case SQLITE_ERROR       : return "SQLITE_ERROR";
	case SQLITE_INTERNAL    : return "SQLITE_INTERNAL";
	case SQLITE_PERM        : return "SQLITE_PERM";
	case SQLITE_ABORT       : return "SQLITE_ABORT";
	case SQLITE_BUSY        : return "SQLITE_BUSY";
	case SQLITE_LOCKED      : return "SQLITE_LOCKED";
	case SQLITE_NOMEM       : return "SQLITE_NOMEM";
	case SQLITE_READONLY    : return "SQLITE_READONLY";
	case SQLITE_INTERRUPT   : return "SQLITE_INTERRUPT";
	case SQLITE_IOERR       : return "SQLITE_IOERR";
	case SQLITE_CORRUPT     : return "SQLITE_CORRUPT";
	case SQLITE_NOTFOUND    : return "SQLITE_NOTFOUND";
	case SQLITE_FULL        : return "SQLITE_FULL";
	case SQLITE_CANTOPEN    : return "SQLITE_CANTOPEN";
	case SQLITE_PROTOCOL    : return "SQLITE_PROTOCOL";
	case SQLITE_EMPTY       : return "SQLITE_EMPTY";
	case SQLITE_SCHEMA      : return "SQLITE_SCHEMA";
	case SQLITE_TOOBIG      : return "SQLITE_TOOBIG";
	case SQLITE_CONSTRAINT  : return "SQLITE_CONSTRAINT";
	case SQLITE_MISMATCH    : return "SQLITE_MISMATCH";
	case SQLITE_MISUSE      : return "SQLITE_MISUSE";
	case SQLITE_NOLFS       : return "SQLITE_NOLFS";
	case SQLITE_AUTH        : return "SQLITE_AUTH";
	case SQLITE_FORMAT      : return "SQLITE_FORMAT";
	case SQLITE_RANGE       : return "SQLITE_RANGE";
	case SQLITE_ROW         : return "SQLITE_ROW";
	case SQLITE_DONE        : return "SQLITE_DONE";
	default: return "UNKNOWN_ERROR";
	}
}
