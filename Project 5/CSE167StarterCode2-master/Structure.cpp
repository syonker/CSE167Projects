#include "Node.cpp"
#include <iostream>
#include <list>

class Structure : public Node {

public:
	glm::mat4 MT;
	std::list<Node*> children;

	Structure(glm::mat4 M) {
		this->MT = M;
	}

	void draw(glm::mat4 C) {
		for (std::list<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
			(*it)->draw(C*MT);
		}
	}
	void update() {

	}

	void addChild(Node* child) {
		children.push_back(child);
	}

	void removeChild(Node* child) {
		children.remove(child);
	}
};