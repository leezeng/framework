#pragma once
#define TABLE_NAME _T("T_TEST")
#include "DBDataObject.h"
class __declspec(dllexport) CTestTable:public CDBDataObject
{
public:
	DECLARE_FACTORYCLASS(CTestTable)
	CTestTable(void);
	~CTestTable(void);

	virtual bool UnRegiestFieldEx();

	virtual void ClearReflect();

	virtual void RegiestFieldEx();

	virtual void RegiestXMLFieldEx();

	virtual void ReflectFieldEx();
private:
	int m_nId;
	CString m_strName;
	double m_dValue;
};

