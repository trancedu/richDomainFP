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