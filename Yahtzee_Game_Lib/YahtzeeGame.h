#pragma once
#include "player/Joueur.h"
#include "dice/Lancer.h"
#include "enums/difficulty.h"
#include "saveLoadGame/Sauvegarde.h"


class YahtzeeGame {
public:

    YahtzeeGame();
    ~YahtzeeGame();

    void playGame();
    void sauvegarderPartie();
    void reprendrePartie();

private:
    DifficultyLevel variante;
    std::vector<std::shared_ptr<Joueur>> joueurs;
    Lancer lancer;

    const char* getDifficultyName(DifficultyLevel level);
    void choisirDifficulte();
    void jouerFacile();
    void jouerNormal();
    void jouerDifficile();
    void jouerHardcore();
    void playHelper();
    void afficherMenuDifficulte();
    int saisirChoix(int min, int max);
    void afficherMenuPrincipal();
    void nouvellePartie();
    void jouerTourFacileAndPlusModes(int num_player, void (Joueur::* createFiguresFunc)());
    void jouerTourDifficileAndPlusModes(int num_player, void (Joueur::* createFiguresFunc)(), const int& NombreMaxOfFigureTopick);
    void jouerTourFacile(int num_player);
    void jouerTourNormalMineure(int num_player);
    void jouerTourNormalMajeur(int num_player);
    void jouerTourDifficile(int num_player);
    void afficherScoresTousJoueurs();
};

