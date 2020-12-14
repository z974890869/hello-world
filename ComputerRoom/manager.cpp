#include<iostream>
using std::cout;
using std::endl;
using std::string;
#include<fstream>
#include<algorithm>
#include"manager.h"

Manager::Manager(const std::string& _name, const std::string& _pswd)
{
	name = _name;
	pswd = _pswd;

	initVector();

	std::ifstream ifs;
	ifs.open(computer_file);

	computerRoom com;
	while (ifs >> com.com_Id && ifs >> com.Max_Num)
		vCom.push_back(com);
	ifs.close();
}

void Manager::openMenu()
{
	cout << "��ӭ����Ա��" << name << "��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();

	std::ifstream ifs;
	ifs.open(student_file);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Student stu;
	while (ifs >> stu.stu_Id() && ifs >> stu.stu_name() && ifs >> stu.stu_pswd())
		vStu.push_back(stu);
	ifs.close();

	ifs.open(teacher_file);
	Teacher t;
	while (ifs >> t.tea_id() && ifs >> t.tea_name() && ifs >> t.tea_pswd())
		vTea.push_back(t);

	ifs.close();
}

bool Manager::checkRepeat(const int& _id, const int& _type)
{
	if (_type == 1)
	{
		for (auto it = vStu.cbegin(); it != vStu.cend();++it)
		{
			if (it->stu_Id() != _id)
				return true;
		}
	}
	else
	{
		for (auto it = vTea.cbegin(); it != vTea.cend();++it)
		{
			if (it->tea_id() != _id)
				return true;
		}
	}
	return false;
}

void Manager::appPerson()
{
	cout << "����������˺�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string fileName; //�����ļ���
	string tip;  //��ʾid��
	string errorTip; //�ظ�������ʾ

	std::ofstream ofs;

	int select = 0;
	std::cin >> select;

	if (select == 1)
	{
		//��ӵ���ѧ��
		fileName = student_file;
		tip = "������ѧ�ţ�";
		errorTip = "ѧ���ظ�������������";
	}
	else
	{
		fileName = teacher_file;
		tip = "������ְ����ţ�";
		errorTip = "ְ�����ظ�������������";
	}

	ofs.open(fileName, std::ofstream::app);

	int _id;
	string _name;
	string _pswd;

	cout << tip << endl;

	while (true)
	{
		std::cin >> _id;
		bool ret = checkRepeat(_id, select);
		if (ret)
			cout << errorTip << endl;
		else
			break;
	}

	cout << "������������ " << endl;
	std::cin >> _name;

	cout << "���������룺 " << endl;
	std::cin >> _pswd;

	//���ļ����������
	if(ofs << _id << " " << _name << " " << _pswd << " " << endl)
	    cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");

	ofs.close();

	initVector();
}

void printStudent(const Student& s)
{
	cout << "ѧ�ţ� " << s.stu_Id() << " ������ " << s.stu_name() << " ���룺" << s.stu_pswd() << endl;
}
void printTeacher(const Teacher& t)
{
	cout << "ѧ�ţ� " << t.tea_id() << " ������ " << t.tea_name() << " ���룺" << t.tea_pswd() << endl;
}

//�鿴�˺�
void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;

	int select = 0; //�����û�ѡ��
	std::cin >> select;

	if (select == 1)
	{
		//�鿴ѧ��
		cout << "����ѧ����Ϣ���£�" << endl;
		for_each(vStu.cbegin(), vStu.cend(), printStudent);
	}
	else
	{
		//�鿴��ʦ
		cout << "������ʦ��Ϣ���£�" << endl;
		for_each(vTea.cbegin(), vTea.cend(), printTeacher);
	}

	system("pause");
	system("cls");
}
//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;

	for (auto it = vCom.cbegin(); it != vCom.cend();it++)
	{
		cout << "������ţ� " << it->com_Id << " ������������� " << it->Max_Num << endl;
	}
	system("pause");
	system("cls");
}
//���ԤԼ��¼
void Manager::cleanFile()
{
	std::ofstream ofs(order_file);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}