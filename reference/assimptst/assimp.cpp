#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <iostream>
#include <map>

#include <assimp/cimport.h> //for c
#include <assimp/Importer.hpp> //for c++
#include <assimp/cexport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



const struct aiScene *scene = NULL;

int main()
{
  //Assimp::Importer importer; //importer.ReadFile("boxy2.ply", aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

  scene = aiImportFile("boxy2.ply", aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices); //imports file by name with processes anded
  if (scene == NULL)
  {
    printf("ERROR: file not read\n");
    exit(-1);
  }

  if(!(scene->HasMeshes()))
	{
		printf("error: scene has no meshes\n");
		return -1;
	}

  printf("%u meshes\n", scene->mNumMeshes);

  printf("%u materials\n", scene->mNumMaterials);

  for (size_t i = 0; i < scene->mNumMaterials; i++)
  {
    printf("%u textures\n", scene->mMaterials[i]->GetTextureCount((aiTextureType)1));
  }

  for (size_t i = 0; i < scene->mNumMeshes; i++)
  {
    printf("vertices %u\n", scene->mMeshes[i]->mNumVertices);
    printf("faces %u\n", scene->mMeshes[i]->mNumFaces);
  }

	float testNum = 69.000000;
  for (size_t i = 0; i < scene->mNumMeshes; i++)
  {
    for (size_t j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
    {
      float x = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[0])].x;
      float y = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[0])].y;
      float z = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[0])].z;
      printf("points x:%f,y:%f,z:%f\n", x,y,z);

      x = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[1])].x;
      y = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[1])].y;
      z = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[1])].z;
      printf("points x:%f,y:%f,z:%f\n", x,y,z);

      x = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[2])].x;
      y = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[2])].y;
      z = scene->mMeshes[i]->mVertices[(scene->mMeshes[i]->mFaces[j].mIndices[2])].z;
      printf("points x:%f,y:%f,z:%f\n", x,y,z);
    	
      //if ((i == 0) && (j == 0)) scene->mMeshes[i]->mFaces[j].mIndices[0] = testNum;
      
      //scene->mMeshes[i]->mFaces[j].mIndices[0] = testNum;
      
      float x = scene->mMeshes[i]->mFaces[j].mIndices[0];
      float y = scene->mMeshes[i]->mFaces[j].mIndices[1];
      float z = scene->mMeshes[i]->mFaces[j].mIndices[2];
      printf("points x:%f, y:%f, z:%f\n", x, y, z);
    }
  }

  size_t exportFormats = aiGetExportFormatCount(); //number of supported export formats
  //std::cout << exportFormats << std::endl;

  for (size_t i = 0; i < exportFormats; i++)
  {
    const aiExportFormatDesc *exportFormatsDesc;
    exportFormatsDesc = aiGetExportFormatDescription(i); //gets description of what format

    if (exportFormatsDesc == NULL)
    {
      printf("ERROR:no export format\n");
      exit(-1);
    }

    //std::cout << i << " " << exportFormatsDesc->description <<" ID: " << exportFormatsDesc->id <<  '\n';
	}

  aiExportScene (scene, "ply", "Testexp.ply", aiProcess_SplitLargeMeshes);

  const struct aiScene *scene2 = new aiScene();
  std::cout << scene2->HasMeshes() << std::endl;


  aiReleaseImport (scene); //for c
  //aiDetachAllLogStreams(); //for c

}
