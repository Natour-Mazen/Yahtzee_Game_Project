#pragma once
#include "Figure.h"

template<short ID>
class Number : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        int score = 0;
        for (int value : diceValues) {
            if (value == ID) {
                score += value;
            }
        }
        return score;
    }

    std::string getName() const {
        return "Number " + std::to_string(ID);
    }

    short getId() const {
        return ID;
    }
};


