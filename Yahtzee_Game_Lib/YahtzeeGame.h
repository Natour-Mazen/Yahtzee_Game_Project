#pragma once
#include "player/Joueur.h"
#include "dice/Lancer.h"
#include "enums/difficulty.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <thread>  // pour std::this_thread::sleep_for
#include <chrono> 

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

    void afficherMenuDifficulte();
    const char* getDifficultyName(DifficultyLevel level);
    void choisirDifficulte();

    void nouvellePartie();
    void nouvellePartieIaVsHumain();
    void playHelper();
  
 
    void afficherMenuPrincipal();
    int saisirChoix(int min, int max);

    void jouerTour(int num_player, void (Joueur::* createFiguresFunc)(), const int& NombreMaxOfFigureTopick, const bool& isDifficileMode);
   
    void jouerFacile();
    void jouerTourFacile(int num_player);

    void jouerNormal();
    void jouerTourNormalMineure(int num_player);
    void jouerTourNormalMajeur(int num_player);

    void jouerDifficile();
    void jouerTourDifficile(int num_player);

    void jouerHardcore();
    void jouerTourHardcore(int num_player);

    void YahtzeeGame::jouerTourIAvsHumain(Joueur* player, bool isIA);
    void jouerIAvsHumain();
    
    void afficherScoresTousJoueurs();

    void serialize() const;
    void deserialize();
};

