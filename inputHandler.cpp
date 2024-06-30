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
                case SDLK_x: memory->keys[0] = 1; break;
                case SDLK_1: memory->keys[1] = 1; break;
                case SDLK_2: memory->keys[2] = 1; break;
                case SDLK_3: memory->keys[3] = 1; break;
                case SDLK_q: memory->keys[4] = 1; break;
                case SDLK_w: memory->keys[5] = 1; break;
                case SDLK_e: memory->keys[6] = 1; break;
                case SDLK_a: memory->keys[7] = 1; break;
                case SDLK_s: memory->keys[8] = 1; break;
                case SDLK_d: memory->keys[9] = 1; break;
                case SDLK_z: memory->keys[0xA] = 1; break;
                case SDLK_c: memory->keys[0xB] = 1; break;
                case SDLK_4: memory->keys[0xC] = 1; break;
                case SDLK_r: memory->keys[0xD] = 1; break;
                case SDLK_f: memory->keys[0xE] = 1; break;
                case SDLK_v: memory->keys[0xF] = 1; break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                    case SDLK_x: memory->keys[0] = 0; break;
                    case SDLK_1: memory->keys[1] = 0; break;
                    case SDLK_2: memory->keys[2] = 0; break;
                    case SDLK_3: memory->keys[3] = 0; break;
                    case SDLK_q: memory->keys[4] = 0; break;
                    case SDLK_w: memory->keys[5] = 0; break;
                    case SDLK_e: memory->keys[6] = 0; break;
                    case SDLK_a: memory->keys[7] = 0; break;
                    case SDLK_s: memory->keys[8] = 0; break;
                    case SDLK_d: memory->keys[9] = 0; break;
                    case SDLK_z: memory->keys[0xA] = 0; break;
                    case SDLK_c: memory->keys[0xB] = 0; break;
                    case SDLK_4: memory->keys[0xC] = 0; break;
                    case SDLK_r: memory->keys[0xD] = 0; break;
                    case SDLK_f: memory->keys[0xE] = 0; break;
                    case SDLK_v: memory->keys[0xF] = 0; break;
                    default:
                        break;
                    }
                    break;
            default:
                break;
            }
    }
}