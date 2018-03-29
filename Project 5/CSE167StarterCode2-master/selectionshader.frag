#version 330 core

in vec3 Normal;
in vec3 FragPos;


uniform uint sbuffIndex;

out vec4 color;


void main()
{    
	color = vec4(sbuffIndex/255.0f,0.0f,0.0f,0.0f);
}
