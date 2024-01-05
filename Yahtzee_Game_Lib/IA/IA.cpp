#include "IA.h"

IA::IA() : Joueur() {}

/**
 * @brief Makes a strategic choice for a figure based on the current dice values.
 * @param diceValues The values obtained from the rolled dice.
 */
void IA::chooseFigure(const std::vector<int>& diceValues) {
    // Display available figures and their scores
    displayFigureAndScores(diceValues);

    // Variables to track the maximum expected score and the best figure choice
    int maxExpectedScore = -1;
    std::shared_ptr<Figure> bestFigure = nullptr;

    // Iterate through all available figures
    for (auto& figure : m_figures) {
        // Check if the figure has already been used
        if (isFigureUsed(figure.get())) continue;

        // Calculate the expected score for this figure
        int expectedScore = figure->calculateScore(diceValues);

        // If the expected score is higher than the current maximum score, update the maximum score and the best figure choice
        if (expectedScore >= maxExpectedScore) {
            maxExpectedScore = expectedScore;
            bestFigure = figure;
        }
    }

    // Update the scores and add the best figure to the list of used figures
    if (bestFigure != nullptr) {
        int score = bestFigure->calculateScore(diceValues);
        updateScores(score, bestFigure);
        m_figuresUsed.push_back(bestFigure);
    }
}


