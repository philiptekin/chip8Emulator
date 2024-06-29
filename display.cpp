#include "display.hpp"
#include <iostream>
#include <vector>

uint32_t fg_color = 0xFFFFFF00; // white
uint32_t bg_color = 0x00000000;//0x00000000; // black
uint8_t bg_r = (bg_color >> 24) & 0xFF;
uint8_t bg_g = (bg_color >> 16) & 0xFF;
uint8_t bg_b = (bg_color >> 8) & 0xFF;
uint8_t bg_a = (bg_color >> 0) & 0xFF;

uint8_t fg_r = (fg_color >> 24) & 0xFF;
uint8_t fg_g = (fg_color >> 16) & 0xFF;
uint8_t fg_b = (fg_color >> 8) & 0xFF;
uint8_t fg_a = (fg_color >> 0) & 0xFF;


void Display::clearScreenOfWindow(){
    SDL_SetRenderDrawColor(sdlRenderer,bg_r,bg_g,bg_b,bg_a);
    SDL_RenderClear(sdlRenderer);
}

void Display::drawSprite()
{
    SDL_Rect rect;
    clearScreenOfWindow();

    for(uint32_t i = 0; i < screen_height*screen_width;i++){
        rect.x = (i % screen_width) * scaleFactor;
        rect.y = (i / screen_width) * scaleFactor;
        rect.h = scaleFactor;
        rect.w = scaleFactor;


        if(memory->display[i]){
            SDL_SetRenderDrawColor(sdlRenderer,fg_r,fg_g,fg_b,fg_a);
            SDL_RenderFillRect(sdlRenderer,&rect);

        }
        else{
            SDL_SetRenderDrawColor(sdlRenderer,bg_r,bg_g,bg_b,bg_a);
            SDL_RenderFillRect(sdlRenderer,&rect);
        }
    }
    SDL_RenderPresent(sdlRenderer); // Update screen
}

void Display::initializeDisplay(){
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);

    window = SDL_CreateWindow( 
    "An SDL2 window",                  //    window title
    SDL_WINDOWPOS_UNDEFINED,           //    initial x position
    SDL_WINDOWPOS_UNDEFINED,           //    initial y position
    width*scaleFactor,                               //    width, in pixels
    height*scaleFactor,                               //    height, in pixels
    SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL //    flags - see below
    );
    if(window==NULL){   
        // In the event that the window could not be made...
        std::cout << "Could not create window: " << SDL_GetError() << '\n';
    }
    else{
        SDL_UpdateWindowSurface(window);
        SDL_Delay(1000);  
    }

    sdlRenderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED);

    clearScreenOfWindow();
}

void Display::renderScreen(){
        SDL_Delay(delayInMs);  
        drawSprite();
        //SDL_RenderPresent(sdlRenderer);
}