//
//  ParticleSystem.hpp
//  CSE_167_Final_Project
//
//  Created by Mackenzie Monroe on 12/10/17.
//  Copyright © 2017 Mackenzie Monroe. All rights reserved.
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>


#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

class Particle{
public:
    
    glm::vec3 pos, speed;
    unsigned char r,g,b,a; // Color
    float size, angle, weight;
    float life; // Remaining life of the particle. if < 0 : dead and unused.
    int diameter = 2; //range in which is position the particle
    glm::vec3 object_center; //center of the object around which to position the particle
    
    Particle(glm::vec3 object_center);
    ~Particle();
    
    float cameradistance;
    
};

class ParticleSystem{
public:
    std::vector<Particle > points;
    //float delta = 0.055f;
    
	float delta = 0.02f;
	int first_call  = 1;
    int iterations = 0;
    int num_points = 100;
    int point_size_range = 100;
    int iteraton_increment = 10;
    GLuint VAO, VBO, EBO;
	std::vector<glm::vec3> vertices;
    
    ~ParticleSystem();
    float compute_point_size(glm::vec3 CameraPosition);
    void initialize_points(glm::vec3 objectCenter);
    void draw(GLint shaderProgram, glm::vec3 CameraPosition, int call_num);
    void update_points(glm::vec3 CameraPosition, int call_num);
    int render_particles(glm::vec3 objectCenter, glm::vec3 cam_pos, GLint shaderProgram, int call_num);
};

#endif /* ParticleSystem_hpp */
