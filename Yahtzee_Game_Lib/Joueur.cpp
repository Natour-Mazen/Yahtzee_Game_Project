#include "Joueur.h"
#include <algorithm>

Joueur::Joueur() : totalScore(0), yamBonus(false), minorScore(0){
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

Figure* Joueur::createNumberFigure(int id) {
    switch (id) {
    case 1: return new Number<1>();
    case 2: return new Number<2>();
    case 3: return new Number<3>();
    case 4: return new Number<4>();
    case 5: return new Number<5>();
    case 6: return new Number<6>();
    default: return nullptr;
    }
}

void Joueur::createFigures(const std::vector<int>& diceValues) {
    std::vector<Figure*> newFigures;

    // Créer les figures pour les nombres
    for (unsigned short i = 1; i <= 6; ++i) {
        Figure* newFigure = createNumberFigure(i);
        if (newFigure && !isFigureUsed(newFigure)) {
            newFigures.push_back(newFigure);
        }
    }

    // Créer les autres figures
    for (unsigned short i = 0; i < 7; ++i) {
        Figure* newFigure = nullptr;
        switch (i) {
        case 0: newFigure = new Brelan<7>();
            break;
        case 1: newFigure = new Carre<8>();
            break;
        case 2: newFigure = new Full<9>();
            break;
        case 3: newFigure = new PetiteSuite<10>();
            break;
        case 4: newFigure = new GrandeSuite<11>();
            break;
            // If a Yathzee have already happend, then we give a other one for the bonus. 
        case 5: !firstYam ? newFigure = new Yahtzee<12>() : newFigure = new Yahtzee<13>();
            break;
        case 6: newFigure = new Chance<14>();
            break;
        }
        if (!isFigureUsed(newFigure)) {
            if (newFigure->getId() == 13) {
                if (!yamBonus)
                {
                    std::cout << "Yahtzee encore ! +100 points." << std::endl;
                    totalScore += 100;
                    yamBonus = true;

                }
                delete newFigure;
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
                    
                    firstYam = true;
                }

                totalScore += scoreForFigure;

                if (figureId >= 1 && figureId <= 6) {
                    minorScore += scoreForFigure;
                    if (minorScore >= 63) {
                        totalScore += 35;
                    }
                }

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

