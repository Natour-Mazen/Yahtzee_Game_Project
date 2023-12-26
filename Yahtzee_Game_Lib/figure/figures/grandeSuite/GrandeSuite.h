#pragma once
#include "Figure.h"

class GrandeSuite : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) {
        std::vector<int> sortedValues(diceValues);
        std::sort(sortedValues.begin(), sortedValues.end());

        for (unsigned short i = 0; i < sortedValues.size() - 1; ++i) {
            if (sortedValues[i + 1] - sortedValues[i] != 1) {
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


