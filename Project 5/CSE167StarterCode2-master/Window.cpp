#include "window.h"
#include "include/irrKlang.h"
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

#define _CRT_SECURE_NO_WARNING

const char* window_title = "GLFW Starter Project";

using namespace irrklang;


// Audio
ISoundEngine* engine;
ISound* music;

//Grammars
Rule* rule11;
Geometry* Base;

Rule* rule21;
Geometry* Top_dome;
Rule* rule22;
Geometry* Top_comm_ant1;
Transform* tca1;
Geometry* Top_comm_ant2;
Transform* tca2;
Geometry* Top_comm_base;
Rule* rule23;
Geometry* Top_extend;

Rule* rule31;
Geometry* Mid_flat;
Rule* rule32;
Geometry* Mid_base1;
Geometry* Mid_left;
Rule* rule33;
Geometry* Mid_base2;
Geometry* Mid_right;



//************************************
//ADDED SCALING
//ALSO CHANGED 1 to 11
Geometry* window1;
Geometry* window12;
Rule* rule12;
Geometry* Base2;
Geometry* window2;
Geometry* window22;
Rule* rule13;
Geometry* Base3;
Geometry* window3;
Geometry* window32;

Rule* rule34;
Geometry* Mid_base3;
Geometry* Mid_back;
Rule* rule35;
Geometry* Mid_base4;
Geometry* Mid_front;

int seed = 0;

//************************************








Structure * building1;
Structure * building2;
Structure * building3;
Structure * building4;

std::vector<Structure*> structures;

Structure * testbuild;




//particle systems
ParticleSystem test_system;
ParticleSystem test_system2;
ParticleSystem test_system3;
ParticleSystem test_system4;
ParticleSystem test_system5;


//procedural plants
std::vector<ProceduralPlants *> trees;
std::vector<glm::vec3> locations;


//bunny stuff
std::vector<float> Window::bunnyVertices;
std::vector<unsigned int> Window::bunnyIndices;
std::vector<float> Window::bunnyNormals;
glm::mat4 Window::bunnyS;
glm::mat4 Window::bunnyT;


int Window::firstPass;

//shaders used
GLint Window::regID;
GLint Window::skyboxID;
GLint Window::selectionID;
GLint Window::envID;
GLint Window::shadowID;
GLint Window::bufferID;
GLint Window::basicID;


//particle stuff
glm::vec3 Window::shotPos;
int Window::objectShot = 0;



//skybox creation
std::vector<std::string> faces;
unsigned int cubemapTexture;
SkyboxObject * skybox;

//selection buffer (max 255 objects) (0 = background)
std::vector<Geometry1 * > Window::sbuff;
GLuint Window::sbuffIndex = 1;
GLuint Window::sbuffOn = 0;

Geometry1 * selected;
unsigned char pix[4];
int selectionMode = 0;
unsigned int val;


//scene graph
Node1* scene;
Geometry1* object;

//create a directional light
Light * directional;
Light * Window::cLight;


//currPosition that can be accessed by shaders in draw
glm::vec3 Window::cP;

int Window::normalColoring = 0;

int Window::particlesOn = 1;

int Window::soundOn = 1;

int Window::shadowWindow = 0;

int Window::shadowsOn = 1;

#define VERTEX_SHADER_PATH  "../shader.vert"
#define FRAGMENT_SHADER_PATH "../shader.frag"

#define SKY_VERTEX_SHADER_PATH  "../skyshader.vert"
#define SKY_FRAGMENT_SHADER_PATH "../skyshader.frag"

#define SELECTION_VERTEX_SHADER_PATH  "../selectionshader.vert"
#define SELECTION_FRAGMENT_SHADER_PATH "../selectionshader.frag"

#define ENVIRONMENT_VERTEX_SHADER_PATH  "../environmentshader.vert"
#define ENVIRONMENT_FRAGMENT_SHADER_PATH "../environmentshader.frag"

#define SHADOW_VERTEX_SHADER_PATH  "../shadowshader.vert"
#define SHADOW_FRAGMENT_SHADER_PATH "../shadowshader.frag"

#define BUFFER_VERTEX_SHADER_PATH  "../buffshader.vert"
#define BUFFER_FRAGMENT_SHADER_PATH "../buffshader.frag"

#define BASIC_VERTEX_SHADER_PATH  "../basicshader.vert"
#define BASIC_FRAGMENT_SHADER_PATH "../basicshader.frag"




/*
#define VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/shader.vert"
#define FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/shader.frag"

#define SKY_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/skyshader.vert"
#define SKY_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/skyshader.frag"

#define SELECTION_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/selectionshader.vert"
#define SELECTION_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/selectionshader.frag"

#define ENVIRONMENT_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/environmentshader.vert"
#define ENVIRONMENT_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/environmentshader.frag"

#define SHADOW_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/shadowshader.vert"
#define SHADOW_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/shadowshader.frag"

#define BUFFER_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/buffshader.vert"
#define BUFFER_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/buffshader.frag"

#define BASIC_VERTEX_SHADER_PATH  "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/basicshader.vert"
#define BASIC_FRAGMENT_SHADER_PATH "C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/CSE167StarterCode2-master/basicshader.frag"
*/

glm::vec3 droneStart = { 0.0f, 15.0f, 150.0f };

//glm::vec3 droneStart = { 0.0f, -2.5f, 15.0f };

//glm::vec3 droneStart = { 0.0f, 5.0f, 20.0f };

/*
glm::vec3 cam_pos(droneStart.x + 1.05, droneStart.y + 5.2, droneStart.z - 11.5);
glm::vec3 cam_look_at(droneStart.x + 1.05, droneStart.y + 5.2, droneStart.z - 20);
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);
*/

glm::vec3 cam_pos(droneStart.x + 1, droneStart.y - 11.3, droneStart.z - 145);
glm::vec3 cam_look_at(droneStart.x + 1, droneStart.y - 11.3, droneStart.z - 155);
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);

glm::vec3 cam_pos_initial(droneStart.x + 1.05, droneStart.y + 5.2, droneStart.z - 11.5);
glm::vec3 cam_look_at_initial(droneStart.x + 1.05, droneStart.y + 5.2, droneStart.z - 20);
glm::vec3 cam_up_initial(0.0f, 1.0f, 0.0f);

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;

glm::vec3 Window::forward;
glm::vec3 Window::right;

//glm::mat4 Window::camM = glm::mat4(1.0f);

Drone * drone;

Line * shot;




//shadow mapping variables

GLuint Window::Framebuffer;

GLuint Window::quad_vertexbuffer;
GLuint Window::quad_vertexTXbuffer;
GLuint Window::VAO;
GLuint Window::VBO;
GLuint Window::VBO2;
GLuint Window::EBO;

GLuint Window::depthTexture;

GLuint Window::depthMatrixID;
//GLuint Window::TextureID;
GLuint Window::DepthBiasID;
GLuint Window::ShadowMapID;

glm::mat4 Window::depthMVP;


Transform1* modelmtx;






// INITIALIZING AUDIO
void init_audio() {
	engine = createIrrKlangDevice();
	music = engine->play3D("../../sounds/music.wav",
		vec3df(0, 0, 0), true, false, true);

	if (music)
		music->setMinDistance(1000.0f);

	engine->setListenerPosition(vec3df(0, 0, 0),
		vec3df(0, 0, 1));

}



// GENERATE GRAMMARS
void Window::generate_grammars() {
	//FOR TESTING
	testbuild = new Structure(glm::mat4(1.0f));

	glm::mat4 CR = glm::rotate(glm::mat4(1.0f), -90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 CT = glm::translate(glm::mat4(1.0f), glm::vec3(0, 30, 0));
	glm::mat4 CS = glm::scale(glm::mat4(1.0f), glm::vec3(.75f, 0.75f, 0.75f));

	//Rotations
	glm::mat4 MR22 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MR23 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MR31 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MR321 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MR322 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 MR331 = glm::rotate(glm::mat4(1.0f), -90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MR332 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

	//Translations
	glm::mat4 MT221 = glm::translate(glm::mat4(1.0f), glm::vec3(-20, 10, 5));
	glm::mat4 MT222 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 10, 0));
	glm::mat4 MT31 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -75, 0));
	glm::mat4 MT32 = glm::translate(glm::mat4(1.0f), glm::vec3(-30, 0, 0));
	glm::mat4 MT33 = glm::translate(glm::mat4(1.0f), glm::vec3(30, 0, 0));

	//Scales
	glm::mat4 MS221 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 2.5f, 0.5f));
	glm::mat4 MS222 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 3.5f, 1.0f));
	glm::mat4 MS223 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 1.0f));
	glm::mat4 MS23 = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 1.0f, 0.25f));
	glm::mat4 MS31 = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 0.1f, 1.5f));
	glm::mat4 MS321 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 1.0f));
	glm::mat4 MS322 = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 0.35f, 0.35f));
	glm::mat4 MS331 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 1.0f));
	glm::mat4 MS332 = glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 0.35f, 0.35f));


	//***********************************************************************
	glm::mat4 MR341 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MR342 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 MR351 = glm::rotate(glm::mat4(1.0f), -90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 MR352 = glm::rotate(glm::mat4(1.0f), 90 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 MT34 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 30));
	glm::mat4 MT35 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -30));

	glm::mat4 MS341 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 1.0f));
	glm::mat4 MS342 = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.35f, 1.5f));
	glm::mat4 MS351 = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 1.0f));
	glm::mat4 MS352 = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.35f, 1.5f));
	//***********************************************************************



	// Rule 1
	rule11 = new Rule(glm::mat4(1.0f));
	Base = new Geometry("../../body.obj", regID);
	Base->obj->toWorld = Base->obj->toWorld * CS * CR;
	rule11->addChild(Base);

	//***********************************************************************
	window1 = new Geometry("../../../OBJFiles/sphere.obj", regID);
	window1->obj->toWorld = window1->obj->toWorld * (glm::scale(glm::mat4(1.0f), glm::vec3(8, 8, 8))) * (glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1.5)));
	window12 = new Geometry("../../OBJFiles/sphere.obj", regID);
	window12->obj->toWorld = window12->obj->toWorld * (glm::scale(glm::mat4(1.0f), glm::vec3(8, 8, 8))) * (glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 1.5)));
	rule11->addChild(window1);
	rule11->addChild(window12);

	// Rule 1.2
	rule12 = new Rule(glm::mat4(1.0f));
	Base2 = new Geometry("../../OBJFiles/body.obj", regID);
	Base2->obj->toWorld = Base2->obj->toWorld * CS * CR;
	rule12->addChild(Base2);
	window2 = new Geometry("../../OBJFiles/head.obj", regID);
	window2->obj->toWorld = window2->obj->toWorld * (glm::scale(glm::mat4(1.0f), glm::vec3(.5f, .5f, .5f))) * (glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 28))) * glm::rotate(glm::mat4(1.0f), 180 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	window22 = new Geometry("../../OBJFiles/head.obj", regID);
	window22->obj->toWorld = window22->obj->toWorld * (glm::scale(glm::mat4(1.0f), glm::vec3(.5f, .5f, .5f))) * (glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -28)));
	rule12->addChild(window2);
	rule12->addChild(window22);


	// Rule 1.3
	rule13 = new Rule(glm::mat4(1.0f));
	Base3 = new Geometry("../../OBJFiles/body.obj", regID);
	Base3->obj->toWorld = Base3->obj->toWorld * CS * CR;
	rule13->addChild(Base3);
	window3 = new Geometry("../../OBJFiles/body.obj", regID);
	window3->obj->toWorld = window3->obj->toWorld * (glm::scale(glm::mat4(1.0f), glm::vec3(.75f, .35f, .75f))) * (glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	rule13->addChild(window3);


	//***********************************************************************





	// Rule 2.1
	rule21 = new Rule(glm::mat4(1.0f));
	Top_dome = new Geometry("../../OBJFiles/head.obj", regID);
	Top_dome->obj->toWorld = Top_dome->obj->toWorld * CS * CR;
	rule21->addChild(Top_dome);

	// Rule 2.2
	rule22 = new Rule(glm::mat4(1.0f));
	Top_comm_ant1 = new Geometry("../../OBJFiles/antenna.obj", regID);
	Top_comm_ant1->obj->toWorld = Top_comm_ant1->obj->toWorld * MS221 * MT221 * MR22;
	Top_comm_ant2 = new Geometry("../../OBJFiles/antenna.obj", regID);
	Top_comm_ant2->obj->toWorld = Top_comm_ant2->obj->toWorld * MS222 * MT222 * MR22;
	Top_comm_base = new Geometry("../../OBJFiles/body.obj", regID);
	Top_comm_base->obj->toWorld = Top_comm_base->obj->toWorld * MS223 * MR22;
	rule22->addChild(Top_comm_ant1);
	rule22->addChild(Top_comm_ant2);
	rule22->addChild(Top_comm_base);

	// Rule 2.3
	rule23 = new Rule(glm::mat4(1.0f));
	Top_extend = new Geometry("../../OBJFiles/body.obj", regID);
	Top_extend->obj->toWorld = Top_extend->obj->toWorld * MS23 * MR23;
	rule23->addChild(Top_extend);

	// Rule 31
	rule31 = new Rule(glm::mat4(1.0f));
	Mid_flat = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_flat->obj->toWorld = Mid_flat->obj->toWorld * MS31 * MT31 * MR31;
	rule31->addChild(Mid_flat);

	// Rule 32
	rule32 = new Rule(glm::mat4(1.0f));
	Mid_base1 = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_base1->obj->toWorld = Mid_base1->obj->toWorld * MS321 * MR321;
	Mid_left = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_left->obj->toWorld = Mid_left->obj->toWorld * MS322 * MT32 * MR322;
	rule32->addChild(Mid_base1);
	rule32->addChild(Mid_left);

	// Rule 33
	rule33 = new Rule(glm::mat4(1.0f));
	Mid_base2 = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_base2->obj->toWorld = Mid_base2->obj->toWorld * MS331 * MR331;
	Mid_right = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_right->obj->toWorld = Mid_right->obj->toWorld * MS332 * MT33 * MR332;
	rule33->addChild(Mid_base2);
	rule33->addChild(Mid_right);


	//***********************************************************************
	// Rule 3.4
	rule34 = new Rule(glm::mat4(1.0f));
	Mid_base3 = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_base3->obj->toWorld = Mid_base3->obj->toWorld * MS341 * MR341;
	Mid_back = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_back->obj->toWorld = Mid_back->obj->toWorld * MS342 * MT34 * MR342;
	rule34->addChild(Mid_base3);
	rule34->addChild(Mid_back);

	// Rule 3.5
	rule35 = new Rule(glm::mat4(1.0f));
	Mid_base4 = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_base4->obj->toWorld = Mid_base4->obj->toWorld * MS351 * MR351;
	Mid_front = new Geometry("../../OBJFiles/body.obj", regID);
	Mid_front->obj->toWorld = Mid_front->obj->toWorld * MS352 * MT35 * MR352;
	rule35->addChild(Mid_base4);
	rule35->addChild(Mid_front);

	//***********************************************************************



	testbuild->addChild(rule33);
}



// GENERATE STRUCTURES
void build_structure(Structure * building, glm::vec3 accum, int win_type) {
	int r, r2;
	int test;
	int full = 0;
	Transform * tmp;
	Structure * newBuilding;
	std::vector<int>* rules = new std::vector<int>();
	//******************************************
	if (win_type == 1) {
		rules->push_back(11);
	}
	else if (win_type == 2) {
		rules->push_back(12);
	}
	else {
		rules->push_back(13);
	}
	//*****************************************
	while (!rules->empty() && full < 10) {
		r = rules->back();
		rules->pop_back();
		full++;
		switch (r) {
		case(11): {
			tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
			tmp->addChild(rule11);
			building->addChild(tmp);
			accum.y += 25;
			test = rand() % 2 + 31; //MID
			rules->push_back(test);
			break;
		}
				  //*************************************
		case(12): {
			tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
			tmp->addChild(rule12);
			building->addChild(tmp);
			accum.y += 25;
			test = rand() % 2 + 31; //MID
			rules->push_back(test);
			break;
		}
		case(13): {
			tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
			tmp->addChild(rule13);
			building->addChild(tmp);
			accum.y += 25;
			test = rand() % 2 + 31; //MID
			rules->push_back(test);
			break;
		}
				  //********************************************
		case(21): {
			tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
			tmp->addChild(rule21);
			building->addChild(tmp);
			break;
		}
		case(22): {
			tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
			tmp->addChild(rule22);
			building->addChild(tmp);
			break;
		}
		case(23): {
			tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
			tmp->addChild(rule23);
			building->addChild(tmp);
			accum.y += 30;
			test = rand() % 2 + 31; //MID
			rules->push_back(test);
			break;
		}
		case(31): {
			tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
			tmp->addChild(rule31);
			building->addChild(tmp);
			accum.y += 2;
			test = rand() % 3 + 21; //TOP
			rules->push_back(test);
			break;
		}
				  //***********
		case(32): {
			r2 = rand() % 4 + 32;

			switch (r2) {
				//***********
			case(32): {
				tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
				tmp->addChild(rule32);
				building->addChild(tmp);
				newBuilding = new Structure(glm::translate(glm::mat4(1.0f), glm::vec3(building->MT[3][0] + accum.x - 80, building->MT[3][1] + (accum.y), building->MT[3][2] + accum.z)));
				structures.push_back(newBuilding);
				build_structure(newBuilding, glm::vec3(0, 0, 0), win_type);
				accum.y += 20;
				test = rand() % 3 + 21; //TOP
				rules->push_back(test);
				break;
			}
			case(33): {
				tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
				tmp->addChild(rule33);
				building->addChild(tmp);
				newBuilding = new Structure(glm::translate(glm::mat4(1.0f), glm::vec3(building->MT[3][0] + accum.x + 80, building->MT[3][1] + (accum.y), building->MT[3][2] + accum.z)));
				structures.push_back(newBuilding);
				build_structure(newBuilding, glm::vec3(0, 0, 0), win_type);
				accum.y += 20;
				test = rand() % 3 + 21; //TOP
				rules->push_back(test);
				break;
			}
					  //***********************************************************************
			case(34): {
				tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
				tmp->addChild(rule34);
				building->addChild(tmp);
				newBuilding = new Structure(glm::translate(glm::mat4(1.0f), glm::vec3(building->MT[3][0] + accum.x, building->MT[3][1] + (accum.y), building->MT[3][2] + accum.z + 80)));
				structures.push_back(newBuilding);
				build_structure(newBuilding, glm::vec3(0, 0, 0), win_type);
				accum.y += 20;
				test = rand() % 3 + 21; //TOP
				rules->push_back(test);
				break;
			}
			case(35): {
				tmp = new Transform(glm::translate(glm::mat4(1.0f), accum));
				tmp->addChild(rule35);
				building->addChild(tmp);
				newBuilding = new Structure(glm::translate(glm::mat4(1.0f), glm::vec3(building->MT[3][0] + accum.x, building->MT[3][1] + (accum.y), building->MT[3][2] + accum.z - 80)));
				structures.push_back(newBuilding);
				build_structure(newBuilding, glm::vec3(0, 0, 0), win_type);
				accum.y += 20;
				test = rand() % 3 + 21; //TOP
				rules->push_back(test);
				break;
			}
					  //***********************************************************************

			}
		}
		}

	}
}



void rebuild() {

	srand(seed);

	structures.clear();

	building1 = new Structure(glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, 100))));
	building2 = new Structure(glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, -100))));
	building3 = new Structure(glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 100))));
	building4 = new Structure(glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, -100))));
	build_structure(building1, glm::vec3(0, 0, 0), 1);
	build_structure(building2, glm::vec3(0, 0, 0), 2);
	build_structure(building3, glm::vec3(0, 0, 0), 3);
	build_structure(building4, glm::vec3(0, 0, 0), 3);
	structures.push_back(building1);
	structures.push_back(building2);
	structures.push_back(building3);
	structures.push_back(building4);
}








void Window::initialize_objects()
{


	init_audio();



	// Load the shader programs
	regID = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);

	skyboxID = LoadShaders(SKY_VERTEX_SHADER_PATH, SKY_FRAGMENT_SHADER_PATH);

	selectionID = LoadShaders(SELECTION_VERTEX_SHADER_PATH, SELECTION_FRAGMENT_SHADER_PATH);

	envID = LoadShaders(ENVIRONMENT_VERTEX_SHADER_PATH, ENVIRONMENT_FRAGMENT_SHADER_PATH);

	shadowID = LoadShaders(SHADOW_VERTEX_SHADER_PATH, SHADOW_FRAGMENT_SHADER_PATH);

	bufferID = LoadShaders(BUFFER_VERTEX_SHADER_PATH, BUFFER_FRAGMENT_SHADER_PATH);

	basicID = LoadShaders(BASIC_VERTEX_SHADER_PATH, BASIC_FRAGMENT_SHADER_PATH);



	generate_grammars();


	building1 = new Structure(glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, 100))));
	building2 = new Structure(glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, -100))));
	building3 = new Structure(glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 100))));
	building4 = new Structure(glm::mat4(glm::translate(glm::mat4(1.0f), glm::vec3(100, 0, -100))));




	build_structure(building1, glm::vec3(0, 0, 0), 1);
	build_structure(building2, glm::vec3(0, 0, 0), 2);
	build_structure(building3, glm::vec3(0, 0, 0), 3);
	build_structure(building4, glm::vec3(0, 0, 0), 3);
	structures.push_back(building1);
	structures.push_back(building2);
	structures.push_back(building3);
	structures.push_back(building4);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);




	Geometry1 * floor = new Geometry1("../../head.obj", 0, 1);
	floor->tag = "floor";
	floor->toon = 0;
	glm::mat4 floorInitial = glm::translate(glm::mat4(1.0f), { 0.0f, -100.0f, 0.0f });
	glm::mat4 floorScale = glm::scale(glm::mat4(1.0f), { 200.0f, 200.0f, 200.0f });
	glm::mat4 floorRot = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));

	floor->initial = floorInitial*floorScale* floorRot  *floor->initial;


	Geometry1 * s1 = new Geometry1("../../bunny.obj", 0, 1);
	s1->tag = "s1";
	s1->toon = 1;
	glm::mat4 s1Initial = glm::translate(glm::mat4(1.0f), { 0.0f, -10.0f, 0.0f });
	glm::mat4 s1Scale = glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 2.0f });

	s1->initial = s1Initial*s1Scale*s1->initial;

/*
	Geometry1 * s2 = new Geometry1("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Final Start/bunny.obj", 2, 0);
	s2->tag = "s2";
	s2->toon = 1;
	glm::mat4 s2Initial = glm::translate(glm::mat4(1.0f), { 2.5f, 2.0f, 0.0f });
	glm::mat4 s2Scale = glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 2.0f });

	s2->initial = s2Initial*s2Scale*s2->initial;
*/





	drone = new Drone("../../bunny.obj");
	drone->toon = 1;
	drone->tag = "drone";

	glm::mat4 droneInitial = glm::translate(glm::mat4(1.0f), droneStart);
	glm::mat4 droneScale = glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 2.0f });
	glm::mat4 droneRot = glm::rotate(glm::mat4(1.0f), 220.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

	drone->initial = droneScale*droneRot *drone->initial;
	drone->extra = droneInitial*drone->extra;
	drone->cPos = cam_pos;
	drone->cLook = cam_look_at;
	//drone->gunPos = { droneStart.x + .9, droneStart.y + 3, droneStart.z - 17 };


	shot = new Line(regID);

	camUpdate();

	



	Transform1* s1mtx = new Transform1(glm::mat4(1.0f));
	s1mtx->addChild(s1);
	//Transform1* s2mtx = new Transform1(glm::mat4(1.0f));
	//s2mtx->addChild(s2);
	Transform1* dronemtx = new Transform1(glm::mat4(1.0f));
	dronemtx->addChild(drone);
	Transform1* floormtx = new Transform1(glm::mat4(1.0f));
	floormtx->addChild(floor);

	modelmtx = new Transform1(glm::mat4(1.0f));
	modelmtx->addChild(s1mtx);
	//modelmtx->addChild(s2mtx);
	modelmtx->addChild(dronemtx);
	modelmtx->addChild(floormtx);

	Group1* objects = new Group1();
	objects->addChild(modelmtx);

	scene = objects;


	srand(5);


	makeBunnyCity(1);
	makeBunnyCity(2);
	makeBunnyCity(3);
	makeBunnyCity(4);




	//lights
	directional = new Light(1);
	cLight = directional;


	//skybox
	skybox = new SkyboxObject();

	faces = {
		"../../purplenebula_rt.jpg",
		"../../purplenebula_lf.jpg",
		"../../purplenebula_up.jpg",
		"../../purplenebula_dn.jpg",
		"../../purplenebula_bk.jpg",
		"../../purplenebula_ft.jpg"
	};

	cubemapTexture = loadCubemap(faces);







	//create texture map for shadow map

	const GLfloat g_quad_vertex_buffer_data[4][3] = {
		{ -1.0f, -1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0f },
		{ 1.0f,  1.0f, 0.0f },
		{ -1.0f,  1.0f, 0.0f }
	};
	

	const GLfloat g_quad_vertex_bufferTX_data[4][2] = {
		{0.0f, 0.0f},
		{1.0f, 0.0f },
		{1.0f, 1.0f},
		{0.0f,  1.0f}
	};

	const GLuint indices[1][6] = {

		{0,1,2,2,3,0}

	};

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

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// Enable the usage of layout location 0 (check the vertex shader to see what this is)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_bufferTX_data), g_quad_vertex_bufferTX_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	// We've sent the vertex data over to OpenGL, but there's still something missing.
	// In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind the VAO now so we don't accidentally tamper with it.
	// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
	glBindVertexArray(0);





	//ShadowMap


	// Get a handle for our "MVP" uniform
	depthMatrixID = glGetUniformLocation(shadowID, "depthMVP");


	// The framebuffer, which reGroup1s 0, 1, or more textures, and 0 or 1 depth buffer.
	Framebuffer = 0;
	glGenFramebuffers(1, &Framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);

	// Depth texture. Slower than a depth buffer, but you can sample it later in your shader
	//GLuint depthTexture;
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);


	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);


	glDrawBuffer(GL_NONE); // No color buffer is drawn to.

						   // Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {


		std::cerr << "BUFFER NOT RIGHT" << std::endl;

	}


	// Get a handle for our "myTextureSampler" uniform
	//TextureID = glGetUniformLocation(regID, "myTextureSampler");

	DepthBiasID = glGetUniformLocation(regID, "DepthBiasMVP");
	ShadowMapID = glGetUniformLocation(regID, "shadowMap");





	srand(5);

	//plants
	for (float i = -180.0; i < 180.0; i += 35.0)
	{
		if ((i > -1 * 20.0) && (i < 20.0)) continue;
		int x_val = rand() % 20;
		if (x_val > 10) x_val = -1 * (x_val / 2);
		locations.push_back(glm::vec3(x_val, 0.0f, i));

	}
	for (float i = -180.0; i < 180.0; i += 35.0)
	{
		if ((i > -1 * 20.0) && (i < 20.0)) continue;
		int z_val = rand() % 20;
		if (z_val > 10) z_val = -1 * (z_val / 2);
		locations.push_back(glm::vec3(i, 0.0f, z_val));

	}

	//generate trees
	for (int i = 0; i < locations.size(); i++)
	{
		int val = 1 + i % 3;
		//if(val == 2) val = 3;
		trees.push_back(new ProceduralPlants(val, i, locations[i]));
	}
	




	
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




void Window::makeBunnyCity(int cityNum) 
{

	int i, j;

	//bunny city
	for (i = 3; i < 8; i++) {

		for (j = 3; j < 8; j++) {

			if ((i == 1) && (j == 1)) {

				continue;

			}

			if ((i == 7) && (j == 7)) {

				continue;

			}

			if ((i % 2 == 0) || (j % 2 == 0)) {

				continue;

			}

			Geometry1 * b = new Geometry1("../../bunny.obj", cityNum, 0);
			b->tag = "b";
			b->toon = 1;

			int xWalk = rand() % 30;
			int zWalk = rand() % 30;

			if (xWalk >= 15) {

				xWalk = -(xWalk % 15);

			}

			if (zWalk >= 15) {

				zWalk = -(zWalk % 15);

			}

			//glm::mat4 bInitial = glm::translate(glm::mat4(1.0f), { (-6.0f * 5) + ((float)i*30.0f), 2.0f, (-6.0f * 5) + ((float)j*30.0f) });
			glm::mat4 bInitial = glm::translate(glm::mat4(1.0f), { ((float)i*20.0f) + xWalk, 2.0f, -((float)j*20.0f) + zWalk });
			glm::mat4 bScale = glm::scale(glm::mat4(1.0f), { 2.0f, 2.0f, 2.0f });

			float cityAngle = 90.0*(cityNum-1);

			glm::mat4 bCity = glm::rotate(glm::mat4(1.0f), cityAngle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

			float angle = rand() % 360;

			glm::mat4 bRot = glm::rotate(glm::mat4(1.0f), angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));

			b->initial = bCity*bInitial*bScale*bRot*b->initial;


			Transform1* bmtx = new Transform1(glm::mat4(1.0f));
			bmtx->addChild(b);

			modelmtx->addChild(bmtx);


		}


	}


}



// Delete dynamically allocated memory here.
void Window::clean_up()
{
	int i;

	for (i = 0; i < trees.size(); i++) {

		delete(trees[i]);

	}

	if (music)
		music->drop(); // release music stream.

	engine->drop(); // delete sound engine


	delete(directional);

	glDeleteProgram(regID);
	glDeleteProgram(skyboxID);
	glDeleteProgram(selectionID);
	glDeleteProgram(envID);
	glDeleteProgram(shadowID);
	glDeleteProgram(bufferID);
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

//update camera based on drone position
void Window::camUpdate() {

	glm::vec4 camTemp;

	camTemp = glm::vec4(drone->cPos, 1.0);
	camTemp = drone->extra * drone->R * camTemp;
	cam_pos = camTemp;

	camTemp = glm::vec4(drone->cLook, 1.0);
	camTemp = drone->extra * drone->R * camTemp;
	cam_look_at = camTemp;

	V = glm::lookAt(cam_pos, cam_look_at, cam_up);

	shot->aP1[0] = { 0,0,0 };
	shot->aP1[1] = { 0,0,0 };

}


void Window::display_callback(GLFWwindow* window)
{

	//prep first pass to framebuffer
	prepFirstPass();


	//first pass
	scene->update(1);
	scene->draw(glm::mat4(1.0f));

	firstPass = 1;
	//first pass buildings
	for (int i = 0; i < structures.size(); i++) {
		structures[i]->draw(glm::mat4(1.0f));
	}

	/*
	//generate trees
	for (int i = 0; i < trees.size(); i++)
	{
		trees[i]->draw(basicID, glm::vec3(0.0f, 0.0f, 0.0f), trees[i]->tree_string, cam_pos, 1);
	}
	*/




	prepSecondPass();




	//skybox
	glUseProgram(skyboxID);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	skybox->draw(skyboxID, cubemapTexture);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	
	


	// Use our shader
	glUseProgram(regID);

	cP = cam_pos;
	//second pass
	scene->update(2);
	scene->draw(glm::mat4(1.0f));



	firstPass = 0;

	//draw buildings
	for (int i = 0; i < structures.size(); i++) {
		structures[i]->draw(glm::mat4(1.0f));
	}





	shot->draw();


	glUseProgram(basicID);


	//generate trees
	for (int i = 0; i < trees.size(); i++)
	{
		trees[i]->draw(basicID, glm::vec3(0.0f, 0.0f, 0.0f), trees[i]->tree_string, cam_pos, 2);
	}
	



	//particles
	if (objectShot && particlesOn) {

		int size_1 = test_system.render_particles(shotPos, cam_pos, basicID, 0);
		int size_2 = test_system2.render_particles(shotPos, cam_pos, basicID, 1);
		//int size_3 = test_system3.render_particles(shotPos, cam_pos, basicID, 2);
		//int size_4 = test_system4.render_particles(shotPos, cam_pos, basicID, 3);
		//int size_5 = test_system5.render_particles(shotPos, cam_pos, basicID, 4);

		//if (!(size_1 || size_2 || size_3 || size_4 || size_5))
		if (!(size_1 || size_2))
		{

			std::cerr << "Objectshot RESET" << std::endl;
			objectShot = 0;
		}


	}

	







	if (shadowsOn) {

		if (shadowWindow) {

			drawShadowWindow();

		}

	}
	


	// Swap buffers
	glfwSwapBuffers(window);
	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();



}





void Window::prepFirstPass()
{

	// Render to our framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);
	glViewport(0, 0, 1024, 1024); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

						 // Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	glUseProgram(regID);
	//glUseProgram(shadowID);

	glm::vec3 lightInvDir = -cLight->direction;

	float boxSize = 210.0f; //30

	//must contain all objects
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-boxSize, boxSize, -boxSize, boxSize, -boxSize, boxSize);

	glm::vec3 up = glm::cross(lightInvDir, glm::vec3(0, 0, 1));

	if (up == glm::vec3(0, 0, 0)) {

		up = glm::cross(lightInvDir, glm::vec3(0, 1, 0));

	}

	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), up);


	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	depthMVP = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

	// Send our Transform1ation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(depthMatrixID, 1, GL_FALSE, &depthMVP[0][0]);


}

void Window::prepSecondPass()
{

	// Render to the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height); // Render on the whole framebuffer, complete from the lower left corner to the upper right

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

						 // Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

void Window::drawShadowWindow()
{


	glViewport(0, 0, 128, 128);

	//draw quad
	glUseProgram(bufferID);

	GLint texLoc = glGetUniformLocation(bufferID, "renderedTexture");
	glUniform1i(texLoc, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, depthTexture);

	glBindVertexArray(VAO);
	// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
	glBindVertexArray(0);



}





void Window::textPrint(int x, int y, int z, char *string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);
	//get the length of the string to display
	int len = (int)strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str ing[i]);
		//glutBitmapCharacter()
		//glm:
	}
};







//scroll
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{




}




//get mouse input
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {

		double currX;
		double currY;

		//get cursor position(x,y)
		glfwGetCursorPos(window, &currX, &currY);

		// Clear the color and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//use a selection buffer to indicate what part of the scene is being selected
		//the rest
		glUseProgram(selectionID);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		sbuffOn = 1;
		scene->draw(glm::mat4(1.0f));
		sbuffOn = 0;

		//get color at currX, currY
		glReadPixels((GLint)currX, (GLint)(height - currY), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pix);

		val = ((unsigned int)pix[0]);

		//if we chose an object
		if (val != 0) {

			selected = sbuff[val - 1];

			if (selected->tag == "floor") {


			}
			else {

				if (selected) {

					std::cerr << selected->tag << " Shot!" << std::endl;

					glm::vec4 gunPos = drone->extra * glm::vec4(drone->gunPos, 1.0);

					glm::vec4 targetPos = selected->extra * selected->initial * glm::vec4(selected->center, 1.0);


					if (selected->beenShot == 0) {

						selected->beenShot = 1;

						shot->aP1[0] = glm::vec3(gunPos.x, gunPos.y, gunPos.z);
						shot->aP1[1] = glm::vec3(targetPos.x, targetPos.y, targetPos.z);

						shotPos = glm::vec3(targetPos.x, targetPos.y, targetPos.z);

						test_system.initialize_points(shotPos);
						test_system2.initialize_points(shotPos);
						test_system3.initialize_points(shotPos);
						test_system4.initialize_points(shotPos);
						test_system5.initialize_points(shotPos);

						//make sun come closer to setting
						//cLight->direction = {cLight->direction.x - .02,cLight->direction.y + .02,cLight->direction.z};

						cLight->direction = { cLight->direction.x - .04,cLight->direction.y + .04,cLight->direction.z };


						//make bunny fall over
						selected->initial = selected->initial * glm::rotate(glm::mat4(1.0f), -90 / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
						selected->extra = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, 0.0f)) * selected->extra;


						if (soundOn) {


							int song = rand() % 3;

							//play shot
							if (song == 0) {

								engine->play3D("../../sounds/shot1.wav", vec3df(0, 0, 0));

							}
							else if (song == 1) {

								engine->play3D("../../sounds/shot2.wav", vec3df(0, 0, 0));

							}
							else if (song == 2) {

								engine->play3D("../../sounds/shot3.wav", vec3df(0, 0, 0));

							}




							song = rand() % 4;

							//play scream
							if (song == 0) {

								engine->play3D("../../sounds/scream1.wav", vec3df(0, 0, 0));

							}
							else if (song == 1) {

								engine->play3D("../../sounds/scream2.wav", vec3df(0, 0, 0));

							}
							else if (song == 2) {

								engine->play3D("../../sounds/scream3.wav", vec3df(0, 0, 0));

							}
							else if (song == 3) {

								engine->play3D("../../sounds/scream4.wav", vec3df(0, 0, 0));

							}


						}






						objectShot = 1;

					}


					

				}
				else {

					std::cerr << "ERROR Invalid Index" << std::endl;

				}

			}

		//background selected
		}
		else {

			std::cerr << "Background Selected" << std::endl;

		}



	}


}

//get cursor position
void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{


}



void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	// Check for a key release
	if (action == GLFW_REPEAT)
	{



		// w = move up
		if (key == GLFW_KEY_W)
		{

			drone->up();

			camUpdate();

		}

		// s = move down
		if (key == GLFW_KEY_S)
		{
			drone->down();

			camUpdate();

		}

		// d = rotate right
		if (key == GLFW_KEY_D)
		{
			drone->rotR();

			camUpdate();

		}

		// a = rotate left
		if (key == GLFW_KEY_A)
		{
			drone->rotL();

			camUpdate();

		}

		// w = move forward
		if (key == GLFW_KEY_UP)
		{

			forward = normalize(cam_look_at - cam_pos);

			float size = 5;

			forward = { size*forward.x,size*forward.y,size*forward.z };

			drone->forward();

			camUpdate();

		}

		// w = move backward
		if (key == GLFW_KEY_DOWN)
		{

			forward = normalize(cam_look_at - cam_pos);

			float size = 5;

			forward = { size*forward.x,size*forward.y,size*forward.z };

			drone->backward();

			camUpdate();

		}

		// w = move right
		if (key == GLFW_KEY_RIGHT)
		{

			forward = normalize(cam_look_at - cam_pos);

			right = cross(forward, cam_up);

			float size = 5;

			right = { size*right.x,size*right.y,size*right.z };

			drone->right();

			camUpdate();

		}

		// w = move left
		if (key == GLFW_KEY_LEFT)
		{

			forward = normalize(cam_look_at - cam_pos);

			right = cross(forward, cam_up);

			float size = 5;

			right = { size*right.x,size*right.y,size*right.z };

			drone->left();

			camUpdate();

		}



	}












	// Check for a key press
	if (action == GLFW_PRESS)
	{

		//increase the random number generator seed
		if (key == GLFW_KEY_P)
		{
			/*test_tree->seed++;
			tree_1->seed++;
			tree_2->seed++;
			tree_3->seed++;*/

			for (int i = 0; i < trees.size(); i++)
			{
				trees[i]->seed++;
				trees[i]->clear_leaves_and_branches();
				trees[i]->fill_leaves_and_branches = 1;
			}
		}
		//decrease the random number generator seed
		if (key == GLFW_KEY_L)
		{

			for (int i = 0; i < trees.size(); i++)
			{
				trees[i]->seed--;
				trees[i]->clear_leaves_and_branches();
				trees[i]->fill_leaves_and_branches = 1;
			}

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
				normalColoring = 0;
			}
			else {
				normalColoring = 1;
			}
		}


		// m = toggle particles
		if (key == GLFW_KEY_M)
		{
			if (particlesOn) {
				particlesOn = 0;
			}
			else {
				particlesOn = 1;
			}
		}

		// b = toggle sound
		if (key == GLFW_KEY_B)
		{
			if (soundOn) {
				soundOn = 0;
			}
			else {
				soundOn = 1;
			}
		}


		// i building stuff
		if (key == GLFW_KEY_I)
		{
			seed++;
			rebuild();
		}


		// 0 = toggle shadows
		if (key == GLFW_KEY_0)
		{
			if (shadowsOn) {
				shadowsOn = 0;
			}
			else {
				shadowsOn = 1;
			}
		}


		// 9 = toggle shadowWindow
		if (key == GLFW_KEY_9)
		{
			if (shadowWindow) {
				shadowWindow = 0;
			}
			else {
				shadowWindow = 1;
			}
		}


		// change light direction
		if (key == GLFW_KEY_1)
		{
			cLight->direction = {1.0f,0.0f,0.0f};
		}
		// change light direction
		if (key == GLFW_KEY_2)
		{
			cLight->direction = { -1.0f,0.0f,0.0f };
		}
		// change light direction
		if (key == GLFW_KEY_3)
		{
			cLight->direction = { 0.0f,1.0f,0.0f };
		}
		// change light direction
		if (key == GLFW_KEY_4)
		{
			cLight->direction = { 0.0f,-1.0f,0.0f };
		}
		// change light direction
		if (key == GLFW_KEY_5)
		{
			cLight->direction = { 0.0f,0.0f,1.0f };
		}
		// change light direction
		if (key == GLFW_KEY_6)
		{
			cLight->direction = { 0.0f,0.0f,-1.0f };
		}


		

		// w = move up
		if (key == GLFW_KEY_W)
		{

			drone->up();

			camUpdate();

		}

		// s = move down
		if (key == GLFW_KEY_S)
		{
			drone->down();

			camUpdate();

		}

		// d = rotate right
		if (key == GLFW_KEY_D)
		{
			drone->rotR();

			camUpdate();

		}

		// a = rotate left
		if (key == GLFW_KEY_A)
		{
			drone->rotL();

			camUpdate();

		}

		// w = move forward
		if (key == GLFW_KEY_UP)
		{

			forward = normalize(cam_look_at - cam_pos);

			float size = 5;

			forward = { size*forward.x,size*forward.y,size*forward.z };

			drone->forward();

			camUpdate();

		}

		// w = move backward
		if (key == GLFW_KEY_DOWN)
		{

			forward = normalize(cam_look_at - cam_pos);

			float size = 5;

			forward = { size*forward.x,size*forward.y,size*forward.z };

			drone->backward();

			camUpdate();

		}

		// w = move right
		if (key == GLFW_KEY_RIGHT)
		{

			forward = normalize(cam_look_at - cam_pos);

			right = cross(forward, cam_up);

			float size = 5;

			right = { size*right.x,size*right.y,size*right.z };

			drone->right();

			camUpdate();

		}

		// w = move left
		if (key == GLFW_KEY_LEFT)
		{

			forward = normalize(cam_look_at - cam_pos);

			right = cross(forward, cam_up);

			float size = 5;

			right = { size*right.x,size*right.y,size*right.z };

			drone->left();

			camUpdate();

		}

		


		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}




}
