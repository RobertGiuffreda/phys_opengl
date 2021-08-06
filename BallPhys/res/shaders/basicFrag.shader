#version 330 core

layout(location = 0) out vec4 color;

in vec2 tex_coord;
in vec3 normal;
in vec3 frag_pos;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec3 view_pos;

uniform sampler2D u_Texture;

void main()
{
	/* PHONE LIGHTING CODE */
	// Ambient
	float ambient_strength = 0.1f;
	vec3 ambient = ambient_strength * light_color;

	// Diffuse
	vec3 norm = normalize(normal);
	vec3 light_dir = normalize(light_pos - frag_pos);
	float diff = max(dot(norm, light_dir), 0.0f);
	vec3 diffuse = diff * light_color;

	// Specular
	float specular_strength = 0.1f;
	vec3 view_dir = normalize(view_pos - frag_pos);
	vec3 reflect_dir = reflect(-light_dir, norm);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 32);
	vec3 specular = spec * specular_strength * light_color;

	vec3 frag_color = (ambient + diffuse + specular);
	color = vec4(frag_color, 1.0f) * texture(u_Texture, tex_coord);
};