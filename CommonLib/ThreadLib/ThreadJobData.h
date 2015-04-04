#pragma once
class __declspec(dllexport) CThreadJobData
{
public:
	CThreadJobData(long uDataId=0);
	virtual ~CThreadJobData(void);
	inline long GetDataID()const;
	inline void SetDataID(long uDataId);
private:
	long m_uDataId;
};

