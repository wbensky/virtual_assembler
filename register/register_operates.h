#ifndef VA_REGISTER_OPERATES_H_
#define VA_REGISTER_OPERATES_H_
#include<iostream>

class RegisterOperates
{
    private:
        unsigned int (&register_buffer)[8] ;
        bool (&symbols_buffer)[4];
        unsigned int &rax;
        unsigned int &rbx;
        unsigned int &rcx;
        unsigned int &rdx;
        unsigned int &rsp;
        unsigned int &rdp;
        unsigned int &rsi;
        unsigned int &rdi;
        bool &zf, &sf, &of, &cf;
        unsigned int &pc;
    public:
        RegisterOperates();

        void set_zf(bool value);
        bool get_zf();
        void set_sf(bool );
        bool get_sf();
        void set_of(bool);
        bool get_of();
        void set_cf(bool);
        bool get_cf();
        void set_pc(unsigned int);
        unsigned int get_pc();

        void set_register(int , void *);
        void get_register(int, void*);
        void print();

        static unsigned int (&create_register_buffer())[8];
        static bool(& create_symbols_buffer())[4];
        static unsigned int& create_pc_buffer();
};

#endif
