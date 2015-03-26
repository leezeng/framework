#pragma once
class __declspec(dllexport) CTask
{
public:
	CTask(void);
	virtual void DoWork();
	~CTask(void);
};

