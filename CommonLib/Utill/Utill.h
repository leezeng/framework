#pragma once
#include <string>
using std::string;
using std::wstring;
class __declspec(dllexport) CUtill
{
public:
	CUtill(void);
	~CUtill(void);
	static wstring GetEnvironmentVariableDirectory(const wchar_t* str);
	static wstring ANSIToUnicode(const string& str);
	static string UnicodeToANSI( const wstring& str);
	static wstring UTF8ToUnicode( const string& str );
	static string UnicodeToUTF8(const wstring& str );
};

