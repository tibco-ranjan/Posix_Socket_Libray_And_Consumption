#ifndef _DATE_TIME_H
#define _DATE_TIME_H
#include<time.h>
#include"aupe.h"
namespace DateTime
{
	const std::string getCurrentDateTime() {
		
		char buff[80] = {0};
		time_t now = time(NULL);
		struct tm tstruct;
		localtime_r(&now, &tstruct);
		strftime(buff, sizeof(buff), "%Y-%m-%d.%X", &tstruct);
		return buff;
	}
}
#endif /*_DATE_TIME_H*/
