#include"points.h"

User::User()
{
	next = back = nullptr;
}

User::User(string name, string account, string id, string phone_num, double points,
	User* link_next, User* link_back)
{
	this->name = name;
	this->account = account;
	this->id = id;
	this->phone_num = phone_num;
	this->points = points;
	next = link_next;
	back = link_back;
}

PointsSystem::PointsSystem()	//初始化
{
	count = 0;
	current = nullptr;
	current_position = -1;
}

void PointsSystem::showMenu()
{
	readData();		//先读取文件中的数据
	cout << '\n' << "按任意键进入主菜单..." << endl;
	system("pause > nul");
	while (1) {
		system("cls");
		unsigned choice;
		cout << "**********客户积分消费管理系统**********" << endl;
		cout << "*             1.账户开户              *" << endl;
		cout << "*             2.账户销户              *" << endl;
		cout << "*             3.积分存入              *" << endl;
		cout << "*             4.积分使用              *" << endl;
		cout << "*             5.查询信息              *" << endl;
		cout << "*             6.修改信息              *" << endl;
		cout << "*             7.交易明细              *" << endl;
		cout << "*             8.退出系统              *" << endl;
		cout << "****************************************" << endl;
		cout << "请输入您要执行的操作：";
		cin >> choice;
		switch (choice) {
			case 1:openAccount(); break;
			case 2:deletAccount(); break;
			case 3:savePoints(); break;
			case 4:usePoints(); break;
			case 5:display(); break;
			case 6:reviseAccount(); break;
			case 7:showDetail(); break;
			case 8:quit(); break;
			default: {cout << "输入非法字符！即将退回主菜单！" << endl; break; }
		}
		cout << '\n' << "按任意键返回主菜单..." << endl;
		system("pause > nul");
	}
}

Error_code PointsSystem::openAccount()	//头插法
{
	char flag = 'Y';
	while (flag != 'n' && flag != 'N')
	{
		system("cls");
		cout << "**********客户消费开户系统**********" << endl;
		string name;
		cout << "请输入开户名称：";
		cin >> name;
		while (name.length() <= 0) {
			cout << "输入有误，请重新输入：";
			cin >> name;
		}

		string account;
		cout << "请输入6位开户账号：";
		cin >> account;
		while (1) {
			while (!AllisNum(account) || account.length() != 6) {
				cout << "输入有误，请重新输入:";
				cin >> account;
			}
			User*& p = current;
			while (p != nullptr) {
				if (account == p->account)
				{
					cout << "该账号已存在，请重新输入：" ;
					cin >> account;
					while (!AllisNum(account) || account.length() != 6) {
						cout << "输入有误，请重新输入:";
						cin >> account;
					}
					break;
				}
				else
					goto here;
				p = p->next;
			}
			here:break;
		}

		string id;
		cout << "请输入18位身份证号：";
		cin >> id;
		while (!AllisNum(id) || id.length() != 18) {
			cout << "输入有误，请重新输入：";
			cin >> id;
		}

		string phone_num;
		cout << "请输入11位电话号码：";
		cin >> phone_num;
		while (!AllisNum(phone_num) || phone_num.length() != 11) {
			cout << "输入有误，请重新输入：";
			cin >> phone_num;
		}

		double points = 0;

		User* new_user, * preceding, * following;
		if (count == 0)
			following = NULL;		//头插法
		else {
			set_position(0);
			following = current;
		}   preceding = NULL;

		new_user = new User(name, account, id, phone_num, points, following, preceding);
		if (new_user == nullptr)return overflow;
		if (preceding != nullptr)preceding->next = new_user;
		if (following != nullptr)following->back = new_user;

		current = new_user;
		current_position = 0;
		count++;
		cout << "开户成功" << endl;

		cout << "是否继续开户（Y/N）：";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::deletAccount()
{
	if (count == 0) {
		cout << "当前系统中暂无账户！！！" << endl;
		return success;
	}
	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		User* old_node = new User();
		old_node = current;
		User* neighbor;
		system("cls");
		cout << "**********客户账号销户系统**********" << endl;
		string account;
		cout << "输入销户账号：";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6 ) {
				cout << "输入有误，请重新输入：";
				cin >> account;
		}
		while (1) {
			if (old_node != nullptr && account == old_node->account) {
				if (neighbor = old_node->back) neighbor->next = old_node->next;
				else if (neighbor = old_node->next) {
					neighbor->back = old_node->back;
					old_node = neighbor;
				}
				else {
					old_node = old_node->back;
					current_position--;
				}
				cout << "销户成功！" << endl;
				break;
			}
			else if (old_node == nullptr) {
				cout << "查无此人！！！" << endl;
				break;
			}
			else old_node = old_node->next;
		}
		old_node = nullptr;
		delete  old_node;		//释放内存
		count--;
		cout << '\n' << "是否继续销户（Y/N）：";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::reviseAccount()
{
	if (count == 0) {
		cout << "当前系统中暂无账户！！！" << endl;
		return success;
	}

	int key;
	string new_name, new_id, new_phone_num;
	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		User* p = new User();	//新建指针p与current指向相同
		p = current;
		system("cls");
		cout << "**********客户信息修改系统**********" << endl;
		string account;
		cout << "输入客户账号：";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6) {
			cout << "输入有误，请重新输入：";
			cin >> account;
		}
		while (1) {
			if (p != nullptr && account == p->account) {
				cout << "原客户姓名：" << p->name << endl;
				cout << "请输入要修改的信息（1-姓名，2-身份证号，3-电话号码）：";
				cin >> key;
				while (key <= 0 || key >= 4) {
					cout << "输入有误，请重新输入：";
					cin >> key;
				}
				switch (key) {
				case 1:
				{
					cout << "输入新的客户姓名：";
					cin >> new_name;
					while (new_name.length() <= 0) {
						cout << "输入有误，请重新输入：";
						cin >> new_name;
					}
					p->name = new_name;
					cout << "姓名修改成功！" << endl;
				}
				break;

				case 2:
				{
					cout << "原客户身份证号：" << p->id << endl;
					cout << "输入新的客户身份证号：";
					cin >> new_id;
					while (!AllisNum(new_id) || new_id.length() != 18) {
						cout << "输入有误，请重新输入：";
						cin >> new_id;
					}
					p->id = new_id;
					cout << "身份证号修改成功！" << endl;
				}
				break;

				case 3:
				{
					cout << "原客户电话号码：" << p->phone_num << endl;
					cout << "输入新的客户电话号码：";
					cin >> new_phone_num;
					while (!AllisNum(new_phone_num) || new_phone_num.length() != 11) {
						cout << "输入有误，请重新输入：";
						cin >> new_phone_num;
					}
					p->phone_num = new_phone_num;
					cout << "电话号码修改成功！" << endl;
				}
				break;

				}
				break;
			}
			else if (p == nullptr) {
				cout << "查无此人！！！" << endl;
				break;
			}
			else p = p->next;
		}
		p = nullptr;		//让指针指向空域
		delete p;		//释放内存
		cout << '\n' << "是否继续修改（Y/N）：";
		cin >> flag;
	}
}

Error_code PointsSystem::savePoints()
{
	if (count == 0) {
		cout << "当前系统中暂无账户！！！" << endl;
		return success;
	}

	SYSTEMTIME st;		//获取当前系统时间
	GetLocalTime(&st);

	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		User* p = new User();	//新建指针p与current指向相同
		p = current;
		system("cls");
		cout << "**********客户积分存储系统**********" << endl;
		string account;
		cout << "输入客户账号：";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6) {
				cout << "输入有误，请重新输入：";
				cin >> account;
		}
		while (1) {
			if (p != nullptr && account == p->account) {
				double amount;
				double new_points;
				cout << "客户姓名：" << p->name << endl;
				cout << '\n' << "请输入消费金额：";
				cin >> amount;
				while (amount <= 0) {
					cout << "输入有误，请重新输入正确的消费金额：";
					cin >> amount;
				}
				if (amount <= 50) {//消费五十元及以下，每多消费1元获得0.8积分
					new_points = 0.8*amount;		
				}
				else if (amount > 50 && amount <= 100) {//消费在五十元至一百元之间，每多消费1元获得1积分
					new_points = 40 + (amount-50);	
				}
				else if (amount > 100) {//消费在一百元以上，每多消费1元获得1.1扣分
					new_points = 90 + 1.1 *(amount - 100);
				}
				cout << "积分存入成功！" << endl;
				p->points += new_points;
				//明细文件写入
				ofstream outfile("pointsdetail.txt", ios::out | ios::app);	//从尾部写入
				if (!outfile.is_open())
				{
					cout << "无法打开文件！！" << endl;
					exit(0);
				}
				else cout << "文件打开成功" << endl;
				outfile << p->account << '\t' << "存入积分" << '\t'
					<< st.wYear << "-" << st.wMonth << "-" << st.wDay
					<< " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << '\t'
					<< new_points << endl;
				cout << "明细成功保存" << endl;

				break;
			}
			else if (p == nullptr) {
				cout << "查无此人！！！" << endl;
				break;
			}
			else p = p->next;
		}
		p = nullptr;		//让指针指向空域
		delete p;		//释放内存
		cout << '\n' << "是否继续存入积分（Y/N）：";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::usePoints()
{
	if (count == 0) {
		cout << "当前系统中暂无账户！！！" << endl;
		return success;
	}

	SYSTEMTIME st;		//获取当前系统时间
	GetLocalTime(&st);
	char flag = 'Y';
	char key ;
	double amount;
	double new_points;
	while (flag != 'n' && flag != 'N') {
		User* p = new User();	//新建指针p与current指向相同
		p = current;
		system("cls");
		cout << "**********客户积分使用系统**********" << endl;
		string account;
		cout << "输入客户账号：";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6) {
				cout << "输入有误，请重新输入：";
				cin >> account;
		}
		while (1) {
			if (p != nullptr && account == p->account) {
				cout << "客户姓名：" << p->name << endl;
				cout << '\n' << "请输入消费金额：";
				cin >> amount;
				while (amount <= 0) {
					cout << "输入有误，请重新输入正确的消费金额：";
					cin >> amount;
				}
				cout << "输入使用积分数量：";
				cin >> new_points;
				while (new_points <= 0) {
					cout << "输入有误，请重新输入正确的积分数量：";
					cin >> new_points;
					}
				while (p->points < new_points) {
					cout << "积分余额不足，请重新输入正确的积分数量：";
					cin >> new_points;
				}
				amount = amount - 0.1 * new_points;	//每十积分可抵扣一元钱
				cout << "抵扣成功！实付金额为："<< amount << endl;
				p->points -= new_points;
				//明细文件写入
				ofstream outfile("pointsdetail.txt", ios::out | ios::app);	//从尾部写入
				if (!outfile.is_open())
				{
					cout << "无法打开文件！！" << endl;
					exit(0);
				}
				else cout << "文件打开成功" << endl;
				outfile << p->account << '\t' << "使用积分" << '\t'
					<< st.wYear << "-" << st.wMonth << "-" << st.wDay
					<< " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << '\t'
					<< new_points << endl;
				cout << "明细成功保存" << endl;

				break;
			}
			else if (p == nullptr) {
				cout << "查无此人！！！" << endl;
				break;
			}
			else p = p->next;
		}
		p = nullptr;		//让指针指向空域
		delete p;		//释放内存
		cout << '\n' << "是否继续消费（Y/N）：";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::display()
{
	if (count == 0) {
		cout << "当前系统中暂无账户！！！" << endl;
		return success;
	}

	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		User* p = new User();	//新建指针p与current指向相同
		p = current;
		system("cls");
		cout << "**********客户积分查询系统**********" << endl;
		string account;
		cout << "输入查询账号：";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6) {
				cout << "输入有误，请重新输入：";
				cin >> account;
		}
		while (1) {
			if (p != nullptr && account == p->account) {
				cout << '\n' << "该账号详细信息如下：" << endl;
				cout << "用户名称：" << p->name << endl;
				cout << "用户账号：" << p->account << endl;
				cout << "身份证号：" << p->id << endl;
				cout << "电话号码：" << p->phone_num << endl;
				cout << "积分余额：" << p->points << endl;
				break;
			}
			else if (p == nullptr) {
				cout << "查无此人！！！" << endl;
				break;
			}
			else p = p->next;
		}
		p = nullptr;		//让指针指向空域
		delete p;		//释放内存
		cout << '\n' << "是否继续查询（Y/N）：";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::showDetail()
{
	if (count == 0) {
		cout << "当前系统中暂无账户！！！" << endl;
		return success;
	}

	char s[100];
	string old_account;
	double points_detail;
	string str1, str2, str3;

	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		system("cls");
		cout << "**********客户积分明细查询系统**********" << endl;
		ifstream infile("pointsdetail.txt", ios::in | ios::beg);
		if (!infile.is_open())
		{
			cout << "无法打开文件！！" << endl;
			exit(0);
		}
		else cout << "文件打开成功" << endl;
		infile.getline(s, 100);		//读取标题不计入

		string new_account;
		cout << "输入查询账号：";
		cin >> new_account;
		while (!AllisNum(new_account) || new_account.length() != 6) {
				cout << "输入有误，请重新输入：";
				cin >> new_account;
		}
		cout << '\n' << "交易类型         " << "时间        " << "积分 " << endl;
		while (!infile.eof()) {
			infile >> old_account >> str1 >> str2 >> str3 >> points_detail;
			if (old_account == new_account) {
				cout << str1 << " " << str2 << " " << str3 << " " << points_detail << endl;
			}

			infile.get();
			if (infile.peek() == '\n')break;		//解决最后一行重复读取
		}
		infile.close();
		cout << '\n' << "是否继续查询（Y/N）：";
		cin >> flag;
	}

	return success;
}

void PointsSystem::quit()
{
	cout << "程序运行结束，退出管理系统！！！" << endl;
	saveData();
	exit(0);
}

Error_code PointsSystem::readData()
{
	char s[100];
	string name;		//客户姓名
	string account;			//账号
	string id;				//身份证号
	string phone_num;			//电话号码
	double points;			//积分余额


	ifstream infile("usersdata.txt", ios::in | ios::beg);
	if (!infile.is_open())
	{
		cout << "无法打开文件！！" << endl;
		exit(0);
	}
	else cout << "文件打开成功" << endl;
	infile.getline(s, 100);	//读取标题不计入
	while (!infile.eof()) {
		infile >> name >> account >> id >> phone_num >> points;

		User* new_user, * preceding, * following;
		if (count == 0)
			following = NULL;		//头插法
		else {
			set_position(0);
			following = current;
		}   preceding = NULL;

		new_user = new User(name, account, id, phone_num, points, following, preceding);
		if (new_user == nullptr)return overflow;
		if (preceding != nullptr)preceding->next = new_user;
		if (following != nullptr)following->back = new_user;

		current = new_user;
		current_position = 0;
		count++;

		infile.get();
		if (infile.peek() == '\n')break;		//解决最后一行重复读取
	}

	infile.close();
	cout << '\n' << "文件读取成功" << endl;

	return success;
}

Error_code PointsSystem::saveData()
{
	ofstream outfile("usersdata.txt", ios::out);
	if (!outfile.is_open())
	{
		cout << "无法打开文件！！" << endl;
		exit(0);
	}
	else cout << "文件打开成功" << endl;
	set_position(0);
	User* p = new User();
	p = current;
	outfile << "姓名" << "            " << "账号" << "                 " << "身份证号" << "                             " <<
		"电话号码" << "           " << "积分" << endl;
	while (p) {
		outfile << p->name << '\t' << p->account << '\t' << p->id << '\t'
			<< p->phone_num << '\t' << p->points << endl;
		p = p->next;
	}
	outfile.close();
	p = nullptr;
	delete p;
	cout << "文件成功保存" << endl;
	return success;
}

void PointsSystem::set_position(int position) const
{
	if (current_position <= position)
		for (; current_position != position; current_position++)
			current = current->next;
	else
		for (; current_position != position; current_position--)
			current = current->back;
}

bool PointsSystem::AllisNum(string str) {
	for (int i = 0; i < str.size(); i++){
		int tmp = (int)str[i];
		if (tmp >= 48 && tmp <= 57){
			continue;
		}
		else{
			return false;
		}
	}
		return true;
}