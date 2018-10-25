#include "server.h"

void *establish_client_connection() {
    return NULL;
}

void *start_login_service() {
    should_accept_connections = 1;

    int logsock = socket(AF_INET, SOCK_STREAM, 0);
    if (logsock == -1) error("could not create socket", errno);
    printf("<login service>: created socket %d\n", logsock);
    
    struct sockaddr_in logaddr;
    logaddr.sin_addr.s_addr = INADDR_ANY;
    logaddr.sin_family = AF_INET;
    logaddr.sin_port = htons(LOGIN_SERVICE_PORT);

    if (bind(logsock, (struct sockaddr*)&logaddr, sizeof(logaddr)) == -1)
        error("could not bind to port", errno);
    printf("<login service>: socket bound to local address\n");

    if (listen(logsock, MAX_PENDING_CONNECTIONS) == -1) 
        error("could not start to listen", errno);
    printf("<login service>: listening on port %d\n", LOGIN_SERVICE_PORT);

    struct sockaddr_in claddr; // client address
    socklen_t cllen;
    int clsock;

    while(should_accept_connections) {
        clsock = accept(logsock, (struct sockaddr*)&claddr, &cllen);
        // create a client, give it some id
        // wait for the client's requests 
        // (guess that is going to be another thread)
        // satisfy them if valid
        // p.s. requests such as put me into game,
        // send me the map of the game 'x', etc.
        // if a client disconnects from here
        // purge them from all games and services
    }
    return NULL;
}

int main() { // WILL BE MOVED TO MAIN.C

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