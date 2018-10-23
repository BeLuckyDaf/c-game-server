#ifndef _MAP_H_
#define _MAP_H_

#include <stdlib.h>
#include "types.h"

#define POINT_TYPE_FREE 0
#define POINT_TYPE_SOLID 1

#define MAX_POINT_TYPE_NUMBER 1

struct map_point {
    int type;
};

struct map {
    uint width;
    uint height; // supposed to be a 2d world
    struct map_point* points; // must be an array of length width * height
};

typedef struct map * p_map;
typedef struct map_point * p_map_point;

p_map create_map(uint width, uint height, p_map_point initial);
int set_point(struct map* pmap, uint x, uint y, int type);

#endif