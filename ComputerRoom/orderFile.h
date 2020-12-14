#pragma once
#include<map>
#include<string>
//记录预约
class OrderFile
{
	using oData_type = std::map<unsigned, std::map<std::string, std::string>>;
public:
	OrderFile();
	//const（常量成员函数）常量this指针 ：常量对象，引用，指针只能调用常量成员函数
	auto& ordernum() { return order_num; }
	//decltype(auto) 不是引用类型
	auto& o_Data() { return orderData; }//orderData[]:添加key
	void printOrder();
private:
	unsigned order_num = 0 ;
	oData_type orderData;
};