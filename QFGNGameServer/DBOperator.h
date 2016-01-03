/*************************************************************************
    > File Name: DBOperator.h
    > Author: ncook 
    > Mail: ncook@163.com 
    > Created Time: Sun 27 Dec 2015 08:13:55 PM CST
 ************************************************************************/
#pragma once

#include "nc_mysql.h" 
#include <string> 
#include <cstdio>
#include <sstream>

using namespace std;
using namespace ncook;

#define DB_COUNT 1

//c++方法：将数值转换为string
template<class T>
string convert_to_string(T x)
{
	ostringstream o;
	if(o << x)
		return o.str();
	return "conversion error";
}
//c++方法，将string转化为数值
template<class T>
T convert_from_string(const string &s)
{

	istringstream i(s);
	T x;
	if(i >> x)
		return x;
	return 0.0;
}
struct TUserAccount
{
	unsigned int uUid;
	string strPasswordMd5;
};
class CDBOperator
{
public:
	CDBOperator();
	~CDBOperator();	
	int selectUserAccount(unsigned int uUid, TUserAccount & stUserAccount);
	int insertUserAccount(TUserAccount & stUserAccount);
	int updateUserAccount(TUserAccount & stUserAccount);
protected:
	NC_Mysql& getMysqlHandle(unsigned int uUid);
public:
	const static int TABLE_COUNT;
	const static string DB_PREFIX;
private:
	NC_Mysql m_mysqlHandle[DB_COUNT];
};

