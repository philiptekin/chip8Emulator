#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include "cpu.hpp"
#include "memory.hpp"
#include "display.hpp"
#include "inputHandler.hpp"

#include <iostream>

class Emulator{
    private:
        Memory memory;
        Display display{&memory};
        CPU cpu{&display,&memory};
        InputHandler inputHandler{&memory};
        emulator_state_t state = RUNNING;
    public:
        Emulator(std::string romName){
            memory.ReadRom(romName);
        }
        void runEmulatorForCycles(int cycles);
        void startEmulator();
};
#endif