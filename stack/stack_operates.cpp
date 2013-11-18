#include"stack_operates.h"

StackOperates::StackOperates():stack_buffer(create_buffer())
{
}

unsigned int(& StackOperates::create_buffer())[1000]
{
    static unsigned int buffer [1000];
    return buffer;
}

void StackOperates::pushl(unsigned int value)
{
    int rsp = reg.get_rsp();
    stack_buffer[rsp] = value;
    reg.set_rsp(rsp + 1);
}

int  StackOperates::is_empty()
{
    return reg.get_rsp() > 0 ? 0 : 1;
}
unsigned int StackOperates::popl()
{
    if(is_empty())
    {
        //error manage module
        return 0;
    }
    int rsp = reg.get_rsp();
    reg.set_rsp(rsp - 1);
    return stack_buffer[rsp - 1];
}
