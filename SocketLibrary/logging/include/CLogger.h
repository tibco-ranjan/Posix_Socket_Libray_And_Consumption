#ifndef _CLOGGER_H
#define _CLOGGER_H
#include"aupe.h"
#define LOGGER CLogger::GetLogger()
/**
 * @brief: It is a singleton Logger class
 *          Can we use in multithreading 
 *          This class is used for logging the 
 *          erro, warning or information. 
 *          TO Do: Need to leverage for verbositiy 
 *          level.
 */
class CLogger {
public:
	void Log(const std::string &message);
	void Log(const char* format, ...);
	CLogger& operator<<(const std::string &message);
	static CLogger *GetLogger();
private:
	CLogger(){}
	~CLogger(){};
	CLogger(const CLogger&){}
	CLogger &operator=(const CLogger &){return *this;}
	
	static const std::string m_FileName;
	static ofstream m_HandleFile;
	static CLogger *m_ThisLogger;
};
#endif /*_CLOGGER_H*/
