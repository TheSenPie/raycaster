#ifndef RENDERER_H
#define RENDERER_H

#include "../util/util.h"
#include "gfx.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"

#include "../world/triangle.h"

enum FillMode {
    FILL_MODE_FILL, FILL_MODE_LINE
};

#define SHADERS_LAST SHADER_BASIC_COLOR
enum ShaderType {
    SHADER_NONE = 0,
    SHADER_BASIC_COLOR
};

#define CAMERA_STACK_MAX 256

struct Renderer {
    enum CameraType camera_type;
    struct {
        enum CameraType array[CAMERA_STACK_MAX];
        size_t size;
    } camera_stack;

    struct PerspectiveCamera perspective_camera;
    struct OrthoCamera ortho_camera;

    struct Shader shaders[SHADERS_LAST + 1];
    enum ShaderType current_shader;
    struct Shader shader;

    vec4s clear_color;

    struct VBO vbo, ibo;
    struct VAO vao;

    struct {
        bool wireframe : 1;
    } flags;
};

void renderer_init(struct Renderer *self);
void renderer_destroy(struct Renderer *self);
void renderer_update(struct Renderer *self);
void renderer_prepare(struct Renderer *self);
void renderer_set_camera(struct Renderer *self, enum CameraType type);
void renderer_push_camera(struct Renderer *self);
void renderer_pop_camera(struct Renderer *self);
void renderer_set_view_proj(struct Renderer *self);
void renderer_use_shader(struct Renderer *self, enum ShaderType shader);

void renderer_triangle(struct Renderer *self, struct Triangle *triangle);

#endif