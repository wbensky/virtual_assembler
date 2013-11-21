#ifndef VA_STACK_STACK_OPERATES_H_
#define VA_STACK_STACK_OPERATES_H_
#include<memory>
#include<iostream>
#include "../register/register_operates.h"
/*
    StackOperates is used to manage stack, include operates like popl,pushl,is_empty
Datatime: 11/18/2013
Auther: wwl;
*/
class StackOperates
{
    private:
        static unsigned int stack_buffer[1000];
        RegisterOperates reg;
    public:
        StackOperates();

        void pushl(unsigned int);
        unsigned popl();
        int is_empty();
        void print();
};

#endif
