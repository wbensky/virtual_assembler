#ifndef VA_ALU_ALU_MANAGE_H_
#define VA_ALU_ALU_MANAGE_H_
#include<iostream>
#include<bitset>

class ALUManage
{
    private:
    public:
        ALUManage();
        static unsigned int ac_uadder(unsigned int vala,
                unsigned int valb,
                int &carry);
        static  int ac_adder(int vala,
                int valb,
                int &carry);




};
#endif
