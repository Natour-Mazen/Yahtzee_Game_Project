#pragma once
#include "Figure.h"

template<int Value>
class Brelan : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) const {
        int count = std::count(diceValues.begin(), diceValues.end(), Value);
        return (count >= 3) ? count * Value : 0;
    }

    virtual std::string getName() const {
        return "Brelan de " + std::to_string(Value);
    }
    static const int ID = 1;
};
