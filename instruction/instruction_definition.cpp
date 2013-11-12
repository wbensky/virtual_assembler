#include "instruction_definition.h"
const std::string InstructionDefinition::MOVB = "movb"; // d <= s
const std::string InstructionDefinition::MOVW = "movw";
const std::string InstructionDefinition::MOVL = "movl";

const std::string InstructionDefinition::MOVSBW = "movsbw"; // signed extend
const std::string InstructionDefinition::MOVSBL = "movsbl";
const std::string InstructionDefinition::MOVSWL = "movswl";

const std::string InstructionDefinition::MOVZBW = "mvozbw";
const std::string InstructionDefinition::MOVZBL = "movzbl";
const std::string InstructionDefinition::MOVZWL = "movzwl";

const std::string InstructionDefinition::PUSHL = "pushl"; // push stack double word
const std::string InstructionDefinition::POPL = "popl";

// Arithmetic and Logic operating
const std::string InstructionDefinition::LEAL = "leal"; //
const std::string InstructionDefinition::INC = "inc";
const std::string InstructionDefinition::DEC = "dec";
const std::string InstructionDefinition::NEG = "neg"; // negative
const std::string InstructionDefinition::NOT = "not";
//logic
const std::string InstructionDefinition::ADD = "add";
const std::string InstructionDefinition::SUB = "sub";
const std::string InstructionDefinition::IMUL = "imul";
const std::string InstructionDefinition::XOR = "xor";
const std::string InstructionDefinition::OR = "or";
const std::string InstructionDefinition::AND = "and";
//FLOAT Arithmetic
const std::string InstructionDefinition::FADD = "fadd";
const std::string InstructionDefinition::FSUB = "fsub";
const std::string InstructionDefinition::FIMUL= "fimul";
const std::string InstructionDefinition::FDIV = "fdiv";

const std::string InstructionDefinition::SAL = "sal";
const std::string InstructionDefinition::SHL = "shl";
const std::string InstructionDefinition::SAR = "sar";
const std::string InstructionDefinition::SHR = "shr";

const std::string InstructionDefinition::IMULL = "imull";
const std::string InstructionDefinition::MULL = "mull";
const std::string InstructionDefinition::CLTD = "cltd";
const std::string InstructionDefinition::IDIVL = "idivl";
const std::string InstructionDefinition::DIVL = "divl";
// control instructions
const std::string InstructionDefinition::CMPB = "cmpb";
const std::string InstructionDefinition::CMPW = "cmpw";
const std::string InstructionDefinition::CMPL = "cmpl";
const std::string InstructionDefinition::FCMP = "fcmp";
const std::string InstructionDefinition::TESTB = "testb";
const std::string InstructionDefinition::TESTW = "testw";
const std::string InstructionDefinition::TESTL = "testl";

const std::string InstructionDefinition::JMP = "jmp";
const std::string InstructionDefinition::JE = "je";    //zf
const std::string InstructionDefinition::JNE = "jne";   //~zf
const std::string InstructionDefinition::JS = "js";    //sf
const std::string InstructionDefinition::JNS = "jns";   //~sf
const std::string InstructionDefinition::JG = "jg";    //~(SF^OF)&~ZF
const std::string InstructionDefinition::JGE = "jge";   //~(SF^OF)
const std::string InstructionDefinition::JL = "jl";    //(SF^OF)
const std::string InstructionDefinition::JLE = "jle";   //(SF^OF)|ZF
const std::string InstructionDefinition::JA = "ja";    //~CF&~ZF
const std::string InstructionDefinition::JAE = "jae";   //~CF
const std::string InstructionDefinition::JB = "jb";    //CF
const std::string InstructionDefinition::JBE = "jbe";   //cfzf
// call
const std::string InstructionDefinition::CALL = "call";
const std::string InstructionDefinition::LEAVE = "leave";
const std::string InstructionDefinition::RET = "ret";
//other
const std::string InstructionDefinition::INT = "ret";

