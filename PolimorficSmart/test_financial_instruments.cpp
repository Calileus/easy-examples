#include "financial_instrument.h"
#include "portfolio_market.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <stdexcept>

// Test basic polymorphism
class FinancialInstrumentTest : public ::testing::Test {
protected:
    void SetUp() override {
        stock = std::make_unique<Stock>("AAPL", 150.0, 100);
        bond = std::make_unique<Bond>("US10Y", 1000.0, 3.5, 10);
        call_option = std::make_unique<Option>("TSLA", 25.0, Option::Type::CALL, 200.0, 10);
        put_option = std::make_unique<Option>("TSLA", 25.0, Option::Type::PUT, 100.0, 10);
    }
    
    std::unique_ptr<Stock> stock;
    std::unique_ptr<Bond> bond;
    std::unique_ptr<Option> call_option;
    std::unique_ptr<Option> put_option;
};

// Test Stock class
TEST_F(FinancialInstrumentTest, StockCalculations) {
    EXPECT_EQ(stock->getSymbol(), "AAPL");
    EXPECT_EQ(stock->getPrice(), 150.0);
    EXPECT_EQ(stock->getType(), "Stock");
    EXPECT_DOUBLE_EQ(stock->calculateValue(), 15000.0); // 150 * 100
    EXPECT_DOUBLE_EQ(stock->calculateRisk(), 2250.0); // 15000 * 0.15
    EXPECT_EQ(stock->getShares(), 100);
}

// Test Bond class
TEST_F(FinancialInstrumentTest, BondCalculations) {
    EXPECT_EQ(bond->getSymbol(), "US10Y");
    EXPECT_EQ(bond->getPrice(), 1000.0);
    EXPECT_EQ(bond->getType(), "Bond");
    EXPECT_DOUBLE_EQ(bond->calculateValue(), 1035.0); // 1000 + (3.5 * 10)
    EXPECT_DOUBLE_EQ(bond->calculateRisk(), 51.75); // 1035 * 0.05
}

// Test Option classes
TEST_F(FinancialInstrumentTest, OptionCalculations) {
    // Call option (in-the-money: 25 > 200 is false, so no intrinsic value)
    EXPECT_EQ(call_option->getType(), "Call Option");
    EXPECT_DOUBLE_EQ(call_option->calculateValue(), 0.0); // Price < Strike
    
    // Update price to be in-the-money
    call_option->setPrice(250.0);
    EXPECT_DOUBLE_EQ(call_option->calculateValue(), 50000.0); // (250-200) * 10 * 100
    
    // Put option (in-the-money: 25 > 100 is false, so intrinsic value)
    EXPECT_EQ(put_option->getType(), "Put Option");
    EXPECT_DOUBLE_EQ(put_option->calculateValue(), 75000.0); // (100-25) * 10 * 100
    
    // Out-of-the-money put
    put_option->setPrice(150.0);
    EXPECT_DOUBLE_EQ(put_option->calculateValue(), 0.0); // Strike <= Price
}

// Test polymorphic behavior
TEST_F(FinancialInstrumentTest, PolymorphicBehavior) {
    std::vector<std::unique_ptr<FinancialInstrument>> instruments;
    instruments.push_back(std::move(stock));
    instruments.push_back(std::move(bond));
    instruments.push_back(std::move(call_option));
    instruments.push_back(std::move(put_option));
    
    std::vector<std::string> expected_types = {"Stock", "Bond", "Call Option", "Put Option"};
    
    for (size_t i = 0; i < instruments.size(); ++i) {
        EXPECT_EQ(instruments[i]->getType(), expected_types[i]);
        EXPECT_GT(instruments[i]->calculateValue(), 0.0);
        EXPECT_GT(instruments[i]->calculateRisk(), 0.0);
    }
}

// Test price updates
TEST_F(FinancialInstrumentTest, PriceUpdates) {
    double original_value = stock->calculateValue();
    stock->setPrice(200.0);
    EXPECT_DOUBLE_EQ(stock->getPrice(), 200.0);
    EXPECT_DOUBLE_EQ(stock->calculateValue(), 20000.0); // 200 * 100
    EXPECT_DOUBLE_EQ(stock->calculateValue(), original_value * (200.0 / 150.0));
}

// Test unique_ptr usage
TEST(SmartPointerTest, UniquePtrUsage) {
    auto instrument = std::make_unique<Stock>("MSFT", 300.0, 50);
    
    EXPECT_NE(instrument.get(), nullptr);
    EXPECT_EQ(instrument->getSymbol(), "MSFT");
    
    // Test move semantics
    std::unique_ptr<FinancialInstrument> moved = std::move(instrument);
    EXPECT_EQ(instrument.get(), nullptr);
    EXPECT_NE(moved.get(), nullptr);
    EXPECT_EQ(moved->getSymbol(), "MSFT");
}

// Test shared_ptr usage
TEST(SmartPointerTest, SharedPtrUsage) {
    auto stock = std::make_shared<Stock>("GOOGL", 2500.0, 10);
    
    EXPECT_EQ(stock.use_count(), 1);
    
    std::shared_ptr<FinancialInstrument> copy = stock;
    EXPECT_EQ(stock.use_count(), 2);
    EXPECT_EQ(copy.use_count(), 2);
    
    std::vector<std::shared_ptr<FinancialInstrument>> instruments;
    instruments.push_back(stock);
    instruments.push_back(copy);
    
    EXPECT_EQ(stock.use_count(), 4);
    
    instruments.clear();
    EXPECT_EQ(stock.use_count(), 2);
    
    copy.reset();
    EXPECT_EQ(stock.use_count(), 1);
}

// Test weak_ptr usage
TEST(SmartPointerTest, WeakPtrUsage) {
    auto stock = std::make_shared<Stock>("AAPL", 150.0, 100);
    std::weak_ptr<FinancialInstrument> weak_stock = stock;
    
    EXPECT_FALSE(weak_stock.expired());
    EXPECT_EQ(stock.use_count(), 1);
    
    // Lock weak_ptr
    if (auto locked = weak_stock.lock()) {
        EXPECT_EQ(locked->getSymbol(), "AAPL");
        EXPECT_EQ(stock.use_count(), 2);
    }
    
    // Reset shared_ptr
    stock.reset();
    EXPECT_TRUE(weak_stock.expired());
    
    // Weak pointer should be expired
    auto locked = weak_stock.lock();
    EXPECT_EQ(locked.get(), nullptr);
}

// Test factory function
TEST(FactoryTest, CreateInstruments) {
    auto stock = createInstrument("stock", "TSLA", 800.0);
    auto bond = createInstrument("bond", "CORP", 950.0);
    auto call = createInstrument("call", "NVDA", 50.0);
    auto put = createInstrument("put", "AMD", 30.0);
    auto invalid = createInstrument("invalid", "XYZ", 100.0);
    
    EXPECT_NE(stock.get(), nullptr);
    EXPECT_EQ(stock->getType(), "Stock");
    EXPECT_EQ(stock->getSymbol(), "TSLA");
    
    EXPECT_NE(bond.get(), nullptr);
    EXPECT_EQ(bond->getType(), "Bond");
    EXPECT_EQ(bond->getSymbol(), "CORP");
    
    EXPECT_NE(call.get(), nullptr);
    EXPECT_EQ(call->getType(), "Call Option");
    EXPECT_EQ(call->getSymbol(), "NVDA");
    
    EXPECT_NE(put.get(), nullptr);
    EXPECT_EQ(put->getType(), "Put Option");
    EXPECT_EQ(put->getSymbol(), "AMD");
    
    EXPECT_EQ(invalid.get(), nullptr);
}

// Test Portfolio class
class PortfolioTest : public ::testing::Test {
protected:
    void SetUp() override {
        portfolio = std::make_unique<Portfolio>("Test Portfolio");
        apple_stock = std::make_shared<Stock>("AAPL", 150.0, 100);
        us_bond = std::make_shared<Bond>("US10Y", 1000.0, 3.5, 10);
    }
    
    std::unique_ptr<Portfolio> portfolio;
    std::shared_ptr<Stock> apple_stock;
    std::shared_ptr<Bond> us_bond;
};

TEST_F(PortfolioTest, EmptyPortfolio) {
    EXPECT_DOUBLE_EQ(portfolio->calculateTotalValue(), 0.0);
    EXPECT_DOUBLE_EQ(portfolio->calculateTotalRisk(), 0.0);
}

TEST_F(PortfolioTest, AddInstruments) {
    portfolio->addInstrument(apple_stock);
    portfolio->addInstrument(us_bond);
    
    EXPECT_DOUBLE_EQ(portfolio->calculateTotalValue(), 15000.0 + 1035.0);
    EXPECT_DOUBLE_EQ(portfolio->calculateTotalRisk(), 2250.0 + 51.75);
}

TEST_F(PortfolioTest, SharedOwnership) {
    portfolio->addInstrument(apple_stock);
    EXPECT_EQ(apple_stock.use_count(), 2); // portfolio + this test
    
    auto portfolio2 = std::make_shared<Portfolio>("Portfolio 2");
    portfolio2->addInstrument(apple_stock);
    EXPECT_EQ(apple_stock.use_count(), 3); // portfolio + portfolio2 + this test
    
    portfolio.reset();
    EXPECT_EQ(apple_stock.use_count(), 2); // portfolio2 + this test
}

// Test edge cases
TEST(EdgeCasesTest, ZeroValues) {
    auto stock = std::make_unique<Stock>("ZERO", 0.0, 0);
    auto bond = std::make_unique<Bond>("ZERO", 0.0, 0.0, 0);
    
    EXPECT_DOUBLE_EQ(stock->calculateValue(), 0.0);
    EXPECT_DOUBLE_EQ(stock->calculateRisk(), 0.0);
    
    EXPECT_DOUBLE_EQ(bond->calculateValue(), 0.0);
    EXPECT_DOUBLE_EQ(bond->calculateRisk(), 0.0);
}

TEST(EdgeCasesTest, NegativePrices) {
    auto stock = std::make_unique<Stock>("NEG", -100.0, 10);
    
    EXPECT_DOUBLE_EQ(stock->calculateValue(), -1000.0);
    EXPECT_DOUBLE_EQ(stock->calculateRisk(), -150.0);
}

TEST(EdgeCasesTest, LargeNumbers) {
    auto stock = std::make_unique<Stock>("LARGE", 1e6, 1e6);
    
    EXPECT_DOUBLE_EQ(stock->calculateValue(), 1e12);
    EXPECT_DOUBLE_EQ(stock->calculateRisk(), 1.5e11);
}

// Test virtual destructor behavior
TEST(VirtualDestructorTest, ProperCleanup) {
    bool destroyed = false;
    
    class TestInstrument : public FinancialInstrument {
    public:
        TestInstrument(bool* destroyed_flag) : FinancialInstrument("TEST", 100.0), destroyed_(destroyed_flag) {}
        
        double calculateValue() const override { return 100.0; }
        std::string getType() const override { return "Test"; }
        void printDetails() const override {}
        
        ~TestInstrument() {
            *destroyed_ = true;
        }
        
    private:
        bool* destroyed_;
    };
    
    {
        std::unique_ptr<FinancialInstrument> instrument = std::make_unique<TestInstrument>(&destroyed);
        EXPECT_FALSE(destroyed);
    }
    
    EXPECT_TRUE(destroyed);
}

// Test polymorphic container operations
TEST(PolymorphicContainerTest, MixedContainerOperations) {
    std::vector<std::unique_ptr<FinancialInstrument>> instruments;
    
    instruments.push_back(std::make_unique<Stock>("AAPL", 150.0, 100));
    instruments.push_back(std::make_unique<Bond>("US10Y", 1000.0, 3.5, 10));
    instruments.push_back(std::make_unique<Option>("TSLA", 250.0, Option::Type::CALL, 200.0, 10));
    
    double total_value = 0.0;
    double total_risk = 0.0;
    
    for (const auto& instrument : instruments) {
        total_value += instrument->calculateValue();
        total_risk += instrument->calculateRisk();
    }
    
    EXPECT_GT(total_value, 0.0);
    EXPECT_GT(total_risk, 0.0);
    
    // Test type identification
    int stock_count = 0, bond_count = 0, option_count = 0;
    
    for (const auto& instrument : instruments) {
        if (instrument->getType() == "Stock") stock_count++;
        else if (instrument->getType() == "Bond") bond_count++;
        else if (instrument->getType().find("Option") != std::string::npos) option_count++;
    }
    
    EXPECT_EQ(stock_count, 1);
    EXPECT_EQ(bond_count, 1);
    EXPECT_EQ(option_count, 1);
}
