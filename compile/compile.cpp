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

std::set<std::string> CompileManage::pseudoinstructions={
    ".data",
    ".end_data",
    "usect",
    ".end_usect",
    ".int",
    ".uint",
    ".text",
    "end"
};

CompileManage::CompileManage(std::string file_name):
    in_file_name(file_name),syntax_error("syntax_error: ")
{
    out_file_name = in_file_name.substr(0, in_file_name.find('.')) + ".bin";
}

CompileManage::CompileManage(std::string in_file, std::string out_file):
    in_file_name(in_file),
    out_file_name(out_file),
    syntax_error("syntax_error: ")
{
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


/*
 * error type:
 *     var repeat definition
 *     var begin with number
 *     var only make up with number ,'_' and letter
 * */
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

/*
 * the same with is_var
 * */
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

void CompileManage::init_register_pc()
{
    /*
     * mov pc .text
     * nop
     * nop
     * */
    std::list<InstructionStructure> instructions_record;
    InstructionStructure temp;
    temp.label = "";
    temp.instruction = "irmovl";
    temp.arg1 = "pc";
    temp.arg2 = "11";
    instructions_record.push_back(temp);
    temp.arg1 = "";
    temp.arg2 = "";
    temp.instruction = "nop";
    instructions_record.push_back(temp);
    instructions_record.push_back(temp);
    update_instructions_to_binary(instructions_record);
}

void CompileManage::operate_code_file()
{
    std::string::size_type n;
    char temp[300];

    std::ifstream input(in_file_name);

    while(input.getline(temp, 100))
    {
        code_file.push_back(temp);
    }

    get_labels(); //add error operations
    init_register_pc();

    for(int i = 0; i< code_file.size(); i++)
    {
        std::string temp = code_file[i];
        n = temp.find(".data");

        if(n !=  std::string::npos) //add error operations
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
            text_position = binary_file.size();
            i = get_text(i);
            continue;
        }

    }
        //std::cout << text_position << std::endl;
        write_into_binary_file(text_position, 2);
        output_file();
}

void CompileManage::output_file()
{
    if(error_record.size() != 0)
    {
        print_error_record();
        return ;
    }
    std::ofstream output(out_file_name);
    for (auto item:binary_file)
        output<<std::hex <<(int) item <<std::endl;
}

int CompileManage::get_int_from_string(std::string str,int &num_end)
{
    int len_str = str.size();
    int flag = 0;
    int start;
    int end;
    for (start = 0 ; start< len_str && (str[start] < '0' ||str[start] > '9' ); start++)
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
            error_record.push_back(syntax_error + "illegal pesudoi at line:" + std::to_string(i));
        }
    }
}

int CompileManage::get_usect(int pos)
{
    int i;
    std::string::size_type n;

    if(find_usect_error(pos))
        return pos + 1;

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

    if(uniq_pesudoi_error(".text",code_file[pos], pos))
        return pos + 1;
    if(find_oppside_pesudoi(".end", pos) == false)
        return pos + 1;

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
    if(find_text_error()== true)
        return pos + 1;

    add_nop_conflict();
    add_nop_jmp();
    update_labels_record();
    update_instructions_to_binary();

    return i;
}

int CompileManage::get_arg_binary(std::string arg1)
{
    if(arg1 == "")
        return 0;
    if(labels_record.find(arg1) != labels_record.end())
        return labels_record[arg1];
    if(vars_record.find(arg1) != vars_record.end())
        return vars_record[arg1];
    if(regd.get_binary(arg1) != -1)
        return regd.get_binary(arg1);
    return std::stoi(arg1);
}

void CompileManage::update_instructions_to_binary()
{
    int instruction;
    int var1;
    int var2;
    unsigned char ch;
    for(auto item: instructions_record)
    {
        //std::cout << item.instruction << "\t"<< item.arg1<<"\t" <<
        //   item.arg2<<std::endl;
        instruction = insb.get_binary(item.instruction);
        var1 = get_arg_binary(item.arg1);
        var2 = get_arg_binary(item.arg2);
        //std::cout << ""<<instruction<<" \t" << var1<<"\t" <<var2<<std::endl;
        ch = instruction;
        binary_file.push_back(ch);
        ch = var1;
        binary_file.push_back(ch);
        write_into_binary_file(var2);
    }
}

void CompileManage::update_instructions_to_binary(std::list<InstructionStructure> & instructions_record)
{
    int instruction;
    int var1;
    int var2;
    unsigned char ch;
    for(auto item: instructions_record)
    {
        //std::cout << item.instruction << "\t"<< item.arg1<<"\t" <<
        //   item.arg2<<std::endl;
        instruction = insb.get_binary(item.instruction);
        var1 = get_arg_binary(item.arg1);
        var2 = get_arg_binary(item.arg2);
        //std::cout << ""<<instruction<<" \t" << var1<<"\t" <<var2<<std::endl;
        ch = instruction;
        binary_file.push_back(ch);
        ch = var1;
        binary_file.push_back(ch);
        write_into_binary_file(var2);
    }
}


void CompileManage::update_labels_record()
{
    int c = 0;
    for(auto item : instructions_record)
    {
        if(item.label != "")
        {
            labels_record[item.label] = c * 6 + binary_file.size();
        }
        c++;
    }
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

    for(end = start; end < str.size() && ((str[end] >='a' && str[end] <='z') || (str[end] <= '9'&& str[end] >= 0) ||str[end] == '_'); end++)
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

    if(find_data_error(pos))
    {     std::cout << "1"<<std::endl;
        return pos + 1;
    }
    for( i = pos + 1; code_file[i].find(".end_data")== std::string::npos ; i++)
    {
        if((n = code_file[i].find(":")) != std::string::npos)
            change_label(i, n);
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

bool CompileManage::find_text_error()
{
    bool flag = false;

    for(auto item: instructions_record)
    {
        if(insb.get_binary(item.instruction) == -1)
        {
            error_record.push_back(syntax_error + "instruction" + item.instruction + " not exist");
            flag = true; 
        } 
    }
    return flag;
}


// find data segement error


void CompileManage::write_into_binary_file(int num)
{
    unsigned char *p = (unsigned char*)&num;
    for(int i = 0 ;i < 4; i++)
        binary_file.push_back( *(p + i));
}

void CompileManage::write_into_binary_file(int num, int position)
{
    unsigned char *p = (unsigned char*)&num;
    for(int i = 0 ;i < 4; i++)
        binary_file[position + i] = ( *(p + i));
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



//error_opera
bool CompileManage::find_data_error(int pos)
{
    bool flag = false;
    std::vector<std::string> legal_pesudoi;

    if(uniq_pesudoi_error(".data", code_file[pos], pos) == true)
        flag = true;
    if(find_oppside_pesudoi(".end_data", pos) == false)
    {
        flag = true;
        return flag;
    }

    legal_pesudoi.push_back(".int");
    legal_pesudoi.push_back(".uint");
    if(find_error_pesudoi(legal_pesudoi, "end_data", pos) == true)
    {
        flag = true;
        return flag;
    }

    if(find_data_num_error(pos, "end_data"))
    {
        flag = true;
        return flag;
    }

    return flag;
}

bool CompileManage::find_usect_error(int pos)
{
    bool flag = false;
    std::vector<std::string> legal_pesudoi;

    if(uniq_pesudoi_error(".usect", code_file[pos], pos) == true)
        flag = true;
    if(find_oppside_pesudoi(".end_usect", pos) == false)
    {
        flag = true;
        return flag;
    }
    legal_pesudoi.push_back(".int");
    legal_pesudoi.push_back(".uint");

    if(find_error_pesudoi(legal_pesudoi, ".end_usect", pos) == true)
    {
        flag = true;
        return flag;
    }
    // vars error;
    int pre_count = error_record.size();
    get_vars(pos);
    if(pre_count < error_record.size())
       return true; 

    if(find_usect_num_error(pos, "end_usect"))
    {
        flag= true;
        return flag;
    }
    return flag;
}

bool CompileManage::find_usect_num_error(int pos, std::string end_str)
{
    bool flag = false;
    for(int i = pos + 1; code_file[i].find(end_str) == std::string::npos; i++)
    {
        if(code_file[i].find(".int") != std::string::npos)
            if(find_usect_int_num_error(i, code_file[i]) == true)
                flag = true;
        if(code_file[i].find(".uint") != std::string::npos)
            if(find_usect_int_num_error(i, code_file[i]) == true)
                flag = true;
    }
    return flag;
}

bool CompileManage::find_data_num_error(int pos, std::string end_str)
{
    bool flag =false;
    for(int i = pos + 1; code_file[i].find(end_str) == std::string::npos; i++ )
    {
        if(code_file[i].find(".int") != std::string::npos)
            if(find_data_int_num_error(i, code_file[i], -1) == true)
                flag = true;
        if(code_file[i].find(".uint") != std::string::npos)
            if( find_data_int_num_error(i, code_file[i], 1)== true)
                flag = true;

    }
    return flag;
}

bool CompileManage::find_usect_int_num_error(int i, std::string str)
{
    std::string::size_type n;
    int j;
    n = str.find(',');
    if(n == std::string::npos)
    {
        error_record.push_back(syntax_error + "lack a comma at line:" + std::to_string(i));
        return true;
    }

    for(j = n + 1; j < str.size() && (str[j] == ' ' || str[j] == '\t');j++)
        ;
    if(j >= str.size())
    {
        error_record.push_back(syntax_error + "lack num at line:" + std::to_string(i) );
        return true;
    }
    int k = j;
    for(; k< str.size() &&str[k]<= '9' && str[k]>= '0'; k++)
        ;
    if(k >= str.size())
        return false;
    for(; k< str.size()&&(str[k] == ' ' || str[k] == '\t'); k++)
        ;
    if(k < str.size())
    {
        error_record.push_back(syntax_error + "illegal num at line:" + std::to_string(i));
        return true;
    }
        return false;
}
bool CompileManage::find_data_int_num_error(int i,std::string str , int sym)
{
    std::string::size_type n;
    int j;
    bool sy = false;

    n = str.find('.');

    for(j = n + 1; j < str.size() && (str[j] > '9'|| str[j]< '0' || str[j] == '-') ; j++)
        ;

    if(j >= code_file[i].size())
        return true;
    int flag = 0; // num

    for(; j < code_file[i].size() ; j++)
    {
        char c = code_file[i][j];
        //std::cout<< "flag:" << flag <<std::endl;
        //std::cout<< "c:" <<c<<std::endl;
        if(sym == 1)
        {
            if(! (c == ' ' || c== '\t' ||( c >= '0' && c<='9')|| c== ','))
            {
                error_record.push_back(syntax_error + c +  " is illegal character at line:" + std::to_string(i) );
                return true; 
            }
        }
        else if(sym == -1)
            if(! (c == ' ' || c== '\t' ||( c >= '0' && c<='9')|| c== ',' || c== '-'))
            {
                error_record.push_back(syntax_error + c +  " is illegal character at line:" + std::to_string(i) );
                return true; 
            }

        if(flag == 0)
        {
            if(c == ' ' || c == '\t')
            {
                flag = 1; // space after num
                continue;
            }

            if(c  <= '9' &&c >= '0')
            {
                continue;
            }

            if(c == ',')
            {
                flag = 2; // comma after num
                continue;
            }

            if(c == '-')
            {
                error_record.push_back(syntax_error + "'-' is not a num at line: " + std::to_string(i));
                return true;
            }
        }
        if(flag == 1)//space after num
        {
            if(c == ' ' || c == '\t')
            {
                continue; 
            }
            if((c <= '9' && c >='0')||c == '-' )
            {
                error_record.push_back(syntax_error + c + "lack comma ',' " + "at line:" + std::to_string(i) + "at position: " + std::to_string(j));
                return true;
            }
            if(c == ',')
            {
                flag = 2;
                continue;
            }

        }
        if(flag ==2) //comma after num
        {
            if(c == ' ' || c == '\t' )
            {
                flag = 2;
                continue;
            }
            if((c <= '9' && c >='0') || c=='-' )
            {
                flag = 0;
                continue;
            }
            if(c == ',')
            {
                error_record.push_back(syntax_error + "lack a num here at line: " + std::to_string(i) +"at position" +  std::to_string(j));
                return true;
            }
        }
    }
    return sy;
}

bool CompileManage::find_error_pesudoi(std::vector<std::string>& legal_pesudoi, std::string end_str, int pos)
{
    int flag = false;
    std::string::size_type n;
    int j;

    for(int i = pos + 1;code_file[i].find(end_str) == std::string::npos; i++)
    {
        if(code_file[i] == "")
            continue;
        n = code_file[i].find(':');
        for(j = n == std::string::npos? 0: n+1; j < code_file[i].size() && (code_file[i][j] == ' ' || code_file[i][j] == '\t'); j++)
            ;
        if(j >= code_file[i].size())
            continue;
        n = code_file[i].find('.');
        if(n == std::string::npos)
        {   error_record.push_back(syntax_error + "this line should add pesudoinstruction like .int or .uint and so on" + "at line" + std::to_string(i));

            flag = true;
        }

        for(j = n + 1; code_file[i][j] != ' ' && code_file[i][j] != '\t'; j++ )
            ;
        std::string pesu_temp = code_file[i].substr(n, j - n);
        if(find(legal_pesudoi.begin(), legal_pesudoi.end(), pesu_temp) == legal_pesudoi.end())
        {
            error_record.push_back(syntax_error + pesu_temp + "is illegal here at line: " + std::to_string(i));
        }
    }

    return flag;
}

bool CompileManage::uniq_pesudoi_error(std::string pesudoi,
        std::string str,int pos)
{
    int i;
    bool flag = false;
    std::string::size_type n;

    n = str.find(pesudoi);

    for( i = n - 1; ;i--)
    {
        if(i == 0)
            break;
        if(str[i] == ':')
            break;
        if(str[i] != ' ' && str[i] != '\t')
        {
            flag = true;
            error_record.push_back(syntax_error + "is label? at position" + std::to_string(i) + "at line:" + std::to_string(pos));
            break;
        }
    }

    if(code_file[pos][i-1] == ' ' || code_file[pos][i - 0] =='\t')
    {
        error_record.push_back( syntax_error + "error .data;");
        flag =true;
    }

    for( i = n + pesudoi.size(); i < str.size() && (str[i] == ' ' ||str[i] == '\t'); i++ )
        ;
    if(i != str.size())
    {
        error_record.push_back(syntax_error + "position: " + std::to_string(i) + " should not exist; at line: " + std::to_string(pos) );
        flag = true;
    }
    return flag;
}

bool CompileManage::find_oppside_pesudoi(std::string opsi_str, int pos)
{
    std::string::size_type n;
    for(int i = pos + 1; i < code_file.size(); i++)
    {
        if( (n = code_file[i].find(opsi_str)) != std::string::npos)
        {
            if(n+opsi_str.size() >= code_file[i].size() ||
                    code_file[i][n + opsi_str.size()] == ' ' ||
                    code_file[i][n + opsi_str.size()] == '\t')
            {
                if( code_file[i][n - 1] == ' ' || code_file[i][n-1] == '\t')
                {
                    return true;
                }
            }
        }
    }
    return  false;
}

void CompileManage::print_all()
{
    //print_labels_record();
    //print_vars_record();
    //print_error_record();
    //print_code_file();
    //print_binary_file();
    //print_instructions_record();
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

void CompileManage::printd()
{
    std::cout << "debug"<<std::endl;
}
