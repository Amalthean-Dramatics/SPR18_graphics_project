/**
 * Name: Riley Myers
 * File Name: mesh.h
 * Synopsis: This file contains a class declaration for a class to store meshes.
 */

#pragma once
#include <string>
#include <iostream>
//#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <vector>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective

class Mesh
{
public:
    Mesh();
    Mesh(std::string fileName);
    bool load_obj_data(void);
    ~Mesh();

private:
    int numVert;
    int numNorm;
    int numFaces;
    int numIndex;
    
    std::vector<float> vao;
    std::vector<float> vbo;
    //std::vector<glm::vec4> vertList;
    //std::vector<glm::vec4> tempVertList;
    //std::vector<glm::vec4> normList;
    //std::vector<uint32_t> vertexIndex;
    //std::vector<uint32_t> normalsIndex;
    //glm::vec4 *vert, *color, *normal;
    //uint32_t *index;
    //uint32_t buffer, IndexBuffer;

    std::string file;
};

