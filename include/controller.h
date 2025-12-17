#pragma once
#include <map>
#include <memory>
#include <string>

#include "valute.h"


class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    static std::string GetVunitRateByCharCode(std::string_view data, std::string_view CharCode) noexcept(false);
    static std::unique_ptr<std::string> GetAllCharCodeAndName(std::string_view data) noexcept(false);
};


class Convertor
{
private:
    static void FormatFPU(std::string& Str, char NewCh) noexcept(false);

public:
    Convertor() = default;
    ~Convertor() = default;

    static std::map<std::string, Valute> CreateMap(std::string_view data);


    static std::string ConvertValute(std::string_view data, double count, std::string_view CharCode, char FFPU);
    static std::string ConvertValuteToValute(std::string_view data, double count, std::string_view CharCode1, std::string_view CharCode2, char FFPU);
};


