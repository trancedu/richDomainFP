#include "Pricer.hpp"
#include "Swap.hpp"
#include "Option.hpp"
#include <iostream>

void Pricer::common_pricing_logic(const FinancialProduct& product) const {
    std::cout << "Pricing " << product.getName() << "...\n";
}

double SwapPricer::price(const Swap& swap) const {
    common_pricing_logic(swap);
    return 100.0;
}

double OptionPricer::price(const Option& option) const {
    common_pricing_logic(option);
    return 50.0;
} 