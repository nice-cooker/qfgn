#include "HttpInterface.h"
#include "string.h"

THttpAsync::THttpAsync()
{
	m_strurl = "";
	m_strtaskfile = "";
	m_strtaskresultfile = "";
	memset(m_ccurlerrorinfo,0,sizeof(m_ccurlerrorinfo));
	m_pcurl = NULL;
	m_strtaskresult = "";
	m_curlcode = CURLE_OK;
	m_stlist = NULL;

	cout << "CURL_ERROR_SIZE:" << CURL_ERROR_SIZE << endl;
}



THttpAsync::~THttpAsync()
{
	// ���m_stlist
	if (NULL != m_stlist)
	{
		curl_slist_free_all(m_stlist);  
	}

	//���CURL  
	if (NULL != m_pcurl)
	{
		curl_easy_cleanup(m_pcurl);
	}

	// ���ȫ������  
	curl_global_cleanup(); 

}


int THttpAsync::init( const string &ip,int port )
{
	char temp[1024] = {0};

	if (port > 0)
	{
		snprintf(temp, sizeof(temp)-1, "http://%s:%d",ip.c_str(),port);
	}
	else
	{
		snprintf(temp, sizeof(temp)-1, "http://%s",ip.c_str());
	}	

	m_strurl = temp;
	cout << "m_strurl:" << m_strurl << endl;

	/*
	1. CURLcode curl_global_init(long flags);
	������flags
	CURL_GLOBAL_ALL        //��ʼ�����еĿ��ܵĵ��á�
	CURL_GLOBAL_SSL        //��ʼ��֧�� ��ȫ�׽��ֲ㡣
	CURL_GLOBAL_WIN32      //��ʼ��win32�׽��ֿ⡣
	CURL_GLOBAL_NOTHING   //û�ж���ĳ�ʼ��
	*/
	m_curlcode = curl_global_init(CURL_GLOBAL_ALL);  
	if (CURLE_OK != m_curlcode)  
	{
		cout << "curl_global_init err, m_curlcode:" << m_curlcode << endl;
		return -1;  
	} 

	//��ȡCURL��ָ��
	m_pcurl= curl_easy_init();
	if (m_pcurl == NULL)
	{
		cout << "Failed to create CURL connection" << endl;
		return -1;
	}
	//����˽�еĴ��󻺳���.
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_ERRORBUFFER,m_ccurlerrorinfo);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set error m_ccurlerror:" << m_curlcode << endl;
		return -1;
	}

	// ����curl����ִ�е����������ʱʱ��  
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_TIMEOUT, 3);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set Time out:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_CONNECTTIMEOUT, 3);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set connect Time out:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	//����Э��汾
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_HTTP_VERSION,CURL_HTTP_VERSION_1_0);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to exec curl_easy_setopt!" << endl;
		return -1;
	}

	return 0;
}

int THttpAsync::setHttpPost(string & sPostFields)
{
	//��������Ϊ��׼��HTTP POST����  
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_POST, 1);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set http post:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	// ����ͷ����Ϣ  
	struct curl_slist *stlist = NULL;  
	unsigned int uiContentLength = (unsigned int) sPostFields.size();  // �������ݴ�С  
	char szContentLength[100];  
	snprintf(szContentLength, sizeof(szContentLength), "Content-Length: %u", uiContentLength);  
	stlist = curl_slist_append(stlist, szContentLength);  
	stlist = curl_slist_append(stlist, "Content-Type: text/plain");

	//����HTTPͷ��Ϣ�����͵����ݸ�ʽΪtext/xml  
	curl_easy_setopt(m_pcurl, CURLOPT_HTTPHEADER, stlist);

	cout << "POST FIELD LENGTH:" << uiContentLength << endl;


	//���ô����͵�POST���ݵĳ��ȡ�����������libcurlͨ��strlen����������͵����ݵĳ��ȣ��Ӷ������������а���\0�ַ���  
	curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t) uiContentLength);  

	//�����͵����ݣ���������Ϊ��׼��HTTP body���ݷ��ͣ�������ͨ�������ļ�����ʽ����  
	curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDS, sPostFields.c_str()); 

	//��server���ص����ݽ�д���ָ����ָ��ĵ�ַ  
	//curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, &strResp);  

	//���ûص����������server���ص�����  
	//curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, &processXML);
	return 0;
}

int THttpAsync::doSyncHttpRequest()
{
	//����Ҫ���ʵ�url��ַ.
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_URL, m_strurl.c_str());
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set URL:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	// ִ��https����  
	m_curlcode = curl_easy_perform(m_pcurl);  
	int lRespCode = 0;

	//��ȡHTTP��Ӧ��  
	curl_easy_getinfo(m_pcurl, CURLINFO_RESPONSE_CODE, &lRespCode);  

	if (CURLE_OK != m_curlcode || 200 != lRespCode)  
	{ 
		cout << "do sync http request failed, eCURLCode:" << m_curlcode << ", lRespCode:" << lRespCode << endl;
		return -1;  
	}

	cout << "m_curlcode:" << m_curlcode << ", lRespCode:" << lRespCode << endl;

	return 0;
}

int THttpAsync::doAsyncHttpRequest()
{
	//����Ҫ���ʵ�url��ַ.
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_URL, m_strurl.c_str());
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set URL:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	//����д�ص�����
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, &callbackFor1);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set write function option :" << m_ccurlerrorinfo << endl;
		return -1;
	}

	//����д�ص���������д���ĵط�
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, &m_strtaskresult);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set write data:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	m_curlcode = curl_easy_perform(m_pcurl);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set write data : " << m_ccurlerrorinfo << endl;
		return -1;
	}

	return 0;
}

int THttpAsync::callbackFor1( void *ptr, size_t size, size_t nmemb, void *outpointer )
{

	string * sResult = (string *)outpointer;
	cout << "HAHA" << endl;

	cout << (*sResult) << endl;

	return 0;
}



//����curl_slist_append()�����Ǻ����õģ�
//��Ϊ�����ʲô����д��
//CUrl�ᴫ��һ������"Get /�����ҳ accept: */*"֮��ļ�Э�飬
//��ĳЩ��֤��Ϊ�ϸ�ķ�������������Http����Э���ֻᱻ�����ġ�Ҳ����˵ɶ�������㷵�أ�����ǧ��Ҫ���ƣ�
// Curl���������͸�������ˣ�curl_slist_append()���API��������αװ��һ����׼����ҳ�����������
// ��Ȼ������Ҳ�����ˣ���׷����һЩHttp��ѡ���Щѡ��ḽ�������Http�����С�
// ��������˳����ͨ����Щ�ϸ���֤�ķ��������������㷵����ȷ�����ݡ�
// ��Ȼ�������ǰ����������Http 1.1Э����һЩ�˽⡣


/*
3��cookie��session
(1)cookie�Ƿ��͵��ͻ���������ı���������������ڿͻ���Ӳ���ϣ�����������ĳ��Webվ��Ự֮��־õر������ݡ�cookie�ڿͻ��ˡ�
(2)session�Ƿ����ߴӵ���ĳ���ض���ҳ���뿪Ϊֹ���Ƕ�ʱ�䡣ÿһ�����߶��ᵥ�����һ��session��ʵ��վ�����û�֮��������ҳ���й�����Ϣ��session�ڷ������ϡ�
(3)libcurl��ʹ��cookie,����cookie, ʹ֮��������������ʹ����ͬ��cookie
(3.1)�ڹر����ӵ�ʱ���cookieд��ָ�����ļ�:  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "/tmp/cookie.txt");
(3.2)ȡ�������е�cookie���������µõ�cookie:  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt");
*/