#include "valute.h"


valute::valute(std::string_view NumCode, std::string_view Name, double VunitRate)
    : NumCode(NumCode), Name(Name), VunitRate(VunitRate)
{

}


std::string_view valute::GetNumCode() {
    return NumCode;
}

std::string_view valute::GetName() {
    return Name;
}

double valute::GetVunitRate() {
    return VunitRate;
}
