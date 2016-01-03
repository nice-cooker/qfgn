#ifndef _QFGN_SERVER_CLIENT_PROTO_
#define _QFGN_SERVER_CLIENT_PROTO_

module QFGNServerClientProto
{

	enum ESvrCmdID
	{
		ESvrCmdIDRegister,						//注册
		ESvrCmdIDRegisterNO,					//获取注册验证码（注册时，使用手机号码换取）
		ESvrCmdIDLogin,							//登陆
		ESvrCmdIDModifyKey,						//修改密码
	};
	
	enum ESvrCmdType
	{
		ESvrCmdTypeRequest,						//请求
		ESvrCmdTypeResponse,					//响应
		ESvrCmdTypeNotify,						//通知
	};

	sequence<byte> ByteBuff;
	struct TPackage
	{
		string strUid; 							//账号信息
		string strPassword;						//密码
		string strClientVer;					//客户端版本
		ESvrCmdID eCmdId;						//命令字
		ESvrCmdType eCmdType;					//命令类型
		ByteBuff vecCmdData;					//命令数据
	};
	
	//获取短信验证码请求
	struct TGetRegisterNOReq
	{
		string	sUid;							//手机号码
		string	sKey;							//玩家密码 -- 该字段在本消息中无效，不需要客户端传入
		string	sExt1;							//扩展字段
	};
	
	//获取短信验证码响应
	struct TGetRegisterNORsp
	{
		int		iReturn;						//结果 -- 注册码通过短信的形式发送给玩家
		string	sExt1;							//扩展字段
	};

	//注册请求 -- 通过手机号码、短信验证码、密码
	struct TRegisterReq
	{
		string	sUid;							//手机号码
		string	sRegisterNO;					//短信验证码
		string	sKey;							//玩家密码
		string	sExt1;							//扩展字段
	};
	
	//注册响应 -- 客户端需要将玩家注册的手机号码和密码保存在手机本地
	struct TRegisterRsp
	{
		int		iReturn;						//返回结果
		string	sUid;							//手机号码
		string	sKey;							//玩家密码
		string	sExt1;							//扩展字段
	};
	
	//正常登陆请求
	struct TLoginReq
	{
		string	sUid;							//玩家uid
		string	sKey;							//密码
		string	sExt1;							//扩展字段
	};
	
	//正常登陆响应
	struct TLoginRsp
	{
		int		iReturn;						//返回结果
		string	sExt1;							//扩展字段
	};
	
	//更换密码请求 -- 客户端需要先验证玩家输入的两次密码是否一致
	struct TChangeKeyReq
	{
		string	sUid;							//玩家uid
		string	sCheckCode;						//短信验证码
		string	sKey;							//密码
		string	sKeySure;						//密码确认
		string	sExt1;							//扩展字段			
	};
	
	//更换密码响应
	struct TChangeKeyRsp
	{
		int		iReturn;						//返回结果
		string	sUid;							//玩家uid
		string	sKey;							//密码
		string	sExt1;							//扩展字段
	};
	

};



#endif //_QFGN_SERVER_CLIENT_PROTO_

