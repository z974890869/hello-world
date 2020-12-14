#pragma once
#include<string>
using std::string;
extern string computer_file;
extern string order_file;
extern string student_file;
extern string teacher_file;
extern string admin_file;

enum class input{ exit = 0,stu = 1,tea = 2,admin =3};
std::istream& operator>>(std::istream& is, input& item);

class Identity
{
public:
	virtual ~Identity() = default;//������̬����
	//����������� openMenu() ����virtual
	//  =0:pure virtual ��������� ���ܶ������ ��Indentity k;
	virtual void openMenu() = 0;
	//�鿴����ԤԼ
	void showAllOrder();
protected:
	string name;
	string pswd;
};