#include "Joueur.h"
#include <algorithm>
#include <iomanip>

//============================================//
//                  PUBLIC                    //
//============================================//

/** Create a player with a total and minor score of 0 and a game grid empty.
**/
Joueur::Joueur() : m_totalScore(0), m_yahtzeeBonus(false), m_minorScore(0), m_firstYahtzee(false), aleardyHardFigureCreated(false ){
    // Already init.
}

/** Destructor for a player, destroy all the vectors with allocated figures.
**/
Joueur::~Joueur() {
    m_figures.clear();
    m_figuresUsed.clear();
}

/** Create all the figures for the minor part if they are not already in the used figures.
**/
void Joueur::createMinorFigures() {
    for (unsigned int i = 1; i <= 6; ++i) {
        std::shared_ptr<Figure> newFigure = createMinorFigure(i);
        if (newFigure && !isFigureUsed(newFigure.get())) {
            m_figures.push_back(newFigure);
        }
    }
}

/** Create all the figures for the major part if they are not alreadyin the used figures.
**/
void Joueur::createMajorFigures() {
    for (unsigned short i = 0; i < 7; ++i) {
        std::shared_ptr<Figure> newFigure = nullptr;
        switch (i) {
        case 0:
            newFigure = std::make_shared<Brelan<7>>();
            break;
        case 1:
            newFigure = std::make_shared<Carre<8>>();
            break;
        case 2:
            newFigure = std::make_shared<Full<9>>();
            break;
        case 3:
            newFigure = std::make_shared<PetiteSuite<10>>();
            break;
        case 4:
            newFigure = std::make_shared<GrandeSuite<11>>();
            break;
        case 5:
            !m_firstYahtzee ? newFigure = std::make_shared<Yahtzee<ID_YAHTZEE_FIRST>>() : newFigure = std::make_shared<Yahtzee<ID_YAHTZEE_BONUS>>();
            break;
        case 6:
            newFigure = std::make_shared<Chance<14>>();
            break;
        }
        if (newFigure && !isFigureUsed(newFigure.get())) {
            m_figures.push_back(newFigure);
        }
    }
}

/** Create the figures for the minor and major part of the game.
**/
void Joueur::createAllFigures() {
    createMinorFigures();
    createMajorFigures();
}

void Joueur::createHardcoreFigures() {
   
    if (!aleardyHardFigureCreated) {
        ordreCreationFiguresHardcore = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
        std::random_shuffle(ordreCreationFiguresHardcore.begin(), ordreCreationFiguresHardcore.end());
        aleardyHardFigureCreated = true;
    }

    for (int i : ordreCreationFiguresHardcore) {
        std::shared_ptr<Figure> newFigure = nullptr;
        switch (i) {
        case 1: newFigure = createMinorFigure(1); break;
        case 2: newFigure = createMinorFigure(2); break;
        case 3: newFigure = createMinorFigure(3); break;
        case 4: newFigure = createMinorFigure(4); break;
        case 5: newFigure = createMinorFigure(5); break;
        case 6: newFigure = createMinorFigure(6); break;
        case 7: newFigure = std::make_shared<Brelan<7>>(); break;
        case 8: newFigure = std::make_shared<Carre<8>>(); break;
        case 9: newFigure = std::make_shared<Full<9>>(); break;
        case 10: newFigure = std::make_shared<PetiteSuite<10>>(); break;
        case 11: newFigure = std::make_shared<GrandeSuite<11>>(); break;
        case 12: !m_firstYahtzee ? newFigure = std::make_shared<Yahtzee<ID_YAHTZEE_FIRST>>() : newFigure = std::make_shared<Yahtzee<ID_YAHTZEE_BONUS>>(); break;
        case 13: newFigure = std::make_shared<Chance<14>>(); break;
        }
        if (newFigure && !isFigureUsed(newFigure.get())) {
            m_figures.push_back(newFigure);
        }
    }
}

bool Joueur::getIsaleardyHardFigureCreated() const {
    return aleardyHardFigureCreated;
}


/** Remove all the figures that we don't use anymore. 
**/
void Joueur::resetFigures() {
    m_figures.clear();
}

/** Display the differents figures possible for a set of dice.
*   @param diveValues : vector of 5 dices.
**/
void Joueur::displayFigureAndScores(const std::vector<int>& diceValues) const {
    std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    std::cout << "|                   YAHTZEE                   |\n";
    std::cout << "|---------------------------------------------|\n";

    for (size_t i = 0; i < m_figures.size(); ++i) {
        int figurescore = m_figures[i]->calculateScore(diceValues);
        std::cout << "| " << std::setw(2) << std::right << i + 1 << " - " << std::setw(19) << std::left << m_figures[i]->getName() << ": ";
        std::cout << std::setw(8) << std::right << figurescore << " points";
        std::cout << std::setw(5) << "|\n";
    }

    std::cout << "|---------------------------------------------|\n";
    std::cout << "| Votre score Total : " << std::setw(14) << std::right << m_totalScore << " points";
    std::cout << std::setw(5) << " |\n";
    std::cout << "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n";
    std::cout << std::endl;
}



void Joueur::chooseFigureHelper(const std::vector<int>& diceValues, const int& maxFigures) {
    int choice;

    displayFigureAndScores(diceValues);

    bool correctAnswer = false;

    if (maxFigures > m_figures.size()) {
        std::cout << "   /!\\ Error : Le nombre de figure max à recuperer est superieur au nombre de figure du jeu /!\\   " << std::endl;
        return;
    }

    do {
        std::cout << ">> Choisissez maintenant une figure, choix (1-" << maxFigures << ") : ";
        std::cin >> choice;

        if (choice >= 1 && choice <= maxFigures) {
            std::shared_ptr<Figure> selectedFigure = m_figures[choice - 1];

            // Vérifier si la figure a déjà été utilisée
            if (isFigureUsed(selectedFigure.get())) {
                std::cout << "Vous avez déjà choisi cette figure. Veuillez choisir une figure différente." << std::endl;
            }
            else {
                int scoreForFigure = selectedFigure->calculateScore(diceValues);

                updateScores(scoreForFigure, selectedFigure);

                // Add the selected figure to the list of figures used.
                m_figuresUsed.push_back(selectedFigure);

                correctAnswer = true;
            }
        }
        else {
            std::cout << "  /!\\ Choix invalide. Veuillez choisir une figure valide. /!\\  " << std::endl;
        }
    } while (!correctAnswer);
}

void Joueur::chooseFigureFacileAndPlusModes(const std::vector<int>& diceValues) {
    chooseFigureHelper(diceValues, m_figures.size());
}

void Joueur::chooseFigureDifficileAndPlusModes(const std::vector<int>& diceValues, const int& NombreMaxOfFigureTopick) {
    std::cout << "   <<=>> Vous ne pourrez choisir que la/les " << NombreMaxOfFigureTopick << "er(es) figure(s), cela fait parti du mode de jeu choisit <<=>>   " << std::endl;
    chooseFigureHelper(diceValues, NombreMaxOfFigureTopick);
}

/** Give the total score of the game in progress.
*   @return : the total score.
**/
int Joueur::getTotalScore() const
{
    return m_totalScore;
}
// TODO : METTRE UN COM
void Joueur::serialize(std::ostream& out) const {
    out << m_firstYahtzee << "\n";
    out << m_yahtzeeBonus << "\n";
    out << m_minorScore << "\n";
    out << m_totalScore << "\n";

    out << m_figures.size() << "\n";
    for (const auto& figure : m_figures) {
        figure->serialize(out);
    }

    out << m_figuresUsed.size() << "\n";
    for (const auto& figure : m_figuresUsed) {
        figure->serialize(out);
    }
}

// TODO : METTRE UN COM
void Joueur::deserialize(std::istream& in) {
    in >> m_firstYahtzee;
    in >> m_yahtzeeBonus;
    in >> m_minorScore;
    in >> m_totalScore;

    size_t taille;
    in >> taille;
    m_figures.resize(taille);
    for (auto& figure : m_figures) {
        int typeId;
        in >> typeId;
        switch (typeId) {
        case 1:
            //figure = new Brelan<65465>();
            break;
        case 2:
            //figure = new SubFigure2();
            break;
            // Ajoutez pour chaque sous-classe de Figure
        default:
            throw std::runtime_error("Type de figure inconnu");
        }
        figure->deserialize(in);
    }

    // Faites de même pour m_figuresUsed
}

//============================================//
//                  PRIVATE                   //
//============================================//

/** Look if the figure pass in parameter is in the used figures.
*   @param figure : the figure that need to be check.
*   @return : true if the figure is in the used figures else false.
*/
bool Joueur::isFigureUsed(Figure* figure) const {
    auto is_figure = [figure](const std::shared_ptr<Figure> usedFigure) {
        return figure->getId() == usedFigure->getId();
        };

    return std::find_if(m_figuresUsed.begin(), m_figuresUsed.end(), is_figure) != std::end(m_figuresUsed);
}

/** Create a figure in the minor part of the game, base on the number on a dice.
*   @param number : the number on a dice (form 1 to 6)
*   @return : the figure associate with it's number.
**/
std::shared_ptr<Figure> Joueur::createMinorFigure(unsigned int number) const {
    switch (number) {
    case 1: return std::make_shared<Number<1>>(number);
    case 2: return std::make_shared<Number<2>>(number);
    case 3: return std::make_shared<Number<3>>(number);
    case 4: return std::make_shared<Number<4>>(number);
    case 5: return std::make_shared<Number<5>>(number);
    case 6: return std::make_shared<Number<6>>(number);
    default: return nullptr;
    }
}

/** For all the figures, look if it's the second Yahtzee and if it's the case then it add 100 points to the player.
*   @param diceValues : vector of 5 dices.
**/
void Joueur::handleYahtzeeBonus(const std::vector<int>& diceValues) {
    for (auto it = m_figures.begin(); it != m_figures.end(); ++it) {
        Figure* figure = it->get();
        if (figure->getId() == ID_YAHTZEE_BONUS) {
            if (!m_yahtzeeBonus && figure->calculateScore(diceValues) > 0) {
                std::cout << "   <<=>> Yahtzee encore ! +100 points <<=>>" << std::endl;
                m_totalScore += 100;
                m_yahtzeeBonus = true;
            }
            m_figures.erase(it);
            break;
        }
    }
}

/** Update the total score base on the points that the selected figure give us.
*   @param scoreForFigure : is the score for the selected figure.
*   @param selectedFigure : the figure selected.
**/
void Joueur::updateScores(int scoreForFigure, std::shared_ptr<Figure> selectedFigure) {
    //const short figureId = selectedFigure->getId();
    const Figure* figure = selectedFigure.get();
    const short figureId = figure->getId();


    if (figureId == ID_YAHTZEE_FIRST && scoreForFigure > 0) {
        m_firstYahtzee = true;
    }

    m_totalScore += scoreForFigure;

    if (figureId >= 1 && figureId <= 6) {
        m_minorScore += scoreForFigure;
        if (m_minorScore >= 63) {
            m_totalScore += 35;
        }
    }

    std::cout << "   <<=>> Vous avez choisi " << selectedFigure->getName() << " et vous avez obtenu " << scoreForFigure << " points <<=>>" << std::endl;

    
}

