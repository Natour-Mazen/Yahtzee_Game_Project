#include "gtest/gtest.h"

#include "Full.h"

/** Test fixture for Full. **/
class FullTest : public ::testing::Test {
protected:
    Full<1> m_full;
};

/** Test case for Full::calculateScore. **/
TEST_F(FullTest, CalculateScore) {

    // Test when there is a Full of 3 and 2.
    std::vector<int> diceValues1 = { 2, 2, 3, 3, 3 };
    m_full.calculateScore(diceValues1);
    EXPECT_EQ(25, m_full.getScore());

    // Test when there is a Full of 6 and 2.
    std::vector<int> diceValues2 = { 6, 2, 6, 6, 2 };
    m_full.calculateScore(diceValues2);
    EXPECT_EQ(25, m_full.getScore());

    // Test when there is a Full of 4 and 2.
    std::vector<int> diceValues3 = { 4, 4, 4, 2, 2 };
    m_full.calculateScore(diceValues3);
    EXPECT_EQ(25, m_full.getScore());

    // Test when there is no Full.
    std::vector<int> diceValues4 = { 2, 2, 3, 3, 5 };
    m_full.calculateScore(diceValues4);
    EXPECT_EQ(0, m_full.getScore());
}

/** Test case for Full::getName. **/
TEST_F(FullTest, GetName) {

    // Test the name after calculating the score.
    std::vector<int> diceValues = { 3, 2, 2, 3, 3 };
    m_full.calculateScore(diceValues);
    EXPECT_EQ("Full de 2 et 3", m_full.getName());
}

/** Test case for Full::getId. **/
TEST_F(FullTest, GetId) {
    EXPECT_EQ(1, m_full.getId());
}