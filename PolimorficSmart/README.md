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

- CMake 3.14+
- C++17-capable compiler (MSVC, GCC, or Clang)
- Optional: Google Test for `financial_tests`

### Recommended (Repository Root Workflow)

Run from repository root for the most consistent experience with CI/documentation:

```bash
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

This module contributes these CTest entries in root builds:

- `financial_simple_test`
- `financial_threaded_test`
- Optional: `financial_gtest_suite` (when GTest is found)

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure this module directly
cmake -S .. -B . -DBUILD_TESTING=ON

# Build the project
cmake --build .

# Run example and tests through custom targets (generator-safe)
cmake --build . --target run_example
cmake --build . --target run_simple_tests
cmake --build . --target run_threaded_example
cmake --build . --target run_threaded_tests

# Run registered CTest tests
ctest --output-on-failure
```

### Build Architecture Note

The CMake build now uses a reusable static library target (`financial_core`) for shared domain logic (`portfolio_market.cpp`).
All executables/tests (`financial_example`, `simple_test`, `threaded_example`, `threaded_tests`, and optional `financial_tests`) link against this target.
This reduces source duplication and keeps shared logic centralized for maintenance.

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

Generator note:

- Multi-config generators (for example Visual Studio) place artifacts under per-config folders.
- Single-config generators (for example Ninja/Makefiles) place artifacts in the build directory.
- Prefer custom targets and CTest commands above instead of hardcoding executable paths.

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
ctest --output-on-failure
```

If GTest is available, run only the optional GTest suite:

```bash
ctest -R financial_gtest_suite --output-on-failure
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
