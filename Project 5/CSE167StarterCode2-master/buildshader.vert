#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 modelview;
//uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = mat3(transpose(inverse(modelview))) * aNormal;
    Position = vec3(modelview * vec4(aPos, 1.0));
    gl_Position = projection * modelview * vec4(aPos, 1.0);
}  