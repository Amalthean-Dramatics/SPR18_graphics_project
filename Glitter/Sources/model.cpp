/**
 * Name: Riley Myers
 * File Name: mesh.cpp
 * Synopsis: This file contains method defintitions for the mesh class.
 */

#include "model.h"
#include "warning.h"

#include <assimp/Importer.hpp>  // C++ import interface
#include <assimp/postprocess.h> // Various post-processing options


/******************************************************************************
    PARAMETERIZED CONSTRUCTOR
    purpose: create instance of Model with file set to specified fileName
    --------------------------------------------------------------------------
    requires: fileName
    ensures: instance of Model created 
******************************************************************************/
Model::Model(std::string filename)
{
    this->file = filename;

    load_model();
}


void Model::render(Shader* shader)
{
    shader->enable();

    for (auto& i: meshes) {
        //std::cout << BGREEN << "Testing!" << ENDCOL << std::endl;
        i.render();
    }

    shader->disable();
}




/******** Private members **********/
/******************************************************************************
    Load_Model
    purpose: to load the various meshes of a model into memory 
    --------------------------------------------------------------------------
    requires: file to be set to some value
    ensures: verticies, normals, and faces read from specified file and stored
                     in respective variables.  Basic object information displayed to 
                     screen for debugging purposes.
    returns: true on success, false on failure
******************************************************************************/
bool Model::load_model(void)
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


    for (uint32_t i = 0; i < scene->mNumMeshes; i++) {
        Mesh mesh(scene, i, this->file);
        meshes.push_back(mesh);
    }

    std::cout << "Model: " << file << " has " << scene->mNumMeshes << " meshes.\n";

    // Test that the import was sucessful
    //std::cout << GREEN << "Test:" << (*scene).mModeles[0] << ENDCOL << std::endl;
    return true;
}

/******************************************************************************
        DECONSTRUCTOR
        purpose: to deallocate memory
        --------------------------------------------------------------------------
        requires: instanced Model
        ensures: all memory allocated to Model returned to OS
******************************************************************************/
Model::~Model()
{

}
