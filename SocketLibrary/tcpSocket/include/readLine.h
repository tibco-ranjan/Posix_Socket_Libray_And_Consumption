#ifndef _READ_LINE_H
#define _READ_LINE_H

#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

using namespace std;
/**
 *
 */
ssize_t readLine
(
	int fd, 
	char* buff, 
	size_t n
);
#endif /*_READ_LINE_H*/
