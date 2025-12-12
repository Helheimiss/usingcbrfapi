#include "tinyxml2.h"

#include "data.h"

#include <iostream>
#include <string>


void test1()
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


void test2(const std::string& CharCodeTarget, const std::string& ValueTarget)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError res = doc.Parse(DATA.c_str());
    assert(res == tinyxml2::XML_SUCCESS);

    tinyxml2::XMLElement* root = doc.RootElement();
    assert(root != nullptr);

    tinyxml2::XMLElement* valute = root->FirstChildElement("Valute");
    assert(valute != nullptr);

    std::string RES_CC {};
    std::string RES_VE {};

    while (valute != nullptr) {
        const char* id = valute->Attribute("ID");
        std::cout << "ID: " << (id ? id : "нет") << std::endl;

        tinyxml2::XMLElement* CC = valute->FirstChildElement("CharCode");
        tinyxml2::XMLElement* VE = valute->FirstChildElement("Value");

        if (CC && VE && CC->GetText() && VE->GetText())
        {
            std::cout << "CharCode: " << CC->GetText() << std::endl;
            std::cout << "Value: " << VE->GetText() << std::endl;

            RES_CC = CC->GetText();
            RES_VE = VE->GetText();

            break;
        }


        valute = valute->NextSiblingElement("Valute");
    }



    assert(CharCodeTarget == RES_CC);
    assert(ValueTarget == RES_VE);
}


int main(int argc, char *argv[])
{
    std::cout << "press enter to continue..." << std::endl;
    getchar();

    std::cout << "test1 all data" << std::endl;
    test1();
    getchar();

    std::cout << "test2 find by CharCode" << std::endl;
    test2("AUD", "53,1079");
    getchar();


    puts("done");
    return 0;
}
