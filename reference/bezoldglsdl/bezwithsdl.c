#include"all.h"

void signal_callback_handler(int signum)
{
   printf("Caught signal %d\n",signum);
   exit(signum);
}


int main(int argc, char **argv)
{
	signal(SIGINT, signal_callback_handler);

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR-init",SDL_GetError(),NULL);
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Window *window;
	SDL_GLContext context;

	window = SDL_CreateWindow("glPlz",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,ScreenWidth,ScreenHeight,SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

	if(window == NULL){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR-window",SDL_GetError(),NULL);
		return 1;
	}

	context = SDL_GL_CreateContext(window);

	if(context == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR-context",SDL_GetError(),NULL);
		return 1;
	}

	SDL_GL_MakeCurrent(window,context);

	if(SDL_GL_SetSwapInterval(1) != 0){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,"ERROR-interval",SDL_GetError(),NULL);
		return 1;
	}

	 //SDL_ShowCursor(SDL_DISABLE);

	while(1)
	{
		SDL_PumpEvents();
		display(window);
	}

	SDL_GL_DeleteContext(context);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}

	void display(SDL_Window *winLoc)
	{

		drawPatch();

		SDL_GL_SwapWindow(winLoc);

		SDL_Delay(waitTime);

	}
