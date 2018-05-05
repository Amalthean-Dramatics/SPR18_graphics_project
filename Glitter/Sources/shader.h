/**
 * Name: Riley Myers
 * File Name: shader.h
 * Synopsis: This file contains a class declaration for a shader class.
 */

#pragma once
#include <iostream>
#include <fstream>
#include <fstream>
#include <string>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>



class Shader
{
public:
    Shader(std::string vertex_name, std::string fragment_name);

    void enable(void);
    void disable(void);

    void set_uni_matrix(glm::mat4 mat);
    void set_has_tex(bool val);

    ~Shader();

    uint16_t shader_id;

private:
    uint16_t vertex_id;
    uint16_t fragment_id;

    int32_t  proj_matrix;
    int32_t  tex_bool;

    uint32_t load_file(std::string file, GLenum type);
    GLint    get_uniform_location(std::string uniform);
};

