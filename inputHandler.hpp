#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "common.hpp"
#include "memory.hpp"

class InputHandler{
    private:
        Memory * memory;
    public:
        InputHandler(Memory* _memory):memory(_memory){

        }
        void checkUserInput(emulator_state_t& state);
    
};
#endif