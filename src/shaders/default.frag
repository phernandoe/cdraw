#version 400

out vec4 fragColour;
in vec3 customColor;

uniform float time;

void main() {
    vec3 c = 0.5 + 0.5 * cos(time + customColor);
    fragColour = vec4(c, 1.0);
}
