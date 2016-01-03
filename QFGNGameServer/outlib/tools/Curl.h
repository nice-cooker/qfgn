//Curl.h
#ifndef _TAOTAO_PUBLIC_CURL_H
#define _TAOTAO_PUBLIC_CURL_H

#include "curl/curl.h"
#include <iostream>
using namespace std;
class Curl
{
	public:
		Curl() : m_curl(curl_easy_init()), m_slist(0L) {}
		CURL* curl() { return m_curl; }

		~Curl()
		{
			if (m_slist) curl_slist_free_all(m_slist);
			curl_easy_cleanup(m_curl);
		}

		static string escape(const string& str)
		{
			char* ret = curl_escape(str.c_str(), str.length());
			if (!ret) return "";

			string val(ret, strlen(ret));
			curl_free(ret);
			return val;
		}

		void addHeader(const string& name, const string& value)
		{
			char header[4096];
			snprintf(header, 4096, "%s: %s", name.c_str(), value.c_str());

			m_slist = curl_slist_append(m_slist, header);
		}

		struct Result
		{
			CURLcode code;
			string data;
		};

		Result get2(const string& url, long timeoutMillis = 1000, long connectTimeoutMillis = 500)
		{
			Result rc;

			if (m_slist)
				curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_slist);

			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str()))
			&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &Curl::write_data_to_string))
			&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &(rc.data)))
			&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1))
			&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT_MS, connectTimeoutMillis))
			&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeoutMillis))
			&&
			CURLE_OK  == (rc.code = curl_easy_perform(m_curl));

			return rc;

		}

		string get(const string& url, const string& sCookie, long timeoutMillis = 1000, long connectTimeoutMillis = 1000)
		{
			string data;			

			if (m_slist)
				curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_slist);

            CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L)
            &&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str())
			&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &Curl::write_data_to_string)
			&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &data)
			&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1)
			&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT_MS, connectTimeoutMillis)
			&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeoutMillis)
			&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_COOKIE, sCookie.c_str())
			&&
			CURLE_OK  == curl_easy_perform(m_curl);

			return data;
		}

		string post(const string& url, const void * data, size_t len, long timeoutMillis = 800)
		{
			string result;

			if (m_slist)
				curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_slist);

            CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L)
                &&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str())
				&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data)
				&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, len)
				&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &Curl::write_data_to_string)
				&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &result)
				&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1)
				&&
			CURLE_OK == curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeoutMillis)
				&&
			CURLE_OK == curl_easy_perform(m_curl);

			return result;
		}

		Result post2(const string& url, const void * data, size_t len, long timeoutMillis = 800, long connectTimeoutMillis = 500)
		{
			Result rc;

			if (m_slist)
				curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_slist);

			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str()))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, len))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &Curl::write_data_to_string))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &(rc.data)))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_TIMEOUT_MS, timeoutMillis))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT_MS, connectTimeoutMillis))
				&&
			CURLE_OK == (rc.code = curl_easy_perform(m_curl));

			return rc;
		}

		//≤ª…Ë÷√≥¨ ±
		Result post_unlimit_time(const string& url, const void * data, size_t len, long timeoutMillis = 800, long connectTimeoutMillis = 500)
		{
			Result rc;

			if (m_slist)
				curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, m_slist);

			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str()))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, data))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, len))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &Curl::write_data_to_string))
				&&
			CURLE_OK == (rc.code = curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &(rc.data)))
				&&
			CURLE_OK == (rc.code = curl_easy_perform(m_curl));

			return rc;
		}
	private:
		static size_t write_data_to_string(void *ptr, size_t size, size_t nmemb, void* context)
		{
			string* data = (string*)context;
			(*data) += string((char*)ptr, (int)size*nmemb);
			return size*nmemb;
		}
	private:
		CURL* m_curl;
		curl_slist* m_slist;
};

#endif
