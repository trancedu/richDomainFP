#pragma once
#include "FinancialProduct.hpp"
#include "Pricer.hpp"
#include <memory>

class Option : public FinancialProduct {
public:
    explicit Option(std::string name);
    void describe() const override;
    std::string getType() const override;
}; 


class AsianOption : public Option {
    std::unique_ptr<AsianOptionPricer> pricer;
public:
    AsianOption(std::string name, std::unique_ptr<AsianOptionPricer> pricer);
    double calculatePrice() const override;
    void describe() const override;
    std::string getType() const override;
};

class EuropeanOption : public Option {
    std::unique_ptr<EuropeanOptionPricer> pricer;
public:
    EuropeanOption(std::string name, std::unique_ptr<EuropeanOptionPricer> pricer);
    double calculatePrice() const override;
    void describe() const override;
    std::string getType() const override;
};