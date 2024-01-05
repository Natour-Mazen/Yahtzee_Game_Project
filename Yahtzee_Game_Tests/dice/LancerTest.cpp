#include "gtest/gtest.h"

#include "dice/Lancer.h"

/** Test fixture for Lancer. **/
class LancerTest : public ::testing::Test {
protected:
    Lancer m_dice;
};

/** Test case for Lancer::rollDices. **/
TEST_F(LancerTest, rollDices) {

    for (unsigned short i = 0; i < 10; ++i) {
        m_dice.rollDices();
        unsigned short nbDices = 0;
        bool isNumberOk = true;
        const std::vector<int>& dices = m_dice.getDiceValues();

        for (int dice : dices)
        {
            ++nbDices;
            if (dice < 1 || 6 < dice)
            {
                isNumberOk = false;
            }
        }

        EXPECT_EQ(5, nbDices);
        EXPECT_EQ(true, isNumberOk);
    }
}