#pragma once
#include "Figure.h"

class Full : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) {
        for (unsigned short i = 1; i <= 6; ++i)
        {
            int count1 = std::count(diceValues.begin(), diceValues.end(), i);
            for (unsigned short y = i + 1; y <= 6; ++y)
            {
                int count2 = std::count(diceValues.begin(), diceValues.end(), y);
                if (count1 == 2 && count2 == 3 || count1 == 3 && count2 == 2) {
                    m_value1 = i;
                    m_value2 = y;
                    return 25;
                }
            }
        }
        return 0;
    }

    virtual std::string getName() const {
        return "Full de " + std::to_string(m_value1) + " et " + std::to_string(m_value2);
    }
    static const int ID = 3;

private:
    int m_value1 = 0;
    int m_value2 = 0;
};
