#include<iostream>
#include<vector>
using std::cout;
using std::endl;
#include"teacher.h"
#include"orderFile.h"

Teacher::Teacher(const int& id, const std::string& _name, const std::string& _pswd)
{
	t_Id = id;
	name = _name;
	pswd = _pswd;
}

void Teacher::openMenu()
{
	cout << "欢迎教师：" << name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//审核预约
void Teacher::checkOrder()
{
	OrderFile of;
	if (of.ordernum() == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	std::vector<int> vi;
	int index = 0;
	cout << "待审核的预约记录如下：" << endl;

	for (auto i = 0; i < of.ordernum(); ++i)
	{
		if (of.o_Data()[i]["status"] == "1")
		{
			vi.push_back(i);
			cout << ++index << "、 ";
			cout << "预约日期： 周" << of.o_Data()[i]["date"];
			cout << " 时间段： " << (of.o_Data()[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 学生编号： " << of.o_Data()[i]["stuId"];
			cout << " 学生姓名： " << of.o_Data()[i]["stuName"];
			cout << " 机房编号： " << of.o_Data()[i]["roomId"];
			std::string status = " 状态：审核中 ";
			cout << status << endl;
		}
	}

	cout << "请输入审核的预约记录，0代表返回" << endl;
	int select = 0; //接受用户选择的预约记录
	int ret = 0;  //接受预约结果记录

	while (true)
	{
		std::cin >> select;
		if (select >= 0 && select <= vi.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				std::cin >> ret;
				if (ret == 1)
				{
					//通过情况
					of.o_Data()[vi[select - 1]]["status"] = "2";
				}
				else
				{
					//不通过情况
					of.o_Data()[vi[select - 1]]["status"] = "-1";
				}
				of.printOrder(); // 更新预约记录
				cout << "审核完毕" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	system("pause");
	system("cls");
}