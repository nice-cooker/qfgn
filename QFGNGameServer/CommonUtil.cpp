#include "CommonUtil.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>

  
namespace CommonUtil
{
    int addInt(int i, int k)
    {
       int t = i + k;
       if (t < 0) 
           return MAX_INT;
       return t;
    }

    int getThisWeekSundayZeroTime()
    {
        time_t tNow = time(0);
        time_t tZeroTime = tNow - (tNow + 8 * 3600)%(24 * 3600);
        tm * tmZero = localtime(&tZeroTime);  
        return tZeroTime - tmZero->tm_wday * 24 * 3600; 
    }
   
    int getRandomValue(int iStart, int iEnd)
    {
		srand(time(0));
        if (iEnd < iStart)
            return 0;

        if (iEnd == iStart)
            return iEnd;

        int iRand = iEnd - iStart;
        return rand()%(iRand+1) + iStart;
    }

	bool checkTwoDayAdjoin( time_t time1, time_t time2 )
	{
		tm tm1;
		tm tm2;
		tm * tmPtr = localtime(&time1);
		memcpy(&tm1, tmPtr, sizeof(tm));

		tmPtr = localtime(&time2);
		memcpy(&tm2, tmPtr, sizeof(tm));

		int iDis = tm2.tm_yday - tm1.tm_yday;

		return  iDis == 1;
	}

	bool checkTwoTimeInSameDay( time_t time1, time_t time2 )
	{
		tm tm1;
		tm tm2;
		tm * tmPtr = localtime(&time1);
		memcpy(&tm1, tmPtr, sizeof(tm));

		tmPtr = localtime(&time2);
		memcpy(&tm2, tmPtr, sizeof(tm));

		return (tm2.tm_yday == tm1.tm_yday);
	}


	map<int, int>::iterator randomWeight(map<int, int> & mapWeight)
   {
        int iTotalWeight = 0;
        for (map<int, int>::iterator it = mapWeight.begin(); it != mapWeight.end(); ++it)
        {
            iTotalWeight += it->second;
        }
        int iRandValue = getRandomValue(1, iTotalWeight); 
        int iWeight = 0;
        for (map<int, int>::iterator it = mapWeight.begin(); it != mapWeight.end(); ++it)
        {
           if (iRandValue >= iWeight && iRandValue < (iWeight+=it->second)) 
               return it;
        }
        return mapWeight.end();
   }

};
