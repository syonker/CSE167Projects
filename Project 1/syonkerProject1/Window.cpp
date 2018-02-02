#include "Window.h"

const char* window_title = "GLFW Starter Project";
Cube cube(5.0f);

OBJObject bunny("../bunny.obj");
OBJObject bear("../bear.obj");
OBJObject dragon("../dragon.obj");

OBJObject *cObject = &bunny;

int rasterizeOn = 0;
int pointSize = 1;

static int window_width = 512, window_height = 512;
static float* pixels = new float[window_width * window_height * 3];


int Window::width;
int Window::height;



void Window::initialize_objects()
{
}

void Window::clean_up()
{
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

struct Color    // generic color class
{
	float r, g, b;  // red, green, blue
};

// Clear frame buffer
void clearBuffer()
{
	Color clearColor = { 1.0, 1.0, 1.0 };   // clear color: black
	for (int i = 0; i<window_width*window_height; ++i)
	{
		pixels[i * 3] = clearColor.r;
		pixels[i * 3 + 1] = clearColor.g;
		pixels[i * 3 + 2] = clearColor.b;
	}
}


// Draw a point into the frame buffer
void drawPoint(int x, int y, float r, float g, float b)
{

	if ((window_width > x) && ((0.0f) < x)) {

		if ((window_height > y) && ((0.0f) < y)) {
		
			int offset = y*window_width * 3 + x * 3;
			pixels[offset] = r;
			pixels[offset + 1] = g;
			pixels[offset + 2] = b;

		}

	}
	
}


void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;

	if (!rasterizeOn) {

		// Set the viewport size
		glViewport(0, 0, width, height);
		// Set the matrix mode to GL_PROJECTION to determine the proper camera properties
		glMatrixMode(GL_PROJECTION);
		// Load the identity matrix
		glLoadIdentity();
		// Set the perspective of the projection viewing frustum

		//( feild of view , aspect ratio , near, far)
		gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0);

		// Move camera back 20 units so that it looks at the origin (or else it's in the origin)
		glTranslatef(0, 0, -20);

	}
	else {

		window_width = width;
		window_height = height;
		delete[] pixels;
		pixels = new float[window_width * window_height * 3];

	}


}


void rasterize()
{

	float x, y, z, mag, xPrime, yPrime;

	int j;

	glm::vec4 p;
	glm::mat4 P;
	glm::mat4 C;
	glm::mat4 D;

	p = glm::vec4(1.0f);

	P = glm::perspective(glm::radians(60.0f), ((float)(window_width) / (float)(window_height)), 1.0f, 1000.0f);

	C = glm::lookAt(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	D = glm::mat4(1.0f);

	D[0][0] = (((float)window_width)/2.0f);
	D[1][1] = (((float)window_height)/2.0f);
	D[2][2] = 0.5f;
	D[3][2] = 0.5f;
	D[3][1] = (((float)window_height) / 2.0f);
	D[3][0] = (((float)window_width) / 2.0f);

	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it

	// Loop through all the vertices of this OBJ Object and render them
	for (unsigned int i = 0; i < cObject->vertices.size(); ++i)
	{

		p[0] = cObject->vertices[i].x;
		p[1] = cObject->vertices[i].y;
		p[2] = cObject->vertices[i].z;
		p[3] = 1.0f;

		p = (cObject->toWorld)*(p);

		p = C*(p);

		p = P*(p);

		p = D*(p);

		x = cObject->normals[i].x;
		y = cObject->normals[i].y;
		z = cObject->normals[i].z;

		mag = sqrt((x*x) + (y*y) + (z*z));

		xPrime = (p[0] / p[3]);
		yPrime = (p[1] / p[3]);

		drawPoint((int)xPrime, (int)yPrime, (x / mag), (y / mag), (z / mag));

		for (j = 1; j < pointSize; j++) {

			drawPoint((int)xPrime + j, (int)yPrime + j, (x / mag), (y / mag), (z / mag));

			drawPoint((int)xPrime - j, (int)yPrime - j, (x / mag), (y / mag), (z / mag));

		}
	

	}


}



void Window::idle_callback()
{
	// Perform any updates as necessary. Here, we will spin the cube slightly.
	(*cObject).update();
}

void Window::display_callback(GLFWwindow* window)
{

	if (!rasterizeOn) {

		// Clear the color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Set the matrix mode to GL_MODELVIEW
		glMatrixMode(GL_MODELVIEW);
		// Load the identity matrix
		glLoadIdentity();
	
		//Render object
		(*cObject).draw();

		// Swap buffers
		glfwSwapBuffers(window);
		// Gets events, including input such as keyboard and mouse or window resizing
		glfwPollEvents();

	}
	else {

		clearBuffer();

		rasterize();

		// glDrawPixels writes a block of pixels to the framebuffer
		glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, pixels);

		// Gets events, including input such as keyboard and mouse or window resizing
		glfwPollEvents();
		// Swap buffers
		glfwSwapBuffers(window);

	}

	
	

}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{

		// F1 = draw the bunny
		if (key == GLFW_KEY_F1)
		{
			cObject = &bunny;
		}

		// F2 = draw the bear
		if (key == GLFW_KEY_F2)
		{
			cObject = &bear;
		}

		// F3 = draw the dragon
		if (key == GLFW_KEY_F3)
		{
			cObject = &dragon;
		}

		// P = increase the point size
		if (key == GLFW_KEY_P && mods == GLFW_MOD_SHIFT)
		{
			if (!rasterizeOn) {
				(*cObject).incPoints();
			}
			else {
				pointSize++;
			}
		}

		// p = decrease the point size
		else if (key == GLFW_KEY_P)
		{
			if (!rasterizeOn) {
				(*cObject).decPoints();
			}
			else {
				if (pointSize > 1) {
					pointSize--;
				}
			}
		}

		// Z = move out
		if (key == GLFW_KEY_Z && mods == GLFW_MOD_SHIFT)
		{
			(*cObject).out();
		}

		// z = move in
		else if (key == GLFW_KEY_Z)
		{
			(*cObject).in();
		}

		// X = move right
		if (key == GLFW_KEY_X && mods == GLFW_MOD_SHIFT)
		{
			(*cObject).right();
		}

		// x = move left
		else if (key == GLFW_KEY_X)
		{
			(*cObject).left();
		}

		// Y = move up
		if (key == GLFW_KEY_Y && mods == GLFW_MOD_SHIFT)
		{
			(*cObject).up();
		}

		// y = move down
		else if (key == GLFW_KEY_Y)
		{
			(*cObject).down();
		}

		// S = scale up
		if (key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT)
		{
			(*cObject).sUp();
		}

		// s = scale down
		else if (key == GLFW_KEY_S)
		{
			(*cObject).sDown();
		}

		// O = orbit clockwise
		if (key == GLFW_KEY_O && mods == GLFW_MOD_SHIFT)
		{
			(*cObject).oClock(10.0f);
		}

		// o = reset position
		else if (key == GLFW_KEY_O)
		{
			(*cObject).oCounterclock(10.0f);
		}


		// R = reset orientation
		if (key == GLFW_KEY_R && mods == GLFW_MOD_SHIFT)
		{
			(*cObject).resetOrientation();
		}

		// r = reset position
		else if (key == GLFW_KEY_R)
		{
			(*cObject).resetPosition();
		}

		// m = switch between the two rendering modes.
		if (key == GLFW_KEY_M)
		{
			if (!rasterizeOn) {

				rasterizeOn = 1;

				Window::resize_callback(window, width, height);
			}
			else {
				rasterizeOn = 0;
			}
		}
		

		// ESC = Close the WINDOW
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}
