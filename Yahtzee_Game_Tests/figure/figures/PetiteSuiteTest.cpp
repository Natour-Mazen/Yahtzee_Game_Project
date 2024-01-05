#include "gtest/gtest.h"

#include "PetiteSuite.h"

/** Test fixture for PetiteSuite. **/
class PetiteSuiteTest : public ::testing::Test {
protected:
    PetiteSuite<1> m_petiteSuite;
};

/** Test case for PetiteSuite::calculateScore. **/
TEST_F(PetiteSuiteTest, CalculateScore) {

    // Test when there is a PetiteSuite.
    std::vector<int> diceValues1 = { 1, 2, 3, 4, 6 };
    EXPECT_EQ(30, m_petiteSuite.calculateScore(diceValues1));

    // Test when there is a PetiteSuite.
    std::vector<int> diceValues2 = { 6, 5, 3, 4, 1 };
    EXPECT_EQ(30, m_petiteSuite.calculateScore(diceValues2));

    // Test when there is a PetiteSuite.
    std::vector<int> diceValues3 = { 4, 2, 3, 5, 1 };
    EXPECT_EQ(30, m_petiteSuite.calculateScore(diceValues3));

    // Test when there is no PetiteSuite.
    std::vector<int> diceValues4 = { 2, 2, 3, 4, 6 };
    EXPECT_EQ(0, m_petiteSuite.calculateScore(diceValues4));

    // Test when there is a PetiteSuite.
    std::vector<int> diceValues5 = { 1, 3, 2, 3, 4 };
    EXPECT_EQ(30, m_petiteSuite.calculateScore(diceValues5));

    // Test when there is no PetiteSuite.
    std::vector<int> diceValues6 = { 1, 3, 3, 3, 4 };
    EXPECT_EQ(0, m_petiteSuite.calculateScore(diceValues6));
}

/** Test case for PetiteSuite::getName. **/
TEST_F(PetiteSuiteTest, GetName) {

    EXPECT_EQ("Petite Suite", m_petiteSuite.getName());
}

/** Test case for PetiteSuite::getId. **/
TEST_F(PetiteSuiteTest, GetId) {
    EXPECT_EQ(1, m_petiteSuite.getId());
}