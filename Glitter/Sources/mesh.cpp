/**
 * Name: Riley Myers
 * File Name: mesh.cpp
 * Synopsis: This file contains method defintitions for the mesh class.
 */

#include "mesh.h"
#include "warning.h"
#include <assimp/scene.h>       // The output data structure
#include <assimp/postprocess.h> // Various post-processing options

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



/******************************************************************************
    PARAMETERIZED CONSTRUCTOR
    purpose: create instance of Mesh with file set to specified fileName
    --------------------------------------------------------------------------
    requires: fileName
    ensures: instance of Mesh created 
******************************************************************************/
Mesh::Mesh(const aiScene* scene, uint32_t index, std::string filename)
{
    this->file = filename;

    load_obj_data(scene, index);
    bind_buf_data();
}




void Mesh::render(void)
{
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->face.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}




/******** Private members **********/
/******************************************************************************
    Bind_Buf_Data
    purpose: TODO
    --------------------------------------------------------------------------
******************************************************************************/
void Mesh::bind_buf_data(void)
{
    this->vaoSize = 1;
    this->vboSize = 1;

    // Generate OpenGL buffer structures
    glGenVertexArrays(this->vaoSize, &this->vao);
    glGenBuffers(this->vboSize, &this->vbo);

    // First, we need to bind this vao so our modifications affect it.
    glBindVertexArray(this->vao);

    // Bind the buffer containing the verticies and actually load said buffer.
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, this->vert.size() * sizeof(glm::vec3), vert.data(), GL_STATIC_DRAW);

    // Set up attribute pointer?
    const GLuint index = 0;
    const GLint  size = 3;
    const GLenum type = GL_FLOAT;
    const GLboolean normalized = GL_FALSE;
    const GLsizei stride = 0;
    const GLvoid *pointer = (void *) 0;

    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(0);

    //Generate index buffer and load with faces
    glGenBuffers(1, &this->indexVbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexVbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->face.size() * sizeof(unsigned int), face.data(), GL_STATIC_DRAW);
    
    // Unbind VAO to be clean.
    glBindVertexArray(0);
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
bool Mesh::load_obj_data(const aiScene* scene, uint32_t ind)
{
    aiMesh* mesh = scene->mMeshes[ind];
    this->numVertices = mesh->mNumVertices;

    glm::vec3 vector;
    for (unsigned int i = 0; i < this->numVertices; i++) {
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        this->vert.push_back(vector);
    }

#ifndef NDEBUG
    std::cout << "Model: " << file << " has " << numVertices << " vertices.\n";
#endif


    numFaces = mesh->mNumFaces;
    for (unsigned int i = 0; i < numFaces; i++) {
        // Assuming that it will always be triangles due to the preprocessing
        face.push_back(mesh->mFaces[i].mIndices[0]);
        face.push_back(mesh->mFaces[i].mIndices[1]);
        face.push_back(mesh->mFaces[i].mIndices[2]);
    }
#ifndef NDEBUG
    std::cout << "Model: " << file << " has " << numFaces << " faces.\n";
#endif


    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../Glitter/Vendor/bullet/data/kitchens/fatihrmutfak/metal.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    // Test that the import was sucessful
    //std::cout << GREEN << "Test:" << (*scene).mMeshes[0] << ENDCOL << std::endl;
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
