#include "headers.h"

#define NCON 5
#define BUFSIZE 100

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    printf("socket descriptor: %d\n", sock);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(10900);

    bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));

    char buf[BUFSIZE];
    struct sockaddr_in clientaddr;
    int clen = sizeof(clientaddr);
    printf("server sockaddr %lu\n", (unsigned long)&servaddr);
    printf("client sockaddr %lu\n", (unsigned long)&clientaddr);

    /* ssize_t size = recvfrom(sock, buf, BUFSIZE, MSG_DONTWAIT,
                            (struct sockaddr*)&clientaddr, &clen); */

    close(sock);

    return 0;
}