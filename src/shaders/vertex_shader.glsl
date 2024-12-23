#version 400

layout (location = 0) in vec3 vertex_position;

out vec3 customColor;

void main() {
    //vec2 st = gl_FragCoord.xy / vertex_position.xy;
    vec2 st = vertex_position.xy;
    vec3 red = vec3(1.0, 0.0, 0.0);
    vec3 canvas = vec3(0.0);
    float dimension = 0.3;

    vec2 bottom_left = step(vec2(dimension), st);
    vec2 bottom_right = step(vec2(dimension), 1.0 - st);

    customColor = red * bottom_left.x * bottom_left.y * bottom_right.x * bottom_right.y;
    gl_Position = vec4(vertex_position, 1.0);
}
