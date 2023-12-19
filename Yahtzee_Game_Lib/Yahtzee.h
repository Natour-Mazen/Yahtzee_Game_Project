#pragma once
#include "Figure.h"

template<int Value>
class Yahtzee : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) const {
        int count = std::count(diceValues.begin(), diceValues.end(), Value);
        return (count == 5) ? 50 : 0;
    }

    virtual std::string getName() const {
        return "Yahtzee de " + std::to_string(Value);
    }
    static const int ID = 6;
};
