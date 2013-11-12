#include"instruction_binary.h"
#include"instruction_definition.h"
#include<iostream>
InstructionBinary::InstructionBinary():instruction_binary(create_map())
{
}

int InstructionBinary::get_binary(std::string  key_instruction)
{
    if(instruction_binary.find(key_instruction) != instruction_binary.end())
        return instruction_binary[key_instruction];
    return -1;
}



std::map<std::string, int>& InstructionBinary::create_map()
{
    static  std::map<std::string, int> m;
    static int mutex = 0;
    if(mutex == 0)
    {
        mutex = 1;
        m[InstructionDefinition:: MOVB] = 0x1;
        m[InstructionDefinition:: MOVW] = 0x2;
        m[InstructionDefinition:: MOVL] = 0x3;

        m[InstructionDefinition:: MOVSBW] = 0x4;
        m[InstructionDefinition:: MOVSBL] = 0x5;
        m[InstructionDefinition:: MOVSWL] = 0x6;

        m[InstructionDefinition:: MOVZBW] = 0x7;
        m[InstructionDefinition:: MOVZBL] = 0x8;
        m[InstructionDefinition:: MOVZWL] = 0x9;
        // for more mov instruction
        m[InstructionDefinition:: PUSHL] = 0x1e;
        m[InstructionDefinition:: POPL] = 0x1f;

        m[InstructionDefinition:: LEAL] = 0x20;
        m[InstructionDefinition:: INC] = 0x21;
        m[InstructionDefinition:: DEC] = 0x22;
        m[InstructionDefinition:: NEG] = 0x23;
        m[InstructionDefinition:: NOT] = 0x24;

        m[InstructionDefinition:: ADD] = 0x25;
        m[InstructionDefinition:: SUB] = 0x26;
        m[InstructionDefinition:: IMUL] = 0x27;
        m[InstructionDefinition:: XOR] = 0x28;
        m[InstructionDefinition:: OR] = 0x29;
        m[InstructionDefinition:: AND] = 0x2a;

        m[InstructionDefinition:: FADD] = 0x2b;
        m[InstructionDefinition:: FSUB] = 0x2c;
        m[InstructionDefinition:: FIMUL] = 0x2d;
        m[InstructionDefinition:: FDIV] = 0x2e;

        m[InstructionDefinition:: SAL] = 0x2f;
        m[InstructionDefinition:: SHL] = 0x31;
        m[InstructionDefinition:: SAR] = 0x32;
        m[InstructionDefinition:: SHR] = 0x33;

        m[InstructionDefinition:: IMULL] = 0x34;
        m[InstructionDefinition:: MULL] = 0x35;
        m[InstructionDefinition:: CLTD] = 0x36;
        m[InstructionDefinition:: IDIVL] = 0x37;
        m[InstructionDefinition:: DIVL] = 0x38;

        m[InstructionDefinition:: CMPB] = 0x70;
        m[InstructionDefinition:: CMPW] = 0x71;
        m[InstructionDefinition:: CMPL] = 0x72;
        m[InstructionDefinition:: FCMP] = 0x73;
        m[InstructionDefinition:: TESTB] = 0x74;
        m[InstructionDefinition:: TESTW] = 0x75;
        m[InstructionDefinition:: TESTL] = 0x76;

        m[InstructionDefinition:: JMP] = 0x80;
        m[InstructionDefinition:: JE] = 0x81;
        m[InstructionDefinition:: JNE] = 0x82;
        m[InstructionDefinition:: JS] = 0x83;
        m[InstructionDefinition:: JNS] = 0x84;
        m[InstructionDefinition:: JG] = 0x85;
        m[InstructionDefinition:: JGE] = 0x86;
        m[InstructionDefinition:: JL] = 0x87;
        m[InstructionDefinition:: JLE] = 0x88;
        m[InstructionDefinition:: JA] = 0x89;
        m[InstructionDefinition:: JAE] = 0x8a;
        m[InstructionDefinition:: JB] = 0x8b;
        m[InstructionDefinition:: JBE] = 0x8c;

        m[InstructionDefinition:: CALL] = 0xe0;
        m[InstructionDefinition::LEAVE] = 0xe1;
        m[InstructionDefinition::RET] = 0xe2;

        m[InstructionDefinition::INT] = 0xf0;
    }
    return m;
}

