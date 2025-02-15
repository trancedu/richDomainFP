#pragma once
#include "FinancialProduct.hpp"

// Forward declarations
class Swap;
class Option;
class AsianOption;

class Pricer {
public:
    virtual ~Pricer() = default;
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
    virtual ~OptionPricer() = default;
    virtual double price(const Option& option) const = 0;
    std::string getType() const override = 0;
};

class AsianOptionPricer : public OptionPricer {
public:
    double price(const AsianOption& asianOption) const;
    double price(const Option& option) const override;
    std::string getType() const override;
};

class DefaultOptionPricer : public OptionPricer {
public:
    double price(const Option& option) const override;
    std::string getType() const override;
};