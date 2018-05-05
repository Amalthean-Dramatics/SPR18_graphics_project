#include "warning.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "../Vendor/apathy/path.hpp"

#include "shader.h"
#include "model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void handleError(GLenum source, GLenum type, GLuint id, GLenum severity,
                 GLsizei length, const GLchar* message, const void* userParam);


//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main(){

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Amalthean Dramatics", NULL, NULL);
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    /* Enable OpenGL Debug information */
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback( (GLDEBUGPROC) handleError, 0);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    Model *box = new Model("../models/test_obj.obj");

    // Setup shaders
    apathy::Path root("../shaders/"); // TODO
    Shader *test = new Shader("../shaders/simple.vs", "../shaders/simple.fs");

    test->enable();

    //box->render(shaderProgram);
    // render loop
    // -----------
    while(!glfwWindowShouldClose(window)){

        // input
        // -----
        processInput(window);

        // render
        // ------
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //Teal
        glClearColor(0.3255f, 0.4078f, 0.4706f, 1.0f);   // Payne's Grey
        glClear(GL_COLOR_BUFFER_BIT);

        box->render(test);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);

    delete box;
    delete test;

    // glfw: terminate, clearing all previously allocated GLFW resources
    // -----------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window){
    int mode[] = {GL_LINE, GL_POINT, GL_FILL};
    static uint8_t state = 0;

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {

        // Switch display modes if the `m` key is pressed
        state = (state + 1) % 3;
        glPolygonMode(GL_FRONT_AND_BACK, mode[state]);
    }
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0,0,width, height);
}

/**
 * Call-back function registered with OpenGL to run on errors.
 * TODO
 */

void handleError( GLenum source,
                  GLenum type,
                  GLuint id,
                  GLenum severity,
                  GLsizei length,
                  const GLchar* message,
                  const void* userParam )
{
  fprintf(stderr, BWHITE "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n" ENDCOL,
           ( type == GL_DEBUG_TYPE_ERROR ? ERRCOL "** GL ERROR **" : WRNCOL "" ),
            type, severity, message );
}
