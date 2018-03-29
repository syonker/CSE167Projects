#include "Node.cpp"
#include "OBJObject.h"
#include <iostream>

class Geometry : public Node {
public:
	OBJObject * obj;

	Geometry(const char* filepath, GLuint shader) {
		init(filepath, shader);
	}

	void draw(glm::mat4 C) {
		glDisable(GL_CULL_FACE);
		(*obj).draw(C);
	}
	void update() {
	
	}

	void init(const char * filepath, GLuint shader) {
		obj = new OBJObject(filepath, shader);
	}
};