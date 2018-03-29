#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;


// Uniform variables can be updated by fetching their location and passing values to that location
uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 DepthBiasMVP;


// The default output, gl_Position, should be assigned something.
out vec3 Normal;
out vec3 FragPos;
out vec4 ShadowCoord;


void main()
{
    // OpenGL maintains the D matrix so you only need to multiply by P, V (aka C inverse), and M
    gl_Position = projection * modelview * vec4(position, 1.0);

	 // Same, but with the light's view matrix
	ShadowCoord = DepthBiasMVP * vec4(position,1.0);


	FragPos = position;
	Normal = normal;

	//FragPos = vec3(modelview * vec4(position, 1.0f));
    //Normal = normalize(transpose(inverse(mat3(modelview))) * normal); 

}