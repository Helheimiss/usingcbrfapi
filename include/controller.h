#pragma once
#include <map>
#include <memory>
#include <string>

#include "valute.h"


class Convertor
{
private:
    static void FormatFPU(std::string& Str, char NewCh) noexcept(false);

public:
    Convertor() = default;
    ~Convertor() = default;

    static std::map<std::string, Valute> CreateMap(std::string_view data);

    static double ConvertValute(std::map<std::string, Valute>& ValuteMap, double count, std::string CharCode);
    static double ConvertValuteToValute(std::map<std::string, Valute>& ValuteMap, double count, std::string CharCode1, std::string CharCode2);
};


