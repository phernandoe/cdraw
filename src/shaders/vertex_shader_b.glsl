#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 color_in;

out vec3 customColor;

void main() {
    customColor = color_in;
    gl_Position = vec4(vertex_position, 1.0);
}
