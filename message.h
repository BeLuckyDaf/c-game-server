#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "headers.h"

struct message_header {
    int msgcode;
    size_t plsize;
};

struct message {
    struct message_header header;
    void *payload;
};

typedef struct message_header* p_message_header;
typedef struct message* p_message;

int tryread(int sockfd, void* buf, size_t len);
p_message_header receive_header(int sockfd);
p_message receive_message(int sockfd, p_message_header header);

#endif