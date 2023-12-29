#include "YahtzeeGame.h"
#include <iostream>
#include <algorithm>

YahtzeeGame::YahtzeeGame() : variante(DifficultyLevel::FACILE), joueurs(), lancer(), sauvegarde() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

YahtzeeGame::~YahtzeeGame() {}


void YahtzeeGame::choisirDifficulte() {
    int choix;

    std::cout << "Choisissez le niveau de difficulte :" << std::endl;

    for (int i = 0; i < HARDCORE + 1; ++i) {
        std::cout << i + 1 << ". " << getDifficultyName(static_cast<DifficultyLevel>(i)) << std::endl;
    }

    do {
        std::cout << "Votre choix (1-" << HARDCORE + 1 << ") : ";
        std::cin >> choix;
    } while (choix < 1 || choix > HARDCORE + 1);

    variante = static_cast<DifficultyLevel>(choix - 1);

    std::cout << "Vous avez choisi le mode " << getDifficultyName(variante) << std::endl;
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
        std::cout << "\t1. Nouvelle partie" << std::endl;
        std::cout << "\t2. Charger partie" << std::endl;
        std::cout << "\t3. Quitter" << std::endl;

        std::cout << ">> Votre choix (1-3) : ";
        std::cin >> choix;

        switch (choix) {
        case 1:
        {
            int numberOfPlayers;
            std::cout << "Entrez le nombre de joueurs : ";
            std::cin >> numberOfPlayers;

            for (int i = 0; i < numberOfPlayers; ++i) {
                Joueur player;
                joueurs.push_back(player);
            }
            std::cout << std::endl;
            choisirDifficulte();
            std::cout << std::endl;
            playHelper();
            break;
        }
        case 2:
            //reprendrePartie();
           // playHelper();
            break;
        case 3:
            std::cout << "Au revoir!" << std::endl;
            break;
        default:
            std::cout << "Choix invalide. Veuillez choisir a nouveau." << std::endl;
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
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            std::cout << "\nJoueur numero " << num_player + 1 << " a vous de joueur :\n" << std::endl;
            lancer.rollDice();
            lancer.printDices();
            lancer.reRollDice();

            joueurs[num_player].resetFigures();
            joueurs[num_player].createFigures();
            joueurs[num_player].chooseFigure(lancer.getDiceValues());
        }
    }

    for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
        std::cout << "Score total du joueur " << num_player << " : " << joueurs[num_player].getTotalScore() << std::endl;
    }
}

void YahtzeeGame::jouerNormal() {
    // En mode normal, la partie supérieure doit être faite avant la partie inférieure
    for (int round = 0; round < 6; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            std::cout << "\nJoueur numero : " << num_player << " à vous de jouer :\n" << std::endl;

            lancer.rollDice();
            lancer.printDices();
            lancer.reRollDice();

            joueurs[num_player].resetFigures();
            joueurs[num_player].createNumberFigures();
            joueurs[num_player].chooseFigure(lancer.getDiceValues());

            std::cout << "Score total du joueur : " << joueurs[num_player].getTotalScore() << std::endl;
        }
    }

    std::cout << "La partie supérieure est finie, le score total des joueurs :\n" << std::endl;

    for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
        std::cout << "Score total du joueur " << num_player << " : " << joueurs[num_player].getTotalScore() << std::endl;
    }

    std::cout << "\nLa partie mineure commence :\n" << std::endl;

    for (int round = 0; round < 7; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            std::cout << "\nJoueur numero : " << num_player << " à vous de jouer :\n" << std::endl;

            lancer.rollDice();
            lancer.printDices();
            lancer.reRollDice();

            joueurs[num_player].resetFigures();
            joueurs[num_player].createOtherFigures();
            joueurs[num_player].chooseFigure(lancer.getDiceValues());

            std::cout << "Score total du joueur : " << joueurs[num_player].getTotalScore() << std::endl;
        }
    }

    std::cout << "La partie mineure est finie, le score total des joueurs :\n" << std::endl;

    for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
        std::cout << "Score total du joueur " << num_player << " : " << joueurs[num_player].getTotalScore() << std::endl;
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



void YahtzeeGame::sauvegarderPartie() {
    sauvegarde.sauvegarder(*this);
    std::cout << "Partie sauvegardée." << std::endl;
}

void YahtzeeGame::reprendrePartie() {
    sauvegarde.charger(*this);
    std::cout << "Partie reprise." << std::endl;
}