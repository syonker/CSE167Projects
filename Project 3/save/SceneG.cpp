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

		if (canDraw[i] == 1) {

			//currChild = children.at(i);
			//maybe revesere to C*M
			children[i]->draw(C*M);

		}

	}


}
void Group::addChild(Node * child) {

	children.push_back(child);
	canDraw.push_back(1);

}
void Group::removeChild(Node * child) {

	//children.erase(std::remove(children.begin(), children.end(), child), children.end());

}

void Group::update() {

	int i, j;
	//Node * currChild;
	glm::vec3 x;
	glm::vec3 n;
	glm::vec3 p;
	glm::mat4 C;
	glm::vec4 x4;

	int prevCullCount;

	float d;

	//x4 = {0.0f, 0.0f, 0.0f, 1.0f};
	x4.x = Window::sOrigin.x;
	x4.y = Window::sOrigin.y;
	x4.z = Window::sOrigin.z;
	x4.w = 1.0f;

	for (i = 0; i < children.size(); i++) {

		//currChild = children[i];

		C = (children[i]->M)*glm::translate(glm::mat4(1.0f), { 0.0f, 1.0f, 0.25f })*Window::sI;

		//C = (children[i]->M)*glm::translate(glm::mat4(1.0f), { 0.0f, 1.0f, 0.25f });

		//x4.x = (currChild->M)[3][0];
		//x4.y = (currChild->M)[3][1] + 1.0f;
		//x4.z = (currChild->M)[3][2] + 0.25f;
		//x4.w = 1.0f;

		//x4 = Window::P * Window::V * x4;

		x4 = Window::P * Window::V * C * x4;

		x.x = x4.x / x4.w;
		x.y = x4.y / x4.w;
		x.z = x4.z / x4.w;

		if ((x.x > 1.0f) || (x.y > 1.0f) || (x.z > 1.0f) || (x.x < -1.0f) || (x.y < -1.0f) || (x.z < 11.0f)) {

			//std::cerr << "OVER/under ONE" << std::endl;

		}

		prevCullCount = Window::cullCount;

		//radius = 6.0f see piazza to scale this

		//for each wall
		for (j = 0; j < 6; j++) {

			//n = normal of wall
			//d = distance from origin to plane
			n = Window::planesNormals[j];
			p = Window::planesPoints[j];

			d = glm::dot((x - p), n);

			if (d < 0.0f) {

				//set draw cancel
				//add to cull count
				//terminate for loop
				Window::cullCount++;
				break;

				//end
			}

			//end
		}

		//if no early termination set to draw
		if (prevCullCount == Window::cullCount) {

			//draw ok
			canDraw[i] = 1;

		}
		else {

			//no draw
			canDraw[i] = 0;
		}





	}

}









Transform::Transform(glm::mat4 transform) {

	M = transform;

}

Transform::~Transform()
{
}



void Transform::draw(glm::mat4 C) {

	int i;
	//Node * currChild;
	for (i = 0; i < children.size(); i++) {

			//currChild = children.at(i);
			//maybe revesere to C*M
			children[i]->draw((C*M));

	}

}
void Transform::addChild(Node * child) {

	children.push_back(child);

}
void Transform::removeChild(Node * child) {

	//children.erase(std::remove(children.begin(), children.end(), child), children.end());

	auto it = children.begin();
	while (it != children.end()) {

		if (*it = child) {

			children.erase(it);

		}

	}

}

void Transform::update() {


}










Geometry::Geometry(const char *filepath, GLuint shaderProgram, int objtype)
{

	type = objtype;

	//diffuse
	kd = { 0.07568f, 0.61424f, 0.07568f };

	//specular
	ks = { 0.633f, 0.727811f, 0.633f };

	//ambient
	ka = { 0.0215f, 0.1745f, 0.0215f };

	//shinyness
	p = 0.6f;

	//scale matrix
	S = glm::mat4(1.0f);

	//centering transformation matrix
	T = glm::mat4(1.0f);

	
	initial = glm::mat4(1.0f);


	toWorld = glm::mat4(1.0f);

	parse(filepath);

	shader = shaderProgram;

	

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


	//arm
	if (type == 1) {

		Rot = glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));

	}
	//head
	else if (type == 2) {

		Rot = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));

	}
	//other
	else {

		Rot = glm::mat4(1.0f);

	}

	if (type == -1) {

		S = S*glm::scale(glm::mat4(1.0f), { 3.0f, 3.0f, 3.0f });

	}
	
	initial = S*T*Rot;
	//initial = T*Rot*S;

	if (type == -1) {

		Window::sI = initial;

		Window::sOrigin = { centerX,centerY,centerZ };

	}
	
	
	
	fclose(fp);

}

void Geometry::draw(glm::mat4 C)
{
	//toWorld = C*toWorld;
	// Calculate the combination of the model and view (camera inverse) matrices
	glm::mat4 modelview = Window::V * C * initial;
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

	/*if (type == -1) {

		glUniform1i(glGetUniformLocation(shader, "isSphere"), 1);

	}
	else {

		glUniform1i(glGetUniformLocation(shader, "isSphere"), 0);

	}*/



	// Now draw the cube. We simply need to bind the VAO associated with it.
	glBindVertexArray(VAO);
	// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
	if (type == -1) {

		if ((Window::drawSphere)==1) {

			glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);

		}

	}
	else {

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	}

	// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
	glBindVertexArray(0);
}

void Geometry::addChild(Node * child) {


}

void Geometry::removeChild(Node * child) {


}

void Geometry::update() {


}
