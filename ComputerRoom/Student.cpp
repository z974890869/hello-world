#include"Student.h"
#include"orderFile.h"
#include<iostream>
using std::cout;
using std::endl;

//�����ļ��У�extern computer_file��ȫ�ֱ���������#inlcudeԴ�ļ���cpp���пɼ�
//��Ҫʹ��ֻ�ڵ�ǰcpp�ɼ� namespace{}δ�����Ŀռ�

//���캯��
Student::Student(const int &id,const std::string &_name,const std::string &_pswd)
{
	s_Id = id;
	name = _name;
	pswd = _pswd;

	std::ifstream ifs;
	ifs.open(computer_file, std::ifstream::in);//Ĭ��

	computerRoom com;
	while (ifs >> com.com_Id && ifs >> com.Max_Num)
		vCom.push_back(com);
	ifs.close();
}

//�˵���
void Student::openMenu() 
{
	cout << "��ӭѧ����" << name << "��¼��" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.����ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.�鿴�ҵ�ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.�鿴����ԤԼ          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.ȡ��ԤԼ              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.ע����¼              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����ԤԼ
void Student::applyOrder()
{
	cout << "��������ʱ��Ϊ��һ������!" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;

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

	cout << "����������ԤԼʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;

	while (true)
	{
		std::cin >> interval;
		if (interval > 0 && interval < 3)
			break;
		cout << "Input Error! Please again" << endl;
	}

	cout << "��ѡ������� "<<endl;
	for (auto i = 0;i != vCom.size();++i)
	{
		cout << vCom[i].com_Id << "�Ż�������Ϊ�� " << vCom[i].Max_Num << endl;
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
		cout << "ԤԼ�ɹ��� �����" << endl;

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

//�鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile of;
	if (of.ordernum() == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
		system("pause");
		system("cls");
		return;
	}
	int xuhao = 1;
	for (unsigned i = 0; i < of.ordernum();++i)
	{//
		if (s_Id == std::stoi(of.o_Data()[i]["stuId"]))
		{
			cout << xuhao++ << "��";
			cout << "ԤԼ���ڣ� ��" << of.o_Data()[i]["date"] << endl;
			cout << " ʱ��Σ� " << (of.o_Data()[i]["interval"] == "1" ? "����" : "����") << endl;
			cout << " �����ţ� " << of.o_Data()[i]["roomId"] << endl;

			std::string status = "״̬: ";
			// 1 �����  2 ��ԤԼ  -1 ԤԼʧ��  0 ȡ��ԤԼ
			if (of.o_Data()[i]["status"] == "1")
				status += "�����";
			else if (of.o_Data()[i]["status"] == "2")
				status += "ԤԼ�ɹ�";
			else if (of.o_Data()[i]["status"] == "-1")
				status += "ԤԼʧ�ܣ����δͨ��";
			else
				status += "ԤԼ��ȡ��";
			cout << status << endl;
			cout << endl;
		}
	}
	system("pause");
	system("cls");
}


//ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;
	if (of.ordernum() == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
	std::vector<unsigned> vu;//��¼������ԤԼ��o_Date�е�keyֵ
	unsigned index = 1; //���ԤԼ���
	for (unsigned i = 0; i != of.ordernum();++i)
	{
		if (s_Id == std::stoi(of.o_Data()[i]["stuId"]))
		{
			//����Ѿ�ԤԼ
			if (of.o_Data()[i]["status"] == "1" || of.o_Data()[i]["status"] == "2")
			{
				vu.push_back(i);
				cout << index++ << "�� ";
				cout << "ԤԼ���ڣ� ��" << of.o_Data()[i]["date"];
				cout << " ʱ��Σ� " << (of.o_Data()[i]["interval"] == "1" ? "����" : "����");
				cout << " ������ţ� " << of.o_Data()[i]["roomId"];
				std::string status = " ״̬�� ";
				if (of.o_Data()[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.o_Data()[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				cout << status << endl;
			}
		}
	}

	cout << "������ȡ���ļ�¼��0������" << endl;
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
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}
	system("pause");
	system("cls");
}