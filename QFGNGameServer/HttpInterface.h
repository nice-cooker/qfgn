//*****************************************************************************
/**
 *  @file    HttpInterface.h
 *
 *  此文件封装Http相关接口
 *	//http://km.oa.com/articles/show/95734?kmref=search&from_page=1&no=1
 *	http://km.oa.com/articles/show/143625?kmref=related_post
 *  @author davidzyang
 */
//*****************************************************************************
#ifndef _HTTP_ASYNC_H_
#define _HTTP_ASYNC_H_


#include "stdio.h"
#include <curl/curl.h>
#include <string>
#include <iostream>
using namespace std;

//#define CURL_ERROR_SIZE 1024


class THttpAsync
{
public:
	//构造函数
	THttpAsync();

	//析构函数
	~THttpAsync();

	//初始化函数
	int init(const string &ip,int port);

	//执行同步Http请求
	int doSyncHttpRequest();

	//异步执行Http请求
	int doAsyncHttpRequest();

	//设置为标准的HTTP POST请求
	int setHttpPost(string & sPostFields);










	//回调函数 -- C++中使用curl回调函数 -- 回调函数不能是类的非静态成员函数
	/**
 *	@brief libcurl接收到数据时的回调函数
 *	@param [in] buffer 接收到的数据所在缓冲区
 *	@param [in] size 数据长度
 *	@param [in] nmemb 数据片数量
 *	@param [in/out] 用户自定义指针
 *	@return 
 */
	static int callbackFor1(void *ptr, size_t size, size_t nmemb, void *outpointer); 

private:
	string m_strip;                        //服务器IP,或者域名
	int    m_iport;                        //服务器端口
	char m_ccurlerrorinfo[CURL_ERROR_SIZE];//curl返回的错误信息
	string m_strtaskresult;                //任务结果，字符串形式保存
	CURLcode m_curlcode;                   //存放curl库操作的返回的结果码
	CURL * m_pcurl;                        //CURL对象指针
	string m_strurl;                       //包含IP和端口信息的url对象
	string m_strtaskfile;                  //要上传的任务文件
	string m_strtaskresultfile;            //任务结果文件

	struct curl_slist *m_stlist;		   //协议头结构信息
};


#endif
