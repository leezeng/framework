#pragma once
class __declspec(dllexport) CListener
{
public:
	CListener(void);
	virtual ~CListener(void);
	virtual bool Receive();
};

