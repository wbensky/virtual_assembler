#ifndef VA_REGISTER_DEFINITION_H_
#define VA_REGISTER_DEFINITION_H_
#include<string>
#include<map>

class RegisterDefinition
{
    private:
        static std::map<std::string, int> register_definition;
    public:
        RegisterDefinition();

        int get_binary(std::string);
};
#endif
