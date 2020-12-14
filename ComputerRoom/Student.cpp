#include"Student.h"
#include"orderFile.h"
#include<iostream>
using std::cout;
using std::endl;

//其他文件中（extern computer_file）全局变量在所有#inlcude源文件（cpp）中可见
//若要使它只在当前cpp可见 namespace{}未命名的空间

//构造函数
Student::Student(const int &id,const std::string &_name,const std::string &_pswd)
{
	s_Id = id;
	name = _name;
	pswd = _pswd;

	std::ifstream ifs;
	ifs.open(computer_file, std::ifstream::in);//默认

	computerRoom com;
	while (ifs >> com.com_Id && ifs >> com.Max_Num)
		vCom.push_back(com);
	ifs.close();
}

//菜单栏
void Student::openMenu() 
{
	cout << "欢迎学生：" << name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::applyOrder()
{
	cout << "机房开放时间为周一至周五!" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;

	int date = 0;
	int interval = 0;
	int room = 0;

	while (true)
	{
		std::cin >> date;
		if (date > 0 && date < 6)
			break;
		cout << "Input Error! Please again" << endl;
	}

	cout << "请输入申请预约时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;

	while (true)
	{
		std::cin >> interval;
		if (interval > 0 && interval < 3)
			break;
		cout << "Input Error! Please again" << endl;
	}

	cout << "请选择机房： "<<endl;
	for (auto i = 0;i != vCom.size();++i)
	{
		cout << vCom[i].com_Id << "号机房容量为： " << vCom[i].Max_Num << endl;
	}
	while (true)
	{
		std::cin >> room;
		if (room > 0 && room < 4)
			break;
		cout << "Input Error! Please again" << endl;
	}

	
	std::ofstream ofs;
	ofs.open(order_file, std::ofstream::app);
	if(ofs)
		cout << "预约成功！ 审核中" << endl;

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << s_Id << " ";
	ofs << "stuName:" << name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << "1" << endl;


	ofs.close();

	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.ordernum() == 0)
	{
		cout << "无预约记录！" << endl;
		system("pause");
		system("cls");
		return;
	}
	int xuhao = 1;
	for (unsigned i = 0; i < of.ordernum();++i)
	{//
		if (s_Id == std::stoi(of.o_Data()[i]["stuId"]))
		{
			cout << xuhao++ << "、";
			cout << "预约日期： 周" << of.o_Data()[i]["date"] << endl;
			cout << " 时间段： " << (of.o_Data()[i]["interval"] == "1" ? "上午" : "下午") << endl;
			cout << " 机房号： " << of.o_Data()[i]["roomId"] << endl;

			std::string status = "状态: ";
			// 1 审核中  2 已预约  -1 预约失败  0 取消预约
			if (of.o_Data()[i]["status"] == "1")
				status += "审核中";
			else if (of.o_Data()[i]["status"] == "2")
				status += "预约成功";
			else if (of.o_Data()[i]["status"] == "-1")
				status += "预约失败，审核未通过";
			else
				status += "预约已取消";
			cout << status << endl;
			cout << endl;
		}
	}
	system("pause");
	system("cls");
}


//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.ordernum() == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
	std::vector<unsigned> vu;//记录所查找预约在o_Date中的key值
	unsigned index = 1; //输出预约序号
	for (unsigned i = 0; i != of.ordernum();++i)
	{
		if (s_Id == std::stoi(of.o_Data()[i]["stuId"]))
		{
			//如果已经预约
			if (of.o_Data()[i]["status"] == "1" || of.o_Data()[i]["status"] == "2")
			{
				vu.push_back(i);
				cout << index++ << "、 ";
				cout << "预约日期： 周" << of.o_Data()[i]["date"];
				cout << " 时间段： " << (of.o_Data()[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房编号： " << of.o_Data()[i]["roomId"];
				std::string status = " 状态： ";
				if (of.o_Data()[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.o_Data()[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入取消的记录，0代表返回" << endl;
	int select = 0;

	while (true)
	{
		std::cin >> select;
		if (select >= 0 && select <= vu.size())
		{
			if (select == 0)
				break;
			else
			{
				of.o_Data()[vu[select - 1]]["status"] = "0";
				of.printOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}