/*
Dylan Gebel

Displaying beziare curves using gl fixed pipeline and sdl

leavin for now as i want to learn some more before coming back
*/
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <math.h>
#include <signal.h>

#define ScreenWidth 1280
#define ScreenHeight 720
#define waitTime 6000
#define FIXEDSTEP 1
#define LINEDOT 1 //0 for dot 1 for line
#define STEP .02
#define NUMBERBEZ 1
typedef struct{
	float x ,y ,z;

}points;

points bez[4][4];

void setRand();

void setPoints();

void drawPatch();

void display(SDL_Window *winLoc);
