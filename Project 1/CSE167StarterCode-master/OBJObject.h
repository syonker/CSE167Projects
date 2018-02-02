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
std::vector<unsigned int> indices;

glm::mat4 pInv;
glm::mat4 oInv;
glm::mat4 M;

public:

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	glm::mat4 toWorld;

	glm::vec2 p;

	OBJObject(const char* filepath);

	float angle;
	float pSize;
	float minSize;
	float scaleCount;

	void parse(const char* filepath);
	void draw();

	void update();

	void spin(float);

	void in();
	void out();
	void left();
	void right();
	void up();
	void down();

	void decPoints();
	void incPoints();

	void sUp();
	void sDown();

	void oClock(float);
	void oCounterclock(float);

	void resetPosition();
	void resetOrientation();

};

#endif