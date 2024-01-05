#include "gtest/gtest.h"

#include "Carre.h"

/** Test fixture for Carre. **/
class CarreTest : public ::testing::Test {
protected:
    Carre<1> m_carre;
};

/** Test case for Carre::calculateScore. **/
TEST_F(CarreTest, CalculateScore) {

    // Test when there is a Carre of 3.
    std::vector<int> diceValues1 = { 1, 3, 3, 3, 3 };
    m_carre.calculateScore(diceValues1);
    EXPECT_EQ(12, m_carre.getScore());

    // Test when there is a Carre of 6.
    std::vector<int> diceValues2 = { 6, 2, 6, 6, 6 };
    m_carre.calculateScore(diceValues2);
    EXPECT_EQ(24, m_carre.getScore());

    // Test when there is a Carre of 4.
    std::vector<int> diceValues3 = { 4, 4, 4, 4, 4 };
    m_carre.calculateScore(diceValues3);
    EXPECT_EQ(16, m_carre.getScore());

    // Test when there is no Carre.
    std::vector<int> diceValues4 = { 1, 2, 3, 4, 5 };
    m_carre.calculateScore(diceValues4);
    EXPECT_EQ(0, m_carre.getScore());
}

/** Test case for Carre::getName. **/
TEST_F(CarreTest, GetName) {

    // Test the name after calculating the score.
    std::vector<int> diceValues = { 3, 2, 3, 3, 3 };
    m_carre.calculateScore(diceValues);
    EXPECT_EQ("Carre de 3", m_carre.getName());
}

/** Test case for Carre::getId. **/
TEST_F(CarreTest, GetId) {
    EXPECT_EQ(1, m_carre.getId());
}