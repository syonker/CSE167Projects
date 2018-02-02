#include "window.h"

#define _CRT_SECURE_NO_WARNING

const char* window_title = "GLFW Starter Project";

//shaders used
GLint shaderProgram;
GLint skyshaderProgram;
GLint selectionshaderProgram;
GLint environmentshaderProgram;

//skybox creation
std::vector<std::string> faces;
unsigned int cubemapTexture;
SkyboxObject * skybox;


//selection buffer (max 255 objects) (0 = background)
std::vector<Geometry * > Window::sbuff;
GLuint Window::sbuffIndex = 1;
GLuint Window::sbuffOn = 0;

Geometry * selected;
unsigned char pix[4];
int selectionMode = 0;


//accessable scene graph parts
Node* scene;


Curve* curve;


//create a directional light
Light * directional;
Light * cLight;

glm::vec3 Window::cP;


int Window::normalColoring = 0;
glm::vec3 Window::view;


//for car
glm::vec3 Window::old_pos = { 20.0f, 0.0f, 0.0f };
glm::vec3 Window::new_pos;
float Window::carT = 0.0;
glm::mat4 Window::roller = glm::mat4(1.0f);


double prevX;
double prevY;
double currX;
double currY;

double prevXC;
double prevYC;
double currXC;
double currYC;

glm::vec3 vPrev;
glm::vec3 vCurr;
glm::vec4 temp4;

float angle;

int mouse = 0;

int pause = 0;

unsigned int val;


#define VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/CSE167StarterCode2-master/shader.vert"
#define FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/CSE167StarterCode2-master/shader.frag"

#define SKY_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/CSE167StarterCode2-master/skyshader.vert"
#define SKY_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/CSE167StarterCode2-master/skyshader.frag"

#define SELECTION_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/CSE167StarterCode2-master/selectionshader.vert"
#define SELECTION_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/CSE167StarterCode2-master/selectionshader.frag"

#define ENVIRONMENT_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/CSE167StarterCode2-master/environmentshader.vert"
#define ENVIRONMENT_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/CSE167StarterCode2-master/environmentshader.frag"


// Default camera parameters
//glm::vec3 cam_pos(0.0f, 0.0f, 20.0f);		// e  | Position of camera
//glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at

glm::vec3 cam_pos(62.6087f, -62.6087f, 100.0f);
glm::vec3 cam_look_at(62.6087f,-62.6087f, 0.0f);
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);	    // up | What orientation "up" is

//glm::vec3 cam_pos_initial(0.0f, 0.0f, 20.0f);
//glm::vec3 cam_look_at_initial(0.0f, 0.0f, 0.0f);

glm::vec3 cam_pos_initial(62.6087f, -62.6087f, 100.0f);
glm::vec3 cam_look_at_initial(62.6087f, -62.6087f, 0.0f);
glm::vec3 cam_up_initial(0.0f, 1.0f, 0.0f);

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;

Geometry * coaster;

Geometry * map;

int riderView = 0;


void Window::initialize_objects()
{

	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

	skyshaderProgram = LoadShaders(SKY_VERTEX_SHADER_PATH, SKY_FRAGMENT_SHADER_PATH);

	selectionshaderProgram = LoadShaders(SELECTION_VERTEX_SHADER_PATH, SELECTION_FRAGMENT_SHADER_PATH);

	environmentshaderProgram = LoadShaders(ENVIRONMENT_VERTEX_SHADER_PATH, ENVIRONMENT_FRAGMENT_SHADER_PATH);




	curve = new Curve(shaderProgram, selectionshaderProgram, environmentshaderProgram);




	//Geometry * bunny = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/bunny.obj", shaderProgram, selectionshaderProgram, environmentshaderProgram);
	//bunny->tag = "BUNNY";
	//glm::mat4 bunnyInitial = glm::mat4(1.0f);

	Geometry * s1 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, environmentshaderProgram, 2);
	s1->tag = "s1";
	s1->environmentMap = 1;
	//glm::mat4 s1Initial = glm::translate(glm::mat4(1.0f), {62.6087f, -62.6087f, 0.0f});
	glm::mat4 s1Initial = glm::translate(glm::mat4(1.0f), { 20.0f, 0.0f, 0.0f });

	glm::mat4 s1Scale = glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 2.0f });

	s1->initial = s1Initial*s1Scale*s1->initial;

	coaster = s1;


	Geometry * s2 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, environmentshaderProgram, 2);
	s2->tag = "s2";
	s2->environmentMap = 1;
	glm::mat4 s2Initial = glm::translate(glm::mat4(1.0f), {62.6087f, -62.6087f, 0.0f });

	//glm::mat4 s2Scale = glm::scale(glm::mat4(1.0f), { 5.0f, 5.0f, 5.0f });

	//s2->initial = s2Initial*s2Scale*s2->initial;
	s2->initial = s2Initial*s2->initial;

	map = s2;


	//Transform* bmtx = new Transform(bunnyInitial);
	Transform* s1mtx = new Transform(glm::mat4(1.0f));

	//bmtx->addChild(bunny);
	s1mtx->addChild(s1);

	Transform* modelmtx = new Transform(glm::mat4(1.0f));
	//modelmtx->addChild(bmtx);
	modelmtx->addChild(s1mtx);

	Group* objects = new Group();
	objects->addChild(modelmtx);

	scene = objects;

	
	

	directional = new Light(1);
	cLight = directional;

	skybox = new SkyboxObject();	

	faces = {
		"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/mars_rt.jpg",
		"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/mars_lf.jpg",
		"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/mars_up.jpg",
		"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/mars_dn.jpg",
		"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/mars_bk.jpg",
		"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/mars_ft.jpg"
	};
	
	cubemapTexture = loadCubemap(faces);

	
	
}

unsigned int Window::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//added for environment mapping
	glEnable(GL_TEXTURE_CUBE_MAP);

	return textureID;
}





/*

void Window::makeTrack()
{
	float t;
	int i;
	glm::vec3 q;
	std::vector<glm::vec3> finalqs;
	std::vector<glm::vec3> p;

	//p0
	p.push_back({0.0f,5.0f,0.0f});
	//p1
	p.push_back({ 1.0f,6.0f,0.0f });
	//p2
	p.push_back({ 2.0f,10.0f,0.0f });
	//p3
	p.push_back({ 8.0f,10.0f,0.0f });

	for (t = 0.0f; t < 1.0f; t += 0.1f) {

		q = { 0.0f,0.0f,0.0f };


		for (i = 0; i < 3; i++) {

			q += (bernstein(i,t)*p[i]);


		}

		finalqs.push_back(q);

	}

	drawTrack(finalqs);


}


void Window::drawTrack(std::vector<glm::vec3> points)
{
	int i;

	//std::cerr << "POINTS SIZE: " << points.size() << std::endl;
	
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);

	//glDrawArrays(GL_LINE_STRIP, 0, points.size());
	for (i = 0; i < points.size()-1; i++) {

		glVertex3f((points[i]).x, (points[i]).y, (points[i]).z) ;

		glVertex3f((points[i+1]).x, (points[i+1]).y, (points[i+1]).z);

	}

	glEnd();
	

}
*/















// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{

	delete(directional);

	glDeleteProgram(shaderProgram);
	glDeleteProgram(skyshaderProgram);
	glDeleteProgram(selectionshaderProgram);
	glDeleteProgram(environmentshaderProgram);
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
	

	
	
	
}


void Window::display_callback(GLFWwindow* window)
{

	float v;
	float a = 0.00005f;

	int usePhysics = 1;

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//skybox
	glDepthMask(GL_FALSE);
	glUseProgram(skyshaderProgram);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	skybox->draw(skyshaderProgram,cubemapTexture);

	glDepthMask(GL_TRUE);

	
	if (riderView == 1) {

		cam_pos = old_pos;

		if (carT < 7.999) {

			cam_look_at = curve->getCarPos(carT + 0.001f);

		}
		else {

			cam_look_at = curve->getCarPos(0.0f);
			
		}

		cam_up = {0.0f,0.0f,1.0f};

		V = glm::lookAt(cam_pos, cam_look_at, cam_up);

	}
	

	//the rest

	//saves so the shaders can access it inside draw methods
	//view = cam_pos;
	cP = cam_pos;
	
	//map->draw(glm::mat4(1.0f));
	
	

	cLight->draw(shaderProgram);


	(curve->spheres)->draw(glm::mat4(1.0f));

	curve->draw();

	if (usePhysics) {

		//scene->draw(glm::mat4(1.0f));

		//v = sqrt((-2.0f)*a*(old_pos.z - curve->highestZ)) + .0005f;

		
		if ((curve->highestZ - old_pos.z) < 0) {

			v = sqrt((2.0f)*.0000001*(old_pos.z - curve->highestZ)) + .0005f;

		}
		else {

			v = sqrt((2.0f)*.0000001*(curve->highestZ - old_pos.z)) + .0005f;

		}
		

		//if (v < .0005f) {

		//	v = .0005f;

		//}



		carT += v;

		if (carT < 7.999) {

			if (isnan(carT)) {

				//std::cerr << "CART NEGATIVE 1" << std::endl;

			}

			new_pos = curve->getCarPos(carT);

		}
		else {

			carT = carT - 7.999f;

			if (isnan(carT)) {

				//std::cerr << "old pos " << old_pos.z << std::endl;

				//std::cerr << "high pos " << curve->highestZ << std::endl;

				//std::cerr << "CART NEGATIVE 2" << std::endl;

			}

			new_pos = curve->getCarPos(carT);

		}

		roller = glm::translate(glm::mat4(1.0f), { new_pos - old_pos });

		coaster->extra = roller*coaster->extra;

		old_pos = new_pos;

		

	}
	else {


		if (carT < 7.999f) {

			if (pause) {


			}
			else {

				carT += 0.001f;

			}

		}
		else {

			carT = 0.0f;

		}

		new_pos = curve->getCarPos(carT);


		roller = glm::translate(glm::mat4(1.0f), { new_pos - old_pos });

		coaster->extra = roller*coaster->extra;

		old_pos = new_pos;




	}




	//std::cerr << carT << std::endl;

	scene->draw(glm::mat4(1.0f));


	//switched
	glfwSwapBuffers(window);
	
	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers

	
}



//scroll
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	glm::mat4 T;
	glm::vec4 tempp;
	glm::vec3 in;

	in = glm::normalize(cam_look_at - cam_pos);

	T = glm::translate(glm::mat4(1.0f), { yoffset*in.x, yoffset*in.y, yoffset*in.z });

	tempp = { cam_pos.x, cam_pos.y, cam_pos.z, 1.0f };

	tempp = T*tempp;

	cam_pos.x = tempp.x;
	cam_pos.y = tempp.y;
	cam_pos.z = tempp.z;

	V = glm::lookAt(cam_pos, cam_look_at, cam_up);


}




//get mouse input
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {

		mouse = 1;

		//get cursor position(x,y)
		glfwGetCursorPos(window, &currX, &currY);

		std::cerr << "Regular click" << std::endl;


		// Clear the color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use a selection buffer to indicate what part of the scene is being selected
		//the rest
		glUseProgram(selectionshaderProgram);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		sbuffOn = 1;
		//scene->draw(glm::mat4(1.0f));
		(curve->spheres)->draw(glm::mat4(1.0f));
		sbuffOn = 0;

		//get color at currX, currY
		glReadPixels((GLint)currX, (GLint)(height - currY), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pix);

		val = ((unsigned int)pix[0]);

		//if we chose an object
		if (val != 0) {

			selected = sbuff[val - 1];

			if (selected) {

				std::cerr << selected->tag << " selected" << std::endl;

				selectionMode = 1;
				prevX = currX;
				prevY = currY;

			}
			else {

				std::cerr << "ERROR Invalid Index" << std::endl;

				selectionMode = 0;

			}

		//background selected
		}
		else {

			std::cerr << "Background selected" << std::endl;

			selectionMode = 0;
		}





	}
	else if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && action != GLFW_RELEASE) {

		mouse = 2;

		//get cursor position(x,y)
		glfwGetCursorPos(window, &prevXC, &prevYC);

	}
	else {

		mouse = 0;

	}

}

//get cursor position
void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	float horzDisp, vertDisp;
	glm::vec3 horzVec, vertVec, sumVec;
	glm::vec4 four;
	
	//normal camera rotation controls
	if (mouse == 2) {

		if (selectionMode == 0) {

			glm::mat4 R;
			glm::mat4 T;
			glm::vec4 temp;
			double resetXC = currXC;
			double resetYC = currYC;

			currXC = xpos;
			currYC = ypos;


			if ((currXC < width) && (currYC < height) && (currXC > 0) && (currYC > 0)) {

				vPrev = trackBallMap(prevXC, prevYC);

				vCurr = trackBallMap(currXC, currYC);

				if (glm::distance(vPrev, vCurr) > 0.1f) {

					//calculate rotation
					angle = acos(glm::dot(vPrev, vCurr));

					R = glm::rotate(glm::mat4(1.0f), angle, glm::cross(vPrev, vCurr));

					temp = { cam_pos.x, cam_pos.y, cam_pos.z, 1.0f };
					temp = R*temp;
					cam_pos.x = temp.x / temp.w;
					cam_pos.y = temp.y / temp.w;
					cam_pos.z = temp.z / temp.w;

					temp = { cam_up.x, cam_up.y, cam_up.z, 0.0f };
					temp = R*temp;
					cam_up.x = temp.x;
					cam_up.y = temp.y;
					cam_up.z = temp.z;

					V = glm::lookAt(cam_pos, cam_look_at, cam_up);

					prevXC = currXC;
					prevYC = currYC;

				}

			}

			else {

				std::cerr << "OUT OF WINDOW" << std::endl;

				currXC = resetXC;
				currYC = resetYC;

			}

		}
		else {


			//std::cerr << "Moving " << selected->tag << std::endl;

			Geometry * alsoMove;


			currX = xpos;
			currY = ypos;

			//possibly change the .08 to have to do with the max/min horz and vertical values  
			horzDisp = (float)(glm::clamp(currX - prevX, -0.08, 0.08));
			vertDisp = (float)(glm::clamp(currY - prevY, -0.08, 0.08));

			horzVec = glm::normalize(glm::cross(cam_up,(cam_look_at-cam_pos)));
			vertVec = cam_up;

			sumVec.x = -(horzDisp*horzVec.x + vertDisp*vertVec.x);
			sumVec.y = -(horzDisp*horzVec.y + vertDisp*vertVec.y);
			sumVec.z = -(horzDisp*horzVec.z + vertDisp*vertVec.z);

			selected->extra = glm::translate(glm::mat4(1.0f), sumVec) * selected->extra;

			four = { (selected->center).x,(selected->center).y, (selected->center).z, 1.0f };
			four = glm::translate(glm::mat4(1.0f), sumVec)*four;
			(selected->center).x = (four.x) / (four.w);
			(selected->center).y = (four.y) / (four.w);
			(selected->center).z = (four.z) / (four.w);

			if (selected->interp == 1) {

				if ((val - 1) == 0) {
				
					alsoMove = sbuff[23];

					alsoMove->extra = glm::translate(glm::mat4(1.0f), sumVec) * alsoMove->extra;

					four = { (alsoMove->center).x,(alsoMove->center).y, (alsoMove->center).z, 1.0f };
					four = glm::translate(glm::mat4(1.0f), sumVec)*four;
					(alsoMove->center).x = (four.x) / (four.w);
					(alsoMove->center).y = (four.y) / (four.w);
					(alsoMove->center).z = (four.z) / (four.w);

					alsoMove = sbuff[val];

					alsoMove->extra = glm::translate(glm::mat4(1.0f), sumVec) * alsoMove->extra;

					four = { (alsoMove->center).x,(alsoMove->center).y, (alsoMove->center).z, 1.0f };
					four = glm::translate(glm::mat4(1.0f), sumVec)*four;
					(alsoMove->center).x = (four.x) / (four.w);
					(alsoMove->center).y = (four.y) / (four.w);
					(alsoMove->center).z = (four.z) / (four.w);

				}
				else if ((val - 1) == 23) {

					alsoMove = sbuff[0];

					alsoMove->extra = glm::translate(glm::mat4(1.0f), sumVec) * alsoMove->extra;

					four = { (alsoMove->center).x,(alsoMove->center).y, (alsoMove->center).z, 1.0f };
					four = glm::translate(glm::mat4(1.0f), sumVec)*four;
					(alsoMove->center).x = (four.x) / (four.w);
					(alsoMove->center).y = (four.y) / (four.w);
					(alsoMove->center).z = (four.z) / (four.w);

					alsoMove = sbuff[val - 2];

					alsoMove->extra = glm::translate(glm::mat4(1.0f), sumVec) * alsoMove->extra;

					four = { (alsoMove->center).x,(alsoMove->center).y, (alsoMove->center).z, 1.0f };
					four = glm::translate(glm::mat4(1.0f), sumVec)*four;
					(alsoMove->center).x = (four.x) / (four.w);
					(alsoMove->center).y = (four.y) / (four.w);
					(alsoMove->center).z = (four.z) / (four.w);


				}
				else {

					alsoMove = sbuff[val];

					alsoMove->extra = glm::translate(glm::mat4(1.0f), sumVec) * alsoMove->extra;

					four = { (alsoMove->center).x,(alsoMove->center).y, (alsoMove->center).z, 1.0f };
					four = glm::translate(glm::mat4(1.0f), sumVec)*four;
					(alsoMove->center).x = (four.x) / (four.w);
					(alsoMove->center).y = (four.y) / (four.w);
					(alsoMove->center).z = (four.z) / (four.w);

					alsoMove = sbuff[val - 2];

					alsoMove->extra = glm::translate(glm::mat4(1.0f), sumVec) * alsoMove->extra;

					four = { (alsoMove->center).x,(alsoMove->center).y, (alsoMove->center).z, 1.0f };
					four = glm::translate(glm::mat4(1.0f), sumVec)*four;
					(alsoMove->center).x = (four.x) / (four.w);
					(alsoMove->center).y = (four.y) / (four.w);
					(alsoMove->center).z = (four.z) / (four.w);


				}


			}

			else if (selected->interp == 0) {

				if (val == 24) {


					alsoMove = sbuff[0];

				}
				else {

					alsoMove = sbuff[val];

				}

				if (alsoMove->interp == 1) {

					if (val == 24) {

						alsoMove = sbuff[1];

					}
					else {

						alsoMove = sbuff[val + 1];

					}

					alsoMove->extra = glm::translate(glm::mat4(1.0f), -sumVec) * alsoMove->extra;

					four = { (alsoMove->center).x,(alsoMove->center).y, (alsoMove->center).z, 1.0f };
					four = glm::translate(glm::mat4(1.0f), -sumVec)*four;
					(alsoMove->center).x = (four.x) / (four.w);
					(alsoMove->center).y = (four.y) / (four.w);
					(alsoMove->center).z = (four.z) / (four.w);


				}
				else {

					if ((val - 1) == 1) {

						alsoMove = sbuff[23];

					}
					else {

						alsoMove = sbuff[val - 3];

					}

					alsoMove->extra = glm::translate(glm::mat4(1.0f), -sumVec) * alsoMove->extra;

					four = { (alsoMove->center).x,(alsoMove->center).y, (alsoMove->center).z, 1.0f };
					four = glm::translate(glm::mat4(1.0f), -sumVec)*four;
					(alsoMove->center).x = (four.x) / (four.w);
					(alsoMove->center).y = (four.y) / (four.w);
					(alsoMove->center).z = (four.z) / (four.w);


				}


			}

			prevX = currX;
			prevY = currY;


		}

	}

	/*
	//selection buffer
	else if (mouse == -1) {

		double resetX = currX;
		double resetY = currY;
		unsigned char pix[4];
		Geometry * selected;

		currX = xpos;
		currY = ypos;

		// Clear the color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use a selection buffer to indicate what part of the scene is being selected
		//the rest
		glUseProgram(selectionshaderProgram);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		sbuffOn = 1;
		scene->draw(glm::mat4(1.0f));
		sbuffOn = 0;

		//get color at currX, currY
		glReadPixels(currX, height - currY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pix);

		//if we chose an object
		if (((unsigned int)pix[0]) != 0) {

			selected = sbuff[((unsigned int)pix[0]) - 1];

			//std::cerr << (unsigned int)pix[0] << " selected" << std::endl;

			
			if (selected) {

				std::cerr << selected->tag << " selected" << std::endl;
				//std::cerr << (unsigned int)pix[0] << " selected" << std::endl;

				selected->initial = glm::translate(glm::mat4(1.0f), glm::vec3((float)(glm::clamp(currX - prevX, -0.08, 0.08)), (float)(glm::clamp(prevY - currY, -0.08, 0.08)), 0.0f))*(selected->initial);

			}
			else {

				std::cerr << "ERROR Invalid Index" << std::endl;

			}

			prevX = currX;
			prevY = currY;

		//background selected
		} else {
		
			std::cerr << "Background selected" << std::endl;

			currX = resetX;
			currY = resetY;
		
		}

		

	}
	*/

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

		// r = reset camera
		if (key == GLFW_KEY_R)
		{
			cam_pos = cam_pos_initial;
			cam_look_at = cam_look_at_initial;
			cam_up = cam_up_initial;

			V = glm::lookAt(cam_pos, cam_look_at, cam_up);

		}

		// t = rider camera
		if (key == GLFW_KEY_T)
		{
			if (riderView == 1) {

				cam_pos = cam_pos_initial;
				cam_look_at = cam_look_at_initial;
				cam_up = cam_up_initial;

				V = glm::lookAt(cam_pos, cam_look_at, cam_up);

				riderView = 0;

			}
			else {

				riderView = 1;

			}

		}


		// n = toggle normalColoring
		if (key == GLFW_KEY_N)
		{
			if (normalColoring) {
				normalColoring = 0;
			}
			else {
				normalColoring = 1;
			}
		}

		// p = toggle pause
		if (key == GLFW_KEY_P)
		{
			if (pause) {
				pause = 0;
			}
			else {
				pause = 1;
			}
		}

		// h = highest point
		if (key == GLFW_KEY_H)
		{

			carT = curve->highestT;

			//std::cerr << curve->highestZ << std::endl;
			
		}


		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}
