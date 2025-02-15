#include "Swap.hpp"
#include "Option.hpp"
#include <iostream>
#include <memory>

int main() {
    // Create products with their specific pricers
    auto swap = std::make_shared<Swap>(std::make_unique<SwapPricer>());
    auto option = std::make_shared<Option>(std::make_unique<OptionPricer>());

    // Create structured product
    auto structuredProduct = std::make_shared<Swap>(std::make_unique<SwapPricer>());
    structuredProduct->addSubproduct(swap);
    structuredProduct->addSubproduct(option);

    // Pricing outputs remain the same
    swap->describe();
    std::cout << "Swap Price: " << swap->calculatePrice() << "\n";

    option->describe();
    std::cout << "Option Price: " << option->calculatePrice() << "\n";

    structuredProduct->describe();
    std::cout << "Structured Price: " << structuredProduct->calculatePrice() << "\n";

    return 0;
}