#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<argp.h>
#include<argz.h>

#include "settings.h"

#define SCREENWIDTH 640 //min width
#define SCREENHEIGHT 480 //min height

struct SETTINGS_DATA SETTINGS::Statsettings;

const char *argp_program_version = "Version 1.0";


SETTINGS::SETTINGS()
{
  SETTINGS::Statsettings.screenWidth = SCREENWIDTH;
  SETTINGS::Statsettings.screenHeight = SCREENHEIGHT;
  SETTINGS::Statsettings.windowName = new std::string("SDL_Window");
  SETTINGS::Statsettings.plyName = new std::string();
  SETTINGS::Statsettings.stepSize = NULL;
}

struct SETTINGS_DATA SETTINGS::currentSettings()
{
  return SETTINGS::Statsettings;
}

void SETTINGS::parseCommandLine(int argc,char** argv)
{
  struct argp_option options[] =
	{
		{"screenWidth",'w',"number",0,"Set screen width."},
    {"screenHeight",'h',"number",0,"Set screen height."},
    {"windowName",'n',"string",0,"Set window name."},
    {"plyName",'p',"file",0,"Name of ply file to load."},
    {"stepSize",'s',"FLOAT",0,"size of the step for patch"},
    {0}
	};

  struct argp argp = {options,parse_opt};  /////////
	argp_parse(&argp,argc,argv,0,0,0);
}

int SETTINGS::parse_opt(int key, char *arg, struct argp_state *state)
{
	switch(key)
	{
		case 'w':
      int width; width = atoi(arg);
      if (width < SCREENWIDTH) width=SCREENWIDTH;
      SETTINGS::Statsettings.screenWidth = width;

      break;
    case 'h':
      int height; height = atoi(arg);
      if(height < SCREENHEIGHT) height=SCREENHEIGHT;
      SETTINGS::Statsettings.screenHeight = height;
      break;
    case 'n':
      delete Statsettings.windowName;
      SETTINGS::Statsettings.windowName = new std::string(arg);
      break;
    case 'p':
      delete Statsettings.plyName; // change to model path and make vector
      SETTINGS::Statsettings.windowName = new std::string(arg);// change this to a vector 
      break;
    case 's':
      SETTINGS::Statsettings.stepSize = atof(arg);
	}
	return 0;
}
/*priority level:(highest) command line, file*/
void SETTINGS::parseSettingsFile(std::string Fname)
{
  printf("test\n");
}
