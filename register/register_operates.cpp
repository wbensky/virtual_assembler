#include"register_operates.h"

RegisterOperates::RegisterOperates():
    register_buffer(create()),
    symbols_buffer(create_symbols_buffer()),
    rax(register_buffer[0]),
    rbx(register_buffer[1]),
    rcx(register_buffer[2]),
    rdx(register_buffer[3]),
    rsp(register_buffer[4]),
    rdp(register_buffer[5]),
    rsi(register_buffer[6]),
    rdi(register_buffer[7]),
    zf(symbols_buffer[0]),
    sf(symbols_buffer[1]),
    of(symbols_buffer[2]),
    cf(symbols_buffer[3]),pc(0)
{

}



void RegisterOperates::set_register(int address, void * num)
{
    int first= address & 00070;
    int second = address & 00007;
    if(second  == 0)
    {
        register_buffer[(first / 8)]  = *(int *)num;
    }
    else
    {
        unsigned int t= *(char*)num;
        unsigned int* temp = register_buffer + (first / 8);
        *temp  =  (*temp) & (0xFF << 8 * (second - 1));
        *temp = *temp + (t << (8 * (second - 1)));
    }
}

void RegisterOperates::get_register(int address, void *num)
{
    int first = address & 00070;
    int second = address & 00007;

    if(second == 0)
    {
        std::cout << "here" << "\n";
        *(int*)num = register_buffer[(first / 8)];
    }
    else
    {
        unsigned int temp = register_buffer[first /8];
        *(char *)num = 0xff & (temp >> 8 * (second - 1));
    }
}

void RegisterOperates::set_zf(bool value)
{
    sf = value;
}

bool RegisterOperates::get_zf()
{
    return zf;
}

void RegisterOperates::set_sf(bool value)
{
    sf = value;
}
bool RegisterOperates::get_sf()
{
    return sf;
}

void RegisterOperates::set_of(bool value)
{
    of = value;
}

bool RegisterOperates::get_of()
{
    return of;
}

void RegisterOperates::set_cf(bool value)
{
    cf = value;
}

bool RegisterOperates::get_cf()
{
    return cf;
}

void RegisterOperates::set_pc(unsigned int value)
{
    pc = value;
}

unsigned int RegisterOperates::get_pc()
{
    return pc;
}



void RegisterOperates::print()
{
    std::cout << "rax:" << rax <<"\n";
    std::cout << "rbx:" << rbx <<"\n";
    std::cout << "rcx:" << rcx <<"\n";
    std::cout << "rdx:" << rdx <<"\n";
    std::cout << "rsp:" << rsp <<"\n";
    std::cout << "rdp:" << rdp <<"\n";
    std::cout << "rsi:" << rsi <<"\n";
    std::cout << "rdi:" << rdi <<"\n";
    std::cout << "zf, sf, of, cf" << zf << sf<< of << cf << "\n";
    std::cout << "pc:" << pc<<"\n";
    for(int i = 0; i< 8; i++)
        std::cout << "buffer: "<< register_buffer[i] << "\n";
}
