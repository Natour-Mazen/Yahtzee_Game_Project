#pragma once
#include "Figure.h"

class Full : public Figure {
public:
    // We can't have default values.
    Full() = delete; 

    Full(int value1, int value2) : m_value1(value1), m_value2(value2)
    {
        // Already init.
    }

    virtual int calculateScore(const std::vector<int>& diceValues) const {
        int count1 = std::count(diceValues.begin(), diceValues.end(), m_value1);
        int count2 = std::count(diceValues.begin(), diceValues.end(), m_value2);
        return (count1 == 3 && count2 == 2 || count1 == 2 && count2 == 3) ? 25 : 0;
    }

    virtual std::string getName() const {
        return "Full de " + std::to_string(m_value1) + " et " + std::to_string(m_value2);
    }
    static const int ID = 3;

private:
    int m_value1;
    int m_value2;
};
