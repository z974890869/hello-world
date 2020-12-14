#pragma once
#include"Identity.h"

class Teacher :public Identity
{
public:
	Teacher() = default;
	Teacher(const int& id, const std::string& _name, const std::string& _pswd);

	void openMenu() override;
//	void showAllOrder();
	void checkOrder();
//สิสิ constexpr
	int& tea_id() { return t_Id; }
	string& tea_name() { return name; }
	string& tea_pswd() { return pswd; }

	const int& tea_id() const { return t_Id; }
	const string& tea_name() const { return name; }
	const string& tea_pswd() const { return pswd; }
private:
	int t_Id;
	string name;
	string pswd;
};