#pragma once
#include <vector>


class Lancer {
private:
    std::vector<int> diceValues;
public:
    std::vector<int> getDiceValues() const {
        return diceValues;
    };

    void rollDice() {
        diceValues.clear();
        for (int i = 0; i < 5; ++i) {
            diceValues.push_back(rand() % 6 + 1);
        }
    }
};

