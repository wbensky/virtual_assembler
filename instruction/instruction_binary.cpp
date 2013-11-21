#include"instruction_binary.h"
#include<iostream>

InstructionBinary::InstructionBinary()
{
}

int InstructionBinary::get_binary(std::string  key_instruction)
{
    if(instruction_binary.find(key_instruction) != instruction_binary.end())
        return instruction_binary[key_instruction];
    return -1;
}

std::map<std::string, int> InstructionBinary::instruction_binary{
    {"rrmovb", 0x10},
        {"irmovb", 0x11},
        {"rmmovb", 0x12},
        {"mrmovb", 0x13},
        {"rrmovl", 0x18},
        {"irmovl", 0x19},
        {"rmmovl", 0x1a},
        {"mrmovl", 0x1b},

        {"inc", 0x21},
        {"dec", 0x22},
        {"addb", 0x31},
        {"subb", 0x32},
        {"mulb", 0x33},
        {"divb", 0x34},
        {"uaddb", 0x35},
        {"usubb", 0x36},
        {"umulb", 0x37},
        {"udivb", 0x38},
        {"mod", 0x30},
        {"addl", 0x40},
        {"subl", 0x41},
        {"mull", 0x42},
        {"divl", 0x43},
        {"uaddl", 0x44},
        {"usubl", 0x45},
        {"umull", 0x46},
        {"udivl", 0x47},
        {"fadd", 0x48},
        {"fsub", 0x49},
        {"fmul", 0x4a},
        {"fdiv", 0x4b},

        {"negb", 0x50},
        {"notb", 0x51},
        {"xorb", 0x52},
        {"orb", 0x53},
        {"andb", 0x54},
        {"negl", 0x55},
        {"notl", 0x56},
        {"xorl", 0x57},
        {"orl", 0x58},
        {"andl", 0x59},
        {"sal", 0x5a},
        {"shl", 0x5b},
        {"sar", 0x5c},
        {"shr", 0x5d},

        {"cmpb", 0x60},
        {"cmpl", 0x61},
        {"fcmp", 0x62},
        {"testb", 0x63},
        {"testl", 0x64},


        {"jmp", 0x70},
        {"je", 0x71},
        {"jne", 0x72},
        {"js", 0x73},
        {"jns", 0x74},
        {"jg", 0x75},
        {"jge", 0x76},
        {"jl", 0x77},
        {"jle", 0x78},
        {"ja", 0x79},
        {"jae", 0x7a},
        {"jb", 0x7b},
        {"jbe", 0x7c},

        {"call", 0x80},
        {"leave", 0x81},
        {"ret", 0x82},
        {"int", 0x83},
        {"halt", 0x84},
        {"nop", 0x85},
        {"pushl", 0x86},
        {"popl", 0x87}
};
