#version 400

out vec4 fragColour;
in vec3 customColor;

void main() {
    fragColour = vec4(customColor, 1.0);
}
