#pragma once
#include "Figure.h"

/**
 * @brief Represents the "Grande Suite" figure in the Yahtzee game.
 * @tparam ID The unique identifier for the Grande Suite figure.
 */
template <short ID>
class GrandeSuite : public Figure {
public:
    /**
     * @brief Gets the name of the Grande Suite figure.
     * @return The name of the figure.
     */
    std::string getName() const  {
        return "Grande Suite";
    }

    /**
     * @brief Gets the unique identifier of the Grande Suite figure.
     * @return The unique identifier.
     */
    short getId() const  {
        return ID;
    }

    /**
     * @brief Serializes the Grande Suite figure to an output stream.
     * @param out The output stream to serialize the data to.
     */
    void serialize(std::ostream& out) const  {
        out << "id: " << ID << "\n";
    }

protected:
    /**
     * @brief Calculates the score for the Grande Suite figure based on the given dice values.
     *
     * This method calculates the score for a Grande Suite figure, where the score is 40 if the dice values
     * form a sequence of five consecutive numbers, and 0 otherwise.
     *
     * @param diceValues The values of the dice.
     * @return The calculated score for the Grande Suite figure.
     */
    int justCalculateScore(const std::vector<int>& diceValues) {
        std::vector<int> sortedValues(diceValues);
        std::sort(sortedValues.begin(), sortedValues.end());

        for (std::size_t i = 0; i < sortedValues.size() - 1; ++i) {
            if (sortedValues[i + 1] - sortedValues[i] != 1) {
                return 0;
            }
        }
        return 40;
    }
};
