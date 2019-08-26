#include"inet_socket.h"
#include"readLine.h"
#include"CLogger.h"

/**
 * @author : Ravi Prasad (India)
 *
 * @brief   : get sockaddr, IPv4 or IPv6 ip address
 *           Note: Used in inet_ntop method.
 *
 * @param  : [in] sa sockaddr
 * @return : struct sockaddr_in/in6 with void 
 */
void *get_in_addr
(
	struct sockaddr *sa
)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief   : get sockaddr, IPv4 or IPv6 port number
 *           Note: Used in ntohs method.
 *
 * @param  : [in] sa sockaddr
 * @return : struct sin/in6_port   
 */

in_port_t get_in_port
(
	struct sockaddr *sa
)
{
    if (sa->sa_family == AF_INET) {
        return (((struct sockaddr_in*)sa)->sin_port);
    }

    return (((struct sockaddr_in6*)sa)->sin6_port);
}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : get sockaddr, IPv4 or IPv6 
 * 					 IP address and port number
 *           Note: Used to get the connecting client
 *           IP address and port number as a part of 
 *           accept call.
 *
 * @param  : [in] sa sockaddr, accept api second parameter
 * @param  : [out] peer_name {connecting client name or IP}
 * @param  : [out] peer_port {connecting client port number}
 * @return : -1 FAIL , 0 SUCCESS 
 */
int get_peer_addr_with_peer_sock
(
	const struct sockaddr *peer_sock, 
  char* peer_name, 
	unsigned short *peer_port
)
{

	if(peer_sock == NULL) 
		return -1;

	if(peer_sock->sa_family == AF_INET)
	{
		struct sockaddr_in *ipv4 = (struct sockaddr_in*)&peer_sock;
		*peer_port = ntohs(ipv4->sin_port);
		inet_ntop(AF_INET, &ipv4->sin_addr, peer_name, INET_ADDRSTRLEN);
	}
	else if(peer_sock->sa_family == AF_INET6) 
	{
		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*)&peer_sock;
		*peer_port = ntohs(ipv6->sin6_port);
		inet_ntop(AF_INET6, &ipv6->sin6_addr, peer_name, INET6_ADDRSTRLEN);
	}
	return 0;
}


/**
 * @author : Ravi Prasad (India)
 *
 * @brief  : get sockaddr, IPv4 or IPv6 
 * 					 IP address and port number
 *           Note: Used to get the connecting client
 *           IP address and port number as a part of 
 *           accept call. I prefer this call to get the 
 *           detalis of peer or connecting client information.
 *
 * @param  : [in] int fd {accept api return value socket fd}
 * @param  : [out] peer_name {connecting client name or IP}
 * @param  : [out] peer_port {connecting client port number}
 * @return : -1 FAIL , 0 SUCCESS 
 */
int get_peer_addr_with_peer_conn_fd
(
	const int fd, 
	char* peer_name, 
	unsigned short *peer_port
) 
{
	
	const char* const who = "get_peer_addr_with_peer_conn_fd";
	struct sockaddr_storage peer_sock;
	socklen_t len;
	len = sizeof(peer_sock);
	
	int status = 0;
	if((status = getpeername(fd, (struct sockaddr*)&peer_sock, &len)) == -1) {
		LOGGER->Log("%s:: getpeername failed with %s", who, gai_strerror(status));
		return -1;
	}

	if(peer_sock.ss_family == AF_INET)
	{
		struct sockaddr_in *ipv4 = (struct sockaddr_in*)&peer_sock;
		*peer_port = ntohs(ipv4->sin_port);
		inet_ntop(AF_INET, &ipv4->sin_addr, peer_name, INET_ADDRSTRLEN);
	}
	else if(peer_sock.ss_family == AF_INET6) 
	{
		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6*)&peer_sock;
		*peer_port = ntohs(ipv6->sin6_port);
		inet_ntop(AF_INET6, &ipv6->sin6_addr, peer_name, INET6_ADDRSTRLEN);
	}
	return status;
}

/**
 *@author : Ravi Prasad (India)
 *
 *@brief  : Internal method to set the O_NONBLOCK (non-blocking)
 *					attribute of a file descriptior.
 *@param  : [in] file descriptor id.
 *@param  : [in] non-blocking boolean flag.
 *@return : boolean Success:TRUE Fail:FALSE  
 */
bool SetSocketNonBlocking 
(
	const int fd, 
	bool is_non_blocking
)
{
   if (fd < 0) return false;
   int flags = fcntl(fd, F_GETFL, 0);

   if (flags == -1) return false;
   flags = is_non_blocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief  :Blocking connect call for the client.
 * @param  :[in] host {host name/url of the server.}
 * @param  :[in] service {port number or service name}
 * @param  :[in] sock_type {type of socket STREAM/DGRAM}
 * @param  :[out] connected fd 
 * @return :status -1: FAIL >0 : SUCCESS.					  
 */
int inet_connect_blocking
(
	const char* host, 
	const char* service, 
	int sock_type, 
	int *connect_fd
)
{
	//const char* const who = "inet_connect";
	std::string who = "inet_connect";
	struct addrinfo hints;
	struct addrinfo *servinfo, *res;
	
	int sfd, rv=0, status=0;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof(hints));
	
	hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = sock_type;
	
	if((status = getaddrinfo(host, service, &hints, &servinfo) != 0 )){
		LOGGER->Log("%s:: getaddrinfo failed with error =%s", who.c_str(), gai_strerror(status));
		return -1;
	}

	for(res=servinfo; res != NULL; res=servinfo->ai_next)
	{
		if((sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
			LOGGER->Log("%s:: inet_connect failed", who.c_str());
			continue;
		}

		cout<<"Trying to connect with the sfd="<<sfd <<endl;
		if((rv = connect(sfd, res->ai_addr, res->ai_addrlen)) == -1)
		{
				LOGGER->Log("%s:: client connect call failed for socket fd=%d with error '%s' and errono = %d", who.c_str(), sfd, gai_strerror(rv), errno);
				close(sfd);
				continue;			
		}
		cout<<"Scuccessfully connected to the sever "<<host <<" on the port=" <<service <<endl;
		break; 
	}

	if( res != NULL)
	{
		
		inet_ntop(res->ai_family, get_in_addr((struct sockaddr *)res->ai_addr), s, sizeof(s));
		short port_num = ntohs(get_in_port((struct sockaddr *)res->ai_addr));
		LOGGER->Log("%s:: client: connecting to address:: %s  with port %d", who.c_str(), s, port_num); 
	}
	else
	{
		LOGGER->Log("%s:: client failed to connect to the server", who.c_str());
		return -1;
	}
	
	*connect_fd = sfd;	
	freeaddrinfo(servinfo);
	return sfd;
}

/**
 * @author : Ravi Prasad (India)
 *
 * @brief  :Non Blocking connect call for the client.
 * @param  :[in] host {host name/url of the server.}
 * @param  :[in] service {port number or service name}
 * @param  :[in] sock_type {type of socket STREAM/DGRAM}
 * @param  :[out] connected fd 
 * @return :status -1: FAIL 0: SUCCESS.					  
 */
int inet_connect_non_blocking
(
	const char* host, 
	const char* service, 
	int sock_type, 
	int *connect_fd
)
{
	//const char* const who = "inet_connect";
	std::string who = "inet_connect";
	struct addrinfo hints;
	struct addrinfo *servinfo, *res;
	
	int sfd, rv=0, status=0, flags;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof(hints));
	
	hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = sock_type;
	
	if((status = getaddrinfo(host, service, &hints, &servinfo) != 0 )){
		LOGGER->Log("%s:: getaddrinfo failed with error =%s", who.c_str(), gai_strerror(status));
		return -1;
	}

	for(res=servinfo; res != NULL; res=servinfo->ai_next)
	{
		if((sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
			LOGGER->Log("%s:: inet_connect failed", who.c_str());
			continue;
		}

		flags = fcntl(sfd, F_GETFL, 0);
		bool ret_non_blocking = SetSocketNonBlocking(sfd, true);
		if(false == ret_non_blocking)
		{
						LOGGER->Log("%s:: Client failed to set connection socket in non blocking mode", who.c_str());
						close(sfd);
						return -1;
		}

		if((rv = connect(sfd, res->ai_addr, res->ai_addrlen)) == -1)
		{
						//As the socket is set into non blocking mode it 
						//might failed with EINPROGRESS.
						if( EINPROGRESS == errno ) 
						{
										cout<<"connection to  "<<host <<" on the port=" <<service << " is in progress" <<endl;
						}
						//Connection completed immmediately.
						else if( 0 == rv )
						{
								/*resotre the sockt status flags*/
								fcntl(sfd, F_SETFL, flags);
						}
						else
						{	
										LOGGER->Log("%s:: client connect call failed for socket fd=%d with error '%s' and errono = %d", who.c_str(), sfd, gai_strerror(rv), errno);
										close(sfd);
										continue;
						}			
		}
		break; 
	}

	if( res != NULL)
	{
		
		inet_ntop(res->ai_family, get_in_addr((struct sockaddr *)res->ai_addr), s, sizeof(s));
		short port_num = ntohs(get_in_port((struct sockaddr *)res->ai_addr));
		LOGGER->Log("%s:: client: connecting to address:: %s  with port %d", who.c_str(), s, port_num); 
	}
	else
	{
		LOGGER->Log("%s:: client failed to connect to the server", who.c_str());
		return -1;
	}
	
	*connect_fd = sfd;	
	freeaddrinfo(servinfo);
	return sfd;
}

/**
 *@author : Ravi Prasad (India)
 *
 *@brief  : Server side socket preparation method.
 *					It performs following tasks.
 *					1. creates a socket of the given type, bound to the wildcard
 *					IP address on the port specified by service and type. (The 
 *					socket type indicates	whether this is a TCP or UDP service.)
 *
 *					2.creates a listening stream (SOCK_STREAM) socket bound
 *					to the wildcard IP address on the TCP port specified by service
 *
 *					3.Set the socket fd in blocking/non-blocking mode.
 *
 *					4.Provides a listening for (TCP) or binding for (UDP) soceket
 *					  via inet_listen() and inet_bind() call respectively.
 *
 * @param  :[in] host {host name/url of the server.}
 * @param  :[in] service {port number or service name}
 * @param  :[in] sock_type {type of socket STREAM/DGRAM}
 * @param  :[in] do_listen {true for TCP false for UDP}
 * @param  :[in] backlog {The backlog argument specifies
 * 							 the permitted backlog of pending connections
 * 							(as for listen()).}
 * @param  :[in] is_non_blocking {flag to set the passive socket
 * 							in blocking or non blocking mode}
 * @param  :[out] listen_fd {Resulted TCP passive (server) socket id}
 * @return : -1 : FAIL >0 : SUCCESS	 
 */
int inet_passive
(
	const char* host,
	const char* service, 
	int sock_type, 
	bool do_listen, 
	int backlog, 
	int *listen_fd,
	bool is_non_blocking)
{
	//const char* const who = "inet_passive";
	std::string  who = "inet_passive";
	struct addrinfo hints;
	struct addrinfo *servinfo, *res;
	
	int sfd, yes=1, status=0;
	memset(&hints, 0, sizeof(hints));
	
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = sock_type;
	hints.ai_flags = AI_PASSIVE;

	

	if((status = getaddrinfo(host, service, &hints, &servinfo) != 0 )){
		LOGGER->Log("%s:: getaddrinfo failed with error =%s", who.c_str(), gai_strerror(status));
		return -1;
	}

	for(res=servinfo; res != NULL; res=servinfo->ai_next){
				
		if((sfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1){
			LOGGER->Log("%s:: inet_connect failed", who.c_str());
			continue;
		}
		
		if(do_listen) {
			if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1){
				LOGGER->Log("%s:: setscokopt failed", who.c_str());
				freeaddrinfo(servinfo);
				return -1;
			}
			
			if(true == is_non_blocking)
			{
				bool ret_non_blocking = SetSocketNonBlocking(sfd, true);
				if(false == ret_non_blocking)
				{
					LOGGER->Log("%s:: Failed to set socket in non blocking mode", who.c_str());
					close(sfd);
					return -1;
				}
			}
		}

		if(bind(sfd, res->ai_addr, res->ai_addrlen) == -1){
			LOGGER->Log("%s:: socket bind failed", who.c_str());
			close(sfd);
			continue;
		}
		break;
	}

	if(do_listen && res != NULL){
		if(listen(sfd, backlog) == -1){
			LOGGER->Log("%s:: listen failed", who.c_str());
			freeaddrinfo(servinfo);
			return -1;
		}		

	}

	*listen_fd = sfd;
	freeaddrinfo(servinfo);
	return (res != NULL ) ? sfd : -1;
}

/**
 *@author : Ravi Prasad (India)
 *
 *@brief  : This function creates a socket of the given type, 
 *					bound to the wildcard IP address on the port specified 
 *					by service and type. (The socket type indicates whether 
 *					this is a TCP or UDP service.) This function is designed 
 *					(primarily) for UDP servers and clients to create a 
 *					socket bound to a specific address. 
 * @param  :[in] host {host name/url of the server.}
 * @param  :[in] service {port number or service name}
 * @param  :[in] sock_type {type of socket STREAM/DGRAM}
 * @param  :[in] is_non_blocking {flag to set the passive socket
 * 							in blocking or non blocking mode}
 * @param  :[out] connected fd 
 */
int inet_bind
(
	const char *host,
	const char* service, 
	int sock_type,
	int *connect_fd,
	bool  is_non_blocking
)
{
	return inet_passive(host, service, sock_type, NOT_LISTEN, 0, connect_fd, is_non_blocking);
}

/**
 *@author : Ravi Prasad (India)
 *
 *@brief  : This function creates a listening stream (SOCK_STREAM) 
 *					socket bound to the wildcard IP address on the TCP port 
 *					specified by service. This function is designed for use 
 *					by TCP servers 
 *
 * @param  :[in] host {host name/url of the server.}
 * @param  :[in] service {port number or service name}
 * @param  :[in] sock_type {type of socket STREAM/DGRAM}
 * @param  :[in] is_non_blocking {flag to set the passive socket
 * 							in blocking or non blocking mode}
 * @param  :[out] connected listening server socket fd 
 */
int inet_listen
(
	const char *host,
	const char* service, 
	int sock_type,
	int *listen_fd,
	bool is_non_blocking
)
{
	return inet_passive(host, service, sock_type, LISTEN, BACKLOG, listen_fd, is_non_blocking);
}

