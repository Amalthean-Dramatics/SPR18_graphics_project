/**
 * Name: Riley Myers
 * File Name: mesh.cpp
 * Synopsis: This file contains method defintitions for the mesh class.
 */

#include "mesh.h"
#include "warning.h"
#include <assimp/Importer.hpp>  // C++ import interface
#include <assimp/scene.h>       // The oupput data structure
#include <assimp/postprocess.h> // Various post-processing options



/******************************************************************************
    DEFAULT CONSTRUCTOR
    purpose: creates default instance of Mesh
    --------------------------------------------------------------------------
    requires: nothing
    ensures: instance of Mesh created such that numVert = numNorm = numFaces
                     = numIndex = 0; 
                     file set to default value
******************************************************************************/
Mesh::Mesh()
{
    numVert = 0;
    numNorm = 0;
    numFaces = 0;
    numIndex = 0;
    file = "default";
}

/******************************************************************************
    PARAMETERIZED CONSTRUCTOR
    purpose: create instance of Mesh with file set to specified fileName
    --------------------------------------------------------------------------
    requires: fileName
    ensures: instance of Mesh created such that numVert = numNorm = numFaces
                     = numIndex = 0;
                     file = #fileName
******************************************************************************/
Mesh::Mesh(std::string fileName)
{
    numVert = 0;
    numNorm = 0;
    numFaces = 0;
    numIndex = 0;
    file = fileName;
}

/******************************************************************************
    LOAD
    purpose: to load the Mesh from the specified .obj file onto the GPU
    --------------------------------------------------------------------------
    requires: program
    ensures: Mesh information is loaded onto the GPU
******************************************************************************/
void Mesh::load(GLuint & program)
{
    load_obj_data();
    // now we need to create a buffer object
    int size = (numVert * sizeof(glm::vec4));

    // make sure to put the color and the vertices into the same buffer
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, size + size, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, vert);
    glBufferSubData(GL_ARRAY_BUFFER, size, size, color);

    // load the index buffer for the vertices
    glGenBuffers(1, &IndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
    // Because GL_ELEMENT_ARRAY_BUFFER deals in vertex array indices we need to multiply by 
    // the number of elements in each vertex (we are using an array of vec4s) to load ALL
    // of our data instead of only the first quarter
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndex * 4, index, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // complete all the plumbing stuffs
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);

    /*glVertexAttribPointer(
        GLuint attribute_v_color,       (attribute)
        GLint 3,                                        (number of elements per vertex, here (r,g,b))
        GLenum GL_FLOAT,                        (the type of each element)
        GLboolean GL_FALSE,                     (take our values as-is)
        GLsizei 0,                  (no extra data between each position)
        const GLvoid* 0             (offset of first element)
    );*/
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, 
            (GLvoid*)(numVert * sizeof(glm::vec4)));
} // end Mesh::load

/******************************************************************************
    DRAW
    purpose: to have the GPU draw the object into the buffer
    --------------------------------------------------------------------------
    requires: successful load
    ensures: Mesh has been drawn into buffer
******************************************************************************/
void Mesh::draw()
{
        glDrawArrays(GL_TRIANGLES, 0, numVert);
}

/******************************************************************************
    Load_Obj_Data
    purpose: to acquire vertex, normals, and faces from the specified .obj 
                     file
    --------------------------------------------------------------------------
    requires: file to be set to some value
    ensures: verticies, normals, and faces read from specified file and stored
                     in respective variables.  Basic object information displayed to 
                     screen for debugging purposes.
    returns: true on success, false on failure
******************************************************************************/
bool Mesh::load_obj_data(void)
{
    Assimp::Importer import;

    // Actually use the importer to load a file
    const aiScene* scene = import.ReadFile(file,
                              aiProcess_Triangulate
                            | aiProcess_FlipUVs
                            | aiProcess_CalcTangentSpace
                            | aiProcess_JoinIdenticalVertices);
    if (!scene) {
        // The file could not be read or some other error occurred
        std::cout << ERRCOL << "ERROR:ASSIMP-MODEL_IMPORT: " 
                  << import.GetErrorString() << ENDCOL << std::endl;
    return false;
    }

    // Test that the import was sucessful
    std::cout << GREEN << "Test:" << (*scene).mMeshes[0] << ENDCOL << std::endl;
    return true;
}

/******************************************************************************
        DECONSTRUCTOR
        purpose: to deallocate memory
        --------------------------------------------------------------------------
        requires: instanced Mesh
        ensures: all memory allocated to Mesh returned to OS
******************************************************************************/
Mesh::~Mesh()
{

}
