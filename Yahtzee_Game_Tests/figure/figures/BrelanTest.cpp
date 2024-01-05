#include "gtest/gtest.h"

#include "Brelan.h"

/** Test fixture for Brelan. **/ 
class BrelanTest : public ::testing::Test {
protected:
    Brelan<1> m_brelan;
};

/** Test case for Brelan::calculateScore. **/
TEST_F(BrelanTest, CalculateScore) {

    // Test when there is a Brelan of 3.
    std::vector<int> diceValues1 = { 1, 2, 3, 3, 3 };
    m_brelan.calculateScore(diceValues1);
    EXPECT_EQ(9, m_brelan.getScore());

    // Test when there is a Brelan of 6.
    std::vector<int> diceValues2 = { 6, 2, 6, 3, 6 };
    m_brelan.calculateScore(diceValues2);
    EXPECT_EQ(18, m_brelan.getScore());

    // Test when there is a Brelan of 4.
    std::vector<int> diceValues3 = { 4, 4, 4, 4, 4 };
    m_brelan.calculateScore(diceValues3);
    EXPECT_EQ(12, m_brelan.getScore());

    // Test when there is no Brelan.
    std::vector<int> diceValues4 = { 1, 2, 3, 4, 5 };
    m_brelan.calculateScore(diceValues4);
    EXPECT_EQ(0, m_brelan.getScore());
}

/** Test case for Brelan::getName. **/
TEST_F(BrelanTest, GetName) {

    // Test the name after calculating the score.
    std::vector<int> diceValues = { 1, 2, 3, 3, 3 };
    m_brelan.calculateScore(diceValues);
    EXPECT_EQ("Brelan de 3", m_brelan.getName());
}

/** Test case for Brelan::getId. **/
TEST_F(BrelanTest, GetId) {
    EXPECT_EQ(1, m_brelan.getId());
}