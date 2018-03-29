#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec3 Normal;
out vec3 Position;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
 Normal = mat3(transpose(inverse(model))) * aNormal;
 Position = vec3(model * vec4(aPos, 1.0));
 gl_Position = projection * view * model * vec4(aPos, 1.0);
} 

/*
#version 400

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

//in vec3 vp; // positions from mesh
//in vec3 vn; // normals from mesh

uniform mat4 P, V, M; // proj, view, model matrices

out vec3 pos_eye;
out vec3 n_eye;

void main()
{

	pos_eye = vec3(V * M * vec4(vp, 1.0));
	n_eye = vec3(V * M * vec4(vn, 0.0));
	gl_Position = P * V * M * vec4(vp, 1.0);

}
*/