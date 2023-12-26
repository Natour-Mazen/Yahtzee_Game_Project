#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "Figure.h"
#include "FigureFactory.h"

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

        // Count the frequency of each dice value
        std::map<int, int> valueCounts;
        for (int value : diceValues) {
            valueCounts[value]++;
        }

        // Create figures based on the frequency of values
        for (const auto& pair : valueCounts) {
            int value = pair.first;
            int count = pair.second;


            // Create a Brelan figure if the frequency is 3
            if (count >= 3) {
                Figure* newBrelan = FigureFactory::createBrelan(value);
                if (newBrelan) {
                    newFigures.push_back(newBrelan);
                }
            }

            // Create a Carre figure if the frequency is 4
            if (count >= 4) {
                Figure* newCarre = FigureFactory::createCarre(value);
                if (newCarre) {
                    newFigures.push_back(newCarre);
                }
            }

            // Create a Full figure if there are two different values with frequencies 3 and 2
            for (const auto& pair2 : valueCounts) {
                int value2 = pair2.first;
                int count2 = pair2.second;
                if (value != value2 && count == 3 && count2 == 2) {
                    Figure* newFull = FigureFactory::createFull(value, value2);
                    if (!isFigureUtilisee(newFull)) {
                        newFigures.push_back(FigureFactory::createFull(value, value2));
                    }
                }
            }

            // Create a Yahtzee figure if the frequency is 5
            if (count == 5) {
                Figure* newYahztee = FigureFactory::createYahtzee(value);
                if (newYahztee) {
                    newFigures.push_back(newYahztee);
                }
            }
        }

        // Create a PetiteSuite figure if the dice values form a small straight
        Figure* newPetiteSuite = FigureFactory::createPetiteSuite();
        if (newPetiteSuite->calculateScore(diceValues) > 0 && !isFigureUtilisee(newPetiteSuite)) {
            newFigures.push_back(newPetiteSuite);
        }

        // Create a GrandeSuite figure if the dice values form a large straight
        Figure* newGrandeSuite = FigureFactory::createGrandeSuite();
        if (newGrandeSuite->calculateScore(diceValues) > 0 && !isFigureUtilisee(newGrandeSuite)) {
            newFigures.push_back(newGrandeSuite);
        }

        // Create a Chance figure only if it's not already used
        Figure* newChance = FigureFactory::createChance();
        if (!isFigureUtilisee(newChance)) {
            newFigures.push_back(newChance);
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

                if (dynamic_cast<Yahtzee<6>*>(selectedFigure) != nullptr) {
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
