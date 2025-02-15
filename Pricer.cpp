#include "Pricer.hpp"
#include "Swap.hpp"
#include "Option.hpp"
#include <iostream>
#include <format>

void Pricer::common_pricing_logic(const FinancialProduct& product) const {
    std::string message = std::format("Pricing {} using {} ", product.getType(), getType());
    std::cout << message;
}

double SwapPricer::price(const Swap& swap) const {
    common_pricing_logic(swap);
    return 100.0;
}

std::string SwapPricer::getType() const {
    return "SwapPricer";
}

double OptionPricer::price(const Option& option) const {
    common_pricing_logic(option);
    return 50.0;
} 

std::string OptionPricer::getType() const {
    return "OptionPricer";
} 