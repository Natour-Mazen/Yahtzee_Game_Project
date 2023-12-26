#pragma once
#include "Figure.h"

class Carre : public Figure {
public:
    Carre() : Figure(2) {}

    virtual int calculateScore(const std::vector<int>& diceValues) {
        for (unsigned short i = 1; i <= 6; ++i) {
            int count = std::count(diceValues.begin(), diceValues.end(), i);
            if (count >= 4) {
                m_value = i;
                return count * i;
            }
        }
        return 0;
    }

    virtual std::string getName() const {
        return "Carré de " + std::to_string(m_value);
    }

private:
    short m_value = 0;
};


