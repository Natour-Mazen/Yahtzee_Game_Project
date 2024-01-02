#pragma once
#include "Figure.h"

/**
 * @brief Represents the "Yahtzee" figure in the Yahtzee game.
 * @tparam ID The unique identifier for the Yahtzee figure.
 */
template <short ID>
class Yahtzee : public Figure {
public:
    /**
     * @brief Calculates the score for the Yahtzee figure based on the given dice values.
     *
     * This method calculates the score for a Yahtzee figure, where the score is 50 if at least five dice
     * have the same value, and 0 otherwise.
     *
     * @param diceValues The values of the dice.
     * @return The calculated score for the Yahtzee figure.
     */
    int calculateScore(const std::vector<int>& diceValues)  {
        for (unsigned int i = 1; i <= 6; ++i) {
            int count = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), i));
            if (count >= 5) {
                return 50;
            }
        }
        return 0;
    }

    /**
     * @brief Gets the name of the Yahtzee figure.
     * @return The name of the figure.
     */
    std::string getName() const  {
        return "Yahtzee";
    }

    /**
     * @brief Gets the unique identifier of the Yahtzee figure.
     * @return The unique identifier.
     */
    short getId() const  {
        return ID;
    }

    /**
     * @brief Serializes the Yahtzee figure to an output stream.
     * @param out The output stream to serialize the data to.
     */
    void serialize(std::ostream& out) const  {
        out << "id: " << ID << "\n";
    }
};
