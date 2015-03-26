#pragma once
#include "DataObject.h"
class COperation
{
public:
	COperation(void);
	virtual ~COperation(void);

	virtual bool openFile(const wchar_t* filename)=0;
	virtual bool closeFile()=0;
	virtual bool select(CDataObject* pDataObject) = 0;
	virtual bool insert(CDataObject* pDataObject) = 0;
};

COperation::~COperation( void )
{

}

COperation::COperation( void )
{

}
