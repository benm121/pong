#version 460 core

out vec4 FragColor;

uniform vec3 uColor;
uniform float uOpacity = 1.0f;

void main() {
    FragColor = vec4(uColor, uOpacity);
}
