#ifndef VA_ALU_ALU_OPERATE_H_
#define VA_ALU_ALU_OPERATE_H_

#include"../register/register_operates.h"
#include<iostream>

class BaseALUOperate
{
    protected:
        RegisterOperates reg;
        int vala;
        int valb;
    public:
        BaseALUOperate(int a, int b):vala(a),valb(b)
        {}
        virtual int operate() = 0;
};

class ACAdder:public BaseALUOperate
{
    private:
        RegisterOperaters reg;
    public:
        ACAdder(int, int);
        int operate();
};

class Implement:public BaseALUOperate
{
    public:
        Implement(int, int);
        int operate();
};

class Suber:public BaseALUOperate
{
    public:
        Suber(int, int);
        int operate();
};


#endif
