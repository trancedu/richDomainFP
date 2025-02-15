#pragma once
#include "FinancialProduct.hpp"

// Forward declarations
class Swap;
class Option;
class AsianOption;

class Pricer {
public:
    void common_pricing_logic(const FinancialProduct& product) const;
    virtual std::string getType() const = 0;
};

class SwapPricer : public Pricer {
public:
    double price(const Swap& swap) const;
    std::string getType() const override;
};

class OptionPricer : public Pricer {
public:
    double price(const Option& option) const;
    std::string getType() const override;
}; 

class AsianOptionPricer : public Pricer {
public:
    double price(const AsianOption& asianOption) const;
    std::string getType() const override;
};