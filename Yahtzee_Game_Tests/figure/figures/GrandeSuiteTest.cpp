#include "gtest/gtest.h"

#include "GrandeSuite.h"

/** Test fixture for GrandeSuite. **/
class GrandeSuiteTest : public ::testing::Test {
protected:
    GrandeSuite<1> m_grandeSuite;
};

/** Test case for GrandeSuite::calculateScore. **/
TEST_F(GrandeSuiteTest, CalculateScore) {

    // Test when there is a GrandeSuite.
    std::vector<int> diceValues1 = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(40, m_grandeSuite.calculateScore(diceValues1));

    // Test when there is a GrandeSuite.
    std::vector<int> diceValues2 = { 6, 5, 3, 4, 2 };
    EXPECT_EQ(40, m_grandeSuite.calculateScore(diceValues2));

    // Test when there is a GrandeSuite.
    std::vector<int> diceValues3 = { 4, 2, 3, 5, 1 };
    EXPECT_EQ(40, m_grandeSuite.calculateScore(diceValues3));

    // Test when there is no GrandeSuite.
    std::vector<int> diceValues4 = { 1, 2, 3, 4, 6 };
    EXPECT_EQ(0, m_grandeSuite.calculateScore(diceValues4));
}

/** Test case for GrandeSuite::getName. **/
TEST_F(GrandeSuiteTest, GetName) {

    EXPECT_EQ("Grande Suite", m_grandeSuite.getName());
}

/** Test case for GrandeSuite::getId. **/
TEST_F(GrandeSuiteTest, GetId) {
    EXPECT_EQ(1, m_grandeSuite.getId());
}