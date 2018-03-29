#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

#define _CRT_SECURE_NO_WARNING

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "shader.h"
#include "Light.h"
#include "SkyboxObject.h"
#include "SceneG.h"
#include "stb_image.h"
#include "Line.h"
#include "ParticleSystem.hpp"
#include "ProceduralPlants.hpp"
#include "Geometry.cpp"
#include "Transform.cpp"
#include "Rule.cpp"
#include "Structure.cpp"


class Geometry1;
class Light;

class Window
{
public:
	static int width;
	static int height;
	static glm::mat4 P; // P for projection
	static glm::mat4 V; // V for view

	//selection buffer
	static std::vector<Geometry1 *> sbuff;
	static GLuint sbuffIndex;
	static GLuint sbuffOn;


	//bunny stuff
	static std::vector<float> bunnyVertices;
	static std::vector<unsigned int> bunnyIndices;
	static std::vector<float> bunnyNormals;
	static glm::mat4 bunnyS;
	static glm::mat4 bunnyT;

	static int soundOn;
	static int particlesOn;
	static int shadowsOn;
	static int normalColoring;
	static int shadowWindow;
	static glm::vec3 cP;
	static Light* cLight;

	//particles
	static int objectShot;
	static glm::vec3 shotPos;

	//static glm::mat4 camM;
	static glm::vec3 forward;
	static glm::vec3 right;


	static int firstPass;
	

	//shaders
	static GLint regID;
	static GLint skyboxID;
	static GLint selectionID;
	static GLint envID;
	static GLint shadowID;
	static GLint bufferID;
	static GLint basicID;


	static GLuint Framebuffer;
	static GLuint quad_vertexbuffer;
	static GLuint quad_vertexTXbuffer;
	static GLuint VAO, VBO, VBO2, EBO;


	static GLuint depthTexture;

	// Get a handle for our "MVP" uniform
	static GLuint depthMatrixID;

	// Get a handle for our "myTextureSampler" uniform
	//static GLuint TextureID;

	static GLuint DepthBiasID;
	static GLuint ShadowMapID;

	static glm::mat4 depthMVP;


	static void makeBunnyCity(int cityNum);


	static void prepFirstPass();
	static void prepSecondPass();
	static void drawShadowWindow();
	static void camUpdate();

	static void generate_grammars();

	static void textPrint(int x, int y, int z, char *string);

	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static unsigned int loadCubemap(std::vector<std::string> faces);

	//scroll
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	//get mouse input
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	//get cursor position
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

};

#endif
