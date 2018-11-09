#include "game.h"

p_game_instance create_instance(uint map_width, uint map_height, uint max_players) {
    p_game_instance inst = (p_game_instance)malloc(sizeof(struct game_instance));
    
    inst->map = create_map(map_width, map_height, NULL);
    inst->players = create_client_list(max_players);

    return inst;
}