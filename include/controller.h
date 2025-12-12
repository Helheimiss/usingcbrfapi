#pragma once
#include <string>


class Convertor
{
private:

public:
    Convertor() = default;
    ~Convertor() = default;

    double GetCountValute(double count, std::string CharCode);
    double ConvertValute(double count, std::string CharCode1, std::string CharCode2);
};


