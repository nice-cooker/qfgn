/*=============================================================================
#
#     FileName: sig_check.h
#         Desc: ͳһ��ǩ����֤��
#               oauth��: http://liboauth.sourceforge.net/index.html
#
#       Author: dantezhu
#        Email: zny2008@gmail.com
#     HomePage: http://www.vimer.cn
#
#      Created: 2011-09-05 19:22:47
#      Version: 0.0.1
#      History:
#               0.0.1 | dantezhu | 2011-09-05 19:22:47 | initialization
#
=============================================================================*/
/*
������ƽ̨������Ӧ�á�ǩ������sig��˵��
sig:
������Դ���Լ���Կ����һ��ǩ���������ɵ�ǩ��ֵ��������ߴ�����̲����ķ��۸��ԡ�
ǩ��ֵ�����ɹ���3�����裺����Դ����������Կ������ǩ��ֵ����������������

һ.˵��
    1.�������URI·������URL���루URI����host����/user/info����
    2.����"sig"������в�����key�����ֵ��������С�
    3.����2���������Ĳ���(key=value)��&ƴ��������������URL���롣
    4.��HTTP����ʽ��GET����POST���Լ���1���͵�3���е��ַ�����&ƴ��������
        HTTP����ʽ & urlencode(uri) & urlencode(a=x&b=y&...)
    5.������Կ������&һ��Ҫ�У�����Ϊ�˺�hmac-sha1�㷨ͳһ����url:http://tools.ietf.org/html/rfc5849#section-3.4.2��
        shared-secret&
    6.���õ�Դ������Կ����HMAC-SHA1���ܣ��õ���buf����Base64�����ֵ��sig�������ֱ���ü�ͨ�Ľӿ���֤�Ļ���Ҫ����base64��decode���ѽ�����buf����ͨ��

��.����Դ��
    ԭʼ������Ϣ
        HTTP����ʽ��GET
        shared-secret��123456
        �����URI·��������HOST����/user/info

    ���������
        openid=11111111111111111&openkey=2222222222222222

    ���濪ʼ����sig�� 
    1.�������URI·������URL���룬�õ���
        %2Fuser%2Finfo
    2.����"sig"������в�����key�����ֵ��������У��õ���
        openid, openkey
    3.����2���������Ĳ���(key=value)��&ƴ��������������URL����
        openid=11111111111111111&openkey=2222222222222222
    4.��HTTP����ʽ����1���Լ���3���еĵ����ַ�����&ƴ������,�õ�Դ����
        GET&%2Fuser%2Finfo&openid%3D11111111111111111%26openkey%3D2222222222222222

��.������Կ
    1.��shared-secretĩβ����һ���ֽڵ�: &���õ�:
        123456&

��.����ǩ��
    1.ʹ��HMAC-SHA1�����㷨�����ڶ����еĵ���Դ���Լ���������ȡ����Կ���м��ܡ�
    2.Ȼ�󽫼��ܺ���ַ�������Base64���룬���õ�"sig"ǩ��������ֵ��
*/

#ifndef _SIG_CHECK_H_20110905192345_
#define _SIG_CHECK_H_20110905192345_
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#ifdef __cplusplus
extern "C"{
#endif
#include "oauth.h"

#ifdef __cplusplus
};
#endif

using namespace std;

#ifndef SIGCHECK_ERROR
#define SIGCHECK_ERROR(fmt, args...) \
    snprintf(m_szErrMsg, sizeof(m_szErrMsg), "[%s][%d][%s]"fmt, \
             __FILE__, __LINE__,__FUNCTION__, ##args)
#endif


namespace NS_SIG_CHECK
{

    struct StSigInfo
    {
        string method; // GET or POST
        string url_path;
        map<string, string> params;

        string share_secret;

        string desc()
        {
            stringstream ss;
            //ss << endl;
            ss << "share_secret:" << share_secret; //<< endl;
            ss << " method:" << method;// << endl;
            ss << " url_path:" << url_path ;//<< endl;

            ss << " params:" ;//<< endl;

            for(map<string, string>::iterator it = params.begin(); it != params.end(); ++it)
            {
                ss << it->first << ":" << it->second <<" ";//<< endl;
            }

            return ss.str();
        }
    };

    class CSigCheck
    {
    public:
        CSigCheck() {}
        virtual ~CSigCheck() {}

        const char* GetErrMsg() { return m_szErrMsg; }

        string Create(StSigInfo& data)
        {
            string source;

            //ת��Ϊ��д
            transform(data.method.begin(), data.method.end(), data.method.begin(), ::toupper);

            source.append(data.method);
            source.append("&");
            source.append(url_encode(data.url_path));
            source.append("&");
            source.append(url_encode(join_params(data.params)));
			
			//cout << "join_params(data.params)=" << join_params(data.params) << endl;

            char* p_sig = oauth_sign_hmac_sha1_raw(
                source.c_str(),
                source.size(), 
                data.share_secret.c_str(),
                data.share_secret.size());

            if (p_sig == NULL)
            {
                return "";
            }

            string sig = p_sig;;

            delete [] p_sig;
            p_sig = NULL;

            return sig;
        }

        int Check(StSigInfo& data, const string& param_sig)
        {
            if (param_sig.empty())
            {
                SIGCHECK_ERROR("param_sig is empty");
                return -1;
            }

            string real_sig = Create(data);

            if (real_sig != param_sig)
            {
                SIGCHECK_ERROR("sig not match,param_sig[%s], real_sig[%s], sig_info[%s]", 
                               param_sig.c_str(), 
                               real_sig.c_str(),
                               data.desc().c_str()
                               );
                return -2;
            }

            return 0;
        }

    public:
        string url_encode(const string& src)
        {
            char* p_dest = oauth_url_escape(src.c_str());
            if (p_dest == NULL)
            {
                return "";
            }
            string str_dest = p_dest;

            delete [] p_dest;
            p_dest = NULL;

            str_dest = replace_str(str_dest, "~", "%7E");

            return str_dest;
        }

        string join_params(map<string,string> &params)
        {
            string source;
            for(map<string, string>::iterator it = params.begin(); it != params.end(); ++it)
            {
                if (it != params.begin())
                {
                    source.append("&");
                }
                source.append(it->first);
                source.append("=");
                source.append(it->second);
            }

            return source;
        }
		
		string http_join_params(map<string,string> &params)
        {
            string source;
            for(map<string, string>::iterator it = params.begin(); it != params.end(); ++it)
            {
                if (it != params.begin())
                {
                    source.append("&");
                }
                source.append(it->first);
                source.append("=");
                source.append(url_encode(it->second));
            }

            return source;
        }

        string replace_str(string src,const string& old_value,const string& new_value)
        {
            for(string::size_type pos(0); pos != string::npos; pos += new_value.size()) 
            {
                if((pos=src.find(old_value, pos)) != string::npos)
                {
                    src.replace(pos, old_value.size(), new_value);
                }
                else 
                {
                    break;
                }
            }
        
            return src;
        }

    private:
        char m_szErrMsg[512];
    };

} /* NS_SIG_CHECK */
#endif
