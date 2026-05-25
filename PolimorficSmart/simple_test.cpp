/// \file simple_test.cpp
/// \brief Unit tests for financial instruments using a custom test framework.
///
/// Tests basic functionality of Stock, Bond, and Option classes including
/// value calculation, risk calculation, and polymorphic behavior.
/// Uses a simple custom test framework (TEST_ASSERT macro) instead of external libraries.
///
/// \author Quantitative Finance Example
/// \version 1.0

#include "financial_instrument.h"
#include "portfolio_market.h"
#include <iostream>
#include <cassert>
#include <memory>

/// \brief Simple assertion macro for testing.
/// \param condition Expression to test.
/// \param message Message to print on success or failure.
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "FAIL: " << message << std::endl; \
            return false; \
        } else { \
            std::cout << "PASS: " << message << std::endl; \
        } \
    } while(0)

bool test_stock_calculations() {
    /// \brief Test Stock class value and risk calculations.
    std::cout << "\n=== Testing Stock Calculations ===" << std::endl;
    
    auto stock = std::make_unique<Stock>("AAPL", 150.0, 100);
    
    TEST_ASSERT(stock->getSymbol() == "AAPL", "Stock symbol correct");
    TEST_ASSERT(stock->getPrice() == 150.0, "Stock price correct");
    TEST_ASSERT(stock->getType() == "Stock", "Stock type correct");
    TEST_ASSERT(stock->calculateValue() == 15000.0, "Stock value calculation correct");
    TEST_ASSERT(stock->calculateRisk() == 2250.0, "Stock risk calculation correct");
    TEST_ASSERT(stock->getShares() == 100, "Stock shares correct");
    
    return true;
}

bool test_bond_calculations() {
    std::cout << "\n=== Testing Bond Calculations ===" << std::endl;
    
    auto bond = std::make_unique<Bond>("US10Y", 1000.0, 3.5, 10);
    
    TEST_ASSERT(bond->getSymbol() == "US10Y", "Bond symbol correct");
    TEST_ASSERT(bond->getPrice() == 1000.0, "Bond price correct");
    TEST_ASSERT(bond->getType() == "Bond", "Bond type correct");
    TEST_ASSERT(bond->calculateValue() == 1035.0, "Bond value calculation correct");
    TEST_ASSERT(bond->calculateRisk() == 51.75, "Bond risk calculation correct");
    
    return true;
}

bool test_option_calculations() {
    std::cout << "\n=== Testing Option Calculations ===" << std::endl;
    
    auto call_option = std::make_unique<Option>("TSLA", 250.0, Option::Type::CALL, 200.0, 10);
    auto put_option = std::make_unique<Option>("TSLA", 25.0, Option::Type::PUT, 100.0, 10);
    
    TEST_ASSERT(call_option->getType() == "Call Option", "Call option type correct");
    TEST_ASSERT(call_option->calculateValue() == 50000.0, "Call option value calculation correct");
    
    TEST_ASSERT(put_option->getType() == "Put Option", "Put option type correct");
    TEST_ASSERT(put_option->calculateValue() == 75000.0, "Put option value calculation correct");
    
    return true;
}

bool test_polymorphism() {
    std::cout << "\n=== Testing Polymorphism ===" << std::endl;
    
    std::vector<std::unique_ptr<FinancialInstrument>> instruments;
    instruments.push_back(std::make_unique<Stock>("AAPL", 150.0, 100));
    instruments.push_back(std::make_unique<Bond>("US10Y", 1000.0, 3.5, 10));
    instruments.push_back(std::make_unique<Option>("TSLA", 25.0, Option::Type::CALL, 200.0, 10));
    
    std::vector<std::string> expected_types = {"Stock", "Bond", "Call Option"};
    
    for (size_t i = 0; i < instruments.size(); ++i) {
        TEST_ASSERT(instruments[i]->getType() == expected_types[i], "Polymorphic type identification correct");
        TEST_ASSERT(instruments[i]->calculateValue() >= 0.0, "Polymorphic value calculation non-negative");
        TEST_ASSERT(instruments[i]->calculateRisk() >= 0.0, "Polymorphic risk calculation non-negative");
    }
    
    return true;
}

bool test_unique_ptr() {
    std::cout << "\n=== Testing Unique Pointer ===" << std::endl;
    
    auto instrument = std::make_unique<Stock>("MSFT", 300.0, 50);
    
    TEST_ASSERT(instrument.get() != nullptr, "Unique pointer created successfully");
    TEST_ASSERT(instrument->getSymbol() == "MSFT", "Unique pointer contains correct object");
    
    // Test move semantics
    std::unique_ptr<FinancialInstrument> moved = std::move(instrument);
    TEST_ASSERT(instrument.get() == nullptr, "Original pointer null after move");
    TEST_ASSERT(moved.get() != nullptr, "Moved pointer contains object");
    TEST_ASSERT(moved->getSymbol() == "MSFT", "Moved object preserved");
    
    return true;
}

bool test_shared_ptr() {
    std::cout << "\n=== Testing Shared Pointer ===" << std::endl;
    
    auto stock = std::make_shared<Stock>("GOOGL", 2500.0, 10);
    
    TEST_ASSERT(stock.use_count() == 1, "Initial reference count is 1");
    
    std::shared_ptr<FinancialInstrument> copy = stock;
    TEST_ASSERT(stock.use_count() == 2, "Reference count increased to 2");
    TEST_ASSERT(copy.use_count() == 2, "Copy reference count is also 2");
    
    std::vector<std::shared_ptr<FinancialInstrument>> instruments;
    instruments.push_back(stock);
    instruments.push_back(copy);
    
    TEST_ASSERT(stock.use_count() == 4, "Reference count increased to 4");
    
    instruments.clear();
    TEST_ASSERT(stock.use_count() == 2, "Reference count decreased to 2");
    
    copy.reset();
    TEST_ASSERT(stock.use_count() == 1, "Reference count decreased to 1");
    
    return true;
}

bool test_weak_ptr() {
    std::cout << "\n=== Testing Weak Pointer ===" << std::endl;
    
    auto stock = std::make_shared<Stock>("AAPL", 150.0, 100);
    std::weak_ptr<FinancialInstrument> weak_stock = stock;
    
    TEST_ASSERT(!weak_stock.expired(), "Weak pointer is not expired");
    TEST_ASSERT(stock.use_count() == 1, "Reference count is 1");
    
    // Lock weak_ptr
    if (auto locked = weak_stock.lock()) {
        TEST_ASSERT(locked->getSymbol() == "AAPL", "Weak pointer locked successfully");
        TEST_ASSERT(stock.use_count() == 2, "Reference count increased during lock");
    } else {
        TEST_ASSERT(false, "Weak pointer should be lockable");
    }
    
    // Reset shared_ptr
    stock.reset();
    TEST_ASSERT(weak_stock.expired(), "Weak pointer is expired after shared_ptr reset");
    
    // Weak pointer should be expired
    auto locked = weak_stock.lock();
    TEST_ASSERT(locked.get() == nullptr, "Expired weak pointer cannot be locked");
    
    return true;
}

bool test_factory_function() {
    std::cout << "\n=== Testing Factory Function ===" << std::endl;
    
    auto stock = createInstrument("stock", "TSLA", 800.0);
    auto bond = createInstrument("bond", "CORP", 950.0);
    auto call = createInstrument("call", "NVDA", 50.0);
    auto put = createInstrument("put", "AMD", 30.0);
    auto invalid = createInstrument("invalid", "XYZ", 100.0);
    
    TEST_ASSERT(stock.get() != nullptr, "Factory created stock successfully");
    TEST_ASSERT(stock->getType() == "Stock", "Factory created correct stock type");
    TEST_ASSERT(stock->getSymbol() == "TSLA", "Factory created stock with correct symbol");
    
    TEST_ASSERT(bond.get() != nullptr, "Factory created bond successfully");
    TEST_ASSERT(bond->getType() == "Bond", "Factory created correct bond type");
    TEST_ASSERT(bond->getSymbol() == "CORP", "Factory created bond with correct symbol");
    
    TEST_ASSERT(call.get() != nullptr, "Factory created call option successfully");
    TEST_ASSERT(call->getType() == "Call Option", "Factory created correct call option type");
    TEST_ASSERT(call->getSymbol() == "NVDA", "Factory created call option with correct symbol");
    
    TEST_ASSERT(put.get() != nullptr, "Factory created put option successfully");
    TEST_ASSERT(put->getType() == "Put Option", "Factory created correct put option type");
    TEST_ASSERT(put->getSymbol() == "AMD", "Factory created put option with correct symbol");
    
    TEST_ASSERT(invalid.get() == nullptr, "Factory returns nullptr for invalid type");
    
    return true;
}

int main() {
    std::cout << "=== Running Simple Tests for Financial Instruments ===" << std::endl;
    
    bool all_passed = true;
    
    all_passed &= test_stock_calculations();
    all_passed &= test_bond_calculations();
    all_passed &= test_option_calculations();
    all_passed &= test_polymorphism();
    all_passed &= test_unique_ptr();
    all_passed &= test_shared_ptr();
    all_passed &= test_weak_ptr();
    all_passed &= test_factory_function();
    
    std::cout << "\n=== Test Results ===" << std::endl;
    if (all_passed) {
        std::cout << "✓ All tests passed!" << std::endl;
        return 0;
    } else {
        std::cout << "✗ Some tests failed!" << std::endl;
        return 1;
    }
}
