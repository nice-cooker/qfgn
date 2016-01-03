#ifndef _COMM_UTIL_H_
#define _COMM_UTIL_H_

#include<time.h>
#include<map>
#include<string>
#include <iostream>
#include <sstream>




#define MAX_INT 2147483647
using namespace std;

namespace CommonUtil
{
   int addInt(int i, int k);
   
   int getThisWeekSundayZeroTime();
   
   int getRandomValue(int iStart, int iEnd);

   //检查两天是否相邻 -- 后者大
   bool checkTwoDayAdjoin(time_t time1, time_t time2);

   bool checkTwoTimeInSameDay(time_t time1, time_t time2);


   //根据权重随机 value:weight
   map<int, int>::iterator randomWeight(map<int, int> & mapWeight);


   template<typename T>
   T strto(const string &sStr, const string &sDefault)
   {
	   string s;

	   if(!sStr.empty())
	   {
		   s = sStr;
	   }
	   else
	   {
		   s = sDefault;
	   }

	   istringstream sBuffer(s);

	   T t;
	   sBuffer >> t;

	   return t;
   }

   template<typename T>
   string tostr(const T &t)
   {
	   ostringstream sBuffer;
	   sBuffer << t;
	   return sBuffer.str();
   }

};
#endif  //_COMM_UTIL_H_
