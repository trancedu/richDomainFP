#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>

// Forward declarations
class Swap;
class Option;

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
    virtual std::string getType() const = 0;
};

// First declare Pricer and concrete pricers before the product classes
class Pricer {
public:
    void common_pricing_logic(const FinancialProduct& product) const {
        std::cout << "Pricing " << product.getType() << "...\n";
    }
};

class SwapPricer : public Pricer {
public:
    double price(const Swap& swap) const {
        common_pricing_logic(swap);
        return 100.0;
    }
};

class OptionPricer : public Pricer {
public:
    double price(const Option& option) const {
        common_pricing_logic(option);
        return 50.0;
    }
};

// Then declare the product classes that use them
class Swap : public FinancialProduct {
    std::unique_ptr<SwapPricer> pricer;  // Now SwapPricer is fully defined
    
public:
    explicit Swap(std::unique_ptr<SwapPricer> pricer) 
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
    std::string getType() const override {
        return "Swap";
    }
};

class Option : public FinancialProduct {
    std::unique_ptr<OptionPricer> pricer;  // Now OptionPricer is fully defined
    
public:
    explicit Option(std::unique_ptr<OptionPricer> pricer)
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
    std::string getType() const override {
        return "Option";
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