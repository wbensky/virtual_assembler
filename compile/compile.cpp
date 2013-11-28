#include"compile.h"

std::set<std::string> CompileManage::jmp_instructions ={
    "jmp",
    "je",
    "jne",
    "js",
    "jns",
    "jg",
    "jge",
    "jl",
    "jle",
    "ja",
    "jae",
    "jb",
    "jbe"
};

CompileManage::CompileManage()
{
}

void CompileManage::read_code_from_file(std::string file_name)
{
    char temp[300];
    std::ifstream input(file_name);
    while(input.getline(temp, 100))
    {
        code_file.push_back(temp);
    }
}

void CompileManage::get_labels()
{
    std::string::size_type n;
    std::string temp;
    std::string error_temp;

    for(int i = 0; i< code_file.size(); i++)
    {
        temp = code_file[i];
        n = temp.find(':');
        if(n != std::string::npos)
        {
            if(is_labels( code_file[i].substr(0, n), error_temp) == false)
                error_record.push_back(error_temp + "at line " + std::to_string(i + 1));
            else
                labels_record[code_file[i].substr(0, n)] = -1;
        }
    }
}

bool CompileManage::is_vars(std::string var, std::string &error_temp)
{
    if(vars_record.find(var) != vars_record.end())
    {
        error_temp = "syntax error: var repeat";
        return false;
    }

    if(var[0] > '0' && var[0] < '9')
    {
        error_temp = "syntax error: var spell error";
        return false;
    }

    for(int i = 1; i< var.size(); i++ )
    {
        if((var[i] <= '9' && var[i] >= '0') ||
                (var[i] <= 'z' && var[i] >= 'a') ||
                (var[i] >= 'A' && var[i] <= 'Z') ||
                var[i] == '_')
            continue;
        error_temp = "syntax error: label spell error";
        return false;
    }
    return true;
}

bool CompileManage::is_labels(std::string label, std::string &error_temp)
{
    if(labels_record.find(label) != labels_record.end())
    {
        error_temp = "syntax error: label repeat";
        return false;
    }

    if(label[0] > '0' && label[0] < '9')
    {
        error_temp = "syntax error: label spell error";
        return false;
    }

    for(int i = 1; i< label.size(); i++ )
    {
        if((label[i] <= '9' && label[i] >= '0') ||
                (label[i] <= 'z' && label[i] >= 'a') ||
                (label[i] >= 'A' && label[i] <= 'Z') ||
                label[i] == '_')
            continue;
        error_temp = "syntax error: label spell error";
        return false;
    }
    return true;
}

void CompileManage::operate_code_file()
{
    std::string::size_type n;
    get_labels();
    for(int i = 0; i< code_file.size(); i++)
    {
        std::string temp = code_file[i];
        n = temp.find(".data");
        if(n !=  std::string::npos)
        {
            i = get_data(i);
            continue;
        }

        n = temp.find(".usect");
        if(n !=  std::string::npos)
        {
            i = get_usect(i);
            continue ;
        }

        n = temp.find(".text");
        if(n != std::string::npos)
        {
            i = get_text(i);
            continue;
        }
    }
}

int CompileManage::get_int_from_string(std::string str,int &num_end)
{
    int len_str = str.size();
    int flag = 0;
    int start;
    int end;
    for (start= 0 ; start< len_str && (str[start] < '0' ||str[start] > '9' ); start++)
    {
        if(str[start] == '-')
        {
            flag = 1;
            break;
        }
    }
    for(;start < len_str && (str[start] < '0' || str[start] > '9'); start++)
        ;
    for(end = start; end < len_str &&str[end] <= '9' && str[end] >= '0'; end ++)
        ;
    num_end = end;
    if(flag == 1)
        return -std::stoi(str.substr(start, end -start));
    num_end = end;
    return std::stoi(str.substr(start, end -start));
}

unsigned long  CompileManage::get_uint_from_string(std::string str, int& num_end)
{
    int len_str = str.size();
    int flag = 0;
    int start;
    int end;

    for( start = 0;start < len_str && (str[start] < '0' || str[start] > '9'); start++)
        ;
    for(end = start; end < len_str &&str[end] <= '9' && str[end] >= '0'; end ++)
        ;
    num_end = end;
    return std::stoul(str.substr(start, end -start));
}

void CompileManage::get_int_from_usect(int pos)
{
    int temp;
    change_var(get_var(pos));

    std::string temp_str = code_file[pos];
    std::string::size_type n = temp_str.find(',');
    temp = get_int_from_string(temp_str.substr(n + 1, temp_str.size()),temp);
    for(int i = 0 ;i < temp; i++)
        write_into_binary_file(0);
}

void CompileManage::get_uint_from_usect(int pos)
{
    int temp;
    change_var(get_var(pos));

    std::string temp_str = code_file[pos];
    std::string::size_type n = temp_str.find(',');
    temp = get_int_from_string(temp_str.substr(n + 1, temp_str.size()),temp);
    for(int i = 0 ;i < temp; i++)
        write_into_binary_file(1);
}

std::string CompileManage::get_var(int pos)
{
    int i, j, k;
    std::string::size_type n;
    std::string temp = code_file[pos];
    n = temp.find(",");
    if(n == std::string::npos)
    {
        for( j = 0; j < temp.size(); j ++)
            if(temp[j] != ' ' && temp[j] != '\t')
                error_record.push_back("syntax error: var error at line" + std::to_string(i));
        return ""; 
    }
    for(k = n -1; temp[k] == ' '||temp[k] == '\t'; k--)
        ;
    for(j=k ; temp[j] != ' ' && temp[j] != '\t';j-- )
        ;

    return temp.substr(j + 1, k-j);
}
void CompileManage::get_vars(int pos)
{
    int i, j,k;
    std::string::size_type n;
    std::string::size_type pos_start;
    std::string::size_type pos_end;
    std::string error_str;

    for(i = pos + 1;
            code_file[i].find(".end_usect") == std::string::npos;
            i++)
    {
        std::string var = get_var(i);
        if (var.size() == 0)
            continue;
        if(is_vars(var, error_str) == true)
        {
            vars_record[var] = -1;
        }
        else
        {
            error_record.push_back(error_str + "at line:" + std::to_string(i));
        }

    }
}

int CompileManage::get_usect(int pos)
{
    int i;
    std::string::size_type n;
    get_vars(pos);
    for( i= pos + 1;
            code_file[i].find(".end_usect") == std::string::npos;
            i++)
    {
        if((n = code_file[i].find(":")) != std::string::npos)
            change_label(i, n);
        if((n = code_file[i].find(".int")) != std::string::npos)
        {
            get_int_from_usect(i);
            continue;
        }

        if((n = code_file[i].find(".uint")) != std::string::npos)
        {
            get_uint_from_usect(i);
            continue;
        }
    }
    return i;
}



int CompileManage::get_text(int pos)
{
    int i;
    std::string::size_type n;
    for(i = pos + 1;
            code_file[i].find(".end") ==std::string::npos;
            i++)
    {
        InstructionStructure temp;
        if(string_is_empty(code_file[i]))
            continue;
        temp.label = get_label(code_file[i]);
        temp.instruction = get_instruction(code_file[i]);
        temp.arg1 = get_arg1(code_file[i]);
        temp.arg2 = get_arg2(code_file[i]);
        instructions_record.push_back(temp);
    }
    add_nop_conflict();
    add_nop_jmp();
    return i;
}

void CompileManage::add_nop_conflict()
{

    InstructionStructure temp;
    temp.instruction = "nop";
    for(auto it = instructions_record.begin(); it != instructions_record.end(); it++)
    {
        auto next = ++it;
        it--;
        if(next == instructions_record.end())
            break;
        if(it -> arg1!="" && next ->arg1 != ""&&next->arg2 != "")
            if(it->arg1 == next->arg1 || it->arg1 == next->arg2)
            {    
                instructions_record.insert(next,temp);
                continue; 
            }
         if(it -> arg2!="" && next ->arg1 != ""&&next->arg2 != "")
            if(it->arg2 == next->arg1 || it->arg2 == next->arg2)
            { 
                instructions_record.insert(next,temp);
                continue; 
            } 
    
    }

}

void CompileManage::add_nop_jmp()
{
    for(auto it = instructions_record.begin(); it != instructions_record.end(); it ++)
        if(jmp_instructions.find(it -> instruction)!= jmp_instructions.end())
        {
            InstructionStructure temp;
            it ++;
            temp.instruction = "nop";
            instructions_record.insert(it, 2, temp);
            it --;
        }
}

std::string CompileManage::get_arg1(std::string str)
{
    std::string::size_type n = str.find(":");
    int end;
    int start;

    if(n == std::string::npos)
        start = 0;
    else
        start = n + 1;
    for(; str[start] == ' ' || str[start] == '\t'; start++ )
        ;
    for(; start < str.size()&&str[start] >= 'a' && str[start] <= 'z'; start++ )
        ;
    if(start == str.size())
        return "";
    for(;str[start] ==' ' || str[start] == '\t'; start++)
        ;
    if(start == str.size())
        return "";

    for(end = start; end < str.size()&&str[end] >= 'a' && str[end] <= 'z' ; end++)
        ;
    return str.substr(start, end - start);
}

std::string CompileManage::get_arg2(std::string str)
{
    int start, end;
    std::string::size_type n = str.find(",");
    if(n == std::string::npos)
        return "";
    start = n + 1;
    for(; str[start]== ' ' || str[start] == '\t'; start++)
        ;

    for(end = start; end < str.size() && str[end] >='a' && str[end] <='z'; end++)
        ;

    return str.substr(start, end - start);
}

std::string CompileManage::get_instruction(std::string str)
{
    std::string::size_type n= str.find(":");
    int start = 0;
    int end;

    if (n != std::string::npos)
        start = n + 1;
    for(; str[start] ==' ' || str[start] == '\t'; start ++)
        ;
    for(end = start; str[end] <= 'z' && str[end] >= 'a'; end ++)
        ;

    return str.substr(start, end - start);
}


std::string CompileManage::get_label(std::string str)
{
    int end;
    std::string::size_type n = str.find(":");

    if(n == std::string::npos)
        return "";
    for( end = n -1; str[end] == ' ' || str[end] == '\t'; end--)
        ;

    return str.substr(0, end + 1);
}

bool CompileManage::string_is_empty(std::string str)
{
    for(auto item: str)
        if( !(item == ' '|| item == '\t'))
            return false;

    return true;
}

int CompileManage::get_data(int pos)
{
    int i;
    std::string::size_type n;
    for( i = pos + 1; code_file[i].find(".end_data")== std::string::npos ; i++)
    {
        if((n = code_file[i].find(":")) != std::string::npos)
            change_label(i , n);
        if((n = code_file[i].find(".int")) != std::string::npos)
        {
            get_int_from_data(i);
            continue;
        }
        if((n = code_file[i].find(".uint")) != std::string::npos)
        {
            get_uint_from_data(i);
            continue;
        }
    }
    return i;
}



void CompileManage::write_into_binary_file(int num)
{
    unsigned char *p = (unsigned char*)&num;
    for(int i = 0 ;i < 4; i++)
        binary_file.push_back( *(p + i));
}

void CompileManage::write_into_binary_file(unsigned long num)
{
    unsigned char *p = (unsigned char *)&num;
    for(int i = 0; i< 4; i++)
        binary_file.push_back(*(p + i));
}

void CompileManage::get_uint_from_data(int row)
{
    std::string temp = code_file[row];
    std::string::size_type n = code_file[row].find(".uint");
    if(!(temp[n + 5] == ' ' || temp[n + 4] == '\t'))
    {
        error_record.push_back("syntax error: is .uint? at line: " + std::to_string(row));
    }
    temp = temp.substr(n + 5);

    for(int i = n + 5; ; i++)
    {
        int num_end = 0;

        write_into_binary_file(get_uint_from_string(temp, num_end));
        for(; num_end != temp.size() &&
                !(temp[num_end] <='9' && temp[num_end] >= '0');
                num_end++ )
            ;
        if(num_end == temp.size())
            break;
        temp = temp.substr(num_end, temp.size());
    }
}

void CompileManage::get_int_from_data(int row)
{
    std::string temp = code_file[row];
    std::string::size_type n = code_file[row].find(".int");

    if(!(temp[n + 4] == ' ' || temp[n + 4] == '\t'))
    {
        error_record.push_back("syntax error: is .int? at line: " + std::to_string(row));
    }
    temp = temp.substr(n + 4);
    for(int i = n + 4; ; i++)
    {
        int num_end = 0;
        write_into_binary_file(get_int_from_string(temp, num_end));
        for(; num_end != temp.size() &&
                !(temp[num_end] <='9' && temp[num_end] >= '0')&&
                temp[num_end]!='-';
                num_end++ )
            ;
        if(num_end == temp.size())
            break;
        temp = temp.substr(num_end, temp.size() );
    }
}

void CompileManage::change_label(int row, int col)
{
    labels_record[code_file[row].substr(0, col)]  = binary_file.size();
}

void CompileManage::change_var(std::string str)
{
    vars_record[str] = binary_file.size();
}

void CompileManage::print_all()
{
    //print_labels_record();
    //print_vars_record();
    //print_error_record();
    //print_code_file();
    //print_binary_file();
    print_instructions_record();
}

void CompileManage::print_instructions_record()
{
    std::cout << "instructions record:"<<std::endl;
    for(auto it: instructions_record)
        std::cout << "l:" + it.label +"\t" +
            it.instruction + "\ta1:" +
            it.arg1  +  "\ta2:" + it.arg2 <<std::endl;
    std::cout << std::endl;
}

void CompileManage::print_vars_record()
{
    std::cout << "vars_record:" <<std::endl;

    for(auto it: vars_record)
    {
        std::cout << it.first <<":\t" << it.second <<"\n";
    }
    std::cout<<std::endl;
}

void CompileManage::print_labels_record()
{
    std::cout << "labels_record;" <<std::endl;
    for(auto it = labels_record.begin();it != labels_record.end(); it++)
    {
        std::cout << it->first <<":\t" << it->second <<"\n";
    }
    std::cout <<std::endl;
}

void CompileManage::print_binary_file()
{
    std::cout<< "binary_file:"<<std::endl;
    for(int i = 0; i < binary_file.size() / 8 + 1; i++)
    {
        for(int j = 0;i * 8 + j < binary_file.size() &&j < 8; j++)
            std::cout << std::hex <<(int)binary_file[i * 8 + j] << '\t';
        std::cout<<std::endl;
    }
}

void CompileManage::print_code_file()
{
    std::cout << "code_file:" <<std::endl;
    for(int i= 0; i< code_file.size(); i++)
    {
        std::cout << code_file[i] << std::endl;
    }
}

void CompileManage::print_error_record()
{
    std::cout << "error_file:" <<std::endl;
    for(int i= 0; i< error_record.size(); i++)
    {
        std::cout << error_record[i] << std::endl;
    }
}

