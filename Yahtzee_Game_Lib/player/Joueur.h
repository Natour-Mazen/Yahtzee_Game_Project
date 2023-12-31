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
    void handleYahtzeeBonus(const std::vector<int>& diceValues);

   
    void chooseFigureFacileAndPlusModes(const std::vector<int>& diceValues);
    void chooseFigureDifficileAndPlusModes(const std::vector<int>& diceValues, const int& NombreMaxOfFigureTopick);
    int getTotalScore() const;
    bool isFiguresEmpty() const;
    void serialize(std::ostream& out) const;
    void deserialize(std::istream& in);

protected:
    static const short ID_YAHTZEE_FIRST = 12;
    static const short ID_YAHTZEE_BONUS = 13;

    std::vector<std::shared_ptr<Figure>> m_figures;
    std::vector<std::shared_ptr<Figure>> m_figuresUsed;
   
    bool m_firstYahtzee;
    bool m_yahtzeeBonus;
    int m_minorScore;
    int m_totalScore;


    bool aleardyHardFigureCreated;
    std::vector<int> ordreCreationFiguresHardcore;

    bool isFigureUsed(Figure* figure) const;
    std::shared_ptr<Figure> createNumberFigure(unsigned int id) const;
    std::shared_ptr<Figure> createFigure(unsigned int id) const;
    void updateScores(int scoreForFigure, std::shared_ptr<Figure> selectedFigure);
    void displayFigureAndScores(const std::vector<int>& diceValues) const;
    void chooseFigureHelper(const std::vector<int>& diceValues, const int& maxFigures);
};
