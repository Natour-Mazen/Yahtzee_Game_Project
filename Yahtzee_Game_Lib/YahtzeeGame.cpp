#include "YahtzeeGame.h"
#include <iostream>
#include <algorithm>

YahtzeeGame::YahtzeeGame() : variante(DifficultyLevel::FACILE), joueur(Joueur()), lancer(Lancer()) {
    srand(static_cast<unsigned int>(time(nullptr)));
}

YahtzeeGame::~YahtzeeGame() {}


void YahtzeeGame::choisirDifficulte() {
    int choix;

    std::cout << "Choisissez le niveau de difficulté :" << std::endl;

    for (int i = 0; i < HARDCORE + 1; ++i) {
        std::cout << i + 1 << ". " << getDifficultyName(static_cast<DifficultyLevel>(i)) << std::endl;
    }

    do {
        std::cout << "Votre choix (1-" << HARDCORE + 1 << ") : ";
        std::cin >> choix;
    } while (choix < 1 || choix > HARDCORE + 1);

    variante = static_cast<DifficultyLevel>(choix - 1);
}

const char* YahtzeeGame::getDifficultyName(DifficultyLevel level) {
    switch (level) {
    case FACILE:
        return "Facile";
    case NORMAL:
        return "Normal";
    case DIFFICILE:
        return "Difficile";
    case HARDCORE:
        return "Hardcore";
    default:
        return "Inconnu";
    }
}


void YahtzeeGame::playGame()
{
    std::cout << "Bienvenue dans le jeu Yahtzee!" << std::endl;

    int choix;

    do {
        std::cout << "Menu principal :" << std::endl;
        std::cout << "1. Nouvelle partie" << std::endl;
        std::cout << "2. Charger partie" << std::endl;
        std::cout << "3. Quitter" << std::endl;

        std::cout << "Votre choix (1-3) : ";
        std::cin >> choix;

        switch (choix) {
        case 1:
        {
            choisirDifficulte();
            playHelper();
            break;
        }
        case 2:
            //reprendrePartie();
            playHelper();
            break;
        case 3:
            std::cout << "Au revoir!" << std::endl;
            break;
        default:
            std::cout << "Choix invalide. Veuillez choisir à nouveau." << std::endl;
            break;
        }
    } while (choix != 3);
}


void YahtzeeGame::playHelper() {
    switch (variante) {
    case FACILE:
        jouerFacile();
        break;
    case NORMAL:
        jouerNormal();
        break;
    case DIFFICILE:
        jouerDifficile();
        break;
    case HARDCORE:
        jouerHardcore();
        break;
    }
}

void YahtzeeGame::jouerFacile() {
    for (int round = 0; round < 13; ++round) {
        lancer.rollDice();
        lancer.printDices();
        lancer.reRollDice();

        joueur.resetFigures();
        joueur.createFigures();
        joueur.chooseFigure(lancer.getDiceValues());

        std::cout << "Score total du joueur : " << joueur.getTotalScore() << std::endl;
    }
}

void YahtzeeGame::jouerNormal() {
    jouerFacile(); // En mode normal, la partie supérieure doit être faite avant la partie inférieure
    for (int round = 0; round < 6; ++round) {
        lancer.rollDice();
        lancer.printDices();
        lancer.reRollDice();

        joueur.resetFigures();
        joueur.createNumberFigures();
        joueur.chooseFigure(lancer.getDiceValues());

        std::cout << "Score total du joueur : " << joueur.getTotalScore() << std::endl;
    }
    std::cout << "La partie mineure est fini, le score total du joueur : " << joueur.getTotalScore() << std::endl;
    for (int round = 0; round < 7; ++round) {
        lancer.rollDice();
        lancer.printDices();
        lancer.reRollDice();

        joueur.resetFigures();
        joueur.createOtherFigures();
        joueur.chooseFigure(lancer.getDiceValues());

        std::cout << "Score total du joueur : " << joueur.getTotalScore() << std::endl;
    }
}

void YahtzeeGame::jouerDifficile() {
    // TODO : ADD implementation
}

void YahtzeeGame::jouerHardcore() {
    std::vector<int> ordreFigures{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    std::random_shuffle(ordreFigures.begin(), ordreFigures.end());

    // TODO : ADD implementation
}
/*
void YahtzeeGame::sauvegarderPartie() {
    sauvegarde.sauvegarder(*this);
    std::cout << "Partie sauvegardée." << std::endl;
}

void YahtzeeGame::reprendrePartie() {
    sauvegarde.charger(*this);
    std::cout << "Partie reprise." << std::endl;
}*/