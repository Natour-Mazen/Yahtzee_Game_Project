#pragma once
#include "Figure.h"

template<int Value1, int Value2>
class Full : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) const {
        int count1 = std::count(diceValues.begin(), diceValues.end(), Value1);
        int count2 = std::count(diceValues.begin(), diceValues.end(), Value2);
        return (count1 == 3 && count2 == 2) ? 25 : 0;
    }

    virtual std::string getName() const {
        return "Full de " + std::to_string(Value1) + " et " + std::to_string(Value2);
    }
    static const int ID = 3;
};
