#include "gtest/gtest.h"

#include "Number.h"

/** Test fixture for Number. **/
class NumberTest : public ::testing::Test {
protected:
    Number<1> m_number1{1};
    Number<10> m_number2{2};
    Number<15> m_number6{6};
};

/** Test case for Number::calculateScore with m_number = 1. **/
TEST_F(NumberTest, CalculateScore_for_1) {

    // Test when there is a Number of 1.
    std::vector<int> diceValues1 = { 1, 1, 3, 5, 3 };
    m_number1.calculateScore(diceValues1);
    EXPECT_EQ(2, m_number1.getScore());

    // Test when there is a Number of 1.
    std::vector<int> diceValues2 = { 1, 2, 1, 1, 1 };
    m_number1.calculateScore(diceValues2);
    EXPECT_EQ(4, m_number1.getScore());

    // Test when there is no Number of 1.
    std::vector<int> diceValues3 = { 2, 2, 3, 4, 5 };
    m_number1.calculateScore(diceValues3);
    EXPECT_EQ(0, m_number1.getScore());
}

/** Test case for Number::calculateScore with m_number = 2. **/
TEST_F(NumberTest, CalculateScore_for_2) {

    // Test when there is a Number of 2.
    std::vector<int> diceValues1 = { 1, 3, 3, 2, 6 };
    m_number2.calculateScore(diceValues1);
    EXPECT_EQ(2, m_number2.getScore());

    // Test when there is a Number of 2.
    std::vector<int> diceValues2 = { 1, 2, 1, 2, 1 };
    m_number2.calculateScore(diceValues2);
    EXPECT_EQ(4, m_number2.getScore());

    // Test when there is no Number of 2.
    std::vector<int> diceValues3 = { 6, 6, 3, 5, 1 };
    m_number2.calculateScore(diceValues3);
    EXPECT_EQ(0, m_number2.getScore());
}

/** Test case for Number::calculateScore with m_number = 6. **/
TEST_F(NumberTest, CalculateScore_for_6) {

    // Test when there is a Number of 6.
    std::vector<int> diceValues1 = { 6, 6, 6, 5, 4 };
    m_number6.calculateScore(diceValues1);
    EXPECT_EQ(18, m_number6.getScore());

    // Test when there is a Number of 6.
    std::vector<int> diceValues2 = { 6, 6, 6, 6, 6 };
    m_number6.calculateScore(diceValues2);
    EXPECT_EQ(30, m_number6.getScore());

    // Test when there is no Number of 6.
    std::vector<int> diceValues3 = { 1, 2, 3, 4, 5 };
    m_number6.calculateScore(diceValues3);
    EXPECT_EQ(0, m_number6.getScore());
}

/** Test case for Number::getName. **/
TEST_F(NumberTest, GetName) {

    EXPECT_EQ("Number 1", m_number1.getName());
    EXPECT_EQ("Number 2", m_number2.getName());
    EXPECT_EQ("Number 6", m_number6.getName());
}

/** Test case for Number::getId. **/
TEST_F(NumberTest, GetId) {
    EXPECT_EQ(1, m_number1.getId());
    EXPECT_EQ(10, m_number2.getId());
    EXPECT_EQ(15, m_number6.getId());
}