#version 330 core
layout (location = 0) in vec3 vertex;

out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform vec3 offset;
uniform vec4 color;

void main()
{
    float scale = 0.2f;
    ParticleColor = color;
    TexCoords = offset.xy;
    //TexCoords = vertex.xz;

    gl_Position = projection * view * model * vec4((vertex.xyz * scale) + offset, 1.0);
}