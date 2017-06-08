// ConsoleApplication1.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include "..\\..\\HRSDK\x86\\HRSDK.h"
using namespace std;
HROBOT s;


void main()
{
	HROBOT s = Connect("192.168.0.3");
	system("pause");
	set_mode(s, 1);
	set_acc_dec_ratio(s, 20);
	int acc = get_acc_dec_ratioRG(s);
	set_ptp_speed(s, 20);
	int vel1 = get_ptp_speedRG(s);
	set_lin_speed(s, 1000);
	int vel2 = get_lin_speedRG(s);
	set_override_ratio(s, 20);
	int override = get_override_ratioRG(s);
	set_tool_number(s, 20);
	int vel3 = get_tool_number(s);
	set_base_number(s, 1);
	int num = get_base_number(s);
	//(1)
	double coor[6] = { 0, 50, 300, 0, 0, 0 };
	define_tool(s, 2, coor);
	double ToolCoor[6];
	get_tool_data(s, 2, ToolCoor);
	//(2)
//	coor[6] = { 0, 0, 100, 0, 0, 0 };
	define_base(s, 2, coor);
	double BaseCoor[6];
	get_base_data(s, 2, BaseCoor);

	//record teach point  校正
	ptp_point(s, 0);   //move to teach point 0 
	system("pause");//wait for arm to teach point 0
	tool_correct_measure(s, 1, 0); //record the point0 as calibration point 
	ptp_point(s, 1); //move to teach point 1 
	system("pause");//wait for arm to teach point 1
	tool_correct_measure(s, 1, 1);//record the point1 as calibration point
	ptp_point(s, 2);   //move to teach point 2 
	system("pause");//wait for arm to teach point 2
	tool_correct_measure(s, 1, 2);//record the point2 as calibration point
	ptp_point(s, 3);   //move to teach point 3 
	system("pause");//wait for arm to teach point 3
	tool_correct_measure(s, 1, 3);//record the point3 as calibration point
	tool_correct_calculate(s, 1); //4 points calibration to tool 1 coordinate
		// record teach point
	ptp_point(s, 0);   //move to teach point 0
	base_correct_measure(s, 1, 0);//record point1 as calibration point
	ptp_point(s, 1);
	base_correct_measure(s, 1, 1);
	ptp_point(s, 2);
	base_correct_measure(s, 1, 2);
	base_correct_calculate(s, 1); //3 points calibration to base 1 coordinate
	//6軸校正
	if (get_motor_state(s) == 1)
		set_motor_state(s, 0);
	mastering(s,0);
	mastering(s,1);
	mastering(s,2);
	mastering(s,3);
	mastering(s,4);
	mastering(s,5);

	set_mode(s, 0);
	int mode = get_mode(s);
	//if your arm get error
	controller_rest(s);

	//(1)
//	double coor[6] = { 0, 0, 0, 0, -90, 0 };
	set_pr(s, 400, 1, coor, 2, 2); //set address register  
	//address register number:400 
	//coordinate type:joint 
	//coordinate:{0,0,0,0,-90,0}
	//tool number:2 
	//base number:2
	
	//(2)
	int prNum = get_pr_type(s, 400);  //get address register number
//	double coor[6];
	get_pr_coordinate(s, 400, coor);  //get coordinate from pr400
	int tool_base[2];
	get_pr_tool_base(s, 400, tool_base); //get tool and base from pr400
	//tool:tool_base[0] 
	//base:tool_base[1]
//絕對座標
	//int ptp_pos(s, double*p);   //p:{XYZABC}
	//int ptp_axis(s, double*p);  //p:{A1~A6}
//相對座標
	//int ptp_rel_pos(s, double*p);  //p:{XYZABC}
	//int ptp_rel_axis(s, double*p); //p:{A1~A6}
//教導點之點對點運動
	//int ptp_point(s, int p);
	// Declare p1,p2,p3,p4,r1,r2 
	// Record teach point 1,2

	double p1[6], p2[6], p3[6], p4[6], r1[6], r2[6];
	set_ptp_speed(s, 100);   // set point to point speed 
	ptp_pos(s, p1);   // ptp to Cartesian coordinates p1
	ptp_axis(s, p2);  // ptp to joint coordinates p2
	ptp_axis(s, p3);   // ptp to joint coordinates p3
	ptp_pos(s, p4);   // ptp to Cartesian coordinates p4
	ptp_rel_pos(s, r1);   // ptp to relative Cartesian coordinates r1
	ptp_rel_pos(s, r2);   // ptp to relative Cartesian coordinates r1
	ptp_rel_axis(s, r1);   // ptp to relative joint coordinates r1 
	system("pause");   //wait for arm to the position 
	teach_point(s, 1);   //save current position point as teach point 2
	ptp_rel_axis(s, r2);   // ptp to relative joint coordinates r1 
	system("pause");   //wait for arm to the position 
	teach_point(s, 2);   //save current position point as teach point 2
	ptp_point(s, 1);   // ptp to teach point 1
	ptp_point(s, 2);   // ptp to teach pint 2

//直線運動
	//絕對座標
	//int lin_pos(s, double*p);   //p:{XYZABC}
	//int lin_axis(s, double*p);  //p:{A1~A6}
	//相對座標
	//int lin_rel_pos(s, double*p);  //p:{XYZABC}
	//int lin_rel_axis(s, double*p); //p:{A1~A6}
	//教導點之點對點運動
	//int lin_point(s, int p);
	
	set_lin_speed(s, 100);   // set point to point speed 
	lin_pos(s, p1);   // lin to Cartesian coordinates p1
	lin_axis(s, p2);  // lin to joint coordinates p2
	lin_axis(s, p3);   // lin to joint coordinates p3
	lin_pos(s, p4);   // lin to Cartesian coordinates p4
	lin_rel_pos(s, r1);   // lin to relative Cartesian coordinates r1
	lin_rel_pos(s, r2);   // lin to relative Cartesian coordinates r1
	lin_rel_axis(s, r1);   // lin to relative joint coordinates r1 
	system("pause");   //wait for arm to the position 
	teach_point(s, 1);   //save current position point as teach point 2
	lin_rel_axis(s, r2);   // lin to relative joint coordinates r1 
	system("pause");   //wait for arm to the position 
	teach_point(s, 2);   //save current position point as teach point 2
	lin_point(s, 1);   // lin to teach point 1
	lin_point(s, 2);   // lin to teach pint 2

//圓弧運動
	//p:{XYZABC}
	circ_set_aux_pos(s, p1);   //set reference point of circle motion 
	circ_set_end_pos(s, p2);   // set end point of circle motion
	circ_pos(s);   // circle motion
	
	double cp1[6], cp2[6], cp3[6], cp4[6];
	//(1)
	circ_set_aux_pos(s, cp1);
	circ_set_end_pos(s, cp2);
	circ_pos(s);
	cout << "press any key to hold the motion." << endl;
	system("pause");
	motion_hold(s);				//運動暫停
	system("pause");
	cout <<"press any key to continue the motion."<< endl;
	motion_continue(s);			//運動繼續
	//(2)
	set_smooth_length(s, 100);  //設定平滑半徑
	circ_set_aux_pos(s, cp3);
	circ_set_end_pos(s, cp4);
	motion_delay(s, 1000);      //運動延遲
	circ_pos(s);
	cout <<"press any key to stop the motion."<< endl;
	motion_abort(s);			//運動停止

	set_com_id(s, 10);   // set number 10 before sending instruction 
	ptp_pos(s, p1);   //instruction number 10 
	int comId;
	int motionID[2];//int[0]:motion type 
					/*2 = 直線運動
					3 = 圓弧運動
					4 = 點對點運動
					7 = 開啟平滑運動
					8 = 關閉平滑運動
					9 = 運動延遲*/
					//int[1]:motion id
	comId = get_com_id(s,motionID);		//取得運動命令編號

	jog_joint1P(s);// positive jog joint 1  
	system("pause");
	jog_stop(s);//joint stop jogging 

	double pos[6];
	get_current_jointRG(s, pos);   //get current point in joint coordinate 關節座標
	
	get_current_cartRG(s, pos);   //get current point in cart coordinate 絕對座標
	
	double rpm[6];
	get_current_rpmRG(s,rpm);   //faster than former 轉速
	
	int count;
	count = get_com_countRG(s);   //get current command count in buffer

	int state;
	//(1)執行 ptp 運動，然後暫停運動，取得的 state 值為暫停(3)
	ptp_pos(s, p1);
	system("pause");
	motion_hold(s);
	state = get_motion_statusRG(s);
	//(2)繼續運動，取得的 state 值為運動(2)
	motion_continue(s);
	state = get_motion_statusRG(s);
	motion_delay(s,3000);
	//(3)延遲 3 秒等運動執行完，獲得的值為停止(1)
	state = get_motion_statusRG(s);

	int err;
	err = get_errCodeRG(s);   //get motion error code

	//設定控制器IP
	int ip[4] = { 192,168,0,3 };
	set_server_ip(s, ip);

	Close(s);

}

