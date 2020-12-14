#include<iostream>
using std::cout;
using std::endl;
#include"Identity.h"
#include"orderFile.h"

string student_file = "student.txt";
string teacher_file = "teacher.txt";
string admin_file = "admin.txt";
string computer_file = "computerRoom.txt";
string order_file = "order.txt";

std::istream& operator>>(std::istream& is, input& item)
{
	int select;
	is >> select;
	if (is)
		item = input(select);
	else
	{
		item = input(0);
		std::cerr << "读取失败" << endl;
	}
	return is;
}
void Identity::showAllOrder()
{
	OrderFile of;
	if (of.ordernum() == 0)
	{
		cout << "无预约记录" << endl;
		system("pasue");
		system("cls");
		return;//提前结束
	}
	for (auto i = 0; i < of.ordernum(); ++i)
	{
		cout << i + 1 << "、 ";
		cout << "预约日期： 周" << of.o_Data()[i]["date"];
		cout << " 时间段： " << (of.o_Data()[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号： " << of.o_Data()[i]["stuId"];
		cout << " 姓名： " << of.o_Data()[i]["stuName"];
		cout << " 机房编号： " << of.o_Data()[i]["roomId"];
		string status = " 状态：";
		// 1 审核中 2 已预约  -1预约失败  0 取消预约
		if (of.o_Data()[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.o_Data()[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.o_Data()[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}