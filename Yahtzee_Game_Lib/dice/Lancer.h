#pragma once
#include <vector>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <limits>


class Lancer {
public:
    const std::vector<int>& getDiceValues() const;
    void rollDices();
    void printDices();
    void reRollDices();

private:
    std::vector<int> m_diceValues;
    bool askReroll();
    std::vector<int> getDiceIndicesToReroll();
};

