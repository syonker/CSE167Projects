//
//  ProceduralPlants.cpp
//  CSE_167_Final_Project
//
//  Created by Mackenzie Monroe on 12/6/17.
//

#include "ProceduralPlants.hpp"

ProceduralPlants::ProceduralPlants(int tree_type, int call_num, glm::vec3 center_pos)
{
    center = center_pos; //initialize object center
    this->tree_type = tree_type; //initialize tree type
    rotation_mat = glm::mat4(1.0f); //initialize rotation matrix
    current_line_width = 0;
    
    //initialize rules
    if(tree_type == 1)
    {
        start = "A";
        RULE_1 = "B";
        RULE_2 = "A";
        RULE_3 = "A[LB]A[RB][B]";
        DEPTH = 9;
    }
    
    //fractal binary tree (rules from wikipedia)
    else if(tree_type == 2)
    {
        start = "B";
        RULE_1 = "AA";
        RULE_2 = "A[LB]RB";
        RULE_3 = "A[LB]RB";
        DEPTH = 5;
    }
    
    //Fern from lecture slides
    else
    {
        start = "A";
        RULE_1 = "BL[[A]RA]RB[RBA]LA";
        RULE_2 = "BB";
        RULE_3 = "BB";
        DEPTH = 3;
    }
    
    //starting position
    positions.push_back(glm::vec3(0.0f,0.0f,0.0f));
    
    srand(seed);
    int rand_num;
    
    //expand the rules into one long string
    std::string curr_string = start;
    
    for(int i = 0; i < DEPTH; i++)
    {
        rand_num = rand() % 100;
        curr_string = expand_string(rand_num, curr_string);
    }
    
    tree_string = curr_string;
    
    //initialize indices
    indices.push_back(0);
    indices.push_back(1);
    
    //calculate line width
    GLfloat LineRange[2];
    glGetFloatv(GL_LINE_WIDTH_RANGE,LineRange);
    min_line_width = LineRange[0];
    max_line_width = LineRange[1];
    
    current_width = max_line_width;
    width_increment = max_line_width / 4.0f;

	//initialize branch buffers
	glEnable(GL_PROGRAM_POINT_SIZE);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//initialize the leaf buffers
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*leaf_points.size(), leaf_points.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

ProceduralPlants::~ProceduralPlants()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VAO2);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &VBO2);
    glDeleteBuffers(1, &EBO);
    
    vertices.clear();
    indices.clear();
    positions.clear();
    leaf_points.clear();
    branch_points.clear();

}

float ProceduralPlants::compute_point_size(glm::vec3 CameraPosition)
{
    float distance = sqrt(pow((CameraPosition[0] - leaf_points[0][0]),2) + pow((CameraPosition[1] - leaf_points[0][1]),2) + pow((CameraPosition[2] - leaf_points[0][2]), 2));
    float point_size = point_size_range / distance;
    return point_size;
}

void ProceduralPlants::pop_position()
{
    positions.pop_back();
        if(fill_leaves_and_branches)leaf_points.push_back(last_position);
		current_width += width_increment;
		if (current_width > max_line_width) current_width = max_line_width;
    
}

void ProceduralPlants::push_position(glm::vec3 curr_pos)
{
    positions.push_back(curr_pos);
 
   
	current_width -= width_increment;
	if (current_width < min_line_width) current_width = min_line_width;

}

void ProceduralPlants::draw_leaves(GLuint shaderProgram, glm::vec3 CameraPosition, std::vector<glm::vec3> points)
{
    for(int i = 0; i < points.size(); i++)
    {
        float point_size = compute_point_size(CameraPosition);
        
        //initialize the leaf points
        /*glGenVertexArrays(1, &VAO2);
        glGenBuffers(1, &VBO2);
        glBindVertexArray(VAO2);
        glBindBuffer(GL_ARRAY_BUFFER, VBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*points.size(), points.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);*/

        glm::mat4 modelview = Window::V;
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &Window::P[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &modelview[0][0]);
        
		glBindVertexArray(VAO2);
		glBindBuffer(GL_ARRAY_BUFFER, VBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*points.size(), points.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

        //randomize leaf color
        glm::vec4 color;
        int rand_num = rand() % 3;
        if(rand_num == 0)
        {
            color = glm::vec4(51.0 / 255.0, 102.0 / 255.0, 0.0 / 255.0, 1.0);
        }
        else if(rand_num == 1)
        {
            color = glm::vec4(0.0 / 255.0, 51.0 / 255.0, 0.0 / 255.0, 1.0);
        }
        else
        {
            color = glm::vec4(0.0 / 255.0, 153.0 / 255.0, 76.0 / 255.0, 1.0);
        }
        
        glUniform4fv(glGetUniformLocation(shaderProgram, "color_val"), 1, &color[0]);
        
        glPointSize(point_size);
        glDrawArrays(GL_POINTS, 0, points.size());
        glBindVertexArray(0);

    }
}

void ProceduralPlants::translate_points()
{
    //translate branch points to the object center
    std::vector<glm::vec3> new_points;
    
    for(int i = 0; i < branch_points.size(); i++)
    {
        glm::vec4 point_homo((branch_points)[i][0], branch_points[i][1], branch_points[i][2], 1);
        
        point_homo = glm::translate(glm::mat4(1.0f), center) *point_homo;
        
        new_points.push_back(glm::vec3(point_homo[0], point_homo[1], point_homo[2]));

    }
    
    branch_points = new_points;
    
    //translate leaves to the object center
    std::vector<glm::vec3> new_leaf_points;
    
    for(int i = 0; i < leaf_points.size(); i++)
    {
        glm::vec4 point_homo((leaf_points)[i][0], leaf_points[i][1], leaf_points[i][2], 1);
        
        point_homo = glm::translate(glm::mat4(1.0f), center) *point_homo;
        
        new_leaf_points.push_back(glm::vec3(point_homo[0], point_homo[1], point_homo[2]));
        
    }
    
    leaf_points = new_leaf_points;
}

void ProceduralPlants::rotate_right(glm::vec3 * point)
{
    //generate random rotation angles
    float x_rotation_val = rand() % 40;
    float y_rotation_val = 60 + rand() % 40;
    float z_rotation_val = rand() % 40;
    
    glm::vec4 point_homo((*point)[0], (*point)[1], (*point)[2], 1);
    
    point_homo = glm::rotate(glm::mat4(1.0f), x_rotation_val / 180.0f * glm::pi<float>(), glm::vec3(1.0f,0.0f,0.0f))*point_homo;
    point_homo = glm::rotate(glm::mat4(1.0f), y_rotation_val / 180.0f * glm::pi<float>(), glm::vec3(0.0f,1.0f,0.0f))*point_homo;
    point_homo = glm::rotate(glm::mat4(1.0f), z_rotation_val / 180.0f * glm::pi<float>(), glm::vec3(0.0f,0.0f,1.0f))*point_homo;
    
    (*point)[0] = point_homo[0];
    (*point)[1] = point_homo[1];
    (*point)[2] = point_homo[2];
    
}


void ProceduralPlants::rotate_left(glm::vec3 * point)
{
    float x_rotation_val = -1*(rand() % 40);
    float y_rotation_val = -(60 + rand() % 40);
    float z_rotation_val = -1*(rand() % 40);
    
    glm::vec4 point_homo((*point)[0], (*point)[1], (*point)[2], 1);
    
    point_homo = glm::rotate(glm::mat4(1.0f), x_rotation_val / 180.0f * glm::pi<float>(), glm::vec3(1.0f,0.0f,0.0f))*point_homo;
    point_homo = glm::rotate(glm::mat4(1.0f), y_rotation_val / 180.0f * glm::pi<float>(), glm::vec3(0.0f,1.0f,0.0f))*point_homo;
    point_homo = glm::rotate(glm::mat4(1.0f), z_rotation_val / 180.0f * glm::pi<float>(), glm::vec3(0.0f,0.0f,1.0f))*point_homo;
    
    (*point)[0] = point_homo[0];
    (*point)[1] = point_homo[1];
    (*point)[2] = point_homo[2];
    
}

std::string ProceduralPlants::expand_string(float rand_num, std::string curr_string)
{
    std::string curr_symbol;
    
    std::vector<std::string> new_string;
    
    //expand the current active string, and add it to the complete tree
    for(int i = 0; i < curr_string.length(); i++)
    {
        curr_symbol = curr_string[i];
        
        //expand A
        if(curr_symbol.compare("A") == 0)
        {
            new_string.push_back(RULE_1);
        }
        
        //expand B
        else if(curr_symbol.compare("B") == 0)
        {
            //randomize rule selection
            if (rand_num < 50){
                new_string.push_back(RULE_2);
                
            } else {
                new_string.push_back(RULE_3);
            }
        }
        else new_string.push_back(curr_symbol);
        
    }

    std::string full_string;
    
    for(int i = 0; i < new_string.size(); i++)
    {
        full_string = full_string.append(new_string[i]);
    }

    return full_string;
}

glm::vec3 ProceduralPlants::draw_line(GLuint shaderProgram, glm::vec3 point_1)
{
    //randomize the line length
    float length = 0.5 + (rand() % 2) / 2.0;
    if(tree_type == 1)
    {
        length = length * 5;
    }
    else if(tree_type == 2)
    {
        length = length;
    }
    else
    {
        length = length * 4;
    }
    
    //calculate the second point
    glm::vec3 point_2;

    glm::vec4 homo_point_2(point_1[0], point_1[1] + length, point_2[2], 1);
    homo_point_2 = rotation_mat * homo_point_2;
   
    point_2[0] = homo_point_2[0];
    point_2[1] = homo_point_2[1];
    point_2[2] = homo_point_2[2];
    
    if(fill_leaves_and_branches)
    {
        branch_points.push_back(point_1);
        branch_points.push_back(point_2);
        line_widths.push_back(current_width);
    }
    
    return point_2;
    
}

void ProceduralPlants::draw_line_2(GLuint shaderProgram, glm::vec3 point_1, glm::vec3 point_2, int pass)
{

	if (pass == 1) {

		glUseProgram(Window::shadowID);


		//add points to vertices
		vertices.clear();
		vertices.push_back(point_1);
		vertices.push_back(point_2);


		glm::mat4 model = glm::mat4(1.0f);

		GLuint Model = glGetUniformLocation(Window::shadowID, "model");

		glUniformMatrix4fv(Model, 1, GL_FALSE, &model[0][0]);


		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//get line width
		//glLineWidth(line_widths[0]);
		glLineWidth(line_widths[current_line_width]);
		current_line_width++;
		glDrawArrays(GL_LINES, 0, vertices.size());

		glBindVertexArray(0);



	}
	else {

		//add points to vertices
		vertices.clear();
		vertices.push_back(point_1);
		vertices.push_back(point_2);


		glm::mat4 modelview = Window::V;

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &Window::P[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelview"), 1, GL_FALSE, &modelview[0][0]);

		//randomize branch color
		glm::vec4 color;
		int rand_num = rand() % 3;
		if (rand_num == 0)
		{
			color = glm::vec4(139.0 / 255.0, 69.0 / 255.0, 19.0 / 255.0, 1.0);
		}
		else if (rand_num == 1)
		{
			color = glm::vec4(160.0 / 255.0, 82.0 / 255.0, 45.0 / 255.0, 1.0);
		}
		else
		{
			color = glm::vec4(205.0 / 255.0, 133.0 / 255.0, 63.0 / 255.0, 1.0);
		}
		glUniform4fv(glGetUniformLocation(shaderProgram, "color_val"), 1, &color[0]);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		//get line width
		//glLineWidth(line_widths[0]);
		glLineWidth(line_widths[current_line_width]);
		current_line_width++;
		glDrawArrays(GL_LINES, 0, vertices.size());

		glBindVertexArray(0);

	}
    
}

void ProceduralPlants::draw(GLuint shaderProgram, glm::vec3 curr_position, std::string curr_string, glm::vec3 CameraPosition, int pass)
{
    srand(seed);
    
    //compute the vertices only the first time draw is called
    if(fill_leaves_and_branches){
        
        std::string curr_symbol;
        
        for(int i = 0; i < curr_string.length(); i++)
        {
            curr_symbol = curr_string.at(i);
            
            //draw current symbol
            if(curr_symbol.compare("A") == 0)
            {
                if(tree_type != 3)
                {
                    glm::vec3 new_position = draw_line(shaderProgram, curr_position);
                    rotation_mat = glm::mat4(1.0f);
                    curr_position = new_position;
                }
            }
            else if(curr_symbol.compare("B") == 0)
            {
                glm::vec3 new_position = draw_line(shaderProgram, curr_position);
                last_position = new_position;
                rotation_mat = glm::mat4(1.0f);
                curr_position = new_position;
            }
            else if(curr_symbol.compare("R") == 0)
            {
                rotation_mat = glm::rotate(glm::mat4(1.0f), 20.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f,1.0f,1.0f));
            }
            else if(curr_symbol.compare("L") == 0)
            {
                rotation_mat = glm::rotate(glm::mat4(1.0f), -20.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f,1.0f,1.0f));
            }
            else if(curr_symbol.compare("[") == 0)
            {
                push_position(curr_position);
            }
            else if(curr_symbol.compare("]") == 0)
            {
                curr_position = positions[positions.size() - 1];
                pop_position();
            }
        }
        fill_leaves_and_branches = 0;
        translate_points();
    }
    //draw lines from memory
    else{
        draw_leaves(shaderProgram, CameraPosition, leaf_points);

        for(int i = 0; i < branch_points.size(); i+=2)
        {

			if (pass == 1) {

				draw_line_2(Window::shadowID, branch_points[i], branch_points[i + 1], 1);

			}
			else {

				draw_line_2(shaderProgram, branch_points[i], branch_points[i + 1], 2);

			}
        }
        current_line_width = 0;
    }
}

//clear the leaves and branches vectors to be refilled
void ProceduralPlants::clear_leaves_and_branches()
{
    leaf_points.clear();
    branch_points.clear();
}