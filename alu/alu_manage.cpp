#include"alu_manage.h"

ALUManage::ALUManage(int cont, int a, int b):
    controller(cont),vala(a), valb(b)
{
}

int ALUManage::select_operate()
{

    switch(controller)
    {
        case 02200:
            alu = new ACAdder(vala, valb);
            return alu->operate();
        case 02201:
            alu = new Suber(vala, valb);
            return alu->operate();
        defalut:
            return vala;
    }
    return 0;
}

