#include<string>
#include<map>

class InstructionDefinition
{
public:
    //mov data
    //d <- s
    static const std::string MOVB; // d <= s
    static const std::string MOVW;
    static const std::string MOVL;

    static const std::string MOVSBW; // signed extend
    static const std::string MOVSBL;
    static const std::string MOVSWL;

    static const std::string MOVZBW;
    static const std::string MOVZBL;
    static const std::string MOVZWL;

    static const std::string PUSHL; // push stack double word
    static const std::string POPL;

    // Arithmetic and Logic operating
    static const std::string LEAL; //
    static const std::string INC;
    static const std::string DEC;
    static const std::string NEG; // negative
    static const std::string NOT;
        //logic
    static const std::string ADD;
    static const std::string SUB;
    static const std::string IMUL;
    static const std::string XOR;
    static const std::string OR;
    static const std::string AND;
    //FLOAT Arithmetic
    static const std::string FADD;
    static const std::string FSUB;
    static const std::string FIMUL;
    static const std::string FDIV;

    static const std::string SAL;
    static const std::string SHL;
    static const std::string SAR;
    static const std::string SHR;

    static const std::string IMULL;
    static const std::string MULL;
    static const std::string CLTD;
    static const std::string IDIVL;
    static const std::string DIVL;
// control instructions
    static const std::string CMPB;
    static const std::string CMPW;
    static const std::string CMPL;
    static const std::string FCMP;
    static const std::string TESTB;
    static const std::string TESTW;
    static const std::string TESTL;

    static const std::string JMP;
    static const std::string JE;    //zf
    static const std::string JNE;   //~zf
    static const std::string JS;    //sf
    static const std::string JNS;   //~sf
    static const std::string JG;    //~(SF^OF)&~ZF
    static const std::string JGE;   //~(SF^OF)
    static const std::string JL;    //(SF^OF)
    static const std::string JLE;   //(SF^OF)|ZF
    static const std::string JA;    //~CF&~ZF
    static const std::string JAE;   //~CF
    static const std::string JB;    //CF
    static const std::string JBE;   //CFZF
// call
    static const std::string CALL;
    static const std::string LEAVE;
    static const std::string RET;
//other
    static const std::string INT;
};
