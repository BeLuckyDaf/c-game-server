#ifndef _HEADERS_H_
#define _HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/errno.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void error(char* msg, int code);

#endif