#include <stdio.h>
#include <map>
#include "string"

using namespace std;


class OutFactoryImp
{
private:
public:
	static int init();

public:
	static map<string, string> m_mapUid2CheckCode;

	//短信url
	static string m_sDuanXinUrl;

	//短信用户名
	static string m_sDuanXinUserName;

	//短信密码
	static string m_sDuanXinKey;
};