#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

vec4 texColor;

void main() {
    texColor = texture2D(ourTexture, TexCoord);
    FragColor = vec4(texColor.rgb, 1);
}
