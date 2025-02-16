#include "FinancialProduct.hpp"

void FinancialProduct::addSubproduct(std::shared_ptr<FinancialProduct> product) {
    subproducts.push_back(std::move(product));
} 

std::string FinancialProduct::getName() const {
    return name;
}

double FinancialProduct::calculatePrice() const {
    if (!subproducts.empty()) {
        double total = 0.0;
        for (const auto& product : subproducts) {
            total += product->calculatePrice();
        }
        return total;
    }
    return 0.0;
}