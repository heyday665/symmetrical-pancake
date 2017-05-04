#ifndef MOUSE_H
#define MOUSE_H

#include<SDL2/SDL.h>

struct MOUSEPOSITION
{
    int x,y;
};

class MOUSE
{
    public:
        MOUSE();
        ~MOUSE();
        struct MOUSEPOSITION mousePosScreen();
        struct MOUSEPOSITION mousePosDisplay();
        bool mouseDown(int);
        void start();
    private:

};

static MOUSE mouse;
#endif