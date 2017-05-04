#include <vector>
#include <map>
#include <iostream>

#include <GL/glew.h>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/cexport.h>
#include <assimp/postprocess.h>

#include "model.h"
#include "enginedata.h"

MODEL::MODEL()
{
    IFlags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices;
    EFlags = aiProcess_SplitLargeMeshes;
    scene = NULL;
    vertexBuffer = 0;
    glGenBuffers(1,&vertexBuffer);
    glGenBuffers(1,&colorBuffer);
    ModelMatrix = glm::mat4(1.0f);
}

MODEL::~MODEL()
{
    if(scene != NULL)
    {
        aiReleaseImport(scene);
        scene = NULL;
    }

    glDeleteBuffers(1, &vertexBuffer);
    
}

bool MODEL::loadModel(std::string path)
{
    if(scene != NULL)
    {
        aiReleaseImport(scene);
        scene = NULL;
    }

    scene = aiImportFile(path.c_str(),IFlags);
    if(scene == NULL)
    {
        return false;
    }

    sceneToVertlist();
    return true;

}

bool MODEL::loadEmptyModel()
{
    if(scene != NULL)
    {
        aiReleaseImport(scene);
    }
    
    scene = new aiScene();
    return true;
}

void MODEL::sceneToVertlist()
{
     if(scene->HasMeshes())
     {
         //pre alocate vector size to be number mesh * num face * 3 or total number faces * 3
         //vertlist.reserve();
         glm::vec3 point1, point2, point3;
        for (size_t i = 0; i < scene->mNumMeshes; i++)
        {
            for (size_t j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
            {
                point1.x = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[0])].x;
                point1.y = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[0])].y;
                point1.z = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[0])].z;
                

                point2.x = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[1])].x;
                point2.y = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[1])].y;
                point2.z = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[1])].z;

                point3.x = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[2])].x;
                point3.y = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[2])].y;
                point3.z = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[2])].z;
                
                vertlist.push_back(point1);
                vertlist.push_back(point2);
                vertlist.push_back(point3);
            }
        }
     }
}

bool MODEL::saveModel(std::string path)
{
    if(scene == NULL)
    {
        std::cout << "scene is null" << std::endl;
        return false;
    }
    if((aiExportScene(scene,"ply",path.c_str(),EFlags) & aiReturn_FAILURE) == aiReturn_FAILURE)
    {
        std::cout << "ai export is null" << std::endl;
        return false;
    }
    return true;
}

bool MODEL::formatSupported(std::string format) // can be made static
{
    size_t exportFormats = aiGetExportFormatCount();// number of supported export formats
    std::cout << exportFormats << std::endl;

    for (size_t i = 0; i < exportFormats; i++)
    {
        const aiExportFormatDesc *exportFormatsDesc;
        exportFormatsDesc = aiGetExportFormatDescription(i);//gets description of what format

        if (exportFormatsDesc == NULL)
        {
        std::cout << "ERROR:no export format\n";
        return false;
        }

        std::cout << i << " " <<exportFormatsDesc->description <<" ID: " <<exportFormatsDesc->id <<  '\n';
    }

    return true;
}

bool MODEL::render(glm::mat4 View,glm::mat4 Projection,struct ENGINEDATA &gamedata)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //add error checking

    glBindVertexArray(gamedata.vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer);

    //assumed that it is tryangles do this for every mesh


    glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertlist.size(),&vertlist[0],GL_DYNAMIC_DRAW);//change to assimp

    //glBindBuffer(GL_ARRAY_BUFFER,colorBuffer);
	//glBufferData(GL_ARRAY_BUFFER,sizeof(g_color_buffer_data),g_color_buffer_data,GL_DYNAMIC_DRAW);

    glUseProgram(gamedata.activeProgram); // grab that

    glm::mat4 MVP = gamedata.Projection * gamedata.View * ModelMatrix;// makes mvp based of model
    glUniformMatrix4fv(gamedata.MatrixID, 1, GL_FALSE,&MVP[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );

    glDrawArrays(GL_TRIANGLES,0,vertlist.size());
    
    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

    return true;
}

std::string MODEL::getFilePath()
{
    if(!filePath.empty())
    {
        return filePath;
    }
    else
    {
        return filePath;
    }
}

void MODEL::transform(glm::vec4 transform)
{
    //ModelMatrix = ModelMatrix * transform;
}