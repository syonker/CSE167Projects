//
//  ProceduralPlants.hpp
//  CSE_167_Final_Project
//
//  Created by Mackenzie Monroe on 12/6/17.
//

#ifndef ProceduralPlants_hpp
#define ProceduralPlants_hpp

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

#include <string>
#include <vector>
#include "Window.h"
#include <iostream>

class ProceduralPlants
{
public:
    
    ProceduralPlants(int tree_type, int call_num, glm::vec3 center); //constructor
    
    ~ProceduralPlants(); //destructor
    
    //characteristics
    std::string start;
    std::string RULE_1;
    std::string RULE_2;
    std::string RULE_3;
    int tree_type;
    int DEPTH;
    glm::vec3 center; //tree position
    
    //for tree building
    glm::mat4 rotation_mat; //keeps track of the current rotation for a given point during building
    std::vector<glm::vec3> positions; //keeps track of which position to draw from during building
    glm::vec3 last_position; //last position during tree drawing
    int seed = 5; //seed used for the random number generator
    std::string tree_string; //fully expanded string
    int fill_leaves_and_branches = 1; //keeps track of whether the trees have been built already
    
    //for redrawing
    std::vector<glm::vec3> vertices; //vertices used in drawing
    std::vector<int> indices; //indices used in drawing
    GLuint VAO, VAO2, VBO, VBO2, EBO; // Buffers used in drawing
    std::vector<glm::vec3> leaf_points; //all leaf points
    std::vector<glm::vec3> branch_points; //sets of branch points
    std::vector<float> line_widths; //line widths for each branch
    int current_line_width; //index for which line were on
    
    //ranges
    float min_line_width; //minimum availabe line width
    float max_line_width; //maximum avaiable line width
    float width_increment; // amount to increment the tree branch widths
    float current_width; //current tree branch width
    int point_size_range = 1500; //used for computing point size
    
    
    //functions to build the tree
    void push_position(glm::vec3 curr_pos);
    void pop_position();
    void rotate_right(glm::vec3 * point);
    void rotate_left(glm::vec3 * point);
    std::string expand_string(float rand_num, std::string curr_string);
    float compute_point_size(glm::vec3 CameraPosition);
    void translate_points();
    
    //drawing functions
    void draw(GLuint shaderProgram, glm::vec3 curr_position, std::string curr_symbol, glm::vec3 CameraPosition, int pass);
    glm::vec3 draw_line(GLuint shaderProgram, glm::vec3 point_1); //computes each next point
    void draw_line_2(GLuint shaderProgram, glm::vec3 point_1, glm::vec3 point_2, int pass); //draws each line
    void draw_leaves(GLuint shaderProgram, glm::vec3 CameraPosition, std::vector<glm::vec3> points);
    void clear_leaves_and_branches();    //clear leaves and branches vectors when seed is changed

};

#endif /* ProceduralPlants_hpp */
