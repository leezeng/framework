#pragma once 
class __declspec(dllexport) CWoker
{
public:
	CWoker(void);
	virtual ~CWoker(void);
	void Execute(DWORD_PTR dwPtr);
};

