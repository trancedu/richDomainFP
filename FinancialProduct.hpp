#pragma once
#include <memory>
#include <vector>
#include <string>

class FinancialProduct {
protected:
    std::vector<std::shared_ptr<FinancialProduct>> subproducts;
    std::string name;
    
public:
    virtual ~FinancialProduct() = default;
    FinancialProduct(std::string name) : name(std::move(name)) {}
    void addSubproduct(std::shared_ptr<FinancialProduct> product);
    virtual double calculatePrice() const = 0;
    virtual void describe() const = 0;
    virtual std::string getType() const = 0;
    std::string getName() const;
}; 