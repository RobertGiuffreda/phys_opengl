#version 400 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 tex_coord;		// Texture Coordinates
out vec3 normal;		// Vertex Normals
out vec3 frag_pos;		// Position in world coordinates

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 m_normal;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	tex_coord = aTexCoord;
	frag_pos = vec3(model * vec4(aPos, 1.0f));
	normal = m_normal * aNormal;
};