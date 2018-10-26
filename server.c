#include "server.h"

void *establish_client_connection(void* cldata) {
    p_client_data data = (p_client_data)cldata;
    p_message message = create_message(SMSG_VERIFY_CONNECTION, 0, NULL);
    send_message(data->sockfd, message);
    
    message = receive_message(data->sockfd);
    // verify somehow

    return NULL;
}

void *start_login_service() {
    client_list = create_client_list(MAX_CLIENTS);
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
        p_client_data cldata = (p_client_data)malloc(sizeof(struct client_data));
        cldata->addr = claddr;
        cldata->sockfd = clsock;

        // send client to establish connection 
        
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

    pthread_create(&login_thread, NULL, start_login_service, NULL);
    pthread_join(login_thread, NULL);

    return 0;
}