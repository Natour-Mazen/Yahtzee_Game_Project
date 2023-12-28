#pragma once
#include "Figure.h"

template<short ID>
class Chance : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        int sum = 0;
        for (int value : diceValues) {
            sum += value;
        }
        return sum;
    }

    std::string getName() const {
        return "Chance";
    }

    short getId() const {
        return m_id;
    }

private:
    static const int m_id = ID;
};

