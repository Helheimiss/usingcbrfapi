#include "tinyxml2.h"

#include <iostream>
#include <string>
#include <cassert>


double test1()
{
    std::string xml_data =
R"(<ValCurs Date="13.12.2025" name="Foreign Currency Market">
    <Valute ID="R01010">
        <NumCode>036</NumCode>
        <CharCode>AUD</CharCode>
        <Nominal>1</Nominal>
        <Name>Australian Dollar</Name>
        <Value>53,1079</Value>
        <VunitRate>53,1079</VunitRate>
    </Valute>
        <Valute ID="R01020A">
        <NumCode>944</NumCode>
        <CharCode>AZN</CharCode>
        <Nominal>1</Nominal>
        <Name>Azerbaijan Manat</Name>
        <Value>46,8998</Value>
        <VunitRate>46,8998</VunitRate>
    </Valute>
        <Valute ID="R01030">
        <NumCode>012</NumCode>
        <CharCode>DZD</CharCode>
        <Nominal>100</Nominal>
        <Name>Algerian Dinar</Name>
        <Value>61,5323</Value>
        <VunitRate>0,615323</VunitRate>
    </Valute>
</ValCurs>)";
    using namespace tinyxml2;

    XMLDocument doc;
    XMLError error = doc.Parse(xml_data.c_str());

    if (error != XML_SUCCESS) {
        std::cerr << "Ошибка парсинга XML: " << doc.ErrorName() << std::endl;
        return 1;
    }

    // Получаем корневой элемент
    XMLElement* root = doc.FirstChildElement("ValCurs");
    if (!root) {
        std::cerr << "Корневой элемент ValCurs не найден!" << std::endl;
        return 1;
    }

    // Получаем дату из атрибута
    const char* date = root->Attribute("Date");
    if (date) {
        std::cout << "Курсы валют на " << date << ":\n";
    }

    // Проходим по всем элементам Valute
    for (XMLElement* valute = root->FirstChildElement("Valute");
         valute != nullptr;
         valute = valute->NextSiblingElement("Valute")) {

        // Получаем код валюты и номинал
        const char* charCode = valute->FirstChildElement("CharCode")->GetText();
        const char* nominal = valute->FirstChildElement("Nominal")->GetText();
        const char* name = valute->FirstChildElement("Name")->GetText();

        // Получаем значение Value
        const char* value = valute->FirstChildElement("Value")->GetText();

        if (charCode && value) {
            std::cout << charCode << " (" << (name ? name : "") << "): "
                      << nominal << " единица = " << value << " руб." << std::endl;
        }
         }


    return 0.0;
}


int main(int argc, char *argv[])
{
    test1();


    puts("done");
    return 0;
}
