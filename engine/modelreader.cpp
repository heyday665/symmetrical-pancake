#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "modelreader.h"

int MODELREADER::readinply(std::string FileN,std::vector<glm::vec3> &forgl)
{
  std::ifstream fs(FileN.c_str());

  if (fs.fail())
  {
    return -1;
  }

  int Nvertes,Nfaces;

  for(std::string line;getline(fs,line);)
  {
    if (strstr(line.c_str(),"element vertex"))
    {
      line = line.substr(15);
      Nvertes = atoi(line.c_str());
    }
    else if (strstr(line.c_str(),"element face"))
    {
      line = line.substr(13);
      Nfaces = atoi(line.c_str());
    }
    else if (strstr(line.c_str(),"end_header"))
    {
      break;
    }
  }

  glm::vec3 vertlist[Nvertes];
  triangleFace facelist[Nfaces];

  for (size_t i = 0; i < Nvertes; i++)
  {
    std::string line;
    std::getline(fs,line);
    std::istringstream in(line);

    in >> vertlist[i].x >> vertlist[i].y >> vertlist[i].z;
  }

  for (size_t i = 0; i < Nfaces; i++)
  {
    std::string line;
    std::getline(fs,line);
    std::istringstream in(line);
    int num;
    in >> num >> facelist[i].a >> facelist[i].s >> facelist[i].d;
  }

  fs.close();

  for (size_t i = 0; i < Nfaces; i++)
  {
    forgl.push_back(vertlist[facelist[i].a]);
    forgl.push_back(vertlist[facelist[i].s]);
    forgl.push_back(vertlist[facelist[i].d]);
  }

  return 1;
}

int MODELREADER::readinply(struct ply *model)
{
  std::ifstream fs(model->FileN);
  if (fs.fail())
  {
    return -1;
  }

  for(std::string line;getline(fs,line);)
  {
    if (strstr(line.c_str(),"element vertex"))
    {
      line = line.substr(15);
      model->Nvertes = atoi(line.c_str());
    }
    else if (strstr(line.c_str(),"element face"))
    {
      line = line.substr(13);
      model->Nfaces = atoi(line.c_str());
    }
    else if (strstr(line.c_str(),"end_header"))
    {
      break;
    }
  }

  model->vertlist = (glm::vec3 *) calloc(model->Nvertes,sizeof(glm::vec3));
  model->facelist = (triangleFace *) calloc(model->Nfaces,sizeof(triangleFace));

  for (size_t i = 0; i < model->Nvertes; i++)
  {
    std::string line;
    std::getline(fs,line);
    std::istringstream in(line);

    in >> model->vertlist[i].x >> model->vertlist[i].y >> model->vertlist[i].z;
  }

  for (size_t i = 0; i < model->Nfaces; i++)
  {
      std::string line;
      std::getline(fs,line);
      std::istringstream in(line);
      int num;
      in >> num >> model->facelist[i].a >> model->facelist[i].s >> model->facelist[i].d;
  }

  fs.close();

  return 1;
}

int MODELREADER::plyToGlData(struct ply *model, std::vector<glm::vec3> &forgl)
{//oeganizes in proper triangles

  for (size_t i = 0; i < model->Nfaces; i++)
  {
    forgl.push_back(model->vertlist[model->facelist[i].a]);
    forgl.push_back(model->vertlist[model->facelist[i].s]);
    forgl.push_back(model->vertlist[model->facelist[i].d]);
  }

  return 1;
}

int MODELREADER::normalizeModel(struct ply *model)
{
  float lowest, highest;

  lowest = model->vertlist[0].x;
  highest = lowest;

  for (size_t i = 0; i < model->Nvertes; i++)
  {
    if (model->vertlist[i].x > highest)
    {
      highest = model->vertlist[i].x;
    }
    else if(model->vertlist[i].x < lowest)
    {
      lowest = model->vertlist[i].x;
    }

    if (model->vertlist[i].y > highest)
    {
      highest = model->vertlist[i].y;
    }
    else if(model->vertlist[i].y < lowest)
    {
      lowest = model->vertlist[i].z;
    }

    if (model->vertlist[i].z > highest)
    {
      highest = model->vertlist[i].z;
    }
    else if(model->vertlist[i].z < lowest)
    {
      lowest = model->vertlist[i].z;
    }
  }

  float diff = (highest - lowest)*.5;
  lowest = (lowest / diff)+1;

  for (size_t i = 0; i < model->Nvertes; i++)
  {
    model->vertlist[i].x = (model->vertlist[i].x / diff) - lowest;
    model->vertlist[i].y = (model->vertlist[i].y / diff) - lowest;
    model->vertlist[i].z = (model->vertlist[i].z / diff) - lowest;
  }

  return 1;
}
