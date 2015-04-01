#include "StdAfx.h"
#include "NotifierManager.h"


CNotifierManager::CNotifierManager(void):m_pMainApp(nullptr)
										,m_dwTls(TlsAlloc())
{
}


CNotifierManager::~CNotifierManager(void)
{
	TlsFree(m_dwTls);
}

bool CNotifierManager::RegisterMessage( CNotifyObject* pNotifyObj,unsigned int uWndResId,unsigned int uMsgId,E_PRIORITY ePriority )
{
	CAutoLock m_AutoLock(&m_lock);
	if (nullptr==pNotifyObj)
	{
		return false;
	}
	for (int i=0;i<m_arrayTarget.GetCount();i++)
	{
		P_SNOTIFY_TARGET pTarget=m_arrayTarget.GetAt(i);
		if (nullptr!=pTarget)
		{
			if (pTarget->eTagObjectType==E_OBJECT&&pNotifyObj==pTarget->pNotifyObj)
			{
				if (FindMsgInNotifyTargetIndex(*pTarget,uMsgId)<0)
				{
					SNOTIFY_MESSAGE sNotifyMssage;
					sNotifyMssage.uMsgId=uMsgId;
					sNotifyMssage.ePriority=ePriority;
					sNotifyMssage.uThreadId=::GetCurrentThreadId();
					pTarget->arrayMsg.Add(sNotifyMssage);
				}
				return true;
			}
		}
	}

	P_SNOTIFY_TARGET pNotifyTarget=new SNOTIFY_TARGET;
	pNotifyTarget->eTagObjectType=E_OBJECT;
	pNotifyTarget->pNotifyObj=pNotifyObj;
	
	pNotifyTarget->uWndResId=uWndResId;
	pNotifyTarget->nGroupId=pNotifyObj->GetGroupId();

	pNotifyTarget->eNotifyState=E_IDLE;

	SNOTIFY_MESSAGE sNotifyMessage;
	sNotifyMessage.uMsgId=uMsgId;
	sNotifyMessage.ePriority=ePriority;
	sNotifyMessage.uThreadId=::GetCurrentThreadId();
	
	pNotifyTarget->arrayMsg.Add(sNotifyMessage);

	m_arrayTarget.Add(pNotifyTarget);

	return true;
}

bool CNotifierManager::RegisterMessage( CWnd* pWnd,unsigned int uWndResId,unsigned int uMsgId,E_PRIORITY ePriority,int nGroupId)
{
	CAutoLock m_AutoLock(&m_lock);
	if (nullptr==pWnd)
	{
		return false;
	}
	for (int i=0;i<m_arrayTarget.GetCount();i++)
	{
		P_SNOTIFY_TARGET pTarget=m_arrayTarget.GetAt(i);

		if (pTarget->eTagObjectType==E_WND&&pWnd==pTarget->pNotifyWnd)
		{
			if (FindMsgInNotifyTargetIndex(*pTarget,uMsgId)<0)
			{
				SNOTIFY_MESSAGE sNotifyMssage;
				sNotifyMssage.uMsgId=uMsgId;
				sNotifyMssage.ePriority=ePriority;
				sNotifyMssage.uThreadId=::GetCurrentThreadId();
				pTarget->arrayMsg.Add(sNotifyMssage);
			}
			return true;
		}
	}

	P_SNOTIFY_TARGET pNotifyTarget=new SNOTIFY_TARGET;
	pNotifyTarget->eTagObjectType=E_WND;
	pNotifyTarget->pNotifyWnd=pWnd;

	pNotifyTarget->uWndResId=uWndResId;
	pNotifyTarget->nGroupId=nGroupId;
	pNotifyTarget->eNotifyState=E_IDLE;

	SNOTIFY_MESSAGE sNotifyMessage;
	sNotifyMessage.uMsgId=uMsgId;
	sNotifyMessage.ePriority=ePriority;
	sNotifyMessage.uThreadId=::GetCurrentThreadId();

	pNotifyTarget->arrayMsg.Add(sNotifyMessage);

	m_arrayTarget.Add(pNotifyTarget);
	return true;
}

void CNotifierManager::SetWinApp( CWinApp* pTheApp )
{
	m_pMainApp=pTheApp;
}

int CNotifierManager::FindMsgInNotifyTargetIndex( const SNOTIFY_TARGET& sNotifyTarget,unsigned int uMsgId )
{
	for (int i=0;i<sNotifyTarget.arrayMsg.GetCount();i++)
	{
		if (uMsgId==sNotifyTarget.arrayMsg.GetAt(i).uMsgId)
		{
			return i;
		}
	}
	return -1;
}

bool CNotifierManager::UnRegisterMessage( CWnd* pWnd,unsigned int uMsgId )
{
	CAutoLock m_AutoLock(&m_lock);
	if (nullptr==pWnd)
	{
		return false;
	}
	for (int i=0;i<m_arrayTarget.GetCount();i++)
	{
		P_SNOTIFY_TARGET pNotifyTarget=m_arrayTarget.GetAt(i);
		if (pNotifyTarget!=nullptr)
		{
			if (pNotifyTarget->eTagObjectType==E_WND&&pWnd==pNotifyTarget->pNotifyWnd)
			{
				if (uMsgId==0)
				{
					pNotifyTarget->arrayMsg.RemoveAll();
					if (E_DOING!=pNotifyTarget->eNotifyState)
					{
						delete pNotifyTarget;
						pNotifyTarget=NULL;
						m_arrayTarget.RemoveAt(i);
					}
					else
					{
						pNotifyTarget->eNotifyState=E_DEL;
					}
				}
				else
				{
					int index=FindMsgInNotifyTargetIndex(*pNotifyTarget,uMsgId);
					if (index>=0)
					{
						pNotifyTarget->arrayMsg.RemoveAt(index);
					}
				}
				break;
			}
		}
	}
	return true;
}

bool CNotifierManager::UnRegisterMessage( CNotifyObject* pNotifyObject,unsigned int uMsgId )
{
	CAutoLock m_AutoLock(&m_lock);
	if (nullptr==pNotifyObject)
	{
		return false;
	}
	for (int i=0;i<m_arrayTarget.GetCount();i++)
	{
		P_SNOTIFY_TARGET pNotifyTarget=m_arrayTarget.GetAt(i);
		if (pNotifyTarget!=nullptr)
		{
			if (pNotifyTarget->eTagObjectType==E_OBJECT&&pNotifyObject==pNotifyTarget->pNotifyObj)
			{
				if (uMsgId==0)
				{
					pNotifyTarget->arrayMsg.RemoveAll();
					if (E_DOING!=pNotifyTarget->eNotifyState)
					{
						delete pNotifyTarget;
						pNotifyTarget=NULL;
						m_arrayTarget.RemoveAt(i);
					}
					else
					{
						pNotifyTarget->eNotifyState=E_DEL;
					}
				}
				else
				{
					 int index=FindMsgInNotifyTargetIndex(*pNotifyTarget,uMsgId);
					 if (index>=0)
					 {
						 pNotifyTarget->arrayMsg.RemoveAt(index);
					 }
				}
				break;
			}
		}
	}
	return true;
}

LRESULT CNotifierManager::BoardCastMessage( unsigned int uMsgId,WPARAM wParam,LPARAM lParam,bool bIsAsyn,int nGroupId )
{
	CAutoLock m_AutoLock(&m_lock);
	CArray<P_SNOTIFY_TARGET,P_SNOTIFY_TARGET> arrSendTarget;
	for (int i=0;i<m_arrayTarget.GetCount();i++)
	{
		P_SNOTIFY_TARGET pNotifyTarget=m_arrayTarget.GetAt(i);
		if (nullptr==pNotifyTarget)
		{
			m_arrayTarget.RemoveAt(i--);
			continue;
		}
		if (pNotifyTarget->eNotifyState==E_DEL)
		{
			delete pNotifyTarget;
			pNotifyTarget=nullptr;
			m_arrayTarget.RemoveAt(i--);
			continue;
		}
		if (pNotifyTarget->nGroupId!=nGroupId)
		{
			continue;
		}
		int nIndex=FindMsgInNotifyTargetIndex(*pNotifyTarget,uMsgId);
		if (nIndex>=0)
		{
			pNotifyTarget->eNotifyState=E_DOING;
			arrSendTarget.Add(pNotifyTarget);
		}
	}
	unsigned int uCurrentThreadId=::GetCurrentThreadId();
	for (int i=0;i<arrSendTarget.GetCount();i++)
	{
		P_SNOTIFY_TARGET pNotifyTarget=arrSendTarget.GetAt(i);
		if (nullptr==pNotifyTarget)
		{
			continue;
		}
		switch(pNotifyTarget->eNotifyState)
		{
		case E_WND:
			{
				if (!::IsWindow(pNotifyTarget->pNotifyWnd->m_hWnd))
				{
					continue;
				}
				if (bIsAsyn)
				{
					pNotifyTarget->pNotifyWnd->PostMessage(uMsgId,wParam,lParam);
				}
				else
				{
					pNotifyTarget->pNotifyWnd->SendMessage(uMsgId,wParam,lParam);
				}
			}
			break;
		case E_OBJECT:
			{
				int nIndex=FindMsgInNotifyTargetIndex(*pNotifyTarget,uMsgId);
				if (nIndex>=0)
				{
					SNOTIFY_MESSAGE sNotifyMsg=pNotifyTarget->arrayMsg.GetAt(i);
					if (sNotifyMsg.uThreadId==uCurrentThreadId)
					{
						pNotifyTarget->pNotifyObj->ProcessNotify(uMsgId,wParam,lParam);
					}
					else
					{
						ULONG_PTR count=(ULONG_PTR)(TlsGetValue(m_dwTls));
						if (count>0)
						{
							pNotifyTarget->pNotifyObj->ProcessNotify(uMsgId,wParam,lParam);
						}
						else
						{
							P_STHREAD_MESSAGE_PARAM pThreadMsgParam=new STHREAD_MESSAGE_PARAM;
							if (nullptr!=pThreadMsgParam)
							{
								pThreadMsgParam->pNotifyObj=pNotifyTarget->pNotifyObj;
								pThreadMsgParam->nMsgId=uMsgId;
								pThreadMsgParam->wParam=wParam;
								pThreadMsgParam->lParam=lParam;
								if (m_pMainApp&&sNotifyMsg.uThreadId==m_pMainApp->m_nThreadID)//如果当前NotifyMsg的线程ID为.
								{
									if (m_pMainApp->m_pMainWnd)
									{
										bool bRet=false;
										for (int j=0;j<5;j++)
										{
											//if (::PostMessage(m_pMainApp->m_pMainWnd->GetSafeHwnd(), WM_NOTIFY_THREAD_MSG,wParam,(LPARAM)pThreadMsgParam))
											if(::PostThreadMessage(sNotifyMsg.uThreadId,WM_NOTIFY_THREAD_MSG,wParam,(LPARAM)pThreadMsgParam))
											{
												bRet = true;
												break;
											}
										}
										if (false==bRet)
										{
											delete pThreadMsgParam;
											pThreadMsgParam=nullptr;
										}
									}
									else
									{
										delete pThreadMsgParam;
										pThreadMsgParam=nullptr;
									}
								}
								else
								{
									BOOL bRet = ::PostThreadMessage(sNotifyMsg.uThreadId,WM_NOTIFY_THREAD_MSG,wParam,(LPARAM)pThreadMsgParam);
									if (!bRet)
									{
										Sleep(500);
										bRet = ::PostThreadMessage(sNotifyMsg.uThreadId,WM_NOTIFY_THREAD_MSG,wParam,(LPARAM)pThreadMsgParam);
									}
								}
							}
						}
					}
				}
			}
			break;
		}
		pNotifyTarget->eNotifyState = E_IDLE;
	}
	return TRUE;
}

void CNotifierManager::BeginInvoke()
{
	ULONG count=(ULONG_PTR)(TlsGetValue(m_dwTls));
	++count;
	TlsSetValue(m_dwTls,(void*)count);
}

void CNotifierManager::EndInvoke()
{
	ULONG count=(ULONG_PTR)(TlsGetValue(m_dwTls));
	if (count>0)
	{
		--count;
	}
	TlsSetValue(m_dwTls,(void*)count);
}

bool CNotifierManager::SetNotifyObjState( CNotifyObject* pNotifyObject,E_NOTIFY_STATE eState )
{
	if (!pNotifyObject)
	{
		return false;
	}
	bool bFlag=false;
	for (int i=0;i<m_arrayTarget.GetCount();i++)
	{
		P_SNOTIFY_TARGET pNotifyTarget=m_arrayTarget.GetAt(i);
		if (nullptr!=pNotifyTarget)
		{
			if (pNotifyTarget->eTagObjectType==E_OBJECT&&pNotifyObject==pNotifyTarget->pNotifyObj)
			{
				pNotifyTarget->eNotifyState=eState;
				bFlag=true;
				break;
			}
		}
	}
	return bFlag;
}

