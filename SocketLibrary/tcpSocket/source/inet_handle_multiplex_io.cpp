#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "inet_socket.h"
#include "inet_handle_multiplex_io.h"
#include "CLogger.h"

#define MAXDATASIZE 128 // max number of bytes we can get at once

/**
 *@author : Ravi Prasad (India).
 *
 *@brief  : This method handles the non blocking I/O 
 *         operation, can be use by both active and 
 *         passive(client or server) socket to monitor 
 *         multiple I/O at their side. uses select call
 *         for monitoring multiple I/Os.
 *
 *@param  : [in] sockfd {socket/file fd monior for I/O}
 *@param  : [in] nsec   {select timeout in seconds}        
 */
int inet_handle_multiplex_io
(
	const int sockfd,
	int nsec
)
{
	fd_set rset, wset;
	struct timeval  tval;
	int n, error, numbytes = 0;
	socklen_t len;
	char buf[MAXDATASIZE];

	FD_ZERO(&rset);
	FD_SET(sockfd, &rset);
	wset = rset;
	tval.tv_sec = nsec;
	tval.tv_usec = 0;

	if ( (n = select(sockfd+1, &rset, &wset, NULL,
					 nsec ? &tval : NULL)) == 0) 
	{
		close(sockfd);		/* timeout */
		errno = ETIMEDOUT;
		return(-1);
	}

	if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset)) 
	{
		len = sizeof(error);
		if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
			return(-1);			/* Solaris pending error */
	} 

	if( FD_ISSET(sockfd, &rset) )
	{
		cout <<"Connection socket ready to read\n";
		if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) > 0) {
				cout<<buf<<endl;
		}
	}
	else if( FD_ISSET(sockfd, &wset) )
	{
		cout <<"Connection socket ready to write\n";
		if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) > 0) {
				cout<<buf<<endl;
		}
	}
	else
	{
		cout<<"select error: sockfd not set" <<endl;
	}
	return 0;
}
