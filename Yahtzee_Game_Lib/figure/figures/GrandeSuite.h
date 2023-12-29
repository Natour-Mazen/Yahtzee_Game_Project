#pragma once
#include "Figure.h"

template<short ID>
class GrandeSuite : public Figure {
public:
    int calculateScore(const std::vector<int>& diceValues) {
        std::vector<int> sortedValues(diceValues);
        std::sort(sortedValues.begin(), sortedValues.end());

        for (std::size_t i = 0; i < sortedValues.size() - 1; ++i) {
            if (sortedValues[i + 1] - sortedValues[i] != 1) {
                return 0;
            }
        }
        return 40;
    }

    std::string getName() const {
        return "Grande Suite";
    }

    short getId() const {
        return ID;
    }

    void serialize(std::ostream& out) const {
        // La classe GrandeSuite n'a pas de membres de données à sérialiser
    }

    void deserialize(std::istream& in) {
        // La classe GrandeSuite n'a pas de membres de données à désérialiser
    }
};


