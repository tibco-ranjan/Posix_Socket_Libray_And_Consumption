#include"CLogger.h"
#include"DateTiime.h"
#include"CMutex.h"

//TO DO: Need to read the logging PATH from the env/config file.
const std::string CLogger::m_FileName="/tmp/logging.txt";
ofstream CLogger::m_HandleFile;

CLogger* CLogger::m_ThisLogger = NULL;
CLogger* CLogger::GetLogger(){
    if (m_ThisLogger == NULL){
        m_ThisLogger = new CLogger();
        m_HandleFile.open(m_FileName.c_str(), ios::out | ios::app);
    }
    return m_ThisLogger;
}
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


