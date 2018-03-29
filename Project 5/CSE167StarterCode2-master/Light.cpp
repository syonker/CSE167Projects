#include "Light.h"
#include "Window.h"

Light::Light(int lightType)
{

	//initial = glm::mat4(1.0f);
	//toWorld = glm::mat4(1.0f);
	


	//directional
	if (lightType == 1) {

		type = lightType;

		color = { 1.0f, 1.0f, 1.0f };

		direction = { 0.0f, -1.0f, 0.0f };


	//point
	} else if (lightType == 2) {

		type = lightType;

		color = { 1.0f, 1.0f, 1.0f };

		direction = { 0.0f, 1.0f, 0.0f };

		position = { 0.0f, 10.0f, 0.0f };

		consAtt = 0.0f;
		linearAtt = 0.05f;
	
	//spot
	} else {

		type = lightType;

		color = { 1.0f, 1.0f, 1.0f };

		direction = { 0.0f, 0.0f, -1.0f };

		position = { 0.0f, 0.0f, 10.0f };

		consAtt = 0.0f;
		linearAtt = 0.05f;
		quadAtt = 0.05f;

		cutoffAngle = 0.03f;
		exponent = 0.2f;

	}


}

Light::~Light()
{
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a 
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!

}



void Light::draw(GLuint shaderProgram)
{

	//glUseProgram(shaderProgram);

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//glUniform1i(glGetUniformLocation(shaderProgram, "light.normalColoring"), Window::normalColoring);

	//send over the camera position
	//glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, &Window::cP[0]);



	//send over the light type
	glUniform1i(glGetUniformLocation(shaderProgram, "light.type"), type);

	//send over the value of light color
	glUniform3fv(glGetUniformLocation(shaderProgram, "light.color"), 1, &color[0]);

	//send over the direction of the light
	glUniform3fv(glGetUniformLocation(shaderProgram, "light.direction"), 1, &direction[0]);

	if (type != 1) {

		//send over the position of the light
		glUniform3fv(glGetUniformLocation(shaderProgram, "light.position"), 1, &position[0]);

		//point light attributes
		glUniform1f(glGetUniformLocation(shaderProgram, "light.consAtt"), consAtt);
		glUniform1f(glGetUniformLocation(shaderProgram, "light.linearAtt"), linearAtt);

		if (type != 2) {

			//send over the spotlight variables
			glUniform1f(glGetUniformLocation(shaderProgram, "light.quadAtt"), quadAtt);
			glUniform1f(glGetUniformLocation(shaderProgram, "light.cutoffAngle"), cutoffAngle);
			glUniform1f(glGetUniformLocation(shaderProgram, "light.exponent"), exponent);

		}

	}



}



