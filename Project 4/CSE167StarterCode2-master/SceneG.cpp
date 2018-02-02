#include "SceneG.h"
#include "Window.h"









Group::Group() {

	M = glm::mat4(1.0f);

}

Group::~Group(){

}



void Group::draw(glm::mat4 C) {

	int i;
	//Node * currChild;
	for (i = 0; i < children.size(); i++) {

			children[i]->draw(C*M);

	}


}
void Group::addChild(Node * child) {

	children.push_back(child);

}
void Group::removeChild(Node * child) {

	//children.erase(std::remove(children.begin(), children.end(), child), children.end());

}

void Group::update() {


}









Transform::Transform(glm::mat4 transform) {

	M = transform;

}

Transform::~Transform()
{
}



void Transform::draw(glm::mat4 C) {

	int i;
	for (i = 0; i < children.size(); i++) {

			children[i]->draw((C*M));

	}

}
void Transform::addChild(Node * child) {

	children.push_back(child);

}
void Transform::removeChild(Node * child) {

	auto it = children.begin();
	while (it != children.end()) {
		if (*it = child) {
			children.erase(it);
		}
	}

}

void Transform::update() {


}










Geometry::Geometry(const char *filepath, GLuint shaderProgram, GLuint selectionshaderProgram, GLuint envshaderProgram, int color)
{

	//add to the selection buffer
	Window::sbuff.push_back(this);
	sbuffIndex = Window::sbuffIndex;
	Window::sbuffIndex++;

	extra = glm::mat4(1.0f);

	environmentMap = 0;

	if (color == 1) {


		//diffuse
		kd = { 0.07568f, 0.61424f, 0.07568f };

		//specular
		ks = { 0.633f, 0.727811f, 0.633f };

		//ambient
		ka = { 0.0215f, 0.1745f, 0.0215f };

		//shinyness
		p = 0.6f;

	}
	else if (color == 0) {

		//diffuse
		kd = { 0.5f, 0.0f, 0.0f };

		//specular
		ks = { 0.7f, 0.6f, 0.6f };

		//ambient
		ka = { 0.0f, 0.0f, 0.0f };

		//shinyness
		p = 0.25f;

	} else {

		//diffuse
		kd = { 0.55f, 0.55f, 0.55f };

		//specular
		ks = { 0.7f, 0.7f, 0.7f };

		//ambient
		ka = { 0.0f, 0.0f, 0.0f };

		//shinyness
		p = 0.25f;

	}

	//scale matrix
	S = glm::mat4(1.0f);

	//centering transformation matrix
	T = glm::mat4(1.0f);

	
	initial = glm::mat4(1.0f);


	toWorld = glm::mat4(1.0f);

	parse(filepath);

	shader = shaderProgram;

	selectionShader = selectionshaderProgram;

	envShader = envshaderProgram;

	

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
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	
	// Enable the usage of layout location 0 (check the vertex shader to see what this is)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), normals.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)0);


	// We've sent the vertex data over to OpenGL, but there's still something missing.
	// In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);


	// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind the VAO now so we don't accidentally tamper with it.
	// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
	glBindVertexArray(0);


}

Geometry::~Geometry()
{
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a 
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);
}

void Geometry::parse(const char *filepath)
{
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data

	using namespace std;

	FILE* fp;     // file pointer
	float x, y, z;  // vertex coordinates
	float r, g, b, q;  // vertex color
	int c1, c2;    // characters read from file
	int iV1, iV2, iV3, iN1, iN2, iN3;

	int i = 0;

	int vertCount = 0;
	int faceCount = 0;

	float xMax = 0.0f;
	float yMax = 0.0f;
	float zMax = 0.0f;

	float xMin = 0.0f;
	float yMin = 0.0f;
	float zMin = 0.0f;

	float largestMax = 0.0f;

	glm::mat4 R(1.0f);

	glm::vec3 v;

	fp = fopen(filepath, "rb");




	if (fp == NULL) {
		cerr << "error loading file" << endl;
		exit(-1);
	}


	c1 = fgetc(fp);

	while (c1 != EOF) {

		c2 = fgetc(fp);

		//vertex
		if ((c1 == 'v') && (c2 == ' ')) {

			fscanf(fp, " %f %f %f %f %f %f %f", &x, &y, &z, &r, &g, &b, &q);

			//v.x = x;
			//v.y = y;
			//v.z = z;
			if (xMax == 0.0f) {

				xMax = x;
				xMin = x;
				yMax = y;
				yMin = y;
				zMax = z;
				zMin = z;

			}

			if (xMax < x) {
				xMax = x;
			}
			if (yMax < y) {
				yMax = y;
			}
			if (zMax < z) {
				zMax = z;
			}
			if (xMin > x) {
				xMin = x;
			}
			if (yMin > y) {
				yMin = y;
			}
			if (zMin > z) {
				zMin = z;
			}



			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			vertCount++;

		}
		//vertex normal
		else if ((c1 == 'v') && (c2 == 'n')) {

			fscanf(fp, " %f %f %f %f %f %f %f", &x, &y, &z, &r, &g, &b, &q);

			//v.x = x;
			//v.y = y;
			//v.z = z;

			//normals.push_back(v);

			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);

		}

		//face
		else if ((c1 == 'f') && (c2 == ' ')) {

			fscanf(fp, " %d//%d %d//%d %d//%d %f", &iV1, &iN1, &iV2, &iN2, &iV3, &iN3, &q);

			indices.push_back(iV1-1);
			indices.push_back(iV2-1);
			indices.push_back(iV3-1);

			faceCount++;

		}

		//ignore line
		else {

			fscanf(fp, "%*[^\n]\n");

		}

		c1 = fgetc(fp);

	}

	cerr << vertices.size() << endl;
	cerr << indices.size() << endl;

	centerX = (xMax + xMin) / 2.0f;
	centerY = (yMax + yMin) / 2.0f;
	centerZ = (zMax + zMin) / 2.0f;

	center = {centerX, centerY, centerZ};


	largestMax = xMax - xMin;

	if ((yMax - yMin) > largestMax) {

		largestMax = yMax - yMin;

	}

	if ((zMax - zMin) > largestMax) {

		largestMax = zMax - zMin;

	}


	//scale
	S = glm::scale(glm::mat4(1.0f), glm::vec3((2.0f/largestMax), (2.0f / largestMax), (2.0f/largestMax)));
	//center
	T = glm::translate(glm::mat4(1.0f), glm::vec3(-centerX, -centerY, -centerZ));

	
	initial = S*T;


	center = {0.0f,0.0f,0.0f};
	
	
	fclose(fp);

}

void Geometry::draw(glm::mat4 C)
{
	glm::mat4 tempV;

	// Calculate the combination of the model and view (camera inverse) matrices
	glm::mat4 modelview = Window::V * C * extra * initial;

	if (Window::sbuffOn) {

		uProjection = glGetUniformLocation(selectionShader, "projection");
		uModelview = glGetUniformLocation(selectionShader, "modelview");
		// Now send these values to the shader program
		glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
		glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);


		glUniform1ui(glGetUniformLocation(selectionShader, "sbuffIndex"), sbuffIndex);

		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);
		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);
		


	} else if (environmentMap) {

		glUseProgram(envShader);


		

		//glm::mat4 model = C * extra * initial;
		glm::mat4 model = extra * initial;

		tempV = Window::V;

		//use environmentMapping with envShader
		P = glGetUniformLocation(envShader, "projection");
		V = glGetUniformLocation(envShader, "view");
		//View = glGetUniformLocation(envShader, "cameraPos");
		Model = glGetUniformLocation(envShader, "model");
		// Now send these values to the shader program
		glUniformMatrix4fv(P, 1, GL_FALSE, &Window::P[0][0]);

		//glUniformMatrix4fv(V, 1, GL_FALSE, &Window::V[0][0]);
		glUniformMatrix4fv(V, 1, GL_FALSE, &tempV[0][0]);

		//glUniformMatrix4fv(View, 1, GL_FALSE, &Window::V[0][0]);
		//glUniformMatrix4fv(View, 1, GL_FALSE, &Window::cP[0][0]);


		glUniform3fv(glGetUniformLocation(envShader, "cameraPos"), 1, &(Window::cP[0]));
		
		
		glUniformMatrix4fv(Model, 1, GL_FALSE, &model[0][0]);


		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);

		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);

		
	}
	else {

		glUseProgram(shader);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glUniform1i(glGetUniformLocation(shader, "light.normalColoring"), Window::normalColoring);

		//send over the camera position
		glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, &Window::view[0]);


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
		glUniform1f(glGetUniformLocation(shader, "p"), p);


		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);
		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);

	}

}

void Geometry::addChild(Node * child) {


}

void Geometry::removeChild(Node * child) {


}

void Geometry::update() {


}
