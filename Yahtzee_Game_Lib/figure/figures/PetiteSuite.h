#pragma once
#include "Figure.h"

/**
 * @brief Represents the "Petite Suite" figure in the Yahtzee game.
 * @tparam ID The unique identifier for the Petite Suite figure.
 */
template <short ID>
class PetiteSuite : public Figure {
public:
    /**
     * @brief Calculates the score for the Petite Suite figure based on the given dice values.
     *
     * This method calculates the score for a Petite Suite figure, where the score is 30 if there is a sequence
     * of four consecutive dice values (e.g., 1-2-3-4 or 2-3-4-5), and 0 otherwise.
     *
     * @param diceValues The values of the dice.
     * @return The calculated score for the Petite Suite figure.
     */
    int calculateScore(const std::vector<int>& diceValues)  {
        std::vector<int> sortedValues(diceValues);
        std::sort(sortedValues.begin(), sortedValues.end());

        for (std::size_t y = 0; y < 2; ++y) {
            bool valid = true;
            for (std::size_t i = y; i < 3 + y; ++i) {
                if (sortedValues[i] != sortedValues[i + 1] - 1) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                return 30;
            }
        }
        return 0;
    }

    /**
     * @brief Gets the name of the Petite Suite figure.
     * @return The name of the figure.
     */
    std::string getName() const  {
        return "Petite Suite";
    }

    /**
     * @brief Gets the unique identifier of the Petite Suite figure.
     * @return The unique identifier.
     */
    short getId() const  {
        return ID;
    }

    /**
     * @brief Serializes the Petite Suite figure to an output stream.
     * @param out The output stream to serialize the data to.
     */
    void serialize(std::ostream& out) const  {
        out << "id: " << ID << "\n";
    }
};
