#include"memory_manage.h"
#include<iostream>

MemoryManage::MemoryManage():
    memory_buffer(create_memory_buffer())
{
}

unsigned char (&MemoryManage::create_memory_buffer())[1000000]
{
    static unsigned char buffer[1000000];
    return buffer;
}

int MemoryManage::set_instruction(int address,
        unsigned char code,
        unsigned char register1,
        unsigned char register2)
{
    memory_buffer[address] = code;
    memory_buffer[address + 1] = register1;
    memory_buffer[address + 2] = register2;
    for (int i = 0; i < 3;i++)
    {
        memory_buffer[address + i + 3] = 0;
    }
    return 0;
}

int MemoryManage::set_instruction(int address,
        unsigned char code,
        unsigned char register1,
        unsigned int number)
{
        memory_buffer[address] =  code;
        memory_buffer[address + 1] = register1;
        for( int i = 0; i < 4 ;i++)
        {
            unsigned char t = (number >> (8 * i) )& (0xff );
            memory_buffer[address + i + 2] = t;
        }
        return 0;
}

int MemoryManage::get_instruction(int address,
        unsigned char instruction[])
{
    for(int i = 0; i < 6; i++)
    {
        instruction[i] = memory_buffer[address + i];
    }
    return 0;
}

int MemoryManage::write_data(int address,
        unsigned char data[],
        int size)
{
    for(int i = 0; i < size; i++)
    {
    }
    return 0;
}

int MemoryManage::write_data(int address,
        unsigned int data[],
        int size)
{
    return 0;
}
int MemoryManage::read_data(int address,
        unsigned char data[],
        int size)
{
    return 0;
}
int MemoryManage::read_data(int address,
        unsigned int data[],
        int size)
{
    return 0;
}
int MemoryManage::print()
{
    for(int i = 0; i < 12; i++)
    {
        unsigned int t = memory_buffer[i];
        std::cout << std::hex << t << "\n";
    }
    return 0;
}




