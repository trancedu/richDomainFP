#pragma once
#include "FinancialProduct.hpp"
#include "Pricer.hpp"
#include <memory>

class Swap : public FinancialProduct {
    std::unique_ptr<SwapPricer> pricer;
    
public:
    explicit Swap(std::string name, std::unique_ptr<SwapPricer> pricer);
    double calculatePrice() const override;
    void describe() const override;
    std::string getType() const override;
}; 