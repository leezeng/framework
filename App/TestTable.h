#pragma once
#define TABLE_NAME ("T_TEST")
#include "DBDataObject.h"
class __declspec(dllexport) CTestTable:public CDBDataObject
{
public:
	DECLARE_FACTORYCLASS(CTestTable)
	CTestTable(void);
	~CTestTable(void);
protected:
	virtual bool UnRegiestFieldEx();
	virtual void ReflectDBField();
	virtual void ReflectDBFieldEx();
	virtual void ReflectXMLFieldEx();
	

private:
	int m_nId;
	CString m_strName;
	double m_dValue;
};

