#pragma once
#include <map>
#include <Windows.h>
using std::pair;
using std::map;
class CNotifyObject;
typedef LRESULT (CNotifyObject::*P_NOTIFY_MSG_FUNC)(WPARAM,LPARAM);
class __declspec(dllexport) CNotifyObject
{
public:
	CNotifyObject(void);
	virtual ~CNotifyObject(void);
	void MappingMessageFunction(unsigned int uMsgId,P_NOTIFY_MSG_FUNC pMsgFunc,void* pThisObj=nullptr);
	LRESULT ProcessNotify(unsigned int uMsgId,WPARAM wParam,LPARAM lParam);
	int GetGroupId();
	void SetGroupId(int nGroupId);
protected:
	virtual void InitMessageMap(void)=0;
private:
	map<unsigned int,P_NOTIFY_MSG_FUNC> m_mapMsgFunc;
	void* m_pThisObj;
	int m_nNotifyGroupId;
};

