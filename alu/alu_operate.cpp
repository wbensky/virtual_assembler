#include"alu_operate.h"

ACAdder::ACAdder(int a, int b):BaseALUOperate(a, b)
{
}

int ACAdder::operate()
{
    std::bitset<32> v1(vala);
    std::bitset<32> v2(valb);
    std::bitset<33> carry_set;
    std::bitset<32> dst;
    int result  = 0;
    int temp;
    int int_length = 32;

    carry_set[0] = 0;
    for(int i = 0; i< int_length ; i++)
    {
        carry_set[i + 1] = (v1[i] && v2[i] )|| ((v1[i] || v2[i]) \
                && carry_set[i]);
        dst[i]  = v1[i] ^ v2[i] ^ carry_set[i];
        temp = dst[i];
        result += temp << i;
    }
    reg.set_zf(result == 0? true: false);
    reg.set_sf(dst[31] == 1? true: false);
    reg.set_cf(carry_set[32] == 1? true:false);
    if(v1[31] == v2[31] && v1[31] != dst[32])
        reg.set_of(true);
    else
        reg.set_of(false);
    return result;
}
// have not write in alumanage
Implement::Implement(int a, int b):BaseALUOperate(a, b)
{
}

int Implement::operate()
{
    return 0;
}

Suber::Suber(int a, int b):BaseALUOperate(a, b)
{
}

int Suber::operate()
{
    ACAdder a(vala,~valb + 1);
    return a.operate();
}

Muler::Muler(int a, int b):BaseALUOperate(a, b)
{
}

int Muler::operate()
{
    RegisterOperates reg;
    int result = vala * valb;
    reg.set_zf(result == 0 ? 1 : 0);
    reg.set_of(is_mul_overflow(vala, valb) == 0? 0: 1);
    reg.set_sf((result & 0x80000000) == 0 ? 0 : 1);
    reg.set_cf(reg.get_of());
    return result;
}

int Muler::is_mul_overflow(int a, int b)
{
    if(a >= 0 && b >= 0)
    {
        return (INT_MAX / a) < b;
    }
    else if(a < 0 && b < 0)
    {
        return (INT_MAX/ a) > b;
    }
    else if( a * b == INT_MIN)
    {
        return 0;
    }
    else
    {
        return a< 0 ? is_mul_overflow(-a , b): is_mul_overflow(a, -b);
    }
}

Diver::Diver(int a, int b):BaseALUOperate(a, b)
{
}

int Diver::operate()
{
    if(valb == 0)
    {
        return vala; // error operate
    }

    int result = vala / valb;

    reg.set_zf(result == 0 ? 1: 0);
    reg.set_of(0);
    reg.set_cf(0);
    reg.set_sf((result & 0x70000000)== 0? 0: 1);

    return result;
}

Noter::Noter(int a, int b):BaseALUOperate(a, b)
{
}

int Noter::operate()
{
    int result = ~vala;

    reg.set_zf(result == 0? 1: 0);
    reg.set_of(0);
    reg.set_cf(0);
    reg.set_sf((result & 0x70000000) == 0? 0: 1);

    return result;
}

Xorer::Xorer(int a, int b):BaseALUOperate(a, b)
{
}

int Xorer::operate()
{
    int result = vala ^ valb;

    reg.set_zf(result == 0? 1: 0);
    reg.set_of(0);
    reg.set_cf(0);
    reg.set_sf((result & 0x70000000) == 0? 0: 1);

    return result;
}

Orer::Orer(int a, int b):BaseALUOperate(a, b)
{
}

int Orer::operate()
{
    int result = vala | valb;

    reg.set_zf(result == 0? 1: 0);
    reg.set_of(0);
    reg.set_cf(0);
    reg.set_sf((result & 0x70000000) == 0? 0: 1);

    return result;
}

Ander::Ander(int a, int b):BaseALUOperate(a, b)
{
}

int Ander::operate()
{
    int result = vala & valb;

    reg.set_zf(result == 0? 1: 0);
    reg.set_of(0);
    reg.set_cf(0);
    reg.set_sf((result & 070000000) == 0? 0: 1);

    return result;
}

Cmper::Cmper(int a, int b):BaseALUOperate(a, b)
{
}

int Cmper::operate()
{
    ACAdder a(vala,~valb + 1);
    a.operate();

    return vala;
}



