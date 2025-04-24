#version 330 core
#define M_PI 3.14
out vec4 FragColor;

uniform float time;

void main() {
    float intensity = 0.5 * (sin(time * 2) + 1.0);
    vec4 color = mix(vec4(1.0, 1.0, 0.0, 1.0), vec4(1.0, 0.5, 0.0, 1.0), intensity);

    FragColor = color;
}