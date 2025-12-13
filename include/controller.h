#pragma once
#include <memory>
#include <string>


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
    //TODO() FPU() format
    static void FormatFPU(std::string& Str, char NewCh) noexcept(false);

public:
    Convertor() = default;
    ~Convertor() = default;



    static std::string ConvertValute(std::string_view data, double count, std::string_view CharCode);
    static std::string ConvertValuteToValute(std::string_view data, double count, std::string_view CharCode1, std::string_view CharCode2);
};


