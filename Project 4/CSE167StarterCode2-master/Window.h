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
#include "Curve.h"

class Geometry;

class Window
{
public:
	static int width;
	static int height;
	static glm::mat4 P; // P for projection
	static glm::mat4 V; // V for view

	//selection buffer
	static std::vector<Geometry *> sbuff;
	static GLuint sbuffIndex;
	static GLuint sbuffOn;

	static int Window::normalColoring;
	static glm::vec3 Window::view;

	static glm::vec3 Window::cP;

	//for car
	static glm::vec3 Window::old_pos;
	static glm::vec3 Window::new_pos;
	static float Window::carT;
	static glm::mat4 Window::roller;


	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static unsigned int loadCubemap(std::vector<std::string> faces);

	/*
	static float bernstein(int i, float t);

	static void makeTrack();
	static void drawTrack(std::vector<glm::vec3> points);
	*/

	//scroll
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	//get mouse input
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	//get cursor position
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

	static glm::vec3 trackBallMap(double xVal, double yVal);

};

#endif
