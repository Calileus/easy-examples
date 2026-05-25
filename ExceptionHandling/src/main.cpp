/// \file main.cpp
/// \brief Comprehensive exception handling demonstration with custom exceptions.
///
/// This example shows practical usage of:
/// - Custom exception classes inheriting from std::exception
/// - Try/catch blocks and exception propagation
/// - RAII (Resource Acquisition Is Initialization) with exceptions
/// - Exception safety guarantees
/// - Catching different exception types
/// - Stack unwinding and cleanup
/// - Exception specifications and noexcept
/// - Best practices for error handling
///
/// Use case: Bank account system with validation and transaction error handling.
///
/// \author Easy Examples
/// \version 1.0

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <sstream>

/// \brief Custom exception for insufficient funds.
class InsufficientFundsException : public std::exception {
private:
    std::string message_;
    
public:
    /// \brief Constructor with account balance and requested amount.
    /// \param balance Current account balance.
    /// \param requested Amount requested to withdraw.
    InsufficientFundsException(double balance, double requested)
        : message_("Insufficient funds: balance=$" + 
                   std::to_string(balance) + ", requested=$" + 
                   std::to_string(requested)) {}
    
    /// \brief Return exception message.
    /// \return Descriptive error message.
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

/// \brief Custom exception for invalid account operations.
class InvalidAccountException : public std::exception {
private:
    std::string message_;
    
public:
    /// \brief Constructor with error description.
    /// \param reason Reason for invalid operation.
    explicit InvalidAccountException(const std::string& reason)
        : message_("Invalid account: " + reason) {}
    
    /// \brief Return exception message.
    /// \return Descriptive error message.
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

/// \brief Custom exception for transaction errors.
class TransactionException : public std::exception {
private:
    std::string message_;
    
public:
    /// \brief Constructor with transaction error description.
    /// \param description Error description.
    explicit TransactionException(const std::string& description)
        : message_("Transaction failed: " + description) {}
    
    /// \brief Return exception message.
    /// \return Descriptive error message.
    const char* what() const noexcept override {
        return message_.c_str();
    }
};

/// \brief Bank account demonstrating exception handling.
class BankAccount {
private:
    std::string accountNumber_;
    double balance_;
    std::vector<std::string> transactionLog_;
    
public:
    /// \brief Construct a bank account with validation.
    /// \param accountNumber Account number string.
    /// \param initialBalance Initial deposit amount.
    /// \throws InvalidAccountException if account number is invalid or balance is negative.
    BankAccount(const std::string& accountNumber, double initialBalance) {
        if (accountNumber.empty()) {
            throw InvalidAccountException("account number cannot be empty");
        }
        if (initialBalance < 0) {
            throw InvalidAccountException("initial balance cannot be negative");
        }
        
        accountNumber_ = accountNumber;
        balance_ = initialBalance;
        
        // Log initial deposit
        std::stringstream ss;
        ss << "Account created with $" << std::fixed << std::setprecision(2) 
           << initialBalance;
        transactionLog_.push_back(ss.str());
    }
    
    /// \brief Get current account balance.
    /// \return Current balance.
    double getBalance() const noexcept {
        return balance_;
    }
    
    /// \brief Withdraw money from account.
    /// \param amount Amount to withdraw.
    /// \throws InsufficientFundsException if amount exceeds balance.
    /// \throws TransactionException if amount is invalid.
    void withdraw(double amount) {
        if (amount <= 0) {
            throw TransactionException("withdrawal amount must be positive");
        }
        if (amount > balance_) {
            throw InsufficientFundsException(balance_, amount);
        }
        
        balance_ -= amount;
        
        std::stringstream ss;
        ss << "Withdrew $" << std::fixed << std::setprecision(2) << amount
           << " (balance: $" << balance_ << ")";
        transactionLog_.push_back(ss.str());
    }
    
    /// \brief Deposit money to account.
    /// \param amount Amount to deposit.
    /// \throws TransactionException if amount is invalid.
    void deposit(double amount) {
        if (amount <= 0) {
            throw TransactionException("deposit amount must be positive");
        }
        
        balance_ += amount;
        
        std::stringstream ss;
        ss << "Deposited $" << std::fixed << std::setprecision(2) << amount
           << " (balance: $" << balance_ << ")";
        transactionLog_.push_back(ss.str());
    }
    
    /// \brief Transfer money to another account (demonstrates exception propagation).
    /// \param toAccount Destination account.
    /// \param amount Amount to transfer.
    /// \throws InsufficientFundsException if source has insufficient funds.
    /// \throws TransactionException if transfer is invalid.
    void transferTo(BankAccount& toAccount, double amount) {
        if (amount <= 0) {
            throw TransactionException("transfer amount must be positive");
        }
        
        // Withdraw from this account (may throw)
        this->withdraw(amount);
        
        try {
            // Deposit to target account (may throw)
            toAccount.deposit(amount);
            
            // Log transfer
            std::stringstream ss;
            ss << "Transferred $" << std::fixed << std::setprecision(2) << amount
               << " to account " << toAccount.accountNumber_;
            transactionLog_.push_back(ss.str());
            
        } catch (const std::exception& e) {
            // Rollback withdrawal if deposit fails
            balance_ += amount;
            std::stringstream ss;
            ss << "Transfer rolled back due to: " << e.what();
            transactionLog_.push_back(ss.str());
            throw TransactionException("transfer failed and was rolled back");
        }
    }
    
    /// \brief Print transaction history.
    void printTransactionLog() const noexcept {
        std::cout << "\n=== Account " << accountNumber_ << " Transactions ===" << std::endl;
        for (const auto& transaction : transactionLog_) {
            std::cout << "  " << transaction << std::endl;
        }
    }
};

/// \brief Demonstrate basic exception handling.
void demonstrateBasicExceptions() {
    std::cout << "\n=== Basic Exception Handling ===" << std::endl;
    
    try {
        BankAccount account("ACC001", 1000.0);
        std::cout << "Account created with balance: $" << account.getBalance() << std::endl;
        
        account.withdraw(200.0);
        std::cout << "Withdrew $200, new balance: $" << account.getBalance() << std::endl;
        
        account.deposit(500.0);
        std::cout << "Deposited $500, new balance: $" << account.getBalance() << std::endl;
        
        // This will throw InsufficientFundsException
        account.withdraw(2000.0);
        
    } catch (const InsufficientFundsException& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}

/// \brief Demonstrate exception propagation through function calls.
void demonstrateExceptionPropagation() {
    std::cout << "\n=== Exception Propagation ===" << std::endl;
    
    try {
        BankAccount account1("ACC001", 500.0);
        BankAccount account2("ACC002", 0.0);
        
        std::cout << "Account1 balance: $" << account1.getBalance() << std::endl;
        std::cout << "Account2 balance: $" << account2.getBalance() << std::endl;
        
        // Try to transfer more than available (will throw)
        account1.transferTo(account2, 600.0);
        
    } catch (const InsufficientFundsException& e) {
        std::cout << "Transfer failed - insufficient funds: " << e.what() << std::endl;
    } catch (const TransactionException& e) {
        std::cout << "Transfer failed - transaction error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Transfer failed - unexpected error: " << e.what() << std::endl;
    }
}

/// \brief Demonstrate multiple exception types and catch order.
void demonstrateMultipleCatchBlocks() {
    std::cout << "\n=== Multiple Exception Types ===" << std::endl;
    
    std::vector<double> operations = {200.0, -50.0, 1500.0, 100.0};
    
    try {
        BankAccount account("ACC001", 1000.0);
        
        for (double operation : operations) {
            try {
                if (operation > 0) {
                    account.withdraw(operation);
                    std::cout << "Withdrew $" << operation << ", balance: $"
                              << account.getBalance() << std::endl;
                } else {
                    throw TransactionException("invalid operation amount");
                }
            } catch (const InsufficientFundsException& e) {
                std::cout << "  ⚠ Caught insufficient funds: " << e.what() << std::endl;
                // Continue with next operation
            } catch (const TransactionException& e) {
                std::cout << "  ⚠ Caught transaction error: " << e.what() << std::endl;
                // Continue with next operation
            }
        }
        
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
}

/// \brief Demonstrate exception safety with RAII.
void demonstrateRAIIWithExceptions() {
    std::cout << "\n=== RAII with Exception Safety ===" << std::endl;
    
    try {
        BankAccount account1("ACC001", 1000.0);
        BankAccount account2("ACC002", 500.0);
        
        std::cout << "Before transfer:" << std::endl;
        std::cout << "  Account1: $" << account1.getBalance() << std::endl;
        std::cout << "  Account2: $" << account2.getBalance() << std::endl;
        
        // Transfer with rollback on failure
        account1.transferTo(account2, 300.0);
        
        std::cout << "After successful transfer:" << std::endl;
        std::cout << "  Account1: $" << account1.getBalance() << std::endl;
        std::cout << "  Account2: $" << account2.getBalance() << std::endl;
        
        account1.printTransactionLog();
        
    } catch (const std::exception& e) {
        std::cout << "Transfer failed: " << e.what() << std::endl;
    }
}

/// \brief Demonstrate exception safety guarantees.
void demonstrateExceptionSafetyGuarantees() {
    std::cout << "\n=== Exception Safety Guarantees ===" << std::endl;
    
    try {
        // Test invalid account creation (strong guarantee)
        try {
            BankAccount invalid("", 1000.0);  // Empty account number
        } catch (const InvalidAccountException& e) {
            std::cout << "Prevented invalid account: " << e.what() << std::endl;
        }
        
        // Test negative balance (strong guarantee)
        try {
            BankAccount invalid2("ACC001", -500.0);  // Negative balance
        } catch (const InvalidAccountException& e) {
            std::cout << "Prevented invalid balance: " << e.what() << std::endl;
        }
        
        // Valid account created successfully
        BankAccount valid("ACC001", 1000.0);
        std::cout << "Valid account created successfully with $" 
                  << valid.getBalance() << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
}

/// \brief Main entry point demonstrating all exception handling patterns.
int main() {
    std::cout << "=== C++ Exception Handling Examples ===" << std::endl;
    std::cout << "Demonstrating custom exceptions, catch blocks, and error recovery\n";
    
    demonstrateBasicExceptions();
    demonstrateMultipleCatchBlocks();
    demonstrateExceptionPropagation();
    demonstrateRAIIWithExceptions();
    demonstrateExceptionSafetyGuarantees();
    
    std::cout << "\n=== Exception Handling Example Completed ===" << std::endl;
    
    return 0;
}
