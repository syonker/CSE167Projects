#ifndef _SCENEG_H_
#define _SCENEG_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

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



class Node1
{
public:
	virtual void draw(glm::mat4 C) = 0;
	virtual void update(int num) = 0;
	virtual void addChild(Node1 * child) = 0;
	virtual void removeChild(Node1 * child) = 0;

	glm::mat4 M;

};

class Group1 : public Node1
{
public:
	Group1();
	~Group1();
	void draw(glm::mat4 C);
	void addChild(Node1 * child);
	void removeChild(Node1 * child);
	void update(int num);

	glm::mat4 M;
	std::vector<Node1*> children;

};

class Transform1 : public Node1
{
public:
	Transform1(glm::mat4 transform);
	~Transform1();
	void draw(glm::mat4 C);
	void addChild(Node1 * child);
	void removeChild(Node1 * child);
	void update(int num);

	glm::mat4 M;
	std::vector<Node1*> children;
	
};



class Geometry1 : public Node1
{
public:
	Geometry1(const char *filepath, int color, int firstBunny);
	~Geometry1();


	void draw(glm::mat4 C);
	void parse(const char *filepath);
	void addChild(Node1 * child);
	void removeChild(Node1 * child);
	void update(int num);

	void makeBunny();

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;

	glm::vec3 center;

	int interp;

	int drawType;

	int beenShot;

	glm::mat4 M;

	glm::mat4 extra;

	GLuint sbuffIndex;

	std::string tag;

	int environmentMap;

	int shadows;

	int toon;

	// These variables are needed for the shader program
	GLuint VBO, VBO2, VAO, EBO;
	GLuint uProjection, uModelview;
	GLuint P, V, View, Model, depthMatrixID, depthBiasMatrixID;


	glm::mat4 Rot;

	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 ka;
	float p;

	glm::mat4 toWorld;

	glm::mat4 S;
	glm::mat4 T;
	glm::mat4 initial;

	float centerX;
	float centerY;
	float centerZ;

};



class Drone : public Node1
{
public:
	Drone(const char *filepath);
	~Drone();


	void draw(glm::mat4 C);
	void parse(const char *filepath);
	void addChild(Node1 * child);
	void removeChild(Node1 * child);
	void update(int num);

	void up();
	void down();
	void rotR();
	void rotL();
	void forward();
	void backward();
	void right();
	void left();

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;

	int drawType;

	glm::vec3 center;

	glm::mat4 extra;

	int environmentMap;

	int shadows;

	int toon;

	int beenShot;

	std::string tag;

	// These variables are needed for the shader program
	GLuint VBO, VBO2, VAO, EBO;
	GLuint uProjection, uModelview;
	GLuint P, V, View, Model, depthMatrixID, depthBiasMatrixID;

	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 ka;
	float p;

	glm::mat4 S;
	glm::mat4 T;
	glm::mat4 initial;

	glm::mat4 R;

	float centerX;
	float centerY;
	float centerZ;

	glm::vec3 cPos;

	glm::vec3 cLook;

	glm::vec3 gunPos;
};



#endif

