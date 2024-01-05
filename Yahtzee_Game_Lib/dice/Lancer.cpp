#include "Lancer.h"

#include <algorithm>

//============================================//
//                  PUBLIC                    //
//============================================//

/** Give the 5 dices.
*   @return : the vector of dices.
**/
const std::vector<int>& Lancer::getDiceValues() const {
    return m_diceValues;
}

/** Reset the 5 dices and init it with 5 new random values. 
**/
void Lancer::rollDices() {
    m_diceValues.clear();

    for (int i = 0; i < 5; ++i) {
        m_diceValues.push_back(rand() % 6 + 1);
    }
}

/** Display the 5 dices in the console.
**/
void Lancer::printDices() {
    std::cout << "   <<=>> Valeurs des Des : ";
    for (int value : m_diceValues) {
        std::cout << value << " ";
    }
    std::cout << " <<=>>" << std::endl;
}

bool Lancer::askReroll() {
    int choix;
    std::cout << ">> Relancer les Des ? (1 pour oui, 0 pour non): ";

    while (!(std::cin >> choix) || (choix != 0 && choix != 1) || std::cin.peek() != '\n') {
        std::cin.clear();  // Reset the error statut of cin.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Flushing the input buffer.
        std::cerr << "  /!\\ Erreur: Veuillez entrer une seule valeur (0 ou 1) /!\\ " << std::endl;
        std::cout << ">> Relancer les Des ? (1 pour oui, 0 pour non): ";
    }

    return choix == 1;
}


std::vector<int> Lancer::getDiceIndicesToReroll() {
    std::vector<int> indices;
    std::string ligne;

    while (true) {
        indices.clear();  // Clear the indices from the previous iteration

        // Selection of dice to reroll.
        if (std::cin.rdbuf()->in_avail())  // Check if the input buffer is not empty
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Flushing the input buffer.
        std::cout << ">> Indices des Des a relancer (separes par un espace et de 1 a 5): ";
        std::getline(std::cin, ligne);

        // Check if the input is composed of digits and spaces only
        if (!std::all_of(ligne.begin(), ligne.end(), [](const char c) { return std::isdigit(c) || std::isspace(c); })) {
            std::cout << "   /!\\ Erreur: L'entree doit etre composee de chiffres et d'espaces uniquement. /!\\   " << std::endl;
            continue;
        }

        std::istringstream iss(ligne);
        int indice;

        // Check if there are more than 5 numbers
        if (std::count(ligne.begin(), ligne.end(), ' ') > 4) {
            std::cout << "   /!\\ Erreur: Plus de 5 nombres entres. /!\\   " << std::endl;
            continue;
        }

        bool allIndicesValid = true;  // Assume all indices are valid until proven otherwise
        while (iss >> indice) {
            // If the index is valid.
            if (indice >= 1 && indice <= 5) {
                indices.push_back(indice - 1);
            }
            else {
                std::cout << "   /!\\ Erreur: Indice invalide pour : " << indice << " /!\\   " << std::endl;
                allIndicesValid = false;  // Set allIndicesValid to false if an invalid index is found
                break;
            }
        }

        if (allIndicesValid) {
            break;
        }
    }

    return indices;
}


void Lancer::reRollDices() {
    // Look if we have 5 dices in the vector.
    if (m_diceValues.size() != 5) {
        std::cerr << "  /!\\ Erreur: la taille du vecteur diceValues n'est pas correcte /!\\ " << std::endl;
        return;
    }

    // Choice of dice to reroll (2 rerolls maximum).
    for (int lancer = 1; lancer <= 2; ++lancer) {
        if (askReroll()) {
            std::vector<int> indices = getDiceIndicesToReroll();
            for (int indice : indices) {
                m_diceValues[indice] = rand() % 6 + 1;
            }
            printDices();
        }
        else {
            break; // Exit the loop if the player does not want to reroll the dices.
        }
    }
}
