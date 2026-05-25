#pragma once

#include "financial_instrument.h"
#include <memory>
#include <string>
#include <vector>

class Portfolio {
public:
    explicit Portfolio(const std::string& name);

    void addInstrument(std::shared_ptr<FinancialInstrument> instrument);
    double calculateTotalValue() const;
    double calculateTotalRisk() const;
    void printPortfolio() const;

private:
    std::string name_;
    std::vector<std::shared_ptr<FinancialInstrument>> instruments_;
};

class Market {
public:
    explicit Market(const std::string& name);

    void addPortfolio(std::shared_ptr<Portfolio> portfolio);
    void updateAllPrices(double multiplier);

private:
    std::string name_;
    std::vector<std::shared_ptr<Portfolio>> portfolios_;
    std::vector<std::weak_ptr<Portfolio>> portfolio_refs_;
};

std::unique_ptr<FinancialInstrument> createInstrument(
    const std::string& type,
    const std::string& symbol,
    double price);
