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
