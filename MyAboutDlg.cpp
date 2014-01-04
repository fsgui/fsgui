// MyAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CamTest.h"
#include "MyAboutDlg.h"
#include "CamTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAboutDlg dialog


CMyAboutDlg::CMyAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMyAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyAboutDlg)
	DDX_Control(pDX, IDC_EDIT2, m_codeinput);
	DDX_Control(pDX, IDC_EDIT1, m_code);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CMyAboutDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonVerify)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyAboutDlg message handlers

void CMyAboutDlg::OnButton1() 
{
ShellExecute(NULL, NULL, _T("http://xiaohaizhu.taobao.com"), NULL,NULL, SW_SHOWNORMAL);  
}

BOOL CMyAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_code.SetWindowText("您的机器码:"+((CCamTestDlg*)GetParent())->machine_code);
	m_codeinput.SetWindowText("请再次输入注册码，然后点击确定输入");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyAboutDlg::OnButtonVerify() 
{
CString temp;
m_codeinput.GetWindowText(temp);

CString des="";
	::GetCurrentDirectory(100,des.GetBuffer(100));
	des.ReleaseBuffer();
	des+="\\config.ini";//设置当前文件目录

	WritePrivateProfileString("CODE","code2",temp,des);	
	MessageBox("请重新打开程序，如果主窗口标题显示为已注册，则注册成功，祝调车愉快");

}

void CMyAboutDlg::OnButton8() 
{
ShellExecute(NULL, NULL, _T("http://fsgui.github.com"), NULL,NULL, SW_SHOWNORMAL); 	
}
