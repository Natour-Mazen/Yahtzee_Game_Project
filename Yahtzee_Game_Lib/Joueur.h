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
    std::vector<Figure*> figuresUtilisees;
public:
    int totalScore;

    void resetFigures() {
        figures.clear();
    }

    Joueur() : totalScore(0), yamBonus(false) {}

    ~Joueur() {
        for (Figure* figure : figures) {
            delete figure;
        }
    }


    bool isFigureUtilisee(Figure* figure) const {
        return std::find_if(figuresUtilisees.begin(), figuresUtilisees.end(),
            [figure](const Figure* usedFigure) {
                return figure->ID == usedFigure->ID;
            }) != figuresUtilisees.end();
    }

    void createFigures(const std::vector<int>& diceValues) {
        std::vector<Figure*> newFigures;

        for (unsigned short i = 0; i < 7; ++i) {
            Figure* newFigure = nullptr;
            switch (i) {
            case 0: newFigure = new Brelan();
            case 1: newFigure = new Carre();
            case 2: newFigure = new Full();
            case 3: newFigure = new PetiteSuite();
            case 4: newFigure = new GrandeSuite();
            case 5: newFigure = new Yahtzee();
            case 6: newFigure = new Chance();
            default: nullptr;
            }
            if (newFigure && newFigure->calculateScore(diceValues) > 0 && !isFigureUtilisee(newFigure)) {
                newFigures.push_back(newFigure);
            }
        }

        figures.insert(figures.end(), newFigures.begin(), newFigures.end());
    }

    void displayFigureScores(const std::vector<int>& diceValues) const {
        std::cout << "Scores des figures possibles : " << std::endl;
        for (size_t i = 0; i < figures.size(); ++i) {
            std::cout << i + 1 << ". " << figures[i]->getName() << ": " << figures[i]->calculateScore(diceValues) << " points" << std::endl;
        }
        std::cout << std::endl;
    }

    void chooseFigure(const std::vector<int>& diceValues) {
        int choice;

        std::cout << "Choisissez une figure parmi les options suivantes :" << std::endl;
        displayFigureScores(diceValues);

        std::cout << "Choix (1-" << figures.size() << ") : ";
        std::cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(figures.size())) {
            Figure* selectedFigure = figures[choice - 1];

            // Vérifier si la figure a déjà été utilisée
            if (std::find(figuresUtilisees.begin(), figuresUtilisees.end(), selectedFigure) != figuresUtilisees.end()) {
                std::cout << "Vous avez déjà choisi cette figure. Veuillez choisir une figure différente." << std::endl;
            }
            else {
                int scoreForFigure = selectedFigure->calculateScore(diceValues);

                if (dynamic_cast<Yahtzee*>(selectedFigure) != nullptr) {
                    if (yamBonus) {
                        std::cout << "Vous avez déjà marqué un Yam's. Vous ne pouvez pas marquer de points pour un deuxième Yam's." << std::endl;
                    }
                    else {
                        yamBonus = true;
                        totalScore += 100;  // Bonus pour le deuxième Yam's
                    }
                }

                totalScore += scoreForFigure;

                std::cout << "Vous avez choisi " << selectedFigure->getName() << " et vous avez obtenu " << scoreForFigure << " points." << std::endl;

                // Remove the chosen figure from the available figures
                figuresUtilisees.push_back(selectedFigure);
            }
        }
        else {
            std::cout << "Choix invalide. Veuillez choisir une figure valide." << std::endl;
        }

    }

    void calculateTotalScore(const std::vector<int>& diceValues) {
        totalScore = 0;
        for (Figure* figure : figures) {
            totalScore += figure->calculateScore(diceValues);
        }
    }
};
