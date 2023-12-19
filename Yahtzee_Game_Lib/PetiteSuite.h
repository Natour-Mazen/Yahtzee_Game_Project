#pragma once
#include "Figure.h"

class PetiteSuite : public Figure {
public:
    virtual int calculateScore(const std::vector<int>& diceValues) const {
        std::vector<int> uniqueValues(diceValues.begin(), diceValues.end());
        std::sort(uniqueValues.begin(), uniqueValues.end());

        for (size_t i = 0; i < uniqueValues.size() - 1; ++i) {
            if (uniqueValues[i + 1] - uniqueValues[i] != 1) {
                return 0;
            }
        }

        return 30;
    }

    virtual std::string getName() const {
        return "Petite Suite";
    }
    static const int ID = 4;
};
