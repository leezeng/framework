#include "StdAfx.h"
#include "Woker.h"
#include "Task.h"

CWoker::CWoker(void)
{
}


CWoker::~CWoker(void)
{
}

void CWoker::Execute( DWORD_PTR dwPtr )
{
	CTask* pTask=(CTask*)dwPtr;
	if (NULL!=pTask)
	{
		pTask->DoWork();
	}
}
