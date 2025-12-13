#pragma once
#include <string>


class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    static std::string GetVunitRateByCharCode(const std::string_view data, const std::string_view CharCode) noexcept(false);
};


class Convertor
{
public:
    Convertor() = default;
    ~Convertor() = default;

    static std::string ConvertValute(const std::string_view data, double count, const std::string_view CharCode);
    static std::string ConvertValuteToValute(const std::string_view data, double count, const std::string_view CharCode1, const std::string_view CharCode2);
};


