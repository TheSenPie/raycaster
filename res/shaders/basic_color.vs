#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 m, v, p;

out vec3 color;

void main() {
    color = aColor;
    gl_Position = p * v * m * vec4(aPos, 1.0);
}