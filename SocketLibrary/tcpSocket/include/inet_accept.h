#ifndef _INET_ACCEPT_H
#define _INET_ACCEPT_H

#define TRUE             1
#define FALSE            0

int non_blocking_accept
(
  const int listen_sd
);

int blocking_accept
(
	const int listen_sd
);
#endif /*_INET_ACCEPT_H*/
