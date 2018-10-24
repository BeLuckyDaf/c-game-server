#include "headers.h"

#define BUFSIZE 100
#define LOGIN_SERVICE_PORT 10910
#define GAME_SERVICE_PORT 10900
#define MAX_PENDING_CONNECTIONS 3

void *start_login_service() {
    int logsock = socket(AF_INET, SOCK_STREAM, 0);
    printf("<login service>: created socket %d\n", logsock);
    
    struct sockaddr_in logaddr;
    logaddr.sin_addr.s_addr = INADDR_ANY;
    logaddr.sin_family = AF_INET;
    logaddr.sin_port = htons(LOGIN_SERVICE_PORT);

    bind(logsock, (struct sockaddr*)&logaddr, sizeof(logaddr));
    printf("<login service>: socket bound to local address\n");

    listen(logsock, MAX_PENDING_CONNECTIONS);
    printf("<login service>: listening on port %d\n", LOGIN_SERVICE_PORT);

    struct sockaddr_in claddr;
    socklen_t cllen;
    int clsock = accept(logsock, (struct sockaddr*)&claddr, &cllen);

    return NULL;
}

int main() {
    start_login_service();
    return 0;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    printf("<main>: socket descriptor: %d\n", sock);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(GAME_SERVICE_PORT);

    bind(sock, (struct sockaddr*)&servaddr, sizeof(servaddr));

    char buf[BUFSIZE];
    struct sockaddr_in clientaddr;
    int clen = sizeof(clientaddr);
    printf("<main>: server sockaddr %lu\n", (unsigned long)&servaddr);
    printf("<main>: client sockaddr %lu\n", (unsigned long)&clientaddr);

    /* ssize_t size = recvfrom(sock, buf, BUFSIZE, MSG_DONTWAIT,
                            (struct sockaddr*)&clientaddr, &clen); */

    close(sock);

    return 0;
}