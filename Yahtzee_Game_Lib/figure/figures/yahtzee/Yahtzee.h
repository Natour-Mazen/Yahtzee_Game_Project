#pragma once
#include "Figure.h"

class Yahtzee : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) {
        for (unsigned short i = 1; i <= 6; ++i) {
            int count = std::count(diceValues.begin(), diceValues.end(), i);
            if (count >= 5) {
                m_value = i;
                return count * i;
            }
        }
        return 0;
    }

    virtual std::string getName() const {
        return "Yahtzee de " + std::to_string(m_value);
    }
    static const int ID = 6;

private:
    int m_value = 0;
};
