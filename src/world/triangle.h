#ifndef TRIANGLE
#define TRIANGLE

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"

#include <cglm/struct.h>

#pragma GCC diagnostic pop

struct Triangle {
    vec3s position;
    vec3s color;

    float *vertices;
    int vertices_size;
    int *indices;
    int indices_size;
};

void triangle_init (struct Triangle *self, vec3s position, vec3s color);

#endif