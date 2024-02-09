#include "IA.h"
#include "../enums/figureId.h"

IA::IA() : Joueur(1) {}


/*
 *This code is a member function of the IA class that makes a strategic choice for a figure based on the current values ​​of the dice. Here's how it works:
 
 * Displaying available Figures and scores: The function starts by displaying the available Figures and their scores.
 
 * Finding the best figure: Next, it initializes two variables, maxExpectedScore and bestFigure, to track the maximum expected score and the best figure choice. It goes through all the available
	figures and, for each figure that has not yet been used, it calculates the expected score. If the expected score is higher than the current maximum score, it updates the maximum score and the best figure choice.

 * Updating scores and adding the best figure to the list of used figures: Finally, if a better figure has been found, it updates the scores and adds the best figure to the list of used figures.
    If the best trick ID is equal to YAHTZEEFIRST_ID and the score is greater than 0, it updates the m_firstYahtzee variable to true.

 */

/**
 * @brief Makes a strategic choice for a figure based on the current dice values.
 */
void IA::chooseFigure() {
    // Display available figures and their scores
    displayFigureAndScores();

    // Variables to track the maximum expected score and the best figure choice
    int maxExpectedScore = -1;
    std::shared_ptr<Figure> bestFigure = nullptr;

    // Iterate through all available figures
    for (auto& figure : m_figures) {
        // Check if the figure has already been used
        if (isFigureUsed(figure.get())) continue;

        // Calculate the expected value for this figure
        //const double expectedValue = calculateExpectedValue(figure);

        // Calculate the expected score for this figure
        const int expectedScore = figure->getScore();

        // If the expected score is higher than the current maximum score, update the maximum score and the best figure choice
        if (expectedScore >= maxExpectedScore) {
            maxExpectedScore = expectedScore;
            bestFigure = figure;
        }
    }

    // Update the scores and add the best figure to the list of used figures
    if (bestFigure != nullptr) {
	    const int score = bestFigure->getScore();

        if (bestFigure.get()->getId() == YAHTZEEFIRST_ID && score > 0) {
            m_firstYahtzee = true;
        }
        updateScores(score, bestFigure);
        m_figuresUsed.push_back(bestFigure);
    }
}

double IA::calculateExpectedValue(std::shared_ptr<Figure>& figure) {
    // Calculate the current score of the figure
    double expectedValue = figure->getScore();

    // Estimate the potential score in future rounds
    // This is a simplified example and the actual calculation would depend on the rules of Yahtzee
    for (int round = 0; round < remainingRounds(); ++round) {
        expectedValue += estimatePotentialScore(figure, round);
    }

    return expectedValue;
}

double IA::estimatePotentialScore(std::shared_ptr<Figure>& figure, int round) {
    // Estimate the potential score of the figure in a future round
    // This is a placeholder implementation and the actual calculation would depend on the rules of Yahtzee
    return figure->getScore() / (round + 1);
}

int IA::remainingRounds() {
    // Calculate the remaining rounds
    // This is a placeholder implementation and the actual calculation would depend on the rules of Yahtzee
    return 13 - m_figuresUsed.size();
}



