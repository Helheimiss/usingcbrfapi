#pragma once
#include <string>


class Convertor
{
public:
    Convertor() = default;
    ~Convertor() = default;

    static double ConvertValute(double count, std::string& CharCode);
    static double ConvertValuteToValute(double count, std::string& CharCode1, std::string& CharCode2);
};


