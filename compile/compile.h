#ifndef VA_COMPILE_COMPILE_MANAGE_H_
#define VA_COMPILE_COMPILE_MANAGE_H_

#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<algorithm>
#include<iostream>
#include<set>
#include<list>
#include"../instruction/instruction_binary.h"
#include"../register/register_definition.h"

class InstructionStructure
{
    public:
        std::string label;
        std::string instruction;
        std::string arg1;
        std::string arg2;
};

class CompileManage
{
    private:
        std::vector<std::string> code_file;
        std::vector<unsigned char> binary_file;
        std::map<std::string, int> labels_record;
        std::vector <std::string> error_record;
        std::map <std::string, int> vars_record;
        std::string in_file_name;
        std::string out_file_name;
        std::string syntax_error;
        //about instruction
        static std::set<std::string> jmp_instructions;
        static std::set<std::string> pseudoinstructions;
        
        std::list<InstructionStructure> instructions_record;
        InstructionBinary insb;
        RegisterDefinition regd;

    public:
        CompileManage(std::string);
        CompileManage(std::string, std::string);

        //utils
        bool string_is_empty(std::string);

        //operate label
        void get_labels();
        void change_label(int, int );
        bool is_labels(std::string ,std::string &);
        bool is_vars(std::string, std::string&);
        void operate_code_file();
        void init_register_pc();
        void change_var(std::string);

        //get_data operates
        int get_data(int);
        void get_int_from_data(int);
        void get_uint_from_data(int);
        void write_into_binary_file(int);
        void write_into_binary_file(unsigned long);

        int get_usect(int );
        void get_int_from_usect(int);
        void get_uint_from_usect(int);
        void get_vars(int);
        std::string get_var(int);
        int get_int_from_string(std::string, int&);
        unsigned long get_uint_from_string(std::string, int&);

        // operate text;
        int get_text(int );
        std::string get_label(std::string);
        std::string get_instruction(std::string);
        std::string get_arg1(std::string);
        std::string get_arg2(std::string);
        void add_nop_jmp();
        void add_nop_conflict();
        void update_labels_record();
        void update_instructions_to_binary();
        int get_arg_binary(std::string);

        // error operations
        bool find_data_error(int);

        bool uniq_pesudoi_error(std::string, std::string ,int pos);
        bool find_oppside_pesudoi(std::string, int pos);
        bool find_error_pesudoi(std::vector<std::string>&,std::string , int pos);
        bool find_data_num_error(int pos, std::string);
        bool find_data_int_num_error(int ,std::string, int);
        //print test
        void print_instructions_record();
        void print_labels_record();
        void print_vars_record();
        void print_binary_file();
        void print_code_file();
        void print_error_record();
        void print_all();
};
#endif
