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



class Shader
{
public:
    Shader(std::string vertex_name, std::string fragment_name);

    void enable(void);
    void disable(void);

    ~Shader();

    uint16_t shader_id;

private:
    uint16_t vertex_id;
    uint16_t fragment_id;



    uint16_t load_file(std::string file, GLenum type);
};

