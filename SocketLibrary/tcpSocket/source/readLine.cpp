#include "readLine.h"
/**
 * @brief: The readLine() function reads bytes from the file referred to by the file descriptor
					argument fd until a newline is encountered. The input byte sequence is returned in
					the location pointed to by buffer, which must point to a region of at least n bytes of
					memory. The returned string is always null-terminated; thus, at most (n – 1) bytes
					of actual data will be returned. On success, readLine() returns the number of bytes of
					data placed in buffer; the terminating null byte is not included in this count.
 * @param: fd [in] file descriptior number.
 * @param: buff [in] buffer to contian the data.
 * @param: n [in] number of bytes expected to read.(should be > 0)
 * @return: Returns number of bytes copied into buffer (excluding
 *				 terminating null byte), or 0 on end-of-file, or –1 on error 
 */
ssize_t
readLine(int fd, char* buff, size_t n)
{

	ssize_t numRead=0;
	size_t  totalRead=0;
	char ch;

	if((buff == NULL) || (n==0)){
		return -1;
	}
	
  /*
	*Addresses following cases.
	*Case 1: read call failed.
  *case 2: there is nothing to read.
  *case 3: A line contains more than n bytes.
	*/
	do{
		numRead = read(fd, &ch, 1);
		if(numRead < 0){
			if (errno == EINTR) 
				continue;
			else 
				return -1;
		}

		if(numRead == 0) {
			if (totalRead == 0) 
				return 0;
			else 
				break;
		}
	
		if(totalRead < n-1 ) {	
			*buff++ = ch;
			totalRead++;
		}

		if(ch == '\n')break;
	
	}while(1);
	*buff = '\0';
	return totalRead;
}
