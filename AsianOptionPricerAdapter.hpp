#pragma once
#include "OptionPricer.hpp"
#include "AsianOptionPricer.hpp"

class AsianOptionPricerAdapter : public OptionPricer {
    std::unique_ptr<AsianOptionPricer> asianPricer;
public:
    double price(const Option& option) const override {
        // Implement proper adaptation logic here
        return dynamic_cast<const AsianOption&>(option).getAsianPrice();
    }
    std::string getType() const override {
        return "AsianOptionPricerAdapter";
    }
}; 