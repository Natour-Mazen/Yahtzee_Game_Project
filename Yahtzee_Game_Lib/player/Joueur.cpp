#include "Joueur.h"
#include <algorithm>
#include <iomanip>
#include "../enums/figureId.h"


/** Create a player with a total and minor score of 0 and a game grid empty.
**/
Joueur::Joueur() : m_totalScore(0), m_yahtzeeBonus(false), m_minorScore(0), m_firstYahtzee(false), aleardyHardFigureCreated(false){
    // Already init.
}

/** Destructor for a player, destroy all the vectors with allocated figures.
**/
Joueur::~Joueur() {
    m_figures.clear();
    m_figuresUsed.clear();
}


/*============================================================*/

/** Remove all the figures that we don't use anymore.
**/
void Joueur::resetFigures() {
    m_figures.clear();
}

/** For all the figures, look if it's the second Yahtzee and if it's the case then it add 100 points to the player.
**/
void Joueur::handleYahtzeeBonus() {
    if (m_firstYahtzee)
    {
        for (auto it = m_figures.begin(); it != m_figures.end(); ++it) {
            Figure* figure = it->get();
            if (figure->getId() == YAHTZEEBONUS_ID) {
                if (!m_yahtzeeBonus && figure->getScore() > 0) {
                    std::cout << "   <<=>> Yahtzee encore ! +100 points <<=>>   " << std::endl;
                    m_totalScore += 100;
                    m_yahtzeeBonus = true;
                }
                m_figures.erase(it);
                break;
            }
        }
    }
}


/*============================================================*/

/** Look if the figure pass in parameter is in the used figures.
*   @param figure : the figure that need to be check.
*   @return : true if the figure is in the used figures else false.
*/
bool Joueur::isFigureUsed(Figure* figure) const {
    auto is_figure = [figure](const std::shared_ptr<Figure> usedFigure) {
        return figure->getId() == usedFigure.get()->getId();
        };

    return std::find_if(m_figuresUsed.begin(), m_figuresUsed.end(), is_figure) != std::end(m_figuresUsed);
}

/** Create a figure in the minor part of the game, base on the number on a dice.
*   @param number : the number on a dice (form 1 to 6)
*   @return : the figure associate with it's number.
**/
std::shared_ptr<Figure> Joueur::createNumberFigure(unsigned int number) const {
    switch (number) {
    case 1: return std::make_shared<Number<ONE_ID>>(number);
    case 2: return std::make_shared<Number<TWO_ID>>(number);
    case 3: return std::make_shared<Number<THREE_ID>>(number);
    case 4: return std::make_shared<Number<FOUR_ID>>(number);
    case 5: return std::make_shared<Number<FIVE_ID>>(number);
    case 6: return std::make_shared<Number<SIX_ID>>(number);
    default: return nullptr;
    }
}

/**
 * @brief Creates a figure based on the specified identifier.
 * @param id The identifier of the figure to create.
 * @return A shared pointer to the created figure, or nullptr if the identifier is invalid.
 */
std::shared_ptr<Figure> Joueur::createFigures(unsigned int id) const {
    switch (id) {
    case 1: case 2: case 3: case 4: case 5: case 6:
        return createNumberFigure(id);
    case 7:
        return std::make_shared<Brelan<BRELAN_ID>>();
    case 8:
        return std::make_shared<Carre<CARRE_ID>>();
    case 9:
        return std::make_shared<Full<FULL_ID>>();
    case 10:
        return std::make_shared<PetiteSuite<PETITESUITE_ID>>();
    case 11:
        return std::make_shared<GrandeSuite<GRANDESUITE_ID>>();
    case 12:
        if (m_firstYahtzee) {
            return std::make_shared<Yahtzee<YAHTZEEBONUS_ID>>();
        }
        return std::make_shared<Yahtzee<YAHTZEEFIRST_ID>>();
    case 13: case 14: // The 14 for the load sys
        return std::make_shared<Chance<14>>();
    default:
        return nullptr;
    }
}

/**
 * @brief Creates all available figures for the player.
 */
void Joueur::createAllFigures() {
    for (unsigned int i = 1; i <= 13; ++i) {
        std::shared_ptr<Figure> newFigure = createFigures(i);
        if (newFigure && !isFigureUsed(newFigure.get())) {
            m_figures.push_back(newFigure);
        }
    }
}

/**
 * @brief Creates figures related to numbers 1 to 6 for the player.
 */
void Joueur::createMinorFigures() {
    for (unsigned int i = 1; i <= 6; ++i) {
        std::shared_ptr<Figure> newFigure = createFigures(i);
        if (newFigure && !isFigureUsed(newFigure.get())) {
            m_figures.push_back(newFigure);
        }
    }
}

/**
 * @brief Creates figures related to combinations from Brelan to Chance for the player.
 */
void Joueur::createMajorFigures() {
    for (unsigned int i = 7; i <= 13; ++i) {
        std::shared_ptr<Figure> newFigure = createFigures(i);
        if (newFigure && !isFigureUsed(newFigure.get())) {
            m_figures.push_back(newFigure);
        }
    }
}

/**
 * @brief Creates figures in a randomized order for the player in hardcore mode.
 */
void Joueur::createHardcoreFigures() {
    if (!aleardyHardFigureCreated) {
        ordreCreationFiguresHardcore = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        std::random_shuffle(ordreCreationFiguresHardcore.begin(), ordreCreationFiguresHardcore.end());
        aleardyHardFigureCreated = true;
    }

    for (int i : ordreCreationFiguresHardcore) {
        std::shared_ptr<Figure> newFigure = createFigures(i);
        if (newFigure && !isFigureUsed(newFigure.get())) {
            m_figures.push_back(newFigure);
        }
    }
}

/*============================================================*/

/** Display the differents figures possible for a set of dice.
**/
void Joueur::displayFigureAndScores() const {
    std::cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    std::cout << "|                   YAHTZEE                   |\n";
    std::cout << "|---------------------------------------------|\n";

    for (size_t i = 0; i < m_figures.size(); ++i) {
        std::cout << "| " << std::setw(2) << std::right << i + 1 << " - " << std::setw(19) << std::left << m_figures[i]->getName() << ": ";
        std::cout << std::setw(8) << std::right << m_figures[i]->getScore() << " points";
        std::cout << std::setw(5) << "|\n";
    }

    std::cout << "|---------------------------------------------|\n";
    std::cout << "| Votre score Total : " << std::setw(14) << std::right << m_totalScore << " points";
    std::cout << std::setw(5) << " |\n";
    std::cout << "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n";
    std::cout << std::endl;
}

/** Display the figures used and their scores.
**/
void Joueur::displayUsedFiguresAndScores(const int& numplayer) const {
    // Create a copy of the m_figuresUsed vector
    std::vector<std::shared_ptr<Figure>> figuresCopy = m_figuresUsed;

    // Sort the copy in ascending order of their IDs
    std::sort(figuresCopy.begin(), figuresCopy.end(), [](const std::shared_ptr<Figure>& a, const std::shared_ptr<Figure>& b){
        return a->getId() < b->getId();
        });

    std::cout << "================================================\n";
    std::cout << "||        FEUILLE DE MARQUE DU JOUEUR "<< numplayer + 1 <<"       ||\n";
    std::cout << "================================================\n";

    for (size_t i = 0; i < figuresCopy.size(); ++i) {
        std::cout << "|| " << std::setw(2) << std::right << std::setw(23) << std::left << figuresCopy[i]->getName() << ": ";
        std::cout << std::setw(9) << std::right << figuresCopy[i]->getScore() << " points";
        std::cout << std::setw(5) << "||\n";
    }

    std::cout << "================================================\n";
    std::cout << "|| Total Score : " << std::setw(20) << std::right << m_totalScore << " points";
    std::cout << std::setw(5) << "  ||\n";
    std::cout << "================================================\n";
    std::cout << std::endl;
}



/** Update the total score base on the points that the selected figure give us.
*   @param scoreForFigure : is the score for the selected figure.
*   @param selectedFigure : the figure selected.
**/
void Joueur::updateScores(int scoreForFigure, std::shared_ptr<Figure> selectedFigure) {
    const Figure* figure = selectedFigure.get();
    const short figureId = figure->getId();


    if (figureId == YAHTZEEFIRST_ID && scoreForFigure > 0) {
        m_firstYahtzee = true;
    }

    m_totalScore += scoreForFigure;

    if (figureId == ONE_ID || figureId == TWO_ID || figureId == THREE_ID || figureId == FOUR_ID || figureId == FIVE_ID || figureId == SIX_ID) {
        m_minorScore += scoreForFigure;
        if (m_minorScore >= 63) {
            m_totalScore += 35;
        }
    }

    std::cout << "   <<=>> La figure choisie est " << selectedFigure->getName() << " et a rapporte " << scoreForFigure << " points <<=>>" << std::endl;
}

/**
 * @brief Helper function for the player to choose a figure.
 * @param maxFigures The maximum number of figures the player can choose from.
 */
void Joueur::chooseFigureHelper(const int& maxFigures) {
    int choice;
    bool isNumber;

    displayFigureAndScores();

    bool correctAnswer = false;

    if (maxFigures > m_figures.size()) {
        std::cout << "   /!\\ Error : Le nombre de figure max à recuperer est superieur au nombre de figure du jeu /!\\   " << std::endl;
        return;
    }

    do {
        std::cout << ">> Choisissez maintenant une figure, choix (1-" << maxFigures << ") : ";
        std::cin >> choice;

        // Check if the previous input to the stream was an integer
        isNumber = std::cin.good();

        if (!isNumber) {
            std::cout << "   /!\\ Erreur : Veuillez entrer un chiffre  /!\\ \n";
        }
        else if (choice >= 1 && choice <= maxFigures) {
            std::shared_ptr<Figure> selectedFigure = m_figures[choice - 1];

            // Check if the figure has already been used
            if (isFigureUsed(selectedFigure.get())) {
                std::cout << "Vous avez déjà choisi cette figure. Veuillez choisir une figure différente." << std::endl;
            }
            else {
                int scoreForFigure = selectedFigure->getScore();

                updateScores(scoreForFigure, selectedFigure);

                // Add the selected figure to the list of figures used.
                m_figuresUsed.push_back(selectedFigure);

                correctAnswer = true;
            }
        }
        else {
            std::cout << "   /!\\ Choix invalide. Veuillez choisir une figure valide /!\\  " << std::endl;
        }

        // Clear the error state of the previous error
        std::cin.clear();

        // Ignore the rest of the line
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (!correctAnswer);
}

/**
 * @brief Allows the player to choose a figure in easy mode and other additional modes.
 */
void Joueur::chooseFigureFacileAndPlusModes() {
    chooseFigureHelper(static_cast<int>(m_figures.size()));
}

/**
 * @brief Allows the player to choose a figure in difficult mode and other additional modes.
 * @param NombreMaxOfFigureTopick The maximum number of figures the player can choose.
 */
void Joueur::chooseFigureDifficileAndPlusModes( const int& NombreMaxOfFigureTopick) {
    std::cout << "   <<=>> Vous ne pourrez choisir que la/les " << NombreMaxOfFigureTopick << "er(es) figure(s), cela fait parti du mode de jeu choisit <<=>>   " << std::endl;
    chooseFigureHelper(NombreMaxOfFigureTopick);
}


/*============================================================*/

/** Give the total score of the game in progress.
*   @return : the total score.
**/
int Joueur::getTotalScore() const
{
    return m_totalScore;
}

/**
 * @brief Checks if the figures for the player are empty.
 *
 * @return True if the figures are empty, false otherwise.
 */
bool Joueur::isFiguresEmpty() const {
    return m_figures.size() == 0;
}

/**
 * @brief Calculates the score for each figure based on the given dice values.
 *
 * @param diceValues A vector of integers representing the values of the dices.
 */
void Joueur::calculateFiguresScore(const std::vector<int>& diceValues) const
{
    for(std::shared_ptr<Figure> figure : m_figures){
        figure->calculateScore(diceValues);
    }
}


/*============================================================*/

/**
 * @brief Serialize the player's data to an output stream.
 * @param out The output stream to serialize the data to.
 */
void Joueur::serialize(std::ostream& out) const {
    out << "m_firstYahtzee: " << m_firstYahtzee << "\n";
    out << "m_yahtzeeBonus: " << m_yahtzeeBonus << "\n";
    out << "m_minorScore: " << m_minorScore << "\n";
    out << "m_totalScore: " << m_totalScore << "\n";
 
    out << "m_figuresUsed size: " << m_figuresUsed.size() << "\n";
    for (const auto& figure : m_figuresUsed) {
        figure->serialize(out);
    }
}

/**
 * @brief Deserialize the player's data from an input stream.
 * @param in The input stream to read the data from.
 */
void Joueur::deserialize(std::istream& in) {
    std::string ligne;

    getline(in, ligne);
    m_firstYahtzee = std::stoi(ligne.substr(ligne.find(":") + 1));

    getline(in, ligne);
    m_yahtzeeBonus = std::stoi(ligne.substr(ligne.find(":") + 1));

    getline(in, ligne);
    m_minorScore = std::stoi(ligne.substr(ligne.find(":") + 1));

    getline(in, ligne);
    m_totalScore = std::stoi(ligne.substr(ligne.find(":") + 1));

    getline(in, ligne);
    int tailleFiguresUtilisees = std::stoi(ligne.substr(ligne.find(":") + 1));

    m_figuresUsed.clear();

    for (int i = 0; i < tailleFiguresUtilisees; i++) {
        getline(in, ligne);
        int figureId = std::stoi(ligne.substr(ligne.find(":") + 1));

        std::shared_ptr<Figure> figure = createFigures(figureId);
        if (figure) {
            m_figuresUsed.push_back(figure);
        }
    }
}
