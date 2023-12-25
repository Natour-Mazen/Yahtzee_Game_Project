#pragma once
#include "Figure.h"

template<int Value>
class Carre : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) const {
        int count = std::count(diceValues.begin(), diceValues.end(), Value);
        return (count >= 4) ? count * Value : 0;
    }

    virtual std::string getName() const {
        return "Carré de " + std::to_string(Value);
    }
    static const int ID = 2;
};


