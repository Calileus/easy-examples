#pragma once

#include "financial_instrument.h"
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <future>
#include <chrono>
#include <random>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include <algorithm>

// Thread-safe logger for market events
class ThreadSafeLogger {
public:
    static ThreadSafeLogger& getInstance() {
        static ThreadSafeLogger instance;
        return instance;
    }
    
    void log(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << "[" << getCurrentTimestamp() << "] " << message << std::endl;
    }
    
    void logWithThread(const std::string& message) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << "[" << getCurrentTimestamp() << "][Thread-" 
                  << std::this_thread::get_id() << "] " << message << std::endl;
    }

private:
    std::mutex mutex_;
    
    std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        std::tm local_tm{};
    #if defined(_WIN32)
        localtime_s(&local_tm, &time_t);
    #else
        localtime_r(&time_t, &local_tm);
    #endif
        
        std::stringstream ss;
        ss << std::put_time(&local_tm, "%H:%M:%S");
        ss << "." << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }
};

// Thread-safe price update event
struct PriceUpdate {
    std::string symbol;
    double new_price;
    std::chrono::system_clock::time_point timestamp;
    
    PriceUpdate(const std::string& sym, double price)
        : symbol(sym), new_price(price), timestamp(std::chrono::system_clock::now()) {}
};

// Thread-safe portfolio class
class ThreadSafePortfolio {
public:
    ThreadSafePortfolio(const std::string& name) : name_(name) {}
    
    void addInstrument(std::shared_ptr<FinancialInstrument> instrument) {
        std::lock_guard<std::mutex> lock(mutex_);
        instruments_.push_back(instrument);
        logger_.logWithThread("Added " + instrument->getType() + " (" + instrument->getSymbol() + 
                             ") to portfolio " + name_);
    }
    
    void updateInstrumentPrice(const std::string& symbol, double new_price) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& instrument : instruments_) {
            if (instrument->getSymbol() == symbol) {
                double old_price = instrument->getPrice();
                instrument->setPrice(new_price);
                logger_.logWithThread("Updated " + symbol + " price: $" + 
                             std::to_string(old_price) + " -> $" + std::to_string(new_price) +
                             " in portfolio " + name_);
                break;
            }
        }
    }
    
    double calculateTotalValue() const {
        std::lock_guard<std::mutex> lock(mutex_);
        double total = 0.0;
        for (const auto& instrument : instruments_) {
            total += instrument->calculateValue();
        }
        return total;
    }
    
    double calculateTotalRisk() const {
        std::lock_guard<std::mutex> lock(mutex_);
        double total = 0.0;
        for (const auto& instrument : instruments_) {
            total += instrument->calculateRisk();
        }
        return total;
    }
    
    size_t getInstrumentCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return instruments_.size();
    }
    
    std::string getName() const {
        return name_;
    }
    
    void printPortfolio() const {
        std::lock_guard<std::mutex> lock(mutex_);
        double total_value = 0.0;
        double total_risk = 0.0;
        logger_.log("=== Portfolio: " + name_ + " ===");
        for (const auto& instrument : instruments_) {
            const double value = instrument->calculateValue();
            const double risk = instrument->calculateRisk();
            total_value += value;
            total_risk += risk;
            std::stringstream ss;
            ss << "  " << instrument->getType() << ": " << instrument->getSymbol() 
               << ", Price: $" << instrument->getPrice() 
               << ", Value: $" << value;
            logger_.log(ss.str());
        }
        logger_.log("Total Value: $" + std::to_string(total_value));
        logger_.log("Total Risk: $" + std::to_string(total_risk));
        logger_.log("========================");
    }

private:
    mutable std::mutex mutex_;
    std::string name_;
    std::vector<std::shared_ptr<FinancialInstrument>> instruments_;
    ThreadSafeLogger& logger_ = ThreadSafeLogger::getInstance();
};

// Thread-safe market data feed
class MarketDataFeed {
public:
    MarketDataFeed() : running_(false) {}
    
    void start() {
        running_ = true;
        logger_.logWithThread("Market data feed started");
    }
    
    void stop() {
        running_ = false;
        logger_.logWithThread("Market data feed stopped");
    }
    
    void addSubscriber(std::weak_ptr<ThreadSafePortfolio> portfolio) {
        std::lock_guard<std::mutex> lock(mutex_);
        subscribers_.push_back(portfolio);
    }
    
    double getLastPrice(const std::string& symbol) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = last_prices_.find(symbol);
        return (it != last_prices_.end()) ? it->second : 100.0; // Default price
    }
    
    void generatePriceUpdate(const std::string& symbol, double current_price) {
        if (!running_) return;
        
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::normal_distribution<> dist(0.0, 0.02); // 2% volatility
        
        double change_percent = dist(gen);
        double new_price = current_price * (1.0 + change_percent);
        
        // Ensure price doesn't go negative
        new_price = std::max(0.01, new_price);
        
        PriceUpdate update(symbol, new_price);

        std::vector<std::shared_ptr<ThreadSafePortfolio>> active_subscribers;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            for (auto it = subscribers_.begin(); it != subscribers_.end();) {
            if (auto portfolio = it->lock()) {
                active_subscribers.push_back(portfolio);
                ++it;
            } else {
                it = subscribers_.erase(it);
            }
        }
        }

        for (const auto& portfolio : active_subscribers) {
            portfolio->updateInstrumentPrice(symbol, new_price);
        }
        
        {
            std::lock_guard<std::mutex> queue_lock(queue_mutex_);
            update_queue_.push(update);
        }
        queue_cv_.notify_one();

        {
            std::lock_guard<std::mutex> lock(mutex_);
            last_prices_[symbol] = new_price;
        }
    }
    
    bool getNextUpdate(PriceUpdate& update) {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        queue_cv_.wait(lock, [this] { return !update_queue_.empty() || !running_; });
        
        if (!running_ && update_queue_.empty()) return false;
        
        update = update_queue_.front();
        update_queue_.pop();
        return true;
    }

private:
    std::atomic<bool> running_;
    mutable std::mutex mutex_;
    mutable std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::queue<PriceUpdate> update_queue_;
    std::vector<std::weak_ptr<ThreadSafePortfolio>> subscribers_;
    std::unordered_map<std::string, double> last_prices_;
    ThreadSafeLogger& logger_ = ThreadSafeLogger::getInstance();
};

// Market simulation orchestrator
class MarketSimulation {
public:
    MarketSimulation() : running_(false) {}
    
    void addPortfolio(std::shared_ptr<ThreadSafePortfolio> portfolio) {
        portfolios_.push_back(portfolio);
        market_feed_.addSubscriber(portfolio);
        
        // Track symbols for price updates
        std::lock_guard<std::mutex> lock(mutex_);
        for (size_t i = 0; i < portfolio->getInstrumentCount(); ++i) {
            // Note: In a real implementation, we'd need to expose instrument symbols
            // For now, we'll track common symbols
        }
    }
    
    void start() {
        if (running_.load()) return;
        
        running_ = true;
        market_feed_.start();
        
        logger_.logWithThread("Starting market simulation");
        
        // Start price update threads
        price_update_thread_ = std::thread(&MarketSimulation::priceUpdateWorker, this);
        
        // Start monitoring thread
        monitoring_thread_ = std::thread(&MarketSimulation::monitoringWorker, this);
        
        // Start portfolio calculation threads
        for (size_t i = 0; i < portfolios_.size(); ++i) {
            calculation_threads_.emplace_back(&MarketSimulation::portfolioCalculationWorker, 
                                              this, portfolios_[i]);
        }
    }
    
    void stop() {
        if (!running_.load()) return;
        
        running_ = false;
        market_feed_.stop();
        
        logger_.logWithThread("Stopping market simulation");
        
        // Wait for all threads to finish
        if (price_update_thread_.joinable()) {
            price_update_thread_.join();
        }
        
        if (monitoring_thread_.joinable()) {
            monitoring_thread_.join();
        }
        
        for (auto& thread : calculation_threads_) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        
        calculation_threads_.clear();
    }
    
    void runSimulation(int duration_seconds) {
        start();
        
        logger_.log("Simulation running for " + std::to_string(duration_seconds) + " seconds");
        
        std::this_thread::sleep_for(std::chrono::seconds(duration_seconds));
        
        stop();
        
        logger_.log("Simulation completed");
        
        // Print final portfolio states
        for (const auto& portfolio : portfolios_) {
            portfolio->printPortfolio();
        }
    }

private:
    std::atomic<bool> running_;
    MarketDataFeed market_feed_;
    std::vector<std::shared_ptr<ThreadSafePortfolio>> portfolios_;
    std::thread price_update_thread_;
    std::thread monitoring_thread_;
    std::vector<std::thread> calculation_threads_;
    mutable std::mutex mutex_;
    ThreadSafeLogger& logger_ = ThreadSafeLogger::getInstance();
    
    void priceUpdateWorker() {
        logger_.logWithThread("Price update thread started");
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> symbol_dist(0, 2);
        std::uniform_int_distribution<> delay_dist(100, 500); // 100-500ms
        
        std::vector<std::pair<std::string, double>> symbols = {
            {"AAPL", 150.0},
            {"GOOGL", 2500.0},
            {"TSLA", 800.0},
            {"MSFT", 300.0},
            {"US10Y", 1000.0}
        };
        
        while (running_.load()) {
            // Generate random price updates
            int symbol_idx = symbol_dist(gen) % symbols.size();
            market_feed_.generatePriceUpdate(symbols[symbol_idx].first, symbols[symbol_idx].second);
            
            // Update the stored price
            symbols[symbol_idx].second = market_feed_.getLastPrice(symbols[symbol_idx].first);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(gen)));
        }
        
        logger_.logWithThread("Price update thread stopped");
    }
    
    void monitoringWorker() {
        logger_.logWithThread("Monitoring thread started");
        
        PriceUpdate update("", 0.0);
        while (running_.load()) {
            if (market_feed_.getNextUpdate(update)) {
                // Log price updates for monitoring
                std::stringstream ss;
                ss << "MONITOR: " << update.symbol << " -> $" << update.new_price;
                logger_.logWithThread(ss.str());
            }
        }
        
        logger_.logWithThread("Monitoring thread stopped");
    }
    
    void portfolioCalculationWorker(std::shared_ptr<ThreadSafePortfolio> portfolio) {
        logger_.logWithThread("Portfolio calculation thread started for " + portfolio->getName());
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> delay_dist(1000, 3000); // 1-3 seconds
        
        while (running_.load()) {
            double total_value = portfolio->calculateTotalValue();
            double total_risk = portfolio->calculateTotalRisk();
            
            std::stringstream ss;
            ss << "CALC: " << portfolio->getName() 
               << " | Value: $" << total_value 
               << " | Risk: $" << total_risk
               << " | Instruments: " << portfolio->getInstrumentCount();
            logger_.logWithThread(ss.str());
            
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_dist(gen)));
        }
        
        logger_.logWithThread("Portfolio calculation thread stopped for " + portfolio->getName());
    }
};

// Utility functions for async operations
namespace AsyncUtils {
    template<typename F, typename... Args>
    auto asyncExecute(F&& func, Args&&... args) -> std::future<decltype(func(args...))> {
        return std::async(std::launch::async, std::forward<F>(func), std::forward<Args>(args)...);
    }
    
    std::future<double> asyncCalculatePortfolioValue(std::shared_ptr<ThreadSafePortfolio> portfolio) {
        return asyncExecute([&portfolio]() {
            return portfolio->calculateTotalValue();
        });
    }
    
    std::future<double> asyncCalculatePortfolioRisk(std::shared_ptr<ThreadSafePortfolio> portfolio) {
        return asyncExecute([&portfolio]() {
            return portfolio->calculateTotalRisk();
        });
    }
}
