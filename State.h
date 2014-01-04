//{{AFX_INCLUDES()
#include "ntgraph.h"
//}}AFX_INCLUDES
#if !defined(AFX_STATE_H__A9D62F2F_A1D4_4F65_9EDE_749DE4BA2FBA__INCLUDED_)
#define AFX_STATE_H__A9D62F2F_A1D4_4F65_9EDE_749DE4BA2FBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// State.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CState dialog

class CState : public CDialog
{
// Construction
public:
	unsigned int transfer_rx;
	unsigned int rx_now1,rx_now2;
	int transfer_dianji;
	int transfer_bianmaqi;
	int transfer_dianji2;    //其实这是舵机
	int transfer_bianmaqi2;	//其实这是舵机期望值
	int transfer_sensor1;
	int transfer_sensor2;
	int transfer_sensor3;
	int transfer_sensor4;
	int transfer_sensor5;
	int transfer_z1;
	int transfer_z2;
	int transfer_z3;
	int transfer_z4;
	int transfer_z5;

	void transfer_value(unsigned int rx,BYTE * canshu_data);
	void draw_sensor(void);
	void draw_custom1(void);
	void draw_custom2(void);
	BOOL CState::loadconfig();

	int sensor_draw_flag;
	int custom1_draw_flag;
	int custom2_draw_flag;
	int all_draw_flag;



	CState(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CState)
	enum { IDD = IDD_DIALOG1 };
	CNTGraph	m_nt_sensor;
	CNTGraph	m_nt_custom1;
	CNTGraph	m_nt_custom2;
	UINT	m_sensor_y_min;
	UINT	m_sensor_y_max;
	UINT	m_custom2_y_min;
	UINT	m_custom2_y_max;
	UINT	m_custom1_y_min;
	UINT	m_custom2_x_max;
	UINT	m_custom1_y_max;
	UINT	m_custom1_x_max;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CState)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CState)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButtonChange();
	afx_msg void OnStop();
	afx_msg void OnClose();
	afx_msg void OnButtonClearDrawSensor();
	afx_msg void OnButtonSensorStop();
	afx_msg void OnButtonChangeDrawSensor();
	afx_msg void OnButtonClearDrawCustom1();
	afx_msg void OnButtonCustom1Stop();
	afx_msg void OnButtonChangeDrawCustom1();
	afx_msg void OnButtonCustom2Stop();
	afx_msg void OnButtonClearDraw3();
	afx_msg void OnButtonChangeDraw2();
	afx_msg void OnStopAll();
	afx_msg void OnButtonLeft1();
	afx_msg void OnButtonRight1();
	afx_msg void OnButtonLeft2();
	afx_msg void OnButtonRight2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATE_H__A9D62F2F_A1D4_4F65_9EDE_749DE4BA2FBA__INCLUDED_)
