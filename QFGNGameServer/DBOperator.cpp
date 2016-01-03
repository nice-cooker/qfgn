/*************************************************************************
    > File Name: DBOperator.cpp
    > Author: ncook 
    > Mail: ncook@163.com 
    > Created Time: Sun 27 Dec 2015 09:25:39 PM CST
 ************************************************************************/
#include "DBOperator.h"
#include <iostream> 

const int CDBOperator::TABLE_COUNT = 1; 
const string CDBOperator::DB_PREFIX = "db_face_flow_";

CDBOperator::CDBOperator()
{
	NC_DBConf dbConf;
	dbConf._host = "rdst53vmmbz8143ec89j.mysql.rds.aliyuncs.com";
	dbConf._user = "zishi_db";
	dbConf._password = "zishi2015";
	dbConf._charset = "utf8";
	dbConf._port = 3306;

	for (int i = 0; i < DB_COUNT; i++)
	{
		dbConf._database = DB_PREFIX + convert_to_string<int>(i);
		m_mysqlHandle[i].init(dbConf);
		m_mysqlHandle[i].connect();
	}
}

	
CDBOperator::~CDBOperator()	
{
	for (int i = 0; i < DB_COUNT; i++)
	{
		m_mysqlHandle[i].disconnect();
	}
}
	
NC_Mysql& CDBOperator::getMysqlHandle(unsigned int uUid)
{
	return m_mysqlHandle[uUid%DB_COUNT];
}

int CDBOperator::selectUserAccount(unsigned int uUid, TUserAccount & stUserAccount)
{
	try
	{
		string sql = "select user_id, user_password_md5 from t_user_account_" + convert_to_string<int>(uUid%TABLE_COUNT);
		NC_Mysql::MysqlData data = getMysqlHandle(uUid).queryRecord(sql);
		if (data.size() > 0)
		{
			stUserAccount.uUid = convert_from_string<unsigned int>(data[0]["user_id"]);
			stUserAccount.strPasswordMd5 = data[0]["user_password_md5"];
		}
		return 0;
	}
	catch(NC_Mysql_Exception & e)
	{
		cout << "selectUserAccount mysql exception:" << e.what() << endl;
		return -1;
	}
	catch(exception & e)
	{
		cout << "selectUserAccount exception:" << e.what() << endl;
		return -1;
	}
	return 0;
}

int CDBOperator::insertUserAccount(TUserAccount & stUserAccount)
{
	try
	{
		map<string, pair<NC_Mysql::FT, string> > mpColumn;
		mpColumn["user_id"] =  make_pair(NC_Mysql::DB_INT, convert_to_string<unsigned>(stUserAccount.uUid));
		mpColumn["user_password_md5"] =  make_pair(NC_Mysql::DB_STR, stUserAccount.strPasswordMd5);

		size_t ret = getMysqlHandle(stUserAccount.uUid).insertRecord("t_user_account_" + convert_to_string<int>(stUserAccount.uUid%TABLE_COUNT), mpColumn);
		if (1 == ret)
		{
			return 0;
		}
		else
		{
			return -1;	
		}
	}
	catch(NC_Mysql_Exception & e)
	{
		cout << "selectUserAccount mysql exception:" << e.what() << endl;
		return -2;
	}
	catch(exception & e)
	{
		cout << "selectUserAccount exception:" << e.what() << endl;
		return -2;
	}
	return 0;
}
	
int CDBOperator::updateUserAccount(TUserAccount & stUserAccount)
{
	try
	{
		map<string, pair<NC_Mysql::FT, string> > mpColumn;
		mpColumn["user_password_md5"] =  make_pair(NC_Mysql::DB_STR, stUserAccount.strPasswordMd5);

		size_t ret = getMysqlHandle(stUserAccount.uUid).updateRecord("t_user_account_" + convert_to_string<int>(stUserAccount.uUid%TABLE_COUNT), mpColumn, "where user_id=" + convert_to_string<unsigned>(stUserAccount.uUid));
		if (1 == ret)
		{
			return 0;
		}
		else
		{
			return -1;	
		}
	}
	catch(NC_Mysql_Exception & e)
	{
		cout << "selectUserAccount mysql exception:" << e.what() << endl;
		return -2;
	}
	catch(exception & e)
	{
		cout << "selectUserAccount exception:" << e.what() << endl;
		return -2;
	}
	return 0;
}
