#include "controller.h"

#include <algorithm>
#include <stdexcept>

#include "tinyxml2.h"


std::string Parser::GetVunitRateByCharCode(const std::string& data, const std::string& CharCode)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.Parse(data.c_str());
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
            strcmp(CharCode.c_str(), CC->GetText()) == 0)
        {
            return VE->GetText();
        }


        valute = valute->NextSiblingElement("Valute");
    }

   throw std::logic_error("Valute not found");
}


std::string Convertor::ConvertValute(const std::string &data, double count, const std::string &CharCode)
{
    std::string result = Parser::GetVunitRateByCharCode(data, CharCode);
    std::ranges::replace(result, ',', '.');


    return std::to_string(count * std::stod(result));
}


std::string Convertor::ConvertValuteToValute(const std::string &data, double count, const std::string &CharCode1,
    const std::string &CharCode2)
{
    //TODO()
    return "";
}
