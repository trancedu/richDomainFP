#pragma once
#include "FinancialProduct.hpp"
#include "Pricer.hpp"
#include <memory>

class Option : public FinancialProduct {
protected:
    std::unique_ptr<OptionPricer> pricer;
    
public:
    explicit Option(std::string name, std::unique_ptr<OptionPricer> pricer);
    double calculatePrice() const override;
    void describe() const override;
    std::string getType() const override;
}; 


class AsianOption : public Option {
public:
    AsianOption(std::string name, std::unique_ptr<AsianOptionPricer> pricer);
    double calculatePrice() const override;
    void describe() const override;
    std::string getType() const override;
};