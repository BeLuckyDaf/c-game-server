#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "common.h"
#include "types.h"
#include <string.h>

/** stores player id and position */
struct player_data {
    uint id;
    int x;
    int y;
};

/** stores player data and client address
 *  for internal purposes */
struct client_data {
    int sockfd;
    struct sockaddr_in addr;
    struct player_data data;
};

/** type definition for pointers */
typedef struct player_data* p_player_data;
typedef struct client_data* p_client_data;
/* making it simpler to assign list data */
typedef struct p_client_data* p_client_list;
typedef struct p_player_data* p_player_list;

/** creates a pointer to a dynamically allocated
 *  array for client_data of size count */
p_client_list create_client_list(uint count);
p_player_data create_player();
p_player_data create_player_at(int x, int y);

#endif
