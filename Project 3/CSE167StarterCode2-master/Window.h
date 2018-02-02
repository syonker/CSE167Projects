#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNING

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "Cube.h"
#include "shader.h"
//#include "OBJObject.h"
#include "Light.h"
#include "SkyboxObject.h"
#include "SceneG.h"
#include "stb_image.h"

class Window
{
public:
	static int width;
	static int height;
	static glm::mat4 P; // P for projection
	static glm::mat4 V; // V for view
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static int drawSphere;
	static int moveArmy;
	static int oneRobot;

	static glm::vec3 cP;

	static glm::mat4 armyMoverS;

	static glm::mat4 armyMoverR;

	static int cullCount;


	static const glm::vec3 planesPoints[6];
	static const glm::vec3 planesNormals[6];

	static glm::mat4 Window::sI;

	static glm::vec3 Window::sOrigin;

	
	static unsigned int loadCubemap(std::vector<std::string> faces);
	//static void loadTexture();

	//scroll
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	

	//get mouse input
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	//get cursor position
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);


	static glm::vec3 trackBallMap(double xVal, double yVal);

};

#endif
