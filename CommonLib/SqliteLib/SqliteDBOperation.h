#pragma once
#include "DBOperation.h"
#include "DataObject.h"
#include <string>
#include <vector>
#include <list>
using std::vector;
using std::list;
using std::string;
using std::wstring;
class __declspec(dllexport) CSqliteDBOperation: public CDBOperation
{
public:
	CSqliteDBOperation(void);
	virtual ~CSqliteDBOperation(void);

	virtual bool select( CDataObject* dataObject );

	virtual bool ExecQuery();
	virtual bool ExecQuery(vector<CDBDataObject*>& vecDBobject,const char* chClassName);
	virtual bool openFile( const wchar_t* filename );
	virtual bool ExecQuery(CDBDataObject* pDbDataObject);
	virtual bool closeFile();

	virtual bool CompileStatement( const wchar_t* pchSQL );

	virtual bool insert( CDataObject* dataObject );
	bool ExecteSqlByPrimaryKey( CDBDataObject* pDBObject );
};

