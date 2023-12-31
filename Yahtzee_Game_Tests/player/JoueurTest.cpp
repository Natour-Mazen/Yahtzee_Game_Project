#include "gtest/gtest.h"

#include "player/Joueur.h"

/** Sub class of Joueur to have access to the protected members **/
class JoueurTestable : public Joueur {
public:
    using Joueur::m_figures;
    using Joueur::m_figuresUsed;

    using Joueur::m_firstYahtzee;
    using Joueur::m_yahtzeeBonus;
    using Joueur::m_minorScore;
    using Joueur::m_totalScore;
};

/** Test fixture for Joueur. **/
class JoueurTest : public ::testing::Test {
protected:
    JoueurTestable m_player;
};


TEST_F(JoueurTest, createMinorFigures) {

    m_player.createMinorFigures();

    for (unsigned short i = 6; i >= 1; --i)
    {
        std::shared_ptr<Figure> f = m_player.m_figures.back();
        EXPECT_EQ(i, f.get()->getId());
        m_player.m_figures.pop_back();
    }
}

TEST_F(JoueurTest, createMajorFigures) {

    m_player.createMajorFigures();

    for (unsigned short i = 14; i >= 7; --i)
    {
        if (i != 13)
        {
            std::shared_ptr<Figure> f = m_player.m_figures.back();
            EXPECT_EQ(i, f.get()->getId());
            m_player.m_figures.pop_back();
        }
    }
}

TEST_F(JoueurTest, createAllFigures) {

    m_player.createAllFigures();

    for (unsigned short i = 14; i >= 1; --i)
    {
        if (i != 13)
        {
            std::shared_ptr<Figure> f = m_player.m_figures.back();
            EXPECT_EQ(i, f.get()->getId());
            m_player.m_figures.pop_back();
        }
    }
}


TEST_F(JoueurTest, getTotalScore) {

    m_player.m_totalScore = 30;
    EXPECT_EQ(30, m_player.getTotalScore());

    m_player.m_totalScore = 0;
    EXPECT_EQ(0, m_player.getTotalScore());

}