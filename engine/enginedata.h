#ifndef ENGINEDATA_H
#define ENGINEDATA_H

#include <string>
#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "settings.h"
//#include "modelreader.h"
#include "model.h"

/*struct SCENEDATA
{
  struct ply *ply_model1;
  struct newply newply_model1;
  MODEL testmodel;
};*/

struct ENGINEDATA
{
  SDL_mutex *mutex;

  SETTINGS_DATA settings;

  int running;

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_GLContext context;

  std::vector<MODEL*> scene1;

  GLuint activeProgram; //active glsl linked program
  GLuint vertexArrayID; //where everything is stored
  GLuint MatrixID;
  glm::mat4 Projection;
	glm::mat4 View;
};

//add one for scenes, gldata and for models
#endif