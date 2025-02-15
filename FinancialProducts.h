#include <string>
#include <memory>

// Pricing strategy interface
class OptionPricingStrategy {
public:
    virtual ~OptionPricingStrategy() = default;
    virtual double calculatePrice(const class Option& option) const = 0;
};

// Base financial product class
class FinancialProduct {
protected:
    std::string name;
    double price;  // Add price member

public:
    FinancialProduct(std::string name, double price)
        : name(std::move(name)), price(price) {}
    virtual ~FinancialProduct() = default;

    std::string getName() const { return name; }
    virtual double getPrice() const = 0;
};

// Greek calculations interface
class GreekCalculable {
public:
    virtual ~GreekCalculable() = default;
    virtual double getDelta() const = 0;
    virtual double getGamma() const = 0;
    virtual double getVega() const = 0;
    virtual double getTheta() const = 0;
};

// Concrete pricing strategy (Black-Scholes model)
class BlackScholesPricing : public OptionPricingStrategy {
public:
    double calculatePrice(const Option& option) const override;
};

// Option class implementing both interfaces
class Option : public FinancialProduct, public GreekCalculable {
    std::unique_ptr<OptionPricingStrategy> pricingStrategy;
    double strikePrice;
    double volatility;
    double timeToExpiration;
    double riskFreeRate;
    double dividendYield;

public:
    Option(std::string name, double price, double strike, double vol, double tte,
           double r, double q,
           std::unique_ptr<OptionPricingStrategy> strategy)
        : FinancialProduct(name, price), strikePrice(strike), volatility(vol),
          timeToExpiration(tte), riskFreeRate(r), dividendYield(q),
          pricingStrategy(std::move(strategy)) {}

    // Price calculation delegation
    double getPrice() const override {
        return pricingStrategy->calculatePrice(*this);
    }

    // Greeks implementation
    double getDelta() const override;
    double getGamma() const override;
    double getVega() const override;
    double getTheta() const override;

    // Option-specific parameters
    double getStrike() const { return strikePrice; }
    double getVolatility() const { return volatility; }
    double getTimeToExpiration() const { return timeToExpiration; }

    // New getters
    double getRiskFreeRate() const { return riskFreeRate; }
    double getDividendYield() const { return dividendYield; }
};

// Add new stock pricing strategy interface above the Stock class
class StockPricingStrategy {
public:
    virtual ~StockPricingStrategy() = default;
    virtual double calculatePrice(const class Stock& stock) const = 0;
};

// Add simple pricing strategy implementation
class SimpleStockPricing : public StockPricingStrategy {
public:
    double calculatePrice(const Stock& stock) const override;
};

// Modified Stock class
class Stock : public FinancialProduct {
    std::unique_ptr<StockPricingStrategy> pricingStrategy;
    
public:
    Stock(std::string name, double price, 
          std::unique_ptr<StockPricingStrategy> strategy)
        : FinancialProduct(std::move(name), price),
          pricingStrategy(std::move(strategy)) {}

    double getPrice() const override {
        return pricingStrategy->calculatePrice(*this);
    }

    // Getter for market price to be used by pricing strategies
    double getMarketPrice() const { return price; }
}; 