#pragma once

#include "financial_instrument.h"
#include <memory>
#include <string>
#include <vector>

/// \brief A collection of financial instruments with aggregated value and risk calculations.
///
/// Portfolio manages a collection of shared_ptr to FinancialInstrument objects,
/// demonstrating shared ownership semantics.
class Portfolio {
public:
    /// \brief Construct a portfolio with a name.
    /// \param name The display name of the portfolio.
    explicit Portfolio(const std::string& name);

    /// \brief Add an instrument to this portfolio.
    /// \param instrument A shared pointer to the instrument to add.
    void addInstrument(std::shared_ptr<FinancialInstrument> instrument);
    
    /// \brief Calculate the total value of all instruments in the portfolio.
    /// \return Sum of all instrument values.
    double calculateTotalValue() const;
    
    /// \brief Calculate the total risk of all instruments in the portfolio.
    /// \return Sum of all instrument risks.
    double calculateTotalRisk() const;
    
    /// \brief Print all instruments and portfolio summary to stdout.
    void printPortfolio() const;

private:
    std::string name_;  ///< Display name of the portfolio.
    std::vector<std::shared_ptr<FinancialInstrument>> instruments_;  ///< Collection of instruments.
};

/// \brief Market observer that tracks multiple portfolios using weak_ptr.
///
/// Market demonstrates the use of weak_ptr to observe portfolios without
/// preventing their destruction.
class Market {
public:
    /// \brief Construct a market with a name.
    /// \param name The display name of the market.
    explicit Market(const std::string& name);

    /// \brief Add a portfolio to be observed by this market.
    /// \param portfolio Shared pointer to the portfolio to add.
    void addPortfolio(std::shared_ptr<Portfolio> portfolio);
    
    /// \brief Update prices in observed portfolios.
    /// \param multiplier Price adjustment factor (e.g., 1.05 for 5% increase).
    void updateAllPrices(double multiplier);

private:
    std::string name_;  ///< Display name of the market.
    std::vector<std::shared_ptr<Portfolio>> portfolios_;  ///< Strong references for ownership.
    std::vector<std::weak_ptr<Portfolio>> portfolio_refs_;  ///< Weak references for observation.
};

/// \brief Factory function to create financial instruments by type string.
///
/// This function demonstrates the factory pattern, creating objects without
/// exposing concrete types to the caller.
///
/// \param type The instrument type: "stock", "bond", "call", or "put".
/// \param symbol The symbol/identifier for the instrument.
/// \param price The initial price for the instrument.
/// \return A unique_ptr to the created instrument, or nullptr if type is invalid.
std::unique_ptr<FinancialInstrument> createInstrument(
    const std::string& type,
    const std::string& symbol,
    double price);
