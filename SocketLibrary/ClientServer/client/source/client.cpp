#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "inet_socket.h"
#include "inet_handle_multiplex_io.h"
#include "CLogger.h"

#define MAXDATASIZE 128 // max number of bytes we can get at once


void func(int sockfd) 
{ 
		char buff[MAXDATASIZE]; 
		int n; 


		for (;;) { 

						int status = inet_handle_multiplex_io(sockfd, 5);
						if ( status < 0 )
						{
										cout<<"Failed to handle non blocking connection" <<endl;
										return ;
						}				

						bzero(buff, sizeof(buff)); 
						printf("\nEnter the stock price : "); 
						n = 0; 
						while ((buff[n++] = getchar()) != '\n') 
										; 
						write(sockfd, buff, sizeof(buff)); 
						bzero(buff, sizeof(buff)); 
						read(sockfd, buff, sizeof(buff)); 
						printf("From Server : %s", buff); 
						if ((strncmp(buff, "exit", 4)) == 0) { 
										printf("Client Exit...\n"); 
										break; 
						} 
		} 
} 


int main(int argc, char *argv[])
{
		int status = 0;
		int connect_fd = 0;

		if (argc != 2) {
						fprintf(stderr,"usage: client hostname\n");
						exit(1);
		}

		status = inet_connect_non_blocking(argv[1], PORT_NUM, SOCK_STREAM, &connect_fd);
		if( status < 0)
		{
						LOGGER->Log("client failed to connect the server %s with status=%d", argv[1], status);
						return -1;
		}
		else
		{
						LOGGER->Log("client connected to server %s, with connection fd=%d", argv[1], connect_fd);
		}

		//Function to Chat with server.
		func(connect_fd);	

		//Close the socket
		close(connect_fd);
		return 0;
}
