#pragma once
#include<vector>
#include"Identity.h"
#include"Student.h"
#include"teacher.h"
#include"computerRoom.h"

class Manager :public Identity
{
public:
	Manager() = default;
	Manager(const std::string& _name, const std::string& _pswd);

	void openMenu() override;
	void appPerson();
	void showPerson();
	void showComputer();
	void cleanFile();

private:
	std::vector<Student> vStu;
	std::vector<Teacher> vTea;
	std::vector<computerRoom> vCom;


	void initVector();
	bool checkRepeat(const int& _id, const int& _type);
};