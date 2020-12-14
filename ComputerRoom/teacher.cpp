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
	cout << "��ӭ��ʦ��" << name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.���ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//���ԤԼ
void Teacher::checkOrder()
{
	OrderFile of;
	if (of.ordernum() == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	std::vector<int> vi;
	int index = 0;
	cout << "����˵�ԤԼ��¼���£�" << endl;

	for (auto i = 0; i < of.ordernum(); ++i)
	{
		if (of.o_Data()[i]["status"] == "1")
		{
			vi.push_back(i);
			cout << ++index << "�� ";
			cout << "ԤԼ���ڣ� ��" << of.o_Data()[i]["date"];
			cout << " ʱ��Σ� " << (of.o_Data()[i]["interval"] == "1" ? "����" : "����");
			cout << " ѧ����ţ� " << of.o_Data()[i]["stuId"];
			cout << " ѧ�������� " << of.o_Data()[i]["stuName"];
			cout << " ������ţ� " << of.o_Data()[i]["roomId"];
			std::string status = " ״̬������� ";
			cout << status << endl;
		}
	}

	cout << "��������˵�ԤԼ��¼��0������" << endl;
	int select = 0; //�����û�ѡ���ԤԼ��¼
	int ret = 0;  //����ԤԼ�����¼

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
				cout << "��������˽��" << endl;
				cout << "1��ͨ��" << endl;
				cout << "2����ͨ��" << endl;
				std::cin >> ret;
				if (ret == 1)
				{
					//ͨ�����
					of.o_Data()[vi[select - 1]]["status"] = "2";
				}
				else
				{
					//��ͨ�����
					of.o_Data()[vi[select - 1]]["status"] = "-1";
				}
				of.printOrder(); // ����ԤԼ��¼
				cout << "������" << endl;
				break;
			}
		}
		cout << "�����������������룡" << endl;
	}
	system("pause");
	system("cls");
}