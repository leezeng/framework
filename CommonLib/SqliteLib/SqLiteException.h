#pragma once
class __declspec(dllexport) CSqLiteException
{
public:
	CSqLiteException(int nErrCode,char* chErrMsg,bool bDelMsg=true);
	CSqLiteException(CSqLiteException& sqLiteException);
	virtual ~CSqLiteException(void);
	const int errorCode();
	const char* errorMessage();
	static const char* errorCodeAsString(int nErrCode);
private:
	int m_nErrorCode;
	char* m_chErrorMsg;
};

