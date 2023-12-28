#include "Sauvegarde.h"
#include "../YahtzeeGame.h"

void Sauvegarde::sauvegarder(const YahtzeeGame& jeu) {
    std::ofstream fichier("sauvegarde.txt", std::ios::out | std::ios::binary);

    if (fichier.is_open()) {
        fichier.write(reinterpret_cast<const char*>(&jeu), sizeof(YahtzeeGame));
        fichier.close();
    }
    else {
        std::cerr << "Impossible d'ouvrir le fichier de sauvegarde." << std::endl;
    }
}

void Sauvegarde::charger(YahtzeeGame& jeu) const {
    std::ifstream fichier("sauvegarde.txt", std::ios::in | std::ios::binary);

    if (fichier.is_open()) {
        fichier.read(reinterpret_cast<char*>(&jeu), sizeof(YahtzeeGame));
        fichier.close();
    }
    else {
        std::cerr << "Impossible de charger la sauvegarde. Démarrage d'une nouvelle partie." << std::endl;
    }
}