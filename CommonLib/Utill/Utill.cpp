#include "StdAfx.h"
#include "Utill.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CUtill::CUtill(void)
{
}


CUtill::~CUtill(void)
{
}

wstring  CUtill::GetEnvironmentVariableDirectory(const wchar_t* str )
{
	wstring strRoot=_T("");
	TCHAR chRoot[MAX_PATH];
	size_t szRootLen;
	_wgetenv_s(&szRootLen,chRoot,MAX_PATH,str);
	strRoot=chRoot;
	return strRoot;
}
wstring CUtill::ANSIToUnicode( const string& str)
{
	size_t len = str.length();
	int  unicodeLen = ::MultiByteToWideChar( CP_ACP,\
		0,\
		str.c_str(),\
		-1,\
		NULL,\
		0 );  
	wchar_t *  pUnicode;  
	pUnicode = new  wchar_t[unicodeLen+1];  
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_ACP,\
		0,\
		str.c_str(),\
		-1,\
		(LPWSTR)pUnicode,\
		unicodeLen );  
	wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode;
	return  rt;  
}
string CUtill::UnicodeToANSI( const wstring& str )
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_ACP,\
		0,\
		str.c_str(),\
		-1,\
		NULL,\
		0,\
		NULL,\
		NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_ACP,\
		0,\
		str.c_str(),\
		-1,\
		pElementText,\
		iTextLen,\
		NULL,\
		NULL );
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}
wstring CUtill::UTF8ToUnicode( const string& str )
{
	size_t len = str.length();
	int  unicodeLen = ::MultiByteToWideChar( CP_UTF8,\
		0,\
		str.c_str(),\
		-1,\
		NULL,\
		0 );  
	wchar_t *  pUnicode;  
	pUnicode = new  wchar_t[unicodeLen+1];  
	memset(pUnicode,0,(unicodeLen+1)*sizeof(wchar_t));  
	::MultiByteToWideChar( CP_UTF8,\
		0,\
		str.c_str(),\
		-1,\
		(LPWSTR)pUnicode,\
		unicodeLen );  
	wstring  rt;  
	rt = ( wchar_t* )pUnicode;
	delete  pUnicode; 

	return  rt;  
}
string CUtill::UnicodeToUTF8( const wstring& str )
{
	char*     pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte( CP_UTF8,\
		0,\
		str.c_str(),\
		-1,\
		NULL,\
		0,\
		NULL,\
		NULL );
	pElementText = new char[iTextLen + 1];
	memset( ( void* )pElementText, 0, sizeof( char ) * ( iTextLen + 1 ) );
	::WideCharToMultiByte( CP_UTF8,\
		0,\
		str.c_str(),\
		-1,\
		pElementText,\
		iTextLen,\
		NULL,\
		NULL );
	string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}