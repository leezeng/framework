#include "StdAfx.h"
#include "Task.h"


CTask::CTask(void)
{
}


CTask::~CTask(void)
{
}

void CTask::DoWork()
{
	AfxOutputDebugString(_T("CTask Test\r\n"));
}
 