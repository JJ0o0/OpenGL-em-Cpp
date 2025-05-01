#version 330 core
out vec4 FragColor;

uniform vec3 ourColor;
uniform vec3 nextColor;

uniform float progress;

void main() {
    vec3 newColor = mix(ourColor, nextColor, progress);
    FragColor = vec4(newColor, 1.0);
}