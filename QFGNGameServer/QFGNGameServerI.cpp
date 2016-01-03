#include <Ice/Ice.h>
#include <QFGNGameServerI.h>
#include <iostream>
#include "OutFactoryImp.h"
#include "HttpInterface.h"
#include "CommonUtil.h"
#include "QFGNServerClientProto.h"
#include "DBOperator.h"

using namespace std;
using namespace QFGN;
using namespace CommonUtil;
using namespace QFGNServerClientProto;


::Ice::Int
QFGN::GameServerI::doTransmit(const ::QFGNServerClientProto::TPackage& stPackage,
                              const Ice::Current& current)
{
	int iReturn = 0;

	//������ϢID������Ϊ
	int iMsgID = stPackage.eCmdId; 
	cout << "A MSG coming, MSGID:" << iMsgID << ", strUid:" << stPackage.strUid << endl;


	do 
	{
		if (ESvrCmdIDRegisterNO == iMsgID)
		{
			//������Ϣ -- ��ȡע����
			Ice::InputStreamPtr in = Ice::createInputStream(current.adapter->getCommunicator(), stPackage.vecCmdData);
			TGetRegisterNOReq stReq;
			in->read(stReq);

			int iRandomKey = CommonUtil::getRandomValue(1000, 9999);
			string sPhoneNO = stReq.sUid;
			string sRandomKey = tostr(iRandomKey);
			cout << "iRandomKey:" << iRandomKey << ", sRandomKey:" << sRandomKey << ", sPhoneNO:" << sPhoneNO << endl;
			//http://106.ihuyi.cn/webservice/sms.php?method=Submit&account=�û���&password=����&mobile=�ֻ�����&content=������֤���ǣ������������벻Ҫ����֤��й¶�������ˡ�
			string sUrl = OutFactoryImp::m_sDuanXinUrl + "?" + "method=Submit&account=" + OutFactoryImp::m_sDuanXinUserName + "&password=" + OutFactoryImp::m_sDuanXinKey + "&mobile=" + sPhoneNO + "&content=������֤���ǣ���" + sRandomKey + "�����벻Ҫ����֤��й¶�������ˡ�";
			//cout << "sUrl:" << sUrl << endl;
			OutFactoryImp::m_mapUid2CheckCode[sPhoneNO] = sRandomKey;

			THttpAsync stTHttpAsync;
			stTHttpAsync.init(sUrl, 0);  //�˿�д0��ʾ�����ö˿ں�����url
			//stTHttpAsync.setHttpPost(strReq);
			stTHttpAsync.doSyncHttpRequest();
		}
		else if (ESvrCmdIDRegister == iMsgID)
		{
			//����ע����Ϣ
			Ice::InputStreamPtr in = Ice::createInputStream(current.adapter->getCommunicator(), stPackage.vecCmdData);
			TRegisterReq stReq;
			in->read(stReq);
			cout << "sUid:" << stReq.sUid << ", sRegisterNO:" << stReq.sRegisterNO << ", sKey:" << stReq.sKey << endl;

			//�����Ҷ�����֤���Ƿ���ȷ
			map<string, string>::iterator itUid2CheckCode = OutFactoryImp::m_mapUid2CheckCode.find(stReq.sUid);
			if(itUid2CheckCode == OutFactoryImp::m_mapUid2CheckCode.end())
			{
				cerr << "No register NO for usr:" << stReq.sUid << endl;
				iReturn = 10005;
				break;
			}

			if (itUid2CheckCode->second != stReq.sRegisterNO)
			{
				cerr << "Register code is wrong, uid:" << stReq.sUid << ", stReq.sRegisterNO:" << stReq.sRegisterNO << ", itUid2CheckCode->second:" << itUid2CheckCode->second << endl;
				iReturn = 10006;
				break;
			}

			//��֤��У��ɹ��������������
			cout << "User:" << stReq.sUid << " register success" << endl;

			

			TUserAccount stUserAccount;
			stUserAccount.uUid = convert_from_string<unsigned int>(stReq.sUid); 
			stUserAccount.strPasswordMd5 = stReq.sKey; 
			cout << "uUid:" << stUserAccount.uUid << ", stReq.sUid:" << stReq.sUid << ", strPasswordMd5:" << stUserAccount.strPasswordMd5 << endl;

			CDBOperator db;
			db.insertUserAccount(stUserAccount);


			//���ݱ���ɹ���ɾ���ڴ���ע������Ϣ
			/*
			OutFactoryImp::m_mapUid2CheckCode.erase(itUid2CheckCode);
			map<string, string>::iterator it = OutFactoryImp::m_mapUid2CheckCode.find(stReq.sUid);
			if(it == OutFactoryImp::m_mapUid2CheckCode.end())
			{
				cout << "Del check code success!" << endl;
			}
			else
			{
				//ɾ��ʧ�ܣ�û�й�ϵ���´λ�ȡ��֤��Ḳ��д������ע����Ȼ�ɹ�
				cerr << "Del check code failed!" << endl;
			}
			*/
			
		}
		else if (ESvrCmdIDLogin == iMsgID)
		{
			//�����½��Ϣ
			Ice::InputStreamPtr in = Ice::createInputStream(current.adapter->getCommunicator(), stPackage.vecCmdData);
			TLoginReq stReq;
			in->read(stReq);
			cout << "sUid:" << stReq.sUid << ", sKey:" << stReq.sKey << endl;

			//У�������Ϣ
			CDBOperator db;
			TUserAccount stUserAccount;
			stUserAccount.uUid = -1;
			stUserAccount.strPasswordMd5 = "";
			unsigned int uUid = convert_from_string<unsigned int>(stReq.sUid);
			iReturn = db.selectUserAccount(uUid, stUserAccount);
			if ((0 != iReturn) || (0 == stUserAccount.uUid) || (0 == stUserAccount.strPasswordMd5.length()))
			{
				//�����ݿ��л�ȡ�����Ϣʧ��
				cerr << "db.selectUserAccount failed, iReturn:" << iReturn << ", uUid:" << stUserAccount.uUid << ", strPasswordMd5.length:" << stUserAccount.strPasswordMd5.length() << endl;
				iReturn = 10007;
				break;
			}

			if ((uUid != stUserAccount.uUid) || (stReq.sKey != stUserAccount.strPasswordMd5))
			{
				cerr << "Invalid user info, uUid:" << uUid << ", stReq.sKey:" << stReq.sKey << "DB uid:" << stUserAccount.uUid << ", DB key:" << stUserAccount.strPasswordMd5 << endl;
				iReturn = 10008;
				break;
			}

			cout << "User:" << uUid << " login success, iReturn:" << iReturn << endl;
		}
		else if (ESvrCmdIDModifyKey == iMsgID)
		{
			Ice::InputStreamPtr in = Ice::createInputStream(current.adapter->getCommunicator(), stPackage.vecCmdData);
			TChangeKeyReq stReq;
			in->read(stReq);

			cout << "sUid:" << stReq.sUid << ", sKey:" << stReq.sKey << ", sKeySure:" << stReq.sKeySure << ", sCheckCode:" << stReq.sCheckCode << endl;
			//У������
			if (stReq.sKey != stReq.sKeySure)
			{
				cerr << "Invalid sKeySure:" << stReq.sKeySure << ", key:" << stReq.sKey << ", uid:" << stReq.sUid << endl;
				iReturn = 10009;
				break;
			}

			//
			CDBOperator db;
			TUserAccount stUserAccount;
			stUserAccount.uUid = -1;
			stUserAccount.strPasswordMd5 = "";
			unsigned int uUid = convert_from_string<unsigned int>(stReq.sUid);
			iReturn = db.selectUserAccount(uUid, stUserAccount);
			if ((0 != iReturn) || (0 == stUserAccount.uUid) || (0 == stUserAccount.strPasswordMd5.length()))
			{
				//�����ݿ��л�ȡ�����Ϣʧ��
				cerr << "db.selectUserAccount failed, iReturn:" << iReturn << ", uUid:" << stUserAccount.uUid << ", strPasswordMd5.length:" << stUserAccount.strPasswordMd5.length() << endl;
				iReturn = 10007;
				break;
			}

			//�޸Ĳ���������
			stUserAccount.strPasswordMd5 = stReq.sKey;
			iReturn = db.updateUserAccount(stUserAccount);
			if (0 != iReturn)
			{
				cerr << "updateUserAccount failed, modify key failed" << endl;
				iReturn = 10010;
				break;
			}

			cout << "Modify key success, uUid:" << uUid << endl;			
		}
		else
		{
			cerr << "Invalid MsgID:" << iMsgID << ", uid:" << stPackage.strUid << endl;
			iReturn = 10011;
		}
		
	} while (0);

    return iReturn;
}

::Ice::Int
QFGN::GameServerI::doPrinter(const ::std::string& sInput,
                             const Ice::Current& current)
{
	cout << sInput << endl;



	int iMsgID = ESvrCmdIDRegister;
	//TPackage stPackage;


	if (ESvrCmdIDRegister == iMsgID)
	{
		int iRandomKey = CommonUtil::getRandomValue(1000, 9999);

		//string sPhoneNO = "15012959550";
		string sPhoneNO = "18589020319";

		string sRandomKey = tostr(iRandomKey);
		cout << "iRandomKey:" << iRandomKey << ", sRandomKey:" << sRandomKey << endl;


		//http://106.ihuyi.cn/webservice/sms.php?method=Submit&account=�û���&password=����&mobile=�ֻ�����&content=������֤���ǣ������������벻Ҫ����֤��й¶�������ˡ�
		string sUrl = OutFactoryImp::m_sDuanXinUrl + "?" + "method=Submit&account=" + OutFactoryImp::m_sDuanXinUserName + "&password=" + OutFactoryImp::m_sDuanXinKey + "&mobile=" + sPhoneNO + "&content=������֤���ǣ���" + sRandomKey + "�����벻Ҫ����֤��й¶�������ˡ���Ǳ��˲������ɲ�����ᣡ";

		cout << "sUrl:" << sUrl << endl;

		THttpAsync stTHttpAsync;
		stTHttpAsync.init(sUrl, 0);  //�˿�д0��ʾ�����ö˿ں�����url
		//stTHttpAsync.setHttpPost(strReq);
		stTHttpAsync.doSyncHttpRequest();
	}


    return 0;
}


int main(int argc, char* argv[])
{
	int iRet = OutFactoryImp::init();
	if (0 != iRet)
	{
		cout << "m_OutPtr.init failed" << endl;
		exit(1);
	}

	int status = 0;
	Ice::CommunicatorPtr ic; 
	try
	{
		ic = Ice::initialize(argc, argv);
		Ice::ObjectAdapterPtr adapter = ic->createObjectAdapterWithEndpoints("SimpleGameServerAdapter", "default -p 10001");
		Ice::ObjectPtr object = new GameServerI;
		adapter->add(object, ic->stringToIdentity("SimpleGameServer"));
		adapter->activate();
		ic->waitForShutdown();
	}
	catch (const Ice::Exception & e) 
	{
		cerr << e << endl; status = 1;
	} 
	catch (const char * msg) 
	{ 
		cerr << msg << endl; status = 1;
	} 

	if (ic) 
		ic->destroy();

	return status;
}

