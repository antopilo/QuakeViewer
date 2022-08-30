#version 460 core

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 UVPosition;

out vec2 UV;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    UV = UVPosition;
    gl_Position = projection * view * vec4(VertexPosition, 1.0f);
}