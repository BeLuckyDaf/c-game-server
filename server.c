#include "server.h"

void *process_client_connection(void *cldata) {
    p_client_data data = (p_client_data)cldata;
    p_message message = create_message(SMSG_VERIFY_CONNECTION, 0, NULL);
    printf("Client connected: %s:%d\n", inet_ntoa(data->addr.sin_addr), ntohs(data->addr.sin_port));
    send_message(data->sockfd, message);

    while((message = receive_message(data->sockfd))->header.msgcode > 0);
    if (message->header.msgcode == 0) printf("Client verified connection.\n");
    else printf("Connection discarded.\n");

    // other things here

    return NULL;
}

void *start_login_service() {
    // initialization
    client_list = create_client_list(MAX_CLIENTS);
    should_accept_connections = 1;

    // creating a login socket
    int logsock = socket(AF_INET, SOCK_STREAM, 0);
    if (logsock == -1) error("could not create socket", errno);
    printf("<login service>: created socket %d\n", logsock);

    // address for login socket
    struct sockaddr_in logaddr;
    logaddr.sin_addr.s_addr = INADDR_ANY;
    logaddr.sin_family = AF_INET;
    logaddr.sin_port = htons(LOGIN_SERVICE_PORT);

    // binding socket to port
    if (bind(logsock, (struct sockaddr*)&logaddr, sizeof(logaddr)) == -1)
        error("could not bind to port", errno);
    printf("<login service>: socket bound to local address\n");

    // starting listening for connections
    if (listen(logsock, MAX_PENDING_CONNECTIONS) == -1)
        error("could not start to listen", errno);
    printf("<login service>: listening on port %d\n", LOGIN_SERVICE_PORT);

    // client data
    struct sockaddr_in claddr;
    socklen_t cllen;
    int clsock;

    // login loop
    while(should_accept_connections) {
        clsock = accept(logsock, (struct sockaddr*)&claddr, &cllen);
        p_client_data cldata = (p_client_data)malloc(sizeof(struct client_data));
        cldata->addr = claddr;
        cldata->sockfd = clsock;

        // add a thread for a client
        process_client_connection(cldata);
    }
    return NULL;
}

int main() { // WILL BE MOVED TO MAIN.C

    pthread_create(&login_thread, NULL, start_login_service, NULL);
    pthread_join(login_thread, NULL);

    return 0;
}
