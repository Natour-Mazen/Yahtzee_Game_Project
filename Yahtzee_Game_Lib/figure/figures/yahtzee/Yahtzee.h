#pragma once
#include "Figure.h"

class Yahtzee : public Figure {
public:
    // We can't have a default value.
    Yahtzee() = delete;

    Yahtzee(int value) : m_value(value){
        // Already init.
    }

    virtual int calculateScore(const std::vector<int>& diceValues) const {
        int count = std::count(diceValues.begin(), diceValues.end(), m_value);
        return (count == 5) ? 50 : 0;
    }

    virtual std::string getName() const {
        return "Yahtzee de " + std::to_string(m_value);
    }
    static const int ID = 6;

private:
    int m_value;
};
