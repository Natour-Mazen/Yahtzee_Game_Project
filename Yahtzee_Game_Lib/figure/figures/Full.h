#pragma once
#include "Figure.h"

/**
 * @brief Represents the "Full" figure in the Yahtzee game.
 * @tparam ID The unique identifier for the Full figure.
 */
template <short ID>
class Full : public Figure {
public:
    /**
     * @brief Gets the name of the Full figure.
     * @return The name of the figure.
     */
    std::string getName() const  {
        if (m_value1 == 0) {
            return "Full";
        }
        return "Full de " + std::to_string(m_value1) + " et " + std::to_string(m_value2);
    }

    /**
     * @brief Gets the unique identifier of the Full figure.
     * @return The unique identifier.
     */
    short getId() const  {
        return ID;
    }

    /**
     * @brief Serializes the Full figure to an output stream.
     * @param out The output stream to serialize the data to.
     */
    void serialize(std::ostream& out) const  {
        out << "id: " << ID << "\n";
        out << "score: " << m_score << "\n";
    }

protected:
    /**
     * @brief Calculates the score for the Full figure based on the given dice values.
     *
     * This method calculates the score for a Full figure, where there are two dice with one value
     * and three dice with another value.
     *
     * @param diceValues The values of the dice.
     * @return The calculated score for the Full figure.
     */
    int justCalculateScore(const std::vector<int>& diceValues) {
        for (int i = 1; i <= 6; ++i) {
            int count1 = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), i));
            if (count1 == 2 || count1 == 3) {
                for (int y = i + 1; y <= 6; ++y) {
                    int count2 = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), y));
                    if ((count1 == 2 && count2 == 3) || (count1 == 3 && count2 == 2)) {
                        m_value1 = i;
                        m_value2 = y;
                        return 25;
                    }
                }
            }
        }
        return 0;
    }

private:
    int m_value1 = 0;  ///< The first value for the Full figure.
    int m_value2 = 0;  ///< The second value for the Full figure.
};
