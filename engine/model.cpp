#include <vector>
#include <map>
#include <iostream>
#include <fstream>

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
    //glGenBuffers(1,&vertexBuffer);
    //glGenBuffers(1,&colorBuffer);
    ModelMatrix = glm::mat4(1.0f);
    bezList.setRand();
    updatePatch(NULL);
    bezPath = std::string("bezOut.ply");
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

    scene = aiImportFile(path.c_str(), IFlags);
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
    if((aiExportScene(scene,"ply", path.c_str(), EFlags) & aiReturn_FAILURE) == aiReturn_FAILURE)
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

void MODEL::updatePatch(float stepsize)
{
    if (stepsize != NULL)
    {
        bezList.setStep(stepsize);
    }
    bezList.genControlPoints();
    bezList.genPatchPoints();
    numStepPoints = bezList.getNumStepPoints();
}

bool MODEL::render(glm::mat4 View, glm::mat4 Projection, struct ENGINEDATA &gamedata)
{
    glm::vec3** list = bezList.getStepPoints();
    fuckingBezShit = bezList.getBez();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < numStepPoints; i++)
    {
        for (int j = 0; j < numStepPoints; j++)
        {
            if (!i ==  0)//do draw left 
            {
                glVertex3f(list[i][j].x, list[i][j].y, list[i][j].z);
                glVertex3f(list[i-1][j].x, list[i-1][j].y, list[i-1][j].z);
                //glVertex3f(stepPoints[row][col-1].x,stepPoints[row][col-1].y,stepPoints[row][col-1].z);
            }
            
            if (!j == 0)//do draw up
            {
                glVertex3f(list[i][j].x, list[i][j].y, list[i][j].z);
                glVertex3f(list[i][j-1].x, list[i][j-1].y, list[i][j-1].z);
                //glVertex3f(stepPoints[row-1][col].x,stepPoints[row-1][col].y,stepPoints[row-1][col].z);
            }
        }
    }
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(10.0f);
    glBegin(GL_POINTS);

        for (int ix = 0; ix < 4; ix++){
            for (int iy = 0; iy < 4; iy++){
                glVertex3f(fuckingBezShit[ix][iy][0], fuckingBezShit[ix][iy][1], fuckingBezShit[ix][iy][2]);
            }
        }
    glEnd();

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

void MODEL::bezToPly()
{
	ofstream btp;
	char c;
	std::string x, y, z;
	int t = (numStepPoints * numStepPoints);
	int tx = ( (numStepPoints - 1) * (numStepPoints - 1) );
	glm::vec3** verts = bezList.getStepPoints();
	btp.open (bezPath, ios::out | ios::trunc);
	btp << "ply" << std::endl;
	btp << "format ascii 1.0" << std::endl;
	btp << "comment This is the Bez Array formatted to look like a .ply file" << std::endl;
	c = '0' + t;
	btp << "element vertex " << c << std::endl;
	btp << "property float x" << std::endl;
	btp << "property float y" << std::endl;
	btp << "property float z" << std::endl;
	c = '0' + tx;
	//btp << "element face " << c << std::endl;
	//btp << "property list uchar int vertex_index" << std::endl;
	btp << "end_header" << std::endl;
	
	for (int i = 0; i < numStepPoints; i++)
	{
		for (int j = 0; j < numStepPoints; j++)
		{
			x = std::to_string(verts[i][j].x);
			y = std::to_string(verts[i][j].y);
			z = std::to_string(verts[i][j].z);
			btp << x << " " << y << " " << z << endl;
			
		}
	}
	
	btp.close();
}

std::string MODEL::getBezPath()
{
	return bezPath;
}

void MODEL::setBezPath(std::string s)
{
	bezPath = s;
}








