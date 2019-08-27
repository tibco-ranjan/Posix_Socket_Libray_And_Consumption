#include "inet_socket.h"
#include "inet_accept.h"
#include "CLogger.h"

using namespace std;

#define TRUE             1
#define FALSE            0


int main (int argc, char *argv[])
{
		int    status = 0;
		//Need to read from the configruation file the server kind
		//NON_BLOCKING = 1
		bool is_non_blcking = true;
		int listen_sd;

		status = inet_listen(NULL, PORT_NUM, SOCK_STREAM, &listen_sd, is_non_blcking);
		if( status < 0)
		{
						LOGGER->Log("server failed with status=%d", status);
						return -1;
		}
		else
		{
						LOGGER->Log("server started with status=%d, for listen fd=%d", status, listen_sd);
		}

		status = non_blocking_accept(listen_sd);
		if(status < 0)
		{
						LOGGER->Log("non_blocking_accept failed with  status==%d", status);
		}

		return 0;
}
