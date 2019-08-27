#include"CLogger.h"
#include"DateTiime.h"
#include"CMutex.h"

//TO DO: Need to read the logging PATH from the env/config file.
const std::string CLogger::m_FileName="/tmp/logging.txt";
ofstream CLogger::m_HandleFile;

CLogger* CLogger::m_ThisLogger = NULL;
/**
 * @breif : This is not thread safe singleton approach,
 *          comment out the below method if you want a 
 *          thread safe Singleton CLogger class.
 */
clogger* clogger::getlogger(){
    if (m_thislogger == null){
        m_thislogger = new clogger();
        m_handlefile.open(m_filename.c_str(), ios::out | ios::app);
    }
    return m_thislogger;
}
/**
 * @brief: Two cases are handled for thread safe Singleton
 *         Logger Class.
 *         case 1: Double checking : Double checking of 
 *         {if (m_thislogger == null)} is done to address 
 *         the case where, if one thread find the object is 
 *         not created it will go for the creation of the object,
 *         while the object is in the process of creation, if 
 *         another thread also tried to creat the object the 
 *         condition if (m_thislogger == null) is also valid for
 *         the second thread, hence it is require to double check
 *         the singleton object.
 *
 *         Case 2: Why taking mutex lock after the first null check
 *         i.e {if (m_thislogger == null) mtx.lock(); } and why not
 *         {mtx.lock(); if (m_thislogger == null) }
 *
 *         Reason: The purpose of singleton class is to create the 
 *         single object and only let the thread to take the 
 *         lock if the object is not yet created, if the mtx.lock() is
 *         put before the null check , even if the object is created 
 *         every time every thread will unnecessry  take a lock
 *         before checking if the object is already created. So to avoid 
 *         this scenario, it is require to take the lock after the null check.
 */
/*
clogger* clogger::getlogger(){
    CMutex mtx;
    if (m_thislogger == null) {
       //Enter the critical section.
       mtx.lock(); 
    if (m_thislogger == null){
        m_thislogger = new clogger();
        m_handlefile.open(m_filename.c_str(), ios::out | ios::app);
    }
    //Leave the critical section.
    mtx.unlock();
  }
    return m_thislogger;
}*/

CLogger& CLogger::operator<<(const std::string &message) {

	m_HandleFile.open(m_FileName.c_str(), ios::out|ios::app);
	m_HandleFile<<"\n"<<DateTime::getCurrentDateTime()<<":\t";
	m_HandleFile<<message<<"\n";
	m_HandleFile.close();
	return *this;
}

void CLogger::Log(const std::string &message) {
		
	m_HandleFile.open(m_FileName.c_str(), ios::out|ios::app);
	m_HandleFile<<"\n"<<DateTime::getCurrentDateTime()<<":\t";
	m_HandleFile<<message<<"\n";
	m_HandleFile.close();
}

void CLogger::Log(const char* format, ...) {
	
	char buff[256] = {0};
	va_list args;
	va_start(args,format);
	vsnprintf(buff, sizeof(buff), format, args);
	m_HandleFile.open(m_FileName.c_str(), ios::out|ios::app);
	m_HandleFile<<"\n"<<DateTime::getCurrentDateTime()<<":\t";
	m_HandleFile<<buff<<"\n";
	m_HandleFile.close();
	va_end(args);

}
