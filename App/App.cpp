
// App.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "App.h"
#include "AppDlg.h"
#include "Message.h"
#include "NotifierManager.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAppApp

BEGIN_MESSAGE_MAP(CAppApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
	ON_THREAD_MESSAGE(WM_NOTIFY_THREAD_MSG,&CAppApp::OnNotifyThreadMsg)
END_MESSAGE_MAP()


// CAppApp construction

CAppApp::CAppApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CAppApp object

CAppApp theApp;


// CAppApp initialization

#include "NotifierManager.h"
BOOL CAppApp::InitInstance()
{
	CWinApp::InitInstance();


	// Create the shell manager, in case the dialog contains
	// any shell tree view or shell list view controls.
	CShellManager *pShellManager = new CShellManager;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	CAppDlg dlg;
	m_pMainWnd = &dlg;
	CNotifierManager* pManger=CNotifierManager::GetInstance();
	pManger->SetWinApp(this);
	INT_PTR nResponse = dlg.DoModal();
	
	

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Delete the shell manager created above.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}
	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CAppApp::OnNotifyThreadMsg( WPARAM wParam, LPARAM lParam )
{
	P_STHREAD_MESSAGE_PARAM pThreadMsgParam=(P_STHREAD_MESSAGE_PARAM)lParam;
	if (nullptr==pThreadMsgParam)
	{
		return;
	}
	bool bFlag=CNotifierManager::GetInstance()->SetNotifyObjState(pThreadMsgParam->pNotifyObj,E_DOING);
	if (bFlag&&pThreadMsgParam->pNotifyObj)
	{
		pThreadMsgParam->pNotifyObj->ProcessNotify(pThreadMsgParam->nMsgId,pThreadMsgParam->wParam,pThreadMsgParam->lParam);
		bool bFlag=CNotifierManager::GetInstance()->SetNotifyObjState(pThreadMsgParam->pNotifyObj,E_IDLE);
	}
	delete pThreadMsgParam;
	pThreadMsgParam=nullptr;
}

