#ifndef VA_REGISTER_OPERATES_H_
#define VA_REGISTER_OPERATES_H_
#include<iostream>

class RegisterOperates
{
    private:
        unsigned int register_buffer[8] ;
        unsigned int &rax;
        unsigned int &rbx;
        unsigned int &rcx;
        unsigned int &rdx;
        unsigned int &rsp;
        unsigned int &rdp;
        unsigned int &rsi;
        unsigned int &rdi;
        bool zf, sf, of, cf;
        int pc;
    public:
        RegisterOperates();
        void set_register(int , void *);
        void get_register(int, void*);
        void print();
};

#endif
