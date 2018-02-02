#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 Position;
uniform vec3 cameraPos;
uniform samplerCube cube_texture;
void main()
{
 vec3 I = normalize(Position - cameraPos);
 vec3 R = reflect(I, normalize(Normal));
 FragColor = vec4(texture(cube_texture, R).rgb, 1.0);
}

/*
#version 400

in vec3 pos_eye;
in vec3 n_eye;

uniform samplerCube cube_texture;
uniform mat4 View; // view matrix

out vec4 frag_colour;

void main()
{
	// reflect ray around normal from eye to surface
	vec3 incident_eye = normalize(pos_eye);
	vec3 normal = normalize(n_eye);
	vec3 reflected = reflect(incident_eye, normal);

	// convert from eye to world space
	reflected = vec3(inverse(V) * vec4(reflected, 0.0));
	frag_colour = texture(cube_texture, reflected);

}
*/