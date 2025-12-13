#pragma once
#include <string>


class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    static std::string GetVunitRateByCharCode(std::string_view data, std::string_view CharCode) noexcept(false);
};


class Convertor
{
public:
    Convertor() = default;
    ~Convertor() = default;

    static std::string ConvertValute(std::string_view data, double count, std::string_view CharCode);
    static std::string ConvertValuteToValute(std::string_view data, double count, std::string_view CharCode1, std::string_view CharCode2);
};


