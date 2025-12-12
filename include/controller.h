#pragma once
#include <string>


class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    static std::string GetValueByCharCode(std::string& CharCode);
};


class Convertor
{
public:
    Convertor() = default;
    ~Convertor() = default;

    static std::string ConvertValute(double count, std::string& CharCode);
    static std::string ConvertValuteToValute(double count, std::string& CharCode1, std::string& CharCode2);
};


