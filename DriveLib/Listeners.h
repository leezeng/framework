#pragma once
#include "Listener.h"
#include <vector>
using std::vector;
class __declspec(dllexport) CListeners
{
public:
	CListeners(void);
	virtual ~CListeners(void);
private:
	vector<CListener*> m_lstListeners;
};

