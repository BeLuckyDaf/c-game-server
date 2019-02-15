#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "common.h"

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

int try_read(int sockfd, void *buf, size_t len);
int try_write(int sockfd, void *buf, size_t len);
p_message_header receive_header(int sockfd);
p_message receive_message_body(int sockfd, p_message_header header);
p_message receive_message(int sockfd);
int send_header(int sockfd, p_message_header header);
int send_payload(int sockfd, void* payload, size_t len);
int send_message(int sockfd, p_message message);
p_message create_message(int msgcode, size_t plsize, void* pl);

#endif
