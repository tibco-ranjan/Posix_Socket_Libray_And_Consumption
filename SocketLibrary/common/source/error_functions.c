#include<stdarg.h>
#include<error_functions.h>
#include<get_num.h>
#include"tlpi_hdr.h"
#define BUFF_SIZE 256
#ifdef __GNUC__
__attribute__((__noreturn__))
#endif
/**
 * @brief: Note: Difference between exit() and _exit()
 *
 * There are the differences:
   _exit() won't flushes the stdio buffer while exit() flushes the stdio buffer prior to exit.
   _exit() can not perform clean-up process while exit() can be registered with some function.
    ( i.e on_exit or at_exit) to perform some clean-up process if anything is required before 
   existing the program.

   exit(status) simply passes the exit status to _exit(status). It is recommended that 
   whenever to perform fork(), one of them between child and parent, one use _exit() and 
   another use exit().
 */


/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : termination function with the provision of 
 * 					 core dump [YES/NO] 
 */
static void
terminate(BOOLEAN useExit) {

	char *s = NULL;
	s=getenv("EF_DUMPCORE");

	if( NULL != s ) {
		abort();
	} else if ( useExit ) {
		exit(EXIT_FAILURE);
	} else {
		_exit(EXIT_FAILURE);
	}
}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : Method to print the message with or without 
 * 					 errorno message. 
 * 					 
 */
static void
outputMessage(BOOLEAN useErrNo,
	      int err,
	      BOOLEAN flushBuffer,
	      const char* format,
	      va_list argList) {
	

	char buff[256] = {'\0'};
	char errMsg[256] = {'\0'};
	char usrMsg[256] = {'\0'};

	vsnprintf(usrMsg, BUFF_SIZE, format, argList);
   
	if(useErrNo) {
	   snprintf(errMsg, BUFF_SIZE, " error=[%d] : [%s] ", err, strerror(err)); 
	} else {
	   snprintf(errMsg, BUFF_SIZE, " :");
	}	

	snprintf(buff, BUFF_SIZE, "ERROR::%s %s", usrMsg, errMsg);
	if(flushBuffer){
		fflush(stdout);
	}
	fputs(buff, stderr);
	fflush(stderr);
}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : Method to print the message with 
 * 					 errno message, without exit or _exit
 * 					 call.
 */
void 
errMsg(const char* format, ...) {
	int saveError;
	saveError = errno;
	va_list arglist;
	va_start(arglist, format);
	outputMessage(TRUE,errno, TRUE, format, arglist);
	va_end(arglist);
	errno = saveError;
	
}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : Method to print the message with 
 * 					 errno message, with exit.
 */
void 
errExit(const char* format, ...) {
	va_list arglist;
	va_start(arglist, format);
	outputMessage(TRUE,errno,TRUE,format,arglist);
	va_end(arglist);
  terminate(TRUE);	
}


/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : Method to print the message with 
 * 					 errno message, with _exit.
 */
void 
err_exit(const char* format, ...) {
	va_list arglist;
	va_start(arglist, format);
	outputMessage(TRUE,errno,FALSE,format,arglist);
	va_end(arglist);
	terminate(FALSE);
}


/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : Method to print the message with
 * 					 errno message, with exit call.
 */
void 
errExitEN(int errNum, const char* format, ...) {
	va_list arglist;
	va_start(arglist, format);
	outputMessage(TRUE,errNum,TRUE,format,arglist);
	va_end(arglist);
  terminate(TRUE);	
}


/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : Method to print the message with
 * 					 errno message, with _exit call.
 */
void 
fatal(const char* format, ...) {
	va_list arglist;
	va_start(arglist, format);
	outputMessage(FALSE,0,TRUE,format,arglist);
	va_end(arglist);
  terminate(TRUE);	

}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : Method to print the uses error.
 */
void
usageErr(const char *format, ...)
{
	va_list arglist;
	fflush(stdout);
	fprintf(stderr, "Usages:");
	va_start(arglist, format);
	vfprintf(stderr,format, arglist);
	va_end(arglist);
	fflush(stderr);
	exit(EXIT_FAILURE);
}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : Method to print the command line argument
 * 					 error.
 */
void
cmdLineErr(const char *format, ...)
{
	va_list arglist;
	fflush(stdout);
	fprintf(stderr, "Command line Usages:");
	va_start(arglist, format);
	vfprintf(stderr,format, arglist);
	va_end(arglist);
	fflush(stderr);
	exit(EXIT_FAILURE);
}
