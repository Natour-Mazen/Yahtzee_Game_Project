#include "gtest/gtest.h"

#include "Yahtzee.h"

/** Test fixture for Yahtzee. **/
class YahtzeeTest : public ::testing::Test {
protected:
    Yahtzee<1> m_yahtzee;
};

/** Test case for Yahtzee::calculateScore. **/
TEST_F(YahtzeeTest, CalculateScore) {

    // Test when there is a Yahtzee.
    std::vector<int> diceValues1 = { 1, 1, 1, 1, 1 };
    EXPECT_EQ(50, m_yahtzee.calculateScore(diceValues1));

    // Test when there is a Yahtzee.
    std::vector<int> diceValues2 = { 6, 6, 6, 6, 6 };
    EXPECT_EQ(50, m_yahtzee.calculateScore(diceValues2));

    // Test when there is no Yahtzee.
    std::vector<int> diceValues3 = {4, 4, 4, 4, 1 };
    EXPECT_EQ(0, m_yahtzee.calculateScore(diceValues3));
}

/** Test case for Yahtzee::getName. **/
TEST_F(YahtzeeTest, GetName) {

    EXPECT_EQ("Yahtzee", m_yahtzee.getName());
}

/** Test case for Yahtzee::getId. **/
TEST_F(YahtzeeTest, GetId) {
    EXPECT_EQ(1, m_yahtzee.getId());
}