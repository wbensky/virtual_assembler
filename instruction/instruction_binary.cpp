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
        m["rrmovb"] = 01000;
        m["irmovb"] = 01001;
        m["rmmovb"] = 01002;
        m["mrmovb"] = 01003;
        m["rrmovl"] = 01100;
        m["irmovl"] = 01101;
        m["rmmovl"] = 01102;
        m["mrmovl"] = 01103;

        m["inc"] = 02001;
        m["dec"] = 02002;
        m["addb"] = 02100;
        m["subb"] = 02101;
        m["mulb"] = 02102;
        m["divb"] = 02103;
        m["uaddb"] = 02104;
        m["usubb"] = 02105;
        m["umulb"] = 02106;
        m["udivb"] = 02107;
        m["mod"] = 02003;
        m["addl"] = 02200;
        m["subl"] = 02201;
        m["mull"] = 02202;
        m["divl"] = 02203;
        m["uaddl"] = 02204;
        m["usubl"] = 02205;
        m["umull"] = 02206;
        m["udivl"] = 02207;
        m["fadd"] = 02400;
        m["fsub"] = 02401;
        m["fmul"] = 02402;
        m["fdiv"] = 02403;

        m["negb"] = 03000;
        m["notb"] = 03001;
        m["xorb"] = 03002;
        m["orb"] = 03003;
        m["andb"] = 03004;
        m["negl"] = 03100;
        m["notl"] = 03101;
        m["xorl"] = 03102;
        m["orl"] = 03103;
        m["andl"] = 03104;
        m["sal"] = 03200;
        m["shl"] = 03201;
        m["sar"] = 03202;
        m["shr"] = 03203;

        m["cmpb"] = 04000;
        m["cmpl"] = 04001;
        m["fcmp"] = 04002;
        m["testb"] = 04003;
        m["testl"] = 04004;


        m["jmp"] = 05000;
        m["je"] = 05002;
        m["jne"] = 05003;
        m["js"] = 05004;
        m["jns"] = 05005;
        m["jg"] = 05006;
        m["jge"] = 05007;
        m["jl"] = 05010;
        m["jle"] = 05011;
        m["ja"] = 05012;
        m["jae"] = 05013;
        m["jb"] = 05014;
        m["jbe"] = 05015;

        m["call"] = 06000;
        m["leave"] = 06001;
        m["ret"] = 06002;
        m["int"] = 06003;
        m["halt"] = 06004;
        m["nop"] = 06005;
        m["pushl"] = 06006;
        m["popl"] = 06007;
    }
    return m;
}

