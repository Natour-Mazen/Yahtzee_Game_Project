#include "YahtzeeGame.h"
#include "player/IA/IA.h"

/**
 * @brief Constructor for the YahtzeeGame class.
 * Initializes the random seed based on the current time.
 */
YahtzeeGame::YahtzeeGame() : variante(DifficultyLevel::FACILE), joueurs(), lancer() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

/**
 * @brief Destructor for the YahtzeeGame class.
 * Clears the list of players.
 */
YahtzeeGame::~YahtzeeGame() {
    joueurs.clear();
}

/*============================================================*/

/**
 * @brief Displays the difficulty selection menu.
 */
void YahtzeeGame::afficherMenuDifficulte() {
    const unsigned char VERTICAL_LINE = 179;
    const unsigned char T_UP = 180;
    const unsigned char UPPER_RIGHT_CORNER = 191;
    const unsigned char LOWER_LEFT_CORNER = 192;
    const unsigned char T_DOWN = 195;
    const unsigned char HORIZONTAL_LINE = 196;
    const unsigned char LOWER_RIGHT_CORNER = 217;
    const unsigned char UPPER_LEFT_CORNER = 218;
    std::cout << UPPER_LEFT_CORNER << std::string(47, HORIZONTAL_LINE) << UPPER_RIGHT_CORNER << "\n";
    std::cout << VERTICAL_LINE << " Choisissez le niveau de difficulte :          " << VERTICAL_LINE << "\n";
    std::cout << T_DOWN << std::string(47, HORIZONTAL_LINE) << T_UP << "\n";
    for (int i = 0; i < HARDCORE + 1; ++i) {
        std::cout << VERTICAL_LINE << " " << std::setw(2) << std::right << i + 1 << ". " << std::setw(30) << std::left << getDifficultyName(static_cast<DifficultyLevel>(i)) << std::setw(13) << std::right << VERTICAL_LINE << "\n";
    }
    std::cout << LOWER_LEFT_CORNER << std::string(47, HORIZONTAL_LINE) << LOWER_RIGHT_CORNER << "\n";
}

/**
 * @brief Displays the main menu of the Yahtzee game.
 */
void YahtzeeGame::afficherMenuPrincipal() {
    const unsigned char T_UP = 185;
    const unsigned char VERTICAL_LINE = 186;
    const unsigned char UPPER_RIGHT_CORNER = 187;
    const unsigned char LOWER_RIGHT_CORNER = 188;
    const unsigned char LOWER_LEFT_CORNER = 200;
    const unsigned char UPPER_LEFT_CORNER = 201;
    const unsigned char T_DOWN = 204;
    const unsigned char HORIZONTAL_LINE = 205;
    std::cout << UPPER_LEFT_CORNER << std::string(47, HORIZONTAL_LINE) << UPPER_RIGHT_CORNER << "\n";
    std::cout << VERTICAL_LINE << " Bienvenue dans le jeu Yahtzee!                " << VERTICAL_LINE << "\n";
    std::cout << T_DOWN << std::string(47, HORIZONTAL_LINE) << T_UP << "\n";
    std::cout << VERTICAL_LINE << " Menu principal :                              " << VERTICAL_LINE << "\n";
    std::cout << T_DOWN << std::string(47, HORIZONTAL_LINE) << T_UP << "\n";
    std::cout << VERTICAL_LINE << " 1. Nouvelle partie                            " << VERTICAL_LINE << "\n";
    std::cout << VERTICAL_LINE << " 2. Charger partie                             " << VERTICAL_LINE << "\n";
    std::cout << VERTICAL_LINE << " 3. IA vs Humain                               " << VERTICAL_LINE << "\n";
    std::cout << VERTICAL_LINE << " 4. Quitter                                    " << VERTICAL_LINE << "\n";
    std::cout << LOWER_LEFT_CORNER << std::string(47, HORIZONTAL_LINE) << LOWER_RIGHT_CORNER << "\n";
}

/*============================================================*/

/**
 * @brief Initiates the Yahtzee game and handles user interactions for menu navigation.
 */
void YahtzeeGame::playGame() {
    int choix;
    do {
        joueurs.clear();
        afficherMenuPrincipal();
        choix = saisirChoix(1, 4);

        switch (choix) {
        case 1:
            nouvellePartie();
            break;
        case 2:
            reprendrePartie();
            break;
        case 3:
            nouvellePartieIaVsHumain();
            break;      
        case 4:
            std::cout << "  <<=>> Au revoir ! <<=>>   " << std::endl;
            break;
        default:
            std::cout << "Choix invalide. Veuillez choisir a nouveau." << std::endl;
            break;
        }
    } while (choix != 4);
}

/**
 * @brief Displays information and starts the game based on the selected difficulty level.
 */
void YahtzeeGame::playHelper() {
    std::cout << "\n  <<=>> Pour info, il y a une sauvgarde automatique a chaque tour de jeu, Amusez vous bien :) <<=>>   " << std::endl;
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

/**
 * @brief Initiates a new game by prompting the user for the number of players and difficulty level.
 */
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
    playHelper();
}

/**
 * @brief Saves the current game state to a file.
 */
void YahtzeeGame::sauvegarderPartie() const
{
    serialize();
}

/**
 * @brief Resumes a saved game by loading the game state from a file.
 */
void YahtzeeGame::reprendrePartie() {
    bool isOkayDeserialize = false;
    deserialize(&isOkayDeserialize);
    if (isOkayDeserialize) {
        std::cout << "  <<=>> La partie a repris avec : <<=>>   " << std::endl;
        std::cout << "\t   <> " << joueurs.size() << " joueur(s)    " << std::endl;
        std::cout << "\t   <> la difficulte " << getDifficultyName(variante) << std::endl;
        playHelper();
    }
}

/**
 * @brief Initiates a new game with a human player and an AI opponent.
 */
void YahtzeeGame::nouvellePartieIaVsHumain() {
    std::cout << "\n                        <<=>> Vous avez choisi le mode 1vs1 (IA vs Humain) <<=>>         " << std::endl;
    std::cout << "  <<=>> Dans ce mode de jeu, il n\'y a pas de sauvegarde ni la possibilite de relancer les des <<=>> " << std::endl;
    std::cout << "                                   <<=>> La diffculte est Facile <<=>>         \n" << std::endl;

    // Créer un joueur humain
    std::shared_ptr<Joueur> joueurHumain = std::make_shared<Joueur>();
    joueurs.push_back(joueurHumain);

    // Créer une IA
    std::shared_ptr<IA> joueurIA = std::make_shared<IA>();
    joueurs.push_back(joueurIA);

    jouerIAvsHumain();
}


/*============================================================*/

/**
 * @brief Takes user input for a menu choice within a specified range.
 * @param min The minimum valid menu choice.
 * @param max The maximum valid menu choice.
 * @return The user's selected menu choice.
 */
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

/**
 * @brief Prompts the user to choose a difficulty level for the game.
 */
void YahtzeeGame::choisirDifficulte() {
    afficherMenuDifficulte();
    int choix = saisirChoix(1, HARDCORE + 1);
    variante = static_cast<DifficultyLevel>(choix - 1);
    std::cout << "  <<=>> Vous avez choisi le mode " << getDifficultyName(variante) << " <<=>>   " << std::endl;
}

/**
 * @brief Returns the name of the difficulty level as a string.
 * @param level The difficulty level enumeration.
 * @return The difficulty level name.
 */
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

/**
 * @brief Displays the scores of all players at the end of the game.
 *        Asks the user if they want to display the scorecards of each player.
 */
void YahtzeeGame::afficherScoresEtFuilleMarqueTousJoueurs() const
{
    std::cout << "\n|------------------Fin du Jeu-----------------|\n";
    std::cout << "|                                             |\n";
    std::cout << "|------Voici les scores de chaque joueur------|\n";
    for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
        std::cout << "\t -> Score total du joueur " << num_player + 1 << " : " << joueurs[num_player]->getTotalScore() << std::endl;
    }

    std::cout << std::endl;

    // Ask the user if they want to display the scorecards
    std::cout << ">> Voulez-vous afficher les feuilles de marque de chaque joueur ? (O/N) ";
    char reponse;
    std::cin >> reponse;

    reponse = toupper(reponse);

	// Check the user's input
    while (std::cin.fail() || (reponse != 'O' && reponse != 'N')) {
        std::cin.clear();  
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
        std::cout << "   <<=>> Entree non valide. Veuillez entrer 'O' pour Oui ou 'N' pour Non. <<=>>   \n";
        std::cout << ">> Voulez-vous afficher les feuilles de marque de chaque joueur ? (O/N) ";
        std::cin >> reponse;
        reponse = toupper(reponse);
    }

    std::cout << std::endl;

    // If the user answered 'O', display the scorecards
    if (reponse == 'O') {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            joueurs[num_player]->displayUsedFiguresAndScores(num_player);
        }
    }

    std::cout << "*****************************************************" << std::endl;
    std::cout << std::endl;
}

/*============================================================*/

/**
 * @brief Executes a game round for a player with the specified figure creation function.
 * @param num_player The index of the current player.
 * @param createFiguresFunc The function to create figures for the player.
 * @param NombreMaxOfFigureTopick The maximum number of figures the player can choose (for difficult mode).
 * @param isDifficileMode Indicates if the game is in difficult mode.
 */
void YahtzeeGame::jouerTour(int num_player, void (Joueur::* createFiguresFunc)(), const int& NombreMaxOfFigureTopick = 0,const bool& isDifficileMode = false) {
    Joueur* player = joueurs[num_player].get();
    (player->*createFiguresFunc)();
    if (!player->isFiguresEmpty())
    {
        std::cout << "\n======== Joueur numero " << num_player + 1 << " a vous de jouer ========\n" << std::endl;
        lancer.rollDices();
        lancer.printDices();
        lancer.reRollDices();
        player->calculateFiguresScore(lancer.getDiceValues());
        player->handleYahtzeeBonus();
        if (isDifficileMode) {
            player->chooseFigureDifficileAndPlusModes(NombreMaxOfFigureTopick);
        }
        else {
            player->chooseFigureFacileAndPlusModes();
        }
        player->resetFigures();
        sauvegarderPartie();
    }
}

/**
 * @brief Plays a round for a player with easy difficulty level.
 * @param num_player The index of the current player.
 */
void YahtzeeGame::jouerTourFacile(int num_player) {
    jouerTour(num_player, &Joueur::createAllFigures);
}

/**
 * @brief Plays a round for a player with normal difficulty level (minor figures).
 * @param num_player The index of the current player.
 */
void YahtzeeGame::jouerTourNormalMineure(int num_player) {
    jouerTour(num_player, &Joueur::createMinorFigures);
}

/**
 * @brief Plays a round for a player with normal difficulty level (major figures).
 * @param num_player The index of the current player.
 */
void YahtzeeGame::jouerTourNormalMajeur(int num_player) {
    jouerTour(num_player, &Joueur::createMajorFigures);
}

/**
 * @brief Plays a round for a player with difficult difficulty level.
 * @param num_player The index of the current player.
 */
void YahtzeeGame::jouerTourDifficile(int num_player) {
    jouerTour(num_player, &Joueur::createAllFigures, 1, true);
}

/**
 * @brief Plays a round for a player with hardcore difficulty level.
 * @param num_player The index of the current player.
 */
void YahtzeeGame::jouerTourHardcore(int num_player) {
    jouerTour(num_player, &Joueur::createHardcoreFigures, 1, true);
}


/**
 * @brief This function represents a single turn in a Yahtzee game between an AI and a human player.
 *
 * @param player Pointer to the player (either AI or human) who is currently playing.
 * @param isIA Boolean flag indicating whether the current player is an AI.
 */
void YahtzeeGame::jouerTourIAvsHumain(Joueur* player, bool isIA) {
    lancer.rollDices();
    lancer.printDices();
    player->createAllFigures();
    player->calculateFiguresScore(lancer.getDiceValues());
    player->handleYahtzeeBonus();
    if (isIA) {
        dynamic_cast<IA*>(player)->chooseFigure();
    }
    else {
        player->chooseFigureFacileAndPlusModes();
    }
    player->resetFigures();
}

/**
 * @brief Plays the Yahtzee game with easy difficulty level for all players.
 */
void YahtzeeGame::jouerFacile() {
    for (int round = 0; round < 13; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourFacile(num_player);
        }
    }
    afficherScoresEtFuilleMarqueTousJoueurs();
}

/**
 * @brief Plays the Yahtzee game with normal difficulty level for all players.
 */
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
    afficherScoresEtFuilleMarqueTousJoueurs();
}

/**
 * @brief Plays the Yahtzee game with difficult difficulty level for all players.
 */
void YahtzeeGame::jouerDifficile() {
    for (int round = 0; round < 13; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourDifficile(num_player);
        }
    }
    afficherScoresEtFuilleMarqueTousJoueurs();
}

/**
 * @brief Plays the Yahtzee game with hardcore difficulty level for all players.
 */
void YahtzeeGame::jouerHardcore() {
    for (int round = 0; round < 13; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            jouerTourHardcore(num_player);
        }
    }
    afficherScoresEtFuilleMarqueTousJoueurs();
}

/**
 * @brief Plays the Yahtzee game with a mix of human and AI players.
 */
void YahtzeeGame::jouerIAvsHumain() {
    for (int round = 0; round < 13; ++round) {
        for (int num_player = 0; num_player < joueurs.size(); ++num_player) {
            IA* iaPlayer = dynamic_cast<IA*>(joueurs[num_player].get());
            if (iaPlayer != nullptr) {  // Le joueur est une IA
                std::cout << "\n======== C'est au tour de l\'IA de jouer ========\n" << std::endl;
                jouerTourIAvsHumain(iaPlayer, true);
                std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            }
            else {  // Le joueur n'est pas une IA
                std::cout << "\n======== Joueur Humain a vous de jouer ========\n" << std::endl;
                jouerTourIAvsHumain(joueurs[num_player].get(), false);
            }
        }
    }
    afficherScoresEtFuilleMarqueTousJoueurs();
}


/*============================================================*/

/**
 * @brief Saves the current game state to a file.
 */
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

        std::cout << "\n  <<===>> Partie sauvegardee <<===>>   \n" << std::endl;
    }
    else {
        std::cerr << "\n  <<===>> Impossible d'ouvrir le fichier de sauvegarde <<===>>   \n" << std::endl;
    }
}

/**
 *@brief This method loads a saved game state from a file and resumes the game.
 *
 * @param isDeserializeOk A boolean pointer that indicates whether the deserialization was successful.
 */
void YahtzeeGame::deserialize(bool* isDeserializeOk) {
    std::ifstream fichier("sauvegarde.txt");
    if (fichier.is_open()) {
        std::string ligne;
        getline(fichier, ligne);
        variante = static_cast<DifficultyLevel>(std::stoi(ligne.substr(ligne.find(":") + 1)));

        getline(fichier, ligne);
        const int nombreJoueurs = std::stoi(ligne.substr(ligne.find(":") + 1));

        joueurs.clear();
        for (int i = 0; i < nombreJoueurs; i++) {
            getline(fichier, ligne);  // Lire "Joueur numero X"
            auto joueur = std::make_shared<Joueur>();
            joueur->deserialize(fichier);
            joueurs.push_back(joueur);
        }

        std::cout << "\n  <<===>> Partie chargee <<===>>   \n" << std::endl;
        *isDeserializeOk = true;
    }
    else {
        std::cerr << "\n  <<===>> Impossible d'ouvrir le fichier de sauvegarde <<===>>   \n" << std::endl;
    }
}