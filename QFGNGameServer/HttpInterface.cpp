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
	// 清空m_stlist
	if (NULL != m_stlist)
	{
		curl_slist_free_all(m_stlist);  
	}

	//清空CURL  
	if (NULL != m_pcurl)
	{
		curl_easy_cleanup(m_pcurl);
	}

	// 清空全局设置  
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
	参数：flags
	CURL_GLOBAL_ALL        //初始化所有的可能的调用。
	CURL_GLOBAL_SSL        //初始化支持 安全套接字层。
	CURL_GLOBAL_WIN32      //初始化win32套接字库。
	CURL_GLOBAL_NOTHING   //没有额外的初始化
	*/
	m_curlcode = curl_global_init(CURL_GLOBAL_ALL);  
	if (CURLE_OK != m_curlcode)  
	{
		cout << "curl_global_init err, m_curlcode:" << m_curlcode << endl;
		return -1;  
	} 

	//获取CURL的指针
	m_pcurl= curl_easy_init();
	if (m_pcurl == NULL)
	{
		cout << "Failed to create CURL connection" << endl;
		return -1;
	}
	//设置私有的错误缓冲区.
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_ERRORBUFFER,m_ccurlerrorinfo);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set error m_ccurlerror:" << m_curlcode << endl;
		return -1;
	}

	// 设置curl允许执行的最长秒数，超时时间  
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

	//设置协议版本
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
	//请求设置为标准的HTTP POST请求  
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_POST, 1);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set http post:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	// 设置头部信息  
	struct curl_slist *stlist = NULL;  
	unsigned int uiContentLength = (unsigned int) sPostFields.size();  // 发送内容大小  
	char szContentLength[100];  
	snprintf(szContentLength, sizeof(szContentLength), "Content-Length: %u", uiContentLength);  
	stlist = curl_slist_append(stlist, szContentLength);  
	stlist = curl_slist_append(stlist, "Content-Type: text/plain");

	//设置HTTP头信息，传送的内容格式为text/xml  
	curl_easy_setopt(m_pcurl, CURLOPT_HTTPHEADER, stlist);

	cout << "POST FIELD LENGTH:" << uiContentLength << endl;


	//设置待发送的POST数据的长度。这样将避免libcurl通过strlen来计算待发送的数据的长度，从而允许发送内容中包括\0字符。  
	curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t) uiContentLength);  

	//待发送的数据，数据是作为标准的HTTP body内容发送，而不是通过发送文件的形式发送  
	curl_easy_setopt(m_pcurl, CURLOPT_POSTFIELDS, sPostFields.c_str()); 

	//从server返回的内容将写入该指针所指向的地址  
	//curl_easy_setopt(m_pcurl, CURLOPT_WRITEDATA, &strResp);  

	//设置回调函数处理从server返回的内容  
	//curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, &processXML);
	return 0;
}

int THttpAsync::doSyncHttpRequest()
{
	//设置要访问的url地址.
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_URL, m_strurl.c_str());
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set URL:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	// 执行https请求  
	m_curlcode = curl_easy_perform(m_pcurl);  
	int lRespCode = 0;

	//获取HTTP响应码  
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
	//设置要访问的url地址.
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_URL, m_strurl.c_str());
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set URL:" << m_ccurlerrorinfo << endl;
		return -1;
	}

	//设置写回调函数
	m_curlcode = curl_easy_setopt(m_pcurl, CURLOPT_WRITEFUNCTION, &callbackFor1);
	if (m_curlcode != CURLE_OK)
	{
		cout << "Failed to set write function option :" << m_ccurlerrorinfo << endl;
		return -1;
	}

	//设置写回调函数数据写到的地方
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



//首先curl_slist_append()函数是很有用的，
//因为如果你什么都不写，
//CUrl会传输一个类似"Get /你的网页 accept: */*"之类的简单协议，
//在某些验证较为严格的服务器，这样的Http链接协议字会被丢弃的。也就是说啥都不给你返回，不够千万不要郁闷，
// Curl的设计者早就给你想好了，curl_slist_append()这个API可以让你伪装成一个标准的网页浏览器的请求，
// 诚然，你们也看到了，我追加了一些Http的选项，这些选项将会附加在你的Http请求中。
// 这样就能顺利的通过那些严格验证的服务器，让它给你返回正确的数据。
// 当然，这里的前提是你必须对Http 1.1协议有一些了解。


/*
3、cookie与session
(1)cookie是发送到客户浏览器的文本串句柄，并保存在客户机硬盘上，可以用来在某个Web站点会话之间持久地保持数据。cookie在客户端。
(2)session是访问者从到达某个特定主页到离开为止的那段时间。每一访问者都会单独获得一个session，实现站点多个用户之间在所有页面中共享信息。session在服务器上。
(3)libcurl中使用cookie,保存cookie, 使之后的链接与此链接使用相同的cookie
(3.1)在关闭链接的时候把cookie写入指定的文件:  curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "/tmp/cookie.txt");
(3.2)取用现在有的cookie，而不重新得到cookie:  curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt");
*/