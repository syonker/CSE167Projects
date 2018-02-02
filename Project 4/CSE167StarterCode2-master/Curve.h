#ifndef _CURVE_H_
#define _CURVE_H_


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


//number of curves to draw
#define numCurves 8


#include "Window.h"

class Geometry;
class Group;

class Curve
{

public:
	Curve(GLuint shaderProgram, GLuint selectionshaderProgram, GLuint envshaderProgram);
	~Curve();

	void draw();

	void update(int pStart);

	glm::vec3 getCarPos(float t);

	float bernstein(int i, float t);


	//will hold the spheres and their centers
	//which will be the control points for our curve
	std::vector<Geometry *> p;

	//store all the points for all the curves connected
	//std::vector<glm::vec3> allPointsVec;

	//151*number of curves in curve
	//GLfloat allPoints[((150*numCurves)+1)][3];
	//GLuint indices[1][((150 * numCurves)+1)];


	std::vector<glm::vec3> allPoints;


	std::vector<unsigned int> indices;

	int count;

	int bufferStuff;

	GLuint shader;

	std::vector<glm::vec3> cPoints;

	Group * spheres;

	GLuint VBO, VAO, EBO;
	GLuint uProjection, uModelview;

	GLuint VBO1, VAO1;
	GLuint VBO2, VAO2;
	GLuint VBO3, VAO3;
	GLuint VBO4, VAO4;
	GLuint VBO5, VAO5;
	GLuint VBO6, VAO6;
	GLuint VBO7, VAO7;
	GLuint VBO8, VAO8;

	std::vector<glm::vec3> aP1;
	std::vector<glm::vec3> aP2;
	std::vector<glm::vec3> aP3;
	std::vector<glm::vec3> aP4;
	std::vector<glm::vec3> aP5;
	std::vector<glm::vec3> aP6;
	std::vector<glm::vec3> aP7;
	std::vector<glm::vec3> aP8;

	float highestT;
	float highestZ;

	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 ka;
	float pp;

};



#endif

