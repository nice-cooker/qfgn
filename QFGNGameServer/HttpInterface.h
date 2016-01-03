//*****************************************************************************
/**
 *  @file    HttpInterface.h
 *
 *  ���ļ���װHttp��ؽӿ�
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
	//���캯��
	THttpAsync();

	//��������
	~THttpAsync();

	//��ʼ������
	int init(const string &ip,int port);

	//ִ��ͬ��Http����
	int doSyncHttpRequest();

	//�첽ִ��Http����
	int doAsyncHttpRequest();

	//����Ϊ��׼��HTTP POST����
	int setHttpPost(string & sPostFields);










	//�ص����� -- C++��ʹ��curl�ص����� -- �ص�������������ķǾ�̬��Ա����
	/**
 *	@brief libcurl���յ�����ʱ�Ļص�����
 *	@param [in] buffer ���յ����������ڻ�����
 *	@param [in] size ���ݳ���
 *	@param [in] nmemb ����Ƭ����
 *	@param [in/out] �û��Զ���ָ��
 *	@return 
 */
	static int callbackFor1(void *ptr, size_t size, size_t nmemb, void *outpointer); 

private:
	string m_strip;                        //������IP,��������
	int    m_iport;                        //�������˿�
	char m_ccurlerrorinfo[CURL_ERROR_SIZE];//curl���صĴ�����Ϣ
	string m_strtaskresult;                //���������ַ�����ʽ����
	CURLcode m_curlcode;                   //���curl������ķ��صĽ����
	CURL * m_pcurl;                        //CURL����ָ��
	string m_strurl;                       //����IP�Ͷ˿���Ϣ��url����
	string m_strtaskfile;                  //Ҫ�ϴ��������ļ�
	string m_strtaskresultfile;            //�������ļ�

	struct curl_slist *m_stlist;		   //Э��ͷ�ṹ��Ϣ
};


#endif
