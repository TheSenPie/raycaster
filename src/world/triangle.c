#include "triangle.h"

void triangle_one (struct Triangle *self) {
    self->v0 = (vec3s) {{-1.5f, -1.0f, -5.0f}};
    self->v1 = (vec3s) {{ 0.5f, -1.0f, -5.0f}};
    self->v2 = (vec3s) {{ -0.5f,  1.0f, -5.0f}};

    self->color_v0 = (vec3s) {{1.0f, 0.0f, 0.0f}};
    self->color_v1 = (vec3s) {{0.0f, 1.0f, 0.0f}};
    self->color_v2 = (vec3s) {{0.0f, 0.0f, 1.0f}};
}

void triangle_two (struct Triangle *self) {
    self->v0 = (vec3s) {{-1.0f, -1.0f, -5.0}};
    self->v1 = (vec3s) {{ 1.0f, -1.0f, -5.0}};
    self->v2 = (vec3s) {{ 0.0f,  1.0f, -5.0}};

    self->color_v0 = (vec3s) {{ 0.0f, 1.0f, 1.0f}};
    self->color_v1 = (vec3s) {{ 1.0f, 0.0f, 1.0f}};
    self->color_v2 = (vec3s) {{ 1.0f, 1.0f, 0.0f}};
}

void triangle_three (struct Triangle *self) {
    self->v0 = (vec3s) {{-0.5f, -1.0f, -5.0f}};
    self->v1 = (vec3s) {{1.5f, -1.0f, -5.0f}};
    self->v2 = (vec3s) {{0.5f,  1.0f, -5.0f}};
    
    self->color_v0 = (vec3s) {{ 0.5f, 0.7f, 0.3f}};
    self->color_v1 = (vec3s) {{ 0.3f, 0.5f, 0.7f}};
    self->color_v2 = (vec3s) {{ 0.7f, 0.3f, 0.5f}};
}