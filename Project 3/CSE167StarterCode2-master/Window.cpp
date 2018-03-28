#include "window.h"

#define _CRT_SECURE_NO_WARNING

const char* window_title = "GLFW Starter Project";
//Cube * cube;
GLint shaderProgram;

GLint skyshaderProgram;

std::vector<std::string> faces;
unsigned int cubemapTexture;

//make objects
//OBJObject * sphere;
//OBJObject * dragon;
//OBJObject * cObject;

int Window::drawSphere = 0;

glm::vec3 Window::cP;

int Window::moveArmy=0;

glm::mat4 Window::armyMoverS(1.0f);
glm::mat4 Window::armyMoverR(1.0f);

int Window::oneRobot=0;

int Window::cullCount = 0;

glm::mat4 Window::sI(1.0f);

glm::vec3 Window::sOrigin;

const glm::vec3 Window::planesNormals[6] =
{
	glm::vec3(0, 0, -1), //Near plane
	glm::vec3(0, 0, 1), //Far plane
	glm::vec3(0, -1, 0), //Top plane
	glm::vec3(0, 1, 0), //Bottom plane
	glm::vec3(-1, 0, 0), //Right plane
	glm::vec3(1, 0, 0) //Left plane
};

const glm::vec3  Window::planesPoints[6] =
{
	glm::vec3(0, 0, 1), //Near plane
	glm::vec3(0, 0, -1), //Far plane
	glm::vec3(0, 1, 0), //Top plane
	glm::vec3(0, -1, 0), //Bottom plane
	glm::vec3(1, 0, 0), //Right plane
	glm::vec3(-1, 0, 0) //Left plane
};



//accessable scene graph parts
Node* drawMe;
Transform* modelmtx;

Transform* hmtx;
Transform* lmtx;
Transform* rmtx;
Transform* bmtx;
Transform* tmtx;
Transform* ttmtx;
Transform* smtx;

Group* satellite;

Group* satellite_party;


//animations
glm::mat4 moveForward = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.001f });
glm::mat4 moveBackward = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -0.001f });
glm::mat4 moveMatrix = moveForward;
int moveCount = 0;

glm::mat4 moveUp = glm::translate(glm::mat4(1.0f), { 0.0f, 0.001f, 0.0f });
glm::mat4 moveDown = glm::translate(glm::mat4(1.0f), { 0.0f, -0.001f, 0.0f });
glm::mat4 moveUpDown = moveUp;
int moveCountUpDown = 0;

glm::mat4 inchForward = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.004f });
glm::mat4 inchBackward = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, -0.004f });
glm::mat4 inchMatrix = inchForward;
int inchCount = 0;

glm::mat4 inchMatrixL = inchBackward;
int inchCountL = 0;






Light * directional;
Light * cLight;

SkyboxObject * skybox;

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
#define VERTEX_SHADER_PATH  "../shader.vert"
//#define FRAGMENT_SHADER_PATH "../shader.frag"
#define FRAGMENT_SHADER_PATH "../shader.frag"

#define SKY_VERTEX_SHADER_PATH  "../skyshader.vert"
//#define FRAGMENT_SHADER_PATH "../shader.frag"
#define SKY_FRAGMENT_SHADER_PATH "../skyshader.frag"


// Default camera parameters
glm::vec3 cam_pos(0.0f, 100.0f, 0.0f);		// e  | Position of camera
//(0,0,20)
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 0.0f, 1.0f);	    // up | What orientation "up" is
//(0,1,0)

glm::vec3 cam_pos_initial(0.0f, 100.0f, 0.0f);
glm::vec3 cam_look_at_initial(0.0f, 0.0f, 0.0f);
glm::vec3 cam_up_initial(0.0f, 0.0f, 1.0f);

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;


void Window::initialize_objects()
{

	int i, j;

	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

	skyshaderProgram = LoadShaders(SKY_VERTEX_SHADER_PATH, SKY_FRAGMENT_SHADER_PATH);

	//cube = new Cube();

	//sphere = new OBJObject("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/shere.obj",1);
	//dragon = new OBJObject("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/dragon.obj",3);
	//cObject = bunny;


	Geometry * head = new Geometry("../../../OBJFiles/head.obj", shaderProgram, 2);
	Geometry * larm = new Geometry("../../../OBJFiles/limb.obj", shaderProgram, 1);
	Geometry * rarm = new Geometry("../../../OBJFiles/limb.obj", shaderProgram, 1);
	Geometry * body = new Geometry("../../../OBJFiles/body.obj", shaderProgram, 0);
	Geometry * top = new Geometry("../../../OBJFiles/head.obj", shaderProgram, 1);
	Geometry * toptop = new Geometry("../../../OBJFiles/head.obj", shaderProgram, 1);
	Geometry * sphere = new Geometry("../../../OBJFiles/sphere.obj", shaderProgram, -1);



	//all
	//glm::mat4 allR = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	
	//head
	//glm::mat4 headT = glm::translate(glm::mat4(1.0f), { 0.0f, 1.55f, 0.0f });
	//glm::mat4 headT = glm::translate(glm::mat4(1.0f), { 0.0f, -3.0f, 4.75f });
	glm::mat4 headT = glm::translate(glm::mat4(1.0f), { 0.0f, 6.20f, 4.75f });
	glm::mat4 headInitial = headT;

	//larm
	glm::mat4 larmT = glm::translate(glm::mat4(1.0f), { -1.35f, -3.5f, 3.5f });
	glm::mat4 larmInitial = larmT;

	//rarmn
	glm::mat4 rarmT = glm::translate(glm::mat4(1.0f), { 1.35f, -3.5f, 3.5f });
	glm::mat4 rarmInitial = rarmT;

	//body
	glm::mat4 bodyT = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.25f });
	glm::mat4 bodyInitial = bodyT;

	//top
	glm::mat4 topT = glm::translate(glm::mat4(1.0f), { 0.0f, -3.0f, 4.75f });
	glm::mat4 topInitial = topT;

	//toptop
	glm::mat4 toptopT = glm::translate(glm::mat4(1.0f), { 0.0f, -1.9f, 4.75f });
	glm::mat4 toptopInitial = toptopT;

	//sphere
	glm::mat4 sphereT = glm::translate(glm::mat4(1.0f), { 0.0f, 1.0f, 0.25f });
	//glm::mat4 sphereS = glm::scale(glm::mat4(1.0f), { 1.5f, 1.5f, 1.5f });
	glm::mat4 sphereInitial = sphereT;


	hmtx = new Transform(headInitial);
	lmtx = new Transform(larmInitial);
	rmtx = new Transform(rarmInitial);
	bmtx = new Transform(bodyInitial);
	tmtx = new Transform(topInitial);
	ttmtx = new Transform(toptopInitial);
	smtx = new Transform(sphereInitial);

	hmtx->addChild(head);
	lmtx->addChild(larm);
	rmtx->addChild(rarm);
	bmtx->addChild(body);
	tmtx->addChild(top);
	ttmtx->addChild(toptop);
	smtx->addChild(sphere);

	//edit each of these to animate each separate part
	// hmtx->M = BS * hmtx->M;

	modelmtx = new Transform(glm::mat4(1.0f));
	modelmtx->addChild(hmtx);
	modelmtx->addChild(lmtx);
	modelmtx->addChild(rmtx);
	modelmtx->addChild(bmtx);
	modelmtx->addChild(tmtx);
	modelmtx->addChild(ttmtx);
	modelmtx->addChild(smtx);

	//edit modelmtx to move whole satellite
	// modelmtx->M = BS * modelmtx->M;

	satellite = new Group();
	satellite->addChild(modelmtx);

	satellite_party = new Group();

	//drawMe = satellite_party;

	//drawMe = satellite;

	/*
	Transform* leftbot = new Transform(glm::translate(glm::mat4(1.0f), { -6.0f, 0.0f, -6.0f }));
	Transform* lefttop = new Transform(glm::translate(glm::mat4(1.0f), { -6.0f, 0.0f, 6.0f }));
	Transform* rightbot = new Transform(glm::translate(glm::mat4(1.0f), { 6.0f, 0.0f, -6.0f }));
	Transform* righttop = new Transform(glm::translate(glm::mat4(1.0f), { 6.0f, 0.0f, 6.0f }));

	leftbot->addChild(satellite);
	lefttop->addChild(satellite);
	rightbot->addChild(satellite);
	righttop->addChild(satellite);

	satellite_party->addChild(leftbot);
	satellite_party->addChild(lefttop);
	satellite_party->addChild(rightbot);
	satellite_party->addChild(righttop);
	*/
	
	for (i = 0; i < 10; i++) {
	
		for (j = 0; j < 10; j++) {

			Transform* part = new Transform(glm::translate(glm::mat4(1.0f), { (-6.0f*5) + ((float)i*6.0f), 0.0f, (-6.0f * 5) + ((float)j*6.0f) }));

			part->addChild(satellite);

			satellite_party->addChild(part);

		}
	
	
	}
	
	
	
	
	





	directional = new Light(1);
	cLight = directional;





	skybox = new SkyboxObject();	

	//unsigned char * image = loadPPM("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 2/PalldioPalace_intern_back.ppm", width, height);
	
	//static std::vector<std::string> faces;
	//static unsigned int cubemapTexture;

	/*
	faces = {
	"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 3/lake1_rt.jpg",
	"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 3/lake1_lf.jpg",
	"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 3/lake1_up.jpg",
	"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 3/lake1_dn.jpg",
	"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 3/lake1_bk.jpg",
	"C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 3/lake1_ft.jpg"
	};
	*/

	faces = {
		"../../alien_rt.jpg",
		"../../alien_lf.jpg",
		"../../alien_up.jpg",
		"../../alien_dn.jpg",
		"../../alien_bk.jpg",
		"../../alien_ft.jpg",
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
			//std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}













// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	//delete(dragon);

	delete(directional);

	glDeleteProgram(shaderProgram);
	glDeleteProgram(skyshaderProgram);
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

	//get n and d values for each plane

	Window::cullCount = 0;

	drawMe->update();

	//std::cerr << "Objects Culled: " << cullCount << std::endl;

	//toptop
	if (moveCountUpDown < 200) {

		ttmtx->M = moveUpDown * ttmtx->M;
		moveCountUpDown++;

	}
	else {

		if (moveUpDown == moveUp) {

			moveUpDown = moveDown;

		}
		else {

			moveUpDown = moveUp;

		}

		moveCountUpDown = 0;

	}




	//rarm
	if (inchCount < 200) {

		rmtx->M = inchMatrix * rmtx->M;
		inchCount++;

	}
	else {

		if (inchMatrix == inchForward) {

			inchMatrix = inchBackward;

		}
		else {

			inchMatrix = inchForward;

		}

		inchCount = 0;

	}

	//larm
	if (inchCountL < 200) {

		lmtx->M = inchMatrixL * lmtx->M;
		inchCountL++;

	}
	else {

		if (inchMatrixL == inchForward) {

			inchMatrixL = inchBackward;

		}
		else {

			inchMatrixL = inchForward;

		}

		inchCountL = 0;

	}




	
	//whole thing
	if (moveCount < 2000) {

		modelmtx->M = moveMatrix * modelmtx->M;
		moveCount++;

	}
	else {

		if (moveMatrix == moveForward) {

			moveMatrix = moveBackward;

		}
		else {

			moveMatrix = moveForward;

		}

		moveCount = 0;

	}
	

}


void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	
	glDepthMask(GL_FALSE);
	glUseProgram(skyshaderProgram);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	skybox->draw(skyshaderProgram,cubemapTexture);

	glDepthMask(GL_TRUE);
	// ... draw rest of the scene
	
	

	// Clear the color and depth buffers
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cP = cam_pos;

	// Use the shader of programID
	glUseProgram(shaderProgram);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glUniform1i(glGetUniformLocation(shaderProgram, "light.normalColoring"), normalColoring);

	//send over the camera position
	//glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, &cam_pos[0]);


	if (oneRobot) {

		drawMe = satellite;

	}
	else {

		drawMe = satellite_party;

	}

	drawMe->draw(glm::mat4(1.0f));

	cLight->draw(shaderProgram);

	

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}



//scroll
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	glm::mat4 T;
	glm::vec4 temp;

	T = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, yoffset });

	if (moveArmy) {

		if (yoffset > 0) {

			armyMoverS = armyMoverS*glm::scale(glm::mat4(1.0f), { 1.05f, 1.05f, 1.05f });

		}
		else {

			armyMoverS = armyMoverS*glm::scale(glm::mat4(1.0f), { 1.0f/1.05f, 1.0f / 1.05f, 1.0f / 1.05f });

		}

		/*
		hmtx->M = hmtx->M * armyMover;
		lmtx->M = lmtx->M * armyMover;
		rmtx->M = rmtx->M * armyMover;
		bmtx->M = bmtx->M * armyMover;
		tmtx->M = tmtx->M * armyMover;
		ttmtx->M = ttmtx->M * armyMover;
		smtx->M = smtx->M * armyMover;
		*/
		satellite_party->M = satellite_party->M*armyMoverS;
		
		
	}
	else {

		temp = { cam_pos.x, cam_pos.y, cam_pos.z, 1.0f };

		temp = T*temp;

		cam_pos.x = temp.x;
		cam_pos.y = temp.y;
		cam_pos.z = temp.z;

		V = glm::lookAt(cam_pos, cam_look_at, cam_up);

	}

	/*
	if ((glm::length(cam_pos) > 1.0f) || glm::clamp(yoffset, -1.0, 1.0) > 0) {

		T = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, glm::clamp(yoffset, -1.0, 1.0)*((cam_pos.z) / (length(cam_pos))) });

		temp = { cam_pos.x, cam_pos.y, cam_pos.z, 1.0f };

		temp = T*temp;

		cam_pos.x = temp.x / temp.w;
		cam_pos.y = temp.y / temp.w;
		cam_pos.z = temp.z / temp.w;

		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}*/

}




//get mouse input
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT && action != GLFW_RELEASE) {

		mouse = 1;

		//get cursor position(x,y)
		//glfwGetCursorPos(window, &prevX, &prevY);

	}
	else if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT && action != GLFW_RELEASE) {

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
	glm::mat4 R;
	glm::mat4 T;
	glm::vec4 temp;
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
				//cMovingObject->toWorld = (glm::rotate(glm::mat4(1.0f), angle, glm::cross(vPrev, vCurr)))*(cMovingObject->toWorld);

				R = glm::rotate(glm::mat4(1.0f), angle, glm::cross(vPrev, vCurr));

				//apply rotation
				//cMovingObject->lightM = (glm::rotate(glm::mat4(1.0f), angle, glm::cross(vPrev, vCurr)))*(cMovingObject->lightM);


				if (moveArmy) {

					

					armyMoverR = R*armyMoverR;

					//modelmtx->M = armyMover * modelmtx->M;

					satellite_party->M = satellite_party->M*armyMoverR;

					/*
					hmtx->M = hmtx->M * armyMover;
					lmtx->M = lmtx->M * armyMover;
					rmtx->M = rmtx->M * armyMover;
					bmtx->M = bmtx->M * armyMover;
					tmtx->M = tmtx->M * armyMover;
					ttmtx->M = ttmtx->M * armyMover;
					smtx->M = smtx->M * armyMover;
					*/


				}
				else {


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

				}

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

		
		//cMovingObject->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3((float)(glm::clamp(currX-prevX,-0.08,0.08)),(float)(glm::clamp(prevY-currY, -0.08, 0.08)), 0.0f))*(cMovingObject->toWorld);

		//cMovingObject->lightM = glm::translate(glm::mat4(1.0f), glm::vec3((float)(glm::clamp(currX - prevX, -0.08, 0.08)), (float)(glm::clamp(prevY - currY, -0.08, 0.08)), 0.0f))*(cMovingObject->lightM);

		T = glm::translate(glm::mat4(1.0f), glm::vec3((float)(glm::clamp(currX - prevX, -0.08, 0.08)), (float)(glm::clamp(prevY - currY, -0.08, 0.08)), 0.0f));

		temp = { cam_pos.x, cam_pos.y, cam_pos.z, 1.0f };
		temp = T*temp;
		cam_pos.x = temp.x / temp.w;
		cam_pos.y = temp.y / temp.w;
		cam_pos.z = temp.z / temp.w;

		temp = { cam_up.x, cam_up.y, cam_up.z, 1.0f };
		temp = T*temp;
		cam_up.x = temp.x / temp.w;
		cam_up.y = temp.y / temp.w;
		cam_up.z = temp.z / temp.w;

		V = glm::lookAt(cam_pos, cam_look_at, cam_up);

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
			//cObject = bunny;

			//cObject->toWorld = (cObject->S)*(cObject->T)*(glm::mat4(1.0f));
			//cObject->initial = cObject->toWorld;

		}

		// F3 = draw the dragon
		if (key == GLFW_KEY_F3)
		{
			//cObject = dragon;

			//cObject->toWorld = (cObject->S)*(cObject->T)*(glm::mat4(1.0f));
			//cObject->initial = cObject->toWorld;

		}

		// s = toggle drawSphere
		if (key == GLFW_KEY_S)
		{

			if (drawSphere) {

				drawSphere = 0;

			}
			else {

				drawSphere = 1;

			}

		}

		// a = toggle moveArmy
		if (key == GLFW_KEY_A)
		{

			if (moveArmy) {

				moveArmy = 0;

			}
			else {

				moveArmy = 1;

			}

		}

		// o = toggle one robot
		if (key == GLFW_KEY_O)
		{

			if (oneRobot) {

				oneRobot = 0;

			}
			else {

				oneRobot = 1;

			}

		}

		// 1 
		if (key == GLFW_KEY_1)
		{
			cLight->direction = {1.0,0.0,0.0};

		}
		// 1 
		if (key == GLFW_KEY_2)
		{
			cLight->direction = { 0.0,-1.0,0.0 };

		}
		// 1 
		if (key == GLFW_KEY_3)
		{
			cLight->direction = { -1.0,0.0,0.0 };

		}
		// 1 
		if (key == GLFW_KEY_4)
		{
			cLight->direction = { 0.0,1.0,0.0 };

		}
		// 1 
		if (key == GLFW_KEY_5)
		{
			cLight->direction = { 0.0,0.0,1.0 };

		}
		// 1 
		if (key == GLFW_KEY_6)
		{
			cLight->direction = { 0.0,0.0,-1.0 };

		}

		// r = reset camera
		if (key == GLFW_KEY_R)
		{
			cam_pos = cam_pos_initial;
			cam_look_at = cam_look_at_initial;
			cam_up = cam_up_initial;

			V = glm::lookAt(cam_pos, cam_look_at, cam_up);

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


		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}
