/**
 * Name: Riley Myers
 * File Name: model.h
 * Synopsis: This file contains a class declaration for a class to contain
 *      three-dimensional models
 */

#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <fstream>
#include <vector>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
// glm::translate, glm::rotate, glm::scale, glm::perspective

#include "shader.h"
#include "mesh.h"

#include <assimp/scene.h>       // The output data structure


class Model
{
public:
    Model(std::string filename);
    void render(Shader* shader);
    ~Model();

private:
    std::vector<Mesh> meshes;
    std::string file;

    bool load_model(void);
};

