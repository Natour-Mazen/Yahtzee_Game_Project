#pragma once
#include "Figure.h"

/**
 * @brief Represents the "Carre" figure in the Yahtzee game.
 * @tparam ID The unique identifier for the Carre figure.
 */
template <short ID>
class Carre : public Figure {
public:
    /**
     * @brief Calculates the score for the Carre figure based on the given dice values.
     *
     * This method checks if there are at least four dice with the same value,
     * and if so, it sets the value of the Carre to that dice value and returns
     * the calculated score, which is four times the dice value. If no Carre is
     * found, the score is 0.
     *
     * @param diceValues The values of the dice.
     * @return The calculated score for the Carre figure.
     */
    int calculateScore(const std::vector<int>& diceValues) override {
        for (unsigned short i = 1; i <= 6; ++i) {
            int count = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), i));
            if (count >= 4) {
                m_value = i;  // Set the value of the Carre to the dice value found
                return 4 * i;  // Return the calculated score (four times the dice value)
            }
        }
        return 0;  // Return 0 if no Carre is found
    }

    /**
     * @brief Gets the name of the Carre figure.
     * @return The name of the figure.
     */
    std::string getName() const override {
        if (m_value == 0) {
            return "Carre";
        }
        return "Carre de " + std::to_string(m_value);
    }

    /**
     * @brief Gets the unique identifier of the Carre figure.
     * @return The unique identifier.
     */
    short getId() const override {
        return ID;
    }

    /**
     * @brief Serializes the Carre figure to an output stream.
     * @param out The output stream to serialize the data to.
     */
    void serialize(std::ostream& out) const override {
        out << "id: " << ID << "\n";
    }

private:
    short m_value = 0;  ///< The value of the Carre figure.
};
