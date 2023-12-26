#pragma once
#include "Figure.h"

class Brelan : public Figure {
public:
    Brelan() : Figure(1) {}

    virtual int calculateScore(const std::vector<int>& diceValues) {
        for (unsigned short i = 1; i <= 6; ++i) {
            int count = std::count(diceValues.begin(), diceValues.end(), i);
            if (count >= 3) {
                m_value = i;
                return count * i;
            }
        }
        return 0;
    }

    virtual std::string getName() const {
        return "Brelan de " + std::to_string(m_value);
    }

private:
    short m_value = 0;
};
