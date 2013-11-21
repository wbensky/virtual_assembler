#ifndef VA_INSTRUCTION_INSTRUCTONBINARY_H_
#define VA_INSTRUCTION_INSTRUCTONBINARY_H_

#include<map>
#include<string>

class InstructionBinary
{
private:
    static std::map<std::string, int> instruction_binary;
public:
    InstructionBinary();

    int get_binary(std::string key_instruction);
};

#endif
