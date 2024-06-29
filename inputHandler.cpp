#include "inputHandler.hpp"
#include <SDL2/SDL.h>
#include <iostream>

void InputHandler::checkUserInput(emulator_state_t& state){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
            state = QUIT;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                state = QUIT;
                break;
            case SDLK_SPACE:
                if(state == RUNNING){
                    state = PAUSED;
                    std::cout<<"Pausing emulation"<<std::endl;
                }
                else{
                    state = RUNNING;
                    std::cout<<"Resuming emulation"<<std::endl;
                }
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}