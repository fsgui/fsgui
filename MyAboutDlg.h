#if !defined(AFX_MYABOUTDLG_H__4AD3295D_FBE9_409B_A93F_6295FD873AB3__INCLUDED_)
#define AFX_MYABOUTDLG_H__4AD3295D_FBE9_409B_A93F_6295FD873AB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyAboutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyAboutDlg dialog

class CMyAboutDlg : public CDialog
{
// Construction
public:
	CMyAboutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMyAboutDlg)
	enum { IDD = IDD_DIALOG2 };
	CEdit	m_codeinput;
	CEdit	m_code;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyAboutDlg)
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonVerify();
	afx_msg void OnButton8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYABOUTDLG_H__4AD3295D_FBE9_409B_A93F_6295FD873AB3__INCLUDED_)
