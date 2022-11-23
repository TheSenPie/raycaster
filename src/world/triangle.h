#ifndef TRIANGLE
#define TRIANGLE

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"

#include <cglm/struct.h>

#pragma GCC diagnostic pop

struct Triangle {
    vec3s v0;
    vec3s v1;
    vec3s v2;

    vec3s color_v0;
    vec3s color_v1;
    vec3s color_v2;
};

void triangle_one (struct Triangle *self);
void triangle_two (struct Triangle *self);
void triangle_three (struct Triangle *self);

#endif