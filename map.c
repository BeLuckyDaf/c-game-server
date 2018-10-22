#include "map.h"

PMAP create_map(uint width, uint height, PMAP_POINT initial) {
    PMAP map = (PMAP)malloc(sizeof(struct map));

    if (initial == NULL)
        map->points = (PMAP_POINT)calloc(width * height, sizeof(struct map_point));
    else
        map->points = initial;

    map->width = width;
    map->height = height;
}

int change_point(PMAP pmap, uint x, uint y, int type) {
    if (type > MAX_POINT_TYPE_NUMBER) return -1;

    return pmap->points[pmap->width*y + x].type = type;
}