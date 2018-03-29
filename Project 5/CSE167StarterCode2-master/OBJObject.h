#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class OBJObject
{
private:

public:
	OBJObject(const char* filepath, GLuint shader);
	~OBJObject();

	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 toWorld;
	glm::vec3 position;
	glm::mat4 initial;

	void parse(const char* filepath);
	void draw(glm::mat4 C);
	void centerPosition();


	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 ka;
	float p;

	// These variables are needed for the shader program
	GLuint VBO, VBO2, VAO, EBO;
	GLuint uProjection, uModelview, uCamPos;
	GLuint shader;
};

#endif