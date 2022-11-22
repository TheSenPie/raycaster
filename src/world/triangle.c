#include "triangle.h"

void triangle_init (struct Triangle *self, vec3s position, vec3s color) {
    self->vertices_size = 3 * 3; // x, y, z
    self->vertices = malloc(self->vertices_size * sizeof(float));

    self->indices_size = 3;
    self->indices = malloc(self->indices_size * sizeof(int));

    // x, y, z
    self->vertices[0] = -1;
    self->vertices[1] = -1;
    self->vertices[2] = 0;

    // x, y, z
    self->vertices[3] = 0;
    self->vertices[4] = 1;
    self->vertices[5] = 0;

    // x, y, z
    self->vertices[6] = 1;
    self->vertices[7] = -1;
    self->vertices[8] = 0;

    // bottom left, top, bottom right
    self->indices[0] = 0;
    self->indices[1] = 1;
    self->indices[2] = 2;
}