#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Figure.h"
#include "brelan/Brelan.h"
#include "carre/Carre.h"
#include "full/Full.h"
#include "chance/Chance.h"
#include "grandeSuite/GrandeSuite.h"
#include "petiteSuite/PetiteSuite.h"
#include "yahtzee/Yahtzee.h"
#include "numbers/Number.h"

class Joueur {
public:
    Joueur();
    ~Joueur();

    void createMinorFigures();
    void createMajorFigures();
    void createAllFigures();

    void resetFigures();

    void displayFigureAndScores(const std::vector<int>& diceValues) const;
    void chooseFigure(const std::vector<int>& diceValues);
    int getTotalScore() const;
    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

private:
    static const short ID_YAHTZEE_FIRST = 12;
    static const short ID_YAHTZEE_BONUS = 13;

    std::vector<Figure*> m_figures;
    bool m_firstYahtzee;
    bool m_yahtzeeBonus;
    std::vector<Figure*> m_figuresUsed;
    int m_minorScore;
    int m_totalScore;

    bool isFigureUsed(Figure* figure) const;
    Figure* createMinorFigure(unsigned int id) const;
    void handleYahtzeeBonus(Figure* newFigure);
    void updateScores(int scoreForFigure, Figure* selectedFigure);
};
