#include "SceneG.h"
#include "Window.h"









Group1::Group1() {

	M = glm::mat4(1.0f);

}

Group1::~Group1(){

}



void Group1::draw(glm::mat4 C) {

	int i;
	//Node1 * currChild;
	for (i = 0; i < children.size(); i++) {

			children[i]->draw(C*M);

	}


}
void Group1::addChild(Node1 * child) {

	children.push_back(child);

}
void Group1::removeChild(Node1 * child) {

	//children.erase(std::remove(children.begin(), children.end(), child), children.end());

}

void Group1::update(int num) {

	int i;
	//Node1 * currChild;
	for (i = 0; i < children.size(); i++) {

		children[i]->update(num);

	}

}









Transform1::Transform1(glm::mat4 Transform1) {

	M = Transform1;

}

Transform1::~Transform1()
{
}



void Transform1::draw(glm::mat4 C) {

	int i;
	for (i = 0; i < children.size(); i++) {

			children[i]->draw((C*M));

	}

}
void Transform1::addChild(Node1 * child) {

	children.push_back(child);

}
void Transform1::removeChild(Node1 * child) {

	auto it = children.begin();
	while (it != children.end()) {
		if (*it = child) {
			children.erase(it);
		}
	}

}

void Transform1::update(int num) {

	int i;
	//Node1 * currChild;
	for (i = 0; i < children.size(); i++) {

		children[i]->update(num);

	}

}










Geometry1::Geometry1(const char *filepath, int color, int firstBunny)
{

	//add to the selection buffer
	Window::sbuff.push_back(this);
	sbuffIndex = Window::sbuffIndex;
	Window::sbuffIndex++;

	extra = glm::mat4(1.0f);

	environmentMap = 0;
	shadows = 0;
	toon = 0;
	beenShot = 0;

	//jade - background
	if (color == 0) {

		
		//ambient
		ka = { 0.0215f, 0.1745f, 0.0215f };

		//diffuse
		kd = { 0.07568f, 0.61424f, 0.07568f };

		//specular
		ks = { 0.633f, 0.727811f, 0.633f };

		//shinyness
		p = 0.6f;

		

		/*
		//ambient
		ka = { 0.135f, 0.2225f, 0.1575f };

		//diffuse
		kd = { 0.54, 0.89f, 0.63f };

		//specular
		ks = { 0.316228f, 0.316228f, 0.316228f };

		//shinyness
		p = 12.8f;
		*/

	}
	 
	//white plastic
	else if (color == 1) {

		//ambient
		ka = { 0.0f, 0.0f, 0.0f };

		//diffuse
		kd = { 0.55f, 0.55f, 0.55f };

		//specular
		ks = { 0.7f, 0.7f, 0.7f };

		//shinyness
		p = 0.25f;
		

	//cyan rubber
	} else if (color == 2) {

		//ambient
		ka = { 0.0f, 0.05f, 0.05f };

		//diffuse
		kd = { 0.5f, 0.5f, 0.5f };

		//specular
		ks = { 0.04f, 0.7f, 0.7f };

		//shinyness
		p = 0.078125f;

	}

	//polished gold
	else if (color == 3) {

		//ambient
		ka = { .24725f, 0.2245f, 0.0645f };

		//diffuse
		kd = { 0.34615f, 0.3143f, 0.0903f };

		//specular
		ks = { 0.797357f, 0.723991f, 0.208006f };

		//shinyness
		p = 83.2f;

	}
	//pewter
	else if (color == 4) {

		//ambient
		ka = { 0.105882f, 0.058824f, 0.113725f };

		//diffuse
		kd = { 0.427451f, 0.470588f, 0.541176f };

		//specular
		ks = { 0.333333f, 0.333333f, 0.521569f };

		//shinyness
		p = 9.84615f;

	}

	//scale matrix
	S = glm::mat4(1.0f);

	//centering Transform1ation matrix
	T = glm::mat4(1.0f);

	
	initial = glm::mat4(1.0f);


	toWorld = glm::mat4(1.0f);

	if (firstBunny) {

		parse(filepath);

	}
	else {

		makeBunny();

	}

	
	

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

Geometry1::~Geometry1()
{
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a 
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);
}

void Geometry1::parse(const char *filepath)
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


	std::cerr << "Largest max" << largestMax << std::endl;


	//scale
	S = glm::scale(glm::mat4(1.0f), glm::vec3((2.0f/largestMax), (2.0f / largestMax), (2.0f/largestMax)));
	//center
	T = glm::translate(glm::mat4(1.0f), glm::vec3(-centerX, -centerY, -centerZ));

	
	initial = S*T;


	center = {0.0f,0.0f,0.0f};
	
	
	fclose(fp);


	Window::bunnyVertices = vertices;
	Window::bunnyNormals = normals;
	Window::bunnyIndices = indices;
	Window::bunnyS = S;
	Window::bunnyT = T;
}



void Geometry1::makeBunny()
{
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data

	vertices = Window::bunnyVertices;
	normals = Window::bunnyNormals;
	indices = Window::bunnyIndices;


	//scale
	S = Window::bunnyS;
	//center
	T = Window::bunnyT;

	initial = S*T;


	center = { 0.0f,0.0f,0.0f };


}




void Geometry1::draw(glm::mat4 C)
{

	glm::mat4 tempV;

	// Calculate the combination of the model and view (camera inverse) matrices
	glm::mat4 modelview = Window::V * C * extra * initial;

	//glm::mat4 modelview = Window::V * extra * initial;


	glm::mat4 model = C * extra * initial;
	//glm::mat4 model = extra * initial;

	//first pass draw
	if (drawType == 1) {

		Model = glGetUniformLocation(Window::shadowID, "model");


		glUniformMatrix4fv(Model, 1, GL_FALSE, &model[0][0]);



		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);
		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);



		return;
	}


	

	if (Window::sbuffOn) {

		uProjection = glGetUniformLocation(Window::selectionID, "projection");
		uModelview = glGetUniformLocation(Window::selectionID, "modelview");
		// Now send these values to the shader program
		glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
		glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);


		glUniform1ui(glGetUniformLocation(Window::selectionID, "sbuffIndex"), sbuffIndex);

		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);
		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);



	}
	else if (environmentMap) {

		glUseProgram(Window::envID);




		//glm::mat4 model = C * extra * initial;
		//glm::mat4 model = extra * initial;

		tempV = Window::V;

		//use environmentMapping with envShader
		P = glGetUniformLocation(Window::envID, "projection");
		V = glGetUniformLocation(Window::envID, "view");
		//View = glGetUniformLocation(envShader, "cameraPos");
		Model = glGetUniformLocation(Window::envID, "model");
		// Now send these values to the shader program
		glUniformMatrix4fv(P, 1, GL_FALSE, &Window::P[0][0]);

		//glUniformMatrix4fv(V, 1, GL_FALSE, &Window::V[0][0]);
		glUniformMatrix4fv(V, 1, GL_FALSE, &tempV[0][0]);

		//glUniformMatrix4fv(View, 1, GL_FALSE, &Window::V[0][0]);
		//glUniformMatrix4fv(View, 1, GL_FALSE, &Window::cP[0][0]);


		glUniform3fv(glGetUniformLocation(Window::envID, "cameraPos"), 1, &(Window::cP[0]));


		glUniformMatrix4fv(Model, 1, GL_FALSE, &model[0][0]);


		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);

		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);

		


	}
	//regular shader used
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

		glUniform1i(glGetUniformLocation(Window::regID, "toon"), toon);

		glUniform1i(glGetUniformLocation(Window::regID, "beenShot"), beenShot);

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

void Geometry1::addChild(Node1 * child) {


}

void Geometry1::removeChild(Node1 * child) {


}

void Geometry1::update(int num) {

	if (num == 1) {

		drawType = 1;

	}
	else {

		drawType = 2;

	}


}



















Drone::Drone(const char *filepath)
{


	extra = glm::mat4(1.0f);

	environmentMap = 0;
	shadows = 0;
	toon = 0;
	beenShot = 0;

	//diffuse
	kd = { 0.61424f, 0.04136f, 0.04136f };

	//specular
	ks = { 0.727811f, 0.626959f, 0.626959f };

	//ambient
	ka = { 0.1745f, 0.01175f, 0.01175f };

	//shinyness
	p = 0.6f;

	//scale matrix
	S = glm::mat4(1.0f);

	//centering Transform1ation matrix
	T = glm::mat4(1.0f);


	initial = glm::mat4(1.0f);


	parse(filepath);


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

Drone::~Drone()
{
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a 
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO);
}

void Drone::parse(const char *filepath)
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

			indices.push_back(iV1 - 1);
			indices.push_back(iV2 - 1);
			indices.push_back(iV3 - 1);

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

	center = { centerX, centerY, centerZ };


	largestMax = xMax - xMin;

	if ((yMax - yMin) > largestMax) {

		largestMax = yMax - yMin;

	}

	if ((zMax - zMin) > largestMax) {

		largestMax = zMax - zMin;

	}


	//scale
	S = glm::scale(glm::mat4(1.0f), glm::vec3((2.0f / largestMax), (2.0f / largestMax), (2.0f / largestMax)));
	//center
	T = glm::translate(glm::mat4(1.0f), glm::vec3(-centerX, -centerY, -centerZ));


	initial = S*T;


	center = { 0.0f,0.0f,0.0f };


	fclose(fp);

}

void Drone::draw(glm::mat4 C)
{

	if (Window::sbuffOn) {

		return;

	}

	glm::mat4 tempV;

	// Calculate the combination of the model and view (camera inverse) matrices
	glm::mat4 modelview = Window::V * C * extra * initial;

	glm::mat4 model = C * extra * initial;

	//first pass draw
	if (drawType == 1) {

		Model = glGetUniformLocation(Window::shadowID, "model");

		glUniformMatrix4fv(Model, 1, GL_FALSE, &model[0][0]);

		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);
		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);

		return;
	}


	
	if (environmentMap) {

		glUseProgram(Window::envID);

		tempV = Window::V;

		//use environmentMapping with envShader
		P = glGetUniformLocation(Window::envID, "projection");
		V = glGetUniformLocation(Window::envID, "view");
		//View = glGetUniformLocation(envShader, "cameraPos");
		Model = glGetUniformLocation(Window::envID, "model");
		// Now send these values to the shader program
		glUniformMatrix4fv(P, 1, GL_FALSE, &Window::P[0][0]);

		//glUniformMatrix4fv(V, 1, GL_FALSE, &Window::V[0][0]);
		glUniformMatrix4fv(V, 1, GL_FALSE, &tempV[0][0]);

		//glUniformMatrix4fv(View, 1, GL_FALSE, &Window::V[0][0]);
		//glUniformMatrix4fv(View, 1, GL_FALSE, &Window::cP[0][0]);


		glUniform3fv(glGetUniformLocation(Window::envID, "cameraPos"), 1, &(Window::cP[0]));


		glUniformMatrix4fv(Model, 1, GL_FALSE, &model[0][0]);


		// Now draw the cube. We simply need to bind the VAO associated with it.
		glBindVertexArray(VAO);

		//glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

		// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
		glBindVertexArray(0);


	}
	//regular shader used
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

		glUniform1i(glGetUniformLocation(Window::regID, "toon"), toon);

		glUniform1i(glGetUniformLocation(Window::regID, "beenShot"), beenShot);

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


void Drone::up() {

	extra = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f))*extra;

}

void Drone::down() {

	extra = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f))*extra;

}

void Drone::rotR() {

	R = R*glm::rotate(glm::mat4(1.0f), 2.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, -1.0f, 0.0f));

	initial = initial * glm::rotate(glm::mat4(1.0f), 2.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, -1.0f, 0.0f));

}

void Drone::rotL() {

	R = R*glm::rotate(glm::mat4(1.0f), 2.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

	initial = initial * glm::rotate(glm::mat4(1.0f), 2.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

}

void Drone::forward() {

	extra = glm::translate(glm::mat4(1.0f), Window::forward)*extra;

}

void Drone::backward() {

	extra = glm::translate(glm::mat4(1.0f), -Window::forward)*extra;

}

void Drone::right() {

	extra = glm::translate(glm::mat4(1.0f), Window::right)*extra;

}

void Drone::left() {

	extra = glm::translate(glm::mat4(1.0f), -Window::right)*extra;

}


void Drone::addChild(Node1 * child) {


}

void Drone::removeChild(Node1 * child) {


}

void Drone::update(int num) {


	if (num == 1) {

		drawType = 1;

	}
	else {

		drawType = 2;

	}

}