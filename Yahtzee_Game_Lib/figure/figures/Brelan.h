#pragma once
#include "Figure.h"

/**
 * @brief Represents the "Brelan" figure in the Yahtzee game.
 * @tparam ID The unique identifier for the Brelan figure.
 */
template <short ID>
class Brelan : public Figure {
public:
    /**
     * @brief Gets the name of the Brelan figure.
     * @return The name of the figure.
     */
    std::string getName() const override {
        if (m_value == 0) {
            return "Brelan";
        }
        return "Brelan de " + std::to_string(m_value);
    }

    /**
     * @brief Gets the unique identifier of the Brelan figure.
     * @return The unique identifier.
     */
    short getId() const override {
        return ID;
    }

    /**
     * @brief Serializes the Brelan figure to an output stream.
     * @param out The output stream to serialize the data to.
     */
    void serialize(std::ostream& out) const override {
        out << "id: " << ID << "\n";
        out << "score: " << m_score << "\n";
    }

protected:
    /**
     * @brief Calculates the score for the Brelan figure based on the given dice values.
     *
     * This method checks if there are at least three dice with the same value,
     * and if so, it sets the value of the Brelan to that dice value and returns
     * the calculated score, which is three times the dice value. If no Brelan is
     * found, the score is 0.
     *
     * @param diceValues The values of the dice.
     * @return The calculated score for the Brelan figure.
     */
    int justCalculateScore(const std::vector<int>& diceValues) override {
        for (unsigned short i = 1; i <= 6; ++i) {
            int count = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), i));
            if (count >= 3) {
                m_value = i;
                return 3 * i;
            }
        }
        return 0;
    }

private:
    short m_value = 0;  ///< The value of the Brelan figure.
};
