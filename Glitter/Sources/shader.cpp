/**
 * Name: Riley Myers
 * File Name: shader.cpp
 * Synopsis: This file contains method definitions for the shader class.
 */

#include "shader.h"
#include "warning.h"



Shader::Shader(std::string vertex_name, std::string fragment_name)
{

}

void Shader::enable(void)
{
    glUseProgram(shader_id);
}

void Shader::disable(void)
{
    glUseProgram(0);
}

/**
 * Destroy! DESTROY IT ALL!
 */
Shader::~Shader()
{
    this->disable();

}


/******** Private members **********/
/******************************************************************************
    update_vectors
    purpose: updates the internal vectors that the camera uses to keep track of
        its position
    --------------------------------------------------------------------------
******************************************************************************/
uint16_t Shader::load_file(std::string file, GLenum type)
{
    std::ifstream f(file);

    //Error check this!

    std::string program = 
}


