#ifndef VA_ALU_ALU_MANAGE_H_
#define VA_ALU_ALU_MANAGE_H_
#include<iostream>
#include<bitset>
#include"alu_operate.h"
class ALUManage
{
    private:
        BaseALUOperate *alu;
        int vala;
        int valb;
        int controller;
    public:
        ALUManage(int cont, int a, int b);
        int select_operate();
};
#endif
