// State.cpp : implementation file
//

#include "stdafx.h"
#include "CamTest.h"
#include "State.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CState dialog


CState::CState(CWnd* pParent /*=NULL*/)
	: CDialog(CState::IDD, pParent)
{
	//{{AFX_DATA_INIT(CState)
	m_sensor_y_min = 0;
	m_sensor_y_max = 0;
	m_custom2_y_min = 0;
	m_custom2_y_max = 0;
	m_custom1_y_min = 0;
	m_custom2_x_max = 0;
	m_custom1_y_max = 0;
	m_custom1_x_max = 0;
	//}}AFX_DATA_INIT
}


void CState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CState)
	DDX_Control(pDX, IDC_NTGRAPHCTRL_SENSOR, m_nt_sensor);
	DDX_Control(pDX, IDC_NTGRAPHCTRL_CUSTOM1, m_nt_custom1);
	DDX_Control(pDX, IDC_NTGRAPHCTRL_CUSTOM2, m_nt_custom2);
	DDX_Text(pDX, IDC_EDIT_SENSOR_Y_MIN, m_sensor_y_min);
	DDX_Text(pDX, IDC_EDIT_SENSOR_Y_MAX, m_sensor_y_max);
	DDX_Text(pDX, IDC_EDIT_CUSTOM2_Y_MIN, m_custom2_y_min);
	DDX_Text(pDX, IDC_EDIT_CUSTOM2_Y_MAX, m_custom2_y_max);
	DDX_Text(pDX, IDC_EDIT_CUSTOM1_Y_MIN, m_custom1_y_min);
	DDX_Text(pDX, IDC_EDIT_CUSTOM2_X_MAX, m_custom2_x_max);
	DDX_Text(pDX, IDC_EDIT_CUSTOM1_Y_MAX, m_custom1_y_max);
	DDX_Text(pDX, IDC_EDIT_CUSTOM1_X_MAX, m_custom1_x_max);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CState, CDialog)
	//{{AFX_MSG_MAP(CState)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonChange)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_DRAW_SENSOR, OnButtonClearDrawSensor)
	ON_BN_CLICKED(IDC_BUTTON_SENSOR_STOP, OnButtonSensorStop)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_DRAW_SENSOR, OnButtonChangeDrawSensor)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_DRAW2, OnButtonClearDrawCustom1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButtonCustom1Stop)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_DRAW, OnButtonChangeDrawCustom1)
	ON_BN_CLICKED(IDC_BUTTON6, OnButtonCustom2Stop)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_DRAW3, OnButtonClearDraw3)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_DRAW2, OnButtonChangeDraw2)
	ON_BN_CLICKED(IDC_STOP2, OnStopAll)
	ON_BN_CLICKED(IDC_BUTTON_LEFT_1, OnButtonLeft1)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT_1, OnButtonRight1)
	ON_BN_CLICKED(IDC_BUTTON_LEFT_2, OnButtonLeft2)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT_2, OnButtonRight2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CState message handlers

/*void CState::DrawCtrl()
{
		CWnd   *pWnd=GetDlgItem(IDC_SpeedPWM); 
        CDC   *pControlDC=pWnd-> GetDC(); 
        pWnd-> Invalidate(); 
        pWnd-> UpdateWindow(); 
        pControlDC-> SelectStockObject(BLACK_BRUSH); 
        pControlDC-> Rectangle(0,0,10,10); 
        pWnd-> ReleaseDC(pControlDC); 
}*/


BOOL CState::OnInitDialog() 
{
	loadconfig();
	UpdateData(FALSE); //
	//��ͼ��ձ��λ
	sensor_draw_flag=1;
	custom1_draw_flag=1;
	custom2_draw_flag=1;
	all_draw_flag=1;
	
	//����������nt��ʼ����������ʽ
	m_nt_sensor.ClearGraph();
	m_nt_sensor.SetElementLinetype(8);
	m_nt_sensor.SetElementLineColor(RGB(118,238,198)); //0
	m_nt_sensor.SetXGridNumber(7);
	m_nt_sensor.SetRange(0,7,m_sensor_y_min,m_sensor_y_max); 
  
	//custom1 nt��ʼ�� 
	transfer_rx=0;
	m_nt_custom1.ClearGraph();
	m_nt_custom1.SetElementLinetype(0);
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetRange(transfer_rx/m_custom1_x_max*m_custom1_x_max,transfer_rx/m_custom1_x_max*m_custom1_x_max+m_custom1_x_max,m_custom1_y_min,m_custom1_y_max);  //


	m_nt_custom1.SetElementLineColor(RGB(255,48,48)); //0
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(255,127,0));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(138,43,226));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(255,193,193));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(139,0,139));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(144,238,144));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(240,255,255));//
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(255,228,225));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(135,206,250));

	
	//custom2 nt��ʼ�� 
	transfer_rx=0;
	m_nt_custom2.ClearGraph();
	m_nt_custom2.SetElementLinetype(0);
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetRange(transfer_rx/m_custom2_x_max*m_custom2_x_max,transfer_rx/m_custom2_x_max*m_custom2_x_max+m_custom2_x_max,m_custom2_y_min,m_custom2_y_max);  //


	m_nt_custom2.SetElementLineColor(RGB(255,48,48)); //0
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(255,127,0));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(138,43,226));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(128,128,64));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(139,0,139));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(144,238,144));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(240,255,255));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(255,228,225));//118,238,198
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(135,206,250));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(240,128,128));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(205,92,92));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(255,255,0));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(85,107,47));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(46,139,87));
	

			GetDlgItem(IDC_BUTTON_LEFT_1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RIGHT_1)->EnableWindow(FALSE);

			GetDlgItem(IDC_BUTTON_LEFT_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RIGHT_2)->EnableWindow(FALSE);
	return TRUE; 
}

void CState::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}




void CState::OnStop() 
{//���ȫ����ͼ��
OnButtonClearDrawSensor();
OnButtonClearDraw3();
OnButtonClearDrawCustom1();
}



void CState::OnClose() 
{
	OnButtonChange();
	SendMessage(WM_CLOSE);
}


///////////////////////////////////////////////////���������

void CState::transfer_value(unsigned int rx,BYTE * canshu_data)
{	transfer_rx=rx;
	transfer_dianji=canshu_data[0]*256+canshu_data[1];
	transfer_bianmaqi=canshu_data[2]*256+canshu_data[3];
	transfer_dianji2=canshu_data[4]*256+canshu_data[5];    //��ʵ���Ƕ��
	transfer_bianmaqi2=canshu_data[6]*256+canshu_data[7];	//��ʵ���Ƕ������ֵ
	transfer_sensor1=canshu_data[8]*256+canshu_data[9];
	transfer_sensor2=canshu_data[10]*256+canshu_data[11];
	transfer_sensor3=canshu_data[12]*256+canshu_data[13];
	transfer_sensor4=canshu_data[14]*256+canshu_data[15];
	transfer_sensor5=canshu_data[16]*256+canshu_data[17];
	transfer_z1=canshu_data[18];
	transfer_z2=canshu_data[19];
	transfer_z3=canshu_data[20];
	transfer_z4=canshu_data[21];
	transfer_z5=canshu_data[22];
	
}

void CState::draw_sensor(void)
{	
	if(sensor_draw_flag==1)
	{
	m_nt_sensor.ClearGraph();//��Ϊ����߲��䣬����Ϊ�˴�value������Сvalue��ֻ��������
	m_nt_sensor.SetElementLinetype(8);
	m_nt_sensor.SetElementLineColor(RGB(118,238,198)); //0
	m_nt_sensor.SetXGridNumber(7);
	m_nt_sensor.SetRange(0,7,m_sensor_y_min,m_sensor_y_max); 

	m_nt_sensor.PlotXY(0,transfer_sensor1,0);
	m_nt_sensor.PlotXY(1,transfer_sensor2,0);
	m_nt_sensor.PlotXY(2,transfer_sensor3,0);
	m_nt_sensor.PlotXY(3,transfer_sensor4,0);
	m_nt_sensor.PlotXY(4,transfer_sensor5,0);
	m_nt_sensor.PlotXY(5,transfer_dianji2,0);
	m_nt_sensor.PlotXY(6,transfer_bianmaqi2,0);
	m_nt_sensor.PlotXY(7,transfer_bianmaqi2,0);//�������д���ˣ������д��7����ʾʲô�ء�����
	}
}

void CState::draw_custom1(void)
{
	if(custom1_draw_flag==1)
	{
	m_nt_custom1.SetRange(transfer_rx/m_custom1_x_max*m_custom1_x_max,transfer_rx/m_custom1_x_max*m_custom1_x_max+m_custom1_x_max,m_custom1_y_min,m_custom1_y_max);  //

	
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_DIANJI))
		m_nt_custom1.PlotXY(transfer_rx,transfer_dianji,0);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_DIANJISUDU))
		m_nt_custom1.PlotXY(transfer_rx,transfer_bianmaqi,1);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_DUOJI))
		m_nt_custom1.PlotXY(transfer_rx,transfer_dianji2,2);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_DUOJIQIWANG))
		m_nt_custom1.PlotXY(transfer_rx,transfer_bianmaqi2,3);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z1))
		m_nt_custom1.PlotXY(transfer_rx,transfer_z1,4);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z2))
		m_nt_custom1.PlotXY(transfer_rx,transfer_z2,5);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z3))
		m_nt_custom1.PlotXY(transfer_rx,transfer_z3,6);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z4))
		m_nt_custom1.PlotXY(transfer_rx,transfer_z4,7);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z5))
		m_nt_custom1.PlotXY(transfer_rx,transfer_z5,8);//��ͼ
}
}

void CState::draw_custom2(void)
{
		if(custom2_draw_flag==1)
	{
	m_nt_custom2.SetRange(transfer_rx/m_custom2_x_max*m_custom2_x_max,transfer_rx/m_custom2_x_max*m_custom2_x_max+m_custom2_x_max,m_custom2_y_min,m_custom2_y_max);  //

	
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_DIANJI))
		m_nt_custom2.PlotXY(transfer_rx,transfer_dianji,0);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_DIANJISUDU))
		m_nt_custom2.PlotXY(transfer_rx,transfer_bianmaqi,1);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_DUOJI))
		m_nt_custom2.PlotXY(transfer_rx,transfer_dianji2,2);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_DUOJIQIWANG))
		m_nt_custom2.PlotXY(transfer_rx,transfer_bianmaqi2,3);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z1))
		m_nt_custom2.PlotXY(transfer_rx,transfer_z1,4);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z2))
		m_nt_custom2.PlotXY(transfer_rx,transfer_z2,5);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z3))
		m_nt_custom2.PlotXY(transfer_rx,transfer_z3,6);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z4))
		m_nt_custom2.PlotXY(transfer_rx,transfer_z4,7);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z5))
		m_nt_custom2.PlotXY(transfer_rx,transfer_z5,8);//��ͼ

	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR1))
		m_nt_custom2.PlotXY(transfer_rx,transfer_sensor1,9);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR2))
		m_nt_custom2.PlotXY(transfer_rx,transfer_sensor2,10);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR3))
		m_nt_custom2.PlotXY(transfer_rx,transfer_sensor3,11);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR4))
		m_nt_custom2.PlotXY(transfer_rx,transfer_sensor4,12);//��ͼ
	if(IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR5))
		m_nt_custom2.PlotXY(transfer_rx,transfer_sensor5,13);//��ͼ

}
}

void CState::OnButtonClearDrawSensor() 
{
	m_nt_sensor.ClearGraph();
	m_nt_sensor.SetElementLinetype(8);
	m_nt_sensor.SetElementLineColor(RGB(118,238,198)); //0
	m_nt_sensor.SetXGridNumber(7);
	m_nt_sensor.SetRange(0,7,m_sensor_y_min,m_sensor_y_max); 
	
}

void CState::OnButtonSensorStop() 
{
	if(sensor_draw_flag==1){
		sensor_draw_flag=0;	
		GetDlgItem(IDC_BUTTON_SENSOR_STOP)-> SetWindowText( "�ָ�");//��ť���ֱ�ɻָ�
	}
	else
	{
		sensor_draw_flag=1;	
		GetDlgItem(IDC_BUTTON_SENSOR_STOP)-> SetWindowText( "��ͣ");//��ť���ֱ����ͣ
	}
}

void CState::OnButtonChangeDrawSensor() 

{	OnButtonChange();
	UpdateData(TRUE); //����༭���е�����	
	m_nt_sensor.SetRange(0,7,m_sensor_y_min,m_sensor_y_max);  //���Ե���Ӧ	
}

void CState::OnButtonClearDrawCustom1() 
{
	m_nt_custom1.ClearGraph();
	m_nt_custom1.SetElementLinetype(0);
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetRange(transfer_rx/m_custom1_x_max*m_custom1_x_max,transfer_rx/m_custom1_x_max*m_custom1_x_max+m_custom1_x_max,m_custom1_y_min,m_custom1_y_max);  //


	m_nt_custom1.SetElementLineColor(RGB(255,48,48)); //0
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(255,127,0));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(138,43,226));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(255,193,193));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(139,0,139));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(144,238,144));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(240,255,255));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(255,228,225));
	m_nt_custom1.AddElement();//
	m_nt_custom1.SetElementWidth(2);
	m_nt_custom1.SetElementLineColor(RGB(135,206,250));
}

void CState::OnButtonCustom1Stop() 
{
	if(custom1_draw_flag==1){
		custom1_draw_flag=0;	
		GetDlgItem(IDC_BUTTON2)-> SetWindowText( "�ָ�");//��ť���ֱ�ɻָ�

		rx_now1=transfer_rx;
	GetDlgItem(IDC_BUTTON_LEFT_1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RIGHT_1)->EnableWindow(TRUE);

	}
	else
	{
		custom1_draw_flag=1;	
		GetDlgItem(IDC_BUTTON2)-> SetWindowText( "��ͣ");//��ť���ֱ����ͣ

		GetDlgItem(IDC_BUTTON_LEFT_1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RIGHT_1)->EnableWindow(FALSE);

	}
	
}

void CState::OnButtonChangeDrawCustom1() 
{	OnButtonChange();
	UpdateData(TRUE); //����༭���е�����	
	m_nt_custom1.SetRange(transfer_rx/m_custom1_x_max*m_custom1_x_max,transfer_rx/m_custom1_x_max*m_custom1_x_max+m_custom1_x_max,m_custom1_y_min,m_custom1_y_max);  //
	
}

void CState::OnButtonCustom2Stop() 
{
if(custom2_draw_flag==1){
		custom2_draw_flag=0;	
		GetDlgItem(IDC_BUTTON6)-> SetWindowText( "�ָ�");//��ť���ֱ�ɻָ�
		rx_now2=transfer_rx;
	GetDlgItem(IDC_BUTTON_LEFT_2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RIGHT_2)->EnableWindow(TRUE);
	}
	else
	{
		custom2_draw_flag=1;	
		GetDlgItem(IDC_BUTTON6)-> SetWindowText( "��ͣ");//��ť���ֱ����ͣ
			GetDlgItem(IDC_BUTTON_LEFT_2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RIGHT_2)->EnableWindow(FALSE);
	}	
}

void CState::OnButtonClearDraw3() 
{
	//custom2 nt��ʼ�� 
	m_nt_custom2.ClearGraph();
	m_nt_custom2.SetElementLinetype(0);
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetRange(transfer_rx/m_custom2_x_max*m_custom2_x_max,transfer_rx/m_custom2_x_max*m_custom2_x_max+m_custom2_x_max,m_custom2_y_min,m_custom2_y_max);  //


	m_nt_custom2.SetElementLineColor(RGB(255,48,48)); //0
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(255,127,0));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(138,43,226));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(255,193,193));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(139,0,139));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(144,238,144));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(240,255,255));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(255,228,225));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(135,206,250));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(240,128,128));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(205,92,92));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(255,255,0));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(85,107,47));
	m_nt_custom2.AddElement();//
	m_nt_custom2.SetElementWidth(2);
	m_nt_custom2.SetElementLineColor(RGB(46,139,87));
}

void CState::OnButtonChangeDraw2() 
{
	OnButtonChange();
UpdateData(TRUE); //����༭���е�����
m_nt_custom2.SetRange(transfer_rx/m_custom2_x_max*m_custom2_x_max,transfer_rx/m_custom2_x_max*m_custom2_x_max+m_custom2_x_max,m_custom2_y_min,m_custom2_y_max);  //
	
}

void CState::OnStopAll() 
{
	if(all_draw_flag==1){
		all_draw_flag=0;	
		GetDlgItem(IDC_STOP2)-> SetWindowText( "ȫ���ָ�");//��ť���ֱ�ɻָ�
		OnButtonSensorStop();
		OnButtonCustom2Stop();
		OnButtonCustom1Stop();
	}
	else
	{
		all_draw_flag=1;	
		GetDlgItem(IDC_STOP2)-> SetWindowText( "ȫ����ͣ");//��ť���ֱ����ͣ
		OnButtonSensorStop();
		OnButtonCustom2Stop();
		OnButtonCustom1Stop();

	}
	
}


BOOL CState::loadconfig()
{	

	CString custom1,custom2,custom3,custom4,custom5;
	CString des="";
	::GetCurrentDirectory(100,des.GetBuffer(100));
	des.ReleaseBuffer();
	des+="\\config.ini";//���õ�ǰ�ļ�Ŀ¼



	//CONTROLPLATFOR MCUSTOM1
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM1","custom1","nocode",custom1.GetBufferSetLength(40),40,des);
	custom1.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM1","custom2","nocode",custom2.GetBufferSetLength(40),40,des);
	custom2.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM1","custom3","nocode",custom3.GetBufferSetLength(40),40,des);
	custom3.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM1","custom4","nocode",custom4.GetBufferSetLength(40),40,des);
	custom4.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM1","custom5","nocode",custom5.GetBufferSetLength(40),40,des);
	custom5.ReleaseBuffer();
	
	GetDlgItem(IDC_CHECK_CUSTOM1_Z1)->SetWindowText(custom1);
	GetDlgItem(IDC_CHECK_CUSTOM1_Z2)->SetWindowText(custom2);
	GetDlgItem(IDC_CHECK_CUSTOM1_Z3)->SetWindowText(custom3);
	GetDlgItem(IDC_CHECK_CUSTOM1_Z4)->SetWindowText(custom4);
	GetDlgItem(IDC_CHECK_CUSTOM1_Z5)->SetWindowText(custom5);

	unsigned int check1,check2,check3,check4,check5,check6,check7,check8,check9,check10,check11,check12,check13,check14;
	check1=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check1",0,des);
	check2=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check2",0,des);
	check3=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check3",0,des);
	check4=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check4",0,des);
	check5=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check5",0,des);
	check6=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check6",0,des);
	check7=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check7",0,des);
	check8=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check8",0,des);
	check9=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","check9",0,des);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_DIANJI))->SetCheck(check1);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_DIANJISUDU))->SetCheck(check2);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_DUOJI))->SetCheck(check3);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_DUOJIQIWANG))->SetCheck(check4);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_Z1))->SetCheck(check5);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_Z2))->SetCheck(check6);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_Z3))->SetCheck(check7);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_Z4))->SetCheck(check8);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM1_Z5))->SetCheck(check9);

	m_custom1_y_min=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","ymin",0,des);
	m_custom1_y_max=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","ymax",65535,des);
	m_custom1_x_max=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM1","xrange",100,des);

	//CONTROLPLATFOR MCUSTOM2
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","custom1","nocode",custom1.GetBufferSetLength(40),40,des);
	custom1.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","custom2","nocode",custom2.GetBufferSetLength(40),40,des);
	custom2.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","custom3","nocode",custom3.GetBufferSetLength(40),40,des);
	custom3.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","custom4","nocode",custom4.GetBufferSetLength(40),40,des);
	custom4.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","custom5","nocode",custom5.GetBufferSetLength(40),40,des);
	custom5.ReleaseBuffer();
	
	GetDlgItem(IDC_CHECK_CUSTOM2_Z1)->SetWindowText(custom1);
	GetDlgItem(IDC_CHECK_CUSTOM2_Z2)->SetWindowText(custom2);
	GetDlgItem(IDC_CHECK_CUSTOM2_Z3)->SetWindowText(custom3);
	GetDlgItem(IDC_CHECK_CUSTOM2_Z4)->SetWindowText(custom4);
	GetDlgItem(IDC_CHECK_CUSTOM2_Z5)->SetWindowText(custom5);
	//sensor��ǩ�ɱ�
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","sensor1","nocode",custom1.GetBufferSetLength(40),40,des);
	custom1.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","sensor2","nocode",custom2.GetBufferSetLength(40),40,des);
	custom2.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","sensor3","nocode",custom3.GetBufferSetLength(40),40,des);
	custom3.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","sensor4","nocode",custom4.GetBufferSetLength(40),40,des);
	custom4.ReleaseBuffer();
	GetPrivateProfileString("CONTROLPLATFORMCUSTOM2","sensor5","nocode",custom5.GetBufferSetLength(40),40,des);
	custom5.ReleaseBuffer();
	
	GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR1)->SetWindowText(custom1);
	GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR2)->SetWindowText(custom2);
	GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR3)->SetWindowText(custom3);
	GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR4)->SetWindowText(custom4);
	GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR5)->SetWindowText(custom5);

//	unsigned int check1,check2,check3,check4,check5,check6,check7,check8,check9,check10,check11,check12,check13,check14;
	check1=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check1",0,des);
	check2=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check2",0,des);
	check3=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check3",0,des);
	check4=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check4",0,des);
	check5=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check5",0,des);
	check6=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check6",0,des);
	check7=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check7",0,des);
	check8=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check8",0,des);
	check9=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check9",0,des);
	check10=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check10",0,des);
	check11=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check11",0,des);
	check12=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check12",0,des);
	check13=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check13",0,des);
	check14=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","check14",0,des);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_DIANJI))->SetCheck(check1);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_DIANJISUDU))->SetCheck(check2);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_DUOJI))->SetCheck(check3);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_DUOJIQIWANG))->SetCheck(check4);

	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR1))->SetCheck(check5);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR2))->SetCheck(check6);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR3))->SetCheck(check7);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR4))->SetCheck(check8);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_SENSOR5))->SetCheck(check9);

	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_Z1))->SetCheck(check10);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_Z2))->SetCheck(check11);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_Z3))->SetCheck(check12);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_Z4))->SetCheck(check13);
	((CButton*)GetDlgItem(IDC_CHECK_CUSTOM2_Z5))->SetCheck(check14);

	m_custom2_y_min=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","ymin",0,des);
	m_custom2_y_max=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","ymax",65535,des);
	m_custom2_x_max=GetPrivateProfileInt("CONTROLPLATFORMCUSTOM2","xrange",100,des);

	//��������
	m_sensor_y_min=GetPrivateProfileInt("CONTROLPLATFORMSENSOR","ymin",0,des);
	m_sensor_y_max=GetPrivateProfileInt("CONTROLPLATFORMSENSOR","ymax",65535,des);




	return 1;
}

void CState::OnButtonChange() 
{	
	UpdateData(TRUE); //����༭���е�����
	CString des="",strtemp;
	::GetCurrentDirectory(100,des.GetBuffer(100));
	des.ReleaseBuffer();
	des+="\\config.ini";//���õ�ǰ�ļ�Ŀ¼

	//���洫������
	strtemp.Format("%d",m_sensor_y_min);
	WritePrivateProfileString("CONTROLPLATFORMSENSOR","ymin",strtemp,des);
	strtemp.Format("%d",m_sensor_y_max);
	WritePrivateProfileString("CONTROLPLATFORMSENSOR","ymax",strtemp,des);

	//�����Զ���1��
	strtemp.Format("%d",m_custom1_y_min);
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","ymin",strtemp,des);
	strtemp.Format("%d",m_custom1_y_max);
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","ymax",strtemp,des);
	strtemp.Format("%d",m_custom1_x_max);
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","xrange",strtemp,des);


	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_DIANJI));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check1",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_DIANJISUDU));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check2",strtemp,des);
		strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_DUOJI));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check3",strtemp,des);
			strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_DUOJIQIWANG));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check4",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z1));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check5",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z2));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check6",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z3));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check7",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z4));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check8",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM1_Z5));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM1","check9",strtemp,des);

	//�����Զ���2��
	strtemp.Format("%d",m_custom2_y_min);
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","ymin",strtemp,des);
	strtemp.Format("%d",m_custom2_y_max);
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","ymax",strtemp,des);
	strtemp.Format("%d",m_custom2_x_max);
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","xrange",strtemp,des);

	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_DIANJI));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check1",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_DIANJISUDU));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check2",strtemp,des);
		strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_DUOJI));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check3",strtemp,des);
			strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_DUOJIQIWANG));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check4",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR1));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check5",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR2));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check6",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR3));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check7",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR4));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check8",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_SENSOR5));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check9",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z1));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check10",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z2));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check11",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z3));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check12",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z4));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check13",strtemp,des);
	strtemp.Format("%d",IsDlgButtonChecked(IDC_CHECK_CUSTOM2_Z5));
	WritePrivateProfileString("CONTROLPLATFORMCUSTOM2","check14",strtemp,des);

}




void CState::OnButtonLeft1() 
{
rx_now1=rx_now1-m_custom1_x_max;
m_nt_custom1.SetRange(rx_now1/m_custom1_x_max*m_custom1_x_max,rx_now1/m_custom1_x_max*m_custom1_x_max+m_custom1_x_max,m_custom1_y_min,m_custom1_y_max);  //
	
}

void CState::OnButtonRight1() 
{
rx_now1=rx_now1+m_custom1_x_max;
m_nt_custom1.SetRange(rx_now1/m_custom1_x_max*m_custom1_x_max,rx_now1/m_custom1_x_max*m_custom1_x_max+m_custom1_x_max,m_custom1_y_min,m_custom1_y_max);  //
	
}

void CState::OnButtonLeft2() 
{
	rx_now2=rx_now2-m_custom2_x_max;

	m_nt_custom2.SetRange(rx_now2/m_custom2_x_max*m_custom2_x_max,rx_now2/m_custom2_x_max*m_custom2_x_max+m_custom2_x_max,m_custom2_y_min,m_custom2_y_max);  //

}

void CState::OnButtonRight2() 
{
	rx_now2=rx_now2+m_custom2_x_max;
	m_nt_custom2.SetRange(rx_now2/m_custom2_x_max*m_custom2_x_max,rx_now2/m_custom2_x_max*m_custom2_x_max+m_custom2_x_max,m_custom2_y_min,m_custom2_y_max);  //

}
