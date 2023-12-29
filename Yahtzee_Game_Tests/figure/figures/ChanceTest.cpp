#include "gtest/gtest.h"

#include "Chance.h"

/** Test fixture for Chance. **/
class ChanceTest : public ::testing::Test {
protected:
    Chance<1> m_chance;
};

/** Test case for Chance::calculateScore. **/
TEST_F(ChanceTest, CalculateScore) {

    // Test when there is a Chance.
    std::vector<int> diceValues1 = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(15, m_chance.calculateScore(diceValues1));

    // Test when there is a Chance.
    std::vector<int> diceValues2 = { 6, 2, 6, 6, 6 };
    EXPECT_EQ(26, m_chance.calculateScore(diceValues2));
}

/** Test case for Chance::getName. **/
TEST_F(ChanceTest, GetName) {

    EXPECT_EQ("Chance", m_chance.getName());
}

/** Test case for Chance::getId. **/
TEST_F(ChanceTest, GetId) {
    EXPECT_EQ(1, m_chance.getId());
}