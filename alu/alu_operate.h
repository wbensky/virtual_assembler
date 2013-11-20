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
        RegisterOperates reg;
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

class Muler:public BaseALUOperate
{
    private:
        int is_mul_overflow(int a, int b);
    public:
        Muler(int, int);
        int operate();
};

class Diver:public BaseALUOperate
{
    public:
        Diver(int, int);
        int operate();
};

class Noter:public BaseALUOperate
{
    public:
        Noter(int, int);
        int operate();
};

class Xorer:public BaseALUOperate
{
    public:
        Xorer(int, int);
        int operate();
};

class Orer:public BaseALUOperate
{
    public:
        Orer(int, int);
        int operate();
};

class Ander:public BaseALUOperate
{
    public:
        Ander(int, int);
        int operate();
};

class Cmper:public BaseALUOperate
{
    public:
        Cmper(int, int);
        int operate();
};

#endif
