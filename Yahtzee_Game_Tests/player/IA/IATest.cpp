#include "gtest/gtest.h"

#include "player/IA/IA.h"

/** Sub class of IA to have access to the protected members **/
class IATestable : public IA {
public:
    using IA::m_firstYahtzee;
    using IA::m_yahtzeeBonus;
    using IA::m_minorScore;
    using IA::m_totalScore;
};

/** Test fixture for IA. **/
class IATest : public ::testing::Test {
protected:
    IATestable m_ia;
};

/** Test case for IA::chooseFigure when there is a yahtzee. **/
TEST_F(IATest, chooseFigure_yahtzee) {

    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    std::vector<int> dices = { 5, 5, 5, 5, 5};
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    // For the first Yahtzee
    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(50, m_ia.m_totalScore);
    EXPECT_EQ(true, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);

    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    m_ia.calculateFiguresScore(dices);
    m_ia.handleYahtzeeBonus();
    m_ia.chooseFigure();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    // For the bonus one Yahtzee
    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(175, m_ia.m_totalScore);
    EXPECT_EQ(true, m_ia.m_firstYahtzee);
    EXPECT_EQ(true, m_ia.m_yahtzeeBonus);
}

/** Test case for IA::chooseFigure when there is a grandeSuite. **/
TEST_F(IATest, chooseFigure_grandeSuite) {

    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    std::vector<int> dices = { 1, 2, 3, 4, 5 };
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(40, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);
}

/** Test case for IA::chooseFigure when there is a petiteSuite. **/
TEST_F(IATest, chooseFigure_petiteSuite) {

    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    std::vector<int> dices = { 1, 2, 3, 4, 6 };
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(30, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);
}

/** Test case for IA::chooseFigure when there is a full. **/
TEST_F(IATest, chooseFigure_full) {

    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    std::vector<int> dices = { 1, 1, 1, 2, 2 };
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(25, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);
}

/** Test case for IA::chooseFigure when there is a carre. **/
TEST_F(IATest, chooseFigure_carre) {

    /// To remove the chance.
    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    std::vector<int> dices = { 1, 1, 1, 1, 2 };
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(6, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);

    /// For the carre.
    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(10, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);
}

/** Test case for IA::chooseFigure when there is a brelan. **/
TEST_F(IATest, chooseFigure_brelan) {

    /// To remove the chance.
    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    std::vector<int> dices = { 1, 1, 1, 3, 2 };
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(8, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);

    /// For the brelan.
    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(11, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);
}

/** Test case for IA::chooseFigure when there is a chance. **/
TEST_F(IATest, chooseFigure_chance) {

    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    std::vector<int> dices = { 1, 2, 5, 5, 6 };
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(19, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);
}

/** Test case for IA::chooseFigure. **/
TEST_F(IATest, chooseFigure_six) {

    /// To remove the chance.
    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    std::vector<int> dices = { 1, 1, 2, 6, 6 };
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(0, m_ia.m_minorScore);
    EXPECT_EQ(16, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);

    /// For the six.
    // "Disable" the std::cout.
    std::cout.setstate(std::ios_base::failbit);
    m_ia.createAllFigures();
    m_ia.calculateFiguresScore(dices);
    m_ia.chooseFigure();
    m_ia.handleYahtzeeBonus();
    m_ia.resetFigures();
    // "Enable" the std::cout.
    std::cout.clear();

    EXPECT_EQ(12, m_ia.m_minorScore);
    EXPECT_EQ(28, m_ia.m_totalScore);
    EXPECT_EQ(false, m_ia.m_firstYahtzee);
    EXPECT_EQ(false, m_ia.m_yahtzeeBonus);
}