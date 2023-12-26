#pragma once
#include "Figure.h"

class Chance : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) {
        int sum = 0;
        for (int value : diceValues) {
            sum += value;
        }
        return sum;
    }

    virtual std::string getName() const {
        return "Chance";
    }
    static const int ID = 7;
};

