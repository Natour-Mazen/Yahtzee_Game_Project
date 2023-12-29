#include "YahtzeeGame.h"
#include <iostream>
#include <algorithm>

YahtzeeGame::YahtzeeGame() : variante(DifficultyLevel::FACILE), joueurs(), lancer(), sauvegarde() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

YahtzeeGame::~YahtzeeGame() {}



int YahtzeeGame::saisirChoix(int min, int max) {
    int choix;
    do {
        std::cout << "Votre choix (" << min << "-" << max << ") : ";
        std::cin >> choix;
    } while (choix < min || choix > max);
    return choix;
}

void YahtzeeGame::playGame() {
    std::cout << "Bienvenue dans le jeu Yahtzee!" << std::endl;

    int choix;
    do {
        afficherMenuPrincipal();
        choix = saisirChoix(1, 3);

        switch (choix) {
        case 1:
            nouvellePartie();
            break;
        case 2:
            // reprendrePartie();
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

void YahtzeeGame::afficherMenuDifficulte() {
    std::cout << "Choisissez le niveau de difficulte :" << std::endl;
    for (int i = 0; i < HARDCORE + 1; ++i) {
        std::cout << i + 1 << ". " << getDifficultyName(static_cast<DifficultyLevel>(i)) << std::endl;
    }
}

void YahtzeeGame::afficherMenuPrincipal() {
    std::cout << "Menu principal :" << std::endl;
    std::cout << "1. Nouvelle partie" << std::endl;
    std::cout << "2. Charger partie" << std::endl;
    std::cout << "3. Quitter" << std::endl;
}

void YahtzeeGame::choisirDifficulte() {
    afficherMenuDifficulte();
    int choix = saisirChoix(1, HARDCORE + 1);
    variante = static_cast<DifficultyLevel>(choix - 1);
    std::cout << "Vous avez choisi le mode " << getDifficultyName(variante) << std::endl;
}

void YahtzeeGame::nouvellePartie() {
    int numberOfPlayers;
    do {
        std::cout << "Entrez le nombre de joueurs : ";
        std::cin >> numberOfPlayers;
        if (numberOfPlayers <= 0) {
            std::cout << "Le nombre de joueurs doit etre superieur a 0. Veuillez reessayer.\n";
        }
    } while (numberOfPlayers <= 0);

    for (int i = 0; i < numberOfPlayers; ++i) {
        Joueur player;
        joueurs.push_back(player);
    }
    std::cout << std::endl;
    choisirDifficulte();
    std::cout << std::endl;
    playHelper();
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

void YahtzeeGame::jouerTour(int num_player, void (Joueur::* createFiguresFunc)()) {
    std::cout << "\n======== Joueur numero " << num_player + 1 << " a vous de jouer ========\n" << std::endl;
    lancer.rollDice();
    lancer.printDices();
    lancer.reRollDice();
    joueurs[num_player].resetFigures();
    (joueurs[num_player].*createFiguresFunc)();
    joueurs[num_player].chooseFigure(lancer.getDiceValues());
    std::cout << "Votre Score total joueur " << num_player + 1 << " : " << joueurs[num_player].getTotalScore() << std::endl;
}

void YahtzeeGame::jouerTourFacile(int num_player) {
    jouerTour(num_player, &Joueur::createAllFigures);
}

void YahtzeeGame::jouerTourNormalMineure(int num_player) {
    jouerTour(num_player, &Joueur::createNumberFigures);
}

void YahtzeeGame::jouerTourNormalMajeur(int num_player) {
    jouerTour(num_player, &Joueur::createOtherFigures);
}

void YahtzeeGame::afficherScoresTousJoueurs() {
    std::cout << "------ Voici le scores de chaque joueurs ------" << std::endl;
    for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
        std::cout << "\t -> Score total du joueur " << num_player + 1  << " : " << joueurs[num_player].getTotalScore() << std::endl;
    }
}

void YahtzeeGame::jouerFacile() {
    for (int round = 0; round < 13; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourFacile(num_player);  
        }
    }
    afficherScoresTousJoueurs();
}


void YahtzeeGame::jouerNormal() {
    std::cout << "\n<<<<<< La partie majeure commence >>>>>>\n" << std::endl;

    for (int round = 0; round < 6; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourNormalMineure(num_player);
        }
    }
    afficherScoresTousJoueurs();

    std::cout << "\n<<<<<< La partie majeure commence >>>>>>\n" << std::endl;

    for (int round = 0; round < 7; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourNormalMajeur(num_player);          
        }
    }
    afficherScoresTousJoueurs();
}

void YahtzeeGame::jouerDifficile() {
    // TODO: Ajouter l'implémentation
}

void YahtzeeGame::jouerHardcore() {
    std::vector<int> ordreFigures{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    std::random_shuffle(ordreFigures.begin(), ordreFigures.end());

    // TODO: Ajouter l'implémentation
}

void YahtzeeGame::sauvegarderPartie() {
    sauvegarde.sauvegarder(*this);
    std::cout << "Partie sauvegardée." << std::endl;
}

void YahtzeeGame::reprendrePartie() {
    sauvegarde.charger(*this);
    std::cout << "Partie reprise." << std::endl;
}
