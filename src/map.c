#include "map.h"

p_map create_map(uint width, uint height, p_map_point_list initial) {
    p_map map = (p_map)malloc(sizeof(struct map));

    if (initial == NULL)
        map->points = (p_map_point_list)calloc(width * height, sizeof(p_map_point));
    else
        map->points = initial;

    map->width = width;
    map->height = height;
}

int set_point(p_map map, uint x, uint y, int type) {
    if (type > MAX_POINT_TYPE_NUMBER) return -1;

    return map->points[map->width*y + x]->type = type;
}
