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
private:
    std::vector<Figure*> figures;
    bool firstYam = false;
    bool yamBonus = false;
    std::vector<Figure*> figuresUsed;
    int minorScore;
    int totalScore;

    bool isFigureUsed(Figure* figure) const;
    Figure* createNumberFigure(int id);
    void handleYahtzeeBonus(Figure* newFigure);
    void updateScores(int scoreForFigure, Figure* selectedFigure, const std::vector<int>& diceValues);
    
public:
   

    Joueur();

    ~Joueur();

    void createNumberFigures();
    void createOtherFigures();

    void resetFigures();
    void createFigures();
    void displayFigureAndScores(const std::vector<int>& diceValues) const;
    void chooseFigure(const std::vector<int>& diceValues);
    int getTotalScore() const;
};
