#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "./world/triangle.h"
#include "./util/util.h"

#define WIDTH  1920
#define HEIGHT 1920

int main(int args, char *argv[]) {
	size_t triangles_size;
	struct Triangle *triangles;

	triangles_size = 3;
	triangles = malloc(triangles_size * sizeof(struct Triangle));
	triangle_one(&triangles[0]);
	triangle_two(&triangles[1]);
	triangle_three(&triangles[2]);

	vec3s colorTmp;
	colorTmp = GLMS_VEC3_ZERO;
 
    int num = WIDTH * HEIGHT * 3;
	unsigned char *colors = calloc(num, sizeof(char));
	int offset = 0;
    float fov = 51.52; 
    float scale = tan(glm_rad(fov * 0.5)); 
    float imageAspectRatio = WIDTH / (float)HEIGHT; 
    vec3s orig;
	orig = GLMS_VEC3_ZERO; 
	size_t i, j, triangle_idx;
    for (j = 0; j < WIDTH; j++) { 
        for (i = 0; i < HEIGHT; i++) {
            // compute primary ray
            float x = (2 * (i + 0.5) / (float) WIDTH - 1) * imageAspectRatio * scale; 
            float y = (1 - 2 * (j + 0.5) / (float)HEIGHT) * scale; 
            vec3s dir;
			dir = (vec3s) {{x, y, -1}}; 
            glms_normalize(dir);
			float t_min = INFINITY;
			for (triangle_idx = 0; triangle_idx < triangles_size; triangle_idx++) {
				float t, u, v;
				if (ray_triangle_intersect(orig, dir, triangles[triangle_idx].v0, triangles[triangle_idx].v1, triangles[triangle_idx].v2, &t, &u, &v) && t < t_min) {
					glm_vec3_zero(colorTmp.raw);
					colorTmp = glms_vec3_muladds(triangles[triangle_idx].color_v0, u, colorTmp);
					colorTmp = glms_vec3_muladds(triangles[triangle_idx].color_v1, v, colorTmp);
					colorTmp = glms_vec3_muladds(triangles[triangle_idx].color_v2, (1 - u - v), colorTmp);

					colors[offset] = (int) (255 * colorTmp.r);
					colors[offset + 1] = (int) (255 * colorTmp.g);
					colors[offset + 2] = (int) (255 * colorTmp.b);
					t_min = t;
				}
			}
			offset += 3;
        } 
    }
	stbi_write_bmp("output.bmp", WIDTH, HEIGHT, 3, colors); // generates and image with the specified width, height, and color buffer
}
