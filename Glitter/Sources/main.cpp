#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


/************************************************************ DEBUG **********/
class my_application{
private:
    GLuint rendering_program;
    GLuint vao;

public:
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;

    void startup() {
        rendering_program = compile_shaders();
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    void shutdown(){
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(rendering_program);
        glDeleteVertexArrays(1, &vao);
    }

    // Our rendering function
    void render(double currentTime){
        // Simply clear the window with red
         const GLfloat color[] = {1.0f, 0.0f, 0.0f, 1.0f};
         glClearBufferfv(GL_COLOR, 0, color);

        // Use the program object we created earlier for rendering
        glUseProgram(rendering_program);

        glDrawArrays(GL_POINTS,0,1);
    }

    // Shader compiler
    GLuint compile_shaders(void){

        // source code for vertex shader
        static const GLchar * vertex_shader_source[] = {
                "#version 450 core                              \n"
                "                                               \n"
                "void main(void)                                \n"
                "{                                              \n"
                "   gl_Position = vec4(0.0, 0.0, 0.5, 1.0);     \n"
                "}                                              \n"
        };

        // Source code for fragment shader
        static const GLchar * fragment_shader_source[] = {
                "#version 450 core                              \n"
                "                                               \n"
                "out vec4 color;                                \n"
                "                                               \n"
                "void main(void)                                \n"
                "{                                              \n"
                "   color = vec4(0.0, 0.8, 1.0, 1.0)            \n"
                "}                                              \n"
        };

        // create and compile vertex shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, vertex_shader_source, nullptr);
        glCompileShader(vertex_shader);

        // create and compile fragment shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, fragment_shader_source, nullptr);
        glCompileShader(fragment_shader);

        // create program, attach shaders to it, and link it
        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        // Delete the shaders as the program has them now
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return program;
   }
};



/************************************************************ DEBUG **********/

int main(){

    my_application tst;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    tst.startup();

    // render loop
    // -----------
    while(!glfwWindowShouldClose(window)){

        tst.render(clock());

        // input
        // -----
        processInput(window);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources
    // -----------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

//glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){

    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0,0,width, height);
}
