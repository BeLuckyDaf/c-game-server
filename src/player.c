#include "player.h"

p_client_list create_client_list(uint count) {
    p_client_data list = (p_client_data)malloc(count * sizeof(struct client_data));
    memset(list, NULL, count * sizeof(struct client_data));
}

int add_client_to_list(p_client_data* list, size_t size, p_client_data data) {
    int _iter = -1;

    while(list[++_iter] != NULL) if (_iter == size-1) return -1;
    list[_iter] = data;

    return _iter;
}

p_player_data create_player() {
    static uint _curid = 0;

    p_player_data pdata = (p_player_data)malloc(sizeof(struct player_data));
    pdata->id = _curid++;
    pdata->x = pdata->y = 0;

    return pdata;
}

p_player_data create_player_at(int x, int y) {
    p_player_data pdata = create_player();
    pdata->x = x;
    pdata->y = y;

    return pdata;
}

