#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>

/// \brief Abstract base class for all financial instruments.
///
/// This class defines the interface for different types of financial instruments
/// (stocks, bonds, options) using polymorphism. Derived classes implement
/// specific valuation and risk calculation logic.
///
/// \note Uses virtual functions to enable runtime polymorphism.
/// \example See Stock, Bond, and Option derived classes for usage.
class FinancialInstrument {
public:
    /// \brief Construct a financial instrument with a symbol and price.
    /// \param symbol The ticker symbol of the instrument.
    /// \param price The current price of the instrument.
    FinancialInstrument(const std::string& symbol, double price) 
        : symbol_(symbol), price_(price) {}
    
    /// \brief Virtual destructor for proper cleanup of derived classes.
    virtual ~FinancialInstrument() = default;
    
    /// \brief Calculate the current market value of this instrument.
    /// \return The calculated value (implementation-specific).
    virtual double calculateValue() const = 0;
    
    /// \brief Get the type of this instrument as a string.
    /// \return A string describing the instrument type (e.g., "Stock", "Bond", "Call Option").
    virtual std::string getType() const = 0;
    
    /// \brief Print detailed information about this instrument to stdout.
    virtual void printDetails() const = 0;
    
    /// \brief Get the ticker symbol of this instrument.
    /// \return The symbol string.
    std::string getSymbol() const { return symbol_; }
    
    /// \brief Get the current price of this instrument.
    /// \return The current price.
    double getPrice() const { return price_; }
    
    /// \brief Set the price of this instrument.
    /// \param price The new price to set.
    void setPrice(double price) { price_ = price; }
    
    /// \brief Calculate the risk associated with this instrument.
    /// \return The calculated risk value. Default is 10% of price.
    /// Derived classes override this to provide instrument-specific risk calculations.
    virtual double calculateRisk() const {
        return price_ * 0.1; // Default 10% risk
    }

protected:
    std::string symbol_;
    double price_;
};

// Derived class: Stock

/// \brief Represents an equity (stock) financial instrument.
///
/// A stock's value is calculated as price × number of shares.
/// Risk is calculated as 15% of the total stock value.
/// 
/// \code
/// Stock apple("AAPL", 150.0, 100);
/// double value = apple.calculateValue();  // 150 * 100 = 15,000
/// double risk = apple.calculateRisk();    // 15,000 * 0.15 = 2,250
/// \endcode
class Stock : public FinancialInstrument {
public:
    /// \brief Construct a stock with symbol, price, and share count.
    /// \param symbol The ticker symbol (e.g., "AAPL").
    /// \param price The price per share in dollars.
    /// \param shares The number of shares held.
    Stock(const std::string& symbol, double price, int shares)
        : FinancialInstrument(symbol, price), shares_(shares) {}
    
    /// \brief Calculate stock value as price × shares.
    /// \return The total stock position value.
    double calculateValue() const override {
        return price_ * shares_;
    }
    
    /// \brief Return the instrument type.
    /// \return "Stock".
    std::string getType() const override {
        return "Stock";
    }
    
    /// \brief Print stock details to stdout including type, symbol, price, shares, and value.
    void printDetails() const override {
        std::cout << "Stock: " << symbol_ << ", Price: $" << price_ 
                  << ", Shares: " << shares_ << ", Value: $" << calculateValue() << std::endl;
    }
    
    /// \brief Calculate stock risk as 15% of position value.
    /// \return Risk value.
    double calculateRisk() const override {
        return calculateValue() * 0.15; // 15% risk for stocks
    }
    
    /// \brief Get the number of shares held.
    /// \return The share count.
    int getShares() const { return shares_; }

private:
    int shares_;
};

// Derived class: Bond

/// \brief Represents a fixed-income bond instrument.
///
/// A bond's value includes the face price plus accrued coupon interest.
/// Risk is calculated as 5% of the total bond value.
///
/// \code
/// Bond usBond("US10Y", 1000.0, 3.5, 10);
/// double value = usBond.calculateValue();  // 1000 + (3.5 * 10) = 1035
/// double risk = usBond.calculateRisk();    // 1035 * 0.05 = 51.75
/// \endcode
class Bond : public FinancialInstrument {
public:
    /// \brief Construct a bond with symbol, price, coupon rate, and maturity.
    /// \param symbol The bond symbol/identifier (e.g., "US10Y").
    /// \param price The current bond price in dollars.
    /// \param coupon The annual coupon rate as a percentage.
    /// \param years Years until the bond matures.
    Bond(const std::string& symbol, double price, double coupon, int years)
        : FinancialInstrument(symbol, price), coupon_(coupon), yearsToMaturity_(years) {}
    
    /// \brief Calculate bond value using simplified formula: price + accrued interest.
    /// \return The bond value.
    double calculateValue() const override {
        // Simplified bond valuation: price + accrued interest
        return price_ + (coupon_ * yearsToMaturity_);
    }
    
    /// \brief Return the instrument type.
    /// \return "Bond".
    std::string getType() const override {
        return "Bond";
    }
    
    /// \brief Print bond details to stdout including coupon and maturity.
    void printDetails() const override {
        std::cout << "Bond: " << symbol_ << ", Price: $" << price_ 
                  << ", Coupon: " << coupon_ << "%, Years: " << yearsToMaturity_
                  << ", Value: $" << calculateValue() << std::endl;
    }
    
    /// \brief Calculate bond risk as 5% of value.
    /// \return Risk value.
    double calculateRisk() const override {
        return calculateValue() * 0.05; // 5% risk for bonds
    }

private:
    double coupon_;
    int yearsToMaturity_;
};

// Derived class: Option

/// \brief Represents an options contract (call or put).
///
/// Option value is calculated using simplified intrinsic value calculation (not Black-Scholes).
/// Risk is calculated as 25% of the option value.
///
/// \code
/// Option callOpt("AAPL", 150.0, Option::Type::CALL, 140.0, 10);
/// double value = callOpt.calculateValue();  // (150 - 140) * 10 * 100 = 10,000
/// double risk = callOpt.calculateRisk();    // 10,000 * 0.25 = 2,500
/// \endcode
class Option : public FinancialInstrument {
public:
    /// \brief Enumeration for option contract type.
    enum class Type { 
        CALL,  ///< Call option (right to buy).
        PUT    ///< Put option (right to sell).
    };
    
    /// \brief Construct an option contract.
    /// \param symbol The underlying asset symbol (e.g., "AAPL").
    /// \param price The current price of the underlying asset.
    /// \param optionType Type of option (Type::CALL or Type::PUT).
    /// \param strike The strike price of the option.
    /// \param contracts Number of option contracts (each contract = 100 shares).
    Option(const std::string& symbol, double price, Type optionType, double strike, int contracts)
        : FinancialInstrument(symbol, price), optionType_(optionType), strike_(strike), contracts_(contracts) {}
    
    /// \brief Calculate option value using simplified intrinsic value formula.
    /// For call options: max(0, price - strike) * contracts * 100.
    /// For put options: max(0, strike - price) * contracts * 100.
    /// \return The calculated intrinsic value (0 if out-of-the-money).
    double calculateValue() const override {
        // Simplified option valuation (not using Black-Scholes for brevity)
        double intrinsicValue = 0.0;
        if (optionType_ == Type::CALL && price_ > strike_) {
            intrinsicValue = (price_ - strike_) * contracts_ * 100;
        } else if (optionType_ == Type::PUT && strike_ > price_) {
            intrinsicValue = (strike_ - price_) * contracts_ * 100;
        }
        return intrinsicValue;
    }
    
    /// \brief Return the instrument type.
    /// \return "Call Option" or "Put Option".
    std::string getType() const override {
        return optionType_ == Type::CALL ? "Call Option" : "Put Option";
    }
    
    /// \brief Print option details to stdout including strike and contract count.
    void printDetails() const override {
        std::cout << getType() << ": " << symbol_ << ", Price: $" << price_
                  << ", Strike: $" << strike_ << ", Contracts: " << contracts_
                  << ", Value: $" << calculateValue() << std::endl;
    }
    
    /// \brief Calculate option risk as 25% of value.
    /// \return Risk value.
    double calculateRisk() const override {
        return calculateValue() * 0.25; // 25% risk for options
    }

private:
    Type optionType_;
    double strike_;
    int contracts_;
};
