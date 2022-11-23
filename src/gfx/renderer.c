#include "stdio.h"

#include "renderer.h"

void renderer_init(struct Renderer *self) {
    *self = (struct Renderer) {0};
    self->camera_type = CAMERA_PERSPECTIVE;
    self->current_shader = SHADER_NONE;

    self->shaders[SHADER_BASIC_COLOR] = shader_create(
        "res/shaders/basic_color.vs", "res/shaders/basic_color.fs",
        1, (struct VertexAttr[]) {
            { .index = 0, .name = "position" }
        }
    );

    self->vao = vao_create();
    self->vbo = vbo_create(GL_ARRAY_BUFFER, false);
    self->ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    perspective_camera_init(&self->perspective_camera, radians(75.0f));

    // set clear color
    self->clear_color.r = 0.2f;
    self->clear_color.g = 0.3f;
    self->clear_color.b = 0.3f;
    self->clear_color.a = 1.0f;
}

void renderer_destroy(struct Renderer *self) {
    for (size_t i = 0; i <= SHADERS_LAST; i++) {
        shader_destroy(self->shaders[i]);
    }

    vao_destroy(self->vao);
    vbo_destroy(self->vbo);
    vbo_destroy(self->ibo);
}

void renderer_prepare(struct Renderer *self) {
    glClearColor(
        self->clear_color.x, self->clear_color.y,
        self->clear_color.z, self->clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, self->flags.wireframe ? GL_LINE : GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void renderer_set_camera(struct Renderer *self, enum CameraType type) {
    self->camera_type = type;
}

void renderer_set_view_proj(struct Renderer *self) {
    struct ViewProj view_proj;

    switch (self->camera_type) {
        case CAMERA_PERSPECTIVE:
            view_proj = self->perspective_camera.view_proj;
            break;
        case CAMERA_ORTHO:
            view_proj = self->ortho_camera.view_proj;
            break;
    }

    shader_uniform_view_proj(self->shader, view_proj);
}

void renderer_use_shader(struct Renderer *self, enum ShaderType shader) {
    if (shader == self->current_shader) {
        return;
    }

    self->current_shader = shader;
    self->shader = self->shaders[shader];
    shader_bind(self->shader);
}

void renderer_triangle(struct Renderer *self, struct Triangle *triangle) {
    vao_bind(self->vao);
    vbo_bind(self->vbo);
    vbo_bind(self->ibo);

    renderer_use_shader(self, SHADER_BASIC_COLOR);
    renderer_set_view_proj(self);

    mat4s model = GLMS_MAT4_IDENTITY;
    shader_uniform_mat4(self->shader, "m", model);

    vbo_buffer(self->vbo, triangle->vertices, 0, triangle->vertices_size * sizeof(float));

    vbo_buffer(self->ibo, triangle->indices, 0, triangle->indices_size * sizeof(int));

    vao_attr(self->vao, self->vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), 0);
    vao_attr(self->vao, self->vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (3 * sizeof(GLfloat)));

    glDrawElements(GL_TRIANGLES, triangle->indices_size, GL_UNSIGNED_INT, (void *) 0);
}
