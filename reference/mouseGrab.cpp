#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>

#define ScreenWidth 1280
#define ScreenHeight 720

using namespace std;

//Compile with: g++ -o mouseGrab mouseGrab.cpp -lm -lSDL2 -lGL

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR-init",SDL_GetError(),NULL);
		return 1;
	}
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);	

	SDL_Window *window;
	SDL_GLContext context;

	window = SDL_CreateWindow("glPlz", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

	if (window == NULL) 
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR-window", SDL_GetError(), NULL);
		return 1;	
	}

	context = SDL_GL_CreateContext(window);

	if (context == NULL) 
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR-context", SDL_GetError(), NULL);
		return 1;
	}

	SDL_GL_MakeCurrent(window, context);

	if (SDL_GL_SetSwapInterval(1) != 0) 
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR-interval", SDL_GetError(), NULL);
		return 1;	
	}

	int x, y, t = 0;
	while(1) 
	{
		SDL_PumpEvents();
		if (SDL_GetMouseState(&x, &y) && SDL_BUTTON(SDL_BUTTON_LEFT)) 
		{
    		cout << "Mouse is at x=" << x << " and y=" << y << endl;
		}
		
	}

	SDL_GL_DeleteContext(context);

	SDL_DestroyWindow(window);
	
	SDL_Quit();

	return 0;
}
