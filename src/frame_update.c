#include "TGJGE.h"

extern SDL_Window *TG_main_window;
extern const Uint8 *TG_keyboard_state;
extern SDL_Event TG_event;


extern unsigned int TG_desired_frametime;
extern unsigned int TG_last_frametime;
extern unsigned int TG_current_frametime;
extern unsigned int TG_delta_frametime;

//takes in the clear color as a parameter
void TG_new_frame(float r, float g, float b)
{
    //setting up new frametime
    TG_last_frametime=TG_current_frametime;
    TG_current_frametime=SDL_GetTicks();
    TG_delta_frametime=TG_current_frametime-TG_last_frametime;
    if(TG_delta_frametime<TG_desired_frametime)
    {
        SDL_Delay(TG_desired_frametime-TG_delta_frametime);
        TG_current_frametime=SDL_GetTicks();
        TG_delta_frametime=TG_current_frametime-TG_last_frametime;
    }
    //printf("frametime: %u ms\n", TG_delta_frametime);

    //checking the keyboard state to get the latest input
    while(SDL_PollEvent(&TG_event))
    {
    };
    TG_keyboard_state=SDL_GetKeyboardState(NULL);

    //drawing
    SDL_GL_SwapWindow(TG_main_window);
    glClearColor(r,g,b,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}