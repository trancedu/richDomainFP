#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

// Forward declarations
class Swap;
class Option;

// Pricer interfaces
class ISwapPricer {
public:
    virtual ~ISwapPricer() = default;
    virtual double price(const Swap& swap) const = 0;
};

class IOptionPricer {
public:
    virtual ~IOptionPricer() = default;
    virtual double price(const Option& option) const = 0;
};

// Concrete pricers
class SwapPricer : public ISwapPricer {
public:
    double price(const Swap& swap) const override {
        std::cout << "Pricing Swap...\n";
        return 100.0;
    }
};

class OptionPricer : public IOptionPricer {
public:
    double price(const Option& option) const override {
        std::cout << "Pricing Option...\n";
        return 50.0;
    }
};

// Base financial product
class FinancialProduct {
protected:
    std::vector<std::shared_ptr<FinancialProduct>> subproducts;
    
public:
    virtual ~FinancialProduct() = default;
    void addSubproduct(std::shared_ptr<FinancialProduct> product) {
        subproducts.push_back(std::move(product));
    }
    virtual double calculatePrice() const = 0;
    virtual void describe() const = 0;
};

// Swap with dedicated pricer interface
class Swap : public FinancialProduct {
    std::unique_ptr<ISwapPricer> pricer;
    
public:
    explicit Swap(std::unique_ptr<ISwapPricer> pricer) 
        : pricer(std::move(pricer)) {}

    double calculatePrice() const override {
        if (!subproducts.empty()) {
            double total = 0.0;
            for (const auto& product : subproducts) {
                total += product->calculatePrice();
            }
            return total;
        }
        return pricer->price(*this);
    }

    void describe() const override {
        std::cout << "This is a Swap contract.\n";
    }
};

// Option with dedicated pricer interface
class Option : public FinancialProduct {
    std::unique_ptr<IOptionPricer> pricer;
    
public:
    explicit Option(std::unique_ptr<IOptionPricer> pricer)
        : pricer(std::move(pricer)) {}

    double calculatePrice() const override {
        if (!subproducts.empty()) {
            double total = 0.0;
            for (const auto& product : subproducts) {
                total += product->calculatePrice();
            }
            return total;
        }
        return pricer->price(*this);
    }

    void describe() const override {
        std::cout << "This is an Option contract.\n";
    }
};

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