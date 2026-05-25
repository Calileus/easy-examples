/// \file threaded_main.cpp
/// \brief Advanced C++ threading demonstrations with smart pointers.
///
/// Demonstrates:
/// - **Thread-safe operations** with shared_ptr in multithreaded contexts.
/// - **Async operations** using std::async and std::future.
/// - **Producer-consumer pattern** with condition variables.
/// - **Market simulation** with multiple concurrent worker threads.
///
/// \author Quantitative Finance Example
/// \version 1.0

#include "threaded_market.h"
#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <future>

// Factory function (same as before)
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

// Demonstrate basic threading with smart pointers
void demonstrateBasicThreading() {
    std::cout << "\n=== Basic Threading Demonstration ===" << std::endl;
    
    // Create instruments using unique_ptr
    auto stock = std::make_unique<Stock>("AAPL", 150.0, 100);
    auto bond = std::make_unique<Bond>("US10Y", 1000.0, 3.5, 10);
    
    // Move to shared_ptr for thread sharing
    std::shared_ptr<FinancialInstrument> shared_stock = std::move(stock);
    std::shared_ptr<FinancialInstrument> shared_bond = std::move(bond);
    
    // Create threads that work with the shared instruments
    std::thread stock_thread([shared_stock]() {
        for (int i = 0; i < 5; ++i) {
            double new_price = shared_stock->getPrice() * (1.0 + 0.01 * i);
            shared_stock->setPrice(new_price);
            
            std::stringstream ss;
            ss << "Stock thread: Updated " << shared_stock->getSymbol() 
               << " to $" << new_price << ", Value: $" << shared_stock->calculateValue();
            ThreadSafeLogger::getInstance().logWithThread(ss.str());
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    
    std::thread bond_thread([shared_bond]() {
        for (int i = 0; i < 5; ++i) {
            double new_price = shared_bond->getPrice() * (1.0 - 0.005 * i);
            shared_bond->setPrice(new_price);
            
            std::stringstream ss;
            ss << "Bond thread: Updated " << shared_bond->getSymbol() 
               << " to $" << new_price << ", Value: $" << shared_bond->calculateValue();
            ThreadSafeLogger::getInstance().logWithThread(ss.str());
            
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    });
    
    // Wait for threads to complete
    stock_thread.join();
    bond_thread.join();
    
    std::cout << "Final stock value: $" << shared_stock->calculateValue() << std::endl;
    std::cout << "Final bond value: $" << shared_bond->calculateValue() << std::endl;
}

// Demonstrate async operations with smart pointers
void demonstrateAsyncOperations() {
    std::cout << "\n=== Async Operations Demonstration ===" << std::endl;
    
    auto portfolio = std::make_shared<ThreadSafePortfolio>("Async Portfolio");
    
    // Add instruments
    portfolio->addInstrument(std::make_shared<Stock>("GOOGL", 2500.0, 50));
    portfolio->addInstrument(std::make_shared<Bond>("CORP", 950.0, 5.0, 5));
    portfolio->addInstrument(std::make_shared<Option>("TSLA", 25.0, Option::Type::CALL, 200.0, 10));
    
    // Launch async calculations
    auto value_future = AsyncUtils::asyncCalculatePortfolioValue(portfolio);
    auto risk_future = AsyncUtils::asyncCalculatePortfolioRisk(portfolio);
    
    // Do other work while calculations run
    ThreadSafeLogger::getInstance().log("Main thread doing other work...");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Get results
    double total_value = value_future.get();
    double total_risk = risk_future.get();
    
    std::cout << "Async calculated value: $" << total_value << std::endl;
    std::cout << "Async calculated risk: $" << total_risk << std::endl;
}

// Demonstrate producer-consumer pattern
void demonstrateProducerConsumer() {
    std::cout << "\n=== Producer-Consumer Pattern Demonstration ===" << std::endl;
    
    MarketDataFeed feed;
    feed.start();
    
    auto portfolio = std::make_shared<ThreadSafePortfolio>("Consumer Portfolio");
    portfolio->addInstrument(std::make_shared<Stock>("MSFT", 300.0, 25));
    
    feed.addSubscriber(portfolio);
    
    // Producer thread
    std::thread producer([&feed]() {
        for (int i = 0; i < 10; ++i) {
            feed.generatePriceUpdate("MSFT", 300.0 + i * 10);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    });
    
    // Consumer thread
    std::thread consumer([&feed]() {
        PriceUpdate update("", 0.0);
        int count = 0;
        while (count < 10) {
            if (feed.getNextUpdate(update)) {
                std::stringstream ss;
                ss << "Consumer received: " << update.symbol << " -> $" << update.new_price;
                ThreadSafeLogger::getInstance().logWithThread(ss.str());
                count++;
            }
        }
    });
    
    producer.join();
    consumer.join();
    feed.stop();
}

// Demonstrate thread-safe polymorphic operations
void demonstratePolymorphicThreading() {
    std::cout << "\n=== Polymorphic Threading Demonstration ===" << std::endl;
    
    std::vector<std::shared_ptr<FinancialInstrument>> instruments;
    instruments.push_back(std::make_shared<Stock>("AAPL", 150.0, 100));
    instruments.push_back(std::make_shared<Bond>("US10Y", 1000.0, 3.5, 10));
    instruments.push_back(std::make_shared<Option>("TSLA", 25.0, Option::Type::CALL, 200.0, 10));
    
    std::vector<std::thread> threads;
    
    // Create a thread for each instrument type
    for (auto& instrument : instruments) {
        threads.emplace_back([instrument]() {
            for (int i = 0; i < 3; ++i) {
                // Polymorphic behavior - each instrument type calls its own methods
                double current_value = instrument->calculateValue();
                double current_risk = instrument->calculateRisk();
                
                std::stringstream ss;
                ss << "Thread for " << instrument->getType() << " (" << instrument->getSymbol() 
                   << "): Value=$" << current_value << ", Risk=$" << current_risk;
                ThreadSafeLogger::getInstance().logWithThread(ss.str());
                
                // Update price
                double new_price = instrument->getPrice() * (1.0 + 0.02 * (i + 1));
                instrument->setPrice(new_price);
                
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
            }
        });
    }
    
    // Wait for all threads
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Show final results
    std::cout << "\nFinal instrument values:" << std::endl;
    for (const auto& instrument : instruments) {
        std::cout << instrument->getType() << " (" << instrument->getSymbol() 
                  << "): $" << instrument->calculateValue() << std::endl;
    }
}

// Demonstrate weak_ptr usage in multithreaded environment
void demonstrateWeakPtrThreading() {
    std::cout << "\n=== Weak Pointer Threading Demonstration ===" << std::endl;
    
    auto portfolio = std::make_shared<ThreadSafePortfolio>("WeakPtr Portfolio");
    portfolio->addInstrument(std::make_shared<Stock>("NVDA", 500.0, 20));
    
    std::weak_ptr<ThreadSafePortfolio> weak_portfolio = portfolio;
    
    // Thread that uses weak_ptr
    std::thread weak_thread([weak_portfolio]() {
        for (int i = 0; i < 5; ++i) {
            if (auto locked = weak_portfolio.lock()) {
                double value = locked->calculateTotalValue();
                std::stringstream ss;
                ss << "Weak thread: Portfolio value = $" << value;
                ThreadSafeLogger::getInstance().logWithThread(ss.str());
            } else {
                ThreadSafeLogger::getInstance().logWithThread("Weak thread: Portfolio expired");
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    });
    
    // Main thread destroys portfolio after some time
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    std::cout << "Main thread: Destroying portfolio..." << std::endl;
    portfolio.reset();
    
    weak_thread.join();
}

// Main market simulation
void runMarketSimulation() {
    std::cout << "\n=== Full Market Simulation ===" << std::endl;
    
    MarketSimulation simulation;
    
    // Create portfolios
    auto tech_portfolio = std::make_shared<ThreadSafePortfolio>("Technology");
    auto bond_portfolio = std::make_shared<ThreadSafePortfolio>("Fixed Income");
    auto mixed_portfolio = std::make_shared<ThreadSafePortfolio>("Mixed Strategy");
    
    // Add instruments to portfolios
    tech_portfolio->addInstrument(std::make_shared<Stock>("AAPL", 150.0, 100));
    tech_portfolio->addInstrument(std::make_shared<Stock>("GOOGL", 2500.0, 50));
    tech_portfolio->addInstrument(std::make_shared<Option>("TSLA", 25.0, Option::Type::CALL, 200.0, 10));
    
    bond_portfolio->addInstrument(std::make_shared<Bond>("US10Y", 1000.0, 3.5, 10));
    bond_portfolio->addInstrument(std::make_shared<Bond>("CORP", 950.0, 5.0, 5));
    
    mixed_portfolio->addInstrument(std::make_shared<Stock>("MSFT", 300.0, 75));
    mixed_portfolio->addInstrument(std::make_shared<Bond>("US10Y", 1000.0, 3.5, 10));
    mixed_portfolio->addInstrument(std::make_shared<Option>("NVDA", 50.0, Option::Type::PUT, 400.0, 5));
    
    // Add portfolios to simulation
    simulation.addPortfolio(tech_portfolio);
    simulation.addPortfolio(bond_portfolio);
    simulation.addPortfolio(mixed_portfolio);
    
    // Run simulation for 10 seconds
    simulation.runSimulation(10);
}

int main() {
    std::cout << "=== C++ Threading, Polymorphism and Smart Points Example ===" << std::endl;
    std::cout << "Advanced Financial Instruments for Quant Dev Interview" << std::endl;
    
    try {
        demonstrateBasicThreading();
        demonstrateAsyncOperations();
        demonstrateProducerConsumer();
        demonstratePolymorphicThreading();
        demonstrateWeakPtrThreading();
        runMarketSimulation();
        
        std::cout << "\n=== All threading demonstrations completed successfully! ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
