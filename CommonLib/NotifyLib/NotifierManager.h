#pragma once
#include "AutoLock.h"
#include "Message.h"
#include "NotifyObject.h"
enum E_PRIORITY {
	E_LOWEST,
	E_LOW,
	E_NORMAL,
	E_HIGH,
	E_HIGHEST
};
enum E_TARGET
{
	E_OBJECT,
	E_WND,
	E_NULL
};
enum E_NOTIFY_STATE
{
	E_DOING,
	E_IDLE,
	E_DEL
};
typedef struct STRUCT_NOTIFY_MESSAGE 
{
	unsigned int uMsgId;
	unsigned int uThreadId;
	E_PRIORITY ePriority;
}SNOTIFY_MESSAGE,*P_SNOTIFY_MESSAGE;
typedef struct STRUCT_NOTIFY_TARGET
{
	E_TARGET eTagObjectType;
	union
	{
		CNotifyObject* pNotifyObj;
		CWnd* pNotifyWnd;
	};
	unsigned int uWndResId;
	unsigned int nGroupId;
	CArray<SNOTIFY_MESSAGE,SNOTIFY_MESSAGE> arrayMsg;
	E_NOTIFY_STATE eNotifyState;
}SNOTIFY_TARGET,*P_SNOTIFY_TARGET;

typedef struct STRUCT_THREAD_MESSAGE_PARAM{
	CNotifyObject* pNotifyObj;
	unsigned int nMsgId;
	WPARAM wParam;
	LPARAM lParam;
}STHREAD_MESSAGE_PARAM,*P_STHREAD_MESSAGE_PARAM;

class __declspec(dllexport) CNotifierManager
{
private:
	CNotifierManager(void);
	virtual ~CNotifierManager(void);
	CNotifierManager(CNotifierManager const&){};  
	CNotifierManager& operator=(CNotifierManager const&){return *this;};
	int FindMsgInNotifyTargetIndex(const SNOTIFY_TARGET& sNotifyTarget,unsigned int uMsgId);
public:
	void SetWinApp(CWinApp* pTheApp);
	bool RegisterMessage(CNotifyObject* pNotifyObj,unsigned int uWndResId,unsigned int uMsgId,E_PRIORITY ePriority);
	bool RegisterMessage(CWnd* pWnd,unsigned int uWndResId,unsigned int uMsgId,E_PRIORITY ePriority,int nGroupId);
	bool UnRegisterMessage(CNotifyObject* pNotifyObject,unsigned int uMsgId);
	bool UnRegisterMessage(CWnd* pWnd,unsigned int uMsgId);
	LRESULT BoardCastMessage(unsigned int uMsgId,WPARAM wParam,LPARAM lParam,bool bIsAsyn,int nGroupId);
	void BeginInvoke();
	void EndInvoke();
	bool SetNotifyObjState(CNotifyObject* pNotifyObject,E_NOTIFY_STATE eState);
	static CNotifierManager* GetInstance()
	{
		static CNotifierManager m_NotifyManager;
		return &m_NotifyManager;
	};
private:
	CWinApp* m_pMainApp;
	CArray<P_SNOTIFY_TARGET,P_SNOTIFY_TARGET> m_arrayTarget;
	DWORD m_dwTls;
	CAutoLock::CLock m_lock; 
};

