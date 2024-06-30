#include "cpu.hpp"
#include <iostream>
#include <chrono>
#include <random>

uint8_t randomByteGenerator(){
    std::default_random_engine randGen;
    return std::uniform_int_distribution<uint8_t>(0,255)(randGen);
}



void CPU::ExecuteInstruction(uint16_t instruction){
    if(instruction == 0){
        std::cout << "No instruction found at PC: " << PC << std::endl;
    }
    else{
        std::cout << "Executing instruction: " << std::hex << instruction << std::endl;
        std::cout << "PC value: " << std::hex << (PC) << std::endl;
    }

    
    switch(instruction & 0xF000){
        case 0x0000:{
            switch(instruction & 0x00FF){
                case 0xE0:{
                    std::cout<<"Clear display"<<std::endl;
                    memset(memory->display,0,sizeof(memory->display));
                    break;
                }
                case 0xEE:{
                    --stackPointer;
                    PC = stack[stackPointer];
                    std::cout<<"Return from subroutine"<<std::endl;
                    return;
                }
                default:
                    std::cout<<"This instruction is not implemented on modern machine"<<std::endl;
            }
            break;
        }
        case 0x1000:{
            PC = (instruction & 0x0FFF);
            return;
        }
        case 0x2000:{
            stack[stackPointer] = PC + 2;
            stackPointer++;
            PC = (instruction & 0x0FFF);
            return;
        }
        case 0x3000:{
            uint16_t element = (instruction & 0x0F00)>>8;
            uint16_t valuekk = (instruction & 0x00FF);
            if(V[element] == valuekk){
                PC += 2;
            }
            break;
        }
        case 0x4000:{
            uint16_t element = (instruction & 0x0F00)>>8;
            uint16_t valuekk = (instruction & 0x00FF);
            if(V[element] != valuekk){
                PC += 2;
            }
            break;
        }
        case 0x5000:{
            uint16_t x = (instruction & 0x0F00)>>8;
            uint16_t y = (instruction & 0x00F0)>>4;
            if(V[x] == V[y]){
                PC += 2;
            }
            break;
        }
        case 0x6000:{
            uint16_t element = (instruction & 0x0F00)>>8;
            uint16_t valuekk = instruction & 0x00FF;
            V[element] = valuekk;
            break;
        }
        case 0x7000:{
            uint16_t element = (instruction & 0x0F00)>>8;
            uint16_t valuekk = instruction & 0x00FF;
            V[element] += valuekk;
            break;
        }
        case 0x8000:{
            uint16_t x = ((instruction & 0x0F00)>>8);
            uint16_t y = ((instruction & 0x00F0)>>4);
            switch(instruction & 0x000F){
                case 0x0000:{
                    V[x] = V[y];
                    break;
                }
                case 0x0001:{
                    V[x] |= V[y];
                    break;
                }
                case 0x0002:{
                    V[x] &= V[y];
                    break;
                }
                case 0x0003:{
                    V[x] ^= V[y];
                    break;
                }
                case 0x0004:{
                    uint16_t temp = V[x] + V[y];
                    V[x] = (temp & 0x00FF);
                    if((temp & 0x200) > 0){
                        V[0x000F] = 1;
                    }
                    else{
                        V[0x000F] = 0;
                    }
                    break;
                }
                case 0x0005:{
                    uint16_t temp = V[x] - V[y];
                    V[x] -= V[y];
                    if(V[x] > V[y]){
                        V[0x000F] = 1;
                    }
                    else{
                        V[0x000F] = 0;
                    }
                    break;
                }
                case 0x0006:{
                    if(V[x] & 0x01){
                        V[0x0F] = 1;
                    }
                    else{
                        V[0x0F] = 0;
                    }
                    V[x] >>= 1;
                    break;
                }
                case 0x0007:{
                    if(V[y] > V[x]){
                        V[0x0F] = 1;
                    }
                    else{
                        V[0x0F] = 0;
                    }
                    V[x] = V[y] - V[x];
                    break;
                }
                case 0x000E:{
                    if(V[x] & 0x01){
                        V[0x0F] = 1;
                    }
                    else{
                        V[0x0F] = 0;
                    }
                    V[x] <<= 1;
                    break;
                }
            }
            break;
        }
        case 0x9000:{
            uint16_t x = ((instruction & 0x0F00)>>8);
            uint16_t y = ((instruction & 0x00F0)>>4);
            if(V[x] != V[y]){
                PC += 2;
            }
            break;
        }
        case 0xA000:{
            uint16_t value = (instruction & 0x0FFF);
            I = value;
            break;
        }
        case 0xB000:{
            uint16_t valuennn = (instruction & 0x0FFF);
            PC = valuennn + V[0];
            return;
        }
        case 0xC000:{
            uint8_t x = (instruction & 0x0F00)>>8;
            uint8_t byte = instruction & 0x00FF;
            V[x] = randomByteGenerator() & byte;
            break;
        }
        case 0xD000:{
            uint16_t tempX = ((instruction & 0x0F00) >> 8);
            uint16_t tempY = ((instruction & 0x00F0) >> 4);
            uint8_t x = V[tempX] % screen_width;
            uint8_t y = V[tempY] % screen_height;
            uint8_t n = (instruction & 0x000F);
            V[0xF] = 0;
            uint8_t originalX = x;

            for(uint8_t i = 0; i < n;i++){
                const uint8_t spriteData = memory->ram[I + i];
                x = originalX;

                for(int8_t j = 0; j < 8; j++){
                    if((spriteData & (0x80 >> j)) && memory->display[(y) * screen_width + x]){
                        V[0xF] = 1;
                    }
                    memory->display[(y) * screen_width + x] ^= (spriteData & (0x80 >> j));

                    if(++x >= screen_width){
                        break;
                    }
                }
                if(++y >= screen_height){
                    break;
                }
            }


            break;
        }
        case 0xE000:{
            uint8_t x = (instruction & 0x0F00) >> 8;
            uint8_t key = V[x];
            switch(instruction & 0x00FF){
                case 0x009E:{
                    if (memory->keys[key]){
                        PC += 2;
                    }
                    break;
                }
                case 0x00A1:{
                    if (!memory->keys[key]){
                        PC += 2;
                    }
                    break;
                }
            }
            break;
        }
        case 0xF000:{
            uint8_t x = (instruction & 0x0F00)>>8;
            switch(instruction & 0x00FF){
                case 0x07:{
                    V[x] = delayTimer;
                    break;
                }
                case 0x0A:{
                    bool anyKeyPressed = false;
                    for(int i = 0; i < 16; i++){
                        if(memory->keys[i]){
                            V[x] = i;
                            anyKeyPressed = true;
                        }
                    }
                    if(!anyKeyPressed){
                        PC -= 2;
                    }
                    break;
                }
                case 0x15:{
                    delayTimer = V[x];
                    break;
                }
                case 0x18:{
                    soundTimer = V[x];
                    break;
                }
                case 0x1E:{
                    I += V[x];
                    break;
                }
                case 0x29:{
                    int fontsStartInMemory = 0x0000;
                    int fontSizeInBytes = 5;
                    I = fontsStartInMemory + (fontSizeInBytes * V[x]);
                    break;
                }
                case 0x33:{
                    uint8_t value = V[x];
                    memory->ram[I + 2] = value % 10;
                    value /= 10;

                    memory->ram[I + 1] = value % 10;
                    value /= 10;

                    memory->ram[I + 0] = value % 10;
                    break;
                }
                case 0x55:{
                    uint8_t amountOfRegistersToAdd = V[x]; // can be between 0 - 15, so the for loop contains <= instead of <.
                    for(uint8_t i = 0; i <= amountOfRegistersToAdd; i++){
                        memory->ram[I + i] = V[i];
                    }
                    break;
                }
                case 0x65:{
                    uint8_t amountOfRegistersToAdd = V[x]; // can be between 0 - 15, so the for loop contains <= instead of <.
                    for(uint8_t i = 0; i <= amountOfRegistersToAdd; i++){
                        V[i] = memory->ram[I + i];
                    }
                    break;
                }

                default:
                    std::cout<<"Instruction not found"<<std::endl;
            }
            break;
            }
        default:
        std::cout<<"Instruction not found"<<std::endl;
    }
    PC += 2;
    

}