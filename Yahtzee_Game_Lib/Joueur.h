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

class Joueur {
private:
    std::vector<Figure*> figures;
    bool yamBonus;
    std::vector<Figure*> figuresUsed;
public:
    int totalScore;

    Joueur();

    ~Joueur();

    void resetFigures();

    bool isFigureUsed(Figure* figure) const;

    void createFigures(const std::vector<int>& diceValues);

    void displayFigureScores(const std::vector<int>& diceValues) const;

    void chooseFigure(const std::vector<int>& diceValues);

    void calculateTotalScore(const std::vector<int>& diceValues);
};
