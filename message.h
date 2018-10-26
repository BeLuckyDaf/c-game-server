#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "common.h"

/** common messages */

#define BMSG_POSITIVE 0
#define BMSG_NEGATIVE -1
#define BMSG_DISCONNECT -2

/** server messages */

#define SMSG_VERIFY_CONNECTION 1
#define SMSG_REQUEST_NAME 2
#define SMSG_INFO_MAP 3
#define SMSG_INFO_PLAER_LIST 4
#define SMSG_INFO_GAME 5

/** client messages */

#define CMSG_SET_NAME 1
#define CMSG_REQUEST_GAME 2
#define CMSG_REQUEST_PLAYER_LIST 3
#define CMSG_REQUEST_MAP 4

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
int trywrite(int sockfd, void* buf, size_t len);
p_message_header receive_header(int sockfd);
p_message receive_message_body(int sockfd, p_message_header header);
p_message receive_message(int sockfd);
int send_header(int sockfd, p_message_header header);
int send_payload(int sockfd, void* payload, size_t len);
int send_message(int sockfd, p_message message);
p_message create_message(int msgcode, size_t plsize, void* pl);

#endif