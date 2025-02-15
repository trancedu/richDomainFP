#pragma once
#include "FinancialProduct.hpp"
#include "Pricer.hpp"
#include <memory>

class Option : public FinancialProduct {
    std::unique_ptr<OptionPricer> pricer;
    
public:
    explicit Option(std::unique_ptr<OptionPricer> pricer);
    double calculatePrice() const override;
    void describe() const override;
    std::string getName() const override;
}; 