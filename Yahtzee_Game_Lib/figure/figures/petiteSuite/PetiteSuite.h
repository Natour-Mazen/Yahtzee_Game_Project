#pragma once
#include "Figure.h"

template<short ID>
class PetiteSuite : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        std::vector<int> sortedValues(diceValues);
        std::sort(sortedValues.begin(), sortedValues.end());

        for (std::size_t y = 0; y < 2; ++y) {
            bool valid = true;
            for (std::size_t i = y; i < 4 + y; ++i) {
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

    std::string getName() const {
        return "Petite Suite";
    }

    short getId() const {
        return m_id;
    }

private:
    static const int m_id = ID;
};
