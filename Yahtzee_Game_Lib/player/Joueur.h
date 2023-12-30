#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Figure.h"
#include "Brelan.h"
#include "Carre.h"
#include "Full.h"
#include "Chance.h"
#include "GrandeSuite.h"
#include "PetiteSuite.h"
#include "Yahtzee.h"
#include "Number.h"

class Joueur {
public:
    Joueur();
    ~Joueur();

    void createMinorFigures();
    void createMajorFigures();
    void createAllFigures();
    void createHardcoreFigures();

    void resetFigures();
    bool getIsaleardyHardFigureCreated() const;
    void handleYahtzeeBonus(const std::vector<int>& diceValues);

   
    void chooseFigureFacileAndPlusModes(const std::vector<int>& diceValues);
    void chooseFigureDifficileAndPlusModes(const std::vector<int>& diceValues, const int& NombreMaxOfFigureTopick);
    int getTotalScore() const;
    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

private:
    static const short ID_YAHTZEE_FIRST = 12;
    static const short ID_YAHTZEE_BONUS = 13;

    std::vector<std::shared_ptr<Figure>> m_figures;
    bool m_firstYahtzee;
    bool m_yahtzeeBonus;
    std::vector<std::shared_ptr<Figure>> m_figuresUsed;
    int m_minorScore;
    int m_totalScore;
    bool aleardyHardFigureCreated;

    bool isFigureUsed(Figure* figure) const;
    std::shared_ptr<Figure> createMinorFigure(unsigned int id) const;
   // void handleYahtzeeBonus(std::shared_ptr<Figure> newFigure);
    void updateScores(int scoreForFigure, std::shared_ptr<Figure> selectedFigure);
    void displayFigureAndScores(const std::vector<int>& diceValues) const;
    void chooseFigureHelper(const std::vector<int>& diceValues, const int& maxFigures);
  
};
