#include "mouse.h"

MOUSE::MOUSE()
{

}

MOUSE::~MOUSE()
{

}

struct MOUSEPOSITION MOUSE::mousePosDisplay()
{
    struct MOUSEPOSITION mousePos;
    SDL_GetMouseState(&mousePos.x,&mousePos.y);
    return mousePos;

}

struct MOUSEPOSITION MOUSE::mousePosScreen()
{
    struct MOUSEPOSITION mousePos;
    SDL_GetMouseState(&mousePos.x,&mousePos.y);
    return mousePos;
}

/*- Button 1:  Left mouse button
 *- Button 2:  Middle mouse button
 *- Button 3:  Right mouse button
*/
bool MOUSE::mouseDown(int button)
{
    return SDL_BUTTON(button);
}