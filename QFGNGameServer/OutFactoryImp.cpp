#include "OutFactoryImp.h"

map<string, string> OutFactoryImp::m_mapUid2CheckCode;
string OutFactoryImp::m_sDuanXinUrl;

string OutFactoryImp::m_sDuanXinUserName;

string OutFactoryImp::m_sDuanXinKey;


//http://106.ihuyi.cn/webservice/sms.php?method=Submit&account=cf_zishi&password=zishi2015&mobile=15012959550&content=������֤���ǣ���8888�����벻Ҫ����֤��й¶�������ˡ���Ǳ��˲������ɲ�����ᣡ

int OutFactoryImp::init()
{
	//1.�û���:cf_zishi
	//����:zishi2015
	m_mapUid2CheckCode.clear();
	m_sDuanXinUrl = "106.ihuyi.cn/webservice/sms.php";
	m_sDuanXinUserName = "cf_zishi";
	m_sDuanXinKey = "zishi2015";
	return 0;
}
