#pragma once
#include "DBDataObject.h"
#include "Operation.h"
#include "DBBase.h"
#include "DataObject.h"
class __declspec(dllexport)  CDBOperation:public COperation
{
public:
	CDBOperation(void);
	virtual ~CDBOperation(void);
	virtual bool openFile(const wchar_t* filename)=0;
	virtual bool closeFile()=0;
	virtual bool ExecQuery()=0;
	virtual bool CompileStatement(const wchar_t* pchSQL)=0;
	virtual bool ExecQuery(CDBDataObject* pDbDataObject)=0;
	virtual bool select(CDataObject* dataObject)=0;
	virtual bool insert(CDataObject* dataObject)=0;
protected:
	CDBBase* m_pDbBase;
};

