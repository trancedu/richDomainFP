#include <iostream>
#include <memory>
#include <vector>

// Forward declarations
class Swap;
class Option;
class FinancialProduct;

// Base class for pricers
class Pricer {
public:
    virtual ~Pricer() = default;
    virtual double price(const Swap& swap) const = 0;
    virtual double price(const Option& option) const = 0;
};

// Concrete pricer for Swaps
class SwapPricer : public Pricer {
public:
    double price(const Swap& swap) const override {
        std::cout << "Pricing Swap...\n";
        return 100.0;
    }
    
    // Add missing implementation for Option
    double price(const Option& option) const override {
        throw std::runtime_error("SwapPricer cannot price Options");
        return 0.0;
    }
};

// Concrete pricer for Options
class OptionPricer : public Pricer {
public:
    double price(const Option& option) const override {
        std::cout << "Pricing Option...\n";
        return 50.0;
    }
    
    // Add missing implementation for Swap
    double price(const Swap& swap) const override {
        throw std::runtime_error("OptionPricer cannot price Swaps");
        return 0.0;
    }
};

// Base class for financial products
class FinancialProduct {
protected:
    std::shared_ptr<Pricer> pricer;  // Injected pricer
    std::vector<std::shared_ptr<FinancialProduct>> subproducts; // Subproducts

public:
    explicit FinancialProduct(std::shared_ptr<Pricer> pricer) : pricer(std::move(pricer)) {}

    virtual ~FinancialProduct() = default;

    // Allow adding subproducts
    void addSubproduct(std::shared_ptr<FinancialProduct> product) {
        subproducts.push_back(std::move(product));
    }

    virtual double calculatePrice() const = 0;
    virtual void describe() const = 0;
};

// Derived class for Swaps
class Swap : public FinancialProduct {
public:
    explicit Swap(std::shared_ptr<Pricer> pricer) : FinancialProduct(std::move(pricer)) {}

    double calculatePrice() const override {
        if (!subproducts.empty()) {
            double totalPrice = 0.0;
            for (const auto& product : subproducts) {
                totalPrice += product->calculatePrice();
            }
            return totalPrice;
        }
        return pricer->price(*this);
    }

    void describe() const override {
        std::cout << "This is a Swap contract.\n";
    }
};

// Derived class for Options
class Option : public FinancialProduct {
public:
    explicit Option(std::shared_ptr<Pricer> pricer) : FinancialProduct(std::move(pricer)) {}

    double calculatePrice() const override {
        if (!subproducts.empty()) {
            double totalPrice = 0.0;
            for (const auto& product : subproducts) {
                totalPrice += product->calculatePrice();
            }
            return totalPrice;
        }
        return pricer->price(*this);
    }

    void describe() const override {
        std::cout << "This is an Option contract.\n";
    }
};

int main() {
    // Create pricers
    auto swapPricer = std::make_shared<SwapPricer>();
    auto optionPricer = std::make_shared<OptionPricer>();

    // Create standalone financial products
    auto swap = std::make_shared<Swap>(swapPricer);
    auto option = std::make_shared<Option>(optionPricer);

    // Create a structured product with subproducts
    auto structuredProduct = std::make_shared<Swap>(swapPricer);
    structuredProduct->addSubproduct(swap);
    structuredProduct->addSubproduct(option);

    // Price individual products
    swap->describe();
    double swapPrice = swap->calculatePrice();
    std::cout << "Swap Price: " << swapPrice << "\n";

    option->describe();
    double optionPrice = option->calculatePrice();
    std::cout << "Option Price: " << optionPrice << "\n";

    // Price structured product
    structuredProduct->describe();
    double structuredPrice = structuredProduct->calculatePrice();
    std::cout << "Structured Product Price: " << structuredPrice << "\n";

    return 0;
}