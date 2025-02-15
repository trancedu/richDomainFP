#include <string>
#include <memory>

// Pricing strategy interface
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double calculatePrice(const class Option& option) const = 0;
};

// Base financial product class
class FinancialProduct {
protected:
    std::string name;
    double marketPrice;

public:
    FinancialProduct(std::string name, double price)
        : name(std::move(name)), marketPrice(price) {}
    virtual ~FinancialProduct() = default;

    std::string getName() const { return name; }
    double getMarketPrice() const { return marketPrice; }
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
class BlackScholesPricing : public PricingStrategy {
public:
    double calculatePrice(const Option& option) const override;
};

// Option class implementing both interfaces
class Option : public FinancialProduct, public GreekCalculable {
    std::unique_ptr<PricingStrategy> pricingStrategy;
    double strikePrice;
    double volatility;
    double timeToExpiration;

public:
    Option(std::string name, double price, double strike, double vol, double tte,
           std::unique_ptr<PricingStrategy> strategy)
        : FinancialProduct(name, price), strikePrice(strike), volatility(vol),
          timeToExpiration(tte), pricingStrategy(std::move(strategy)) {}

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
};

// Stock class - simple implementation
class Stock : public FinancialProduct {
public:
    Stock(std::string name, double price)
        : FinancialProduct(name, price) {}

    double getPrice() const override {
        return getMarketPrice(); // Simple stock price is market price
    }
}; 