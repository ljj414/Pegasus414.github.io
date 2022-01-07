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
	string name;		//�û�����
	string account;			//�˺�
	string id;				//���֤��
	string phone_num;			//�绰����
	double points;			//�˻����
	//string detail;			//������ϸ
	User* next;	//ָ���һ��
	User* back;	//ָ��ǰһ��
	//constructors
	User();
	User(string name, string account, string id, string phone_num, double points,
		User* link_next, User* link_back);
};


class PointsSystem {		//����ϵͳ
public:
	PointsSystem();		//����ϵͳ
	void showMenu();			//��ʾ�˵�
	Error_code openAccount();		//����
	Error_code deletAccount();		//����
	Error_code reviseAccount();		//�޸��û���Ϣ
	Error_code savePoints();		//������֣��������ѽ�ͬ���еȶ���ִ��룩
	Error_code usePoints();		//ʹ�û���(���ݻ��ֲ�ͬ���еֿ�)
	Error_code display();			//��ʾ�˻���Ϣ
	Error_code showDetail();		//��ʾ������ϸ
	void quit();				//�˳�����
	Error_code readData();	//��ȡ����
	Error_code saveData();	//��������
protected:
	mutable User* current;
	mutable int current_position;
	int count;
	void set_position(int position) const;
	bool AllisNum(string str);//�����ַ����Ƿ�Ϊ����
};