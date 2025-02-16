#include "Swap.hpp"
#include "Option.hpp"
#include <iostream>
#include <memory>

int main() {
    // Create products with their specific pricers
    auto swap = std::make_shared<Swap>("Swap1", std::make_unique<SwapPricer>());
    auto europeanOption = std::make_shared<EuropeanOption>("EuroOption1", 
        std::make_unique<EuropeanOptionPricer>());
    auto asianOption = std::make_shared<AsianOption>("AsianOption1",
        std::make_unique<AsianOptionPricer>());

    // Create structured product
    auto structuredProduct = std::make_shared<Swap>("Structured Product1", std::make_unique<SwapPricer>());
    structuredProduct->addSubproduct(swap);
    structuredProduct->addSubproduct(europeanOption);
    structuredProduct->addSubproduct(asianOption);
    // Pricing outputs remain the same
    // swap->describe();
    std::cout << swap->getName() << " Price: " << swap->calculatePrice() << "\n";

    // europeanOption->describe();
    std::cout << europeanOption->getName() << " Price: " << europeanOption->calculatePrice() << "\n";

    // asianOption->describe();
    std::cout << asianOption->getName() << " Price: " << asianOption->calculatePrice() << "\n";

    // structuredProduct->describe();
    std::cout << structuredProduct->getName() << " Price: " << structuredProduct->calculatePrice() << "\n";

    return 0;
}