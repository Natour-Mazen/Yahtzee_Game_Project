#include "Joueur.h"
#include <algorithm>

Joueur::Joueur() : totalScore(0), yamBonus(false){
	// Already init.
}

Joueur::~Joueur() {
    for (Figure* figure : figures) {
        delete figure;
    }
}

void Joueur::resetFigures() {
    figures.clear();
}

bool Joueur::isFigureUsed(Figure* figure) const {

    auto is_figure = [figure](const Figure* usedFigure){
            return figure->getId() == usedFigure->getId();
        };

    return std::find_if(figuresUsed.begin(), figuresUsed.end(), is_figure) != std::end(figuresUsed);
}

void Joueur::createFigures(const std::vector<int>& diceValues) {
    std::vector<Figure*> newFigures;

    for (unsigned short i = 0; i < 7; ++i) {
        Figure* newFigure = nullptr;
        switch (i) {
        case 0: newFigure = new Brelan<1>(); 
            break;
        case 1: newFigure = new Carre<2>();
            break;
        case 2: newFigure = new Full<3>();
            break;
        case 3: newFigure = new PetiteSuite<4>();
            break;
        case 4: newFigure = new GrandeSuite<5>();
            break;
        // If a Yathzee have already happend, then we give a other one for the bonus. 
        case 5: !firstYam ? newFigure = new Yahtzee<6>() : newFigure = new Yahtzee<7>();
            break;
        case 6: newFigure = new Chance<8>();
            break;
        }
        if (!isFigureUsed(newFigure)) {
            if (newFigure->getId() == 7) {
                totalScore += 100;
                yamBonus = true;
            }
            else {
                newFigures.push_back(newFigure);
            }
        }
    }

    figures.insert(figures.end(), newFigures.begin(), newFigures.end());
}

void Joueur::displayFigureScores(const std::vector<int>& diceValues) const {
    std::cout << "Scores des figures possibles : " << std::endl;
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << i + 1 << ". " << figures[i]->getName() << ": " << figures[i]->calculateScore(diceValues) << " points" << std::endl;
    }
    std::cout << std::endl;
}

void Joueur::chooseFigure(const std::vector<int>& diceValues) {
    int choice;

    std::cout << std::endl << "Choisissez une figure parmi les options suivantes :" << std::endl;
    displayFigureScores(diceValues);

    bool correctAnswer = false;

    do {
        std::cout << "Choix (1-" << figures.size() << ") : ";
        std::cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(figures.size())) {
            Figure* selectedFigure = figures[choice - 1];

            // Vérifier si la figure a déjà été utilisée
            if (isFigureUsed(selectedFigure)) {
                std::cout << "Vous avez déjà choisi cette figure. Veuillez choisir une figure différente." << std::endl;
            }
            else {

                int scoreForFigure = selectedFigure->calculateScore(diceValues);

                const short figureId = selectedFigure->getId();

                if (figureId == 6 && scoreForFigure > 0) {
                    
                    std::cout << "YAM" << std::endl;
                    firstYam = true;
                }

                totalScore += scoreForFigure;

                std::cout << "Vous avez choisi " << selectedFigure->getName() << " et vous avez obtenu " << scoreForFigure << " points." << std::endl;

                // Remove the chosen figure from the available figures
                figuresUsed.push_back(selectedFigure);

                correctAnswer = true;
            }
        }
        else {
            std::cout << "Choix invalide. Veuillez choisir une figure valide." << std::endl;
        }
    } while (!correctAnswer);
}

void Joueur::calculateTotalScore(const std::vector<int>& diceValues) {
    for (Figure* figure : figures) {
        totalScore += figure->calculateScore(diceValues);
    }
}