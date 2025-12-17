#include "valute.h"


Valute::Valute(std::string_view ID, std::string_view NumCode, std::string_view Name, double VunitRate)
    : ID(ID), NumCode(NumCode), Name(Name), VunitRate(VunitRate)
{

}

std::string_view Valute::GetID() {
    return ID;
}

std::string_view Valute::GetNumCode() {
    return NumCode;
}

std::string_view Valute::GetName() {
    return Name;
}

double Valute::GetVunitRate() {
    return VunitRate;
}
