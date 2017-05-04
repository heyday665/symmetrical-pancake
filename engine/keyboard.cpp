#include <iostream>

#include <SDL2/SDL.h>

#include "keyboard.h"

KEYBOARD::KEYBOARD()
{
	mutex = SDL_CreateMutex();//could change to a map of keys so only the key is stoped not the whole map

	keydown[SDL_SCANCODE_ESCAPE] = false;
	keydown[SDL_SCANCODE_RIGHT] = false;
	keydown[SDL_SCANCODE_RETURN] = false;
	keydown[SDL_SCANCODE_UP] = false;
	keydown[SDL_SCANCODE_LEFT] = false;
	keydown[SDL_SCANCODE_DOWN] = false;
	keydown[SDL_SCANCODE_Q] = false;
	keydown[SDL_SCANCODE_E] = false;
	//keydown[] = false;
	//keydown[] = false;
	//keydown[] = false;
}

KEYBOARD::~KEYBOARD()
{
  SDL_DestroyMutex(mutex);
}

int KEYBOARD::thread_func_wrapper(void* data)
{
  KEYBOARD* self = static_cast<KEYBOARD*>(data);
  return self->grabkeys();
}

int KEYBOARD::grabkeys()
{
  while (true)
  {
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
      if (SDL_LockMutex(mutex) == 0)
      {
        switch(e.type)
        {
				      case SDL_KEYDOWN:
					         keydown[e.key.keysym.scancode] = true;
					              break;
				      case SDL_KEYUP:
					         keydown[e.key.keysym.scancode] = false;
					              break;
			}
        SDL_UnlockMutex(mutex);
      }
      else
      {
        fprintf(stderr, "Couldn't lock mutex\n");
      }
      SDL_Delay(10);
    }
  }

}

bool KEYBOARD::isdown(SDL_Scancode code)
{
  if (SDL_LockMutex(mutex) == 0)
  {
    bool tmp = keydown[code];
    SDL_UnlockMutex(mutex);
    return tmp;
  }
  else
  {
    fprintf(stderr, "Couldn't lock mutex\n");
    return false;
  }
}

void KEYBOARD::start()
{

  thread = SDL_CreateThread(thread_func_wrapper,"grabkeys",this);

}
