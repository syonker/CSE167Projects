#include "Line.h"
#include "Window.h"
#include "math.h"


Line::Line(GLuint shaderProgram)
{
	

	shader = shaderProgram;


	indices.push_back(0);
	indices.push_back(1);
	allPoints.push_back({0.0f,0.0f,0.0f});
	allPoints.push_back({ 0.0f,0.0f,0.0f });
	aP1.push_back({ 0.0f,0.0f,0.0f });
	aP1.push_back({ 0.0f,0.0f,0.0f });

	
	//ruby
	//diffuse
	kd = { 0.61424f, 0.04136f, 0.04136f };

	//specular
	ks = { 0.727811f, 0.626959f, 0.626959f };

	//ambient
	ka = { 0.1745f, 0.01175f, 0.01175f };

	//shinyness
	pp = 0.6f;
	
	

		/*


		// Create array object and buffers. Remember to delete your buffers when the object is destroyed!
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
		// Consider the VAO as a container for all your buffers.
		glBindVertexArray(VAO);

		// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
		// you want to draw, such as vertices, normals, colors, etc.
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
		// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
		//glBufferData(GL_ARRAY_BUFFER, sizeof(allPoints), allPoints, GL_STATIC_DRAW);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*allPoints.size(), allPoints.data(), GL_STATIC_DRAW);





		// Enable the usage of layout location 0 (check the vertex shader to see what this is)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
			3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
			GL_FLOAT, // What type these components are
			GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
			3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
			(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);

		// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind the VAO now so we don't accidentally tamper with it.
		// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
		glBindVertexArray(0);

		*/


		//line
		glGenVertexArrays(1, &VAO1);
		glGenBuffers(1, &VBO1);

		glBindVertexArray(VAO1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP1.size(), aP1.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); 

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


}

Line::~Line()
{
	// Delete previously generated buffers.
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO1);
	glDeleteBuffers(1, &EBO);
	
}


void Line::draw()
{

		// Calculate the combination of the model and view (camera inverse) matrices
		glm::mat4 modelview = Window::V;

		glUseProgram(shader);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		glUniform1i(glGetUniformLocation(shader, "light.normalColoring"), Window::normalColoring);

		//send over the camera position
		glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, &Window::cP[0]);

		glm::mat4 model = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);


		// We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
		// Consequently, we need to forward the projection, view, and model matrices to the shader programs
		// Get the location of the uniform variables "projection" and "modelview"
		uProjection = glGetUniformLocation(shader, "projection");
		uModelview = glGetUniformLocation(shader, "modelview");
		// Now send these values to the shader program
		glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
		glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);


		//send over the material attributes
		glUniform3fv(glGetUniformLocation(shader, "kd"), 1, &(kd[0]));
		glUniform3fv(glGetUniformLocation(shader, "ks"), 1, &(ks[0]));
		glUniform3fv(glGetUniformLocation(shader, "ka"), 1, &(ka[0]));
		glUniform1f(glGetUniformLocation(shader, "p"), pp);


		/*

		// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
		// Consider the VAO as a container for all your buffers.
		glBindVertexArray(VAO);

		// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
		// you want to draw, such as vertices, normals, colors, etc.
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
		// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
		//glBufferData(GL_ARRAY_BUFFER, sizeof(allPoints), allPoints, GL_STATIC_DRAW);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*allPoints.size(), allPoints.data(), GL_STATIC_DRAW);


		glBindBuffer(GL_ARRAY_BUFFER, 0);



		//third number is 150*number of curves in curve
		glDrawArrays(GL_LINE_STRIP, 0, allPoints.size());



		//glDrawElements(GL_LINE_STRIP, ((150 * numCurves)+1), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		*/


		//lines

		//1
		glBindVertexArray(VAO1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP1.size(), aP1.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP1.size());

		glBindVertexArray(0);


}
