#pragma once
#include "Figure.h"

/**
 * @brief Represents the "Chance" figure in the Yahtzee game.
 * @tparam ID The unique identifier for the Chance figure.
 */
template <short ID>
class Chance : public Figure {
public:
    /**
     * @brief Calculates the score for the Chance figure based on the given dice values.
     *
     * This method calculates the score by summing up all the values of the dice.
     *
     * @param diceValues The values of the dice.
     * @return The calculated score for the Chance figure.
     */
    int calculateScore(const std::vector<int>& diceValues)  {
        int sum = 0;
        for (int value : diceValues) {
            sum += value;
        }
        return sum;
    }

    /**
     * @brief Gets the name of the Chance figure.
     * @return The name of the figure.
     */
    std::string getName() const  {
        return "Chance";
    }

    /**
     * @brief Gets the unique identifier of the Chance figure.
     * @return The unique identifier.
     */
    short getId() const  {
        return ID;
    }

    /**
     * @brief Serializes the Chance figure to an output stream.
     * @param out The output stream to serialize the data to.
     */
    void serialize(std::ostream& out) const  {
        out << "id: " << ID << "\n";
    }
};
