#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include <SDL2/SDL.h>
#include <vector>
#include "memory.hpp"

class Display{
    private:
        SDL_Window* window;
        SDL_Renderer* sdlRenderer;
        Memory *memory;
        int width = screen_width;
        int height = screen_height;
        int delayInMs = refreshRateInMs; // Pause execution for 16 ms / 60hz / 60fps, 16.67 is exact
        void initializeDisplay();
    public:
        Display(Memory* _memory):memory(_memory){
            initializeDisplay();
        }
        ~Display(){
            SDL_DestroyRenderer(sdlRenderer);
            SDL_DestroyWindow(window); 
            SDL_Quit(); 
        };
        void renderScreen();
        void clearScreenOfWindow();
        void drawSprite();
    
};
#endif