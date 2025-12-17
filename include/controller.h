#pragma once
#include <map>
#include <memory>
#include <string>

#include "valute.h"


class Convertor
{
private:

    std::map<std::string, Valute> ValuteMap;
    static std::map<std::string, Valute> CreateMap(std::string_view data);
public:
    Convertor(std::string_view data);
    ~Convertor() = default;


    static void FormatFPU(std::string& Str, char NewCh) noexcept(false);
    double ConvertValute(double count, std::string CharCode);
    double ConvertValuteToValute(double count, std::string CharCode1, std::string CharCode2);
};


