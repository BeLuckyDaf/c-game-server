#include "player.h"

p_client_data create_client_list(uint count) {
    p_client_data list = (p_client_data)malloc(count * sizeof(struct client_data));
    memset(list, 0, count * sizeof(struct client_data));
}