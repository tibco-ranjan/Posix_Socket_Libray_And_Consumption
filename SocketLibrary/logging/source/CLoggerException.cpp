#include"CLoggerException.h"
/*Example
 * int fun(){
 * 	throw CLoggerException("Can't log the message", true);
 * }
 *
 * int main(){
 * 	try{
 * 		int res=fun();
 * 	}catch(CLoggerException &exp) {
 * 		cout<<exp.what() <<endl;
 * 	}
 * }
 */
CLoggerException::CLoggerException(const std::string &message,
				   bool sysError) throw() 
				   :m_message(message){

	if(sysError){
		m_message.append("::system Error=");
		m_message.append(strerror(errno));
	}
}

const char* CLoggerException::what() const throw() {
	return m_message.c_str();
}
	

CLoggerException::~CLoggerException() throw() {}
