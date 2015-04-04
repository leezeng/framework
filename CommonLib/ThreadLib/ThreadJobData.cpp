#include "StdAfx.h"
#include "ThreadJobData.h"


CThreadJobData::CThreadJobData(long uDataId):m_uDataId(uDataId)
{
}


CThreadJobData::~CThreadJobData(void)
{
}

long CThreadJobData::GetDataID() const
{
	return m_uDataId;
}

void CThreadJobData::SetDataID( long uDataId )
{
	m_uDataId=uDataId;
}
