// CamTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CamTest.h"
#include "CamTestDlg.h"
#include "State.h"
#include "md5.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamTestDlg dialog

CCamTestDlg::CCamTestDlg(CWnd* pParent /*=NULL*/)
: CDialog(CCamTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamTestDlg)
	m_yuzhi = 128;
	m_bianmaqi = 0;
	m_dianji = 0;
	m_bianmaqi2 = 0;
	m_z1 = 0;
	m_z2 = 0;
	m_z3 = 0;
	m_z4 = 0;
	m_send_dianji = 0;
	m_send_duoji = 0;
	m_send_z1 = 0;
	m_send_z2 = 0;
	m_send_z3 = 0;
	m_send_z4 = 0;
	m_dianji2 = 0;
	m_z5 = 0;
	m_sensor1 = 0;
	m_sensor2 = 0;
	m_sensor3 = 0;
	m_sensor4 = 0;
	m_sensor5 = 0;
	m_send_z5 = 0;
	m_send_z6 = 0;
	m_y_min = 0;
	m_y_max = 0;
	m_x_max = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCamTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamTestDlg)
	DDX_Text(pDX, IDC_EDIT_YUZHI, m_yuzhi);
	DDX_Text(pDX, IDC_EDIT_BIANMAQI, m_bianmaqi);
	DDX_Text(pDX, IDC_EDIT_DIANJI, m_dianji);
	DDX_Text(pDX, IDC_EDIT_BIANMAQI2, m_bianmaqi2);
	DDX_Text(pDX, IDC_EDIT_Z1, m_z1);
	DDX_Text(pDX, IDC_EDIT_Z2, m_z2);
	DDX_Text(pDX, IDC_EDIT_Z3, m_z3);
	DDX_Text(pDX, IDC_EDIT_Z4, m_z4);
	DDX_Text(pDX, IDC_SEND_DIANJI, m_send_dianji);
	DDX_Text(pDX, IDC_SEND_DUOJI, m_send_duoji);
	DDX_Text(pDX, IDC_SEND_Z1, m_send_z1);
	DDX_Text(pDX, IDC_SEND_Z2, m_send_z2);
	DDX_Text(pDX, IDC_SEND_Z3, m_send_z3);
	DDX_Text(pDX, IDC_SEND_Z4, m_send_z4);
	DDX_Text(pDX, IDC_EDIT_DIANJI2, m_dianji2);
	DDX_Text(pDX, IDC_EDIT_Z5, m_z5);
	DDX_Text(pDX, IDC_EDIT_SENSOR1, m_sensor1);
	DDX_Text(pDX, IDC_EDIT_SENSOR2, m_sensor2);
	DDX_Text(pDX, IDC_EDIT_SENSOR3, m_sensor3);
	DDX_Text(pDX, IDC_EDIT_SENSOR4, m_sensor4);
	DDX_Text(pDX, IDC_EDIT_SENSOR5, m_sensor5);
	DDX_Text(pDX, IDC_SEND_Z5, m_send_z5);
	DDX_Text(pDX, IDC_SEND_Z6, m_send_z6);
	DDX_Control(pDX, IDC_NTGRAPHCTRL1, m_graph_main);
	DDX_Text(pDX, IDC_EDIT_Y_MIN, m_y_min);
	DDX_Text(pDX, IDC_EDIT_Y_MAX, m_y_max);
	DDX_Text(pDX, IDC_EDIT_X_MAX, m_x_max);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCamTestDlg, CDialog)
//{{AFX_MSG_MAP(CCamTestDlg)
ON_WM_SYSCOMMAND()
ON_MESSAGE(WM_COMM_RXCHAR, OnComm)  //这是我自己加的
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
ON_BN_CLICKED(IDC_NEW, OnNew)
ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
ON_BN_CLICKED(IDC_ABOUT, OnAbout)
ON_BN_CLICKED(IDC_OPEN, OnOpen)
ON_BN_CLICKED(IDC_CLOSESERIAL, OnCloseserial)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_DRAW, OnButtonChangeDraw)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_DRAW, OnButtonClearDraw)
	ON_BN_CLICKED(IDC_BUTTON_STOP_SERIAL, OnButtonStopSerial)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, OnButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, OnButtonRight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamTestDlg message handlers

BOOL CCamTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CComboBox *combo;
	combo=(CComboBox *)GetDlgItem(IDC_COM);
	combo->AddString("COM1");
	combo->AddString("COM2");
	combo->AddString("COM3");
	combo->AddString("COM4");
	combo->AddString("COM5");
	combo->AddString("COM6");
	combo->AddString("COM7");
	combo->AddString("COM8");
	combo->AddString("COM9");
	combo->SetCurSel(0);
	
	combo=(CComboBox *)GetDlgItem(IDC_BAUD);
	combo->AddString("9600");
	combo->AddString("19200");
	combo->AddString("38400");
	combo->AddString("43000");
	combo->AddString("56000");
	combo->AddString("57600");
	combo->AddString("115200");
	combo->SetCurSel(0);
	//配置文件还会再修改一次值
	//disable left and right button
	GetDlgItem(IDC_BUTTON_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_CLOSESERIAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_SERIAL)->EnableWindow(FALSE);
	//第二个窗口
	flag_serial=0;
	pDlg=new CState();
	pDlg->Create(IDD_DIALOG1,this);
	rx=0;
	//从配置文件载入值
	loadconfig();
	UpdateData(FALSE); //配置文件修改了变量
	//md5检测
	md5_right=md5check();//加密
	if(md5_right==0)
	{AfxGetMainWnd()-> SetWindowText( "FS智能车调试工具（电磁试用版）——海猪的淘宝店http://xiaohaizhu.taobao.com"); }
	
	//graph initial
	m_graph_main.ClearGraph();
	m_graph_main.SetElementLinetype(0);
	m_graph_main.SetElementWidth(2);
	m_graph_main.SetElementLineColor(RGB(255,48,48)); //0
	m_graph_main.AddElement();//
	m_graph_main.SetElementWidth(2);
	m_graph_main.SetElementLineColor(RGB(255,127,0));
	m_graph_main.AddElement();//
	m_graph_main.SetElementWidth(2);
	m_graph_main.SetElementLineColor(RGB(138,43,226));
	m_graph_main.AddElement();//
	m_graph_main.SetElementWidth(2);
	m_graph_main.SetElementLineColor(RGB(255,193,193));
	m_graph_main.AddElement();//
	m_graph_main.SetElementWidth(2);
	m_graph_main.SetElementLineColor(RGB(139,0,139));
	m_graph_main.AddElement();//
	m_graph_main.SetElementWidth(2);
	m_graph_main.SetElementLineColor(RGB(144,238,144));
	m_graph_main.AddElement();//
	m_graph_main.SetElementWidth(2);
	m_graph_main.SetElementLineColor(RGB(46,139,87));

	
	m_graph_main.SetRange(rx/m_x_max*m_x_max,rx/m_x_max*m_x_max+m_x_max,m_y_min,m_y_max);  //

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCamTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCamTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCamTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCamTestDlg::OnOK() 
{
}




LONG CCamTestDlg::OnComm(WPARAM ch, LPARAM port)
{
	
	static CString str="";
	static unsigned char count=0;
	static unsigned int i=0;
	static CString temp="";
	CString temp2;// string.format 不能用static,所以用这个中转一下
	
	//static int rx=0;
	static CString strrx;
	
	//收到一个char显示一个char
	CString strchar;
	strchar.Format("%02X",ch);
	GetDlgItem(IDC_STATIC_RECEIVE_CHAR)->SetWindowText(strchar);
	
	if (rerecive==1)//如果点了关闭按钮，此标记变量会置1。所有一切会重新开始。 点击打开串口，变量又置0
	{str="";
	count=0;
	i=0;
	rerecive=0;
	rx=0;
	temp="";}
	
	if ((ch==0xaa) && (count==0))
	{
		count++;
		GetDlgItem(IDC_STATIC_VER_DATA)->SetWindowText("正在接收验证位:");
	}
	if ((ch==0xbb) && (count==1)) {count++;}
	if ((ch==0xcc) && (count==2)) 
	{
		count++;
		temp="";
		return 0;
	}  //分隔符 0xAA, 0xBB, 0xCC
	if (count==3)
	{
		GetDlgItem(IDC_STATIC_VER_DATA)->SetWindowText("正在接收数据位:");
		
		if (i<23)
		{   temp2=temp;
		canshu_data[i]=ch;
		temp.Format("%s%-03X",temp2,ch);  //-左对齐
		i++; 
		} 
		if (i==23)   //接受完参数
		{	
			rx+=1;
			strrx.Format("%d%s",rx,"轮");
			GetDlgItem(IDC_STATIC_RX)->SetWindowText(strrx);
			if(canshushow==1)//在文本框显示接受数据，防止刷屏卡住 
			{
				str="新数据:\r\naa bb cc "+temp+"\r\n"+str;
				str=str.Mid(0,1700);
				GetDlgItem(IDC_EDIT1)->SetWindowText(str);
			}
			shishicanshu();
			i=0;   //计数清零
			count=0;  //标志清零
		}
		
	}
	
	
	
	return 0;
	
}





void CCamTestDlg::OnButton4()    
{
	PostQuitMessage(0);
	
	
}


void CCamTestDlg::shishicanshu()
{	
	m_dianji=canshu_data[0]*256+canshu_data[1];
	m_bianmaqi=canshu_data[2]*256+canshu_data[3];
	m_dianji2=canshu_data[4]*256+canshu_data[5];    //其实这是舵机
	m_bianmaqi2=canshu_data[6]*256+canshu_data[7];	//其实这是舵机期望值
	m_sensor1=canshu_data[8]*256+canshu_data[9];
	m_sensor2=canshu_data[10]*256+canshu_data[11];
	m_sensor3=canshu_data[12]*256+canshu_data[13];
	m_sensor4=canshu_data[14]*256+canshu_data[15];
	m_sensor5=canshu_data[16]*256+canshu_data[17];
	m_z1=canshu_data[18];
	m_z2=canshu_data[19];
	m_z3=canshu_data[20];
	m_z4=canshu_data[21];
	m_z5=canshu_data[22];
	UpdateData(FALSE);//呈现在编辑框中
	//ntgraph绘图


	m_graph_main.SetRange(rx/m_x_max*m_x_max,rx/m_x_max*m_x_max+m_x_max,m_y_min,m_y_max);  //调整坐标范围

	
	if(IsDlgButtonChecked(IDC_CHECK_0))
	m_graph_main.PlotXY(rx,m_dianji,0);//绘图
	if(IsDlgButtonChecked(IDC_CHECK_1))
	m_graph_main.PlotXY(rx,m_bianmaqi,1);//绘图
	if(md5_right==1){
	if(IsDlgButtonChecked(IDC_CHECK_2))
	m_graph_main.PlotXY(rx,m_dianji2,2);//绘图
	if(IsDlgButtonChecked(IDC_CHECK_3))
	m_graph_main.PlotXY(rx,m_bianmaqi2,3);//绘图
	if(IsDlgButtonChecked(IDC_CHECK_4))
	m_graph_main.PlotXY(rx,m_z1,4);//绘图
	if(IsDlgButtonChecked(IDC_CHECK_5))
	m_graph_main.PlotXY(rx,m_z2,5);//绘图
	
	}
	
	
	//drawbianmaqi(m_bianmaqi);//显示速度曲线！
	if(md5_right==1){

		pDlg->transfer_value(rx,canshu_data);	  
		pDlg->draw_sensor();	          
		
		pDlg->draw_custom1();	  
		pDlg->draw_custom2();	       
	}

}


void CCamTestDlg::OnNew() 
{
	pDlg->ShowWindow(SW_SHOW);	
}

void CCamTestDlg::OnButtonSend() 
{
	unsigned char buf[20];
	
	CString str,temp;
	if(!flag_serial) //检查串口是否打开
	{
		AfxMessageBox("串口没有打开");
		return; 
	}
	else{
		UpdateData(TRUE); //读入编辑框中的数据	
		buf[0]=0xaa;
		buf[1]=0xbb;
		buf[2]=0xcc;
		buf[3]=m_send_dianji/256;
		buf[4]=m_send_dianji%256;
		buf[5]=m_send_duoji/256;
		buf[6]=m_send_duoji%256;
		buf[7]=m_send_z1/256;
		buf[8]=m_send_z1%256;
		buf[9]=m_send_z2/256;
		buf[10]=m_send_z2%256;
		buf[11]=m_send_z3/256;
		buf[12]=m_send_z3%256;
		buf[13]=m_send_z4/256;
		buf[14]=m_send_z4%256;
		buf[15]=m_send_z5/256;
		buf[16]=m_send_z5%256;
		buf[17]=m_send_z6/256;
		buf[18]=m_send_z6%256;

		m_SerialPort.WriteToPort(buf,19);
		

		GetDlgItem(IDC_EDIT1)->GetWindowText(temp);//先获取原来的字符串，再添加新的字符串
		str.Format("%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9],buf[10],buf[11],buf[12],buf[13],buf[14],buf[15],buf[16],buf[17],buf[18]);
		GetDlgItem(IDC_EDIT1)->SetWindowText("发送数据包:\r\n"+str+"\r\n"+temp);//显示16进制数据 
	}
	
}

void CCamTestDlg::OnAbout() 
{
	pMyAboutDlg=new CMyAboutDlg();
	pMyAboutDlg->Create(IDD_DIALOG2,this);
	pMyAboutDlg->ShowWindow(SW_SHOW);
	
}

BOOL CCamTestDlg::md5check()
{
	LPCTSTR lpRootPathName = "c:\\";          // root directory
	LPTSTR lpVolumeNameBuffer = new char[12];        // volume name buffer
	DWORD nVolumeNameSize = 12 ;          // length of name buffer
	DWORD lpVolumeSerialNumber;     // volume serial number
	DWORD lpMaximumComponentLength; // maximum file name length
	DWORD lpFileSystemFlags;      // file system options
	LPTSTR lpFileSystemNameBuffer = new char[10];   // file system name buffer
	DWORD nFileSystemNameSize = 10;         // length of file system name buffer
	GetVolumeInformation(lpRootPathName,lpVolumeNameBuffer,nVolumeNameSize,
		&lpVolumeSerialNumber,&lpMaximumComponentLength,
		&lpFileSystemFlags,lpFileSystemNameBuffer,nFileSystemNameSize);
	
	CString str;
	str.Format("%lx",lpVolumeSerialNumber);//获取真实机器码
	
	//要CString 转char*
	str="626"+str;   //626+机器码   伪装
    char *ch_str = new char[str.GetLength() + 1];
    strncpy(ch_str,str, str.GetLength() + 1);
	machine_code=MD5String(ch_str);  //真实机器码md5加密，显示在客户界面上的
	//需要释放一次
	CString str2=machine_code+"yike";
	char *ch_str2 = new char[str2.GetLength() + 1];
    strncpy(ch_str2,str2, str2.GetLength() + 1);
	
	CString md5_str2;
	md5_str2=MD5String(ch_str2);  //加密算法，理论上他们不可能生成 md5(machinecode+"yike")
	
	//释放空间
	delete ch_str;
	delete ch_str2;
	
	//获取配置文件密钥
	CString code1,code2,code3;
	CString des="";
	::GetCurrentDirectory(100,des.GetBuffer(100));
	des.ReleaseBuffer();
	des+="\\config.ini";//获取文件路径
	
	GetPrivateProfileString("CODE","code1","nocode",code1.GetBufferSetLength(40),40,des);
	code1.ReleaseBuffer();
	GetPrivateProfileString("CODE","code2","nocode",code2.GetBufferSetLength(40),40,des);
	code2.ReleaseBuffer();
	GetPrivateProfileString("CODE","code3","nocode",code3.GetBufferSetLength(40),40,des);
	code3.ReleaseBuffer();
	
	if(md5_str2==code1||md5_str2==code2||md5_str2==code3)
		return 1;
	else	
		return 0;
}

BOOL CCamTestDlg::loadconfig()
{	

	CString custom1,custom2,custom3,custom4,custom5,custom6;
	CString des="";
	::GetCurrentDirectory(100,des.GetBuffer(100));
	des.ReleaseBuffer();
	des+="\\config.ini";//设置当前文件目录



	//数据接收区
	GetPrivateProfileString("RECEIVEDATA","custom1","nocode",custom1.GetBufferSetLength(40),40,des);
	custom1.ReleaseBuffer();
	GetPrivateProfileString("RECEIVEDATA","custom2","nocode",custom2.GetBufferSetLength(40),40,des);
	custom2.ReleaseBuffer();
	GetPrivateProfileString("RECEIVEDATA","custom3","nocode",custom3.GetBufferSetLength(40),40,des);
	custom3.ReleaseBuffer();
	GetPrivateProfileString("RECEIVEDATA","custom4","nocode",custom4.GetBufferSetLength(40),40,des);
	custom4.ReleaseBuffer();
	GetPrivateProfileString("RECEIVEDATA","custom5","nocode",custom5.GetBufferSetLength(40),40,des);
	custom5.ReleaseBuffer();
	
	GetDlgItem(IDC_STATIC_Z1)->SetWindowText(custom1);
	GetDlgItem(IDC_STATIC_Z2)->SetWindowText(custom2);
	GetDlgItem(IDC_STATIC_Z3)->SetWindowText(custom3);
	GetDlgItem(IDC_STATIC_Z4)->SetWindowText(custom4);
	GetDlgItem(IDC_STATIC_Z5)->SetWindowText(custom5);
//sensor的标签值也可以改了！！！
	GetPrivateProfileString("RECEIVEDATA","sensor1","nocode",custom1.GetBufferSetLength(40),40,des);
	custom1.ReleaseBuffer();
	GetPrivateProfileString("RECEIVEDATA","sensor2","nocode",custom2.GetBufferSetLength(40),40,des);
	custom2.ReleaseBuffer();
	GetPrivateProfileString("RECEIVEDATA","sensor3","nocode",custom3.GetBufferSetLength(40),40,des);
	custom3.ReleaseBuffer();
	GetPrivateProfileString("RECEIVEDATA","sensor4","nocode",custom4.GetBufferSetLength(40),40,des);
	custom4.ReleaseBuffer();
	GetPrivateProfileString("RECEIVEDATA","sensor5","nocode",custom5.GetBufferSetLength(40),40,des);
	custom5.ReleaseBuffer();

	GetDlgItem(IDC_STATIC_SENSOR1)->SetWindowText(custom1);
	GetDlgItem(IDC_STATIC_SENSOR2)->SetWindowText(custom2);
	GetDlgItem(IDC_STATIC_SENSOR3)->SetWindowText(custom3);
	GetDlgItem(IDC_STATIC_SENSOR4)->SetWindowText(custom4);
	GetDlgItem(IDC_STATIC_SENSOR5)->SetWindowText(custom5);

	//数据发送区
	GetPrivateProfileString("SENDDATA","custom1","nocode",custom1.GetBufferSetLength(40),40,des);
	custom1.ReleaseBuffer();
	GetPrivateProfileString("SENDDATA","custom2","nocode",custom2.GetBufferSetLength(40),40,des);
	custom2.ReleaseBuffer();
	GetPrivateProfileString("SENDDATA","custom3","nocode",custom3.GetBufferSetLength(40),40,des);
	custom3.ReleaseBuffer();
	GetPrivateProfileString("SENDDATA","custom4","nocode",custom4.GetBufferSetLength(40),40,des);
	custom4.ReleaseBuffer();
	GetPrivateProfileString("SENDDATA","custom5","nocode",custom5.GetBufferSetLength(40),40,des);
	custom5.ReleaseBuffer();
	GetPrivateProfileString("SENDDATA","custom6","nocode",custom6.GetBufferSetLength(40),40,des);
	custom5.ReleaseBuffer();
	
	GetDlgItem(IDC_STATIC_SEND_Z1)->SetWindowText(custom1);
	GetDlgItem(IDC_STATIC_SEND_Z2)->SetWindowText(custom2);
	GetDlgItem(IDC_STATIC_SEND_Z3)->SetWindowText(custom3);
	GetDlgItem(IDC_STATIC_SEND_Z4)->SetWindowText(custom4);
	GetDlgItem(IDC_STATIC_SEND_Z5)->SetWindowText(custom5);
	GetDlgItem(IDC_STATIC_SEND_Z6)->SetWindowText(custom6);

	//绘图设置区
	
	GetPrivateProfileString("DRAWSETTING","custom1","nocode",custom1.GetBufferSetLength(40),40,des);
	custom1.ReleaseBuffer();
	GetPrivateProfileString("DRAWSETTING","custom2","nocode",custom2.GetBufferSetLength(40),40,des);
	custom2.ReleaseBuffer();

	GetDlgItem(IDC_CHECK_4)->SetWindowText(custom1);
	GetDlgItem(IDC_CHECK_5)->SetWindowText(custom2);
	
	unsigned int check1,check2,check3,check4,check5,check6;
	check1=GetPrivateProfileInt("DRAWSETTING","check1",0,des);
	check2=GetPrivateProfileInt("DRAWSETTING","check2",0,des);
	check3=GetPrivateProfileInt("DRAWSETTING","check3",0,des);
	check4=GetPrivateProfileInt("DRAWSETTING","check4",0,des);
	check5=GetPrivateProfileInt("DRAWSETTING","check5",0,des);
	check6=GetPrivateProfileInt("DRAWSETTING","check6",0,des);
	((CButton*)GetDlgItem(IDC_CHECK_0))->SetCheck(check1);
	((CButton*)GetDlgItem(IDC_CHECK_1))->SetCheck(check2);
	((CButton*)GetDlgItem(IDC_CHECK_2))->SetCheck(check3);
	((CButton*)GetDlgItem(IDC_CHECK_3))->SetCheck(check4);
	((CButton*)GetDlgItem(IDC_CHECK_4))->SetCheck(check5);
	((CButton*)GetDlgItem(IDC_CHECK_5))->SetCheck(check6);

	m_y_min=GetPrivateProfileInt("DRAWSETTING","ymin",0,des);
	m_y_max=GetPrivateProfileInt("DRAWSETTING","ymax",65535,des);
	m_x_max=GetPrivateProfileInt("DRAWSETTING","xrange",100,des);

	//串口设置
	unsigned int port,baud;
	port=GetPrivateProfileInt("SETTING","port",0,des);
	baud=GetPrivateProfileInt("SETTING","baud",0,des);
	((CComboBox *)GetDlgItem(IDC_BAUD))->SetCurSel(baud);
	((CComboBox *)GetDlgItem(IDC_COM))->SetCurSel(port);
	
	check1=GetPrivateProfileInt("SETTING","check1",0,des);
	((CButton*)GetDlgItem(IDC_CHECK_CANSHU))->SetCheck(check1);
	return 1;
}


void CCamTestDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	// 获取波特率
	CComboBox *comboBox=(CComboBox *)GetDlgItem(IDC_BAUD);
	CString BaudRate;
	comboBox->GetWindowText(BaudRate);
	int nBaudRate=atoi(BaudRate);
	
	//获取端口号
	comboBox=(CComboBox *)GetDlgItem(IDC_COM);
	int port=comboBox->GetCurSel()+1;
	
	//判断复选 
	UpdateData(TRUE); //读入编辑框中的数据？
	
	canshushow=IsDlgButtonChecked(IDC_CHECK_CANSHU);
	
	//控件初始化	init_Comm(port,BaudRate);
	
	if(m_SerialPort.InitPort(this, port, nBaudRate,'N',8,1,EV_RXFLAG | EV_RXCHAR,512))
	{
		m_SerialPort.StartMonitoring();
		flag_serial=1;
		GetDlgItem(IDC_OPEN)->EnableWindow(FALSE);//打开串口按钮失效
		GetDlgItem(IDC_BUTTON_STOP_SERIAL)->EnableWindow(1);
		GetDlgItem(IDC_BUTTON_LEFT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_CLOSESERIAL)->EnableWindow(1);
		
		GetDlgItem(IDC_CHECK_CANSHU)->EnableWindow(FALSE);//复选框失效


	CString des="",strtemp;
	::GetCurrentDirectory(100,des.GetBuffer(100));
	des.ReleaseBuffer();
	des+="\\config.ini";//设置当前文件目录


	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CANSHU));
	WritePrivateProfileString("SETTING","check1",strtemp,des);

	strtemp.Format("%d",((CComboBox *)GetDlgItem(IDC_BAUD))->GetCurSel());
	WritePrivateProfileString("SETTING","baud",strtemp,des);
		strtemp.Format("%d",((CComboBox *)GetDlgItem(IDC_COM))->GetCurSel());
	WritePrivateProfileString("SETTING","port",strtemp,des);
	

	}
	else
	{
		AfxMessageBox("串口不存在或被占用，请检查串口资源");
	}


}

void CCamTestDlg::OnCloseserial() 
{
	m_SerialPort.ClosePort();//关闭串口
	flag_serial=0;
	rerecive=1;
	GetDlgItem(IDC_OPEN)->EnableWindow(1);
	GetDlgItem(IDC_CLOSESERIAL)->EnableWindow(0);	
	
	GetDlgItem(IDC_BUTTON_STOP_SERIAL)->EnableWindow(0);	
	GetDlgItem(IDC_CHECK_CANSHU)->EnableWindow(1);//复选框失效
	GetDlgItem(IDC_EDIT1)->SetWindowText("");//文本框接收的数据清空

		//graph initial
	m_graph_main.ClearGraph();
	m_graph_main.SetElementLinetype(0);
	m_graph_main.SetElementLineColor(RGB(255,48,48)); //0
	m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(255,127,0));
	m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(138,43,226));
		m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(255,193,193));
		m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(139,0,139));
		m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(144,238,144));
			m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(46,139,87));
//设置坐标范围

	UpdateData(TRUE); //读入编辑框中的数据	
	m_graph_main.SetRange(rx/m_x_max*m_x_max,rx/m_x_max*m_x_max+m_x_max,m_y_min,m_y_max);  //

//左右翻转有效
		rx_now=rx;
	GetDlgItem(IDC_BUTTON_LEFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RIGHT)->EnableWindow(TRUE);

}

void CCamTestDlg::OnButtonChangeDraw() 
{
	UpdateData(TRUE); //读入编辑框中的数据	
	m_graph_main.SetRange(rx/m_x_max*m_x_max,rx/m_x_max*m_x_max+m_x_max,m_y_min,m_y_max);  //粗略的适应


	UpdateData(TRUE); //读入编辑框中的数据
	CString des="",strtemp;
	::GetCurrentDirectory(100,des.GetBuffer(100));
	des.ReleaseBuffer();
	des+="\\config.ini";//设置当前文件目录

	//保存
	strtemp.Format("%d",m_y_min);
	WritePrivateProfileString("DRAWSETTING","ymin",strtemp,des);
	strtemp.Format("%d",m_y_max);
	WritePrivateProfileString("DRAWSETTING","ymax",strtemp,des);
	strtemp.Format("%d",m_x_max);
	WritePrivateProfileString("DRAWSETTING","xrange",strtemp,des);
	
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_0));
	WritePrivateProfileString("DRAWSETTING","check1",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_1));
	WritePrivateProfileString("DRAWSETTING","check2",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_2));
	WritePrivateProfileString("DRAWSETTING","check3",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_3));
	WritePrivateProfileString("DRAWSETTING","check4",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_4));
	WritePrivateProfileString("DRAWSETTING","check5",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_5));
	WritePrivateProfileString("DRAWSETTING","check6",strtemp,des);
	
}

void CCamTestDlg::OnButtonClearDraw() 
{
	//graph initial
	m_graph_main.ClearGraph();
	m_graph_main.SetElementLinetype(0);
	m_graph_main.SetElementLineColor(RGB(255,48,48)); //0
	m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(255,127,0));
	m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(138,43,226));
		m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(255,193,193));
		m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(139,0,139));
		m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(144,238,144));
			m_graph_main.AddElement();//
	m_graph_main.SetElementLineColor(RGB(46,139,87));
//设置坐标范围

	UpdateData(TRUE); //读入编辑框中的数据	
	m_graph_main.SetRange(rx/m_x_max*m_x_max,rx/m_x_max*m_x_max+m_x_max,m_y_min,m_y_max);  //
}

void CCamTestDlg::OnButtonStopSerial() 
{
	
	static int stop_flag=1;
if(stop_flag==1)
{	rx_now=rx;
	GetDlgItem(IDC_BUTTON_LEFT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RIGHT)->EnableWindow(TRUE);
	m_SerialPort.StopMonitoring();	
	stop_flag=0;
	GetDlgItem(IDC_BUTTON_STOP_SERIAL)-> SetWindowText( "恢复串口");//恢复串口

}
else
{
	
	GetDlgItem(IDC_BUTTON_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RIGHT)->EnableWindow(FALSE);
	m_SerialPort.RestartMonitoring();	
	stop_flag=1;
	GetDlgItem(IDC_BUTTON_STOP_SERIAL)-> SetWindowText( "暂停串口");
}
}

void CCamTestDlg::OnButtonLeft() 
{rx_now=rx_now-m_x_max;
m_graph_main.SetRange(rx_now/m_x_max*m_x_max,rx_now/m_x_max*m_x_max+m_x_max,m_y_min,m_y_max);  //调整坐标范围	
}

void CCamTestDlg::OnButtonRight() 
{
rx_now=rx_now+m_x_max;
m_graph_main.SetRange(rx_now/m_x_max*m_x_max,rx_now/m_x_max*m_x_max+m_x_max,m_y_min,m_y_max);  //调整坐标范围	
}
