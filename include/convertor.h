#pragma once
#include <map>
#include <string>

#include "valute.h"


class convertor
{
private:
    std::map<std::string, valute> ValuteMap;
    static std::map<std::string, valute> CreateMap(std::string_view data);
public:
    convertor(std::string_view data);
    ~convertor() = default;

    static void FormatFPU(std::string& Str, char NewCh) noexcept(false);

    std::string GetAllData();

    double ConvertValute(double count, const std::string &CharCode);
    double ConvertValuteToValute(double count, const std::string &CharCode1, const std::string &CharCode2);
};


