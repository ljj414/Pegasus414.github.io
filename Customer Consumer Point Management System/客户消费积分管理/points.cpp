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

PointsSystem::PointsSystem()	//��ʼ��
{
	count = 0;
	current = nullptr;
	current_position = -1;
}

void PointsSystem::showMenu()
{
	readData();		//�ȶ�ȡ�ļ��е�����
	cout << '\n' << "��������������˵�..." << endl;
	system("pause > nul");
	while (1) {
		system("cls");
		unsigned choice;
		cout << "**********�ͻ��������ѹ���ϵͳ**********" << endl;
		cout << "*             1.�˻�����              *" << endl;
		cout << "*             2.�˻�����              *" << endl;
		cout << "*             3.���ִ���              *" << endl;
		cout << "*             4.����ʹ��              *" << endl;
		cout << "*             5.��ѯ��Ϣ              *" << endl;
		cout << "*             6.�޸���Ϣ              *" << endl;
		cout << "*             7.������ϸ              *" << endl;
		cout << "*             8.�˳�ϵͳ              *" << endl;
		cout << "****************************************" << endl;
		cout << "��������Ҫִ�еĲ�����";
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
			default: {cout << "����Ƿ��ַ��������˻����˵���" << endl; break; }
		}
		cout << '\n' << "��������������˵�..." << endl;
		system("pause > nul");
	}
}

Error_code PointsSystem::openAccount()	//ͷ�巨
{
	char flag = 'Y';
	while (flag != 'n' && flag != 'N')
	{
		system("cls");
		cout << "**********�ͻ����ѿ���ϵͳ**********" << endl;
		string name;
		cout << "�����뿪�����ƣ�";
		cin >> name;
		while (name.length() <= 0) {
			cout << "�����������������룺";
			cin >> name;
		}

		string account;
		cout << "������6λ�����˺ţ�";
		cin >> account;
		while (1) {
			while (!AllisNum(account) || account.length() != 6) {
				cout << "������������������:";
				cin >> account;
			}
			User*& p = current;
			while (p != nullptr) {
				if (account == p->account)
				{
					cout << "���˺��Ѵ��ڣ����������룺" ;
					cin >> account;
					while (!AllisNum(account) || account.length() != 6) {
						cout << "������������������:";
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
		cout << "������18λ���֤�ţ�";
		cin >> id;
		while (!AllisNum(id) || id.length() != 18) {
			cout << "�����������������룺";
			cin >> id;
		}

		string phone_num;
		cout << "������11λ�绰���룺";
		cin >> phone_num;
		while (!AllisNum(phone_num) || phone_num.length() != 11) {
			cout << "�����������������룺";
			cin >> phone_num;
		}

		double points = 0;

		User* new_user, * preceding, * following;
		if (count == 0)
			following = NULL;		//ͷ�巨
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
		cout << "�����ɹ�" << endl;

		cout << "�Ƿ����������Y/N����";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::deletAccount()
{
	if (count == 0) {
		cout << "��ǰϵͳ�������˻�������" << endl;
		return success;
	}
	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		User* old_node = new User();
		old_node = current;
		User* neighbor;
		system("cls");
		cout << "**********�ͻ��˺�����ϵͳ**********" << endl;
		string account;
		cout << "���������˺ţ�";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6 ) {
				cout << "�����������������룺";
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
				cout << "�����ɹ���" << endl;
				break;
			}
			else if (old_node == nullptr) {
				cout << "���޴��ˣ�����" << endl;
				break;
			}
			else old_node = old_node->next;
		}
		old_node = nullptr;
		delete  old_node;		//�ͷ��ڴ�
		count--;
		cout << '\n' << "�Ƿ����������Y/N����";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::reviseAccount()
{
	if (count == 0) {
		cout << "��ǰϵͳ�������˻�������" << endl;
		return success;
	}

	int key;
	string new_name, new_id, new_phone_num;
	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		User* p = new User();	//�½�ָ��p��currentָ����ͬ
		p = current;
		system("cls");
		cout << "**********�ͻ���Ϣ�޸�ϵͳ**********" << endl;
		string account;
		cout << "����ͻ��˺ţ�";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6) {
			cout << "�����������������룺";
			cin >> account;
		}
		while (1) {
			if (p != nullptr && account == p->account) {
				cout << "ԭ�ͻ�������" << p->name << endl;
				cout << "������Ҫ�޸ĵ���Ϣ��1-������2-���֤�ţ�3-�绰���룩��";
				cin >> key;
				while (key <= 0 || key >= 4) {
					cout << "�����������������룺";
					cin >> key;
				}
				switch (key) {
				case 1:
				{
					cout << "�����µĿͻ�������";
					cin >> new_name;
					while (new_name.length() <= 0) {
						cout << "�����������������룺";
						cin >> new_name;
					}
					p->name = new_name;
					cout << "�����޸ĳɹ���" << endl;
				}
				break;

				case 2:
				{
					cout << "ԭ�ͻ����֤�ţ�" << p->id << endl;
					cout << "�����µĿͻ����֤�ţ�";
					cin >> new_id;
					while (!AllisNum(new_id) || new_id.length() != 18) {
						cout << "�����������������룺";
						cin >> new_id;
					}
					p->id = new_id;
					cout << "���֤���޸ĳɹ���" << endl;
				}
				break;

				case 3:
				{
					cout << "ԭ�ͻ��绰���룺" << p->phone_num << endl;
					cout << "�����µĿͻ��绰���룺";
					cin >> new_phone_num;
					while (!AllisNum(new_phone_num) || new_phone_num.length() != 11) {
						cout << "�����������������룺";
						cin >> new_phone_num;
					}
					p->phone_num = new_phone_num;
					cout << "�绰�����޸ĳɹ���" << endl;
				}
				break;

				}
				break;
			}
			else if (p == nullptr) {
				cout << "���޴��ˣ�����" << endl;
				break;
			}
			else p = p->next;
		}
		p = nullptr;		//��ָ��ָ�����
		delete p;		//�ͷ��ڴ�
		cout << '\n' << "�Ƿ�����޸ģ�Y/N����";
		cin >> flag;
	}
}

Error_code PointsSystem::savePoints()
{
	if (count == 0) {
		cout << "��ǰϵͳ�������˻�������" << endl;
		return success;
	}

	SYSTEMTIME st;		//��ȡ��ǰϵͳʱ��
	GetLocalTime(&st);

	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		User* p = new User();	//�½�ָ��p��currentָ����ͬ
		p = current;
		system("cls");
		cout << "**********�ͻ����ִ洢ϵͳ**********" << endl;
		string account;
		cout << "����ͻ��˺ţ�";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6) {
				cout << "�����������������룺";
				cin >> account;
		}
		while (1) {
			if (p != nullptr && account == p->account) {
				double amount;
				double new_points;
				cout << "�ͻ�������" << p->name << endl;
				cout << '\n' << "���������ѽ�";
				cin >> amount;
				while (amount <= 0) {
					cout << "��������������������ȷ�����ѽ�";
					cin >> amount;
				}
				if (amount <= 50) {//������ʮԪ�����£�ÿ������1Ԫ���0.8����
					new_points = 0.8*amount;		
				}
				else if (amount > 50 && amount <= 100) {//��������ʮԪ��һ��Ԫ֮�䣬ÿ������1Ԫ���1����
					new_points = 40 + (amount-50);	
				}
				else if (amount > 100) {//������һ��Ԫ���ϣ�ÿ������1Ԫ���1.1�۷�
					new_points = 90 + 1.1 *(amount - 100);
				}
				cout << "���ִ���ɹ���" << endl;
				p->points += new_points;
				//��ϸ�ļ�д��
				ofstream outfile("pointsdetail.txt", ios::out | ios::app);	//��β��д��
				if (!outfile.is_open())
				{
					cout << "�޷����ļ�����" << endl;
					exit(0);
				}
				else cout << "�ļ��򿪳ɹ�" << endl;
				outfile << p->account << '\t' << "�������" << '\t'
					<< st.wYear << "-" << st.wMonth << "-" << st.wDay
					<< " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << '\t'
					<< new_points << endl;
				cout << "��ϸ�ɹ�����" << endl;

				break;
			}
			else if (p == nullptr) {
				cout << "���޴��ˣ�����" << endl;
				break;
			}
			else p = p->next;
		}
		p = nullptr;		//��ָ��ָ�����
		delete p;		//�ͷ��ڴ�
		cout << '\n' << "�Ƿ����������֣�Y/N����";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::usePoints()
{
	if (count == 0) {
		cout << "��ǰϵͳ�������˻�������" << endl;
		return success;
	}

	SYSTEMTIME st;		//��ȡ��ǰϵͳʱ��
	GetLocalTime(&st);
	char flag = 'Y';
	char key ;
	double amount;
	double new_points;
	while (flag != 'n' && flag != 'N') {
		User* p = new User();	//�½�ָ��p��currentָ����ͬ
		p = current;
		system("cls");
		cout << "**********�ͻ�����ʹ��ϵͳ**********" << endl;
		string account;
		cout << "����ͻ��˺ţ�";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6) {
				cout << "�����������������룺";
				cin >> account;
		}
		while (1) {
			if (p != nullptr && account == p->account) {
				cout << "�ͻ�������" << p->name << endl;
				cout << '\n' << "���������ѽ�";
				cin >> amount;
				while (amount <= 0) {
					cout << "��������������������ȷ�����ѽ�";
					cin >> amount;
				}
				cout << "����ʹ�û���������";
				cin >> new_points;
				while (new_points <= 0) {
					cout << "��������������������ȷ�Ļ���������";
					cin >> new_points;
					}
				while (p->points < new_points) {
					cout << "�������㣬������������ȷ�Ļ���������";
					cin >> new_points;
				}
				amount = amount - 0.1 * new_points;	//ÿʮ���ֿɵֿ�һԪǮ
				cout << "�ֿ۳ɹ���ʵ�����Ϊ��"<< amount << endl;
				p->points -= new_points;
				//��ϸ�ļ�д��
				ofstream outfile("pointsdetail.txt", ios::out | ios::app);	//��β��д��
				if (!outfile.is_open())
				{
					cout << "�޷����ļ�����" << endl;
					exit(0);
				}
				else cout << "�ļ��򿪳ɹ�" << endl;
				outfile << p->account << '\t' << "ʹ�û���" << '\t'
					<< st.wYear << "-" << st.wMonth << "-" << st.wDay
					<< " " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << '\t'
					<< new_points << endl;
				cout << "��ϸ�ɹ�����" << endl;

				break;
			}
			else if (p == nullptr) {
				cout << "���޴��ˣ�����" << endl;
				break;
			}
			else p = p->next;
		}
		p = nullptr;		//��ָ��ָ�����
		delete p;		//�ͷ��ڴ�
		cout << '\n' << "�Ƿ�������ѣ�Y/N����";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::display()
{
	if (count == 0) {
		cout << "��ǰϵͳ�������˻�������" << endl;
		return success;
	}

	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		User* p = new User();	//�½�ָ��p��currentָ����ͬ
		p = current;
		system("cls");
		cout << "**********�ͻ����ֲ�ѯϵͳ**********" << endl;
		string account;
		cout << "�����ѯ�˺ţ�";
		cin >> account;
		while (!AllisNum(account) || account.length() != 6) {
				cout << "�����������������룺";
				cin >> account;
		}
		while (1) {
			if (p != nullptr && account == p->account) {
				cout << '\n' << "���˺���ϸ��Ϣ���£�" << endl;
				cout << "�û����ƣ�" << p->name << endl;
				cout << "�û��˺ţ�" << p->account << endl;
				cout << "���֤�ţ�" << p->id << endl;
				cout << "�绰���룺" << p->phone_num << endl;
				cout << "������" << p->points << endl;
				break;
			}
			else if (p == nullptr) {
				cout << "���޴��ˣ�����" << endl;
				break;
			}
			else p = p->next;
		}
		p = nullptr;		//��ָ��ָ�����
		delete p;		//�ͷ��ڴ�
		cout << '\n' << "�Ƿ������ѯ��Y/N����";
		cin >> flag;
	}
	return success;
}

Error_code PointsSystem::showDetail()
{
	if (count == 0) {
		cout << "��ǰϵͳ�������˻�������" << endl;
		return success;
	}

	char s[100];
	string old_account;
	double points_detail;
	string str1, str2, str3;

	char flag = 'Y';
	while (flag != 'n' && flag != 'N') {
		system("cls");
		cout << "**********�ͻ�������ϸ��ѯϵͳ**********" << endl;
		ifstream infile("pointsdetail.txt", ios::in | ios::beg);
		if (!infile.is_open())
		{
			cout << "�޷����ļ�����" << endl;
			exit(0);
		}
		else cout << "�ļ��򿪳ɹ�" << endl;
		infile.getline(s, 100);		//��ȡ���ⲻ����

		string new_account;
		cout << "�����ѯ�˺ţ�";
		cin >> new_account;
		while (!AllisNum(new_account) || new_account.length() != 6) {
				cout << "�����������������룺";
				cin >> new_account;
		}
		cout << '\n' << "��������         " << "ʱ��        " << "���� " << endl;
		while (!infile.eof()) {
			infile >> old_account >> str1 >> str2 >> str3 >> points_detail;
			if (old_account == new_account) {
				cout << str1 << " " << str2 << " " << str3 << " " << points_detail << endl;
			}

			infile.get();
			if (infile.peek() == '\n')break;		//������һ���ظ���ȡ
		}
		infile.close();
		cout << '\n' << "�Ƿ������ѯ��Y/N����";
		cin >> flag;
	}

	return success;
}

void PointsSystem::quit()
{
	cout << "�������н������˳�����ϵͳ������" << endl;
	saveData();
	exit(0);
}

Error_code PointsSystem::readData()
{
	char s[100];
	string name;		//�ͻ�����
	string account;			//�˺�
	string id;				//���֤��
	string phone_num;			//�绰����
	double points;			//�������


	ifstream infile("usersdata.txt", ios::in | ios::beg);
	if (!infile.is_open())
	{
		cout << "�޷����ļ�����" << endl;
		exit(0);
	}
	else cout << "�ļ��򿪳ɹ�" << endl;
	infile.getline(s, 100);	//��ȡ���ⲻ����
	while (!infile.eof()) {
		infile >> name >> account >> id >> phone_num >> points;

		User* new_user, * preceding, * following;
		if (count == 0)
			following = NULL;		//ͷ�巨
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
		if (infile.peek() == '\n')break;		//������һ���ظ���ȡ
	}

	infile.close();
	cout << '\n' << "�ļ���ȡ�ɹ�" << endl;

	return success;
}

Error_code PointsSystem::saveData()
{
	ofstream outfile("usersdata.txt", ios::out);
	if (!outfile.is_open())
	{
		cout << "�޷����ļ�����" << endl;
		exit(0);
	}
	else cout << "�ļ��򿪳ɹ�" << endl;
	set_position(0);
	User* p = new User();
	p = current;
	outfile << "����" << "            " << "�˺�" << "                 " << "���֤��" << "                             " <<
		"�绰����" << "           " << "����" << endl;
	while (p) {
		outfile << p->name << '\t' << p->account << '\t' << p->id << '\t'
			<< p->phone_num << '\t' << p->points << endl;
		p = p->next;
	}
	outfile.close();
	p = nullptr;
	delete p;
	cout << "�ļ��ɹ�����" << endl;
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