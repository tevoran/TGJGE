#include "TGJGE.h"

extern SDL_Window *TG_main_window;

//takes in the clear color as a parameter
void TG_flip(float r, float g, float b)
{
    glClearColor(r,g,b,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(TG_main_window);
}