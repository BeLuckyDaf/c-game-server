#include "message.h"

p_message create_message(int msgcode, size_t plsize, void* pl) {
    p_message message = (p_message)malloc(sizeof(struct message));
    message->header.msgcode = msgcode;
    message->header.plsize = plsize;
    message->payload = pl;

    return message;
}

int try_read(int sockfd, void *buf, size_t len) {
    size_t total_bytes = 0;
    ssize_t bytes_read;
    while(total_bytes < len) {
        bytes_read = read(sockfd, (char*)buf + total_bytes, len-total_bytes);
        if (bytes_read == -1) {
            log("error reading socket");
            return -1;
        }
        total_bytes += bytes_read;
    }

    return 0;
}

int try_write(int sockfd, void *buf, size_t len) {
    size_t total_bytes = 0;
    ssize_t bytes_sent;
    while(total_bytes < len) {
        bytes_sent = write(sockfd, (char*)buf + total_bytes, len-total_bytes);
        if (bytes_sent == -1) {
            log("error writing to socket");
            return -1;
        }
        total_bytes += bytes_sent;
    }

    return 0;
}

int send_header(int sockfd, p_message_header header) {
    if (try_write(sockfd, header, sizeof(struct message_header)) == 0)
        return 0;
    return -1;
}

int send_payload(int sockfd, void* payload, size_t len) {
    if (len == 0 || try_write(sockfd, payload, sizeof(len)) == 0)
        return 0;
    return -1;
}

int send_message(int sockfd, p_message message) {
    if (send_header(sockfd, &message->header) != 0)
        error("error sending header", -5); // return -1
    if (send_payload(sockfd, message->payload, message->header.plsize) != 0)
        error("error sending payload", -6); // return -2
    return 0;
}

p_message_header receive_header(int sockfd) {
    p_message_header header = (p_message_header)malloc(sizeof(struct message_header));
    if (try_read(sockfd, header, sizeof(struct message_header)) == 0)
        return header;
    return NULL;
}

p_message receive_payload(int sockfd, p_message_header header) {
    p_message message = (p_message)malloc(sizeof(struct message));
    memset(message, 0, sizeof(struct message));
    message->header = *header;
    if (try_read(sockfd, message->payload, message->header.plsize) == 0)
        return message;
    return NULL;
}

p_message receive_message(int sockfd) {
    p_message_header header = receive_header(sockfd);
    return receive_payload(sockfd, header);
}
