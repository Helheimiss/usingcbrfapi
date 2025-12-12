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
</ValCurs>)";


    return 0.0;
}


int main(int argc, char *argv[])
{
    test1();


    puts("done");
    return 0;
}
