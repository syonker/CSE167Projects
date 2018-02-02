#include "OBJObject.h"
#include <iostream>
#include <math.h>

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);

	//positional inverse
	pInv = glm::mat4(1.0f);

	//orientational inverse
	oInv = glm::mat4(1.0f);

	//transformation matrix
	M = glm::mat4(1.0f);

	p = { 1.0f,1.0f };

	parse(filepath);

	this->angle = 0.0f;
	this->pSize = 1.0f;
	this->minSize = 2.0f;
	this->scaleCount = 1.0f;
}

void OBJObject::parse(const char *filepath) 
{
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data

	using namespace std;

	FILE* fp;     // file pointer
	float x, y, z;  // vertex coordinates
	float r, g, b, q;  // vertex color
	int c1, c2;    // characters read from file

	glm::vec3 v;

	fp = fopen(filepath,"rb");

	
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

			v.x = x;
			v.y = y;
			v.z = z;

			vertices.push_back(v);

		}
		//vertex normal
		else if ((c1 == 'v') && (c2 == 'n')) {

			fscanf(fp, " %f %f %f %f %f %f %f", &x, &y, &z, &r, &g, &b, &q);

			v.x = x;
			v.y = y;
			v.z = z;

			normals.push_back(v);

		}
		//ignore line
		else {

			fscanf(fp, "%*[^\n]\n");

		}

		c1 = fgetc(fp);

	}
	
	fclose(fp);

}

void OBJObject::draw() 
{

	float x, y, z, mag;

	glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&(toWorld[0][0]));

	glBegin(GL_POINTS);
	// Loop through all the vertices of this OBJ Object and render them
	for (unsigned int i = 0; i < vertices.size(); ++i) 
	{

		x = normals[i].x;
		y = normals[i].y;
		z = normals[i].z;

		mag = sqrt((x*x)+(y*y)+(z*z));

		// Set the color of the object
		glColor3f((x/mag), (y/mag), (z/mag));

		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);

	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();
}



void OBJObject::update()
{
	spin(1.0f);
}

void OBJObject::spin(float deg)
{

	this->angle = deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
	
	// This creates the matrix to rotate the object
	M = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

	this->toWorld = (this->toWorld)*M;

}

void OBJObject::in()
{
	M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	this->toWorld = M*(this->toWorld);

	//get the inverse
	M[3][0] = -M[3][0];
	M[3][1] = -M[3][1];
	M[3][2] = -M[3][2];

	//store the invese
	pInv = M*pInv;
}

void OBJObject::out()
{
	M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	this->toWorld = M*(this->toWorld);

	//get the inverse
	M[3][0] = -M[3][0];
	M[3][1] = -M[3][1];
	M[3][2] = -M[3][2];

	//store the invese
	pInv = M*pInv;
}

void OBJObject::left()
{
	M = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	this->toWorld = M*(this->toWorld);

	//get the inverse
	M[3][0] = -M[3][0];
	M[3][1] = -M[3][1];
	M[3][2] = -M[3][2];

	//store the invese
	pInv = M*pInv;
}

void OBJObject::right()
{
	M = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	this->toWorld = M*(this->toWorld);

	//get the inverse
	M[3][0] = -M[3][0];
	M[3][1] = -M[3][1];
	M[3][2] = -M[3][2];

	//store the invese
	pInv = M*pInv;
}

void OBJObject::down()
{
	M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	this->toWorld = M*(this->toWorld);

	//get the inverse
	M[3][0] = -M[3][0];
	M[3][1] = -M[3][1];
	M[3][2] = -M[3][2];

	//store the invese
	pInv = M*pInv;
}

void OBJObject::up()
{
	M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	this->toWorld = M*(this->toWorld);

	//get the inverse
	M[3][0] = -M[3][0];
	M[3][1] = -M[3][1];
	M[3][2] = -M[3][2];

	//store the invese
	pInv = M*pInv;
}

void OBJObject::sUp()
{

	scaleCount=(1.5f)*scaleCount;

	// Loop through all the vertices of this OBJ Object
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{

		vertices[i].x = 1.5f*(vertices[i].x);
		vertices[i].y = 1.5f*(vertices[i].y);
		vertices[i].z = 1.5f*(vertices[i].z);

	}

}

void OBJObject::sDown()
{

	scaleCount = scaleCount/(1.5f);

	// Loop through all the vertices of this OBJ Object
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{

		vertices[i].x = (1.0f / 1.5f)*(vertices[i].x);
		vertices[i].y = (1.0f / 1.5f)*(vertices[i].y);
		vertices[i].z = (1.0f / 1.5f)*(vertices[i].z);

	}

}

void OBJObject::oClock(float deg)
{

	this->angle = deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;

	// This creates the matrix to rotate the object
	M = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));

	this->toWorld = M*(this->toWorld);

	oInv = (glm::transpose(M))*oInv;
}

void OBJObject::oCounterclock(float deg)
{

	this->angle = deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;

	// This creates the matrix to rotate the object
	M = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, -1.0f));

	this->toWorld = M*(this->toWorld);

	oInv = (glm::transpose(M))*oInv;

}


void OBJObject::decPoints()
{

	if (this->pSize > this->minSize) {

		this->pSize -= this->minSize;

		glPointSize(this->pSize);

	}

}

void OBJObject::incPoints()
{

	this->pSize += this->minSize;

	glPointSize(this->pSize);

}

void OBJObject::resetPosition()
{

	this->toWorld = pInv*(this->toWorld);

	//reset the inverse
	pInv = glm::mat4(1.0f);

}

void OBJObject::resetOrientation()
{

	this->toWorld = oInv*(this->toWorld);

	//reset the inverse
	oInv = glm::mat4(1.0f);

	// Loop through all the vertices of this OBJ Object
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{

		vertices[i].x = (1.0f / scaleCount)*(vertices[i].x);
		vertices[i].y = (1.0f / scaleCount)*(vertices[i].y);
		vertices[i].z = (1.0f / scaleCount)*(vertices[i].z);

	}

	//reset the scale count
	scaleCount = 1.0f;

}