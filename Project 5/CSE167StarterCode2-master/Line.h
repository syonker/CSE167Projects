#ifndef _SHOT_H_
#define _SHOT_H_


#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>



#include "Window.h"


class Line
{

public:
	Line(GLuint shaderProgram);
	~Line();

	void draw();

	std::vector<glm::vec3> allPoints;

	std::vector<unsigned int> indices;

	int display;

	std::vector<glm::vec3> aP1;


	GLuint shader;


	GLuint VBO, VAO, EBO;
	GLuint uProjection, uModelview;

	GLuint VBO1, VAO1;

	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 ka;
	float pp;

};



#endif

