#pragma once
#include "Figure.h"

template<short ID>
class Full : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        for (int i = 1; i <= 6; ++i)
        {
            int count1 = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), i));
            if (count1 == 2 || count1 == 3) {
                for (int y = i + 1; y <= 6; ++y)
                {
                    int count2 = static_cast<int>(std::count(diceValues.begin(), diceValues.end(), y));
                    if (count1 == 2 && count2 == 3 || count1 == 3 && count2 == 2) {
                        m_value1 = i;
                        m_value2 = y;
                        return 25;
                    }
                }
            }
        }
        return 0;
    }

    std::string getName() const {
        if (m_value1 == 0) {
            return "Full";
        }
        return "Full de " + std::to_string(m_value1) + " et " + std::to_string(m_value2);
    }

    short getId() const {
        return ID;
    }

    void serialize(std::ostream& out) const {
        out << m_value1 << "\n";
        out << m_value2 << "\n";
    }

    void deserialize(std::istream& in) {
        in >> m_value1;
        in >> m_value2;
    }

private:
    int m_value1 = 0;
    int m_value2 = 0;
};
