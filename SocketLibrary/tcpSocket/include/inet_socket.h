#ifndef INET_SOCKET_H
#define INET_SOCKET_H
#include "tcp_common.h"

#define LISTEN 1
#define NOT_LISTEN 0
#define BACKLOG 10
#define PORT_NUM "50000"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr
(
	struct sockaddr *sa
);

// get port, IPv4 or IPv6:
in_port_t get_in_port
(
	struct sockaddr *sa
);

int get_peer_addr_with_peer_sock
(
	const struct sockaddr *peer_sock, 
	char* peer_name, 
	unsigned short *port
);

int get_peer_addr_with_peer_conn_fd
(
	const int fd, 
	char* peer_name, 
	unsigned short *port
);

int inet_connect_non_blocking
(
	const char* host, 
	const char* service, 
	int socket_type, 
	int *connect_fd
); 

int inet_connect_blocking
(
	const char* host, 
	const char* service, 
	int socket_type, 
	int *connect_fd
); 

int inet_passive
(
	const char* host, 
	const char* service, 
	int socket_type, 
	bool do_listen, 
	int backlog,
	int *listen_fd,
	bool is_non_blocking = false
); 


int inet_bind
(
	const char* service, 
	int sock_type,
  int *listen_fd,
	bool is_non_blocking
);

int inet_listen
(
	const char* host, 
	const char* service, 
	int sock_type,
	int *listen_fd,
	bool is_non_blocking
);

bool SetSocketBlockingEnabled
(
	const int fd, 
	bool blocking
);

int inet_non_blocking_connect
(
	int sockfd, 
	const struct sockaddr *saptr, 
	socklen_t salen, 
	int nsec
);

int inet_non_blocking_accept
(
	
);

bool inet_set_socket_non_blocking
(
	const int fd, 
	bool blocking
);
#endif /*INET_SOCKET_H*/ 

