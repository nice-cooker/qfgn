#include "OutFactoryImp.h"

map<string, string> OutFactoryImp::m_mapUid2CheckCode;
string OutFactoryImp::m_sDuanXinUrl;

string OutFactoryImp::m_sDuanXinUserName;

string OutFactoryImp::m_sDuanXinKey;


//http://106.ihuyi.cn/webservice/sms.php?method=Submit&account=cf_zishi&password=zishi2015&mobile=15012959550&content=您的验证码是：【8888】。请不要把验证码泄露给其他人。如非本人操作，可不用理会！

int OutFactoryImp::init()
{
	//1.用户名:cf_zishi
	//密码:zishi2015
	m_mapUid2CheckCode.clear();
	m_sDuanXinUrl = "106.ihuyi.cn/webservice/sms.php";
	m_sDuanXinUserName = "cf_zishi";
	m_sDuanXinKey = "zishi2015";
	return 0;
}
