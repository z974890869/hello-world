#pragma once
#include"Identity.h"
#include<fstream>
#include<vector>
#include"computerRoom.h"

class Student :public Identity
{
public:

	Student() = default;
	Student(const int &id,const std::string &name,const std::string &pswd);
	//�������� virtual override �����п���û��
	
	void openMenu() override; 
	void applyOrder();
	void showMyOrder();
//	void showAllOrder(); //�̳л���
	void cancelOrder();

	int& stu_Id() { return s_Id; }
	string& stu_name(){ return name; }
	string& stu_pswd() { return pswd; }

	const int& stu_Id() const { return s_Id; }
	const string& stu_name() const { return name; }
	const string& stu_pswd() const { return pswd; }
private:
	int s_Id = 0;
	string name;
	string pswd;
	std::vector<computerRoom> vCom;
};