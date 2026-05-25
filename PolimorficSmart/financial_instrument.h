#pragma once

#include <string>
#include <memory>
#include <vector>
#include <iostream>

class FinancialInstrument {
public:
    FinancialInstrument(const std::string& symbol, double price) 
        : symbol_(symbol), price_(price) {}
    
    virtual ~FinancialInstrument() = default;
    
    // Virtual methods for polymorphism
    virtual double calculateValue() const = 0;
    virtual std::string getType() const = 0;
    virtual void printDetails() const = 0;
    
    // Common methods
    std::string getSymbol() const { return symbol_; }
    double getPrice() const { return price_; }
    void setPrice(double price) { price_ = price; }
    
    // Virtual method with default implementation
    virtual double calculateRisk() const {
        return price_ * 0.1; // Default 10% risk
    }

protected:
    std::string symbol_;
    double price_;
};

// Derived class: Stock
class Stock : public FinancialInstrument {
public:
    Stock(const std::string& symbol, double price, int shares)
        : FinancialInstrument(symbol, price), shares_(shares) {}
    
    double calculateValue() const override {
        return price_ * shares_;
    }
    
    std::string getType() const override {
        return "Stock";
    }
    
    void printDetails() const override {
        std::cout << "Stock: " << symbol_ << ", Price: $" << price_ 
                  << ", Shares: " << shares_ << ", Value: $" << calculateValue() << std::endl;
    }
    
    double calculateRisk() const override {
        return calculateValue() * 0.15; // 15% risk for stocks
    }
    
    int getShares() const { return shares_; }

private:
    int shares_;
};

// Derived class: Bond
class Bond : public FinancialInstrument {
public:
    Bond(const std::string& symbol, double price, double coupon, int years)
        : FinancialInstrument(symbol, price), coupon_(coupon), yearsToMaturity_(years) {}
    
    double calculateValue() const override {
        // Simplified bond valuation: price + accrued interest
        return price_ + (coupon_ * yearsToMaturity_);
    }
    
    std::string getType() const override {
        return "Bond";
    }
    
    void printDetails() const override {
        std::cout << "Bond: " << symbol_ << ", Price: $" << price_ 
                  << ", Coupon: " << coupon_ << "%, Years: " << yearsToMaturity_
                  << ", Value: $" << calculateValue() << std::endl;
    }
    
    double calculateRisk() const override {
        return calculateValue() * 0.05; // 5% risk for bonds
    }

private:
    double coupon_;
    int yearsToMaturity_;
};

// Derived class: Option
class Option : public FinancialInstrument {
public:
    enum class Type { CALL, PUT };
    
    Option(const std::string& symbol, double price, Type optionType, double strike, int contracts)
        : FinancialInstrument(symbol, price), optionType_(optionType), strike_(strike), contracts_(contracts) {}
    
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
    
    std::string getType() const override {
        return optionType_ == Type::CALL ? "Call Option" : "Put Option";
    }
    
    void printDetails() const override {
        std::cout << getType() << ": " << symbol_ << ", Price: $" << price_
                  << ", Strike: $" << strike_ << ", Contracts: " << contracts_
                  << ", Value: $" << calculateValue() << std::endl;
    }
    
    double calculateRisk() const override {
        return calculateValue() * 0.25; // 25% risk for options
    }

private:
    Type optionType_;
    double strike_;
    int contracts_;
};
