#ifndef _SERVER_H_
#define _SERVER_H_

#include "common.h"
#include "player.h"
#include "message.h"
#include "msgcodes.h"

#define BUFSIZE 100
#define LOGIN_SERVICE_PORT 10910
#define GAME_SERVICE_PORT 10900
#define MAX_PENDING_CONNECTIONS 3
#define MAX_CLIENTS 5

struct server_info {
    int sockfd;
    int *aptcon;
    pthread_t tid;
    void *(*conn_handler)(void*);
};

typedef struct server_info* p_server_info;

int should_accept_connections;
p_client_data client_list;

pthread_t login_thread;

void *start_login_service();
void *process_client_connection(void *cldata);

#endif
