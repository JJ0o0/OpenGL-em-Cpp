#version 330 core
in vec3 ourColor;
out vec4 FragColor;

uniform float time;

void main() {
    vec3 rotatedColor;
    float angle = time * 0.5;  // Rotation speed
    
    rotatedColor.r = ourColor.r * abs(sin(angle)) + ourColor.g * abs(sin(angle + 2.094)) + ourColor.b * abs(sin(angle + 4.188));
    rotatedColor.g = ourColor.r * abs(sin(angle + 4.188)) + ourColor.g * abs(sin(angle)) + ourColor.b * abs(sin(angle + 2.094));
    rotatedColor.b = ourColor.r * abs(sin(angle + 2.094)) + ourColor.g * abs(sin(angle + 4.188)) + ourColor.b * abs(sin(angle));
    
    FragColor = vec4(rotatedColor, 1.0);
}