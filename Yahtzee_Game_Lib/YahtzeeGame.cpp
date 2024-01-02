#include "YahtzeeGame.h"


YahtzeeGame::YahtzeeGame() : variante(DifficultyLevel::FACILE), joueurs(), lancer() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

YahtzeeGame::~YahtzeeGame() {
    joueurs.clear();
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






void YahtzeeGame::playGame() {
    int choix;
    do {
        joueurs.clear();
        afficherMenuPrincipal();
        choix = saisirChoix(1, 3);

        switch (choix) {
        case 1:
            nouvellePartie();
            break;
        case 2:
            reprendrePartie();
            break;
        case 3:
            std::cout << "  <<=>> Au revoir ! <<=>>   " << std::endl;
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
    default:
        throw std::exception("erreur de variante");
        break;
    }
}

void YahtzeeGame::nouvellePartie() {
    int numberOfPlayers;
    do {
        std::cout << ">> Entrez le nombre de joueurs (max 8) : ";
        std::cin >> numberOfPlayers;

        // Vérifiez si l'entrée était un nombre entier
        if (std::cin.fail()) {
            std::cin.clear(); // efface l'état d'erreur sur cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore les caractères incorrects
            std::cout << "   /!\\ Vous devez entrer un nombre. Veuillez reessayer /!\\    \n";
            continue;
        }

        if (numberOfPlayers <= 0 || numberOfPlayers > 8) {
            std::cout << "   /!\\ Le nombre de joueurs doit etre superieur a 0 et inferieur a 8. Veuillez reessayer /!\\    \n";
        }
    } while (numberOfPlayers <= 0 || numberOfPlayers > 8);

    for (int i = 0; i < numberOfPlayers; ++i) {
        std::shared_ptr<Joueur> player = std::make_shared<Joueur>();
        joueurs.push_back(player);
    }
    std::cout << std::endl;
    choisirDifficulte();
    std::cout << std::endl;
    playHelper();
}

void YahtzeeGame::sauvegarderPartie() {
    serialize();
}

void YahtzeeGame::reprendrePartie() {
    deserialize();
    std::cout << "  <<=>> La partie a repris avec : <<=>>   " << std::endl;
    std::cout << "\t   <> " << joueurs.size() << " joueur(s)    " << std::endl;
    std::cout << "\t   <> la difficulte " << getDifficultyName(variante) << std::endl;
    playHelper();
}





int YahtzeeGame::saisirChoix(int min, int max) {
    int choix;
    bool isNumber;

    do {
        std::cout << ">> Votre choix (" << min << "-" << max << ") : ";
        std::cin >> choix;

        // Vérifie si l'entrée précédente sur le flux était un entier
        isNumber = std::cin.good();

        if (!isNumber) {
            std::cout << "   /!\\ Erreur : Veuillez entrer un chiffre /!\\   \n";
        }
        else if (choix < min || choix > max) {
            std::cout << "   /!\\ Erreur : Votre choix doit etre entre " << min << " et " << max << " /!\\   \n";
        }

        // Efface l'état de l'erreur précédente
        std::cin.clear();

        // Ignore le reste de la ligne
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (!isNumber || choix < min || choix > max);

    return choix;
}

void YahtzeeGame::choisirDifficulte() {
    afficherMenuDifficulte();
    int choix = saisirChoix(1, HARDCORE + 1);
    variante = static_cast<DifficultyLevel>(choix - 1);
    std::cout << "  <<=>> Vous avez choisi le mode " << getDifficultyName(variante) << " <<=>>   " << std::endl;
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

void YahtzeeGame::afficherScoresTousJoueurs() {
    std::cout << "\n|------------------Fin du Jeu-----------------|\n";
    std::cout << "|                                             |\n";
    std::cout << "|------Voici le scores de chaque joueurs------|\n";
    for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
        std::cout << "\t -> Score total du joueur " << num_player + 1 << " : " << joueurs[num_player]->getTotalScore() << std::endl;
    }
    std::cout << std::endl;
}






void YahtzeeGame::jouerTour(int num_player, void (Joueur::* createFiguresFunc)(), const int& NombreMaxOfFigureTopick = 0,const bool& isDifficileMode = false) {
    Joueur* player = joueurs[num_player].get();
    (player->*createFiguresFunc)();
    if (!player->isFiguresEmpty())
    {
        std::cout << "\n======== Joueur numero " << num_player + 1 << " a vous de jouer ========\n" << std::endl;
        lancer.rollDices();
        lancer.printDices();
        lancer.reRollDices();
        player->handleYahtzeeBonus(lancer.getDiceValues());
        if (isDifficileMode) {
            player->chooseFigureDifficileAndPlusModes(lancer.getDiceValues(), NombreMaxOfFigureTopick);
        }
        else {
            player->chooseFigureFacileAndPlusModes(lancer.getDiceValues());
        }
        player->resetFigures();
        sauvegarderPartie();
    }
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

void YahtzeeGame::jouerTourDifficile(int num_player) {
    jouerTour(num_player, &Joueur::createAllFigures, 1, true);
}

void YahtzeeGame::jouerTourHardcore(int num_player) {
    jouerTour(num_player, &Joueur::createHardcoreFigures, 1, true);
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

    std::cout << "\n   <<===>> La partie majeure commence <<===>>\n" << std::endl;

    for (int round = 0; round < 7; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourNormalMajeur(num_player);          
        }
    }
    afficherScoresTousJoueurs();
}

void YahtzeeGame::jouerDifficile() {
    for (int round = 0; round < 13; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourDifficile(num_player);
        }
    }
    afficherScoresTousJoueurs();
}

void YahtzeeGame::jouerHardcore() {
    for (int round = 0; round < 13; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourHardcore(num_player);
        }
    }
    afficherScoresTousJoueurs();
}




// Save/Load
void YahtzeeGame::serialize() const {
    std::ofstream fichier("sauvegarde.txt");
    if (fichier.is_open()) {
        fichier << "variante :" << variante << "\n";
        fichier << "Combien de joueurs :" << joueurs.size() << "\n";
        int i = 0;
        for (auto& joueur : joueurs) {
            fichier << "Joueur numero: " << i << "\n";
            joueur->serialize(fichier);
            i++;
        }

        std::cout << "\n   <<===>> Partie sauvegardee <<===>>   \n" << std::endl;
    }
    else {
        std::cerr << "\n   <<===>> Impossible d'ouvrir le fichier de sauvegarde <<===>>   \n" << std::endl;
    }
}

void YahtzeeGame::deserialize() {
    std::ifstream fichier("sauvegarde.txt");
    if (fichier.is_open()) {
        std::string ligne;
        getline(fichier, ligne);
        variante = static_cast<DifficultyLevel>(std::stoi(ligne.substr(ligne.find(":") + 1)));

        getline(fichier, ligne);
        int nombreJoueurs = std::stoi(ligne.substr(ligne.find(":") + 1));

        joueurs.clear();
        for (int i = 0; i < nombreJoueurs; i++) {
            getline(fichier, ligne);  // Lire "Joueur numero X"
            auto joueur = std::make_shared<Joueur>();
            joueur->deserialize(fichier);
            joueurs.push_back(joueur);
        }

        std::cout << "\n   <<===>> Partie chargee <<===>>   \n" << std::endl;
    }
    else {
        std::cerr << "\n   <<===>> Impossible d'ouvrir le fichier de sauvegarde <<===>>   \n" << std::endl;
    }
}



