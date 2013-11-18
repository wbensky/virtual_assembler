#include"alu_manage.h"


ALUManage::ALUManage()
{
}


unsigned int ALUManage::ac_uadder(unsigned int vala,
        unsigned int valb,
        int &carry)
{
    std::bitset<32> v1(vala);
    std::bitset<32> v2(valb);
    std::bitset<33> carry_set;
    std::bitset<32> dst;
    unsigned int result  = 0;
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
    carry = carry_set[32];
    return result;
}

int ALUManage::ac_adder(int vala,
        int valb,
        int &carry)
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
    carry = carry_set[32];
    return result;
}

