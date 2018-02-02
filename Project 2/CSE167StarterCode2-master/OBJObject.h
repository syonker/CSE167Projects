#ifndef _OBJOBJECT_H_
#define _OBJOBJECT_H_

//#define _CRT_SECURE_NO_WARNINGS

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

class OBJObject
{
private:

	glm::mat4 pInv;
	glm::mat4 M;


public:
	OBJObject(const char *filepath, int objectNum);
	~OBJObject();

	//std::vector<glm::vec3> vertices;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;
	//std::vector<glm::vec3> normals;

	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 ka;

	float p;

	int objType;

	glm::mat4 toWorld;

	glm::mat4 lightM;

	glm::mat4 S;
	glm::mat4 T;
	glm::mat4 Sinv;
	glm::mat4 Tinv;
	glm::mat4 initial;

	float centerX;
	float centerY;
	float centerZ;


	void parse(const char *filepath);
	void draw(GLuint);
	void update();
	void spin(float);

	void in();
	void out();
	void left();
	void right();
	void up();
	void down();

	void resetPosition();

	void sUp();
	void sDown();

	// These variables are needed for the shader program
	GLuint VBO, VBO2, VAO, EBO;
	GLuint uProjection, uModelview;


	//GLfloat vertices;
	//GLfloat normals;
	//GLuint indices;
};




#endif

