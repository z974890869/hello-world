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
				cin >> select; //�����û�ѡ��

				if (select == 1) //����ԤԼ
				{
					s_up->applyOrder();
				}
				else if (select == 2) //�鿴����ԤԼ
				{
					s_up->showMyOrder();
				}
				else if (select == 3) //�鿴������ԤԼ
				{
					s_up->showAllOrder();
				}
				else if (select == 4) //ȡ��ԤԼ
				{
					s_up->cancelOrder();
				}
				else
				{
					//ע����¼
					cout << "ע���ɹ�" << endl;
					system("pause");
					system("cls");
					return;
				}
		}
	}
}
//�����ʦ�Ӳ˵�����
void teacherMenu(shared_ptr<Identity> &teacher)
{
	while (true)
	{
		//�����Ӳ˵�����
		teacher->openMenu();

		if (auto t_up = dynamic_pointer_cast<Teacher>(teacher))
		{
			int select = 0; //�����û�ѡ��

			cin >> select;

			if (select == 1) //�鿴����ԤԼ
			{
				t_up->showAllOrder();
			}
			else if (select == 2) //���ԤԼ
			{
				t_up->checkOrder();
			}
			else
			{
				cout << "ע���ɹ�" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
	}
}

//�������Ա�Ӳ˵�����
void managerMenu(shared_ptr<Identity> &manager)
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manager->openMenu();

		//������ָ�� תΪ����ָ�룬���������������ӿ�
		if (auto m_up = dynamic_pointer_cast<Manager>(manager))
		{
			int select = 0;
			//�����û�ѡ��
			cin >> select;

			if (select == 1) //����˺�
			{
				//cout << "����˺�" << endl;
				m_up->appPerson();
			}
			else if (select == 2) //�鿴�˺�
			{
				//cout << "�鿴�˺�" << endl;
				m_up->showPerson();
			}
			else if (select == 3) //�鿴����
			{
				//cout << "�鿴����" << endl;
				m_up->showComputer();
			}
			else if (select == 4) //���ԤԼ
			{
				//cout << "���ԤԼ" << endl;
				m_up->cleanFile();
			}
			else
			{
				//ע��
				cout << "ע���ɹ�" << endl;
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
		cout << "�ļ���ʧ��" << endl;
		ifs.close();
		return;
	}

	int _id = 0;
	string _name;
	string _pswd;

	//�ж����
	if (shenfen == input::stu) //ѧ�����
	{
		cout << "���������ѧ�ţ�" << endl;
		cin >> _id;
	}
	else if (shenfen == input::tea)
	{
		cout << "����������ְ���ţ� " << endl;
		cin >> _id;
	}

	cout << "�������û�����" << endl;
	cin >> _name;

	cout << "���������룺" << endl;
	cin >> _pswd;
	
	if (shenfen == input::stu)
	{
		//ѧ�������֤
		int fId; //���ļ��ж�ȡ��id��
		string fName; //���ļ��л�ȡ������
		string fPwd; //���ļ��л�ȡ����
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (fId == _id && fName == _name && fPwd == _pswd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
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
		//��ʦ�����֤
		int fId; //���ļ��л�ȡ��id��
		string fName; //���ļ��л�ȡ������
		string fPwd; //���ļ��л�ȡ������
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == _id && fName == _name && fPwd == _pswd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				shared_ptr<Identity> person = make_shared<Teacher>(_id, _name, _pswd);
//				unique_ptr<Identity> person(new Teacher(_id, _name, _pswd));
				//�����ʦ�Ӳ˵�
				teacherMenu(person);
				return;
			}
		}
	}
	else if (shenfen == input::admin)
	{
		//����Ա�����֤
		string fName; //���ļ��л�ȡ����
		string fPwd; //���ļ��л�ȡ����

		while (ifs >> fName && ifs >> fPwd)
		{
			if (_name == fName && _pswd == fPwd)
			{
				cout << "����Ա��֤��¼�ɹ�!" << endl;
				system("pause");
				system("cls");
				shared_ptr<Identity> person = make_shared<Manager>(_name, _pswd);
//				unique_ptr<Identity> person(new Manager(_name, _pswd));
				//�������Ա�Ӳ˵�����
				managerMenu(person);
				return;
			}
		}
	}
	cout << "��֤��¼ʧ�ܣ�" << endl;
	system("pause");
	system("cls");
	return;
}


int main()
{
	while (true)
	{
		cout << "= ==================== = ��ӭ������˧��Ļ���ԤԼϵͳ  ==================== = " << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.ѧ    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.��    ʦ           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.�� �� Ա           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "��������ѡ��: ";

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
		case input::exit:  //�˳�ϵͳ
			cout << "��ӭ��һ��ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");//����ʵ�ֶ�����Ļ�����ڹ۲�����ִ�н��
	return 0;
}