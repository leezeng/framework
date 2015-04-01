
// AppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "App.h"
#include "AppDlg.h"
#include "afxdialogex.h"
#include "Message.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAppDlg dialog




CAppDlg::CAppDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAppDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Event=CreateEvent(NULL,FALSE,FALSE,NULL);
}

void CAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAppDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAppDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CAppDlg::OnBnClickedButton1)
	ON_MESSAGE(WM_NOTIFY_THREAD_MSG,&CAppDlg::OnNotifyThreadMsg)
END_MESSAGE_MAP()


#include "Message.h"
#include "NotifierManager.h"
#include "NotifyObject.h"
#include "TestContorller.h"
LRESULT CAppDlg::OnNotifyThreadMsg( WPARAM wParam, LPARAM lParam )
{
	P_STHREAD_MESSAGE_PARAM pThreadMsgParam=(P_STHREAD_MESSAGE_PARAM)lParam;
	if (nullptr==pThreadMsgParam)
	{
		return FALSE;
	}
	bool bFlag=CNotifierManager::GetInstance()->SetNotifyObjState(pThreadMsgParam->pNotifyObj,E_DOING);
	if (bFlag&&pThreadMsgParam->pNotifyObj)
	{
		pThreadMsgParam->pNotifyObj->ProcessNotify(pThreadMsgParam->nMsgId,pThreadMsgParam->wParam,pThreadMsgParam->lParam);
		bool bFlag=CNotifierManager::GetInstance()->SetNotifyObjState(pThreadMsgParam->pNotifyObj,E_IDLE);
	}
	delete pThreadMsgParam;
	pThreadMsgParam=nullptr;
	return TRUE;
}


// CAppDlg message handlers

BOOL CAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAppDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include "DBOperation.h"
#include "DBSqlite.h"
#include "SqliteDBOperation.h"
#include "TestTable.h"
#include <algorithm>
void CAppDlg::OnBnClickedOk()
{
	CSqliteDBOperation sqlOperation;
	sqlOperation.openFile(_T("test.db"));
	
	vector<CDBDataObject*> vecObject;
	sqlOperation.ExecQuery(vecObject,"CTestTable");
	std::for_each(vecObject.begin(),vecObject.end(),[](CDBDataObject*& p){
		delete p;
		p=nullptr;
	});
	vecObject.clear();
	
	CTestTable testTable;
	testTable.SetOperatorType(DB_SELECT);
	sqlOperation.ExecteSqlByPrimaryKey(&testTable);

}

static unsigned __stdcall ThreadFunc( void* param )
{
	CAppDlg* pThreadPool=(CAppDlg*)(param);
	if (NULL!=pThreadPool)
	{
		CNotifierManager::GetInstance()->BoardCastMessage(WM_TEST_MSG,NULL,NULL,false,0);
	    WaitForSingleObject(pThreadPool->m_Event,100000);
	}
	return FALSE;
}
CTestContorller contorll;
void CAppDlg::OnBnClickedButton1()
{
		
	contorll.InitMessageMap();

	//CNotifierManager::GetInstance()->BoardCastMessage(WM_TEST_MSG,NULL,NULL,false,0);
	// TODO: Add your control notification handler code here
	unsigned int nThreadId;
	//CreateThread(NULL,0,)
	HANDLE hHandle=(HANDLE)_beginthreadex(NULL,0,ThreadFunc,(void*)this,0,&nThreadId);

}
