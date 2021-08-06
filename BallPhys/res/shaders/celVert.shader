#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 p_normal;

out vec3 normal;
out vec3 world_pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 m_normal;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    normal = m_normal * p_normal;
    world_pos = vec3(model * vec4(position, 1.0f));
}