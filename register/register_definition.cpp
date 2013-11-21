#include "register_definition.h"

RegisterDefinition::RegisterDefinition()
{
}

int RegisterDefinition::get_binary(std::string key_register)
{
    if(register_definition.find(key_register) != register_definition.end())
        return register_definition[key_register];
    return -1;
}


std::map<std::string, int> RegisterDefinition::\
        register_definition = {
        {"rax", 0x00},
        {"raxll", 0x01},
        {"raxlh", 0x02},
        {"raxhl", 0x03},
        {"raxhh", 0x04},

        {"rbx", 0x10},
        {"rbxll", 0x11},
        {"rbxlh", 0x12},
        {"rbxhl", 0x13},
        {"rbxhh", 0x14},

        {"rcx", 0x20},
        {"rcxll", 0x21},
        {"rcxlh", 0x22},
        {"rcxhl", 0x23},
        {"rcxhh", 0x24},

        {"rdx", 0x30},
        {"rdxll", 0x31},
        {"rdxlh", 0x32},
        {"rdxhl", 0x33},
        {"rdxhh", 0x34},

        {"rsp", 0x40},
        {"rspll", 0x41},
        {"rsplh", 0x42},
        {"rsphl", 0x43},
        {"rsphh", 0x44},

        {"rdp", 0x50},
        {"rdpll", 0x51},
        {"rdplh", 0x52},
        {"rdphl", 0x53},
        {"rdphh", 0x54},

        {"rsi", 0x60},
        {"rsill", 0x61},
        {"rsilh", 0x62},
        {"rsihl", 0x63},
        {"rsihh", 0x64},

        {"rdi", 0x70},
        {"rdill", 0x71},
        {"rdilh", 0x72},
        {"rdihl", 0x73},
        {"rdihh", 0x74},

        {"zf", 0x80},
        {"sf", 0x81},
        {"of", 0x82},
        {"cf", 0x83},
        {"pc", 0x84}};
