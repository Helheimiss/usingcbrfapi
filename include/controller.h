#pragma once
#include <string>


class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    static std::string GetVunitRateByCharCode(const std::string& data, const std::string& CharCode) noexcept(false);
};


class Convertor
{
public:
    Convertor() = default;
    ~Convertor() = default;

    static std::string ConvertValute(const std::string& data, double count, const std::string& CharCode);
    static std::string ConvertValuteToValute(const std::string& data, double count, const std::string& CharCode1, const std::string& CharCode2);
};


