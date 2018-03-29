//
//  ParticleSystem.cpp
//  CSE_167_Final_Project
//
//  Created by Mackenzie Monroe on 12/10/17.
//  Copyright © 2017 Mackenzie Monroe. All rights reserved.
//

#include "ParticleSystem.hpp"
#include "time.h"


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


Particle::Particle(glm::vec3 objectCenter)
{
    //initialize the particle
    life = 140;
    
    speed = glm::vec3(0.0f, 2.0f, 0.0f);
    object_center = objectCenter;
    pos = glm::vec3(object_center[0] + rand() % diameter,
                    object_center[1] + rand() % 20,
                    object_center[2] + rand() % diameter);
    size = 1;

    float angle_val = rand() % 180;
    angle = angle_val / 180.0f * glm::pi<float>();
    weight = 1;
    r = 0.5f;
    g = 0.5f;
    b = 0.5f;
    a = 0.5f;
    
    
    
}

Particle::~Particle()
{
    
}


void ParticleSystem::initialize_points(glm::vec3 objectCenter)
{
    for(int i = 0; i < num_points; i++)
    {
        Particle particle_i(objectCenter);
        points.push_back(particle_i);
        
    }
	glEnable(GL_PROGRAM_POINT_SIZE);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ParticleSystem::~ParticleSystem()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    points.clear();
}

float ParticleSystem::compute_point_size(glm::vec3 CameraPosition)
{
    float distance = sqrt(pow((CameraPosition[0] - points[0].pos[0]),2) + pow((CameraPosition[1] - points[0].pos[1]),2) + pow((CameraPosition[2] - points[0].pos[2]), 2));
    float point_size = point_size_range / distance;
    return point_size;
}

void ParticleSystem::draw(GLint shaderProgram, glm::vec3 CameraPosition, int call_num)
{
    iterations++;
    if(iterations < call_num * iteraton_increment) return;
    
    float point_size = compute_point_size(CameraPosition);
    
	vertices.clear();
  
    for(int i = 0; i < points.size(); i++)
    {
        vertices.push_back(points[i].pos);
    }
    
    
    glm::mat4 modelview = Window::V;
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &modelview[0][0]);
    
    //randomize leaf color
    //glm::vec4 color(188.0f, 1.0f, 20.0f, 1.0f);
	glm::vec4 color(0.0f, 0.0f, 0.0f, 1.0f);
    glUniform4fv(glGetUniformLocation(shaderProgram, "color_val"), 1, &color[0]);
    
    
    glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glPointSize(point_size);
    
    glDrawArrays(GL_POINTS, 0, vertices.size());
    
    glBindVertexArray(0);

}


void ParticleSystem::update_points(glm::vec3 CameraPosition, int call_num)
{
    if(iterations < call_num * iteraton_increment) return;
    
    // Simulate all particles
    int ParticlesCount = 0;
    
    auto it = points.begin();
    
    for(int i=0; i<points.size(); i++){
        
        Particle * p = &points[i]; // shortcut
        
        if((*p).life > 0.0f){
            
            // Decrease life
            (*p).life -= 1;
            if ((*p).life > 0.0f){
                
                // Simulate simple physics : gravity only, no collisions
                (*p).speed += glm::vec3(0.0f,-9.81f, 0.0f) * (float)delta * 0.5f;
                (*p).pos += (*p).speed * (float)delta;
                (*p).cameradistance = glm::length( (*p).pos - CameraPosition );

                
                //slightly rotate p
                glm::vec4 homo_point_2((*p).pos, 1.0f);
                homo_point_2 = glm::rotate(glm::mat4(1.0f), 0.5f / 180.0f * glm::pi<float>() , glm::vec3((rand() % 100) / 100.0f, 0.0f, (rand() % 100) / 100.0f)) * homo_point_2;
                (*p).pos[0] = homo_point_2[0];
                (*p).pos[1] = homo_point_2[1];
                (*p).pos[2] = homo_point_2[2];

            }
            //particle died
            else
            {
                points.erase(it);
            }
            ++it;
    
        }
    }
}

int ParticleSystem::render_particles(glm::vec3 objectCenter, glm::vec3 CameraPosition, GLint shader_program, int call_num)
{
    
    srand(time(NULL) + call_num); //increase randomness
    if(first_call){
        initialize_points(objectCenter);
        first_call = 0;
    }
    draw(shader_program, CameraPosition, call_num);
    update_points(CameraPosition, call_num);
    
    return points.size();
}





