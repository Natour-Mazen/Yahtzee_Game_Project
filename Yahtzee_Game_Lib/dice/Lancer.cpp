#include "Lancer.h"

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
    std::cout << "<<< Valeurs des Des : ";
    for (int value : m_diceValues) {
        std::cout << value << " ";
    }
    std::cout << " >>>" << std::endl;
}

/** Display the choice to re roll the dices two times of the dices that the user wants (between 1 and 5). 
**/
void Lancer::reRollDices() {
    // Look if we have 5 dices in the vector.
    if (m_diceValues.size() != 5) {
        std::cerr << "  /!\\ Erreur: la taille du vecteur diceValues n'est pas correcte /!\\ " << std::endl;
        return;
    }

    // Choice of dice to reroll (2 rerolls maximum).
    for (int lancer = 1; lancer <= 2; ++lancer) {
        int choix;
        std::cout << ">> Relancer les Des ? (1 pour oui, 0 pour non): ";

        while (!(std::cin >> choix) || (choix != 0 && choix != 1) || std::cin.peek() != '\n') {
            std::cin.clear();  // Reset the error statut of cin.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Flushing the input buffer.
            std::cerr << "  /!\\ Erreur: Veuillez entrer une seule valeur (0 ou 1) /!\\ " << std::endl;
            std::cout << ">> Relancer les Des ? (1 pour oui, 0 pour non): ";
        }

        if (choix) {
            // Selection of dice to reroll.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Flushing the input buffer.
            std::cout << ">> Indices des Des a relancer (separes par un espace et de 1 a 5): ";
            std::string ligne;
            std::getline(std::cin, ligne);

            std::istringstream iss(ligne);
            int indice;
            while (iss >> indice) {
                // If the index is valid.
                if (indice >= 1 && indice <= 5) {
                    m_diceValues[indice - 1] = rand() % 6 + 1;
                }
                else {
                    std::cerr << "/!\\ Erreur: Indice invalide pour : " << indice << " /!\\" << std::endl;
                }
            }
            printDices();
        }
        else {
            break; // Exit the loop if the player does not want to reroll the dices.
        }
    }
}
