#ifndef VA_COMPILE_COMPILE_MANAGE_H_
#define VA_COMPILE_COMPILE_MANAGE_H_

#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<iostream>

class CompileManage
{
    private:
        std::vector<std::string> code_file;
        std::vector<unsigned char> binary_file;
        std::map<std::string, int> labels_record;
        std::vector <std::string> error_record;
        std::map <std::string, int> vars_record;

    public:
        CompileManage();
        void read_code_from_file(std::string );
        void get_labels();
        void change_label(int, int );
        bool is_labels(std::string ,std::string &);
        bool is_vars(std::string, std::string&); 
        void operate_code_file();

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

        //print test
        void print_labels_record();
        void print_vars_record();
        void print_binary_file();
        void print_code_file();
        void print_error_record();
        void print_all();
};
#endif
