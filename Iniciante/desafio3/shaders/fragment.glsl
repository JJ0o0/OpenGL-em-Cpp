#version 330 core
out vec4 FragColor;

void main() {
    float gradient = gl_FragCoord.x / 800;
    FragColor = vec4(gradient, 0.0, 1.0, 1.0);
}