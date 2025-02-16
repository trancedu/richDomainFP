#include "Option.hpp"
#include <iostream>

Option::Option(std::string name) 
    : FinancialProduct(name) {}

void Option::describe() const {
    std::cout << "This is an Option contract.\n";
}

std::string Option::getType() const {
    return "Option";
} 

AsianOption::AsianOption(std::string name, std::unique_ptr<AsianOptionPricer> pricer)
    : Option(std::move(name)), pricer(std::move(pricer)) {}

double AsianOption::calculatePrice() const {
    return pricer->price(*this);
}

void AsianOption::describe() const {
    std::cout << "This is an Asian Option contract.\n";
}

std::string AsianOption::getType() const {
    return "AsianOption";
}

EuropeanOption::EuropeanOption(std::string name, std::unique_ptr<EuropeanOptionPricer> pricer)
    : Option(std::move(name)), pricer(std::move(pricer)) {}

double EuropeanOption::calculatePrice() const {
    return pricer->price(*this);
}

void EuropeanOption::describe() const {
    std::cout << "This is a European Option contract.\n";
}

std::string EuropeanOption::getType() const {
    return "EuropeanOption";
}