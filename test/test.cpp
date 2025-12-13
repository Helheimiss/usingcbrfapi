#include "tinyxml2.h"

#include <iostream>
#include <string>

#include "data.h"
#include "controller.h"


void PrintAllData()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.Parse(DATA.c_str());
    assert(res == tinyxml2::XML_SUCCESS);

    tinyxml2::XMLElement* root = doc.RootElement();
    assert(root != nullptr);

    tinyxml2::XMLElement* valute = root->FirstChildElement("Valute");
    assert(valute != nullptr);


    while (valute != nullptr) {
        const char* id = valute->Attribute("ID");
        std::cout << "ID: " << (id ? id : "нет") << std::endl;


        tinyxml2::XMLElement* charCodeElem = valute->FirstChildElement("CharCode");
        tinyxml2::XMLElement* nameElem = valute->FirstChildElement("Name");
        tinyxml2::XMLElement* valueElem = valute->FirstChildElement("Value");

        if (charCodeElem && charCodeElem->GetText()) {
            std::cout << "CharCode: " << charCodeElem->GetText() << std::endl;
        }

        if (nameElem && nameElem->GetText()) {
            std::cout << "Name: " << nameElem->GetText() << std::endl;
        }

        if (valueElem && valueElem->GetText()) {
            std::cout << "Value: " << valueElem->GetText() << std::endl;
        }

        std::cout << "-------------------------" << std::endl;


        valute = valute->NextSiblingElement("Valute");
    }
}


void GetVunitRateByCharCodeTest()
{
    assert(Parser::GetVunitRateByCharCode(DATA, "USD") == "79,7296");
    assert(Parser::GetVunitRateByCharCode(DATA, "NOK") == "7,89809");
    assert(Parser::GetVunitRateByCharCode(DATA, "RON") == "18,3683");
}


void ConvertValuteTest()
{
    assert(Convertor::ConvertValute(DATA, 1, "USD", ',') == "79,729600");
}


void ConvertValuteToValuteTest()
{
    assert(Convertor::ConvertValuteToValute(DATA, 2, "RUB", "USD", ',') == "0,025316");
    assert(Convertor::ConvertValuteToValute(DATA, 2, "USD", "RUB", ',') == "159,459200");
}


int main(int argc, char *argv[])
{
    GetVunitRateByCharCodeTest();
    ConvertValuteTest();
    ConvertValuteToValuteTest();


    puts("done");
    return 0;
}
