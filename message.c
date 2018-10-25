#include "message.h"

int tryread(int sockfd, void* buf, size_t len) {
    size_t total_bytes = 0;
    size_t bytes_read;
    while(total_bytes < len) {
        bytes_read = read(sockfd, (char*)buf + total_bytes, len-total_bytes);
        if (bytes_read == -1) error("error reading socket", -3); // return -1
        total_bytes += bytes_read;
    }

    return 0;
}

p_message_header receive_header(int sockfd) {
    p_message_header header = (p_message_header)malloc(sizeof(struct message_header));
    if (tryread(sockfd, header, sizeof(header)) == 0) 
        return header;
    return NULL;
}

p_message receive_message(int sockfd, p_message_header header) {
    p_message message = (p_message)malloc(sizeof(struct message));
    message->header = *header;
    if (tryread(sockfd, message->payload, message->header.plsize) == 0)
        return message;
    return NULL;
}