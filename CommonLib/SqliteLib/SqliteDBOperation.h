#pragma once
#include "DBOperation.h"
#include "DataObject.h"
#include <string>
using std::string;
using std::wstring;
class __declspec(dllexport) CSqliteDBOperation: public CDBOperation
{
public:
	CSqliteDBOperation(void);
	virtual ~CSqliteDBOperation(void);

	virtual bool select( CDataObject* dataObject );

	virtual bool ExecQuery();
	virtual bool ExecQuery( CDBDataObject* pDbDataObject );

	virtual bool openFile( const wchar_t* filename );

	virtual bool closeFile();

	virtual bool CompileStatement( const wchar_t* pchSQL );

	virtual bool insert( CDataObject* dataObject );

};

