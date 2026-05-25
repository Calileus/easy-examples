/// \file portfolio_market.cpp
/// \brief Implementation of Portfolio and Market classes.
///
/// This file contains the implementation of shared portfolio and market
/// management functionality extracted from main.cpp for code reuse across
/// examples and tests.
///
/// \author Quantitative Finance Example
/// \version 1.0

#include "portfolio_market.h"

#include <iostream>

/// \brief Construct an empty portfolio with a given name.
Portfolio::Portfolio(const std::string& name) : name_(name) {}

void Portfolio::addInstrument(std::shared_ptr<FinancialInstrument> instrument) {
    instruments_.push_back(instrument);
}

double Portfolio::calculateTotalValue() const {
    double total = 0.0;
    for (const auto& instrument : instruments_) {
        total += instrument->calculateValue();
    }
    return total;
}

double Portfolio::calculateTotalRisk() const {
    double total = 0.0;
    for (const auto& instrument : instruments_) {
        total += instrument->calculateRisk();
    }
    return total;
}

void Portfolio::printPortfolio() const {
    std::cout << "\n=== Portfolio: " << name_ << " ===" << std::endl;
    for (const auto& instrument : instruments_) {
        instrument->printDetails();
    }
    std::cout << "Total Value: $" << calculateTotalValue() << std::endl;
    std::cout << "Total Risk: $" << calculateTotalRisk() << std::endl;
    std::cout << "========================\n" << std::endl;
}

Market::Market(const std::string& name) : name_(name) {}

void Market::addPortfolio(std::shared_ptr<Portfolio> portfolio) {
    portfolios_.push_back(portfolio);
    portfolio_refs_.push_back(portfolio);
}

void Market::updateAllPrices(double multiplier) {
    std::cout << "\n=== Market Update: " << name_ << " ===" << std::endl;
    std::cout << "Updating prices by factor: " << multiplier << std::endl;

    for (auto& weak_ref : portfolio_refs_) {
        if (auto portfolio = weak_ref.lock()) {
            std::cout << "Portfolio still exists: " << portfolio->calculateTotalValue() << std::endl;
        } else {
            std::cout << "Portfolio has been destroyed" << std::endl;
        }
    }
}

std::unique_ptr<FinancialInstrument> createInstrument(
    const std::string& type,
    const std::string& symbol,
    double price) {
    if (type == "stock") {
        return std::make_unique<Stock>(symbol, price, 100);
    }
    if (type == "bond") {
        return std::make_unique<Bond>(symbol, price, 5.0, 10);
    }
    if (type == "call") {
        return std::make_unique<Option>(symbol, price, Option::Type::CALL, 150.0, 10);
    }
    if (type == "put") {
        return std::make_unique<Option>(symbol, price, Option::Type::PUT, 100.0, 10);
    }

    return nullptr;
}
