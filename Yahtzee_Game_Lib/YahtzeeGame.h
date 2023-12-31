#pragma once
#include "player/Joueur.h"
#include "dice/Lancer.h"
#include "enums/difficulty.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

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

    void jouerTour(int num_player, void (Joueur::* createFiguresFunc)(), const int& NombreMaxOfFigureTopick, const bool& isDifficileMode);
    void jouerTourFacile(int num_player);
    void jouerTourNormalMineure(int num_player);
    void jouerTourNormalMajeur(int num_player);
    void jouerTourDifficile(int num_player);
    void jouerTourHardcore(int num_player);

    void afficherScoresTousJoueurs();
};

