#include "YahtzeeGame.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

YahtzeeGame::YahtzeeGame() : variante(DifficultyLevel::FACILE), joueurs(), lancer() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

YahtzeeGame::~YahtzeeGame() {
    joueurs.clear();
}

int YahtzeeGame::saisirChoix(int min, int max) {
    int choix;
    do {
        std::cout << ">> Votre choix (" << min << "-" << max << ") : ";
        std::cin >> choix;
    } while (choix < min || choix > max);
    return choix;
}

void YahtzeeGame::playGame() {
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
    const char UPPER_LEFT_CORNER = 218;
    const char HORIZONTAL_LINE = 196;
    const char UPPER_RIGHT_CORNER = 191;
    const char VERTICAL_LINE = 179;
    const char T_DOWN = 195;
    const char T_UP = 180;
    const char LOWER_LEFT_CORNER = 192;
    const char LOWER_RIGHT_CORNER = 217;
    std::cout << UPPER_LEFT_CORNER << std::string(47, HORIZONTAL_LINE) << UPPER_RIGHT_CORNER << "\n";
    std::cout << VERTICAL_LINE << " Choisissez le niveau de difficulte :          " << VERTICAL_LINE << "\n";
    std::cout << T_DOWN << std::string(47, HORIZONTAL_LINE) << T_UP << "\n";
    for (int i = 0; i < HARDCORE + 1; ++i) {
        std::cout << VERTICAL_LINE << " " << std::setw(2) << std::right << i + 1 << ". " << std::setw(30) << std::left << getDifficultyName(static_cast<DifficultyLevel>(i)) << std::setw(13) << std::right << VERTICAL_LINE << "\n";
    }
    std::cout << LOWER_LEFT_CORNER << std::string(47, HORIZONTAL_LINE) << LOWER_RIGHT_CORNER << "\n";
}

void YahtzeeGame::afficherMenuPrincipal() {
    const char UPPER_LEFT_CORNER = 201;
    const char HORIZONTAL_LINE = 205;
    const char UPPER_RIGHT_CORNER = 187;
    const char VERTICAL_LINE = 186;
    const char T_DOWN = 204;
    const char T_UP = 185;
    const char LOWER_LEFT_CORNER = 200;
    const char LOWER_RIGHT_CORNER = 188;
    std::cout << UPPER_LEFT_CORNER << std::string(47, HORIZONTAL_LINE) << UPPER_RIGHT_CORNER << "\n";
    std::cout << VERTICAL_LINE << " Bienvenue dans le jeu Yahtzee!                " << VERTICAL_LINE << "\n";
    std::cout << T_DOWN << std::string(47, HORIZONTAL_LINE) << T_UP << "\n";
    std::cout << VERTICAL_LINE << " Menu principal :                              " << VERTICAL_LINE << "\n";
    std::cout << T_DOWN << std::string(47, HORIZONTAL_LINE) << T_UP << "\n";
    std::cout << VERTICAL_LINE << " 1. Nouvelle partie                            " << VERTICAL_LINE << "\n";
    std::cout << VERTICAL_LINE << " 2. Charger partie                             " << VERTICAL_LINE << "\n";
    std::cout << VERTICAL_LINE << " 3. Quitter                                    " << VERTICAL_LINE << "\n";
    std::cout << LOWER_LEFT_CORNER << std::string(47, HORIZONTAL_LINE) << LOWER_RIGHT_CORNER << "\n";
}


void YahtzeeGame::choisirDifficulte() {
    afficherMenuDifficulte();
    int choix = saisirChoix(1, HARDCORE + 1);
    variante = static_cast<DifficultyLevel>(choix - 1);
    std::cout << "  <<=>> Vous avez choisi le mode " << getDifficultyName(variante) << " <<=>>" << std::endl;
}

void YahtzeeGame::nouvellePartie() {
    int numberOfPlayers;
    do {
        std::cout << ">> Entrez le nombre de joueurs : ";
        std::cin >> numberOfPlayers;
        if (numberOfPlayers <= 0) {
            std::cout << "/!\\ Le nombre de joueurs doit etre superieur a 0. Veuillez reessayer /!\\ \n";
        }
    } while (numberOfPlayers <= 0);

    for (int i = 0; i < numberOfPlayers; ++i) {
        std::shared_ptr<Joueur> player = std::make_shared<Joueur>();
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
    lancer.rollDices();
    lancer.printDices();
    lancer.reRollDices();
    Joueur* player = joueurs[num_player].get();
    (player->*createFiguresFunc)();
    player->handleYahtzeeBonus(lancer.getDiceValues());
    player->chooseFigure(lancer.getDiceValues());
    player->resetFigures();
}

void YahtzeeGame::jouerTourFacile(int num_player) {
    jouerTour(num_player, &Joueur::createAllFigures);
}

void YahtzeeGame::jouerTourNormalMineure(int num_player) {
    jouerTour(num_player, &Joueur::createMinorFigures);
}

void YahtzeeGame::jouerTourNormalMajeur(int num_player) {
    jouerTour(num_player, &Joueur::createMajorFigures);
}

void YahtzeeGame::afficherScoresTousJoueurs() {
    std::cout << "\n------ Voici le scores de chaque joueurs ------" << std::endl;
    for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
        std::cout << "\t -> Score total du joueur " << num_player + 1  << " : " << joueurs[num_player]->getTotalScore() << std::endl;
    }
    std::cout << std::endl;
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
    std::cout << "\n   <<===>> La partie mineure commence <<===>>\n" << std::endl;

    for (int round = 0; round < 6; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourNormalMineure(num_player);
        }
    }
    afficherScoresTousJoueurs();

    std::cout << "\n   <<===>> La partie majeure commence <<===>>\n" << std::endl;

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

// Sérialisation
void YahtzeeGame::sauvegarderPartie() {
    std::ofstream fichier("sauvegarde.txt");
    if (fichier.is_open()) {
        fichier << variante << "\n";
        fichier << joueurs.size() << "\n";
        for (auto& joueur : joueurs) {
            joueur->serialize(fichier);
        }
        
        std::cout << "Partie sauvegardée." << std::endl;
    }
    else {
        std::cerr << "Impossible d'ouvrir le fichier de sauvegarde." << std::endl;
    }
}

// Désérialisation
void YahtzeeGame::reprendrePartie() {
    std::ifstream fichier("sauvegarde.txt");
    if (fichier.is_open()) {
        int temp;
        fichier >> temp;
        variante = static_cast<DifficultyLevel>(temp);
        size_t taille;
        fichier >> taille;
        joueurs.resize(taille);
        for (auto& joueur : joueurs) {
            joueur->deserialize(fichier);
        }

        std::cout << "Partie reprise." << std::endl;
    }
    else {
        std::cerr << "Impossible de charger la sauvegarde. Démarrage d'une nouvelle partie." << std::endl;
    }
}


