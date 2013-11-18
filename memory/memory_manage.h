#ifndef VA_MEMORY_MEMORY_MANAGE_H_
#define VA_MEMORY_MEMORY_MANAGE_H_
#include<iostream>
#include<cstring>
#include<cstdlib>
/*
   memory management, include write instruction into the memory
   and read instruction from the memory, and write the data into
   the memory and read data form memory;
Datatime: 11,13,2013
Auther:wwl
*/
class MemoryManage
{
    private:
        unsigned char (&memory_buffer)[1000000];
    public:
        MemoryManage();

        static unsigned char (&create_memory_buffer())[1000000];

        int set_instruction(int address,
                unsigned char code,
                unsigned char register1,
                unsigned char register2
                );
        int set_instruction(int address,
                unsigned char code,
                unsigned char register1,
                unsigned int number
                );
        int get_instruction(int address, unsigned char[]);

        int write_data(int address,
                unsigned char data[],
                int size);
        int write_data(int address,
                unsigned int  data[],
                int size);

        int read_data(int address,
                unsigned char data[],
                int size);
        int read_data(int address,
                unsigned int data[],
                int size);
        int print();
};

#endif
