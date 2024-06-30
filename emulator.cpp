#include "emulator.hpp"
#include <fstream>



void Emulator::runEmulatorForCycles(int cycles){

    while(cycles > 0){
        uint8_t lower = memory.ReadFromRAM(cpu.PC);
        uint8_t higher = memory.ReadFromRAM(cpu.PC + 1);
        uint16_t fullAddress = (lower << 8) | higher;
        cpu.ExecuteInstruction(fullAddress);
        cycles--;
    }
}
void Emulator::startEmulator(){
    while(state != QUIT){
        inputHandler.checkUserInput(state);
        if(state==PAUSED){
            continue;
        }
        runEmulatorForCycles(instructionsExecutedForEachFrame);
        display.renderScreen();

        
    }
}
