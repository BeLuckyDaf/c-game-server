#ifndef _GAME_H_
#define _GAME_H_

#include "player.h"
#include "map.h"

struct game_instance {
    p_client_data players;
    p_map map;
};

typedef struct game_instance* p_game_instance;

p_game_instance create_instance(uint map_width, uint map_height, uint max_players);

#endif