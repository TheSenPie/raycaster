#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH  640
#define HEIGHT 640

#include "gfx/window.h"
#include "world/world.h"
#include "gfx/gfx.h"

#include "state.h"

// global state
struct State state;

void init() {
	state.window = &window;
	renderer_init(&state.renderer);
	world_init(&state.world);
	mouse_set_grabbed(true);
}

void destroy() {
	renderer_destroy(&state.renderer);
}

void tick() {
	state.ticks++;
}

void update() {

	if (state.window->mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].down) {
		state.renderer.perspective_camera.theta -= state.window->mouse.delta.x * 0.01f;
		state.renderer.perspective_camera.fi += state.window->mouse.delta.y * 0.01f;

		perspective_camera_look_at(&state.renderer.perspective_camera, (vec3s) {{0.0f, 0.0f, 0.0f}});
	}
	
    // wireframe toggle (T)
    if (state.window->keyboard.keys[GLFW_KEY_T].pressed) {
        state.renderer.flags.wireframe = !state.renderer.flags.wireframe;
    }

    // mouse toggle (ESC)
    if (state.window->keyboard.keys[GLFW_KEY_ESCAPE].pressed) {
        mouse_set_grabbed(!mouse_get_grabbed());
    }
}

void render() {
	renderer_prepare(&state.renderer);
	mat4s cube_model = GLMS_MAT4_IDENTITY;
	int i;

	for (i = 0; i < state.world.triangles_size; i++) {
		renderer_triangle(&state.renderer, &state.world.triangles[i]);
	}
}

int main(int argc, char *argv[]) {
	window_create(init, destroy, tick, update, render);
	window_loop();
	return 0;
}


// int main(int args, char *argv[]) {
// 	vec3s v0, v1, v2, colorTmp;
// 	v0 = (vec3s) {{-1, -1, -5}};
//     v1 = (vec3s) {{ 1, -1, -5}};
//     v2 = (vec3s) {{ 0,  1, -5}};
// 	colorTmp = GLMS_VEC3_ZERO;
 
//     int num = WIDTH * HEIGHT * 3;
// 	unsigned char *colors = calloc(num, sizeof(char));
// 	int offset = 0;
//     float fov = 51.52; 
//     float scale = tan(glm_rad(fov * 0.5)); 
//     float imageAspectRatio = WIDTH / (float)HEIGHT; 
//     vec3s orig;
// 	orig = GLMS_VEC3_ZERO; 
// 	int i, j;
//     for (j = 0; j < WIDTH; j++) { 
//         for (i = 0; i < HEIGHT; i++) {
//             // compute primary ray
//             float x = (2 * (i + 0.5) / (float) WIDTH - 1) * imageAspectRatio * scale; 
//             float y = (1 - 2 * (j + 0.5) / (float)HEIGHT) * scale; 
//             vec3s dir;
// 			dir = (vec3s) {{x, y, -1}}; 
//             glms_normalize(dir);
//             float t, u, v;
//             if (ray_triangle_intersect(orig, dir, v0, v1, v2, &t, &u, &v)) {
// 				glm_vec3_zero(colorTmp.raw);
// 				colorTmp = glms_vec3_muladds((vec3s) {{1.0f, 0.0f, 0.0f}}, u, colorTmp);
// 				colorTmp = glms_vec3_muladds((vec3s) {{0.0f, 1.0f, 0.0f}}, v, colorTmp);
// 				colorTmp = glms_vec3_muladds((vec3s) {{0.0f, 0.0f, 1.0f}}, (1 - u - v), colorTmp);
// 				// printf("hit x: %d, y: %d, r: %f, g: %f, b: %f\n", j, i, colorTmp.r, colorTmp.g, colorTmp.b);

// 				colors[offset] = (int) (256 * colorTmp.r);
// 				colors[offset + 1] = (int) (256 * colorTmp.g);
// 				colors[offset + 2] = (int) (256 * colorTmp.b);
//             }
// 			offset += 3;
//         } 
//     }
// 	stbi_write_bmp("output.bmp", WIDTH, HEIGHT, 3, colors); // generates and image with the specified width, height, and color buffer
// }
