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



class Node
{
public:
	virtual void draw(glm::mat4 C) = 0;
	virtual void update() = 0;
	virtual void addChild(Node * child) = 0;
	virtual void removeChild(Node * child) = 0;

	glm::mat4 M;

};

class Group : public Node
{
public:
	Group();
	~Group();
	void draw(glm::mat4 C);
	void addChild(Node * child);
	void removeChild(Node * child);
	void update();

	glm::mat4 M;
	std::vector<Node*> children;

};

class Transform : public Node
{
public:
	Transform(glm::mat4 transform);
	~Transform();
	void draw(glm::mat4 C);
	void addChild(Node * child);
	void removeChild(Node * child);
	void update();

	glm::mat4 M;
	std::vector<Node*> children;
	
};



class Geometry : public Node
{
public:
	Geometry(const char *filepath, GLuint shaderProgram, GLuint selectionshaderProgram, GLuint envshaderProgram, int color);
	~Geometry();


	void draw(glm::mat4 C);
	void parse(const char *filepath);
	void addChild(Node * child);
	void removeChild(Node * child);
	void update();

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> normals;

	glm::vec3 center;

	int interp;

	glm::mat4 M;

	glm::mat4 extra;

	GLuint sbuffIndex;

	std::string tag;

	int environmentMap;

	GLuint shader;
	GLuint selectionShader;
	GLuint envShader;
	// These variables are needed for the shader program
	GLuint VBO, VBO2, VAO, EBO;
	GLuint uProjection, uModelview;
	GLuint P, V, View, Model;


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




#endif

