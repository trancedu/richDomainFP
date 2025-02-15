#include "FinancialProduct.hpp"

void FinancialProduct::addSubproduct(std::shared_ptr<FinancialProduct> product) {
    subproducts.push_back(std::move(product));
} 

std::string FinancialProduct::getName() const {
    return name;
}