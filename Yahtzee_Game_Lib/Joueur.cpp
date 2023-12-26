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
            return figure->getID() == usedFigure->getID();
        };

    return std::find_if(figuresUsed.begin(), figuresUsed.end(), is_figure) != std::end(figuresUsed);
}

void Joueur::createFigures(const std::vector<int>& diceValues) {
    std::vector<Figure*> newFigures;

    for (unsigned short i = 0; i < 7; ++i) {
        Figure* newFigure = nullptr;
        switch (i) {
        case 0: newFigure = new Brelan(); 
            break;
        case 1: newFigure = new Carre(); 
            break;
        case 2: newFigure = new Full(); 
            break;
        case 3: newFigure = new PetiteSuite(); 
            break;
        case 4: newFigure = new GrandeSuite(); 
            break;
        case 5: newFigure = new Yahtzee(); 
            break;
        case 6: newFigure = new Chance(); 
            break;
        }
        if (newFigure->calculateScore(diceValues) > 0 && !isFigureUsed(newFigure)) {
            newFigures.push_back(newFigure);
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

    std::cout << "Choisissez une figure parmi les options suivantes :" << std::endl;
    displayFigureScores(diceValues);

    std::cout << "Choix (1-" << figures.size() << ") : ";
    std::cin >> choice;

    if (choice >= 1 && choice <= static_cast<int>(figures.size())) {
        Figure* selectedFigure = figures[choice - 1];

        // Vérifier si la figure a déjà été utilisée
        if (std::find(figuresUsed.begin(), figuresUsed.end(), selectedFigure) != figuresUsed.end()) {
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
            figuresUsed.push_back(selectedFigure);
        }
    }
    else {
        std::cout << "Choix invalide. Veuillez choisir une figure valide." << std::endl;
    }

}

void Joueur::calculateTotalScore(const std::vector<int>& diceValues) {
    for (Figure* figure : figures) {
        totalScore += figure->calculateScore(diceValues);
    }
}