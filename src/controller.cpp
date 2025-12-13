#include "controller.h"

#include <algorithm>
#include <stdexcept>

#include "tinyxml2.h"


std::string Parser::GetVunitRateByCharCode(std::string_view data, std::string_view CharCode) noexcept(false)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.Parse(data.data());
    assert(res == tinyxml2::XML_SUCCESS);

    tinyxml2::XMLElement* root = doc.RootElement();
    assert(root != nullptr);

    tinyxml2::XMLElement* valute = root->FirstChildElement("Valute");
    assert(valute != nullptr);


    while (valute != nullptr)
    {
        tinyxml2::XMLElement* CC = valute->FirstChildElement("CharCode");
        tinyxml2::XMLElement* VE = valute->FirstChildElement("VunitRate");

        if (
            CC && VE &&
            CC->GetText() &&
            VE->GetText() &&
            strcmp(CharCode.data(), CC->GetText()) == 0)
        {
            return VE->GetText();
        }


        valute = valute->NextSiblingElement("Valute");
    }

   throw std::logic_error("Valute not found");
}

std::unique_ptr<std::string> Parser::GetAllCharCodeAndName(std::string_view data) noexcept(false)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.Parse(data.data());
    assert(res == tinyxml2::XML_SUCCESS);

    tinyxml2::XMLElement* root = doc.RootElement();
    assert(root != nullptr);

    tinyxml2::XMLElement* valute = root->FirstChildElement("Valute");
    assert(valute != nullptr);


    std::unique_ptr<std::string> result = std::make_unique<std::string>();
    while (valute != nullptr)
    {
        tinyxml2::XMLElement* CC = valute->FirstChildElement("CharCode");
        tinyxml2::XMLElement* NE = valute->FirstChildElement("Name");

        if (
            CC && NE &&
            CC->GetText() &&
            NE->GetText())
        {
            result->append(CC->GetText())
                    .append(" ")
                    .append(NE->GetText())
                    .append("\n");
        }


        valute = valute->NextSiblingElement("Valute");
    }


    return result;
}


void Convertor::FormatFPU(std::string &Str, char NewCh) noexcept(false)
{
    if (NewCh == '.') std::ranges::replace(Str, ',', NewCh);
    else if (NewCh == ',') std::ranges::replace(Str, '.', NewCh);
    else throw std::invalid_argument("Invalid character");
}


std::string Convertor::ConvertValute(std::string_view data, double count, std::string_view CharCode, char FFPU)
{
    std::string VunitRate = Parser::GetVunitRateByCharCode(data, CharCode);
    FormatFPU(VunitRate, '.');

    std::string result = std::to_string(count * std::stod(VunitRate));
    FormatFPU(result, FFPU);

    return result;
}


std::string Convertor::ConvertValuteToValute(std::string_view data, double count, std::string_view CharCode1, std::string_view CharCode2, char FFPU)
{
    if (CharCode1 == CharCode2) throw std::logic_error("currency is the same");


    if (CharCode1 == "RUB")
    {
        std::string result = std::to_string(count / std::stod(ConvertValute(data, 1, CharCode2, FFPU)));
        FormatFPU(result, FFPU);

        return result;
    }

    if (CharCode2 == "RUB")
        return ConvertValute(data, count, CharCode1, FFPU);


    std::string CC1result = ConvertValute(data, count, CharCode1, FFPU);
    std::string CC2result = ConvertValute(data, 1, CharCode2, FFPU);
    FormatFPU(CC1result, '.');
    FormatFPU(CC2result, '.');


    std::string result = std::to_string(
        std::stod(CC1result) /
        std::stod(CC2result)
    );



    FormatFPU(result, FFPU);
    return result;
}