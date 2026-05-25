# C++ Polymorphism and Smart Pointers Example

A comprehensive C++ example demonstrating polymorphism and smart pointers designed for quantitative finance developer interviews.

## Overview

This project showcases modern C++ features through a financial instrument hierarchy that includes:
- **Polymorphism**: Virtual functions and inheritance
- **Smart Pointers**: `unique_ptr`, `shared_ptr`, and `weak_ptr`
- **Memory Management**: RAII and automatic resource cleanup
- **Financial Domain**: Stocks, Bonds, and Options with realistic calculations

## Key Concepts Demonstrated

### 1. Polymorphism
- Abstract base class `FinancialInstrument` with pure virtual methods
- Derived classes: `Stock`, `Bond`, `Option`
- Runtime polymorphism through virtual function calls
- Type-safe downcasting and dynamic dispatch

### 2. Smart Pointers
- **`unique_ptr`**: Exclusive ownership, move semantics
- **`shared_ptr`**: Shared ownership with reference counting
- **`weak_ptr`**: Non-owning references to avoid circular dependencies
- **Factory Pattern**: Functions returning `unique_ptr` for object creation

### 3. Financial Modeling
- **Stock**: Value = price × shares, Risk = 15% of value
- **Bond**: Value = price + (coupon × years), Risk = 5% of value
- **Option**: Intrinsic value calculation, Risk = 25% of value
- **Portfolio**: Collection of instruments with aggregated calculations

## Project Structure

```
PolimorficSmart/
├── financial_instrument.h    # Class definitions
├── main.cpp                  # Example usage and demonstrations
├── test_financial_instruments.cpp  # Comprehensive gtests
├── CMakeLists.txt            # Build configuration
└── README.md                 # This file
```

## Building the Project

### Prerequisites
- C++17 compatible compiler
- CMake 3.14 or higher
- Google Test (GTest) library (optional - for advanced tests)

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake (MinGW on Windows)
cmake .. -G "MinGW Makefiles"

# Build the project
cmake --build .

# Run the example
./financial_example

# Run simple tests (always available)
./simple_test

# Run GTest tests (if GTest is available)
./financial_tests
```

### Alternative Build Commands

```bash
# Run example directly
cmake --build . --target run_example

# Run simple tests directly
cmake --build . --target run_simple_tests

# Run GTest tests directly (if available)
cmake --build . --target run_tests

# Run tests with CTest (if GTest is available)
ctest
```

## Example Usage

The main program demonstrates:

1. **Polymorphism**: Different instrument types calling their own methods
2. **Shared Ownership**: Multiple portfolios sharing the same instruments
3. **Weak References**: Market observing portfolios without ownership
4. **Move Semantics**: Efficient transfer of ownership
5. **Factory Pattern**: Creating objects without exposing concrete types

Sample output:
```
=== Polymorphism Demonstration ===
Stock: AAPL, Price: $150, Shares: 100, Value: $15000
Risk: $2250
Bond: US10Y, Price: $1000, Coupon: 3.5%, Years: 10, Value: $1035
Risk: $51.75
Call Option: TSLA, Price: $25, Strike: $200, Contracts: 10, Value: $0
Risk: $0
```

## Testing

The test suite includes:

- **Unit Tests**: Individual class functionality
- **Polymorphism Tests**: Virtual function behavior
- **Smart Pointer Tests**: Ownership semantics and reference counting
- **Edge Cases**: Zero values, negative numbers, large numbers
- **Integration Tests**: Portfolio and market interactions

Run tests with:
```bash
./bin/financial_tests
```

## Interview Talking Points

### Memory Management
- RAII principles with smart pointers
- Avoiding memory leaks and dangling pointers
- Reference counting and circular reference prevention

### Design Patterns
- Factory pattern for object creation
- Observer pattern with weak_ptr
- Strategy pattern through polymorphism

### Performance Considerations
- Move semantics vs copying
- Reference counting overhead
- Cache-friendly data structures

### Financial Domain Knowledge
- Instrument valuation methods
- Risk calculations
- Portfolio management concepts

## Extending the Example

Potential enhancements for interview discussions:
1. **More Complex Valuation**: Black-Scholes for options
2. **Market Data**: Real-time price feeds
3. **Concurrency**: Thread-safe portfolio operations
4. **Serialization**: JSON/Binary persistence
5. **Analytics**: Greeks, VaR calculations

## Best Practices Demonstrated

- **Modern C++**: C++17 features, smart pointers over raw pointers
- **SOLID Principles**: Single responsibility, open/closed, Liskov substitution
- **Exception Safety**: Strong exception guarantee with RAII
- **Test-Driven Development**: Comprehensive test coverage
- **Build Systems**: CMake for cross-platform builds

This example serves as an excellent foundation for discussing advanced C++ concepts in a quantitative finance context during technical interviews.
