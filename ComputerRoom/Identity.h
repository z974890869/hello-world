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
	virtual ~Identity() = default;//析构动态对象
	//所有派生类的 openMenu() 都是virtual
	//  =0:pure virtual ：抽象基类 不能定义对象 ：Indentity k;
	virtual void openMenu() = 0;
	//查看所有预约
	void showAllOrder();
protected:
	string name;
	string pswd;
};