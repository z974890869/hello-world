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
	cout << "欢迎管理员：" << name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();

	std::ifstream ifs;
	ifs.open(student_file);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
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
	cout << "请输入添加账号类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string fileName; //操作文件名
	string tip;  //提示id号
	string errorTip; //重复错误提示

	std::ofstream ofs;

	int select = 0;
	std::cin >> select;

	if (select == 1)
	{
		//添加的是学生
		fileName = student_file;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else
	{
		fileName = teacher_file;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";
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

	cout << "请输入姓名： " << endl;
	std::cin >> _name;

	cout << "请输入密码： " << endl;
	std::cin >> _pswd;

	//向文件中添加数据
	if(ofs << _id << " " << _name << " " << _pswd << " " << endl)
	    cout << "添加成功" << endl;

	system("pause");
	system("cls");

	ofs.close();

	initVector();
}

void printStudent(const Student& s)
{
	cout << "学号： " << s.stu_Id() << " 姓名： " << s.stu_name() << " 密码：" << s.stu_pswd() << endl;
}
void printTeacher(const Teacher& t)
{
	cout << "学号： " << t.tea_id() << " 姓名： " << t.tea_name() << " 密码：" << t.tea_pswd() << endl;
}

//查看账号
void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0; //接受用户选择
	std::cin >> select;

	if (select == 1)
	{
		//查看学生
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.cbegin(), vStu.cend(), printStudent);
	}
	else
	{
		//查看老师
		cout << "所有老师信息如下：" << endl;
		for_each(vTea.cbegin(), vTea.cend(), printTeacher);
	}

	system("pause");
	system("cls");
}
//查看机房信息
void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;

	for (auto it = vCom.cbegin(); it != vCom.cend();it++)
	{
		cout << "机房编号： " << it->com_Id << " 机房最大容量： " << it->Max_Num << endl;
	}
	system("pause");
	system("cls");
}
//清空预约记录
void Manager::cleanFile()
{
	std::ofstream ofs(order_file);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}