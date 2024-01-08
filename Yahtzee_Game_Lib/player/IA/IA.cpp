#include "IA.h"
#include "../enums/figureId.h"

IA::IA() : Joueur() {}

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


