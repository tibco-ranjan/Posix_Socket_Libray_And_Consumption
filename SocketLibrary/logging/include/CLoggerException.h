#ifndef _EX_H
#define _EX_H
#include"aupe.h"
class CLoggerException:public std::exception {
public:
        CLoggerException(const std::string &message, bool syeError=false) throw();
        const char* what() const throw();
        virtual ~CLoggerException() throw();
protected:
        std::string m_message;
};
#endif /*_EX_H*/
