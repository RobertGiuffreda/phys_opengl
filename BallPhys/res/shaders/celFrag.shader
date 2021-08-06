#version 330 core

layout(location = 0) out vec4 color;

in vec3 normal;
in vec3 world_pos;

uniform vec3 light_pos;
uniform vec3 light_color;
uniform vec4 obj_color;
//uniform vec3 view_pos;

float b_levels = 6;           // Brightness Levels
void main()
{
    // Ambient
	float ambient_strength = 0.3f;
	vec3 ambient = ambient_strength * light_color;

    // Diffuse
	vec3 norm = normalize(normal);
	vec3 light_dir = normalize(light_pos - world_pos);
	//float diff = max(dot(norm, light_dir), 0.0f);
	float diff = dot(norm, light_dir);
	diff = (diff + 1) / 2;
    
	// Specular
	//float specular_strength = 0.1f;
	//vec3 view_dir = normalize(view_pos - world_pos);
	//vec3 reflect_dir = reflect(-light_dir, norm);
	//float spec = pow(max(dot(view_dir, reflect_dir), 0.0f), 32);
	//vec3 specular = spec * specular_strength * light_color;

    // Cel Shader code
    float intensity = diff;
    intensity = floor(intensity * b_levels);
    intensity = intensity/b_levels;
    vec4 frag_color = vec4((intensity * light_color) + ambient, 1.0f) * obj_color;
    color = frag_color;
}