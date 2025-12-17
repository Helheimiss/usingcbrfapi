#include "convertor.h"

#include <algorithm>
#include <functional>
#include <ranges>
#include <stdexcept>

#include "tinyxml2.h"


void convertor::FormatFPU(std::string &Str, char NewCh) noexcept(false)
{
    if (NewCh == '.') std::ranges::replace(Str, ',', NewCh);
    else if (NewCh == ',') std::ranges::replace(Str, '.', NewCh);
    else throw std::invalid_argument("Invalid character");
}

std::string convertor::GetAllData()
{
    std::string res;

    for (const auto &key: ValuteMap | std::views::keys)
    {
        res.append(key)
        .append(" ")
        .append(ValuteMap.at(key).GetName())
        .append("\n");
    }

    return res;
}

convertor::convertor(std::string_view data) : ValuteMap(CreateMap(data))
{ }


std::map<std::string, valute> convertor::CreateMap(std::string_view data)
{
    std::map<std::string, valute> ValuteMap;

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.Parse(data.data());
    assert(res == tinyxml2::XML_SUCCESS);

    tinyxml2::XMLElement* root = doc.RootElement();
    assert(root != nullptr);

    tinyxml2::XMLElement* valute_root = root->FirstChildElement("Valute");
    assert(valute_root != nullptr);

    while (valute_root != nullptr)
    {
        tinyxml2::XMLElement* CharCode = valute_root->FirstChildElement("CharCode");
        tinyxml2::XMLElement* NumCode = valute_root->FirstChildElement("NumCode");
        tinyxml2::XMLElement* Name = valute_root->FirstChildElement("Name");
        tinyxml2::XMLElement* VunitRate = valute_root->FirstChildElement("VunitRate");

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
            valute(NumCode->GetText(),
            Name->GetText(),
            std::stod(vr)));
        }


        valute_root = valute_root->NextSiblingElement("Valute");
    }


    return ValuteMap;
}


double convertor::ConvertValute(double count, const std::string &CharCode)
{
    double VunitRate = ValuteMap.at(CharCode).GetVunitRate();
    return count * VunitRate;
}


double convertor::ConvertValuteToValute(double count, const std::string &CharCode1, const std::string &CharCode2)
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