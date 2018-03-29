#include "OBJObject.h"
#include "Window.h"
#include "shader.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

OBJObject::OBJObject(const char *filepath, GLuint shader)
{
	this->toWorld = glm::mat4(1.0f);
	this->shader = shader;
	parse(filepath);





	//diffuse
	kd = { 0.2125f, 0.1275f, 0.054f };

	//specular
	ks = { 0.714f, 0.4284f, 0.18144f };

	//ambient
	ka = { 0.393548f, 0.271906f, 0.166721f };

	//shinyness
	p = 0.2f;






	// Create array object and buffers. Remember to delete your buffers when the object is destroyed!
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
	// Consider the VAO as a container for all your buffers.
	glBindVertexArray(VAO);

	// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
	// you want to draw, such as vertices, normals, colors, etc.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
	// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	// Enable the usage of layout location 0 (check the vertex shader to see what this is)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.


	// We've sent the vertex data over to OpenGL, but there's still something missing.
	// In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);

	// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GLfloat),
		(GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind the VAO now so we don't accidentally tamper with it.
	// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
	glBindVertexArray(0);
}

OBJObject::~OBJObject() {
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a 
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);
}

void OBJObject::parse(const char *filepath)
{
	int debug = 0;

	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
	FILE* fp;     // file pointer
	float x, y, z;  // vertex coordinates
	unsigned int f11, f12, f21, f22, f31, f32;
	char line[100];

	fopen_s(&fp, filepath, "rb");  // make the file name configurable so you can load other files
	if (fp == NULL) { cerr << "error loading file" << endl; exit(-1); }  // just in case the file can't be found or is corrupt

	fgets(line, 100, fp);
	//continue to scan untl out of characters
	while (feof(fp) == 0) {
		if (line[0] == 'v' && line[1] == ' ') {
			sscanf_s(line + 2, "%f %f %f", &x, &y, &z);
			glm::vec3 *vertex = new glm::vec3(x, y, z);
			vertices.push_back(*vertex);
		}
		else if (line[0] == 'v' && line[1] == 'n') {
			sscanf_s(line + 2, "%f %f %f", &x, &y, &z);
			glm::vec3 *normal = new glm::vec3(x, y, z);
			*normal = glm::normalize(*normal);
			normals.push_back(*normal);
		}
		else if (line[0] == 'f') {
			sscanf_s(line + 2, "%u//%u %u//%u %u//%u", &f11, &f12, &f21, &f22, &f31, &f32);
			indices.push_back(f11-1);
			indices.push_back(f21-1);
			indices.push_back(f31-1);
		}
		fgets(line, 100, fp);
	}
	fclose(fp);

	centerPosition();

}

void OBJObject::centerPosition() {
	float minX = vertices[0].x,
		minY = vertices[0].y,
		minZ = vertices[0].z,
		maxX = vertices[0].x,
		maxY = vertices[0].y,
		maxZ = vertices[0].z;

	for (int i = 0; i < vertices.size(); i++) {
		if (vertices[i].x < minX) {
			minX = vertices[i].x;
		}
		if (vertices[i].x > maxX) {
			maxX = vertices[i].x;
		}

		if (vertices[i].y < minY) {
			minY = vertices[i].y;
		}
		if (vertices[i].y > maxY) {
			maxY = vertices[i].y;
		}

		if (vertices[i].z < minZ) {
			minZ = vertices[i].z;
		}
		if (vertices[i].z > maxZ) {
			maxZ = vertices[i].z;
		}
	}

	float diffX = maxX - minX;
	float diffY = maxY - minY;
	float diffZ = maxZ - minZ;
	float centerX = (diffX / 2) + minX;
	float centerY = (diffY / 2) + minY;
	float centerZ = (diffZ / 2) + minZ;

	initial = glm::translate(toWorld, glm::vec3(-centerX, -centerY, -centerZ));

}

void OBJObject::draw(glm::mat4 C)
{

	// Calculate the combination of the model and view (camera inverse) matrices
	glm::mat4 modelview = Window::V * C * toWorld * initial;

	glm::mat4 model = C * toWorld * initial;

	//first pass draw
	if (Window::firstPass == 1) {

		GLuint Model = glGetUniformLocation(Window::shadowID, "model");

		glUniformMatrix4fv(Model, 1, GL_FALSE, &model[0][0]);


		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);
		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);


		return;
	}
	else {


		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
		);

		glm::mat4 depthBiasMVP = biasMatrix * Window::depthMVP * model;

		// Send our Transform1ation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(Window::DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);


		/*
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Window::Texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(Window::TextureID, 0);
		*/

		GLint texLoc = glGetUniformLocation(Window::regID, "shadowMap");
		glUniform1i(texLoc, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Window::depthTexture);

		/*
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Window::depthTexture);
		glUniform1i(Window::ShadowMapID, 0);
		*/


		glUniform1i(glGetUniformLocation(Window::regID, "light.normalColoring"), Window::normalColoring);

		glUniform1i(glGetUniformLocation(Window::regID, "shadowsOn"), Window::shadowsOn);

		glUniform1i(glGetUniformLocation(Window::regID, "toon"), 1);

		glUniform1i(glGetUniformLocation(Window::regID, "beenShot"), 0);

		Window::cLight->draw(Window::regID);

		//send over the camera position
		glUniform3fv(glGetUniformLocation(Window::regID, "viewPos"), 1, &Window::cP[0]);

		//glm::mat4 model = C * extra * initial;
		glUniformMatrix4fv(glGetUniformLocation(Window::regID, "model"), 1, GL_FALSE, &model[0][0]);


		// We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
		// Consequently, we need to forward the projection, view, and model matrices to the shader programs
		// Get the location of the uniform variables "projection" and "modelview"
		uProjection = glGetUniformLocation(Window::regID, "projection");
		uModelview = glGetUniformLocation(Window::regID, "modelview");
		// Now send these values to the shader program
		glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
		glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);


		//send over the material attributes
		glUniform3fv(glGetUniformLocation(Window::regID, "kd"), 1, &(kd[0]));
		glUniform3fv(glGetUniformLocation(Window::regID, "ks"), 1, &(ks[0]));
		glUniform3fv(glGetUniformLocation(Window::regID, "ka"), 1, &(ka[0]));
		glUniform1f(glGetUniformLocation(Window::regID, "p"), p);


		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);
		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);


	}




}
