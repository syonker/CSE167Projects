#ifndef _LIGHT_H_
#define _LIGHT_H_

#define _CRT_SECURE_NO_WARNINGS

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

class Light
{

public:

	Light(int lightType);
	~Light();

	int type;

	glm::vec3 color;
	glm::vec3 direction;

	glm::vec3 position;

	float consAtt;
	float linearAtt;
	float quadAtt;

	float cutoffAngle;
	float exponent;



	void draw(GLuint);

	
	//glm::mat4 toWorld;

	



};




#endif

