#pragma once
#include "Figure.h"

/**
 * @brief Represents a generic "Number" figure in the Yahtzee game.
 * @tparam ID The unique identifier for the Number figure.
 */
template <short ID>
class Number : public Figure {
public:
    /**
     * @brief Constructs a Number figure with the specified number.
     * @param number The number associated with the figure.
     */
    Number(unsigned int number) : m_number(number) {}

    /**
     * @brief Gets the name of the Number figure.
     * @return The name of the figure.
     */
    std::string getName() const  {
        return "Somme des " + std::to_string(m_number);
    }

    /**
     * @brief Gets the unique identifier of the Number figure.
     * @return The unique identifier.
     */
    short getId() const  {
        return ID;
    }

    /**
     * @brief Serializes the Number figure to an output stream.
     * @param out The output stream to serialize the data to.
     */
    void serialize(std::ostream& out) const  {
        out << "id: " << ID << "\n";
    }

protected:
    /**
     * @brief Calculates the score for the Number figure based on the given dice values.
     *
     * This method calculates the score for a Number figure, where the score is the sum of the dice values
     * that match the specified number.
     *
     * @param diceValues The values of the dice.
     * @return The calculated score for the Number figure.
     */
    int justCalculateScore(const std::vector<int>& diceValues) {
        int score = 0;
        for (int value : diceValues) {
            if (value == m_number) {
                score += value;
            }
        }
        return score;
    }

private:
    unsigned int m_number;  ///< The number associated with the Number figure.
};
