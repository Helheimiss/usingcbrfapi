#pragma once
#include <string>


class valute {
    std::string NumCode;
    std::string Name;
    double VunitRate;
public:
    valute(std::string_view NumCode, std::string_view Name, double VunitRate);

    std::string_view GetNumCode();
    std::string_view GetName();
    double GetVunitRate();
};
