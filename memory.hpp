#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>
#include <iostream>
#include "common.hpp"

class Memory{
    private:
        static const int maxMemorySize = 4*1024;
        static const int maxDisplaySize = screen_width*screen_height;
        static const int maxKeys = 16;
        
        
    public:
        uint8_t ram[maxMemorySize];
        uint8_t display[maxDisplaySize];
        bool keys[maxKeys]; // 1 2 3 4 Q W E R A S D F Z X C V
        
        void Initialise(){
            for(int i = 0; i < maxMemorySize; i++){
                ram[i] = 0;
            }
           for(int i = 0; i < maxDisplaySize; i++){
                display[i] = 0;
            }
        }
        void ReadRom(std::string romName);
        uint8_t ReadFromRAM(uint16_t address);
        void WriteToRAM(uint16_t address, uint8_t value);

        Memory(){
            Initialise();
        }
};
#endif