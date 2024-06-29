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
    int i = 0;
    while(state != QUIT){
        if(i > 40){
            state = PAUSED;
        }
        
        display.renderScreen();
        inputHandler.checkUserInput(state);
        if(state==PAUSED){
            continue;
        }
        runEmulatorForCycles(1);
        i++;
        
        

    }
}
