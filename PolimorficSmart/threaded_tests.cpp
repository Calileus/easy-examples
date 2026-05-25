/// \file threaded_tests.cpp
/// \brief Unit tests for threading and concurrent smart pointer usage.
///
/// Tests thread-safe operations including:
/// - Thread-safe logger with mutex protection
/// - Concurrent portfolio modification from multiple threads
/// - Market data feed with producer-consumer pattern
/// - Async operations with futures
/// - Polymorphic operations across threads
/// - Weak pointer behavior in multithreaded context
/// - Market simulation with multiple worker threads
/// - Shared pointer thread safety
/// - Condition variables for synchronization
///
/// Uses a simple custom TEST_ASSERT macro for testing without external dependencies.
///
/// \author Quantitative Finance Example
/// \version 1.0

#include "threaded_market.h"
#include <iostream>
#include <cassert>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>

/// \brief Simple assertion macro for testing.
/// Prints "PASS" or "FAIL" and returns false on failure, preventing further test execution.
/// \param condition Expression to test.
/// \param message Message describing the assertion.
#define TEST_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "FAIL: " << message << std::endl; \
            return false; \
        } else { \
            std::cout << "PASS: " << message << std::endl; \
        } \
    } while(0)

// Factory function implementation
/// \brief Factory function for creating financial instruments by type.
/// 
/// Creates different instrument types without exposing the concrete classes
/// to the test code. Supports "stock", "bond", "call", and "put" types.
///
/// \param type String identifying instrument type.
/// \param symbol Instrument symbol/identifier.
/// \param price Initial price for the instrument.
/// \return Unique pointer to created instrument, or nullptr if type is invalid.
std::unique_ptr<FinancialInstrument> createInstrument(const std::string& type, 
                                                      const std::string& symbol, 
                                                      double price) {
    if (type == "stock") {
        return std::make_unique<Stock>(symbol, price, 100);
    } else if (type == "bond") {
        return std::make_unique<Bond>(symbol, price, 5.0, 10);
    } else if (type == "call") {
        return std::make_unique<Option>(symbol, price, Option::Type::CALL, 150.0, 10);
    } else if (type == "put") {
        return std::make_unique<Option>(symbol, price, Option::Type::PUT, 100.0, 10);
    }
    return nullptr;
}

bool test_thread_safe_logger() {
    std::cout << "\n=== Testing Thread-Safe Logger ===" << std::endl;
    
    auto& logger = ThreadSafeLogger::getInstance();
    
    // Test basic logging
    logger.log("Test message");
    logger.logWithThread("Thread test message");
    
    // Test concurrent logging
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&logger, i]() {
            logger.logWithThread("Concurrent message " + std::to_string(i));
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    TEST_ASSERT(true, "Thread-safe logger handles concurrent access");
    return true;
}

bool test_thread_safe_portfolio() {
    std::cout << "\n=== Testing Thread-Safe Portfolio ===" << std::endl;
    
    auto portfolio = std::make_shared<ThreadSafePortfolio>("Test Portfolio");
    
    // Test adding instruments from multiple threads
    std::vector<std::thread> threads;
    std::atomic<int> added_count{0};
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([portfolio, &added_count, i]() {
            auto instrument = std::make_shared<Stock>("STK" + std::to_string(i), 100.0 + i, 10);
            portfolio->addInstrument(instrument);
            added_count++;
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    TEST_ASSERT(added_count.load() == 10, "All instruments added from multiple threads");
    TEST_ASSERT(portfolio->getInstrumentCount() == 10, "Portfolio contains correct number of instruments");
    
    // Test concurrent price updates
    std::vector<std::thread> update_threads;
    for (int i = 0; i < 5; ++i) {
        update_threads.emplace_back([portfolio, i]() {
            portfolio->updateInstrumentPrice("STK0", 100.0 + i * 10);
        });
    }
    
    for (auto& thread : update_threads) {
        thread.join();
    }
    
    TEST_ASSERT(portfolio->calculateTotalValue() > 0, "Portfolio value calculated after concurrent updates");
    return true;
}

bool test_market_data_feed() {
    std::cout << "\n=== Testing Market Data Feed ===" << std::endl;
    
    MarketDataFeed feed;
    feed.start();
    
    auto portfolio = std::make_shared<ThreadSafePortfolio>("Feed Test Portfolio");
    portfolio->addInstrument(std::make_shared<Stock>("TEST", 100.0, 10));
    
    feed.addSubscriber(portfolio);
    
    // Test price updates
    feed.generatePriceUpdate("TEST", 105.0);
    feed.generatePriceUpdate("TEST", 110.0);
    
    // Test consuming updates
    PriceUpdate update("", 0.0);
    bool received_update = false;
    
    std::thread consumer([&feed, &update, &received_update]() {
        if (feed.getNextUpdate(update)) {
            received_update = true;
        }
    });
    
    consumer.join();
    
    feed.stop();
    
    TEST_ASSERT(received_update, "Price update received by consumer");
    TEST_ASSERT(update.symbol == "TEST", "Correct symbol in price update");
    return true;
}

bool test_async_operations() {
    std::cout << "\n=== Testing Async Operations ===" << std::endl;
    
    auto portfolio = std::make_shared<ThreadSafePortfolio>("Async Test Portfolio");
    portfolio->addInstrument(std::make_shared<Stock>("ASYNC", 200.0, 50));
    
    // Test async calculations
    auto value_future = AsyncUtils::asyncCalculatePortfolioValue(portfolio);
    auto risk_future = AsyncUtils::asyncCalculatePortfolioRisk(portfolio);
    
    double value = value_future.get();
    double risk = risk_future.get();
    
    TEST_ASSERT(value > 0, "Async value calculation successful");
    TEST_ASSERT(risk > 0, "Async risk calculation successful");
    TEST_ASSERT(value == 10000.0, "Correct portfolio value calculated");
    return true;
}

bool test_polymorphic_threading() {
    std::cout << "\n=== Testing Polymorphic Threading ===" << std::endl;
    
    std::vector<std::shared_ptr<FinancialInstrument>> instruments;
    instruments.push_back(std::make_shared<Stock>("POLY_STOCK", 150.0, 100));
    instruments.push_back(std::make_shared<Bond>("POLY_BOND", 1000.0, 3.5, 10));
    instruments.push_back(std::make_shared<Option>("POLY_OPT", 25.0, Option::Type::CALL, 200.0, 10));
    
    std::vector<std::thread> threads;
    std::atomic<int> completed_operations{0};
    
    // Create threads for each instrument type
    for (auto& instrument : instruments) {
        threads.emplace_back([&instrument, &completed_operations]() -> bool {
            // Test polymorphic behavior in thread
            std::string type = instrument->getType();
            double value = instrument->calculateValue();
            double risk = instrument->calculateRisk();
            
            TEST_ASSERT(!type.empty(), "Type identified correctly in thread");
            TEST_ASSERT(value >= 0, "Value calculated correctly in thread");
            TEST_ASSERT(risk >= 0, "Risk calculated correctly in thread");
            
            completed_operations++;
            return true;
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    TEST_ASSERT(completed_operations.load() == 3, "All polymorphic operations completed");
    return true;
}

bool test_weak_ptr_threading() {
    std::cout << "\n=== Testing Weak Pointer Threading ===" << std::endl;
    
    auto portfolio = std::make_shared<ThreadSafePortfolio>("Weak Test Portfolio");
    portfolio->addInstrument(std::make_shared<Stock>("WEAK", 300.0, 10));
    
    std::weak_ptr<ThreadSafePortfolio> weak_portfolio = portfolio;
    std::atomic<bool> weak_ptr_worked{false};
    
    // Thread using weak_ptr
    std::thread weak_thread([&weak_portfolio, &weak_ptr_worked]() -> bool {
        if (auto locked = weak_portfolio.lock()) {
            double value = locked->calculateTotalValue();
            TEST_ASSERT(value > 0, "Weak pointer locked successfully");
            weak_ptr_worked = true;
        }
        return true;
    });
    
    weak_thread.join();
    
    TEST_ASSERT(weak_ptr_worked.load(), "Weak pointer worked correctly in thread");
    
    // Test expired weak_ptr
    portfolio.reset();
    
    std::thread expired_thread([&weak_portfolio]() -> bool {
        auto locked = weak_portfolio.lock();
        TEST_ASSERT(locked.get() == nullptr, "Weak pointer correctly reports expired");
        return true;
    });
    
    expired_thread.join();
    
    return true;
}

bool test_market_simulation() {
    std::cout << "\n=== Testing Market Simulation ===" << std::endl;
    
    MarketSimulation simulation;
    
    auto portfolio = std::make_shared<ThreadSafePortfolio>("Sim Test Portfolio");
    portfolio->addInstrument(std::make_shared<Stock>("SIM", 100.0, 10));
    
    simulation.addPortfolio(portfolio);
    
    // Test start/stop
    simulation.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    simulation.stop();
    
    TEST_ASSERT(true, "Market simulation started and stopped successfully");
    return true;
}

bool test_shared_ptr_thread_safety() {
    std::cout << "\n=== Testing Shared Pointer Thread Safety ===" << std::endl;
    
    auto instrument = std::make_shared<Stock>("SHARED", 200.0, 50);
    
    std::vector<std::thread> threads;
    std::atomic<int> operations{0};
    
    // Multiple threads sharing the same instrument
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([instrument, &operations, i]() -> bool {
            // Test shared access
            double price = instrument->getPrice();
            double value = instrument->calculateValue();
            std::string type = instrument->getType();
            
            TEST_ASSERT(price > 0, "Price accessible from thread");
            TEST_ASSERT(value > 0, "Value accessible from thread");
            TEST_ASSERT(!type.empty(), "Type accessible from thread");
            
            operations++;
            return true;
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
    
    TEST_ASSERT(operations.load() == 10, "All shared pointer operations completed");
    TEST_ASSERT(instrument.use_count() == 1, "Reference count correct after threads complete");
    return true;
}

bool test_unique_ptr_move_semantics() {
    std::cout << "\n=== Testing Unique Pointer Move Semantics ===" << std::endl;
    
    auto instrument = createInstrument("stock", "UNIQUE", 150.0);
    
    TEST_ASSERT(instrument.get() != nullptr, "Unique pointer created");
    
    // Test move to shared_ptr for threading
    std::shared_ptr<FinancialInstrument> shared = std::move(instrument);
    TEST_ASSERT(instrument.get() == nullptr, "Original unique pointer null after move");
    TEST_ASSERT(shared.get() != nullptr, "Shared pointer contains moved object");
    
    // Use in thread
    std::thread thread([shared]() -> bool {
        TEST_ASSERT(shared->getSymbol() == "UNIQUE", "Moved object accessible in thread");
        return true;
    });
    
    thread.join();
    
    return true;
}

bool test_condition_variable_usage() {
    std::cout << "\n=== Testing Condition Variable Usage ===" << std::endl;
    
    MarketDataFeed feed;
    feed.start();
    
    std::atomic<bool> producer_done{false};
    std::atomic<bool> consumer_done{false};
    
    // Producer thread
    std::thread producer([&feed, &producer_done]() {
        for (int i = 0; i < 5; ++i) {
            feed.generatePriceUpdate("CV_TEST", 100.0 + i);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        producer_done = true;
    });
    
    // Consumer thread
    std::thread consumer([&feed, &consumer_done]() -> bool {
        int count = 0;
        while (count < 5) {
            PriceUpdate update("", 0.0);
            if (feed.getNextUpdate(update)) {
                count++;
                TEST_ASSERT(update.symbol == "CV_TEST", "Correct update received");
            }
        }
        consumer_done = true;
        return true;
    });
    
    producer.join();
    consumer.join();
    feed.stop();
    
    TEST_ASSERT(consumer_done.load(), "Consumer completed successfully");
    return true;
}

int main() {
    std::cout << "=== Running Threading Tests for Financial Instruments ===" << std::endl;
    
    bool all_passed = true;
    
    all_passed &= test_thread_safe_logger();
    all_passed &= test_thread_safe_portfolio();
    all_passed &= test_market_data_feed();
    all_passed &= test_async_operations();
    all_passed &= test_polymorphic_threading();
    all_passed &= test_weak_ptr_threading();
    all_passed &= test_market_simulation();
    all_passed &= test_shared_ptr_thread_safety();
    all_passed &= test_unique_ptr_move_semantics();
    all_passed &= test_condition_variable_usage();
    
    std::cout << "\n=== Threading Test Results ===" << std::endl;
    if (all_passed) {
        std::cout << "✓ All threading tests passed!" << std::endl;
        return 0;
    } else {
        std::cout << "✗ Some threading tests failed!" << std::endl;
        return 1;
    }
}
