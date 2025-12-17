#include "controller.h"

#include <algorithm>
#include <stdexcept>

#include "tinyxml2.h"


void Convertor::FormatFPU(std::string &Str, char NewCh) noexcept(false)
{
    if (NewCh == '.') std::ranges::replace(Str, ',', NewCh);
    else if (NewCh == ',') std::ranges::replace(Str, '.', NewCh);
    else throw std::invalid_argument("Invalid character");
}

Convertor::Convertor(std::string_view data) : ValuteMap(CreateMap(data)) {
}


std::map<std::string, Valute> Convertor::CreateMap(std::string_view data) {
    std::map<std::string, Valute> ValuteMap;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.Parse(data.data());
    assert(res == tinyxml2::XML_SUCCESS);

    tinyxml2::XMLElement* root = doc.RootElement();
    assert(root != nullptr);

    tinyxml2::XMLElement* valute = root->FirstChildElement("Valute");
    assert(valute != nullptr);

    while (valute != nullptr)
    {
        tinyxml2::XMLElement* CharCode = valute->FirstChildElement("CharCode");
        tinyxml2::XMLElement* NumCode = valute->FirstChildElement("NumCode");
        tinyxml2::XMLElement* Name = valute->FirstChildElement("Name");
        tinyxml2::XMLElement* VunitRate = valute->FirstChildElement("VunitRate");

        if (
            CharCode && NumCode && Name && VunitRate &&
            CharCode->GetText() &&
            NumCode->GetText() &&
            Name->GetText() &&
            VunitRate->GetText()
            )
        {

            std::string vr = VunitRate->GetText();
            FormatFPU(vr, '.');

            ValuteMap.emplace(
            CharCode->GetText(),
            Valute(NumCode->GetText(),
            Name->GetText(),
            std::stod(vr)));
        }


        valute = valute->NextSiblingElement("Valute");
    }


    return ValuteMap;
}


double Convertor::ConvertValute(double count, std::string CharCode)
{
    double VunitRate = ValuteMap.at(CharCode).GetVunitRate();
    return count * VunitRate;
}


double Convertor::ConvertValuteToValute(double count, std::string CharCode1, std::string CharCode2)
{
    if (CharCode1 == CharCode2) throw std::logic_error("currency is the same");


    if (CharCode1 == "RUB")
        return count / ConvertValute(1, CharCode2);

    if (CharCode2 == "RUB")
        return ConvertValute(count, CharCode1);


    double CC1result = ConvertValute(count, CharCode1);
    double CC2result = ConvertValute(1, CharCode2);

    return CC1result / CC2result;
}