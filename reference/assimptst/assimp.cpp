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
  //Assimp::Importer importer;//importer.ReadFile("boxy2.ply",aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

  scene = aiImportFile("Armadillo.ply",aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);//imports file by name with proceesses anded
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

  printf("%u meshes\n",scene->mNumMeshes);

  printf("%u materials\n",scene->mNumMaterials);

  for (size_t i = 0; i < scene->mNumMaterials; i++)
  {
    printf("%u textruees\n", scene->mMaterials[i]->GetTextureCount((aiTextureType)1));
  }

  for (size_t i = 0; i < scene->mNumMeshes; i++)
  {
    printf("verticies %u\n", scene->mMeshes[i]->mNumVertices);
    printf("faces %u\n",scene->mMeshes[i]->mNumFaces);
  }

  for (size_t i = 0; i < scene->mNumMeshes; i++)
  {
    for (size_t j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
    {
      float x = scene->mMeshes[i]->mFaces[j].mIndices[0];
      float y = scene->mMeshes[i]->mFaces[j].mIndices[1];
      float z = scene->mMeshes[i]->mFaces[j].mIndices[2];
      //printf("points x:%f,y:%f,z:%f\n", x,y,z);
    }
  }

  size_t exportFormats = aiGetExportFormatCount();// number of supported export formats
  std::cout << exportFormats << std::endl;

  for (size_t i = 0; i < exportFormats; i++)
  {
    const aiExportFormatDesc *exportFormatsDesc;
    exportFormatsDesc = aiGetExportFormatDescription(i);//gets description of what format

    if (exportFormatsDesc == NULL)
    {
      printf("ERROR:no export format\n");
      exit(-1);
    }

    std::cout << i << " " <<exportFormatsDesc->description <<" ID: " <<exportFormatsDesc->id <<  '\n';
}

  aiExportScene(scene,"ply","Testexp.ply",aiProcess_SplitLargeMeshes);

  aiReleaseImport(scene); //for c
  //aiDetachAllLogStreams(); //for c

}