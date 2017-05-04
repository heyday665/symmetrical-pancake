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

#define ScreenWidth 1920
#define ScreenHeight 1080
#define waitTime 6000 //time between patch redrawings
#define FIXEDSTEP 1 //0 for non fixed step 1 for fixed
#define LINEDOT 1 //0 for dot 1 for line
#define STEP .5 //step size .2
#define NUMBERBEZ 1 //number of patches
typedef struct{
	float x ,y ,z;

}points;

points bez[4][4];

void setRand();

void setPoints();

void drawPatch();

void display(SDL_Window *winLoc);
