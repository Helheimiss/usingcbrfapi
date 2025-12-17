#pragma once
#include <string>


class Valute {
    std::string NumCode;
    std::string Name;
    double VunitRate;
public:
    Valute(std::string_view NumCode, std::string_view Name, double VunitRate);

    std::string_view GetNumCode();
    std::string_view GetName();
    double GetVunitRate();
};
