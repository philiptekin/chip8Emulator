#include "emulator.hpp"
#include <iostream>
#include <string>

int main(){

    std::string temp;
    std::cout<<"Type your filename to run"<<std::endl;
    std::cin>>temp;
    temp += ".ch8";

    Emulator emulator{temp};
    emulator.startEmulator();

    return 0;
}