#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
    // Sample the color from the scene texture
    vec3 texColor = texture(screenTexture, TexCoords).rgb;
    // Apply an effect (e.g., color inversion)
    // FragColor = vec4(1.0 - texColor, 1.0);
    FragColor = vec4(texColor, 1.0);
}