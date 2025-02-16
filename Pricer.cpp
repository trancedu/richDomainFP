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

void OptionPricer::option_common_pricing_logic(const Option& option) const {
    common_pricing_logic(option);
    std::cout << "Option pricing logic";
} 

std::string OptionPricer::getType() const {
    return "OptionPricer";
} 

double AsianOptionPricer::price(const AsianOption& asianOption) const {
    common_pricing_logic(asianOption);
    return 75.0;
}

std::string AsianOptionPricer::getType() const {
    return "AsianOptionPricer";
}

double EuropeanOptionPricer::price(const EuropeanOption& option) const {
    common_pricing_logic(option);
    return 60.0;
}

std::string EuropeanOptionPricer::getType() const {
    return "EuropeanOptionPricer";
}