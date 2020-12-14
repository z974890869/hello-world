#include<iostream>
#include<fstream>
using std::ifstream;
#include<string>
using std::string;
#include"orderFile.h"
extern string order_file;
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(order_file);

	string date;
	string interval;
	string std_Id;
	string std_name;
	string room_Id;
	string status;

	order_num = 0;

	while (ifs >> date && ifs >> interval && ifs >> std_Id
		&& ifs >> std_name && ifs >> room_Id && ifs >> status)
	{
		string key;
		string value;
		std::map<string, string> mss;

		auto pos = date.find(":");//return type:   string::size_type(unsigned类型)
		if (pos != string::npos)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);

			mss.emplace(key, value);
		}
		//截取时间段
		pos = interval.find(":"); // 4
		if (pos != string::npos)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);  // size = 10  pos = 4  size - pos  - 1 = 6 - 1
			mss.emplace(key, value);
		}

		//截取学号
		pos = std_Id.find(":"); // 4
		if (pos != string::npos)
		{
			key = std_Id.substr(0, pos);
			value = std_Id.substr(pos + 1, std_Id.size() - pos - 1);  // size = 10  pos = 4  size - pos  - 1 = 6 - 1
			mss.emplace(key, value);
		}
		//截取姓名
		pos = std_name.find(":"); // 4
		if (pos != string::npos)
		{
			key = std_name.substr(0, pos);
			value = std_name.substr(pos + 1, std_name.size() - pos - 1);  // size = 10  pos = 4  size - pos  - 1 = 6 - 1
			mss.emplace(key, value);
		}
		//截取机房号
		pos = room_Id.find(":"); // 4
		if (pos != string::npos)
		{
			key = room_Id.substr(0, pos);
			value = room_Id.substr(pos + 1, room_Id.size() - pos - 1);  // size = 10  pos = 4  size - pos  - 1 = 6 - 1
			mss.emplace(key, value);
		}
		//截取预约状态
		pos = status.find(":"); // 4
		if (pos != string::npos)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);  // size = 10  pos = 4  size - pos  - 1 = 6 - 1
			mss.emplace(key, value);
		}

		orderData.emplace(order_num++, mss);
	}
	ifs.close();
}

//查看预约记录
void OrderFile::printOrder()
{
	std::string s = "data";
	std::ofstream ofs(order_file);//默认ofstream::out | ofstream::trunc 不保留（app）原文件
	for (auto map_it = orderData.begin();map_it != orderData.end();++map_it)
	{
		ofs << "date:" << map_it->second["date"] << "  ";
		ofs << "interval:" << map_it->second["interval"] << " ";
		ofs << "stuId:" << map_it->second["stuId"] << " ";
		ofs << "stuName:" << map_it->second["stuName"] << " ";
		ofs << "roomId:" << map_it->second["roomId"] << " ";
		ofs << "status:" << map_it->second["status"] << std::endl;
	}

	ofs.close();
	/*
	for(unsigned i = 1;i != order_num; ++i)
	{
		ofs << "date:" << orderData[i]["date"] << "  ";
		ofs << "interval:" << orderData[i]["interval"] << " ";
		ofs << "stuId:" << orderData[i]["stuId"] << " ";
		ofs << "stuName:" << orderData[i]["stuName"] << " ";
		ofs << "roomId:" << orderData[i]["roomId"] << " ";
		ofs << "status:" << orderData[i]["status"] << std::endl;
	}
	*/
}