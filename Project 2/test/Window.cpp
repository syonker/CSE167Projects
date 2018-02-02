#include "window.h"

const char* window_title = "GLFW Starter Project";
//Cube * cube;
GLint shaderProgram;

//make objects
OBJObject * bunny;
OBJObject * bear;
OBJObject * dragon;
OBJObject * cObject;

OBJObject * cMovingObject;

OBJObject * fakeObject;
OBJObject * sphere;
OBJObject * cone;

Light * directional;
Light * point;
Light * spot;
Light * cLight;

int normalColoring = 1;

double prevX;
double prevY;
double currX;
double currY;

glm::vec3 vPrev;
glm::vec3 vCurr;
glm::vec4 temp4;

float angle;

int mouse = 0;



// On some systems you need to change this to the absolute path
//#define VERTEX_SHADER_PATH "../shader.vert"
#define VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/CSE167StarterCode2-master/shader.vert"
//#define FRAGMENT_SHADER_PATH "../shader.frag"
#define FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/CSE167StarterCode2-master/shader.frag"

// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize_objects()
{
	//cube = new Cube();

	bunny = new OBJObject("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/bunny.obj",1);
	bear = new OBJObject("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/bear.obj",2);
	dragon = new OBJObject("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/dragon.obj",3);
	cObject = bunny;

	cMovingObject = bunny;

	fakeObject = new OBJObject("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/sphere.obj", 4);
	sphere = new OBJObject("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/sphere.obj", 4);
	cone = new OBJObject("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/cone.obj", 4);

	directional = new Light(1);
	point = new Light(2);
	spot = new Light(3);
	cLight = directional;

	cObject->toWorld = (cObject->S)*(cObject->T)*(glm::mat4(1.0f));
	cObject->initial = cObject->toWorld;

	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

	






	//glUniform3f(glGetUniformLocation(shaderProgram, "viewPos"), 0.0f, 0.0f, -1.0f);
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	delete(bunny);
	delete(bear);
	delete(dragon);
	delete(fakeObject);
	delete(sphere);
	delete(cone);
	delete(directional);
	delete(point);
	delete(spot);
	glDeleteProgram(shaderProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
	// Call the update function the cube
	//cube->update();
	//cObject->update();
}


void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	glUseProgram(shaderProgram);

	glUniform1i(glGetUniformLocation(shaderProgram, "light.normalColoring"), normalColoring);

	//send over the material attributes
	glUniform3fv(glGetUniformLocation(shaderProgram, "kd"), 1, &(cObject->kd[0]));
	glUniform3fv(glGetUniformLocation(shaderProgram, "ks"), 1, &(cObject->ks[0]));
	glUniform3fv(glGetUniformLocation(shaderProgram, "ka"), 1, &(cObject->ka[0]));
	glUniform1f(glGetUniformLocation(shaderProgram, "p"), cObject->p);

	//send over the camera position
	glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, &cam_pos[0]);

	cObject->draw(shaderProgram);
	
	if (cLight->type == 1) {

		temp4 = { (cLight->direction).x, (cLight->direction).y, (cLight->direction).z, 1.0f };

		temp4 = (fakeObject->lightM)*temp4;

		(cLight->direction).x = -temp4.x / temp4.w;
		(cLight->direction).y = -temp4.y / temp4.w;
		(cLight->direction).z = -temp4.z / temp4.w;
		

	} else if (cLight->type == 2) {

		sphere->draw(shaderProgram);
		
		temp4 = { (cLight->position).x, (cLight->position).y, (cLight->position).z, 1.0f };

		temp4 = (sphere->toWorld)*temp4;

		(cLight->position).x = temp4.x / temp4.w;
		(cLight->position).y = temp4.y / temp4.w;
		(cLight->position).z = temp4.z / temp4.w;
		

	} else if (cLight->type == 3) {

		cone->draw(shaderProgram);
		
		temp4 = { (cLight->position).x, (cLight->position).y, (cLight->position).z, 1.0f };

		temp4 = (cone->toWorld)*temp4;

		(cLight->position).x = temp4.x / temp4.w;
		(cLight->position).y = temp4.y / temp4.w;
		(cLight->position).z = temp4.z / temp4.w;

		temp4 = { (cLight->direction).x, (cLight->direction).y, (cLight->direction).z, 1.0f };

		temp4 = (cone->toWorld)*temp4;

		(cLight->direction).x = -temp4.x / temp4.w;
		(cLight->direction).y = -temp4.y / temp4.w;
		(cLight->direction).z = -temp4.z / temp4.w;
		
	}
	

	cLight->draw(shaderProgram);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}



//scroll
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	glm::vec3 tempp;

	if (cMovingObject->objType == 4) {

		if ((glm::length(cLight->position) > 1.0f) || glm::clamp(yoffset, -1.0, 1.0) > 0) {

			tempp = glm::normalize(cLight->position);

			tempp.x = glm::clamp(yoffset, -1.0, 1.0)*tempp.x;
			tempp.y = glm::clamp(yoffset, -1.0, 1.0)*tempp.y;
			tempp.z = glm::clamp(yoffset, -1.0, 1.0)*tempp.z;

			cMovingObject->toWorld = glm::translate(glm::mat4(1.0f), tempp)*(cMovingObject->toWorld);

			cMovingObject->lightM = glm::translate(glm::mat4(1.0f), tempp)*(cMovingObject->lightM);

		}
	}
	else {

		cMovingObject->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, glm::clamp(yoffset, -1.0, 1.0)))*(cMovingObject->toWorld);


		cMovingObject->lightM = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, glm::clamp(yoffset, -1.0, 1.0)))*(cMovingObject->lightM);

	}


}




//get mouse input
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT && action != GLFW_RELEASE) {

		mouse = 1;

		//get cursor position(x,y)
		glfwGetCursorPos(window, &prevX, &prevY);

	}
	else if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && action != GLFW_RELEASE) {

		//std::cerr << "TRACKBALL" << std::endl;

		mouse = 2;

		//get cursor position(x,y)
		glfwGetCursorPos(window, &prevX, &prevY);

	}
	else {

		mouse = 0;

	}

}

//get cursor position
void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	double resetX = currX;
	double resetY = currY;


	currX = xpos;
	currY = ypos;


	if (mouse == 2) {

		vPrev = trackBallMap(prevX, prevY);

		//Get cursor position(x, y)
		//Save(x, y) as curr_pos
		//glfwGetCursorPos(window, &currX, &currY);
		

		if ((currX < width) && (currY < height) && (currX > 0) && (currY > 0)) {

			//Trackballmap(curr_pos)
			vCurr = trackBallMap(currX, currY);

			//if (abs(vPrev.x - vCurr.x) > .01 && abs(vPrev.y - vCurr.y) > .01 && abs(vPrev.z - vCurr.z) > .01) {
			if (glm::distance(vPrev,vCurr) > 0.1f) {

				//calculate rotation
				angle = acos(glm::dot(vPrev, vCurr));

				//apply rotation
				cMovingObject->toWorld = (glm::rotate(glm::mat4(1.0f), angle, glm::cross(vPrev, vCurr)))*(cMovingObject->toWorld);

				//apply rotation
				cMovingObject->lightM = (glm::rotate(glm::mat4(1.0f), angle, glm::cross(vPrev, vCurr)))*(cMovingObject->lightM);


				prevX = currX;
				prevY = currY;

			}
			

		}
		else {

			//std::cerr << "OUT OF WINDOW" << std::endl;

			currX = resetX;
			currY = resetY;

		}

		

	}
	else if (mouse == 1) {

		
		cMovingObject->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3((float)(glm::clamp(currX-prevX,-0.08,0.08)),(float)(glm::clamp(prevY-currY, -0.08, 0.08)), 0.0f))*(cMovingObject->toWorld);

		cMovingObject->lightM = glm::translate(glm::mat4(1.0f), glm::vec3((float)(glm::clamp(currX - prevX, -0.08, 0.08)), (float)(glm::clamp(prevY - currY, -0.08, 0.08)), 0.0f))*(cMovingObject->lightM);


		prevX = currX;
		prevY = currY;

	}


	


}

glm::vec3 Window::trackBallMap(double xVal,double yVal)
{
	glm::vec3 v;
	float d;
	v.x = (float)((2.0f*xVal - width) / width);
	v.y = (float)((height - 2.0f*yVal) / height);
	v.z = 0.0f;
	d = glm::length(v);
	d = (d<1.0f) ? d : 1.0f;
	v.z = sqrtf(1.001f - d*d);
	glm::normalize(v);
	return v;


}



void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{

		// F1 = draw the bunny
		if (key == GLFW_KEY_F1)
		{
			cObject = bunny;

			cMovingObject = cObject;

			cObject->toWorld = (cObject->S)*(cObject->T)*(glm::mat4(1.0f));
			cObject->initial = cObject->toWorld;

		}

		// F2 = draw the bear
		if (key == GLFW_KEY_F2)
		{
			cObject = bear;

			cMovingObject = cObject;

			cObject->toWorld = (cObject->S)*(cObject->T)*(glm::mat4(1.0f));
			cObject->initial = cObject->toWorld;

		}

		// F3 = draw the dragon
		if (key == GLFW_KEY_F3)
		{
			cObject = dragon;

			cMovingObject = cObject;

			cObject->toWorld = (cObject->S)*(cObject->T)*(glm::mat4(1.0f));
			cObject->initial = cObject->toWorld;

		}

		// 1 = use directional light
		if (key == GLFW_KEY_1)
		{
			cLight = directional;

			cMovingObject = fakeObject;

			cMovingObject->toWorld = glm::mat4(1.0f);

			//glm::mat4 R(glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f)));

			//cMovingObject->toWorld = (cMovingObject->S)*(cMovingObject->T)*(glm::mat4(1.0f));
			//cMovingObject->initial = cMovingObject->toWorld;

		}

		// 2 = use point light
		if (key == GLFW_KEY_2)
		{
			cLight = point;

			cMovingObject = sphere;

			//cMovingObject->toWorld = glm::mat4(1.0f);

			//glm::mat4 R(glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f)));

			cMovingObject->toWorld = (cMovingObject->S)*(cMovingObject->T)*(glm::mat4(1.0f));
			cMovingObject->initial = cMovingObject->toWorld;

		}

		// 3 = use spot light
		if (key == GLFW_KEY_3)
		{
			cLight = spot;

			cMovingObject = cone;

			//cMovingObject->toWorld = glm::mat4(1.0f);
			glm::mat4 R(glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f)));

			cMovingObject->toWorld = (cMovingObject->S)*(cMovingObject->T)*(glm::mat4(1.0f)*R);
			cMovingObject->initial = cMovingObject->toWorld;

		}

		// 0 = switch back to controlling object
		if (key == GLFW_KEY_0)
		{

			cMovingObject = cObject;

			//cObject->toWorld = (cObject->S)*(cObject->T)*(glm::mat4(1.0f));
			//cObject->initial = cObject->toWorld;

		}

		// n = toggle normalColoring
		if (key == GLFW_KEY_N)
		{

			if (normalColoring) {

				//glUniform1i(glGetUniformLocation(shaderProgram, "light.normalColoring"), 0);

				normalColoring = 0;

				//glUniform1i(glGetUniformLocation(shaderProgram, "light.normalColoring"), normalColoring);

			}
			else {

				//glUniform1i(glGetUniformLocation(shaderProgram, "light.normalColoring"), 1);

				normalColoring = 1;

				//glUniform1i(glGetUniformLocation(shaderProgram, "light.normalColoring"), normalColoring);

			}

		}

		// Q = higher quad value
		if (key == GLFW_KEY_Q && mods == GLFW_MOD_SHIFT)
		{
			if (spot->quadAtt > 0.01f) {

				spot->quadAtt -= 0.005f;

			}
		}

		// q = lower quad val
		else if (key == GLFW_KEY_Q)
		{
			if (spot->quadAtt < 0.955f) {

				spot->quadAtt += 0.005f;

			}
		}

		// W = make spotlight narrower
		if (key == GLFW_KEY_W && mods == GLFW_MOD_SHIFT)
		{
			if (spot->cutoffAngle > 0.01f) {

				spot->cutoffAngle -= 0.005f;

			}
		}

		// w = make spotlight wider
		else if (key == GLFW_KEY_W)
		{
			if (spot->cutoffAngle < 0.955f) {

				spot->cutoffAngle += 0.005f;

			}
		}

		// E = make spot edge blurrier
		if (key == GLFW_KEY_E && mods == GLFW_MOD_SHIFT)
		{
			if (spot->exponent < 0.99f) {

				spot->exponent += 0.01f;

			}
		}

		// e = make spot edge sharper
		else if (key == GLFW_KEY_E)
		{
			if (spot->exponent > 0.02f) {

				spot->exponent -= 0.01f;

			}
		}

		// Z = move out
		if (key == GLFW_KEY_Z && mods == GLFW_MOD_SHIFT)
		{
			cMovingObject->out();
		}

		// z = move in
		else if (key == GLFW_KEY_Z)
		{
			cMovingObject->in();
		}

		// X = move right
		if (key == GLFW_KEY_X && mods == GLFW_MOD_SHIFT)
		{
			cMovingObject->right();
		}

		// x = move left
		else if (key == GLFW_KEY_X)
		{
			cMovingObject->left();
		}

		// Y = move up
		if (key == GLFW_KEY_Y && mods == GLFW_MOD_SHIFT)
		{
			cMovingObject->up();
		}

		// y = move down
		else if (key == GLFW_KEY_Y)
		{
			cMovingObject->down();
		}

		// r = reset position
		if (key == GLFW_KEY_R)
		{
			cMovingObject->resetPosition();
		}



		// S = scale up
		if (key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT)
		{
			cMovingObject->sUp();
		}

		// s = scale down
		else if (key == GLFW_KEY_S)
		{
			cMovingObject->sDown();
		}





		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}
