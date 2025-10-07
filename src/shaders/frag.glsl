#version 460 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
