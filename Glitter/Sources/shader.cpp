/**
 * Name: Riley Myers
 * File Name: shader.cpp
 * Synopsis: This file contains method definitions for the shader class.
 */

#include "shader.h"
#include "warning.h"

#include <glm/detail/type_mat.hpp>
#include <glm/gtc/type_ptr.hpp>



Shader::Shader(std::string vertex_name, std::string fragment_name)
{
    // Load shaders from files
    vertex_id = this->load_file(vertex_name, GL_VERTEX_SHADER);
    fragment_id = this->load_file(fragment_name, GL_FRAGMENT_SHADER);
            
    // Link shaders
    shader_id = glCreateProgram();
    glAttachShader(shader_id, vertex_id);
    glAttachShader(shader_id, fragment_id);

    // Bind to caller's VAO (Causing errors, so leaving out atm)
    //glBindAttribLocation(shader_id, 0, "position");

    // Actually link it!
    glLinkProgram(shader_id);


    int success;
    // Check for linking errors
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shader_id, 512, NULL, infoLog);
        std::cout << ERRCOL << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << ENDCOL << infoLog << std::endl;
    }


    // Get uniforms so that they can be set later
    proj_matrix = get_uniform_location("view_matrix");
    tex_bool = get_uniform_location("has_tex");
}


/**
 * Enable the given shader
 */
void Shader::enable(void)
{
    glUseProgram(shader_id);
}

/**
 * Disable the given shader
 */
void Shader::disable(void)
{
    glUseProgram(0);
}

/**
 * Set the universal view matrix for the vertex shader
 */

void Shader::set_uni_matrix(glm::mat4 mat)
{
    glUniformMatrix4fv(proj_matrix, 1, GL_FALSE, glm::value_ptr(mat));
}

/**
 * Set whether the fragment shader uses a texture or whether it uses a (flat) colour
 */

void Shader::set_has_tex(bool val)
{
    glUniform1i(tex_bool, val);
}

/**
 * Destroy! DESTROY IT ALL!
 */
Shader::~Shader()
{
    // Stahp.
    disable();

    glDetachShader(shader_id, vertex_id);
    glDetachShader(shader_id, fragment_id);

    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);

    glDeleteProgram(shader_id);
}


/******** Private members **********/
/******************************************************************************
    load_file
    purpose: Loads a shader of a given type from a given file 
    --------------------------------------------------------------------------
******************************************************************************/
uint32_t Shader::load_file(std::string file, GLenum type)
{
#ifndef NDEBUG
    //DEBUG!!!
    std::cout << BGREEN << "File path is: " << file << ENDCOL << std::endl;
#endif
    //Error check this!
    std::ifstream f(file);

    // This gives me shudders....WHY!!!
    std::string contents((std::istreambuf_iterator<char>(f)),
                          std::istreambuf_iterator<char>());
    const char* program = contents.c_str();              

#ifndef NDEBUG
    std::cout << BGREEN << "File program is: \n" << ENDCOL << program << std::endl;
#endif

    // Now create and compile the shader!
    int success;
    char infoLog[512];
    uint32_t shade = glCreateShader(type);

    glShaderSource(shade, 1, &program, NULL);
    glCompileShader(shade);

    // Check for shader compile errors
    glGetShaderiv(shade, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shade, 512, NULL, infoLog);
        std::cout << ERRCOL << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << ENDCOL << infoLog << std::endl;
        exit(-1);
    }

    return shade;
}


/**
 * Wrapper function to get a given uniform location and error-catch.
 */
GLint Shader::get_uniform_location(std::string uniform)
{
    GLint location = glGetUniformLocation(shader_id, uniform.c_str());
    if (location == -1) {
        std::cout << WRNCOL << "WARN: Uniform \"" << uniform 
                  << "\" not found in shader"     << ENDCOL << std::endl;
    }
    return location;
}
