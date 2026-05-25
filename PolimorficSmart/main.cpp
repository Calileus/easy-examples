#include "financial_instrument.h"
#include "portfolio_market.h"
#include <vector>
#include <memory>
#include <iostream>

// Demonstrate polymorphism with smart pointers
void demonstratePolymorphism() {
    std::cout << "\n=== Polymorphism Demonstration ===" << std::endl;
    
    // Using unique_ptr for exclusive ownership
    std::vector<std::unique_ptr<FinancialInstrument>> instruments;
    
    instruments.push_back(std::make_unique<Stock>("AAPL", 150.0, 50));
    instruments.push_back(std::make_unique<Bond>("US10Y", 1000.0, 3.5, 10));
    instruments.push_back(std::make_unique<Option>("TSLA", 25.0, Option::Type::CALL, 200.0, 5));
    
    // Polymorphic behavior - each object calls its own overridden method
    for (const auto& instrument : instruments) {
        instrument->printDetails();
        std::cout << "Risk: $" << instrument->calculateRisk() << std::endl;
    }
}

// Demonstrate shared_ptr usage
void demonstrateSharedPtr() {
    std::cout << "\n=== Shared Pointer Demonstration ===" << std::endl;
    
    // Create shared instruments
    auto apple_stock = std::make_shared<Stock>("AAPL", 150.0, 100);
    auto us_bond = std::make_shared<Bond>("US10Y", 1000.0, 3.5, 10);
    
    std::cout << "AAPL reference count: " << apple_stock.use_count() << std::endl;
    
    // Create portfolios that share ownership of instruments
    auto portfolio1 = std::make_shared<Portfolio>("Growth Portfolio");
    auto portfolio2 = std::make_shared<Portfolio>("Income Portfolio");
    
    portfolio1->addInstrument(apple_stock);
    portfolio2->addInstrument(us_bond);
    portfolio2->addInstrument(apple_stock); // Shared ownership
    
    std::cout << "AAPL reference count after adding to portfolios: " << apple_stock.use_count() << std::endl;
    
    portfolio1->printPortfolio();
    portfolio2->printPortfolio();
}

// Demonstrate weak_ptr usage
void demonstrateWeakPtr() {
    std::cout << "\n=== Weak Pointer Demonstration ===" << std::endl;
    
    auto portfolio = std::make_shared<Portfolio>("Test Portfolio");
    auto stock = std::make_shared<Stock>("GOOGL", 2500.0, 10);
    
    portfolio->addInstrument(stock);
    
    // Create weak_ptr
    std::weak_ptr<FinancialInstrument> weak_stock = stock;
    std::weak_ptr<Portfolio> weak_portfolio = portfolio;
    
    std::cout << "Stock reference count: " << stock.use_count() << std::endl;
    std::cout << "Portfolio reference count: " << portfolio.use_count() << std::endl;
    
    // Use weak_ptr
    if (auto locked_stock = weak_stock.lock()) {
        std::cout << "Weak pointer successfully locked to: " << locked_stock->getSymbol() << std::endl;
    }
    
    // Reset shared_ptr to demonstrate weak_ptr expiration
    stock.reset();
    std::cout << "After resetting stock, weak_ptr expired: " << weak_stock.expired() << std::endl;
    
    if (auto locked_stock = weak_stock.lock()) {
        std::cout << "This should not print" << std::endl;
    } else {
        std::cout << "Weak pointer could not be locked - object destroyed" << std::endl;
    }
}

// Demonstrate move semantics with unique_ptr
void demonstrateMoveSemantics() {
    std::cout << "\n=== Move Semantics Demonstration ===" << std::endl;
    
    auto instrument = createInstrument("stock", "MSFT", 300.0);
    std::cout << "Created instrument: ";
    instrument->printDetails();
    
    // Move ownership
    std::unique_ptr<FinancialInstrument> moved_instrument = std::move(instrument);
    std::cout << "After move, original pointer is: " << (instrument ? "valid" : "null") << std::endl;
    std::cout << "Moved instrument: ";
    moved_instrument->printDetails();
    
    // Pass by move to function
    auto final_instrument = std::move(moved_instrument);
    std::cout << "Final instrument value: $" << final_instrument->calculateValue() << std::endl;
}

int main() {
    std::cout << "=== C++ Polymorphism and Smart Pointers Example ===" << std::endl;
    std::cout << "Financial Instruments for Quant Dev Interview" << std::endl;
    
    demonstratePolymorphism();
    demonstrateSharedPtr();
    demonstrateWeakPtr();
    demonstrateMoveSemantics();
    
    std::cout << "\n=== Complete Market Simulation ===" << std::endl;
    
    // Create market and portfolios
    Market market("NYSE");
    
    auto tech_portfolio = std::make_shared<Portfolio>("Technology");
    auto bond_portfolio = std::make_shared<Portfolio>("Fixed Income");
    
    // Add instruments using factory
    tech_portfolio->addInstrument(std::make_shared<Stock>("AAPL", 150.0, 100));
    tech_portfolio->addInstrument(std::make_shared<Stock>("GOOGL", 2500.0, 50));
    tech_portfolio->addInstrument(std::make_shared<Option>("TSLA", 25.0, Option::Type::CALL, 200.0, 10));
    
    bond_portfolio->addInstrument(std::make_shared<Bond>("US10Y", 1000.0, 3.5, 10));
    bond_portfolio->addInstrument(std::make_shared<Bond>("CORP", 950.0, 5.0, 5));
    
    market.addPortfolio(tech_portfolio);
    market.addPortfolio(bond_portfolio);
    
    tech_portfolio->printPortfolio();
    bond_portfolio->printPortfolio();
    
    market.updateAllPrices(1.05);
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    
    return 0;
}
