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
		std::cerr << "��ȡʧ��" << endl;
	}
	return is;
}
void Identity::showAllOrder()
{
	OrderFile of;
	if (of.ordernum() == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pasue");
		system("cls");
		return;//��ǰ����
	}
	for (auto i = 0; i < of.ordernum(); ++i)
	{
		cout << i + 1 << "�� ";
		cout << "ԤԼ���ڣ� ��" << of.o_Data()[i]["date"];
		cout << " ʱ��Σ� " << (of.o_Data()[i]["interval"] == "1" ? "����" : "����");
		cout << " ѧ�ţ� " << of.o_Data()[i]["stuId"];
		cout << " ������ " << of.o_Data()[i]["stuName"];
		cout << " ������ţ� " << of.o_Data()[i]["roomId"];
		string status = " ״̬��";
		// 1 ����� 2 ��ԤԼ  -1ԤԼʧ��  0 ȡ��ԤԼ
		if (of.o_Data()[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.o_Data()[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.o_Data()[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}