#include <stdlib.h>//c
#include <stdio.h>

#include <string>//c++
#include <iostream>
#include <fstream>//for shaders
#include <vector>

#include <glm/glm.hpp>//libraries
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "model.h"
#include "enginedata.h"
#include "settings.h"
#include "modelreader.h"
#include "keyboard.h"
#include "mouse.h"

int init_GLEW()
{
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    printf("GLEW ERROR: %s\n",glewGetErrorString(err));
    return -1;
  }

  return 1;
}

int init_SDL(struct ENGINEDATA &gamedata)
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR-init",SDL_GetError(),NULL);
    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );

  /*int nmaj = 0,nmin = 0, depth = 0;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,&nmaj);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,&nmin);
	SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE,&depth);
  printf("major:%d min:%d, depth:%d\n",nmaj,nmin,depth);*/

  gamedata.window = SDL_CreateWindow(gamedata.settings.windowName->c_str(),SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,gamedata.settings.screenWidth,gamedata.settings.screenHeight,SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

  if(gamedata.window == NULL)
  {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR-window",SDL_GetError(),NULL);
		return -1;
	}

  gamedata.context = SDL_GL_CreateContext(gamedata.window);

  if(gamedata.context == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR-window",SDL_GetError(),NULL);
		return -1;
	}

	gamedata.renderer = SDL_CreateRenderer(gamedata.window, -1, SDL_RENDERER_ACCELERATED);

	if (SDL_GL_SetSwapInterval(-1) == -1)
  {
    printf("%s\n", SDL_GetError());
    SDL_GL_SetSwapInterval(1);
  }

}

int init_1(struct ENGINEDATA &gamedata)
{//settings, SDL2 full glew
  gamedata.settings = gamesettings.currentSettings();

  if(init_SDL(gamedata) < 0)
  {
    printf("SDL ERROR\n");
    return -1;
  }

  if(init_GLEW() < 0)
  {
    printf("glew ERROR\n");
    return -1;
  }

  gamedata.mutex = SDL_CreateMutex();

  return 1; 
}//add error handleing

int init_model(struct ENGINEDATA &gamedata)
{
  if(!gamedata.settings.plyName->empty())
  {
    MODEL *newModel = new MODEL();

    if(!newModel->loadModel(std::string(gamedata.settings.plyName->c_str())))
    { // cant find a good way to convert from string* to string
      delete newModel; // clean up memory if it dosent load
      return -1;
    }

    gamedata.scene1.push_back(newModel); // will need to be deleted the destructer will not be auto called unless you cast it as  EX:std::unique_ptr <Foo> leedle = std::make_unique <Foo> ();
    return 0;
  }
  else
  {
     MODEL *newModel = new MODEL();

    if(!newModel->loadEmptyModel())
    {
      delete newModel; // clean up memory if it dosent load
      return -1;
    }

    gamedata.scene1.push_back(newModel); // will need to be deleted the destructer will not be auto called unless you cast it as  EX:std::unique_ptr <Foo> leedle = std::make_unique <Foo> ();
    return 0;    
  }

}

int init_GL(struct ENGINEDATA &gamedata)
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc( GL_LEQUAL );

  char *nameFS = strdup("default.fs");
  char *nameVS = strdup("default.vs");
  std::string vertexCode;
  std::ifstream vertexCodeStream(nameVS);
  if (vertexCodeStream.fail())
  {
    return -1;
  }
  std::string Line = "";
  while (getline(vertexCodeStream,Line))
  {
    vertexCode += "\n" + Line;
  }
  vertexCodeStream.close();

  std::string fragmentCode;
  std::ifstream fragmentCodeStream(nameFS);
  if (fragmentCodeStream.fail())
  {
    return -1;
  }

  Line = "";

  while (getline(fragmentCodeStream,Line))
  {
    fragmentCode += "\n" + Line;
  }
  fragmentCodeStream.close();

  GLuint defaultVSID = glCreateShader(GL_VERTEX_SHADER);
  GLuint defaultFSID = glCreateShader(GL_FRAGMENT_SHADER);

  char const * VertexSourcePointer = vertexCode.c_str();
  char const * FragmentSourcePointer = fragmentCode.c_str();

  glShaderSource(defaultVSID, 1, &VertexSourcePointer , NULL);
  glShaderSource(defaultFSID, 1, &FragmentSourcePointer , NULL);
  glCompileShader(defaultVSID);
  glCompileShader(defaultFSID);

  GLint Result = GL_FALSE;
  int InfoLogLength;
  // Check Vertex Shader
	glGetShaderiv(defaultVSID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(defaultVSID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0  && Result == GL_FALSE)
  {
		std::vector<char> ShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(defaultVSID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
    return -1;
	}

  Result = GL_FALSE;
  InfoLogLength = 0;
  // Check Vertex Shader
	glGetShaderiv(defaultFSID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(defaultFSID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0  && Result == GL_FALSE)
  {
		std::vector<char> ShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(defaultFSID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
    return -1;
	}

  GLuint ProgramID = glCreateProgram();
  glAttachShader(ProgramID, defaultVSID);
	glAttachShader(ProgramID, defaultFSID);
	glLinkProgram(ProgramID);


  Result = GL_FALSE;
  InfoLogLength = 0;
  // Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 && Result == GL_FALSE)
  {
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
    return -1;
	}

  gamedata.activeProgram = ProgramID;
	//move to after shaders
  gamedata.MatrixID = glGetUniformLocation(ProgramID, "MVP");

  float ratio = (float) gamedata.settings.screenWidth;
  ratio = ratio/gamedata.settings.screenHeight;

  gamedata.Projection = glm::perspective(45.0f,ratio,0.001f,100.0f);

  gamedata.View = glm::lookAt(
                glm::vec3(4,3,3),
                glm::vec3(0,0,0),
                glm::vec3(0,1,0)
  );

  //gamedata.scene1.newply_model1.MVP = gamedata.scene1.newply_model1.Projection * gamedata.scene1.newply_model1.View * gamedata.scene1.newply_model1.Model;

  glDetachShader(ProgramID, defaultVSID);
	glDetachShader(ProgramID, defaultFSID);

	glDeleteShader(defaultFSID);
	glDeleteShader(defaultVSID);

  return 1;
}

int init_2(struct ENGINEDATA &gamedata)
{//model gl
  if(init_model(gamedata) < 0)
  {
    return -1;
  }

  if(init_GL(gamedata) < 0)
  {
    return -1;
  }

  return 1;
}

int init_3(struct ENGINEDATA &gamedata)
{// keyboard
  keyboard.start();
}

/*----------------------------------------------------------------------------*/

int renderloop(struct ENGINEDATA &gamedata)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0f,0.5f,0.5f,1.0f);

  int i;
  for(i = 0;i< gamedata.scene1.size();i++)
  {
    gamedata.scene1[i]->render(gamedata.View,gamedata.Projection,gamedata);
  }

  SDL_GL_SwapWindow(gamedata.window);

}

int userInputloop(struct ENGINEDATA &gamedata)
{
  if (keyboard.isdown(SDL_SCANCODE_ESCAPE))
  {
    gamedata.running = 0;
  }
}

int mainloop(struct ENGINEDATA &gamedata)
{
  gamedata.running = 1;
  while(gamedata.running)
  {//add mutex use
    renderloop(gamedata);
    userInputloop(gamedata);
    //int ret = glGetError();
    //if(ret)
    //{
    //  std::cout << ret << std::endl;
    //  std::cout << gluErrorString(ret) << std::endl;
    //}
    //SDL_Delay(150);
  }
}

int main(int argc, char **argv)
{
  //parse file settings first
  gamesettings.parseCommandLine(argc,argv);
  struct ENGINEDATA gamedata;//init enginedata to defaults
  
  if(init_1(gamedata) < 0)
  {
    std::cout << "error in init_1" << std::endl;
    exit(-1);
  }
 
  if(init_2(gamedata) < 0)
  {
    std::cout << "error in init_2" << std::endl;
    exit(-1);
  }

  if(init_3(gamedata) < 0)
  {
    std::cout << "error in init_3" << std::endl;
    exit(-1);
  }

  glGenVertexArrays(1, &gamedata.vertexArrayID);
  //start game loop
  mainloop(gamedata);

  glDeleteVertexArrays(1, &gamedata.vertexArrayID);

  return 0;
}
