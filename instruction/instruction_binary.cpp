#include"instruction_binary.h"
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
        m["rrmovb"] = 0x10;
        m["irmovb"] = 0x11;
        m["rmmovb"] = 0x12;
        m["mrmovb"] = 0x13;
        m["rrmovl"] = 0x18;
        m["irmovl"] = 0x19;
        m["rmmovl"] = 0x1a;
        m["mrmovl"] = 0x1b;

        m["inc"] = 0x21;
        m["dec"] = 0x22;
        m["addb"] = 0x31;
        m["subb"] = 0x32;
        m["mulb"] = 0x33;
        m["divb"] = 0x34;
        m["uaddb"] = 0x35;
        m["usubb"] = 0x36;
        m["umulb"] = 0x37;
        m["udivb"] = 0x38;
        m["mod"] = 0x30;
        m["addl"] = 0x40;
        m["subl"] = 0x41;
        m["mull"] = 0x42;
        m["divl"] = 0x43;
        m["uaddl"] = 0x44;
        m["usubl"] = 0x45;
        m["umull"] = 0x46;
        m["udivl"] = 0x47;
        m["fadd"] = 0x48;
        m["fsub"] = 0x49;
        m["fmul"] = 0x4a;
        m["fdiv"] = 0x4b;

        m["negb"] = 0x50;
        m["notb"] = 0x51;
        m["xorb"] = 0x52;
        m["orb"] = 0x53;
        m["andb"] = 0x54;
        m["negl"] = 0x55;
        m["notl"] = 0x56;
        m["xorl"] = 0x57;
        m["orl"] = 0x58;
        m["andl"] = 0x59;
        m["sal"] = 0x5a;
        m["shl"] = 0x5b;
        m["sar"] = 0x5c;
        m["shr"] = 0x5d;

        m["cmpb"] = 0x60;
        m["cmpl"] = 0x61;
        m["fcmp"] = 0x62;
        m["testb"] = 0x63;
        m["testl"] = 0x64;


        m["jmp"] = 0x70;
        m["je"] = 0x71;
        m["jne"] = 0x72;
        m["js"] = 0x73;
        m["jns"] = 0x74;
        m["jg"] = 0x75;
        m["jge"] = 0x76;
        m["jl"] = 0x77;
        m["jle"] = 0x78;
        m["ja"] = 0x79;
        m["jae"] = 0x7a;
        m["jb"] = 0x7b;
        m["jbe"] = 0x7c;

        m["call"] = 0x80;
        m["leave"] = 0x81;
        m["ret"] = 0x82;
        m["int"] = 0x83;
        m["halt"] = 0x84;
        m["nop"] = 0x85;
        m["pushl"] = 0x86;
        m["popl"] = 0x87;
    }
    return m;
}

