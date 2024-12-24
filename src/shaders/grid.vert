#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 color_in;
layout (location = 2) in vec3 offset_in;

out vec3 customColor;

uniform vec3 offsets[1000]; // This needs to be at least the amount of squares in the grid

void main() {
    gl_Position = vec4(vertex_position + offset_in, 1.0);
    customColor = color_in;
}