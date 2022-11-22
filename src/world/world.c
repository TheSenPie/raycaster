#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"

#include <cglm/struct.h>

#pragma GCC diagnostic pop

#include "world.h"

void world_init (struct World *self) {
    self->triangles_size = 1;
    self->triangles = malloc(self->triangles_size * sizeof(struct Triangle));

    int i;

    for (i = 0; i < self->triangles_size; i++) {
        triangle_init(&self->triangles[i], GLMS_VEC3_ZERO, GLMS_VEC3_ZERO);
    }
}