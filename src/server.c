#include "server.h"

void *process_client_connection(void *cldata) {
    p_client_data data = (p_client_data)cldata;
    p_message message = create_message(SMSG_VERIFY_CONNECTION, 0, NULL);
    printf("Client connected: %s:%d\n", inet_ntoa(data->addr.sin_addr), ntohs(data->addr.sin_port));
    send_message(data->sockfd, message);

    while((message = receive_message(data->sockfd))->header.msgcode > 0);
    printf("MSGCODE: %d\n");
    if (message->header.msgcode == BMSG_POSITIVE) log("Client verified connection.");
    else log("Connection discarded.");

    printf("Client sockfd: %d.\n", data->sockfd);

    // other things here
    close(data->sockfd);

    return NULL;
}

void *accept_connections(void *svinfo) {
    p_server_info info = (p_server_info)svinfo;
    int aptcon = 1;
    info->aptcon = &aptcon;

    // client data
    struct sockaddr_in claddr;
    socklen_t cllen = sizeof(struct sockaddr_in);
    int clsock;
    p_client_data cldata;

    // accept loop
    while(*info->aptcon) {
        cldata = (p_client_data)malloc(sizeof(struct client_data));
        clsock = accept(info->sockfd, (struct sockaddr*)&claddr, &cllen);
        cldata->addr = claddr;
        cldata->sockfd = clsock;

        // add a thread for a client
        pthread_t tid;
        pthread_create(&tid, NULL, info->conn_handler, (void*)cldata);
    }
}

p_server_info create_tcp_server(char* alias, unsigned short port, void *(*conn_handler)(void*)) {
    // creating a login socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) error("could not create socket", errno);
    printf("<%s>: created socket %d\n", alias, sock);

    // address for login socket
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    // binding socket to port
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
        error("could not bind to port", errno);
    printf("<%s>: socket bound to local address\n", alias);

    // starting listening for connections
    if (listen(sock, MAX_PENDING_CONNECTIONS) == -1)
        error("could not start to listen", errno);
    printf("<%s>: listening on port %d\n", alias, port);

    // create info structure
    p_server_info svinfo = (p_server_info)malloc(sizeof(struct server_info));
    svinfo->sockfd = sock;
    svinfo->conn_handler = conn_handler;
    svinfo->aptcon = NULL;

    // accept connections in a different thread
    pthread_create(&svinfo->tid, NULL, accept_connections, (void*)svinfo);

    return svinfo;
}

int main() { // WILL BE MOVED TO MAIN.C

    p_server_info svinfo = create_tcp_server("login", LOGIN_SERVICE_PORT, process_client_connection);
    pthread_join(svinfo->tid, NULL);

    return 0;
}
