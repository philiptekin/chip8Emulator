#ifndef CPU_HPP
#define CPU_HPP

#include <cstdint>
#include "display.hpp"
#include "memory.hpp"
#include <memory>

class CPU{
    private:
        uint8_t V[16];
        uint16_t I; // only 12 lowest most bits are used
        uint16_t stack[16];
        uint8_t stackPointer = 0;
        uint8_t delayTimer = 255;
        uint8_t soundTimer = 0;
        Display* display;
        Memory* memory;

    public:
        CPU(Display *_display,Memory *_memory): display(_display),memory(_memory){

        }
        void ExecuteInstruction(uint16_t instruction);
        uint16_t PC = 0x200; // program starts at 0x200

};
#endif