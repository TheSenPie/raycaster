#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define WIDTH  512
#define HEIGHT 512

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
// 	int num = WIDTH * HEIGHT * 3;
// 	unsigned char colors[num];
// 	for (int i = 0; i < num; i = i + 3) {
// 		colors[i] = 225;
// 		colors[i + 1] = i % 255 ;
// 		colors[i + 2] = 100;
// 	}
// 	stbi_write_bmp("output.bmp", WIDTH, HEIGHT, 3, colors); // generates and image with the specified width, height, and color buffer
// }
