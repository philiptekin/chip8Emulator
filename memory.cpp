#include "memory.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

const uint8_t font[] = { 0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
                        0x20, 0x60, 0x20, 0x20, 0x70, // 1
                        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
                        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
                        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
                        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
                        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
                        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
                        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
                        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
                        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
                        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
                        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
                        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
                        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
                        0xF0, 0x80, 0xF0, 0x80, 0x80  // F                               
                        };

uint8_t Memory::ReadFromRAM(uint16_t address){
    if(address < maxMemorySize){
        return ram[address];
    }
    else{
        std::cout<<"Trying to read from outside of memory: " << std::hex << std::uppercase << address << std::endl;
        return 0;
    }
}

void Memory::WriteToRAM(uint16_t address, uint8_t value){
    if(address < maxMemorySize){
        ram[address] = value;
    }
    else{
        std::cout<<"Trying to write from outside of memory: " << std::hex << std::uppercase << address << std::endl;
    }
}

void Memory::ReadRom(std::string romName){
    // loadFont
    std::memcpy(&ram[0],font,sizeof(font));


    std::ifstream file(romName, std::ios::binary);
    
    file.seekg(0,std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0,std::ios::beg);

    if(!file.is_open()){
        std::cerr << "Failed to open file for reading \n";
        exit(-1);
    }

    if(file.read(reinterpret_cast<char*>(&ram[0x200]),size)){
        std::cout << "Successfully read the ROM with size: "<<size<< std::endl;
        for(uint16_t i = 0x0;i < size + 0x200;i=i+2){
            uint8_t lower = ReadFromRAM(i);
            uint8_t higher = ReadFromRAM(i+1);
            uint16_t fullAddress = (lower << 8) | higher;
            std::cout<<std::hex<<(fullAddress)<<std::endl;
        }
        
    }
    else{
        std::cout << "Failed to read the ROM\n";
    }

    file.close();
}