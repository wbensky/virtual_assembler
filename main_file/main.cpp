#include<iostream>
#include<string>
#include<map>
#include<vector>
#include"../compile/compile.h"

void analyse_instruction(int argc, char **argv);

int main(int argc, char **argv)
{
    analyse_instruction(argc - 1, argv + 1);
    return 0;
}

void analyse_instruction(int argc, char **argv)
{
    std::string instruction(argv[0]);

    if(instruction == "-c")
    {
        CompileManage cm(argv[1]);
        cm.operate_code_file();
        cm.print_all();
    }
    else
    {
        std::cout << "the insturction is illegal;"<< std::endl;
        return ;
    }
}
