#include"alu_manage.h"

ALUManage::ALUManage(int cont, int a, int b):
    controller(cont),vala(a), valb(b)
{
}

int ALUManage::select_operate()
{
    alu = NULL;
    switch(controller)
    {
        case 0x40:
            alu = new ACAdder(vala, valb);
            break;
        case 0x41:
            alu = new Suber(vala, valb);
            break;
        case 0x42:
            alu = new Muler(vala, valb);
            break;
        case 0x43:
            alu = new Diver(vala, valb);
        case 0x56:
            alu = new Noter(vala, valb);
        case 0x57:
            alu = new Xorer(vala, valb);
        case 0x58:
            alu = new Orer(vala, valb);
        case 0x59:
            alu = new Ander(vala, valb);
        case 0x61:
            alu = new Cmper(vala, valb);
        default:
            return vala;
    }
    if(alu != NULL)
        return alu->operate();
    return 0;
}


