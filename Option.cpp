#include "Option.hpp"
#include <iostream>

Option::Option(std::string name, std::unique_ptr<OptionPricer> pricer) 
    : FinancialProduct(name), pricer(std::move(pricer)) {}

double Option::calculatePrice() const {
    if (!subproducts.empty()) {
        double total = 0.0;
        for (const auto& product : subproducts) {
            total += product->calculatePrice();
        }
        return total;
    }
    return pricer->price(*this);
}

void Option::describe() const {
    std::cout << "This is an Option contract.\n";
}

std::string Option::getType() const {
    return "Option";
} 

AsianOption::AsianOption(std::string name, std::unique_ptr<AsianOptionPricer> pricer)
    : Option(std::move(name), std::unique_ptr<OptionPricer>(pricer.release())) {}

double AsianOption::calculatePrice() const {
    return pricer->price(*this);
}

void AsianOption::describe() const {
    std::cout << "This is an Asian Option contract.\n";
}

std::string AsianOption::getType() const {
    return "AsianOption";
}