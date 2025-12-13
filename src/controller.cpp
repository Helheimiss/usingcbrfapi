#include "controller.h"

#include <algorithm>
#include <stdexcept>

#include "tinyxml2.h"


std::string Parser::GetVunitRateByCharCode(const std::string_view data, const std::string_view CharCode)
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


std::string Convertor::ConvertValute(const std::string_view data, double count, const std::string_view CharCode)
{
    std::string VunitRate = Parser::GetVunitRateByCharCode(data, CharCode);
    std::ranges::replace(VunitRate, ',', '.');

    std::string result = std::to_string(count * std::stod(VunitRate));
    std::ranges::replace(result, '.', ',');

    return result;
}


std::string Convertor::ConvertValuteToValute(const std::string_view data, double count, const std::string_view CharCode1, const std::string_view CharCode2)
{
    if (CharCode1 == CharCode2) throw std::logic_error("currency is the same");


    if (CharCode1 == "RUB")
    {
        std::string result = std::to_string(count / std::stod(ConvertValute(data, 1, CharCode2)));
        std::ranges::replace(result, '.', ',');

        return result;
    }

    if (CharCode2 == "RUB")
        return ConvertValute(data, count, CharCode1);


    std::string CC1result = ConvertValute(data, count, CharCode1);
    std::string CC2result = ConvertValute(data, 1, CharCode2);
    std::ranges::replace(CC1result, ',', '.');
    std::ranges::replace(CC2result, ',', '.');

    std::string result = std::to_string(
        std::stod(CC1result) /
        std::stod(CC2result)
    );

    std::ranges::replace(CC2result, '.', ',');

    return result;
}
