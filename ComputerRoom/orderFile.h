#pragma once
#include<map>
#include<string>
//��¼ԤԼ
class OrderFile
{
	using oData_type = std::map<unsigned, std::map<std::string, std::string>>;
public:
	OrderFile();
	//const��������Ա����������thisָ�� �������������ã�ָ��ֻ�ܵ��ó�����Ա����
	auto& ordernum() { return order_num; }
	//decltype(auto) ������������
	auto& o_Data() { return orderData; }//orderData[]:���key
	void printOrder();
private:
	unsigned order_num = 0 ;
	oData_type orderData;
};