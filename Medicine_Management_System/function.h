#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H

#include<iostream>
#include<string>
#include<cstdio>
#include"Menu.h"
#include"Array.h"
#include<cstdlib>

extern ArrayOfPersonnel array_of_personnel;             //�����ⲿ����
extern ArrayOfUser array_of_user;                       //�����ⲿ����
extern ArrayOfMedicine array_of_medicine;               //�����ⲿ����

using std::cout;
using std::cin;
using std::wcin;
using std::endl;
using std::string;
using std::system;

void Function_Personnel_Menu_Sub();                     //��Ա����˵����Ӳ˵�
void Function_Main_Menu();                              //���˵�
void Function_Medicine_Management_Menu();               //������˵�
void Function_Login_Menu();                             //��¼�˵�

void Add_input_personnel();                             //���Personnel�Ĺ��ܺ���
void Delete_input_personnel();                          //ɾ��Personnel�Ĺ��ܺ���
void Show_all_input_personnel();                        //��ѯ����Personnel�Ĺ��ܺ���
void Show_input_personnel();                            //��ѯPersonnel�Ĺ��ܺ���

void Add_input_medicine();                              //ҩƷ���Ĺ��ܺ���
void Add_output_medicine();								//ҩƷ����Ĺ��ܺ���
void Show_input_medicine();                             //ҩƷ��ѯ�Ĺ��ܺ���
void Show_all_input_medicine();                         //��ѯ����ҩƷ�Ĺ��ܺ���

void wflush();											// ˢ�»�����


														// �˵�ʵ��
void Function_Personnel_Menu()                          //��Ա����˵��Ĺ���ʵ��
{
	system("cls");
	Person_Menu();                                      //���˵��Ľ���
	int temp;
	cin >> temp;
	if (temp >= 1 && temp <= 4)
	{
		switch (temp)
		{
		case 1: Function_Personnel_Menu_Sub(); break;   //��ת����Ա����˵����Ӳ˵�
		case 2: Function_Personnel_Menu_Sub(); break;   //��ת����Ա����˵����Ӳ˵�
		case 3: Function_Personnel_Menu_Sub(); break;   //��ת����Ա����˵����Ӳ˵�
		case 4:
			system("cls");
			Function_Main_Menu();                       //�������˵�
			break;
		}
	}
	else
	{
		cout << "Error!" << endl;
		system("pause");
		system("cls");
		Function_Personnel_Menu();                      //������Ա����˵�
	}
}

void Function_Personnel_Menu_Sub()                      //��Ա����˵����Ӳ˵��Ĺ���ʵ��
{
	system("cls");
	Person_Menu_1();                                    //��Ա����˵����Ӳ˵��Ľ���
	int temp;
	cin >> temp;
	if (temp >= 1 && temp <= 4)
	{
		switch (temp)
		{
		case 1: Show_input_personnel(); break;          //��ѯPersonnnel
		case 2: Add_input_personnel(); break;           //���Personnnel
		case 3: Delete_input_personnel(); break;        //ɾ��Personnnel
		case 4:
			system("cls");
			Function_Personnel_Menu();                  //������Ա����˵�
			break;
		}
	}
	else
	{
		cout << "Error!" << endl;
		system("pause");
		system("cls");
		Function_Personnel_Menu_Sub();                  //������Ա����˵����Ӳ˵�
	}
}

void Function_Main_Menu()                               //���˵��Ĺ���ʵ��
{
	system("cls");
	if (array_of_personnel.getCurrentUser() == NO_USERS)
	{
		Function_Login_Menu();                          //���ص�¼����
	}
	MainMenu();                                         //���˵��Ľ���
	int temp;
	cin >> temp;
	if (temp >= 1 && temp <= 3)
	{
		switch (temp)
		{
		case 1:Function_Medicine_Management_Menu(); break;     //������
		case 2:Function_Personnel_Menu(); break;        //��Ա����
		case 3:array_of_user.login(NO_USERS); Function_Login_Menu(); break;
														//ע���û�
		}
	}
	else
	{
		cout << "Error!" << endl;
		system("pause");
		Function_Main_Menu();                           //�������˵�
	}
}
// User��ع��ܺ���ʵ�ְ���������
void Function_Login_Menu()                              //��¼����Ĺ���ʵ��
{
	system("cls");
	Login_Menu();                                       //��¼����
	int login_select;
	cin >> login_select;
	if (login_select >= 1 && login_select <= 3)
	{
		string account;
		string password;
		int authority;
		bool is_successfully_login = false;
		bool is_account_found = false;
		bool is_password_correct = false;

		switch (login_select)
		{
		case 1:
			if (array_of_user.calNumberOfUser() == 0)
			{
				cout << "Ŀǰϵͳ�л�û���˻����봴���˻�����в�����" << endl;
				cout << "ע�⣺������ϵͳ����Ա�˻����ܴ�����ͨ�˻���������ϵ����Ա����ϵͳ����Ա�˻���" << endl;
				cout << endl << "--ע���˻�--" << endl;
				cout << "�û����� ";
				wflush();
				getline(cin, account);
				cout << "���룺 ";
				getline(cin, password);
				cout << "�˻�����(<1>ϵͳ����Ա <2>������Ա <3>�ֿ������Ա): ";
				cin >> authority;
				while (authority != 1)
				{
					while (!(authority >= 1 && authority <= 3))
						//��ֹ���������˻����ͱ��
					{
						cout << "�����������������롣" << endl;
						cout << "�˻�����(<1>ϵͳ����Ա <2>������Ա <3>�ֿ������Ա): ";
						cin >> authority;
					}
					cout << "�����ȴ���ϵͳ����Ա�˻���" << endl;
					cout << "�˻�����(<1>ϵͳ����Ա <2>������Ա <3>�ֿ������Ա): ";
					cin >> authority;
				}

				switch (authority)
				{
				case 1:
					authority = IS_ADMIN;               //�����ϵͳ����Ա
					break;

				case 2:
					authority = IS_MANAGER;             //�����������Ա
					break;

				case 3:
					authority = IS_WAREHOUSE;           //����ǿ�������Ա
					break;
				}

				array_of_user.Add(authority, array_of_user.calNumberOfUser() + 1, account, password);

				system("pause");
				Function_Login_Menu();                  //��ת�����˵�
			}

			while (!is_successfully_login)
			{
				cout << endl << "--��½�˻�--" << endl;
				cout << "�û����� ";
				wflush();
				getline(cin, account);
				cout << "���룺 ";
				getline(cin, password);

				for (int i = 0; i < array_of_user.calNumberOfUser(); i++)
				{
					if (array_of_user.user[i].account == account)
					{
						is_account_found = true;
						cout << "--���ҵ��˻����������...--" << endl;
						if (array_of_user.user[i].password == password)
						{
							array_of_user.user[i].is_login = true;
							Array::login(array_of_user.user[i].authority);
							is_password_correct = true;
							is_successfully_login = true;
							cout << "--��֤ͨ������ӭ��½��--" << endl << endl;
							system("pause");
							Function_Main_Menu();       //��ת�����˵�
							break;
						}
						else
						{
							cout << "--��������������������������롣--" << endl;
							is_successfully_login = false;
							is_password_correct = false;
							break;
						}
					}
				}
				if (is_account_found != true)
				{
					cout << "--������δ�ҵ����˻������������Ƿ�����--" << endl;
				}
			}
			break;

		case 2:
			cout << "--ע���˻�--" << endl;
			cout << "�û����� ";
			wflush();
			getline(cin, account);
			cout << "���룺 ";
			getline(cin, password);
			cout << "�˻�����(<1>ϵͳ����Ա <2>������Ա <3>�ֿ������Ա): ";
			cin >> authority;
			while (authority == 1 && array_of_user.admin_existed)
			{
				while (!(authority >= 1 && authority <= 3))
				{
					cout << "--�����������������������롣--" << endl;
					cout << "�˻�����(<1>ϵͳ����Ա <2>������Ա <3>�ֿ������Ա): ";
					cin >> authority;
				}
				cout << "--(���ش���ϵͳ����Ա�˻��Ѿ����ڣ���������ֹ--" << endl;
				cout << "�˻�����(<1>ϵͳ����Ա <2>������Ա <3>�ֿ������Ա): ";
				cin >> authority;
			}


			switch (authority)
			{
			case 1:
				authority = IS_ADMIN;                   //�����ϵͳ����Ա
				break;

			case 2:
				authority = IS_MANAGER;                 //�����������Ա
				break;

			case 3:
				authority = IS_WAREHOUSE;               //����ǿ�������Ա
				break;
			}

			array_of_user.Add(authority, array_of_user.calNumberOfUser() + 1, account, password);

			system("pause");

			Function_Login_Menu();                      //���ص�¼����
			break;

		case 3:
			char type;
			cout << "��ȷ���˳���(Y/N)" << endl;
			cin >> type;
			if (type == 'Y' || type == 'y')
			{
				exit(0);
			}
			else
			{
				setbuf(stdin, NULL);
				Function_Login_Menu();
			}
			break;
		}
	}
}

void Function_Medicine_Management_Menu()                //������˵��Ĺ���ʵ��
{
	system("cls");
	Medicine_Management_Menu();                         //������˵��Ľ���
	int temp;
	cin >> temp;
	if (temp >= 1 && temp <= 4)
	{
		switch (temp)
		{
		case 1:                                         //ҩƷ���
			Add_input_medicine();
			break;

		case 2:                                         //ҩƷ����
			Add_output_medicine();
			break;

		case 3:                                         //����ѯ
			Show_input_medicine();
			break;

		case 4:Function_Main_Menu();                    //�������˵�
			break;
		}
	}
	else
	{
		cout << "Error!" << endl;
		system("pause");
		Function_Medicine_Management_Menu();            //���ؿ�����˵�
	}
}
//

// Personnel��ع��ܺ���ʵ��
void Add_input_personnel()                              //���Personnel�Ĺ���ʵ��
{
	int age;
	string name;
	int number;
	int authority;

	cout << "���: ";
	cin >> number;
	cout << "����: ";
	wflush();
	getline(cin, name);
	cout << "����: ";
	cin >> age;
	cout << "������������(<1>Ա�� <2>�˿� <3>������): ";
	cout << "���: ";
	cin >> authority;

	if (authority != 1 && authority != 2 && authority != 3)
	{
		cout << "Error!" << endl;
		system("pause");
		Function_Personnel_Menu_Sub();                  //������Ա����˵����Ӳ˵�
	}

	switch (authority)
	{
	case 1:
		authority = STAFF;                              //�����Ա��
		break;
	case 2:
		authority = CUSTOMER;                           //����ǹ˿�
		break;
	case 3:
		authority = VENDOR;                             //����ǹ�����
		break;
	}

	array_of_personnel.Add(number, name, age, authority);

	system("pause");
	Function_Personnel_Menu_Sub();                      //������Ա����˵����Ӳ˵�
}

void Show_all_input_personnel()                         //��ѯ��������Ϣ�Ĺ���ʵ��
{
	array_of_personnel.ShowAllPersonnel();
	system("pause");
}

void Show_input_personnel()                             //��ѯPersonnel�Ĺ���ʵ��
{
	string  temp;

	cout << "�����ѯ������Ϣ��������ALL���������ִ�Сд��" << endl;
	cout << "���: ";
	cin >> temp;

	if (temp == "ALL" || temp == "all")
	{
		Show_all_input_personnel();                     //���ò�ѯ��������Ϣ�Ĺ��ܺ���
	}
	else
	{
		int number;
		number = atoi(temp.c_str());                            //��stringת����int��
		int index = array_of_personnel.FindIndex(number);
		//���ձ�Ų��±�
		array_of_personnel.Show(index, SHOW_TITLES);
		system("pause");
	}
	Function_Personnel_Menu_Sub();                      //������Ա����˵����Ӳ˵�
}

void Delete_input_personnel()                           //ɾ��Personnel�Ĺ���ʵ��
{
	cout << "--��ǰ��Ա��Ϣ�����--" << endl << endl;

	array_of_personnel.ShowAllPersonnel();

	int number;
	cout << "���: ";
	cin >> number;
	int index = array_of_personnel.FindIndex(number);   //���ձ�Ų��±�
	array_of_personnel.Delete(index);
	system("pause");
	Function_Personnel_Menu_Sub();                      //������Ա����˵����Ӳ˵�
}
//

// Medicine��ع��ܺ���ʵ��
void Show_all_input_medicine()                          //��ѯ����ҩƷ�Ĺ���ʵ��
{
	array_of_medicine.ShowAllMedicine();
	system("pause");
}

void Show_input_medicine()                              //��ѯҩƷ�Ĺ���ʵ��
{
	string  temp;

	cout << "�����ѯ������Ϣ��������ALL���������ִ�Сд��" << endl;
	cout << "���: ";
	cin >> temp;

	if (temp == "ALL" || temp == "all")
	{
		Show_all_input_medicine();
	}
	else
	{
		int number;
		number = atoi(temp.c_str());
		int index = array_of_medicine.FindIndex(number);
		array_of_medicine.Show(index, SHOW_TITLES);
		system("pause");
	}
	Function_Medicine_Management_Menu();                //������Ա����˵����Ӳ˵�
}

void Add_input_medicine()                               //���ҩƷ�Ĺ���ʵ��
{
	string name;
	int number;
	int amount;
	double price;

	cout << "--��ǰҩƷ��������--" << endl << endl;
	array_of_medicine.ShowAllMedicine();
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	cout << "ҩƷ���� ";
	wflush();
	getline(cin, name);
	cout << "ҩƷ��ţ� ";
	cin >> number;
	cout << "������ ";
	cin >> amount;
	cout << "�۸� ";
	cin >> price;

	array_of_medicine.Add(number, name, amount, price);

	system("pause");
	Function_Medicine_Management_Menu();
}

void Add_output_medicine()
{
	string name;
	int number;
	int amount;
	int old_authority;
	double price;
	int index;
	bool judge = false;

	cout << "--��ǰҩƷ��������--" << endl << endl;
	array_of_medicine.ShowAllMedicine();
	cout << "--------------------------------------------------------------------------------" << endl << endl;

	cout << "ҩƷ��ţ� ";
	cin >> number;
	judge = array_of_medicine.catchError(array_of_medicine.checkFormat(number, IGNORE));
	if (judge == true)
	{
		index = array_of_medicine.FindIndex(number);
		cout << "�������� ";
		cin >> amount;
		name = array_of_medicine.medicine[index].getName();
		price = array_of_medicine.medicine[index].getPrice();

		old_authority = array_of_user.getCurrentUser();
		array_of_user.login(IS_ADMIN);

		array_of_medicine.Add(number, name, -amount, price);

		array_of_user.login(old_authority);
	}

	system("pause");
	Function_Medicine_Management_Menu();
}

void wflush()
{
	wchar_t c;
	while (1)
	{
		c = wcin.get();
		if (c == EOF)
			break;
		else if (c == '\n')
			break;
		else if (c == NULL)
			break;
	}
}

#endif // FUNCTION_H
