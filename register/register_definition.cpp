#include "register_definition.h"

RegisterDefinition::RegisterDefinition():
    register_definition(create_register_definition())
{
}

int RegisterDefinition::get_binary(std::string key_register)
{
    if(register_definition.find(key_register) != register_definition.end())
        return register_definition[key_register];
    return -1;
}


std::map<std::string, int>& RegisterDefinition::
create_register_definition()
{
    static std::map<std::string, int>m;
    static int mutex = 0;
    if(mutex == 0)
    {
        mutex = 1;
        m["rax"] = 00000;
        m["raxll"] = 00001;
        m["raxlh"] = 00002;
        m["raxhl"] = 00003;
        m["raxhh"] = 00004;

        m["rbx"] = 00010;
        m["rbxll"] = 00011;
        m["rbxlh"] = 00012;
        m["rbxhl"] = 00013;
        m["rbxhh"] = 00014;

        m["rcx"] = 00020;
        m["rcxll"] = 00021;
        m["rcxlh"] = 00022;
        m["rcxhl"] = 00023;
        m["rcxhh"] = 00024;

        m["rdx"] = 00030;
        m["rdxll"] = 00031;
        m["rdxlh"] = 00032;
        m["rdxhl"] = 00033;
        m["rdxhh"] = 00034;

        m["rsp"] = 00040;
        m["rspll"] = 00041;
        m["rsplh"] = 00042;
        m["rsphl"] = 00043;
        m["rsphh"] = 00044;

        m["rdp"] = 00050;
        m["rdpll"] = 00051;
        m["rdplh"] = 00052;
        m["rdphl"] = 00053;
        m["rdphh"] = 00054;

        m["rsi"] = 00060;
        m["rsill"] = 00061;
        m["rsilh"] = 00062;
        m["rsihl"] = 00063;
        m["rsihh"] = 00064;

        m["rdi"] = 00070;
        m["rdill"] = 00071;
        m["rdilh"] = 00072;
        m["rdihl"] = 00073;
        m["rdihh"] = 00074;

        m["zf"] = 00100;
        m["sf"] = 00101;
        m["of"] = 00102;
        m["cf"] = 00103;
        m["pc"] = 00104;
    }
    return m;
}
