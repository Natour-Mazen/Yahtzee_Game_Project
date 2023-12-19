#pragma once
#include "Figure.h"

class GrandeSuite : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) const {
        std::vector<int> sortedValues(diceValues);
        std::sort(sortedValues.begin(), sortedValues.end());

        for (int i = 0; i < 4; ++i) {
            if (sortedValues[i] != sortedValues[i + 1] - 1) {
                return 0;
            }
        }

        return 40;
    }

    virtual std::string getName() const {
        return "Grande Suite";
    }
    static const int ID = 5;
};


