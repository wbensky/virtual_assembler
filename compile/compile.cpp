#include"compile.h"

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
    //std::cout << labels_record.size()<< std::endl;
    //std::cout << error_record.size()<<std::endl;
    //std::map<std::string, int>::iterator it = labels_record.begin();
    //for(; it != labels_record.end(); ++it)
    //{
    //   std::cout << it->first <<": " << it->second<<std::endl;
    //}
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
    }
}

void CompileManage::get_int_from_usect(int)
{
    
}

void CompileManage::get_uint_from_usect(int)
{
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
        int num_start=0;
        int num_end = 0;
        for(; temp[num_start] <'0' || temp[num_start] > '9';
                num_start++ )
            ;
        for(num_end = num_start;
                temp[num_end] <= '9' && temp[num_end] >= '0';
                num_end++ )
            ;

        write_into_binary_file( std::stoul(temp.substr(num_start,num_end - num_start)) );
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
        int num_start=0;
        int num_end = 0;
        int flag = 0;
        for(; temp[num_start] <'0' || temp[num_start] > '9';
                num_start++ )
        {
            if(temp[num_start]== '-')
            {
                num_start += 1;
                flag = 1;
                break;
            }
        }
        for(num_end = num_start;
                temp[num_end] <= '9' && temp[num_end] >= '0';num_end++ )
            ;

        if(flag == 1)
            write_into_binary_file( -std::stoi(temp.substr(num_start,num_end - num_start)) );
        else
            write_into_binary_file( std::stoi(temp.substr(num_start,num_end - num_start)) );
        for(; num_end != temp.size() &&
                !(temp[num_end] <='9' && temp[num_end] >= '0');
                num_end++ )
            ;
        if(num_end == temp.size())
            break;
        temp = temp.substr(num_end, temp.size());
    }
}

void CompileManage::change_label(int row, int col)
{
    labels_record[code_file[row].substr(0, col)]  = binary_file.size();
}

void CompileManage::print_all()
{
    print_labels_record();
    print_vars_record();
    //print_error_record();
    //print_code_file();
    print_binary_file();
}

void CompileManage::print_vars_record()
{
    std::cout << "vars_record" <<std::endl;
    std::map<std::string, int>::iterator it = vars_record.begin();

    for(;it != vars_record.end(); it++)
    {
        std::cout << it->first <<":\t" << it->second <<"\n";
    }
}

void CompileManage::print_labels_record()
{
    std::cout << "labels_record" <<std::endl;
    std::map<std::string, int>::iterator it = labels_record.begin();
    for(;it != labels_record.end(); it++)
    {
        std::cout << it->first <<":\t" << it->second <<"\n";
    }
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
