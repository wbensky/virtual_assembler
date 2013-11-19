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
