#pragma once
#include "FinancialProduct.hpp"

// Forward declarations
class Swap;
class Option;
class AsianOption;
class EuropeanOption;

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
    std::string getType() const override = 0;
    void option_common_pricing_logic(const Option& option) const;
};

class EuropeanOptionPricer : public OptionPricer {
public:
    double price(const EuropeanOption& europeanOption) const;
    std::string getType() const override;
};

class AsianOptionPricer : public OptionPricer {
public:
    double price(const AsianOption& asianOption) const;
    std::string getType() const override;
};
