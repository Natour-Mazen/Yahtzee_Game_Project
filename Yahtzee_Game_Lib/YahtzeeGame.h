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
#include <../../RapidXML-master/RapidXML/rapidxml_print.hpp>
#include <../../RapidXML-master/RapidXML/rapidxml.hpp>
#include <../../RapidXML-master/RapidXML/rapidxml_utils.hpp>

class YahtzeeGame {
public:

    YahtzeeGame();
    ~YahtzeeGame();

    void playGame();
    void sauvegarderPartie() const;
    void reprendrePartie();

private:
    DifficultyLevel variante;
    std::vector<std::shared_ptr<Joueur>> joueurs;
    Lancer lancer;

    void afficherMenuDifficulte();
    static const char* getDifficultyName(DifficultyLevel level);
    void choisirDifficulte();

    void nouvellePartie();
    void nouvellePartieIaVsHumain();
    void playHelper();
    void ajoutJoueurClassement() const;


    void afficherMenuPrincipal();
    void afficherClassement();
    int saisirChoix(int min, int max);

    void jouerTour(int num_player, void (Joueur::* createFiguresFunc)(), const int& NombreMaxOfFigureTopick = 0, const bool& isDifficileMode = false);
   
    void jouerFacile();
    void jouerTourFacile(int num_player);

    void jouerNormal();
    void jouerTourNormalMineure(int num_player);
    void jouerTourNormalMajeur(int num_player);

    void jouerDifficile();
    void jouerTourDifficile(int num_player);

    void jouerHardcore();
    void jouerTourHardcore(int num_player);

    void jouerTourIAvsHumain(Joueur* player, bool isIA);
    void jouerIAvsHumain();
    
    void afficherScoresEtFuilleMarqueTousJoueurs() const;

    void serialize() const;
    void deserialize(bool* isDeserializeOk);
};

