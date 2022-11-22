#include "triangle.h"

struct World {
    struct Triangle *triangles;
    int triangles_size;
};

void world_init (struct World *self);