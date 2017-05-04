#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>

#include <SDL2/SDL.h>


class KEYBOARD
{
	public:
			KEYBOARD();
			~KEYBOARD();
			bool isdown(SDL_Scancode);
			void start();
	private:
			int grabkeys();
			static int thread_func_wrapper(void* data);
			std::map<SDL_Scancode,bool> keydown;
			SDL_Thread *thread;
			SDL_mutex *mutex;
};

static KEYBOARD keyboard;

#endif