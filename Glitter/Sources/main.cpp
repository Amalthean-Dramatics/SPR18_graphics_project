#include "warning.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "../Vendor/apathy/path.hpp"

#include "shader.h"
#include "camera.h"
#include "model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_call(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_call(GLFWwindow* window, double xpos, double ypos);
void handleError(GLenum source, GLenum type, GLuint id, GLenum severity,
                 GLsizei length, const GLchar* message, const void* userParam);


//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Sadness....
Camera* cam = new Camera();
double delta = 0;


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

    glm::mat4 view(1.0f);

    /* Set up the camera */
    cam->set_fov(90);
    cam->set_render(PERSPECTIVE);
    cam->update_window(SCR_WIDTH, SCR_HEIGHT);

    glEnable(GL_DEPTH_TEST);
  

    /* Enable OpenGL Debug information */
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback( (GLDEBUGPROC) handleError, 0);


    // Setup shaders
    apathy::Path root("shaders/"); // TODO
    Shader *test = new Shader("shaders/ortho.vs", "shaders/ortho.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    //Model *box = new Model("models/basic_cube.obj", test);
    //Model *box = new Model("models/test_obj.obj", test);
    Model *box = new Model("models/museum.obj", test);


    //Handle key presses using callback functions
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
        
    glfwSetKeyCallback(window, key_call);
    glfwSetCursorPosCallback(window, mouse_call);


    /* Set up some variables to track how long each frame takes to get
     * smooth(er) movement*/
    double last = 0.0;
    double curr = 0.0;

    // render loop
    // -----------
    while(!glfwWindowShouldClose(window)){

        curr  = glfwGetTime();

        delta = curr - last;
        last  = curr;

        // render
        // ------
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   //Teal
        glClearColor(0.3255f, 0.4078f, 0.4706f, 1.0f);   // Payne's Grey
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        box->render(cam);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    delete box;
    delete test;

    // glfw: terminate, clearing all previously allocated GLFW resources
    // -----------------------------------------------------------------
    glfwTerminate();
    return 0;
}


/**
 * Process keyboard input using a GLFW callback function.
 */
void key_call(GLFWwindow* window __attribute__((unused)), int key,
              int scancode __attribute__((unused)), int action,
              int mods __attribute__((unused)))
{
    const int mode[] = {GL_LINE, GL_POINT, GL_FILL};
    static uint8_t state = 0;
    static uint8_t rend = 0;
    int dir = NONE;

    /* I immediately regret my decision */
    /* Handle keypresses for the camera */
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_W)    dir |= FORWARDS;
        if (key == GLFW_KEY_S)    dir |= BACKWARDS; 
        if (key == GLFW_KEY_A)    dir |= LEFT;      
        if (key == GLFW_KEY_D)    dir |= RIGHT;     
        if (key == GLFW_KEY_Q)    dir |= ROLL_LEFT; 
        if (key == GLFW_KEY_E)    dir |= ROLL_RIGHT;
        if (key == GLFW_KEY_Z)    dir |= UP;        
        if (key == GLFW_KEY_C)    dir |= DOWN;      
    }


    cam->process_kbd((direction_t)dir, delta);


    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (key == GLFW_KEY_M && action == GLFW_PRESS) {

        // Switch display modes if the `m` key is pressed
        state = (state + 1) % 3;
        glPolygonMode(GL_FRONT_AND_BACK, mode[state]);
    } else if (key == GLFW_KEY_R && action == GLFW_PRESS) {

        // Switch rendering modes
        if (rend) {
            cam->set_render(PERSPECTIVE);
        } else {
            cam->set_render(ORTHOGRAPHIC);
        }
        rend = !rend;
    }


}

/**
 * Process all mouse motion input, using a GLFW callback function.
 * TODO - add option to invert y-axis
 */
void mouse_call(GLFWwindow* window __attribute__((unused)),
                double xpos, double ypos)
{
    //We need to do some pre-processing here
    static float x = 0.0f, y = 0.0f; 
    cam->process_mouse(xpos - x, y - ypos);

    x = xpos;
    y = ypos;
}


//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window __attribute__((unused)),
                               int width, int height){

    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    cam->update_window(width, height);
}

/**
 * Call-back function registered with OpenGL to run on errors.
 * TODO
 */

void handleError( GLenum source __attribute__((unused)),
                  GLenum type,
                  GLuint id __attribute__((unused)),
                  GLenum severity,
                  GLsizei length __attribute__((unused)),
                  const GLchar* message,
                  const void* userParam __attribute__((unused)))
{
  fprintf(stderr, BWHITE "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n" ENDCOL,
           ( type == GL_DEBUG_TYPE_ERROR ? ERRCOL "** GL ERROR **" : WRNCOL "" ),
            type, severity, message );
}
