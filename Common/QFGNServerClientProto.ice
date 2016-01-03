#ifndef _QFGN_SERVER_CLIENT_PROTO_
#define _QFGN_SERVER_CLIENT_PROTO_

module QFGNServerClientProto
{

	enum ESvrCmdID
	{
		ESvrCmdIDRegister,						//ע��
		ESvrCmdIDRegisterNO,					//��ȡע����֤�루ע��ʱ��ʹ���ֻ����뻻ȡ��
		ESvrCmdIDLogin,							//��½
		ESvrCmdIDModifyKey,						//�޸�����
	};
	
	enum ESvrCmdType
	{
		ESvrCmdTypeRequest,						//����
		ESvrCmdTypeResponse,					//��Ӧ
		ESvrCmdTypeNotify,						//֪ͨ
	};

	sequence<byte> ByteBuff;
	struct TPackage
	{
		string strUid; 							//�˺���Ϣ
		string strPassword;						//����
		string strClientVer;					//�ͻ��˰汾
		ESvrCmdID eCmdId;						//������
		ESvrCmdType eCmdType;					//��������
		ByteBuff vecCmdData;					//��������
	};
	
	//��ȡ������֤������
	struct TGetRegisterNOReq
	{
		string	sUid;							//�ֻ�����
		string	sKey;							//������� -- ���ֶ��ڱ���Ϣ����Ч������Ҫ�ͻ��˴���
		string	sExt1;							//��չ�ֶ�
	};
	
	//��ȡ������֤����Ӧ
	struct TGetRegisterNORsp
	{
		int		iReturn;						//��� -- ע����ͨ�����ŵ���ʽ���͸����
		string	sExt1;							//��չ�ֶ�
	};

	//ע������ -- ͨ���ֻ����롢������֤�롢����
	struct TRegisterReq
	{
		string	sUid;							//�ֻ�����
		string	sRegisterNO;					//������֤��
		string	sKey;							//�������
		string	sExt1;							//��չ�ֶ�
	};
	
	//ע����Ӧ -- �ͻ�����Ҫ�����ע����ֻ���������뱣�����ֻ�����
	struct TRegisterRsp
	{
		int		iReturn;						//���ؽ��
		string	sUid;							//�ֻ�����
		string	sKey;							//�������
		string	sExt1;							//��չ�ֶ�
	};
	
	//������½����
	struct TLoginReq
	{
		string	sUid;							//���uid
		string	sKey;							//����
		string	sExt1;							//��չ�ֶ�
	};
	
	//������½��Ӧ
	struct TLoginRsp
	{
		int		iReturn;						//���ؽ��
		string	sExt1;							//��չ�ֶ�
	};
	
	//������������ -- �ͻ�����Ҫ����֤�����������������Ƿ�һ��
	struct TChangeKeyReq
	{
		string	sUid;							//���uid
		string	sCheckCode;						//������֤��
		string	sKey;							//����
		string	sKeySure;						//����ȷ��
		string	sExt1;							//��չ�ֶ�			
	};
	
	//����������Ӧ
	struct TChangeKeyRsp
	{
		int		iReturn;						//���ؽ��
		string	sUid;							//���uid
		string	sKey;							//����
		string	sExt1;							//��չ�ֶ�
	};
	

};



#endif //_QFGN_SERVER_CLIENT_PROTO_

