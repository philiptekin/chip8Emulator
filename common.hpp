#ifndef COMMON_HPP
#define COMMON_HPP

typedef enum{
    QUIT = 0,
    RUNNING = 1,
    PAUSED = 2,
} emulator_state_t;

int const screen_width = 64;
int const screen_height = 32;
int const scaleFactor = 20;
int const refreshRateInMs = 16; // 16.67 == 60 hz
int const instructionsExecutedForEachFrame = 5; // 500 instructions/second is 8.33 instruction for each frame

#endif