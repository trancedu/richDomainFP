#include "FinancialProducts.h"
#include <cmath>

// Helper function for cumulative normal distribution
double normCDF(double x) {
    return 0.5 * (1 + erf(x / sqrt(2.0)));
}

// Black-Scholes price calculation implementation
double BlackScholesPricing::calculatePrice(const Option& option) const {
    double S = option.getPrice();  // Current price from FinancialProduct
    double K = option.getStrike();
    double T = option.getTimeToExpiration();
    double r = option.getRiskFreeRate();
    double q = option.getDividendYield();
    double σ = option.getVolatility();
    
    double d1 = (log(S/K) + (r - q + σ*σ/2)*T) / (σ*sqrt(T));
    double d2 = d1 - σ*sqrt(T);
    
    // Assuming it's a call option
    double price = S*exp(-q*T)*normCDF(d1) - K*exp(-r*T)*normCDF(d2);
    return price;
}

// Greeks calculations for Option
double Option::getDelta() const {
    double S = getPrice();
    double K = getStrike();
    double T = getTimeToExpiration();
    double r = getRiskFreeRate();
    double q = getDividendYield();
    double σ = getVolatility();
    
    double d1 = (log(S/K) + (r - q + σ*σ/2)*T) / (σ*sqrt(T));
    return exp(-q*T) * normCDF(d1);
}

double Option::getGamma() const {
    // ... similar implementation using Black-Scholes formula ...
    // (Would calculate gamma as exp(-q*T) * normPDF(d1) / (S*σ*sqrt(T)))
    return 0.1; // Placeholder for actual implementation
}

double Option::getVega() const {
    return 0.2;
}

double Option::getTheta() const {
    return -0.01;
}

// Add implementation for simple stock pricing
double SimpleStockPricing::calculatePrice(const Stock& stock) const {
    return stock.getMarketPrice(); // Directly return market price
} 