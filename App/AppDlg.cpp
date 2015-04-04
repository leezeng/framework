
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
	ON_BN_CLICKED(IDC_BUTTON2, &CAppDlg::OnBnClickedButton2)
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
		//contorll.InitMessageMap();
		CNotifierManager::GetInstance()->BoardCastMessage(WM_TEST_MSG,NULL,NULL,false,0);
	    WaitForSingleObject(pThreadPool->m_Event,100000);
	}
	return FALSE;
}

static unsigned __stdcall ThreadFunc2( void* param )
{
	CTestContorller contorll;
	CAppDlg* pThreadPool=(CAppDlg*)(param);
	if (NULL!=pThreadPool)
	{
		contorll.InitMessageMap();
		MSG msg;
		while (true)
		{
			GetMessage(&msg,NULL,0,0);
			switch(msg.message)
			{
			case WM_TEST_MSG:
				{
					AfxOutputDebugString("test msg");
				}
			case WM_NOTIFY_THREAD_MSG:
				{
					AfxOutputDebugString("notify thread msg");
				}
				break;
			}
		}
		//CNotifierManager::GetInstance()->BoardCastMessage(WM_TEST_MSG,NULL,NULL,false,0);
		//WaitForSingleObject(pThreadPool->m_Event,100000);
	}
	return FALSE;
}

void CAppDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	unsigned int nThreadId;
	HANDLE hHandle2=(HANDLE)_beginthreadex(NULL,0,ThreadFunc2,(void*)this,0,&nThreadId);
	Sleep(1000);
	HANDLE hHandle=(HANDLE)_beginthreadex(NULL,0,ThreadFunc,(void*)this,0,&nThreadId);
}
class __declspec(dllexport) CJob
{
public:
	CJob(unsigned int uMsgId):m_uMsgId(uMsgId){}
	virtual ~CJob(){}
private:
	unsigned int m_uMsgId;
};
#include "Queue.h"
#include "ThreadJobData.h"
void CAppDlg::OnBnClickedButton2()
{
	CQueue<CThreadJobData*>* pQueue=new CQueue<CThreadJobData*>;
	pQueue->enqueue(new CThreadJobData(WM_JOB_1_MSG));
	pQueue->enqueue(new CThreadJobData(WM_JOB_2_MSG));
	pQueue->enqueue(new CThreadJobData(WM_JOB_3_MSG));
	pQueue->enqueue(new CThreadJobData(WM_JOB_4_MSG));
	pQueue->enqueue(new CThreadJobData(WM_JOB_5_MSG));
	//pQueue->enqueue(new CJob(2));
	//pQueue->enqueue(new CJob(3));
	//pQueue->enqueue(new CJob(4));
	//pQueue->enqueue(new CJob(5));
	//int nLength=pQueue->length();
	//pQueue->clear();
	//CJob* pJobRef=nullptr;/*
	//pQueue->dequeue(pJobRef);
	//pQueue->dequeue(pJobRef);
	//pQueue->dequeue(pJobRef);*/
	//int nLength2=pQueue->length();
	/*pQueue->dequeue(pJobRef);
	pQueue->dequeue(pJobRef);
	pQueue->dequeue(pJobRef);*//*
	int nLength3=pQueue->length();*/
	// TODO: Add your control notification handler code here
}
