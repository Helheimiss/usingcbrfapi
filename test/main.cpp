#include "tinyxml2.h"

#include <iostream>
#include <string>


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

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.Parse(xml_data.c_str());
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


    return 0;
}


int main(int argc, char *argv[])
{
    test1();


    puts("done");
    return 0;
}
