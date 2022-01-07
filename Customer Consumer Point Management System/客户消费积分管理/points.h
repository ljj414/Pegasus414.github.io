#pragma once
#include<iostream>
#include<string>
#include<cstdlib>
#include<windows.h>
#include<fstream>
#include<cstring>

using namespace std;


enum Error_code {
	success, fail, ranger_error, underflow, overflow, fatal, not_present,
	duplicate_error, entry_inserted, entry_found, internal_error
};

struct  User {
	//data members
	string name;		//用户姓名
	string account;			//账号
	string id;				//身份证号
	string phone_num;			//电话号码
	double points;			//账户余额
	//string detail;			//交易明细
	User* next;	//指向后一个
	User* back;	//指向前一个
	//constructors
	User();
	User(string name, string account, string id, string phone_num, double points,
		User* link_next, User* link_back);
};


class PointsSystem {		//储蓄系统
public:
	PointsSystem();		//积分系统
	void showMenu();			//显示菜单
	Error_code openAccount();		//开户
	Error_code deletAccount();		//销户
	Error_code reviseAccount();		//修改用户信息
	Error_code savePoints();		//存入积分（根据消费金额不同进行等额积分存入）
	Error_code usePoints();		//使用积分(根据积分不同进行抵抗)
	Error_code display();			//显示账户信息
	Error_code showDetail();		//显示交易明细
	void quit();				//退出程序
	Error_code readData();	//读取数据
	Error_code saveData();	//保存数据
protected:
	mutable User* current;
	mutable int current_position;
	int count;
	void set_position(int position) const;
	bool AllisNum(string str);//检验字符串是否为数字
};