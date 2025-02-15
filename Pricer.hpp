#pragma once
#include "FinancialProduct.hpp"

// Forward declarations
class Swap;
class Option;

class Pricer {
public:
    void common_pricing_logic(const FinancialProduct& product) const;
};

class SwapPricer : public Pricer {
public:
    double price(const Swap& swap) const;
};

class OptionPricer : public Pricer {
public:
    double price(const Option& option) const;
}; 