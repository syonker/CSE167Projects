#include "Curve.h"
#include "Window.h"
#include "math.h"


Curve::Curve(GLuint shaderProgram, GLuint selectionshaderProgram, GLuint envshaderProgram)
{
	int j;
	glm::vec4 four;

	glm::vec3 center;

	glm::vec3 c0;
	glm::vec3 c1(20, 20, 0);
	glm::vec3 c2(40, 20, 0);
	glm::vec3 c3;
	glm::vec3 c4(80, -20, 0);
	glm::vec3 c5(100, -20, 0);
	glm::vec3 c6;
	glm::vec3 c7(140, -20, 0);
	glm::vec3 c8(140, -40, 0);
	glm::vec3 c9;
	glm::vec3 c10(100, -80, 0);
	glm::vec3 c11(100, -100, 0);
	glm::vec3 c12;
	glm::vec3 c13(100, -140, 0);
	glm::vec3 c14(80, -140, 0);
	glm::vec3 c15;
	glm::vec3 c16(40, -100, 0);
	glm::vec3 c17(20, -100, 0);
	glm::vec3 c18;
	glm::vec3 c19(-20, -100, 0);
	glm::vec3 c20(-20, -80, 0);
	glm::vec3 c21;
	glm::vec3 c22(20, -40, 0);
	glm::vec3 c23(20, -20, 0);


	c3 = (c4 + c2)*(0.5f);
	c6 = (c7 + c5)*(0.5f);
	c9 = (c10 + c8)*(0.5f);
	c12 = (c13 + c11)*(0.5f);
	c15 = (c16 + c14)*(0.5f);
	c18 = (c19 + c17)*(0.5f);
	c21 = (c22 + c20)*(0.5f);
	c0 = (c1 + c23)*(0.5f);


	//center = (c0 + c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9 + c10 + c11 + c12 + c13 + c14 + c15 + c16 + c17 + c18 + c19 + c20 + c21 + c22 + c23)*(1.0f/23.0f);

	//std::cerr << center.x << "   " << center.y << "   " << center.z << std::endl;

	bufferStuff = 1;

	shader = shaderProgram;


	for (j = 0; j < ((150 * numCurves)+1); j++) {

		indices.push_back(j);
		allPoints.push_back({0.0f,0.0f,0.0f});

	}

	aP1.push_back({0.0f,0.0f,0.0f});
	aP1.push_back({ 0.0f,0.0f,0.0f });
	aP2.push_back({ 0.0f,0.0f,0.0f });
	aP2.push_back({ 0.0f,0.0f,0.0f });
	aP3.push_back({ 0.0f,0.0f,0.0f });
	aP3.push_back({ 0.0f,0.0f,0.0f });
	aP4.push_back({ 0.0f,0.0f,0.0f });
	aP4.push_back({ 0.0f,0.0f,0.0f });
	aP5.push_back({ 0.0f,0.0f,0.0f });
	aP5.push_back({ 0.0f,0.0f,0.0f });
	aP6.push_back({ 0.0f,0.0f,0.0f });
	aP6.push_back({ 0.0f,0.0f,0.0f });
	aP7.push_back({ 0.0f,0.0f,0.0f });
	aP7.push_back({ 0.0f,0.0f,0.0f });
	aP8.push_back({ 0.0f,0.0f,0.0f });
	aP8.push_back({ 0.0f,0.0f,0.0f });

	//diffuse
	kd = { 0.07568f, 0.61424f, 0.07568f };

	//specular
	ks = { 0.633f, 0.727811f, 0.633f };

	//ambient
	ka = { 0.0215f, 0.1745f, 0.0215f };

	//shinyness
	pp = 0.6f;

	/*

	//populate p
	Geometry * p0 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram);
	p0->tag = "p0";
	glm::mat4 p0Initial = glm::translate(glm::mat4(1.0f), { -100.0f, -2.0f, 0.0f });

	cPoints.push_back({ -100.0f, -2.0f, 0.0f });

	Geometry * p1 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram);
	p1->tag = "p1";
	glm::mat4 p1Initial = glm::translate(glm::mat4(1.0f), { -80.0f, -2.0f, 20.0f });

	cPoints.push_back({ -80.0f, -2.0f, 20.0f });

	Geometry * p2 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram);
	p2->tag = "p2";
	glm::mat4 p2Initial = glm::translate(glm::mat4(1.0f), { -60.0f, -2.0f, 40.0f });

	cPoints.push_back({ -60.0f, -2.0f, 40.0f });

	Geometry * p3 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram);
	p3->tag = "p3";
	glm::mat4 p3Initial = glm::translate(glm::mat4(1.0f), { -40.0f, -2.0f, 60.0f });

	cPoints.push_back({ -40.0f, -2.0f, 60.0f });

	Geometry * p4 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram);
	p4->tag = "p4";
	glm::mat4 p4Initial = glm::translate(glm::mat4(1.0f), { -20.0f, -2.0f, 80.0f });

	cPoints.push_back({ -20.0f, -2.0f, 80.0f });

	Geometry * p5 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram);
	p5->tag = "p5";
	glm::mat4 p5Initial = glm::translate(glm::mat4(1.0f), { 0.0f, -2.0f, 100.0f });

	cPoints.push_back({ 0.0f, -2.0f, 100.0f });

	Geometry * p6 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram);
	p6->tag = "p6";
	glm::mat4 p6Initial = glm::translate(glm::mat4(1.0f), { 20.0f, -2.0f, 80.0f });

	cPoints.push_back({ 20.0f, -2.0f, 80.0f });

	Geometry * p7 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram);
	p7->tag = "p7";
	glm::mat4 p7Initial = glm::translate(glm::mat4(1.0f), { 40.0f, -2.0f, 60.0f });

	cPoints.push_back({ 40.0f, -2.0f, 60.0f });

	*/


	highestZ = -10000.0f;
	highestT = 0.0f;

	//populate p
	Geometry * p0 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 0);
	p0->tag = "p0";
	p0->interp = 1;
	glm::mat4 p0Initial = glm::translate(glm::mat4(1.0f), c0);


	Geometry * p1 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p1->tag = "p1";
	p1->interp = 0;
	glm::mat4 p1Initial = glm::translate(glm::mat4(1.0f), c1);


	Geometry * p2 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p2->tag = "p2";
	p2->interp = 0;
	glm::mat4 p2Initial = glm::translate(glm::mat4(1.0f), c2);


	Geometry * p3 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 0);
	p3->tag = "p3";
	p3->interp = 1;
	glm::mat4 p3Initial = glm::translate(glm::mat4(1.0f), c3);


	Geometry * p4 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p4->tag = "p4";
	p4->interp = 0;
	glm::mat4 p4Initial = glm::translate(glm::mat4(1.0f), c4);


	Geometry * p5 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p5->tag = "p5";
	p5->interp = 0;
	glm::mat4 p5Initial = glm::translate(glm::mat4(1.0f), c5);


	Geometry * p6 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 0);
	p6->tag = "p6";
	p6->interp = 1;
	glm::mat4 p6Initial = glm::translate(glm::mat4(1.0f), c6);


	Geometry * p7 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p7->tag = "p7";
	p7->interp = 0;
	glm::mat4 p7Initial = glm::translate(glm::mat4(1.0f), c7);


	Geometry * p8 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p8->tag = "p8";
	p8->interp = 0;
	glm::mat4 p8Initial = glm::translate(glm::mat4(1.0f), c8);


	Geometry * p9 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 0);
	p9->tag = "p9";
	p9->interp = 1;
	glm::mat4 p9Initial = glm::translate(glm::mat4(1.0f), c9);


	Geometry * p10 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p10->tag = "p10";
	p10->interp = 0;
	glm::mat4 p10Initial = glm::translate(glm::mat4(1.0f), c10);


	Geometry * p11 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p11->tag = "p11";
	p11->interp = 0;
	glm::mat4 p11Initial = glm::translate(glm::mat4(1.0f), c11);


	Geometry * p12 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 0);
	p12->tag = "p12";
	p12->interp = 1;
	glm::mat4 p12Initial = glm::translate(glm::mat4(1.0f), c12);


	Geometry * p13 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p13->tag = "p13";
	p13->interp = 0;
	glm::mat4 p13Initial = glm::translate(glm::mat4(1.0f), c13);


	Geometry * p14 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p14->tag = "p14";
	p14->interp = 0;
	glm::mat4 p14Initial = glm::translate(glm::mat4(1.0f), c14);


	Geometry * p15 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 0);
	p15->tag = "p15";
	p15->interp = 1;
	glm::mat4 p15Initial = glm::translate(glm::mat4(1.0f), c15);


	Geometry * p16 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p16->tag = "p16";
	p16->interp = 0;
	glm::mat4 p16Initial = glm::translate(glm::mat4(1.0f), c16);


	Geometry * p17 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p17->tag = "p17";
	p17->interp = 0;
	glm::mat4 p17Initial = glm::translate(glm::mat4(1.0f), c17);


	Geometry * p18 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 0);
	p18->tag = "p18";
	p18->interp = 1;
	glm::mat4 p18Initial = glm::translate(glm::mat4(1.0f), c18);


	Geometry * p19 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p19->tag = "p19";
	p19->interp = 0;
	glm::mat4 p19Initial = glm::translate(glm::mat4(1.0f), c19);


	Geometry * p20 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p20->tag = "p20";
	p20->interp = 0;
	glm::mat4 p20Initial = glm::translate(glm::mat4(1.0f), c20);


	Geometry * p21 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 0);
	p21->tag = "p21";
	p21->interp = 1;
	glm::mat4 p21Initial = glm::translate(glm::mat4(1.0f), c21);


	Geometry * p22 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p22->tag = "p22";
	p22->interp = 0;
	glm::mat4 p22Initial = glm::translate(glm::mat4(1.0f), c22);


	Geometry * p23 = new Geometry("C:/Users/sbyon_000/Desktop/SCHOOL BS/CSE 167 (B00)/Project 4/sphere.obj", shaderProgram, selectionshaderProgram, envshaderProgram, 1);
	p23->tag = "p23";
	p23->interp = 0;
	glm::mat4 p23Initial = glm::translate(glm::mat4(1.0f), c23);




	//add to our vector so we can traverse it
	p.push_back(p0);
	p.push_back(p1);
	p.push_back(p2);
	p.push_back(p3);
	p.push_back(p4);
	p.push_back(p5);
	p.push_back(p6);
	p.push_back(p7);
	p.push_back(p8);
	p.push_back(p9);
	p.push_back(p10);
	p.push_back(p11);
	p.push_back(p12);
	p.push_back(p13);
	p.push_back(p14);
	p.push_back(p15);
	p.push_back(p16);
	p.push_back(p17);
	p.push_back(p18);
	p.push_back(p19);
	p.push_back(p20);
	p.push_back(p21);
	p.push_back(p22);
	p.push_back(p23);

	//lines
	aP1[0] = p[2]->center;
	aP1[1] = p[4]->center;
	aP2[0] = p[5]->center;
	aP2[1] = p[7]->center;
	aP3[0] = p[8]->center;
	aP3[1] = p[10]->center;
	aP4[0] = p[11]->center;
	aP4[1] = p[13]->center;
	aP5[0] = p[14]->center;
	aP5[1] = p[16]->center;
	aP6[0] = p[17]->center;
	aP6[1] = p[19]->center;
	aP7[0] = p[20]->center;
	aP7[1] = p[22]->center;
	aP8[0] = p[23]->center;
	aP8[1] = p[1]->center;

	p0->initial = p0Initial * p0->initial;
	p1->initial = p1Initial * p1->initial;
	p2->initial = p2Initial * p2->initial;
	p3->initial = p3Initial * p3->initial;
	p4->initial = p4Initial * p4->initial;
	p5->initial = p5Initial * p5->initial;
	p6->initial = p6Initial * p6->initial;
	p7->initial = p7Initial * p7->initial;
	p8->initial = p8Initial * p8->initial;
	p9->initial = p9Initial * p9->initial;
	p10->initial = p10Initial * p10->initial;
	p11->initial = p11Initial * p11->initial;
	p12->initial = p12Initial * p12->initial;
	p13->initial = p13Initial * p13->initial;
	p14->initial = p14Initial * p14->initial;
	p15->initial = p15Initial * p15->initial;
	p16->initial = p16Initial * p16->initial;
	p17->initial = p17Initial * p17->initial;
	p18->initial = p18Initial * p18->initial;
	p19->initial = p19Initial * p19->initial;
	p20->initial = p20Initial * p20->initial;
	p21->initial = p21Initial * p21->initial;
	p22->initial = p22Initial * p22->initial;
	p23->initial = p23Initial * p23->initial;

	//p0
	four = { (p0->center), 1.0f };
	four = p0Initial*four;
	p0->center = four;
	//p1
	four = { (p1->center), 1.0f };
	four = p1Initial*four;
	p1->center = four;
	//p2
	four = { (p2->center), 1.0f };
	four = p2Initial*four;
	p2->center = four;
	//p3
	four = { (p3->center), 1.0f };
	four = p3Initial*four;
	p3->center = four;
	//p4
	four = { (p4->center), 1.0f };
	four = p4Initial*four;
	p4->center = four;
	//p5
	four = { (p5->center), 1.0f };
	four = p5Initial*four;
	p5->center = four;
	//p6
	four = { (p6->center), 1.0f };
	four = p6Initial*four;
	p6->center = four;
	//p7
	four = { (p7->center), 1.0f };
	four = p7Initial*four;
	p7->center = four;
	//p8
	four = { (p8->center), 1.0f };
	four = p8Initial*four;
	p8->center = four;
	//p9
	four = { (p9->center), 1.0f };
	four = p9Initial*four;
	p9->center = four;
	//p10
	four = { (p10->center), 1.0f };
	four = p10Initial*four;
	p10->center = four;
	//p11
	four = { (p11->center), 1.0f };
	four = p11Initial*four;
	p11->center = four;
	//p12
	four = { (p12->center), 1.0f };
	four = p12Initial*four;
	p12->center = four;
	//p13
	four = { (p13->center), 1.0f };
	four = p13Initial*four;
	p13->center = four;
	//p14
	four = { (p14->center), 1.0f };
	four = p14Initial*four;
	p14->center = four;
	//p15
	four = { (p15->center), 1.0f };
	four = p15Initial*four;
	p15->center = four;
	//p16
	four = { (p16->center), 1.0f };
	four = p16Initial*four;
	p16->center = four;
	//p17
	four = { (p17->center), 1.0f };
	four = p17Initial*four;
	p17->center = four;
	//p18
	four = { (p18->center), 1.0f };
	four = p18Initial*four;
	p18->center = four;
	//p19
	four = { (p19->center), 1.0f };
	four = p19Initial*four;
	p19->center = four;
	//p20
	four = { (p20->center), 1.0f };
	four = p20Initial*four;
	p20->center = four;
	//p21
	four = { (p21->center), 1.0f };
	four = p21Initial*four;
	p21->center = four;
	//p22
	four = { (p22->center), 1.0f };
	four = p22Initial*four;
	p22->center = four;
	//p23
	four = { (p23->center), 1.0f };
	four = p23Initial*four;
	p23->center = four;



	/*
	//p0
	four = {(p0->center).x,(p0->center).y, (p0->center).z, 1.0f};
	four = p0Initial*four;
	(p0->center).x = (four.x) / (four.w);
	(p0->center).y = (four.y) / (four.w);
	(p0->center).z = (four.z) / (four.w);
	//p1
	four = { (p1->center).x,(p1->center).y, (p1->center).z, 1.0f };
	four = p1Initial*four;
	(p1->center).x = (four.x) / (four.w);
	(p1->center).y = (four.y) / (four.w);
	(p1->center).z = (four.z) / (four.w);
	//p2
	four = { (p2->center).x,(p2->center).y, (p2->center).z, 1.0f };
	four = p2Initial*four;
	(p2->center).x = (four.x) / (four.w);
	(p2->center).y = (four.y) / (four.w);
	(p2->center).z = (four.z) / (four.w);
	//p3
	four = { (p3->center).x,(p3->center).y, (p3->center).z, 1.0f };
	four = p3Initial*four;
	(p3->center).x = (four.x) / (four.w);
	(p3->center).y = (four.y) / (four.w);
	(p3->center).z = (four.z) / (four.w);
	//p4
	four = { (p4->center).x,(p4->center).y, (p4->center).z, 1.0f };
	four = p4Initial*four;
	(p4->center).x = (four.x) / (four.w);
	(p4->center).y = (four.y) / (four.w);
	(p4->center).z = (four.z) / (four.w);
	//p5
	four = { (p5->center).x,(p5->center).y, (p5->center).z, 1.0f };
	four = p5Initial*four;
	(p5->center).x = (four.x) / (four.w);
	(p5->center).y = (four.y) / (four.w);
	(p5->center).z = (four.z) / (four.w);
	//p6
	four = { (p6->center).x,(p6->center).y, (p6->center).z, 1.0f };
	four = p6Initial*four;
	(p6->center).x = (four.x) / (four.w);
	(p6->center).y = (four.y) / (four.w);
	(p6->center).z = (four.z) / (four.w);
	//p7
	four = { (p7->center).x,(p7->center).y, (p7->center).z, 1.0f };
	four = p7Initial*four;
	(p7->center).x = (four.x) / (four.w);
	(p7->center).y = (four.y) / (four.w);
	(p7->center).z = (four.z) / (four.w);
	*/

	/*
	Transform* p0mtx = new Transform(p0Initial);
	Transform* p1mtx = new Transform(p1Initial);
	Transform* p2mtx = new Transform(p2Initial);
	Transform* p3mtx = new Transform(p3Initial);
	Transform* p4mtx = new Transform(p4Initial);
	Transform* p5mtx = new Transform(p5Initial);
	Transform* p6mtx = new Transform(p6Initial);
	Transform* p7mtx = new Transform(p7Initial);
	*/

	Transform* p0mtx = new Transform(glm::mat4(1.0f));
	Transform* p1mtx = new Transform(glm::mat4(1.0f));
	Transform* p2mtx = new Transform(glm::mat4(1.0f));
	Transform* p3mtx = new Transform(glm::mat4(1.0f));
	Transform* p4mtx = new Transform(glm::mat4(1.0f));
	Transform* p5mtx = new Transform(glm::mat4(1.0f));
	Transform* p6mtx = new Transform(glm::mat4(1.0f));
	Transform* p7mtx = new Transform(glm::mat4(1.0f));
	Transform* p8mtx = new Transform(glm::mat4(1.0f));
	Transform* p9mtx = new Transform(glm::mat4(1.0f));
	Transform* p10mtx = new Transform(glm::mat4(1.0f));
	Transform* p11mtx = new Transform(glm::mat4(1.0f));
	Transform* p12mtx = new Transform(glm::mat4(1.0f));
	Transform* p13mtx = new Transform(glm::mat4(1.0f));
	Transform* p14mtx = new Transform(glm::mat4(1.0f));
	Transform* p15mtx = new Transform(glm::mat4(1.0f));
	Transform* p16mtx = new Transform(glm::mat4(1.0f));
	Transform* p17mtx = new Transform(glm::mat4(1.0f));
	Transform* p18mtx = new Transform(glm::mat4(1.0f));
	Transform* p19mtx = new Transform(glm::mat4(1.0f));
	Transform* p20mtx = new Transform(glm::mat4(1.0f));
	Transform* p21mtx = new Transform(glm::mat4(1.0f));
	Transform* p22mtx = new Transform(glm::mat4(1.0f));
	Transform* p23mtx = new Transform(glm::mat4(1.0f));

	p0mtx->addChild(p0);
	p1mtx->addChild(p1);
	p2mtx->addChild(p2);
	p3mtx->addChild(p3);
	p4mtx->addChild(p4);
	p5mtx->addChild(p5);
	p6mtx->addChild(p6);
	p7mtx->addChild(p7);
	p8mtx->addChild(p8);
	p9mtx->addChild(p9);
	p10mtx->addChild(p10);
	p11mtx->addChild(p11);
	p12mtx->addChild(p12);
	p13mtx->addChild(p13);
	p14mtx->addChild(p14);
	p15mtx->addChild(p15);
	p16mtx->addChild(p16);
	p17mtx->addChild(p17);
	p18mtx->addChild(p18);
	p19mtx->addChild(p19);
	p20mtx->addChild(p20);
	p21mtx->addChild(p21);
	p22mtx->addChild(p22);
	p23mtx->addChild(p23);

	Transform* modelmtx = new Transform(glm::mat4(1.0f));
	modelmtx->addChild(p0mtx);
	modelmtx->addChild(p1mtx);
	modelmtx->addChild(p2mtx);
	modelmtx->addChild(p3mtx);
	modelmtx->addChild(p4mtx);
	modelmtx->addChild(p5mtx);
	modelmtx->addChild(p6mtx);
	modelmtx->addChild(p7mtx);
	modelmtx->addChild(p8mtx);
	modelmtx->addChild(p9mtx);
	modelmtx->addChild(p10mtx);
	modelmtx->addChild(p11mtx);
	modelmtx->addChild(p12mtx);
	modelmtx->addChild(p13mtx);
	modelmtx->addChild(p14mtx);
	modelmtx->addChild(p15mtx);
	modelmtx->addChild(p16mtx);
	modelmtx->addChild(p17mtx);
	modelmtx->addChild(p18mtx);
	modelmtx->addChild(p19mtx);
	modelmtx->addChild(p20mtx);
	modelmtx->addChild(p21mtx);
	modelmtx->addChild(p22mtx);
	modelmtx->addChild(p23mtx);

	Group* objects = new Group();
	objects->addChild(modelmtx);

	spheres = objects;



	int pIndex;


	//NEED THIS
	//start the vertex count at 0
	//count = 0;
	
	//for (pIndex = 0; pIndex < (4*numCurves); pIndex += 4) {

	//	update(pIndex);

	//}
	


	if (bufferStuff == 1) {

		// Create array object and buffers. Remember to delete your buffers when the object is destroyed!
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
		// Consider the VAO as a container for all your buffers.
		glBindVertexArray(VAO);

		// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
		// you want to draw, such as vertices, normals, colors, etc.
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
		// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
		//glBufferData(GL_ARRAY_BUFFER, sizeof(allPoints), allPoints, GL_STATIC_DRAW);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*allPoints.size(), allPoints.data(), GL_STATIC_DRAW);





		// Enable the usage of layout location 0 (check the vertex shader to see what this is)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
			3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
			GL_FLOAT, // What type these components are
			GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
			3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
			(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);

		// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Unbind the VAO now so we don't accidentally tamper with it.
		// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
		glBindVertexArray(0);






		//lines

		//1
		glGenVertexArrays(1, &VAO1);
		glGenBuffers(1, &VBO1);

		glBindVertexArray(VAO1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP1.size(), aP1.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); 

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//2
		glGenVertexArrays(1, &VAO2);
		glGenBuffers(1, &VBO2);

		glBindVertexArray(VAO2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP2.size(), aP2.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//3
		glGenVertexArrays(1, &VAO3);
		glGenBuffers(1, &VBO3);

		glBindVertexArray(VAO3);
		glBindBuffer(GL_ARRAY_BUFFER, VBO3);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP3.size(), aP3.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//4
		glGenVertexArrays(1, &VAO4);
		glGenBuffers(1, &VBO4);

		glBindVertexArray(VAO4);
		glBindBuffer(GL_ARRAY_BUFFER, VBO4);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP4.size(), aP4.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//5
		glGenVertexArrays(1, &VAO5);
		glGenBuffers(1, &VBO5);

		glBindVertexArray(VAO5);
		glBindBuffer(GL_ARRAY_BUFFER, VBO5);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP5.size(), aP5.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//6
		glGenVertexArrays(1, &VAO6);
		glGenBuffers(1, &VBO6);

		glBindVertexArray(VAO6);
		glBindBuffer(GL_ARRAY_BUFFER, VBO6);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP6.size(), aP6.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//7
		glGenVertexArrays(1, &VAO7);
		glGenBuffers(1, &VBO7);

		glBindVertexArray(VAO7);
		glBindBuffer(GL_ARRAY_BUFFER, VBO7);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP7.size(), aP7.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//8
		glGenVertexArrays(1, &VAO8);
		glGenBuffers(1, &VBO8);

		glBindVertexArray(VAO8);
		glBindBuffer(GL_ARRAY_BUFFER, VBO8);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP8.size(), aP8.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);









	}

}

Curve::~Curve()
{
	// Delete previously generated buffers.
	
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	
}


void Curve::draw()
{
	

	int pIndex, i;

	//start the vertex count at 0
	count = 0;
	highestT = 0.0f;
	highestZ = -10000.0f;

	for (pIndex = 0; pIndex < ((4*numCurves)-numCurves); pIndex += 3) {

		update(pIndex);

	}

	

	//std::cerr << highestZ << std::endl;

	if (bufferStuff == 0) {

		glBegin(GL_LINE_STRIP);
		for (i = 0; i < ((150 * numCurves) + 1); i++) {

			glVertex3f((allPoints[i]).x, (allPoints[i]).y, (allPoints[i]).z);

		}
		glEnd();

	}
	else {




		// Calculate the combination of the model and view (camera inverse) matrices
		glm::mat4 modelview = Window::V;

		glUseProgram(shader);

		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		glUniform1i(glGetUniformLocation(shader, "light.normalColoring"), Window::normalColoring);

		//send over the camera position
		glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, &Window::view[0]);


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
		glUniform1f(glGetUniformLocation(shader, "p"), pp);


























		// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
		// Consider the VAO as a container for all your buffers.
		glBindVertexArray(VAO);

		// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
		// you want to draw, such as vertices, normals, colors, etc.
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
		// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
		//glBufferData(GL_ARRAY_BUFFER, sizeof(allPoints), allPoints, GL_STATIC_DRAW);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*allPoints.size(), allPoints.data(), GL_STATIC_DRAW);


		glBindBuffer(GL_ARRAY_BUFFER, 0);




		//third number is 150*number of curves in curve
		glDrawArrays(GL_LINE_STRIP, 0, allPoints.size());



		//glDrawElements(GL_LINE_STRIP, ((150 * numCurves)+1), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);



		//lines
		aP1[0] = p[2]->center;
		aP1[1] = p[4]->center;
		aP2[0] = p[5]->center;
		aP2[1] = p[7]->center;
		aP3[0] = p[8]->center;
		aP3[1] = p[10]->center;
		aP4[0] = p[11]->center;
		aP4[1] = p[13]->center;
		aP5[0] = p[14]->center;
		aP5[1] = p[16]->center;
		aP6[0] = p[17]->center;
		aP6[1] = p[19]->center;
		aP7[0] = p[20]->center;
		aP7[1] = p[22]->center;
		aP8[0] = p[23]->center;
		aP8[1] = p[1]->center;


		//lines

		//1
		glBindVertexArray(VAO1);
		glBindBuffer(GL_ARRAY_BUFFER, VBO1);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP1.size(), aP1.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP1.size());

		glBindVertexArray(0);

		//2
		glBindVertexArray(VAO2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP2.size(), aP2.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP2.size());

		glBindVertexArray(0);

		//3
		glBindVertexArray(VAO3);
		glBindBuffer(GL_ARRAY_BUFFER, VBO3);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP3.size(), aP3.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP3.size());

		glBindVertexArray(0);

		//4
		glBindVertexArray(VAO4);
		glBindBuffer(GL_ARRAY_BUFFER, VBO4);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP4.size(), aP4.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP4.size());

		glBindVertexArray(0);

		//5
		glBindVertexArray(VAO5);
		glBindBuffer(GL_ARRAY_BUFFER, VBO5);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP5.size(), aP5.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP5.size());

		glBindVertexArray(0);

		//6
		glBindVertexArray(VAO6);
		glBindBuffer(GL_ARRAY_BUFFER, VBO6);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP6.size(), aP6.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP6.size());

		glBindVertexArray(0);

		//7
		glBindVertexArray(VAO7);
		glBindBuffer(GL_ARRAY_BUFFER, VBO7);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP7.size(), aP7.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP7.size());

		glBindVertexArray(0);

		//8
		glBindVertexArray(VAO8);
		glBindBuffer(GL_ARRAY_BUFFER, VBO8);

		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*aP8.size(), aP8.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_LINE_STRIP, 0, aP8.size());

		glBindVertexArray(0);








	}
	


}

void Curve::update(int pStart) {

	//std::vector<glm::vec3> controlP(4);
	float t;
	glm::vec3 c0;
	glm::vec3 c1;
	glm::vec3 c2;
	glm::vec3 c3;

	int i;
	glm::vec3 q;
	glm::vec4 temp;
	glm::vec4 G;
	glm::mat4 B;
	glm::vec4 bigT;
	glm::vec4 test;

	//B = { {-1.0f, 3.0f, -3.0f, 1.0f}, 
	//	  {3.0f, -6.0f, 3.0f, 0.0f}, 
	//	  {-3.0f, 3.0f, 0.0f, 0.0f},
	//	  {1.0f, 0.0f, 0.0f, 0.0f} };

	B[0][0] = -1.0f;
	B[1][0] = 3.0f;
	B[2][0] = -3.0f;
	B[3][0] = 1.0f;

	B[0][1] = 3.0f;
	B[1][1] = -6.0f;
	B[2][1] = 3.0f;
	B[3][1] = 0.0f;

	B[0][2] = -3.0f;
	B[1][2] = 3.0f;
	B[2][2] = 0.0f;
	B[3][2] = 0.0f;

	B[0][3] = 1.0f;
	B[1][3] = 0.0f;
	B[2][3] = 0.0f;
	B[3][3] = 0.0f;



	//controlP.push_back({0.0f,0.0f,0.0f});
	//controlP.push_back({ 0.0f,0.0f,0.0f });
	//controlP.push_back({ 0.0f,0.0f,0.0f });
	//controlP.push_back({ 0.0f,0.0f,0.0f });
	
	/*
	//p0
	temp = { p[pStart]->center, 1.0f };
	controlP[0] = (p[pStart]->extra)*(p[pStart]->initial)*(temp);
	controlP[0] = controlP[0] / temp.w;
	//p1
	temp = { p[pStart+1]->center, 1.0f };
	controlP[1] = (p[pStart+1]->extra)*(p[pStart+1]->initial)*(temp);
	controlP[1] = controlP[1] / temp.w;
	//p2
	temp = { p[pStart+2]->center, 1.0f };
	controlP[2] = (p[pStart+2]->extra)*(p[pStart+2]->initial)*(temp);
	controlP[2] = controlP[2] / temp.w;
	//p3
	temp = { p[pStart+3]->center, 1.0f };
	controlP[3] = (p[pStart+3]->extra)*(p[pStart+3]->initial)*(temp);
	controlP[3] = controlP[3] / temp.w;
	*/

	/*
	//p0
	controlP[0] = p[pStart]->center;
	//p1
	controlP[1] = p[pStart + 1]->center;
	//p2
	controlP[2] = p[pStart + 2]->center;
	//p3
	controlP[3] = p[pStart + 3]->center;
	*/

	//p0
	c0 = p[pStart]->center;
	//p1
	c1 = p[pStart + 1]->center;
	//p2
	c2 = p[pStart + 2]->center;


	if ((pStart + 3) == 24) {

		//p3
		c3 = p[0]->center;

	}
	else {

		//p3
		c3 = p[pStart + 3]->center;

	}
	
	/*


	if (pStart == 0) {

		controlP[0] = cPoints[0];
		controlP[1] = cPoints[1];
		controlP[2] = cPoints[2];
		controlP[3] = cPoints[3];

	} else {

		controlP[0] = cPoints[4];
		controlP[1] = cPoints[5];
		controlP[2] = cPoints[6];
		controlP[3] = cPoints[7];

	}


	/*
	//p0
	temp = { p[pStart]->center, 1.0f };
	controlP[0] = (p[pStart]->extra)*(p[pStart]->initial)*(temp);
	controlP[0] = controlP[0];
	//p1
	temp = { p[pStart + 1]->center, 1.0f };
	controlP[1] = (p[pStart + 1]->extra)*(p[pStart + 1]->initial)*(temp);
	controlP[1] = controlP[1];
	//p2
	temp = { p[pStart + 2]->center, 1.0f };
	controlP[2] = (p[pStart + 2]->extra)*(p[pStart + 2]->initial)*(temp);
	controlP[2] = controlP[2];
	//p3
	temp = { p[pStart + 3]->center, 1.0f };
	controlP[3] = (p[pStart + 3]->extra)*(p[pStart + 3]->initial)*(temp);
	controlP[3] = controlP[3];
	*/
	

	for (t = 0.0f; t < 1.0f; t += (1.0f/150.0f)) {


		q = { 0.0f,0.0f,0.0f };
		
		/*
		bigT = { pow(t,3), pow(t,2), t, 1.0f};


		G = { controlP[pStart].x, controlP[pStart +1].x, controlP[pStart +2].x, controlP[pStart +3].x };
		test = (B*bigT);
		q.x = glm::dot(G,test);

		G = { controlP[pStart].y, controlP[pStart + 1].y, controlP[pStart + 2].y, controlP[pStart + 3].y };
		test = (B*bigT);
		q.y = glm::dot(G, test);

		G = { controlP[pStart].z, controlP[pStart + 1].z, controlP[pStart + 2].z, controlP[pStart + 3].z };
		test = (B*bigT);
		q.z = glm::dot(G, test);
		*/
		

		q += (bernstein(0, t)*c0);
		q += (bernstein(1, t)*c1);
		q += (bernstein(2, t)*c2);
		q += (bernstein(3, t)*c3);
		
		/*
		for (i = 0; i < 3; i++) {

			q += (bernstein(i, t)*controlP[i]);


		}
		*/
		
		

		/*
		if (t == 0.0f) {

			q = controlP[pStart];

		}

		if (t == 1.0f) {

			q = controlP[pStart+3];

		}
		*/
		
		
		//allPoints[count][0] = q.x;
		//allPoints[count][1] = q.y;
		//allPoints[count][2] = q.z;
		//count++;

		if (bufferStuff == 0) {

			allPoints[count] = q;

		}
		else {


			allPoints[count] = q;
			//allPoints[count][0] = q.x;
			//allPoints[count][1] = q.y;
			//allPoints[count][2] = q.z;

		}
		count++;

		if (q.z > highestZ) {

			highestZ = q.z;
			highestT = (t + (pStart/3));

		}
		

		

	}


}

//t between 0.0f and 8.0f
glm::vec3 Curve::getCarPos(float t) {

	//std::vector<glm::vec3> controlP(4);
	glm::vec3 c0;
	glm::vec3 c1;
	glm::vec3 c2;
	glm::vec3 c3;
	int i;
	glm::vec3 q;
	//glm::vec4 temp;

	//std::cerr << t << std::endl;

	//determine pStart to use given t
	int pStart = 3 * (int)floor(t);

	//std::cerr << pStart << std::endl;

	//p0
	c0 = p[pStart]->center;
	//p1
	c1 = p[pStart + 1]->center;
	//p2
	c2 = p[pStart + 2]->center;


	if ((pStart + 3) == 24) {

		//p3
		c3 = p[0]->center;

	}
	else {

		//p3
		c3 = p[pStart + 3]->center;

	}


	q = { 0.0f,0.0f,0.0f };

	q += (bernstein(0, (t - floor(t)))*c0);
	q += (bernstein(1, (t - floor(t)))*c1);
	q += (bernstein(2, (t - floor(t)))*c2);
	q += (bernstein(3, (t - floor(t)))*c3);


	//return the sum q that you get
	return q;

	//in Window.cpp use this position to place the roller coaster car 
	//maybe make a moveTo(vec3 newPos) function

}

float Curve::bernstein(int i, float t)
{
	std::vector<int> threeChoose = { 1,3,3,1 };

	return (threeChoose[i] * (pow(t, i))*(pow(1 - t, 3 - i)));

}