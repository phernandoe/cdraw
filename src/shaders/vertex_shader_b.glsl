#version 400

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 color_in;

out vec3 customColor;

uniform vec3 offsets[2];

void main() {
    vec3 offset = offsets[gl_InstanceID];
    gl_Position = vec4(vertex_position + offset, 1.0);

    customColor = color_in;
}
