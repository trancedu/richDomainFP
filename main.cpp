#include "FinancialProducts.h"
#include <iostream>
#include <memory>

void analyzeRisk(const GreekCalculable& product) {
    std::cout << "Risk Analysis:\n"
              << "Delta: " << product.getDelta() << "\n"
              << "Gamma: " << product.getGamma() << "\n"
              << "Vega: " << product.getVega() << "\n"
              << "Theta: " << product.getTheta() << "\n\n";
}

int main() {
    // Create an option with Black-Scholes pricing
    auto option = Option(
        "AAPL_CALL_2025",  // Name
        150.0,             // Current price
        160.0,             // Strike price
        0.25,              // Volatility (25%)
        1.0,               // Time to expiration (1 year)
        std::make_unique<BlackScholesPricing>()
    );

    // Create a stock
    Stock apple("AAPL", 185.3);

    // Demonstrate pricing
    std::cout << "Option Price: " << option.getPrice() << "\n";
    std::cout << "Stock Price: " << apple.getPrice() << "\n\n";

    // Show Greeks for the option
    analyzeRisk(option);

    // Uncommenting this will cause a compile error (good!)
    // analyzeRisk(apple); 

    return 0;
} 