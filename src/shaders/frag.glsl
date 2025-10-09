#version 460 core

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
in vec4 MaterialColor;

uniform sampler2D u_Texture;

out vec4 FragColor;

void main()
{
    vec3 ambient = 0.4 * MaterialColor.rgb;
    vec3 LightDir = -vec3(-1.0, -0.5, -1.0);
    vec3 diffuse = max(dot(normalize(LightDir), normalize(Normal)), 0.0) * MaterialColor.rgb * 3.0;
    // vec3 texColor = texture(u_Texture, TexCoord).rgb;
    // vec3 color = texColor * intensity;

    FragColor = vec4(diffuse + ambient, 1.0);
}
