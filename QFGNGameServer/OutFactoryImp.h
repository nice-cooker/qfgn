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

	//����url
	static string m_sDuanXinUrl;

	//�����û���
	static string m_sDuanXinUserName;

	//��������
	static string m_sDuanXinKey;
};