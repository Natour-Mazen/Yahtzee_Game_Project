#pragma once
#include "Figure.h"

class PetiteSuite : public Figure {
public:
    PetiteSuite() : Figure(4) {}

    virtual int calculateScore(const std::vector<int>& diceValues) {
        std::vector<int> sortedValues(diceValues);
        std::sort(sortedValues.begin(), sortedValues.end());

        for (unsigned char y = 0; y < 2; ++y) {
            bool valid = true;
            for (unsigned short i = y; i < 4 + y; ++i) {
                if (sortedValues[i] != sortedValues[i + 1] - 1) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                return 30;
            }
        }
        return 0;
    }

    virtual std::string getName() const {
        return "Petite Suite";
    }
};
