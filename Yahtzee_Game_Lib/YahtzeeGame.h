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
    std::vector<Joueur> joueurs;
    Lancer lancer;
    Sauvegarde sauvegarde;

    const char* getDifficultyName(DifficultyLevel level);
    void choisirDifficulte();
    void jouerFacile();
    void jouerNormal();
    void jouerDifficile();
    void jouerHardcore();
    void playHelper();
};

