#include "Swap.hpp"
#include <iostream>

Swap::Swap(std::unique_ptr<SwapPricer> pricer) : pricer(std::move(pricer)) {}

double Swap::calculatePrice() const {
    if (!subproducts.empty()) {
        double total = 0.0;
        for (const auto& product : subproducts) {
            total += product->calculatePrice();
        }
        return total;
    }
    return pricer->price(*this);
}

void Swap::describe() const {
    std::cout << "This is a Swap contract.\n";
}

std::string Swap::getName() const {
    return "Swap";
} 