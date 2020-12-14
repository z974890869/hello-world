#include<iostream>
#include<memory>
#include"orderFile.h"
#include"Student.h"
#include"teacher.h"
#include"manager.h"

using namespace std;
/*
//https://stackoom.com/question/1mfyQ/%E5%A6%82%E4%BD%95%E4%BD%BF%E7%94%A8unique-ptr%E6%89%A7%E8%A1%8Cdynamic-cast
template <typename To, typename From, typename Deleter>
unique_ptr<To, Deleter> dynamic_pointer_cast(unique_ptr<From, Deleter>&& p) {
	if (To* cast = dynamic_cast<To*>(p.get()))
	{
		unique_ptr<To, Deleter> result(cast, std::move(p.get_deleter()));
		p.release();
		return result;
	}
	return unique_ptr<To, Deleter>(nullptr); // or throw std::bad_cast() if you prefer
}
*/

void studentMenu(shared_ptr<Identity> &student)
{
	while (true)
	{
		student->openMenu();//call virtual function member()
		if (auto s_up = dynamic_pointer_cast<Student>(student))
		{
			int select = 0;
				cin >> select; //接受用户选择

				if (select == 1) //申请预约
				{
					s_up->applyOrder();
				}
				else if (select == 2) //查看自身预约
				{
					s_up->showMyOrder();
				}
				else if (select == 3) //查看所有人预约
				{
					s_up->showAllOrder();
				}
				else if (select == 4) //取消预约
				{
					s_up->cancelOrder();
				}
				else
				{
					//注销登录
					cout << "注销成功" << endl;
					system("pause");
					system("cls");
					return;
				}
		}
	}
}
//进入教师子菜单界面
void teacherMenu(shared_ptr<Identity> &teacher)
{
	while (true)
	{
		//调用子菜单界面
		teacher->openMenu();

		if (auto t_up = dynamic_pointer_cast<Teacher>(teacher))
		{
			int select = 0; //接受用户选择

			cin >> select;

			if (select == 1) //查看所有预约
			{
				t_up->showAllOrder();
			}
			else if (select == 2) //审核预约
			{
				t_up->checkOrder();
			}
			else
			{
				cout << "注销成功" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
	}
}

//进入管理员子菜单界面
void managerMenu(shared_ptr<Identity> &manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->openMenu();

		//将父类指针 转为子类指针，调用子类里其他接口
		if (auto m_up = dynamic_pointer_cast<Manager>(manager))
		{
			int select = 0;
			//接受用户选项
			cin >> select;

			if (select == 1) //添加账号
			{
				//cout << "添加账号" << endl;
				m_up->appPerson();
			}
			else if (select == 2) //查看账号
			{
				//cout << "查看账号" << endl;
				m_up->showPerson();
			}
			else if (select == 3) //查看机房
			{
				//cout << "查看机房" << endl;
				m_up->showComputer();
			}
			else if (select == 4) //清空预约
			{
				//cout << "清空预约" << endl;
				m_up->cleanFile();
			}
			else
			{
				//注销
				cout << "注销成功" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		
	}

}
void Login(const string &filename,const input &shenfen)
{
	ifstream ifs;
	ifs.open(filename);

	if (!ifs.good())
	{
		cout << "文件打开失败" << endl;
		ifs.close();
		return;
	}

	int _id = 0;
	string _name;
	string _pswd;

	//判断身份
	if (shenfen == input::stu) //学生身份
	{
		cout << "请输入你的学号：" << endl;
		cin >> _id;
	}
	else if (shenfen == input::tea)
	{
		cout << "请输入您的职工号： " << endl;
		cin >> _id;
	}

	cout << "请输入用户名：" << endl;
	cin >> _name;

	cout << "请输入密码：" << endl;
	cin >> _pswd;
	
	if (shenfen == input::stu)
	{
		//学生身份验证
		int fId; //从文件中读取的id号
		string fName; //从文件中获取的姓名
		string fPwd; //从文件中获取密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (fId == _id && fName == _name && fPwd == _pswd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				shared_ptr<Identity> person = make_shared<Student>(_id, _name, _pswd);
//				unique_ptr<Identity> person(new Student(_id, _name, _pswd));
				studentMenu(person);
				return;
			}
		}
	}
	else if (shenfen == input::tea)
	{
		//教师身份验证
		int fId; //从文件中获取的id号
		string fName; //从文件中获取的姓名
		string fPwd; //从文件中获取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == _id && fName == _name && fPwd == _pswd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				shared_ptr<Identity> person = make_shared<Teacher>(_id, _name, _pswd);
//				unique_ptr<Identity> person(new Teacher(_id, _name, _pswd));
				//进入教师子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (shenfen == input::admin)
	{
		//管理员身份验证
		string fName; //从文件中获取姓名
		string fPwd; //从文件中获取密码

		while (ifs >> fName && ifs >> fPwd)
		{
			if (_name == fName && _pswd == fPwd)
			{
				cout << "管理员验证登录成功!" << endl;
				system("pause");
				system("cls");
				shared_ptr<Identity> person = make_shared<Manager>(_name, _pswd);
//				unique_ptr<Identity> person(new Manager(_name, _pswd));
				//进入管理员子菜单界面
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}


int main()
{
	while (true)
	{
		cout << "= ==================== = 欢迎来到张帅哥的机房预约系统  ==================== = " << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学    生           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";

		input shenfen;
		cin >> shenfen;
		switch (shenfen)
		{
		case input::stu:
			Login(student_file, input::stu);
			break;
		case input::tea:
			Login(teacher_file, input::tea);
			break;
		case input::admin:
			Login(admin_file, input::admin);
			break;
		case input::exit:  //退出系统
			cout << "欢迎下一次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");//可以实现冻结屏幕，便于观察程序的执行结果
	return 0;
}