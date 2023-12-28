#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <limits>


class Lancer {
private:
    std::vector<int> diceValues;
public:
    std::vector<int> getDiceValues() const {
        return diceValues;
    };

    void rollDice() {
        diceValues.clear();
        /*
        for (int i = 0; i < 5; ++i) {
            diceValues.push_back(rand() % 6 + 1);
        }*/
        diceValues.push_back(5);
        diceValues.push_back(5);
        diceValues.push_back(5);
        diceValues.push_back(5);
        diceValues.push_back(5);
    }
    void printDices() {
        std::cout << "Valeurs des Des : ";
        for (int value : diceValues) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    void reRollDice() {
        // le vecteur a une taille suffisante
        if (diceValues.size() != 5) {
            std::cerr << "Erreur: la taille du vecteur diceValues n'est pas correcte." << std::endl;
            return;
        }

        // Choix des dés à relancer (3 lancers au total)
        for (int lancer = 1; lancer <= 2; ++lancer) {
            int choix;
            std::cout << "Relancer des dés? (1 pour oui, 0 pour non): ";

            while (!(std::cin >> choix) || (choix != 0 && choix != 1) || std::cin.peek() != '\n') {
                std::cin.clear();  // Réinitialise le statut d'erreur de cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Vidage du tampon d'entrée
                std::cerr << "Erreur: Veuillez entrer une seule valeur (0 ou 1)." << std::endl;
                std::cout << "Relancer des dés? (1 pour oui, 0 pour non): ";
            }

            if (choix) {
                // Sélection des dés à relancer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Vidage du tampon d'entrée
                std::cout << "Indices des Des a relancer (separes par un espace et de 1 a 5): ";
                std::string ligne;
                std::getline(std::cin, ligne);

                std::istringstream iss(ligne);
                int indice;
                while (iss >> indice) {
                    // Assurez-vous que l'indice est valide
                    if (indice >= 1 && indice <= 5) {
                        diceValues[indice - 1] = rand() % 6;
                    }
                    else {
                        std::cerr << "Erreur: Indice invalide pour : " << indice << "." << std::endl;
                    }
                }
                printDices();
            }
            else {
                break; // Sortir de la boucle si le joueur ne veut pas relancer les dés
            }
        }
    }
};

