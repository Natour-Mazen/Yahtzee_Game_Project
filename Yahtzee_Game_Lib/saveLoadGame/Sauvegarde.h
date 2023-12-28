#pragma once
#include <fstream>

class YahtzeeGame;

class Sauvegarde {
public:
    // Méthode pour sauvegarder l'état du jeu
    void sauvegarder(const YahtzeeGame& jeu);

    // Méthode pour charger l'état du jeu
    void charger(YahtzeeGame& jeu) const;
};


