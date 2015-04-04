
// AppDlg.h : header file
//

#pragma once


// CAppDlg dialog
class CAppDlg : public CDialogEx
{
// Construction
public:
	CAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_APP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	LRESULT OnNotifyThreadMsg(WPARAM wParam, LPARAM lParam);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	HANDLE m_Event;
	afx_msg void OnBnClickedButton2();
};
